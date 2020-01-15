
float pIntensity = 1.5f;
float pBaseBrightness = -0.2f;
float pSeed = 2.0f;
float pPulses = 8.0f;

public void main(Frame editingFrame, FrameStrip strip)
{
  float nK = ((float)Math.PI * (pPulses * 2.0f)) / ((float)strip.NumFrames);
  float n = 0;
	
	for (int f=0; f<strip.NumFrames; f++)
  {
    Frame q = strip.getFrameAtIndex(f);
    
    float Nf = FrameTools.LoopingPerlinNoise(pSeed, 0.6, n, ((Double)strip.NumFrames) );
    n += nK;
    
    q.BrightnessAsFloat = pBaseBrightness + (Nf * pIntensity);
  }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float Pulses
{
  get { return pPulses; }
  set { pPulses = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float Seed
{
  get { return pSeed; }
  set { pSeed = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float Intensity
{
  get { return pIntensity; }
  set { pIntensity = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float BaseBrightness
{
  get { return pBaseBrightness; }
  set { pBaseBrightness = value; }
}


