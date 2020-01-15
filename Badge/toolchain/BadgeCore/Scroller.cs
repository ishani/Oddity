using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Reflection;
using System.IO;
using System.IO.Ports;
using System.Threading;
using System.Xml;
using System.Xml.Serialization;

namespace BadgeCore
{
  public class TextWizard
  {
    private List<Frame> mFontTemplate;
    private static String fontMap = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!?:.[]()-+\\/";

    public TextWizard(string fontFileName)
    {
      String rootPath = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);
      String fullFontPath = (rootPath + "\\" + fontFileName);

      Stream stream = null;
      try
      {
        stream = File.Open(fullFontPath, FileMode.Open);
        Type[] extraTypes = new Type[2] { typeof(Frame), typeof(List<Frame>) };
        XmlSerializer serializer = new XmlSerializer(typeof(FrameStripData), extraTypes);
        FrameStripData incomingData = (FrameStripData)serializer.Deserialize(stream);

        mFontTemplate = new List<Frame>(incomingData.m_frames);
      }
      catch (Exception e)
      {
        MessageBox.Show(e.Message, "Font Load Failed", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
      }
      finally
      {
        if (stream != null)
          stream.Close();
      }
    }

    public delegate void ColourFunc(Int32 x, Int32 y, Int32 globalX, Int32 letterIndex, out Byte r, out Byte g);

    public bool generateBurst(FrameStrip strip, String text, Int32 framesPerLetter, ColourFunc cfn)
    {
      String upperText = text.ToUpper();
      
      for (Int32 i = 0; i < upperText.Length; i++)
      {
        char cT = upperText[i];
        if (cT == ' ')
        {
          for (Int32 n = 0; n < framesPerLetter; n++)
          {
            strip.addFrame(new Frame(), false);
          }
          continue;
        }

        Int32 frameIndex = fontMap.IndexOf(cT);
        if (frameIndex == -1)
        {
          return false;
        }
        if (frameIndex > mFontTemplate.Count)
        {
          return false;
        }

        float bright = 0.9f;
        for (Int32 n = 0; n < framesPerLetter; n++)
        {
          Frame letter = mFontTemplate[frameIndex];
          Frame t = new Frame();

          bool fOutDE = t.DisableEvents;
          t.DisableEvents = true;

          t.copyFromWithXOffset(letter, 1, false);

          Byte R, G;
          for (Int32 y = 0; y < Frame.EdgeLEDCount; y++)
          {
            for (Int32 x = 0; x < Frame.EdgeLEDCount; x++)
            {
              t.getLED(x, y, out R, out G);

              if (R != 0)
              {
                cfn(x, y, x, i, out R, out G);
                t.setLED(x, y, R, G);
              }
            }
          }

          Int32 fadeSeq = (n - (framesPerLetter - 4));
          for (Int32 f = 0; f < fadeSeq; f++)
          {
            t.fade(true, true);

            Frame tF = new Frame();
            for (Int32 y = 0; y < Frame.EdgeLEDCount; y++)
            {
              for (Int32 x = 0; x < Frame.EdgeLEDCount; x++)
              {
                t.getLED(x, y, out R, out G);

                tF.setLEDDiscard(x, y - 1, R, G);
              }
            }
            t.copyFrom(tF);
          }

          t.DisableEvents = fOutDE;

          t.BrightnessAsFloat = bright;
          bright *= 0.7f;
          if (bright < 0.3f)
            bright = 0.3f;

          strip.addFrame(t, false);
        }
      }

      return true;
    }

    public bool generateScroller(FrameStrip strip, String text, Int32 yOffset, float scrollSpeed, ColourFunc cfn)
    {
      String upperText = text.ToUpper();

      Int32 textWidth = (Frame.EdgeLEDCount * upperText.Length);
      Int32 arraySpan = textWidth + (Frame.EdgeLEDCount * 2);
      {
        Byte[,] tArray = new Byte[arraySpan, Frame.EdgeLEDCount];
        Int32 arrayX = Frame.EdgeLEDCount;

        for (Int32 i = 0; i < upperText.Length; i++)
        {
          char cT = upperText[i];
          if (cT == ' ')
          {
            arrayX += 6;
            continue;
          }

          Int32 frameIndex = fontMap.IndexOf(cT);
          if (frameIndex == -1)
          {
            return false;
          }
          if (frameIndex > mFontTemplate.Count)
          {
            return false;
          }

          Frame letter = mFontTemplate[frameIndex];
          Size bounds = letter.getUsedPixelSpace();

          Byte R, G;
          for (Int32 y = 0; y < Frame.EdgeLEDCount; y++)
          {
            Int32 arrayXiter = arrayX;
            for (Int32 x = 0; x < Frame.EdgeLEDCount; x++, arrayXiter++)
            {
              letter.getLED(x, y, out R, out G);

              if (R != 0)
              {
                cfn(x, y, arrayXiter, i, out R, out G);
                tArray[arrayXiter, y] = (Byte)((R) | (G << 2));
              }
            }
          }
          arrayX += 1 + bounds.Width;
        }


        for (float q = 0.0f; q < (float)arrayX; q += scrollSpeed)
        {
          Frame t = new Frame();
          t.copyFromLEDArray(tArray, (Int32)q, -yOffset);
          strip.addFrame(t, false);
        }
      }

      return true;
    }
  }
}