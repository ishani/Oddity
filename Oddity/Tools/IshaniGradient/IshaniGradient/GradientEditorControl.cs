using System;
using System.Collections;
using System.ComponentModel;
using System.ComponentModel.Design;
using System.ComponentModel.Design.Serialization;
using System.Windows.Forms;
using System.Windows.Forms.Design;
using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
using System.Data;
using System.Runtime.InteropServices;
using System.Globalization;
using System.Reflection;
using System.Diagnostics;


namespace Ishani.UI
{
	/// <summary>
	/// enumeration used to define the draw style of a gradient key
	/// </summary>
	public enum GradientKeyVisualStyle
	{
		Raised,
		Flat,
		Sunken
	}

	/// <summary>
	/// 
	/// </summary>
	[ToolboxBitmap(typeof(GradientEditorControl))]
	[DefaultProperty("GradientKeys")]
	[Designer(typeof(Ishani.UI.GradientDesigner))]
	public class GradientEditorControl : System.Windows.Forms.UserControl
	{
		private System.ComponentModel.Container components = null;
		private IComponentChangeService mChangeService;

		private Int32 mGKeySelectedIndex = -1;
		private Int32 mGKeySelectedOffset = 0;
		public Int32 mLastClickedKeyIndex = 0;
		public MouseButtons mLastClickedButtons = MouseButtons.None;

		protected GradientKeyCollection mGradientKeyCollection = new GradientKeyCollection();
		protected Int32 mGradientKeyWidth = 14;
		protected Int32 mGradientKeyHeight = 20;
    protected Boolean mOnlyRedGreen = false;
		protected Border3DStyle mBorderStyle = Border3DStyle.Sunken;
		protected GradientKeyVisualStyle mKeyStyle = GradientKeyVisualStyle.Raised;
		protected Bitmap mGradientCache = null;
		protected ContextMenu mRCKeyContextmenu = null;
		protected ContextMenu mRCAreaContextmenu = null;
		private System.Windows.Forms.ColorDialog keyColorPicker;
		public System.Windows.Forms.ContextMenu defaultKeyRCMenu;
		public System.Windows.Forms.ContextMenu defaultAreaRCMenu;
		private System.Windows.Forms.MenuItem deleteKeyMenuItem;
		private System.Windows.Forms.MenuItem setColorMenuItem;
		private System.Windows.Forms.MenuItem addKeyMenuItem;
		protected bool mAutoMouseBehavior = true;


		#region Public Accessors
		[
			Category("Gradient"),
			Description("All color keys being used by the gradient"),
			DesignerSerializationVisibility(DesignerSerializationVisibility.Content),
			Editor(typeof(System.ComponentModel.Design.CollectionEditor), typeof(System.Drawing.Design.UITypeEditor))
		]
		public GradientKeyCollection GradientKeys
		{
			get { return mGradientKeyCollection; }
		} 

		[
			Category("Gradient"),
			Description("Width of the gradient keys displayed on the control")
		]
		public Int32 GradientKeyWidth
		{
			get { return mGradientKeyWidth; }
			set 
			{ 
				mGradientKeyWidth = value; 
				if (mGradientKeyWidth < 10)
				{
					mGradientKeyWidth = 10;
				}

				// invalidate after parameter change
				invalidateControl(this, EventArgs.Empty);
			}
		}


		[
			Category("Gradient"),
			Description("Only use Red/Green for display")
		]
    public Boolean OnlyRedGreen
		{
      get { return mOnlyRedGreen; }
			set 
			{
        mOnlyRedGreen = value; 

				// invalidate after parameter change
				invalidateControl(this, EventArgs.Empty);
			}
		}

    

		[
			Category("Gradient"),
			Description("Height of the gradient keys area, displayed under the gradient itself")
		]
		public Int32 GradientKeyHeight
		{
			get { return mGradientKeyHeight; }
			set
			{ 
				mGradientKeyHeight = value; 
				if (mGradientKeyHeight < 10)
				{
					mGradientKeyHeight = 10;
				}

				// invalidate after parameter change
				invalidateControl(this, EventArgs.Empty);
			}
		}

		[
		Category("Gradient"),
		DefaultValue(null),
		Description("Context menu invoked when right-clicking on a gradient key - when blank/none uses default menu handler")
		]
		public ContextMenu RCKeyContextmenu
		{
			get { return mRCKeyContextmenu; }
			set
			{ 
				if (value == null)
				{
					mRCKeyContextmenu = defaultKeyRCMenu;
				}
				else
				{
					mRCKeyContextmenu = value;
				}
			}
		}

		[
		Category("Gradient"),
		DefaultValue(null),
		Description("Context menu invoked when right-clicking in an area of the gradient control that is not a gradient key - when blank/none uses default menu handler")
		]
		public ContextMenu RCAreaContextmenu
		{
			get { return mRCAreaContextmenu; }
			set
			{ 
				if (value == null)
				{
					mRCAreaContextmenu = defaultAreaRCMenu;
				}
				else
				{
					mRCAreaContextmenu = value;
				}
			}
		}

		[
		Category("Gradient"),
		Description("if true, automatic double-click behavior will be used for this control as well as RC context menus")
		]
		public bool AutoMouseBehavior
		{
			get { return mAutoMouseBehavior; }
			set	{ mAutoMouseBehavior = value; }
		}

		[
		Category("Gradient"),
		Description("Controls which 3D border style to use for the gradient edge")
		]
		public Border3DStyle VisualBorderStyle
		{
			get { return mBorderStyle; }
			set	
			{ 
				mBorderStyle = value; 

				// invalidate after parameter change
				invalidateControl(this, EventArgs.Empty);
			}
		}

		[
		Category("Gradient"),
		Description("Controls which rendering style to use for gradient keys")
		]
		public GradientKeyVisualStyle VisualKeyStyle
		{
			get { return mKeyStyle; }
			set	
			{ 
				mKeyStyle = value; 

				// invalidate after parameter change
				invalidateControl(this, EventArgs.Empty);
			}
		}

		#endregion


		public GradientEditorControl()
		{
			// This call is required by the Windows.Forms Form Designer.
			InitializeComponent();

			// prevent flicker with double buffering and all painting inside WM_PAINT
			SetStyle(ControlStyles.DoubleBuffer | 
				ControlStyles.AllPaintingInWmPaint |
				ControlStyles.UserPaint, true);

			// register for redraw on parameter change in the key list
			mGradientKeyCollection.DataChanged += new EventHandler(invalidateControl);

			// assign default click menus
			mRCKeyContextmenu = defaultKeyRCMenu;
			mRCAreaContextmenu = defaultAreaRCMenu;
		}


		/// <summary> 
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			mGradientKeyCollection.DataChanged -= new EventHandler(invalidateControl);

			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region ISite
		public override ISite Site 
		{
			get 
			{
				return base.Site;
			}
			set 
			{
				// this value will always be null when not in design mode.
				mChangeService = (IComponentChangeService)GetService(typeof(IComponentChangeService));

				// the change service works in design mode only, and only after the component is sited.
				// register the event handlers at this time.
				if (mChangeService != null) 
				{
					// clear our the component change events to prepare for re-siting.
					mChangeService.ComponentRemoved -= new ComponentEventHandler(OnComponentRemoved);
				}

				base.Site = value;

				// this value is always null when not in design mode.
				mChangeService = (IComponentChangeService)GetService(typeof(IComponentChangeService));

				// the change service works in design mode only, and only after the component is sited.
				// register the event handlers at this time.
				if (mChangeService != null) 
				{
					mChangeService.ComponentRemoved += new ComponentEventHandler(OnComponentRemoved);
				}
			}
		}

		private void OnComponentRemoved(object sender, ComponentEventArgs ce) 
		{
      if (ce.Component is GradientEditorControl)
      {
        GradientEditorControl host = (GradientEditorControl)ce.Component;
        IDesignerHost designHost = (IDesignerHost)GetService(typeof(IDesignerHost));

        // remove our gradient key components
        // so they are not left in the serialized form definition
        foreach (Component c in host.mGradientKeyCollection)
        {
          if (c != null)
            designHost.DestroyComponent(c);
        }
      }
		}
		#endregion


		#region Component Designer generated code
		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.keyColorPicker = new System.Windows.Forms.ColorDialog();
			this.defaultKeyRCMenu = new System.Windows.Forms.ContextMenu();
			this.defaultAreaRCMenu = new System.Windows.Forms.ContextMenu();
			this.deleteKeyMenuItem = new System.Windows.Forms.MenuItem();
			this.setColorMenuItem = new System.Windows.Forms.MenuItem();
			this.addKeyMenuItem = new System.Windows.Forms.MenuItem();
			// 
			// keyColorPicker
			// 
			this.keyColorPicker.AnyColor = true;
			this.keyColorPicker.Color = System.Drawing.Color.DarkOrange;
			this.keyColorPicker.FullOpen = true;
			// 
			// defaultKeyRCMenu
			// 
			this.defaultKeyRCMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																							 this.deleteKeyMenuItem,
																							 this.setColorMenuItem});
			// 
			// defaultAreaRCMenu
			// 
			this.defaultAreaRCMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																							  this.addKeyMenuItem});
			// 
			// deleteKeyMenuItem
			// 
			this.deleteKeyMenuItem.Index = 0;
			this.deleteKeyMenuItem.Text = "Delete Key";
			this.deleteKeyMenuItem.Click += new System.EventHandler(this.deleteKeyMenuItem_Click);
			// 
			// setColorMenuItem
			// 
			this.setColorMenuItem.Index = 1;
			this.setColorMenuItem.Text = "Set Color...";
			this.setColorMenuItem.Click += new System.EventHandler(this.setColorMenuItem_Click);
			// 
			// addKeyMenuItem
			// 
			this.addKeyMenuItem.Index = 0;
			this.addKeyMenuItem.Text = "Add Key";
			this.addKeyMenuItem.Click += new System.EventHandler(this.addKeyMenuItem_Click);
			// 
			// GradientEditorControl
			// 
			this.Name = "GradientEditorControl";
			this.Size = new System.Drawing.Size(312, 56);
			this.Resize += new System.EventHandler(this.GradientEdit_Resize);
			this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GradientEdit_MouseUp);
			this.Paint += new System.Windows.Forms.PaintEventHandler(this.GradientEdit_Paint);
			this.DoubleClick += new System.EventHandler(this.GradientEditorControl_DoubleClick);
			this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.GradientEdit_MouseMove);
			this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GradientEdit_MouseDown);

		}
		#endregion

		/// <summary>
		/// generic function callback used when parameters have changed to redraw the control
		/// </summary>
		internal void invalidateControl(object sender, EventArgs e)
		{
			rebuildGradientCache();
			this.Invalidate();
		}

		/// <summary>
		/// get the area used to render the gradient, without the gradient key area
		/// and key rendering boundries at the sides
		/// </summary>
		/// <returns>a rectangle defining the gradient viewing area</returns>
		internal Rectangle getGradientViewRect()
		{
			Rectangle gradientViewRect = this.ClientRectangle;
			
			// shrink draw area so that keys are never clipped even if drawn at 0-1 extremes
			gradientViewRect.Inflate(-(mGradientKeyWidth >> 1), 0);
			gradientViewRect.Height -= mGradientKeyHeight;

			return gradientViewRect;
		}

		/// <summary>
		/// generic function callback used when parameters have changed to redraw the control
		/// </summary>
		internal void rebuildGradientCache()
		{
			Rectangle gradientViewRect = getGradientViewRect();
			Color interpCol;

			if (mGradientCache == null || (mGradientCache.Width != gradientViewRect.Width))
			{
				mGradientCache = new Bitmap(gradientViewRect.Width, 1, Graphics.FromHwnd(this.Handle));
			}

			Double iterant = 1.0 / (Double)(gradientViewRect.Width);
			for (Int32 i=0; i<gradientViewRect.Width; i++)
			{
				interpCol = getColorAtPoint( ((Double)i * iterant) );

				mGradientCache.SetPixel(i, 0, interpCol);
			}
		}

		/// <summary>
		/// add a new gradient key at the cursor's point on the screen (mapped to
		/// the gradient view area)
		/// </summary>
		/// <returns>index of new key</returns>
		internal Int32 addNewKeyAtCursor()
		{
			Rectangle gradientViewRect = getGradientViewRect();
			Point clientPoint = PointToClient(Cursor.Position);

			// add a new key, set to the colour at the point clicked
			GradientKey newKey = new GradientKey();
			newKey.Position = ((1.0 / (Double)gradientViewRect.Width) * (Double)(clientPoint.X));
			newKey.KeyColor = getColorAtPoint(newKey.Position);

			return mGradientKeyCollection.Add(newKey);
		}

		/// <summary>
		/// publically and internally used function to interpolate the gradient
		/// and return a color value at the given point
		/// </summary>
		/// <param name="value">a value between 0 and 1, 0% and 100% of the gradient</param>
		/// <returns>the interpolated color at this point</returns>
		public Color getColorAtPoint(Double value)
		{
			ArrayList gkArray = mGradientKeyCollection.getSortedArray();

			// continue if we have some keys to work with
			if (gkArray.Count > 0)
			{
				// if only one key, just return that colour
				if (gkArray.Count == 1)
				{
					return ((GradientKey)gkArray[0]).KeyColor;
				}

				// get the first/last keys to check for out-of-bounds requests
				GradientKey firstKey = gkArray[0] as GradientKey;
				GradientKey lastKey = gkArray[gkArray.Count - 1] as GradientKey;

				// if value is before the first or after the last key, just return their colours to repeat
				if (value <= firstKey.Position)
				{
					return firstKey.KeyColor;
				}
				else if (value >= lastKey.Position)
				{
					return lastKey.KeyColor;
				}
				else
				{
					// go search for the keys that will be used as interpolators
					for (Int32 i=0; i<gkArray.Count-1; i++)
					{
						if (((GradientKey)gkArray[i+1]).Position >= value)
						{
							// get the key pair to use
							GradientKey primary = gkArray[i] as GradientKey;
							GradientKey secondary = gkArray[i+1] as GradientKey;

							// work out a interpolation pair based on position of keys and value passed
							Double keyDelta = 1.0 / (secondary.Position - primary.Position);
							Double interPos = keyDelta * (value - primary.Position);
							if (interPos > 1.0) interPos = 1.0;
							if (interPos < 0.0) interPos = 0.0;
							Double invInterPos = 1.0 - interPos;

							// interpolate the keys
							Double fR = ((Double)primary.KeyColor.R * invInterPos) + ((Double)secondary.KeyColor.R * interPos);
							Double fG = ((Double)primary.KeyColor.G * invInterPos) + ((Double)secondary.KeyColor.G * interPos);

              Double fB = 0;
              if (!mOnlyRedGreen)
							  fB = ((Double)primary.KeyColor.B * invInterPos) + ((Double)secondary.KeyColor.B * interPos);
							
							// spit out a Color class
							return Color.FromArgb((Int32)fR, (Int32)fG, (Int32)fB);
						}
					}
				}
			}

			// 'empty' colour
			return Color.Gray;
		}

		private void GradientEdit_Paint(object sender, System.Windows.Forms.PaintEventArgs e)
		{
			Rectangle gradientViewRect = getGradientViewRect();
			
			// create an area for keys to be drawn in; although their tips
			// are drawn over the gradient display this defines the lower key section only
			Rectangle keyDrawArea = new Rectangle(
				gradientViewRect.Left, 
				gradientViewRect.Height, 
				gradientViewRect.Width, 
				mGradientKeyHeight);

			// if the cache is empty, rebuild the gradient image
			if (mGradientCache == null)
			{
				rebuildGradientCache();
			}
			
			// render the cached gradient image if available and area to render is of a usable size
			if (mGradientCache != null && (gradientViewRect.Height >= 1 && gradientViewRect.Width >= 1))
			{
				// setup interp modes to make sure the single pixel image is stretched correctly
				e.Graphics.CompositingQuality = CompositingQuality.AssumeLinear;
				e.Graphics.PixelOffsetMode = PixelOffsetMode.HighQuality;
				e.Graphics.InterpolationMode = InterpolationMode.NearestNeighbor;

				// stretch the image into the area reserved for the gradient
				e.Graphics.DrawImage(
					mGradientCache,
					gradientViewRect);
			}

			// draw a border around the gradient display
			ControlPaint.DrawBorder3D(
				e.Graphics,
				gradientViewRect,
				mBorderStyle);

			// draw all the keys
			for (Int32 i=0; i<mGradientKeyCollection.Count; i++)
			{
				mGradientKeyCollection[i].Paint(
					e.Graphics,
					mKeyStyle,
					mGradientKeyWidth,
					keyDrawArea,
					(i == mGKeySelectedIndex));
			}
		}

		private void GradientEdit_Resize(object sender, System.EventArgs e)
		{
			// redraw
			invalidateControl(sender, e);
		}

		internal void GradientEdit_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
		{
			Point clientPoint = new Point(e.X, e.Y);
			mLastClickedKeyIndex = -1;
			mLastClickedButtons = e.Button;

			for (Int32 i=0; i<mGradientKeyCollection.Count; i++)
			{
				// hit test the key with our client point
				if (mGradientKeyCollection[i].HitTest(clientPoint, out mGKeySelectedOffset))
				{
					mLastClickedKeyIndex = i;

					if (e.Button == MouseButtons.Right)
					{
						if (mRCKeyContextmenu != null)
						{
							mRCKeyContextmenu.Show(this, new Point(e.X, e.Y));
						}
					}
					else if (e.Button == MouseButtons.Left)
					{
						// set this gradient key to be selected for movement
						mGKeySelectedIndex = i;
						invalidateControl(sender, e);

						// aquire all mouse movement
						this.Capture = true;
					}

					return;
				}
			}

			if (e.Button == MouseButtons.Right)
			{
				if (mRCAreaContextmenu != null)
				{
					mRCAreaContextmenu.Show(this, new Point(e.X, e.Y));
				}
			}
		}

		internal void GradientEdit_MouseUp(object sender, System.Windows.Forms.MouseEventArgs e)
		{
			// release the selected gradient key
			if (mGKeySelectedIndex != -1)
			{
				mLastClickedKeyIndex = mGKeySelectedIndex;
				mLastClickedButtons = e.Button;

				mGKeySelectedIndex = -1;
				invalidateControl(sender, e);

				// release mouse movement capture
				this.Capture = false;
			}
		}

		internal void GradientEdit_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
		{
			if (mGKeySelectedIndex != -1)
			{
				Point clientPoint = new Point(e.X, e.Y);
				Rectangle gradientViewRect = getGradientViewRect();

				// find the keys new position
				// automatically clamped by the value accessor
				mGradientKeyCollection[mGKeySelectedIndex].Position = 
					((1.0 / (Double)gradientViewRect.Width) * (Double)(clientPoint.X - mGKeySelectedOffset));

				// changing a key position automatically invalidates the gradient
				// so no code is required here to do so				
			}
		}

		private void GradientEditorControl_DoubleClick(object sender, System.EventArgs e)
		{
			if (mAutoMouseBehavior && mLastClickedButtons == MouseButtons.Left)
			{
				if (mLastClickedKeyIndex != -1)
				{
					setColorMenuItem_Click(sender, e);
					return;
				}

				addKeyMenuItem_Click(sender, e);
			}
		}

		private void deleteKeyMenuItem_Click(object sender, System.EventArgs e)
		{
			ContextMenu cm = ((MenuItem)sender).Parent as ContextMenu;
			if (cm != null)
			{
				GradientEditorControl gec = cm.SourceControl as GradientEditorControl;
				if (gec != null)
				{
					gec.GradientKeys.RemoveAt(gec.mLastClickedKeyIndex);
				}
			}		
		}

		private void setColorMenuItem_Click(object sender, System.EventArgs e)
		{
			if (mLastClickedKeyIndex != -1)
			{
				// ask the color picker dialog to handle the change of color for the key
				this.keyColorPicker.Color = mGradientKeyCollection[mLastClickedKeyIndex].KeyColor;
				if (this.keyColorPicker.ShowDialog() == DialogResult.OK)
				{
					mGradientKeyCollection[mLastClickedKeyIndex].KeyColor = this.keyColorPicker.Color;
				}
			}
		}

		private void addKeyMenuItem_Click(object sender, System.EventArgs e)
		{
			addNewKeyAtCursor();
		}
	}
}
