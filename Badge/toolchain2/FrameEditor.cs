using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

using MatrixCore;


namespace Matrix
{
  public partial class FrameEditor : UserControl
  {
    private Frame     m_viewFrame = null;

    private Point     m_hitLED;

    private Stack<FrameData> m_undoStack = new Stack<FrameData>(6);
    private Stack<FrameData> m_redoStack = new Stack<FrameData>(6);
 

    public FrameEditor()
    {
      InitializeComponent();

      wFrameRender.OverlayPaint += FrameEditor_Overlay;
    }

    public Frame ViewFrame
    {
      set
      {
        // nix the undo/redo stacks when we change frames
        m_undoStack.Clear();
        m_redoStack.Clear();

        m_viewFrame = value;
        wFrameRender.FrameToRender = value;
      }
      get { return m_viewFrame; }
    }

    public void Undo()
    {
      if (m_viewFrame == null)
        return;

      if (m_undoStack.Count > 0)
      {
        // push the current state onto the redo stack
        m_redoStack.Push(m_viewFrame.CloneData());

        // replace current with last recorded undo
        m_viewFrame.ReplaceData(m_undoStack.Pop());
      }
    }

    public void Redo()
    {
      if (m_viewFrame == null)
        return;

      if (m_redoStack.Count > 0)
      {
        // the inverse of Undo
        m_undoStack.Push(m_viewFrame.CloneData());
        m_viewFrame.ReplaceData(m_redoStack.Pop());
      }
    }

    private void StoreForUndo()
    {
      // store original data if we need to undo
      m_undoStack.Push(m_viewFrame.CloneData());
    }

    private void HandleLEDPaint(MouseEventArgs e)
    {
      Point LED = new Point();
      if (!wFrameRender.MouseToLEDIndex(e.X, e.Y, ref LED))
        return;

      // any change will nuke the redo stack
      m_redoStack.Clear();
      
      m_hitLED = LED;

      FrameData fd;
      m_viewFrame.Lock(out fd);

      if (Control.ModifierKeys == Keys.Control)
      {
        if (e.Button == MouseButtons.Left)
          fd.Data[LED.X, LED.Y].decR();
        if (e.Button == MouseButtons.Right)
          fd.Data[LED.X, LED.Y].decG();
      }
      else
      {
        if (e.Button == MouseButtons.Left)
          fd.Data[LED.X, LED.Y].incR();
        if (e.Button == MouseButtons.Right)
          fd.Data[LED.X, LED.Y].incG();
      }

      m_viewFrame.Unlock(ref fd);
    }

    private void wFrameRender_MouseDown(object sender, MouseEventArgs e)
    {
      base.OnMouseDown(e);

      if (!wFrameRender.Focused)
        return;

      if (m_viewFrame == null)
        return;

      if (e.Button == MouseButtons.Left ||
          e.Button == MouseButtons.Right)
      {
        StoreForUndo();
        HandleLEDPaint(e);
      }
    }

    private void wFrameRender_MouseUp(object sender, MouseEventArgs e)
    {
      base.OnMouseUp(e);
    }

    private void wFrameRender_MouseMove(object sender, MouseEventArgs e)
    {
      base.OnMouseMove(e);

      if (m_viewFrame == null)
        return;

      if (e.Button == MouseButtons.Left ||
          e.Button == MouseButtons.Right)
      {
        Point LED = new Point();
        if (!wFrameRender.MouseToLEDIndex(e.X, e.Y, ref LED))
          return;

        if (m_hitLED.X != LED.X || m_hitLED.Y != LED.Y)
        {
          HandleLEDPaint(e);
        }
      }
    }

    private void wFrameRender_KeyUp(object sender, KeyEventArgs e)
    {
      if (m_viewFrame == null)
        return;

      FrameData fd;
      m_viewFrame.Lock(out fd);

      if (e.KeyCode == Keys.Up)
      {
        StoreForUndo();
        fd.ShiftVertical(-1, true);
        m_viewFrame.Unlock(ref fd);
      }
      else if (e.KeyCode == Keys.Down)
      {
        StoreForUndo();
        fd.ShiftVertical(1, true);
        m_viewFrame.Unlock(ref fd);
      }
      else if (e.KeyCode == Keys.Right)
      {
        StoreForUndo();
        fd.ShiftHorizontal(1, true);
        m_viewFrame.Unlock(ref fd);
      }
      else if (e.KeyCode == Keys.Left)
      {
        StoreForUndo();
        fd.ShiftHorizontal(-1, true);
        m_viewFrame.Unlock(ref fd);
      }
      else if (e.KeyCode == Keys.PageDown)
      {
        StoreForUndo();
        fd.Fade();
        m_viewFrame.Unlock(ref fd);
      }
      else if (e.KeyCode == Keys.PageUp)
      {
        StoreForUndo();
        fd.Intensify();
        m_viewFrame.Unlock(ref fd);
      }
      else if (e.KeyCode == Keys.Z && 
               Control.ModifierKeys == Keys.Control)
      {
        m_viewFrame.Discard(ref fd);
        Undo();
      }
      else if (e.KeyCode == Keys.Y &&
               Control.ModifierKeys == Keys.Control)
      {
        m_viewFrame.Discard(ref fd);
        Redo();
      }
      else
      {
        m_viewFrame.Discard(ref fd);
      }
    }

    private void FrameEditor_Overlay(object sender, PaintEventArgs e)
    {

    }
  }
}
