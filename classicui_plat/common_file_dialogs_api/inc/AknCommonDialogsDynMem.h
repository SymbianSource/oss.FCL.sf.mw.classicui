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
* Description:  Static class to call combined common file dialogs
*
*/



#ifndef AKNCOMMONDIALOGSDYNMEM_H
#define AKNCOMMONDIALOGSDYNMEM_H


#include <CAknCommonDialogsBase.h>

class MAknMemorySelectionObserver;
class MAknFileSelectionObserver;
class MAknFileFilter;


/**
 *  New version of AknCommonDialogs class suporting dynamic drives such as
 *  remote drive. Use this instead of now deprecated old AknCommonDialogs.
 *
 *  A simple facade class that consists of static functions that launch UI
 *  components in a sequence. First, memory selection component is launched and
 *  then file/directory selection component. In save and move dialogs directory
 *  selection may not be shown if there are no subdirectories to choose from.
 *  In save dialog, finally filename prompt component is launched.
 *
 *  All methods have an obligatory resource ID parameter for memory selection
 *  because it contains the paths for both memories (Phone&MMC) (LOCATION
 *  structs). New TMemoryTypes functionality allows defining dynamic memories
 *  to be used.
 *
 *  If set, an observer is queried just before exiting the dialog.
 *  At this point the application can either reject or accept user's selection.
 *  Every dialog returns a boolean value which tells if user has selected
 *  something or not.
 *
 *  @lib CommonDialogs.lib
 *  @since S60 3.2
 */
NONSHARABLE_CLASS( AknCommonDialogsDynMem )
    {

public:

    /**
     * Bit flag definition of the memory types that will  be listed by the
     * dialog. These are used in the new functions to include for example
     * remote drives. In case new media types are added in the future, the
     * types can be added to the end of this enumeration.
     *
     * Application logic and UI specification is mainly interested in
     * division between 'phone memory' and 'MMC' with the latest addition of
     * 'remote drives'. In Symbian OS level this is somewhat more
     * complicated because these do not map directly to any drive or memory
     * type. For example try defining the drive letter for remote drive.
     *
     * Basically TMediaType could be used but the types may vary in the same
     * drive and application logic mostly understands only division between
     * 'phone' and 'MMC' memory - these do not map to TMediaType directly.
     * This the reasoning for this new enumeration.
     *
     * Uses binary flagging.
     *
     * Use for example 'EMemoryTypePhone|EMemoryTypeMMC|EMemoryTypeRemote' to
     * have phone memory, MMC and remote drives included.
     *
     * Notice: 0 value means no media included. Only
     * EMemoryTypePhone|EMemoryTypeMMC for legacy applications and
     * EMemoryTypePhone|EMemoryTypeMMC|EMemoryTypeRemote for new remote
     * drives-aware applications are supported for the time being.
     * Use EMemoryTypePhone|EMemoryTypeInternalMassStorage|EMemoryMMCExternal
     * |EMemoryTypeRemote for multiple drive support. And EMemoryTypeMMC will
     * be deprecated.
     */
    enum TMemoryTypes
        {
       /**
        * EMemoryTypePhone
        * Device memory drive inside phone
        *
        * There might be multiple device memory drives because of multiple
        * partitions.
        */
        EMemoryTypePhone        = 0x00000001,

       /**
        * @Deprecated It will be mapped to
        *             EMemoryTypeInternalMassStorage|EMemoryMMCExternal
        *             internally.
        *
        * EMemoryTypeMMC
        * Standard external removable memory card drive
        *
        * There might be multiple removable MMC drives because of
        * multiple partitions.
        */
        EMemoryTypeMMC          = 0x00000002,

       /**
        * EMemoryTypeRemote
        * Remote drive
        *
        * There might be multiple remote drives.
        */
        EMemoryTypeRemote       = 0x00000004,

       /**
        * EMemoryTypeInternalMassStorage
        * Internal mass storage, like internal MMC, hard disk, flash, etc.
        *
        * There might be multiple internal disk drives
        */
        EMemoryTypeInternalMassStorage  = 0x00000008,

       /**
        * EMemoryTypeMMCExternal
        * Removable external memory card
        *
        */
        EMemoryTypeMMCExternal = 0x00000010

        };

public:

    /**
     * A static method that launches file selection dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
     * @param aFileName Full path and filename of the file that user
     *        selects is stored to this descriptor.
     * @param aMemorySelectionResourceId A resource id for memory selection
     *        dialog.
     * @param aObserver An observer which is asked, if set, to verify user's
     *        selection.
     * @return Returns ETrue if user selects a file, otherwise EFalse.
     */
    IMPORT_C static TBool RunSelectDlgLD(
        TInt aIncludedMedias,
        TDes& aFileName,
        TInt aMemorySelectionResourceId,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches file selection dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
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
        TInt aIncludedMedias,
        TDes& aFileName,
        TInt aMemorySelectionResourceId,
        MAknFileFilter* aFilter,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches file selection dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
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
        TInt aIncludedMedias,
        TDes& aFileName,
        TInt aMemorySelectionResourceId,
        const TDesC& aFileSelectionTitle,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches file selection dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
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
        TInt aIncludedMedias,
        TDes& aFileName,
        TInt aMemorySelectionResourceId,
        TInt aFileSelectionResourceId,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches move dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
     * @param aDirectory Full path of the folder that user
     *        selects is stored to this descriptor.
     * @param aMemorySelectionResourceId A resource id for memory selection
     *        dialog.
     * @param aObserver An observer which is asked, if set, to verify user's
     *        selection.
     * @return Returns ETrue if user selects a folder, otherwise EFalse.
     */
    IMPORT_C static TBool RunMoveDlgLD(
        TInt aIncludedMedias,
        TDes& aDirectory,
        TInt aMemorySelectionResourceId,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches move dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
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
        TInt aIncludedMedias,
        TDes& aDirectory,
        TInt aMemorySelectionResourceId,
        MAknFileFilter* aFilter,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches move dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
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
        TInt aIncludedMedias,
        TDes& aDirectory,
        TInt aMemorySelectionResourceId,
        const TDesC& aFileSelectionTitle,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches move dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
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
        TInt aIncludedMedias,
        TDes& aDirectory,
        TInt aMemorySelectionResourceId,
        TInt aFileSelectionResourceId,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches save dialog which does not run folder
     * selection dialog at all. Instead the resulting path will be
     * constructed from the root and default folder read from resources and
     * from the file name given by the user.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
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
        TInt aIncludedMedias,
        TDes& aDefaultFileName,
        TInt aMemorySelectionResourceId,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches save dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
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
        TInt aIncludedMedias,
        TDes& aDefaultFileName,
        TInt aMemorySelectionResourceId,
        MAknFileFilter* aFilter,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches save dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
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
        TInt aIncludedMedias,
        TDes& aDefaultFileName,
        TInt aMemorySelectionResourceId,
        const TDesC& aFileSelectionTitle,
        const TDesC& aFileNamePromptTitle,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches save dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
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
        TInt aIncludedMedias,
        TDes& aDefaultFileName,
        TInt aMemorySelectionResourceId,
        TInt aFileSelectionResourceId,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches save dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
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
        TInt aIncludedMedias,
        TDes& aDefaultFileName,
        TInt aMemorySelectionResourceId,
        TInt aFileSelectionResourceId,
        const TDesC& aFileNamePromptTitle,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches save dialog. No file selection dialog
     * for directory selection is displayed.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
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
        TInt aIncludedMedias,
        TDes& aDefaultFileName,
        TInt aMemorySelectionResourceId,
        MAknFileSelectionObserver* aObserver = NULL );

     /**
     * A static method that launches save dialog. No file selection dialog
     * for directory selection is displayed.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
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
        TInt aIncludedMedias,
        TDes& aDefaultFileName,
        TInt aMemorySelectionResourceId,
        const TDesC& aFileNamePromptTitle,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches copy dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
     * @param aDirectory Full path of the folder that user
     *        selects is stored to this descriptor.
     * @param aMemorySelectionResourceId A resource id for memory selection
     *        dialog.
     * @param aObserver An observer which is asked, if set, to verify user's
     *        selection.
     * @return Returns ETrue if user selects a folder, otherwise EFalse.
     */
    IMPORT_C static TBool RunCopyDlgLD(
        TInt aIncludedMedias,
        TDes& aDirectory,
        TInt aMemorySelectionResourceId,
        MAknFileSelectionObserver* aObserver = NULL );


    /**
     * A static method that launches copy dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
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
        TInt aIncludedMedias,
        TDes& aDirectory,
        TInt aMemorySelectionResourceId,
        MAknFileFilter* aFilter,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches copy dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
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
        TInt aIncludedMedias,
        TDes& aDirectory,
        TInt aMemorySelectionResourceId,
        TInt aFileSelectionResourceId,
        MAknFileSelectionObserver* aObserver = NULL );

     /**
     * A static method that launches file selection dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
     * @param aFileName Full path and filename of the file that user
     *        selects is stored to this descriptor.
     * @param aStartFolder User defined folder to start browsing in file
     *        selection.
     * @param aMemorySelectionResourceId A resource id for memory selection
     *        dialog.
     * @param aObserver An observer which is asked, if set, to verify user's
     *        selection.
     * @return Returns ETrue if user selects a file, otherwise EFalse.
     * @since 3.2
     */
    IMPORT_C static TBool RunSelectDlgLD(
        TInt aIncludedMedias,
        TDes& aFileName,
        const TDesC& aStartFolder,
        TInt aMemorySelectionResourceId,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches file selection dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
     * @param aFileName Full path and filename of the file that user
     *        selects is stored to this descriptor.
     * @param aStartFolder User defined folder to start browsing in file
     *        selection
     * @param aMemorySelectionResourceId A resource id for memory selection
     *        dialog.
     * @param aFilter Filter is asked if a directory entry can be shown in
     *        list. Ownership is not transferred.
     * @param aObserver An observer which is asked, if set, to verify user's
     *        selection.
     * @return Returns ETrue if user selects a file, otherwise EFalse.
     * @since 3.2
     */
    IMPORT_C static TBool RunSelectDlgLD(
        TInt aIncludedMedias,
        TDes& aFileName,
        const TDesC& aStartFolder,
        TInt aMemorySelectionResourceId,
        MAknFileFilter* aFilter,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches file selection dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
     * @param aFileName Full path and filename of the file that user
     *        selects is stored to this descriptor.
     * @param aStartFolder User defined folder to start browsing in file
     *        selection
     * @param aMemorySelectionResourceId A resource id for memory selection
     *        dialog.
     * @param aFileSelectionTitle A custom title for file selection dialog.
     * @param aObserver An observer which is asked, if set, to verify user's
     *        selection.
     * @return Returns ETrue if user selects a file, otherwise EFalse.
     * @since 3.2
     */
    IMPORT_C static TBool RunSelectDlgLD(
        TInt aIncludedMedias,
        TDes& aFileName,
        const TDesC& aStartFolder,
        TInt aMemorySelectionResourceId,
        const TDesC& aFileSelectionTitle,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches file selection dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
     * @param aFileName Full path and filename of the file that user
     *        selects is stored to this descriptor.
     * @param aStartFolder User defined folder to start browsing in file
     *        selection
     * @param aMemorySelectionResourceId A resource id for memory selection
     *        dialog.
     * @param aFileSelectionResourceId A resource id for file selection
     *        dialog.
     * @param aObserver An observer which is asked, if set, to verify user's
     *        selection.
     * @return Returns ETrue if user selects a file, otherwise EFalse.
     * @since 3.2
     */
    IMPORT_C static TBool RunSelectDlgLD(
        TInt aIncludedMedias,
        TDes& aFileName,
        const TDesC& aStartFolder,
        TInt aMemorySelectionResourceId,
        TInt aFileSelectionResourceId,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches file selection dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
     * @param aFileName Full path and filename of the file that user selects is
     *        stored to this descriptor.
     * @param aStartFolder User defined folder to start browsing in file
     *        selection.
     * @param aMemorySelectionResourceId A resource id for memory selection
     *        dialog.
     * @param aFileSelectionResourceId A resource id for file selection dialog.
     * @param aFileSelectionTitle Custom title for file selection dialog.
     * @param aFilter Filter asked if a directory entry can be shown in list.
     * @param aObserver An observer which is asked to verify user's selection.
     * @return Returns ETrue if user selects a file, otherwise EFalse
     * @since 3.2
     */
    IMPORT_C static TBool RunSelectDlgLD(
        TInt aIncludedMedias,
        TDes& aFileName,
        const TDesC& aStartFolder,
        TInt aMemorySelectionResourceId,
        TInt aFileSelectionResourceId,
        const TDesC& aFileSelectionTitle,
        MAknFileFilter* aFilter = NULL,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches save dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
     * @param aDefaultFileName Full path + the filename that user enters
     *        is stored to this descriptor. The descriptor may contain text
     *        that is used as default filename, for example "Attachment".
     * @param aStartFolder User defined folder to start browsing in file
     *        selection.
     * @param aMemorySelectionResourceId A resource id for memory selection
     *        dialog.
     * @param aFileSelectionResourceId A resource id for file selection dialog.
     * @param aFileSelectionTitle Custom title for file selection dialog.
     * @param aFilter Filter asked if a directory entry can be shown in list.
     * @param aObserver An observer which is asked, if set, to verify the
     *        filename that user types.
     * @return Returns ETrue if user accepts or enters a filename, otherwise
     *         EFalse.
     * @since 3.2
     */
    IMPORT_C static TBool RunSaveDlgLD(
        TInt aIncludedMedias,
        TDes& aDefaultFileName,
        const TDesC& aStartFolder,
        TInt aMemorySelectionResourceId,
        TInt aFileSelectionResourceId,
        const TDesC& aFileSelectionTitle,
        MAknFileFilter* aFilter = NULL,
        MAknFileSelectionObserver* aObserver = NULL );

    /**
     * A static method that launches folder selection dialog.
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes.
     * @param aFolder Full path of the folder that user selects is stored to
     *        this descriptor.
     * @param aStartFolder User defined folder to start browsing in file
     *        selection.
     * @param aMemorySelectionResourceId A resource id for memory selection
     *        dialog.
     * @param aFileSelectionResourceId A resource id for file selection dialog.
     * @param aFileSelectionTitle Custom title for file selection dialog.
     * @param aFilter Filter is asked if a directory entry can be shown in
     *        list.
     * @param aObserver An observer which is asked to verify user's selection.
     * @return Returns ETrue if user selects a folder, otherwise EFalse
     * @since 3.2
     */
    IMPORT_C static TBool RunFolderSelectDlgLD(
        TInt aIncludedMedias,
        TDes& aFolder,
        const TDesC& aStartFolder,
        TInt aMemorySelectionResourceId,
        TInt aFileSelectionResourceId,
        const TDesC& aFileSelectionTitle,
        MAknFileFilter* aFilter = NULL,
        MAknFileSelectionObserver* aObserver = NULL );

private:

    /**
     * A static method that launches UI components in a sequence.
     * @param aType Defines what type of dialog is shown.
     * @param aFileName A reference to a descriptor. Usage depends on the
     *        dialog type.
     * @param aMemorySelectionResourceId A resource id for memory selection
     *        dialog.
     * @param aNoFileSelectionDialog, if ETrue and aType is ECFDDialogType-
     *        Save, no file selection dialog is launched, instead the file
     *        will be saved in the default folder given in the resource
     *        structure referred by aMemorySelectionResourceId.
     * @param aFileSelectionResourceId A resource id for file selection
     *        dialog.
     * @param aFileNamePromptResourceId A resource id for filename prompt
     *        dialog.
     * @param aFileSelectionTitle Custom title for file selection.
     * @param aFileNamePromptTitle Custom title for filename prompt dialog.
     * @param aFileFilter Filter is asked if a directory entry can be shown
     *        in list.
     * @param aMemorySelectionObserver An observer for memory selection
     *        dialog.
     * @param aFileSelectionObserver An observer for file selection dialog.
     * @param aFileNamePromptObserver An observer for filename prompt
     *        dialog.
     * @param aStartFolder User defined folder to start browsing in file
     *        selection
     * @param aIncludedMedias defines which medias are included in the
     *        dialog. See TMemoryTypes
     * @return Returns a boolean value that depends on the case.
     */
    static TBool RunL(
        TCommonDialogType aType,
        TDes& aFileName,
        TInt aMemorySelectionResourceId,
        TBool aNoFileSelectionDialog,
        TInt aFileSelectionResourceId,
        TInt aFileNamePromptResourceId,
        const TDesC& aFileSelectionTitle,
        const TDesC& aFileNamePromptTitle,
        MAknFileFilter* aFileFilter,
        MAknMemorySelectionObserver* aMemorySelectionObserver,
        MAknFileSelectionObserver* aFileSelectionObserver,
        MAknFileSelectionObserver* aFileNamePromptObserver,
        const TDesC& aStartFolder,
        TInt aIncludedMedias );

    };

#endif // AKNCOMMONDIALOGSDYNMEM_H
