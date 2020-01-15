using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.CodeDom;
using System.CodeDom.Compiler;

namespace Badge
{
  public partial class ScriptView : Form
  {
    public BadgeForm bf = null;

    public ScriptView()
    {
      InitializeComponent();

      scintillaScript.ConfigurationManager.Language = "cs";
      scintillaScript.Indentation.TabWidth = 2;
    }

    private void addScriptErrString(String text, Color color)
    {
        scriptErr.SelectionColor = color;
        scriptErr.AppendText(text);
        scriptErr.SelectionColor = Color.Black;
    }

    private void hwRun_Click(object sender, EventArgs e)
    {
      scriptErr.Clear();
      CompilerResults cr = bf.run(scintillaScript.Text, bf.UIFrameStrip, bf.UIMatrix);
      if (cr != null)
      {
        foreach (CompilerError ce in cr.Errors)
        {
          // print line
          addScriptErrString("Line " + ce.Line.ToString() + " : ", Color.Blue);

          // print if its a warning or error
          if (ce.IsWarning)
          {
            addScriptErrString("WARNING ", Color.Green);
          }
          else
          {
            addScriptErrString("ERROR ", Color.Red);
          }

          // print the error code and text out
          addScriptErrString("[" + ce.ErrorNumber.ToString() + "]   " + ce.ErrorText + "\n", Color.Red);
        }
      }
      scriptErr.Refresh();
    }
  }
}