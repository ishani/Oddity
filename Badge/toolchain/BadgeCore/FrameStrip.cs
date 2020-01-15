using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using System.IO;
using System.Windows.Forms;


namespace BadgeCore
{
  [Serializable]
  public class FrameStripData
  {
    public Byte m_fps = 15;
    public List<Frame> m_frames = new List<Frame>();
  }

  public class FrameStrip
  {
    protected Frame m_selection = null;
    protected FrameStripData m_data = new FrameStripData();

    public delegate void StripContentsChangeDelegate(Frame frame, bool added, bool autoselect);

    public event EventHandler<EventArgs> FrameDataChanged;
    public event StripContentsChangeDelegate StripContentsChanged;
    public event EventHandler<EventArgs> SelectionChange;


    public Frame SelectedFrame
    {
      get
      {
        return m_selection;
      }

      set
      {
        m_selection = value;

        if (SelectionChange != null)
        {
          EventArgs eN = new EventArgs();
          SelectionChange(this, eN);
        }
      }
    }

    public Int32 NumFrames
    {
      get { return m_data.m_frames.Count; }
    }

    public Byte FPS
    {
      get { return m_data.m_fps; }
      set { m_data.m_fps = value; }
    }

    public Frame getFrameAtIndex(Int32 index)
    {
      return m_data.m_frames[index];
    }

    public Int32 getIndexForFrame(Frame f)
    {
      return m_data.m_frames.IndexOf(f);
    }

    public Frame getLastFrame()
    {
      if (NumFrames > 0)
      {
        return m_data.m_frames[NumFrames - 1];
      }
      return null;
    }





    void CallUpdateEvent(object sender, EventArgs e)
    {
      if (FrameDataChanged != null)
        FrameDataChanged(this, e);
    }

    public void addFrame(Frame f, bool autoSelect)
    {
      f.UpdateEvent += CallUpdateEvent;
      m_data.m_frames.Add(f);

      if (autoSelect)
        SelectedFrame = f;

      if (StripContentsChanged != null)
      {
        EventArgs eN = new EventArgs();
        StripContentsChanged(f, true, autoSelect);
      }
    }

    public void insertFrame(Frame f, Int32 index, bool autoSelect)
    {
      if (index < 0)
        index = 0;

      f.UpdateEvent += CallUpdateEvent;
      m_data.m_frames.Insert(index, f);

      if (autoSelect)
        SelectedFrame = f;

      if (StripContentsChanged != null)
      {
        EventArgs eN = new EventArgs();
        StripContentsChanged(f, true, autoSelect);
      }
    }

    public void deleteFrame(Frame f)
    {
      Int32 index = getIndexForFrame(f) - 1;

      f.UpdateEvent -= CallUpdateEvent;
      m_data.m_frames.Remove(f);

      if (index < m_data.m_frames.Count && index >= 0)
        SelectedFrame = getFrameAtIndex(index);
      else
        SelectedFrame = null;

      if (StripContentsChanged != null)
      {
        EventArgs eN = new EventArgs();
        StripContentsChanged(f, false, false);
      }      
    }



    public void exportToBinary(BinaryWriter writer)
    {
      short frameCount = (short)m_data.m_frames.Count;

      writer.Write(frameCount);
      writer.Write(FPS);

      foreach (Frame f in m_data.m_frames)
      {
        f.exportToBinary(writer);
      }
    }



    public void deleteAll()
    {
      foreach (Frame f in m_data.m_frames)
      {
        f.UpdateEvent -= CallUpdateEvent;
      }

      m_data.m_frames.Clear();
      SelectedFrame = null;

      if (StripContentsChanged != null)
      {
        EventArgs eN = new EventArgs();
        StripContentsChanged(null, false, false);
      }    
    }






    public void save(string file)
    {
      Stream stream = null;
      try
      {
        stream = File.Create(file);
        Type[] extraTypes = new Type[2] { typeof(Frame), typeof(List<Frame>) };
        XmlSerializer serializer = new XmlSerializer(typeof(FrameStripData), extraTypes);
        serializer.Serialize(stream, m_data);
      }
      catch (Exception e)
      {
        MessageBox.Show(e.Message, "Save Failed", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
      }
      finally
      {
        if (stream != null)
          stream.Close();
      }
    }


    public enum LoadMode
    {
      Replace,
      Append,
      Overlay,
      OverlayAdditive,
      OverlayCutoutFG,
      OverlayCutoutBG,
    };

    public void load(string file, LoadMode LM)
    {
      Stream stream = null;
      try
      {
        stream = File.Open(file, FileMode.Open);
        Type[] extraTypes = new Type[2] { typeof(Frame), typeof(List<Frame>) };
        XmlSerializer serializer = new XmlSerializer(typeof(FrameStripData), extraTypes);
        FrameStripData incomingData = (FrameStripData)serializer.Deserialize(stream);

        m_data.m_fps = incomingData.m_fps;

        if (LM == LoadMode.Replace)
        {
          deleteAll();
        }

        Int32 selIndex = m_data.m_frames.Count;

        if (LM == LoadMode.Append || LM == LoadMode.Replace)
        {
          foreach (Frame f in incomingData.m_frames)
            addFrame(f, false);
        }
        else if (LM == LoadMode.Overlay ||
                 LM == LoadMode.OverlayAdditive ||
                 LM == LoadMode.OverlayCutoutFG ||
                 LM == LoadMode.OverlayCutoutBG)
        {
          Int32 curSelIndex = getIndexForFrame(SelectedFrame);
          Int32 maxIndex = Math.Min(incomingData.m_frames.Count, m_data.m_frames.Count - curSelIndex);
          maxIndex = Math.Max(maxIndex, 0);

          for (Int32 i = 0; i < maxIndex; i++)
          {
            if (i >= m_data.m_frames.Count)
              break;

            Frame blendOut = new Frame();

            if (LM == LoadMode.OverlayCutoutFG ||
                LM == LoadMode.OverlayCutoutBG)
            {
              FrameTools.OverlayCutout(m_data.m_frames[curSelIndex + i], incomingData.m_frames[i], blendOut, (LM == LoadMode.OverlayCutoutFG));
            }
            else
            {
              FrameTools.Overlay(m_data.m_frames[curSelIndex + i], incomingData.m_frames[i], blendOut, (LM == LoadMode.OverlayAdditive));
            }

            blendOut.copyTo(m_data.m_frames[curSelIndex + i]);
          }
        }

        if (m_data.m_frames.Count > selIndex)
          SelectedFrame = m_data.m_frames[selIndex];
      }
      catch (Exception e)
      {
        MessageBox.Show(e.Message, "Load Failed", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
      }
      finally
      {
        if (stream != null)
          stream.Close();
      }
    }

  }
}
