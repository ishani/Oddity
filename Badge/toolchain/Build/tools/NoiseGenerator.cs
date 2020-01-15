

int pNumberOfFrames = 80;
bool pRedFirst = true;
bool pFullGradient = true;
Double pXScale = 0.2;
Double pYScale = 0.2;
Double pSpeed = 0.1;
Double pIntensify = 1.0;

public void main(Frame editingFrame, FrameStrip strip)
{
  Byte r, g;

  Double n = 0;
  Double loopInterval = (Double)pNumberOfFrames * pSpeed;

  for (int i=0; i<NumberOfFrames; i++)
  {
    Frame fr = new Frame();

    for (int y=0; y<Frame.EdgeLEDCount; y++)
    {
      for (int x=0; x<Frame.EdgeLEDCount; x++)
      {
        Double a = (Double)x * pXScale;
        Double b = (Double)y * pYScale;
        float f = FrameTools.LoopingPerlinNoise(a, b, n, loopInterval);
        
        f = (float)Math.Pow(f, pIntensify);
        
        FrameTools.ColourGradient(f, RedFirst, !FullGradient, out r, out g);
        
        fr.setLED(x, y, r, g);
      }
    }

    n += pSpeed;
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
public Double XScale
{
  get { return pXScale; }
  set { pXScale = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public Double YScale
{
  get { return pYScale; }
  set { pYScale = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public Double Speed
{
  get { return pSpeed; }
  set { pSpeed = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public Double Intensify
{
  get { return pIntensify; }
  set { pIntensify = value; }
}
