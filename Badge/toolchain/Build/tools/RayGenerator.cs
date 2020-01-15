

int pNumberOfFrames = 60;
bool pRedFirst = true;
bool pFullGradient = false;

float pAlphaPhaseX = 1.0f;
float pAlphaPhaseY = 0f;
float pAlphaDistX = 3.5f;
float pAlphaDistY = 1.5f;

public void main(Frame editingFrame, FrameStrip strip)
{
  Byte r, g;
	
  float nK = ((float)Math.PI * 2.0f) / ((float)pNumberOfFrames);
  float n = 0;
	
  for (int i=0; i<pNumberOfFrames; i++)
  {
    Frame f = new Frame();

    float x1 = 3.5f + (float)(Math.Sin(n + pAlphaPhaseX) * pAlphaDistX);
    float y1 = 3.5f + (float)(Math.Cos(n + pAlphaPhaseY) * pAlphaDistY);
		
    for (int x=0; x<Frame.EdgeLEDCount; x++)
    {
      for (int y=0; y<Frame.EdgeLEDCount; y++)
      {
        float b = (float)Math.Atan2(x1 - (float)x, y1 - (float)y);
        
        b = (float)Math.Sin(n + b);
        b = 1.0f - (float)Math.Abs(b);
        
        FrameTools.ColourGradient(b, pRedFirst, pFullGradient, out r, out g);
        f.setLED(x, y, r, g);
      }
    }

    n += nK;
    
    strip.addFrame(f, false);
  }
}


[CategoryAttribute("Options"), DescriptionAttribute("")] 
public int NumberOfFrames
{
  get { return pNumberOfFrames; }
  set { pNumberOfFrames = value; }
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