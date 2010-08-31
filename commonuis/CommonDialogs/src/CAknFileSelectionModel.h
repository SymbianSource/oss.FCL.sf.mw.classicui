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
* Description:  Model class for file selection
*
*/



#ifndef C_AKNFILESELECTIONMODEL_H
#define C_AKNFILESELECTIONMODEL_H

#include <bamdesca.h>   // MDesCArray
#include <f32file.h>    // File system
#include <apgcli.h> // RApaLsSession

#include "CAknFileSelectionDialog.h"

class MAknFileFilter;
class MAknFileSelectionObserver;
class CDirectoryLocalizer;


/**
 *  A model class for file selection dialog. It is derived from
 *  MDesCArray which provides an interface for listboxes to get items.
 *  Model maintains a list of directory entries.
 *
 *  @lib CommonDialogs.lib
 *  @since S60 1.2
 */
NONSHARABLE_CLASS(CAknFileSelectionModel) : public CBase, public MDesCArray
    {

public:

// Enumerations

    /**
     * Enumerations for images.
     */
    enum TFileTypeIcon
        {
        EFolderIcon,
        EFileIcon,
        ESubFolderIcon,
        EThisFolderIcon,
        EImageFileIcon,
        EGmsFileIcon,
        ELinkFileIcon,
        EVoiceRecFileIcon,
        ESoundFileIcon,
        EPlaylistFileIcon,
        ECompoFileIcon,
        ENoteFileIcon,
        ESisFileIcon,
        EVideoFileIcon,
        EGameFileIcon,
        EJavaFileIcon,
        EUnknowTypeIcon,
        EFolderEmptyIcon,
        EFlashFileIcon
        };

// Constructors and destructor

    /**
     * Static constructor.
     * @param aDialogType Dialog type.
     * @return Returns a pointer to an instance of itself.
     */
    static CAknFileSelectionModel* NewL(
        const TCommonDialogType& aDialogType, CCoeEnv& aCoeEnv );

    ~CAknFileSelectionModel();

// New methods

    /**
     * Sets the current path, this is set as the root path.
     * @param aPath The absolute path. Browsing cannot go beyond this.
     *        This could be for example "E:\\" or "C:\\Nokia\\Images\\".
     * @return Number of items in the new folder or system wide error code if
     *         unsuccessful.
     */
    TInt SetPathL( const TDesC& aPath );

    /**
     * Adds a folder in the end of current path.
     * @param aFolder A folder is added in the end of current path.
     *        This folder is relative to current path. Trailing backslash is
     *        added if necessary. This could be for example "Images\\".
     * @return Number of items in the new folder or system wide error code if
     *         unsuccessful.
     */
    TInt AddFolderL( const TDesC& aFolder );

    /**
     * Adds a filter to filter list. Ownership is taken.
     * @param aFilter A Filter to be added.
     */
    void AddFilterL( MAknFileFilter* aFilter );

    /**
     * Changes directory into a subfolder. Updates entries.
     * @param aFolder The name of the subfolder, trailing backslash is added if
     *                necessary.
     * @return Number of items in the new folder or system wide error code if
     *         unsuccessful.
     */
    TInt GotoSubFolderL( const TDesC& aFolder );

    /**
     * Changes path to one folder up.
     * @return Number of items in the new folder or system wide error code if
     *         unsuccessful.
     */
    TInt GotoParentFolderL();

    /**
     * Updates the filtered entry array.
     * @return If no errors, the number of items in filtered entry array,
     *         otherwise system wide error code.
     */
    TInt UpdateItemListL();

    /**
     * Returns an entry from filtered entry array.
     * @param aIndex Array index.
     * @return Returns an entry from the current index.
     */
    const TEntry& Entry( const TInt& aIndex ) const;

    /**
     * Gets current path.
     * @param aPath A descriptor in which the current path is stored.
     */
    void GetCurrentPath( TDes& aPath ) const;

    /**
     * Returns directory level, 0 is root.
     * @return Returns directory level, 0 is root.
     */
    TInt DirectoryLevel() const;

    /**
     * Returns an index of a folder from list of filtered entries.
     * This can be used for listbox to focus wanted item.
     * @param aFolder A folder to search for.
     * @return The index of the folder in the filtered item list,
     *         KErrNotFound if not found.
     */
    TInt FolderIndex( const TDesC& aFolder ) const;

// Functions from base classes

    /**
     * From MDesCArray
     */
    TInt MdcaCount() const;

    /**
     * From MDesCArray
     */
    TPtrC MdcaPoint( TInt aIndex ) const;

private:    
    
// New functions

    /**
     * Reads directory contents using RFs::GetDir.
     * @param aDirectory Directory.
     * @return Returns pointer to created CDir object.
     */
    CDir* ReadDirectory( const TDesC& aDirectory );

    /**
     * Returns ETrue if a folder contains subfolders.
     * @param aFolder Relative folder to current path.
     * @return Returns ETrue if a folder contains subfolders.
     */
    TBool ContainsSubfolders( const TDesC& aFolder );

    void AppendIconForFileL(const TDesC& aFileName);

    TPtrC GetLocalizedName(const TDesC& aFileName);
    
    /**
     * Returns ETrue if a folder contains files.
     * @param aFolder Relative folder to current path.
     * @return Returns ETrue if a folder contains files.
     */
    TBool ContainsFiles( const TDesC& aFolder );

// Constructors and destructor

    void ConstructL();

    CAknFileSelectionModel(
        const TCommonDialogType& aDialogType, CCoeEnv& aCoeEnv );

private:    // Data

    // Own: Current path being browsed.
    TParse iCurrentPath;

    // Own: An array of filtered directory entries.
    CArrayPakFlat<TEntry>* iEntryArray;

    // Own: An array for image indices
    RArray<TInt> iImageIndexArray;

    // Own: // An array of filters.
    CArrayPtrSeg<MAknFileFilter>* iFilterArray;

    // Own: File server session.
    RFs iFs;

    // Own: Directory level.
    TInt iDirectoryLevel;

    // Own: Directory localiser
    CDirectoryLocalizer* iLocalizer;

    // Ref: Dialog type
    const TCommonDialogType& iDialogType;

    // Ref: Control environment
    CCoeEnv& iCoeEnv;

    // Own: Root folder text
    HBufC* iRootFolderText;

    // Own: RApaLsSession for getting mime-types for files:
    RApaLsSession iApaSession;

    TEntry iFolderEntry;

    TParse iParse;

    HBufC * iItemWithImageIndex;

    };

#endif // C_AKNFILESELECTIONMODEL_H
