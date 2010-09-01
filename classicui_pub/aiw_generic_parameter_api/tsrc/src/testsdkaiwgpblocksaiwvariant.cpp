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
* Description:    Test functions for TAiwVariant
*
*/




// INCLUDE FILES
#include <s32file.h>    // rfilewritestream, rfilereadstream
#include <barsread.h>   // tresourcereader

#include "testsdkaiwgp.h"

// CONSTANTS
const TInt KBufferSize = 50;
const TInt32 KTint32 = 100000;
_LIT(KHBufCContent, "hbufcconstructor");
_LIT8(KBufC8Content, "bufc8Constructor");
_LIT8(KBufC8ContentInput, "bufc8Constructorinput");
_LIT(KTDesCContent, "TDesCContructor");
_LIT(KTDesCContentInput, "TDesCContructorinput");


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestTAiwVariantL
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwgp::TestTAiwVariantL( CStifItemParser& /*aItem */)
    {
    STIF_ASSERT_EQUALS( KErrNone, TestAiwVFuncByDefaultConstructor() );
    STIF_ASSERT_EQUALS( KErrNone, TestAiwVFuncByTInt32Constructor() );
    STIF_ASSERT_EQUALS( KErrNone, TestAiwVFuncByTUidConstructor() );
    STIF_ASSERT_EQUALS( KErrNone, TestAiwVFuncByTTimeConstructor() );
    STIF_ASSERT_EQUALS( KErrNone, TestAiwVFuncByTDesCConstructor() );
    STIF_ASSERT_EQUALS( KErrNone, TestAiwVFuncByHBufCConstructorL() );
    STIF_ASSERT_EQUALS( KErrNone, TestAiwVFuncByTDesC8Constructor() );
    STIF_ASSERT_EQUALS( KErrNone, TestAiwVFuncByRFileConstructorL() );
    STIF_ASSERT_EQUALS( KErrNone, TestAiwVFuncByCopyConstructor() );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestAiwVFuncByDefaultConstructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestAiwVFuncByDefaultConstructor()
    {
    //default constrcutor
        TAiwVariant defaultConstructor;
        STIF_ASSERT_NOT_NULL( &defaultConstructor );
        STIF_ASSERT_EQUALS( EVariantTypeNull, defaultConstructor.TypeId() );
        STIF_ASSERT_TRUE( defaultConstructor.IsEmpty() );
        
        return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestAiwVFuncByTInt32Constructor
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwgp::TestAiwVFuncByTInt32Constructor()
    {
    //constructor use TInt32 as input
    TInt32 tint32 = KTint32;
    TInt32 tint32input = KTint32 * 2;
    TAiwVariant tint32Constructor( tint32 );
    STIF_ASSERT_NOT_NULL( &tint32Constructor );
    STIF_ASSERT_EQUALS( EVariantTypeTInt32, tint32Constructor.TypeId() );
    TAiwVariant tint32Constructorempty;
    tint32Constructorempty = tint32Constructor;
    STIF_ASSERT_TRUE( tint32Constructorempty == tint32Constructor );
    STIF_ASSERT_EQUALS( tint32Constructorempty.AsTInt32(), tint32Constructor.AsTInt32() );
    tint32Constructorempty = tint32input;
    STIF_ASSERT_TRUE( tint32Constructorempty != tint32Constructor );
    STIF_ASSERT_EQUALS( tint32input, tint32Constructorempty.AsTInt32() );
    STIF_ASSERT_EQUALS( tint32, tint32Constructor.AsTInt32() );
    STIF_ASSERT_FALSE( tint32Constructor.IsEmpty() );
    STIF_ASSERT_TRUE( tint32Constructor.Get( tint32input ) );
    STIF_ASSERT_EQUALS( tint32, tint32input );
    tint32Constructor.Reset();
    STIF_ASSERT_TRUE( tint32Constructor.IsEmpty() );
    tint32Constructor.Set( tint32 );
    STIF_ASSERT_FALSE( tint32Constructor.IsEmpty() );
    TAiwVariant copyConstructor;
    copyConstructor = tint32Constructor;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestAiwVFuncByTUidConstructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestAiwVFuncByTUidConstructor()
    {
    //constructor use TUid as input
    TUid tuid = { 0x00000001 };
    TUid tuidinput = { 0x00000002 };
    TAiwVariant tuidConstructor( tuid );
    STIF_ASSERT_NOT_NULL( &tuidConstructor );
    STIF_ASSERT_EQUALS( EVariantTypeTUid, tuidConstructor.TypeId() );
    TAiwVariant tuidConstructorempty;
    tuidConstructorempty = tuidConstructor;
    STIF_ASSERT_TRUE( tuidConstructorempty == tuidConstructor );
    STIF_ASSERT_EQUALS( tuidConstructorempty.AsTUid(), tuidConstructor.AsTUid() );
    tuidConstructorempty = tuidinput;
    STIF_ASSERT_TRUE( tuidConstructorempty != tuidConstructor );
    STIF_ASSERT_EQUALS( tuidinput, tuidConstructorempty.AsTUid() );
    STIF_ASSERT_EQUALS( tuid, tuidConstructor.AsTUid() );
    STIF_ASSERT_FALSE( tuidConstructor.IsEmpty() );
    STIF_ASSERT_TRUE( tuidConstructor.Get( tuidinput ) );
    STIF_ASSERT_EQUALS( tuid, tuidinput );
    tuidConstructor.Reset();
    STIF_ASSERT_TRUE( tuidConstructor.IsEmpty() );
    tuidConstructor.Set( tuid );
    STIF_ASSERT_FALSE( tuidConstructor.IsEmpty() );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestAiwVFuncByTTimeConstructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestAiwVFuncByTTimeConstructor()
    {
    //constructor use TTime as input
    TTime ttime;
    ttime.HomeTime();
    TAiwVariant ttimeConstructor( ttime );
    STIF_ASSERT_NOT_NULL( &ttimeConstructor );
    STIF_ASSERT_EQUALS( EVariantTypeTTime, ttimeConstructor.TypeId() );
    TAiwVariant ttimeConstructorempty;
    ttimeConstructorempty = ttimeConstructor;
    STIF_ASSERT_EQUALS( ttimeConstructorempty.AsTTime(), ttimeConstructor.AsTTime() );
    STIF_ASSERT_TRUE( ttimeConstructorempty == ttimeConstructor );
    STIF_ASSERT_EQUALS( ttime, ttimeConstructor.AsTTime() );
    STIF_ASSERT_FALSE( ttimeConstructor.IsEmpty() );
    TTime ttimeinput;
    ttimeinput.HomeTime();
    ttimeConstructorempty = ttimeinput;
    STIF_ASSERT_EQUALS( ttimeinput, ttimeConstructorempty.AsTTime() );
    STIF_ASSERT_TRUE( ttimeConstructor.Get( ttimeinput ) );
    STIF_ASSERT_EQUALS( ttime, ttimeinput );
    ttimeConstructor.Reset();
    STIF_ASSERT_TRUE( ttimeConstructor.IsEmpty() );
    ttimeConstructor.Set( ttime );
    STIF_ASSERT_FALSE( ttimeConstructor.IsEmpty() );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestAiwVFuncByTDesCConstructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestAiwVFuncByTDesCConstructor()
    {
    //constructor use TDesC as input
    TBufC<64> tdesc( KTDesCContent );
    TBufC<64> tdescinput( KTDesCContentInput );
    TPtrC tptrc = tdescinput;
    TAiwVariant tdescConstructor(tdesc);
    STIF_ASSERT_NOT_NULL( &tdescConstructor );
    STIF_ASSERT_EQUALS( EVariantTypeDesC, tdescConstructor.TypeId() );
    TAiwVariant tdescConstructorempty;
    tdescConstructorempty = tdescConstructor;
    STIF_ASSERT_TRUE( tdescConstructorempty == tdescConstructor );
    TInt result = tdescConstructor.AsDes().Compare( tdescConstructorempty.AsDes() );
    STIF_ASSERT_FALSE( result );
    tdescConstructorempty = tdescinput;
    STIF_ASSERT_TRUE( tdescConstructorempty != tdescConstructor );
    result = tdescConstructorempty.AsDes().Compare( tdescinput );
    STIF_ASSERT_FALSE( result );
    result = tdescConstructor.AsDes().Compare( tdesc );
    STIF_ASSERT_FALSE( result );
    STIF_ASSERT_FALSE( tdescConstructor.IsEmpty() );
    STIF_ASSERT_TRUE( tdescConstructor.Get( tptrc ) );
    result = tptrc.Compare(tdesc);
    STIF_ASSERT_FALSE( result );
    tdescConstructor.Reset();
    STIF_ASSERT_TRUE( tdescConstructor.IsEmpty() );
    tdescConstructor.Set( tdesc );
    STIF_ASSERT_NOT_NULL( &tdescConstructor );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestAiwVFuncByHBufCConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestAiwVFuncByHBufCConstructorL()
    {
    //constructor use HBufC as input
    HBufC* hbufc = HBufC::NewL(KBufferSize);
    CleanupStack::PushL( hbufc );
    *hbufc = KHBufCContent;
    TPtrC tptrc;
    TAiwVariant hbufcConstructor(hbufc);
    STIF_ASSERT_NOT_NULL( &hbufcConstructor );
    STIF_ASSERT_EQUALS( EVariantTypeDesC, hbufcConstructor.TypeId() );
    TAiwVariant hbufcConstructorempty;
    hbufcConstructorempty = hbufcConstructor;
    STIF_ASSERT_TRUE( hbufcConstructorempty == hbufcConstructor );
    TInt result = hbufcConstructor.AsDes().Compare( hbufcConstructorempty.AsDes() );
    STIF_ASSERT_FALSE( result );
    hbufcConstructorempty = hbufc;
    STIF_ASSERT_FALSE( hbufcConstructorempty != hbufcConstructor );
    result = hbufcConstructorempty.AsDes().Compare( *hbufc );
    STIF_ASSERT_FALSE( result );
    result = hbufcConstructor.AsDes().Compare( *hbufc );
    STIF_ASSERT_FALSE( result );
    STIF_ASSERT_FALSE( hbufcConstructor.IsEmpty() );
    STIF_ASSERT_TRUE( hbufcConstructor.Get( tptrc ) );
    result = tptrc.Compare( *hbufc);
    STIF_ASSERT_FALSE( result );
    hbufcConstructor.Reset();
    STIF_ASSERT_TRUE( hbufcConstructor.IsEmpty() );
    hbufcConstructor.Set( hbufc );
    STIF_ASSERT_NOT_NULL( &hbufcConstructor );
    
    CleanupStack::PopAndDestroy( hbufc );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestAiwVFuncByTDesC8Constructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestAiwVFuncByTDesC8Constructor()
    {
    //constructor use TDes8 as input
    TBufC8<64> tbufc8( KBufC8Content );
    TBufC8<64> tbufc8input( KBufC8ContentInput );
    TPtrC8 tptrc8 = tbufc8input;
    TAiwVariant tbufc8Constructor(tbufc8);
    STIF_ASSERT_NOT_NULL( &tbufc8Constructor );
    STIF_ASSERT_EQUALS( EVariantTypeDesC8, tbufc8Constructor.TypeId() );
    TAiwVariant tbufc8Constructorempty;
    tbufc8Constructorempty = tbufc8Constructor;
    STIF_ASSERT_TRUE( tbufc8Constructorempty == tbufc8Constructor );
    TInt result = tbufc8Constructor.AsData().Compare( tbufc8Constructorempty.AsData() );
    STIF_ASSERT_FALSE( result );
    tbufc8Constructorempty = tbufc8input;
    STIF_ASSERT_TRUE( tbufc8Constructorempty != tbufc8Constructor );
    result = tbufc8Constructorempty.AsData().Compare( tbufc8input );
    result = tbufc8Constructor.AsData().Compare( tbufc8 );
    STIF_ASSERT_FALSE( result );
    STIF_ASSERT_FALSE( tbufc8Constructor.IsEmpty() );
    STIF_ASSERT_TRUE( tbufc8Constructor.Get( tptrc8 ) );
    result = tptrc8.Compare(tbufc8);
    STIF_ASSERT_FALSE( result );
    tbufc8Constructor.Reset();
    STIF_ASSERT_TRUE( tbufc8Constructor.IsEmpty() );
    tbufc8Constructor.Set( tbufc8 );
    STIF_ASSERT_NOT_NULL( &tbufc8Constructor );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestAiwVFuncByRFileConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestAiwVFuncByRFileConstructorL()
    {
    //constructor use RFile as input
    RFile rfile;
    CleanupClosePushL( rfile );
    RFile rfileinput;
    CleanupClosePushL( rfileinput );
    TAiwVariant rfileConstructor(rfile);
    STIF_ASSERT_NOT_NULL( &rfileConstructor );
    STIF_ASSERT_EQUALS( EVariantTypeFileHandle, rfileConstructor.TypeId() );
    TAiwVariant rfileConstructorempty;
    rfileConstructorempty = rfileConstructor;
    STIF_ASSERT_TRUE( rfileConstructorempty == rfileConstructor );
    STIF_ASSERT_EQUALS( rfileConstructorempty.AsFileHandle(), rfileConstructor.AsFileHandle() );
    rfileConstructorempty = rfileinput;
    STIF_ASSERT_EQUALS( rfileinput, rfileConstructorempty.AsFileHandle() );
    STIF_ASSERT_EQUALS( rfile, rfileConstructor.AsFileHandle() );
    STIF_ASSERT_FALSE( rfileConstructor.IsEmpty() );
    STIF_ASSERT_TRUE( rfileConstructor.Get( rfileinput ) );
    STIF_ASSERT_EQUALS( rfile, rfileinput );
    rfileConstructor.Reset();
    STIF_ASSERT_TRUE( rfileConstructor.IsEmpty() );
    rfileConstructor.Set(rfile);
    STIF_ASSERT_FALSE( rfileConstructor.IsEmpty() );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestAiwVFuncByCopyConstructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestAiwVFuncByCopyConstructor()
    {
    //copy constructor
    TBufC8<64> tbufc8( KBufC8Content );
    TBufC8<64> tbufc8input( KBufC8ContentInput );
    TPtrC8 tptrc8 = tbufc8input;
    TAiwVariant tbufc8Constructor(tbufc8);
    TAiwVariant copyConstructor(tbufc8Constructor);
    STIF_ASSERT_NOT_NULL( &copyConstructor );
    STIF_ASSERT_EQUALS( EVariantTypeDesC8, copyConstructor.TypeId() );
    TInt result = tbufc8Constructor.AsData().Compare(tbufc8);
    STIF_ASSERT_FALSE( result );
    STIF_ASSERT_FALSE( copyConstructor.IsEmpty() );
    STIF_ASSERT_TRUE( copyConstructor.Get( tptrc8 ) );
    result = tptrc8.Compare(tbufc8);
    STIF_ASSERT_FALSE( result );
    copyConstructor.Reset();
    STIF_ASSERT_TRUE( copyConstructor.IsEmpty() );
    return KErrNone;
    }
