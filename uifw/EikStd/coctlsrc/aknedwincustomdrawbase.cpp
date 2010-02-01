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
*
*/


// INCLUDE FILES
#include "aknedwincustomdrawbase.h"
#include <lafmain.h>
#include <AknsDrawUtils.h>
#include <frmtview.h>
#include <coecntrl.h>
#include <eikedwin.h>
#include <eikenv.h> // for AKN_LAF_COLOR macro
#include <AknUtils.h>
#include <gdi.h>
#include <AknPictographInterface.h>
#include <AknPictographDrawerInterface.h>
#include <aknenv.h>
#include <AknFontProvider.h>
#include <AknTextDecorationMetrics.h>
#include <AknsUtils.h>


// CONSTANTS

// This is the last character that will be treated as requiring higher underline
// const TText KMaxSpecialUnderliningChar = 0x0E5B;
const TInt KWsBufferSize = 16000;

// MEMBER FUNCTIONS

CAknEdwinCustomDrawBase::CAknEdwinCustomDrawBase(
    const MLafEnv& aEnv, const CEikEdwin& aEdwin ) :
        CLafEdwinCustomDrawBase( aEnv, aEdwin ), iEdwin( aEdwin )
    {
    // This value has to be stored as the meaning of the flag governs behaviour of controls
    // at the point of construction
    iAppSkinEnabled = AknsUtils::AvkonSkinEnabled();
    }

CAknEdwinCustomDrawBase::CAknEdwinCustomDrawBase(
    const MLafEnv& aEnv,
    const CEikEdwin& aEdwin,
    CTextView* aTextView,
    CWindowGc* aSystemGc ) :
        CLafEdwinCustomDrawBase( aEnv,aEdwin ),
        iEdwin( aEdwin ),
        iTextView( aTextView ),
        iSysGc( aSystemGc )
    {
    // This value has to be stored as the meaning of the flag governs behaviour of controls
    // at the point of construction
    iAppSkinEnabled = AknsUtils::AvkonSkinEnabled();
    }

// -----------------------------------------------------------------------------
// CAknEdwinCustomDrawBase::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CAknEdwinCustomDrawBase::ConstructL()
    {
    iWsBufferRequestId = CAknEnv::Static()->RequestWsBuffer( KWsBufferSize );
    // Returns NULL if feature not supported.
    iPictographDrawer = CAknPictographInterface::NewL(
        static_cast<CCoeControl&>( const_cast<CEikEdwin&>( iEdwin ) ),
        *static_cast<MAknPictographAnimatorCallBack*>( this ) );
    }

// -----------------------------------------------------------------------------
// CAknEdwinCustomDraw::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknEdwinCustomDrawBase* CAknEdwinCustomDrawBase::NewL(
    const MLafEnv& aEnv, const CEikEdwin& aControl )
    { // static
    CAknEdwinCustomDrawBase* self =
        new( ELeave ) CAknEdwinCustomDrawBase( aEnv, aControl );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// -----------------------------------------------------------------------------
// CAknEdwinCustomDraw::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknEdwinCustomDrawBase* CAknEdwinCustomDrawBase::NewL(
    const MLafEnv& aEnv,
    const CEikEdwin& aControl,
    CTextView* aTextView,
    CWindowGc* aSystemGc )
    { // static
    CAknEdwinCustomDrawBase* self = new( ELeave ) CAknEdwinCustomDrawBase(
        aEnv, aControl, aTextView, aSystemGc );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// Destructor
CAknEdwinCustomDrawBase::~CAknEdwinCustomDrawBase()
    {
    delete iPictographDrawer;
    CAknEnv::Static()->CancelWsBufferRequest( iWsBufferRequestId );
    }

// -----------------------------------------------------------------------------
// CAknEdwinCustomDrawBase::DrawPictographArea
// -----------------------------------------------------------------------------
//
void CAknEdwinCustomDrawBase::DrawPictographArea()
    {
    iEdwin.DrawTextView();

    // Mainly used for drawing form highlight frame
    const TCallBack& callback = iEdwin.PictographAnimationCallBack();
    if ( callback.iFunction )
        {
        callback.CallBack();
        }
    }

// -----------------------------------------------------------------------------
// CAknEdwinCustomDrawBase::DrawText
// -----------------------------------------------------------------------------
//
void CAknEdwinCustomDrawBase::DrawText( const TParam& aParam, 
    const TLineInfo& aLineInfo, const TCharFormat& aFormat, const TDesC& aText,
    const TPoint& aTextOrigin, TInt aExtraPixels ) const
    {
    TRect textLinesRect = iEdwin.GetTextLinesRect();

    if ( !textLinesRect.IsEmpty() )
        {
        if ( aLineInfo.iInnerRect.iTl.iY < textLinesRect.iTl.iY ||
             aLineInfo.iInnerRect.iBr.iY > textLinesRect.iBr.iY )
            {
            return;
            }
        }

    TCharFormat alteredFormat(aFormat);

    if( aFormat.iFontPresentation.iUnderline == EUnderlineOn )
        {
        // Inhibit all excess pixels
        aExtraPixels = 0;

        TInt underlinePos(0);
        (void)TextNeedsCustomUnderline( aText, aParam, aFormat, underlinePos ) ;
        // always perform custom underlining

        TRect underlineRect(aParam.iDrawRect);
        TAknTextDecorationMetrics decoration( 0 ); // Give dummy font id for default decoration
        // Note that underlinePos in scalable is a delta relative to normal baseline
        underlineRect.iBr.iY = aLineInfo.iBaseline - underlinePos + decoration.BaselineToUnderlineOffset();
        underlineRect.iTl.iY = underlineRect.iBr.iY - decoration.UnderlineHeight();

        TRAPD
            (
            err,
            DrawUnderlineL( underlineRect, aParam,aLineInfo,alteredFormat,aText,aTextOrigin,aExtraPixels)
            );
        if ( err != KErrNone )
            {
            // Just draw the underline solid
            aParam.iGc.DrawRect( underlineRect );
            }
        // we've handled the underline, so switch it off now
        alteredFormat.iFontPresentation.iUnderline = EUnderlineOff;
        aParam.iGc.SetUnderlineStyle( EUnderlineOff);  // and force it off in the GC
        }
    CFont* font = NULL;
    aParam.iMap.GetNearestFontInTwips( font, aFormat.iFontSpec );
    RRegion rgn;
    if ( iEdwin.IsSmileyEnabled() && font )
        {
        rgn.AddRect( iEdwin.AdjustDrawRectForSmiley( aParam.iDrawRect ) );
        iEdwin.GetClipRegionForSmiley( rgn, *font, aText, aTextOrigin, 
            aParam.iDrawRect );
        aParam.iGc.SetClippingRegion( rgn );
        }
    CLafEdwinCustomDrawBase::DrawText( aParam, aLineInfo, alteredFormat, 
        aText, aTextOrigin, aExtraPixels );
    if ( iEdwin.IsSmileyEnabled() )
        {
        aParam.iGc.CancelClippingRegion();
        }
    rgn.Close();
    
    if ( iEdwin.IsSmileyEnabled() && font && ( &aParam.iGc ==
        static_cast<CGraphicsContext*>( iTextView->BitmapContext() ) ) )
        {
        CBitmapContext* bitmapGc( iTextView->BitmapContext() );
        CEikEdwin& edwin = const_cast<CEikEdwin&>( iEdwin );
        TPoint startPt( aParam.iDrawRect.iTl );
        startPt.iY = aLineInfo.iBaseline;
        TRAP_IGNORE( {
            edwin.HandleScrollForSmileyL();
            edwin.DrawSmileyInTextL( *bitmapGc, *font, aText, startPt );
            } );
        }

    // Draw pictographs if the feature is supported.
    // Character justification is not supported.
    if ( ( iPictographDrawer && !aExtraPixels ) )
        {
        CBitmapContext* bitmapGc = NULL;

        // This is how we check the type of the graphics context
        // The gc should be one of these:
        if ( &aParam.iGc == static_cast<CGraphicsContext*>( iSysGc ) )
            {
            bitmapGc = iSysGc;
            }
        else if ( &aParam.iGc ==
            static_cast<CGraphicsContext*>( iTextView->BitmapContext() ) )
            {
            bitmapGc = iTextView->BitmapContext();
            }

        if ( bitmapGc )
            {
            const TText* text = aText.Ptr();
            TInt length( aText.Length() ); 
                        
            TPoint point = aParam.iDrawRect.iTl;
            point.iY = aLineInfo.iBaseline;
            if ( iPictographDrawer && !aExtraPixels )
                {
                MAknPictographDrawer* drawer = 
                    iPictographDrawer->Interface();                
                if ( font )
                    {
                    drawer->DrawPictographsInText(
                        *bitmapGc,
                        *font,
                        aText,
                        point);                    
                    }
                }            
            }
        }
    aParam.iMap.ReleaseFont( font );
    // set brush back to original
    aParam.iGc.SetBrushColor(CEikonEnv::Static()->ControlColor(EColorControlBackground,iEdwin));
    }

// -----------------------------------------------------------------------------
// CAknEdwinCustomDrawBase::DrawText
// -----------------------------------------------------------------------------
//
void CAknEdwinCustomDrawBase::DrawText( const TParam& aParam, 
    const TLineInfo& aLineInfo, const TCharFormat& aFormat, const TDesC& aText, 
    const TInt aStart, const TInt aEnd, const TPoint& aTextOrigin, 
    TInt aExtraPixels ) const
    {
    DrawText( aParam, aLineInfo, aFormat, aText.Mid( aStart, aEnd - aStart ), 
        aTextOrigin, aExtraPixels );
    }

// -----------------------------------------------------------------------------
// CAknEdwinCustomDrawBase::DrawBackground
// -----------------------------------------------------------------------------
//
void CAknEdwinCustomDrawBase::DrawBackground(
    const TParam& aParam, const TRgb& aBackground, TRect& aDrawnRect ) const
    {
    if ( !iEdwin.IsBackgroundDrawingSuppressed() )
        {
        const MCoeControlBackground* drawer = iEdwin.FindBackground();
        
        if ( drawer )
            {
            if ( !iEdwin.SkipBackgroundDrawer() )
                {
                drawer->Draw( static_cast<CWindowGc&>( aParam.iGc ),
                              iEdwin,
                              aParam.iDrawRect );
                }
            }
        else
            {
            if ( !DrawRectWithSkin( aParam.iGc, aParam.iDrawRect, aDrawnRect ) )
                {
                aParam.iGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
                aParam.iGc.SetPenStyle( CGraphicsContext::ESolidPen );
                aParam.iGc.SetBrushColor( aBackground );
                aParam.iGc.SetPenColor( aBackground );
                aParam.iGc.DrawRect( aParam.iDrawRect );
                }
            }
        }
    
    aDrawnRect = aParam.iDrawRect;
    }

// -----------------------------------------------------------------------------
// CAknEdwinCustomDrawBase::DrawLineGraphics
// -----------------------------------------------------------------------------
//
void CAknEdwinCustomDrawBase::DrawLineGraphics(const TParam& aParam,const TLineInfo& aLineInfo ) const
    {
    CLafEdwinCustomDrawBase::DrawLineGraphics( aParam, aLineInfo ); // Base Call
    }


TRgb CAknEdwinCustomDrawBase::SystemColor(TUint aColorIndex,TRgb aDefaultColor) const
    {
    TRgb ret = aDefaultColor;
    if (aColorIndex==TLogicalRgb::ESystemForegroundIndex)
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        if (skin && iEdwin.SkinColorId() != KErrNotFound)
            {
            AknsUtils::GetCachedColor(skin, ret, KAknsIIDQsnTextColors, iEdwin.SkinColorId());
            }
        }
    else if (aColorIndex==TLogicalRgb::ESystemBackgroundIndex)
        {
        // Only override aDefaultColor if SetBackgroundColorL was called:
        (void)iEdwin.EditorBackgroundColor(ret);
        // Insist on opaque background
        ret.SetAlpha(0xFF);
        }

    else if (aColorIndex==TLogicalRgb::ESystemSelectionForegroundIndex)
        {
        ret = KRgbWhite;
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        if (skin)
            {
            if ( iEdwin.HighlightStyle() == EEikEdwinHighlightLink )
                {
                AknsUtils::GetCachedColor(skin, ret, KAknsIIDQsnHighlightColors, EAknsCIQsnTextColorsCG3);
                }
            else // default
                {
                AknsUtils::GetCachedColor(skin, ret, KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG24);
                }
            }
        }
    else if (aColorIndex==TLogicalRgb::ESystemSelectionBackgroundIndex)
        {
        ret = KRgbBlue;
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        if (skin)
            {
            if ( iEdwin.HighlightStyle() == EEikEdwinHighlightLink )
                {
                AknsUtils::GetCachedColor(skin, ret, KAknsIIDQsnHighlightColors, EAknsCIQsnTextColorsCG1);
                }
            else // default
                {
                AknsUtils::GetCachedColor(skin, ret, KAknsIIDQsnHighlightColors, EAknsCIQsnHighlightColorsCG2);
                }
            }
        }

    return ret;
    }

void CAknEdwinCustomDrawBase::CAknEdwinCustomDrawBase_Reserved_1()
    {
    }

/**
* Routine to group the common skin custom drawing
*
* @return TBool EFalse iff the drawing was not performed
*/
TBool CAknEdwinCustomDrawBase::DrawRectWithSkin( const CGraphicsContext& aGc, const TRect& aRect, TRect& aDrawnRect ) const
    {
    TBool drawn(EFalse);

    if ( iAppSkinEnabled && iTextView)
        {
        CBitmapContext* bitmapGc = NULL;

        // This is how we check the type of the graphics context
        // The gc should be one of these:
        if ( &aGc == static_cast<CGraphicsContext*>( iSysGc ) )
            bitmapGc = iSysGc;
        else if ( &aGc == static_cast<CGraphicsContext*>( iTextView->BitmapContext() ) )
            bitmapGc = iTextView->BitmapContext();
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
        else if( &aGc == static_cast<CGraphicsContext*>( &(iControl.SystemGc()) ) )
            bitmapGc = &(iControl.SystemGc());
#endif //RD_UI_TRANSITION_EFFECTS_POPUPS
        if ( bitmapGc && iEdwin.SkinEnabled() )
            {
            MAknsSkinInstance* skin = AknsUtils::SkinInstance();
            // Edwin manages the skin background
            MAknsControlContext* edCc = iEdwin.SkinBackgroundControlContext();

            TInt drawFlags = KAknsDrawParamDefault;
            if( CAknEnv::Static()->TransparencyEnabled() )
            {
                drawFlags |= KAknsDrawParamNoClearUnderImage;
            }

            if( AknsDrawUtils::DrawBackground( skin, edCc,
                    &iControl, *bitmapGc, aRect.iTl, aRect,
                    drawFlags ))
                {
                aDrawnRect = aRect;
                drawn = ETrue;
                }
            }
        else
            {
            // perform unoptimized draw of skin using bitmap brushstyle?
            }

        }

    return drawn;
    }

TBool CAknEdwinCustomDrawBase::TextNeedsCustomUnderline( const TDesC& aText, const TParam& aParam, const TCharFormat& aFormat, TInt& underlinePos ) const
    {
    TBool needsCustomUnderline(EFalse);

    TInt fontProviderIndex = AknFontProvider::FontProviderIndexFromFontSpec( aFormat.iFontSpec );
    if ( fontProviderIndex > KErrNotFound )
        {
        needsCustomUnderline = AknFontProvider::HasBaselineCorrection( fontProviderIndex );
        if ( needsCustomUnderline )
            {
            TInt denominatorIfFractional(KAknFontProviderBaselineCorrectionIsAbsolute);
            TInt numInitialCharsTheSame(0); // not used
            TInt minimumBaselineLift(0);
            AknFontProvider::MinimumBaselineDeltaForDescriptor(
                fontProviderIndex,
                aText,
                minimumBaselineLift,
                denominatorIfFractional,
                EFalse, // Look at whole descriptor and take minimum baseline lift
                numInitialCharsTheSame);

            // Check for proportional baseline deltas:
            if ( denominatorIfFractional != KAknFontProviderBaselineCorrectionIsAbsolute )
                {
                underlinePos = minimumBaselineLift * aParam.iDrawRect.Height() / denominatorIfFractional;
                }
            else
                {
                underlinePos = minimumBaselineLift;
                }
            }
        }

    return needsCustomUnderline;
    }

// -----------------------------------------------------------------------------
// CAknEdwinCustomDrawBase::DrawUnderlineL
// -----------------------------------------------------------------------------
/*
This method has the responsibility for drawing a custom underline.

An offscreen bitmap with 8 bit greyscale is made the size of the underline. Using the same font as the editor, the text
is drawn onto this bitmap, with variable positioning, so that the text is smeared.

The "descenderBitmap" is passed to a routine that analyzes this bitmap and draws the underlines only in
between the descenders, leaving gaps.

*/
void CAknEdwinCustomDrawBase::DrawUnderlineL(
        const TRect& aUnderlineRect,
        const TParam& aParam,
        const TLineInfo& aLineInfo,
        const TCharFormat& aFormat,
        const TDesC& aText,
        const TPoint& /*aTextOrigin*/, // Not currently used
        TInt aExtraPixels) const
    {

    if (aUnderlineRect.Width() <= 0 || aUnderlineRect.Height() <= 0 )
        return;

    TRect localUnderlineRect(aUnderlineRect);

    // Create bitmap to draw the descenders to
    CFbsBitmap* descendersBitmap = new (ELeave) CFbsBitmap();
    CleanupStack::PushL( descendersBitmap);
    User::LeaveIfError( descendersBitmap->Create(TSize(localUnderlineRect.Width(),localUnderlineRect.Height()) , EGray256));

    CFbsBitmapDevice* device = CFbsBitmapDevice::NewL(descendersBitmap);
    CleanupStack::PushL(device);
    CGraphicsContext* context=NULL;
    User::LeaveIfError(device->CreateContext(context));
    CleanupStack::PushL(context);

    CFont* font;
    // Fetch the font.  This font is already in use by the editor.  Since it is a request in twips, it will be in the
    // twips cache and the request should not go to the Fbserv server.  It should therefore be fast.
    User::LeaveIfError(aParam.iMap.GetNearestFontInTwips( font, aFormat.iFontSpec) );

    context->UseFont( font );
    DrawDescendersOntoBitmap( *context, aText, aParam, aLineInfo, localUnderlineRect, aExtraPixels );
    context->DiscardFont ();

    aParam.iMap.ReleaseFont( font );

    // Draw the line using aParam.iGc so as to pick up correct foreground color. Algo inside this method is used to avoid the descenders that are
    // already drawn onto descendersBitmap
    DrawLineWithGaps( aParam, *descendersBitmap, localUnderlineRect ) ;

    // Delete all the local objects
    CleanupStack::PopAndDestroy( context );
    CleanupStack::PopAndDestroy( device );
    CleanupStack::PopAndDestroy( descendersBitmap );
    }

/**
*  The descender parts of the text are drawn onto the bitmap context.
*  The text is drawn several times with horizontal and vertical offsets. The resulting bitmap will be used to determine
*  where the underline should be drawn to avoid touching the descenders
*/
void CAknEdwinCustomDrawBase::DrawDescendersOntoBitmap(
        CGraphicsContext& aContext,
        const TDesC& aText,
        const TParam& /*aParam*/,
        const TLineInfo& aLineInfo,
        const TRect& aUnderlineRect,
        TInt aExtraPixels ) const
    {
    // Have to arrange to draw text onto the underline rectangle bitmap context.
    // The text needs to be positioned so that the correct parts of the text (ie.part of the descenders)
    // are within this underline rectangle. We need to calculate the distance from the top of the drawing rectangle
    // (which will perform the clipping) to the baseline of the text.
    // This will be used as the  "aBaselineOffset" parameter to the CGraphicsContext::DrawText method.
    // Expect this value to be small and negative, since the baseline is usually above the underline.
    TInt posOfBaselineFromUnderline =  posOfBaselineFromUnderline = aLineInfo.iBaseline - aUnderlineRect.iTl.iY;

    // Here, draw the text with letter spacing. This is what Tagma will do when it really draws the text.
    if (aExtraPixels)
        {
        aContext.SetCharJustification(aExtraPixels,aText.Length());
        }

    // We are going to draw the text moved around both horizontally and vertically.
    // Use this rectangle with 0,0 at top left to match the bitmap's own 0,0-based coord system
    TRect movingRect( TPoint(0,0), TPoint( aUnderlineRect.Width(), aUnderlineRect.Height()));

    // Double loop to perform text smearing horizontally and vertically

    // These constants reflect the desired gaps around the descenders
    // This calculation allows the descender-avoiding gaps to scale:
    const TInt KHorizontalSmear = Max( aUnderlineRect.Height()/2, 1);
    const TInt KVerticalSmear = KHorizontalSmear;

    for ( TInt xOffset = -KHorizontalSmear; xOffset <= KHorizontalSmear; xOffset++ )
        {
        for ( TInt yOffset = -KVerticalSmear; yOffset <= KVerticalSmear; yOffset++ )
            {
            // Drawing is relative to the left, and top (assuming posOfBaselineFromUnderline is constant), so fiddle
            // top left point.
            movingRect.iTl.iX = xOffset;
            movingRect.iTl.iY = 0;
            aContext.DrawText( aText, movingRect, posOfBaselineFromUnderline + yOffset, CGraphicsContext::ELeft, 0 );
            }
        }
    }

/**
  Draws the underline in the aParam.iGc pen color onto the screen, but uses the smeared descenders bitmap to
  avoid drawing underline through descenders.

  The offscreen bitmap is walked, watching for light/dark and dark./light transitions which drive the drawing of line segments
  on the screen device.

  Various features are built in the bitmap walk.
  - use special "off" threshold near the beginning of a text to encourage leading bits of underline
  - special "on" threshold to encourage small trailing pieces of underlines

  There are special conditions that must be met for success to be claimed, and a value of ETrue to be returned.
  These conditions insist on at least one segment of line being drawn, and that lines occupy a big enough percentage of the
  total underline length.
 */
void CAknEdwinCustomDrawBase::DrawLineWithGaps(
        const TParam& aParam,
        CFbsBitmap& aSmearedDescendersBitmap,
        const TRect& aUnderlineRect ) const
    {
    // Use the Symbian utility to provide access to bitmaps:
    TBitmapUtil util(&aSmearedDescendersBitmap);
    util.Begin( TPoint(0,0) );

    const TInt lastRow = aUnderlineRect.Height() - 1; // zero-based
    const TInt lastPos = aUnderlineRect.Width() - 1; // zero-based

    TUint32 thisPixel;
    const TUint32 thresholdPixel(254); // Must suit the TDrawMode. This value for Gray255
    const TUint32 darkerThreshold(32); // Must suit the TDrawMode. this low (near-black) value encourages underlines to start at the far left.
    const TUint32 endThreshold(128); // Must suit the TDrawMode. Lower threshold to encourage a line segment at the far right.
    const TInt shortRunLimit(1);

    // Anchor and end point are used to draw the lines in the most common cases
    TPoint anchor;
    TPoint earlyAnchor;

    // State flags
    TBool currentlyInALine;  // An anchor point of some sort has been recorded. Committed to drawing at least something for the segment.
    TBool earlyLineActive; // Special state where the earlyAnchor is used rather than the normally recorded one.

    TInt numberSegmentsDrawn(0); // records how many segments of underline are drawn.  Used to set a return value
    TInt lengthDrawnOnThisLine(0);
    TInt maxPercentOfALineDrawn(0);

    // Analyse the smeared character bitmap, and draw line segments that avoid the descenders
    // The smeared descenders appear as black (or grey) pixels in the offscreen bitmap
    // Using gray256, white is 255, black is 0.
    // Do not get confused by the fact we tend to draw where there is white, and not draw then there is black!

    for ( TInt row = 0; row <= lastRow; row++, util.IncYPos() )
        {
        // Set at beginning of the row at column 0
        util.SetPos( TPoint(0,row) );

        // row initialization.
        TInt pos = 0;  // Position in the row.
        currentlyInALine = EFalse;
        earlyLineActive = EFalse;
        lengthDrawnOnThisLine = 0; // zero the length recorded to be drawn in each row.

        thisPixel = util.GetPixel();
        if ( thisPixel >= darkerThreshold ) // use low (near-black) value to encourage leading lines
            {
            anchor = TPoint(aUnderlineRect.iTl.iX + pos, aUnderlineRect.iTl.iY + row); // beginning of lines
            currentlyInALine = ETrue;
            }

        for (util.IncXPos(), pos = 1; pos < lastPos; pos++, util.IncXPos())
            {
            thisPixel = util.GetPixel();

            if ( currentlyInALine )
                {
                // If we are not near the beginning, but have gone below normal threshold, end the line segment
                TBool endTheLineSegment(EFalse);
                if ( thisPixel < thresholdPixel && pos > shortRunLimit ) //then end it
                    {
                    endTheLineSegment = ETrue;
                    }
                // If we ARE near the beginning and below the special dark threshold
                else if ( thisPixel < darkerThreshold && pos <= shortRunLimit )
                    {
                    endTheLineSegment = ETrue;
                    }

                if ( endTheLineSegment )
                    { // The last TPoint is not drawn, so use pos and not pos - 1
                    DrawLineAndRecord( aParam.iGc, aUnderlineRect, anchor, pos, row, lengthDrawnOnThisLine, numberSegmentsDrawn);
                    currentlyInALine = EFalse;
                    earlyLineActive = EFalse; // cancel any early starts
                    }

                }
            else // not currentlyInALine
                {
                //
                if (thisPixel >= thresholdPixel ) // not in a line, but now above threshold
                    {
                    anchor = TPoint(aUnderlineRect.iTl.iX+pos, aUnderlineRect.iTl.iY + row);
                    currentlyInALine = ETrue;
                    }
                else if ( thisPixel >= endThreshold ) // mark a potential "early start" for a line if even a little off black
                    {
                    // There is no test on whether we are already in earlyLineActive, so this updates, essentially recording a last
                    // point above this lower threshold
                    earlyAnchor = TPoint( aUnderlineRect.iTl.iX+pos, aUnderlineRect.iTl.iY + row );
                    earlyLineActive = ETrue;
                    // But not currently in a line
                    }
                else // not in a line and going below (darker than) endThreshold cancels the earlyLine stuff
                    {
                    earlyLineActive = EFalse;
                    }
                }

            }  // end of for loop over columns

        // Finish off the line. Pixel index already incremented by the for loop, but the pixel has not been fetched
        thisPixel = util.GetPixel();
        if ( currentlyInALine)
            {
            // 2nd TPoint in the call is not plotted, so go further, to lastPos+1
            DrawLineAndRecord( aParam.iGc, aUnderlineRect, anchor, lastPos+1, row, lengthDrawnOnThisLine, numberSegmentsDrawn);
            }
        else
            {
            // Special rule, with special low threshold, to get end runs even if somewhat suppressed
            if ( thisPixel >= endThreshold )
                {
                if ( earlyLineActive ) // Use the recorded early anchor
                    {
                    // 2nd TPoint in the call is not plotted, so go further by 1
                    DrawLineAndRecord( aParam.iGc, aUnderlineRect, earlyAnchor, lastPos+1, row, lengthDrawnOnThisLine, numberSegmentsDrawn);
                    }
                else // just draw the one point
                    {
                    TPoint startPoint(aUnderlineRect.iTl.iX+lastPos,aUnderlineRect.iTl.iY + row);
                    // 2nd TPoint in the call is not plotted, so go further by 1
                    DrawLineAndRecord( aParam.iGc, aUnderlineRect, startPoint, lastPos+1, row, lengthDrawnOnThisLine, numberSegmentsDrawn);
                    }
                }
            }

        maxPercentOfALineDrawn = Max( maxPercentOfALineDrawn, (lengthDrawnOnThisLine * 100 )/aUnderlineRect.Width()  );
        } // end of for loop over rows

    util.End();

    // Check criteria for whether to say this was successful or not.
    const TInt KMinPercentOfLineDrawn(33); // need a third drawn
    if ( numberSegmentsDrawn <  (aUnderlineRect.Height()*2) && ( maxPercentOfALineDrawn < KMinPercentOfLineDrawn ) )
        {
        // Not enough line drawn.
        // Extend the underlines on both sides.  Use some scaling for how much to extend
        const TInt extraLineLength = Max( 1, aUnderlineRect.Height() );
        for ( TInt row = 0; row <= lastRow; row++ ) // lastRow is zero-based
            {
            aParam.iGc.DrawLine(
                TPoint(aUnderlineRect.iTl.iX-extraLineLength, aUnderlineRect.iTl.iY+ row ),
                TPoint(aUnderlineRect.iTl.iX, aUnderlineRect.iTl.iY+ row)  );
            aParam.iGc.DrawLine(
                TPoint(aUnderlineRect.iBr.iX,  aUnderlineRect.iTl.iY+ row ),
                TPoint(aUnderlineRect.iBr.iX+extraLineLength, aUnderlineRect.iTl.iY+ row)  );
            }

        }
    }

void CAknEdwinCustomDrawBase::DrawLineAndRecord(
    CGraphicsContext& aGc,
    const TRect& aRect,
    const TPoint& aAnchor,
    TInt aColumn,
    TInt aRow,
    TInt& aAccumulatedLength,
    TInt& aSegmentsDrawn) const
    {
    TPoint endPoint = TPoint(aRect.iTl.iX + aColumn, aRect.iTl.iY + aRow);
    aGc.DrawLine( aAnchor, endPoint );
    aAccumulatedLength += (endPoint.iX - aAnchor.iX);
    aSegmentsDrawn++;
    }
