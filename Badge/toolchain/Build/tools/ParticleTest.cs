
Random rng = new Random();

public void main(Frame editingFrame, FrameStrip strip)
{   
  float px = (float)rng.NextDouble() * 7.0f, py = (float)rng.NextDouble() * 7.0f;
  float vx = -2.0f + ((float)rng.NextDouble() * 4.0f), vy = -2.0f + ((float)rng.NextDouble() * 4.0f);

  if (strip.NumFrames < 140)
  {
    for (int i=0; i<140; i++)
    {
      Frame f = new Frame();
      strip.addFrame(f, false);
    }
  }
  
  for (int i=0; i<140; i++)
  {
	  px += vx;
	  py += vy;
	  if (px < 0)
	  {
		  px = 0;
		  vx = -vx * 0.7f;
	  }
	  if (px > 7.0f)
	  {
		  px = 7.0f;
		  vx = -vx * 0.7f;
	  }	
	  if (py < 0)
	  {
		  py = 0;
		  vy = -vy * 0.9f;
	  }
	  if (py > 7.0f)
	  {
		  py = 7.0f;
		  vy = -vy * 0.9f;
	  }

	  vy -= 0.12f;

	  Frame f = strip.getFrameAtIndex(i);

	  f.plotAntialiasedLED(px, 7.0f - py, 0);    
  }
}