

static Int32 generateColourAtPoint(
	Int32 iterations,
	Double RealC,
	Double ImaginaryC )
{
	Double RealZ = 0;
	Double ImaginaryZ = 0;
	Double RealZ2 = 0;
	Double ImaginaryZ2 = 0;
	Int32 ColorIndex = 0;
	while( (ColorIndex < iterations) && (RealZ2 + ImaginaryZ2 < 4) )
	{
		RealZ2 = RealZ * RealZ;
		ImaginaryZ2 = ImaginaryZ * ImaginaryZ;
		ImaginaryZ = 2 * ImaginaryZ * RealZ + ImaginaryC;
		RealZ = RealZ2 - ImaginaryZ2 + RealC;
		ColorIndex++;
	}

	Int32 colourValue = (ColorIndex % 16);
	colourValue *= colourValue;
	return colourValue;
}

public void main(Frame editingFrame, FrameStrip strip)
{
  Double scale = 0.01;

  Byte r, g;
  for (int i=0; i<250; i++)
  {
    Frame fr = new Frame();
  	Double newScale = (0.1 / Math.Exp(scale));
	  Double realMin = 0.5 - (newScale * Frame.EdgeLEDCount) / 2.0;
	  Double imgMin = 0 - (newScale * Frame.EdgeLEDCount) / 2.0;

    for (int y=0; y<Frame.EdgeLEDCount; y++)
    {
      for (int x=0; x<Frame.EdgeLEDCount; x++)
      {
        Int32 gen = generateColourAtPoint(
					512,
					(realMin + newScale * (Double)x),
					(imgMin + newScale * (Double)y));

        FrameTools.ColourGradient((float)gen / 64.0f, true, true, out r, out g);
        fr.setLED(x, y, r, g);
      }
    }

    scale += 0.03;
    strip.addFrame(fr, false);
  }
}
