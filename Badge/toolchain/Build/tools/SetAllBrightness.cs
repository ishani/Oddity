
float pAmount = 0.4f;

public void main(Frame editingFrame, FrameStrip strip)
{
	for (int f=0; f<strip.NumFrames; f++)
  {
    Frame q = strip.getFrameAtIndex(f);
    q.BrightnessAsFloat = pAmount;
  }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public float Amount
{
  get { return pAmount; }
  set { pAmount = value; }
}

