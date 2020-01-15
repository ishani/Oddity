namespace Badge
{
  partial class ScriptView
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
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ScriptView));
      this.scintillaScript = new ScintillaNet.Scintilla();
      this.scriptErr = new System.Windows.Forms.RichTextBox();
      this.hwRun = new System.Windows.Forms.Button();
      this.panel1 = new System.Windows.Forms.Panel();
      this.panel4 = new System.Windows.Forms.Panel();
      this.panel3 = new System.Windows.Forms.Panel();
      this.panel2 = new System.Windows.Forms.Panel();
      ((System.ComponentModel.ISupportInitialize)(this.scintillaScript)).BeginInit();
      this.panel1.SuspendLayout();
      this.panel4.SuspendLayout();
      this.panel3.SuspendLayout();
      this.panel2.SuspendLayout();
      this.SuspendLayout();
      // 
      // scintillaScript
      // 
      this.scintillaScript.Dock = System.Windows.Forms.DockStyle.Fill;
      this.scintillaScript.Font = new System.Drawing.Font("Courier New", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.scintillaScript.Location = new System.Drawing.Point(0, 0);
      this.scintillaScript.Margins.Margin0.Width = 10;
      this.scintillaScript.Margins.Margin1.Width = 10;
      this.scintillaScript.Margins.Margin2.Width = 14;
      this.scintillaScript.Name = "scintillaScript";
      this.scintillaScript.Size = new System.Drawing.Size(646, 373);
      this.scintillaScript.TabIndex = 25;
      // 
      // scriptErr
      // 
      this.scriptErr.BackColor = System.Drawing.SystemColors.ButtonShadow;
      this.scriptErr.Dock = System.Windows.Forms.DockStyle.Fill;
      this.scriptErr.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.scriptErr.Location = new System.Drawing.Point(0, 2);
      this.scriptErr.Name = "scriptErr";
      this.scriptErr.ReadOnly = true;
      this.scriptErr.Size = new System.Drawing.Size(579, 66);
      this.scriptErr.TabIndex = 24;
      this.scriptErr.Text = "";
      this.scriptErr.WordWrap = false;
      // 
      // hwRun
      // 
      this.hwRun.Location = new System.Drawing.Point(4, 5);
      this.hwRun.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
      this.hwRun.Name = "hwRun";
      this.hwRun.Size = new System.Drawing.Size(59, 60);
      this.hwRun.TabIndex = 23;
      this.hwRun.Text = "Run";
      this.hwRun.UseVisualStyleBackColor = true;
      this.hwRun.Click += new System.EventHandler(this.hwRun_Click);
      // 
      // panel1
      // 
      this.panel1.Controls.Add(this.panel4);
      this.panel1.Controls.Add(this.panel3);
      this.panel1.Dock = System.Windows.Forms.DockStyle.Bottom;
      this.panel1.Location = new System.Drawing.Point(0, 373);
      this.panel1.Name = "panel1";
      this.panel1.Size = new System.Drawing.Size(646, 68);
      this.panel1.TabIndex = 26;
      // 
      // panel4
      // 
      this.panel4.Controls.Add(this.scriptErr);
      this.panel4.Dock = System.Windows.Forms.DockStyle.Fill;
      this.panel4.Location = new System.Drawing.Point(0, 0);
      this.panel4.Name = "panel4";
      this.panel4.Padding = new System.Windows.Forms.Padding(0, 2, 0, 0);
      this.panel4.Size = new System.Drawing.Size(579, 68);
      this.panel4.TabIndex = 26;
      // 
      // panel3
      // 
      this.panel3.Controls.Add(this.hwRun);
      this.panel3.Dock = System.Windows.Forms.DockStyle.Right;
      this.panel3.Location = new System.Drawing.Point(579, 0);
      this.panel3.Name = "panel3";
      this.panel3.Size = new System.Drawing.Size(67, 68);
      this.panel3.TabIndex = 25;
      // 
      // panel2
      // 
      this.panel2.Controls.Add(this.scintillaScript);
      this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
      this.panel2.Location = new System.Drawing.Point(0, 0);
      this.panel2.Name = "panel2";
      this.panel2.Size = new System.Drawing.Size(646, 373);
      this.panel2.TabIndex = 27;
      // 
      // ScriptView
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(646, 441);
      this.Controls.Add(this.panel2);
      this.Controls.Add(this.panel1);
      this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
      this.Name = "ScriptView";
      this.Text = "Badge Script Editor";
      ((System.ComponentModel.ISupportInitialize)(this.scintillaScript)).EndInit();
      this.panel1.ResumeLayout(false);
      this.panel4.ResumeLayout(false);
      this.panel3.ResumeLayout(false);
      this.panel2.ResumeLayout(false);
      this.ResumeLayout(false);

    }

    #endregion

    private ScintillaNet.Scintilla scintillaScript;
    private System.Windows.Forms.RichTextBox scriptErr;
    private System.Windows.Forms.Button hwRun;
    private System.Windows.Forms.Panel panel1;
    private System.Windows.Forms.Panel panel4;
    private System.Windows.Forms.Panel panel3;
    private System.Windows.Forms.Panel panel2;
  }
}