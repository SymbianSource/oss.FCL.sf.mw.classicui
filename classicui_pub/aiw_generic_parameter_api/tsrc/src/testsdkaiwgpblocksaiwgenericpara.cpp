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
* Description:    Test functions for TAiwGenericParam and TAiwGenericParamList
*
*/




// INCLUDE FILES
#include <testscripterinternal.h>
#include <s32strm.h> 
#include <s32mem.h>
#include <f32file.h>
#include <s32file.h>
#include <e32cmn.h>

#include "testsdkaiwgp.h"

// CONSTANTS
_LIT( KFullFileName, "\\tet.txt" );
const TInt KArraySize = 10;
const TInt KDataListSize = 75;
const TInt32 KTint32 = 10000000;

// -----------------------------------------------------------------------------
// simple test class for RSessionBase
// -----------------------------------------------------------------------------
//
class RTestSession : public RSessionBase
    {
public:
    // Create session
    TInt Create( RServer2 aServer, TRequestStatus& aStatus )
        {
        return CreateSession( aServer,
                              TVersion(),
                              2,
                              EIpcSession_Sharable,
                              NULL,
                              &aStatus);
        }
    // Send msg
    inline void Send( const TIpcArgs& aArgs, TRequestStatus& aStatus )
        {
        RSessionBase::SendReceive( 0x8000, aArgs, aStatus );
        }
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestTAiwGP
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwgp::TestTAiwGP(CStifItemParser& aItem)
    {
    STIF_ASSERT_EQUALS( KErrNone, TestAiwGPFuncByDefaultConstructor( aItem ) );
    
    STIF_ASSERT_EQUALS( KErrNone, TestAiwGPFuncByConstructorOnePara( aItem ) );
    
    STIF_ASSERT_EQUALS( KErrNone, TestAiwGPFuncByConstructorTwoPara( aItem ) );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestAiwGPFuncByDefaultConstructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestAiwGPFuncByDefaultConstructor( CStifItemParser& aItem )
    {
    TAiwGenericParam defaultConstructor;
    STIF_ASSERT_NOT_NULL( &defaultConstructor );
    
    TAiwGenericParam defaultConstructorequal;
    STIF_ASSERT_TRUE( defaultConstructorequal == defaultConstructor );
    STIF_ASSERT_FALSE( defaultConstructorequal != defaultConstructor );
    
    STIF_ASSERT_TRUE( defaultConstructor.SemanticId() == EGenericParamUnspecified );
    
    TInt id = 0;
    TInt err = aItem.GetNextInt(id);
    if (err != KErrNone)
        {
        return err;
        }
    defaultConstructor.SetSemanticId( id );
    STIF_ASSERT_TRUE( defaultConstructor.SemanticId() == id );
    
    TAiwVariant defaultaiwvariant = defaultConstructor.Value();
    STIF_ASSERT_TRUE( defaultaiwvariant.IsEmpty() );
    const TAiwVariant defaultconstaiwvariant = defaultConstructor.Value();
    STIF_ASSERT_TRUE( defaultconstaiwvariant.IsEmpty() );
    
    defaultConstructor.Reset();
    STIF_ASSERT_TRUE( defaultConstructor.SemanticId() == EGenericParamUnspecified );
    defaultaiwvariant = defaultConstructor.Value();
    STIF_ASSERT_TRUE( defaultaiwvariant.IsEmpty() );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestAiwGPFuncByConstructorOnePara
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestAiwGPFuncByConstructorOnePara( CStifItemParser& aItem )
    {
    TAiwGenericParam oneparaConstructor(EGenericParamLandmark);
    STIF_ASSERT_NOT_NULL( &oneparaConstructor );
    STIF_ASSERT_TRUE( oneparaConstructor.SemanticId() == EGenericParamLandmark );
    
    TAiwGenericParam oneparaConstructorequal(EGenericParamLandmark);
    STIF_ASSERT_TRUE( oneparaConstructorequal == oneparaConstructor );
    STIF_ASSERT_FALSE( oneparaConstructorequal != oneparaConstructor );
    
    TInt id = 0;
    TInt err = aItem.GetNextInt(id);
    if (err != KErrNone)
        {
        return err;
        }
    oneparaConstructor.SetSemanticId(id);
    STIF_ASSERT_TRUE( oneparaConstructor.SemanticId() == id );
    
    TAiwVariant oneparaaiwvariant = oneparaConstructor.Value();
    STIF_ASSERT_TRUE( oneparaaiwvariant.IsEmpty() );
    TAiwVariant oneparaconstaiwvariant = oneparaConstructor.Value();
    STIF_ASSERT_TRUE( oneparaconstaiwvariant.IsEmpty() );
    
    oneparaConstructor.Reset();
    STIF_ASSERT_TRUE( oneparaConstructor.SemanticId() == EGenericParamUnspecified );
    oneparaaiwvariant = oneparaConstructor.Value();
    STIF_ASSERT_TRUE( oneparaaiwvariant.IsEmpty() );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestAiwGPFuncByConstructorTwoPara
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestAiwGPFuncByConstructorTwoPara( CStifItemParser& aItem )
    {
    TAiwVariant aiwvariable(KTint32);
    TAiwGenericParam twoparaConstructor(EGenericParamReferringURI, aiwvariable);
    STIF_ASSERT_NOT_NULL( &twoparaConstructor );
    STIF_ASSERT_TRUE( twoparaConstructor.SemanticId() == EGenericParamReferringURI );
    
    TAiwGenericParam twoparaConstructorequal(EGenericParamReferringURI, aiwvariable);
    STIF_ASSERT_TRUE( twoparaConstructorequal == twoparaConstructor );
    STIF_ASSERT_FALSE( twoparaConstructorequal != twoparaConstructor );
    
    TInt id = 0;
    TInt err = aItem.GetNextInt(id);
    if (err != KErrNone)
        {
        return err;
        }
    twoparaConstructor.SetSemanticId(id);
    STIF_ASSERT_TRUE( twoparaConstructor.SemanticId() == id );
    
    TAiwVariant twoparaaiwvariant = twoparaConstructor.Value();
    STIF_ASSERT_FALSE( twoparaaiwvariant.IsEmpty() );
    STIF_ASSERT_TRUE( twoparaaiwvariant.AsTInt32() == KTint32 );
    TAiwVariant twoparaconstaiwvariant = twoparaConstructor.Value();
    STIF_ASSERT_FALSE( twoparaconstaiwvariant.IsEmpty() );
    STIF_ASSERT_TRUE( twoparaconstaiwvariant.AsTInt32() == KTint32 );
    
    twoparaConstructor.Reset();
    STIF_ASSERT_TRUE( twoparaConstructor.SemanticId() == EGenericParamUnspecified );
    twoparaaiwvariant = twoparaConstructor.Value();
    STIF_ASSERT_TRUE( twoparaaiwvariant.IsEmpty() );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestTAiwGPListNewFunctionsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestTAiwGPListNewFunctionsL( CStifItemParser& /*aItem*/ )
    {
    RFs rfs;
    CleanupClosePushL( rfs );
    User::LeaveIfError( rfs.Connect() );
    RFileWriteStream filewritestream;
    CleanupClosePushL( filewritestream );
    TInt32 tint32 = KTint32;
    filewritestream.Replace( rfs, KFullFileName, EFileWrite );
    CAiwGenericParamList* list = CAiwGenericParamList::NewL();
    CleanupStack::PushL( list );
    for ( TInt i = 0; i < KArraySize; i++ )
        {
        TAiwVariant aiwvariable( tint32 );
        TAiwGenericParam para( i, aiwvariable );
        tint32++;
        list->AppendL( para );
        }
    list->ExternalizeL( filewritestream );
    CleanupStack::PopAndDestroy( list );
    filewritestream.CommitL();
    filewritestream.Release();
    filewritestream.Close();
    CleanupStack::PopAndDestroy( &filewritestream );

    RFileReadStream filereadstream;
    CleanupClosePushL( filereadstream );
    filereadstream.Open( rfs, KFullFileName, EFileRead );
    
    CAiwGenericParamList* newllist = CAiwGenericParamList::NewL();
    CleanupStack::PushL( newllist );
    STIF_ASSERT_NOT_NULL( newllist );
    CleanupStack::Pop( newllist );
    delete newllist;
    
    CAiwGenericParamList* newlclist = CAiwGenericParamList::NewLC();
    STIF_ASSERT_NOT_NULL( newlclist );
    CleanupStack::PopAndDestroy( newlclist );
    
    CAiwGenericParamList* newlparalist = CAiwGenericParamList::NewL( filereadstream );
    CleanupStack::PushL( newlparalist );
    STIF_ASSERT_NOT_NULL( newlparalist );
    CleanupStack::Pop( newlparalist );
    delete newlparalist;
    filereadstream.Release();
    filereadstream.Close();
    
    filereadstream.Open(rfs, KFullFileName, EFileRead);
    CAiwGenericParamList* newlcparalist = CAiwGenericParamList::NewLC( filereadstream );
    STIF_ASSERT_NOT_NULL( newlcparalist );
    CleanupStack::PopAndDestroy( newlcparalist );
    
    filereadstream.Release();
    filereadstream.Close();
    CleanupStack::PopAndDestroy( &filereadstream );
    
    rfs.Close();
    CleanupStack::PopAndDestroy( &rfs );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestTAiwGPListCountL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestTAiwGPListCountL( CStifItemParser& aItem )
    {
    TInt num;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    CAiwGenericParamList* list = CAiwGenericParamList::NewL();
    CleanupStack::PushL(list);
    STIF_ASSERT_EQUALS( 0, list->Count() );
    for( TInt i = 0; i < KArraySize; i++ )
        {
        TAiwGenericParam para(i);
        list->AppendL(para);
        }
    if( num == 1 )
        {
        STIF_ASSERT_EQUALS( KArraySize, list->Count() );
        }
    if( num == 2 )
        {
        for( TInt i = 0; i < KArraySize; i++ )
            {
            TAiwGenericParam para(i);
            list->AppendL(para);
            }
        for( TInt i = 0; i < KArraySize; i++ )
        STIF_ASSERT_EQUALS( 2, list->Count( i ) );
        }
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestTAiwGPListSquareBracketL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestTAiwGPListSquareBracketL( CStifItemParser& /*aItem*/ )
    {
    CAiwGenericParamList* list = CAiwGenericParamList::NewL();
    CleanupStack::PushL( list );
    for ( TInt i = 0; i < KArraySize; i++ )
        {
        TAiwGenericParam para( i );
        list->AppendL( para );
        }
    for ( TInt i = 0; i < list->Count(); i++ )
        {
        TAiwGenericParam backpara = (*list)[i];
        STIF_ASSERT_EQUALS( i, backpara.SemanticId() );
        }
    CleanupStack::PopAndDestroy(list);
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestTAiwGPListAppendL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestTAiwGPListAppendL( CStifItemParser& aItem )
    {
    TInt num;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    CAiwGenericParamList* list = CAiwGenericParamList::NewL();
    CleanupStack::PushL( list );
    
    for ( TInt i = 0; i < KArraySize; i++ )
        {
        TAiwGenericParam para( i );
        list->AppendL( para );
        }
    
    switch ( num )
        {
        case ECaseOne:
            {
            TAiwGenericParam newpara( KTint32 );
            list->AppendL( newpara );
            
            STIF_ASSERT_EQUALS( KArraySize + 1, list->Count() );
            STIF_ASSERT_EQUALS( newpara, (*list)[KArraySize] );
            break;
            }
        case ECaseTwo:
            {
            CAiwGenericParamList* listforappend = CAiwGenericParamList::NewL();
            CleanupStack::PushL( listforappend );
            for ( TInt i = 0; i < KArraySize; i++ )
                {
                TAiwGenericParam para( i );
                listforappend->AppendL( para );
                }
            listforappend->AppendL( *list );
            STIF_ASSERT_EQUALS( KArraySize * 2, listforappend->Count() );
            CleanupStack::PopAndDestroy( listforappend );
            break;
            }
        default:
            CleanupStack::PopAndDestroy( list );
            return KErrNotSupported;
        }
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestTAiwGPListResetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestTAiwGPListResetL( CStifItemParser& /*aItem*/ )
    {
    CAiwGenericParamList* list = CAiwGenericParamList::NewL();
    CleanupStack::PushL( list );
    
    for ( TInt i = 0; i < KArraySize; i++ )
        {
        TAiwGenericParam para( i );
        list->AppendL( para );
        }
    STIF_ASSERT_EQUALS( KArraySize, list->Count() );
    list->Reset();
    STIF_ASSERT_EQUALS( 0, list->Count() );
    
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestTAiwGPListFindL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestTAiwGPListFindL( CStifItemParser& aItem )
    {
    TInt num;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    CAiwGenericParamList* list = CAiwGenericParamList::NewL();
    CleanupStack::PushL( list );
    
    for ( TInt i = 0; i < KArraySize; i++ )
        {
        TAiwGenericParam para( i );
        list->AppendL( para );
        }
    
    const TAiwGenericParam* para = NULL;
    TInt index = 0;
    if ( num == 1 )
        {
        for( TInt i = 0; i < KArraySize; i++ )
            {
            index = i + 1;
            para = list->FindFirst( index, i );
            STIF_ASSERT_EQUALS( KErrNotFound, index );
            STIF_ASSERT_NULL( para );
            }
        for( TInt i = 0; i < KArraySize; i++ )
            {
            index = i;
            para = list->FindFirst( index, i);
            STIF_ASSERT_EQUALS( i, index );
            STIF_ASSERT_NOT_NULL( para );
            }
        }
    if ( num == 2)
        {
        for ( TInt i = 0; i < KArraySize; i++ )
            {
            TAiwGenericParam para( i );
            list->AppendL( para );
            }
        for( TInt i = 0; i < KArraySize; i++ )
            {
            index = i + 1;
            para = list->FindNext( index, i);
            STIF_ASSERT_EQUALS( i + KArraySize, index );
            STIF_ASSERT_NOT_NULL( para );
            }
        }
    
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestTAiwGPListSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestTAiwGPListSizeL( CStifItemParser& /*aItem*/ )
    {
    CAiwGenericParamList* list = CAiwGenericParamList::NewL();
    CleanupStack::PushL( list );
    
    for ( TInt i = 0; i < KArraySize; i++ )
        {
        TAiwGenericParam para( i );
        list->AppendL( para );
        }
    
    STIF_ASSERT_EQUALS( KDataListSize, list->Size() );
    
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestTAiwGPListRemoveL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestTAiwGPListRemoveL( CStifItemParser& /*aItem*/ )
    {
    CAiwGenericParamList* list = CAiwGenericParamList::NewL();
    CleanupStack::PushL( list );
    
    for ( TInt i = 0; i < KArraySize; i++ )
        {
        TAiwGenericParam para( i );
        list->AppendL( para );
        }
    
    TInt index;
    TInt id = KArraySize / 2;
    list->Remove( id );
    STIF_ASSERT_EQUALS( KArraySize - 1, list->Count() );
    const TAiwGenericParam* para = NULL;
    para = list->FindFirst( index, id );
    STIF_ASSERT_NULL( para );
    
    CleanupStack::PopAndDestroy(list);
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestTAiwGPListInternalizeLAndExternalizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestTAiwGPListInternalizeLAndExternalizeL(
        CStifItemParser& /*aItem*/)
    {
    RFs rfs;
    CleanupClosePushL( rfs );
    User::LeaveIfError(rfs.Connect());
    RFileWriteStream filewritestream;
    CleanupClosePushL( filewritestream );
    TInt32 tint32 = KTint32;
    filewritestream.Replace(rfs, KFullFileName, EFileWrite);
    CAiwGenericParamList* list = CAiwGenericParamList::NewL();
    CleanupStack::PushL(list);
    for (TInt i = 0; i < KArraySize; i++)
        {
        TAiwVariant aiwvariable(tint32);
        TAiwGenericParam para(i, aiwvariable);
        tint32++;
        list->AppendL(para);
        }
    list->ExternalizeL(filewritestream);
    CleanupStack::PopAndDestroy(list);
    filewritestream.CommitL();
    filewritestream.Release();
    filewritestream.Close();

    RFileReadStream filereadstream;
    CleanupClosePushL( filereadstream );
    tint32 = KTint32;
    filereadstream.Open(rfs, KFullFileName, EFileRead);
    CAiwGenericParamList* listcopy = CAiwGenericParamList::NewL();
    CleanupStack::PushL(listcopy);
    listcopy->InternalizeL(filereadstream);
    filereadstream.Release();
    filereadstream.Close();
    for (TInt i = 0; i < listcopy->Count(); i++)
        {
        TAiwGenericParam para = (*listcopy)[i];
        TAiwVariant variant = para.Value();
        TInt32 content = variant.AsTInt32();
        STIF_ASSERT_EQUALS(tint32, content);
        tint32++;
        }
    
    rfs.Close();
    

    CleanupStack::PopAndDestroy( 4 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestTAiwGPListPackForServerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestTAiwGPListPackForServerL( CStifItemParser& /*aItem*/ )
    {
    TInt32 tint32 = KTint32;
    CAiwGenericParamList* list = CAiwGenericParamList::NewL();
    CleanupStack::PushL(list);
    for (TInt i = 0; i < KArraySize; i++)
        {
        TAiwVariant aiwvariable(tint32);
        TAiwGenericParam para(i, aiwvariable);
        tint32++;
        list->AppendL(para);
        }
    TIpcArgs ipc;
    HBufC8* hbuf8 = list->PackForServerL(ipc);
    TInt len = hbuf8->Length();
    
    STIF_ASSERT_NOT_EQUALS(0, len);
    
    CleanupStack::PopAndDestroy(list);
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwgp::TestTAiwGPListUnpackFromClientL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwgp::TestTAiwGPListUnpackFromClientL( CStifItemParser& /*aItem*/ )
    {
    TInt32 tint32 = KTint32;
    CAiwGenericParamList* list = CAiwGenericParamList::NewL();
    CleanupStack::PushL(list);
    for (TInt i = 0; i < KArraySize; i++)
        {
        TAiwVariant aiwvariable(tint32);
        TAiwGenericParam para(i, aiwvariable);
        tint32++;
        list->AppendL(para);
        }
    TIpcArgs ipc;
    list->PackForServerL(ipc);
    // Test server handle
    RServer2 server;

    // Test message handle
    RMessage2 message;

    // Test session handle
    RTestSession session;

    TRequestStatus sessionCreation;
    TRequestStatus firstMessageReceived;
    TRequestStatus argumentsReceived;
    TRequestStatus secondMessageReceived;

    // Test server is created
    User::LeaveIfError(server.CreateGlobal(KNullDesC) );
    CleanupClosePushL(server);

    // Test session is created
    User::LeaveIfError(session.Create(server, sessionCreation) );
    CleanupClosePushL(session);

    // Server receives and completes the session creation message
    server.Receive(message, firstMessageReceived);
    User::WaitForRequest(firstMessageReceived);
    message.Complete(KErrNone);
    User::WaitForRequest(sessionCreation);

    // Parameters of genericParamList are sent via session to server
    session.Send(ipc, argumentsReceived);

    // Server receives the parameters
    server.Receive(message, secondMessageReceived);
    User::WaitForRequest(secondMessageReceived);

    list->UnpackFromClientL(message);

    message.Complete(KErrNone);
    User::WaitForRequest(argumentsReceived);

    CleanupStack::PopAndDestroy( 2 );//server, session,

    CleanupStack::PopAndDestroy(list);
    return KErrNone;
    }

// End File
