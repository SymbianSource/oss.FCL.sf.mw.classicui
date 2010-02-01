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


#include <coefont.h>

// 
// class TCoeFont 
// 


/** constructor

@publishedAll
@released
*/
EXPORT_C TCoeFont::TCoeFont(TLogicalSize aSize, TInt aStyle, TInt aFlags) : 
                iLogicalSize(aSize), iHeightInPixels(0), iStyle(aStyle), iFlags(aFlags) 
        { 
        ASSERT(!(iStyle&ESuper && iStyle&ESub));        // Super and sub not allowed at once!         
        } 
        

/** constructor

@publishedAll
@released
*/
EXPORT_C TCoeFont::TCoeFont(TInt aHeightInPixels, TInt aStyle, TInt aFlags) : 
                iLogicalSize(EUndefinedSize), iHeightInPixels(aHeightInPixels), iStyle(aStyle), iFlags(aFlags) 
        {
        ASSERT(!(iStyle&ESuper && iStyle&ESub));        // Super and sub not allowed at once!
        }         

/** Copy constructor

@publishedAll
@released
*/
EXPORT_C TCoeFont::TCoeFont(const TCoeFont& aFont) 
    { 
    iLogicalSize = aFont.iLogicalSize; 
    iHeightInPixels = aFont.iHeightInPixels; 
    iStyle = aFont.iStyle; 
    iFlags = aFont.iFlags; 
    iTypeface = aFont.iTypeface;         
    iSpare = aFont.iSpare; 
    } 

EXPORT_C TCoeFont::TCoeFont() 
		: iLogicalSize(EUndefinedSize)
		{
		}

/** Return a default "normal" font

@publishedAll
@released
*/
EXPORT_C TCoeFont TCoeFont::NormalFont(TInt aFlags) 
        { 
        return TCoeFont(EMedium, EPlain, aFlags);
        } 
        
/** Return a default "legend" font

@publishedAll
@released
*/
EXPORT_C TCoeFont TCoeFont::LegendFont(TInt aFlags) 
        { 
        return TCoeFont(EMedium, EBold, aFlags);
        } 
        
/** Return a default "annotation" font

@publishedAll
@released
*/
EXPORT_C TCoeFont TCoeFont::AnnotationFont(TInt aFlags) 
        { 
        return TCoeFont(ESmall, EPlain, aFlags);
        } 
        
/** Return a default "title" font

@publishedAll
@released
*/
EXPORT_C TCoeFont TCoeFont::TitleFont(TInt aFlags) 
        { 
        return TCoeFont(ELarge, EBold, aFlags);
        } 

/** Return this font's logical size
*/
EXPORT_C TCoeFont::TLogicalSize TCoeFont::LogicalSize() const 
        { 
        return iLogicalSize; 
        } 

/** Return this font's height in pixels

@publishedAll
@released
*/
EXPORT_C TInt TCoeFont::HeightInPixels() const 
        { 
        return iHeightInPixels;         
        } 
        
/** Return this font's style

@publishedAll
@released
*/
EXPORT_C TFontStyle TCoeFont::Style() const 
        { 
        return TFontStyle((iStyle&EItalic ? EPostureItalic : EPostureUpright), 
                                                (iStyle&EBold ? EStrokeWeightBold : EStrokeWeightNormal), 
                                                (iStyle&ESuper ? EPrintPosSuperscript : (iStyle&ESub ? EPrintPosSubscript : EPrintPosNormal))); 
        } 

/** Says whether this font can be zoomed or not

@publishedAll
@released
*/
EXPORT_C TBool TCoeFont::IsNonZooming() const 
        { 
        return (iFlags & ENonZooming); 
        } 

/** Compare two TCoeFont objects
*/
TInt TCoeFont::Compare(const TCoeFont& aFirst, const TCoeFont& aSecond) 
    { 
    if(aFirst.iStyle - aSecond.iStyle) 
    	return (aFirst.iStyle - aSecond.iStyle); 
        
    if(aFirst.iLogicalSize - aSecond.iLogicalSize) 
        return (aFirst.iLogicalSize - aSecond.iLogicalSize); 
        
    if(aFirst.iHeightInPixels - aSecond.iHeightInPixels) 
        return (aFirst.iHeightInPixels - aSecond.iHeightInPixels); 
                        
    return (aFirst.iFlags - aSecond.iFlags); 
    } 
	

