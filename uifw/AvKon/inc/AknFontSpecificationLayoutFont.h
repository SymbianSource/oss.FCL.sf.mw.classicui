/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
*   Interface for Series 60 layout font managed by series 60 font ids
*
*
*/

   
#ifndef AKNFONTIDLAYOUTFONT_H
#define AKNFONTIDLAYOUTFONT_H

#include "AknLayoutFont.h"

class CBitmapDevice;

NONSHARABLE_CLASS(CAknFontSpecificationLayoutFont) : public CAknLayoutFont
    {

    public:  // Constructors and destructor

    /**
    * Create a layout font object from the passed in font specification.  
    * The Font category within the specification is the primary determinant of the 
    * typeface that will be selected via fontprovider
    */
    static CAknFontSpecificationLayoutFont* NewL( 
        CBitmapDevice& aScreenDevice, 
        const TAknFontSpecification& aSpec );

    /**
    * Create a layout font object from the passed in Typeface and specification
    * The FontCategory within the TAknFontSpecifation copied into the constructed object is
    * is cleared (set to EAknFontCategoryUndefined).  Font matching will be performed based upon the
    * passed in typeface information. 
    */
    static CAknFontSpecificationLayoutFont* NewL( 
        CBitmapDevice& aScreenDevice, 
        const TTypeface& aTypeface,
        const TAknFontSpecification& aSpec );

    /**
    * C++ Destructor.
    */
    virtual ~CAknFontSpecificationLayoutFont();

    /**
    */
    void ConstructL();

    public: // New functions
    
    /**
    * Change the font specification and update the binding of the font
    * 
    * @param aFontId    The new font specification
    */
    void UpdateWithSpecification( const TAknFontSpecification& aSpec, const TTypeface& aTypeface );

    public: // Functions from CFont
     
    public:// Functions from CFbsFont
    
    private: // Functions from CAknLayoutFont
    CFbsFont* SupplyFont();
 
    TAknTextDecorationMetrics DoTextDecorationMetrics() const;

    TAknFontSpecification DoFontSpecification() const;

    TInt DoAscentForCharacter( TChar aCharacter ) const;

    void Reserved_1();

    private:

    /**
    * C++ Constructors.
    */
    CAknFontSpecificationLayoutFont( 
        CBitmapDevice& aScreenDevice, 
        const TAknFontSpecification& aSpec);

    CAknFontSpecificationLayoutFont( 
        CBitmapDevice& aScreenDevice, 
        const TTypeface& aTypeface,
        const TAknFontSpecification& aSpec );

    private:

    TAknFontSpecification iSpec;
    TTypeface iTypeface;
    TInt iFontProviderId;   // Identifier in FontProvider for a callback
    TBitFlags32 iFlags; 
    TInt iSpare;
    };

#endif
