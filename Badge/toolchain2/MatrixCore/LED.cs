using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace MatrixCore
{
  [Serializable]
  public struct LED
  {
    public LED(Int32 iR, Int32 iG)
    {
      _R = Clamp4Bit(iR);
      _G = Clamp4Bit(iG);
    }

    public LED(LED rhs)
    {
      _R = rhs._R;
      _G = rhs._G;
    }

    public bool isLit()
    {
      return (_R != 0 || _G != 0);
    }

    #region Operators
    // fade both R & G
    public static LED operator --(LED rhs)
    {
      LED nL = new LED(rhs.R, rhs.G);
      nL.decR();
      nL.decG();
      return nL;
    }

    // brighten both R & G
    public static LED operator ++(LED rhs)
    {
      LED nL = new LED(rhs.R, rhs.G);
      nL.incR();
      nL.incG();
      return nL;
    }

    public static LED operator +(LED lhs, LED rhs)
    {
      LED nL = new LED();
      nL.setRClamped(lhs.R + rhs.R);
      nL.setGClamped(lhs.G + rhs.G);
      return nL;
    }

    public static LED operator -(LED lhs, LED rhs)
    {
      LED nL = new LED();
      nL.setRClamped(lhs.R - rhs.R);
      nL.setGClamped(lhs.G - rhs.G);
      return nL;
    }
    #endregion

    #region Inc/Dec
    public void incR()
    {
      if (_R < 3)
        _R++;
    }
    public void incG()
    {
      if (_G < 3)
        _G++;
    }
    public void decR()
    {
      if (_R > 0)
        _R--;
    }
    public void decG()
    {
      if (_G > 0)
        _G--;
    }
    #endregion

    #region Accessors

    // ..Clamped() will clamp the inputs and set the LED, 
    // so if you pass '10', it will be set to '3'
    void setRClamped(Int32 iR)
    {
      _R = Clamp4Bit(iR);
    }
    void setGClamped(Int32 iG)
    {
      _G = Clamp4Bit(iG);
    }

    // default accessors will discard any invalid inputs
    public Byte R
    {
      get { return _R; }
      set
      {
        if (value >= 0 && value < 4)
          _R = value;
      }
    }
    public Byte G
    {
      get { return _G; }
      set
      {
        if (value >= 0 && value < 4)
          _G = value;
      }
    }
    #endregion

    #region Tools
    public static Byte Clamp4Bit(Int32 v)
    {
      if (v <= 0)
        return 0;
      else if (v >= 3)
        return 3;
      else
        return (Byte)v;
    }

    public void Gradient(float t, Tools.GradientColouring gColouring, Tools.GradientStyle gStyle)
    {
      Tools.Gradient(t, gColouring, gStyle, ref this);
    }
    #endregion

    private Byte _R;
    private Byte _G;
  }
}
