/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Series 60 layout font constructed from a font specification or a 
*  combination of font specification plus typeface or typeface alias
*
*/


// INCLUDE FILES
#include <eikdef.h>
#include <eikenv.h>
#include <aknenv.h>

#include "AknPanic.h"
#include "AknFontSpecificationLayoutFont.h"
#include <AknFontSpecification.h>

#include <AknFontProvider.h>
#include <AknFontProviderSuppliedMetrics.h>

// CONSTANTS

enum TAknFontSpecificationLayoutFontFlags
	{
	EUseTypeface = 0
	};

// ============================ MEMBER FUNCTIONS ===============================

CAknFontSpecificationLayoutFont* CAknFontSpecificationLayoutFont::NewL( 
    CBitmapDevice& aScreenDevice, 
    const TAknFontSpecification& aSpec )
    {
    CAknFontSpecificationLayoutFont* self = 
        new (ELeave) CAknFontSpecificationLayoutFont( aScreenDevice, aSpec);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(); //self
    return self;
    }

CAknFontSpecificationLayoutFont* CAknFontSpecificationLayoutFont::NewL( 
    CBitmapDevice& aScreenDevice, 
    const TTypeface& aTypeface,
    const TAknFontSpecification& aSpec )
    {
	CAknFontSpecificationLayoutFont* self = 
        new (ELeave) CAknFontSpecificationLayoutFont( aScreenDevice, aTypeface, aSpec);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(); //self
	return self;
    }


CAknFontSpecificationLayoutFont::~CAknFontSpecificationLayoutFont()
    {
    }

void CAknFontSpecificationLayoutFont::ConstructL()
    {
    CAknLayoutFont::Update();
    }

/** 
* Implementation of the framework method for this class
*
*/
CFbsFont* CAknFontSpecificationLayoutFont::SupplyFont()
    {
    TAknFontProviderSuppliedMetrics info;
    CFbsFont* font;
    // Use Font provisioning.
    if ( iFlags[EUseTypeface] )
        {       
        font = AknFontProvider::CreateFontFromTypefaceAndMetrics( BitmapDevice(), iTypeface, iSpec, info, iFontProviderId );
        }
    else
        {
        // Use category matching. There is no ID
        font = AknFontProvider::CreateFontFromMetrics( BitmapDevice(), 0, iSpec, info, iFontProviderId );       
        }

    SetExcessAscent( info.ExcessAscent() );
    SetExcessDescent( info.ExcessDescent() );
    SetBottomShortfall( info.MaxDescentToTextPaneBottom() );
    return font;
    }
    
TAknTextDecorationMetrics CAknFontSpecificationLayoutFont::DoTextDecorationMetrics() const
    {
    return TAknTextDecorationMetrics( iSpec );
    }

TAknFontSpecification CAknFontSpecificationLayoutFont::DoFontSpecification() const
    {
    return TAknFontSpecification( iSpec );
    }

TInt CAknFontSpecificationLayoutFont::DoAscentForCharacter( TChar aCharacter ) const
    {
    TInt ascent = AscentInPixels();

    if ( AknFontProvider::HasBaselineCorrection( iFontProviderId ) )
        {
        TInt baselineLift;
        TInt denominatorIfFractional;
        TInt err = AknFontProvider::BaselineDeltaForCharacter( iFontProviderId, 
                                                     aCharacter, 
                                                     baselineLift, 
                                                     denominatorIfFractional );
        if ( err == KErrNone )
            {
            if ( denominatorIfFractional > 0)
                {
                ascent -= ( baselineLift * ascent ) / denominatorIfFractional;
                }
            else
                {
                ascent -= baselineLift;
                }
            }
        }
    __ASSERT_DEBUG( ascent > 0, Panic( EAknPanicInvalidValue ) );
    return ascent;
    }

/**
* C++ Constructors.
*/
CAknFontSpecificationLayoutFont::CAknFontSpecificationLayoutFont( 
    CBitmapDevice& aScreenDevice, 
    const TTypeface& aTypeface, 
    const TAknFontSpecification& aSpec ) : 
    CAknLayoutFont(aScreenDevice), iSpec(aSpec), iTypeface(aTypeface) 
    {
    // When constructed from typeface and metrics, the typeface information replaces the role of category
    // completely. Set it to "undefined"
    iSpec.SetFontCategory( EAknFontCategoryUndefined);
    iFlags.Set(EUseTypeface);    

    // Keep versions of text pane height in step
    __ASSERT_ALWAYS(iSpec.Units() == TAknFontSpecification::EPixels, Panic(EAknPanicInconsistentUnits) );
    SetTextPaneHeight( iSpec.TextPaneHeight() );
    }
    
CAknFontSpecificationLayoutFont::CAknFontSpecificationLayoutFont( 
    CBitmapDevice& aScreenDevice, 
    const TAknFontSpecification& aSpec) : 
    CAknLayoutFont(aScreenDevice), iSpec(aSpec) 
    {
    // Keep versions of text pane height in step
    __ASSERT_ALWAYS(iSpec.Units() == TAknFontSpecification::EPixels, Panic(EAknPanicInconsistentUnits) );
    SetTextPaneHeight( iSpec.TextPaneHeight() ); 
    }


void CAknFontSpecificationLayoutFont::Reserved_1()
    {}


//  End of File
