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


#ifndef C_TESTSDKCFDSETTINGITEMMULTIDRIVE_H
#define C_TESTSDKCFDSETTINGITEMMULTIDRIVE_H

#include <caknmemoryselectionsettingitemmultidrive.h>

/**
 * CTestSettingItemMultiDrive derived from CAknMemorySelectionSettingItemMultiDrive
 *  and test it for getting private member variable
 */
class CTestSettingItemMultiDrive : public CAknMemorySelectionSettingItemMultiDrive
    {
public:
    
    /**
     * Constructor.
     */
    CTestSettingItemMultiDrive( TInt aIdentifier, TDriveNumber& aSelectedDrive );
    
    /**
     * Get setting page pointer.
     */
    CAknMemorySelectionSettingItemExtension* GetExtensionPointer() const;
    };

/**
 *  CTestSettingItemListMultiDrive derived from CAknSettingItemList
 *   and test it for getting private member variable
 */
class CTestSettingItemListMultiDrive : public CAknSettingItemList
    {
public:
    
    /**
     * By default Symbian 2nd phase constructor is private.
     */
    void ConstructL();
    
    /**
     * Constructor.
     */
    CAknSettingItem* CreateSettingItemL( TInt aIdentifier );

private:
    //Own : setting itme pointer
    CTestSettingItemMultiDrive* iItem;
    };

#endif      // C_TESTSDKCFDSETTINGITEMMULTIDRIVE_H

// End of File
