
bool pFadeRed = true;
bool pFadeGreen = true;
bool pAllFrames = true;


public void main(Frame editingFrame, FrameStrip strip)
{
  if (pAllFrames)
  {
    for (int f=0; f<strip.NumFrames; f++)
    {
      Frame q = strip.getFrameAtIndex(f);
      q.fade(FadeRed, FadeGreen);
    }
  }
  else
  {
    if (editingFrame != null)
      editingFrame.fade(FadeRed, FadeGreen);
  }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public bool AllFrames
{
  get { return pAllFrames; }
  set { pAllFrames = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public bool FadeRed
{
  get { return pFadeRed; }
  set { pFadeRed = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public bool FadeGreen
{
  get { return pFadeGreen; }
  set { pFadeGreen = value; }
}