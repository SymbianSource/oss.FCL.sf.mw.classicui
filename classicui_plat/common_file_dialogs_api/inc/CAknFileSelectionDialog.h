/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Dialog used to select target file or directory
*
*/


#ifndef CAKNFILESELECTIONDIALOG_H
#define CAKNFILESELECTIONDIALOG_H

// INCLUDES
#include <CAknCommonDialogsBase.h>

// FORWARD DECLARATIONS
class CAknFileSelectionModel;
class CAknFileSelectionEventHandler;
class MAknFileSelectionObserver;
class MAknFileFilter;

//  CLASS DEFINITION
/**
*  A class that launches a popup dialog for file selection or directory browsing.
*
*  @lib CommonDialogs.lib
*  @since 1.2
*/
NONSHARABLE_CLASS(CAknFileSelectionDialog) : public CAknCommonDialogsBase
    {
    public:     // Constructors and destructors
        /**
        * Static constructor.
        * @param aDialogType Type of the dialog for reading correct default values.
        * @return Returns a pointer to an instance of itself.
        */
        IMPORT_C static CAknFileSelectionDialog* NewL(
            TCommonDialogType aDialogType );

        /**
        * Static constructor.
        * @param aDialogType Type of the dialog for reading correct default values.
        * @param aResourceId A resource id (FILESELECTIONDIALOG).
        * @return Returns a pointer to an instance of itself.
        */
        IMPORT_C static CAknFileSelectionDialog* NewL(
            TCommonDialogType aDialogType, TInt aResourceId );

        IMPORT_C ~CAknFileSelectionDialog();

    public: // New functions

        /**
        * Sets an observer which is asked if the selected item can be selected.
        * @param aObserver A pointer to an observer.
        */
        IMPORT_C void SetObserver( MAknFileSelectionObserver* aObserver );

        /**
        * Adds a filter to list of filters owned by the engine.
        * Note! The ownership of the filter is transferred to the engine.
        * @param aFilter A pointer to a filter that is derived from MAknFileFilter.
        */
        IMPORT_C void AddFilterL( MAknFileFilter* aFilter );

        /**
        * Sets the default folder that browsing is started from.
        * @param aDefaultFolder A folder that is relative to the root path,
        *        e.g. root path = "C:\" so the default folder could be
        *        "Nokia\Images\".
        */
        IMPORT_C void SetDefaultFolderL( const TDesC& aDefaultFolder );

        /**
        * Sets title to the pop-up dialog.
        * @param aText Title text.
        */
        IMPORT_C void SetTitleL( const TDesC& aText );

        /**
        * Sets the text used for left softkey when a file is focused.
        * @param aText The text for softkey.
        */
        IMPORT_C void SetLeftSoftkeyFileL( const TDesC& aText );

        /**
        * Sets the text used for left softkey when a folder is focused.
        * @param aText The text for softkey.
        */
        IMPORT_C void SetLeftSoftkeyFolderL( const TDesC& aText );

        /**
        * Sets the text used for right softkey when user is in the root folder.
        * @param aText The text used for right softkey when user is in the root folder.
        */
        IMPORT_C void SetRightSoftkeyRootFolderL( const TDesC& aText );

        /**
        * Sets the text used for right softkey when user is in a subfolder.
        * @param aText The text used for right softkey when user is in a subfolder.
        */
        IMPORT_C void SetRightSoftkeySubfolderL( const TDesC& aText );

        /**
        * Executes the file selection dialog.
        * @param aFileName Contains the root path.
        *        If an item is selected, the selected item will be set to the
        *        parameter with full path.
        * @return Returns ETrue if user has selected an item and EFalse
        *         if user hits cancel.
        */
        IMPORT_C TBool ExecuteL( TDes& aFileName );

        /**
        * A static method that launches a file selection dialog.
        * @see RunL()
        */
        IMPORT_C static TBool RunDlgLD( TDes& aFileName,
            const TDesC& aDefaultFolder,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
        * A static method that launches a file selection dialog.
        * @see RunL()
        */
        IMPORT_C static TBool RunDlgLD( TDes& aFileName,
            const TDesC& aDefaultFolder,
            const TDesC& aTitle,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
        * A static method that launches a file selection dialog.
        * @see RunL()
        */
        IMPORT_C static TBool RunDlgLD( TDes& aFileName,
            const TDesC& aDefaultFolder,
            TInt aResourceId,
            MAknFileSelectionObserver* aObserver = NULL );

    private:    // New functions

        /**
        * A static method for launching a file selection dialog.
        * Creates, constructs, runs and deletes a file selection dialog with
        * different parameters.
        * @param aResourceId An id of a resource. If zero, default resource is used.
        * @param aFileName A reference to a filename. Must contain the root path
        *        to start browsing from (if the root path is not defined in
        *        resource). If user accepts a selection, the whole path + current
        *        filename is set to aFileName.
        * @param aDefaultFolder A descriptor that contains one or more folders
        *        that are relative to the root path. Browsing is started from
        *        the default folder and user can browse folders up all the way
        *        to the root folder.
        * @param aTitle A title for file selection dialog.
        * @param aObserver An observer which is asked if the selected item
        *        can be selected. Implemented in application.
        * @return Returns true if user has selected an item and false
        *         if user hits cancel.
        */
        static TBool RunL(
            TInt aResourceId,
            TDes& aFileName,
            const TDesC& aDefaultFolder,
            const TDesC& aTitle,
            MAknFileSelectionObserver* aObserver );

        /**
        * Initialization method that must be called before executing the dialog.
        * Initializes the engine and event handler with correct values.
        * Decides if the dialog should be shown or not.
        * Called in ExecuteL.
        * @param aFileName The root path.
        * @return Returns EFalse if the dialog cannot be executed.
        */
        TBool PrepareL( const TDesC& aFileName );

        /**
        * Sets id to a default CFD resource depending on dialog type.
        * @param aResourceId Resource id variable to be modified.
        * @param aType Dialog type.
        */
        void SetResourceId( TInt& aResourceId, TCommonDialogType aType ) const;

        /**
        * Reads settings from resource.
        * @param aResourceId Resource id.
        */
        void ReadFromResourceL( TInt aResourceId );

    private:    // Constructors and destructors

        CAknFileSelectionDialog( TCommonDialogType aDialogType );

        /**
         * Second phase construct. Constructs itself from a resource.
         * @param aResourceId A resource id (FILESELECTIONDIALOG).
         */
        void ConstructFromResourceL( TInt aResourceId );

    private:    // Data

        // Own: Dialog type
        TCommonDialogType iDialogType;

        // Own: Model
        CAknFileSelectionModel* iModel;

        // Own: Event handler
        CAknFileSelectionEventHandler* iEventHandler;

        // Ref: Observer
        MAknFileSelectionObserver* iObserver;

        // Own: Title
        HBufC* iTitle;

        // Own: Left softkey when file focused
        HBufC* iLeftSoftkeyFile;

        // Own: Left softkey when folder focused
        HBufC* iLeftSoftkeyFolder;

        // Own: Right softkey when in root folder
        HBufC* iRightSoftkeyRootFolder;

        // Own: Right softkey when in subfolder
        HBufC* iRightSoftkeySubfolder;

        // Own: Root path
        HBufC* iRootPath;

        // Own: Default folder
        HBufC* iDefaultFolder;

        // Own: Boolean value that tells if the dialog has been executed already.
        TBool iExecuted;
    };

#endif // CAKNFILESELECTIONDIALOG_H

// End of File
