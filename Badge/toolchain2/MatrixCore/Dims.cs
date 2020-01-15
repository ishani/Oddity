using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MatrixCore
{
  // dimensions of LED matrix
  public static class Dims
  {
    // the app can handle different dimensions, but only in square NxN configurations
    public const Int32 LEDs = 8;
    public const Int32 TotalLEDs = LEDs * LEDs;

    #region Dimension Tests
    public static void Clamp(ref Int32 x, ref Int32 y)
    {
      if (x >= LEDs) x = LEDs - 1;
      if (y >= LEDs) y = LEDs - 1;
      if (x < 0) x = 0;
      if (y < 0) y = 0;
    }

    public static void Wrap(ref Int32 x, ref Int32 y)
    {
      while (x < 0) x += LEDs;
      while (y < 0) y += LEDs;
      while (x >= LEDs) x -= LEDs;
      while (y >= LEDs) y -= LEDs;
    }

    public static bool Discardable(Int32 x, Int32 y)
    {
      if (x >= LEDs) return true;
      if (y >= LEDs) return true;
      if (x < 0) return true;
      if (y < 0) return true;
      return false;
    }
    #endregion
  }
}
