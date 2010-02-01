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

class CWsScreenDevice;

NONSHARABLE_CLASS(CAknFontIdLayoutFont) : public CAknLayoutFont
    {

    public:  // Constructors and destructor

    /**
    * Create a layout font object from the passed in font id.
    */
    IMPORT_C static CAknFontIdLayoutFont* NewL( CWsScreenDevice& aScreenDevice, TInt aFontId );

    /**
    * C++ Destructor.
    */
    virtual ~CAknFontIdLayoutFont();

    /**
    */
    void ConstructL();

    public: // New functions
    
    /**
    * Extract the font id from the object
    * 
    * @return the identifier currently set in the font
    */
    IMPORT_C TInt FontId() const;

    /**
    * Change the font id and update the binding of the font
    * 
    * @param aFontId    The new font id.
    */
    IMPORT_C void UpdateId( TInt aFontId );

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
    * C++ Constructor.
    */
    CAknFontIdLayoutFont( CWsScreenDevice& aScreenDevice, TInt aFontId );

    private:

    TInt iFontId;
    TInt iFontProviderId; // Identifier in FontProvider for a callback

    };

#endif
