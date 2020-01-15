
int pShiftAmount = 1;

public void main(Frame editingFrame, FrameStrip strip)
{
  Frame outFrame = new Frame();
  editingFrame.copyTo(outFrame);

  for (int y=0; y<Frame.EdgeLEDCount; y++)
    FrameTools.HorizontalShift(editingFrame, outFrame, y, pShiftAmount, true);

  editingFrame.copyFrom(outFrame);
  editingFrame.callUpdateEvent();
}

[CategoryAttribute("Options"), DescriptionAttribute("Amount to shift pixels by")] 
public int ShiftAmount
{
  get { return pShiftAmount; }
  set { pShiftAmount = value; }
}