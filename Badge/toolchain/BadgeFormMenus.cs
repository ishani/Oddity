using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.IO;
using BadgeUI;
using BadgeCore;

namespace Badge
{
    partial class BadgeForm
    {
        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (saveFileDialog.ShowDialog(this) == DialogResult.OK)
            {
              frStrip.Data().save(saveFileDialog.FileName);
            }
        }

        private void exportBINToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (exportFileDialog.ShowDialog(this) == DialogResult.OK)
            {
                Stream stream = null;
                try
                {
                    stream = File.Create(exportFileDialog.FileName);
                    BinaryWriter writer = new BinaryWriter(stream);

                    frStrip.Data().exportToBinary(writer);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message, "Export Failed", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
                finally
                {
                    if (stream != null)
                        stream.Close();
                }
            }
        }


        private void exportToCArrayToolStripMenuItem_Click(object sender, EventArgs e)
        {
          if (exportToHeader.ShowDialog(this) == DialogResult.OK)
          {
            try
            {
              using (MemoryStream memStream = new MemoryStream(4096))
              {
                byte[] bytes;
                long mstreamlen = 0;

                // build the payload
                using (BinaryWriter writer = new BinaryWriter(memStream))
                {
                  frStrip.Data().exportToBinary(writer);
                  bytes = memStream.GetBuffer();
                  mstreamlen = memStream.Length;
                }

                using (StreamWriter sw = new StreamWriter(exportToHeader.FileName))
                {
                  sw.Write("const unsigned char[");
                  sw.Write(mstreamlen.ToString());
                  sw.Write("] = {\n");

                  for (long n = 0; n < mstreamlen; n++)
                  {
                    byte b = bytes[n];
                    sw.Write("{0}, ", b.ToString());

                    if (n != 0 && (n % 20) == 0)
                      sw.Write("\n");
                  }


                  sw.WriteLine("};");
                }
              }
            }
            catch (Exception ex)
            {
              MessageBox.Show(ex.Message, "Export Failed", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
          }

        }

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog.ShowDialog(this) == DialogResult.OK)
            {
                stopAnimDemo();
                frStrip.Data().load(openFileDialog.FileName, FrameStrip.LoadMode.Replace);
            }
        }

        private void appendToolStripMenuItem_Click(object sender, EventArgs e)
        {
          if (openFileDialog.ShowDialog(this) == DialogResult.OK)
          {
            stopAnimDemo();
            frStrip.Data().load(openFileDialog.FileName, FrameStrip.LoadMode.Append);
          }
        }

        private void overlayToolStripMenuItem_Click(object sender, EventArgs e)
        {
          if (openFileDialog.ShowDialog(this) == DialogResult.OK)
          {
            stopAnimDemo();
            frStrip.Data().load(openFileDialog.FileName, FrameStrip.LoadMode.Overlay);
          }
        }

        private void overlayAdditiveToolStripMenuItem_Click(object sender, EventArgs e)
        {
          if (openFileDialog.ShowDialog(this) == DialogResult.OK)
          {
            stopAnimDemo();
            frStrip.Data().load(openFileDialog.FileName, FrameStrip.LoadMode.OverlayAdditive);
          }
        }

        private void overlayPunchoutToolStripMenuItem_Click(object sender, EventArgs e)
        {
          if (openFileDialog.ShowDialog(this) == DialogResult.OK)
          {
            stopAnimDemo();
            frStrip.Data().load(openFileDialog.FileName, FrameStrip.LoadMode.OverlayCutoutFG);
          }
        }

        private void overlayCutOutBackgroundToolStripMenuItem_Click(object sender, EventArgs e)
        {
          if (openFileDialog.ShowDialog(this) == DialogResult.OK)
          {
            stopAnimDemo();
            frStrip.Data().load(openFileDialog.FileName, FrameStrip.LoadMode.OverlayCutoutBG);
          }
        }
    }
}