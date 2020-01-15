namespace Badge
{
    partial class BadgeForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(BadgeForm));
            this.hwAddFrame = new System.Windows.Forms.Button();
            this.hwDupe = new System.Windows.Forms.Button();
            this.hwPlay = new System.Windows.Forms.Timer(this.components);
            this.hwPlayBtn = new System.Windows.Forms.Button();
            this.hwDel = new System.Windows.Forms.Button();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.exportFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.panel1 = new System.Windows.Forms.Panel();
            this.hwMatrixLarge = new BadgeUI.LEDMatrix();
            this.hwDelAll = new System.Windows.Forms.Button();
            this.hwFPS = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.mainMenu = new System.Windows.Forms.MenuStrip();
            this.fileMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exportBINToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exportToCArrayToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.loadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.appendToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.overlayToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.overlayAdditiveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.overlayPunchoutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.overlayCutOutBackgroundToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.editorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.undoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.hwPorts = new System.Windows.Forms.ToolStripComboBox();
            this.hardwareToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.sendToDeviceToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toggleDisplayToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.windowsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.scriptEditorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exportToAVIToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.panel2 = new System.Windows.Forms.Panel();
            this.hwDemoBright = new System.Windows.Forms.RadioButton();
            this.demoMatrix = new BadgeUI.LEDMatrix();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.hwSendProgress = new System.Windows.Forms.ToolStripProgressBar();
            this.hwDupeInsert = new System.Windows.Forms.Button();
            this.hwInsert = new System.Windows.Forms.Button();
            this.saveAVI = new System.Windows.Forms.SaveFileDialog();
            this.toolList = new System.Windows.Forms.ListBox();
            this.propertyGrid = new System.Windows.Forms.PropertyGrid();
            this.exportToHeader = new System.Windows.Forms.SaveFileDialog();
            this.frStrip = new BadgeUI.FrameStripControl();
            this.clipboardcap = new System.Windows.Forms.Button();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.hwFPS)).BeginInit();
            this.mainMenu.SuspendLayout();
            this.panel2.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // hwAddFrame
            // 
            this.hwAddFrame.Location = new System.Drawing.Point(9, 511);
            this.hwAddFrame.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.hwAddFrame.Name = "hwAddFrame";
            this.hwAddFrame.Size = new System.Drawing.Size(96, 23);
            this.hwAddFrame.TabIndex = 2;
            this.hwAddFrame.Text = "Add Frame";
            this.hwAddFrame.UseVisualStyleBackColor = true;
            this.hwAddFrame.Click += new System.EventHandler(this.hwAddFrame_Click);
            // 
            // hwDupe
            // 
            this.hwDupe.Location = new System.Drawing.Point(113, 511);
            this.hwDupe.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.hwDupe.Name = "hwDupe";
            this.hwDupe.Size = new System.Drawing.Size(133, 23);
            this.hwDupe.TabIndex = 3;
            this.hwDupe.Text = "Duplicate && Append";
            this.hwDupe.UseVisualStyleBackColor = true;
            this.hwDupe.Click += new System.EventHandler(this.hwDupe_Click);
            // 
            // hwPlay
            // 
            this.hwPlay.Interval = 60;
            this.hwPlay.Tick += new System.EventHandler(this.hwPlay_Tick);
            // 
            // hwPlayBtn
            // 
            this.hwPlayBtn.FlatAppearance.BorderColor = System.Drawing.Color.Orange;
            this.hwPlayBtn.FlatAppearance.BorderSize = 2;
            this.hwPlayBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.DarkBlue;
            this.hwPlayBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.MidnightBlue;
            this.hwPlayBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.hwPlayBtn.Font = new System.Drawing.Font("Trebuchet MS", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.hwPlayBtn.ForeColor = System.Drawing.Color.Orange;
            this.hwPlayBtn.Location = new System.Drawing.Point(16, 116);
            this.hwPlayBtn.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.hwPlayBtn.Name = "hwPlayBtn";
            this.hwPlayBtn.Size = new System.Drawing.Size(73, 38);
            this.hwPlayBtn.TabIndex = 5;
            this.hwPlayBtn.Text = "Play";
            this.hwPlayBtn.UseVisualStyleBackColor = true;
            this.hwPlayBtn.Click += new System.EventHandler(this.hwPlayBtn_Click);
            // 
            // hwDel
            // 
            this.hwDel.Location = new System.Drawing.Point(798, 511);
            this.hwDel.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.hwDel.Name = "hwDel";
            this.hwDel.Size = new System.Drawing.Size(133, 23);
            this.hwDel.TabIndex = 6;
            this.hwDel.Text = "Delete Selected";
            this.hwDel.UseVisualStyleBackColor = true;
            this.hwDel.Click += new System.EventHandler(this.hwDel_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.DefaultExt = "BD";
            this.openFileDialog.Filter = "Badge Data|*.bd|All Files|*.*";
            this.openFileDialog.Title = "Load Data";
            // 
            // saveFileDialog
            // 
            this.saveFileDialog.DefaultExt = "BD";
            this.saveFileDialog.Filter = "Badge Data|*.bd|All Files|*.*";
            this.saveFileDialog.Title = "Save Data";
            // 
            // exportFileDialog
            // 
            this.exportFileDialog.DefaultExt = "bin";
            this.exportFileDialog.Filter = "Badge Binary Data|*.bin|All Files|*.*";
            this.exportFileDialog.Title = "Export Data";
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.Black;
            this.panel1.Controls.Add(this.hwMatrixLarge);
            this.panel1.Location = new System.Drawing.Point(12, 38);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(561, 251);
            this.panel1.TabIndex = 18;
            // 
            // hwMatrixLarge
            // 
            this.hwMatrixLarge.DotSize = 26;
            this.hwMatrixLarge.Location = new System.Drawing.Point(20, 18);
            this.hwMatrixLarge.Name = "hwMatrixLarge";
            this.hwMatrixLarge.Size = new System.Drawing.Size(214, 214);
            this.hwMatrixLarge.TabIndex = 1;
            // 
            // hwDelAll
            // 
            this.hwDelAll.Location = new System.Drawing.Point(939, 511);
            this.hwDelAll.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.hwDelAll.Name = "hwDelAll";
            this.hwDelAll.Size = new System.Drawing.Size(84, 23);
            this.hwDelAll.TabIndex = 23;
            this.hwDelAll.Text = "Delete All";
            this.hwDelAll.UseVisualStyleBackColor = true;
            this.hwDelAll.Click += new System.EventHandler(this.hwDelAll_Click);
            // 
            // hwFPS
            // 
            this.hwFPS.Location = new System.Drawing.Point(1083, 488);
            this.hwFPS.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.hwFPS.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.hwFPS.Name = "hwFPS";
            this.hwFPS.Size = new System.Drawing.Size(52, 21);
            this.hwFPS.TabIndex = 1;
            this.hwFPS.Value = new decimal(new int[] {
            15,
            0,
            0,
            0});
            this.hwFPS.ValueChanged += new System.EventHandler(this.hwFPS_ValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(1044, 492);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(37, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "FPS :";
            // 
            // mainMenu
            // 
            this.mainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileMenu,
            this.editorToolStripMenuItem,
            this.hwPorts,
            this.hardwareToolStripMenuItem,
            this.windowsToolStripMenuItem});
            this.mainMenu.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.HorizontalStackWithOverflow;
            this.mainMenu.Location = new System.Drawing.Point(0, 0);
            this.mainMenu.Name = "mainMenu";
            this.mainMenu.Size = new System.Drawing.Size(1147, 27);
            this.mainMenu.TabIndex = 27;
            this.mainMenu.Text = "mainMenu";
            // 
            // fileMenu
            // 
            this.fileMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.saveToolStripMenuItem,
            this.exportBINToolStripMenuItem,
            this.exportToCArrayToolStripMenuItem,
            this.toolStripSeparator1,
            this.loadToolStripMenuItem,
            this.loadToolStripMenuItem1});
            this.fileMenu.Name = "fileMenu";
            this.fileMenu.Size = new System.Drawing.Size(37, 23);
            this.fileMenu.Text = "&File";
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(173, 22);
            this.saveToolStripMenuItem.Text = "&Save...";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // exportBINToolStripMenuItem
            // 
            this.exportBINToolStripMenuItem.Name = "exportBINToolStripMenuItem";
            this.exportBINToolStripMenuItem.Size = new System.Drawing.Size(173, 22);
            this.exportBINToolStripMenuItem.Text = "&Export BIN...";
            this.exportBINToolStripMenuItem.Click += new System.EventHandler(this.exportBINToolStripMenuItem_Click);
            // 
            // exportToCArrayToolStripMenuItem
            // 
            this.exportToCArrayToolStripMenuItem.Name = "exportToCArrayToolStripMenuItem";
            this.exportToCArrayToolStripMenuItem.Size = new System.Drawing.Size(173, 22);
            this.exportToCArrayToolStripMenuItem.Text = "Export to C Array...";
            this.exportToCArrayToolStripMenuItem.Click += new System.EventHandler(this.exportToCArrayToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(170, 6);
            // 
            // loadToolStripMenuItem
            // 
            this.loadToolStripMenuItem.Name = "loadToolStripMenuItem";
            this.loadToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.L)));
            this.loadToolStripMenuItem.Size = new System.Drawing.Size(173, 22);
            this.loadToolStripMenuItem.Text = "&Load...";
            this.loadToolStripMenuItem.Click += new System.EventHandler(this.loadToolStripMenuItem_Click);
            // 
            // loadToolStripMenuItem1
            // 
            this.loadToolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.appendToolStripMenuItem,
            this.overlayToolStripMenuItem,
            this.overlayAdditiveToolStripMenuItem,
            this.overlayPunchoutToolStripMenuItem,
            this.overlayCutOutBackgroundToolStripMenuItem});
            this.loadToolStripMenuItem1.Name = "loadToolStripMenuItem1";
            this.loadToolStripMenuItem1.Size = new System.Drawing.Size(173, 22);
            this.loadToolStripMenuItem1.Text = "Load && ...";
            // 
            // appendToolStripMenuItem
            // 
            this.appendToolStripMenuItem.Name = "appendToolStripMenuItem";
            this.appendToolStripMenuItem.Size = new System.Drawing.Size(228, 22);
            this.appendToolStripMenuItem.Text = "Append";
            this.appendToolStripMenuItem.Click += new System.EventHandler(this.appendToolStripMenuItem_Click);
            // 
            // overlayToolStripMenuItem
            // 
            this.overlayToolStripMenuItem.Name = "overlayToolStripMenuItem";
            this.overlayToolStripMenuItem.Size = new System.Drawing.Size(228, 22);
            this.overlayToolStripMenuItem.Text = "Overlay";
            this.overlayToolStripMenuItem.Click += new System.EventHandler(this.overlayToolStripMenuItem_Click);
            // 
            // overlayAdditiveToolStripMenuItem
            // 
            this.overlayAdditiveToolStripMenuItem.Name = "overlayAdditiveToolStripMenuItem";
            this.overlayAdditiveToolStripMenuItem.Size = new System.Drawing.Size(228, 22);
            this.overlayAdditiveToolStripMenuItem.Text = "Overlay Additive";
            this.overlayAdditiveToolStripMenuItem.Click += new System.EventHandler(this.overlayAdditiveToolStripMenuItem_Click);
            // 
            // overlayPunchoutToolStripMenuItem
            // 
            this.overlayPunchoutToolStripMenuItem.Name = "overlayPunchoutToolStripMenuItem";
            this.overlayPunchoutToolStripMenuItem.Size = new System.Drawing.Size(228, 22);
            this.overlayPunchoutToolStripMenuItem.Text = "Overlay Cut-Out Foreground";
            this.overlayPunchoutToolStripMenuItem.Click += new System.EventHandler(this.overlayPunchoutToolStripMenuItem_Click);
            // 
            // overlayCutOutBackgroundToolStripMenuItem
            // 
            this.overlayCutOutBackgroundToolStripMenuItem.Name = "overlayCutOutBackgroundToolStripMenuItem";
            this.overlayCutOutBackgroundToolStripMenuItem.Size = new System.Drawing.Size(228, 22);
            this.overlayCutOutBackgroundToolStripMenuItem.Text = "Overlay Cut-Out Background";
            this.overlayCutOutBackgroundToolStripMenuItem.Click += new System.EventHandler(this.overlayCutOutBackgroundToolStripMenuItem_Click);
            // 
            // editorToolStripMenuItem
            // 
            this.editorToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.undoToolStripMenuItem});
            this.editorToolStripMenuItem.Name = "editorToolStripMenuItem";
            this.editorToolStripMenuItem.Size = new System.Drawing.Size(50, 23);
            this.editorToolStripMenuItem.Text = "&Editor";
            // 
            // undoToolStripMenuItem
            // 
            this.undoToolStripMenuItem.Name = "undoToolStripMenuItem";
            this.undoToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Z)));
            this.undoToolStripMenuItem.Size = new System.Drawing.Size(144, 22);
            this.undoToolStripMenuItem.Text = "&Undo";
            this.undoToolStripMenuItem.Click += new System.EventHandler(this.undoToolStripMenuItem_Click);
            // 
            // hwPorts
            // 
            this.hwPorts.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.hwPorts.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.hwPorts.Name = "hwPorts";
            this.hwPorts.Size = new System.Drawing.Size(121, 23);
            this.hwPorts.SelectedIndexChanged += new System.EventHandler(this.hwPorts_SelectedIndexChanged);
            // 
            // hardwareToolStripMenuItem
            // 
            this.hardwareToolStripMenuItem.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.hardwareToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.sendToDeviceToolStripMenuItem,
            this.toggleDisplayToolStripMenuItem});
            this.hardwareToolStripMenuItem.Name = "hardwareToolStripMenuItem";
            this.hardwareToolStripMenuItem.Size = new System.Drawing.Size(118, 23);
            this.hardwareToolStripMenuItem.Text = "&Hardware on port :";
            // 
            // sendToDeviceToolStripMenuItem
            // 
            this.sendToDeviceToolStripMenuItem.Enabled = false;
            this.sendToDeviceToolStripMenuItem.Name = "sendToDeviceToolStripMenuItem";
            this.sendToDeviceToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F5;
            this.sendToDeviceToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.sendToDeviceToolStripMenuItem.Text = "&Send to Device";
            this.sendToDeviceToolStripMenuItem.Click += new System.EventHandler(this.sendToDeviceToolStripMenuItem_Click);
            // 
            // toggleDisplayToolStripMenuItem
            // 
            this.toggleDisplayToolStripMenuItem.Enabled = false;
            this.toggleDisplayToolStripMenuItem.Name = "toggleDisplayToolStripMenuItem";
            this.toggleDisplayToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F10;
            this.toggleDisplayToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.toggleDisplayToolStripMenuItem.Text = "Toggle Display";
            this.toggleDisplayToolStripMenuItem.Click += new System.EventHandler(this.toggleDisplayToolStripMenuItem_Click);
            // 
            // windowsToolStripMenuItem
            // 
            this.windowsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.scriptEditorToolStripMenuItem,
            this.exportToAVIToolStripMenuItem});
            this.windowsToolStripMenuItem.Name = "windowsToolStripMenuItem";
            this.windowsToolStripMenuItem.Size = new System.Drawing.Size(50, 23);
            this.windowsToolStripMenuItem.Text = "Extras";
            // 
            // scriptEditorToolStripMenuItem
            // 
            this.scriptEditorToolStripMenuItem.Name = "scriptEditorToolStripMenuItem";
            this.scriptEditorToolStripMenuItem.Size = new System.Drawing.Size(151, 22);
            this.scriptEditorToolStripMenuItem.Text = "Script Editor";
            this.scriptEditorToolStripMenuItem.Click += new System.EventHandler(this.scriptEditorToolStripMenuItem_Click);
            // 
            // exportToAVIToolStripMenuItem
            // 
            this.exportToAVIToolStripMenuItem.Name = "exportToAVIToolStripMenuItem";
            this.exportToAVIToolStripMenuItem.Size = new System.Drawing.Size(151, 22);
            this.exportToAVIToolStripMenuItem.Text = "Export to AVI...";
            this.exportToAVIToolStripMenuItem.Click += new System.EventHandler(this.exportToAVIToolStripMenuItem_Click);
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.Black;
            this.panel2.Controls.Add(this.demoMatrix);
            this.panel2.Controls.Add(this.hwDemoBright);
            this.panel2.Controls.Add(this.hwPlayBtn);
            this.panel2.Location = new System.Drawing.Point(1029, 295);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(106, 186);
            this.panel2.TabIndex = 28;
            // 
            // hwDemoBright
            // 
            this.hwDemoBright.AutoCheck = false;
            this.hwDemoBright.AutoSize = true;
            this.hwDemoBright.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.hwDemoBright.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.hwDemoBright.Font = new System.Drawing.Font("Trebuchet MS", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.hwDemoBright.ForeColor = System.Drawing.Color.Orange;
            this.hwDemoBright.Location = new System.Drawing.Point(15, 159);
            this.hwDemoBright.Name = "hwDemoBright";
            this.hwDemoBright.Size = new System.Drawing.Size(78, 20);
            this.hwDemoBright.TabIndex = 35;
            this.hwDemoBright.TabStop = true;
            this.hwDemoBright.Text = "Brightness";
            this.hwDemoBright.UseVisualStyleBackColor = true;
            this.hwDemoBright.MouseClick += new System.Windows.Forms.MouseEventHandler(this.hwDemoBright_MouseClick);
            // 
            // demoMatrix
            // 
            this.demoMatrix.DotSize = 12;
            this.demoMatrix.Location = new System.Drawing.Point(4, 3);
            this.demoMatrix.Name = "demoMatrix";
            this.demoMatrix.Size = new System.Drawing.Size(98, 98);
            this.demoMatrix.TabIndex = 4;
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.hwSendProgress});
            this.statusStrip1.Location = new System.Drawing.Point(0, 569);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(1147, 22);
            this.statusStrip1.SizingGrip = false;
            this.statusStrip1.TabIndex = 29;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // hwSendProgress
            // 
            this.hwSendProgress.Margin = new System.Windows.Forms.Padding(1, 3, 2, 1);
            this.hwSendProgress.Name = "hwSendProgress";
            this.hwSendProgress.Size = new System.Drawing.Size(720, 18);
            this.hwSendProgress.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            // 
            // hwDupeInsert
            // 
            this.hwDupeInsert.Location = new System.Drawing.Point(113, 540);
            this.hwDupeInsert.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.hwDupeInsert.Name = "hwDupeInsert";
            this.hwDupeInsert.Size = new System.Drawing.Size(133, 23);
            this.hwDupeInsert.TabIndex = 33;
            this.hwDupeInsert.Text = "Duplicate && Insert";
            this.hwDupeInsert.UseVisualStyleBackColor = true;
            this.hwDupeInsert.Click += new System.EventHandler(this.hwDupeInsert_Click);
            // 
            // hwInsert
            // 
            this.hwInsert.Location = new System.Drawing.Point(8, 540);
            this.hwInsert.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.hwInsert.Name = "hwInsert";
            this.hwInsert.Size = new System.Drawing.Size(97, 23);
            this.hwInsert.TabIndex = 34;
            this.hwInsert.Text = "Insert Frame";
            this.hwInsert.UseVisualStyleBackColor = true;
            this.hwInsert.Click += new System.EventHandler(this.hwInsert_Click);
            // 
            // saveAVI
            // 
            this.saveAVI.DefaultExt = "AVI";
            this.saveAVI.Filter = "AVI Movies|*.AVI|All Files|*.*";
            this.saveAVI.Title = "Save Movie";
            // 
            // toolList
            // 
            this.toolList.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.toolList.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.toolList.FormattingEnabled = true;
            this.toolList.IntegralHeight = false;
            this.toolList.ItemHeight = 18;
            this.toolList.Location = new System.Drawing.Point(579, 38);
            this.toolList.Name = "toolList";
            this.toolList.Size = new System.Drawing.Size(147, 251);
            this.toolList.TabIndex = 36;
            this.toolList.SelectedIndexChanged += new System.EventHandler(this.toolList_SelectedIndexChanged);
            this.toolList.KeyUp += new System.Windows.Forms.KeyEventHandler(this.toolList_KeyUp);
            this.toolList.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.toolList_MouseDoubleClick);
            // 
            // propertyGrid
            // 
            this.propertyGrid.Location = new System.Drawing.Point(732, 38);
            this.propertyGrid.Name = "propertyGrid";
            this.propertyGrid.PropertySort = System.Windows.Forms.PropertySort.Categorized;
            this.propertyGrid.Size = new System.Drawing.Size(291, 251);
            this.propertyGrid.TabIndex = 37;
            this.propertyGrid.ToolbarVisible = false;
            // 
            // exportToHeader
            // 
            this.exportToHeader.DefaultExt = "h";
            this.exportToHeader.Filter = "C Header|*.h|All Files|*.*";
            this.exportToHeader.Title = "Export Header";
            // 
            // frStrip
            // 
            this.frStrip.Location = new System.Drawing.Point(12, 295);
            this.frStrip.Name = "frStrip";
            this.frStrip.Size = new System.Drawing.Size(1011, 210);
            this.frStrip.TabIndex = 0;
            // 
            // clipboardcap
            // 
            this.clipboardcap.Location = new System.Drawing.Point(630, 540);
            this.clipboardcap.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.clipboardcap.Name = "clipboardcap";
            this.clipboardcap.Size = new System.Drawing.Size(96, 23);
            this.clipboardcap.TabIndex = 38;
            this.clipboardcap.Text = "CLIPBOARD";
            this.clipboardcap.UseVisualStyleBackColor = true;
            this.clipboardcap.Click += new System.EventHandler(this.clipboardcap_Click);
            // 
            // BadgeForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(1147, 591);
            this.Controls.Add(this.clipboardcap);
            this.Controls.Add(this.toolList);
            this.Controls.Add(this.propertyGrid);
            this.Controls.Add(this.hwInsert);
            this.Controls.Add(this.hwDupeInsert);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.hwFPS);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.hwDelAll);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.hwDel);
            this.Controls.Add(this.hwDupe);
            this.Controls.Add(this.hwAddFrame);
            this.Controls.Add(this.frStrip);
            this.Controls.Add(this.mainMenu);
            this.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ForeColor = System.Drawing.SystemColors.ControlText;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.mainMenu;
            this.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.MaximizeBox = false;
            this.Name = "BadgeForm";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Badge Designer";
            this.Load += new System.EventHandler(this.BadgeForm_Load);
            this.panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.hwFPS)).EndInit();
            this.mainMenu.ResumeLayout(false);
            this.mainMenu.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private BadgeUI.FrameStripControl frStrip;
        private BadgeUI.LEDMatrix hwMatrixLarge;
        private System.Windows.Forms.Button hwAddFrame;
        private System.Windows.Forms.Button hwDupe;
        private BadgeUI.LEDMatrix demoMatrix;
        private System.Windows.Forms.Timer hwPlay;
        private System.Windows.Forms.Button hwPlayBtn;
      private System.Windows.Forms.Button hwDel;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.SaveFileDialog saveFileDialog;
        private System.Windows.Forms.SaveFileDialog exportFileDialog;
      private System.Windows.Forms.Panel panel1;
      private System.Windows.Forms.Button hwDelAll;
        private System.Windows.Forms.Label label1;
      private System.Windows.Forms.NumericUpDown hwFPS;
        private System.Windows.Forms.MenuStrip mainMenu;
        private System.Windows.Forms.ToolStripMenuItem fileMenu;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exportBINToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
      private System.Windows.Forms.ToolStripMenuItem loadToolStripMenuItem;
      private System.Windows.Forms.Panel panel2;
      private System.Windows.Forms.ToolStripMenuItem editorToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem undoToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem hardwareToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem sendToDeviceToolStripMenuItem;
      private System.Windows.Forms.StatusStrip statusStrip1;
      private System.Windows.Forms.ToolStripProgressBar hwSendProgress;
      private System.Windows.Forms.ToolStripComboBox hwPorts;
      private System.Windows.Forms.Button hwDupeInsert;
      private System.Windows.Forms.Button hwInsert;
      private System.Windows.Forms.RadioButton hwDemoBright;
      private System.Windows.Forms.ToolStripMenuItem loadToolStripMenuItem1;
      private System.Windows.Forms.ToolStripMenuItem appendToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem overlayToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem overlayAdditiveToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem overlayPunchoutToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem toggleDisplayToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem overlayCutOutBackgroundToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem windowsToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem scriptEditorToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem exportToAVIToolStripMenuItem;
      private System.Windows.Forms.SaveFileDialog saveAVI;
      private System.Windows.Forms.ListBox toolList;
      private System.Windows.Forms.PropertyGrid propertyGrid;
      private System.Windows.Forms.ToolStripMenuItem exportToCArrayToolStripMenuItem;
      private System.Windows.Forms.SaveFileDialog exportToHeader;
      private System.Windows.Forms.Button clipboardcap;



    }
}

