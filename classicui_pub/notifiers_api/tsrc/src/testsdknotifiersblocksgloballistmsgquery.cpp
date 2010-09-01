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
* Description:  Test AknGlobalListMsgQuery.h
*
*/

/*
 * Include files
 */
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <akngloballistmsgquery.h>
#include <bamdesca.h>
#include <badesca.h>
#include <aknsddata.h>

#include "testsdknotifiers.h"
#include "activeexample.h"

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestCAknGMsgQueryL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestCAknGMsgQueryNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKNotifiers, "TestSDKNotifiers" );
    _LIT( KTestCAknGMsgQueryNewL, "In TestCAknGMsgQueryNewL" );
    TestModuleIf().Printf( 0, KTestSDKNotifiers, KTestCAknGMsgQueryNewL );
    // Print to log file
    iLog->Log( KTestCAknGMsgQueryNewL );
    
    //test NewL function
    CAknGlobalListMsgQuery* globalMsgQuery = CAknGlobalListMsgQuery::NewL();
    CleanupStack::PushL( globalMsgQuery );
    
    STIF_ASSERT_NOT_NULL( globalMsgQuery );   
    CleanupStack::PopAndDestroy( globalMsgQuery );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestCAknGMsgQueryLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestCAknGMsgQueryNewLC( CStifItemParser& /*aItem*/ )
    {
    
    // Print to UI
    _LIT( KTestSDKNotifiers, "TestSDKNotifiers" );
    _LIT( KTestCAknGMsgQueryNewLC, "In TestCAknGMsgQueryNewLC" );
    TestModuleIf().Printf( 0, KTestSDKNotifiers, KTestCAknGMsgQueryNewLC );
    // Print to log file
    iLog->Log( KTestCAknGMsgQueryNewLC );
    
    //test NewLC function
    CAknGlobalListMsgQuery* globalMsgQuery = CAknGlobalListMsgQuery::NewLC();
    STIF_ASSERT_NOT_NULL( globalMsgQuery );
    CleanupStack::PopAndDestroy( globalMsgQuery );
    
    return KErrNone;
}

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestCAknGMsgQueryShowListMsgQueryL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestCAknGMsgQueryShowListMsgQueryL( CStifItemParser& /*aItem*/ )

    {
    
    // Print to UI
    _LIT( KTestSDKNotifiers, "TestSDKNotifiers" );
    _LIT( KTestCAknGMsgQueryShowListMsgQueryL, 
                                   "In TestCAknGMsgQueryShowListMsgQueryL" );
    TestModuleIf().Printf( 0, KTestSDKNotifiers, 
                                    KTestCAknGMsgQueryShowListMsgQueryL );
    // Print to log file
    iLog->Log( KTestCAknGMsgQueryShowListMsgQueryL );  
    
    CActiveExample* activeObject = CActiveExample::NewL();
    CleanupStack::PushL( activeObject );
    
    activeObject->ShowTheListMsgQueryL();
    
    CleanupStack::PopAndDestroy( activeObject );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestCAknGMsgQueryMoveSelectionUpL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestCAknGMsgQueryMoveSelectionUpL( CStifItemParser& /*aItem*/   )

    {
    
    // Print to UI
    _LIT( KTestSDKNotifiers, "TestSDKNotifiers" );
    _LIT( KTestCAknGMsgQueryMoveSelectionUpL, 
                                   "In TestCAknGMsgQueryMoveSelectionUpL" );
    TestModuleIf().Printf( 0, KTestSDKNotifiers, 
                                       KTestCAknGMsgQueryMoveSelectionUpL );
    // Print to log file
    iLog->Log( KTestCAknGMsgQueryMoveSelectionUpL );  
    
    CAknGlobalListMsgQuery* globalMsgQuery = CAknGlobalListMsgQuery::NewL();
    CleanupStack::PushL( globalMsgQuery );
      
    //test MoveSelectionUp function
    globalMsgQuery->MoveSelectionUp();
    
    CleanupStack::PopAndDestroy( globalMsgQuery );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestCAknGMsgQueryMoveSelectionDownL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestCAknGMsgQueryMoveSelectionDownL( 
    CStifItemParser& /*aItem*/)
    {
    
    // Print to UI
    _LIT( KTestSDKNotifiers, "TestSDKNotifiers" );
    _LIT( KTestCAknGMsgQueryMoveSelectionDownL, 
                                  "In TestCAknGMsgQueryMoveSelectionDownL" );
    TestModuleIf().Printf( 0, KTestSDKNotifiers,
                                      KTestCAknGMsgQueryMoveSelectionDownL );
    // Print to log file
    iLog->Log( KTestCAknGMsgQueryMoveSelectionDownL ); 
    
    CAknGlobalListMsgQuery* globalMsgQuery = CAknGlobalListMsgQuery::NewL();
    CleanupStack::PushL( globalMsgQuery );
      
    //test MoveSelectionDown function
    globalMsgQuery->MoveSelectionDown();
    
    CleanupStack::PopAndDestroy( globalMsgQuery );    
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestCAknGMsgQuerySelectItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestCAknGMsgQuerySelectItemL( CStifItemParser& /*aItem*/)
    {
    
    // Print to UI
    _LIT( KTestSDKNotifiers, "TestSDKNotifiers" );
    _LIT( KTestCAknGMsgQuerySelectItemL, "In TestCAknGMsgQuerySelectItemL" );
    TestModuleIf().Printf( 0, KTestSDKNotifiers, KTestCAknGMsgQuerySelectItemL );
    // Print to log file
    iLog->Log( KTestCAknGMsgQuerySelectItemL );  
    
    CAknGlobalListMsgQuery* globalMsgQuery = CAknGlobalListMsgQuery::NewL();
    CleanupStack::PushL( globalMsgQuery );
      
    //test SelectItem function
    globalMsgQuery->SelectItem();
    
    CleanupStack::PopAndDestroy( globalMsgQuery );  
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestCAknGMsgQueryCancelListMsgQueryL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestCAknGMsgQueryCancelListMsgQueryL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KTestSDKNotifiers, "TestSDKNotifiers" );
    _LIT( KTestCAknGMsgQueryCancelListMsgQueryL, 
                                  "In TestCAknGMsgQueryCancelListMsgQueryL" );
    TestModuleIf().Printf( 0, KTestSDKNotifiers, 
                                      KTestCAknGMsgQueryCancelListMsgQueryL );
    // Print to log file
    iLog->Log( KTestCAknGMsgQueryCancelListMsgQueryL );     
    
    CAknGlobalListMsgQuery* globalMsgQuery = CAknGlobalListMsgQuery::NewL();
    CleanupStack::PushL( globalMsgQuery );
      
    //test SelectItem function
    globalMsgQuery->CancelListMsgQuery();
    
    CleanupStack::PopAndDestroy( globalMsgQuery );  
    
    return KErrNone;   
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestCAknGMsgQuerySetSecondaryDisplayDataL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestCAknGMsgQuerySetSecondaryDisplayDataL( 
    CStifItemParser& /*aItem*/ )
    {
    
    // Print to UI
    _LIT( KTestSDKNotifiers, "TestSDKNotifiers" );
    _LIT( KTestCAknGMsgQuerySetSecondaryDisplayDataL, 
                             "In TestCAknGMsgQuerySetSecondaryDisplayDataL" );
    TestModuleIf().Printf( 0, KTestSDKNotifiers, 
                                 KTestCAknGMsgQuerySetSecondaryDisplayDataL );
    // Print to log file
    iLog->Log( KTestCAknGMsgQuerySetSecondaryDisplayDataL );     
    
    CAknGlobalListMsgQuery* globalMsgQuery = CAknGlobalListMsgQuery::NewL();
    CleanupStack::PushL( globalMsgQuery );
    CAknSDData* setData = new ( ELeave ) CAknSDData();
      
    //test SelectItem function
    globalMsgQuery->SetSecondaryDisplayData( setData );
     
    CleanupStack::PopAndDestroy( globalMsgQuery );  
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestCAknGMsgQuerySetImageSkinIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestCAknGMsgQuerySetImageSkinIdL( CStifItemParser& /*aItem*/)
    {
    
    // Print to UI
    _LIT( KTestSDKNotifiers, "TestSDKNotifiers" );
    _LIT( KTestCAknGMsgQuerySetImageSkinIdL, 
                                      "In TestCAknGMsgQuerySetImageSkinIdL" );
    TestModuleIf().Printf( 0, KTestSDKNotifiers, 
                                          KTestCAknGMsgQuerySetImageSkinIdL );
    // Print to log file
    iLog->Log( KTestCAknGMsgQuerySetImageSkinIdL );       
    
    CAknGlobalListMsgQuery* globalMsgQuery = CAknGlobalListMsgQuery::NewL();
    CleanupStack::PushL( globalMsgQuery );
      
    TAknsItemID itemId;
    
    //test SelectItem function
    globalMsgQuery->SetImageSkinId( itemId );
     
    CleanupStack::PopAndDestroy( globalMsgQuery );     
    
    return KErrNone;
    }

//End file
