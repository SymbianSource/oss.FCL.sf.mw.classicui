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
class TResourceReader;
class TCFDFileTypes;

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
     * Test if a folder contains subfolders.
     * @param aFolder Relative folder to current path.
     * @return Returns ETrue if a folder contains subfolders.
     */
    TBool ContainsSubfolders( const TDesC& aFolder );
    
    /**
     * Test if a folder contains files.
     * @param aFolder Relative folder to current path.
     * @return Returns ETrue if a folder contains files.
     */
    TBool ContainsFiles( const TDesC& aFolder );
    /**
     * Test if a folder contains contents.
     * @param aFolder Relative folder to current path.
     * @return Returns ETrue if a folder contains contents.
     */
    TBool ContainsContents( const TDesC& aFolder, TUint aAttMask );
    /**
     * Get the file type icon.
     * @param aFileName File name to get right icon.
     * return Return incon index base on the extname of file.
     */
    TInt GetIconForFileL( const TDesC& aFileName ) const;
    /**
     * Get the file local name.
     * @param aFileName File name to get its locallize name.
     * @return Returns file's local name.
     */
    TPtrC GetLocalizedName(const TDesC& aFileName);
    /**
     * Test if a entry can be added in listbox.
     * @param aEntry The entry which be added or not.
     * @return Returns ETrue if a entry can be added.
     */
    TBool EntryIsAccepted( const TEntry& aEntry ) const;
    /**
     * Read file type and icon index from reader
     * @param aReader Reader object
     */
    void ReadFileExtNameAndIconIndexL( TResourceReader& aReader );
// Constructors and destructor

    void ConstructL();

    CAknFileSelectionModel(
        const TCommonDialogType& aDialogType, CCoeEnv& aCoeEnv );

private:    // Data

    // Own: Current path being browsed.
    TParse iCurrentPath;

    // Own: An array of filtered directory entries.
    CArrayPakFlat<TEntry>* iEntryArray;
    
    /* Own: An array which item has local name of file entry 
     * with icon index and entry index in iEntryArray
     * */
    CDesC16ArraySeg * iLocalFileNameArray;
    
    /* Own: An array which item has local name of directory entry 
     * with icon index and entry index in iEntryArray
     * */
    CDesC16ArraySeg * iLocalDirNameArray;
    
    /* Own: An array which item has extent name of file entry 
     * with icon index for the file type
     * */
    CArrayFixFlat<TCFDFileTypes>* iFileTypeArray;

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

    TParse iParse;
    // Own: A buffer for using
    HBufC * iStringBuf;

    };

#endif // C_AKNFILESELECTIONMODEL_H
