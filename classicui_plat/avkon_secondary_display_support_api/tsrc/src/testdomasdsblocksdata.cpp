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
* Description:  avkon_secondary_display_support_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknsddata.h>
#include <coemop.h>
#include <avkon.rsg>
#include <s32mem.h>

#include "testdomasds.h"



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMASDS::TestSDDExternalizeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMASDS::TestSDDExternalizeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomasds, "testdomasds" );
    _LIT( KTestSDDExternalizeL, "In TestSDDExternalizeL" );
    TestModuleIf().Printf( 0, Ktestdomasds, KTestSDDExternalizeL );
    // Print to log file
    iLog->Log( KTestSDDExternalizeL );
    
    TInt err = KErrNone;
    TTypeUid categoryIndex = 0x00000000;
    TInt pDialogIndex = R_AVKON_SPECIAL_CHARACTER_TABLE_DIALOG;
    _LIT8(pAdditionalData, "addData" );
    TBuf8<32> pData( pAdditionalData );
    RStoreWriteStream storewrite;
    CBufStore* store = CBufStore::NewLC( 1024 );     
    TStreamId steamid = storewrite.CreateLC( *store );
    CAknSDData* sdata = CAknSDData::NewL( categoryIndex, pDialogIndex, pData);
    CleanupStack::PushL( sdata );
    TRAP( err, sdata->ExternalizeL( storewrite ) );
    CleanupStack::PopAndDestroy( sdata );    
    CleanupStack::PopAndDestroy();    
    CleanupStack::PopAndDestroy();    
    return err;

    }
// -----------------------------------------------------------------------------
// CTestDOMASDS::TestSDDInternalizeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMASDS::TestSDDInternalizeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomasds, "testdomasds" );
    _LIT( KTestSDDInternalizeL, "In TestSDDInternalizeL" );
    TestModuleIf().Printf( 0, Ktestdomasds, KTestSDDInternalizeL );
    // Print to log file
    iLog->Log( KTestSDDInternalizeL );
    
    TInt err = KErrNone;
    TTypeUid categoryIndex = 0x00000000;
    TInt pDialogIndex = R_AVKON_SPECIAL_CHARACTER_TABLE_DIALOG;
    _LIT8(pAdditionalData, "addData" );
    TBuf8<32> pData( pAdditionalData );
    RStoreWriteStream storewrite;
    CBufStore* store = CBufStore::NewLC( 1024 );     
    TStreamId steamid = storewrite.CreateLC( *store );
    RStoreReadStream  rdstream;
    rdstream.OpenLC( *store, steamid );
    CAknSDData* sdata = CAknSDData::NewL( categoryIndex, pDialogIndex, pData);
    CleanupStack::PushL( sdata );
    sdata->ExternalizeL( storewrite );
    TRAP( err, sdata->InternalizeL( rdstream ) );
    CleanupStack::PopAndDestroy( sdata );    
    CleanupStack::PopAndDestroy();    
    CleanupStack::PopAndDestroy();    
    CleanupStack::PopAndDestroy();    
    return err;

    }
// -----------------------------------------------------------------------------
// CTestDOMASDS::TestSDDInsertGlobalListQueryItemIdsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMASDS::TestSDDInsertGlobalListQueryItemIdsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomasds, "testdomasds" );
    _LIT( KTestSDDInsertGlobalListQueryItemIdsL, "In TestSDDInsertGlobalListQueryItemIdsL" );
    TestModuleIf().Printf( 0, Ktestdomasds, KTestSDDInsertGlobalListQueryItemIdsL );
    // Print to log file
    iLog->Log( KTestSDDInsertGlobalListQueryItemIdsL );
    
    TInt err = KErrNone;
    TTypeUid categoryIndex = 0x00000000;
    TInt pDialogIndex = R_AVKON_SPECIAL_CHARACTER_TABLE_DIALOG;
    _LIT8(pAdditionalData, "addData" );
    TBuf8<32> pData( pAdditionalData );
    RArray<TInt> idarray;
    CAknSDData* sdata = CAknSDData::NewL( categoryIndex, pDialogIndex, pData);
    CleanupStack::PushL( sdata );

    TRAP( err, sdata->InsertGlobalListQueryItemIdsL( idarray ) );
    CleanupStack::PopAndDestroy( sdata );    

    return err;

    }
