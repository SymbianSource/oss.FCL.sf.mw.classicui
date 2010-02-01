/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef AKNPHEDVIEW_H
#define AKNPHEDVIEW_H

// INCLUDE FILES

#include "AknPhedModel.h"
#include <gdi.h>
#include <w32std.h>
#include "AknUtils.h"

// FORWARD DECLARATIONS

class CAknPhoneNumberEditor;
class MAknsSkinInstance;
class MAknsControlContext;

//
// TAknPhedViewLine
//
// Encapsulates the concept of a display line which exists as one of a set of lines.
// Handles text, cursor and truncation positioning and drawing.
// Note: position indexing is from RHS, since this class shows right justified text.
//
class TAknPhedViewLine
    {
    public:
        TAknPhedViewLine();
        
        // structural manipulation
        inline void SetModel( CAknPhedModel* aData );
        inline void SetLeftLine( TAknPhedViewLine* iLeft );
        inline void SetRightLine( TAknPhedViewLine* iRight );
        void SetFormat( const CFont* aFont, const TRect& aRect, TInt aBaseline );
        
        // Line limits manipulation
        inline TInt LeftPos() const;
        inline TInt RightPos() const;
        inline TBool LineContains( TInt aPos ) const;
        inline TInt LineWidth() const;
        void SetLeftPos( TInt aPos );
        void SetRightPos( TInt aPos );
        
        // Event handlers
        TBool HandleTextChange( TInt aStart, TInt aEnd );
        TBool HandleCursorChange( TInt aCursor );
        void HandleSelectionChange( TInt aLeft, TInt aRight );
        
        // Utility functions
        inline TBool InRange( TInt aPos, TInt aLeft, TInt aRight ) const;
        TInt CountChars( const TDesC& aDes, TBool aStartTruncated, 
            TBool aAllowEndTruncation, TInt aCharsToEnd ) const;
        
        // Truncation functions
        void SetTruncation( const TDesC& aTruncation );
        inline TInt TruncationWidth() const;
        inline TBool IsTruncated() const;
        inline TBool IsTruncatedLeft() const;
        inline TBool IsTruncatedRight() const;
        
        // Selection functions
        TBool HasSelection() const;
        TInt SelectionStart() const;
        TInt SelectionEnd() const;
        
        // Position translation functions
        TInt CursorPosToXPos( TInt aCursorPos ) const;
        TInt XPosToCursorPos( TInt aXPos ) const;
        
        // Positioning functions
        inline TInt Baseline() const;
        TPoint CursorPosition() const;
        
        // Text access functions
        TPtrC Text() const;
        TPtrC ReverseText() const;
        TPtrC MaxText() const;
        TPtrC MaxReverseText() const;
        
        // Drawing
        inline void SetRedrawRequired();
        inline TBool IsRedrawRequired() const;
        void Draw( CWindowGc& aGc, MAknsSkinInstance* aSkin, 
            MAknsControlContext* aContext, const CCoeControl* aControl ) const;
        void DrawText( CGraphicsContext& aGc, const TDesC& aText, TInt aBaseline,
            TRect& aRect ) const;
        
        TRect Rect() const;
        
    private:
        //
        // Measuring and drawing routines capable of implementing character translation. 
        //(for ArabicIndic number support)
        //
        
        /**
        * This routine is used to Draw text with settings-dependent numerals.
        * It is used as a replacement for CGraphicsContext::DrawText( const TDesC& aText,
        * TInt aBaseline, TRect& aRect, CGraphicsContext:TAlign aAlignment);
        * except that numeric digits will be replaced with the correct digits according 
        * to device settings.
        * 
        * The buffer passed to this routine must be <= length than the buffers
        * present in CAknPhedModel.
        */
        void DrawTextWithTranslation( CGraphicsContext& aGc, const TDesC& aText, 
            TInt aBaseline, TRect& aRect ) const;
        
        /**
        * This routine is used to count the numbers of unicode characters that fit in the given width
        * It is used as a replacement for CFont::TextCount( const TDesC& aText, TInt aWidth );
        * except that numeric digits will be replaced before measurement with 
        * the correct digits according to device settings.
        * 
        * The buffer passed to this routine must be <= length than the 
        * buffers present in CAknPhedModel.
        */
        TInt TextCountWithTranslation( const TDesC& aText, TInt aWidth ) const;
        
        /**
        * This routine is used to measure the width of the text when rendered.
        * It is used as a replacement for CFont::TextWidthInPixels( const TDesC& aText );
        * except that numeric digits will be replaced before measurement with 
        * the correct digits according to device settings.
        * 
        * The buffer passed to this routine must be <= length than the buffers 
        * present in CAknPhedModel.
        */
        TInt TextWidthInPixelsWithTranslation( const TDesC& aText ) const;
        
        void DrawHighlightText( CGraphicsContext& aGc, TBool aUseSkin ) const;
        TPtr TranslatedText( const TDesC& aText ) const;
        
    private:
        // None of these pointer data members own the objects pointed to.
        CAknPhedModel* iModel;
        TAknPhedDataMirror iMirror;
        const CFont* iFont;
        TRect iRect;
        TInt iBaseline;
        TPtrC iTruncation;
        TInt iTruncationWidth;
        
        TAknPhedViewLine* iLeftLine;
        TAknPhedViewLine* iRightLine;
        
        TInt iCursor;
        TInt iLeftPos;
        TInt iRightPos;
        
        mutable TBool iRedraw;
        
    private: // for testing
        friend class CTestPhedView;
    };
    
typedef CArrayFixFlat<TAknPhedViewLine> CAknPhedViewLineArray;
    
    
    
    //
    // CAknPhedView
    //
    // Encapsulates the logical and positional relationships between display lines.
    // Handles "vertical" operations and logic.
    // Note: position indexing is from bottom-RHS, since this class 
    // shows bottom-right justified text.
    //
NONSHARABLE_CLASS( CAknPhedView ) : public CBase, public MPhedDataObserver
    {
public:
    enum
        {
        KNoPos = -1
        };
    
public:
    CAknPhedView( CAknPhedModel* aModel );
    ~CAknPhedView();
    void ConstructL( TInt aMaxLines, const TDesC& aTruncation );
    void SetWindows( RWindowGroup* aWg, RWindowBase* aWindow );
    void SetChangeReceiver( CAknPhoneNumberEditor* aChangeReceiver );
    
    // Format manipulation functions
    TBool IsTruncated() const;
    void SetFormat( TInt aLines, const CFont* aFont, const TRect& aRect, 
        TInt aBottomBaselineOffset, TInt aBaselineSeparation );
    TRect Rect() const;
    
    // Drawing and cursor graphics
    void EnableCursor();
    void DisableCursor();
    void Draw( CWindowGc& aGc, TBool aRedrawAll, const CCoeControl* aControl ) const;
    
    // vertical navigation functions
    TBool CursorUp( TInt aTargetCursorPos );
    TBool CursorDown( TInt aTargetCursorPos );
    TBool SelectUp( TInt aTargetCursorPos );
    TBool SelectDown( TInt aTargetCursorPos );
    TPoint CursorPosition() const;
    TInt CursorLine() const;
    inline const CAknPhedViewLineArray* LineArray();
    
    /**
    * Calculate cursor position by pointer position.
    * 
    * @param aPt, the pointer position.     
    * @return cursor position for CAknPhedModel.
    */
    TInt GetCursorPosByPoint( const TPoint& aPt );
    
private:
    // Event handling and reformatting
    void HandlePhedDataEvent( const TAknPhedDataEvent& aEvent, 
        CAknPhedModel* aPhedData );
    void FullFormat();
    void TextChangeFormat( TInt aStart, TInt aEnd );
    void CursorChangeFormat( TInt aCursor );
    void SelectionChangeFormat( TInt aLeft, TInt aRight );
    void SetLeftPos( TInt aPos );
    
    // cursor positioning and drawing
    void MoveCursorToLine( TInt aLineNo, TInt aTargetCursorPos );
    void UpdateCursor();
    void SetCursorFormat( const CFont* aFont );
    
    // Setting up the logical relationship between lines
    void SetConnectingLines( TAknPhedViewLine& aLine, TInt aLineNum );
    
private:
    // owned pointer member
    CAknPhedViewLineArray* iLines;
    HBufC* iTruncation;
    
    // non-owned pointer members
    CAknPhedModel* iModel;
    TAknPhedDataMirror iMirror;
    
    TInt iNumLines;
    TInt iCursorLine;
    const CFont* iFont;
    TRect iRect;
    
    TTextCursor iCursor;
    TBool iCursorEnabled;
    RWindowGroup* iWg;
    RWindowBase* iWindow;
    
    CAknPhoneNumberEditor* iChangeReceiver;
    
private: // for testing
    friend class CTestPhedView;
    };


inline void TAknPhedViewLine::SetModel( CAknPhedModel* aModel )
    { iModel = aModel; iMirror.SetPhedModel( iModel ); }

inline void TAknPhedViewLine::SetLeftLine( TAknPhedViewLine* iLeft )
    { iLeftLine = iLeft; }

inline void TAknPhedViewLine::SetRightLine( TAknPhedViewLine* iRight )
    { iRightLine = iRight; }

inline TInt TAknPhedViewLine::LeftPos() const
    { return iLeftPos; }

inline TInt TAknPhedViewLine::RightPos() const
    { return iRightPos; }

inline TBool TAknPhedViewLine::LineContains( TInt aPos ) const
    { return InRange(aPos, iLeftPos, iRightPos); }

inline TBool TAknPhedViewLine::InRange( TInt aPos, TInt aLeft, TInt aRight ) const
    { return aLeft >= aPos && aPos >= aRight; }

inline TInt TAknPhedViewLine::TruncationWidth() const
    { return iTruncationWidth; }

inline TBool TAknPhedViewLine::IsTruncated() const
    { return IsTruncatedLeft() || IsTruncatedRight(); }

inline TBool TAknPhedViewLine::IsTruncatedLeft() const
    { return !iLeftLine && iLeftPos < iModel->Length(); }

inline TBool TAknPhedViewLine::IsTruncatedRight() const
    { return !iRightLine && iRightPos > 0; }

inline TInt TAknPhedViewLine::LineWidth() const
    { return iLeftPos - iRightPos; }

inline void TAknPhedViewLine::SetRedrawRequired()
    { iRedraw = ETrue; }

inline TBool TAknPhedViewLine::IsRedrawRequired() const
    { return iRedraw; }

inline TInt TAknPhedViewLine::Baseline() const
    { return iBaseline; }

inline TPtrC TAknPhedViewLine::MaxText() const
    { return iModel->Text(iMirror.Mirror(iLeftPos), iModel->Length() - 1); }

inline TPtrC TAknPhedViewLine::MaxReverseText() const
    { return iModel->ReverseText(iRightPos, iModel->Length() - 1); }

inline TPtrC TAknPhedViewLine::Text() const
    { return MaxText().Left(LineWidth()); }

inline TPtrC TAknPhedViewLine::ReverseText() const
    { return MaxReverseText().Left(LineWidth()); }

inline const CAknPhedViewLineArray* CAknPhedView::LineArray()
    {
    return iLines;
    }

#endif
