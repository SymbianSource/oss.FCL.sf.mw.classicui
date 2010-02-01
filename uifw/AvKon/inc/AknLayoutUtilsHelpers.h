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
*  Internal implementations of Avkon Layout Utilities
* 
*
*/


#ifndef __AKNLAYOUTUTILSHELPERS_H__
#define __AKNLAYOUTUTILSHELPERS_H__

#include <e32std.h>
#include <AknsConstants.h> // For TAknsQsnTextColorsIndex

class CEikEdwin;
class TAknTextLineLayout;
class CAknLayoutFont;
class TAknTextDecorationMetrics;
class CFont;

/**
* This class contains non-exported internal implementations of some of the functionality within
* AknLayoutUtils.
*
*/
class AknLayoutUtilsHelpers 
    {
public:               

/**
* This layout routine performs the core of the edwin layout.  All layout structures and fonts
* are to be processed to basic parameters by this point.  A font is passed in, and not font id.
* Baselines are defined in terms of the distance from the parent to the baseline of the font, 
* where both a parent boundary and baseline are inifinitely thin lines. (This differs from the 
* baseline definition used elsewhere in the layout system where a value smaller by 1 pixel is used.)*
*
* This routine may be used within Avkon by those writing editor layout routines
* 
* @param aEdwin                 a constructed edwin pointer 
* @param aEdwinParent           rectangle in which to position editor
* @param aFont                  constructed layout font pointer
* @param aColor                 color index
* @param aLeftMargin            space between editor and parent on the left       
* @param aRightMargin           space between editor and parent on the right
* @param aFirstBaseline         distance from parent top to 1st baseline. 
* @param aWidth                 Width of the text pane (For debug checking only)
* @param aJustification         text justification
* @param aNumberOfLinesShown    number of lines of editor to format
* @param aSecondLineBaseline    distance from parent top to 2nd baseline. 0 if not required
* @param aOverrideColor         a Skins color index if required
* @param decorationMetrics      Metrics for the highlights and cursor
* @param aEnsureEditorIsContainedByParent   Boolean to say whether the editor is allowed to
*                                           extend below the parent's bottom.
* @param aNumberOfVisibleLines  Outputs the number of lines formatted in the editor
*/
static void LayoutEdwinScalableWithCorrectedParametersAndDecorationMetrics(
                                 CEikEdwin *aEdwin, 
                                 const TRect &aEdwinParent, 
                                 const CAknLayoutFont *aFont, 
                                 TInt aColor, 
                                 TInt aLeftMargin, 
                                 TInt aRightMargin, 
                                 TInt aFirstBaseline, // naturally defined
                                 TInt aWidth,
                                 TInt aJustification, 
                                 TInt aNumberOfLinesShown, 
                                 TInt aSecondLineBaseline, //naturally defined
                                 TAknsQsnTextColorsIndex aOverrideColor,
                                 TAknTextDecorationMetrics& decorationMetrics,
                                 TBool aEnsureEditorIsContainedByParent,
                                 TInt& aNumberOfVisibleLines);
/**
* Layout helper routine used by majority of LayoutEdwin implementations
*  
* @param aEdwin                 a constructed edwin pointer 
* @param aEdwinParent           rectangle in which to position editor
* @param aFontId                An Avkon font id
* @param aColor                 color index
* @param aLeftMargin            space between editor and parent on the left       
* @param aRightMargin           space between editor and parent on the right
* @param aBaseline              distance from parent top to the top of the pixel row sitting on the baseline 
*                               of the glyphs. 
* @param aWidth                 width of editor
* @param aJustification         text justification
* @param aNumberOfLinesShown    number of lines of editor to format
* @param aSecondLineBaseline    distance from parent top to the top of the pixel row sitting on the baseline 
*                               of the glyphs in the 2nd line. 
* @param aOverrideColor         a Skins color index if required
* @param aCustomFont            font to be used if the layout has a font id = EFontCustom
* @param aMinimizeEdwinView     Editor view size is to be minimised (not used)
*/
static void LayoutEdwinScalable(CEikEdwin *aEdwin, 
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
                                 TBool aMinimizeEdwinView);
                                   
/**
* Routine to determine the height required for an editor.  The position of the editor
* relative to parent is also returned via the parameter aVerticalPositionOfEdwin.
* This gap between parent and editor is not included in the returned height.
*/

static TInt EdwinHeightFromLines(
        TInt aParentHeight,
        const TAknTextLineLayout& aLayout,
        TInt aBaselineSeparationOverRide,
        TInt aNumberOfLinesToShowOverRide,
        TInt& aVerticalPositionOfEdwin
        );
        
/**
* Routine to tell how many lines of laid out editor can fit into an edwin of a given 
* height.
*/
static TInt EdwinLinesWithinHeight (
        const TAknTextLineLayout& aLayout,
        TInt aBaselineSeparationOverRide,
        TInt aMaxHeight,
        TInt& aUsedHeight
        );


private:
/**
* Corrects the baseline back to pre-aknlayout2 conventions. 
*
* If the font is encoded, then the legacy baseline value definition is returned
* If not, then the passed-in value is returned.
*/
static TInt CorrectBaseline( TInt aParentHeight, TInt aBaseline, TInt aFontId);
        
/** 
* This routine emulates what the Symbian Form/Tagma component is doing 
* internally to get font height and depth.
*/
static void GetFontMaxHeightAndDepth( 
        const CFont* aFont, TInt& aMaxHeight, TInt& aMaxDepth); 

static TInt EdwinHeightFromLines (
        TInt aTextPaneHeight,
        TAknTextDecorationMetrics& aDecorationMetrics,
        TInt aBaselineSeparation,
        TInt aNumberOfLinesToShow
        );

 static TInt EdwinLinesWithinHeight (
        TInt aTextPaneHeight,
        TAknTextDecorationMetrics& aDecorationMetrics,
        TInt aBaselineSeparation,
        TInt aMaxHeight,
        TInt& aUsedHeight
        );
/**
* Routine to obtain the position of an editor's top relative to the parent.
* Because of the way baseline is specified in scalable layout, parent height is 
* required.
*/ 
static void GetEditorVerticalPositionWithinParent(
    TInt aParentHeight, 
    const TAknTextLineLayout& aLayout, 
    TInt& aRelativeVerticalPositionOfEditor );
        
static TInt EditorVerticalPositionWithinParent(
    const CAknLayoutFont* aLayoutFont,
    TInt aFirstBaseline,
    TInt aTopMargin );

    };
    
#endif //  __AKNLAYOUTUTILSHELPERS_H__

// End of file









