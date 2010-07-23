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
* Description:  Test aknglobalmsgquery.h
*
*/

/*
 * Include files
 */
#include <aknglobalmsgquery.h>
#include <aknsddata.h>
#include <avkon.mbg>
#include <aknutils.h>

#include "testsdknotifiers.hrh"
#include "activeexample.h"
#include "testsdknotifiers.h"

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersMsgQueryNewLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersMsgQueryNewLL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalMsgQuery* msgquery = CAknGlobalMsgQuery::NewL();
    CleanupStack::PushL( msgquery );
    STIF_ASSERT_NOT_NULL( msgquery );
    CleanupStack::PopAndDestroy( msgquery );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersMsgQueryNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersMsgQueryNewLCL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalMsgQuery* msgquery = CAknGlobalMsgQuery::NewLC();
    STIF_ASSERT_NOT_NULL( msgquery );
    CleanupStack::PopAndDestroy( msgquery );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersMsgQueryDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersMsgQueryDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalMsgQuery* msgquery = CAknGlobalMsgQuery::NewL();
    CleanupStack::PushL( msgquery );
    STIF_ASSERT_NOT_NULL( msgquery );
    CleanupStack::PopAndDestroy( msgquery );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersMsgQueryShowMsgQueryLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersMsgQueryShowMsgQueryLL( CStifItemParser& /*aItem*/ )
    {
    CActiveExample* observer = CActiveExample::NewLC();
    observer->ShowMsgQueryLL( KNullDesC, KZero, KNullDesC, KNullDesC, KZero, KZero );
    CleanupStack::PopAndDestroy( observer );
    
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) );
    TBuf<KBufSize> text( KTestString );
    
    CActiveExample* observerparamer = CActiveExample::NewLC();
    observerparamer->ShowMsgQueryLL( text, KZero, text, file, KZero, KOne );
    CleanupStack::PopAndDestroy( observerparamer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersMsgQueryUpdateMsgQueryL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersMsgQueryUpdateMsgQueryL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalMsgQuery* msgquery = CAknGlobalMsgQuery::NewL();
    CleanupStack::PushL( msgquery );
    msgquery->UpdateMsgQuery( KTwo );
    CleanupStack::PopAndDestroy( msgquery );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersMsgQueryCancelMsgQueryL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersMsgQueryCancelMsgQueryL( CStifItemParser& aItem )
    {
    TInt err = TestNotifiersMsgQueryShowMsgQueryLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersMsgQuerySetExitDelayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersMsgQuerySetExitDelayL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalMsgQuery* msgquery = CAknGlobalMsgQuery::NewL();
    CleanupStack::PushL( msgquery );
    msgquery->SetExitDelay( KTwo );
    CleanupStack::PopAndDestroy( msgquery );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersMsgQuerySetImageSkinIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersMsgQuerySetImageSkinIdL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalMsgQuery* msgquery = CAknGlobalMsgQuery::NewL();
    CleanupStack::PushL( msgquery );
    TAknsItemID testid = KAknsIIDNone;
    msgquery->SetImageSkinId( testid );
    CleanupStack::PopAndDestroy( msgquery );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersMsgQuerySetSecondaryDisplayDataL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersMsgQuerySetSecondaryDisplayDataL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalMsgQuery* msgquery = CAknGlobalMsgQuery::NewL();
    CleanupStack::PushL( msgquery );
    CAknSDData* sddata = new( ELeave ) CAknSDData;
    msgquery->SetSecondaryDisplayData( sddata );
    CleanupStack::PopAndDestroy( msgquery );
    
    return KErrNone;
    }

//End file
