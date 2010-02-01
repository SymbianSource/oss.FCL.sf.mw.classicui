/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test case for various list classes
*
*/


#include <eikclbd.h>
#include <aknlists.h>
#include <barsread.h>
#include <gulicon.h>
#include <AknIconUtils.h>
#include <akniconarray.h>

#include <bctestmix50.rsg>
#include <bctestmix50.mbg>
#include "bctestmix50patchcolumnbasecase.h"
#include "bctestmix50container.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// C++ Default constructor.
// ---------------------------------------------------------------------------
//
CBCTestMix50ListBaseCase::CBCTestMix50ListBaseCase( 
		CBCTestMix50Container* aContainer, CEikonEnv* aEikEnv) 
    : iContainer( aContainer ), iEikEnv( aEikEnv )
    {
    }

// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestMix50ListBaseCase::~CBCTestMix50ListBaseCase()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestMix50ListBaseCase::SetListBoxFromResourceL
// ---------------------------------------------------------------------------
//
void CBCTestMix50ListBaseCase::SetListBoxFromResourceL(
    CEikColumnListBox* aListBox, const TInt aResourceId )
    {
    if ( aListBox && aResourceId )
        {
        aListBox->SetContainerWindowL( *iContainer );        

        TResourceReader reader;
        iEikEnv->CreateResourceReaderLC( reader, aResourceId );
        aListBox->ConstructFromResourceL( reader );
        CleanupStack::PopAndDestroy(); // resource stuffs.
        }
    }

// ---------------------------------------------------------------------------
// CBCTestMix50ListBaseCase::SetListBoxFromResourceL
// ---------------------------------------------------------------------------
//
void CBCTestMix50ListBaseCase::SetListBoxFromResourceL(
    CEikFormattedCellListBox* aListBox, const TInt aResourceId )
    {
    if ( aListBox && aResourceId )
        {
        aListBox->SetContainerWindowL( *iContainer );        
        
        TResourceReader reader;
        iEikEnv->CreateResourceReaderLC( reader, aResourceId );
        aListBox->ConstructFromResourceL( reader );
        CleanupStack::PopAndDestroy(); // resource stuffs.        
        }
    }

// ---------------------------------------------------------------------------
// CBCTestMix50ListBaseCase::SetListBoxFromInnerDescriptionL
// ---------------------------------------------------------------------------
//
void CBCTestMix50ListBaseCase::SetListBoxFromInnerDescriptionL(
    CEikColumnListBox* aListBox, const TInt aFlags, CDesCArray* textArray )
    {
    if ( aListBox )
        {
        // Constructs listbox.
        aListBox->ConstructL( iContainer, aFlags );        
        
        if ( textArray )
            {
            // Sets list item from resource.
            aListBox->Model()->SetItemTextArray( textArray );
            aListBox->Model()->SetOwnershipType( ELbmOwnsItemArray );
            }        
        }
    }
    
// ---------------------------------------------------------------------------
// CBCTestMix50ListBaseCase::SetListBoxFromInnerDescriptionL
// ---------------------------------------------------------------------------
//
void CBCTestMix50ListBaseCase::SetListBoxFromInnerDescriptionL(
    CEikFormattedCellListBox* aListBox,
    const TInt aFlags,
    CDesCArray* textArray )
    {
    if ( aListBox )
        {
        // Constructs listbox.
        aListBox->ConstructL( iContainer, aFlags );
        
        if ( textArray )
            {
            // Sets list item from resource.
            aListBox->Model()->SetItemTextArray( textArray );
            aListBox->Model()->SetOwnershipType( ELbmOwnsItemArray );
            }        
        }
    }

// ---------------------------------------------------------------------------
// CBCTestMix50ListBaseCase::SetGraphicIconL
// ---------------------------------------------------------------------------
//
void CBCTestMix50ListBaseCase::SetGraphicIconL( CEikColumnListBox* aListBox )
    {
    if ( aListBox )
        {
        // Creates gul icon.
        CArrayPtr<CGulIcon>* icons = new( ELeave ) CAknIconArray(
            KBCTestListGraphicGulIconIndex );

        CleanupStack::PushL( icons );

        GraphicIconL( icons ); // Appends graphic data.

        // Sets graphics as ListBox icon.
        aListBox->ItemDrawer()->ColumnData()->SetIconArray( icons );

        CleanupStack::Pop();

        }
    }

// ---------------------------------------------------------------------------
// CBCTestMix50ListBaseCase::SetGraphicIconL
// ---------------------------------------------------------------------------
//
void CBCTestMix50ListBaseCase::SetGraphicIconL(
    CEikFormattedCellListBox* aListBox )
    {
    if ( aListBox )
        {
        // Creates gul icon.
        CArrayPtr<CGulIcon>* icons = new( ELeave ) CAknIconArray(
            KBCTestListGraphicGulIconIndex );

        CleanupStack::PushL( icons );

        GraphicIconL( icons ); // Appends graphic data.

        // Sets graphics as ListBox icon.
        aListBox->ItemDrawer()->FormattedCellData()->SetIconArrayL( icons );

        CleanupStack::Pop();
        }
    }

// ---------------------------------------------------------------------------
// CBCTestMix50ListBaseCase::GraphicIconL
// ---------------------------------------------------------------------------
//
void CBCTestMix50ListBaseCase::GraphicIconL( CArrayPtr<CGulIcon>* aIcons )
    {
    if ( aIcons )
        {
        // Appends icon.
        CreateIconAndAddToArrayL(aIcons, KBCTestListMbmFileName,
            EMbmBctestmix50Qgn_indi_marked_add, 
            EMbmBctestmix50Qgn_indi_marked_add_mask);
        }
    }

// ---------------------------------------------------------------------------
// CBCTestMix50ListBaseCase::CreateIconAndAddToArrayL
// Creates the icon and adds it to the array if it was successful
// ---------------------------------------------------------------------------
//
void CBCTestMix50ListBaseCase::CreateIconAndAddToArrayL( 
    CArrayPtr<CGulIcon>*& aIconsArray,
    const TDesC& aIconFile,
    TInt aBitmap, TInt aMask/* = -1*/)
    {
    CGulIcon* icon = CGulIcon::NewLC();
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    if (aMask >= 0)
        {
        AknIconUtils::CreateIconL( bitmap, mask, aIconFile, aBitmap, aMask);
        }
    else
        {
        bitmap = AknIconUtils::CreateIconL( aIconFile, aBitmap);
        }

    if (bitmap)
        {
        icon->SetBitmap(bitmap);
        if (mask)
            icon->SetMask(mask);
        aIconsArray->AppendL(icon);
        CleanupStack::Pop(icon);
        }
    else
        {
        CleanupStack::PopAndDestroy(icon);
        }
    }
