using System;
using BadgeCore;

namespace BadgeScript
{
  public interface ScriptedTool
  {
    void main(Frame editingFrame, FrameStrip strip);
  }
}
