using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Drawing;
using System.Data;
using System.Reflection;
using System.Reflection.Emit;
using System.CodeDom;
using System.CodeDom.Compiler;
using System.Xml;
using Microsoft.CSharp;
using BadgeUI;

namespace Badge
{
  public class CompiledTool
  {
    public String Label;
    public Type CompiledType;
    public MethodInfo ToolMain;
    public object Instance;

    public override string ToString()
    {
      return Label;
    }
  }

  partial class BadgeForm
  {
    List<String> mNamespaces = new List<String>();
    List<String> mAssemblyRefs = new List<String>();
    List<CompiledTool> mTools = new List<CompiledTool>();

    private CSharpCodeProvider mProvider;
    private CompilerParameters mCompilerParam;

    private void initScriptCompiler()
    {
      // add default references
      mNamespaces.Add("System");
      mNamespaces.Add("System.Collections.Generic");
      mNamespaces.Add("System.Windows.Forms");
      mNamespaces.Add("System.Text");
      mNamespaces.Add("System.ComponentModel");
      mNamespaces.Add("BadgeCore");
      mAssemblyRefs.Add("mscorlib.dll");
      mAssemblyRefs.Add("System.dll");
      mAssemblyRefs.Add("System.Windows.Forms.dll");

      string rootPath = Path.GetDirectoryName(Assembly.GetCallingAssembly().Location);
      mAssemblyRefs.Add(rootPath + "\\BadgeCore.dll");

      // create a new codeDOM compiler
      mProvider = new CSharpCodeProvider();

      // create some compiler parameters
      mCompilerParam = new CompilerParameters(mAssemblyRefs.ToArray());
      mCompilerParam.GenerateInMemory = true;
      mCompilerParam.CompilerOptions = "/target:library /optimize";
      mCompilerParam.TreatWarningsAsErrors = false;
    }

    private void loadTools()
    {
      if (!Directory.Exists("tools"))
        return;

      string[] fxFiles = Directory.GetFiles("tools", "*.cs", SearchOption.TopDirectoryOnly);
      foreach (String s in fxFiles)
      {
        TextReader tr = new StreamReader(s);
        String fileName = Path.GetFileNameWithoutExtension(s);
        String className = "Tool_" + fileName;

        StringBuilder srcCode = new StringBuilder(512);
        foreach (string ns in mNamespaces)
        {
          srcCode.AppendFormat("using {0};\n", ns);
        }
        srcCode.Append("namespace BadgeScript { public class ");
        srcCode.Append(className);
        srcCode.Append(": ScriptedTool {");
        srcCode.Append(tr.ReadToEnd());
        srcCode.Append("} }");

        CompilerResults result = mProvider.CompileAssemblyFromSource(
          mCompilerParam,
          srcCode.ToString());

        if (result.Errors.Count > 0)
        {
          StringBuilder errMsgs = new StringBuilder(512);
          foreach (CompilerError ce in result.Errors)
          {
            errMsgs.Append("Line ");
            errMsgs.Append(ce.Line.ToString());
            errMsgs.Append(":    ");
            errMsgs.Append(ce.ErrorText);
            errMsgs.Append(Environment.NewLine);
            errMsgs.Append(Environment.NewLine);
          }
          MessageBox.Show(errMsgs.ToString(), "Error compiling \"" + s + "\"", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
        else
        {
          CompiledTool ct = new CompiledTool();

          ct.Label = fileName;

          ct.CompiledType = result.CompiledAssembly.GetType("BadgeScript." + className);
          if (ct.CompiledType == null)
          {
            MessageBox.Show("Could not find compiled tool type information.", "Error compiling \"" + s + "\"", MessageBoxButtons.OK, MessageBoxIcon.Error);
            continue;
          }

          ct.ToolMain = ct.CompiledType.GetMethod("main", BindingFlags.Public | BindingFlags.DeclaredOnly | BindingFlags.Instance);
          if (ct.ToolMain == null)
          {
            MessageBox.Show("Could not find main() function in compiled tool.", "Error compiling \"" + s + "\"", MessageBoxButtons.OK, MessageBoxIcon.Error);
            continue;
          }

          ct.Instance = Activator.CreateInstance(ct.CompiledType, false);
          if (ct.Instance == null)
          {
            MessageBox.Show("Could not create instance of tool.", "Error compiling \"" + s + "\"", MessageBoxButtons.OK, MessageBoxIcon.Error);
            continue;
          }

          mTools.Add(ct);

          toolList.Items.Add(ct);
        }
      }
    }


    public CompilerResults run(String script, FrameStripControl strip, LEDMatrix matrix)
    {
      Int32 numExtraLines = 0;
      StringBuilder srcCode = new StringBuilder();

      // add each namespace into the source code
      foreach (string ns in mNamespaces)
      {
        srcCode.AppendFormat("using {0};\n", ns);
        numExtraLines++;
      }

      // form a dummy class and function, etc
      srcCode.Append("namespace Badge\n{\npublic class ScriptDynamic\n{\n\n");
      srcCode.Append("static public void ScriptRun(Frame editingFrame, FrameStrip strip)\n{");
      numExtraLines += 6;

      // append all the actual source code
      srcCode.Append(script);

      // finish the source code
      srcCode.Append("}\n}\n}\n");

      // compile it
      CompilerResults result = mProvider.CompileAssemblyFromSource(
        mCompilerParam,
        srcCode.ToString());

      // nothing wrong with the compile?
      if (result.Errors.Count == 0)
      {
        try
        {
          // invoke the compiled funtion
          Type dynType = result.CompiledAssembly.GetType("Badge.ScriptDynamic");
          MethodInfo runMethod = dynType.GetMethod("ScriptRun", BindingFlags.Public | BindingFlags.Static);
          runMethod.Invoke(null, new object[] { matrix.CurrentFrame, strip.Data() });
        }
        catch (Exception e)
        {
          // something bad happened here
          MessageBox.Show("Fatal Compiler Error : \n\n" + e.Message, "Script Compiler");
        }
        return null;
      }
      else
      {
        // adjust all compiler line errors to take namespace/class additions
        // into account, so any error reporting will be accurate to the original script file
        foreach (CompilerError er in result.Errors)
        {
          er.Line -= numExtraLines;
        }
      }
      return result;
    }
  }
}
