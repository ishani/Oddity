using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.ComponentModel.Design;
using System.Windows.Forms;
using System.Windows.Forms.Design;

namespace Ishani.UI
{
	public class GradientDesigner :  ParentControlDesigner
	{
		public override ICollection AssociatedComponents
		{
			get 
			{
				if (base.Control is GradientEditorControl)
					return ((GradientEditorControl)base.Control).GradientKeys;
				else
					return base.AssociatedComponents;
			}
		}

		protected override bool DrawGrid
		{
			get { return false; }
		}

		protected override bool EnableDragRect
		{
			get { return false; }
		}
	}
}