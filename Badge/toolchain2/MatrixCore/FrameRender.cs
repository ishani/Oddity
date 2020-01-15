using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Windows.Forms;

namespace MatrixCore
{
  public partial class FrameRender : Control
  {
    private Int32 m_dotSize = 10;
    private Int32 m_dotLEDSize = 0, m_dotEdge = 0;
    private LEDColouring m_colouring = new LEDColouring();

    private Frame m_frame = null;
    
    public PaintEventHandler OverlayPaint;


    public FrameRender()
    {
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

    public Frame FrameToRender
    {
      set 
      {
        if (m_frame != null)
        {
          m_frame.FrameChangedEvent -= FrameDataUpdated;
        }

        m_frame = value;

        if (m_frame != null)
        {
          m_frame.FrameChangedEvent += FrameDataUpdated;
        }

        Refresh();
      }
      get { return m_frame; }
    }

    [Bindable(true), DesignerSerializationVisibility(DesignerSerializationVisibility.Visible), Category("Appearance")]
    public Int32 DotSize
    {
      get { return m_dotSize; }
      set
      {
        m_dotSize = value;

        m_dotLEDSize = (Int32)((float)m_dotSize * 0.9f);
        m_dotEdge = (Int32)((float)m_dotSize * 0.25f);

        Size = DefaultSize;
        Refresh();
      }
    }

    public Int32 DotLEDSize
    {
      get { return m_dotLEDSize; }
    }

    protected override Size DefaultSize
    {
      get
      {
        return new Size(
          (Dims.LEDs * m_dotSize) + (m_dotEdge * 2), 
          (Dims.LEDs * m_dotSize) + (m_dotEdge * 2));
      }
    }

    public Int32 DotPixelOffset(Int32 index)
    {
      return 1 + m_dotEdge + (index * DotSize);
    }

    public bool MouseToLEDIndex(Int32 x, Int32 y, ref Point p)
    {
      if (x < m_dotEdge || y < m_dotEdge ||
          x > Size.Width - m_dotEdge || y > Size.Width - m_dotEdge)
        return false;

      Int32 indexX = (x / m_dotSize);
      Int32 indexY = (y / m_dotSize);

      Dims.Clamp(ref indexX, ref indexY);

      p.X = indexX;
      p.Y = indexY;

      return true;
    }

    protected override void OnResize(EventArgs e)
    {
      Size = DefaultSize;
    }

    protected override void OnLostFocus(EventArgs e)
    {
      base.OnLostFocus(e);
      Refresh();
    }

    protected override void OnGotFocus(EventArgs e)
    {
      base.OnGotFocus(e);
      Refresh();
    }

    protected override void OnPaint(PaintEventArgs pe)
    {
      pe.Graphics.Clear(Color.Black);

      if (Focused)
      {
        Pen focusPen = new Pen(Color.DarkGray, 1.0f);
        focusPen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dot;

        pe.Graphics.DrawRectangle(focusPen, 1, 1, Size.Width - 3, Size.Height - 3);
      }

      if (m_frame != null)
      {
        pe.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;

        m_frame.Iterate((Int32 x, Int32 y, LED led) =>
          {
            pe.Graphics.FillEllipse(m_colouring.BrushForLED(ref led),
              DotPixelOffset(x),
              DotPixelOffset(y),
              DotLEDSize,
              DotLEDSize);
          }
        );

        OverlayPaint(this, pe);
      }
    }
  }
}
