/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/



#include <pathinfo.h> //PathInfo
#include <driveinfo.h> //DriveInfo

#include "CAknMemorySelectionSettingItem.h"
#include "AknCFDUtility.h"

// ============================ MEMBER FUNCTIONS =============================

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItem::CAknMemorySelectionSettingItem
// ---------------------------------------------------------------------------
//
EXPORT_C CAknMemorySelectionSettingItem::CAknMemorySelectionSettingItem(
    TInt aIdentifier,
    CAknMemorySelectionSettingPage::TMemory& aSelectedMemory )
    :   CAknSettingItem( aIdentifier ),
        iExternalData( aSelectedMemory )
    {
    }

// Destructor
EXPORT_C CAknMemorySelectionSettingItem::~CAknMemorySelectionSettingItem()
    {
    delete iSettingPage;
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItem::CompleteConstructionL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemorySelectionSettingItem::CompleteConstructionL()
    {
    if( !iSettingPage )
        {
        iSettingPage =
            CAknMemorySelectionSettingPage::NewL( SettingPageResourceId() );
        }
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItem::EditItemL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemorySelectionSettingItem::EditItemL( TBool aCalledFromMenu )
    {
    // This in case application hasn't called CompleteConstructionL()
    CompleteConstructionL();
    
	  if( aCalledFromMenu )
        {
        // Changed with Options/Change
        iSettingPage->ExecuteL( iInternalData );
        }
    else
        {
        // Changed with selection key
        TDriveNumber mmcDrive;
        User::LeaveIfError(
            DriveInfo::GetDefaultDrive( DriveInfo::EDefaultRemovableMassStorage,
                                        ( TInt& )mmcDrive ) );
        if( iSettingPage->NumberOfItems() != 2 ||
            AknCFDUtility::DriveStatusL( mmcDrive )  != EDriveOK )
            {
            // Does not qualify as binary pop-up setting page
            // with two available values
            iSettingPage->ExecuteL( iInternalData );
            }
        else
            {
            // Two items in list, function as binary pop-up setting page
            if( iInternalData == CAknMemorySelectionSettingPage::EMemoryCard )
                {
                iInternalData = CAknMemorySelectionSettingPage::EPhoneMemory;
                }
            else
                {
                iInternalData = CAknMemorySelectionSettingPage::EMemoryCard;
                }
            }
        }
    UpdateListBoxTextL();
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItem::LoadL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemorySelectionSettingItem::LoadL()
    {
    iInternalData = iExternalData;
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItem::StoreL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemorySelectionSettingItem::StoreL()
    {
    iExternalData = iInternalData;
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItem::SettingTextL
// ---------------------------------------------------------------------------
//
EXPORT_C const TDesC& CAknMemorySelectionSettingItem::SettingTextL()
    {
    // This in case application hasn't called CompleteConstructionL()
    CompleteConstructionL();

    TInt memoryIndex( iInternalData );
    if( iInternalData == CAknMemorySelectionSettingPage::EMemoryCard )
        {
        TDriveNumber mmcDrive;
        User::LeaveIfError(
            DriveInfo::GetDefaultDrive( DriveInfo::EDefaultRemovableMassStorage,
                                        ( TInt& )mmcDrive ) );
        if( AknCFDUtility::DriveStatusL( mmcDrive ) != EDriveOK )
            {
            // If user's selection is memory card and it is locked, corrupted
            // or unavailable, show name of phone memory as selected item.
            memoryIndex = CAknMemorySelectionSettingPage::EPhoneMemory;
            }
        }

    iSettingPage->GetItem( memoryIndex, iSettingText );
    return iSettingText;
    }

