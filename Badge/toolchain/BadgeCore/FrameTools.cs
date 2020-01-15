using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace BadgeCore
{
  public class FrameTools
  {
    static public void ColourGradient(float t, bool redFirst, bool halfGradient, out Byte r, out Byte g)
    {
      Byte[] A = new Byte[11] { 1, 2, 3, 3, 3, 3, 2, 1, 0, 0, 0 };
      Byte[] B = new Byte[11] { 0, 0, 0, 1, 2, 3, 3, 3, 3, 2, 1};

      if (t < 0.0f) t = 0.0f;
      if (t > 1.0f) t = 1.0f;

      int index = (int)(t * (halfGradient?5.0f:10.0f));

      if (redFirst)
      {
        r = A[index];
        g = B[index];
      }
      else
      {
        r = B[index];
        g = A[index];
      }
    }

    static public float DistanceBetween(float x, float y, float cX, float cY)
    {
      double dX = (double)(x - cX);
      double dY = (double)(y - cY);
      double distance = Math.Sqrt((dX * dX) + (dY * dY));

      return (float)distance;
    }

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
      return (float)( ((t - z) * ((Double)PerlinNoise(x, y, z)) + (z) * ((Double)PerlinNoise(x, y, z - t))) / (t) );
    }

    public static void Overlay(Frame fBackground, Frame fForeground, Frame fOut, bool additive)
    {
      Byte ledR, ledG;
      Byte fR, fG;

      bool fOutDE = fOut.DisableEvents;
      fOut.DisableEvents = true;

      for (Int32 y = 0; y < Frame.EdgeLEDCount; y++)
      {
        for (Int32 x = 0; x < Frame.EdgeLEDCount; x++)
        {
          fBackground.getLED(x, y, out ledR, out ledG);
          fForeground.getLED(x, y, out fR, out fG);

          if (fR != 0 || fG != 0)
          {
            if (additive)
            {
              ledR += fR;
              if (ledR > 3)
                ledR = 3;

              ledG += fG;
              if (ledG > 3)
                ledG = 3;

              fOut.setLED(x, y, ledR, ledG);
            }
            else
            {
              fOut.setLED(x, y, fR, fG);
            }
          }
          else
          {
            fOut.setLED(x, y, ledR, ledG);
          }
        }
      }

      fOut.DisableEvents = fOutDE;
      fOut.callUpdateEvent();
    }

    public static void OverlayCutout(Frame fBackground, Frame fForeground, Frame fOut, bool cutoutForeground)
    {
      Byte ledR, ledG;
      Byte fR, fG;

      bool fOutDE = fOut.DisableEvents;
      fOut.DisableEvents = true;

      for (Int32 y = 0; y < Frame.EdgeLEDCount; y++)
      {
        for (Int32 x = 0; x < Frame.EdgeLEDCount; x++)
        {
          fBackground.getLED(x, y, out ledR, out ledG);
          fForeground.getLED(x, y, out fR, out fG);

          // only write BG if FG pixel is blank
          if (fR == 0 && fG == 0)
          {
            if (cutoutForeground)
              fOut.setLED(x, y, ledR, ledG);
            else
              fOut.setLED(x, y, 0, 0);
          }
          else
          {
            if (cutoutForeground)
              fOut.setLED(x, y, 0, 0);
            else
              fOut.setLED(x, y, ledR, ledG);
          }
        }
      }

      fOut.DisableEvents = fOutDE;
      fOut.callUpdateEvent();
    }

    public static void ColourSwap(Frame fIn, Frame fOut)
    {
      Byte ledR, ledG;

      bool fOutDE = fOut.DisableEvents;
      fOut.DisableEvents = true;

      for (Int32 y = 0; y < Frame.EdgeLEDCount; y++)
      {
        for (Int32 x = 0; x < Frame.EdgeLEDCount; x++)
        {
          fIn.getLED(x, y, out ledR, out ledG);
          fOut.setLED(x, y, ledG, ledR);
        }
      }

      fOut.DisableEvents = fOutDE;
      fOut.callUpdateEvent();
    }

    public static void HorizontalShift(Frame fIn, Frame fOut, Int32 column, Int32 shift, bool wrap)
    {
      bool fOutDE = fOut.DisableEvents;
      fOut.DisableEvents = true;

      for (Int32 x = 0; x < Frame.EdgeLEDCount; x++)
      {
        Byte ledR, ledG;
        fIn.getLED(x, column, out ledR, out ledG);

        Int32 tX = x + shift;

        if (wrap)
          fOut.setLEDWrap(tX, column, ledR, ledG);
        else
          fOut.setLEDDiscard(tX, column, ledR, ledG);
      }

      fOut.DisableEvents = fOutDE;
      fOut.callUpdateEvent();
    }


    public static void VerticalShift(Frame fIn, Frame fOut, Int32 row, Int32 shift, bool wrap)
    {
      bool fOutDE = fOut.DisableEvents;
      fOut.DisableEvents = true;

      for (Int32 y = 0; y < Frame.EdgeLEDCount; y++)
      {
        Byte ledR, ledG;
        fIn.getLED(row, y, out ledR, out ledG);

        Int32 tY = y + shift;

        if (wrap)
          fOut.setLEDWrap(row, tY, ledR, ledG);
        else
          fOut.setLEDDiscard(row, tY, ledR, ledG);
      }

      fOut.DisableEvents = fOutDE;
      fOut.callUpdateEvent();
    }

    public static void Blur(Frame fIn, Frame fOut)
    {
      bool fOutDE = fOut.DisableEvents;
      fOut.DisableEvents = true;

      for (Int32 y = 0; y < Frame.EdgeLEDCount; y++)
      {
        for (Int32 x = 0; x < Frame.EdgeLEDCount; x++)
        {
          Byte count = 1;
          Byte finalR, finalG;
          Byte ledR, ledG;

          fIn.getLED(x, y, out finalR, out finalG);

          if (x > 0)
          {
            fIn.getLED(x - 1, y, out ledR, out ledG);
            finalR += ledR;
            finalG += ledG;
            count++;
          }

          if (y > 0)
          {
            fIn.getLED(x, y - 1, out ledR, out ledG);
            finalR += ledR;
            finalG += ledG;
            count++;
          }

          if (x <= Frame.EdgeLEDCount - 2)
          {
            fIn.getLED(x + 1, y, out ledR, out ledG);
            finalR += ledR;
            finalG += ledG;
            count++;
          }

          if (y <= Frame.EdgeLEDCount - 2)
          {
            fIn.getLED(x, y + 1, out ledR, out ledG);
            finalR += ledR;
            finalG += ledG;
            count++;
          }

          Byte ffR = (Byte)((float)finalR / (float)count);
          Byte ffG = (Byte)((float)finalG / (float)count);

          fOut.setLED(x, y, ffR, ffG);
        }
      }

      fOut.DisableEvents = fOutDE;
      fOut.callUpdateEvent();
    }
  }
}