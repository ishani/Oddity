using MatrixCore;

namespace Matrix
{
  partial class FrameEditor
  {
    /// <summary> 
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary> 
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
      if (disposing && (components != null))
      {
        components.Dispose();
      }
      base.Dispose(disposing);
    }

    #region Component Designer generated code

    /// <summary> 
    /// Required method for Designer support - do not modify 
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      this.wFrameRender = new MatrixCore.FrameRender();
      this.SuspendLayout();
      // 
      // wFrameRender
      // 
      this.wFrameRender.BackColor = System.Drawing.Color.Black;
      this.wFrameRender.Cursor = System.Windows.Forms.Cursors.Hand;
      this.wFrameRender.DotSize = 28;
      this.wFrameRender.FrameToRender = null;
      this.wFrameRender.Location = new System.Drawing.Point(6, 6);
      this.wFrameRender.Name = "wFrameRender";
      this.wFrameRender.Size = new System.Drawing.Size(238, 238);
      this.wFrameRender.TabIndex = 0;
      this.wFrameRender.KeyUp += new System.Windows.Forms.KeyEventHandler(this.wFrameRender_KeyUp);
      this.wFrameRender.MouseDown += new System.Windows.Forms.MouseEventHandler(this.wFrameRender_MouseDown);
      this.wFrameRender.MouseMove += new System.Windows.Forms.MouseEventHandler(this.wFrameRender_MouseMove);
      this.wFrameRender.MouseUp += new System.Windows.Forms.MouseEventHandler(this.wFrameRender_MouseUp);
      // 
      // FrameEditor
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
      this.Controls.Add(this.wFrameRender);
      this.Name = "FrameEditor";
      this.Size = new System.Drawing.Size(250, 250);
      this.ResumeLayout(false);

    }

    #endregion

    private MatrixCore.FrameRender wFrameRender;
  }
}
