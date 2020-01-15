using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.CodeDom;
using System.CodeDom.Compiler;
using System.Windows.Forms;
using System.Windows.Forms.Integration;

using ICSharpCode.AvalonEdit;
using ICSharpCode.AvalonEdit.Document;
using ICSharpCode.AvalonEdit.Gui;
using ICSharpCode.AvalonEdit.Highlighting;
using MatrixCore;

namespace Matrix
{
  public partial class MatrixForm : Form
  {
    private ScriptingEngine Scripting;
    private ElementHost ScriptWPFHost;
    private TextEditor ScriptEditor;

    public MatrixForm()
    {
      InitializeComponent();

      // fire up the scripting system
      Scripting = new ScriptingEngine();
      Scripting.LoadTools();

      // colourize the hints box for the scripting window
      wHintBox.SelectionLength = 6;
      wHintBox.SelectionColor = Color.Blue;
      wHintBox.SelectionStart = wHintBox.Find("FrameSequence");
      wHintBox.SelectionLength = "FrameSequence".Length;
      wHintBox.SelectionColor = Color.Blue;

      // build the script editor window
      ScriptEditor = new TextEditor();
      ScriptEditor.FontFamily = new System.Windows.Media.FontFamily("Courier New");
      ScriptEditor.FontSize = 14.0f;
      ScriptEditor.SyntaxHighlighting = HighlightingManager.Instance.GetDefinitionByExtension(".cs");      
      ScriptEditor.KeyDown += new System.Windows.Input.KeyEventHandler(avalon_KeyDown);

      // host it (it's WPF)
      ScriptWPFHost = new ElementHost();
      ScriptWPFHost.Dock = DockStyle.Fill;
      ScriptWPFHost.Child = ScriptEditor;
      wEditorDock.Controls.Add(ScriptWPFHost);


      TabPage tb = new TabPage("Pattern 1");
      FrameSequenceView sv = new FrameSequenceView();
      sv.Dock = DockStyle.Fill;
      tb.Controls.Add(sv);
      wSequenceTabs.TabPages.Add(tb);
 
      
      Frame t = new Frame();
      sv.Sequence.Add(t, false);
      wFrameEditor.ViewFrame = t;
    }

    // execute the script  CTRL-RTN
    void avalon_KeyDown(object sender, System.Windows.Input.KeyEventArgs e)
    {
      wScriptStat.Visible = false;

      if (e.Key == System.Windows.Input.Key.OemPeriod)
      {
        // autocomplete
        
      }
      else if (e.Key == System.Windows.Input.Key.Return && (Control.ModifierKeys == Keys.Control))
      {
        // execute the current script text
        CompilerResults cr = Scripting.Run(ScriptEditor.Text, wFrameEditor.ViewFrame, null);

        // if we have errors, report them in a pop-up
        if (cr != null && cr.Errors.Count != 0)
        {
          StringBuilder sb = new StringBuilder(64);
          foreach (CompilerError c in cr.Errors)
          {
            sb.AppendFormat("[{0}] ", c.Line);
            sb.Append(c.ErrorText);
            sb.Append("\n");
          }

          ScriptingErrorForm sef = new ScriptingErrorForm(sb.ToString());
          Point newLoc = new Point();
          newLoc.X = (Int32)((float)ScriptWPFHost.Width * 0.8f);
          newLoc.Y = (Int32)((float)ScriptWPFHost.Height);
          sef.Location = this.PointToScreen(newLoc);

          sef.Show();
        }
        else
        {
          // show the icon that means "everything's ok!"
          wScriptStat.Visible = true;
        }
      }
    }
  }
}