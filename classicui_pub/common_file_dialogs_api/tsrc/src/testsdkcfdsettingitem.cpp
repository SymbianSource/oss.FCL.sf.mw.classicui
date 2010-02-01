/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test Common File Dialogs
 *
*/


// [INCLUDE FILES]
#include "testsdkcfdsettingitem.h"
#include "testsdkcfd.hrh"

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestSettingItem::GetText
// Get text value.
// -----------------------------------------------------------------------------
//
void CTestSettingItem::GetText( TDes& aDes )
    {
    TInt memoryIndex( CAknMemorySelectionDialog::EPhoneMemory );
    iSettingPage->GetItem( memoryIndex, aDes );
    }

// -----------------------------------------------------------------------------
// CTestSettingItem::CTestSettingItem
// Constructor.
// -----------------------------------------------------------------------------
//
CTestSettingItem::CTestSettingItem( TInt aIdentifier,
    CAknMemorySelectionSettingPage::TMemory& aSelectedMemory ) :
    CAknMemorySelectionSettingItem( aIdentifier, aSelectedMemory )
    {
    }

// -----------------------------------------------------------------------------
// CAknMemorySelectionDialog::TMemory CTestSettingItem::GetExternalData
// Get iExternale value.
// -----------------------------------------------------------------------------
//
CAknMemorySelectionDialog::TMemory CTestSettingItem::GetExternalData() const
    {
    return iExternalData;
    }

// -----------------------------------------------------------------------------
// CAknMemorySelectionDialog::TMemory CTestSettingItem::GetInternalData
// Get iInternale value.
// -----------------------------------------------------------------------------
//
CAknMemorySelectionDialog::TMemory CTestSettingItem::GetInternalData() const
    {
    return iInternalData;
    }

// -----------------------------------------------------------------------------
// CAknMemorySelectionSettingPage* CTestSettingItem::GetSettingPagePointer
// Get setting page pointer.
// -----------------------------------------------------------------------------
//
CAknMemorySelectionSettingPage* CTestSettingItem::GetSettingPagePointer() const
    {
    return iSettingPage;
    }

// -----------------------------------------------------------------------------
// CTestSettingItem::GetSettingText
// Get text value.
// -----------------------------------------------------------------------------
//
TDes CTestSettingItem::GetSettingText() const
    {
    return iSettingText;
    }

// -----------------------------------------------------------------------------
// CAknSettingItem* CTestSettingItemList::CreateSettingItemL
// Constructor.
// -----------------------------------------------------------------------------
//
CAknSettingItem* CTestSettingItemList::CreateSettingItemL( TInt aIdentifier )
    {
    CAknMemorySelectionDialog::TMemory memorytpye =
        CAknMemorySelectionDialog::EPhoneMemory;
    iItem = NULL;
    switch (aIdentifier)
        {
        case ETestSettingItem:
            iItem = new( ELeave )CTestSettingItem( aIdentifier, memorytpye );
            break;
        }
    return iItem;
    }

// -----------------------------------------------------------------------------
// CTestSettingItemList::ConstructL
// By default Symbian 2nd phase constructor is private.
// -----------------------------------------------------------------------------
//
void CTestSettingItemList::ConstructL()
    {
    CAknSettingItemList::ConstructFromResourceL( R_SETTINGS_ITEM_LIST );
    }

// End of file
