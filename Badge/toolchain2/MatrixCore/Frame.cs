using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Drawing;

namespace MatrixCore
{
  public delegate void IterateFrameDataDelegate(Int32 x, Int32 y, LED led);

  public class Frame
  {
    private FrameData   m_frameData;
    private Byte        m_brightness;

    public Frame()
    {
      m_frameData   = new FrameData();
      m_brightness  = 100;
    }

    public Frame(Frame rhs)
    {
      m_frameData = rhs.CloneData();
      m_brightness = rhs.m_brightness;
    }

    #region Data Access
    // call Lock to acquire the Frame's data for modification
    public void Lock(out FrameData fd)
    {
      fd = CloneData();
    }

    // call Unlock with your changes to update the frame
    public void Unlock(ref FrameData fd)
    {
      m_frameData = fd;
      fd = null;        // causes fd to be nulled, avoiding accidental access to unlocked data

      callFrameChangedEvent();
      GC.Collect();
    }

    // like Unlock, but ignoring changes
    public void Discard(ref FrameData fd)
    {
      fd = null;        // causes fd to be nulled, avoiding accidental access to unlocked data
    }

    public void ReplaceData(FrameData fd)
    {
      m_frameData = fd;
      callFrameChangedEvent();
      GC.Collect();
    }

    public FrameData CloneData()
    {
      return new FrameData(m_frameData);
    }

    public void Iterate(IterateFrameDataDelegate mm)
    {
      for (Int32 y = 0; y < Dims.LEDs; y++)
      {
        for (Int32 x = 0; x < Dims.LEDs; x++)
        {
          mm(x, y, m_frameData.Data[x, y]);
        }
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
        callFrameChangedEvent();
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

    #region Events
    public event EventHandler<EventArgs> FrameChangedEvent;
    public void callFrameChangedEvent()
    {
      if (FrameChangedEvent != null)
      {
        EventArgs e = new EventArgs();
        FrameChangedEvent(this, e);
      }
    }
    #endregion

    #region Export
    // LED order in memory [1 2 3 4 5 6 7 8 ]
    // LED order on export [5 6 7 8 1 2 3 4 ]
    // un-interleaved, G then R
    public void exportToBinary(BinaryWriter bw)
    {
      Byte scanByte = 0;

      bw.Write(m_brightness);

      // -------------------------------------------------
      // GREEN
      for (Int32 y = 0; y < Dims.LEDs; y++)
      {     
        scanByte  = (Byte)(m_frameData.Data[4, y].G << 6);
        scanByte |= (Byte)(m_frameData.Data[5, y].G << 4);
        scanByte |= (Byte)(m_frameData.Data[6, y].G << 2);
        scanByte |= (Byte)(m_frameData.Data[7, y].G << 0);
        bw.Write(scanByte);
      }
      for (Int32 y = 0; y < Dims.LEDs; y++)
      {
        scanByte  = (Byte)(m_frameData.Data[0, y].G << 6);
        scanByte |= (Byte)(m_frameData.Data[1, y].G << 4);
        scanByte |= (Byte)(m_frameData.Data[2, y].G << 2);
        scanByte |= (Byte)(m_frameData.Data[3, y].G << 0);
        bw.Write(scanByte);
      }

      // -------------------------------------------------
      // RED
      for (Int32 y = 0; y < Dims.LEDs; y++)
      {
        scanByte  = (Byte)(m_frameData.Data[4, y].R << 6);
        scanByte |= (Byte)(m_frameData.Data[5, y].R << 4);
        scanByte |= (Byte)(m_frameData.Data[6, y].R << 2);
        scanByte |= (Byte)(m_frameData.Data[7, y].R << 0);
        bw.Write(scanByte);
      }
      for (Int32 y = 0; y < Dims.LEDs; y++)
      {
        scanByte  = (Byte)(m_frameData.Data[0, y].R << 6);
        scanByte |= (Byte)(m_frameData.Data[1, y].R << 4);
        scanByte |= (Byte)(m_frameData.Data[2, y].R << 2);
        scanByte |= (Byte)(m_frameData.Data[3, y].R << 0);
        bw.Write(scanByte);
      }
    }
    #endregion
  }

  #region Tools
  public static class Tools
  {
    public enum GradientStyle
    {
      Half,
      Full,
    };

    public enum GradientColouring
    {
      RedFirst,
      RedOnly,
      GreenFirst,
      GreenOnly
    };

    static public void Gradient(float t, GradientColouring gColouring, GradientStyle gStyle, ref LED result)
    {
      Byte[] A = new Byte[11] { 1, 2, 3, 3, 3, 3, 2, 1, 0, 0, 0 };
      Byte[] B = new Byte[11] { 0, 0, 0, 1, 2, 3, 3, 3, 3, 2, 1 };

      if (t < 0.0f) t = 0.0f;
      if (t > 1.0f) t = 1.0f;

      int index = (int)(t * ((gStyle == GradientStyle.Half) ? 5.0f : 10.0f));

      if (gColouring == GradientColouring.RedFirst ||
          gColouring == GradientColouring.RedOnly)
      {
        result.R = A[index];

        if (gColouring == GradientColouring.RedOnly)
          result.G = 0;
        else
          result.G = B[index];
      }
      else
      {
        result.G = A[index];

        if (gColouring == GradientColouring.GreenOnly)
          result.R = 0;
        else
          result.R = B[index];
      }
    }

    static public float DistanceBetween(float x, float y, float cX, float cY)
    {
      double dX = (double)(x - cX);
      double dY = (double)(y - cY);
      double distance = Math.Sqrt((dX * dX) + (dY * dY));

      return (float)distance;
    }

    #region Perlin Noise
    static Double fade(Double t) { return t * t * t * (t * (t * 6 - 15) + 10); }
    static Double lerp(Double t, Double a, Double b) { return a + t * (b - a); }
    static Double grad(Int32 hash, Double x, Double y, Double z)
    {
      Int32 h = hash & 15;
      Double u = h < 8 ? x : y,
             v = h < 4 ? y : h == 12 || h == 14 ? x : z;
      return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }

    static Int32[] p = { 151,160,137,91,90,15,
       131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
       190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
       88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
       77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
       102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
       135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
       5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
       223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
       129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
       251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
       49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
       138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
       151,160,137,91,90,15,
       131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
       190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
       88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
       77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
       102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
       135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
       5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
       223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
       129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
       251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
       49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
       138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180};

    static public float PerlinNoise(Double x, Double y, Double z)
    {
      Int32 X = (Int32)Math.Floor(x) & 255,
            Y = (Int32)Math.Floor(y) & 255,
            Z = (Int32)Math.Floor(z) & 255;
      x -= Math.Floor(x);
      y -= Math.Floor(y);
      z -= Math.Floor(z);
      Double u = fade(x),
             v = fade(y),
             w = fade(z);
      Int32 A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z,
            B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

      float k = (float)lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z),
                                     grad(p[BA], x - 1, y, z)),
                             lerp(u, grad(p[AB], x, y - 1, z),
                                     grad(p[BB], x - 1, y - 1, z))),
                     lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1),
                                     grad(p[BA + 1], x - 1, y, z - 1)),
                             lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
                                     grad(p[BB + 1], x - 1, y - 1, z - 1))));

      return 0.5f + (k * 0.5f);
    }

    static public float LoopingPerlinNoise(Double x, Double y, Double z, Double loopInterval)
    {
      Double t = loopInterval;
      return (float)(((t - z) * ((Double)PerlinNoise(x, y, z)) + (z) * ((Double)PerlinNoise(x, y, z - t))) / (t));
    }
    #endregion
  }
  #endregion

}
