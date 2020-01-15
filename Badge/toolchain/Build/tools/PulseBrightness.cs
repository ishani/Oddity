
float pPulses = 2.0f;

public void main(Frame editingFrame, FrameStrip strip)
{
  float nK = ((float)Math.PI * (pPulses * 2.0f)) / ((float)strip.NumFrames);
  float n = 0;
	
	for (int f=0; f<strip.NumFrames; f++)
  {
    Frame q = strip.getFrameAtIndex(f);
    q.BrightnessAsFloat = 0.5f + (float)(Math.Sin( f * nK ) * 0.5);
  }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float Pulses
{
  get { return pPulses; }
  set { pPulses = value; }
}

