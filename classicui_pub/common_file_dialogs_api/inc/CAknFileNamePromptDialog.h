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
* Description:  Dialog used to prompt filename.
*
*/


#ifndef CAKNFILENAMEPROMPTDIALOG_H
#define CAKNFILENAMEPROMPTDIALOG_H

// INCLUDES
#include <CAknCommonDialogsBase.h>

// FORWARD DECLARATIONS
class MAknFileSelectionObserver;

//  CLASS DEFINITION
/**
* A class that launches a pop-up dialog for filename prompting.
*
*  @lib CommonDialogs.lib
*  @since 1.2
*/
NONSHARABLE_CLASS(CAknFileNamePromptDialog) : public CAknCommonDialogsBase
    {
    public:     // Constructors and destructors

        /**
        * Static constructor.
        * Creates Filename Prompt Dialog with default values.
        * @return Returns a pointer to an instance of itself.
        */
        IMPORT_C static CAknFileNamePromptDialog* NewL();

        /**
        * Static constructor.
        * @param aResourceId A resource id (FILENAMEPROMPTDIALOG).
        * @return Returns a pointer to an instance of itself.
        */
        IMPORT_C static CAknFileNamePromptDialog* NewL( TInt aResourceId );

        IMPORT_C ~CAknFileNamePromptDialog();

    public:     // New functions

        /**
        * Sets path from which is checked if a file already exists.
        * @param aPath Full path with trailing backslash.
        */
        IMPORT_C void SetPathL( const TDesC& aPath );

        /**
        * Sets an observer which is asked if if the filename user inputs
        *  can be accepted.
        * @param aObserver A pointer to an observer (implemented in an application).
        */
        IMPORT_C void SetObserver( MAknFileSelectionObserver* aObserver );

        /**
        * Sets prompt text (title) for dialog.
        * @param aText Title text.
        */
        IMPORT_C void SetTitleL( const TDesC& aText );

        /**
        * Sets the text used for left softkey.
        * @param aText The text used for left softkey.
        */
        IMPORT_C void SetLeftSoftkeyL( const TDesC& aText );

        /**
        * Sets the text used for right softkey.
        * @param aText The text used for right softkey.
        */
        IMPORT_C void SetRightSoftkeyL( const TDesC& aText );

        /**
        * Executes the filename prompt dialog.
        * @param aFileName A reference to filename.
        *        If parameter is set, it is used as default filename.
        * @return Returns true if user has accepted filename and false
        *         if user hits cancel.
        */
        IMPORT_C TBool ExecuteL( TDes& aFileName );

        /**
        * A static method for launching a filename prompt dialog.
        * Parameters are described in method RunL
        */
        IMPORT_C static TBool RunDlgLD( TDes& aFileName,
            const TDesC& aPath,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
        * A static method for launching a filename prompt dialog.
        * Parameters are described in method RunL
        */
        IMPORT_C static TBool RunDlgLD( TDes& aFileName,
            const TDesC& aPath,
            const TDesC& aTitle,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
        * A static method for launching a filename prompt dialog.
        * Parameters are described in method RunL
        */
        IMPORT_C static TBool RunDlgLD( TDes& aFileName,
            const TDesC& aPath,
            TInt aResourceId,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
        * A method for use this dialog for renaming file
        *
        * @param aFileName File name user input
        * @return Returns true if user has accepted filename and false
        *         if user hits cancel.
        * @since 3.2
        */
        IMPORT_C TBool RenameL( TDes& aFileName );
    private:    // New functions

        /**
        * A static method for launching a filename prompt dialog.
        * Method is called from a RunDlgLD method with correct parameters.
        * @param aResourceId A resource id (FILENAMEPROMPTDIALOG).
        * @param aFileName A reference to a filename as described in ExecuteL.
        * @param aPath Full path with trailing backslash.
        * @param aTitle The text for title.
        * @param aObserver An observer which is assigned to NULL by default.
        */
        static TBool RunL(
            TInt aResourceId,
            TDes& aFileName,
            const TDesC& aPath,
            const TDesC& aTitle,
            MAknFileSelectionObserver* aObserver );

        /**
        * Sets default CFD resource id.
        */
        void SetResourceId( TInt& aResourceId ) const;

        /**
        * Reads settings from resource.
        */
        void ReadFromResourceL( TInt aResourceId );

        /**
        * Handle file name dialog for both creating and renaming
        * @param aFileName File name user input
        * @param aIfRename True for renaming; False for creating
        * @return Returns true if user has accepted filename and false
        *         if user hits cancel.
        * @since 3.2
        */
        TBool ShowDialogL( TDes& aFilename, TBool aIfRename );
    private:    // Constructors and destructors

        /**
        * Second phase construct from resource.
        * @param aResourceId A resource id (FILENAMEPROMPTDIALOG).
        */
        void ConstructFromResourceL( TInt aResourceId );

        CAknFileNamePromptDialog();

    protected:  // Data

        // Ref: observer
        MAknFileSelectionObserver* iObserver;

        // Own: Descriptor for default filename
        HBufC* iDefaultFileName;

        // Own: Descriptor for path
        HBufC* iPath;

        // Own: Descriptor for window title
        HBufC* iTitle;

        // Own: Descriptor for left softkey
        HBufC* iLeftSoftkey;

        // Own: Descriptor for right softkey
        HBufC* iRightSoftkey;
    };

#endif // CAKNFILENAMEPROMPTDIALOG_H

// End of File
