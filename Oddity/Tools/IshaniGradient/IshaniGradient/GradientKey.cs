using System;
using System.Collections;
using System.ComponentModel;
using System.ComponentModel.Design;
using System.ComponentModel.Design.Serialization;
using System.Windows.Forms;
using System.Windows.Forms.Design;
using System.Drawing;
using System.Data;
using System.Runtime.InteropServices;
using System.Globalization;
using System.Reflection;


namespace Ishani.UI
{
	/// <summary>
	/// 
	/// </summary>
	[DesignTimeVisible(false), ToolboxItem(false), ComVisible(false)]
	[DefaultProperty("Position")]
	[DefaultEvent("PositionChanged")]
	public class GradientKey : Component, IComparable, ICloneable, IDisposable
	{
		// rendering constants
		internal const Int32	GradientKeyLipHeight		= 8;
		internal const Int32	GradientKeyInteriorRim		= 2;


		// values defining this key
		private Double			mPosition;
		private Color			mColor;

		// cached brush used during drawing
		private SolidBrush 		mDrawColorBrush;

		// cached rendering and hittest boundaries
		private Rectangle		mBounds;
		private Int32			mBoundHash;

		// event handlers called when properties change
		public event EventHandler	PositionChanged;
		public event EventHandler	ColorChanged;


		/// <summary>
		/// get or set the position of the key, a value between
		/// 0 and 1 defining where in the gradient the key is placed
		/// </summary>
		public Double	Position
		{
			get { return mPosition; }
			set 
			{ 
				mPosition = value; 

				// clamp value within 0 and 1 range
				if (mPosition < 0.0)
				{
					mPosition = 0.0;
				}
				else if (mPosition > 1.0)
				{
					mPosition = 1.0;
				}

				// reset bounds for regeneration
				// during next draw / paint
				mBounds = Rectangle.Empty;

				OnPositionChanged();
			}
		}

		public Color	KeyColor
		{
			get { return mColor; }
			set 
			{ 
				// set value
				mColor = value; 

				// reset cached color brush to force
				// rebuild when drawing / painting
				if (mDrawColorBrush != null)
				{
					mDrawColorBrush.Dispose();
					mDrawColorBrush = null;
				}

				OnColorChanged();
			}
		}

		public void OnPositionChanged() 
		{ 
			if (this.PositionChanged != null) 
				this.PositionChanged(this, EventArgs.Empty); 
		}

		public void OnColorChanged() 
		{ 
			if (this.ColorChanged != null) 
				this.ColorChanged(this, EventArgs.Empty); 
		}


		/// <summary>
		/// key constructor sets all values to defaults
		/// </summary>
		public GradientKey()
		{
			mPosition = 0.0;
			mColor = Color.Blue;
			mBounds = Rectangle.Empty;
			mBoundHash = 0;
			PositionChanged = null;
			ColorChanged = null;
		}

		/// <summary>
		/// construct from a given GradientKey instance
		/// </summary>
		/// <param name="fromKey">key to construct from</param>
		public GradientKey(
			GradientKey fromKey)
		{
			mPosition = fromKey.Position;
			mColor = fromKey.KeyColor;
			mBounds = Rectangle.Empty;
			mBoundHash = 0;
			PositionChanged = fromKey.PositionChanged;
			ColorChanged = fromKey.ColorChanged;
		}

		/// <summary>
		/// support for ICloneable Clone method, returns carbon copy of gradient key
		/// </summary>
		/// <returns>new gradient key instance based on this one</returns>
		public object Clone()
		{
			return new GradientKey(this);
		}

		/// <summary>
		/// Compares two gradient keys (positions) and returns standard IComparable values
		/// for use with sorting etc
		/// </summary>
		/// <param name="keyB">key to compare against</param>
		/// <returns>using Position values, -1 if this key is less that the given, 0 if same, 1 if greater</returns>
		public int CompareTo(
			object keyB)
		{
			GradientKey gkB = (GradientKey)keyB;

			if (mPosition < gkB.Position)
			{
				return -1;
			}
			else if (mPosition == gkB.Position)
			{
				return 0;
			}

			return 1;
		}

		/// <summary> 
		/// clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if (disposing)
			{
				if (mDrawColorBrush != null)
				{
					mDrawColorBrush.Dispose();
					mDrawColorBrush = null;
				}
			}
			base.Dispose( disposing );
		}

		/// <summary>
		/// test the coordinates in parent control space against this gradient key
		/// </summary>
		/// <param name="pt">coordinates to test, given in coordinate space of owning GradientEdit control</param>
		/// <returns>true if the point hits this key</returns>
		public bool HitTest(
			Point pt,
			out Int32 xOffset)
		{
			if (mBounds.IsEmpty)
			{
				xOffset = 0;
				return false;
			}
			xOffset = (pt.X - mBounds.Left);
			return mBounds.Contains(pt);
		}

		/// <summary>
		/// render the key onto a graphics object surface
		/// </summary>
		/// <param name="g">graphics instance to use, usually from Paint callback</param>
		/// <param name="keyWidth">key is drawn with this width</param>
		/// <param name="keyDrawArea">defines the main key area on the owning form</param>
		public void Paint(
			Graphics g, 
			GradientKeyVisualStyle style,
			Int32 keyWidth,
			Rectangle keyDrawArea,
			bool selected)
		{
			Int32 xLoc = keyDrawArea.Left + (Int32)((Double)keyDrawArea.Width * mPosition);
			Int32 keyBtnWidth = keyWidth >> 1;

			ButtonState buttonStyle = ButtonState.Normal;
			Border3DStyle borderStyle = Border3DStyle.Sunken;

			// sort out visual style for the key
			switch (style)
			{
				case GradientKeyVisualStyle.Flat:
					{
						buttonStyle = ButtonState.Flat;
						borderStyle = selected?Border3DStyle.SunkenInner:Border3DStyle.Flat;
					}
					break;

				case GradientKeyVisualStyle.Raised:
					{
						buttonStyle = ButtonState.Normal;
						borderStyle = selected?Border3DStyle.Sunken:Border3DStyle.SunkenOuter;
					}
					break;

				case GradientKeyVisualStyle.Sunken:
					{
						buttonStyle = ButtonState.Pushed;
						borderStyle = selected?Border3DStyle.SunkenInner:Border3DStyle.RaisedInner;
					}
					break;
			}

			// regenerate the bounding box if it has been nullified or
			// if the parent volume has changed
			if (mBounds.IsEmpty || (keyDrawArea.GetHashCode() != mBoundHash))
			{
				mBounds = new Rectangle(
					xLoc - keyBtnWidth,
					keyDrawArea.Top - GradientKeyLipHeight,
					keyWidth,
					keyDrawArea.Height + GradientKeyLipHeight);

				// save hash code of parent volume for future comparisons
				mBoundHash = keyDrawArea.GetHashCode();
			}

			// render a button to act as the key container graphic
			ControlPaint.DrawButton(
				g,
				mBounds.Left,
				mBounds.Top,
				mBounds.Width,
				mBounds.Height,
				buttonStyle);

			// create new color brush if not already generated
			if (mDrawColorBrush == null)
				mDrawColorBrush = new SolidBrush(mColor);

			// draw a color block to show the color set on this key
			Rectangle colorBlock = new Rectangle(
				mBounds.Left + GradientKeyInteriorRim, 
				mBounds.Top + GradientKeyLipHeight, 
				mBounds.Width - (GradientKeyInteriorRim << 1), 
				mBounds.Height - GradientKeyLipHeight - GradientKeyInteriorRim);

			if (style == GradientKeyVisualStyle.Flat)
			{
				colorBlock.Inflate(-1, -1);
			}

			g.FillRectangle(mDrawColorBrush, colorBlock);

			// sink the color block to give it some depth, and sink it
			// fully if this key is being selected and moved about
			ControlPaint.DrawBorder3D(
				g,
				colorBlock,
				borderStyle);
		}
	}
}
