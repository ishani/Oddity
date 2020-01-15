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
  public partial class LEDMatrix : UserControl
  {
    private Frame m_frame = null;
    private Int32 m_dotSize;
    private Frame m_undo;
    public bool m_considerFrameBrightness = false;

    public LEDMatrix()
    {
      init(18);
    }
    public LEDMatrix(Int32 dotSize)
    {
      init(dotSize);
    }

    [Bindable(true), DesignerSerializationVisibility(DesignerSerializationVisibility.Visible), Category("Appearance")]
    public Int32 DotSize
    {
      get { return m_dotSize; }
      set
      {
        m_dotSize = value;

        Size = DefaultSize;
        Refresh();
      }
    }

    private void init(Int32 dotSize)
    {
      DotSize = dotSize;
      m_undo = new Frame();

      InitializeComponent();

      this.SetStyle(
          ControlStyles.UserPaint |
          ControlStyles.AllPaintingInWmPaint |
          ControlStyles.DoubleBuffer, true);
    }

    void FrameDataUpdated(object sender, EventArgs e)
    {
      Refresh();
    }

    public void setFrame(Frame fr)
    {
      if (m_frame != null)
      {
        m_frame.UpdateEvent -= FrameDataUpdated;
      }

      m_frame = fr;

      if (m_frame != null)
      {
        m_frame.copyTo(m_undo);
        m_frame.UpdateEvent += FrameDataUpdated;
      }

      Refresh();
    }

    public Frame CurrentFrame
    {
      get { return m_frame; }
    }

    protected override Size DefaultSize
    {
      get
      {
        Int32 dotEdge = (Int32)((float)m_dotSize * 0.15f);
        return new Size((Frame.EdgeLEDCount * m_dotSize) + (dotEdge * 2), (Frame.EdgeLEDCount * m_dotSize) + (dotEdge * 2));
      }
    }

    protected override void OnResize(EventArgs e)
    {
      Size = DefaultSize;
    }

    public void undo()
    {
      if (m_frame != null)
      {
        Frame tF = new Frame();
        m_frame.copyTo(tF);

        m_undo.copyTo(m_frame);

        tF.copyTo(m_undo);
      }
    }

    static public void renderFrameToGraphics(Frame f, Graphics Gr, bool considerFrameBrightness, Int32 dotSize)
    {
      Int32 dotGap = (Int32)((float)dotSize * 0.9f);
      Int32 dotEdge = (Int32)((float)dotSize * 0.15f);

      Gr.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;

      Gr.Clear(Color.Black);
      SolidBrush dotBrush = new SolidBrush(Color.FromArgb(40, 40, 40));

      for (Int32 y = 0; y < Frame.EdgeLEDCount; y++)
      {
        for (Int32 x = 0; x < Frame.EdgeLEDCount; x++)
        {
          Byte ledR, ledG;
          f.getLED(x, y, out ledR, out ledG);

          float brMult = f.BrightnessAsFloat;

          if (considerFrameBrightness)
          {
            Int32 led_red = 40 + (Int32)((float)(ledR * 70) * brMult);
            Int32 led_green = 40 + (Int32)((float)(ledG * 70) * brMult);

            dotBrush.Color = Color.FromArgb(led_red, led_green, 40);
          }
          else
          {
            Int32 led_red = 40 + ledR * 70;
            Int32 led_green = 40 + ledG * 70;

            dotBrush.Color = Color.FromArgb(led_red, led_green, 40);
          }

          Gr.FillEllipse(dotBrush, 1 + dotEdge + (x * dotSize), 1 + dotEdge + (y * dotSize), dotGap, dotGap);
        }
      }
    }

    private void LEDMatrix_Paint(object sender, PaintEventArgs e)
    {
      if (m_frame == null)
        return;

      renderFrameToGraphics(m_frame, e.Graphics, m_considerFrameBrightness, m_dotSize);
    }

    private Int32 lastX = -1, lastY = -1;

    private void paintModifyLED(MouseEventArgs e, ref Byte ledR, ref Byte ledG)
    {
      Int32 inc = 1;
      if (Control.ModifierKeys == Keys.Control)
        inc = -1;

      Int32 R = ledR;
      Int32 G = ledG;

      if (e.Button == MouseButtons.Left)
      {
        R += inc;
      }
      if (e.Button == MouseButtons.Right)
      {
        G += inc;
      }

      if (R > 3) R = 3;
      if (R < 0) R = 0;

      if (G > 3) G = 3;
      if (G < 0) G = 0;

      ledR = (Byte)R;
      ledG = (Byte)G;
    }

    private void LEDMatrix_MouseMove(object sender, MouseEventArgs e)
    {
      if (m_frame == null || !Focused)
        return;

      if (e.Button == MouseButtons.Left ||
          e.Button == MouseButtons.Right)
      {
        Int32 indexX = (e.X / m_dotSize);
        Int32 indexY = (e.Y / m_dotSize);

        if (indexX > 15) indexX = 15;
        if (indexY > 15) indexY = 15;
        if (indexX < 0) indexX = 0;
        if (indexY < 0) indexY = 0;

        if (indexX != lastX || indexY != lastY)
        {
          lastX = indexX;
          lastY = indexY;

          Byte ledR, ledG;
          m_frame.getLED(indexX, indexY, out ledR, out ledG);

          paintModifyLED(e, ref ledR, ref ledG);

          m_frame.setLED(indexX, indexY, ledR, ledG);
          m_frame.callUpdateEvent();
        }
      }
    }

    private void LEDMatrix_MouseClick(object sender, MouseEventArgs e)
    {

    }

    private void LEDMatrix_MouseDown(object sender, MouseEventArgs e)
    {
      if (m_frame == null || !Focused)
        return;

      m_frame.copyTo(m_undo);

      Int32 indexX = lastX = (e.X / m_dotSize);
      Int32 indexY = lastY = (e.Y / m_dotSize);

      if (indexX > 15) indexX = 15;
      if (indexY > 15) indexY = 15;
      if (indexX < 0) indexX = 0;
      if (indexY < 0) indexY = 0;

      Byte ledR, ledG;
      m_frame.getLED(indexX, indexY, out ledR, out ledG);

      paintModifyLED(e, ref ledR, ref ledG);

      m_frame.setLED(indexX, indexY, ledR, ledG);
      m_frame.callUpdateEvent();
    }

    private void LEDMatrix_MouseUp(object sender, MouseEventArgs e)
    {

    }
  }
}
