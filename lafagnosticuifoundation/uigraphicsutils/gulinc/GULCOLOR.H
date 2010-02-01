// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#if !defined(__GULCOLOR_H__)
#define __GULCOLOR_H__

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__GDI_H__)
#include <gdi.h>
#endif

/** Logical colours.

Logical colours are used to specify the colour scheme for the controls in 
an application.

Many controls have one logical colour for text and another logical colour 
for the background. Some logical colours have a dimmed variant for when the 
control becomes inactive or disabled. Highlighted and pressed variants exist 
for controls that support selection or which can be pressed. 

@publishedAll
@released */
enum TLogicalColor
	{
	// Windows
	/** The colour of a window's background. */
	EColorWindowBackground,
	/** The colour of text in a window. */
	EColorWindowText,
	// Controls
	/** The colour of the background contents of a control. */
	EColorControlBackground,
	/** The colour of the text inside a control. */
	EColorControlText, 
	/** The background colour of a control's border. */
	EColorControlSurroundBackground,
	/** The colour of text in a control's border. */
	EColorControlSurroundText,
	/** The colour of a control's background when highlighted for selection. */
	EColorControlHighlightBackground, 
	/** The colour of the text in a control when highlighted for selection. */
	EColorControlHighlightText,
	/** The colour of a control's background when dimmed. */
	EColorControlDimmedBackground, 
	/** The colour of the text in a control when dimmed. */
	EColorControlDimmedText,
	/** The colour of a control's background when dimmed and highlighted for selection. */
	EColorControlDimmedHighlightBackground,
	/** The colour of the text in a control when dimmed and highlighted for selection. */
	EColorControlDimmedHighlightText,
	// Dialogs
	/** The colour of a dialog's background. */
	EColorDialogBackground,
	/** The colour of text inside a dialog. */
	EColorDialogText,
	/** A dialog title's background colour. */
	EColorDialogTitle,
	/** A dialog title's background colour when pressed. */
	EColorDialogTitlePressed,
	/** The text colour in a dialog's title. */
	EColorDialogTitleText,
	/** The text colour in a dialog's title when pressed. */
	EColorDialogTitleTextPressed,
	// Menus
	/** The colour of the menubar's background. */
	EColorMenubarBackground,
	/** The colour of text in the menubar. */
	EColorMenubarText,
	/** The colour of the menubar title's background. */
	EColorMenubarTitleBackground,
	/** The colour of text in the menubar title. */
	EColorMenubarTitleText,
	/** The colour of the menu pane background. */
	EColorMenuPaneBackground,
	/** The colour of text in the menu pane. */
	EColorMenuPaneText,
	/** The colour of the menu pane background when highlighted for selection. */
	EColorMenuPaneHighlight,
	/** The colour of text in the menu pane when highlighted for selection. */
	EColorMenuPaneTextHighlight,
	/** The colour of the menu pane background when dimmed and highlighted. */
	EColorMenuPaneDimmedHighlight,
	/** The colour of text in the menu pane when dimmed. */
	EColorMenuPaneDimmedText,
	/** The colour of text in the menu pane when dimmed and highlighted for selection. */
	EColorMenuPaneDimmedTextHighlight,
	// Command buttons
	/** The colour of the button background, when the button is in the unset state. */
	EColorButtonFaceClear,
	/** The colour of the button background when the button is in the set state. */
	EColorButtonFaceSet,
	/** The colour of the button background when the button is in the set state and 
	is pressed. */
	EColorButtonFaceSetPressed,
	/** The colour of the button background when the button is in the unset state and 
	is pressed. */
	EColorButtonFaceClearPressed,
	/** The colour of the button text. */
	EColorButtonText,
	/** The colour of the button text when the button is pressed. */
	EColorButtonTextPressed,
	/** The colour of the button text when the button is dimmed. */
	EColorButtonTextDimmed,		
	// Message windows
	/** The colour of the message window foreground. */
	EColorMsgWinForeground,
	EColorMsgWinBackground,
	// Scrollbars
	/** The colour of the scroll bar border. */
	EColorScrollBarBorder,
	EColorScrollBarShaft,
	/** The colour of the scroll bar shaft background when dimmed. */
	EColorScrollBarShaftDimmed,
	/** The colour of the scroll bar shaft background when pressed. */
	EColorScrollBarShaftPressed,
	/** The colour of the background for scroll bars with no thumb and no shaft. */
	EColorScrollBarNoShaftOrThumb,
	/** The colour of scroll bar buttons. */
	EColorScrollButtonIcon,
	/** The colour of scroll bar buttons when pressed. */
	EColorScrollButtonIconPressed,
	/** The colour of scroll bar buttons when dimmed. */
	EColorScrollButtonIconDimmed,
	/** The colour of a scroll bar thumb's background. */
	EColorScrollButtonThumbBackground,
	/** The colour of a scroll bar thumb's background when pressed. */
	EColorScrollButtonThumbBackgroundPressed,
	/** The colour of a scroll bar thumb's background when dimmed. */
	EColorScrollThumbDimmed,
	/** The colour of a scroll bar thumb's edge. */
	EColorScrollThumbEdge,
	// Toolbars
	/** The colour of a toolbar's background. */
	EColorToolbarBackground,
	/** The colour of the text in a toolbar. */
	EColorToolbarText,
	// Status pane
	/** The colour of a status pane's background. */
	EColorStatusPaneBackground,
	/** The colour of the text in a status pane. */
	EColorStatusPaneText,
	// Labels
	/** The colour of the text in a label. */
	EColorLabelText,
	/** The colour of emphasised text in a label. */
	EColorLabelTextEmphasis,
	/** The colour of the text in a label when dimmed. */
	EColorLabelDimmedText,
	/** The colour of the label background when highlighted and dimmed. */
	EColorLabelHighlightPartialEmphasis,
	/** The colour of the label background when highlighted. */
	EColorLabelHighlightFullEmphasis,
	/** The number of logical colours */
	EColorNumberOfLogicalColors
	};

class RReadStream;
class RWriteStream;
class CColorArray;

// not available before Release 005

class CColorList : public CBase
/** A palette that maps logical colours (TLogicalColor) to physical (TRgb) values. It 
also supports independent sections for applications: a section is identified by an 
application UID, and the mappings are held as a colour array (CColorArray). 

A colour list also supports mapping for both four-grey and 256-colour schemes; the 
256-colour scheme will be used and will look good if the screen mode supports 16 or 
more colours. Otherwise, the four-grey scheme will be used. 

@publishedAll 
@released */
	{
public:
	IMPORT_C static CColorList* NewL(CArrayFix<TRgb>* aColors);
	IMPORT_C ~CColorList();
	// Accessors
	IMPORT_C TRgb Color(TLogicalColor aColor) const;
	IMPORT_C TInt Count() const;
	IMPORT_C TRgb Color(TUid aApp,TInt aColor) const;
	IMPORT_C CColorArray* ColorArray(TUid aApp) const;
	IMPORT_C TBool ContainsColorArray(TUid aApp) const;
	// Manipulators
	IMPORT_C void SetColor(TLogicalColor aLogicalColor,TRgb aColor);
	IMPORT_C void AddColorArrayL(TUid aApp,CColorArray* aArray); // takes ownership
	IMPORT_C void DeleteColorArray(TUid aApp);
public:
	IMPORT_C static CColorList* NewLC();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void MergeL(const CColorList& aList);
private:
	CColorList(CArrayFix<TRgb>* aColors);
	TInt Find(TUid aApp) const;
private:
	class TAppColorList
		{
	public:
		inline TAppColorList(TUid aApp,CColorArray* aColorArray);
	public:
		TUid iApp;
		CColorArray* iColorArray;
		};
private:
	CArrayFix<TRgb>* iEikColors;
	CArrayFix<TAppColorList>* iAppColors;
	};

// not available before Release 005

class CColorArray : public CBase
/** A dynamic array of mappings between logical and physical colours (TRgb values).

@publishedAll 
@released */
	{
public:
	IMPORT_C static CColorArray* NewL();
	IMPORT_C static CColorArray* NewLC();
	IMPORT_C ~CColorArray();
	IMPORT_C TRgb Color(TInt aLogicalColor) const;
	IMPORT_C void SetColor(TInt aLogicalColor,TRgb aColor);
	IMPORT_C TBool Contains(TInt aLogicalColor) const;
	IMPORT_C TInt Count() const;
	IMPORT_C void Reset();
	IMPORT_C void AddL(TInt aLogicalColor,TRgb aColor);
	IMPORT_C void Remove(TInt aLogicalColor);
public:
	static CColorArray* NewLC(const CColorArray& aArray);
public:
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:
	CColorArray();
	void ConstructL();
	TInt Find(TInt aLogicalColor) const;
private:
	class TColor
		{
	public:
		inline TColor();
		inline TColor(TRgb aColor,TInt aLogicalColor);
	public:
		void InternalizeL(RReadStream& aStream);
		void ExternalizeL(RWriteStream& aStream) const;
	public:
		TRgb iColor;
		TInt iLogicalColor;
		};
	CArrayFixFlat<TColor> iColors;
	};

#endif
