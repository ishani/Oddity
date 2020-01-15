// <file>
//     <copyright see="prj:///doc/copyright.txt"/>
//     <license see="prj:///doc/license.txt"/>
//     <author name="Daniel Grunwald"/>
//     <version>$Revision: 4125 $</version>
// </file>

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Documents;
using System.Windows.Input;

using ICSharpCode.AvalonEdit.Document;
using ICSharpCode.AvalonEdit.Highlighting;
using ICSharpCode.AvalonEdit.Utils;

namespace ICSharpCode.AvalonEdit.Gui
{
	/// <summary>
	/// We re-use the CommandBinding and InputBinding instances between multiple text areas,
	/// so this class is static.
	/// </summary>
	static class EditingCommandHandler
	{
		/// <summary>
		/// Creates a new <see cref="TextAreaInputHandler"/> for the text area.
		/// </summary>
		public static TextAreaInputHandler Create(TextArea textArea)
		{
			TextAreaInputHandler handler = new TextAreaInputHandler(textArea);
			handler.CommandBindings.AddRange(CommandBindings);
			handler.InputBindings.AddRange(InputBindings);
			return handler;
		}
		
		static readonly List<CommandBinding> CommandBindings = new List<CommandBinding>();
		static readonly List<InputBinding> InputBindings = new List<InputBinding>();
		
		static void AddBinding(ICommand command, ModifierKeys modifiers, Key key, ExecutedRoutedEventHandler handler)
		{
			CommandBindings.Add(new CommandBinding(command, handler));
			InputBindings.Add(new KeyBinding(command, key, modifiers));
		}
		
		static EditingCommandHandler()
		{
			CommandBindings.Add(new CommandBinding(ApplicationCommands.Delete, OnDelete(ApplicationCommands.NotACommand), CanDelete));
			AddBinding(EditingCommands.Delete, ModifierKeys.None, Key.Delete, OnDelete(EditingCommands.SelectRightByCharacter));
			AddBinding(EditingCommands.DeleteNextWord, ModifierKeys.Control, Key.Delete, OnDelete(EditingCommands.SelectRightByWord));
			AddBinding(EditingCommands.Backspace, ModifierKeys.None, Key.Back, OnDelete(EditingCommands.SelectLeftByCharacter));
			InputBindings.Add(new KeyBinding(EditingCommands.Backspace, Key.Back, ModifierKeys.Shift)); // make Shift-Backspace do the same as plain backspace
			AddBinding(EditingCommands.DeletePreviousWord, ModifierKeys.Control, Key.Back, OnDelete(EditingCommands.SelectLeftByWord));
			AddBinding(EditingCommands.EnterParagraphBreak, ModifierKeys.None, Key.Enter, OnEnter);
			AddBinding(EditingCommands.EnterLineBreak, ModifierKeys.Shift, Key.Enter, OnEnter);
			AddBinding(EditingCommands.TabForward, ModifierKeys.None, Key.Tab, OnTab);
			AddBinding(EditingCommands.TabBackward, ModifierKeys.Shift, Key.Tab, OnShiftTab);
			
			CommandBindings.Add(new CommandBinding(ApplicationCommands.Copy, OnCopy, CanCutOrCopy));
			CommandBindings.Add(new CommandBinding(ApplicationCommands.Cut, OnCut, CanCutOrCopy));
			CommandBindings.Add(new CommandBinding(ApplicationCommands.Paste, OnPaste, CanPaste));
		}
		
		static TextArea GetTextArea(object target)
		{
			return target as TextArea;
		}
		
		#region EnterLineBreak
		static void OnEnter(object target, ExecutedRoutedEventArgs args)
		{
			TextArea textArea = GetTextArea(target);
			if (textArea != null && textArea.Document != null) {
				string newLine = NewLineFinder.GetNewLineFromDocument(textArea.Document, textArea.Caret.Line);
				using (textArea.Document.RunUpdate()) {
					textArea.ReplaceSelectionWithText(newLine);
					if (textArea.IndentationStrategy != null) {
						DocumentLine line = textArea.Document.GetLineByNumber(textArea.Caret.Line);
						textArea.IndentationStrategy.IndentLine(line);
					}
				}
				textArea.Caret.BringCaretToView();
				args.Handled = true;
			}
		}
		#endregion
		
		#region Tab
		static void OnTab(object target, ExecutedRoutedEventArgs args)
		{
			TextArea textArea = GetTextArea(target);
			if (textArea != null && textArea.Document != null) {
				using (textArea.Document.RunUpdate()) {
					if (textArea.Selection.IsMultiline(textArea.Document)) {
						DocumentLine start = textArea.Document.GetLineByOffset(textArea.Selection.SurroundingSegment.Offset);
						DocumentLine end = textArea.Document.GetLineByOffset(textArea.Selection.SurroundingSegment.EndOffset);
						while (true) {
							int offset = start.Offset;
							if (textArea.ReadOnlySectionProvider.CanInsert(offset))
								textArea.Document.Insert(offset, textArea.Options.IndentationString);
							if (start == end)
								break;
							start = start.NextLine;
						}
					} else {
						string indentationString = textArea.Options.GetIndentationString(textArea.Caret.Column);
						textArea.ReplaceSelectionWithText(indentationString);
					}
				}
				textArea.Caret.BringCaretToView();
				args.Handled = true;
			}
		}
		
		static void OnShiftTab(object target, ExecutedRoutedEventArgs args)
		{
			TextArea textArea = GetTextArea(target);
			if (textArea != null && textArea.Document != null) {
				using (textArea.Document.RunUpdate()) {
					DocumentLine start, end;
					if (textArea.Selection.IsEmpty) {
						start = end = textArea.Document.GetLineByNumber(textArea.Caret.Line);
					} else {
						start = textArea.Document.GetLineByOffset(textArea.Selection.SurroundingSegment.Offset);
						end = textArea.Document.GetLineByOffset(textArea.Selection.SurroundingSegment.EndOffset);
					}
					while (true) {
						int offset = start.Offset;
						ISegment s = TextUtilities.GetSingleIndentationSegment(textArea.Document, offset, textArea.Options.IndentationSize);
						if (s.Length > 0) {
							s = textArea.ReadOnlySectionProvider.GetDeletableSegments(s).FirstOrDefault();
							if (s != null && s.Length > 0) {
								textArea.Document.Remove(s.Offset, s.Length);
							}
						}
						if (start == end)
							break;
						start = start.NextLine;
					}
				}
				textArea.Caret.BringCaretToView();
				args.Handled = true;
			}
		}
		#endregion
		
		#region Delete
		static ExecutedRoutedEventHandler OnDelete(RoutedUICommand selectingCommand)
		{
			return (target, args) => {
				TextArea textArea = GetTextArea(target);
				if (textArea != null && textArea.Document != null) {
					// call BeginUpdate before running the 'selectingCommand'
					// so that undoing the delete does not select the deleted character
					using (textArea.Document.RunUpdate()) {
						if (textArea.Selection.IsEmpty)
							selectingCommand.Execute(args.Parameter, textArea);
						textArea.RemoveSelectedText();
						if (selectingCommand == EditingCommands.SelectLeftByWord) {
							// Special case: when Ctrl+Backspace deletes until the start of the line,
							// also delete the previous line delimiter.
							// This allows deleting lines that consist only of indentation using a single
							// press on Ctrl+Backspace.
							if (textArea.Caret.Column == 1 && textArea.Caret.VisualColumn == 0 && textArea.Caret.Line > 1) {
								DocumentLine previousLine = textArea.Document.GetLineByNumber(textArea.Caret.Line - 1);
								textArea.Document.Remove(previousLine.EndOffset, previousLine.DelimiterLength);
							}
						}
					}
					textArea.Caret.BringCaretToView();
					args.Handled = true;
				}
			};
		}
		
		static void CanDelete(object target, CanExecuteRoutedEventArgs args)
		{
			// HasSomethingSelected for delete command
			TextArea textArea = GetTextArea(target);
			if (textArea != null && textArea.Document != null) {
				args.CanExecute = !textArea.Selection.IsEmpty;
				args.Handled = true;
			}
		}
		#endregion
		
		#region Clipboard commands
		static void CanCutOrCopy(object target, CanExecuteRoutedEventArgs args)
		{
			// HasSomethingSelected for copy and cut commands
			TextArea textArea = GetTextArea(target);
			if (textArea != null && textArea.Document != null) {
				args.CanExecute = textArea.Options.CutCopyWholeLine || !textArea.Selection.IsEmpty;
				args.Handled = true;
			}
		}
		
		static void OnCopy(object target, ExecutedRoutedEventArgs args)
		{
			TextArea textArea = GetTextArea(target);
			if (textArea != null && textArea.Document != null) {
				if (textArea.Selection.IsEmpty && textArea.Options.CutCopyWholeLine) {
					DocumentLine currentLine = textArea.Document.GetLineByNumber(textArea.Caret.Line);
					CopyWholeLine(textArea, currentLine);
				} else {
					CopySelectedText(textArea);
				}
				args.Handled = true;
			}
		}
		
		static void OnCut(object target, ExecutedRoutedEventArgs args)
		{
			TextArea textArea = GetTextArea(target);
			if (textArea != null && textArea.Document != null) {
				if (textArea.Selection.IsEmpty && textArea.Options.CutCopyWholeLine) {
					DocumentLine currentLine = textArea.Document.GetLineByNumber(textArea.Caret.Line);
					CopyWholeLine(textArea, currentLine);
					textArea.Document.Remove(currentLine.Offset, currentLine.TotalLength);
				} else {
					CopySelectedText(textArea);
					textArea.RemoveSelectedText();
				}
				textArea.Caret.BringCaretToView();
				args.Handled = true;
			}
		}
		
		static void CopySelectedText(TextArea textArea)
		{
			string text = textArea.Selection.GetText(textArea.Document);
			// Ensure we use the appropriate newline sequence for the OS
			DataObject data = new DataObject(NewLineFinder.NormalizeNewLines(text, Environment.NewLine));
			// Also copy text in HTML format to clipboard - good for pasting text into Word
			// or to the SharpDevelop forums.
			HtmlClipboard.SetHtml(data, HtmlClipboard.CreateHtmlFragmentForSelection(textArea, new HtmlOptions(textArea.Options)));
			Clipboard.SetDataObject(data, true);
		}
		
		const string LineSelectedType = "MSDEVLineSelect";  // This is the type VS 2003 and 2005 use for flagging a whole line copy
		
		static void CopyWholeLine(TextArea textArea, DocumentLine line)
		{
			ISegment wholeLine = new SimpleSegment(line.Offset, line.TotalLength);
			string text = textArea.Document.GetText(wholeLine);
			// Ensure we use the appropriate newline sequence for the OS
			DataObject data = new DataObject(NewLineFinder.NormalizeNewLines(text, Environment.NewLine));
			
			// Also copy text in HTML format to clipboard - good for pasting text into Word
			// or to the SharpDevelop forums.
			DocumentHighlighter highlighter = textArea.GetService(typeof(DocumentHighlighter)) as DocumentHighlighter;
			HtmlClipboard.SetHtml(data, HtmlClipboard.CreateHtmlFragment(textArea.Document, highlighter, wholeLine, new HtmlOptions(textArea.Options)));
			
			MemoryStream lineSelected = new MemoryStream(1);
			lineSelected.WriteByte(1);
			data.SetData(LineSelectedType, lineSelected, false);
			
			Clipboard.SetDataObject(data, true);
		}
		
		static void CanPaste(object target, CanExecuteRoutedEventArgs args)
		{
			TextArea textArea = GetTextArea(target);
			if (textArea != null && textArea.Document != null) {
				args.CanExecute = textArea.ReadOnlySectionProvider.CanInsert(textArea.Caret.Offset)
					&& Clipboard.ContainsText();
				args.Handled = true;
			}
		}
		
		static void OnPaste(object target, ExecutedRoutedEventArgs args)
		{
			TextArea textArea = GetTextArea(target);
			if (textArea != null && textArea.Document != null) {
				Debug.WriteLine( Clipboard.GetText(TextDataFormat.Html) );
				
				// convert text back to correct newlines for this document
				string newLine = NewLineFinder.GetNewLineFromDocument(textArea.Document, textArea.Caret.Line);
				string text = NewLineFinder.NormalizeNewLines(Clipboard.GetText(), newLine);
				
				bool fullLine = textArea.Options.CutCopyWholeLine && Clipboard.ContainsData(LineSelectedType);
				if (fullLine) {
					DocumentLine currentLine = textArea.Document.GetLineByNumber(textArea.Caret.Line);
					textArea.Document.Insert(currentLine.Offset, text);
				} else {
					textArea.ReplaceSelectionWithText(text);
				}
				textArea.Caret.BringCaretToView();
				args.Handled = true;
			}
		}
		#endregion
	}
}
