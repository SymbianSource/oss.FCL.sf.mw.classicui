/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/


#include <coemain.h>
#include <featmgr.h>
#include <driveinfo.h>
#include <pathinfo.h>
#include <commondialogs.rsg>

#include "AknCommonDialogsDynMem.h"
#include "CAknMemorySelectionDialog.h"
#include "CAknMemorySelectionDialogMultiDrive.h"
#include "CAknFileSelectionDialog.h"
#include "CAknFileNamePromptDialog.h"
#include "AknCFDUtility.h"
#include "CCFDCustomFilter.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunSelectDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunSelectDlgLD(
    TInt aIncludedMedias,
    TDes& aFileName,
    TInt aMemorySelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeSelect, aFileName,
        aMemorySelectionResourceId, EFalse, 0, 0,
        KNullDesC, KNullDesC,
        NULL, NULL, aObserver, NULL, KNullDesC,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunSelectDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunSelectDlgLD(
    TInt aIncludedMedias,
    TDes& aFileName,
    TInt aMemorySelectionResourceId,
    MAknFileFilter* aFilter,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeSelect, aFileName,
        aMemorySelectionResourceId, EFalse, 0, 0,
        KNullDesC, KNullDesC,
        aFilter, NULL, aObserver, NULL, KNullDesC,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunSelectDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunSelectDlgLD(
    TInt aIncludedMedias,
    TDes& aFileName,
    TInt aMemorySelectionResourceId,
    const TDesC& aFileSelectionTitle,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeSelect, aFileName,
        aMemorySelectionResourceId, EFalse, 0, 0,
        aFileSelectionTitle, KNullDesC,
        NULL, NULL, aObserver, NULL, KNullDesC,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunSelectDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunSelectDlgLD(
    TInt aIncludedMedias,
    TDes& aFileName,
    TInt aMemorySelectionResourceId,
    TInt aFileSelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeSelect, aFileName,
        aMemorySelectionResourceId, EFalse, aFileSelectionResourceId, 0,
        KNullDesC, KNullDesC,
        NULL, NULL, aObserver, NULL, KNullDesC,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunMoveDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunMoveDlgLD(
    TInt aIncludedMedias,
    TDes& aDirectory,
    TInt aMemorySelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeMove, aDirectory,
        aMemorySelectionResourceId, EFalse, 0, 0,
        KNullDesC, KNullDesC,
        NULL, NULL, aObserver, NULL, KNullDesC,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunMoveDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunMoveDlgLD(
    TInt aIncludedMedias,
    TDes& aDirectory,
    TInt aMemorySelectionResourceId,
    MAknFileFilter* aFilter,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeMove, aDirectory,
        aMemorySelectionResourceId, EFalse, 0, 0,
        KNullDesC, KNullDesC,
        aFilter, NULL, aObserver, NULL, KNullDesC,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunMoveDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunMoveDlgLD(
    TInt aIncludedMedias,
    TDes& aDirectory,
    TInt aMemorySelectionResourceId,
    const TDesC& aFileSelectionTitle,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeMove, aDirectory,
        aMemorySelectionResourceId, EFalse, 0, 0,
        aFileSelectionTitle, KNullDesC,
        NULL, NULL, aObserver, NULL, KNullDesC,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunMoveDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunMoveDlgLD(
    TInt aIncludedMedias,
    TDes& aDirectory,
    TInt aMemorySelectionResourceId,
    TInt aFileSelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeMove, aDirectory,
        aMemorySelectionResourceId, EFalse, aFileSelectionResourceId, 0,
        KNullDesC, KNullDesC,
        NULL, NULL, aObserver, NULL, KNullDesC,
        aIncludedMedias);
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunSaveDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunSaveDlgLD(
    TInt aIncludedMedias,
    TDes& aDefaultFileName,
    TInt aMemorySelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeSave, aDefaultFileName,
        aMemorySelectionResourceId, EFalse, 0, 0,
        KNullDesC, KNullDesC,
        NULL, NULL, NULL, aObserver, KNullDesC,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunSaveDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunSaveDlgLD(
    TInt aIncludedMedias,
    TDes& aDefaultFileName,
    TInt aMemorySelectionResourceId,
    MAknFileFilter* aFilter,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeSave, aDefaultFileName,
        aMemorySelectionResourceId, EFalse, 0, 0,
        KNullDesC, KNullDesC,
        aFilter, NULL, NULL, aObserver, KNullDesC,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunSaveDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunSaveDlgLD(
    TInt aIncludedMedias,
    TDes& aDefaultFileName,
    TInt aMemorySelectionResourceId,
    const TDesC& aFileSelectionTitle,
    const TDesC& aFileNamePromptTitle,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeSave, aDefaultFileName,
        aMemorySelectionResourceId, EFalse, 0, 0,
        aFileSelectionTitle, aFileNamePromptTitle,
        NULL, NULL, NULL, aObserver, KNullDesC,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunSaveDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunSaveDlgLD(
    TInt aIncludedMedias,
    TDes& aDefaultFileName,
    TInt aMemorySelectionResourceId,
    TInt aFileSelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeSave, aDefaultFileName,
        aMemorySelectionResourceId, EFalse, aFileSelectionResourceId, 0,
        KNullDesC, KNullDesC,
        NULL, NULL, NULL, aObserver, KNullDesC,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunSaveDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunSaveDlgLD(
    TInt aIncludedMedias,
    TDes& aDefaultFileName,
    TInt aMemorySelectionResourceId,
    TInt aFileSelectionResourceId,
    const TDesC& aFileNamePromptTitle,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeSave, aDefaultFileName,
        aMemorySelectionResourceId, EFalse, aFileSelectionResourceId, 0,
        KNullDesC, aFileNamePromptTitle,
        NULL, NULL, NULL, aObserver, KNullDesC,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunSaveDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunSaveDlgNoDirectorySelectionLD(
    TInt aIncludedMedias,
    TDes& aDefaultFileName,
    TInt aMemorySelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeSave, aDefaultFileName,
        aMemorySelectionResourceId, ETrue, 0, 0,
        KNullDesC, KNullDesC,
        NULL, NULL, NULL, aObserver, KNullDesC,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunSaveDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunSaveDlgNoDirectorySelectionLD(
    TInt aIncludedMedias,
    TDes& aDefaultFileName,
    TInt aMemorySelectionResourceId,
    const TDesC& aFileNamePromptTitle,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeSave, aDefaultFileName,
        aMemorySelectionResourceId, ETrue, 0, 0,
        KNullDesC, aFileNamePromptTitle,
        NULL, NULL, NULL, aObserver, KNullDesC,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunCopyDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunCopyDlgLD(
    TInt aIncludedMedias,
    TDes& aDirectory,
    TInt aMemorySelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeCopy, aDirectory,
        aMemorySelectionResourceId, EFalse, 0, 0,
        KNullDesC, KNullDesC,
        NULL, NULL, aObserver, NULL, KNullDesC,
        aIncludedMedias );
    }


// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunCopyDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunCopyDlgLD(
    TInt aIncludedMedias,
    TDes& aDirectory,
    TInt aMemorySelectionResourceId,
    MAknFileFilter* aFilter,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeCopy, aDirectory,
        aMemorySelectionResourceId, EFalse, 0, 0,
        KNullDesC, KNullDesC,
        aFilter, NULL, aObserver, NULL, KNullDesC,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunCopyDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunCopyDlgLD(
    TInt aIncludedMedias,
    TDes& aDirectory,
    TInt aMemorySelectionResourceId,
    TInt aFileSelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeCopy, aDirectory,
        aMemorySelectionResourceId, EFalse, aFileSelectionResourceId, 0,
        KNullDesC, KNullDesC,
        NULL, NULL, aObserver, NULL, KNullDesC,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunSelectDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunSelectDlgLD(
    TInt aIncludedMedias,
    TDes& aFileName,
    const TDesC& aStartFolder,
    TInt aMemorySelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeSelect, aFileName,
        aMemorySelectionResourceId, EFalse, 0, 0,
        KNullDesC, KNullDesC,
        NULL, NULL, aObserver, NULL, aStartFolder,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunSelectDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunSelectDlgLD(
    TInt aIncludedMedias,
    TDes& aFileName,
    const TDesC& aStartFolder,
    TInt aMemorySelectionResourceId,
    MAknFileFilter* aFilter,
    MAknFileSelectionObserver* aObserver )
    {

    return RunL( ECFDDialogTypeSelect, aFileName,
        aMemorySelectionResourceId, EFalse, 0, 0,
        KNullDesC, KNullDesC,
        aFilter, NULL, aObserver, NULL, aStartFolder,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunSelectDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunSelectDlgLD(
    TInt aIncludedMedias,
    TDes& aFileName,
    const TDesC& aStartFolder,
    TInt aMemorySelectionResourceId,
    const TDesC& aFileSelectionTitle,
    MAknFileSelectionObserver* aObserver )
    {

    return RunL( ECFDDialogTypeSelect, aFileName,
        aMemorySelectionResourceId, EFalse, 0, 0,
        aFileSelectionTitle, KNullDesC,
        NULL, NULL, aObserver, NULL, aStartFolder,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunSelectDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunSelectDlgLD(
    TInt aIncludedMedias,
    TDes& aFileName,
    const TDesC& aStartFolder,
    TInt aMemorySelectionResourceId,
    TInt aFileSelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeSelect, aFileName,
        aMemorySelectionResourceId, EFalse, aFileSelectionResourceId, 0,
        KNullDesC, KNullDesC,
        NULL, NULL, aObserver, NULL, aStartFolder,
        aIncludedMedias );
    }
// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunSelectDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunSelectDlgLD(
    TInt aIncludedMedias,
    TDes& aFileName,
    const TDesC& aStartFolder,
    TInt aMemorySelectionResourceId,
    TInt aFileSelectionResourceId,
    const TDesC& aFileSelectionTitle,
    MAknFileFilter* aFilter,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeSelect, aFileName,
        aMemorySelectionResourceId, EFalse, aFileSelectionResourceId, 0,
        aFileSelectionTitle, KNullDesC,
        aFilter, NULL, aObserver, NULL, aStartFolder,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunSaveDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunSaveDlgLD(
    TInt aIncludedMedias,
    TDes& aDefaultFileName,
    const TDesC& aStartFolder,
    TInt aMemorySelectionResourceId,
    TInt aFileSelectionResourceId,
    const TDesC& aFileSelectionTitle,
    MAknFileFilter* aFilter,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeSave, aDefaultFileName,
        aMemorySelectionResourceId, EFalse, aFileSelectionResourceId, 0,
        aFileSelectionTitle, KNullDesC,
        aFilter, NULL, aObserver, NULL, aStartFolder,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunFolderSelectDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogsDynMem::RunFolderSelectDlgLD(
    TInt aIncludedMedias,
    TDes& aFolder,
    const TDesC& aStartFolder,
    TInt aMemorySelectionResourceId,
    TInt aFileSelectionResourceId,
    const TDesC& aFileSelectionTitle,
    MAknFileFilter* aFilter,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( ECFDDialogTypeBrowse, aFolder,
        aMemorySelectionResourceId, EFalse, aFileSelectionResourceId, 0,
        aFileSelectionTitle, KNullDesC,
        aFilter, NULL, aObserver, NULL, aStartFolder,
        aIncludedMedias );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogsDynMem::RunL
//
//
// -----------------------------------------------------------------------------
//
TBool AknCommonDialogsDynMem::RunL(
    TCommonDialogType aDialogType,
    TDes& aFileName,
    TInt aMemorySelectionResourceId,
    TBool aNoFileSelectionDialog,
    TInt aFileSelectionResourceId,
    TInt aFileNamePromptResourceId,
    const TDesC& aFileSelectionTitle,
    const TDesC& aFileNamePromptTitle,
    MAknFileFilter* aFileFilter,
    MAknMemorySelectionObserver* /*aMemorySelectionObserver*/,
    MAknFileSelectionObserver* aFileSelectionObserver,
    MAknFileSelectionObserver* aFileNamePromptObserver,
    const TDesC& aStartFolder,
    TInt aIncludedMedias )
    {

    FeatureManager::InitializeLibL();
    TBool mmcSupported( FeatureManager::FeatureSupported( KFeatureIdMmc ) );
    FeatureManager::UnInitializeLib();
    CCoeEnv* coeEnv = CCoeEnv::Static();

    // Temp variables
    HBufC* rootPath         = HBufC::NewLC(KMaxPath);
    HBufC* defaultFolder    = HBufC::NewLC(KMaxPath);
    HBufC* cachedRootPath   = HBufC::NewLC(KMaxPath);

    TPtr ptrRootPath = rootPath->Des();
    TPtr ptrDefaultFolder = defaultFolder->Des();
    TPtr ptrCachedRootPath = cachedRootPath->Des();

    TDriveNumber defaultDrive;
    User::LeaveIfError(
        DriveInfo::GetDefaultDrive( DriveInfo::EDefaultSystem,
                                    ( TInt& )defaultDrive ) );
    TDriveNumber selectedDrive( defaultDrive );

    // Variables for return values from dialogs
    TBool memoryReturnValue(    EFalse );
    TBool fileReturnValue(      EFalse );
    TBool promptReturnValue(    EFalse );

    // These booleans tell what dialogs have been shown
    TBool usedMemorySelection(  EFalse );
    TBool usedFileSelection(    EFalse );
    TBool usedFileNamePrompt(   EFalse );

    // Variable to handle start folder, if client gives a specific folder to
    // start browsing in file selecting
    HBufC * startFolder = aStartFolder.AllocLC();
    TPtr ptrStartFolder = startFolder->Des();

    TDriveNumber defaultMMC;
    User::LeaveIfError(
        DriveInfo::GetDefaultDrive( DriveInfo::EDefaultRemovableMassStorage,
                                    ( TInt& )defaultMMC ) );
    TCFDDriveStatus driveStatus( EDriveOK );

    // Start a FOREVER loop in order to show memory selection dialog again if
    // user hits back in file selection
    FOREVER
        {
        // Reset variables
        *rootPath = KNullDesC;
        *defaultFolder = KNullDesC;
        fileReturnValue = ETrue;
        promptReturnValue = ETrue;
        memoryReturnValue = EFalse;

        ptrRootPath = rootPath->Des();
        ptrDefaultFolder = defaultFolder->Des();

        if ( mmcSupported )
            {
            driveStatus = AknCFDUtility::DriveStatusL( defaultMMC );
            }

        // Start folder is not defined so ask for it. Normal situation, or
        // second round with user given starting folder.
        if ( ptrStartFolder == KNullDesC )
            {
            // Run MEMORY SELECTION DIALOG
           CAknMemorySelectionDialogMultiDrive* memoryDialogMD =
                CAknMemorySelectionDialogMultiDrive::NewL(
                    aDialogType,
                    aMemorySelectionResourceId,
                    EFalse,
                    aIncludedMedias
                    ); 
           CleanupStack::PushL( memoryDialogMD );

            // Check if there ame multiple drives in which case use memory
            // selection instead of file selection.
            if( usedMemorySelection ||
                AknCFDUtility::UserVisibleDriveCountL( aIncludedMedias ) > 1 )
                {
                // Multiple drives: Execute memory selection
                memoryReturnValue = memoryDialogMD->ExecuteL( selectedDrive,
                    &ptrRootPath, &ptrDefaultFolder );
                usedMemorySelection = ETrue; // Memory selection was used
                CleanupStack::PopAndDestroy();// memoryDialog or memoryDialogMD
                if ( !memoryReturnValue )
                    {
                    // User cancels memory selection
                    CleanupStack::PopAndDestroy(startFolder);
                    CleanupStack::PopAndDestroy(cachedRootPath);
                    CleanupStack::PopAndDestroy(defaultFolder);
                    CleanupStack::PopAndDestroy(rootPath);
                    return EFalse;
                    }
                }
             else
                {
                // Only one drive - get it's paths. EPhoneMemory is legacy.
                // Functionally it points to index 0 of stored paths array, not
                // necessarily the drive of the phone memory.

                // The above is only valid for legacy code (even remote drive is
                // used). For multiple drive support, default system drive
                // should be more reasonable to be used in this case.
                memoryDialogMD->GetDrivePaths(
                    defaultDrive,
                    &ptrRootPath,
                    &ptrDefaultFolder
                    );
                CleanupStack::PopAndDestroy();// memoryDialog or memoryDialogMD
                }
            }
        else // User gave a specific folder to start browsing
            {
            ptrDefaultFolder = ptrStartFolder;
            AknCFDUtility::AddTrailingBackslash(ptrDefaultFolder);
            TDriveNumber driveNumber = ( TDriveNumber )
                AknCFDUtility::DriveNumber( ptrDefaultFolder );

            // Different logic should be used here.
            // Not only C & E drives need to be checked now. And the new method
            // PathInfo::GetRootPath could be used to get each drive's root
            // path. The specific folder user gave should be in drive's root
            // path. So generic check is launched here.
            PathInfo::GetRootPath( ptrRootPath, driveNumber );

            if ( ptrDefaultFolder.Length() )
                {
                if ( ptrDefaultFolder.Left( ptrRootPath.Length() ).CompareF(
                     ptrRootPath ) )
                    {
                    User::Leave( KErrPathNotFound );
                    }
                else
                    {
                    ptrDefaultFolder = ptrDefaultFolder.Right(
                        ptrDefaultFolder.Length() - ptrRootPath.Length() );
                    }
                }

            // Use system default drive if current drive is not ready
            driveStatus = AknCFDUtility::DriveStatusL( driveNumber );

            if ( driveStatus == EDriveNotReady )
                {
                PathInfo::GetRootPath( ptrRootPath, defaultDrive );
                ptrDefaultFolder = KNullDesC;
                }

            ptrStartFolder = KNullDesC; // we use starting folder only once...

            usedMemorySelection =
                ( AknCFDUtility::UserVisibleDriveCountL( aIncludedMedias ) > 1 );
            }

        ptrCachedRootPath = ptrRootPath;

        CAknFileSelectionDialog* fileDialog = NULL;
        // aNoFileSelectionDialog is ETrue only with save dialog when the
        // client does not want the file selection dialog to be launched:
        if( !aNoFileSelectionDialog )
            {
            fileDialog = CAknFileSelectionDialog::NewL( aDialogType,
                         aFileSelectionResourceId );
            CleanupStack::PushL( fileDialog );
            fileDialog->SetTitleL( aFileSelectionTitle );
            fileDialog->SetObserver( aFileSelectionObserver );
            if ( usedMemorySelection )
                {
                HBufC* text = coeEnv->AllocReadResourceLC(
                              R_CFD_TEXT_SOFTKEY_BACK );
                fileDialog->SetRightSoftkeyRootFolderL( *text );
                CleanupStack::PopAndDestroy(); // text
                }
            fileDialog->SetDefaultFolderL( ptrDefaultFolder );
            if( aFileFilter )
                {
                CCFDCustomFilter* filter =
                    new( ELeave ) CCFDCustomFilter( aFileFilter );
                CleanupStack::PushL( filter );
                fileDialog->AddFilterL( filter ); // Ownership is transferred
                CleanupStack::Pop(); // filter
                }
            }
        else
            {
            ptrCachedRootPath.Append( ptrDefaultFolder );
            }

        // Start file selection ExecuteL loop (needed in save case)
        FOREVER
            {
            usedFileSelection = EFalse;
            usedFileNamePrompt = EFalse;

            // Root path must be always the root path which is read from
            // resource
            ptrRootPath = ptrCachedRootPath;
            if( fileDialog )
                {
                TRAPD( endKeyErr, fileReturnValue = fileDialog->ExecuteL( ptrRootPath ) );
                if ( endKeyErr == KErrAbort )
                    {
                    CleanupStack::PopAndDestroy(); // fileDialog
                    CleanupStack::PopAndDestroy(4); //4 number of HBufC
                    return EFalse;
                    }

                // If file selection dialog returns ESelectionKey, it means
                // that browsing was not used. The directory was empty.
                if ( fileReturnValue != CAknCommonDialogsBase::ESelectionKey )
                    {
                    usedFileSelection = ETrue;
                    }

                // If the user cancels file selection and memory selection was
                // not used, exit function
                if ( ( !usedMemorySelection ) && ( !fileReturnValue ) )
                    {
                    CleanupStack::PopAndDestroy(); // fileDialog
                    CleanupStack::PopAndDestroy(4); //4 number of HBufC
                    return EFalse;
                    }
                }

            // If dialog type is SAVE and user selected something or in the case
            // of save dialog, if the file selection was not used at all, show
            // Filename prompt dialog
            if ( ( ( aDialogType == ECFDDialogTypeSave )
                   && ( fileReturnValue ) ) || aNoFileSelectionDialog )
                {
                CAknFileNamePromptDialog* promptDialog =
                    CAknFileNamePromptDialog::NewL(
                    aFileNamePromptResourceId );
                CleanupStack::PushL( promptDialog );
                promptDialog->SetTitleL( aFileNamePromptTitle );
                promptDialog->SetObserver( aFileNamePromptObserver );
                promptDialog->SetPathL( ptrRootPath );

                promptReturnValue = promptDialog->ExecuteL( aFileName );
                CleanupStack::PopAndDestroy(); // promptDialog
                usedFileNamePrompt = ETrue;
                if ( promptReturnValue )
                    {
                    // User approved the filename.
                    // Exit loop
                    break;
                    }
                else
                    {
                    // User cancelled the operation.
                    if ( fileDialog )
                        {
                        CleanupStack::PopAndDestroy(); // fileDialog
                        }
                    CleanupStack::PopAndDestroy(4); //4 number of HBufC
                    return EFalse;
                    }
                }
            // Exit loop if filename prompt wasn't used
            if ( ( !usedFileNamePrompt ) || 
                // Exit loop if file selection wasn't used but prompt was
                ( usedFileNamePrompt && !usedFileSelection ) )
                {
                break;
                }
            } // FOREVER

        if ( fileDialog )
            {
            CleanupStack::PopAndDestroy(); // fileDialog
            }

        if (  // If neither file selection or filename prompt was used, break
            ( !usedFileNamePrompt && !usedFileSelection ) ||
             // If filename prompt was used and selection was made, break
            ( usedFileNamePrompt && promptReturnValue ) ||
             // If only file selection was used and selection made, break
            ( usedFileSelection && !usedFileNamePrompt && fileReturnValue ) )
            {
            break;
            }

        } // FOREVER

    if ( aDialogType == ECFDDialogTypeSave )
        {
        // In the save case, append the typed file in the end of path
        // If not enough space in descriptor, let the system panic because
        // it's not reasonable to append a partial file name.
        ptrRootPath.Append( aFileName );
        }

    aFileName = ptrRootPath;

    CleanupStack::PopAndDestroy(4); //4 number of HBufC

    return ETrue;
    }


//  End of File
