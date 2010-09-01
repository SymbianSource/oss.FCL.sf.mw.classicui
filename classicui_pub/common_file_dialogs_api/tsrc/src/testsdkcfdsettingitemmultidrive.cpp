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
#include <testsdkcfd.rsg>
#include "testsdkcfdsettingitemmultidrive.h"
#include "testsdkcfd.hrh"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSettingItemMultiDrive::CTestSettingItemMultiDrive
// Constructor.
// -----------------------------------------------------------------------------
//
CTestSettingItemMultiDrive::CTestSettingItemMultiDrive(
        TInt aIdentifier, TDriveNumber& aSelectedDrive ) :
        CAknMemorySelectionSettingItemMultiDrive( aIdentifier, aSelectedDrive )
    {
    }

// -----------------------------------------------------------------------------
// CAknMemorySelectionSettingItemExtension* CTestSettingItemMultiDrive::GetExtensionPointer
// Get setting page pointer.
// -----------------------------------------------------------------------------
//
CAknMemorySelectionSettingItemExtension* CTestSettingItemMultiDrive::GetExtensionPointer() const
    {
    return iExtension;
    }

// -----------------------------------------------------------------------------
// CAknSettingItem* CTestSettingItemListMultiDrive::CreateSettingItemL
// Constructor.
// -----------------------------------------------------------------------------
//
CAknSettingItem* CTestSettingItemListMultiDrive::CreateSettingItemL( TInt aIdentifier )
    {
    TDriveNumber selectedDrive = EDriveC;
    iItem = NULL;
    switch ( aIdentifier )
        {
        case ETestSettingItem:
            iItem = new( ELeave )CTestSettingItemMultiDrive( aIdentifier, selectedDrive );
            break;
        }
    return iItem;
    }

// -----------------------------------------------------------------------------
// CTestSettingItemListMultiDrive::ConstructL
// By default Symbian 2nd phase constructor is private.
// -----------------------------------------------------------------------------
//
void CTestSettingItemListMultiDrive::ConstructL()
    {
    CAknSettingItemList::ConstructFromResourceL( R_SETTINGS_ITEM_LIST );
    }

// End of file
