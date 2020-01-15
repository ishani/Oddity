
float pFreq = 0.4f;
float pAmplitude = 5.0f;
float pXScale = 0.4f;
bool fillEdges = true;

public void main(Frame editingFrame, FrameStrip strip)
{
  for (float t=0; t<(Math.PI * 2.0f); t+=pFreq)
  {
    Frame f = new Frame();

    for (int x=0; x<Frame.EdgeLEDCount; x++)
    {
      int y = 3 + (int)(Math.Sin(t + ((float)x * pXScale)) * pAmplitude);

      if (fillEdges)
      {
        for (int m=6; m<35; m++)
          f.setLEDDiscard(x, y-m, 0, 1);
      }
        
      f.setLEDDiscard(x, y-5, 0, 1);
      f.setLEDDiscard(x, y-4, 0, 2);
      f.setLEDDiscard(x, y-3, 1, 3);
      f.setLEDDiscard(x, y-2, 2, 3);
      f.setLEDDiscard(x, y-1, 3, 3);
      f.setLEDDiscard(x, y, 3, 2);
      f.setLEDDiscard(x, y+1, 3, 1);
      f.setLEDDiscard(x, y+2, 3, 0);
      f.setLEDDiscard(x, y+3, 2, 0);
      f.setLEDDiscard(x, y+4, 1, 0);
      
      if (fillEdges)
      {      
        for (int m=5; m<35; m++)
          f.setLEDDiscard(x, y+m, 1, 0);
      }
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
public float XScale
{
  get { return pXScale; }
  set { pXScale = value; }
}


[CategoryAttribute("Options"), DescriptionAttribute("")] 
public bool FillEdges
{
  get { return fillEdges; }
  set { fillEdges = value; }
}
