namespace Test
{
  partial class IGradTest
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
      this.gradientControl = new Ishani.UI.GradientEditorControl();
      this.gradientKey1 = new Ishani.UI.GradientKey();
      this.gradientKey2 = new Ishani.UI.GradientKey();
      this.gradientKey3 = new Ishani.UI.GradientKey();
      this.button1 = new System.Windows.Forms.Button();
      this.stepCount = new System.Windows.Forms.NumericUpDown();
      this.label1 = new System.Windows.Forms.Label();
      this.codeName = new System.Windows.Forms.TextBox();
      ((System.ComponentModel.ISupportInitialize)(this.stepCount)).BeginInit();
      this.SuspendLayout();
      // 
      // gradientControl
      // 
      this.gradientControl.AutoMouseBehavior = true;
      this.gradientControl.GradientKeyHeight = 20;
      this.gradientControl.GradientKeys.AddRange(new Ishani.UI.GradientKey[] {
            this.gradientKey1,
            this.gradientKey2,
            this.gradientKey3});
      this.gradientControl.GradientKeyWidth = 14;
      this.gradientControl.Location = new System.Drawing.Point(12, 12);
      this.gradientControl.Margin = new System.Windows.Forms.Padding(3, 3, 3, 8);
      this.gradientControl.Name = "gradientControl";
      this.gradientControl.OnlyRedGreen = true;
      this.gradientControl.Padding = new System.Windows.Forms.Padding(0, 0, 0, 8);
      this.gradientControl.Size = new System.Drawing.Size(520, 74);
      this.gradientControl.TabIndex = 0;
      this.gradientControl.VisualBorderStyle = System.Windows.Forms.Border3DStyle.SunkenOuter;
      this.gradientControl.VisualKeyStyle = Ishani.UI.GradientKeyVisualStyle.Raised;
      this.gradientControl.Load += new System.EventHandler(this.gradientEditorControl1_Load);
      // 
      // gradientKey1
      // 
      this.gradientKey1.KeyColor = System.Drawing.Color.Lime;
      this.gradientKey1.Position = 0.1D;
      // 
      // gradientKey2
      // 
      this.gradientKey2.KeyColor = System.Drawing.Color.Yellow;
      this.gradientKey2.Position = 0.9D;
      // 
      // gradientKey3
      // 
      this.gradientKey3.KeyColor = System.Drawing.Color.Red;
      this.gradientKey3.Position = 0.5D;
      // 
      // button1
      // 
      this.button1.Location = new System.Drawing.Point(358, 194);
      this.button1.Name = "button1";
      this.button1.Size = new System.Drawing.Size(147, 34);
      this.button1.TabIndex = 2;
      this.button1.Text = "Export to Clipboard";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new System.EventHandler(this.button1_Click);
      // 
      // stepCount
      // 
      this.stepCount.Location = new System.Drawing.Point(54, 138);
      this.stepCount.Name = "stepCount";
      this.stepCount.Size = new System.Drawing.Size(120, 20);
      this.stepCount.TabIndex = 3;
      this.stepCount.Value = new decimal(new int[] {
            18,
            0,
            0,
            0});
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(51, 122);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(40, 13);
      this.label1.TabIndex = 4;
      this.label1.Text = "Steps :";
      // 
      // codeName
      // 
      this.codeName.Location = new System.Drawing.Point(193, 138);
      this.codeName.MaxLength = 64;
      this.codeName.Name = "codeName";
      this.codeName.Size = new System.Drawing.Size(134, 20);
      this.codeName.TabIndex = 5;
      this.codeName.Text = "name_of_gradient";
      // 
      // IGradTest
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(544, 284);
      this.Controls.Add(this.codeName);
      this.Controls.Add(this.label1);
      this.Controls.Add(this.stepCount);
      this.Controls.Add(this.button1);
      this.Controls.Add(this.gradientControl);
      this.Name = "IGradTest";
      this.Text = "Gradient";
      ((System.ComponentModel.ISupportInitialize)(this.stepCount)).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private Ishani.UI.GradientEditorControl gradientControl;
    private Ishani.UI.GradientKey gradientKey1;
    private Ishani.UI.GradientKey gradientKey2;
    private Ishani.UI.GradientKey gradientKey3;
    private System.Windows.Forms.Button button1;
    private System.Windows.Forms.NumericUpDown stepCount;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.TextBox codeName;
  }
}

