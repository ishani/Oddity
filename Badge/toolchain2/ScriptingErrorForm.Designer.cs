namespace Matrix
{
  partial class ScriptingErrorForm
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

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      this.wText = new System.Windows.Forms.Label();
      this.SuspendLayout();
      // 
      // wText
      // 
      this.wText.BackColor = System.Drawing.Color.Transparent;
      this.wText.Dock = System.Windows.Forms.DockStyle.Fill;
      this.wText.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.wText.Image = global::Matrix.Properties.Resources.ErrorSymbol;
      this.wText.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
      this.wText.Location = new System.Drawing.Point(5, 6);
      this.wText.Name = "wText";
      this.wText.Size = new System.Drawing.Size(393, 292);
      this.wText.TabIndex = 0;
      this.wText.Text = "error text";
      // 
      // ScriptingErrorForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.BackColor = System.Drawing.SystemColors.Info;
      this.ClientSize = new System.Drawing.Size(400, 300);
      this.ControlBox = false;
      this.Controls.Add(this.wText);
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = "ScriptingErrorForm";
      this.Padding = new System.Windows.Forms.Padding(5, 6, 2, 2);
      this.ShowIcon = false;
      this.ShowInTaskbar = false;
      this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
      this.Text = "ScriptingErrorForm";
      this.TopMost = true;
      this.Load += new System.EventHandler(this.ScriptingErrorForm_Load);
      this.ResumeLayout(false);

    }

    #endregion

    private System.Windows.Forms.Label wText;
  }
}