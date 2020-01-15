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
using Crownwood.Magic.Collections;

namespace Ishani.UI
{
	/// <summary>
	/// Holds all the gradient keys used by a gradient control
	/// </summary>
	public class GradientKeyCollection : CollectionWithEvents
	{
		public event EventHandler DataChanged;

		/// <summary>
		/// reference to our sorted version of the internal array
		/// rebuilt when required, only invalidated back to null when
		/// a value in the internal array is modified
		/// </summary>
		internal ArrayList	mSortedVersion = null;


		/// <summary>
		/// link to the changed callback so that the sorted
		/// array version can be invalidated when anything changed
		/// </summary>
		public GradientKeyCollection()
		{
			this.Cleared += new CollectionClear(KeySequenceChanged);
			this.Inserted += new CollectionChange(KeySequenceChanged);
			this.Removed += new CollectionChange(KeySequenceChanged);
		}

		/// <summary>
		/// set the sorted array to null so it is rebuilt when required
		/// </summary>
		public void KeySequenceChanged()
		{
			mSortedVersion = null;
			OnDataChanged(this, EventArgs.Empty);
		}

		/// <summary>
		/// set the sorted array to null so it is rebuilt when required
		/// </summary>
		public void KeySequenceChanged(object sender, EventArgs e)
		{
			mSortedVersion = null;
			OnDataChanged(sender, e);
		}

		/// <summary>
		/// set the sorted array to null so it is rebuilt when required
		/// </summary>
		public void KeySequenceChanged(int index, object value)
		{
			mSortedVersion = null;
			OnDataChanged(value, EventArgs.Empty);
		}

		/// <summary>
		/// 
		/// </summary>
		public void OnDataChanged(object sender, EventArgs e)
		{
			if (DataChanged != null)
				DataChanged(sender, e);
		}

		/// <summary>
		/// called externally to get the keys, sorted by position, in a new array
		/// only built if anything has changed since last call to this function
		/// </summary>
		/// <returns>an ArrayList of sorted gradient keys</returns>
		public ArrayList getSortedArray()
		{
			if (mSortedVersion == null)
			{
				mSortedVersion = (ArrayList)base.InnerList.Clone();
				mSortedVersion.Sort();
			}

			return mSortedVersion;
		}

		/// <summary>
		/// overriden accessor to get access to the gradient keys, also used by the
		/// design-time collection editor
		/// </summary>
		public GradientKey this[int index]
		{
			get 
			{ 
				if (index < 0 || index >= base.List.Count)  
					throw new ArgumentOutOfRangeException("Invalid Argument {0}: {1}", "index", index.ToString()); 
 
				return base.List[index] as GradientKey; 
			}
			set 
			{
				if (value == null) 
					throw new ArgumentNullException("value"); 
 
				if (index < 0 || index >= base.List.Count) 
					throw new ArgumentOutOfRangeException(String.Format("Invalid Argument {0}: {1}", "index", index.ToString())); 
 
				OnDataChanged(this, EventArgs.Empty);
				base.List[index] = value as GradientKey; 
			}
		}

		public void AddRange(GradientKey[] items)
		{
			foreach (GradientKey gk in items)
			{
				gk.ColorChanged += new EventHandler(OnDataChanged);
				gk.PositionChanged += new EventHandler(KeySequenceChanged);

				base.List.Add(gk);
			}

			KeySequenceChanged();  
		}

		public int Add(GradientKey gk) 
		{ 
			gk.ColorChanged += new EventHandler(OnDataChanged);
			gk.PositionChanged += new EventHandler(KeySequenceChanged);

			int n = base.List.Add(gk); 
			KeySequenceChanged();
 
			return n; 
		} 

		public void Insert(int index, GradientKey gk) 
		{ 
			gk.ColorChanged += new EventHandler(OnDataChanged);
			gk.PositionChanged += new EventHandler(KeySequenceChanged);

			base.List.Insert(index, gk); 
			KeySequenceChanged();
		}

		public void Remove(GradientKey gk)
		{
			gk.ColorChanged -= new EventHandler(OnDataChanged);
			gk.PositionChanged -= new EventHandler(KeySequenceChanged);

			base.List.Remove(gk);
		}

		public bool Contains(GradientKey value)
		{
			return base.List.Contains(value as object);
		}

		public int IndexOf(GradientKey value)
		{
			return base.List.IndexOf(value);
		}
	}
}
