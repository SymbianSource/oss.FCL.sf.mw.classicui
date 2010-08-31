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
* Description:  Model used in listbox of memory selection dialog.
*                New model class to support multiple drives.
*
*/



#ifndef C_AKNMEMORYSELECTIONMODELMULTIDRIVE_H
#define C_AKNMEMORYSELECTIONMODELMULTIDRIVE_H

#include <e32base.h>
#include <f32file.h>

#include "maknmemoryselectionmodel.h"

class CCoeEnv;
class TCFDDriveInfo;

/**
 *  A model class for memory selection. Model is derived from MDesCArray
 *  which provides an interface for list boxes to get items. Model has the
 *  responsibility to maintain a list of items for the listbox.
 *  This class supports multiple drives comparing CAknMemorySelectionModel.
 *
 *  @lib CommonDialogs.lib
 *  @since S60 5.0
 */
NONSHARABLE_CLASS(CAknMemorySelectionModelMultiDrive)
                    : public CBase,
                      public MAknMemorySelectionModel
    {
public:

// Constructors and destructor

    /**
     * Static constructor.
     * @return Returns a pointer to an instance of itself.
     */
    static CAknMemorySelectionModelMultiDrive* NewL(
        CCoeEnv* aCoeEnv,
        MDesCArray* aDriveArray,
        MDesCArray* aDefaultFolderArray,
        TInt aIncludedMedias,
        TBool aShowUnavailable,
        TListBoxLayout aLayout );

    ~CAknMemorySelectionModelMultiDrive();

// New functions

    /**
     * Gets listbox text of a memory at desired lbx index.
     * @param aIndex Index of the memory.
     * @param aItem A reference to a descriptor where the item is stored.
     */
    void GetItem( TInt aIndex, TDes& aItem );

// Functions from base class MAknMemorySelectionModel

    /**
     * Update root path and default folder arrays
     */
    void UpdateDataArraysL();

    /**
     * Read root paths and default folders defined in resource.
     * @param aReader Is the resource reader;
     * @param aLocations Is the count of locations;
     */
    void ReadUserDefinedDataL( TResourceReader& aReader, TInt aLocations );

    /**
     * Updates items in listbox.
     */
    void UpdateItemsL();

    /**
     * Get path of a drive referenced by given listbox item index.
     * @param aLbxItemIndex Index of the listbox item.
     * @param aDrivePath A reference to a descriptor where the drive path is
     *        stored.
     */
    void GetDrive( TInt aLbxItemIndex, TDes& aDrivePath );

    /**
     * Check if there is any unavailable MMC (not inserted).
     *
     * @return ETrue There is at least one MMC unavailble.
     *         EFalse MMC inserted.
     */
    TBool HasUnavailbleMMC();

// Functions from base class MDesCArray

    /**
     ** From MDesCArray.
     */
    TInt MdcaCount() const;

    /**
     ** From MDesCArray.
     */
    TPtrC MdcaPoint( TInt aIndex ) const;

private:

// Enumerations

    /**
     * Indexes to the memory icons owned by the listbox.
     */
    enum TMemIcons
        {
        EIconDeviceMemory = 0,
        EIconMMC,
        EIconMMCLocked,
        EIconMMCUnavailable,
        EIconRemoteDrive,
        EIconRemoteDriveActive, // Icon used in D-column if drive active
        EIconInternalMassStorage,
        EIconInternalMassStorageUnavailable
        };

    /**
     * Indexes to the localized memory texts (iLocStringArray).
     */
    enum TMemLocTexts
        {
        ETextDeviceMemory = 0,
        ETextMMCDefaultName,
        ETextMMCLocked,
        ETextMMCUnavailable,
        ETextRemoteDrive,
        ETextInternalMassStorage,
        ETextInternalMassStorageUnavailable,
        ETextMMCNamed,
        ETextCount // Count of the localized texts - must remain last!
        };

// New functions

    /**
     * Reads localised texts from resource.
     */
    void ReadResourcesL();

    /**
     * Creates formatted listbox item string from given drive information
     * and appends it to iListBoxArray.
     *
     * @param aDriveInfo Drive information from which the lxx item string is
     *                   created.
     */
    void AddItemToLbxL( const TCFDDriveInfo &aDriveInfo );

    /**
     * Creates formatted listbox item and appends it to iListBoxArray.
     * This method is for device memory drives.
     *
     * @param aDriveInfo Drive information from which the lxx item string is
     *                   created.
     */
    void AddDeviceMemoryItemToLbxL( const TCFDDriveInfo& aDriveInfo );

    /**
     * Creates formatted listbox item and appends it to iListBoxArray.
     * This method is for internal mass storage drives.
     *
     * @param aDriveInfo Drive information from which the lxx item string is
     *                   created.
     */
    void AddInternalStorageItemToLbxL( const TCFDDriveInfo& aDriveInfo );

    /**
     * Creates formatted listbox item and appends it to iListBoxArray.
     * This method is for removable mass storage drives.
     *
     * @param aDriveInfo Drive information from which the lxx item string is
     *                   created.
     */
    void AddMMCItemToLbxL( const TCFDDriveInfo& aDriveInfo );

    /**
     * Creates formatted listbox item and appends it to iListBoxArray.
     * This method is for remote drives.
     *
     * @param aDriveInfo Drive information from which the lxx item string is
     *                   created.
     */
    void AddRemoteItemToLbxL( const TCFDDriveInfo& aDriveInfo );

    /**
     * Creates formatted listbox item and appends it to iListBoxArray.
     *
     * @param aDriveInfo Drive information from which the lxx item string is
     *                   created.
     */
    void AddDefaultItemToLbxL( const TCFDDriveInfo& aDriveInfo );

    /**
     * Gets resource ID for resource item.
     * @param aLocStrIndex Index of the localized item.
     * @return ID of the resource item.
     */
    TInt ResourceIDForLayoutPopupMenuItem( TInt aLocStrIndex );

    /**
     * Gets resource ID for resource item.
     * @param aLocStrIndex Index of the localized item.
     * @return ID of the resource item.
     */
    TInt ResourceIDForLayoutSettingPageItem( TInt aLocStrIndex );

    /**
     * Gets resource ID for resource item.
     * @param aLocStrIndex Index of the localized item.
     * @return ID of the resource item.
     */
    TInt ResourceIDForLayoutDoublePopupItem( TInt aLocStrIndex );

// Constructors and destructor

    /**
     * Second phase construct. Reads localised texts from resource.
     */
    void ConstructL();

    CAknMemorySelectionModelMultiDrive(
        CCoeEnv* aCoeEnv,
        MDesCArray* aDriveArray,
        MDesCArray* aDefaultFolderArray,
        TInt aIncludedMedias,
        TBool aShowUnavailable,
        TListBoxLayout aLayout );

private: // Data

    // Own: Array of items in listbox, decorated
    RPointerArray<HBufC> iListBoxArray;

    // Own: Array for localised texts, read from resource
    RPointerArray<HBufC> iLocStringArray;

    // Ref: Pointer to control environment
    CCoeEnv* iCoeEnv;

    // Ref: Array of drives to choose from
    MDesCArray* iDriveArray;

    /**
     * Ref: Array of default folder to choose from
     */
    MDesCArray* iDefaultFolderArray;
    
    /**
     * Indicate which media types of drives could be visible.
     */
    TInt iIncludedMedias;
    
    /**
     * Own: Array of drives in resource to choose from
     */
    CDesCArrayFlat* iDefDriveArray;
    
    /**
     * Own: Array of default folder in resource to choose from
     */
    CDesCArrayFlat* iDefDefaultFolderArray;

    // Own: Defines if unavailable drives are shown in list
    TBool iShowUnavailable;

    // Own: Defines layout of the items
    TListBoxLayout iLayout;

    /**
     * Indicate if there is any unavailable MMC
     */
    TBool iHasMMCUnavailable;
    };

#endif // C_AKNMEMORYSELECTIONMODELMULTIDRIVE_H
