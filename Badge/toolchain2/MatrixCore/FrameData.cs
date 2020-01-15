using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace MatrixCore
{
  public delegate void ModifyFrameDataDelegate(Int32 x, Int32 y, ref LED led);

  [Serializable]
  public class FrameData
  {
    public LED[,] Data = new LED[Dims.LEDs, Dims.LEDs];

    public FrameData()
    {
    }

    public FrameData(FrameData rhs)
    {
      Data = (LED[,])rhs.Data.Clone();
    }

    public void CopyBlock(Point dest, Rectangle src, LED[,] srcData)
    {
      for (Int32 y = src.Top; y < src.Height; y++)
      {
        for (Int32 x = src.Left; x < src.Width; x++)
        {
          SetDiscardable(dest.X + x, dest.Y + y, srcData[x, y]);
        }
      }
    }

    public void Modify(ModifyFrameDataDelegate mm)
    {
      for (Int32 y = 0; y < Dims.LEDs; y++)
      {
        for (Int32 x = 0; x < Dims.LEDs; x++)
        {
          mm(x, y, ref Data[x, y]);
        }
      }
    }

    #region Checked Setters
    public void SetClamp(Int32 x, Int32 y, LED led)
    {
      Dims.Clamp(ref x, ref y);
      Data[x, y] = led;
    }

    public void SetWrap(Int32 x, Int32 y, LED led)
    {
      Dims.Wrap(ref x, ref y);
      Data[x, y] = led;
    }

    public void SetDiscardable(Int32 x, Int32 y, LED led)
    {
      if (Dims.Discardable(x, y))
        return;

      Data[x, y] = led;
    }
    #endregion

    #region Shifting

    public void ShiftColumn(Int32 x, Int32 amount, bool wrap)
    {
      // copy the column in question
      LED[] col = new LED[Dims.LEDs];
      for (Int32 y = 0; y < Dims.LEDs; y++)
      {
        col[y] = Data[x, y];
      }

      // apply the shift
      for (Int32 y = 0; y < Dims.LEDs; y++)
      {
        Int32 offsetY = y + amount;
        if (wrap)
          SetWrap(x, offsetY, col[y]);
        else
          SetDiscardable(x, offsetY, col[y]);
      }
    }

    public void ShiftRow(Int32 y, Int32 amount, bool wrap)
    {
      // copy the row in question
      LED[] row = new LED[Dims.LEDs];
      for (Int32 x = 0; x < Dims.LEDs; x++)
      {
        row[x] = Data[x, y];
      }

      // apply the shift
      for (Int32 x = 0; x < Dims.LEDs; x++)
      {
        Int32 offsetX = x + amount;
        if (wrap)
          SetWrap(offsetX, y, row[x]);
        else
          SetDiscardable(offsetX, y, row[x]);
      }
    }

    public void ShiftVertical(Int32 amount, bool wrap)
    {
      for (Int32 x = 0; x < Dims.LEDs; x++)
      {
        ShiftColumn(x, amount, wrap);
      }
    }

    public void ShiftHorizontal(Int32 amount, bool wrap)
    {
      for (Int32 y = 0; y < Dims.LEDs; y++)
      {
        ShiftRow(y, amount, wrap);
      }
    }

    #endregion

    #region Colour Manipulation
    public void SwapRG()
    {
      Modify((Int32 x, Int32 y, ref LED led) =>
      {
        Byte t = led.R;
        led.R = led.G;
        led.G = t;
      }
      );
    }

    public void Fade(bool fadeRed = true, bool fadeGreen = true)
    {
      Modify((Int32 x, Int32 y, ref LED led) =>
      {
        if (fadeRed) led.decR();
        if (fadeGreen) led.decG();
      }
      );
    }

    // brighten any lit LEDs, ignoring any black/unlit ones
    public void Intensify(bool brRed = true, bool brGreen = true)
    {
      Modify((Int32 x, Int32 y, ref LED led) =>
      {
        if (brRed && led.R != 0) led.incR();
        if (brGreen && led.G != 0) led.incG();
      }
      );
    }

    // brighten all LEDs, regardless of current lit/unlit state
    public void Brighten(bool brRed = true, bool brGreen = true)
    {
      Modify((Int32 x, Int32 y, ref LED led) =>
      {
        if (brRed) led.incR();
        if (brGreen) led.incG();
      }
      );
    }

    public void Clear(Byte clearRed = 0, Byte clearGreen = 0)
    {
      Modify((Int32 x, Int32 y, ref LED led) =>
      {
        led.R = clearRed;
        led.G = clearGreen;
      }
      );
    }
    #endregion

    #region Tools
    public Size GetLitLEDBounds()
    {
      Int32 boundFarX = 0;
      for (Int32 y = 0; y < Dims.LEDs; y++)
      {
        for (Int32 x = Dims.LEDs - 1; x >= 0; x--)
        {
          if (Data[x, y].isLit())
          {
            if (x > boundFarX)
              boundFarX = x;

            break;
          }
        }
      }

      Int32 boundFarY = 0;
      for (Int32 x = 0; x < Dims.LEDs; x++)
      {
        for (Int32 y = Dims.LEDs - 1; y >= 0; y--)
        {
          if (Data[x, y].isLit())
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
    #endregion

  }

}
