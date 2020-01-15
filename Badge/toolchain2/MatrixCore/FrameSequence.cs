using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using System.IO;
using System.Windows.Forms;

namespace MatrixCore
{
  [Serializable]
  public class FrameSequenceData
  {
    public Byte Fps = 20;
    public List<Frame> Frames = new List<Frame>();
  }

  public class FrameSequence
  {
    private Int32 m_selectionIndex = -1;
    private FrameSequenceData m_data = new FrameSequenceData();

    public event EventHandler<EventArgs> SelectionChange;
    public event EventHandler<EventArgs> FrameDataChanged;


    #region Accessors
    public Frame SelectedFrame
    {
      get 
      {
        if (m_selectionIndex < 0)
          return null;

        return m_data.Frames[m_selectionIndex]; 
      }
    }

    public Int32 SelectionIndex
    {
      get { return m_selectionIndex; }
      set
      {
        if (m_selectionIndex > m_data.Frames.Count)
          throw new InvalidOperationException();

        m_selectionIndex = value;

        CallSelectionChange();
      }
    }

    public Int32 NumFrames
    {
      get { return m_data.Frames.Count; }
    }

    public Byte FPS
    {
      get { return m_data.Fps; }
      set { m_data.Fps = value; }
    }

    public Frame FrameAtIndex(Int32 index)
    {
      return m_data.Frames[index];
    }

    public Int32 IndexForFrame(Frame f)
    {
      return m_data.Frames.IndexOf(f);
    }
    #endregion

    #region Events    
    void CallFrameDataChanged(object sender, EventArgs e)
    {
      if (FrameDataChanged != null)
        FrameDataChanged(this, e);
    }

    void CallSelectionChange()
    {
      if (SelectionChange != null)
        SelectionChange(this, new EventArgs());
    }
    #endregion

    #region AddRemove
    public void Add(Frame f, bool autoSelect)
    {
      f.FrameChangedEvent += CallFrameDataChanged;
      m_data.Frames.Add(f);
    }

    public void Insert(Frame f, Int32 index, bool autoSelect)
    {
      if (index < 0)
        index = 0;

      f.FrameChangedEvent += CallFrameDataChanged;
      m_data.Frames.Insert(index, f);
    }

    public void Delete(Frame f)
    {
      Frame selFrame = SelectedFrame;

      f.FrameChangedEvent -= CallFrameDataChanged;
      m_data.Frames.Remove(f);

      SelectionIndex = IndexForFrame(selFrame);         
    }
    #endregion
  }
}
