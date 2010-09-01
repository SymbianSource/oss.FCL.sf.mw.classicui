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
* Description:  Container
*
*/


#include "akncompagscontainer.h"
#include "akncompagsmodel.h"
#include "akncompags.hrh"

#include <bldvariant.hrh>
#include <akncompagsrsc.rsg>
#include <aknlists.h>
#include <StringLoader.h>
#include <AknUtils.h>
#include <cshelp/conset.hlp.hrh>
#include <gsfwviewuids.h>
#include <gslistbox.h>

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
void CAknCompaGSContainer::ConstructL( const TRect& aRect )
    {
    iListBox = new( ELeave ) CAknSettingStyleListBox;
    
    BaseConstructL( aRect, R_AKNCOMPAGS_VIEW_TITLE, R_AKNCOMPAGS_LBX );
    }


// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CAknCompaGSContainer::~CAknCompaGSContainer()
    {
    delete iListboxItemArray;
    delete iCompaModeStateItems;
    }

// --------------------------------------------------------------------------
// Construct a list box
// --------------------------------------------------------------------------
void CAknCompaGSContainer::ConstructListBoxL( TInt aResLbxId )
    {
    iListBox->ConstructL( this, EAknListBoxSelectionList );

    iListboxItemArray = CGSListBoxItemTextArray::NewL( aResLbxId,
        *iListBox, *iCoeEnv );
    iListBox->Model()->SetItemTextArray( iListboxItemArray );
    iListBox->Model()->SetOwnershipType( ELbmDoesNotOwnItemArray );

    iCompaModeStateItems = iCoeEnv->ReadDesC16ArrayResourceL(
            R_AKNCOMPAGS_STATE_SETTING_PAGE_LBX );

    CreateListBoxItemsL();
    }

// --------------------------------------------------------------------------
// Create list box items
// --------------------------------------------------------------------------
void CAknCompaGSContainer::CreateListBoxItemsL()
    {
    MakeCompaModeStateItemL();
    CAknCompaGSModel* model = CAknCompaGSModel::NewL();
    CleanupStack::PushL(model);
    UpdateCompaModeStateItemL(model->CompaAppState());
    CleanupStack::PopAndDestroy( model );
    }


// --------------------------------------------------------------------------
// Update list box item
// --------------------------------------------------------------------------
void CAknCompaGSContainer::UpdateListBoxL( TInt aFeatureId, 
                                              TInt aValue )
    {
    switch( aFeatureId )
        {
        case KCompaGSIdState:
            UpdateCompaModeStateItemL(aValue);
            break;
        default:
            break;
        }

    iListBox->HandleItemAdditionL();
    }

// --------------------------------------------------------------------------
// Make compa-mode setting visible
// --------------------------------------------------------------------------
void CAknCompaGSContainer::MakeCompaModeStateItemL()
    {
    iListboxItemArray->SetItemVisibilityL( KCompaGSIdState,
        CGSListBoxItemTextArray::EVisible );
    }

// --------------------------------------------------------------------------
// Update compa-mode setting item on display
// --------------------------------------------------------------------------
void CAknCompaGSContainer::UpdateCompaModeStateItemL(const TInt& aState)
    {
    HBufC* dynamicText = HBufC::NewLC( KGSBufSize128 );
    TPtr ptrBuffer ( dynamicText->Des() );

    ptrBuffer = ( *iCompaModeStateItems )[ aState ];

    iListboxItemArray->SetDynamicTextL( KCompaGSIdState, ptrBuffer );
    CleanupStack::PopAndDestroy( dynamicText );

    iListboxItemArray->SetItemVisibilityL( KCompaGSIdState,
        CGSListBoxItemTextArray::EVisible );
    }

// --------------------------------------------------------------------------
// Return currently selected listbox feature id
// --------------------------------------------------------------------------
TInt CAknCompaGSContainer::CurrentFeatureId( ) const
    {
    return iListboxItemArray->CurrentFeature( );
    }
