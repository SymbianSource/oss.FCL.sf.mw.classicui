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
* Description:  New memory selection dialog to support multiple drives.
*
*/



#ifndef C_AKNMEMORYSELECTIONDIALOGMULTIDRIVE_H
#define C_AKNMEMORYSELECTIONDIALOGMULTIDRIVE_H

#include <CAknCommonDialogsBase.h>
#include <badesca.h> // CDesCArray
#include <f32file.h> // TDriveNumber

class CAknMemorySelectionModelMultiDrive;
class CAknMemorySelectionEventHandler;
class MAknMemorySelectionObserver;
class TDriveInfo;
class CAknIconArray;

/**
 *  A class that launches a pop-up dialog for memory (drive) selection.
 *
 *  It is used to replace CAknMemorySelectionDialog class to support multiple
 *  drives.
 *
 *  @lib CommonDialogs.lib
 *  @since S60 5.0
 */
NONSHARABLE_CLASS( CAknMemorySelectionDialogMultiDrive )
    : public CAknCommonDialogsBase
    {
public:


// Constructors and destructors

    /**
     * Static constructor.
     *
     * @since S60 5.0
     * @param aDialogType Defines the type of the dialog in order to read
     *        correct default settings for title and softkeys from resource.
     * @param aShowUnavailableDrives Defines whether unavailable or corrupted
     *        drives are shown in memory selection list or not.
     * @return Returns a pointer to an instance of itself.
     */
    IMPORT_C static CAknMemorySelectionDialogMultiDrive* NewL(
        TCommonDialogType aDialogType,
        TBool aShowUnavailableDrives );


    /**
     * Static constructor.
     *
     * @since S60 5.0
     * @param aDialogType Defines the type of the dialog in order to read
     *        correct default settings for title and softkeys from resource.
     * @param aResourceId A resource id (MEMORYSELECTIONDIALOG). "Locations"
     *                    part of resource is not used any more.
     * @param aShowUnavailableDrives Defines whether unavailable or corrupted
     *        drives are shown in memory selection list or not.
     * @return Returns a pointer to an instance of itself.
     */
    IMPORT_C static CAknMemorySelectionDialogMultiDrive* NewL(
        TCommonDialogType aDialogType,
        TInt aResourceId,
        TBool aShowUnavailableDrives );

    /**
     * Static constructor.
     *
     * @since S60 5.0
     * @param aDialogType Defines the type of the dialog in order to read
     *        correct default settings for title and softkeys from resource.
     * @param aResourceId A resource id (MEMORYSELECTIONDIALOG). "Locations"
     *                    part of resource is not used any more.
     * @param aShowUnavailableDrives Defines whether unavailable or corrupted
     *        drives are shown in memory selection list or not.
     * @param aIncludedMedias bit flag definition of which medias are
     *        included in the dialog. See TMemoryTypes.
     * @return Returns a pointer to an instance of itself.
     */
    IMPORT_C static CAknMemorySelectionDialogMultiDrive* NewL(
        TCommonDialogType aDialogType,
        TInt aResourceId,
        TBool aShowUnavailableDrives,
        TInt aIncludedMedias );

    IMPORT_C virtual ~CAknMemorySelectionDialogMultiDrive();

// New functions

    /**
     * Sets title for the dialog.
     *
     * @since S60 5.0
     * @param aText Title text.
     */
    IMPORT_C void SetTitleL( const TDesC& aText );

    /**
     * Sets the text used for left softkey.
     *
     * @since S60 5.0
     * @param aText The text used for left softkey.
     */
    IMPORT_C void SetLeftSoftkeyL( const TDesC& aText );

    /**
     * Sets the text used for right softkey.
     *
     * @param aText The text used for right softkey.
     */
    IMPORT_C void SetRightSoftkeyL( const TDesC& aText );

    /**
     * Gets an item from memory selection dialog at specified index.
     *
     * @since S60 5.0
     * @param aIndex Index to the item in the memory selection list.
     * @param aItem A reference to a descriptor where the item is stored.
     */
    IMPORT_C void GetItem( TInt aIndex, TDes& aItem );


    /**
     * Executes the memory selection dialog. Virtual to allow derivation.
     *
     * @since S60 5.0
     * @param aSelectedDrive A reference to a drive.
     *        If one of the drives is selected, the selected drive is
     *        stored to the parameter.
     * @return Returns true if user has selected an item and false
     *         if user hits cancel.
     */
    IMPORT_C virtual TReturnKey ExecuteL( TDriveNumber& aSelectedDrive );

    /**
     * Executes the memory selection dialog. Virtual to allow derivation.
     *
     * @since S60 5.0
     * @param aSelectedDrive A reference to a drive.
     *        If one of the drives is selected, the selected drive is
     *        stored to the parameter.
     * @param aRootPath A pointer to a descriptor where the root path
     *        of the selected memory is stored.
     * @param aDefaultFolder A pointer to a descriptor where the default folder
     *        of the selected memory is stored.
     * @return Returns true if user has selected an item and false
     *         if user hits cancel.
     */
    IMPORT_C virtual TReturnKey ExecuteL(
        TDriveNumber& aSelectedDrive,
        TDes* aRootPath, TDes* aDefaultFolder );

    /**
     * A static method that launches a memory selection dialog.
     *
     * @since S60 5.0
     * @see RunL()
     */
    IMPORT_C static TBool RunDlgLD( TDriveNumber& aSelectedDrive );

    /**
     * New overloaded function to support multiple drives.
     * A static method that launches a memory selection dialog.
     *
     * @since S60 5.0
     * @see RunL()
     */
    IMPORT_C static TBool RunDlgLD(
        TDriveNumber& aSelectedDrive, const TDesC& aTitle );

    /**
     * A static method that launches a memory selection dialog.
     *
     * @since S60 5.0
     * @see RunL()
     */
    IMPORT_C static TBool RunDlgLD(
        TDriveNumber& aSelectedDrive,
        TInt aResourceId,
        TDes* aRootPath = NULL,
        TDes* aDefaultFolder = NULL );

    /**
     * Returns the number of items in list box array.
     * Not exported, for CFD internal use only.
     *
     * @return Returns the number of items in list box array.
     */
    TInt NumberOfItems() const;

    /**
     * Maps drive paths according to drive number. This function is valid
     * for dynamic drives.
     *
     * @since S60 5.0
     * @param aDrive Drive number.
     * @param aRootPath A pointer to a descriptor where the root path of the
     *        selected drive will be stored. Must have KMaxFileName space.
     *        Set to NULL to ignore.
     * @param aDefaultFolder A pointer to a descriptor where the default folder
     *        of the selected drive will be stored. Must have
     *        KMaxFileNamespace.
     *        Set to NULL to ignore.
     * @return Return error code
     *         KErrNone The drive is found in internal drive list
     *         KErrNotFound The drive is not visible to user or does not exist
     */
    TInt GetDrivePaths( TDriveNumber aDrive,
                        TDes* aRootPath,
                        TDes* aDefaultFolder );

    /**
     * Maps drive paths according to selected listbox item. This function is
     * valid for dynamic drives. The prerequisite for this function is that
     * iRootPathArray and additionally iDefaultFolderArray indexes map
     * correctly to iModel's listbox items.
     *
     * @since S60 5.0
     * @param aLbxIndex Index to the selected listbox item.
     * @param aRootPath A pointer to a descriptor where the root path of the
     *        selected drive will be stored. Must have KMaxFileName space.
     *        Set to NULL to ignore.
     * @param aDefaultFolder A pointer to a descriptor where the default folder
     *        of the selected drive will be stored. Must have
     *        KMaxFileNamespace.
     *        Set to NULL to ignore.
     * @return Return error code
     *         KErrNone The drive is found in internal drive list
     *         KErrNotFound The drive is not visible to user or does not exist
     */
    TInt GetDrivePaths( TInt aLbxIndex,
                        TDes* aRootPath,
                        TDes* aDefaultFolder );

    /**
     * Add user defined root path and default folder into memory selection
     * dialog. It is used to replace old user defined resource.
     *
     * @since S60 5.0
     * @param aRootPath A pointer to a descriptor where the root path of the
     *        selected drive will be stored. Must have KMaxFileName space.
     *        Set to NULL to ignore.
     *        The user defined root path will be added after each drive's root
     *        path. For example, if user specifics "Sounds\Digital\" for root
     *        path, then the root paths for all drives will be:
     *        C:\Data\Sounds\Digital\
     *        E:\Sounds\Digital\
     *        F:\Sounds\Digital\
     *        ...
     *
     * @param aDefaultFolder A pointer to a descriptor where the default folder
     *        of the selected drive will be stored. Must have KMaxFileName
     *        space. The user defined root path will be added after each drive's
     *        root path. Set to NULL to ignore. For example, if user specifics
     *        "MyFolder\" for default folder, then the default folders of all
     *        drives will be:
     *        <C drive's root path>\"MyFolder\"
     *        ...
     *        The trailing backslash will be added automatically whether user
     *        add it or not.
     *        
     * @return Return error code
     */
    IMPORT_C TInt AddDrivePathsL( const TDesC& aRootPath,
                                  const TDesC& aDefaultFolder );
    
    /**
     * Gets item index based on given drive number.
     *
     * @since S60 5.0
     * @param aDrive Drive to be searched.
     * @return Return item index if given drive is found in memory selection
     *         dialog's drive list. Othewise return KErrNotFound
     */
    IMPORT_C TInt FindIndexByDrive( const TDriveNumber& aDrive );
    
    /**
     * Get drive number based on item index in the listbox
     *
     * @param aIndex Listbox's item index.
     * @return Return drive number
     */
    TDriveNumber FindDriveByIndex( const TInt aIndex );
    
    /**
     * Check if there is any unavailable MMC (not inserted).
     * 
     * @return ETrue There is at least one MMC unavailble.
     *         EFalse MMC inserted.
     */
    TBool HasUnavailbleMMC();
    
    /**
     * Update model.
     * */
    void UpdateModelL();
    
protected:

// Constructors and destructors

    CAknMemorySelectionDialogMultiDrive( TCommonDialogType aDialogType );

    /**
     * Constructs class from resource
     *
     * @param aResourceId ID of the resource. Can be zero.
     * @param aShowUnavailableDrives Defines whether unavailable or corrupted
     *        drives are shown in memory selection list or not.
     */
    virtual void ConstructFromResourceL(
        TInt aResourceId,
        TBool aShowUnavailableDrives );

    /**
     * Constructs class from resource
     *
     * @param aResourceId ID of the resource. Can be zero.
     * @param aShowUnavailableDrives Defines whether unavailable or corrupted
     *        drives are shown in memory selection list or not.
     * @param aIncludedMedias bit flag definition of which medias are
     *        included in the dialog. See TMemoryTypes.
     */
    virtual void ConstructFromResourceL(
        TInt aResourceId,
        TBool aShowUnavailableDrives,
        TInt aIncludedMedias );
        
private:

//  New functions

    /**
     * New overloaded function to support multiple drives.
     * A static method for launching a memory selection dialog.
     * Creates, constructs, runs and deletes a memory selection dialog with
     * different parameters.
     *
     * @since S60 5.0
     * @param aResourceId An id of a resource.
     * @param aSelectedMemory A reference to a memory described in ExecuteL.
     * @param aRootPath A pointer to a descriptor where the root path
     *        of the selected memory is stored.
     * @param aDefaultFolder A pointer to a descriptor where the default folder
     *        of the selected memory is stored.
     * @param aTitle A title for memory selection dialog.
     */
    static TBool RunL(
        TInt aResourceId,
        TDriveNumber& aSelectedDrive,
        TDes* aRootPath,
        TDes* aDefaultFolder,
        const TDesC& aTitle );

    /**
     * Sets id to a default CFD resource depending on dialog type.
     */
    void SetResourceId( TInt& aResourceId, TCommonDialogType aDialogType )
        const;

    /**
     * Reads settings from resource.
     */
    void ReadFromResourceL( TInt aResourceId );

    /**
     * Loads icons into the icon-array.
     * @param aIconArray Array of which to append the loaded icons.
     * @param aDoubleStyle Is the dialog doublestyle.
     */
    void LoadIconsL( CAknIconArray* aIconArray, TBool aDoubleStyle );

    /**
     * Get all user visible drives with information of their root paths and
     * default folders.
     * Internal usage for memory selection dialog
     * @param aUserDefinedId Is the user defined resource id;
     */
    void GetSystemDrivesL( TInt aUserDefinedId );

protected:

// Data

    // Own: Dialog type
    TCommonDialogType iDialogType;

    // Own: Model
    CAknMemorySelectionModelMultiDrive* iModel;

    // Own: Event handler
    CAknMemorySelectionEventHandler* iEventHandler;

    // Own: Title
    HBufC* iTitle;

    // Own: Left softkey text
    HBufC* iLeftSoftkey;

    // Own: Right softkey text
    HBufC* iRightSoftkey;

    // Own: Root path array
    CDesCArrayFlat iRootPathArray;

    // Own: Default folder array
    CDesCArrayFlat iDefaultFolderArray;

    // Own: ETrue if dynamic drive reading is enabled
    //      EFalse if drives are static (C: and E:).
    // This affects iRootPathArray and iDefaultFolderArray content and
    // ordering.
    TBool iDynamicDrivesEnabled;

    /**
     * Indicate which media types of drives could be visible.
     */
    TInt iIncludedMedias;
    
    };

#endif // C_AKNMEMORYSELECTIONDIALOGMULTIDRIVE_H
