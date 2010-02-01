/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case for various list classes
*
*/









#include <eikclbd.h>
#include <aknlists.h>
#include <barsread.h>
#include <gulicon.h>
#include <AknIconUtils.h>
#include <akniconarray.h>

#include <bctestlist.rsg>
#include <bctestlist.mbg>
#include "bctestlistbasecase.h"
#include "bctestlistcontainer.h"


// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// C++ Default constructor.
// ----------------------------------------------------------------------------
//
CBCTestListBaseCase::CBCTestListBaseCase( 
    CBCTestListContainer* aContainer, CEikonEnv* aEikEnv) 
    : iContainer( aContainer ), iEikEnv( aEikEnv )
    {
    }

// ----------------------------------------------------------------------------
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestListBaseCase::~CBCTestListBaseCase()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestListBaseCase::SetListBoxFromResourceL
// Sets listbox from resource using ConstructFromResourceL() of
// CEikColumnListBox class.
// ----------------------------------------------------------------------------
//
void CBCTestListBaseCase::SetListBoxFromResourceL(
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

// ----------------------------------------------------------------------------
// CBCTestListBaseCase::SetListBoxFromResourceL
// Sets listbox from resource using ConstructFromResourceL() of
// CEikFormattedCellListBox class.
// ----------------------------------------------------------------------------
//
void CBCTestListBaseCase::SetListBoxFromResourceL(
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

// ----------------------------------------------------------------------------
// CBCTestListBaseCase::SetListBoxFromInnerDescriptionL
// Sets listbox from inner description using ConstructL() of CEikColumnListBox
// class.
// ----------------------------------------------------------------------------
//
void CBCTestListBaseCase::SetListBoxFromInnerDescriptionL(
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
    
// ----------------------------------------------------------------------------
// CBCTestListBaseCase::SetListBoxFromInnerDescriptionL
// Sets listbox from inner description using ConstructL() of
// CEikFormattedCellListBox class.
// ----------------------------------------------------------------------------
//
void CBCTestListBaseCase::SetListBoxFromInnerDescriptionL(
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

// ----------------------------------------------------------------------------
// CBCTestListBaseCase::SetGraphicIconL( CEikColumnListBox* )
// Sets graphic icon using listbox as CEikColumnListBox.
// ----------------------------------------------------------------------------
//
void CBCTestListBaseCase::SetGraphicIconL( CEikColumnListBox* aListBox )
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

// ----------------------------------------------------------------------------
// CBCTestListBaseCase::SetGraphicIconL
// Sets graphic icon using listbox as CEikFormattedCellListBox.
// ----------------------------------------------------------------------------
//
void CBCTestListBaseCase::SetGraphicIconL(
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


// ----------------------------------------------------------------------------
// CBCTestListBaseCase::GraphicIconL
// Appends graphics data.
// ----------------------------------------------------------------------------
//
void CBCTestListBaseCase::GraphicIconL( CArrayPtr<CGulIcon>* aIcons )
    {
    if ( aIcons )
        {
        // Appends icon.
        CreateIconAndAddToArrayL(aIcons, KBCTestListMbmFileName,
            EMbmBctestlistQgn_indi_marked_add, 
            EMbmBctestlistQgn_indi_marked_add_mask);
        }
    }

// ----------------------------------------------------------------------------
// CBCTestListBaseCase::CreateIconAndAddToArrayL
// Creates the icon and adds it to the array if it was successful
// ----------------------------------------------------------------------------
//
void CBCTestListBaseCase::CreateIconAndAddToArrayL( 
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
