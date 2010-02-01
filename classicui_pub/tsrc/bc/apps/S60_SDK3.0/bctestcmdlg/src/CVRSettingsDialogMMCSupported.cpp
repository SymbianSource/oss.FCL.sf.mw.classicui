/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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







#include <bctestcmdlg.rsg>
#include <AknLists.h>
#include "CVRSettingsDialogMMCSupported.h"
#include <hlplch.h>

#include <CAknMemorySelectionSettingItem.h>
#include <aknnotewrappers.h>

#include "bctestcmdlg.hrh"

CVRSettingsDialog::~CVRSettingsDialog()
    {
	iSettingItemArray.ResetAndDestroy();
    }

CVRSettingsDialog* CVRSettingsDialog::NewL()
    {
    CVRSettingsDialog* self = new( ELeave ) CVRSettingsDialog;
	CleanupStack::PushL( self );
	self->ConstructL( R_VR_SETTINGS_MENUBAR );
	CleanupStack::Pop();
    return self;
    }

TBool CVRSettingsDialog::OkToExitL( TInt aButtonId )
	{
	if ( aButtonId == EAknSoftkeyOptions )
        {
        DisplayMenuL();
        return EFalse;
        }

	TInt settingItemCount( iSettingItemArray.Count() );

	for ( TInt i( 0 ); i < settingItemCount; i++ )
		{
		iSettingItemArray.At( i )->StoreL();
		}

	return ETrue;
	}

void CVRSettingsDialog::PreLayoutDynInitL()
	{
	// Convert the internal memory enumeration to CFD enumeration
	CAknSettingStyleListBox* listBox = static_cast< CAknSettingStyleListBox* >
										( Control( EVRSettingsListboxId ) );
	User::LeaveIfNull( listBox );

    CAknSettingItem* settingItem;
    HBufC* itemTitle;
   	TInt id( 0 );

	// Create the memo store item
	settingItem =
				new( ELeave ) CAknMemorySelectionSettingItem( 0, iMemoStore );
	CleanupStack::PushL( settingItem );

	// Set memo store item's title
	itemTitle = iCoeEnv->AllocReadResourceLC( R_QTN_VOREC_SET_STORE );
	settingItem->ConstructL( EFalse, id, *itemTitle, NULL, 0,
													EAknCtPopupSettingList );
	CleanupStack::PopAndDestroy();	// itemTitle

	// Add memo store item to the settings array
	iSettingItemArray.AppendL( settingItem );
	CleanupStack::Pop();	// settingItem
	id++;

	CTextListBoxModel* model = listBox->Model();
	model->SetItemTextArray( &iSettingItemArray );
	// Ownership retained by us
	model->SetOwnershipType( ELbmDoesNotOwnItemArray );

	iSettingItemArray.RecalculateVisibleIndicesL();
	listBox->CreateScrollBarFrameL( ETrue );
	listBox->ScrollBarFrame()->SetScrollBarVisibilityL(
						CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
	listBox->HandleItemAdditionL();
	listBox->SetListBoxObserver( this );
	listBox->UpdateScrollBarsL();

	}

void CVRSettingsDialog::HandleListBoxEventL( CEikListBox* aListBox,
											 TListBoxEvent aEventType )
	{
	TInt index( aListBox->CurrentItemIndex() );
		if ( index >=0 )	// index is -1 if there are no items in the list
			{
			iSettingItemArray.At( index )->EditItemL( 
				aEventType == EEventEditingStarted );
			aListBox->DrawItem( index );
			}
	}

void CVRSettingsDialog::ProcessCommandL( TInt aCommandId )
	{
	HideMenu();
	switch ( aCommandId )
		{
		case ECmdChange:
			{
			CEikListBox* listBox = static_cast< CEikListBox* >( Control( EVRSettingsListboxId ) );
			HandleListBoxEventL( listBox, EEventEditingStarted );
			break;
			}
		case EEikCmdExit:
			{
			TryExitL( EEikCmdExit );
			CEikonEnv::Static()->EikAppUi()->HandleCommandL( aCommandId );
			break;
			}
		default:
			{
			CEikonEnv::Static()->EikAppUi()->HandleCommandL( aCommandId );
			break;
			}
		}
	}
