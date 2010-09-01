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
* Description:  Test AknCommonDialogs.h
*
*/



// [INCLUDE FILES]
#include <testsdkcfd.rsg>
#include <akncommondialogs.h>
#include <maknfileselectionobserver.h>
#include <maknfilefilter.h>

#include "testsdkcfd.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunSelectDlgLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunSelectDlgLD( CStifItemParser& /*aItem*/ )
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
    
    TBool flag = AknCommonDialogs::RunSelectDlgLD( fileName, 0, observer );

    CleanupStack::PopAndDestroy( observer );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunSelectDlgLDFilterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunSelectDlgLDFilterL( CStifItemParser& /*aItem*/ )
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

    TBool flag = AknCommonDialogs::RunSelectDlgLD( fileName, 0, filter, NULL );
    
    CleanupStack::PopAndDestroy( filter );

    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunSelectDlgLDTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunSelectDlgLDTitleL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KFileName, "Select Dialog" );
    TBuf<KMaxFileName> fileName( KFileName );
    _LIT( KFileSelTitle, "File Selection Title" );
    TBuf<KMaxFileName> fileSelTitle( KFileSelTitle );

    TBool flag = AknCommonDialogs::RunSelectDlgLD( fileName, 0, fileSelTitle, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunSelectDlgLDFileIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunSelectDlgLDFileIdL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KFileName, "Select Dialog" );
    TBuf<KMaxFileName> fileName( KFileName );

    TBool flag = AknCommonDialogs::RunSelectDlgLD( fileName, 0, 0, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunMoveDlgLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunMoveDlgLD( CStifItemParser& /*aItem*/ )
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

    TBool flag = AknCommonDialogs::RunMoveDlgLD( directory, 0, observer );
    STIF_ASSERT_FALSE( flag );
    CleanupStack::PopAndDestroy( observer );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunMoveDlgLDFilterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunMoveDlgLDFilterL( CStifItemParser& /*aItem*/ )
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

    TBool flag = AknCommonDialogs::RunMoveDlgLD( directory, 0, filter, NULL );

    CleanupStack::PopAndDestroy( filter );

    STIF_ASSERT_FALSE( flag );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunMoveDlgLDTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunMoveDlgLDTitleL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDirectory, "C:\\Data" );
    TBuf<KMaxPath> directory( KDirectory );
    _LIT( KFileSelTitle, "File Selection Title" );
    TBuf<KMaxFileName> fileSelTitle( KFileSelTitle );

    TBool flag = AknCommonDialogs::RunMoveDlgLD( directory, 0, fileSelTitle, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunMoveDlgLDFileIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunMoveDlgLDFileIdL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDirectory, "C:\\Data" );
    TBuf<KMaxPath> directory( KDirectory );

    TBool flag = AknCommonDialogs::RunMoveDlgLD( directory, 0, 0, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunSaveDlgLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunSaveDlgLD( CStifItemParser& /*aItem*/ )
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

    TBool flag = AknCommonDialogs::RunSaveDlgLD( defaultFileName, 0, observer );

    CleanupStack::PopAndDestroy( observer );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunSaveDlgLDFilterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunSaveDlgLDFilterL( CStifItemParser& /*aItem*/ )
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

    TBool flag = AknCommonDialogs::RunSaveDlgLD( defaultFileName, 0, filter, NULL );

    CleanupStack::PopAndDestroy( filter );

    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunSaveDlgLDTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunSaveDlgLDTitleL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDefaultFileName, "Save Dialog" );
    TBuf<KMaxFileName> defaultFileName( KDefaultFileName );
    _LIT( KFileSelTitle, "File Selection Title" );
    TBuf<KMaxFileName> fileSelTitle( KFileSelTitle );
    _LIT( KFileNamePromptTitle, "File Name Prompt Title" );
    TBuf<KMaxFileName> fileNamePromptTitle( KFileNamePromptTitle );

    TBool flag = AknCommonDialogs::RunSaveDlgLD
        ( defaultFileName, 0, fileSelTitle, fileNamePromptTitle, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunSaveDlgLDFileIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunSaveDlgLDFileIdL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDefaultFileName, "Save Dialog" );
    TBuf<KMaxFileName> defaultFileName( KDefaultFileName );

    TBool flag = AknCommonDialogs::RunSaveDlgLD( defaultFileName, 0, 0, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunSaveDlgLDIdTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunSaveDlgLDIdTitleL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDefaultFileName, "Save Dialog" );
    TBuf<KMaxFileName> defaultFileName( KDefaultFileName );
    _LIT( KFileNamePromptTitle, "File Name Prompt Title" );
    TBuf<KMaxFileName> fileNamePromptTitle( KFileNamePromptTitle );

    TBool flag = AknCommonDialogs::RunSaveDlgLD
        ( defaultFileName, 0, 0, fileNamePromptTitle, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunSaveDlgNoDirectorySelectionLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunSaveDlgNoDirectorySelectionLD( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDefaultFileName, "Save Dialog" );
    TBuf<KMaxFileName> defaultFileName( KDefaultFileName );

    TBool flag = AknCommonDialogs::RunSaveDlgNoDirectorySelectionLD
        ( defaultFileName, 0, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunSaveDlgNoDirectorySelectionLDTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunSaveDlgNoDirectorySelectionLDTitleL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDefaultFileName, "Save Dialog" );
    TBuf<KMaxFileName> defaultFileName( KDefaultFileName );
    _LIT( KFileNamePromptTitle, "File Name Prompt Title" );
    TBuf<KMaxFileName> fileNamePromptTitle( KFileNamePromptTitle );

    TBool flag = AknCommonDialogs::RunSaveDlgNoDirectorySelectionLD
        ( defaultFileName, 0, fileNamePromptTitle, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunCopyDlgLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunCopyDlgLD( CStifItemParser& /*aItem*/ )
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

    TBool flag = AknCommonDialogs::RunCopyDlgLD( directory, 0, observer );

    CleanupStack::PopAndDestroy( observer );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunCopyDlgLDFilterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunCopyDlgLDFilterL( CStifItemParser& /*aItem*/ )
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

    TBool flag = AknCommonDialogs::RunCopyDlgLD( directory, 0, filter, NULL );

    CleanupStack::PopAndDestroy( filter );

    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunCopyDlgLDFileIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunCopyDlgLDFileIdL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KDirectory, "C:\\Data" );
    TBuf<KMaxPath> directory( KDirectory );

    TBool flag = AknCommonDialogs::RunCopyDlgLD( directory, 0, 0, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunSelectDlgLDFolderL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunSelectDlgLDFolderL( CStifItemParser& /*aItem*/ )
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

    TBool flag = AknCommonDialogs::RunSelectDlgLD( fileName, startFolder, 0, observer );

    CleanupStack::PopAndDestroy( observer );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunSelectDlgLDFolderFilterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunSelectDlgLDFolderFilterL( CStifItemParser& /*aItem*/ )
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

    TBool flag = AknCommonDialogs::RunSelectDlgLD
        ( fileName, startFolder, 0, filter, NULL );

    CleanupStack::PopAndDestroy( filter );

    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunSelectDlgLDFolderTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunSelectDlgLDFolderTitleL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KFileName, "Select Dialog" );
    TBuf<KMaxFileName> fileName( KFileName );
    _LIT( KStartFolder, "C:\\Data\\Images" );
    TBuf<KMaxPath> startFolder( KStartFolder );
    _LIT( KFileSelTitle, "File Selection Title" );
    TBuf<KMaxFileName> fileSelTitle( KFileSelTitle );

    TBool flag = AknCommonDialogs::RunSelectDlgLD
        ( fileName, startFolder, 0, fileSelTitle, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunSelectDlgLDFolderFileIDL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunSelectDlgLDFolderFileIDL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KFileName, "Select Dialog" );
    TBuf<KMaxFileName> fileName( KFileName );
    _LIT( KStartFolder, "C:\\Data" );
    TBuf<KMaxPath> startFolder( KStartFolder );

    TBool flag = AknCommonDialogs::RunSelectDlgLD
        ( fileName, startFolder, 0, 0, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunSelectDlgLDFolderTitleFilterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunSelectDlgLDFolderTitleFilterL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KFileName, "Select Dialog" );
    TBuf<KMaxFileName> fileName( KFileName );
    _LIT( KStartFolder, "C:\\Data" );
    TBuf<KMaxPath> startFolder( KStartFolder );
    _LIT( KFileSelTitle, "File Selection Title" );
    TBuf<KMaxFileName> fileSelTitle( KFileSelTitle );

    TBool flag = AknCommonDialogs::RunSelectDlgLD
        ( fileName, startFolder, 0, 0, fileSelTitle, NULL, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunSaveDlgLDFolderTitleFilterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunSaveDlgLDFolderTitleFilterL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KFileName, "Select Dialog" );
    TBuf<KMaxFileName> fileName( KFileName );
    _LIT( KStartFolder, "C:\\Data" );
    TBuf<KMaxPath> startFolder( KStartFolder );
    _LIT( KFileSelTitle, "File Selection Title" );
    TBuf<KMaxFileName> fileSelTitle( KFileSelTitle );

    TBool flag = AknCommonDialogs::RunSaveDlgLD
        ( fileName, startFolder, 0, 0, fileSelTitle, NULL, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestCDRunFolderSelectDlgLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestCDRunFolderSelectDlgLD( CStifItemParser& /*aItem*/ )
    {
    _LIT( KFolder, "C:\\Data" );
    TBuf<KMaxPath> folder( KFolder );
    _LIT( KStartFolder, "C:\\Data\\Images" );
    TBuf<KMaxPath> startFolder( KStartFolder );
    _LIT( KFileSelTitle, "File Selection Title" );
    TBuf<KMaxFileName> fileSelTitle( KFileSelTitle );

    TBool flag = AknCommonDialogs::RunFolderSelectDlgLD
        ( folder, startFolder, 0, 0, fileSelTitle, NULL, NULL );
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

//  [End of File]
