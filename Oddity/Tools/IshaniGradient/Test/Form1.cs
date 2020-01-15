using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Test
{
  public partial class IGradTest : Form
  {
    public IGradTest()
    {
      InitializeComponent();
    }

    private void gradientEditorControl1_Load(object sender, EventArgs e)
    {

    }

    private void button1_Click(object sender, EventArgs e)
    {
      Int32 steps = (Int32)stepCount.Value;
      double stepDelta = 1.0 / (double)(steps - 1);


      StringBuilder rOut = new StringBuilder(1024);
      StringBuilder gOut = new StringBuilder(1024);
      StringBuilder bOut = new StringBuilder(1024);


      rOut.AppendFormat("const byte {0}_red[{1}]   = {{", codeName.Text, steps);
      gOut.AppendFormat("const byte {0}_green[{1}] = {{", codeName.Text, steps);
      bOut.AppendFormat("const byte {0}_blue[{1}]  = {{", codeName.Text, steps);


      double pt = 0;
      for (Int32 i = 0; i < steps; i++)
      {
        Color gc = gradientControl.getColorAtPoint(pt);

        double R = (double)gc.R / 255.0;
        double G = (double)gc.G / 255.0;
        double B = (double)gc.B / 255.0;

        byte R4 = (byte)Math.Floor(R * 15.0);
        byte G4 = (byte)Math.Floor(G * 15.0);
        byte B4 = (byte)Math.Floor(B * 15.0);

        rOut.AppendFormat(" {0,2},", R4);
        gOut.AppendFormat(" {0,2},", G4);
        bOut.AppendFormat(" {0,2},", B4);

        pt += stepDelta;
      }

      String rRes = rOut.ToString().TrimEnd(new char[] { ',' });
      String gRes = gOut.ToString().TrimEnd(new char[] { ',' });
      String bRes = bOut.ToString().TrimEnd(new char[] { ',' });

      rRes += " }; " + Environment.NewLine;
      gRes += " }; " + Environment.NewLine;
      bRes += " }; " + Environment.NewLine;

      Clipboard.SetText(rRes + gRes + bRes);

    }
  }
}