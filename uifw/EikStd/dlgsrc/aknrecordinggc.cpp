/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:    Recording graphics context used to cache drawing commands
*
*/



#include <bitdev.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <graphics/gdi/gdiconsts.h>
#include <graphics/gdi/gdistructs.h>
#endif // SYMBIAN_ENABLE_SPLIT_HEADERS
#include <e32err.h>

#include "aknrecordinggc.h"

#ifdef _DEBUG
_LIT( KOverFlow, "Array overflow" );
_LIT( KBadArgument, "Bad argument");
#endif // _DEBUG

// ======== MEMBER FUNCTIONS ========

// -----------------------------------------------------------------------------
// CAknRecordingGc::CAknRecordingGc
// -----------------------------------------------------------------------------
//
CAknRecordingGc::CAknRecordingGc( CWindowGc* aRealGc ) : 
    CWindowGc( static_cast<CWsScreenDevice*>( aRealGc->Device() ) )
    {
    iRealGc = aRealGc;
    iCurrentLine = -1;
    }


// -----------------------------------------------------------------------------
// CAknRecordingGc::ConstructL
// -----------------------------------------------------------------------------
//
void CAknRecordingGc::ConstructL( const TSize& /*aSize*/ )
    {
//    iOffScreenBmp = new ( ELeave ) CFbsBitmap;
//    User::LeaveIfError( iOffScreenBmp->Create( TSize( 360, 640 ) /*aSize*/, EColor64K ) );
//    iBitmapDevice = CFbsBitmapDevice::NewL( iOffScreenBmp );
//    User::LeaveIfError( iBitmapDevice->CreateContext( iBitGc ) );
    }


// -----------------------------------------------------------------------------
// CAknRecordingGc::~CAknRecordingGc
// -----------------------------------------------------------------------------
//
CAknRecordingGc::~CAknRecordingGc()
    {
    iLines.ResetAndDestroy();
    delete iOffScreenBmp;
    delete iBitGc;
    delete iBitmapDevice;
    }
    

// -----------------------------------------------------------------------------
// CAknRecordingGc::FlushBuffer
// -----------------------------------------------------------------------------
//
void CAknRecordingGc::FlushBuffer( const TRect& aRect, TInt aLineToSkip )
    {
    if ( iLines.Count() == 0 )
        {
        return;
        }
        
    CBufferItem* item = NULL;
    CLineData* line = NULL;
    CBitmapContext* gc = iRealGc;
    
    // modify target rectangle to match recorded coordinates
    TInt topY = iLines[0]->iRect.iTl.iY;
    TRect rect( aRect );
    rect.iTl.iY += topY;
    rect.iBr.iY += topY;

    // move out-of-screen rectangle to match real screen coordinates
    rect.Move( 1000, 0 );
    
    if ( iUseBitGc )
        {
        gc = iBitGc;
        }
    
    TRect realRect( TPoint( 1000, 0 ), iLines[0]->iRect.Size() );
    TRect includeNextLine( realRect );
    for ( TInt i = 0; i < iLines.Count(); ++i )
        {
        line = iLines[i];

        if ( rect.Intersects( includeNextLine ) && i != aLineToSkip )
            {
            gc->SetOrigin( TPoint( aRect.iTl.iX-line->iRect.iTl.iX, -rect.iTl.iY + realRect.iTl.iY ) );

            for ( TInt ii = 0; ii < line->iItems.Count(); ++ii )
                {
                item = line->iItems[ii];
                
                switch ( item->iType )
                    {
                    case CBufferItem::EShortText:
                        gc->DrawText( *item->iText, item->iPosition );
                        break;
                        
                    case CBufferItem::ELongText:
                        gc->DrawText( *item->iText, item->iBox, item->iBaseLineOffset, item->iHorizontal, item->iLeftMargin );
                        break;
                        
                    case CBufferItem::ESetPenColor:
                        gc->SetPenColor( item->iColor );
                        break;
                        
/*                    case CBufferItem::EBitBlt2:
                        iRealGc->BitBlt( item->iPosition, item->iBitmap, item->iBox );
                        break;*/
                        
                    case CBufferItem::EBitBltMasked1:
                        gc->BitBltMasked( item->iPosition, item->iBitmap, item->iBox, item->iMask, item->iInvertMask );
                        break;
                        
                    case CBufferItem::EUseFont:
                        gc->UseFont( item->iFont );
                        break;
                        
                    case CBufferItem::EDiscardFont:
                        gc->DiscardFont();
                        break;
                        
                    case CBufferItem::ESetDrawMode:
                        gc->SetDrawMode( item->iDrawMode );
                        break;
                        
                    case CBufferItem::ESetClippingRect:
                        gc->SetClippingRect( item->iBox );
                        break;
                        
                    case CBufferItem::ECancelClippingRect:
                        gc->CancelClippingRect();
                        break;
                        
                    case CBufferItem::ESetBrushColor:
                        gc->SetBrushColor( item->iColor );
                        break;
                        
                    case CBufferItem::ESetBrushStyle:
                        gc->SetBrushStyle( item->iBrushStyle );
                        break;

                    case CBufferItem::EDrawRect:
                        gc->DrawRect( item->iRect );
                        break;
                    case CBufferItem::EClear:
                        gc->Clear( item->iRect );
                        break;
                    }
                }
                
            gc->CancelClippingRect();
            }
        else if ( realRect.iTl.iY > aRect.iBr.iY )
            {
            break;
            }
            
        realRect.Move( 0, line->iRect.Height() );
        includeNextLine = realRect;
        if( i < iLines.Count()-1 )
        	includeNextLine.iBr.iY += iLines[i+1]->iRect.Height();
        }
        
    gc->SetOrigin( TPoint( 0, 0 ) );

    if ( iUseBitGc )
        {
        iRealGc->BitBlt( TPoint( 0, 0 ), iOffScreenBmp, TRect( 0, 0, 360, 500 ) );
        }
    }


// -----------------------------------------------------------------------------
// CAknRecordingGc::PurgeBuffer
// -----------------------------------------------------------------------------
//
void CAknRecordingGc::PurgeBuffer()
    {
    iLines.ResetAndDestroy();
    iCurrentLine = -1;
    }


// -----------------------------------------------------------------------------
// CAknRecordingGc::PrepareForNewLineL
// -----------------------------------------------------------------------------
//
void CAknRecordingGc::PrepareForNewLineL( const TRect& aRect )
    {
    CLineData* newLine = new ( ELeave ) CLineData;
    newLine->iRect = aRect;
    iLines.AppendL( newLine );
    iCurrentLine = iLines.Count() - 1;
    }


// -----------------------------------------------------------------------------
// CAknRecordingGc::ReplaceLineL
// -----------------------------------------------------------------------------
//
void CAknRecordingGc::ReplaceLineL( TInt aLine )
    {
    if (  aLine < iLines.Count() )
        {
        TRect rect( iLines[aLine]->iRect );
        
        delete iLines[aLine];
        iLines[aLine] = NULL;
        iLines[aLine] = new ( ELeave ) CLineData;
        iLines[aLine]->iRect = rect;
        }
        
    iCurrentLine = aLine;
    }


// -----------------------------------------------------------------------------
// CAknRecordingGc::UseBitGc
// -----------------------------------------------------------------------------
//
void CAknRecordingGc::UseBitGc( TBool aUseBitGc )
    {
    iUseBitGc = aUseBitGc;
    }


// -----------------------------------------------------------------------------
// CAknRecordingGc::InsertLineL
// -----------------------------------------------------------------------------
//
void CAknRecordingGc::InsertLineL( TInt aLine, const TRect& aRect )
    {
    CLineData* newLine = new ( ELeave ) CLineData;
    newLine->iRect = aRect;
    
    iLines.Insert( newLine, aLine );
    iCurrentLine = aLine;
    }


// -----------------------------------------------------------------------------
// CAknRecordingGc::InsertLineL
// -----------------------------------------------------------------------------
//
void CAknRecordingGc::InsertLineL( TInt aLine )
    {
    InsertLineL( aLine, TRect( 0, 0, 0, 0 ) );
    }
    

// -----------------------------------------------------------------------------
// CAknRecordingGc::AppendLineL
// -----------------------------------------------------------------------------
//
void CAknRecordingGc::AppendLineL()
    {
    PrepareForNewLineL( TRect( 0, 0, 0, 0 ) );
    }


// -----------------------------------------------------------------------------
// CAknRecordingGc::PurgeLine
// -----------------------------------------------------------------------------
//
void CAknRecordingGc::PurgeLine( TInt aLine )
    {
    if ( aLine < iLines.Count() )
        {
        iLines[aLine]->iItems.ResetAndDestroy();
        iCurrentLine = aLine;
        }
    }


// -----------------------------------------------------------------------------
// CAknRecordingGc::SetLineRect
// -----------------------------------------------------------------------------
//
void CAknRecordingGc::SetLineRect( TInt aLine, const TRect& aRect )
    {
    __ASSERT_DEBUG( aLine < iLines.Count(), User::Panic( KOverFlow, KErrOverflow ) );
    iLines[aLine]->iRect = aRect;
    }


// -----------------------------------------------------------------------------
// CAknRecordingGc::DeleteLine
// -----------------------------------------------------------------------------
//
void CAknRecordingGc::DeleteLine( TInt aLine )
    {
    if ( aLine != -1 && aLine < iLines.Count() )
        {
        delete iLines[aLine];
        iLines.Remove( aLine );
        }
    }


// -----------------------------------------------------------------------------
// CAknRecordingGc::CBufferItem::~CBufferItem()
// -----------------------------------------------------------------------------
//
CAknRecordingGc::CBufferItem::~CBufferItem()
    {
    delete iText;
    delete iBitmap;
    delete iMask;
    }


// -----------------------------------------------------------------------------
// CAknRecordingGc::CLineData::~CLineData()
// -----------------------------------------------------------------------------
//
CAknRecordingGc::CLineData::~CLineData()
    {
    iItems.ResetAndDestroy();
    }


// -----------------------------------------------------------------------------
// CAknRecordingGc::BufferItem
// -----------------------------------------------------------------------------
//
CAknRecordingGc::CBufferItem* CAknRecordingGc::BufferItem()
    {
    CBufferItem* buffer ( NULL );
    TRAP_IGNORE( buffer = new ( ELeave ) CBufferItem );
    TRAP_IGNORE( iLines[iCurrentLine]->iItems.AppendL( buffer ) );
    buffer->iPosition.SetXY( -1, -1 );
    
    return buffer;
    }
        
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::Activate( RDrawableWindow& /*aDevice*/ )
    {
    }

    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::Deactivate()
    {
    }

    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
CGraphicsDevice* CAknRecordingGc::Device() const
    {
    return NULL;
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// 
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::SetOrigin( const TPoint& /*aPoint*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::SetDrawMode( TDrawMode aDrawingMode )
    {
    CBufferItem* buffer = BufferItem();
    buffer->iType = CBufferItem::ESetDrawMode;
    buffer->iDrawMode = aDrawingMode;
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::SetClippingRect( const TRect& aRect )
    {
    CBufferItem* buffer = BufferItem();
    buffer->iType = CBufferItem::ESetClippingRect;
    buffer->iBox = aRect;
    buffer->iPosition = aRect.iTl;
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::CancelClippingRect()
    {
    CBufferItem* buffer = BufferItem();
    buffer->iType = CBufferItem::ECancelClippingRect;
    }

    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
TInt CAknRecordingGc::SetClippingRegion( const TRegion& /*aRegion*/ )
    {
    return 0;
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::Reset()
    {
    }


// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::UseFont( const CFont* aFont )
    {
    CBufferItem* buffer = BufferItem();
    buffer->iType = CBufferItem::EUseFont;
    buffer->iFont = aFont;
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DiscardFont()
    {
    CBufferItem* buffer = BufferItem();
    buffer->iType = CBufferItem::EDiscardFont;
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::SetUnderlineStyle( TFontUnderline /*aUnderlineStyle*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::SetStrikethroughStyle( 
    TFontStrikethrough /*aStrikethroughStyle*/ )
    {
    }
    

    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::SetWordJustification( TInt /*aExcessWidth*/, 
    TInt /*aNumGaps*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::SetCharJustification( TInt /*aExcessWidth*/, 
    TInt /*aNumChars*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::SetPenColor( const TRgb& aColor )
    {
    CBufferItem* buffer = BufferItem();
    buffer->iType = CBufferItem::ESetPenColor;
    buffer->iColor = aColor;
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::SetPenStyle( TPenStyle /*aPenStyle*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::SetPenSize( const TSize& /*aSize*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::SetBrushColor( const TRgb& aColor )
    {
    CBufferItem* buffer = BufferItem();
    buffer->iType = CBufferItem::ESetBrushColor;
    buffer->iColor = aColor;
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::SetBrushStyle( TBrushStyle aBrushStyle )
    {
    CBufferItem* buffer = BufferItem();
    buffer->iType = CBufferItem::ESetBrushStyle;
    buffer->iBrushStyle = aBrushStyle;
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::SetBrushOrigin( const TPoint& /*aOrigin*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::UseBrushPattern( const CFbsBitmap* /*aDevice*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DiscardBrushPattern()
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::MoveTo( const TPoint& /*aPoint*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::MoveBy( const TPoint& /*aPoint*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::Plot( const TPoint& /*aPoint*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DrawArc( const TRect& /*aRect*/, const TPoint& /*aStart*/, 
    const TPoint& /*aEnd*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DrawLine( const TPoint& /*aPoint1*/, 
    const TPoint& /*aPoint2*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DrawLineTo( const TPoint& /*aPoint*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DrawLineBy( const TPoint& /*aPoint*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DrawPolyLine( const CArrayFix<TPoint>* /*aPointList*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DrawPolyLine( const TPoint* /*aPointList*/, 
    TInt /*aNumPoints*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DrawPie( const TRect& /*aRect*/, const TPoint& /*aStart*/, 
    const TPoint& /*aEnd*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DrawEllipse( const TRect& /*aRect*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DrawRect( const TRect& aRect )
    {
    CBufferItem* buffer = BufferItem();
    buffer->iType = CBufferItem::EDrawRect;
    buffer->iRect = aRect;
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DrawRoundRect( const TRect& /*aRect*/, 
    const TSize& /*aEllipse*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
TInt CAknRecordingGc::DrawPolygon( const CArrayFix<TPoint>* /*aPointList*/, 
    TFillRule /*aFillRule*/ )
    {
    return 0;
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
TInt CAknRecordingGc::DrawPolygon( const TPoint* /*aPointList*/, 
    TInt /*aNumPoints*/, TFillRule /*aFillRule*/ )
    {
    return 0;
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DrawBitmap( const TPoint& /*aTopLeft*/, 
    const CFbsBitmap* /*aDevice*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DrawBitmap( const TRect& /*aDestRect*/, 
    const CFbsBitmap* /*aDevice*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DrawBitmap( const TRect& /*aDestRect*/, 
    const CFbsBitmap* /*aDevice*/, const TRect& /*aSourceRect*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DrawBitmapMasked( const TRect& /*aDestRect*/, 
    const CFbsBitmap* /*aBitmap*/, const TRect& /*aSourceRect*/, 
    const CFbsBitmap* /*aMaskBitmap*/, TBool /*aInvertMask*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DrawBitmapMasked( const TRect& /*aDestRect*/, 
    const CWsBitmap* /*aBitmap*/, const TRect& /*aSourceRect*/, 
    const CWsBitmap* /*aMaskBitmap*/, TBool /*aInvertMask*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DrawText( const TDesC& aBuf, const TPoint& aPos )
    {
    CBufferItem* buffer = BufferItem();
    buffer->iType = CBufferItem::EShortText;
    TRAP_IGNORE( buffer->iText = aBuf.AllocL() );
    buffer->iPosition = aPos;
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DrawText( const TDesC& aBuf, const TRect& aBox, 
    TInt aBaselineOffset, TTextAlign aHoriz, TInt aLeftMrg )
    {
    CBufferItem* buffer = BufferItem();
    buffer->iType = CBufferItem::ELongText;
    TRAP_IGNORE( buffer->iText = aBuf.AllocL() );
    buffer->iBox = aBox;
    buffer->iBaseLineOffset = aBaselineOffset;
    buffer->iHorizontal = aHoriz;
    buffer->iLeftMargin = aLeftMrg;
    buffer->iPosition = aBox.iTl;
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::Clear()
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::Clear( const TRect& aRect )
    {
    CBufferItem* buffer = BufferItem();
    buffer->iType = CBufferItem::EClear;
    buffer->iRect = aRect;
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::CopyRect( const TPoint& /*aOffset*/, 
    const TRect& /*aRect */ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::BitBlt( const TPoint& /*aPos*/, 
    const CFbsBitmap* /*aBitmap*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::BitBlt( const TPoint& aDestination,
    const CFbsBitmap* aBitmap, const TRect& aSource )
    {
    if ( iUseBitGc )
        {
        iBitGc->BitBlt( aDestination, aBitmap, aSource );
        }
/*    CBufferItem* buffer = new ( ELeave ) CBufferItem;
    buffer->iType = CBufferItem::EBitBlt2;
    buffer->iPosition = aDestination;
    buffer->iBitmap = aBitmap;
    buffer->iBox = aSource;
    
    iLines[iCurrentLine]->iItems.AppendL( buffer );*/
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::BitBltMasked( const TPoint& aPoint, 
    const CFbsBitmap* aBitmap, const TRect& aSourceRect, 
    const CFbsBitmap* aMaskBitmap, TBool aInvertMask )
    {
    if ( !iUseBitGc )
        {
        CBufferItem* buffer = BufferItem();
        buffer->iType = CBufferItem::EBitBltMasked1;
        buffer->iPosition = aPoint;
        buffer->iBox = aSourceRect;
        buffer->iInvertMask = aInvertMask;
        
        // Make a duplicate of passed in bitmap, so that to make sure
        // the bitmap won't be freed when FlushBuffer(). (Duplicate
        // only increases the access count for bitmap)
        CFbsBitmap* bitmap = NULL;
        CFbsBitmap* maskBitmap = NULL;
        TRAP_IGNORE( bitmap = new (ELeave) CFbsBitmap() );
        TRAP_IGNORE( maskBitmap = new (ELeave) CFbsBitmap() );
        bitmap->Duplicate(aBitmap->Handle());
        maskBitmap->Duplicate(aMaskBitmap->Handle());
        buffer->iBitmap = bitmap;
        buffer->iMask = maskBitmap;
        }
    else
        {
        iBitGc->BitBltMasked( aPoint, aBitmap, aSourceRect, aMaskBitmap, aInvertMask );
        }
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::BitBlt( const TPoint& /*aPoint*/, 
    const CWsBitmap* /*aBitmap*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::BitBlt( const TPoint& /*aDestination*/, 
    const CWsBitmap* /*aBitmap*/, const TRect& /*aSource*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::BitBltMasked( const TPoint& /*aPoint*/,
    const CWsBitmap* /*aBitmap*/, const TRect& /*aSourceRect*/, 
    const CWsBitmap* /*aMaskBitmap*/, TBool /*aInvertMask*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::MapColors( const TRect& /*aRect*/, const TRgb* /*aColors*/,
    TInt /*aNumPairs*/, TBool /*aMapForwards*/ )
    {
    }

    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DrawTextVertical( const TDesC& /*aText*/, 
    const TPoint& /*aPos*/, TBool /*aUp*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::DrawTextVertical( const TDesC& /*aText*/, 
    const TRect& /*aBox*/, TInt /*aBaselineOffset*/, TBool /*aUp*/,
    TTextAlign /*aVert*/, TInt /*aMargin*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::SetDitherOrigin( const TPoint& /*aPoint*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
TInt SetClippingRegion( const TRegion& /*aRegion*/ )
    {
    return 0;
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::CancelClippingRegion()
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::SetOpaque( TBool /*aDrawOpaque*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::SetFaded( TBool /*aFaded*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
void CAknRecordingGc::SetFadingParameters( TUint8 /*aBlackMap*/,
    TUint8 /*aWhiteMap*/ )
    {
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
TInt CAknRecordingGc::AlphaBlendBitmaps( const TPoint& /*aDestPt*/, 
    const CFbsBitmap* /*aSrcBmp*/, const TRect& /*aSrcRect*/, 
    const CFbsBitmap* /*aAlphaBmp*/, const TPoint& /*aAlphaPt*/ )
    {
    return 0;
    }
    
    
// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
TInt CAknRecordingGc::AlphaBlendBitmaps( const TPoint& /*aDestPt*/, 
    const CWsBitmap* /*aSrcBmp*/, const TRect& /*aSrcRect*/, 
    const CWsBitmap* /*aAlphaBmp*/, const TPoint& /*aAlphaPt*/ )
    {
    return 0;
    }


// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
TAny* CAknRecordingGc::Interface( TUid /*aInterfaceId*/ )
    {
    return NULL;
    }


// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
const TAny* CAknRecordingGc::Interface( TUid /*aInterfaceId*/ ) const
    {
    return NULL;
    }


// ---------------------------------------------------------------------------
// From class CWindowGc
// ---------------------------------------------------------------------------
//
TInt CAknRecordingGc::APIExtension( TUid aUid, TAny*& /*aOutput*/,
    TAny* aInput )
    {
    if (aUid == KDrawTextInContextUid)
        {
        __ASSERT_DEBUG( aInput, User::Panic(KBadArgument, KErrArgument ));
        TDrawTextInContextInternal* contextParam = 
            static_cast<TDrawTextInContextInternal*>(aInput);
        const TTextParameters* params = &contextParam->iParam;
        __ASSERT_DEBUG( params, User::Panic(KBadArgument, KErrArgument ));
        TPtrC textToDraw = contextParam->iText.Mid( params->iStart, 
                                                    params->iEnd - params->iStart );
        DrawText(textToDraw, contextParam->iPosition);
        return KErrNone;
        }
    else
        {
        return KErrNotSupported;
        }
    }
