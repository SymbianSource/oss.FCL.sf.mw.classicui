/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  New memory selection setting item to support multiple drives.
*
*/



#ifndef C_AKNMEMORYSELECTIONSETTINGITEMMULTIDRIVE_H
#define C_AKNMEMORYSELECTIONSETTINGITEMMULTIDRIVE_H

#include <aknsettingitemlist.h>

class CAknMemorySelectionSettingItemExtension;
class CAknCFDFileSystemEvent;

/**
 *  CAknMemorySelectionSettingItemMultiDrive is a setting item class that
 *  launches a CAknMemorySelectionDialogMultiDrive. It is used to replace
 *  old CAknMemorySelectionSettingItem for multiple drive support.
 *
 *  @lib CommonDialogs.lib
 *  @since S60 5.0
 */
class CAknMemorySelectionSettingItemMultiDrive : public CAknSettingItem
    {
        
public:
    
// Constructors and destructor

    /**
     * Constructor
     *
     * @since s60 5.0
     */
    IMPORT_C CAknMemorySelectionSettingItemMultiDrive(
        TInt aIdentifier,
        TDriveNumber& aSelectedDrive
        );            
            
    IMPORT_C virtual ~CAknMemorySelectionSettingItemMultiDrive();
    
    /**
     * The 2nd phase constructor. It is called internally when extension
     * object is needed. User also could call it after creating a object of
     * CAknMemorySelectionSettingItemMultiDrive.
     *
     * @since s60 5.0
     */
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
    
    /**
     * Update contents of setting item
     */
    void UpdateSettingItemContentL();
    
protected: // Data

    // Ref: External data
    TDriveNumber& iExternalData;

    // Own: Internal data
    TDriveNumber iInternalData;
    
    // Own: Pointer to extension object
    CAknMemorySelectionSettingItemExtension* iExtension;

    // Own: The length is enough for memory name.
    HBufC* iSettingText;
    
    };

#endif      // C_AKNMEMORYSELECTIONSETTINGITEMMULTIDRIVE_H
