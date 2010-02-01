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
* Description:  A scaleable font with layout API
*
*/



// INCLUDE FILES
#include <w32std.h>
#include "AknLayoutFont.h"
#include <AknFontSpecification.h>
#include <aknenv.h>
#include "AknFontRegistry.h"

// CONSTANTS

// ============================ MEMBER FUNCTIONS ===============================

/**
* C++ Constructor.
*/
CAknLayoutFont::CAknLayoutFont( CBitmapDevice& aScreenDevice ) : 
    CFbsFont(), iScreenDevice(aScreenDevice)
    {
    Register();
    }

CAknLayoutFont::~CAknLayoutFont()
    {
    Deregister();
    iScreenDevice.ReleaseFont(iNonDynamicFont);
    }  


EXPORT_C void CAknLayoutFont::Update()
    {
    CFbsFont* newNonDynamicFont = NULL;

    // Ask concrete type for a font
    TRAPD(err, newNonDynamicFont = SupplyFont());

    if (err == KErrNone)
        {
        // Release the old 'real' font ...
        iScreenDevice.ReleaseFont(iNonDynamicFont);

        // Copy this new font into the current object 
        iNonDynamicFont = newNonDynamicFont;
        (void) Duplicate( iNonDynamicFont->Handle() );
        }
    }

EXPORT_C TInt CAknLayoutFont::MaxAscent() const
    {
    return iExcessAscent + AscentInPixels();
    }

EXPORT_C TInt CAknLayoutFont::MaxDescent() const
    {
    return iExcessDescent + DescentInPixels();
    }

EXPORT_C TInt CAknLayoutFont::TextPaneTopToBaseline() const
    {
    return iTextPaneHeight - BaselineToTextPaneBottom();
    }

EXPORT_C TInt CAknLayoutFont::BaselineToTextPaneBottom() const
    {
    return ( iBottomShortfall + MaxDescent() );
    }

EXPORT_C TInt CAknLayoutFont::TextPaneHeight() const
    {
    return iTextPaneHeight;
    }

void CAknLayoutFont::SetExcessAscent( TInt aExcessAscent )
    {
    iExcessAscent = aExcessAscent;
    }

void CAknLayoutFont::SetExcessDescent( TInt aExcessDescent )
    {
    iExcessDescent = aExcessDescent;
    }

void CAknLayoutFont::SetBottomShortfall( TInt aBottomShortfall )
    {
    iBottomShortfall = aBottomShortfall;
    }

void CAknLayoutFont::SetTextPaneHeight( TInt aTextPaneHeight )
    {
    iTextPaneHeight = aTextPaneHeight;
    }

TInt CAknLayoutFont::AscentForCharacter( TChar aCharacter ) const
    {
    return DoAscentForCharacter( aCharacter );
    }

TInt CAknLayoutFont::DoAscentForCharacter( TChar /*aCharacter*/ ) const
    {
    // Default implementation. 
    return AscentInPixels();
    }

EXPORT_C const CAknLayoutFont* CAknLayoutFont::AsCAknLayoutFontOrNull( const CFont* aFont )
    {
    const CAknLayoutFont* layoutFontOrNull = NULL;
    if ( AVKONENV->FontRegistry().IsRegistered( aFont ) )
        {
        layoutFontOrNull = static_cast<const CAknLayoutFont*>( aFont );
        }
    return layoutFontOrNull;
    }

EXPORT_C TAknTextDecorationMetrics CAknLayoutFont::TextDecorationMetrics() const
    {
    return DoTextDecorationMetrics();
    }

EXPORT_C TAknFontSpecification CAknLayoutFont::FontSpecification() const
    {
    return DoFontSpecification();
    }

void CAknLayoutFont::Register()
    {
    AVKONENV->FontRegistry().RegisterFont( this );
    }

void CAknLayoutFont::Deregister()
    {
    AVKONENV->FontRegistry().DeRegisterFont( this );
    }

void CAknLayoutFont::CAknLayoutFont_Reserved_1()
    {}

EXPORT_C TAknFontCategory CAknLayoutFont::FontCategory() const
    {
    TAknFontSpecification spec = FontSpecification();
    return spec.FontCategory();
    }
    
TFontSpec CAknLayoutFont::DoFontSpecInTwips() const
    {
    // Implementation should be (prior to the iHeight patching at the end):
    //    TFontSpec fontSpec = CFbsFont::DoFontSpecInTwips(); currently private
    // So for now, have copied implementation from CFbsFont:
    TFontSpec fontSpec;
    if (!iHandle)
        return fontSpec;
    fontSpec = Address()->FontSpecInTwips();    
    // Patch up the iHeight for the correct device's twips/pixel ratio
    fontSpec.iHeight = iScreenDevice.VerticalPixelsToTwips( HeightInPixels() );   
    return fontSpec;
    }

CBitmapDevice& CAknLayoutFont::BitmapDevice() const
    {
    return iScreenDevice;
    }

//  End of File

