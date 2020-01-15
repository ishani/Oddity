using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using BadgeCore;


namespace BadgeUI
{
  public partial class FrameStripControl : UserControl
  {
    private FrameStrip m_strip;
    private Font m_frameFont;
    private SolidBrush m_frameBrush;

    internal static readonly Int32 LedsSize = (10 * Frame.EdgeLEDCount);
    internal static readonly Int32 LedsSizePlusMargin = ((10 * Frame.EdgeLEDCount) + 4);

    public FrameStripControl()
    {
      InitializeComponent();

      this.SetStyle(
          ControlStyles.UserPaint |
          ControlStyles.AllPaintingInWmPaint |
          ControlStyles.DoubleBuffer, true);

      m_frameFont = new Font("Tahoma", 8);
      m_frameBrush = new SolidBrush(Color.WhiteSmoke);

      m_strip = new FrameStrip();
      m_strip.FrameDataChanged += RefreshOnEvent;
      m_strip.SelectionChange += RefreshOnEvent;
      m_strip.StripContentsChanged += StripContentsChanged;

      UpdateScroll();
    }

    public FrameStrip Data()
    {
      return m_strip;
    }

    void RefreshOnEvent(object sender, EventArgs e)
    {
      Refresh();
    }

    void StripContentsChanged(Frame frame, bool added, bool autoselect)
    {
      UpdateScroll();

      if ((frame != null) && added && autoselect)
      {
        Int32 scrollOff = (ClientSize.Width / LedsSizePlusMargin);

        Int32 index = m_strip.getIndexForFrame(frame);
        if (hwScroll.Value + scrollOff <= index)
          hwScroll.Value = (index - scrollOff) + 1;
      }
    }


    private void UpdateScroll()
    {
      Int32 viewMax = (m_strip.NumFrames - (ClientSize.Width / LedsSizePlusMargin));
      if (viewMax < 0)
        viewMax = 0;
      hwScroll.Maximum = viewMax;
      hwScroll.Update();
      Refresh();
    }


    private void hwScroll_ValueChanged(object sender, EventArgs e)
    {
      Refresh();
    }

    private void FrameStrip_Paint(object sender, PaintEventArgs e)
    {
      e.Graphics.Clear(Color.Black);
      e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;

      Pen selPen = new Pen(Color.Orange, 1.5f);
      SolidBrush bgBrush = new SolidBrush(Color.Black);
      SolidBrush dotBrush = new SolidBrush(Color.FromArgb(40, 40, 40));
      SolidBrush brBrush = new SolidBrush(Color.LightGray);

      Int32 drawStart = hwScroll.Value;
      Int32 drawEnd = drawStart + (ClientSize.Width / LedsSizePlusMargin);
      if (drawEnd > m_strip.NumFrames)
        drawEnd = m_strip.NumFrames;

      Int32 brightS = (ClientSize.Height - 110) + 34;
      Int32 brightE = (ClientSize.Height - 22);

      Int32 brightH = (brightE - brightS);
      float brightD = (float)brightH;

      Int32 Sx = ClientRectangle.Left + 4;
      Int32 Sy = ClientRectangle.Top + 4;

      e.Graphics.DrawLine(new Pen(Color.DimGray), 0, brightS - 3, ClientRectangle.Width, brightS - 3);

      for (Int32 i = drawStart; i < drawEnd; i++)
      {
        e.Graphics.FillRectangle(bgBrush, Sx, Sy, LedsSize, LedsSize);

        Frame f = m_strip.getFrameAtIndex(i);

        if (m_strip.SelectedFrame == f)
          e.Graphics.DrawRectangle(selPen, Sx - 2, Sy - 2, LedsSizePlusMargin, LedsSizePlusMargin);

        for (Int32 y = 0; y < Frame.EdgeLEDCount; y++)
        {
          for (Int32 x = 0; x < Frame.EdgeLEDCount; x++)
          {
            Byte ledR, ledG;
            f.getLED(x, y, out ledR, out ledG);

            Int32 led_red = 40 + ledR * 70;
            Int32 led_green = 40 + ledG * 70;

            dotBrush.Color = Color.FromArgb(led_red, led_green, 40);

            e.Graphics.FillRectangle(dotBrush, Sx + (x * 10), Sy + (y * 10), 10, 10);
          }
        }

        Int32 frameText = i + 1;
        e.Graphics.DrawString(frameText.ToString(), m_frameFont, m_frameBrush, Sx + 2, Sy + LedsSizePlusMargin);

        // brightness

        Int32 bScale = (Int32)(f.BrightnessAsFloat * brightD);
        e.Graphics.FillRectangle(brBrush, Sx, brightS + (brightH - bScale), LedsSize, bScale);


        Sx += LedsSizePlusMargin;
      }
    }

    private bool selectingFrames = true;

    private void FrameStrip_MouseDown(object sender, MouseEventArgs e)
    {
      if (e.Button != MouseButtons.Left)
        return;

      Int32 brightS = (ClientSize.Height - 110) + 34;

      Int32 sIndex = ((e.X - 4) / LedsSizePlusMargin) + hwScroll.Value;
      if (sIndex >= 0 && sIndex < m_strip.NumFrames)
      {
        if (e.Y < brightS)
        {
          selectingFrames = true;

          m_strip.SelectedFrame = m_strip.getFrameAtIndex(sIndex);
        }
        else
        {
          selectingFrames = false;

          Int32 brightE = (ClientSize.Height - 22);

          float brightH = (float)(brightE - brightS);
          float brightD = (float)brightH / 255.0f;

          float newBright = 1.0f - ((float)(e.Y - brightS) / brightH);
          if (newBright < 0.0f)
            newBright = 0.0f;
          if (newBright > 1.0f)
            newBright = 1.0f;

          Int32 newBrightInt = (Int32)(newBright * 256.0f);
          newBrightInt -= (newBrightInt % 16);
          if (newBrightInt > 255)
            newBrightInt = 255;
          m_strip.getFrameAtIndex(sIndex).Brightness = (Byte)newBrightInt;
          Refresh();
        }
      }
    }

    private void FrameStrip_MouseMove(object sender, MouseEventArgs e)
    {
      if (e.Button != MouseButtons.Left)
        return;

      Int32 brightS = (ClientSize.Height - 110) + 32;

      Int32 sIndex = ((e.X - 4) / LedsSizePlusMargin) + hwScroll.Value;
      if (sIndex >= 0 && sIndex < m_strip.NumFrames)
      {
        if (selectingFrames)
        {
          m_strip.SelectedFrame = m_strip.getFrameAtIndex(sIndex);
        }
        else
        {
          Int32 brightE = (ClientSize.Height - 22);

          float brightH = (float)(brightE - brightS);
          float brightD = (float)brightH / 255.0f;

          float newBright = 1.0f - ((float)(e.Y - brightS) / brightH);
          if (newBright < 0.0f)
            newBright = 0.0f;
          if (newBright > 1.0f)
            newBright = 1.0f;

          Int32 newBrightInt = (Int32)(newBright * 256.0f);
          newBrightInt -= (newBrightInt % 16);
          if (newBrightInt > 255)
            newBrightInt = 255;
          m_strip.getFrameAtIndex(sIndex).Brightness = (Byte)newBrightInt;
          Refresh();
        }
      }
    }
  }
}