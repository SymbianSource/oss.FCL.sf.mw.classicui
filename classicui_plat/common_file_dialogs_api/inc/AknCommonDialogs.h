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
* Description:  Static class to call combined common file dialogs.
*
*/


#ifndef AKNCOMMONDIALOGS_H
#define AKNCOMMONDIALOGS_H

// INCLUDES
#include <CAknCommonDialogsBase.h>

// FORWARD DECLARATIONS
class MAknMemorySelectionObserver;
class MAknFileSelectionObserver;
class MAknFileFilter;

// CLASS DEFINITION
/**
*  DEPRECATED: Use AknCommonDialogsDynMem instead. This class is only used as a
*  proxy to the new implementation class to maintain backwards compatibility.
*
*  A class that consists of static functions that launch UI components in a
*  sequence. First, memory selection component is launched and then
*  file/directory selection component. In save and move dialogs directory
*  selection may not be shown if there are no subdirectories to choose from.
*  In save dialog, finally filename prompt component is launched.
*
*  All methods have an obligatory resource ID parameter for memory selection
*  because it contains the paths for both memories (Phone&MMC) (LOCATION structs).
*  If set, an observer is queried just before exiting the dialog.
*  At this point the application can either reject or accept user's selection.
*  Every dialog returns a boolean value which tells if user has selected something
*  or not.
*
*  @lib CommonDialogs.lib
*  @since 1.2
*/
class AknCommonDialogs
    {
    
    public:
  
        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches file selection dialog.
         * @param aFileName Full path and filename of the file that user
         *        selects is stored to this descriptor.
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog.
         * @param aObserver An observer which is asked, if set, to verify user's
         *        selection.
         * @return Returns ETrue if user selects a file, otherwise EFalse.
         */
        IMPORT_C static TBool RunSelectDlgLD(
            TDes& aFileName,
            TInt aMemorySelectionResourceId,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches file selection dialog.
         * @param aFileName Full path and filename of the file that user
         *        selects is stored to this descriptor.
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog.
         * @param aFilter Filter is asked if a directory entry can be shown in
         *        list. Ownership is not transferred.
         * @param aObserver An observer which is asked, if set, to verify user's
         *        selection.
         * @return Returns ETrue if user selects a file, otherwise EFalse.
         */
        IMPORT_C static TBool RunSelectDlgLD(
            TDes& aFileName,
            TInt aMemorySelectionResourceId,
            MAknFileFilter* aFilter,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches file selection dialog.
         * @param aFileName Full path and filename of the file that user
         *        selects is stored to this descriptor.
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog.
         * @param aFileSelectionTitle A custom title for file selection dialog.
         * @param aObserver An observer which is asked, if set, to verify user's
         *        selection.
         * @return Returns ETrue if user selects a file, otherwise EFalse.
         */
        IMPORT_C static TBool RunSelectDlgLD(
            TDes& aFileName,
            TInt aMemorySelectionResourceId,
            const TDesC& aFileSelectionTitle,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches file selection dialog.
         * @param aFileName Full path and filename of the file that user
         *        selects is stored to this descriptor.
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog.
         * @param aFileSelectionResourceId A resource id for file selection
         *        dialog.
         * @param aObserver An observer which is asked, if set, to verify user's
         *        selection.
         * @return Returns ETrue if user selects a file, otherwise EFalse.
         */
        IMPORT_C static TBool RunSelectDlgLD(
            TDes& aFileName,
            TInt aMemorySelectionResourceId,
            TInt aFileSelectionResourceId,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches move dialog.
         * @param aDirectory Full path of the folder that user
         *        selects is stored to this descriptor.
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog.
         * @param aObserver An observer which is asked, if set, to verify user's
         *        selection.
         * @return Returns ETrue if user selects a folder, otherwise EFalse.
         */
        IMPORT_C static TBool RunMoveDlgLD(
            TDes& aDirectory,
            TInt aMemorySelectionResourceId,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches move dialog.
         * @param aDirectory Full path of the folder that user
         *        selects is stored to this descriptor.
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog.
         * @param aFilter Filter is asked if a directory entry can be shown in
         *        list. Ownership is not transferred.
         * @param aObserver An observer which is asked, if set, to verify user's
         *        selection.
         * @return Returns ETrue if user selects a folder, otherwise EFalse.
         */
        IMPORT_C static TBool RunMoveDlgLD(
            TDes& aDirectory,
            TInt aMemorySelectionResourceId,
            MAknFileFilter* aFilter,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches move dialog.
         * @param aDirectory Full path of the folder that user
         *        selects is stored to this descriptor.
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog.
         * @param aFileSelectionTitle A custom title for directory selection
         *        dialog.
         * @param aObserver An observer which is asked, if set, to verify user's
         *        selection.
         * @return Returns ETrue if user selects a folder, otherwise EFalse
         */
        IMPORT_C static TBool RunMoveDlgLD(
            TDes& aDirectory,
            TInt aMemorySelectionResourceId,
            const TDesC& aFileSelectionTitle,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches move dialog.
         * @param aDirectory Full path of the folder that user
         *        selects is stored to this descriptor.
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog
         * @param aFileSelectionResourceId A resource id for file selection
         *        dialog
         * @param aObserver An observer which is asked, if set, to verify user's
         *        selection.
         * @return Returns ETrue if user selects a folder, otherwise EFalse
         */
        IMPORT_C static TBool RunMoveDlgLD(
            TDes& aDirectory,
            TInt aMemorySelectionResourceId,
            TInt aFileSelectionResourceId,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches save dialog which does not run folder
         * selection dialog at all. Instead the resulting path will be
         * constructed from the root and default folder read from resources and
         * from the file name given by the user.
         * @param aDefaultFileName Full path + the filename that user enters
         *        is stored to this descriptor. The descriptor may contain text
         *        that is used as default filename, for example "Attachment".
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog.
         * @param aObserver An observer which is asked, if set, to verify the
         *        filename that user types.
         * @return Returns ETrue if user accepts or enters a filename, otherwise
         *         EFalse.
         */
         IMPORT_C static TBool RunSaveDlgLD(
            TDes& aDefaultFileName,
            TInt aMemorySelectionResourceId,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches save dialog.
         * @param aDefaultFileName Full path + the filename that user enters
         *        is stored to this descriptor. The descriptor may contain text
         *        that is used as default filename, for example "Attachment".
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog.
         * @param aFilter Filter is asked if a directory entry can be shown in
         *        list. Ownership is not transferred.
         * @param aObserver An observer which is asked, if set, to verify the
         *        filename that user types.
         * @return Returns ETrue if user accepts or enters a filename, otherwise
         *         EFalse.
         */
         IMPORT_C static TBool RunSaveDlgLD(
            TDes& aDefaultFileName,
            TInt aMemorySelectionResourceId,
            MAknFileFilter* aFilter,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches save dialog.
         * @param aDefaultFileName Full path + the filename that user enters
         *        is stored to this descriptor. The descriptor may contain text
         *        that is used as default filename, for example "Attachment".
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog.
         * @param aFileSelectionTitle Custom title for file selection dialog.
         * @param aFileNamePromptTitle Custom title for filename prompt dialog.
         * @param aObserver An observer which is asked, if set, to verify the
         *        filename that user types.
         * @return Returns ETrue if user accepts or enters a filename, otherwise
         *         EFalse.
         */
        IMPORT_C static TBool RunSaveDlgLD(
            TDes& aDefaultFileName,
            TInt aMemorySelectionResourceId,
            const TDesC& aFileSelectionTitle,
            const TDesC& aFileNamePromptTitle,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches save dialog.
         * @param aDefaultFileName Full path + the filename that user enters
         *        is stored to this descriptor. The descriptor may contain text
         *        that is used as default filename, for example "Attachment".
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog.
         * @param aFileSelectionResourceId A resource id for file selection
         *        dialog.
         * @param aObserver An observer which is asked, if set, to verify the
         *        filename that user types.
         * @return Returns ETrue if user accepts or enters a filename, otherwise
         *         EFalse.
         */
         IMPORT_C static TBool RunSaveDlgLD(
            TDes& aDefaultFileName,
            TInt aMemorySelectionResourceId,
            TInt aFileSelectionResourceId,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches save dialog.
         * @param aDefaultFileName Full path + the filename that user enters
         *        is stored to this descriptor. The descriptor may contain text
         *        that is used as default filename, for example "Attachment".
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog.
         * @param aFileSelectionResourceId A resource id for file selection
         *        dialog.
         * @param aFileNamePromptTitle Custom title for filename prompt dialog.
         * @param aObserver An observer which is asked, if set, to verify the
         *        filename that user types.
         * @return Returns ETrue if user accepts or enters a filename, otherwise
         *         EFalse.
         */
         IMPORT_C static TBool RunSaveDlgLD(
            TDes& aDefaultFileName,
            TInt aMemorySelectionResourceId,
            TInt aFileSelectionResourceId,
            const TDesC& aFileNamePromptTitle,
            MAknFileSelectionObserver* aObserver = NULL );

         /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches save dialog. No file selection dialog
         * for directory selection is displayed.
         * @param aDefaultFileName Full path + the filename that user enters
         *        is stored to this descriptor. The descriptor may contain text
         *        that is used as default filename, for example "Attachment".
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog. The folders in which the file will be saved should be
         *        given in this resource.
         * @param aObserver An observer which is asked, if set, to verify the
         *        filename that user types.
         * @return Returns ETrue if user accepts or enters a filename, otherwise
         *         EFalse.
         */
         IMPORT_C static TBool RunSaveDlgNoDirectorySelectionLD(
            TDes& aDefaultFileName,
            TInt aMemorySelectionResourceId,
            MAknFileSelectionObserver* aObserver = NULL );

         /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches save dialog. No file selection dialog
         * for directory selection is displayed.
         * @param aDefaultFileName Full path + the filename that user enters
         *        is stored to this descriptor. The descriptor may contain text
         *        that is used as default filename, for example "Attachment".
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog. The folders in which the file will be saved should be
         *        given in this resource.
         * @param aFileNamePromptTitle Custom title for filename prompt dialog.
         * @param aObserver An observer which is asked, if set, to verify the
         *        filename that user types.
         * @return Returns ETrue if user accepts or enters a filename, otherwise
         *         EFalse.
         */
         IMPORT_C static TBool RunSaveDlgNoDirectorySelectionLD(
            TDes& aDefaultFileName,
            TInt aMemorySelectionResourceId,
            const TDesC& aFileNamePromptTitle,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches copy dialog.
         * @param aDirectory Full path of the folder that user
         *        selects is stored to this descriptor.
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog.
         * @param aObserver An observer which is asked, if set, to verify user's
         *        selection.
         * @return Returns ETrue if user selects a folder, otherwise EFalse.
         */
        IMPORT_C static TBool RunCopyDlgLD(
            TDes& aDirectory,
            TInt aMemorySelectionResourceId,
            MAknFileSelectionObserver* aObserver = NULL );
        
        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches copy dialog.
         * @param aDirectory Full path of the folder that user
         *        selects is stored to this descriptor.
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog.
         * @param aFilter Filter is asked if a directory entry can be shown in
         *        list. Ownership is not transferred.
         * @param aObserver An observer which is asked, if set, to verify user's
         *        selection.
         * @return Returns ETrue if user selects a folder, otherwise EFalse.
         */
        IMPORT_C static TBool RunCopyDlgLD(
            TDes& aDirectory,
            TInt aMemorySelectionResourceId,
            MAknFileFilter* aFilter,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches copy dialog.
         * @param aDirectory Full path of the folder that user
         *        selects is stored to this descriptor.
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog
         * @param aFileSelectionResourceId A resource id for file selection
         *        dialog
         * @param aObserver An observer which is asked, if set, to verify user's
         *        selection.
         * @return Returns ETrue if user selects a folder, otherwise EFalse
         */
        IMPORT_C static TBool RunCopyDlgLD(
            TDes& aDirectory,
            TInt aMemorySelectionResourceId,
            TInt aFileSelectionResourceId,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
        * A static method that launches file selection dialog.
        * @param aFileName Full path and filename of the file that user
        *        selects is stored to this descriptor.
        * @param aStartFolder User defined folder to start browsing in file selection
        * @param aMemorySelectionResourceId A resource id for memory selection
        *        dialog.
        * @param aObserver An observer which is asked, if set, to verify user's
        *        selection.
        * @return Returns ETrue if user selects a file, otherwise EFalse.
        * @since 2.6
        */
        IMPORT_C static TBool RunSelectDlgLD(
            TDes& aFileName,
            const TDesC& aStartFolder,
            TInt aMemorySelectionResourceId,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches file selection dialog.
         * @param aFileName Full path and filename of the file that user
         *        selects is stored to this descriptor.
         * @param aStartFolder User defined folder to start browsing in file selection
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog.
         * @param aFilter Filter is asked if a directory entry can be shown in
         *        list. Ownership is not transferred.
         * @param aObserver An observer which is asked, if set, to verify user's
         *        selection.
         * @return Returns ETrue if user selects a file, otherwise EFalse.
         * @since 2.6
         */
        IMPORT_C static TBool RunSelectDlgLD(
            TDes& aFileName,
            const TDesC& aStartFolder,
            TInt aMemorySelectionResourceId,
            MAknFileFilter* aFilter,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches file selection dialog.
         * @param aFileName Full path and filename of the file that user
         *        selects is stored to this descriptor.
         * @param aStartFolder User defined folder to start browsing in file selection
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog.
         * @param aFileSelectionTitle A custom title for file selection dialog.
         * @param aObserver An observer which is asked, if set, to verify user's
         *        selection.
         * @return Returns ETrue if user selects a file, otherwise EFalse.
         * @since 2.6
         */
        IMPORT_C static TBool RunSelectDlgLD(
            TDes& aFileName,
            const TDesC& aStartFolder,
            TInt aMemorySelectionResourceId,
            const TDesC& aFileSelectionTitle,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches file selection dialog.
         * @param aFileName Full path and filename of the file that user
         *        selects is stored to this descriptor.
         * @param aStartFolder User defined folder to start browsing in file selection
         * @param aMemorySelectionResourceId A resource id for memory selection
         *        dialog.
         * @param aFileSelectionResourceId A resource id for file selection
         *        dialog.
         * @param aObserver An observer which is asked, if set, to verify user's
         *        selection.
         * @return Returns ETrue if user selects a file, otherwise EFalse.
         * @since 2.6
         */
        IMPORT_C static TBool RunSelectDlgLD(
            TDes& aFileName,
            const TDesC& aStartFolder,
            TInt aMemorySelectionResourceId,
            TInt aFileSelectionResourceId,
            MAknFileSelectionObserver* aObserver = NULL );
            
        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches file selection dialog.
         * @param aFileName Full path and filename of the file that user selects is
         *        stored to this descriptor.
         * @param aStartFolder User defined folder to start browsing in file selection.
         * @param aMemorySelectionResourceId A resource id for memory selection dialog.
         * @param aFileSelectionResourceId A resource id for file selection dialog.
         * @param aFileSelectionTitle Custom title for file selection dialog.
         * @param aFilter Filter asked if a directory entry can be shown in list.
         * @param aObserver An observer which is asked to verify user's selection.
         * @return Returns ETrue if user selects a file, otherwise EFalse
         * @since 3.1
         */
        IMPORT_C static TBool RunSelectDlgLD(
            TDes& aFileName,
            const TDesC& aStartFolder,
            TInt aMemorySelectionResourceId,
            TInt aFileSelectionResourceId,
            const TDesC& aFileSelectionTitle,
            MAknFileFilter* aFilter = NULL,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches save dialog.
         * @param aDefaultFileName Full path + the filename that user enters
         *        is stored to this descriptor. The descriptor may contain text
         *        that is used as default filename, for example "Attachment".
         * @param aStartFolder User defined folder to start browsing in file selection.
         * @param aMemorySelectionResourceId A resource id for memory selection dialog.
         * @param aFileSelectionResourceId A resource id for file selection dialog.
         * @param aFileSelectionTitle Custom title for file selection dialog.
         * @param aFilter Filter asked if a directory entry can be shown in list.
         * @param aObserver An observer which is asked, if set, to verify the
         *        filename that user types.
         * @return Returns ETrue if user accepts or enters a filename, otherwise
         *         EFalse.
         * @since 3.1
         */
        IMPORT_C static TBool RunSaveDlgLD(
            TDes& aDefaultFileName,
            const TDesC& aStartFolder,
            TInt aMemorySelectionResourceId,
            TInt aFileSelectionResourceId,
            const TDesC& aFileSelectionTitle,
            MAknFileFilter* aFilter = NULL,
            MAknFileSelectionObserver* aObserver = NULL );

        /**
         * DEPRECATED: Use AknCommonDialogsDynMem funcions instead.
         *
         * A static method that launches folder selection dialog.
         * @param aFolder Full path of the folder that user selects is stored to this
         *        descriptor.
         * @param aStartFolder User defined folder to start browsing in file selection.
         * @param aMemorySelectionResourceId A resource id for memory selection dialog.
         * @param aFileSelectionResourceId A resource id for file selection dialog.
         * @param aFileSelectionTitle Custom title for file selection dialog.
         * @param aFilter Filter is asked if a directory entry can be shown in list.
         * @param aObserver An observer which is asked to verify user's selection.
         * @return Returns ETrue if user selects a folder, otherwise EFalse
         * @since 3.1
         */
        IMPORT_C static TBool RunFolderSelectDlgLD(
            TDes& aFolder,
            const TDesC& aStartFolder,
            TInt aMemorySelectionResourceId,
            TInt aFileSelectionResourceId,
            const TDesC& aFileSelectionTitle,
            MAknFileFilter* aFilter = NULL,
            MAknFileSelectionObserver* aObserver = NULL );

    };

#endif // AKNCOMMONDIALOGS_H

// End of File
