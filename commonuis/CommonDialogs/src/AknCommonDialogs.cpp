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
#include <pathinfo.h>
#include <commondialogs.rsg>

#include "AknCommonDialogs.h"
#include "AknCommonDialogsDynMem.h"
#include "CAknMemorySelectionDialog.h"
#include "CAknFileSelectionDialog.h"
#include "CAknFileNamePromptDialog.h"
#include "CCFDCustomFilter.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunSelectDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunSelectDlgLD(
    TDes& aFileName,
    TInt aMemorySelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunSelectDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aFileName,
        aMemorySelectionResourceId,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunSelectDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunSelectDlgLD(
    TDes& aFileName,
    TInt aMemorySelectionResourceId,
    MAknFileFilter* aFilter,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunSelectDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aFileName,
        aMemorySelectionResourceId,
        aFilter,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunSelectDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunSelectDlgLD(
    TDes& aFileName,
    TInt aMemorySelectionResourceId,
    const TDesC& aFileSelectionTitle,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunSelectDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aFileName,
        aMemorySelectionResourceId,
        aFileSelectionTitle,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunSelectDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunSelectDlgLD(
    TDes& aFileName,
    TInt aMemorySelectionResourceId,
    TInt aFileSelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunSelectDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aFileName,
        aMemorySelectionResourceId, 
        aFileSelectionResourceId,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunMoveDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunMoveDlgLD(
    TDes& aDirectory,
    TInt aMemorySelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunMoveDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aDirectory,
        aMemorySelectionResourceId,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunMoveDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunMoveDlgLD(
    TDes& aDirectory,
    TInt aMemorySelectionResourceId,
    MAknFileFilter* aFilter,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunMoveDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aDirectory,
        aMemorySelectionResourceId,
        aFilter,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunMoveDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunMoveDlgLD(
    TDes& aDirectory,
    TInt aMemorySelectionResourceId,
    const TDesC& aFileSelectionTitle,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunMoveDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aDirectory,
        aMemorySelectionResourceId,
        aFileSelectionTitle,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunMoveDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunMoveDlgLD(
    TDes& aDirectory,
    TInt aMemorySelectionResourceId,
    TInt aFileSelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunMoveDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aDirectory,
        aMemorySelectionResourceId,
        aFileSelectionResourceId,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunSaveDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunSaveDlgLD(
    TDes& aDefaultFileName,
    TInt aMemorySelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunSaveDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aDefaultFileName,
        aMemorySelectionResourceId,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunSaveDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunSaveDlgLD(
    TDes& aDefaultFileName,
    TInt aMemorySelectionResourceId,
    MAknFileFilter* aFilter,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunSaveDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aDefaultFileName,
        aMemorySelectionResourceId,
        aFilter,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunSaveDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunSaveDlgLD(
    TDes& aDefaultFileName,
    TInt aMemorySelectionResourceId,
    const TDesC& aFileSelectionTitle,
    const TDesC& aFileNamePromptTitle,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunSaveDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aDefaultFileName,
        aMemorySelectionResourceId,
        aFileSelectionTitle,
        aFileNamePromptTitle,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunSaveDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunSaveDlgLD(
    TDes& aDefaultFileName,
    TInt aMemorySelectionResourceId,
    TInt aFileSelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunSaveDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aDefaultFileName,
        aMemorySelectionResourceId,
        aFileSelectionResourceId,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunSaveDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunSaveDlgLD(
    TDes& aDefaultFileName,
    TInt aMemorySelectionResourceId,
    TInt aFileSelectionResourceId,
    const TDesC& aFileNamePromptTitle,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunSaveDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aDefaultFileName,
        aMemorySelectionResourceId,
        aFileSelectionResourceId,
        aFileNamePromptTitle,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunSaveDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunSaveDlgNoDirectorySelectionLD(
    TDes& aDefaultFileName,
    TInt aMemorySelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunSaveDlgNoDirectorySelectionLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aDefaultFileName,
        aMemorySelectionResourceId,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunSaveDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunSaveDlgNoDirectorySelectionLD(
    TDes& aDefaultFileName,
    TInt aMemorySelectionResourceId,
    const TDesC& aFileNamePromptTitle,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunSaveDlgNoDirectorySelectionLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aDefaultFileName,
        aMemorySelectionResourceId,
        aFileNamePromptTitle,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunCopyDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunCopyDlgLD(
    TDes& aDirectory,
    TInt aMemorySelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunCopyDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aDirectory,
        aMemorySelectionResourceId,
        aObserver );
    }


// -----------------------------------------------------------------------------
// AknCommonDialogs::RunCopyDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunCopyDlgLD(
    TDes& aDirectory,
    TInt aMemorySelectionResourceId,
    MAknFileFilter* aFilter,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunCopyDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aDirectory,
        aMemorySelectionResourceId,
        aFilter,
        aObserver );
    }


// -----------------------------------------------------------------------------
// AknCommonDialogs::RunCopyDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunCopyDlgLD(
    TDes& aDirectory,
    TInt aMemorySelectionResourceId,
    TInt aFileSelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunCopyDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aDirectory,
        aMemorySelectionResourceId,
        aFileSelectionResourceId,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunSelectDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunSelectDlgLD(
    TDes& aFileName,
    const TDesC& aStartFolder,
    TInt aMemorySelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunSelectDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aFileName,
        aStartFolder,
        aMemorySelectionResourceId,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunSelectDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunSelectDlgLD(
    TDes& aFileName,
    const TDesC& aStartFolder,
    TInt aMemorySelectionResourceId,
    MAknFileFilter* aFilter,
    MAknFileSelectionObserver* aObserver )
    {

    return AknCommonDialogsDynMem::RunSelectDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aFileName,
        aStartFolder,
        aMemorySelectionResourceId,
        aFilter,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunSelectDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunSelectDlgLD(
    TDes& aFileName,
    const TDesC& aStartFolder,
    TInt aMemorySelectionResourceId,
    const TDesC& aFileSelectionTitle,
    MAknFileSelectionObserver* aObserver )
    {

    return AknCommonDialogsDynMem::RunSelectDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aFileName,
        aStartFolder,
        aMemorySelectionResourceId,
        aFileSelectionTitle,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunSelectDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunSelectDlgLD(
    TDes& aFileName,
    const TDesC& aStartFolder,
    TInt aMemorySelectionResourceId,
    TInt aFileSelectionResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunSelectDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aFileName,
        aStartFolder,
        aMemorySelectionResourceId,
        aFileSelectionResourceId,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunSelectDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunSelectDlgLD(
    TDes& aFileName, 
    const TDesC& aStartFolder, 
    TInt aMemorySelectionResourceId, 
    TInt aFileSelectionResourceId, 
    const TDesC& aFileSelectionTitle, 
    MAknFileFilter* aFilter, 
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunSelectDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aFileName,
        aStartFolder,
        aMemorySelectionResourceId,
        aFileSelectionResourceId,
        aFileSelectionTitle,
        aFilter,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunSaveDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunSaveDlgLD(
    TDes& aDefaultFileName, 
    const TDesC& aStartFolder, 
    TInt aMemorySelectionResourceId, 
    TInt aFileSelectionResourceId, 
    const TDesC& aFileSelectionTitle, 
    MAknFileFilter* aFilter, 
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunSaveDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aDefaultFileName,
        aStartFolder,
        aMemorySelectionResourceId,
        aFileSelectionResourceId,
        aFileSelectionTitle,
        aFilter,
        aObserver );
    }

// -----------------------------------------------------------------------------
// AknCommonDialogs::RunFolderSelectDlgLD
// A wrapper for AknCommonDialogsDynMem:: function.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool AknCommonDialogs::RunFolderSelectDlgLD( 
    TDes& aFolder, 
    const TDesC& aStartFolder, 
    TInt aMemorySelectionResourceId, 
    TInt aFileSelectionResourceId, 
    const TDesC& aFileSelectionTitle, 
    MAknFileFilter* aFilter, 
    MAknFileSelectionObserver* aObserver )
    {
    return AknCommonDialogsDynMem::RunFolderSelectDlgLD( 
        AknCommonDialogsDynMem::EMemoryTypePhone|AknCommonDialogsDynMem::EMemoryTypeMMC,
        aFolder,
        aStartFolder,
        aMemorySelectionResourceId,
        aFileSelectionResourceId,
        aFileSelectionTitle,
        aFilter,
        aObserver );
    }

//  End of File  
