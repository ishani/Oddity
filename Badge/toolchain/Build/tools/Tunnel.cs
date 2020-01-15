

int pNumberOfFrames = 100;
bool pRedFirst = true;
bool pFullGradient = true;

float pAlphaRate  = 3.0f;
float pAlphaPhaseX = 0f;
float pAlphaPhaseY = 0f;
float pAlphaDistX = 0.0f;
float pAlphaDistY = 2.0f;

float pRepeat = 1.2f;
float pScale = 1.3f;
float pTunnelRate = 1.0f;


public void main(Frame editingFrame, FrameStrip strip)
{
  Byte r, g;
  
  float nK = ((float)Math.PI * 2.0f) / ((float)NumberOfFrames);
  float tK = (((float)Math.PI * 2.0f) * pTunnelRate) / ((float)NumberOfFrames);
  
  float vv = 0.0f;
  float n = 0;
  
  float rptScale = 1.0f / (pScale * 8.0f);
  
  for (int i=0; i<pNumberOfFrames; i++)
  {
    Frame fr = new Frame();
    
    float x1 = 3.5f + (float)(Math.Sin(n + pAlphaPhaseX) * pAlphaDistX);
    float y1 = 3.5f + (float)(Math.Sin(n + pAlphaPhaseY) * pAlphaDistY);
    
    for (int y=0; y<Frame.EdgeLEDCount; y++)
    {
      for (int x=0; x<Frame.EdgeLEDCount; x++)
      {
        float fX = (float)x;
        float fY = (float)y;
        
        float dX = (x1 - fX) * rptScale;
        float dY = (y1 - fY) * rptScale;
        
        float dT = (dX * dX) + (dY * dY);
        dT = (float)(Math.Abs(Math.Sin(vv + Math.Sqrt(dT) * (Math.PI * pRepeat))));
        
        FrameTools.ColourGradient(dT, RedFirst, !FullGradient, out r, out g);

        fr.setLED(x, y, r, g);
      }
    }
   
    strip.addFrame(fr, false);
    vv -= tK;   
    n += nK;
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

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float Repeat
{
  get { return pRepeat; }
  set { pRepeat = value; }
}


[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float Scale
{
  get { return pScale; }
  set { pScale = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float TunnelRate
{
  get { return pTunnelRate; }
  set { pTunnelRate = value; }
}
