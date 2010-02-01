/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
*  Special character table control that is shown
*  inside special character table dialog.
*
*
*/


#ifndef AKNCHARMAP_H
#define AKNCHARMAP_H

#include <coecntrl.h>
#include <AknUtils.h>
#include <AknPictographDrawerInterface.h>

// Maximum number of rows that fits visible to the screen.
const TInt KSCTMaxVisibleRowsAPAC = 7;
const TInt KSCTMaxVisibleRowsELAF = 8;
#define KSCTMaxVisibleRows ( (AknLayoutUtils::Variant()==EApacVariant) ? KSCTMaxVisibleRowsAPAC : KSCTMaxVisibleRowsELAF )

const TInt KCharMapCaseMask = 0xFF;

enum TAknCharMapPictoMode
    {
    EAknCharMapPictoNoUse       = 0x00010000, 
    EAknCharMapPictoFirst       = 0x00020000
    };

enum TAknCharMapEmotionMode
    {
    EAknCharMapEmotionNoUse     = 0x00040000, 
    EAknCharMapEmotionUse       = 0x00080000, 
    EAknCharMapEmotionFirst     = 0x00100000
    };

enum TAknChaMapTableCase
    {
    EAknCharMapTableNull = -1,
    EAknCharMapTableSpecialChar = 0,
    EAknCharMapTablePicto,
    EAknCharMapTablePicto2
    };

enum TAknChaMapStatusChanged
    {
    EAknCharNoSelection = -1,
    EAknCharSelectedSpecialCharacter = 0,
    EAknCharChangedCategory,
    EAknCharSelectedNextTableButton,
    EAknCharSelectedTableExitButton
    };


class CEikScrollBarFrame;
class CAknPictographInterface;
class CAknCharMapHistory;
class CAknCharMapExtension;
class MAknSctFocusHandler;
/**
 * Special character table control for AVKON
 *
 */
class CAknCharMap : public CCoeControl, public MAknPictographAnimatorCallBack, public MEikScrollBarObserver
    {

    friend class CAknCharMapExtension;

public: 
    
    /** 
    * Character table constructor
    *
    */
    IMPORT_C CAknCharMap();
    
    /** 
    * Character table destructor
    *
    */
    IMPORT_C ~CAknCharMap();
    
    /** 
    * Character table resource constructor.
    * 
    * @param aReader Special character table resource: SPECIAL_CHAR_TABLE
    * 
    */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

    /**
    * Number of rows in special character map.
    *
    * @return Number of rows in special character map.
    *
    */
    IMPORT_C TInt HeightInRows();
    
    /**
    * Set the emotion mode for the special character table.
    *
    * @param aMode The emotion mode for the special character table 
    *      (EAknCharMapEmotionUse, EAknCharMapEmotionFirst, EAknCharMapEmotionNoUse).
    */
    IMPORT_C void SetEmotionModeL(TAknCharMapEmotionMode aMode);
    
    /**
    * Set the case for the special character table.
    *
    * @param aCharCase The case for the special character table 
    *      (EAknSCTLowerCase or EAknSCTUpperCase).
    */
    IMPORT_C void SetCharacterCaseL(TInt aCharCase);

    /**
    * Sets reference to the buffer where selected special character(s) are put.
    *
    * @param aSpecialChars Reference to the buffer where selected special characters are put.
    */
    IMPORT_C void SetBuffer(TDes& aSpecialChars);
    
    /**
    * Reads special characters from the resource. 
    *
    * @param aReader Special character table resource: SPECIAL_CHAR_TABLE
    *
    */
    void ReadCharSetFromResourceL(TResourceReader& aReader);
    
    /**
    * Reads special characters from the resource and add recent characters. 
    *
    * @param aReader Special character table resource: SPECIAL_CHAR_TABLE
    *
    */
    void ReadAndAddCharSetFromResourceL(TResourceReader& aReader);

public: // from CCoeControl
    IMPORT_C TSize MinimumSize();
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode);
    IMPORT_C TCoeInputCapabilities InputCapabilities() const;
    IMPORT_C virtual void ActivateL();

protected: // from CCoeControl
    IMPORT_C void SizeChanged();
    IMPORT_C void HandleResourceChange(TInt aType);
    IMPORT_C TInt CountComponentControls() const;
    IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;

public: // new functions
    void SetPictoMode(TAknCharMapPictoMode aMode);
    void SetCaseTableL(const RArray<TInt> & aCase);
    TInt LengthOfRecentChar();

private: // from MAknPictographDrawerCallBack
    void DrawPictographArea();

public: // new methods
    const TDesC* LowerCaseCharacters() const;
    const TDesC* UpperCaseCharacters() const;
    const TDesC* NumericCharacters() const;
    void CopyCharactersL( const CAknCharMap& aCharMap ); 

    TBool SwitchTablesL( TBool& aLayoutChanged );
    TInt PageCount() const;
    TInt CurrentPage() const;
    TInt NextPageL();

    void CreateOffscreenBackgroundL();
    void DrawOffscreenBackgroundIfRequired() const;
    void SetTitleL(TPtrC aTitle);
    const TDesC* Title() const;
    void DoLayout();
    
    TBool HasPictoInterface() const;
    
    /**
    * Get the case for the special character table.
    *
    * @return aCharCase The case for the special character table 
    *      (EAknSCTLowerCase, EAknSCTQwerty or EAknSCTUpperCase).
    */
    TInt CharacterCase();

    void DisableRecentCharsRow();

protected:
    void Draw(const TRect& aRect) const;

    /**
    * Draw the special char inside the grid cell.
    * @param aGC, the graphic context;
    * @param aSctPosition, the rectangle inside the cell (exclude the cell edge).
    * @param aCharIndex, the index of the special char, used to determin
    *        whether the char is recent char or not.
    * @param aHighlighted, the flag to indicate if the char is highlighted.
    * @param aDrawBackground, the flag to indicate if it is neccessary to brush
    *        the back ground inside the cell.
    */
    void DrawItem(
        CWindowGc& aGc,
        const TRect& aSctPosition,
        TInt aCharIndex,
        TBool aHighlighted,
        TBool aDrawBackground ) const;

    /**
    * Draw the shade background inside the cell.
    * @param aGC, the graphic context;
    * @param aItemRect, the rectangle inside the cell (exclude the cell edge).
    * @param aCharIndex, the index of the special char, used to determin
    *        whether the char is recent char or not.
    * @param aHighlighted, the flag to indicate if the char is highlighted.
    * @param aDrawBackground, the flag to indicate if it is neccessary to brush
    *        the back ground inside the cell.
    */
    void DrawItemShade( CWindowGc& aGc, 
        const TRect& aItemRect, TInt aCharIndex,
        TBool aHighlighted,
        TBool aDrawBackground ) const;

    /**
    * Set the pen size, color, etc. before drawing the frame of a special char 
    * item. 
    * Note: The frame is inside the cell.
    *
    * @param aGC, the graphic context;
    */
    void SetItemFrameStyle( CWindowGc& aGc) const;

    /**
    * Draw the frame of a special char item.
    * Note: The frame is inside the cell.
    *
    * @param aGC, the graphic context;
    * @param aItemRect, the rectangle inside the cell (exclude the cell edge).
    * @param aCharIndex, the index of the special char, used to determin
    *        whether the char is recent char or not.
    * @param aHighlighted, the flag to indicate if the char is highlighted.
    * @param aDrawBackground, the flag to indicate if it is neccessary to brush
    *        the back ground inside the cell.
    */
    void DrawItemFrame( CWindowGc& aGc, 
        const TRect& aItemRect, TInt aCharIndex,
        TBool aHighlighted,
        TBool aDrawBackground ) const;

    /**
    * Set the pen size, color, etc. before drawing the thick frame of all 
    * recent chars. 
    * Note: The frame is always on the top of all SCT grid, or inside the
    * MenuSct.
    *
    * @param aGC, the graphic context;
    */
    void SetRecentCharFrameStyle( CWindowGc& aGc) const;

    /**
    * Draw the frame of all recent chars.
    * Note: The frame is always on the top of all SCT grid, or inside the
    * MenuSct.
    *
    * @param aGC, the graphic context;
    */
    void DrawRecentCharFrame( CWindowGc& aGc) const;

    /**
    * Set the pen size, color, etc. before drawing the SCT grid. 
    *
    * @param aGC, the graphic context;
    */
    void SetGridStyle( CWindowGc& aGc) const;

    /**
    * Draw the SCT grid. This is a better method. It will iterate
    * all visible special chars, and draw a simple rect around it.
    *
    * @param aGC, the graphic context;
    */
    void DrawGrid( CWindowGc& aGc) const;

    /**
    * Get How many special chars are visible in the current page,
    * or in the current MenuSct frame.
    * @return the number of the visible special chars.
    */
    TInt NumberOfVisibleChars() const;

    void DrawCursor() const;
    void MoveCursorL(TInt aX, TInt aY);

    void DrawCell( TInt aCursorPos, TBool aHighLighted ) const;
    TRect CursorRect( TInt aCursorPos, TInt aCharIndex ) const;

    void UpdateScrollIndicatorL();

    void DrawPicto(
        CWindowGc& aGc,
        const TRect& aSctPosition,
        TInt aCharIndex,
        TBool aHighlighted,
        TBool aDrawBackground ) const;

    HBufC* AppendTextL(HBufC* aChars, HBufC* aText);
    TInt SwitchAnotherTableL(TInt aIncrement);

    void CountMaxColumnsAndCellSizes();

    HBufC* CharsFromCase(TInt aCharCase) const;
    TInt PageCountFromChars(TDesC& aChar) const;
    TInt VisibleRows() const;

    void CreatePictoCharL();
    void AppendRecentCharL();
    HBufC* InsertSwitchCharAndHistoryToCharsBufL(HBufC* aCharsBuf, TChar aSwitchChar, const TDesC& aHistory);
    TBool IsRecentChar(TInt aIndex = 0) const;
    void SaveRecentDataL(TChar aChar);
    CAknCharMapExtension* Extension() const;

    void UpdateHeadingPane( TBool aUpdateTitle );

public:
    /**
     * This function handles pointer events directed at the charmapdialog.
     * @param aPointerEvent The pointer event directed at the charmapdialog.
     */
    IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    
    /**
    * From CCoeControl        
    * Sets iCharmapObserver to be as observer
    * @param aObserver pointer to observer
    */
    IMPORT_C void SetObserver( MCoeControlObserver* aObserver  );
 
private: //from CCoeContrl
    void Reserved_1();
    void Reserved_2();
    
public:
     /**
     * This function handles pointer events directed at the charmapdialog.
     * @param aScrollBar The scrollbar to be observed.
     * @param aEventType The incomming event type so that correct functionality can be done.
     */
    void HandleScrollEventL(CEikScrollBar* aScrollBar, TEikScrollEvent aEventType);
    
    /** 
    * Constructs a special character row for edit menu.
    * 
    * @since 3.1
    */
    IMPORT_C void ConstructMenuSctRowL();
    
    /** 
    * Sets the rect which SCT should use to draw itself.
    * @param aRect The used rectangle.
    * @since 3.1
    */
    IMPORT_C void SetMenuSctRect( const TRect& aRect );


    /** 
    * Constructs a special character row for edit menu. Uses the given resource
    * of a dialog to construct the special character table. The recently used characters 
    * are only from the selected special character table. 
    * 
    * @since S60 3.1
    *
    * @param aResourceId    The resource id of the special character dialog which 
    *                       is used with editor.
    */
    IMPORT_C void ConstructMenuSctRowL(TInt aResourceId);
    
    /** 
    * Constructs a special character row for edit menu. Uses the given resource
    * of a dialog to construct the special character table. The recently used characters 
    * are only from the selected special character table. 
    * 
    * @since S60 3.2
    *
    * @param aResourceId    The resource id of the special character dialog which
    *                       is used with editor.
    */
    IMPORT_C void ConstructMenuSctRowFromDialogL(TInt aResourceId);

    /**
    * Highlight the row of recent used character according to argument.
    * @param aHighlight     the flag to indicate wheather the row is highlighted
    *                       or not.
    * @since S60 3.1
    */
    IMPORT_C void HighlightSctRow(TBool aHighlight);
public:
    void SetStatusChanged(const TInt aStatusChanged);
    TInt StatusChanged();
    TInt CurrentCategory();
    TBool ChangeCategoryL(const TInt aCategory, TBool& aLayoutChanged );
    TInt Category();
    TBool IsSupportCategoryButtonUi() const;
    TBool IsJapaneseSctUi() const;
    const TDesC* TitleWithSelectingSpecialChar();

private:
    void ChangeFocusSct(TBool aFocusOn);
    void CreateTitleWithSelectingSpecialCharL(const TDesC* aTitle);

private:
    void DoHandleResourceChangeL(TInt aType);                                          
    void EnableCategoryButtonsL();
    void DisableCategoryButtonsL();    
    void EnableNavigationButtonsL();
    void DisableNavigationButtonsL();             
    void EnableCategoryInputFieldL();
    void DisableCategoryInputFieldL();   
                
public:                    
    TAknChaMapTableCase NextTableCase() const;
    CCoeControl* FocusedControl();
    MAknSctFocusHandler* FocusHandler();    
    TBool EnterControl(TInt aX, TInt aY);    
    void MoveFocus(TInt aX, TInt aY);              
    TBool LeaveControl();             
    TBool ExitWithKey(TInt aKeycode);    
    void UpdateInputFieldL(); 
    void RefreshNaviPageL();  
    TInt TableCount() const;
    TInt PrevPageL();    
    TInt RowMin(TInt aRow) const;
    TInt RowMax(TInt aRow) const;
    TInt ColMin(TInt aCol) const;
    TInt ColMax(TInt aCol) const;    
    TInt MaxCols() const;
    TBool TakeFocus();
    void ShowFocus();
    TPoint CursorPos();

private:
    void HandleFocusStatusChanged(TBool aIsFocused=ETrue);
    TBool EmotionsAreAllReadyToDraw(TInt aIndex, TInt aCount) const;
    void GetFocusSctName(TChar& aChar, TDes& aName) const;
    TBool HaveBufferToAppendFocusSct() const;
    TBool AppendFocusSctToDestinationBufferL();
    TBool SwitchSctAndEmotionL();

private:
    TBool iIsMirrored;
    const CFont* iFont;     // drawing text font
    
    TInt iGridItemWidth;    // grid cell width
    TInt iGridItemHeight;   // grid cell height

    TPoint iOffset;
    TPoint iGridTopLeft;
    
    TInt iRows;             // total rows of all chars
    TInt iMaxColumns;       // column count in current gird
    TInt iFirstVisibleRow;  // first row index in current page window

    TPoint iCursorPos;
    TPoint iOldCursorPos;
    mutable TBool iDrawnBefore;

    // shown table case
    TAknChaMapTableCase iChaMapTableCase;
    TInt iSpecialCharCase;
    
    // des buffer
    TDes* iFetcherCharsBuffer;
    
    // all the data buffers
    HBufC* iChars;
    HBufC* iCharsBufferFull;
    HBufC* iCharsBufferHalf;
    HBufC* iCharsBufferLower;
    HBufC* iCharsBufferUpper;
    HBufC* iCharsBufferNumeric;
    HBufC* iPictographsBuffer;
    HBufC* iPictographsBuffer2;

    CEikScrollBarFrame* iSBFrame;

    CAknPictographInterface* iPictoInterface;
    TBool iAnimated;

    CFbsBitmap* iOffscreenBg;
    CFbsBitmapDevice* iBitmapDevice;
    CFbsBitGc* iBitmapGc;
    TBool iHasBitmapBackground;  // Keeped only for Binary Compatibility  
    mutable TBool iOffscreenBgDrawn;
    
    // all kind of titles
    HBufC* iTitleDefault;
    HBufC* iTitleFull;
    HBufC* iTitleHalf;
    HBufC* iTitlePicto;
    HBufC* iTitlePicto2;

    TInt iCaseIndex;
    
    // cases info
    RArray<TInt>* iShowCasesRef;
    RArray<TInt> iSpecialCharCases;
    RArray<TInt> iPictographCases;
    
    // pages info
    RArray<TInt>* iShowPagesRef;
    RArray<TInt> iSpecialCharPages;
    RArray<TInt> iPictographPages;

    TAknPictographHeight iCurrentPictographHeight;
    CAknCharMapExtension* iExtension;
    CAknCharMapHistory* iCharMapHistory;
    
    TBool iSetRecentSct;        // ETrue is set when setting recent used characters to SCT
    TBool iSetRecentPic;        // ETrue is set when setting recent used characters to Picto
    TInt iStatusChanged;
    };

#endif // __AKNCHARMAP_H__
