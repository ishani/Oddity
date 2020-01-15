using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Text;
using System.Windows.Forms;

using System.Reflection;
using System.IO;
using System.IO.Ports;
using System.Threading;

using BadgeUI;
using BadgeCore;

using Ishani.Movie;


namespace Badge
{
  public partial class BadgeForm : Form
  {
    private Int32 m_playFrame;
    private ScriptView sv = new ScriptView();

    public BadgeForm()
    {
      InitializeComponent();

      sv.bf = this;

      // fill in our serial port options
      string[] ports = SerialPort.GetPortNames();
      foreach (String p in ports)
      {
        hwPorts.Items.Add(p);
      }

      frStrip.Data().SelectionChange += FrameStripSelection;
      frStrip.Data().addFrame(new Frame(), true);

      demoMatrix.m_considerFrameBrightness = false;
      hwDemoBright.Checked = false;

      initScriptCompiler();
      loadTools();

      GC.Collect();
      GC.WaitForPendingFinalizers();
    }

    public FrameStripControl UIFrameStrip
    {
      get { return frStrip; }
    }

    public LEDMatrix UIMatrix
    {
      get { return hwMatrixLarge; }
    }


    void FrameStripSelection(object sender, EventArgs e)
    {
      hwMatrixLarge.setFrame(frStrip.Data().SelectedFrame);
    }

    private void hwAddFrame_Click(object sender, EventArgs e)
    {
      Frame f = new Frame();

      Frame n = frStrip.Data().getLastFrame();
      if (n != null)
        f.Brightness = n.Brightness;

      frStrip.Data().addFrame(f, true);
    }

    private void hwInsert_Click(object sender, EventArgs e)
    {
      Frame f = new Frame();

      Frame n = frStrip.Data().SelectedFrame;
      if (n != null)
        f.Brightness = n.Brightness;

      frStrip.Data().insertFrame(f, frStrip.Data().getIndexForFrame(frStrip.Data().SelectedFrame), true);
    }

    private void hwDupe_Click(object sender, EventArgs e)
    {
      Frame f = frStrip.Data().SelectedFrame;
      if (f != null)
        frStrip.Data().addFrame(f.clone(), true);
    }

    private void hwDupeInsert_Click(object sender, EventArgs e)
    {
      Frame f = frStrip.Data().SelectedFrame;
      if (f != null)
        frStrip.Data().insertFrame(f.clone(), frStrip.Data().getIndexForFrame(frStrip.Data().SelectedFrame), true);
    }

    private void hwDel_Click(object sender, EventArgs e)
    {
      stopAnimDemo();
      Frame f = frStrip.Data().SelectedFrame;
      if (f != null)
        frStrip.Data().deleteFrame(f);
    }

    private void hwPlay_Tick(object sender, EventArgs e)
    {
      if (frStrip.Data().NumFrames == 0)
        return;

      m_playFrame++;
      if (m_playFrame >= frStrip.Data().NumFrames)
        m_playFrame = 0;

      demoMatrix.setFrame(frStrip.Data().getFrameAtIndex(m_playFrame));
    }

    private void stopAnimDemo()
    {
      hwPlay.Enabled = false;
      demoMatrix.setFrame(null);

      hwPlayBtn.Text = "Play";
    }

    private void hwPlayBtn_Click(object sender, EventArgs e)
    {
      if (hwPlay.Enabled)
      {
        stopAnimDemo();
      }
      else
      {
        hwPlayBtn.Text = "Stop";

        m_playFrame = 0;
        hwPlay.Enabled = true;
      }
    }

    private void undoToolStripMenuItem_Click(object sender, EventArgs e)
    {
      hwMatrixLarge.undo();
    }


    private void hwDelAll_Click(object sender, EventArgs e)
    {
      stopAnimDemo();
      frStrip.Data().deleteAll();
      GC.Collect();
      GC.WaitForPendingFinalizers();
    }

    private void BadgeForm_Load(object sender, EventArgs e)
    {
      hwFPS.Value = (Int32)frStrip.Data().FPS;
    }

    private void hwFPS_ValueChanged(object sender, EventArgs e)
    {
      frStrip.Data().FPS = (Byte)hwFPS.Value;
      hwPlay.Interval = 1000 / (Int32)hwFPS.Value;
    }

    SerialPort serialPort = null;

    private void hwPorts_SelectedIndexChanged(object sender, EventArgs e)
    {
      try
      {
        serialPort = new SerialPort(hwPorts.SelectedItem.ToString(), 9600, Parity.None, 8, StopBits.One);
        serialPort.Handshake = Handshake.None;
        serialPort.WriteBufferSize = 4096;
        serialPort.ReadBufferSize = 4096;
        serialPort.Open();

        sendToDeviceToolStripMenuItem.Enabled = true;
        toggleDisplayToolStripMenuItem.Enabled = true;
        hwPorts.Enabled = false;
      }
      catch (System.Exception ex)
      {
        MessageBox.Show(ex.Message, "Error: Could not open serial port!", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
        serialPort = null;
      }
    }

    private void sendToDevice()
    {
      if (serialPort == null)
        return;

      try
      {
        Cursor.Current = Cursors.WaitCursor;
        using (MemoryStream memStream = new MemoryStream(4096))
        {
          // build the payload            
          BinaryWriter writer = new BinaryWriter(memStream);
          frStrip.Data().exportToBinary(writer);

          string asciiFrames = memStream.Length.ToString();
          System.Text.ASCIIEncoding encoding = new System.Text.ASCIIEncoding();
          byte[] frameCountAsBytes = encoding.GetBytes(asciiFrames);

          hwSendProgress.Maximum = (Int32)memStream.Length;
          hwSendProgress.Value = 0;

          serialPort.DiscardInBuffer();

          serialPort.BaseStream.WriteByte((Byte)'r');
          Thread.Sleep(100);
          serialPort.BaseStream.Write(frameCountAsBytes, 0, asciiFrames.Length);
          Thread.Sleep(100);
          serialPort.BaseStream.WriteByte((Byte)'\n');
          Thread.Sleep(100);

          byte[] dataBuf = memStream.GetBuffer();
          for (Int32 n = 0; n < memStream.Length; n++)
          {
            serialPort.Write(dataBuf, n, 1);
            hwSendProgress.Value++;
            Thread.Sleep(5);
          }

          Thread.Sleep(100);
          hwSendProgress.Value = 0;
        }
      }
      catch (Exception ex)
      {
        MessageBox.Show(ex.Message, "Hardware Send Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
      }
      finally
      {
        Cursor.Current = Cursors.Default;
      }
    }

    private void sendToDeviceToolStripMenuItem_Click(object sender, EventArgs e)
    {
      sendToDevice();
    }

    private void runCurrentToolInToolList()
    {
      CompiledTool ct = (toolList.SelectedItem as CompiledTool);
      if (ct == null)
        return;

      try
      {
        Cursor.Current = Cursors.WaitCursor;
        ct.ToolMain.Invoke(ct.Instance, new object[] { hwMatrixLarge.CurrentFrame, frStrip.Data() });
      }
      catch (System.Exception e)
      {
        MessageBox.Show(e.Message, "Error During Tool Execution", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
      }
      finally
      {
        GC.Collect();
        GC.WaitForPendingFinalizers();

        Cursor.Current = Cursors.Default;
      }
    }

    private void toolList_MouseDoubleClick(object sender, MouseEventArgs e)
    {
      runCurrentToolInToolList();
    }

    private void toolList_KeyUp(object sender, KeyEventArgs e)
    {
      if (e.KeyCode == Keys.Enter)
        runCurrentToolInToolList();
    }

    private void toolList_SelectedIndexChanged(object sender, EventArgs e)
    {
      CompiledTool ct = (toolList.SelectedItem as CompiledTool);
      if (ct == null)
        return;

      propertyGrid.SelectedObject = ct.Instance;
    }

    private void hwDemoBright_MouseClick(object sender, MouseEventArgs e)
    {
      demoMatrix.m_considerFrameBrightness = !demoMatrix.m_considerFrameBrightness;
      hwDemoBright.Checked = demoMatrix.m_considerFrameBrightness;
    }

    private void toggleDisplayToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (serialPort == null)
        return;

      serialPort.Write(new char[] { 'e' }, 0, 1);
      Thread.Sleep(15);
    }

    private void scriptEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      sv.Show();
    }

    private void exportToAVIToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (saveAVI.ShowDialog() == DialogResult.OK)
      {
        if (File.Exists(saveAVI.FileName))
          File.Delete(saveAVI.FileName);

        const Int32 outputSize = 200;

        ImageSequenceCompressor isc = CompressorFactory.getImageSequenceCompressor(
          CompressorFactory.eSeqCompressorType.eAVI);

        Bitmap sample = new Bitmap(outputSize, outputSize, PixelFormat.Format24bppRgb);
        isc.beginSequence(this, sample, saveAVI.FileName, (Int32)hwFPS.Value);
        sample.Dispose();

        for (int i = 0; i < frStrip.Data().NumFrames; i++)
        {
          Frame f = frStrip.Data().getFrameAtIndex(i);

          Bitmap frameBM = new Bitmap(outputSize, outputSize, PixelFormat.Format24bppRgb);
          Graphics Gr = Graphics.FromImage(frameBM);
          LEDMatrix.renderFrameToGraphics(f, Gr, false, 24);
          isc.addBitmap(frameBM);
          frameBM.Dispose();
        }

        isc.endSequence();
      }
    }

    private void clipboardcap_Click(object sender, EventArgs e)
    {
      Byte R, G;

      StringBuilder sb = new StringBuilder(1024);

      sb.AppendLine("const unsigned char glyph[16 * 16] __FLASH__ = { ");

      for (Int32 y = 0; y < Frame.EdgeLEDCount; y++)
      {
        
        for (Int32 x = 0; x < Frame.EdgeLEDCount; x++)
        {
          hwMatrixLarge.CurrentFrame.getLED(x, y, out R, out G);

          sb.Append(G);
          sb.Append(", ");
        }

        sb.Append(Environment.NewLine);
      }

      sb.AppendLine("};");

      Clipboard.SetText(sb.ToString());
    }

  }
}