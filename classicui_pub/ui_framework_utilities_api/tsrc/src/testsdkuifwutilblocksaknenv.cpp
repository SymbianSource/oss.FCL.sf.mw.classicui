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
* Description:  test functions in aknenv.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknlists.h>
#include <aknlayout2id.h> // for taknlayoutid
#include <akndef.h> // for taknuizoom
#include <aknsettingcache.h>
#include <aknlayoutconfig.h>
#include <documenthandler.h>
#include <apmstd.h> // tdatatype
#include <testsdkuifwutil.rsg>
#include <eikcmobs.h>

#include "testsdkuifwutil.h"

// CONSTANTS
_LIT( KEmptyText, "" );
_LIT( KTitleText, "title" );
const TInt KBufSize = 64;
const TInt KWsBufSize = 10240;
// FORWARD DECLARATIONS
// Oberver instance for MAknEditingStateIndicator
class CTestEditingStateIndicator : public CBase, public MAknEditingStateIndicator
    {
private:
    // from MAknEditingStateIndicator, not used
    void SetState( TAknEditingState /*aState*/ ){}
    
    // from MAknEditingStateIndicator, not used
    CAknIndicatorContainer* IndicatorContainer(){ return NULL; }
    };

// Observer instance for MAknIntermediateState
class CTestIntermediateState : public CBase, public MAknIntermediateState
    {
private:
    // from MAknIntermediateState, not used
    void CloseState(){}
    };

// Observer instance for MEikCommandObserver
class CTestCommandObserver : public CBase, public MEikCommandObserver
    {
    // from MEikCommandObserver, not used
    void ProcessCommandL( TInt /*aCommandId*/ ){};
    };

// Observer instance for MEikMenuObserver
class CTestMenuObserver : public CBase, public MEikMenuObserver
    {
    // from MEikCommandObserver, not used
    void ProcessCommandL( TInt /*aCommandId*/ ){};
    void SetEmphasis(CCoeControl* /*aMenuControl*/,TBool /*aEmphasis*/){};
    };


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvStatic
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvStatic( CStifItemParser& /*aItem*/ )
    {
    CAknEnv* aknenv = CAknEnv::Static();
    STIF_ASSERT_NOT_NULL( aknenv);
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvExecuteEmptyPopupListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvExecuteEmptyPopupListL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    CAknEnv* aknenv = CAknEnv::Static();
    TBuf<KBufSize> buf( KEmptyText );
    switch ( num )
        {
        case ECaseZero:
            {
            aknenv->ExecuteEmptyPopupListL( &buf );
            break;
            }
        case ECaseOne:
            {
            TBuf<KBufSize> titlebuf( KTitleText );
            aknenv->ExecuteEmptyPopupListL( &buf, &titlebuf );
            break;
            }
        default:
            {
            return KErrNotSupported;
            }
        }
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvSetAndGetObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvSetAndGetObserverL( CStifItemParser& /*aItem*/ )
    {
    CAknEnv* aknenv = CAknEnv::Static();
    CTestMenuObserver* ob = new ( ELeave ) CTestMenuObserver;
    CleanupStack::PushL( ob );
    aknenv->SetFepMenuObserver( ob );
    MEikMenuObserver* observer = aknenv->FepMenuObserver();
    STIF_ASSERT_NOT_NULL( observer );
    observer = NULL;
    CleanupStack::PopAndDestroy( ob );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvEditingStateIndicator
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvEditingStateIndicator( CStifItemParser& /*aItem*/ )
    {
    CAknEnv* aknenv = CAknEnv::Static();
    MAknEditingStateIndicator* indicator = aknenv->EditingStateIndicator();
    STIF_ASSERT_NOT_NULL( indicator );
    indicator = NULL;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvSwapEditingStateIndicatorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvSwapEditingStateIndicatorL( CStifItemParser& /*aItem*/ )
    {
    CAknEnv* aknenv = CAknEnv::Static();
    CTestEditingStateIndicator* indicator = new ( ELeave ) CTestEditingStateIndicator;
    CleanupStack::PushL( indicator );
    MAknEditingStateIndicator* oldindicator = aknenv->SwapEditingStateIndicator( indicator );
    STIF_ASSERT_NOT_NULL( oldindicator );
    oldindicator = NULL;
    CleanupStack::PopAndDestroy( indicator );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvExitForegroundAppL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvExitForegroundAppL( CStifItemParser& /*aItem*/ )
    {
    CAknEnv* aknenv = CAknEnv::Static();
    CDocumentHandler* dochandler = CDocumentHandler::NewL((CEikProcess*)iEnv->Process());
    CleanupStack::PushL( dochandler );
    TDataType empty;
    dochandler->OpenFileEmbeddedL(_L("\\testframework\\tctestsdkuifwutilaknenv.cfg"), empty);
    aknenv->ExitForegroundAppL();
    CleanupStack::PopAndDestroy( dochandler );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvRegisterIntermediateStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvRegisterIntermediateStateL( CStifItemParser& /*aItem*/ )
    {
    CAknEnv* aknenv = CAknEnv::Static();
    CTestIntermediateState* state = new ( ELeave ) CTestIntermediateState;
    CleanupStack::PushL( state );
    aknenv->RegisterIntermediateStateL( state );
    CleanupStack::PopAndDestroy( state );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvExitForegroundAppL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvUnRegisterIntermediateStateL( CStifItemParser& /*aItem*/ )
    {
    CAknEnv* aknenv = CAknEnv::Static();
    CTestIntermediateState* state = new ( ELeave ) CTestIntermediateState;
    CleanupStack::PushL( state );
    aknenv->RegisterIntermediateStateL( state );
    aknenv->UnRegisterIntermediateState( state );
    CleanupStack::PopAndDestroy( state );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvExitForegroundAppL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvCloseAllIntermediateStates( CStifItemParser& /*aItem*/ )
    {
    CAknEnv* aknenv = CAknEnv::Static();
    aknenv->CloseAllIntermediateStates();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvRunAppShutterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvRunAppShutterL( CStifItemParser& /*aItem*/ )
    {//!!! crash, so comment it in tc config file, but the coverage ok
    CDocumentHandler* dochandler = CDocumentHandler::NewL((CEikProcess*)iEnv->Process());
    CleanupStack::PushL( dochandler );
    TDataType empty;
    dochandler->OpenFileEmbeddedL(_L("\\testframework\\tctestsdkuifwutilakniconarray.cfg"), empty);
    CAknEnv::RunAppShutter();
    CleanupStack::PopAndDestroy( dochandler );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvAppWithShutterRunningL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvAppWithShutterRunningL( CStifItemParser& /*aItem*/ )
    {
    CDocumentHandler* dochandler = CDocumentHandler::NewL((CEikProcess*)iEnv->Process());
    CleanupStack::PushL( dochandler );
    TDataType empty;
    dochandler->OpenFileEmbeddedL(_L("\\testframework\\tctestsdkuifwutilakniconarray.cfg"), empty);
    CAknEnv::AppWithShutterRunning();
    CleanupStack::PopAndDestroy( dochandler );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvStopSchedulerWaitWithBusyMessage
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvStopSchedulerWaitWithBusyMessage( CStifItemParser& /*aItem*/ )
    {//!!! crash, coverage ok
    CAknEnv* aknenv = CAknEnv::Static();
    CActiveSchedulerWait wait;
    aknenv->StopSchedulerWaitWithBusyMessage( wait );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvProcessObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvProcessObserverL( CStifItemParser& /*aItem*/ )
    {
    CAknEnv* aknenv = CAknEnv::Static();
    CTestCommandObserver* ob = new ( ELeave ) CTestCommandObserver;
    CleanupStack::PushL( ob );
    CEikButtonGroupContainer* cba = CEikButtonGroupContainer::NewL(
                                                                    CEikButtonGroupContainer::ECba,
                                                                    CEikButtonGroupContainer::EHorizontal,
                                                                    ob,
                                                                    R_CBABUTTON );
    CleanupStack::PushL( cba );
    CAknSingleStyleListBox* list = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( list );
    aknenv->CreateCbaObserverL( cba, list );
    aknenv->RemoveCbaObserver();
    aknenv->InformCbaDeletion( cba );
    
    CleanupStack::PopAndDestroy( 3 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvProcessCommandMediationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvProcessCommandMediationL( CStifItemParser& /*aItem*/ )
    {
    CAknEnv* aknenv = CAknEnv::Static();
    CTestCommandObserver* observer = new ( ELeave ) CTestCommandObserver;
    CleanupStack::PushL( observer );
    aknenv->RequestCommandMediationL( *CEikButtonGroupContainer::Current(), *observer );
    aknenv->EndCommandMediation( *observer );
    
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvGetCurrentLayoutId
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvGetCurrentLayoutId( CStifItemParser& /*aItem*/ )
    {
    CAknEnv* aknenv = CAknEnv::Static();
    TAknLayoutId layoutid;
    aknenv->GetCurrentLayoutId( layoutid );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvGetCurrentGlobalUiZoom
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvGetCurrentGlobalUiZoom( CStifItemParser& /*aItem*/ )
    {
    CAknEnv* aknenv = CAknEnv::Static();
    TAknUiZoom uizoom;
    aknenv->GetCurrentGlobalUiZoom( uizoom );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvStatusPaneResIdForCurrentLayout
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvStatusPaneResIdForCurrentLayout( CStifItemParser& /*aItem*/ )
    {
    CAknEnv* aknenv = CAknEnv::Static();
    TAknLayoutId layoutid;
    aknenv->GetCurrentLayoutId( layoutid );
    aknenv->StatusPaneResIdForCurrentLayout( layoutid );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvRequestWsBuffer
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvRequestWsBuffer( CStifItemParser& /*aItem*/ )
    {
    CAknEnv* aknenv = CAknEnv::Static();
    TInt requestid = aknenv->RequestWsBuffer( KWsBufSize );
    aknenv->CancelWsBufferRequest( requestid );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvSettingCache
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvSettingCache( CStifItemParser& /*aItem*/ )
    {
    CAknEnv* aknenv = CAknEnv::Static();
    aknenv->SettingCache();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvLoadAknLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvLoadAknLayoutL( CStifItemParser& /*aItem*/ )
    {
    CAknEnv* aknenv = CAknEnv::Static();
    aknenv->LoadAknLayoutL();
    aknenv->AknLayout();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvAvkonColor
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvAvkonColor( CStifItemParser& /*aItem*/ )
    {
    CAknEnv* aknenv = CAknEnv::Static();
    aknenv->AvkonColor( 0 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvSplitViewActive
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvSplitViewActive( CStifItemParser& /*aItem*/ )
    {
    CAknEnv* aknenv = CAknEnv::Static();
    aknenv->SplitViewActive();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknEnvTransparencyEnabled
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknEnvTransparencyEnabled( CStifItemParser& /*aItem*/ )
    {
    CAknEnv* aknenv = CAknEnv::Static();
    aknenv->TransparencyEnabled();
    
    return KErrNone;
    }

// End of file


