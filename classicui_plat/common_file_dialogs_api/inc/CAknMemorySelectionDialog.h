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
* Description:  Dialog used to selection target memory.
*
*/


#ifndef C_AKNMEMORYSELECTIONDIALOG_H
#define C_AKNMEMORYSELECTIONDIALOG_H

#include <CAknCommonDialogsBase.h>
#include <badesca.h> // CDesCArray

class CAknMemorySelectionModel;
class CAknMemorySelectionEventHandler;
class MAknMemorySelectionObserver;
class TDriveInfo;
class CAknIconArray;

/**
 *  A class that launches a pop-up dialog for memory selection.
 *
 *  @lib CommonDialogs.lib
 *  @since S60 1.2
 */
NONSHARABLE_CLASS(CAknMemorySelectionDialog) : public CAknCommonDialogsBase
    {

public:

// Enumerations
    /**
     * @Deprecated: This only works with fixed C: and E: drives.
     * Enumerations for memory items in listbox .
     */
    enum TMemory
        {
        EPhoneMemory = 0,   // C:
        EMemoryCard,        // E:
        EMemoryCount        // must remain last one
        };

// Constructors and destructors

    /**
     * Static constructor.
     *
     * @since S60 3.2
     * @param aDialogType Defines the type of the dialog in order to read
     *        correct default settings for title and softkeys from resource.
     * @param aShowUnavailableDrives Defines whether unavailable or corrupted
     *        drives are shown in memory selection list or not.
     * @return Returns a pointer to an instance of itself.
     */
    IMPORT_C static CAknMemorySelectionDialog* NewL(
        TCommonDialogType aDialogType,
        TBool aShowUnavailableDrives );


    /**
     * Static constructor.
     *
     * @since S60 3.2
     * @param aDialogType Defines the type of the dialog in order to read
     *        correct default settings for title and softkeys from resource.
     * @param aResourceId A resource id (MEMORYSELECTIONDIALOG).
     * @param aShowUnavailableDrives Defines whether unavailable or corrupted
     *        drives are shown in memory selection list or not.
     * @return Returns a pointer to an instance of itself.
     */
    IMPORT_C static CAknMemorySelectionDialog* NewL(
        TCommonDialogType aDialogType,
        TInt aResourceId,
        TBool aShowUnavailableDrives );

    /**
     * Static constructor.
     *
     * @since S60 3.2
     * @param aDialogType Defines the type of the dialog in order to read
     *        correct default settings for title and softkeys from resource.
     * @param aResourceId A resource id (MEMORYSELECTIONDIALOG).
     * @param aShowUnavailableDrives Defines whether unavailable or corrupted
     *        drives are shown in memory selection list or not.
     * @param aIncludedMedias bit flag definition of which medias are
     *        included in the dialog. See TMemoryTypes.
     * @return Returns a pointer to an instance of itself.
     */
    IMPORT_C static CAknMemorySelectionDialog* NewL(
        TCommonDialogType aDialogType,
        TInt aResourceId,
        TBool aShowUnavailableDrives,
        TInt aIncludedMedias );

    IMPORT_C virtual ~CAknMemorySelectionDialog();

// New functions

    /**
     * Sets an observer which is asked if the selected item can be selected.
     *
     * @param aObserver A pointer to an observer.
     */
    IMPORT_C void SetObserver( MAknMemorySelectionObserver* aObserver );

    /**
     * Sets title for the dialog.
     *
     * @param aText Title text.
     */
    IMPORT_C void SetTitleL( const TDesC& aText );

    /**
     * Sets the text used for left softkey.
     *
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
     * @param aIndex Index to the item in the memory selection list.
     * @param aItem A reference to a descriptor where the item is stored.
     */
    IMPORT_C void GetItem( TInt aIndex, TDes& aItem );

    /**
     * Gets the location paths of a memory.
     *
     * @param aSelectedMemory The memory that was selected.
     * @param aRootPath A pointer to a descriptor where the root path
     *        of the selected memory is stored. Must have KMaxFileName space.
     *        Set to NULL to ignore.
     * @param aDefaultFolder A pointer to a descriptor where the default folder
     *        of the selected memory is stored. Must have KMaxFileName space.
     *        Set to NULL to ignore.
     */
    IMPORT_C void GetMemories( TMemory aSelectedMemory,
                               TDes* aRootPath,
                               TDes* aDefaultFolder );

    /**
     * Executes the memory selection dialog. Virtual to allow derivation.
     *
     * @param aSelectedMemory A reference to a memory (TMemory).
     *        If one of the memories is selected, the selected memory is
     *        stored to the parameter.
     * @return Returns true if user has selected an item and false
     *         if user hits cancel.
     */
    IMPORT_C virtual TReturnKey ExecuteL( TMemory& aSelectedMemory );

    /**
     * Executes the memory selection dialog. Virtual to allow derivation.
     *
     * @param aSelectedMemory A reference to a memory (TMemory).
     *        If one of the memories is selected, the selected memory is
     *        stored to the parameter.
     * @param aRootPath A pointer to a descriptor where the root path
     *        of the selected memory is stored.
     * @param aDefaultFolder A pointer to a descriptor where the default folder
     *        of the selected memory is stored.
     * @return Returns true if user has selected an item and false
     *         if user hits cancel.
     */
    IMPORT_C virtual TReturnKey ExecuteL(
        TMemory& aSelectedMemory,
        TDes* aRootPath, TDes* aDefaultFolder );

    /**
     * A static method that launches a memory selection dialog.
     * @see RunL()
     */
    IMPORT_C static TBool RunDlgLD(
        TMemory& aSelectedMemory,
        MAknMemorySelectionObserver* aObserver = NULL );

    /**
     * A static method that launches a memory selection dialog.
     * @see RunL()
     */
    IMPORT_C static TBool RunDlgLD(
        TMemory& aSelectedMemory,
        const TDesC& aTitle,
        MAknMemorySelectionObserver* aObserver = NULL );

    /**
     * A static method that launches a memory selection dialog.
     * @see RunL()
     */
    IMPORT_C static TBool RunDlgLD(
        TMemory& aSelectedMemory,
        TInt aResourceId,
        TDes* aRootPath = NULL, TDes* aDefaultFolder = NULL,
        MAknMemorySelectionObserver* aObserver = NULL );

    /**
     * Returns the number of items in list box array.
     * Not exported, for CFD internal use only.
     *
     * @return Returns the number of items in list box array.
     */
    TInt NumberOfItems() const;

    /**
     * Maps drive paths according to selected listbox item. This function is
     * valid for dynamic drives. The prerequisite for this function is that
     * iRootPathArray and additionally iDefaultFolderArray indexes map
     * correctly to iModel's listbox items.
     *
     * @since S60 3.2
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

protected:

// Constructors and destructors

    CAknMemorySelectionDialog( TCommonDialogType aDialogType );

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
     * A static method for launching a memory selection dialog.
     * Creates, constructs, runs and deletes a memory selection dialog with
     * different parameters.
     *
     * @param aResourceId An id of a resource.
     * @param aSelectedMemory A reference to a memory described in ExecuteL.
     * @param aRootPath A pointer to a descriptor where the root path
     *        of the selected memory is stored.
     * @param aDefaultFolder A pointer to a descriptor where the default folder
     *        of the selected memory is stored.
     * @param aTitle A title for memory selection dialog.
     * @param aObserver An observer which is asked if the selected item
     *        can be selected. Implemented in application..
     */
    static TBool RunL(
        TInt aResourceId,
        TMemory& aSelectedMemory,
        TDes* aRootPath,
        TDes* aDefaultFolder,
        const TDesC& aTitle,
        MAknMemorySelectionObserver* aObserver );


    /**
     * Sets id to a default CFD resource depending on dialog type.
     */
    void SetResourceId( TInt& aResourceId, TCommonDialogType aDialogType )
        const;

    /**
     * Reads settings from resource.
     *
     * @param aResourceId Resource's ID to be read.
     * @param aResourceDefined If user defines the resource.
     */
    void ReadFromResourceL( TInt aResourceId, TBool aResourceDefined );

    /**
     * Loads icons into the icon-array.
     * @param aIconArray Array of which to append the loaded icons.
     * @param aDoubleStyle Is the dialog doublestyle.
     */
    void LoadIconsL( CAknIconArray* aIconArray, TBool aDoubleStyle );

    /**
     * Loads default root and default paths of phone memory & memory card
     */
    void GetSystemPathsL();

protected: // Data

    // Own: Dialog type
    TCommonDialogType iDialogType;

    // Own: Model
    CAknMemorySelectionModel* iModel;

    // Own: Event handler
    CAknMemorySelectionEventHandler* iEventHandler;

    // Ref: Observer
    MAknMemorySelectionObserver* iObserver;

    // Own: Title
    HBufC* iTitle;

    // Own: Left softkey text
    HBufC* iLeftSoftkey;

    // Own: Right softkey text
    HBufC* iRightSoftkey;

    // Own: Root path array
    // iDynamicDrivesEnabled indicates the content of this array.
    CDesCArrayFlat iRootPathArray;

    // Own: Default folder array
    CDesCArrayFlat iDefaultFolderArray;

    // Own: ETrue if dynamic drive reading is enabled
    //      EFalse if drives are static (C: and E:).
    // This affects iRootPathArray and iDefaultFolderArray content and
    // ordering.
    TBool iDynamicDrivesEnabled;

    TInt iIncludedMedias;
    };

#endif // C_AKNMEMORYSELECTIONDIALOG_H
