namespace Matrix
{
  partial class MatrixForm
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
      this.components = new System.ComponentModel.Container();
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MatrixForm));
      this.wStatusBar = new System.Windows.Forms.StatusStrip();
      this.wFrameEditor = new Matrix.FrameEditor();
      this.wTopTabs = new System.Windows.Forms.TabControl();
      this.wTabTools = new System.Windows.Forms.TabPage();
      this.wTabScripting = new System.Windows.Forms.TabPage();
      this.panel2 = new System.Windows.Forms.Panel();
      this.wEditorDock = new System.Windows.Forms.Panel();
      this.panel1 = new System.Windows.Forms.Panel();
      this.wScriptStat = new System.Windows.Forms.PictureBox();
      this.wHintBox = new System.Windows.Forms.RichTextBox();
      this.wSequenceTabs = new System.Windows.Forms.TabControl();
      this.menuStrip1 = new System.Windows.Forms.MenuStrip();
      this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.SerialPort = new System.IO.Ports.SerialPort(this.components);
      this.wTopTabs.SuspendLayout();
      this.wTabScripting.SuspendLayout();
      this.panel2.SuspendLayout();
      this.panel1.SuspendLayout();
      ((System.ComponentModel.ISupportInitialize)(this.wScriptStat)).BeginInit();
      this.menuStrip1.SuspendLayout();
      this.SuspendLayout();
      // 
      // wStatusBar
      // 
      this.wStatusBar.Location = new System.Drawing.Point(0, 587);
      this.wStatusBar.Name = "wStatusBar";
      this.wStatusBar.Size = new System.Drawing.Size(842, 22);
      this.wStatusBar.TabIndex = 0;
      // 
      // wFrameEditor
      // 
      this.wFrameEditor.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
      this.wFrameEditor.BackColor = System.Drawing.Color.Black;
      this.wFrameEditor.Location = new System.Drawing.Point(9, 35);
      this.wFrameEditor.Name = "wFrameEditor";
      this.wFrameEditor.Size = new System.Drawing.Size(251, 250);
      this.wFrameEditor.TabIndex = 1;
      this.wFrameEditor.ViewFrame = null;
      // 
      // wTopTabs
      // 
      this.wTopTabs.Controls.Add(this.wTabTools);
      this.wTopTabs.Controls.Add(this.wTabScripting);
      this.wTopTabs.Location = new System.Drawing.Point(270, 35);
      this.wTopTabs.Multiline = true;
      this.wTopTabs.Name = "wTopTabs";
      this.wTopTabs.SelectedIndex = 0;
      this.wTopTabs.Size = new System.Drawing.Size(566, 250);
      this.wTopTabs.TabIndex = 2;
      // 
      // wTabTools
      // 
      this.wTabTools.Location = new System.Drawing.Point(4, 22);
      this.wTabTools.Name = "wTabTools";
      this.wTabTools.Padding = new System.Windows.Forms.Padding(3);
      this.wTabTools.Size = new System.Drawing.Size(558, 224);
      this.wTabTools.TabIndex = 0;
      this.wTabTools.Text = "Tools";
      this.wTabTools.UseVisualStyleBackColor = true;
      // 
      // wTabScripting
      // 
      this.wTabScripting.BackColor = System.Drawing.Color.Transparent;
      this.wTabScripting.Controls.Add(this.panel2);
      this.wTabScripting.Location = new System.Drawing.Point(4, 22);
      this.wTabScripting.Name = "wTabScripting";
      this.wTabScripting.Padding = new System.Windows.Forms.Padding(3);
      this.wTabScripting.Size = new System.Drawing.Size(558, 224);
      this.wTabScripting.TabIndex = 1;
      this.wTabScripting.Text = "Scripting";
      // 
      // panel2
      // 
      this.panel2.BackColor = System.Drawing.Color.White;
      this.panel2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
      this.panel2.Controls.Add(this.wEditorDock);
      this.panel2.Controls.Add(this.panel1);
      this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
      this.panel2.Location = new System.Drawing.Point(3, 3);
      this.panel2.Name = "panel2";
      this.panel2.Size = new System.Drawing.Size(552, 218);
      this.panel2.TabIndex = 0;
      // 
      // wEditorDock
      // 
      this.wEditorDock.BackColor = System.Drawing.Color.Transparent;
      this.wEditorDock.Dock = System.Windows.Forms.DockStyle.Fill;
      this.wEditorDock.Location = new System.Drawing.Point(0, 20);
      this.wEditorDock.Name = "wEditorDock";
      this.wEditorDock.Padding = new System.Windows.Forms.Padding(1, 2, 1, 1);
      this.wEditorDock.Size = new System.Drawing.Size(550, 196);
      this.wEditorDock.TabIndex = 6;
      // 
      // panel1
      // 
      this.panel1.Controls.Add(this.wScriptStat);
      this.panel1.Controls.Add(this.wHintBox);
      this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
      this.panel1.Location = new System.Drawing.Point(0, 0);
      this.panel1.Name = "panel1";
      this.panel1.Padding = new System.Windows.Forms.Padding(4, 2, 0, 0);
      this.panel1.Size = new System.Drawing.Size(550, 20);
      this.panel1.TabIndex = 5;
      // 
      // wScriptStat
      // 
      this.wScriptStat.Dock = System.Windows.Forms.DockStyle.Right;
      this.wScriptStat.Image = global::Matrix.Properties.Resources.OKSymbol;
      this.wScriptStat.Location = new System.Drawing.Point(534, 2);
      this.wScriptStat.Name = "wScriptStat";
      this.wScriptStat.Padding = new System.Windows.Forms.Padding(0, 0, 2, 0);
      this.wScriptStat.Size = new System.Drawing.Size(16, 18);
      this.wScriptStat.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
      this.wScriptStat.TabIndex = 0;
      this.wScriptStat.TabStop = false;
      this.wScriptStat.Visible = false;
      // 
      // wHintBox
      // 
      this.wHintBox.BackColor = System.Drawing.SystemColors.Window;
      this.wHintBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
      this.wHintBox.Dock = System.Windows.Forms.DockStyle.Left;
      this.wHintBox.Font = new System.Drawing.Font("Courier New", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.wHintBox.Location = new System.Drawing.Point(4, 2);
      this.wHintBox.MaxLength = 128;
      this.wHintBox.Multiline = false;
      this.wHintBox.Name = "wHintBox";
      this.wHintBox.ReadOnly = true;
      this.wHintBox.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.None;
      this.wHintBox.Size = new System.Drawing.Size(527, 18);
      this.wHintBox.TabIndex = 0;
      this.wHintBox.Text = "Frame EditingFrame, FrameSequence CurrentSequence";
      // 
      // wSequenceTabs
      // 
      this.wSequenceTabs.Location = new System.Drawing.Point(9, 294);
      this.wSequenceTabs.Name = "wSequenceTabs";
      this.wSequenceTabs.SelectedIndex = 0;
      this.wSequenceTabs.Size = new System.Drawing.Size(827, 219);
      this.wSequenceTabs.TabIndex = 3;
      // 
      // menuStrip1
      // 
      this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
      this.menuStrip1.Location = new System.Drawing.Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new System.Drawing.Size(842, 24);
      this.menuStrip1.TabIndex = 4;
      this.menuStrip1.Text = "menuStrip1";
      // 
      // fileToolStripMenuItem
      // 
      this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
      this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
      this.fileToolStripMenuItem.Text = "File";
      // 
      // MatrixForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(842, 609);
      this.Controls.Add(this.wSequenceTabs);
      this.Controls.Add(this.wTopTabs);
      this.Controls.Add(this.wStatusBar);
      this.Controls.Add(this.menuStrip1);
      this.Controls.Add(this.wFrameEditor);
      this.DoubleBuffered = true;
      this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
      this.MainMenuStrip = this.menuStrip1;
      this.Name = "MatrixForm";
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
      this.Text = "Matrix";
      this.wTopTabs.ResumeLayout(false);
      this.wTabScripting.ResumeLayout(false);
      this.panel2.ResumeLayout(false);
      this.panel1.ResumeLayout(false);
      ((System.ComponentModel.ISupportInitialize)(this.wScriptStat)).EndInit();
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private FrameEditor wFrameEditor;
    private System.Windows.Forms.StatusStrip wStatusBar;
    private System.Windows.Forms.TabControl wTopTabs;
    private System.Windows.Forms.TabPage wTabTools;
    private System.Windows.Forms.TabPage wTabScripting;
    private System.Windows.Forms.TabControl wSequenceTabs;
    private System.Windows.Forms.Panel panel2;
    private System.Windows.Forms.Panel wEditorDock;
    private System.Windows.Forms.Panel panel1;
    private System.Windows.Forms.PictureBox wScriptStat;
    private System.Windows.Forms.RichTextBox wHintBox;
    private System.Windows.Forms.MenuStrip menuStrip1;
    private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
    private System.IO.Ports.SerialPort SerialPort;
  }
}

