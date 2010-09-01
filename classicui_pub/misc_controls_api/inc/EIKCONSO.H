/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:
*
*/


#if !defined(__EIKCONSO_H__)
#define __EIKCONSO_H__
													   
#if !defined(__E32CONS_H__)
#include <e32cons.h>
#endif

#if !defined(__EIKSBOBS_H__)
#include <eiksbobs.h>
#endif

#if !defined(__EIKSBFRM_H__)
#include <eiksbfrm.h>
#endif

#include <AknControl.h>

#define ATT_DOUBLEWIDTH					0x60
#define ATT_DOUBLETOP	   			0x20	
#define ATT_DOUBLEBOTTOM				0x40	
////////////////////////////////////////////
#define ATT_ITALIC						0x08	
#define ATT_INVERSE 					0x04
#define ATT_UNDERLINE					0x02
#define ATT_BOLD						0x01
////////////////////////////////////////////
#define ATT_COLORMASK					0x80	// &x!=0 : color
#define ATT_DOUBLEMASK					0x60 	// &x : only the bits relevant for doublewidth/doubleheight
#define ATT_RIGHTMASK					0x10	// |x to set RIGHT indicator
#define ATT_IGNORE_RIGHTLEFT			0xEF	// &x to clear the RIGHT/LEFT flag
#define ATT_IGNORE_INVERSE				0xFB	// &x to clear the INVERSE flag
////////////////////////////////////////////
#define ATT_MAXVALUE					0xFF	// all flags set (maximum value of attribute byte)
#define ATT_NORMAL						0		// the default character attribute

enum TEikConsWinUnits
	{
	EEikConsWinInPixels,
	EEikConsWinInChars
	};


	/** CEikConsoleScreen()
	
	@param aBuffer         String that needs to be clipped. will be modified by this call
	@param aFont           Font used in the code
	@param aMaxWidthInPixels Maximum length of text that will not be clipped.
	@param aDir            Where is the text clipped from. EDoNotClip, EClipFromEnd, EClipFromBeginning.
	@param aClipWidth      The length of the text after clipping. KDefaultClipWidth will make it use aMaxWidthInPixels.
	@param aClipString     The representation of three dots. (not really used anywhere - use the default value always or "")
       
	returns true if the text was clipped and 3 dots were added. 
    */
class CEikConsoleControl;
class CEikConsoleScreen : public CConsoleBase
	{
public:
	enum TEikConsoleFlags
		{
		EUseBackedUpWindow	=0x1,
		ENoInitialCursor	=0x2
		};
public:
	/** 
     * CEikConsoleScreen() constructor 
     */
	IMPORT_C CEikConsoleScreen();
	/** 
     * CEikConsoleScreen() destructor
     */
	IMPORT_C ~CEikConsoleScreen();

	/** Create() Creates a console and sets title and size
	 *
	 * @param aTitle          Title of the console
	 * @param aSize           Size of the console in pixels
     *  
	 * returns error code
     */
	IMPORT_C TInt Create(const TDesC& aTitle,TSize aSize);
    /** Read()
     * Not implemented
     */
	IMPORT_C void Read(TRequestStatus& aStatus);
    /** ReadCancel()
     * Not implemented
     */
	IMPORT_C void ReadCancel();
    /** KeyCode()
     * Not implemented
     */
	IMPORT_C TKeyCode KeyCode() const;
    /** KeyModifiers()
     * Not implemented
     */
	IMPORT_C TUint KeyModifiers() const;
	/** ConstructL() Constructs a console and sets title
	 *
	 * @param aTitle          Title of the console
	 * @param aFlags          Flags, for example EUseBackedUpWindow or ENoInitialCursor
     */
	IMPORT_C void ConstructL(const TDesC &aTitle,TInt aFlags);// use full screen 
	/** ConstructL() Constructs a console and sets title and size
	 *
	 * @param aTitle          Title of the console
     * @param aSize           Size of the console in pixels
	 * @param aFlags          Flags, for example EUseBackedUpWindow or ENoInitialCursor
	 * @param aUnit           Unit of the console
     */
	IMPORT_C void ConstructL(const TDesC &aTitle,const TSize &aSize,TInt aFlags,TEikConsWinUnits aUnit=EEikConsWinInChars); // place the screen at TPoint(0,0)
	/** ConstructL() Constructs a console and sets title and position and size
	 *
	 * @param aTitle          Title of the console
     * @param aTopLeft        TopLeft corner of the console window
     * @param aSize           Size of the console in pixels
	 * @param aFlags          Flags, for example EUseBackedUpWindow or ENoInitialCursor
	 * @param aUnit           Unit of the console
     */
	IMPORT_C void ConstructL(const TDesC &aTitle,TPoint aTopLeft,const TSize &aSize,TInt aFlags,TEikConsWinUnits aUnit=EEikConsWinInChars); 
	/** SetConsWin() Sets console window
	 *
	 * @param aConsWin          Console control
     */
	IMPORT_C void SetConsWin(CEikConsoleControl *aConsWin); // use if you don't want WHOLE screen
	/** ConsoleControl() fetching console control
	 *
	 * Returns console control
     */
	inline CEikConsoleControl* ConsoleControl() const {return iConsoleControl;};

	/** SetTitle() Set title of the console
	 *
	 * @param aTitle          Title of the console
     */
	IMPORT_C void SetTitle(const TDesC &aTitle);
	/** SetTitle() Set title of the console
	 *
	 * @param aTitle          Title of the console
     */
	IMPORT_C void SetTitleL(const TDesC &aTitle);
	/** Title() Gets title of the console
	 *
	 * returns Title of the console
     */
	inline HBufC *Title() const {return iConsoleTitle;};
	
	/** ScreenSize() Gets size of the screen
	 *
	 * returns Size of the screen in pixels
     */
	IMPORT_C TSize ScreenSize() const;
	/** FlushChars() Updates the character buffers
	 */
	IMPORT_C void FlushChars(); //new
	/** CursorPos() Cursor position getter
     *  returns cursor position
	 */
	IMPORT_C TPoint CursorPos() const;
	/** SetCursorPosAbs Moving cursor to absolute position
     *
     * @param aPoint Position in absolute coordinates
	 */
	IMPORT_C void SetCursorPosAbs(const TPoint &aPoint);		
	/** SetCursorPosRel Moving cursor to relative position
     *
     * @param aPoint Position in relative coordinates
	 */
	IMPORT_C void SetCursorPosRel(const TPoint &aPoint);		
	/** SetCursorHeight changes cursor height
     *
     * @param aPercentage Cursor height relative to character height
	 */
	IMPORT_C void SetCursorHeight(TInt aPercentage);		
	/** Write() Writes text to the console
     *
     * @param aDes Text to be written to the console
	 */
	IMPORT_C void Write(const TDesC &aDes);				   		
	/** ClearScreen() Clears the console screen
	 * 
	 */
	IMPORT_C void ClearScreen();				
	/** ClearToEndOfLine() Clears from cursor position to end of the line
	 * 
	 */
	IMPORT_C void ClearToEndOfLine();		
	/** ClearChars() Clears characters within rectangle matching attributes
     *
     * @param aRect Rectangle in pixels
     * @param aCharacterAttributes Matching character attributes
	 */
	IMPORT_C void ClearChars(const TRect &aRect,TUint aCharacterAttributes);	
	/** HideCursor() Hides cursor
	 *
	 * @return nonzero if cursor was not visible
	 */
	IMPORT_C TInt HideCursor(); // returns nonzero if cursor wasn't visible
	/** DrawCursor() Draws cursor
	 */
	IMPORT_C void DrawCursor(); 
	/** DrawInSight Moves topleft corner
	 *
	 * @param aPosition New position for insight
	 */
	IMPORT_C void DrawInSight(TPoint aPosition);
	/** DrawCursorInSight() Draws cursor and insight
	 */
	IMPORT_C void DrawCursorInSight();

	/** Move cursor up
	 * @param aCount Number of steps to move
	 */	
	IMPORT_C void Up(TUint aCount=1);		
	/** Move cursor down
	 * @param aCount Number of steps to move
	 */	
	IMPORT_C void Down(TUint aCount=1);	
	/** Move cursor right
	 * @param aCount Number of steps to move
	 */	
	IMPORT_C void Right(TUint aCount=1);	
	/** Move cursor left
	 * @param aCount Number of steps to move
	 */	
	IMPORT_C void Left(TUint aCount=1);	
	/** Insert a CR
	 */
	IMPORT_C void Cr();							
	/** Insert a linefeed
	 */
	IMPORT_C void Lf();							
	/** Scroll characters
	 * @param anArea Area to scroll
	 * @param aVector How much to scroll
	 */
	IMPORT_C void ScrollChars(const TRect &anArea,const TPoint &aVector);

    /** Redraw a rectangle
	 * @param aRect Rectangle to redraw
     */
	IMPORT_C void Redraw(const TRect &aRect);	// called by CEikConsoleControl
    /** Moves topleft
     * @param aVector new position of topleft
     */
	IMPORT_C void MoveTopLeft(TPoint aVector);	// called by CEikConsoleControl

    /** Size of the history
     * @return lines stored for history buffer
     */
	inline TUint HistorySize() const {return iNoChrExtra;}; // lines ACTUALLY stored				
    /** Set history buffer size
     * @param aMaxChrExtra lines allocated for history
     * @param aMaxAttExtra attributed lines allocated for history
     */
	IMPORT_C void SetHistorySizeL(TUint aMaxChrExtra,TUint aMaxAttExtra);  // lines of back-scroll history resp. lines of ATTRIBUTED backscroll history (aMaxAttExtra<=aMaxChrExtra)
		
    /** Att() Attributes
     * @returns attributes
     */
	inline TUint Att() const {return iAtt;};
	
	/** Set attributes
     * @param aCharacterAttributes Attributes for characters
	 */
	IMPORT_C void SetAtt(TUint aCharacterAttributes);		
	/** Set attributes
     * @param aForegroundGray16 Grey16 attributes for foreground
     * @param aBackgroundGray16 Grey16 attribuets for background
	 */
	IMPORT_C void SetAtt(TUint aForegroundGray16,TUint aBackgroundGray16); 

    /** SetFontL() Sets the font for console
     * @param aFontDesc font specification
     */
	IMPORT_C void SetFontL(const TFontSpec &aFontDesc);	
	/** Font() Gets the used font
	 * @returns font specification
	 */
	IMPORT_C const TFontSpec& Font() const;

	/** SetSelection() Sets the selection position
     * @param aRange range of the selection
	 */
	IMPORT_C void SetSelection(const TRect &aRange); 
    /** SelectCursor() Sets empty selection starting and ending at cursor position
     */
	IMPORT_C void SelectCursor(); // empty selection starting and ending at cursor position
    /** Selection() Get selection position
     * @return selection position
     */
	IMPORT_C TRect Selection();
    /** RetrieveL() returns selected text
     * @param aRange selection
     * @return text in descriptor
     */
	IMPORT_C HBufC *RetrieveL(const TRect &aRange);	// returns selection in newly allocated buffer
	
	/** SetPureCRLF() sets pure flag
     * @param aFlag flags
	 */
	IMPORT_C void SetPureCRLF(TUint aFlag);
	/** SetAllPrintable() sets all printable flag
     * @param aFlag flags
	 */
	IMPORT_C void SetAllPrintable(TUint aFlag);
	/** SetScrollLock() sets scroll lock flag
     * @param aFlag flags
	 */
	IMPORT_C void SetScrollLock(TUint aFlag);
	/** SetKeepCursorInSight() sets cursor in sight flag
     * @param aFlag flags
	 */
	IMPORT_C void SetKeepCursorInSight(TUint aFlag);
	/** SetScrollBarVisibilityL() sets scrollbar visibility
     * @param aHBarVisibility horizontal scrollbar visibility
     * @param aVBarVisibility vertical scrollbar visibility
	 */
	IMPORT_C void SetScrollBarVisibilityL(CEikScrollBarFrame::TScrollBarVisibility aHBarVisibility, CEikScrollBarFrame::TScrollBarVisibility aVBarVisibility);
	/** UpdateScrollBars() updates scrollbars
	 * 
	 */
	IMPORT_C TBool UpdateScrollBars();

private:
	// high-level history manipulation
	void MemScrPut(const TDesC &aString,TPoint aPos,TUint8 aCharacterAttributes);
	void MemScrClr(const TRect &aRect,TUint8 aCharacterAttributes);
	void MemScrScrollUp(TUint aLines=1);
	void MemScrMove(TPoint anOldPt,TPoint aNewPt,TUint aLen);
	void MemScrScroll(const TRect &aRect,TPoint aVector);
	// low-level history access
	TPtr	MemChrPtr(TPoint aPos,TUint aLen);
	TPtr8	MemAttPtr(TPoint aPos,TUint aLen);
	// console screen-to-visible window conversion
	TPoint 	ScrToVis(TPoint aPoint);
	TRect 	ScrToVis(const TRect &aRect);
	// recalculates iVisSize and iVisWin
	TBool RecalculateSize();	
	// calculate a TopLeft that would put aPosition in-sight
	TPoint GetAnInSightPosition(TPoint aPosition) const;
	// draw cursor or draw cursor in sight, depending on iKeepCursorInSight
	void DrawCursorWhereNeeded();
	// smart cursor-clipping: clips cursor to within screen, but allows it to be past the last character
	void ClipCursor();
	// redraw characters with doublewidth LEFT/RIGHT flag set depending on odd/even columns
	void RedrawChars(TInt anX,TInt anY,TInt aLength,TUint aCharacterAttributes);
	// routines needed for selection
	void InvertOverlap(TPoint aStart,TPoint aEnd,TPoint bStart,TPoint bEnd);
	void InvertRange(const TRect &aRect);

private:
	CEikConsoleControl *iConsoleControl;// console window (handles redraw events)
	TSize iConsoleSize; 		// size of console in characters (e.g. 80x24)	
	HBufC *iConsoleTitle;		// console title
	TRect iSelection; 			// current selection
	TPoint iCursor;				// current cursor position
	TUint iAtt;					// current character attribute

	TInt iWriteNow;				// if FALSE, Write()-calls can be buffered
	TBuf<256> iWriteBuffer;		// the Write() buffer

	TInt	iMaxChrExtra;		// max nr of extra lines of characters stored
	TInt	iNoChrExtra;		// actual nr of extra lines of characters stored
	TInt	iMaxAttExtra;		// max nr of extra lines of character attributes stored
	TText	*iChrBuf;			// character history
	TUint8	*iAttBuf;			// attribute history

	TPoint	iTopLeft;			// coordinates of top left corner of visual display
	TRect iVisWin;				// RECT visible window
	TSize iVisSize;				// SIZE visible window

	// settings
	TUint iPureCRLF;			// FALSE by default. If TRUE, CR and LF are "pure"
	TUint iAllPrintable;		// FALSE by default. If TRUE, even chars 0-31 are printed
	TUint iScrollLock;			// FALSE by default. If TRUE, will not scroll at bottom line
	TUint iKeepCursorInSight;	// TRUE by default. If FALSE, cursor may be offscreen after a Write()
	TUint iCursorBlinking; 		// TRUE if cursor should be visible (i.e. user WANTS it to be visible)

	TInt iConsFlags;
	};

class CEikConsoleControl : public CAknControl, public MEikScrollBarObserver
	{
public:	
	// constructors, destructors, initialization
    /** Constructor
     */
	IMPORT_C CEikConsoleControl();
	/** Destructor
	 */
	IMPORT_C ~CEikConsoleControl();
    /* ConstructL()
     */
	IMPORT_C void	ConstructL(TInt aFlags);
    /* ConstructL()
     */
	IMPORT_C void	ConstructL(TPoint aTopLeft,const TSize &aSize,TInt aFlags,TEikConsWinUnits aUnit);
    /** SetRedrawer
     * @param aConsole console screen
     */
	IMPORT_C void 	SetRedrawer(CEikConsoleScreen *aConsole);

	// font stuff
	/** SetFontL() sets the console font
	 * @param aFontSpec font specification
	 * @param aFont font instance
	 */
	IMPORT_C void	SetFontL(const TFontSpec &aFontSpec,const CFbsFont* aFont);		// change to font aFontSpec
	/** Font() gets font specification
	 */
	inline const TFontSpec& Font() const {return iFontSpec;};	// returns current fontspec

	/** CharSize() gets character size
	 */
	inline const TSize& CharSize() const {return iCharSize;};	
    /** VisibibleSize() gets visible size
     *
     */
	IMPORT_C TSize	VisibleSize() const;						// returns maximal visible nr of visible characters

	// cursor stuff
	/** SetCursorHeight() Sets cursor height
     * @param aPercentage value 0..100%
	 */
	IMPORT_C void	SetCursorHeight(TUint aPercentage);	// set cursor height (0-100%)
    /** DrawCursor Draws cursor at position
     * @param aPosition position
     */
	IMPORT_C void	DrawCursor(TPoint aPosition);		// draw cursor at character position
    /** HideCursor hides cursor
     */
	IMPORT_C void	HideCursor();						// hide cursor

	// basic graphic functions
	/** DrawChars() draws characters
     * @param aString string to be drawn
     * @param aPosition position of the string
     * @param aCharacterAttributes attributes of the drawn string
	 */
	IMPORT_C void	DrawChars(const TDesC &aString,const TPoint &aPosition,TUint aCharacterAttributes);	// draw aString at character position aPosition using
    /** ClearChars() clears characters
     * @param anArea area to be cleared
     * @param aCharacterAttributes attributes of cleared characters
     */
	IMPORT_C void	ClearChars(const TRect &anArea,TUint aCharacterAttributes);	// clear the character area
    /** InsertChars() inserts character area
     * @param anArea area to be inserted
     */
	IMPORT_C void	InvertChars(const TRect &anArea);	// invert the character area
    /** ScrollChars scrolls character area
     * @param anArea area to be scrolled
     * @param aVector direction to be scrolled
     */
	IMPORT_C void	ScrollChars(const TRect &anArea,const TPoint &aVector);	// scroll characters inside anArea by the given vector

	// scrollbar stuff
    /** sets scrollbar visibility
     * @param aHBarVisibility horizontal scrollbar visibility
     * @param aVBarVisibility vertical scrollbar visibility
     */    
	IMPORT_C TInt	SetScrollBarVisibilityL(CEikScrollBarFrame::TScrollBarVisibility aHBarVisibility, CEikScrollBarFrame::TScrollBarVisibility aVBarVisibility);
    /** Updates scrollbar
     * @param aDataSize size of the data
     * @param aVisibleSize how much of the data is visible on the console
     * @param aPos position of the visible area relative to whole data
     * @return ETrue if as a result, the visible window has changed
     */
	IMPORT_C TBool	UpdateScrollbarsL(const TSize &aDataSize,const TSize& aVisibleSize,TPoint aPos);
    /** Handles scroll event
     * @param aScrollBar scrollbar to be used for the event
     * @param aEventType type of the event that happened
     */
	IMPORT_C void	HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType);
    /** Updates an area
     */
	IMPORT_C void	UpdateArea();

public:	// from CCoeControl
	/** GetColorUseListL provides color use list for the control
	 */
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
    /** HandleResourceChange handles several kinds of resource change events
     */
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
    /** HandlePointerEventL handles touch pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

protected:	// virtual
	// window stuff
    /** Draws the control
     */
	IMPORT_C void	Draw(const TRect& aRect) const;	
    /** Size has changed
     */
	IMPORT_C void	SizeChanged();
    /** Focus has changed
     */
	IMPORT_C void FocusChanged(TDrawNow aDrawNow);
    /** Component controls count
     */
	IMPORT_C virtual TInt CountComponentControls() const;
    /** Component controls
     */
	IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;
    /** Writes internal state
     */
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

private:  // virtual - Reserved from CCoeControl
	IMPORT_C virtual void Reserved_2();

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private:
	TPoint	CharsToPixels(TPoint aPoint);
	TRect	CharsToPixels(const TRect &aRect);
	TRect	PixelsToChars(const TRect &aRect);
	void	ClearPixels(const TRect &anArea,TRgb aColor) const;

	void 	NextFontL(); 			
	void	InterpretAttribute(TUint AnAtt);
	void	InterpretColorBits(TUint aCharacterAttributes);
	inline 	CEikConsoleControl &M() const {return((CEikConsoleControl&)(*this));}
 	void CreateScrollBarFrameLayout(TEikScrollBarFrameLayout& aLayout) const;
	void	InitFontSpecL();

private:
	CEikConsoleScreen *iConsole;	// the console that owns this window
	TRgb iBackGray16;				// current background color 
	TRgb iPenGray16;				// current pen color for characters
	TUint iLastAtt;					// last attribute, to see if we need to change the gc
	TUint iLastFontFlags;			// last attribute, to see if we need to load another font

	TSize iCharSize;				// size of a single character (in pixels)
	TSize iViewInPixels;			// size of area available for characters (in pixels)
	TSize iViewInChars;				// size of area available for characters (in characters)

	TTextCursor iTextCursor;		// cursor to use
	TUint iCursorHeightPercentage;	// required height of cursor (as a percentage)

	TInt iRedrawing;				// NONZERO IF BUSY REDRAWING
	
	CEikScrollBarFrame* iSBFrame;
	CEikScrollBarFrame::TScrollBarVisibility	iHBarVisibility;
	CEikScrollBarFrame::TScrollBarVisibility	iVBarVisibility;
	TPoint	iLastThumbPos;

	const CFont *iCurrentFont;		// Current font
	TFontSpec iFontSpec;			// Current font spec
	TFontUnderline iFontUnderline;	// Current font spec underline
	TUint iFontHeight;				// Height of current font when not doubleheight/doublewidth
	TUint iFontIsProportional; 		// nonzero if font is proportional
	};



#endif
