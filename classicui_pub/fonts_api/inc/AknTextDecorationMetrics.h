/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef AKNTEXTDECORATIONMETRICS_H
#define AKNTEXTDECORATIONMETRICS_H

#include <e32std.h>
#include <AknFontCategory.hrh>

class CFont;
class TAknFontSpecification;
class TAknWindowComponentLayout;
class TAknTextComponentLayout;

/**
* This class contains information to decorate a text with highlights, cursors and margins
*
* Construction is performed driven by metrics and style derived from the various object that are 
* used in the different contstructors. The metrics used are height, weight, and posture.
* 
* From Series 60 font id, the current layout is accessed to provide metrics and style info.
* From a CFont object, the font's own accessible metrics and styles are accessed (e.g. HeightInPixels())
* From a TFontSpec object, the height and style are extracted via its APIs.
* 
*  @lib avkon.dll
*  @since 2.8
*
*  @internal
*/
class TAknTextDecorationMetrics
    {
public:
    // C++ Constructors
    /**
    * Construct the object with values that are correct for the given font identifier.
    *
    * @param    A Series 60 Font id
    */
    IMPORT_C TAknTextDecorationMetrics( TInt aFontId );

    /**
    * Construct the object with values that are correct for the given Symbian Font
    * A null pointer passed in will result in a default set of metrics.
    *
    * @param    A generic Symbian font object pointer
    */
    IMPORT_C TAknTextDecorationMetrics( const CFont* aFont );

    /**
    * Construct the object with values that are correct for the given Series 60 Font Specification.
    * This constructor depends upon the font height and boldness being set in the font specifcation 
    * object.
    *
    * @param    A Series 60 font specification
    */
    IMPORT_C TAknTextDecorationMetrics( const TAknFontSpecification& aFontSpecification );

public:
    /**
    * Fetch the values in pixels for the distances reserved for cursor and highlights 
    * that extend beyond the font's rendering area (where the glyphs draw)
    *
    * Values are positive for any normal margin - one that is outside the glyphs area.
    *
    * @param aLeft   number of extra columns of pixels left of glyphs for additional graphics
    * @param aRight   number of extra rows of pixels right of glyphs for additional graphics
    */
    IMPORT_C void GetLeftAndRightMargins( TInt& aLeft, TInt& aRight ) const;

    /**
    * Fetch the values in pixels for the distances reserved for cursor and highlights 
    * that extend beyond the font's rendering area (where the glyphs draw)
    *
    * Values are positive for any normal margin - one that is outside the glyphs area.
    *
    * @param aTop   number of extra rows of pixels above font ascent for additional graphics
    * @param aTop   number of extra rows of pixels below font descent for additional graphics
    */
    IMPORT_C void GetTopAndBottomMargins( TInt& aTop, TInt& aBottom ) const;

    /**
    * Width of the cursor in pixels. This width is to be used when cursor is drawn
    * rather than an image.
    *
    * @return   Width of the cursor in pixels.
    */
    IMPORT_C TInt CursorWidth() const;

    /**
    * Offset distance measured from the bottom of the baseline row of pixels to the 
    * bottom of the underline.  E.g. if this method returns 3, and the underline height 
    * is 1, then there are 2 pixel rows of gap between the baseline of glyphs and the 
    * underline.
    * 
    * The baseline referred to is the natural baseline of the glyph, not the formal
    * baseline reported by the font. To draw the underline, it may be necessary, depending
    * on how the font is compounded, to find the baseline (i.e. ascent) of individual character codes'
    * glyphs. 
    *
    * @return   Offset distance measured from bottom of glyphs baseline to bottom of underline graphics
    */
    IMPORT_C TInt BaselineToUnderlineOffset() const;

    /**
    * Height (i.e. thickness) of the drawing of the underline
    * Positive for any visible line. e.g. a value of 1, means one row of pixels is drawn.
    *
    * @return   Number of rows pixels in the underline graphics
    */
    IMPORT_C TInt UnderlineHeight() const;

private: // Internal routines for construction
    void SetMetricsFromSizeAndBoldness( 
        TAknFontCategory aCategory, 
        TInt aTextHeight, 
        TBool aIsBold );
    void SetDefaultMetrics( 
        TAknFontCategory aCategory, 
        TBool aIsBold );
    void GetHighlightLayoutsFromCategory( 
        TAknFontCategory aCategory,
        TAknWindowComponentLayout& aHighlightParentPane,
        TAknTextComponentLayout& aHighlightTextPane,
        TAknWindowComponentLayout& aHighlightPane ) const;
    void GetCursorLayoutsFromCategory( 
        TAknFontCategory aCategory,
        TAknWindowComponentLayout& aCursorLayout,
        TAknWindowComponentLayout& aCursorLayoutGraphic ) const;

private:
	TInt16 iTopMargin;
	TInt16 iBottomMargin;
	TInt16 iLeftMargin;
	TInt16 iRightMargin;
    TInt16 iCursorWidth;
    TInt16 iBaselineToUnderlineOffset;
    TInt16 iUnderlineHeight;
    TInt16 iSpare;
    };

#endif
// End of File
