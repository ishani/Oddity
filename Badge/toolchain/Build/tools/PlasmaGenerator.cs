

int pNumberOfFrames = 60;
bool pRedFirst = true;
bool pFullGradient = false;

public enum ColouringModeEnum
{
  Polar,
  Min,
  Max,
  Blended
};
ColouringModeEnum    pColouringMode = ColouringModeEnum.Max;

float pRampMultiplier = 1.0f;

float pAlphaRate  = 6.0f;
float pAlphaPhaseX = 0f;
float pAlphaPhaseY = 0f;
float pAlphaDistX = 2.0f;
float pAlphaDistY = 7.0f;

float pBetaRate  = 3.0f;
float pBetaPhaseX = -2.0f;
float pBetaPhaseY = 1.5f;
float pBetaDistX = 5.0f;
float pBetaDistY = 4.0f;


public void main(Frame editingFrame, FrameStrip strip)
{
  Byte r, g;
  Byte []intense = new Byte[6]{1, 2, 3, 3, 2, 1};

  float nK = ((float)Math.PI * 2.0f) / ((float)NumberOfFrames);
  float n = 0;

  for (int i=0; i<NumberOfFrames; i++)
  {
    Frame fr = new Frame();

    float x1 = 3.5f + (float)(Math.Sin(n + pAlphaPhaseX) * pAlphaDistX);
    float y1 = 3.5f + (float)(Math.Sin(n + pAlphaPhaseY) * pAlphaDistY);

    float x2 = 3.5f + (float)(Math.Sin(n + pBetaPhaseX) * pBetaDistX);
    float y2 = 3.5f + (float)(Math.Sin(n + pBetaPhaseY) * pBetaDistY);

    for (int y=0; y<Frame.EdgeLEDCount; y++)
    {
      for (int x=0; x<Frame.EdgeLEDCount; x++)
      {
        float f1 = FrameTools.DistanceBetween(x, y, x1, y1);
        float f2 = FrameTools.DistanceBetween(x, y, x2, y2);

        if (ColouringMode == ColouringModeEnum.Polar)
        {
          float combo = (float)(Math.Atan2(f1, f2));
          combo += (float)Math.Sin(n * -RampMultiplier) * 0.5f;

          FrameTools.ColourGradient(combo, RedFirst, !FullGradient, out r, out g);
        }
        else if (ColouringMode == ColouringModeEnum.Min)
        {
          float c1 = 0.5f + ((float)Math.Sin(f1 + (n * -pAlphaRate)) * 0.5f);
          float c2 = 0.5f + ((float)Math.Cos(f2 + (n * -pBetaRate)) * 0.5f);
          float combo = (float)Math.Min(c1, c2) * 1.05f;
          FrameTools.ColourGradient(combo * RampMultiplier, RedFirst, !FullGradient, out r, out g);
        }
        else if (ColouringMode == ColouringModeEnum.Max)
        {
          float c1 = 0.5f + ((float)Math.Sin(f1 + (n * -pAlphaRate)) * 0.5f);
          float c2 = 0.5f + ((float)Math.Cos(f2 + (n * -pBetaRate)) * 0.5f);
          float combo = (float)Math.Max(c1, c2) * 1.05f;
          FrameTools.ColourGradient(combo * RampMultiplier, RedFirst, !FullGradient, out r, out g);
        }
        else if (ColouringMode == ColouringModeEnum.Blended)
        {
          int ind = Math.Abs((int)(f1 + (n * -pAlphaRate)));
          ind %= 6;

          int indB = Math.Abs((int)(f2 + (n * -pBetaRate)));
          indB %= 6;

          r = (Byte)(intense[ind]);
          g = (Byte)(intense[indB]);
        }
        else
        {
          r = g = 0;
        }

        fr.setLED(x, y, r, g);
      }
    }

    n += nK;
    strip.addFrame(fr, false);
  }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public int NumberOfFrames
{
  get { return pNumberOfFrames; }
  set { pNumberOfFrames = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public ColouringModeEnum ColouringMode
{
  get { return pColouringMode; }
  set { pColouringMode = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public bool RedFirst
{
  get { return pRedFirst; }
  set { pRedFirst = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public bool FullGradient
{
  get { return pFullGradient; }
  set { pFullGradient = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float RampMultiplier
{
  get { return pRampMultiplier; }
  set { pRampMultiplier = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float AlphaRate
{
  get { return pAlphaRate; }
  set { pAlphaRate = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float AlphaPhaseX
{
  get { return pAlphaPhaseX; }
  set { pAlphaPhaseX = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float AlphaPhaseY
{
  get { return pAlphaPhaseY; }
  set { pAlphaPhaseY = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float AlphaDistX
{
  get { return pAlphaDistX; }
  set { pAlphaDistX = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float AlphaDistY
{
  get { return pAlphaDistY; }
  set { pAlphaDistY = value; }
}

// --- 

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float BetaRate
{
  get { return pBetaRate; }
  set { pBetaRate = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float BetaPhaseX
{
  get { return pBetaPhaseX; }
  set { pBetaPhaseX = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float BetaPhaseY
{
  get { return pBetaPhaseY; }
  set { pBetaPhaseY = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float BetaDistX
{
  get { return pBetaDistX; }
  set { pBetaDistX = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float BetaDistY
{
  get { return pBetaDistY; }
  set { pBetaDistY = value; }
}