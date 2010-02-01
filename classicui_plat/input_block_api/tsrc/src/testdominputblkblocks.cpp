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
* Description:  Test AknInputBlock.h
*
*/



/*
 *  [INCLUDE FILES]
 */
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <akninputblock.h>
#include <e32base.h>

#include "testdominputblk.h"
#include "blockcancelhandler.h"
#include "activeexample.h"

const TInt KTwo = 2;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMINPUTBLK::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//

void CTestDOMINPUTBLK::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestDOMINPUTBLK::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMINPUTBLK::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestIPBLKNewLCL", CTestDOMINPUTBLK::TestIPBLKNewLCL ),
        ENTRY( "TestIPBLKNewCancelHandlerLCL", CTestDOMINPUTBLK::TestIPBLKNewCancelHandlerLCL ),
        ENTRY( "TestIPBLKNewCancelActiveLCL", CTestDOMINPUTBLK::TestIPBLKNewCancelActiveLCL ),
        ENTRY( "TestIPBLKNewCancelDeleteLCL", CTestDOMINPUTBLK::TestIPBLKNewCancelDeleteLCL ),
        ENTRY( "TestIPBLKDestructorL", CTestDOMINPUTBLK::TestIPBLKDestructorL ),
        ENTRY( "TestIPBLKSetCancelHandlerL", CTestDOMINPUTBLK::TestIPBLKSetCancelHandlerL ),
        ENTRY( "TestIPBLKSetCancelActiveL", CTestDOMINPUTBLK::TestIPBLKSetCancelActiveL ),
        ENTRY( "TestIPBLKSetCancelDeleteL", CTestDOMINPUTBLK::TestIPBLKSetCancelDeleteL ),
        ENTRY( "TestIPBLKCancelL", CTestDOMINPUTBLK::TestIPBLKCancelL ),

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMINPUTBLK::TestIPBLKNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestDOMINPUTBLK::TestIPBLKNewLCL( CStifItemParser& /*aItem*/ )
    {
    CAknInputBlock* inputblock( NULL );
    inputblock = CAknInputBlock::NewLC();
    STIF_ASSERT_NOT_NULL( inputblock );
    CleanupStack::PopAndDestroy( inputblock );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMINPUTBLK::TestIPBLKNewCancelHandlerLCL
// -----------------------------------------------------------------------------
//
TInt CTestDOMINPUTBLK::TestIPBLKNewCancelHandlerLCL( CStifItemParser& /*aItem*/ )
    {
    CBlockCancelHandler* blockcancelhandler = new( ELeave ) CBlockCancelHandler;
    CleanupStack::PushL( blockcancelhandler );
    
    CAknInputBlock* inputblock( NULL );
    inputblock = CAknInputBlock::NewCancelHandlerLC( blockcancelhandler );
    STIF_ASSERT_NOT_NULL( inputblock );
    
    CleanupStack::PopAndDestroy( KTwo );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMINPUTBLK::TestIPBLKNewCancelActiveLCL
// -----------------------------------------------------------------------------
//
TInt CTestDOMINPUTBLK::TestIPBLKNewCancelActiveLCL( CStifItemParser& /*aItem*/ )
    {
    CActiveExample* active = new( ELeave ) CActiveExample;
    CleanupStack::PushL( active );
    
    CAknInputBlock* inputblock( NULL );
    inputblock = inputblock->NewCancelActiveLC( active );
    STIF_ASSERT_NOT_NULL( inputblock );
    
    CleanupStack::PopAndDestroy( KTwo );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMINPUTBLK::TestIPBLKNewCancelDeleteLCL
// -----------------------------------------------------------------------------
//
TInt CTestDOMINPUTBLK::TestIPBLKNewCancelDeleteLCL( CStifItemParser& /*aItem*/ )
    {
    CBase* base = new( ELeave ) CBase;
    
    CAknInputBlock* inputblock( NULL );
    inputblock = inputblock->NewCancelDeleteLC( base );
    STIF_ASSERT_NOT_NULL( inputblock );
    
    CleanupStack::PopAndDestroy( inputblock );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMINPUTBLK::TestIPBLKDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestDOMINPUTBLK::TestIPBLKDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknInputBlock* inputblock( NULL );
    inputblock = CAknInputBlock::NewLC();
    STIF_ASSERT_NOT_NULL( inputblock );
    
    CleanupStack::Pop( inputblock );
    delete inputblock;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMINPUTBLK::TestIPBLKSetCancelHandlerL
// -----------------------------------------------------------------------------
//
TInt CTestDOMINPUTBLK::TestIPBLKSetCancelHandlerL( CStifItemParser& /*aItem*/ )
    {
    CBlockCancelHandler* blockcancelhandler = new( ELeave ) CBlockCancelHandler;
    CleanupStack::PushL( blockcancelhandler );
    
    CAknInputBlock* inputblock( NULL );
    inputblock = inputblock->NewLC();
    inputblock->SetCancelHandler( blockcancelhandler );
    
    inputblock->Cancel();
    TBool flag = blockcancelhandler->Getflag();
    STIF_ASSERT_TRUE( flag );
    
    CleanupStack::PopAndDestroy( KTwo );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMINPUTBLK::TestIPBLKSetCancelActiveL
// -----------------------------------------------------------------------------
//
TInt CTestDOMINPUTBLK::TestIPBLKSetCancelActiveL( CStifItemParser& /*aItem*/ )
    {
    CActiveExample* active = CActiveExample::NewLC();
    
    CAknInputBlock* inputblock( NULL );
    inputblock = inputblock->NewLC();
    
    active->Start( 0 );
    inputblock->SetCancelActive( active );
    
    inputblock->Cancel();
    TBool flag = active->Getflag();
    STIF_ASSERT_TRUE( flag );
    
    CleanupStack::PopAndDestroy( KTwo );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMINPUTBLK::TestIPBLKSetCancelDeleteL
// -----------------------------------------------------------------------------
//
TInt CTestDOMINPUTBLK::TestIPBLKSetCancelDeleteL( CStifItemParser& /*aItem*/ )
    {
    CBase* base = new( ELeave ) CBase;
    
    CAknInputBlock* inputblock( NULL );
    inputblock = CAknInputBlock::NewLC();
    
    inputblock->SetCancelDelete( base );
    inputblock->Cancel();
    CleanupStack::PopAndDestroy( inputblock );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMINPUTBLK::TestIPBLKCancelL
// -----------------------------------------------------------------------------
//
TInt CTestDOMINPUTBLK::TestIPBLKCancelL( CStifItemParser& aItem )
    {
    TInt err( KErrNone );
    err = TestIPBLKSetCancelHandlerL( aItem );
    STIF_ASSERT_EQUALS( err, KErrNone );
    
    err = TestIPBLKSetCancelActiveL( aItem );
    STIF_ASSERT_EQUALS( err, KErrNone );
    
    err = TestIPBLKSetCancelDeleteL( aItem );
    STIF_ASSERT_EQUALS( err, KErrNone );
    
    return err;
    }


/*
 *   [End of File]
 */
