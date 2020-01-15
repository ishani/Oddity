using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace BadgeCore
{
  [Serializable]
  public class Frame
  {
    public const Int32 EdgeLEDCount = 8;
    public Byte[] m_ledStates = new Byte[EdgeLEDCount * EdgeLEDCount];
    public Byte m_brightness = 80;

    [NonSerialized]
    public bool DisableEvents = false;

    public Frame()
    {
    }

    #region CopyOps

    public Frame clone()
    {
      Frame o = new Frame();
      copyTo(o);

      return o;
    }

    public void copyTo(Frame f)
    {
      m_ledStates.CopyTo(f.m_ledStates, 0);
      f.m_brightness = m_brightness;
      f.callUpdateEvent();
    }

    public void copyFrom(Frame f)
    {
      f.m_ledStates.CopyTo(m_ledStates, 0);
      m_brightness = f.m_brightness;
      callUpdateEvent();
    }

    public void copyFromWithXOffset(Frame f, Int32 offset, bool wrap)
    {
      bool fOutDE = DisableEvents;
      DisableEvents = true;

      Byte R, G;
      for (Int32 y = 0; y < Frame.EdgeLEDCount; y++)
      {
        for (Int32 x = 0; x < Frame.EdgeLEDCount; x++)
        {
          f.getLED(x, y, out R, out G);

          Int32 tX = x + offset;

          if (wrap)
            setLEDWrap(tX, y, R, G);
          else
            setLEDDiscard(tX, y, R, G);
        }
      }

      m_brightness = f.m_brightness;
      DisableEvents = fOutDE;
      callUpdateEvent();
    }

    public void copyFromLEDArray(Byte[,] input, Int32 xStart, Int32 yStart)
    {
      for (Int32 y = 0; y < Frame.EdgeLEDCount; y++)
      {
        for (Int32 x = 0; x < Frame.EdgeLEDCount; x++)
        {
          Int32 arrayX = xStart + x;
          Int32 arrayY = yStart + y;

          if (arrayX < 0 ||
              arrayX > input.GetUpperBound(0) ||
              arrayY < 0 ||
              arrayY > input.GetUpperBound(1))
            continue;

          m_ledStates[(y * EdgeLEDCount) + x] = input[arrayX, arrayY];
        }
      }
      callUpdateEvent();
    }

    #endregion

    #region Export

    // LED order in memory [1 2 3 4 5 6 7 8 ]
    // LED order on export [5 6 7 8 1 2 3 4 ]
    // un-interleaved, G then R
    public void exportToBinary(BinaryWriter bw)
    {
      Byte ledR, ledG;
      Byte scanByte;

      bw.Write(m_brightness);

      // -------------------------------------------------
      // GREEN
      for (Int32 y = 0; y < EdgeLEDCount; y++)
      {
        scanByte = 0;

        getLED(4, y, out ledR, out ledG);
        scanByte |= (Byte)(ledG << 6);

        getLED(5, y, out ledR, out ledG);
        scanByte |= (Byte)(ledG << 4);

        getLED(6, y, out ledR, out ledG);
        scanByte |= (Byte)(ledG << 2);

        getLED(7, y, out ledR, out ledG);
        scanByte |= (Byte)(ledG << 0);

        bw.Write(scanByte);
      }
      for (Int32 y = 0; y < EdgeLEDCount; y++)
      {
        scanByte = 0;

        getLED(0, y, out ledR, out ledG);
        scanByte |= (Byte)(ledG << 6);

        getLED(1, y, out ledR, out ledG);
        scanByte |= (Byte)(ledG << 4);

        getLED(2, y, out ledR, out ledG);
        scanByte |= (Byte)(ledG << 2);

        getLED(3, y, out ledR, out ledG);
        scanByte |= (Byte)(ledG << 0);

        bw.Write(scanByte);
      }

      // -------------------------------------------------
      // RED
      for (Int32 y = 0; y < EdgeLEDCount; y++)
      {
        scanByte = 0;

        getLED(4, y, out ledR, out ledG);
        scanByte |= (Byte)(ledR << 6);

        getLED(5, y, out ledR, out ledG);
        scanByte |= (Byte)(ledR << 4);

        getLED(6, y, out ledR, out ledG);
        scanByte |= (Byte)(ledR << 2);

        getLED(7, y, out ledR, out ledG);
        scanByte |= (Byte)(ledR << 0);

        bw.Write(scanByte);
      }
      for (Int32 y = 0; y < EdgeLEDCount; y++)
      {
        scanByte = 0;

        getLED(0, y, out ledR, out ledG);
        scanByte |= (Byte)(ledR << 6);

        getLED(1, y, out ledR, out ledG);
        scanByte |= (Byte)(ledR << 4);

        getLED(2, y, out ledR, out ledG);
        scanByte |= (Byte)(ledR << 2);

        getLED(3, y, out ledR, out ledG);
        scanByte |= (Byte)(ledR << 0);

        bw.Write(scanByte);
      }
    }

    #endregion

    #region LEDAccess
    public void setLED(Int32 x, Int32 y, Byte red, Byte green)
    {
      if (x < 0 || x >= EdgeLEDCount || y < 0 || y >= EdgeLEDCount)
        throw new InvalidOperationException("Frame::setLED x/y out of bounds");

      if (red < 0)
        red = 0;
      if (green < 0)
        green = 0;
      if (red > 3)
        red = 3;
      if (green > 3)
        green = 3;

      m_ledStates[(y * EdgeLEDCount) + x] = (Byte)((red) | (green << 2));
      callUpdateEvent();
    }

    public void setLEDDiscard(Int32 x, Int32 y, Byte red, Byte green)
    {
      if (x > EdgeLEDCount - 1) return;
      if (y > EdgeLEDCount - 1) return;
      if (x < 0) return;
      if (y < 0) return;
      setLED(x, y, red, green);
    }

    public void setLEDWrap(Int32 x, Int32 y, Byte red, Byte green)
    {
      while (x < 0) x += EdgeLEDCount;
      while (x > EdgeLEDCount - 1) x -= EdgeLEDCount;
      while (y < 0) y += EdgeLEDCount;
      while (y > EdgeLEDCount - 1) y -= EdgeLEDCount;
      setLED(x, y, red, green);
    }

    public void getLED(Int32 x, Int32 y, out Byte red, out Byte green)
    {
      if (x < 0 || x >= EdgeLEDCount || y < 0 || y >= EdgeLEDCount)
        throw new InvalidOperationException("Frame::setLED x/y out of bounds");

      Byte led = m_ledStates[(y * EdgeLEDCount) + x];
      red = (Byte)(led & 3);
      green = (Byte)((led >> 2) & 3);
    }
    #endregion

    #region Events
    public event EventHandler<EventArgs> UpdateEvent;
    public void callUpdateEvent()
    {
      if (UpdateEvent != null && !DisableEvents)
      {
        EventArgs e = new EventArgs();
        UpdateEvent(this, e);
      }
    }
    #endregion

    #region Brightness
    public Byte Brightness
    {
      get { return m_brightness; }
      set 
      {
        m_brightness = value;
        callUpdateEvent();
      }
    }

    public float BrightnessAsFloat
    {
      get { return (float)Brightness / 255.0f; }
      set
      {
        float newV = value;
        if (newV < 0)
          newV = 0;
        if (newV > 1.0f)
          newV = 1.0f;

        Byte n = (Byte)(newV * 255.0f);
        Brightness = n;
      }
    }
    #endregion

    public void fade(bool fadeRed, bool fadeGreen)
    {
      Byte R, G;

      for (int y = 0; y < EdgeLEDCount; y++)
      {
        for (int x = 0; x < EdgeLEDCount; x++)
        {
          getLED(x, y, out R, out G);
          if (fadeRed && R > 0)
            R--;
          if (fadeGreen && G > 0)
            G--;

          m_ledStates[(y * EdgeLEDCount) + x] = (Byte)((R) | (G << 2));
        }
      }

      callUpdateEvent();
    }

    public void plotAntialiasedLED(float x, float y, float bias)
    {
      int x1 = (int)Math.Floor(x) - 1;
      int y1 = (int)Math.Floor(y) - 1;
      int x2 = (int)Math.Ceiling(x) + 1;
      int y2 = (int)Math.Ceiling(y) + 1;

      if (x2 > EdgeLEDCount) x2 = EdgeLEDCount;
      if (y2 > EdgeLEDCount) y2 = EdgeLEDCount;
      if (x1 < 0) x1 = 0;
      if (y1 < 0) y1 = 0;


      float d1;

      if (bias > 3.0f)
        bias = 3.0f;
      if (bias < 0.0f)
        bias = 0.0f;

      for (int _y = y1; _y < y2; _y++)
      {
        for (int _x = x1; _x < x2; _x++)
        {
          d1 = 3.0f - (FrameTools.DistanceBetween((float)_x, (float)_y, x, y) * (3.0f - bias));
          if (d1 > 0)
          {
            Byte r, g, n = (Byte)d1;
            getLED(_x, _y, out r, out g);
            setLEDDiscard(_x, _y, (Byte)(r + n), (Byte)(g + n));
          }
        }
      }
    }

    public Size getUsedPixelSpace()
    {
      Byte R, G;

      Int32 boundFarX = 0;
      for (Int32 y = 0; y < Frame.EdgeLEDCount; y++)
      {
        for (Int32 x = Frame.EdgeLEDCount - 1; x >= 0; x--)
        {
          getLED(x, y, out R, out G);

          if (R != 0 || G != 0)
          {
            if (x > boundFarX)
              boundFarX = x;

            break;
          }
        }
      }

      Int32 boundFarY = 0;
      for (Int32 x = 0; x < Frame.EdgeLEDCount; x++)
      {
        for (Int32 y = Frame.EdgeLEDCount - 1; y >= 0; y--)
        {
          getLED(x, y, out R, out G);

          if (R != 0 || G != 0)
          {
            if (y > boundFarY)
              boundFarY = y;

            break;
          }
        }
      }

      Size result = new Size(boundFarX + 1, boundFarY + 1);

      return result;
    }

  }
}
