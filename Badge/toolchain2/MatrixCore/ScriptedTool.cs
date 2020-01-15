using System;
using MatrixCore;

namespace MatrixCore
{
  public interface ScriptedTool
  {
    void main(Frame EditingFrame, FrameSequence CurrentSequence);
  }
}
