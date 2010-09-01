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
* Description:    For testing aiw_service_handler_api
*
*/





// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <testsdkaiwservicehandler.rsg>

#include "testsdkaiwservicehandler.h"

// FORWARD DECLARATIONS
class CTestMenuObserver : public CBase, public MEikMenuObserver
    {
public:
    // from MEikMenuObserver, only for test, no use 
    void ProcessCommandL(TInt /*aCommandId*/){}
    // from MEikMenuObserver, only for test, no use 
    void SetEmphasis(CCoeControl */*aMenuControl*/, TBool /*aEmphasis*/){}
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKAiwServiceHandler::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwServiceHandler::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestAiwServiceHandlerNewFuncL", CTestSDKAiwServiceHandler::TestAiwServiceHandlerNewFuncL ),
        ENTRY( "TestAiwServiceHandlerDeconstructorL", CTestSDKAiwServiceHandler::TestAiwServiceHandlerDeconstructorL ),
        ENTRY( "TestAiwServiceHandlerResetL", CTestSDKAiwServiceHandler::TestAiwServiceHandlerResetL ),
        ENTRY( "TestAiwServiceHandlerNbrOfProvidersL", CTestSDKAiwServiceHandler::TestAiwServiceHandlerNbrOfProvidersL ),
        ENTRY( "TestAiwServiceHandlerAttachAndDetachL", CTestSDKAiwServiceHandler::TestAiwServiceHandlerAttachAndDetachL ),
        ENTRY( "TestAiwServiceHandlerGetInterestL", CTestSDKAiwServiceHandler::TestAiwServiceHandlerGetInterestL ),
        ENTRY( "TestAiwServiceHandlerGetCriteriaL", CTestSDKAiwServiceHandler::TestAiwServiceHandlerGetCriteriaL ),
        ENTRY( "TestAiwServiceHandlerInAndOutParamListL", CTestSDKAiwServiceHandler::TestAiwServiceHandlerInAndOutParamListL ),
        ENTRY( "TestAiwServiceHandlerInitializeMenuPaneL", CTestSDKAiwServiceHandler::TestAiwServiceHandlerInitializeMenuPaneL ),
        ENTRY( "TestAiwServiceHandlerServiceCmdByMenuCmdL", CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceCmdByMenuCmdL ),
        ENTRY( "TestAiwServiceHandlerServiceExecuteMenuCmdL", CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceExecuteMenuCmdL ),
        ENTRY( "TestAiwServiceHandlerServiceAttachMenuL", CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceAttachMenuL ),
        ENTRY( "TestAiwServiceHandlerServiceDetachMenuL", CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceDetachMenuL ),
        ENTRY( "TestAiwServiceHandlerServiceIsSubMenuEmptyL", CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceIsSubMenuEmptyL ),
        ENTRY( "TestAiwServiceHandlerServiceIsAiwMenuL", CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceIsAiwMenuL ),
        ENTRY( "TestAiwServiceHandlerServiceHandleSubmenuL", CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceHandleSubmenuL ),
        ENTRY( "TestAiwServiceHandlerServiceReportMenuLaunchL", CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceReportMenuLaunch ),
        ENTRY( "TestAiwServiceHandlerServiceExecuteServiceCmdL", CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceExecuteServiceCmdL),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::TestAiwServiceHandlerNewFuncL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwServiceHandler::TestAiwServiceHandlerNewFuncL( CStifItemParser& aItem )
    {
    TInt num;
    TInt err = aItem.GetNextInt(num);
    if(err != KErrNone)
        {
        return err;
        }
    switch(num)
        {
        case ECaseOne:
            {
            CAiwServiceHandler* servicehandler = CAiwServiceHandler::NewL();
            CleanupStack::PushL(servicehandler);
            STIF_ASSERT_NOT_NULL(servicehandler);
            CleanupStack::PopAndDestroy(servicehandler);
            break;
            }
        case ECaseTwo:
            {
            CAiwServiceHandler* servicehandlerforlc = CAiwServiceHandler::NewLC();
            STIF_ASSERT_NOT_NULL(servicehandlerforlc);
            CleanupStack::PopAndDestroy(servicehandlerforlc);
            break;
            }
        default:
            return KErrNotSupported;
        }
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::TestAiwServiceHandlerDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwServiceHandler::TestAiwServiceHandlerDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAiwServiceHandler* servicehandler = CAiwServiceHandler::NewL();
    delete servicehandler;
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::TestAiwServiceHandlerResetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwServiceHandler::TestAiwServiceHandlerResetL( CStifItemParser& /*aItem*/ )
    {
    CAiwServiceHandler* servicehandler = CAiwServiceHandler::NewLC();
    servicehandler->Reset();
    CleanupStack::PopAndDestroy(servicehandler);
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::TestAiwServiceHandlerNbrOfProvidersL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwServiceHandler::TestAiwServiceHandlerNbrOfProvidersL( CStifItemParser& /*aItem*/ )
    {
    CAiwServiceHandler* servicehandler = CAiwServiceHandler::NewLC();
    CAiwCriteriaItem* item = CAiwCriteriaItem::NewLC();
    TInt num = servicehandler->NbrOfProviders(item);
    STIF_ASSERT_EQUALS(0, num);
    CleanupStack::PopAndDestroy(2);
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::TestAiwServiceHandlerAttachAndDetachL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwServiceHandler::TestAiwServiceHandlerAttachAndDetachL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    CAiwServiceHandler* servicehandler = CAiwServiceHandler::NewLC();
    const CAiwCriteriaItem* item = NULL;
    switch ( num )
        {
        case ECaseOne:
            {
            servicehandler->AttachL( R_AIW_INTEREST_ONE );
            item = servicehandler->GetCriteria( 0x8001 );
            STIF_ASSERT_NOT_NULL( item );
            item = NULL;
            servicehandler->DetachL( R_AIW_INTEREST_TWO );
            item = servicehandler->GetCriteria( 0x8003 );
            STIF_ASSERT_NULL( item );
            CleanupStack::PopAndDestroy( servicehandler );
            break;
            }
        case ECaseTwo:
            {
            RCriteriaArray interest;
            CleanupClosePushL( interest );
            _LIT8( KContentTypeLandmark, "application/x-landmark" );
            CAiwCriteriaItem* criteria = CAiwCriteriaItem::NewLC( KAiwCmdMnShowMap, KAiwCmdMnShowMap, KContentTypeLandmark );
            TUid base;
            base.iUid = KAiwClassBase;
            criteria->SetServiceClass( base );
            User::LeaveIfError( interest.Append( criteria ) );            
            servicehandler->AttachL( interest );
            
            RCriteriaArray temp;
            CleanupClosePushL( temp );
            servicehandler->GetInterest( temp );
            STIF_ASSERT_EQUALS( 1, temp.Count() );
            
            servicehandler->DetachL( temp );
            CleanupStack::Pop( &temp );
            CleanupStack::PopAndDestroy( 3 ); // criteria, interest, servicehandler
            break;
            }
        default:
            CleanupStack::PopAndDestroy( servicehandler );
            return KErrNotSupported;
        }
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::TestAiwServiceHandlerGetInterestL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwServiceHandler::TestAiwServiceHandlerGetInterestL( CStifItemParser& /*aItem*/ )
    {
    CAiwServiceHandler* servicehandler = CAiwServiceHandler::NewLC();
    RCriteriaArray interest;
    CleanupClosePushL( interest );
    _LIT8( KContentTypeLandmark, "application/x-landmark" );
    CAiwCriteriaItem* criteria = CAiwCriteriaItem::NewLC( KAiwCmdMnShowMap, KAiwCmdMnShowMap, KContentTypeLandmark );
    TUid base;
    base.iUid = KAiwClassBase;
    criteria->SetServiceClass( base );
    User::LeaveIfError( interest.Append( criteria ) );
    
    servicehandler->AttachL( interest );
    RCriteriaArray temp;
    CleanupClosePushL( temp );
    temp.ResetAndDestroy();
    servicehandler->GetInterest( temp );
    STIF_ASSERT_EQUALS( 1, temp.Count() );
    
    CleanupStack::PopAndDestroy( 4 ); // criteria, interest, servicehandler
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::TestAiwServiceHandlerGetCriteriaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwServiceHandler::TestAiwServiceHandlerGetCriteriaL( CStifItemParser& /*aItem*/ )
    {
    CAiwServiceHandler* servicehandler = CAiwServiceHandler::NewLC();
    servicehandler->AttachL( R_AIW_INTEREST_TWO );
    const CAiwCriteriaItem* item = NULL;
    item = servicehandler->GetCriteria( 0x8003 );
    
    STIF_ASSERT_NOT_NULL(item);
    
    CleanupStack::PopAndDestroy( servicehandler );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::TestAiwServiceHandlerInAndOutParamListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwServiceHandler::TestAiwServiceHandlerInAndOutParamListL( CStifItemParser& /*aItem*/ )
    {
    CAiwServiceHandler* servicehandler = CAiwServiceHandler::NewLC();
    CAiwGenericParamList* inlist = NULL;
    CAiwGenericParamList* outlist = NULL;
    inlist = &(servicehandler->InParamListL());
    outlist = &(servicehandler->OutParamListL());
    STIF_ASSERT_NOT_NULL( inlist );
    STIF_ASSERT_NOT_NULL( outlist );
    STIF_ASSERT_EQUALS( 0, inlist->Count() );
    STIF_ASSERT_EQUALS( 0, outlist->Count() );
    
    CleanupStack::PopAndDestroy( servicehandler );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::TestAiwServiceHandlerInitializeMenuPaneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwServiceHandler::TestAiwServiceHandlerInitializeMenuPaneL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    CTestMenuObserver* ob = new ( ELeave ) CTestMenuObserver;
    CleanupStack::PushL( ob );
    
    CAiwServiceHandler* servicehandler = CAiwServiceHandler::NewLC();
    CEikMenuPane* menupane = new ( ELeave ) CEikMenuPane( ob );
    CleanupStack::PushL( menupane );
    TInt baseid = 0;
    switch ( num )
        {
        case ECaseOne:
            {
            servicehandler->InitializeMenuPaneL( *menupane, R_AIW_MENU, 
                                                    baseid, servicehandler->InParamListL() );
            break;
            }
        case ECaseTwo:
            {
            servicehandler->InitializeMenuPaneL( *menupane, R_AIW_MENU, 
                                                    baseid, servicehandler->InParamListL(), ETrue );
            break;
            }
        default:
            CleanupStack::PopAndDestroy( menupane );
            CleanupStack::PopAndDestroy(servicehandler);
            CleanupStack::PopAndDestroy( ob );
            return KErrNotSupported;
        }
    CleanupStack::Pop( menupane );
    CleanupStack::PopAndDestroy( servicehandler );
    CleanupStack::PopAndDestroy( ob );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceCmdByMenuCmdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceCmdByMenuCmdL( CStifItemParser& /*aItem*/ )
    {
    TInt baseid = 0;
    CAiwServiceHandler* servicehandler = CAiwServiceHandler::NewLC();
    servicehandler->AttachMenuL( R_AIW_MENU, R_AIW_INTEREST_TWO );
    servicehandler->ExecuteMenuCmdL( baseid, servicehandler->InParamListL(), 
                                        servicehandler->OutParamListL() );
    TInt num = servicehandler->ServiceCmdByMenuCmd( R_AIW_MENU );
    STIF_ASSERT_EQUALS( 0, num );
    CleanupStack::PopAndDestroy( servicehandler );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceExecuteMenuCmdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceExecuteMenuCmdL( CStifItemParser& /*aItem*/ )
    {
    CTestMenuObserver* ob = new ( ELeave ) CTestMenuObserver;
    CleanupStack::PushL( ob );
    CAiwServiceHandler* servicehandler = CAiwServiceHandler::NewLC();
    TInt baseid = 0;
    CEikMenuPane* menupane = new ( ELeave ) CEikMenuPane( ob );
    CleanupStack::PushL( menupane );
    servicehandler->InitializeMenuPaneL( *menupane, R_AIW_MENU, 
                                                baseid, servicehandler->InParamListL(), ETrue );
    servicehandler->ExecuteMenuCmdL( baseid, servicehandler->InParamListL(), 
                                    servicehandler->OutParamListL() );
    CleanupStack::Pop( menupane );
    CleanupStack::PopAndDestroy( servicehandler );
    CleanupStack::PopAndDestroy( ob );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceAttachMenuL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceAttachMenuL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        return err;
    CAiwServiceHandler* servicehandler = CAiwServiceHandler::NewLC();
    switch ( num )
        {
        case ECaseOne:
            {
            servicehandler->AttachMenuL( R_AIW_MENU, R_AIW_INTEREST_TWO );
            CleanupStack::PopAndDestroy( servicehandler );
            break;
            }
        case ECaseTwo:
            {
            TResourceReader reader;
            CCoeEnv::Static()->CreateResourceReaderLC( reader, R_AIW_INTEREST_TWO );
            servicehandler->AttachMenuL( R_AIW_MENU, reader );
            CleanupStack::PopAndDestroy( 2 );
            break;
            }
        case ECaseThree:
            {
            RCriteriaArray interest;
            CleanupClosePushL( interest );
            _LIT8( KContentTypeLandmark, "application/x-landmark" );
            CAiwCriteriaItem* criteria = CAiwCriteriaItem::NewLC( KAiwCmdMnShowMap, KAiwCmdMnShowMap, KContentTypeLandmark );
            TUid base;
            base.iUid = KAiwClassBase;
            criteria->SetServiceClass( base );
            User::LeaveIfError( interest.Append( criteria ) );
            servicehandler->AttachMenuL( R_AIW_MENU, interest );
            CleanupStack::PopAndDestroy( 3 );// interest, criteria, servicehandler
            break;
            }
        default:
            CleanupStack::PopAndDestroy( servicehandler );
            return KErrNotSupported;
        }
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceDetachMenuL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceDetachMenuL( CStifItemParser& /*aItem*/ )
    {
    CAiwServiceHandler* servicehandler = CAiwServiceHandler::NewLC();
    servicehandler->AttachMenuL( R_AIW_MENU, R_AIW_INTEREST_TWO );
    servicehandler->DetachMenu( R_AIW_MENU, R_AIW_INTEREST_TWO );
    CleanupStack::PopAndDestroy( servicehandler );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceIsSubMenuEmptyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceIsSubMenuEmptyL( CStifItemParser& /*aItem*/ )
    {
    CAiwServiceHandler* servicehandler = CAiwServiceHandler::NewLC();
    servicehandler->AttachMenuL( R_AIW_MENU, R_AIW_INTEREST_TWO );
    TBool result = servicehandler->IsSubMenuEmpty( 0x8901 );
    STIF_ASSERT_FALSE( result );
    CleanupStack::PopAndDestroy( servicehandler );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceIsAiwMenuL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceIsAiwMenuL( CStifItemParser& /*aItem*/ )
    {
    CAiwServiceHandler* servicehandler = CAiwServiceHandler::NewLC();
    servicehandler->AttachMenuL( R_AIW_MENU, R_AIW_INTEREST_TWO );
    TBool result = servicehandler->IsAiwMenu( R_AIW_MENU );
    STIF_ASSERT_FALSE( result );
    CleanupStack::PopAndDestroy( servicehandler );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceHandleSubmenuL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceHandleSubmenuL( CStifItemParser& /*aItem*/ )
    {
    TInt baseid = 0;
    CTestMenuObserver* ob = new ( ELeave ) CTestMenuObserver;
    CleanupStack::PushL( ob );
    CAiwServiceHandler* servicehandler = CAiwServiceHandler::NewLC();
    CEikMenuPane* menupane = new ( ELeave ) CEikMenuPane( ob );
    CleanupStack::PushL( menupane );
    servicehandler->InitializeMenuPaneL( *menupane, R_AIW_MENU, 
                                                baseid, servicehandler->InParamListL(), ETrue );
    CleanupStack::Pop( menupane );
    TBool result = servicehandler->HandleSubmenuL( *menupane );
    STIF_ASSERT_FALSE( result );
    CleanupStack::PopAndDestroy( servicehandler );
    CleanupStack::PopAndDestroy( ob );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceReportMenuLaunch
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceReportMenuLaunch( CStifItemParser& /*aItem*/ )
    {
    CAiwServiceHandler::ReportMenuLaunch();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceReportMenuLaunch
// -----------------------------------------------------------------------------
//
TInt CTestSDKAiwServiceHandler::TestAiwServiceHandlerServiceExecuteServiceCmdL( CStifItemParser& /*aItem*/ )
    {
    CAiwServiceHandler* servicehandler = CAiwServiceHandler::NewLC();
    servicehandler->AttachMenuL( R_AIW_MENU, R_AIW_INTEREST_TWO );
    servicehandler->ExecuteServiceCmdL( KAiwCmdMnShowMap,
                                        servicehandler->InParamListL(),
                                        servicehandler->OutParamListL(),
                                        0,
                                        NULL );
    CleanupStack::PopAndDestroy( servicehandler );
    return KErrNone;
    }






//  [End of File]
