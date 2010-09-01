/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test AknCommonDialogsDynMem.h
*
*/



// [INCLUDE FILES]
#include <testsdkcfd.rsg>
#include <akncommondialogsdynmem.h>
#include <maknfileselectionobserver.h>
#include <maknfilefilter.h>

#include "testsdkcfd.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunSelectDlgLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunSelectDlgLD( CStifItemParser& /*aItem*/ )
    {
    _LIT( KFileName, "Select Dialog" );
    TBuf<KMaxFileName> fileName( KFileName );

    struct MObserver : public MAknFileSelectionObserver
        {
        TBool OkToExitL( const TDesC& /*aDriveAndPath*/, const TEntry& /*aEntry*/)
            {
            return ETrue;
            }
        };

    MObserver* observer = new( ELeave ) MObserver;
    CleanupStack::PushL( observer );

    TBool flag = AknCommonDialogsDynMem::RunSelectDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypePhone, fileName, 0, observer );

    CleanupStack::PopAndDestroy( observer );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunSelectDlgLDFilterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunSelectDlgLDFilterL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KFileName, "Select Dialog" );
    TBuf<KMaxFileName> fileName( KFileName );
    
    struct MFileFilter : public MAknFileFilter
        {
        TBool Accept( const TDesC& /*aDriveAndPath*/, const TEntry& /*aEntry*/) const
            {
            return ETrue;
            }
        };

    MFileFilter* filter = new (ELeave) MFileFilter;
    CleanupStack::PushL( filter );

    TBool flag = AknCommonDialogsDynMem::RunSelectDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypeMMC, fileName, 0, filter, NULL );

    CleanupStack::PopAndDestroy( filter );

    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunSelectDlgLDTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunSelectDlgLDTitleL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KFileName, "Select Dialog" );
    TBuf<KMaxFileName> fileName( KFileName );
    _LIT( KFileSelTitle, "File Selection Title" );
    TBuf<KMaxFileName> fileSelTitle( KFileSelTitle );

    TBool flag = AknCommonDialogsDynMem::RunSelectDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypeMMC, fileName, 0, fileSelTitle, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunSelectDlgLDFileIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunSelectDlgLDFileIdL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KFileName, "Select Dialog" );
    TBuf<KMaxFileName> fileName( KFileName );

    TBool flag = AknCommonDialogsDynMem::RunSelectDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypeMMC, fileName, 0, 0, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunMoveDlgLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunMoveDlgLD( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDirectory, "C:\\Data" );
    TBuf<KMaxPath> directory( KDirectory );

    struct MObserver : public MAknFileSelectionObserver
        {
        TBool OkToExitL( const TDesC& /*aDriveAndPath*/, const TEntry& /*aEntry*/)
            {
            return ETrue;
            }
        };

    MObserver* observer = new( ELeave ) MObserver;
    CleanupStack::PushL( observer );

    TBool flag = AknCommonDialogsDynMem::RunMoveDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypeMMC, directory, 0, observer );

    CleanupStack::PopAndDestroy( observer );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunMoveDlgLDFilterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunMoveDlgLDFilterL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDirectory, "C:\\Data" );
    TBuf<KMaxPath> directory( KDirectory );
    
    struct MFileFilter : public MAknFileFilter
        {
        TBool Accept( const TDesC& /*aDriveAndPath*/, const TEntry& /*aEntry*/) const
            {
            return ETrue;
            }
        };

    MFileFilter* filter = new (ELeave) MFileFilter;
    CleanupStack::PushL( filter );

    TBool flag = AknCommonDialogsDynMem::RunMoveDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypeMMC, directory, 0, filter, NULL );

    CleanupStack::PopAndDestroy( filter );

    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunMoveDlgLDTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunMoveDlgLDTitleL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDirectory, "C:\\Data" );
    TBuf<KMaxPath> directory( KDirectory );
    _LIT( KFileSelTitle, "File Selection Title" );
    TBuf<KMaxFileName> fileSelTitle( KFileSelTitle );

    TBool flag = AknCommonDialogsDynMem::RunMoveDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypeMMC, directory, 0, fileSelTitle, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunMoveDlgLDFileIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunMoveDlgLDFileIdL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDirectory, "C:\\Data" );
    TBuf<KMaxPath> directory( KDirectory );

    TBool flag = AknCommonDialogsDynMem::RunMoveDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypeMMC, directory, 0, 0, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunSaveDlgLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunSaveDlgLD( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDefaultFileName, "Save Dialog" );
    TBuf<KMaxFileName> defaultFileName( KDefaultFileName );

    struct MObserver : public MAknFileSelectionObserver
        {
        TBool OkToExitL( const TDesC& /*aDriveAndPath*/, const TEntry& /*aEntry*/)
            {
            return ETrue;
            }
        };

    MObserver* observer = new( ELeave ) MObserver;
    CleanupStack::PushL( observer );

    TBool flag = AknCommonDialogsDynMem::RunSaveDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypePhone, defaultFileName, 0, observer );

    CleanupStack::PopAndDestroy( observer );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunSaveDlgLDFilterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunSaveDlgLDFilterL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDefaultFileName, "Save Dialog" );
    TBuf<KMaxFileName> defaultFileName( KDefaultFileName );
    
    struct MFileFilter : public MAknFileFilter
        {
        TBool Accept( const TDesC& /*aDriveAndPath*/, const TEntry& /*aEntry*/) const
            {
            return ETrue;
            }
        };

    MFileFilter* filter = new (ELeave) MFileFilter;
    CleanupStack::PushL( filter );

    TBool flag = AknCommonDialogsDynMem::RunSaveDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypePhone, defaultFileName, 0, filter, NULL );

    CleanupStack::PopAndDestroy( filter );

    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunSaveDlgLDTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunSaveDlgLDTitleL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDefaultFileName, "Save Dialog" );
    TBuf<KMaxFileName> defaultFileName( KDefaultFileName );
    _LIT( KFileSelTitle, "File Selection Title" );
    TBuf<KMaxFileName> fileSelTitle( KFileSelTitle );
    _LIT( KFileNamePromptTitle, "File Name Prompt Title" );
    TBuf<KMaxFileName> fileNamePromptTitle( KFileNamePromptTitle );

    TBool flag = AknCommonDialogsDynMem::RunSaveDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypePhone, defaultFileName,
        0, fileSelTitle, fileNamePromptTitle, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunSaveDlgLDFileIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunSaveDlgLDFileIdL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDefaultFileName, "Save Dialog" );
    TBuf<KMaxFileName> defaultFileName( KDefaultFileName );

    TBool flag = AknCommonDialogsDynMem::RunSaveDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypePhone, defaultFileName, 0, 0, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunSaveDlgLDIdTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunSaveDlgLDIdTitleL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDefaultFileName, "Save Dialog" );
    TBuf<KMaxFileName> defaultFileName( KDefaultFileName );
    _LIT( KFileNamePromptTitle, "File Name Prompt Title" );
    TBuf<KMaxFileName> fileNamePromptTitle( KFileNamePromptTitle );

    TBool flag = AknCommonDialogsDynMem::RunSaveDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypePhone, defaultFileName, 0, 0, 
        fileNamePromptTitle, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunSaveDlgNoDirectorySelectionLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunSaveDlgNoDirectorySelectionLD( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDefaultFileName, "Save Dialog" );
    TBuf<KMaxFileName> defaultFileName( KDefaultFileName );

    TBool flag = AknCommonDialogsDynMem::RunSaveDlgNoDirectorySelectionLD
        ( AknCommonDialogsDynMem::EMemoryTypeMMC, defaultFileName, 0, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunSaveDlgNoDirectorySelectionLDTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunSaveDlgNoDirectorySelectionLDTitleL
    ( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDefaultFileName, "Save Dialog" );
    TBuf<KMaxFileName> defaultFileName( KDefaultFileName );
    _LIT( KFileNamePromptTitle, "File Name Prompt Title" );
    TBuf<KMaxFileName> fileNamePromptTitle( KFileNamePromptTitle );

    TBool flag = AknCommonDialogsDynMem::RunSaveDlgNoDirectorySelectionLD
        ( AknCommonDialogsDynMem::EMemoryTypePhone, defaultFileName, 0, 
        fileNamePromptTitle, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunCopyDlgLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunCopyDlgLD( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDirectory, "C:\\Data" );
    TBuf<KMaxPath> directory( KDirectory );

    struct MObserver : public MAknFileSelectionObserver
        {
        TBool OkToExitL( const TDesC& /*aDriveAndPath*/, const TEntry& /*aEntry*/)
            {
            return ETrue;
            }
        };

    MObserver* observer = new( ELeave ) MObserver;
    CleanupStack::PushL( observer );

    TBool flag = AknCommonDialogsDynMem::RunCopyDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypePhone, directory, 0, observer );

    CleanupStack::PopAndDestroy( observer );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunCopyDlgLDFilterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunCopyDlgLDFilterL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDirectory, "C:\\Data" );
    TBuf<KMaxPath> directory( KDirectory );
    
    struct MFileFilter : public MAknFileFilter
        {
        TBool Accept( const TDesC& /*aDriveAndPath*/, const TEntry& /*aEntry*/) const
            {
            return ETrue;
            }
        };

    MFileFilter* filter = new (ELeave) MFileFilter;
    CleanupStack::PushL( filter );

    TBool flag = AknCommonDialogsDynMem::RunCopyDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypePhone, directory, 0, filter, NULL );

    CleanupStack::PopAndDestroy( filter );

    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunCopyDlgLDFileIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunCopyDlgLDFileIdL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDirectory, "C:\\Data" );
    TBuf<KMaxPath> directory( KDirectory );

    TBool flag = AknCommonDialogsDynMem::RunCopyDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypePhone, directory, 0, 0, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunSelectDlgLDFolderL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunSelectDlgLDFolderL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KFileName, "Select Dialog" );
    TBuf<KMaxFileName> fileName( KFileName );
    _LIT( KStartFolder, "C:\\Data\\Images" );
    TBuf<KMaxPath> startFolder( KStartFolder );

    struct MObserver : public MAknFileSelectionObserver
        {
        TBool OkToExitL( const TDesC& /*aDriveAndPath*/, const TEntry& /*aEntry*/)
            {
            return ETrue;
            }
        };

    MObserver* observer = new( ELeave ) MObserver;
    CleanupStack::PushL( observer );

    TBool flag = AknCommonDialogsDynMem::RunSelectDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypePhone, fileName, startFolder, 0, observer );

    CleanupStack::PopAndDestroy( observer );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunSelectDlgLDFolderFilterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunSelectDlgLDFolderFilterL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KFileName, "Select Dialog" );
    TBuf<KMaxFileName> fileName( KFileName );
    _LIT( KStartFolder, "C:\\Data\\Images" );
    TBuf<KMaxPath> startFolder( KStartFolder );
    
    struct MFileFilter : public MAknFileFilter
        {
        TBool Accept( const TDesC& /*aDriveAndPath*/, const TEntry& /*aEntry*/) const
            {
            return ETrue;
            }
        };

    MFileFilter* filter = new (ELeave) MFileFilter;
    CleanupStack::PushL( filter );

    TBool flag = AknCommonDialogsDynMem::RunSelectDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypePhone, fileName, startFolder, 0, filter, NULL );

    CleanupStack::PopAndDestroy( filter );

    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunSelectDlgLDFolderTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunSelectDlgLDFolderTitleL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KFileName, "Select Dialog" );
    TBuf<KMaxFileName> fileName( KFileName );
    _LIT( KStartFolder, "C:\\Data\\Images" );
    TBuf<KMaxPath> startFolder( KStartFolder );
    _LIT( KFileSelTitle, "File Selection Title" );
    TBuf<KMaxFileName> fileSelTitle( KFileSelTitle );

    TBool flag = AknCommonDialogsDynMem::RunSelectDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypePhone, fileName, startFolder, 0, 
        fileSelTitle, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunSelectDlgLDFolderFileIDL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunSelectDlgLDFolderFileIDL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KFileName, "Select Dialog" );
    TBuf<KMaxFileName> fileName( KFileName );
    _LIT( KStartFolder, "C:\\Data" );
    TBuf<KMaxPath> startFolder( KStartFolder );

    TBool flag = AknCommonDialogsDynMem::RunSelectDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypePhone, fileName, startFolder, 0, 0, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunSelectDlgLDFolderTitleFilterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunSelectDlgLDFolderTitleFilterL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KFileName, "Select Dialog" );
    TBuf<KMaxFileName> fileName( KFileName );
    _LIT( KStartFolder, "C:\\Data" );
    TBuf<KMaxPath> startFolder( KStartFolder );
    _LIT( KFileSelTitle, "File Selection Title" );
    TBuf<KMaxFileName> fileSelTitle( KFileSelTitle );

    TBool flag = AknCommonDialogsDynMem::RunSelectDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypePhone, fileName, startFolder, 0, 0, 
        fileSelTitle, NULL, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunSaveDlgLDFolderTitleFilterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunSaveDlgLDFolderTitleFilterL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KFileName, "Select Dialog" );
    TBuf<KMaxFileName> fileName( KFileName );
    _LIT( KStartFolder, "C:\\Data" );
    TBuf<KMaxPath> startFolder( KStartFolder );
    _LIT( KFileSelTitle, "File Selection Title" );
    TBuf<KMaxFileName> fileSelTitle( KFileSelTitle );

    TBool flag = AknCommonDialogsDynMem::RunSaveDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypePhone, fileName, startFolder, 0, 0, 
        fileSelTitle, NULL, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDDMRunFolderSelectDlgLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDDMRunFolderSelectDlgLD( CStifItemParser& /*aItem*/ )
    {
    _LIT( KFolder, "C:\\Data" );
    TBuf<KMaxPath> folder( KFolder );
    _LIT( KStartFolder, "C:\\Data\\Images" );
    TBuf<KMaxPath> startFolder( KStartFolder );
    _LIT( KFileSelTitle, "File Selection Title" );
    TBuf<KMaxFileName> fileSelTitle( KFileSelTitle );

    TBool flag = AknCommonDialogsDynMem::RunFolderSelectDlgLD
        ( AknCommonDialogsDynMem::EMemoryTypePhone, folder, startFolder, 0, 0, 
        fileSelTitle, NULL, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }


//  [End of File]
