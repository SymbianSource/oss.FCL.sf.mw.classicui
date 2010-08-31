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
* Description:  Test aknglobalconfirmationquery.h
*
*/

/*
 * Include files
 */

#include <aknglobalconfirmationquery.h>
#include <e32cmn.h>
#include <aknsddata.h>

#include "testsdknotifiers.hrh"
#include "activeexample.h"
#include "testsdknotifiers.h"

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::TestNotifiersCFMQueryNewLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersCFMQueryNewLL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalConfirmationQuery* confirmationquery = CAknGlobalConfirmationQuery::NewL();
    CleanupStack::PushL( confirmationquery );
    STIF_ASSERT_NOT_NULL( confirmationquery );
    CleanupStack::PopAndDestroy( confirmationquery );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::TestNotifiersCFMQueryNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersCFMQueryNewLCL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalConfirmationQuery* confirmationquery = CAknGlobalConfirmationQuery::NewLC();
    STIF_ASSERT_NOT_NULL( confirmationquery );
    CleanupStack::PopAndDestroy( confirmationquery );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::TestNotifiersCFMQueryDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersCFMQueryDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalConfirmationQuery* confirmationquery = CAknGlobalConfirmationQuery::NewL();
    CleanupStack::PushL( confirmationquery );
    STIF_ASSERT_NOT_NULL( confirmationquery );
    CleanupStack::PopAndDestroy( confirmationquery );
        
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::TestNotifiersCFMQueryShowConfirmationQueryLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersCFMQueryShowConfirmationQueryLL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> prompt( KTestString );
    CAknGlobalConfirmationQuery* confirmationquery = CAknGlobalConfirmationQuery::NewL();
    CleanupStack::PushL( confirmationquery );
    
    RTimer timer;
    CleanupClosePushL( timer );
    TRequestStatus timerStatus;
    timer.CreateLocal();  
    timer.After( timerStatus, KTimeDelay ); 
    User::WaitForRequest( timerStatus );
    
    confirmationquery->ShowConfirmationQueryL( timerStatus, prompt );
    
    timer.Close();
    CleanupStack::PopAndDestroy( &timer );
    CleanupStack::PopAndDestroy( confirmationquery );
    
    CAknGlobalConfirmationQuery* confirmationquerytwo = CAknGlobalConfirmationQuery::NewL();
    CleanupStack::PushL( confirmationquerytwo );
    CAknSDData* sddata = new( ELeave ) CAknSDData;
    confirmationquerytwo->SetSecondaryDisplayData( sddata );
    
    RTimer timertwo;
    CleanupClosePushL( timertwo );
    TRequestStatus status;
    timertwo.CreateLocal();  
    timertwo.After( status, KTimeDelay ); 
    User::WaitForRequest( status );
    
    confirmationquerytwo->ShowConfirmationQueryL( status, prompt, KZero, KZero, prompt, 
        KZero, KZero, CAknQueryDialog::ENoTone, ETrue );
    
    timertwo.Close();
    CleanupStack::PopAndDestroy( &timertwo );
    CleanupStack::PopAndDestroy( confirmationquerytwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::TestNotifiersCFMQueryUpdateConfirmationQueryL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersCFMQueryUpdateConfirmationQueryL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalConfirmationQuery* confirmationquery = CAknGlobalConfirmationQuery::NewL();
    CleanupStack::PushL( confirmationquery );
    
    confirmationquery->UpdateConfirmationQuery( KTwo );
    
    CleanupStack::PopAndDestroy( confirmationquery );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::TestNotifiersCFMQueryCancelConfirmationQueryL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersCFMQueryCancelConfirmationQueryL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buf( KTestString );
    CActiveExample* observer = CActiveExample::NewLC();
    observer->ShowAndCancelConfirmationQueryLL( buf );
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::TestNotifiersCFMQuerySetImageSkinIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersCFMQuerySetImageSkinIdL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalConfirmationQuery* confirmationquery = CAknGlobalConfirmationQuery::NewL();
    CleanupStack::PushL( confirmationquery );
    TAknsItemID testid = KAknsIIDNone;
    confirmationquery->SetImageSkinId( testid );
    
    CleanupStack::PopAndDestroy( confirmationquery );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::TestNotifiersCFMQuerySetSecondaryDisplayDataL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersCFMQuerySetSecondaryDisplayDataL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalConfirmationQuery* confirmationquery = CAknGlobalConfirmationQuery::NewL();
    CleanupStack::PushL( confirmationquery );
    CAknSDData* sddata = new( ELeave ) CAknSDData;
    confirmationquery->SetSecondaryDisplayData( sddata );
    
    CleanupStack::PopAndDestroy( confirmationquery );
    return KErrNone;
    }

//End file
