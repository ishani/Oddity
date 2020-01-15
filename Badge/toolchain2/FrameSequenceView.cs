using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

using MatrixCore;

namespace Matrix
{
  public partial class FrameSequenceView : UserControl
  {
    private FrameSequence m_strip;
    private Font m_frameFont;
    private SolidBrush m_frameBrush;
    private LEDColouring m_colouring = new LEDColouring();


    public FrameSequenceView()
    {
      InitializeComponent();

      this.SetStyle(
          ControlStyles.UserPaint |
          ControlStyles.AllPaintingInWmPaint |
          ControlStyles.DoubleBuffer, true);

      m_frameFont = new Font("Tahoma", 8);
      m_frameBrush = new SolidBrush(Color.WhiteSmoke);

      m_strip = new FrameSequence();
      m_strip.FrameDataChanged += RefreshOnEvent;
      m_strip.SelectionChange += RefreshOnEvent;
      //m_strip.StripContentsChanged += StripContentsChanged;

      UpdateScroll();
    }

    public FrameSequence Sequence
    {
      get { return m_strip; }
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
        Int32 scrollOff = (ClientSize.Width / 84);

        Int32 index = m_strip.IndexForFrame(frame);
        if (hwScroll.Value + scrollOff <= index)
          hwScroll.Value = (index - scrollOff) + 1;
      }
    }

    private void UpdateScroll()
    {
      Int32 viewMax = (m_strip.NumFrames - (ClientSize.Width / 84));
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

    private void FrameSequenceView_Paint(object sender, PaintEventArgs e)
    {
      e.Graphics.Clear(Color.Black);
      e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.Default;

      Pen selPen = new Pen(Color.Orange, 1.0f);
      selPen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;

      SolidBrush brBrush = new SolidBrush(Color.White);

      Int32 drawStart = hwScroll.Value;
      Int32 drawEnd = drawStart + (ClientSize.Width / 84);
      if (drawEnd > m_strip.NumFrames)
        drawEnd = m_strip.NumFrames;

      Int32 brightS = (ClientSize.Height - 110) + 34;
      Int32 brightE = (ClientSize.Height - 22);

      Int32 brightH = (brightE - brightS);
      float brightD = (float)brightH;

      Int32 Sx = ClientRectangle.Left + 4;
      Int32 Sy = ClientRectangle.Top + 4;

      e.Graphics.DrawLine(new Pen(Color.DimGray), 0, brightS - 4, ClientRectangle.Width, brightS - 4);

      for (Int32 i = drawStart; i < drawEnd; i++)
      {
        Frame f = m_strip.FrameAtIndex(i);

        if (m_strip.SelectedFrame == f)
          e.Graphics.DrawRectangle(selPen, Sx - 2, Sy - 2, 83, 83);

        f.Iterate((Int32 x, Int32 y, LED led) =>
          {
            e.Graphics.FillRectangle(
              m_colouring.BrushForLED(ref led), 
              Sx + (x * 10), 
              Sy + (y * 10), 
              10, 
              10);
          }
        );


        Int32 frameText = i + 1;
        e.Graphics.DrawString(frameText.ToString(), m_frameFont, m_frameBrush, Sx + 2, Sy + 83);

        // brightness indicator
        Int32 bScale = (Int32)(f.BrightnessAsFloat * brightD);
        Int32 bAlpha = 100 + (Int32)(f.BrightnessAsFloat * 155.0f);

        brBrush.Color = Color.FromArgb(bAlpha, 255, 255, 255);
        e.Graphics.FillRectangle(brBrush, Sx, brightS + (brightH - bScale), 80, bScale);

        Sx += 84;
      }
    }

    private bool selectingFrames = true;

    private void FrameSequenceView_MouseDown(object sender, MouseEventArgs e)
    {
      if (e.Button != MouseButtons.Left)
        return;

      Int32 brightS = (ClientSize.Height - 110) + 34;

      Int32 sIndex = ((e.X - 4) / 84) + hwScroll.Value;
      if (sIndex >= 0 && sIndex < m_strip.NumFrames)
      {
        if (e.Y < brightS)
        {
          selectingFrames = true;

          m_strip.SelectionIndex = sIndex;
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
          m_strip.FrameAtIndex(sIndex).Brightness = (Byte)newBrightInt;
          Refresh();
        }
      }
    }

    private void FrameSequenceView_MouseMove(object sender, MouseEventArgs e)
    {
      if (e.Button != MouseButtons.Left)
        return;

      Int32 brightS = (ClientSize.Height - 110) + 32;

      Int32 sIndex = ((e.X - 4) / 84) + hwScroll.Value;
      if (sIndex >= 0 && sIndex < m_strip.NumFrames)
      {
        if (selectingFrames)
        {
          m_strip.SelectionIndex = sIndex;
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
          m_strip.FrameAtIndex(sIndex).Brightness = (Byte)newBrightInt;
          Refresh();
        }
      }
    }
  }
}