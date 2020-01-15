namespace BadgeUI
{
    partial class FrameStripControl
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
            this.hwScroll = new System.Windows.Forms.HScrollBar();
            this.SuspendLayout();
            // 
            // hwScroll
            // 
            this.hwScroll.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.hwScroll.LargeChange = 1;
            this.hwScroll.Location = new System.Drawing.Point(0, 56);
            this.hwScroll.Maximum = 3;
            this.hwScroll.Name = "hwScroll";
            this.hwScroll.Size = new System.Drawing.Size(399, 18);
            this.hwScroll.TabIndex = 0;
            this.hwScroll.ValueChanged += new System.EventHandler(this.hwScroll_ValueChanged);
            // 
            // FrameStrip
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.hwScroll);
            this.Name = "FrameStrip";
            this.Size = new System.Drawing.Size(399, 74);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.FrameStrip_Paint);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.FrameStrip_MouseDown);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.FrameStrip_MouseMove);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.HScrollBar hwScroll;
    }
}
