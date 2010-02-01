/*
* Copyright (c) 2002 - 2008 Nokia Corporation and/or its subsidiary(-ies).
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

#include "AknPhedView.h"
#include "AknPhoneNumberEditor.h"

#include <AknsDrawUtils.h>

#include <gfxtranseffect/gfxtranseffect.h>
#include <akntransitionutils.h>
#include <avkondomainpskeys.h>
#include <e32property.h>

// Helper class that monitor redirection changes
class CRedirectionListener : public CBase, public MAknTransitionUtilsObserver
    {
private:
    TInt AknTransitionCallback( TInt aEvent, TInt aState,
                                const TDesC8* /*aParams*/ )
        {
        if ( aEvent == CAknTransitionUtils::EEventWsBufferRedirection )
            {
            iRedirected = aState;
            if ( iCursorEnabled )
                {
                if ( iRedirected )
                    {
                    if ( iWg && iCursorStatus )
                        {
                        iWg->CancelTextCursor();
                        }
                    iCursorStatus = EFalse;
                    }
                else
                    {
                    iOwner.EnableCursor();
                    }
                }
            }
        return 0;
        }

public:
    CRedirectionListener( CAknPhedView& aOwner ) : iOwner( aOwner )
        {
        iRedirected = 0;
        TInt serverrunning;
        TInt ret=RProperty::Get( KPSUidAvkonDomain, KAknTfxServerStatus,
                 serverrunning );
        if(KErrNone == ret && ETfxSrvRunning == serverrunning) 
	        {
	        RProperty::Get( KPSUidAvkonDomain, KAknTfxServerRedirectionStatus,
	                        iRedirected );
	        iRedirected &= ETfxScreenRedirected;
	        }
        }
    inline void EnableCursor()
        {
        iCursorEnabled = ETrue;
        }
    void DisableCursor()
        {
        if ( iWg && iCursorStatus )
            {
            iWg->CancelTextCursor();
            }
        iCursorEnabled = EFalse;
        iCursorStatus = EFalse;
        }
    void UpdateCursor( const TTextCursor& aCursor )
        {
        TInt redirected=0; // init the value
        //judge the server status, if server is not running, it is no need to get redirect value.
        TInt serverrunning;
        TInt ret=RProperty::Get( KPSUidAvkonDomain, KAknTfxServerStatus,
                 serverrunning );

        if(KErrNone == ret && ETfxSrvRunning == serverrunning) 
            {
            ret=RProperty::Get( KPSUidAvkonDomain, KAknTfxServerRedirectionStatus,
                        redirected );

            if( KErrNone != ret)
                redirected = 0;
 
            redirected &= ETfxScreenRedirected;
            if ( redirected != iRedirected && redirected )
                {
                AknTransitionCallback( CAknTransitionUtils::EEventWsBufferRedirection,
                                       1, NULL );
                return;
                }
            }

        iRedirected = redirected;
        
        if ( iCursorEnabled && iWg && iWindow && !iRedirected )
            {
            iWg->SetTextCursor( *iWindow,
                                iOwner.CursorPosition() + TPoint( -1, 0 ),
                                aCursor );
            iCursorStatus = ETrue;
            }
        }
        
    inline void SetWindows( RWindowGroup* aWg, RWindowBase* aWindow )
        {
        iWg = aWg;
        iWindow = aWindow;
        }
        
private:
    TBool iRedirected;
    TBool iCursorEnabled;
    TBool iCursorStatus;
    RWindowGroup* iWg;
    RWindowBase* iWindow;
    CAknPhedView& iOwner;
    };

enum TAknPhedViewPanic
    {
    EFormatNullLines,
    EFormatTooManyLines,
    EFormatTooFewLines,
    EEventNullLines,
    ELineNoCursor
    };

void PhedViewPanic( TAknPhedViewPanic aPanic )
    {
    _LIT( KAknPhedView,"AknPhedView" );
    User::Panic( KAknPhedView, aPanic );
    }



TAknPhedViewLine::TAknPhedViewLine()
    {
    Mem::FillZ( this, sizeof( *this ) );
    iCursor = CAknPhedView::KNoPos;
    SetRedrawRequired();
    }

void TAknPhedViewLine::SetFormat( const CFont* aFont, const TRect& aRect, TInt aBaseline )
    {
    iFont = aFont;
    iRect = aRect;
    SetTruncation( iTruncation );
    iBaseline = aBaseline;
    }
    
TRect TAknPhedViewLine::Rect() const
    {
    return iRect;
    }

void TAknPhedViewLine::SetLeftPos( TInt aPos )
    {
    SetRedrawRequired();
    iLeftPos = aPos;

    if ( InRange(aPos, iModel->Length(), 0 ) )
        {
        if( iLeftPos > 0 && iLeftPos < iModel->Length() && iModel->Language() )
            {
            if ( iModel->ReverseText( iLeftPos ).Length() == 
                 iModel->ReverseText( iLeftPos - 1 ).Length() && !iLeftLine ) 
                {
                iLeftPos++; 
                }
            else if ( iModel->ReverseText( iLeftPos ).Length() == 
                      iModel->ReverseText( iLeftPos - 1 ).Length() && iLeftLine ) 
                {
                iLeftPos--; 
                }
            }
        // count characters that will fit to the right of this new left position
        iRightPos = iLeftPos - CountChars( MaxText(), IsTruncatedLeft(), 
                    !iRightLine, iLeftPos );
        if( iRightPos > 0 && iRightPos < iModel->Length() && iModel->Language() )
            {
            if ( iModel->ReverseText( iRightPos ).Length() == 
                 iModel->ReverseText( iRightPos + 1 ).Length() ) 
                {
                iRightPos++; 
                }
            }
        
        }
    else
        {
        iRightPos = aPos;
        }

    // propogate change of left hand side to right hand neighbor
    if ( iRightLine )
        iRightLine->SetLeftPos( iRightPos );
    }

void TAknPhedViewLine::SetRightPos( TInt aPos )
    {
    SetRedrawRequired();
    TInt nLength = iModel->Length();
    
    iRightPos = aPos;
 
    if ( InRange( aPos, nLength, 0 ) )
        {
        if( iRightPos > 0 && iRightPos < iModel->Length() && iModel->Language() )
            {
            
            if ( iModel->ReverseText( iRightPos ).Length() == 
                 iModel->ReverseText( iRightPos +1 ).Length() ) 
                {
                iRightPos++; 
                }
            }
                                  
        // count characters that will fit to the left of this new right position
        iLeftPos = iRightPos + CountChars( MaxReverseText(), 
                                           IsTruncatedRight(), 
                                           !iLeftLine,
                                           iMirror.Mirror( iRightPos ) );
        if( iLeftPos > 0 && iLeftPos < iModel->Length() && iModel->Language() )
            {
            if ( iModel->ReverseText( iLeftPos ).Length() == 
                 iModel->ReverseText( iLeftPos - 1 ).Length() && !iLeftLine ) 
                {
                iLeftPos++; 
                }
            else if ( iModel->ReverseText( iLeftPos ).Length() == 
                      iModel->ReverseText( iLeftPos - 1 ).Length() && iLeftLine ) 
                {
                iLeftPos--; 
                }
            }
        }
    else
        {
        iLeftPos = aPos;
        }

    // propogate change of right hand side to left hand neighbor
    if ( iLeftLine )
        iLeftLine->SetRightPos( iLeftPos );
    }

TBool TAknPhedViewLine::HandleTextChange( TInt aStart, TInt aEnd )
    {
    // If the text change happens somewhere to the right of my LHS, handle it.
    TBool handled = EFalse;
    if ( aStart == aEnd && !iLeftLine && aStart > iLeftPos)
        {
        iLeftPos = aStart;
        }
    if ( !iRightLine && iRightPos > aStart )
        {
        iRightPos = aStart;
        }
    
    TInt chars = CountChars( MaxReverseText(), 
                             IsTruncatedRight(), 
                             !iLeftLine, 
                             iMirror.Mirror( iRightPos ) );
    if( iLeftPos < chars )
        {
        iLeftPos = chars;   
        }
        
    if ( iLeftPos >= aStart || ( !iLeftLine && aStart > iLeftPos ) )
        {
        if( iRightLine )
            {
            iRightLine->SetLeftPos( Max( iRightPos - 1, iRightLine->LeftPos() ) );
            TAknPhedViewLine * firstLine = this;
            while ( firstLine->iRightLine )
                {
                firstLine = firstLine->iRightLine;
                }
            firstLine->SetRightPos( firstLine->RightPos() );
            }
        else
            {
            SetRightPos( iRightPos );
            }
        handled = ETrue;
        }
    else if ( !iLeftLine || iLeftLine->LineWidth() == 0 )
        {
        SetLeftPos( aEnd );        
        }
    return handled;
    }

TBool TAknPhedViewLine::HandleCursorChange( TInt aCursor )
    {
    // cursor rule: cursor goes on bottom most line that can contain it (order is
    // specified by loop order in CAknPhedView::CursorChangeFormat).
    if ( LineContains( aCursor ) )
        {
        iCursor = aCursor;
        return ETrue;
        }
    else
        {
        iCursor = CAknPhedView::KNoPos;
        return EFalse;
        }
    }

void TAknPhedViewLine::HandleSelectionChange( TInt aLeft, TInt aRight )
    {
    if (InRange( iLeftPos, aLeft, aRight ) || LineContains( aLeft ) || aLeft == aRight )
        {
        SetRedrawRequired();
        }
    }

TInt TAknPhedViewLine::CountChars( const TDesC& aDes, 
                                   TBool aStartTruncated, 
                                   TBool aAllowEndTruncation, 
                                   TInt aCharsToEnd) const
    {
    // reduce width for start truncation
    TInt width = iRect.Width();
    if ( aStartTruncated )
        {
        width -= TruncationWidth();
        }

    TInt chars = TextCountWithTranslation( aDes, width );

    if ( aAllowEndTruncation && chars < aCharsToEnd )
        {
        // reduce with for end truncation and recalculate number of chars that will fit
        width -= TruncationWidth();
        chars = TextCountWithTranslation( aDes, width );
        }

    return chars;
    }

void TAknPhedViewLine::SetTruncation( const TDesC& aTruncation )
    {
    SetRedrawRequired();
    iTruncation.Set( aTruncation );
    if ( iFont )
        iTruncationWidth = TextWidthInPixelsWithTranslation( iTruncation );
    }

TBool TAknPhedViewLine::HasSelection() const
    { 
    return SelectionStart() != CAknPhedView::KNoPos; 
    }

TInt TAknPhedViewLine::SelectionStart() const
    {
    TInt start = CAknPhedView::KNoPos;
    if ( iModel->SelectionExists() )
        {
        // This line has selection in it if there is a definite overlap between
        // the line and the selection
        TInt leftMark = iMirror.LeftMark();
        TInt rightMark = iMirror.RightMark();
        if ( InRange( iRightPos, leftMark-1, rightMark ) )
            start = iRightPos;
        else if ( InRange( rightMark, iLeftPos-1, iRightPos ) )
            start = rightMark;
        }
    return start;
    }

TInt TAknPhedViewLine::SelectionEnd() const
    {
    TInt end = CAknPhedView::KNoPos;
    if ( iModel->SelectionExists() )
        {
        // This line has selection in it if there is a definite overlap between
        // the line and the selection
        TInt leftMark = iMirror.LeftMark();
        TInt rightMark = iMirror.RightMark();
        if ( InRange(iLeftPos, leftMark, rightMark+1 ) )
            end = iLeftPos;
        else if ( InRange( leftMark, iLeftPos, iRightPos+1 ) )
            end = leftMark;
        }
    return end;
    }

TInt TAknPhedViewLine::CursorPosToXPos( TInt aCursorPos ) const
    {
    TInt xPos = iRect.iBr.iX;
    if ( IsTruncatedRight() )
        xPos -= TruncationWidth();
    xPos -= TextWidthInPixelsWithTranslation( ReverseText().Left( aCursorPos - iRightPos ) );
    return --xPos;
    }

TInt TAknPhedViewLine::XPosToCursorPos( TInt aXPos ) const
    {
    if ( IsTruncatedRight() )
        aXPos += TruncationWidth();
    TInt cursor = iRightPos + TextCountWithTranslation( ReverseText(), iRect.iBr.iX - aXPos );

    // cursor rule: Cursor can not be beyond the left end of the line
    if ( cursor > iLeftPos )
        cursor = iLeftPos;

    // cursor rule: Cursor should not be on the right end of a line, except the rightmost line
    if ( cursor == iRightPos && cursor < iLeftPos && iRightLine )
        cursor++;

    return cursor;
    }

void TAknPhedViewLine::Draw( CWindowGc& aGc, MAknsSkinInstance* aSkin,
    MAknsControlContext* aContext, const CCoeControl* aControl ) const
    {
    TBool useSkin = AknsDrawUtils::Background( aSkin, aContext, aControl, 
        aGc, iRect );
    // set up colors and styles 
    if( useSkin )
        {        
        aGc.SetBrushStyle( CGraphicsContext::ENullBrush );
        }
    else
        {
        aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        }
    aGc.SetPenStyle( CGraphicsContext::ESolidPen );
    aGc.SetPenColor( KRgbBlack );
    aGc.SetBrushColor( KRgbWhite );

    // draw the text, including truncation
    TRect rect = iRect;
    TInt baseline =  Baseline() - iRect.iTl.iY;
    
    if ( IsTruncatedRight() )
        {
        DrawText( aGc, iTruncation, baseline, rect );
        }    
    if ( IsTruncatedLeft() )
        {
        TInt textWidth = iFont->TextWidthInPixels( Text() );
        TInt truncationWidth = iFont->TextWidthInPixels( iTruncation );

        if ( textWidth + truncationWidth > rect.Width() && Text().Length() >= 1 )    
            {        
            TPtrC text( Text() );
            DrawText(aGc, text.Right( text.Length() - 1 ), baseline, rect );            
            }
        else
            {
            DrawText( aGc, Text(), baseline, rect );
            }
        DrawText( aGc, iTruncation, baseline, rect );        
        }
    else
        {
        DrawText( aGc, Text(), baseline, rect );        
        }
    

    // blank the rest of the line
    if( !useSkin )
        {
        aGc.SetPenStyle( CGraphicsContext::ENullPen );
        aGc.DrawRect( rect );
        }

    // invert any selection by xoring with white
    if ( HasSelection() )
        {
        DrawHighlightText( aGc, useSkin );
        }

    iRedraw = EFalse;
    }

void TAknPhedViewLine::DrawText( CGraphicsContext& aGc, 
                                 const TDesC& aText, 
                                 TInt aBaseline, 
                                 TRect& aRect) const
    {
    TRgb color = KRgbBlack;
    AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), color,
                KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG51 );
    aGc.SetPenColor( color );
    // This function shifts the RHS of aRect left by the width of the text drawn.
    // It temporarily limits the draw rectangle to the text width to prevent flicker.
    TPtr buf( TranslatedText( aText ) );
    
    TInt width = iFont->TextWidthInPixels( buf );
    TInt x = aRect.iTl.iX;
    aRect.iTl.iX = aRect.iBr.iX - width;


    aGc.DrawText( buf, aRect, aBaseline, CGraphicsContext::ERight );
    aRect.iBr.iX -= width;
    aRect.iTl.iX = x;
    }

void TAknPhedViewLine::DrawTextWithTranslation( CGraphicsContext& aGc, 
                                                const TDesC& aText, 
                                                TInt aBaseline, 
                                                TRect& aRect ) const
    {
    TRgb color;
    color = KRgbBlack;
    AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), color,
                KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG51 );
    aGc.SetPenColor( color );
    TPtr buf( TranslatedText( aText ) );
    aGc.DrawText( buf, aRect, aBaseline, CGraphicsContext::ERight );
    }

TInt TAknPhedViewLine::TextCountWithTranslation( const TDesC& aText, TInt aWidth ) const
    {
    TPtr buf( TranslatedText( aText ) );
    return iFont->TextCount( buf, aWidth );
    }

TInt TAknPhedViewLine::TextWidthInPixelsWithTranslation( const TDesC& aText ) const
    {
    TPtr buf( TranslatedText( aText ) );
    return iFont->TextWidthInPixels( buf );
    }

TPoint TAknPhedViewLine::CursorPosition() const
    {
    __ASSERT_DEBUG( iCursor != CAknPhedView::KNoPos, PhedViewPanic( ELineNoCursor ) );
    return TPoint( CursorPosToXPos( iCursor ), Baseline() );
    }

// ---------------------------------------------------------------------------
// TAknPhedViewLine::DrawHighlightText
// ---------------------------------------------------------------------------
// 
void TAknPhedViewLine::DrawHighlightText( CGraphicsContext& aGc, 
    TBool aUseSkin ) const
    {
    TInt baseline =  Baseline() - iRect.iTl.iY;
    TRect rect( iRect );
    rect.iBr.iX = CursorPosToXPos( SelectionStart() );
    rect.iTl.iX = CursorPosToXPos( SelectionEnd() );
    
    TRgb penColor( KRgbWhite );
    TRgb brushColor( KRgbBlue );
    if ( aUseSkin )
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        AknsUtils::GetCachedColor( skin, penColor, KAknsIIDQsnTextColors, 
            EAknsCIQsnTextColorsCG24);
        AknsUtils::GetCachedColor( skin, brushColor, KAknsIIDQsnHighlightColors, 
            EAknsCIQsnHighlightColorsCG2 );
        }
    aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    aGc.SetBrushColor( brushColor );
    aGc.DrawRect( rect );
    aGc.SetPenStyle( CGraphicsContext::ESolidPen );
    aGc.SetPenColor( penColor );
    TInt selStart( iModel->LeftMark() );
    TInt endPos( iModel->Length() - SelectionStart() );
    TInt startPos( iModel->Length() - SelectionEnd() );
    TPtrC text( TranslatedText( iModel->Selection().Mid( startPos - selStart, 
        endPos - startPos ) ) );
    aGc.DrawText( text, rect, baseline, CGraphicsContext::ERight );
    }

TPtr TAknPhedViewLine::TranslatedText( const TDesC& aText ) const
    {
    TPtr buf( iModel->TranslationBuffer() );
    // to make sure that the buffer does not overflow.
    TInt maxLength = buf.MaxLength();
    buf.Copy( aText.Left( maxLength ) );
    // this routine will not expand the contents of the buffer:
    AknTextUtils::DisplayTextLanguageSpecificNumberConversion( buf );
    return buf;
    }

CAknPhedView::CAknPhedView( CAknPhedModel* aModel ) : iModel( aModel )
    {
    iMirror.SetPhedModel( iModel );
    iMirror.SetObserver( this );
    }

CAknPhedView::~CAknPhedView()
    {
    CRedirectionListener* listener = ( CRedirectionListener* )
                                    CAknTransitionUtils::GetData( (TInt) this );
    if ( listener )
        {
        CAknTransitionUtils::RemoveObserver( listener,
                                CAknTransitionUtils::EEventWsBufferRedirection );
        CAknTransitionUtils::RemoveData( (TInt) this );
        delete listener;
        }
    delete iLines;
    delete iTruncation;
    }

void CAknPhedView::ConstructL( TInt aMaxLines, const TDesC& aTruncation )
    {
    iTruncation = aTruncation.AllocL();
    iLines = new(ELeave) CAknPhedViewLineArray( aMaxLines );
    iLines->ResizeL(aMaxLines);
    for ( TInt ii=0; ii<aMaxLines; ii++ )
        {
        iLines->At( ii ).SetModel( iModel );
        iLines->At( ii ).SetTruncation( *iTruncation );
        }
    // Create listener that listen for redirection changes
    CRedirectionListener* listener = new (ELeave) CRedirectionListener( *this );
    User::LeaveIfError( CAknTransitionUtils::SetData( (TInt) this,
                                                      (TDesC8*) listener ) );
    User::LeaveIfError( CAknTransitionUtils::AddObserver( listener,
                            CAknTransitionUtils::EEventWsBufferRedirection ) );
	}

void CAknPhedView::SetFormat( TInt aLines, 
                              const CFont* aFont, 
                              const TRect& aRect, 
                              TInt aBottomBaselineOffset, 
                              TInt aBaselineSeparation)
    {
    __ASSERT_DEBUG(iLines, PhedViewPanic(EFormatNullLines));
    __ASSERT_DEBUG(aLines <= iLines->Count(), PhedViewPanic(EFormatTooManyLines));
    __ASSERT_DEBUG(aLines > 0, PhedViewPanic(EFormatTooFewLines));

    iNumLines = aLines;
    iFont = aFont;
    iRect = aRect;

    TRect rect(aRect);
    TInt baseline(rect.iBr.iY - aBottomBaselineOffset);
    for (TInt ii=0; ii<aLines; ii++)
        {
        TAknPhedViewLine& line = iLines->At(ii);
        
        // give each line a part of the rectangle aBaselineSeparation high
        if ( iNumLines > 1)
            {
            rect.iTl.iY = rect.iBr.iY - aBaselineSeparation;
            }
        line.SetFormat(aFont, rect, baseline);
        rect.iBr.iY = rect.iTl.iY;
        baseline -= aBaselineSeparation;

        SetConnectingLines(line, ii);
        }

    SetCursorFormat(aFont);

    FullFormat();
    }

void CAknPhedView::SetConnectingLines(TAknPhedViewLine& aLine, TInt aLineNum)
    {
    // connect up lines. Line 0 is the bottom line.
    aLine.SetLeftLine(aLineNum >= iNumLines-1 ? NULL : &iLines->At(aLineNum+1));
    aLine.SetRightLine(aLineNum <= 0 ? NULL : &iLines->At(aLineNum - 1));
    }

void CAknPhedView::HandlePhedDataEvent( const TAknPhedDataEvent& aEvent, 
                                        CAknPhedModel* /*aPhedData*/)
    {
    __ASSERT_DEBUG( iLines, PhedViewPanic( EEventNullLines ) );

    if ( aEvent.TextChanged() )
        {
        TInt start;
        TInt end;
        aEvent.TextChangeRange( start, end );
        TextChangeFormat( start, end );
        }
    // text change handling also repositions cursor, so don't handle it twice
    else if ( aEvent.CursorChanged() )
        {
        CursorChangeFormat( iMirror.CursorPosition() );
        }

    if ( aEvent.SelectionChanged() )
        {
        SelectionChangeFormat( iMirror.LeftMark(), iMirror.RightMark() );
        }

    // report that the editor has changed to the containing control, so that it
    // can report to it's observer.
    if ( iChangeReceiver )
        iChangeReceiver->StateChanged();
    }

void CAknPhedView::FullFormat()
    {
    TextChangeFormat( 0, iModel->Length() );
    SelectionChangeFormat( iMirror.LeftMark(), iMirror.RightMark() );
    }

void CAknPhedView::TextChangeFormat( TInt aStart, TInt aEnd )
    {
    // Let the lines handle the change. 
    // Stops after the first line able to handle the change, because it will tell the rest
    for ( TInt ii=0; ii<iNumLines; ii++ )
        {
        if ( iLines->At(ii).HandleTextChange( aStart, aEnd ) )
            break;
        }
    
    // Make as much text fit on screen, to the RHS as possible
    TAknPhedViewLine& leftLine = iLines->At( iNumLines-1 );
    TAknPhedViewLine& rightLine = iLines->At( 0 );
    if ( rightLine.IsTruncatedRight() && !leftLine.IsTruncatedLeft() && aStart <0 )
        {
        SetLeftPos( 0 );
        }
    if ( rightLine.IsTruncatedRight() && !leftLine.IsTruncatedLeft() )
        {
        SetLeftPos(leftLine.LeftPos());
        }

    // Cursor positioning must be affected by all that
    CursorChangeFormat( iMirror.CursorPosition() );
    }

void CAknPhedView::CursorChangeFormat( TInt aCursor )
    {
    if ( aCursor < 0 )
        {
        return;
        }
    // Shift the text so that the cursor appears on the screen
    TAknPhedViewLine& leftLine = iLines->At( iNumLines-1 );
    TAknPhedViewLine& rightLine = iLines->At( 0 );    
    
    if ( aCursor < rightLine.RightPos() )
        {
        rightLine.SetRightPos( aCursor );
        }
    else if ( aCursor >= leftLine.LeftPos() && leftLine.LineWidth() != 0 &&
        leftLine.IsTruncatedLeft() )
        {
        
        // cursor rule: cursor should not be a LHS of left truncated line
        if ( aCursor == iModel->Length() )
            SetLeftPos( aCursor );
        else
            SetLeftPos( aCursor+1 );
        }
    else if ( aCursor >= leftLine.LeftPos() )
        {
    	SetLeftPos( aCursor );
        }
    // Tell each line about the cursor.
    // Bottom most line to handle the event claims the cursor
    for ( TInt ii=0; ii<iNumLines; ii++ )
        {
        if ( iLines->At( ii ).HandleCursorChange( aCursor ) )
            {
            iCursorLine = ii;
            aCursor = KNoPos;
            }
        }

    UpdateCursor();
    }

void CAknPhedView::SelectionChangeFormat( TInt aLeft, TInt aRight )
    {
    // Tell each line about the selection change
    for ( TInt ii=0; ii<iNumLines; ii++ )
        {
        iLines->At( ii ).HandleSelectionChange( aLeft, aRight );
        }
    }

void CAknPhedView::Draw( CWindowGc& aGc, TBool aRedrawAll,
    const CCoeControl* aControl ) const
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( aControl );

    aGc.UseFont( iFont );
    for ( TInt ii=0; ii<iNumLines; ii++ )
        {
        TAknPhedViewLine& line = iLines->At( ii );
        if ( aRedrawAll || line.IsRedrawRequired() )
            {
            line.Draw( aGc, skin, cc, aControl );
            }
        }
    aGc.DiscardFont();
    }

void CAknPhedView::MoveCursorToLine( TInt aLineNo, TInt aTargetCursorPos )
    {
    // Used by up and down cursor move functions. Scroll one line if necessary
    if ( aLineNo < 0 )
        {
        TAknPhedViewLine& line = iLines->At( 0 );
        line.SetLeftPos(line.RightPos());
		iMirror.SetCompensatedCursorPosition(line.XPosToCursorPos(aTargetCursorPos));
        line.SetRightPos( line.RightPos() );
        }
    else if ( aLineNo >= iNumLines )
        {
        TAknPhedViewLine& line = iLines->At( iNumLines-1 );
        line.SetRightPos( line.LeftPos() );
		iMirror.SetCompensatedCursorPosition(line.XPosToCursorPos(aTargetCursorPos));
        SetLeftPos( line.LeftPos() );
        }
    else
        {
        iMirror.SetCompensatedCursorPosition(
            iLines->At( aLineNo ).XPosToCursorPos( aTargetCursorPos ) );
        }

    UpdateCursor();
	}


TBool CAknPhedView::CursorUp( TInt aTargetCursorPos )
    {
    // cursor rule: if at top LHS, wrap to bottom RHS, otherwise up one line
    if ( iMirror.CursorPosition() == iModel->Length() )
        {
		// This code should be setting the real cursor position, but there is 
		// a bug in the real cursor position function, in that it works in "compensated/formatted" space.
		iMirror.SetCompensatedCursorPosition(0);
        return EFalse;
        }
    else
        {
        MoveCursorToLine( iCursorLine + 1, aTargetCursorPos );
        return ( iMirror.CursorPosition() != iModel->Length() );
        }
    }

TBool CAknPhedView::CursorDown( TInt aTargetCursorPos )
    {
    // cursor rule: if at bottom RHS, wrap to top LHS, otherwise down one line
    if ( iMirror.CursorPosition() == 0 )
        {
		// This code depends on the fact that there is a bug in the real cursor
		// position function, in that it works in "compensated/formatted" space.
		iMirror.SetRealCursorPosition(iModel->Length());
        return EFalse;
        }
    else
        {
        MoveCursorToLine( iCursorLine - 1, aTargetCursorPos );
        return ( iMirror.CursorPosition() != 0 );
        }
    }

TBool CAknPhedView::SelectUp( TInt aTargetCursorPos )
    {
    TInt anchor = iModel->AnchorPosition();
    TBool targetPosUsed = CursorUp( aTargetCursorPos );
    iModel->SetAnchorPosition( anchor );
    return targetPosUsed;
    }

TBool CAknPhedView::SelectDown( TInt aTargetCursorPos )
    {
    TInt anchor = iModel->AnchorPosition();
    TBool targetPosUsed = CursorDown( aTargetCursorPos );
    iModel->SetAnchorPosition( anchor );
    return targetPosUsed;
    }

void CAknPhedView::EnableCursor()
    {
    CRedirectionListener* listener = ( CRedirectionListener* )
                                    CAknTransitionUtils::GetData( (TInt) this );
    listener->EnableCursor();
    UpdateCursor();
    }

void CAknPhedView::DisableCursor()
    {
    CRedirectionListener* listener = ( CRedirectionListener* )
                                    CAknTransitionUtils::GetData( (TInt) this );
    listener->DisableCursor();
    }

void CAknPhedView::UpdateCursor()
    {
    CRedirectionListener* listener = ( CRedirectionListener* )
                                    CAknTransitionUtils::GetData( (TInt) this );
    listener->UpdateCursor( iCursor );
    }

void CAknPhedView::SetWindows( RWindowGroup* aWg, RWindowBase* aWindow )
    {
    CRedirectionListener* listener = ( CRedirectionListener* )
                                    CAknTransitionUtils::GetData( (TInt) this );
    listener->SetWindows( aWg, aWindow );
    }

TPoint CAknPhedView::CursorPosition() const
    {
    return iLines->At( iCursorLine ).CursorPosition();
    }

void CAknPhedView::SetCursorFormat( const CFont* aFont )
    {
    iCursor.iType   = TTextCursor::ETypeRectangle;
    iCursor.iHeight = AknLayoutUtils::CursorHeightFromFont( aFont->FontSpecInTwips() );
    iCursor.iAscent = AknLayoutUtils::CursorAscentFromFont( aFont->FontSpecInTwips() );
    iCursor.iWidth  = AknLayoutUtils::CursorWidthFromFont ( aFont->FontSpecInTwips() );
    iCursor.iFlags  = 0;
    iCursor.iColor  = KRgbWhite;
    }

TBool CAknPhedView::IsTruncated() const
    {
    return iLines->At( 0 ).IsTruncatedRight() || iLines->At( iNumLines-1 ).IsTruncatedLeft();
    }

void CAknPhedView::SetLeftPos( TInt aPos )
    {
    iLines->At( iNumLines-1 ).SetLeftPos( aPos );

    // format rule: always justify to bottom right, if not truncated
    TAknPhedViewLine& rightLine = iLines->At( 0 );
    if ( !rightLine.IsTruncated() )
        {
        rightLine.SetRightPos( 0 );
        }
    }

void CAknPhedView::SetChangeReceiver( CAknPhoneNumberEditor* aChangeReceiver )
    {
    iChangeReceiver = aChangeReceiver;
    }

TRect CAknPhedView::Rect() const
    {
    return iRect;
    }

TInt CAknPhedView::CursorLine() const
    {
    return iCursorLine;
    }

// ---------------------------------------------------------------------------
// CAknPhedView::GetCursorPosByPoint
// ---------------------------------------------------------------------------
// 
TInt CAknPhedView::GetCursorPosByPoint( const TPoint& aPt )
    {
    TInt posLine = -1, cursor = -1;
    //check which line the pointer position is within.
    for ( TInt i = 0; i < iNumLines; i++ )        
        {
        if ( iLines->At( i ).Rect().Contains( aPt ) )
            {
            posLine = i;
            break;
            }
        }
    if ( posLine < 0 )
        {
        // if pointer position is out of right border of line but its
        // Y coordinates is within range of the line, the iRightPos of
        // the line should be returned to preserve the selection made
        // by user, otherwise a negative value will be returned.
        TInt rectBrX = iLines->At( 0 ).Rect().iBr.iX;
        if ( aPt.iX > rectBrX )
            {
            for ( TInt i = 0; i < iNumLines; i++ )
                {
                TInt topY = iLines->At( i ).Rect().iTl.iY;
                TInt bottomY = iLines->At( i ).Rect().iBr.iY;
                if ( aPt.iY >= topY && aPt.iY <= bottomY )
                    {
                    posLine = i;
                    break;
                    }
                }
            if ( posLine >= 0 && iLines->At( posLine ).LineWidth() > 0 )
                {
                TInt rightPos = iLines->At( posLine ).RightPos();
                cursor = iModel->Length() - rightPos;
                }
            }            
        return cursor;
        } 
    // only handle pointer event when the line has data
    if ( iLines->At( posLine ).LineWidth() > 0)
        {
        iCursorLine = posLine;        
        TInt pos = iLines->At( iCursorLine ).XPosToCursorPos( aPt.iX );        
        cursor = iModel->Length() - pos;
        
        const TReal32 KHalfRatio = 0.5;        
        TInt rightX = iLines->At( iCursorLine ).CursorPosToXPos( pos );
        TInt leftX = iLines->At( iCursorLine ).CursorPosToXPos( pos + 1 );        
        TInt rightPos = iLines->At( iCursorLine ).RightPos();  
        TInt leftPos = iLines->At( iCursorLine ).LeftPos(); 
        if ( aPt.iX < iLines->At( iCursorLine ).CursorPosToXPos( leftPos ) 
            && aPt.iX > 0 )
            {
            return cursor;
            } 
             
        if ( aPt.iX > rightX && rightPos > 0 )
            {
            leftX = rightX;
            rightX = iLines->At( iCursorLine ).Rect().iBr.iX;
            cursor++;            
            }        
        if ( ( aPt.iX - leftX ) < ( ( rightX - leftX ) * KHalfRatio ) )
            {
            cursor--;
            }        
        }    
    return cursor;
    }

// End of File
