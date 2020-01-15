using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Windows.Forms;

namespace MatrixCore
{
  public class LEDColouring
  {
    private SolidBrush[,] m_ledBrushes = new SolidBrush[4, 4];

    public LEDColouring()
    {
      // build brush colour LUT
      for (Int32 r = 0; r < 4; r++)
      {
        for (Int32 g = 0; g < 4; g++)
        {
          Int32 led_red = 30 + r * 70;
          Int32 led_green = 30 + g * 70;

          m_ledBrushes[r,g] = new SolidBrush( Color.FromArgb(led_red, led_green, 40) );
        }
      }
    }

    public SolidBrush BrushForLED(ref LED led)
    {
      return m_ledBrushes[led.R, led.G];
    }
  }
}
