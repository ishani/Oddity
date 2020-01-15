

public void main(Frame editingFrame, FrameStrip strip)
{
  if (editingFrame == null)
    return;
  
  int startIndex = strip.getIndexForFrame(strip.SelectedFrame);
  int endIndex = startIndex + 8;
  
  if (endIndex > strip.NumFrames)
    endIndex = strip.NumFrames;

  
  float initial = strip.getFrameAtIndex(startIndex).BrightnessAsFloat;
  
  for (int f=startIndex; f<endIndex; f++)
  {
    Frame q = strip.getFrameAtIndex(f);
    q.BrightnessAsFloat = initial;
    initial += (-initial) * 0.5f;
  }
}
