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
* Description:  Test aknglobalprogressdialog.h
*
*/

/*
 * Include files
 */

#include <aknglobalprogressdialog.h>
#include <avkon.mbg>
#include <aknutils.h>
#include <aknsddata.h>

#include "testsdknotifiers.hrh"
#include "activeexample.h"
#include "testsdknotifiers.h"

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersPGDialogNewLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersPGDialogNewLL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalProgressDialog* progressdialog = CAknGlobalProgressDialog::NewL();
    CleanupStack::PushL( progressdialog );
    STIF_ASSERT_NOT_NULL( progressdialog );
    CleanupStack::PopAndDestroy( progressdialog );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersPGDialogNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersPGDialogNewLCL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalProgressDialog* progressdialog = CAknGlobalProgressDialog::NewLC();
    STIF_ASSERT_NOT_NULL( progressdialog );
    CleanupStack::PopAndDestroy( progressdialog );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersPGDialogDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersPGDialogDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalProgressDialog* progressdialog = CAknGlobalProgressDialog::NewL();
    CleanupStack::PushL( progressdialog );
    STIF_ASSERT_NOT_NULL( progressdialog );
    CleanupStack::PopAndDestroy( progressdialog );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersPGDialogSetIconLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersPGDialogSetIconLL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalProgressDialog* progressdialog = CAknGlobalProgressDialog::NewL();
    CleanupStack::PushL( progressdialog );
    
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) );
    
    TBuf<KBufSize> buf( KTestString );
    progressdialog->SetIconL( buf, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    
    CleanupStack::PopAndDestroy( progressdialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersPGDialogSetImageLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersPGDialogSetImageLL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalProgressDialog* progressdialog = CAknGlobalProgressDialog::NewL();
    CleanupStack::PushL( progressdialog );
    
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) );
    
    progressdialog->SetImageL( file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    
    CleanupStack::PopAndDestroy( progressdialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersPGDialogShowProgressDialogLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersPGDialogShowProgressDialogLL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buf( KTestString );
    CActiveExample* observer = CActiveExample::NewLC();
    observer->ShowAndCancelProgressDialogLL( buf );
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersPGDialogUpdateProgressDialogL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersPGDialogUpdateProgressDialogL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalProgressDialog* progressdialog = CAknGlobalProgressDialog::NewL();
    CleanupStack::PushL( progressdialog );
    
    progressdialog->UpdateProgressDialog( KZero, KHundred );
    
    CleanupStack::PopAndDestroy( progressdialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersPGDialogProcessFinishedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersPGDialogProcessFinishedL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalProgressDialog* progressdialog = CAknGlobalProgressDialog::NewL();
    CleanupStack::PushL( progressdialog );
    
    progressdialog->ProcessFinished();
    
    CleanupStack::PopAndDestroy( progressdialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersPGDialogCancelProgressDialogL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersPGDialogCancelProgressDialogL( CStifItemParser& aItem )
    {
    TInt err = TestNotifiersPGDialogShowProgressDialogLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersPGDialogSetImageSkinIdsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersPGDialogSetImageSkinIdsL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalProgressDialog* progressdialog = CAknGlobalProgressDialog::NewL();
    CleanupStack::PushL( progressdialog );
    
    TAknsItemID testid = KAknsIIDNone;
    progressdialog->SetImageSkinIds( testid, testid );
    
    CleanupStack::PopAndDestroy( progressdialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersPGDialogSetSecondaryDisplayDataL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersPGDialogSetSecondaryDisplayDataL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalProgressDialog* progressdialog = CAknGlobalProgressDialog::NewL();
    CleanupStack::PushL( progressdialog );
    
    CAknSDData* sddata = new( ELeave ) CAknSDData;
    progressdialog->SetSecondaryDisplayData( sddata );
    
    CleanupStack::PopAndDestroy( progressdialog );
    return KErrNone;
    }

//End file
