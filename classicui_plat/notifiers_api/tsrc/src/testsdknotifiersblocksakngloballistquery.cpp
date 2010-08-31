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
* Description:  Test AknGlobalListQuery.h
*
*/

/*
 * Include files
 */

#include <akngloballistquery.h>
#include <badesca.h>
#include <aknsddata.h>

#include "testsdknotifiers.hrh"
#include "activeexample.h"
#include "testsdknotifiers.h"

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::TestNotifiersListQueryNewLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersListQueryNewLL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalListQuery* listquery = CAknGlobalListQuery::NewL();
    CleanupStack::PushL( listquery );
    STIF_ASSERT_NOT_NULL( listquery );
    CleanupStack::PopAndDestroy( listquery );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::TestNotifiersListQueryNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersListQueryNewLCL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalListQuery* listquery = CAknGlobalListQuery::NewLC();
    STIF_ASSERT_NOT_NULL( listquery );
    CleanupStack::PopAndDestroy( listquery );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::TestNotifiersListQueryDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersListQueryDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalListQuery* listquery = CAknGlobalListQuery::NewL();
    CleanupStack::PushL( listquery );
    STIF_ASSERT_NOT_NULL( listquery );
    CleanupStack::PopAndDestroy( listquery );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::TestNotifiersListQueryShowListQueryLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersListQueryShowListQueryLL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalListQuery* listquery = CAknGlobalListQuery::NewL();
    CleanupStack::PushL( listquery );
    
    CDesCArrayFlat* arr = new( ELeave ) CDesCArrayFlat( KSize );
    CleanupStack::PushL( arr );

    HBufC* buf1 = KTom().AllocLC();
    HBufC* buf2 = KJack().AllocLC();
    HBufC* buf3 = KMary().AllocLC();
    
    arr->AppendL(*buf1);
    arr->AppendL(*buf2);
    arr->AppendL(*buf3);
    
    RTimer timer;
    CleanupClosePushL( timer );
    TRequestStatus timerStatus;
    timer.CreateLocal();  
    timer.After( timerStatus, KTimeDelay ); 
    User::WaitForRequest( timerStatus );
    
    listquery->ShowListQueryL( arr, timerStatus );
    
    timer.Close();
    CleanupStack::PopAndDestroy( &timer );
    CleanupStack::PopAndDestroy( buf3 );
    CleanupStack::PopAndDestroy( buf2 );
    CleanupStack::PopAndDestroy( buf1 );
    CleanupStack::PopAndDestroy( arr );
    CleanupStack::PopAndDestroy( listquery );
    
    CAknGlobalListQuery* listquerytwo = CAknGlobalListQuery::NewL();
    CleanupStack::PushL( listquerytwo );
    
    CDesCArrayFlat* arrcopy = new( ELeave ) CDesCArrayFlat( KSize );
    CleanupStack::PushL( arrcopy );

    HBufC* buf4 = KTom().AllocLC();
    HBufC* buf5 = KJack().AllocLC();
    HBufC* buf6 = KMary().AllocLC();
    
    arrcopy->AppendL(*buf4);
    arrcopy->AppendL(*buf5);
    arrcopy->AppendL(*buf6);
        
    RTimer timertwo;
    CleanupClosePushL( timertwo );
    TRequestStatus status;
    timertwo.CreateLocal();  
    timertwo.After( status, KTimeDelay ); 
    User::WaitForRequest( status );
    
    listquerytwo->ShowListQueryL( arrcopy, status );
    
    timertwo.Close();
    CleanupStack::PopAndDestroy( &timertwo );
    CleanupStack::PopAndDestroy( buf6 );
    CleanupStack::PopAndDestroy( buf5 );
    CleanupStack::PopAndDestroy( buf4 );
    CleanupStack::PopAndDestroy( arrcopy );
    CleanupStack::PopAndDestroy( listquerytwo );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::TestNotifiersListQueryMoveSelectionUpL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersListQueryMoveSelectionUpL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalListQuery* listquery = CAknGlobalListQuery::NewL();
    CleanupStack::PushL( listquery );
    listquery->MoveSelectionUp();
    
    CleanupStack::PopAndDestroy( listquery );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::TestNotifiersListQueryMoveSelectionDownL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersListQueryMoveSelectionDownL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalListQuery* listquery = CAknGlobalListQuery::NewL();
    CleanupStack::PushL( listquery );
    listquery->MoveSelectionDown();
    
    CleanupStack::PopAndDestroy( listquery );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::TestNotifiersListQuerySelectItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersListQuerySelectItemL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalListQuery* listquery = CAknGlobalListQuery::NewL();
    CleanupStack::PushL( listquery );
    listquery->SelectItem();
    
    CleanupStack::PopAndDestroy( listquery );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::TestNotifiersListQueryCancelListQueryL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersListQueryCancelListQueryL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* arr = new( ELeave ) CDesCArrayFlat( KSize );
    CleanupStack::PushL( arr );

    HBufC* buf1 = KTom().AllocLC();
    HBufC* buf2 = KJack().AllocLC();
    HBufC* buf3 = KMary().AllocLC();
    
    arr->AppendL(*buf1);
    arr->AppendL(*buf2);
    arr->AppendL(*buf3);
    
    TBuf<KBufSize> buf( KTestString );
    CActiveExample* observer = CActiveExample::NewLC();
    observer->ShowAndCancelConfirmationQueryLL( buf );
    
    CleanupStack::PopAndDestroy( observer );
    CleanupStack::PopAndDestroy( buf3 );
    CleanupStack::PopAndDestroy( buf2 );
    CleanupStack::PopAndDestroy( buf1 );
    CleanupStack::PopAndDestroy( arr );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::TestNotifiersListQuerySetHeadingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersListQuerySetHeadingLL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalListQuery* listquery = CAknGlobalListQuery::NewL();
    CleanupStack::PushL( listquery );
    TBuf<KBufSize> heading( KTestString );
    listquery->SetHeadingL( heading );
    
    CleanupStack::PopAndDestroy( listquery );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::TestNotifiersListQuerySetSecondaryDisplayDataL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersListQuerySetSecondaryDisplayDataL( CStifItemParser& /*aItem*/ )
    {
    CAknGlobalListQuery* listquery = CAknGlobalListQuery::NewL();
    CleanupStack::PushL( listquery );
    CAknSDData* sddata = new( ELeave ) CAknSDData;
    listquery->SetSecondaryDisplayData( sddata );
    
    CleanupStack::PopAndDestroy( listquery );
    return KErrNone;
    }

//End file
