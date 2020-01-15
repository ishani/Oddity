float t = 0.0f;

float pPerFrameFreq = 0.3f;
float pAmplitude = 3.0f;
float pXFreq = 0.1f;
bool pWrap = false;

public void main(Frame editingFrame, FrameStrip strip)
{
  for (int i=0; i<strip.NumFrames; i++)
  {
    Frame f = strip.getFrameAtIndex(i);
    t += pPerFrameFreq;

    Frame nF = new Frame();

    for (int x=0; x<Frame.EdgeLEDCount; x++)
    {
      float sn = (float)Math.Sin( (t + ((float)x * pXFreq)) ) * pAmplitude;

      FrameTools.VerticalShift(f, nF, x, (Int32)sn, Wrap);
    }

    nF.copyTo(f);
  }
}


[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float PerFrameFrequency
{
  get { return pPerFrameFreq; }
  set { pPerFrameFreq = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float Amplitude
{
  get { return pAmplitude; }
  set { pAmplitude = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float FrequencyInX
{
  get { return pXFreq; }
  set { pXFreq = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public bool Wrap
{
  get { return pWrap; }
  set { pWrap = value; }
}
