// <file>
//     <copyright see="prj:///doc/copyright.txt"/>
//     <license see="prj:///doc/license.txt"/>
//     <author name="Daniel Grunwald"/>
//     <version>$Revision: 3635 $</version>
// </file>

using System;

namespace ICSharpCode.AvalonEdit.Document
{
	/// <summary>
	/// Allows for low-level line tracking.
	/// The methods on this interface are called by the TextDocument's LineManager immediately after the document
	/// has changed, *while* the DocumentLineTree is updating.
	/// Thus, the DocumentLineTree may be in an invalid state when these methods are called.
	/// This interface should only be used to update per-line data structures like the HeightTree.
	/// Line trackers must not cause any events to be raised during an update to prevent other code from seeing
	/// the invalid state.
	/// </summary>
	public interface ILineTracker
	{
		/// <summary>
		/// Is called immediately before a document line is removed.
		/// </summary>
		void BeforeRemoveLine(DocumentLine line);
		
//		/// <summary>
//		/// Is called immediately after a document line is removed.
//		/// </summary>
//		void AfterRemoveLine(DocumentLine line);
		
		/// <summary>
		/// Is called immediately before a document line changes length.
		/// </summary>
		void SetLineLength(DocumentLine line, int newTotalLength);
		
		/// <summary>
		/// Is called immediately after a line was inserted.
		/// </summary>
		/// <param name="newLine">The new line</param>
		/// <param name="insertionPos">The existing line before the new line</param>
		void LineInserted(DocumentLine insertionPos, DocumentLine newLine);
		
		/// <summary>
		/// Indicates that there were changes to the document that the line tracker was not notified of.
		/// The document is in a consistent state (but the line trackers aren't), and line trackers should
		/// throw away their data and rebuild the document.
		/// </summary>
		void RebuildDocument();
	}
}
