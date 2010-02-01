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
* Description:  Series 60 layout font constructed from a font id.
*
*/


// INCLUDE FILES
#include <eikdef.h>
#include <eikenv.h>
#include <aknenv.h>
#include "AknFontIdLayoutFont.h"
#include <AknFontSpecification.h>
#include <CdlEngine.h>

#include <AknFontProvider.h>
#include <AknFontProviderSuppliedMetrics.h>
#include <AknFontId.h>

// CONSTANTS

// ============================ MEMBER FUNCTIONS ===============================

EXPORT_C CAknFontIdLayoutFont* CAknFontIdLayoutFont::NewL( 
    CWsScreenDevice& aScreenDevice, 
    TInt aFontId )
    {
	CAknFontIdLayoutFont* self = new (ELeave) CAknFontIdLayoutFont( aScreenDevice, aFontId);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(); //self
	return self;
    }

CAknFontIdLayoutFont::~CAknFontIdLayoutFont()
    {
    }

void CAknFontIdLayoutFont::ConstructL()
    {
    CAknLayoutFont::Update();
    }

/** 
* Implementation of the framework method for this class
*
*/
CFbsFont* CAknFontIdLayoutFont::SupplyFont ()
    {
    TAknFontProviderSuppliedMetrics info;
    CFbsFont* font(0);

    // Need to check if CDL is initialized if the font is not encoded
    TInt fontId;
    if ( TAknFontId::IsEncodedFont(iFontId) || CdlEngine::IsCdlEngineCreated() )
        {
        fontId = iFontId;
        }
    else
        {
        // Fall-back in case of no initialization whatsoever. Use the special fontid for this purpose
        fontId = TAknFontId::FontIdForStartupNormalFont();
        }

    TAknFontSpecification spec( fontId );
    // Use Font provisioning;
    font = AknFontProvider::CreateFontFromMetrics( BitmapDevice(), fontId, spec, info, iFontProviderId );
    SetTextPaneHeight( spec.TextPaneHeight() );

    SetExcessAscent( info.ExcessAscent() );
    SetExcessDescent( info.ExcessDescent() );
    SetBottomShortfall( info.MaxDescentToTextPaneBottom() );
 
    return font;
    }
    
TAknTextDecorationMetrics CAknFontIdLayoutFont::DoTextDecorationMetrics() const
    {
    return TAknTextDecorationMetrics( iFontId );
    }

TAknFontSpecification CAknFontIdLayoutFont::DoFontSpecification() const
    {
    return TAknFontSpecification( iFontId );
    }

EXPORT_C TInt CAknFontIdLayoutFont::FontId() const
    { return iFontId;}

EXPORT_C void CAknFontIdLayoutFont::UpdateId( TInt aFontId )
    {
    iFontId = aFontId;
    Update();
    };

TInt CAknFontIdLayoutFont::DoAscentForCharacter( TChar aCharacter ) const
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
    return ascent;
    }

/**
* C++ Constructor.
*/
CAknFontIdLayoutFont::CAknFontIdLayoutFont( CWsScreenDevice& aScreenDevice, TInt aFontId ) : 
    CAknLayoutFont(aScreenDevice), iFontId(aFontId)
    {}

void CAknFontIdLayoutFont::Reserved_1()
    {}

//  End of File

