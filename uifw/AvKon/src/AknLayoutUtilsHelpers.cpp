/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
*     Internal implementations for Avkon Layout Utilities.  Related public interfaces are to be 
*  found in AknUtils.h. 
*     Implementations that use these internal routines are to be found in AknUtils.cpp
* 
*
*/


#include "AknLayoutUtilsHelpers.h"
#include <eikedwin.h>
#include <AknFontId.h>
#include <AknUtils.h>
#include <AknLayoutFont.h>
#include <AknSettingCache.h>
#include <AknsUtils.h>
#include <AknPanic.h>

LOCAL_C TBool IsEmpty(TInt aValue)
	{
	return aValue == ELayoutEmpty;
	}
	

// ================= MEMBER FUNCTIONS =======================


TInt AknLayoutUtilsHelpers::CorrectBaseline( TInt aParentHeight, TInt aBaseline, TInt aFontId )
    {
    TInt B = aBaseline;
    if( TAknFontId::IsEncodedFont(aFontId) ) // This tells us that the font id has come from scalable layout API
        {
        // From scalable layout, the iB member is the distance from the bottom of the 
        // parent to the bottom of the text pane.
        // 
        TInt b = aBaseline;
        if (IsParentRelative(b)) { b = aParentHeight - ELayoutP + b; }

        const CAknLayoutFont *font = AknLayoutUtils::LayoutFontFromId(aFontId);
        TInt descent = font->BaselineToTextPaneBottom();

		// calculate distance down from top of parent to bottom of maximal glyph
        TInt top2bog = aParentHeight - b;

		// distance down to baseline is distance down to bottom of glyph minus descent
        // A further 1 is subtracted to account for the definition of baseline in the
        // Series 60 pre-2.8 layout specifications.
        B = top2bog - descent - 1;
        }
 
    return B;
    }

TInt AknLayoutUtilsHelpers::EdwinHeightFromLines (
        TInt aParentHeight,
        const TAknTextLineLayout& aLayout,
        TInt aBaselineSeparationOverRide,
        TInt aNumberOfLinesToShowOverRide,
        TInt& aVerticalPositionOfEdwin
        )
    {
    TInt fontId = aLayout.FontId();
    const CAknLayoutFont* font = AknLayoutUtils::LayoutFontFromId( fontId, NULL );

    // Take on the overrides
    if ( aBaselineSeparationOverRide <= 0 )
        aBaselineSeparationOverRide = aLayout.BaselineSkip();
    if ( aNumberOfLinesToShowOverRide <= 0)
        aNumberOfLinesToShowOverRide = aLayout.NumberOfLinesShown();
    
    TAknTextDecorationMetrics decorationMetrics( fontId );
    TInt topMargin, bottomMargin;
    decorationMetrics.GetTopAndBottomMargins( topMargin, bottomMargin );

    TInt newBaseline = CorrectBaseline( aParentHeight, aLayout.iB, fontId );
    
    aVerticalPositionOfEdwin = 
        EditorVerticalPositionWithinParent( font, newBaseline, topMargin );
    
    return EdwinHeightFromLines(
        font->TextPaneHeight(), decorationMetrics,
        aBaselineSeparationOverRide, aNumberOfLinesToShowOverRide);	
    }
    
 TInt AknLayoutUtilsHelpers::EdwinHeightFromLines (
        TInt aTextPaneHeight,
        TAknTextDecorationMetrics& aDecorationMetrics,
        TInt aBaselineSeparation,
        TInt aNumberOfLinesToShow
        )
    {
    // This space around the glyph areas is for cursor and highlight extensions
    TInt topMargin, bottomMargin;
    aDecorationMetrics.GetTopAndBottomMargins( topMargin, bottomMargin );

    TInt height = (aNumberOfLinesToShow-1)*aBaselineSeparation 
        + aTextPaneHeight // includes top and bottom text pane parts
        + topMargin + bottomMargin;
    return height;
    }

 TInt AknLayoutUtilsHelpers::EdwinLinesWithinHeight (
        const TAknTextLineLayout& aLayout,
        TInt aBaselineSeparationOverride,
        TInt aMaxHeight,
        TInt& aUsedHeight
        )
    {
    
    TInt fontId = aLayout.FontId();
    TInt textPaneHeight;
    if ( TAknFontId::IsEncodedFont( fontId ))
        {
        TAknFontSpecification spec( fontId );
        textPaneHeight = spec.TextPaneHeight();
        }
    else
        {
        const CAknLayoutFont* font = AknLayoutUtils::LayoutFontFromId( fontId, NULL );
        textPaneHeight = font->TextPaneHeight();
        }    
        
    // Deal with the override
    if ( aBaselineSeparationOverride <= 0 )
        aBaselineSeparationOverride = aLayout.BaselineSkip();
    TAknTextDecorationMetrics decorationMetrics( fontId );
    return AknLayoutUtilsHelpers::EdwinLinesWithinHeight(
        textPaneHeight,
        decorationMetrics,
        aBaselineSeparationOverride,
        aMaxHeight,
        aUsedHeight );
    }
    
/**
* This implemenation is protected against aBaseline <=0 baseline, but that is all, and the math 
* will just to its stuff.
*/
TInt AknLayoutUtilsHelpers::EdwinLinesWithinHeight (
        TInt aTextPaneHeight,
        TAknTextDecorationMetrics& aDecorationMetrics,
        TInt aBaselineSeparation,
        TInt aMaxHeight,
        TInt& aUsedHeight
        )
    {
    TInt numberOfLinesThatFit(0);

    // This space around the glyph areas is for cursor and highlight extensions
    TInt topMargin, bottomMargin;
    aDecorationMetrics.GetTopAndBottomMargins( topMargin, bottomMargin );

    if ( aBaselineSeparation > 0 )
        {
        // This variable precalculates how much bigger the baseline separation is than the 
        // text and highlights. Adding it to aHeight lets us pretend that all lines, whether they
        // are at top bottom or middle, are the same. Then we can just divide to see how many lines 
        // there are. 
        TInt savedSpaceAtTopAndBottom = 
            aBaselineSeparation - aTextPaneHeight - topMargin - bottomMargin;
        TInt virtualMaxHeight = aMaxHeight + savedSpaceAtTopAndBottom;
        numberOfLinesThatFit = virtualMaxHeight/aBaselineSeparation; // Integer diviion
        aUsedHeight = (numberOfLinesThatFit-1)*aBaselineSeparation 
            + aTextPaneHeight + topMargin + bottomMargin;
        }
    else
        {
        // The question is, does even one line fit?
        TInt lineHeight = aTextPaneHeight + topMargin + bottomMargin;
        if ( lineHeight >= aMaxHeight )
            {
            numberOfLinesThatFit = 1;
            aUsedHeight = lineHeight;            
            }
        else
            {
            numberOfLinesThatFit = 0;
            aUsedHeight = 0;    
            }            
        }
        
    return numberOfLinesThatFit;
    }

/** 
* This routine emulates what Form is doing internally to get font height and depth.
*/
void AknLayoutUtilsHelpers::GetFontMaxHeightAndDepth( const CFont* aFont, TInt& aMaxHeight, TInt& aMaxDepth) 
    {
    const CFbsFont* fbsFont = NULL;

    if ( aFont->TypeUid() == KCFbsFontUid)
        {
        fbsFont = (CFbsFont*)aFont;
        }

    if ( fbsFont && fbsFont->IsOpenFont() )
        {
        TOpenFontMetrics metrics;
        fbsFont->GetFontMetrics(metrics);
        aMaxHeight = metrics.MaxHeight();
        aMaxDepth = metrics.MaxDepth();
        }
    else
        {
        aMaxHeight = aFont->AscentInPixels();
        aMaxDepth = aFont->DescentInPixels();
        }	
    }

    
void AknLayoutUtilsHelpers::LayoutEdwinScalableWithCorrectedParametersAndDecorationMetrics(
                                 CEikEdwin *aEdwin, 
                                 const TRect &aEdwinParent, 
                                 const CAknLayoutFont *aFont, 
                                 TInt aColor, 
                                 TInt aLeftMargin, 
                                 TInt aRightMargin, 
                                 TInt aBaseline, // naturally defined
                                 TInt /*aWidth*/,    // Used with some printing diagnostics
                                 TInt aJustification, 
                                 TInt aNumberOfLinesShown, 
                                 TInt aSecondLineBaseline, //naturally defined
                                 TAknsQsnTextColorsIndex aOverrideColor,
                                 TAknTextDecorationMetrics& decorationMetrics,
                                 TBool aEnsureEditorIsContainedByParent,
                                 TInt& aNumberOfVisibleLines)
    {

    // Get editor margin information
    // This space around the glyph areas is for cursor and highlight extensions
    TInt topMargin, bottomMargin, leftMargin, rightMargin;
    decorationMetrics.GetTopAndBottomMargins( topMargin, bottomMargin );
    decorationMetrics.GetLeftAndRightMargins( leftMargin, rightMargin );

    /* 
    If there is a second baseline, set the baselineDelta to second - first
    */
    TInt baselineDelta = (aSecondLineBaseline)
        ?(aSecondLineBaseline - aBaseline)
        :aFont->TextPaneHeight()+topMargin+bottomMargin;

    CParaFormat paraFormat;
    TParaFormatMask paraFormatMask;
    paraFormat.iLineSpacingControl = CParaFormat::ELineSpacingExactlyInPixels;
    paraFormatMask.SetAttrib(EAttLineSpacingControl); // Switches mode to "Exact line spacing"
    paraFormat.iLineSpacingInTwips = baselineDelta;
    paraFormatMask.SetAttrib(EAttLineSpacing); 

	CAknSettingCache& cache = CAknEnv::Static()->SettingCache();
    paraFormat.iLanguage = cache.InputLanguage(); // Default paragraph language (in case there is no text yet)
	paraFormatMask.SetAttrib(EAttParaLanguage);

    TCharFormat charFormat;
    TCharFormatMask charFormatMask;
    charFormat.iFontSpec = aFont->FontSpecInTwips();
    charFormatMask.SetAttrib(EAttFontTypeface);
    charFormatMask.SetAttrib(EAttFontHeight);
	charFormatMask.SetAttrib(EAttFontStrokeWeight);
	charFormatMask.SetAttrib(EAttFontPosture);

    charFormat.iFontPresentation.iTextColor = AKN_LAF_COLOR_STATIC(aColor);
    charFormatMask.SetAttrib(EAttColor);

    if ( AknsUtils::AvkonSkinEnabled() )
        {
        // This is not needed actually anymore, left here to ensure backward compatibility  
        AknsUtils::GetCachedColor( AknsUtils::SkinInstance(),
                                   charFormat.iFontPresentation.iTextColor,
                                   KAknsIIDQsnTextColors,
                                   aOverrideColor );
        
        }
    TRAP_IGNORE(aEdwin->SetTextSkinColorIdL(aOverrideColor)); // this can leave only if there is no extension before
                                                              // and allocating new one fails

    // ensure that logical index is being set correctly, so we can override color afterwards in SystemColor()
    charFormat.iFontPresentation.iTextColor.SetSystemColorIndex(TLogicalRgb::ESystemForegroundIndex);

    // this is needed because edwin in noneditable flags on draws with EColorControlText and not charformat layer.
    TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL(*aEdwin, EColorControlText, charFormat.iFontPresentation.iTextColor));


    CParaFormatLayer* paraFormatLayer = NULL;
    CCharFormatLayer* charFormatLayer = NULL;

    TRAPD(
            error, 
            { 
            paraFormatLayer = CParaFormatLayer::NewL(&paraFormat,paraFormatMask);
            CleanupStack::PushL(paraFormatLayer);
            charFormatLayer = CCharFormatLayer::NewL(charFormat,charFormatMask); 
            CleanupStack::Pop(); // paraFormatLayer
            } 
        );
    
    if (error)
        {
#ifdef AKNUTILS_ENABLE_TRACES
        LOGTEXT(_L("Error in applying formatting\n"));
#endif // AKNUTILS_ENABLE_TRACES
        }
    else
        {
        aEdwin->SetParaFormatLayer(paraFormatLayer);
        aEdwin->SetCharFormatLayer(charFormatLayer);
        }
    aEdwin->SetSuppressFormatting(ETrue);
	// Setting editor alignment must be done after
	// other editor paragraph formatting
	aEdwin->SetAlignment(aJustification);
    aEdwin->SetSuppressFormatting(EFalse);

    aEdwin->SetBorder(ENone);

    // Edwin control`s rectangle starts out as the parent rectangle
    TRect edwinRect = aEdwinParent;

    // Editor margin" is used to position the TextView inside the editor
    // May have to modify top and bottom margins for font characteristics
    // "fontAscent" variable stands for total (+ve) distance from the baseline to the top of the Scalable layout textpane.
    TInt fontAscent = aFont->TextPaneTopToBaseline();
    // Form itself uses an OpenFont MaxHeight it if can get it. Account for this
    TInt maxHeight;
    TInt maxDepth;
    GetFontMaxHeightAndDepth( aFont, maxHeight, maxDepth );
    // This is now excess as measured in S60 relative to what TOpenFontMetrics reports
    // Should be zero in optimal situations.
    TInt roomForHighGlyphs = fontAscent - maxHeight; 

    TMargins8 editorMargins; 
    editorMargins.iBottom = 0; // allow the viewrect to extend into the bottom margin
    editorMargins.iTop = 0;
    editorMargins.iRight = (TUint8)rightMargin;
    editorMargins.iLeft = (TUint8)leftMargin;

    // Use left and right layout information (from parameters) and additional margins 
    // (for highlights). Top and bottom corrections are not done here.
    edwinRect.iTl.iX += aLeftMargin; 
    edwinRect.iTl.iX -=editorMargins.iLeft; // subtract left highlight margin
    edwinRect.iBr.iX -= aRightMargin;
    edwinRect.iBr.iX += editorMargins.iRight; // add right highlight margin
#ifdef AKNUTILS_ENABLE_TRACES
    __ASSERT_DEBUG(edwinRect.Size().iWidth == aWidth,  LOGTEXT(_L("AknLayoutUtils:LayoutEdwin: edwinRect.Size().iWidth differs from parameter value aWidth")));
#endif // AKNUTILS_ENABLE_TRACES

    // because of right alignment, cursor width added
    TInt cursorWidth = decorationMetrics.CursorWidth();
    edwinRect.iBr.iX += cursorWidth; 
    edwinRect.iTl.iX += cursorWidth; 
    
    // Scaleable layout uses convention where topMargin (space for highlights) is positive.
    TInt posOfFirstBaselineInsideTextView( fontAscent + topMargin);
    TInt heightBetweenTextViewAndTopOfEditor( editorMargins.iTop );
    TInt editorTopFromParentTop = 
        aBaseline - (posOfFirstBaselineInsideTextView + heightBetweenTextViewAndTopOfEditor);  

#ifdef AKNUTILS_ENABLE_TRACES
    // There is a problem with layout or the font if the editor has had to be positioned higher than its parent
    if ( editorTopFromParentTop < 0 )
        {
        LOGTEXT( _L("WARNING:LayoutEdwinScalable: Editor top has been placed higher than parent top") );
        }
#endif // AKNUTILS_ENABLE_TRACES

    aEdwin->SetBorderViewMargins(editorMargins); 
    
    TInt madeATextView=KErrNone;
    if (!aEdwin->TextView())
        TRAP(madeATextView,aEdwin->CreateTextViewL());
    if (KErrNone==madeATextView)
        {

        /* 
        The left and right values passed to SetHighlighExtensions are unambiguous.
        The top value is measured up from the top of the textview.  Note that that the top of the textview 
        includes all of the following: 
            Font ascent; 
            + Any excess height as reported by OpenFont's MaxHeight;
            + excess height above that requested by SetExcessHeightRequired
        Since we already pass in the top margin + any excess over and above OpenFont's maxheight into 
        SetExcessHeightRequired (see below), then the top highlight needs no extension.

        The bottomMargin returned by HighlightExtensionsFromFont is measured down from the bottom of the Series 60 
        text pane. But the value to be passed in to SetHighlightExtension is measured down from the default bottom 
        of Form's Text Band. Now, the bottom of the Text Band is by default the top of the text on the 
        next line (or where the next line would be). However, the placement of the Text Band is modified 
        by the call to SetExcessHeightRequired, raising it up by the value passed in.
        */

        // First we can group together all the distances from the top of the highlight to the baseline
        TInt topOfHighlightToBaseline = maxHeight + roomForHighGlyphs + topMargin;
        // Position ourselves at the top of the CURRENT line by subtracting baselineDelta.
        TInt bottomWrtBandedHeight = -baselineDelta;
        // Then we can measure down to the bottom of the highlight:
        bottomWrtBandedHeight += topOfHighlightToBaseline + aFont->BaselineToTextPaneBottom() + bottomMargin; 

        aEdwin->TextView()->SetHighlightExtensions(
            leftMargin, rightMargin, 0, bottomWrtBandedHeight );
        }
    /*
    Added to restrict the height of the edwin in pixels to the max height in lines.
    This is because MaximumHeightInLines is simply a number held by Edwin and the editor 
    height is only enforced for MaximumHeight.
    */
    TInt maxHeightInLinesForEdwin=aEdwin->MaximumHeightInLines();
    if (maxHeightInLinesForEdwin)
        {
       
        TInt edwinMaxHeight = EdwinHeightFromLines(
            aFont->TextPaneHeight(),
            decorationMetrics,
            baselineDelta,
            maxHeightInLinesForEdwin );
        aEdwin->SetMaximumHeight( edwinMaxHeight );

        // Also restrict the number of lines to set up now 
        if ( maxHeightInLinesForEdwin < aNumberOfLinesShown)
            {
            aNumberOfLinesShown = maxHeightInLinesForEdwin;     
            }
        
        }
    
    /*
    Make the edwin height big enough to eliminate scrolling... 
    If  !aMinimizeEdwinView then this is fine.
    If aMinimizeEdwinView, the printing region will be altered anyway.
    */
    TInt edwinHeight = EdwinHeightFromLines(
            aFont->TextPaneHeight(),
            decorationMetrics,
            baselineDelta,
            aNumberOfLinesShown );        

    edwinRect.iTl.iY += editorTopFromParentTop; 
    TInt availableHeight = aEdwinParent.Height()-editorTopFromParentTop;
    if ( aEnsureEditorIsContainedByParent && (edwinHeight > availableHeight))
        {
        aNumberOfVisibleLines = EdwinLinesWithinHeight(
           aFont->TextPaneHeight(), decorationMetrics, baselineDelta, availableHeight, edwinHeight );
        }
    else
        {
        aNumberOfVisibleLines = aNumberOfLinesShown;
        }
    
    edwinRect.iBr.iY = edwinRect.iTl.iY + edwinHeight;
   
    if (aEdwin->TextLayout())
        {
        // Do not automatically inflate the ascents inside Form 
        aEdwin->TextLayout()->SetFontHeightIncreaseFactor(0); 
        // Allow minimum descent of 0
        aEdwin->TextLayout()->SetMinimumLineDescent(0);
        }

    CTextView* view = aEdwin->TextView();
    if ( view )
        {
        view->SetExcessHeightRequired( roomForHighGlyphs + topMargin );
        // Cursor extensions and width
        TInt firstExtension = topMargin + aFont->TextPaneTopToBaseline() - aFont->AscentInPixels();
        TInt secondExtension = bottomMargin + aFont->BaselineToTextPaneBottom() - aFont->DescentInPixels();
        view->SetCursorExtensions( firstExtension, secondExtension );
        view->SetCursorWeight( decorationMetrics.CursorWidth() );       
        }

    // The order of SetRect(), AlterViewRect and NotifyNewFormat is important.
    aEdwin->SetSuppressFormatting(ETrue);
    aEdwin->SetRect(edwinRect);
    aEdwin->SetSuppressFormatting(EFalse);
    
	aEdwin->SetSuppressNotifyDraw( ETrue );
    TRAP_IGNORE(aEdwin->NotifyNewFormatL());
	aEdwin->SetSuppressNotifyDraw( EFalse );
    }

void AknLayoutUtilsHelpers::LayoutEdwinScalable(CEikEdwin *aEdwin, 
                                 const TRect &aEdwinParent, 
                                 TInt aFontId, 
                                 TInt aColor, 
                                 TInt aLeftMargin, 
                                 TInt aRightMargin, 
                                 TInt aBaseline, 
                                 TInt aWidth, 
                                 TInt aJustification, 
                                 TInt aNumberOfLinesShown, 
                                 TInt aSecondLineBaseline, 
                                 TAknsQsnTextColorsIndex aOverrideColor,
                                 const CAknLayoutFont *aCustomFont, 
                                 TBool aMinimizeEdwinView)
    {
    __ASSERT_DEBUG(aEdwin,Panic(EAknPanicNullPointer));
    __ASSERT_DEBUG(!(aEdwin->MaximumHeightInLines())||aNumberOfLinesShown<=aEdwin->MaximumHeightInLines(),Panic(EAknPanicOutOfRange));
	
    const CAknLayoutFont *font = AknLayoutUtils::LayoutFontFromId(aFontId, aCustomFont);
    
    aBaseline = CorrectBaseline( aEdwinParent.Height(), aBaseline, aFontId);
    
    // This puts baseline into a more natural definition where the baselins is an infinitely
    // thin imaginary line underneath the glyphs' baseline pixels:
    aBaseline += 1; 
    
	if (aSecondLineBaseline != 0)
        {
        aSecondLineBaseline = CorrectBaseline( aEdwinParent.Height(),aSecondLineBaseline, aFontId);    
        aSecondLineBaseline += 1; // This puts baseline into a more natural definition
        }

    if (IsParentRelative(aLeftMargin)) { aLeftMargin = aEdwinParent.Width() - ELayoutP + aLeftMargin; }
    if (IsParentRelative(aRightMargin)) { aRightMargin = aEdwinParent.Width() - ELayoutP + aRightMargin; }
    if (IsParentRelative(aWidth)) { aWidth = aEdwinParent.Width() - ELayoutP + aWidth; }

	if (IsEmpty(aLeftMargin)) { aLeftMargin = aEdwinParent.Width() - aRightMargin - aWidth; }
	if (IsEmpty(aRightMargin)) { aRightMargin = aEdwinParent.Width() - aLeftMargin - aWidth; }
	if (IsEmpty(aWidth)) { aWidth = aEdwinParent.Width() - aLeftMargin - aRightMargin; }

    TAknTextDecorationMetrics metrics( aFontId );
    LayoutEdwinScalableWithCorrectedParametersAndDecorationMetrics(
                                 aEdwin, 
                                 aEdwinParent, 
                                 font, 
                                 aColor, 
                                 aLeftMargin, 
                                 aRightMargin, 
                                 aBaseline,
                                 aWidth, 
                                 aJustification, 
                                 aNumberOfLinesShown, 
                                 aSecondLineBaseline, 
                                 aOverrideColor,
                                 metrics,
                                 EFalse, // Legacy behaviour is not to constrain editor to stay inside parent 
                                 aMinimizeEdwinView);
    }

void AknLayoutUtilsHelpers::GetEditorVerticalPositionWithinParent(
    TInt aParentHeight,
    const TAknTextLineLayout& aLayout, 
    TInt& aVerticalPosOfEditor )
    {

    TInt newBaseline = CorrectBaseline( aParentHeight, aLayout.iB, aLayout.FontId());
    
    // This puts baseline into a more natural definition where the baselins is an infinitely
    // thin imaginary line underneath the glyphs' baseline pixels:
    newBaseline += 1; 
    
    TInt fontId = aLayout.FontId();
    const CAknLayoutFont* font = AknLayoutUtils::LayoutFontFromId( fontId, NULL );
        
    TAknTextDecorationMetrics decorationMetrics( aLayout.FontId() );

    // Editor margin" is used to position the TextView inside the editor
    // May have to modify top and bottom margins for font characteristics
    // "fontAscent" variable stands for total (+ve) distance from the baseline to the top of the Scalable layout textpane.
    TInt topMargin;
    TInt bottomMargin;
    decorationMetrics.GetTopAndBottomMargins( topMargin, bottomMargin);
    aVerticalPosOfEditor = 
        EditorVerticalPositionWithinParent( font, newBaseline, topMargin );
    }

TInt AknLayoutUtilsHelpers::EditorVerticalPositionWithinParent(
    const CAknLayoutFont* aLayoutFont,
    TInt aFirstBaseline,
    TInt aTopMargin )
    {
    return aFirstBaseline - (aLayoutFont->TextPaneTopToBaseline() + aTopMargin );
    }



// End of file

