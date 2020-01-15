namespace BadgeUI
{
    partial class LEDMatrix
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
            this.SuspendLayout();
            // 
            // LEDMatrix
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Name = "LEDMatrix";
            this.Size = new System.Drawing.Size(276, 253);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.LEDMatrix_Paint);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.LEDMatrix_MouseMove);
            this.MouseClick += new System.Windows.Forms.MouseEventHandler(this.LEDMatrix_MouseClick);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.LEDMatrix_MouseDown);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.LEDMatrix_MouseUp);
            this.ResumeLayout(false);

        }

        #endregion
    }
}
