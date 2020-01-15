
float pFreq = 0.4f;
float pAmplitude = 5.0f;
float pPhase = 0.0f;

public void main(Frame editingFrame, FrameStrip strip)
{
 
  for (float t=0; t<(Math.PI * 2.0f); t+=pFreq)
  {
    Frame f = new Frame();

    for (int x=0; x<Frame.EdgeLEDCount; x++)
    {
      int y = 3 + (int)(Math.Sin((pPhase + t) + ((float)x * 0.4f)) * pAmplitude);

      f.setLEDDiscard(x, y-2, 1, 0);
      f.setLEDDiscard(x, y-1, 2, 0);
      f.setLEDDiscard(x, y, 3, 0);
      f.setLEDDiscard(x, y+1, 2, 0);
      f.setLEDDiscard(x, y+2, 1, 0);
    }

    strip.addFrame(f, false);
  }

}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float Frequency
{
  get { return pFreq; }
  set { pFreq = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float Amplitude
{
  get { return pAmplitude; }
  set { pAmplitude = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float Phase
{
  get { return pPhase; }
  set { pPhase = value; }
}