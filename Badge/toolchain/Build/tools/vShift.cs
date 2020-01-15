
int pShiftAmount = 1;

public void main(Frame editingFrame, FrameStrip strip)
{
  Frame outFrame = new Frame();
  editingFrame.copyTo(outFrame);

  for (int x=0; x<Frame.EdgeLEDCount; x++)
    FrameTools.VerticalShift(editingFrame, outFrame, x, pShiftAmount, true);

  editingFrame.copyFrom(outFrame);
  editingFrame.callUpdateEvent();
}

[CategoryAttribute("Options"), DescriptionAttribute("Amount to shift pixels by")] 
public int ShiftAmount
{
  get { return pShiftAmount; }
  set { pShiftAmount = value; }
}