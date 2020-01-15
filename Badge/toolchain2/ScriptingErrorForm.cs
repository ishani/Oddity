using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Text;
using System.Windows.Forms;

namespace Matrix
{
  public partial class ScriptingErrorForm : Form
  {
    private String ErrorString;
    private SizeF ErrorSize;
    private GraphicsPath MaskPath, EdgePath;

    // Define the CS_DROPSHADOW constant
    private const int CS_DROPSHADOW = 0x00020000;

    // Override the CreateParams property
    protected override CreateParams CreateParams
    {
      get
      {
        CreateParams cp = base.CreateParams;
        cp.ClassStyle |= CS_DROPSHADOW;
        return cp;
      }
    }

    public ScriptingErrorForm(String errors)
    {
      InitializeComponent();
      ErrorString = "\n               Scripting Errors\n\n\n" + errors;
    }

    private void ScriptingErrorForm_Load(object sender, EventArgs e)
    {
      // see how tall this dialog needs to be
      Graphics a = Graphics.FromHwnd(wText.Handle);
      ErrorSize = a.MeasureString(ErrorString, wText.Font, 400);
      ErrorSize.Height += 15;

      this.Height = (Int32)ErrorSize.Height;
      wText.Text = ErrorString;
      wText.MouseUp += new MouseEventHandler(wText_MouseUp);
      
      // cut the form to size
      MaskPath = GetRoundedRect(new RectangleF(0.0f, 0.0f, 400.0f, ErrorSize.Height), 12.0f);
      Region = new Region(MaskPath);

      EdgePath = GetRoundedRect(new RectangleF(0.75f, 0.75f, 399.0f, ErrorSize.Height - 1.0f), 12.0f);
    }

    protected override void OnPaint(PaintEventArgs e)
    {
      base.OnPaint(e);
      Pen p = new Pen(Color.Gold, 3.0f);

      e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;
      e.Graphics.PixelOffsetMode = PixelOffsetMode.HighQuality;
      e.Graphics.DrawPath(p, EdgePath);
    }

    void wText_MouseUp(object sender, MouseEventArgs e)
    {
      Close();
    }

    protected override void OnLostFocus(EventArgs e)
    {
      base.OnLostFocus(e);
      Close();
    }

    protected override void OnKeyDown(KeyEventArgs e)
    {
      base.OnKeyDown(e);
      Close();
    }

    #region RoundedRect
    private GraphicsPath GetRoundedRect(RectangleF baseRect, float radius)
    {
      float diameter = radius * 2.0F;
      SizeF sizeF = new SizeF(diameter, diameter);
      RectangleF arc = new RectangleF(baseRect.Location, sizeF);
      GraphicsPath path = new System.Drawing.Drawing2D.GraphicsPath();

      // top left arc 

      path.AddArc(arc, 180, 90);

      // top right arc 

      arc.X = baseRect.Right - diameter;
      path.AddArc(arc, 270, 90);

      // bottom right arc 

      arc.Y = baseRect.Bottom - diameter;
      path.AddArc(arc, 0, 90);

      // bottom left arc

      arc.X = baseRect.Left;
      path.AddArc(arc, 90, 90);

      path.CloseFigure();
      return path;
    }
    #endregion 
  }
}
