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


#ifndef C_TESTSDKCFDSETTINGITEM_H
#define C_TESTSDKCFDSETTINGITEM_H

#include <caknmemoryselectionsettingitem.h>
#include <testsdkcfd.rsg>

/**
 * CTestSettingItem derived from CAknMemorySelectionSettingItem and test it for
 * getting private member variable
 */
class CTestSettingItem : public CAknMemorySelectionSettingItem
    {
public:
    
    /**
     * Constructor.
     */
    CTestSettingItem( TInt aIdentifier,
        CAknMemorySelectionSettingPage::TMemory& aSelectedMemory );
    
    /**
     * Get iExternale value.
     */
    CAknMemorySelectionDialog::TMemory GetExternalData() const;
    
    /**
     * Get iInternale value.
     */
    CAknMemorySelectionDialog::TMemory GetInternalData() const;
    
    /**
     * Get setting page pointer.
     */
    CAknMemorySelectionSettingPage* GetSettingPagePointer() const;
    
    /**
     * Get text value.
     */
    TDes GetSettingText() const;
    /**
     * Get text value.
     */
    void GetText( TDes& aDes );
    };

/**
 *  CTestSettingItemList derived from CAknSettingItemList and test it for getting private member variable
 */
class CTestSettingItemList : public CAknSettingItemList
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

public:
    //Own : setting itme pointer
    CTestSettingItem* iItem;
    };

#endif      // C_TESTSDKCFDSETTINGITEM_H

// End of File
