/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  The setting item to use CAknMemorySelectionSettingPage.
*
*/



#ifndef C_AKNMEMORYSELECTIONSETTINGITEM_H
#define C_AKNMEMORYSELECTIONSETTINGITEM_H

#include <aknsettingitemlist.h>
#include <CAknMemorySelectionSettingPage.h>

/**
 *  CAknMemorySelectionSettingItem is a setting item class that
 *  launches a CAknMemorySelectionSettingPage.
 *
 *  @lib CommonDialogs.lib
 *  @since S60 1.2
 */
class CAknMemorySelectionSettingItem : public CAknSettingItem
    {
public:

// Constructors and destructor

    /**
     * Constructor
     */
    IMPORT_C CAknMemorySelectionSettingItem(
        TInt aIdentifier,
        CAknMemorySelectionSettingPage::TMemory& aSelectedMemory );

    IMPORT_C virtual ~CAknMemorySelectionSettingItem();
    IMPORT_C void CompleteConstructionL();

// Functions from base class CAknSettingItem

    /**
    * From CAknSettingItem
    */
    IMPORT_C virtual void EditItemL( TBool aCalledFromMenu );

    /**
    * From CAknSettingItem
    */
    IMPORT_C virtual void LoadL();

    /**
    * From CAknSettingItem
    */
    IMPORT_C virtual void StoreL();

    /**
    * From CAknSettingItem
    */
    IMPORT_C virtual const TDesC& SettingTextL();

protected: // Data

    // Ref: External data
    CAknMemorySelectionSettingPage::TMemory& iExternalData;

    // Own: Internal data
    CAknMemorySelectionSettingPage::TMemory iInternalData;

    // Own: Setting page
    CAknMemorySelectionSettingPage* iSettingPage;

    // Own: The length is enough for memory name.
    TBuf<64> iSettingText;

    };

#endif      // C_AKNMEMORYSELECTIONSETTINGITEM_H
