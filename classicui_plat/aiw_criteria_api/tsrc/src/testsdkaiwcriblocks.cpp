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
* Description:    Test aiw_criteria_api
*
*/





// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aiwcommon.h>
#include <testsdkaiwcri.rsg>

#include "testsdkaiwcri.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdkaiwcri::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKAiwCri::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctestsdkaiwcri::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwCri::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestACINewL", CTestSDKAiwCri::TestACINewL ),
        ENTRY( "TestACINewLC", CTestSDKAiwCri::TestACINewLC ),
        ENTRY( "TestACINewLIDL", CTestSDKAiwCri::TestACINewLIDL ),
        ENTRY( "TestACINewLCIDL", CTestSDKAiwCri::TestACINewLCIDL ),
        ENTRY( "TestACISetId", CTestSDKAiwCri::TestACISetId ),
        ENTRY( "TestACISetServiceClass", CTestSDKAiwCri::TestACISetServiceClass ),
        ENTRY( "TestACISetServiceCmd", CTestSDKAiwCri::TestACISetServiceCmd ),
        ENTRY( "TestACISetContentTypeL", CTestSDKAiwCri::TestACISetContentTypeL ),
        ENTRY( "TestACIId", CTestSDKAiwCri::TestACIId ),
        ENTRY( "TestACIServiceClass", CTestSDKAiwCri::TestACIServiceClass ),
        ENTRY( "TestACIServiceCmd", CTestSDKAiwCri::TestACIServiceCmd ),
        ENTRY( "TestACIContentType", CTestSDKAiwCri::TestACIContentType ),
        ENTRY( "TestACISetOptions", CTestSDKAiwCri::TestACISetOptions ),
        ENTRY( "TestACIOptions", CTestSDKAiwCri::TestACIOptions ),
        ENTRY( "TestACIMaxProviders", CTestSDKAiwCri::TestACIMaxProviders ),
        ENTRY( "TestACIReadFromResoureL", CTestSDKAiwCri::TestACIReadFromResoureL ),
        ENTRY( "TestACIDefaultProvider", CTestSDKAiwCri::TestACIDefaultProvider ),
        ENTRY( "TestACISetDefaultProvider", CTestSDKAiwCri::TestACISetDefaultProvider ),
        ENTRY( "TestACIOperatorL", CTestSDKAiwCri::TestACIOperatorL ),
        ENTRY( "TestACISetMaxProviders", CTestSDKAiwCri::TestACISetMaxProviders ),
        ENTRY( "TestACIRomOnly", CTestSDKAiwCri::TestACIRomOnly ),
        ENTRY( "TestACIDelete", CTestSDKAiwCri::TestACIDelete ),
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACINewL
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACINewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACINewL, "In TestACINewL" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACINewL );
    // Print to log file
    iLog->Log( KTestACINewL );

    TInt err = KErrNone;
    TRAP( err, iAiwCriItem = CAiwCriteriaItem::NewL() );
    
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACINewLC
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACINewLC( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACINewLC, "In TestACINewLC" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACINewLC );
    // Print to log file
    iLog->Log( KTestACINewLC );

    TInt err = KErrNone;
    TRAP( err, iAiwCriItem = CAiwCriteriaItem::NewLC(); CleanupStack::Pop(); );
    
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACINewLIDL
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACINewLIDL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACINewLIDL, "In TestACINewLIDL" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACINewLIDL );
    // Print to log file
    iLog->Log( KTestACINewLIDL );

    TInt err = KErrNone;
    _LIT8( KContentTypeLandmark, "application/x-landmark" );
    TRAP( err, iAiwCriItem = CAiwCriteriaItem::NewL
        ( KAiwCmdMnShowMap, KAiwCmdMnShowMap, KContentTypeLandmark ) );
    
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACINewLCIDL
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACINewLCIDL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACINewLCIDL, "In TestACINewLCIDL" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACINewLCIDL );
    // Print to log file
    iLog->Log( KTestACINewLCIDL );

    TInt err = KErrNone;
    _LIT8( KContentTypeLandmark, "application/x-landmark" );
    TRAP( err, iAiwCriItem = CAiwCriteriaItem::NewLC
        ( KAiwCmdMnShowMap, KAiwCmdMnShowMap, KContentTypeLandmark );
        CleanupStack::Pop(); );
    
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACISetId
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACISetId( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACISetId, "In TestACISetId" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACISetId );
    // Print to log file
    iLog->Log( KTestACISetId );

    TInt err = KErrNone;
    TRAP( err, iAiwCriItem->SetId( KAiwCmdMnShowMap ) );
    
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACISetServiceClass
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACISetServiceClass( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACISetServiceClass, "In TestACISetServiceClass" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACISetServiceClass );
    // Print to log file
    iLog->Log( KTestACISetServiceClass );

    TInt err = KErrNone;
    TUid base;
    base.iUid = KAiwClassBase;
    TRAP( err, iAiwCriItem->SetServiceClass( base ) );
    
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACISetServiceCmd
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACISetServiceCmd( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACISetServiceCmd, "In TestACISetServiceCmd" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACISetServiceCmd );
    // Print to log file
    iLog->Log( KTestACISetServiceCmd );

    TInt err = KErrNone;
    TRAP( err, iAiwCriItem->SetServiceCmd( KAiwCmdMnShowMap ) );
    
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACISetContentTypeL
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACISetContentTypeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACISetContentTypeL, "In TestACISetContentTypeL" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACISetContentTypeL );
    // Print to log file
    iLog->Log( KTestACISetContentTypeL );

    TInt err = KErrNone;
    _LIT8( KContentTypeLandmark, "application/x-landmark" );
    TRAP( err, iAiwCriItem->SetContentTypeL( KContentTypeLandmark ) );
    
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACIId
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACIId( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACIId, "In TestACIId" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACIId );
    // Print to log file
    iLog->Log( KTestACIId );

    TInt err = KErrNone;
    TRAP( err, iAiwCriItem->Id() );
    
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACIServiceClass
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACIServiceClass( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACIServiceClass, "In TestACIServiceClass" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACIServiceClass );
    // Print to log file
    iLog->Log( KTestACIServiceClass );

    TInt err = KErrNone;
    TRAP( err, iAiwCriItem->ServiceClass() );
    
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACIServiceCmd
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACIServiceCmd( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACIServiceCmd, "In TestACIServiceCmd" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACIServiceCmd );
    // Print to log file
    iLog->Log( KTestACIServiceCmd );

    TInt err = KErrNone;
    TRAP( err, iAiwCriItem->ServiceCmd() );
    
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACIContentType
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACIContentType( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACIContentType, "In TestACIContentType" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACIContentType );
    // Print to log file
    iLog->Log( KTestACIContentType );

    TInt err = KErrNone;
    TRAP( err, iAiwCriItem->ContentType() );
    
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACISetOptions
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACISetOptions( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACISetOptions, "In TestACISetOptions" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACISetOptions );
    // Print to log file
    iLog->Log( KTestACISetOptions );

    TInt err = KErrNone;
    TRAP( err, iAiwCriItem->SetOptions( KAiwOptASyncronous ) );
    
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACIOptions
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACIOptions( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACIOptions, "In TestACIOptions" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACIOptions );
    // Print to log file
    iLog->Log( KTestACIOptions );

    TInt err = KErrNone;
    TRAP( err, iAiwCriItem->Options() );
    
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACIMaxProviders
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACIMaxProviders( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACIMaxProviders, "In TestACIMaxProviders" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACIMaxProviders );
    // Print to log file
    iLog->Log( KTestACIMaxProviders );

    TInt err = KErrNone;
    TRAP( err, iAiwCriItem->MaxProviders() );
    
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACIReadFromResoureL
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACIReadFromResoureL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACIReadFromResoureL, "In TestACIReadFromResoureL" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACIReadFromResoureL );
    // Print to log file
    iLog->Log( KTestACIReadFromResoureL );

    TInt err = KErrNone;
    TResourceReader resReader;
    CCoeEnv::Static()->CreateResourceReaderLC( resReader, R_AIWEXAMPLE_MENUINTEREST );
    TRAP( err, iAiwCriItem->ReadFromResoureL( resReader ) );
    CleanupStack::PopAndDestroy();

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACIDefaultProvider
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACIDefaultProvider( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACIDefaultProvider, "In TestACIDefaultProvider" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACIDefaultProvider );
    // Print to log file
    iLog->Log( KTestACIDefaultProvider );

    TInt err = KErrNone;
    TRAP( err, iAiwCriItem->DefaultProvider() );

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACISetDefaultProvider
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACISetDefaultProvider( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACISetDefaultProvider, "In TestACISetDefaultProvider" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACISetDefaultProvider );
    // Print to log file
    iLog->Log( KTestACISetDefaultProvider );

    TInt err = KErrNone;
    TRAP( err, iAiwCriItem->SetDefaultProvider( 0 ) );

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACIOperatorL
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACIOperatorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACIOperator, "In TestACIOperator" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACIOperator );
    // Print to log file
    iLog->Log( KTestACIOperator );

    TInt err = KErrNone;
    _LIT8( KContentTypeLandmark, "application/x-landmark" );
    CAiwCriteriaItem* item1 = CAiwCriteriaItem::NewL
        ( KAiwCmdMnShowMap, KAiwCmdMnShowMap, KContentTypeLandmark );
    CleanupStack::PushL( item1 );
    TUid base;
    base.iUid = KAiwClassBase;
    item1->SetServiceClass( base );
    item1->SetDefaultProvider( 0 );
    item1->SetMaxProviders( 0xff );
    item1->SetOptions( KAiwOptASyncronous );
    
    CAiwCriteriaItem* item2 = CAiwCriteriaItem::NewL
        ( KAiwCmdMnShowMap, KAiwCmdMnShowMap, KContentTypeLandmark );
    CleanupStack::PushL( item2 );
    item2->SetServiceClass( base );
    item2->SetDefaultProvider( 0 );
    item2->SetMaxProviders( 0xff );
    item2->SetOptions( KAiwOptASyncronous );

    STIF_ASSERT_TRUE( (*item1) == (*item2) );
    CleanupStack::PopAndDestroy( 2 );

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACISetMaxProviders
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACISetMaxProviders( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACISetMaxProviders, "In TestACISetMaxProviders" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACISetMaxProviders );
    // Print to log file
    iLog->Log( KTestACISetMaxProviders );

    TInt err = KErrNone;
    TRAP( err, iAiwCriItem->SetMaxProviders( 0xff ) );

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACIRomOnly
// -----------------------------------------------------------------------------
//

TInt CTestSDKAiwCri::TestACIRomOnly( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACIRomOnly, "In TestACIRomOnly" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACIRomOnly );
    // Print to log file
    iLog->Log( KTestACIRomOnly );

    TInt err = KErrNone;
    TRAP( err, iAiwCriItem->RomOnly() );

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwCri::TestACIDelete
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwCri::TestACIDelete( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KTestACIModule, "TestACIModule" );
    _LIT( KTestACIDelete, "In TestACIDelete" );
    TestModuleIf().Printf( 0, KTestACIModule, KTestACIDelete );
    // Print to log file
    iLog->Log( KTestACIDelete );

    if ( iAiwCriItem )
        {
        delete iAiwCriItem;
        iAiwCriItem = NULL;
        }

    return KErrNone;
    }

//  [End of File]
