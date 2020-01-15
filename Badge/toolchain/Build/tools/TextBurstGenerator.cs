
String pGeneratedText = "kaboom";
Int32 pFramesPerLetter = 10;

public enum FontSizeEnum
{
  PixelFont4x5,
  PixelFont5x7,
  PixelFontBold
};
FontSizeEnum    pFontSize;
string []fontFiles = {"pixelfont_4x5.bd", "pixelfont_5x7.bd", "pixelfont_bold.bd"};

public enum ColourModeEnum
{
  PureRed,
  PureGreen,
  OrangeNoise,
  GreenToRedGradientInY,
  GreenToRedGradientInX,
};
ColourModeEnum  pColourMode;

static Random rng = new Random();

static Byte[] RGradient = new Byte[8] {
  0, 0, 1, 2, 3, 3, 2, 1
};

static Byte[] GGradient = new Byte[8] {
  1, 2, 3, 3, 2, 1, 0, 0
};

public static void OP_PureRed(Int32 x, Int32 y, Int32 globalX, Int32 letterIndex, out Byte r, out Byte g)
{
  r = 3;
  g = 0;
}

public static void OP_PureGreen(Int32 x, Int32 y, Int32 globalX, Int32 letterIndex, out Byte r, out Byte g)
{
  r = 0;
  g = 3;
}

public static void OP_OrangeNoise(Int32 x, Int32 y, Int32 globalX, Int32 letterIndex, out Byte r, out Byte g)
{
  r = 3;
  g = (Byte)rng.Next(2,4);
}


public static void OP_GreenToRedGradientInY(Int32 x, Int32 y, Int32 globalX, Int32 letterIndex, out Byte r, out Byte g)
{
  r = RGradient[y];
  g = GGradient[y];
}

public static void OP_GreenToRedGradientInX(Int32 x, Int32 y, Int32 globalX, Int32 letterIndex, out Byte r, out Byte g)
{
  Int32 shifter = (globalX) % 8;
  r = RGradient[shifter];
  g = GGradient[shifter];
}


TextWizard.ColourFunc[] colourModes = 
{ 
  OP_PureRed,
  OP_PureGreen,
  OP_OrangeNoise,
  OP_GreenToRedGradientInY,
  OP_GreenToRedGradientInX
};

            
public void main(Frame editingFrame, FrameStrip strip)
{
  TextWizard s = new TextWizard(fontFiles[(Int32)pFontSize]);
  s.generateBurst(strip, pGeneratedText, pFramesPerLetter, colourModes[(Int32)pColourMode]);
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public FontSizeEnum FontSize
{
  get { return pFontSize; }
  set { pFontSize = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("Text to create")] 
public String GeneratedText
{
  get { return pGeneratedText; }
  set { pGeneratedText = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public Int32 FramesPerLetter
{
  get { return pFramesPerLetter; }
  set { pFramesPerLetter = value; }
}

[CategoryAttribute("Options"), DescriptionAttribute("")] 
public ColourModeEnum ColourMode
{
  get { return pColourMode; }
  set { pColourMode = value; }
}