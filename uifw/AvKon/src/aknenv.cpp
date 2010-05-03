/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: 
*
*/

#include "aknenv.h"
#include "AknUtils.h"
#include "aknEditStateIndicator.h"
#include "AknSgcc.h"
#include "AknSettingCache.h"

#include <apgtask.h>
#include <aknintermediate.h>
#include <coeaui.h>
#include <coemain.h>
#include <AknQueryDialog.h>
#include <aknnotewrappers.h>
#include <eikfrlb.h>
#include <eikfrlbd.h>
#include <aknPopup.h>
#include <aknlists.h>
#include <eiklbv.h>
#include <eiklbi.h>
#include <AknWaitDialog.h>
#include <AknLayout.lag>
#include <bidivisual.h>
#include <aknconsts.h>
#include <AknBidiTextUtils.h>
#include <CdlEngine.h>
#include <CdlRefs.h>
#include <AknLayout2DataDef.h>
#include <layoutpack.cdl.h>
#include <CdlExplorer.h>
#include <aknlayout.cdl.h>
#include <aknapaclayout.cdl.h>
#include <applayout.cdl.h>
#include <appapaclayout.cdl.h>
#include <skinlayout.cdl.h>
#include <cdlfont.cdl.h>
#include "AknFontRegistry.h"
#include <barsread.h>
#include <AknPriv.hrh>
#include <aknlayoutscalable_apps.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>
#include <featmgr.h>
#include <AknIconSrvClient.h>
#include <AknServerApp.h>
#include <AknFontSpecification.h>

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#endif
// Needed to use MopGetObject
#include <coemop.h>

#include <e32property.h>
#include <UikonInternalPSKeys.h>    // KUikLayoutState
#include <AvkonInternalCRKeys.h>    // KAknQwertyInputModeActive
#include "AknDebug.h"
#include <coecntss.h>               // CCoeControlStaticSettings
#include <coefont.h>                // For font size indices
#include <AknLayoutConfig.h>

#define APPLY_CONE_FONT_EXTRA_LARGE_FACTOR(a)   ( a * 4 / 3 )
#define APPLY_CONE_FONT_EXTRA_SMALL_FACTOR(a)   ( a * 3 / 4 )

#include "transitionmanager.h"
#include<akntranseffect.h> // for Transition effect enumerations

// TAknLayoutConfigScreenMode is defined like this because
// the name CAknLayoutConfig::TScreenMode can't be used
// in SDK header files (AknEnv.h). This technique essentially
// gives us an alternative name for CAknLayoutConfig::TScreenMode,
// which can be used in a public header.
class TAknLayoutConfigScreenMode : public CAknLayoutConfig::TScreenMode 
	{
public:
	TAknLayoutConfigScreenMode(const CAknLayoutConfig::TScreenMode& aCopy)
	: CAknLayoutConfig::TScreenMode(aCopy) 
		{
		}
	};


// CAknCommandMediator is an internal class for mediating MSK commands from
// CBA to specified observer.
NONSHARABLE_CLASS( CAknCommandMediator  )
    : public CBase,
      public MEikCommandObserver
    {
public:
    CAknCommandMediator() {};
    ~CAknCommandMediator();
    void SetCbaObserverL( CEikButtonGroupContainer& aCba,
        MEikCommandObserver& aCommandObserver );
    void InformCbaDeletion( CEikButtonGroupContainer& aCba );
    void RemoveCbaObserver( MEikCommandObserver& aCommandObserver );

    // From MEikCommandObserver
    void ProcessCommandL( TInt aCommandId );

private:

    CEikButtonGroupContainer *iCba;
    MEikCommandObserver* iCommandObserver;
    };


CAknCommandMediator::~CAknCommandMediator()
    {    
    // These should already be deleted when CAknEnv is being deleted.
    iCba = NULL;
    iCommandObserver = NULL;
    }


void CAknCommandMediator::ProcessCommandL( TInt aCommandId )
    {
    __ASSERT_DEBUG( iCommandObserver, User::Invariant() );
    if ( iCommandObserver )
        {
        // Mediate event to the observer.
        iCommandObserver->ProcessCommandL( aCommandId );
        }
    }

void CAknCommandMediator::SetCbaObserverL( CEikButtonGroupContainer& aCba,
    MEikCommandObserver& aCommandObserver )
    {
    // Remove mediator from observing the previously set cba.
    if ( iCba && iCba != &aCba )
        {
        iCba->RemoveCommandObserver( 3 );
        
        iCba = NULL;
        iCommandObserver = NULL;
        }

    // Update command observer.
    if ( &aCba && &aCommandObserver )
        {
        aCba.UpdateCommandObserverL( 3, *this );
        
        iCba = &aCba;
        iCommandObserver = &aCommandObserver;
        }
    }

void CAknCommandMediator::InformCbaDeletion( CEikButtonGroupContainer& aCba )
    {
    // Check whether the cba, for which the commands are being mediated,
    // is being deleted.
    if ( iCba == &aCba )
        {
        iCba = NULL;
        iCommandObserver = NULL;
        }
    }

void CAknCommandMediator::RemoveCbaObserver(
    MEikCommandObserver& aCommandObserver )
    {
    if ( iCommandObserver && iCommandObserver == &aCommandObserver )
        {
        __ASSERT_DEBUG( iCba, User::Invariant() );
        iCba->RemoveCommandObserver( 3 );

        iCba = NULL;
        iCommandObserver = NULL;
        }
    }


// const TInt KAknEnvScrollHostGranularity = 1;
const TInt KInitialRunInfoArraySize = 5;
const TInt KAknEnvNoScreenModeLoaded = -1;

// Avkon Color support
const TUint8 ColorRemapTable[256] =
	{
	0xff, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
	0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
	0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
	0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
	0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
	0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
	0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0x00, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
	0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
	0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xd7
	};

EXPORT_C void CAknEnv::SetFepMenuObserver(MEikMenuObserver* aObserver)
    {
    iFepMenuObserver = aObserver;
    }

EXPORT_C MEikMenuObserver* CAknEnv::FepMenuObserver()
    {
    return iFepMenuObserver;
    }

EXPORT_C MAknEditingStateIndicator* CAknEnv::EditingStateIndicator()
    {
    return iEditStateIndicator;
    }

EXPORT_C MAknEditingStateIndicator* CAknEnv::SwapEditingStateIndicator(MAknEditingStateIndicator* aIndicator)
    {
    MAknEditingStateIndicator* indicator = iEditStateIndicator;
    iEditStateIndicator = aIndicator;
    return indicator;
    }

EXPORT_C void CAknEnv::ExitForegroundAppL()
    {
    RWsSession& wsSession=CEikonEnv::Static()->WsSession();
    TInt count=wsSession.NumWindowGroups(0);
    CArrayFixFlat<TInt>* wgIds=new(ELeave) CArrayFixFlat<TInt>(count);
    CleanupStack::PushL(wgIds);
    // Get list of window group ids from WServ
    wsSession.WindowGroupList(0,wgIds);
    // Select the first in the list (which will always be the forground app)
    TInt wgId = (*wgIds)[0];
    CleanupStack::PopAndDestroy();  // wgIds;

    // Exit app
    TApaTask task(wsSession);
    task.SetWgId(wgId);
    task.SendSystemEvent(EApaSystemEventShutdown);
    }



EXPORT_C CAknEnv::CAknEnv() : iWsBufferRequestArray( 1 ), iLastScreenMode(KAknEnvNoScreenModeLoaded)
    {
    }

EXPORT_C void CAknEnv::ConstructL()
    {
    TName threadName=RThread().Name();
    TBool isEiksrvThread=(threadName.CompareC(EIKAPPUI_SERVER_THREAD_NAME)==KErrNone);

    User::LeaveIfError( RAknIconSrvClient::Connect() );

    iCdlEngRef = CdlEngine::CreateCdlEngineL();

    iSettingCache = CAknSettingCache::NewL();
    
    //if KFeatureIdUiTransitionEffects is not supported, CTransitionManager::NewL returns NULL
	iTransitionManager = CTransitionManager::NewL( *iCoeEnv );

    iStateArray = new(ELeave) CArrayPtrFlat<MAknIntermediateState>(1);
    CAknSgcClient::CreateL();   // owned by CCoeStatic system
    TAknPopupFader::CreateStaticL();    // owned by CCoeStatic system

    iRunInfoArray = new( ELeave )
        TBidirectionalState::TRunInfo[KInitialRunInfoArraySize];

    iRunInfoArrayLength = KInitialRunInfoArraySize;

    SetLayoutRequirementsL();
    LoadAknLayoutL();
    AssertLayoutLoaded();
    iLayout = &AknLayout::CustomisationInstance();

    // Set the current feature language
    if (FeatureManager::FeatureSupported(KFeatureIdJapanese))
        {
        iFeatureLanguage = KFeatureIdJapanese;
        }

    }

EXPORT_C CAknEnv* CAknEnv::Static()
    {
    return (CAknEnv*)CEikonEnv::Static()->Extension();
    }

EXPORT_C CAknEnv::~CAknEnv()
    {
    delete iCommandMediator;
    delete iTransitionManager;
    delete iCdlEngRef;
    delete iBusyMsgDialog;
    iBusyMsgDialog = NULL;      // just in case scheduler callback tries to use this during exit
    delete iIdle;
    delete iStateArray;
    delete iSettingCache;
    delete [] iRunInfoArray;
    iWsBufferRequestArray.Close();
    RAknIconSrvClient::Disconnect();
    delete iFontRegistry;
    FeatureManager::UnInitializeLib();
    }


EXPORT_C void CAknEnv::RegisterIntermediateStateL(MAknIntermediateState *aState)
    {
    iStateArray->AppendL(aState);
    }

EXPORT_C void CAknEnv::UnRegisterIntermediateState(MAknIntermediateState *aState)
    {
    TInt count = iStateArray->Count();
    TInt i;
    for (i=0; i<count; i++)
        {
        if (iStateArray->At(i) == aState)
            break;
        }
    if (i<count)
        iStateArray->Delete(i);
    }

EXPORT_C void CAknEnv::CloseAllIntermediateStates()
    {
    delete iIdle;
    iIdle = NULL;
    iIdle = CIdle::New(EActivePriorityWsEvents+1);
    if (iIdle)
        iIdle->Start(TCallBack(RealCloseIntermediateStates, this));
    }
    
// -----------------------------------------------------------------------------
// CAknEnv::GetTransparencyEnabled
// -----------------------------------------------------------------------------
//    
EXPORT_C TBool CAknEnv::TransparencyEnabled() const
    {
    return iSettingCache->TransparencyEnabled();
    }    
    

TInt CAknEnv::RealCloseIntermediateStates(TAny *aEnvAny)
    {
    CAknEnv *env = (CAknEnv*)aEnvAny;
    TInt count = env->iStateArray->Count();
    for (TInt i=0; i<count; i++)
        {
        env->iStateArray->At(i)->CloseState();
        }
    env->iStateArray->Reset();

    // Destroy the CIdle.
    delete env->iIdle;
    env->iIdle = 0;
    return EFalse;
    }

TBool CAknEnv::HasBlank() const
    {
    return iTransitionManager == NULL; //when there is no effects, there is screenblanker
    }

void CAknEnv::TransitionEvent(TInt aEvent)
	{
	TransitionEvent(aEvent, KNullUid); 
	}

void CAknEnv::TransitionEvent(TInt aEvent, const TUid& aUid)
    {
	if(iTransitionManager != NULL)
	    {
    	switch(aEvent)
    		{
    		case AknTransEffect::EEmbeddedApplicationStart:
    			iTransitionManager->SetEmbedded(); //go trough
    		case AknTransEffect::EApplicationStartSwitch:
    		case AknTransEffect::EApplicationStart:
    		case AknTransEffect::EAppStartupBackground:
    			iTransitionManager->AppStartup(aEvent, aUid);
    			break;
    		case AknTransEffect::EAppStartComplete:
    			iTransitionManager->AppStartupComplete();
    			break;
    		case AknTransEffect::EApplicationExit:
    			iTransitionManager->AppExit(aEvent, aUid);
    			break;
    		case KAknTransitionDeactivate:
    			break;
    		case AknTransEffect::EApplicationActivate:
    		    iTransitionManager->AppSwitch(aEvent);
    		    break;
    		case KAknTransitionEventAvkon:
    			iTransitionManager->SetAvkon();
    			break;
    		case KAknTransitionEventFlags:
    			iTransitionManager->CheckFlags();
    		    break;
    		case KAknTransitionExitCancel:
    			iTransitionManager->CancelExit();
    			break;
    		default:
    		    __ASSERT_DEBUG(0, User::Panic(_L("Unknown transition"), aEvent));
    		    User::Invariant();
    		}
	    }
	}


class CMyListBox : public CAknSinglePopupMenuStyleListBox
    {
public:
    TKeyResponse OfferKeyEventL(const TKeyEvent &aKeyEvent, TEventCode aType)
    {
    if (aKeyEvent.iCode != EKeyOK)
        return CAknSinglePopupMenuStyleListBox::OfferKeyEventL(aKeyEvent, aType);
    return EKeyWasConsumed;
    }
    void ActivateL()
    {
    STATIC_CAST(CFormattedCellListBoxItemDrawer*,this->View()->ItemDrawer())->FormattedCellData()->SetSubCellAlignmentL(0,CGraphicsContext::ECenter);

    }
    };

EXPORT_C void CAknEnv::ExecuteEmptyPopupListL(const TDesC *aEmptyText, const TDesC *aPopupTitle, TInt aSoftKeyId)
    {
    HBufC *message = CCoeEnv::Static()->AllocReadResourceL(R_AVKON_EMPTY_POPUP_LIST_TEXT);
    CleanupStack::PushL(message);

    HBufC *emptysoftkey = CCoeEnv::Static()->AllocReadResourceL(R_TEXT_SOFTKEY_EMPTY);
    CleanupStack::PushL(emptysoftkey);

    if (!aEmptyText)
        {
        aEmptyText = message;
        }

    CEikFormattedCellListBox *list = new(ELeave)CMyListBox;
    CleanupStack::PushL(list);
    if (aSoftKeyId == 0) aSoftKeyId = R_AVKON_SOFTKEYS_CANCEL;

    CAknPopupList *popupList = CAknPopupList::NewL(list, aSoftKeyId, AknPopupLayouts::EMenuWindow);
    CleanupStack::PushL(popupList);
    list->ConstructL(popupList, CEikListBox::ELeftDownInViewRect);

    // Logical to visual conversion is already performed.
    list->UseLogicalToVisualConversion( ETrue );

    // Some viewers use ok_empty; We remove left softkey if right softkey has
    // something else than empty.
    if (! ( aSoftKeyId == R_AVKON_SOFTKEYS_OK_EMPTY))
    popupList->ButtonGroupContainer()->SetCommandL(0,EAknSoftkeyEmpty, *emptysoftkey);

    CDesCArrayFlat *items = new(ELeave)CDesCArrayFlat(1);
    CleanupStack::PushL(items);
    
    CTextListBoxModel* model=list->Model();
    model->SetItemTextArray(items);
    model->SetOwnershipType(ELbmOwnsItemArray);
    CleanupStack::Pop(); // items

    list->View()->ItemDrawer()->SetFlags(CTextListItemDrawer::EDisableHighlight);
    
    list->View()->SetListEmptyTextL(*aEmptyText);

    if (aPopupTitle)
        {
        popupList->SetTitleL(*aPopupTitle);
        }
    CleanupStack::Pop(); // popupList
    popupList->ExecuteLD();

    CleanupStack::PopAndDestroy( 3 ); // list, emptysoftkey, message
    }

EXPORT_C void CAknEnv::ExecuteEmptyPopupListL(const TDesC *aEmptyText)
    {
    ExecuteEmptyPopupListL(aEmptyText,0);
    }

EXPORT_C void CAknEnv::RunAppShutter()
    {
    CEikonEnv* eikEnv = CEikonEnv::Static();
    CAknAppUi* base = (CAknAppUi*)eikEnv->EikAppUi();
    while (base && base->ContainerAppUi())
        base = (CAknAppUi*)base->ContainerAppUi();

    CEikAppServer* server = eikEnv->AppServer();
    if (server)
        server->NotifyServerExit(EAknCmdExit);

    if (base)
        base->RunAppShutter();
    }

EXPORT_C CAknAppUi* CAknEnv::AppWithShutterRunning()
    {
    CEikonEnv* eikEnv = CEikonEnv::Static();
    CAknAppUi* app = (CAknAppUi*)eikEnv->EikAppUi();
    do  {
        if (app->IsAppShutterRunning())
            return app;
        app = (CAknAppUi*)app->ContainerAppUi();
        } while (app);

    return NULL;
    }

EXPORT_C void CAknEnv::StopSchedulerWaitWithBusyMessage(CActiveSchedulerWait& aWait)
    {
    if (aWait.IsStarted())
        {
        if (aWait.CanStopNow())
            {
            aWait.AsyncStop();
            }
        else
            {
            CEikonEnv* eikEnv = CEikonEnv::Static();
            CEikAppUi* appUi = eikEnv->EikAppUi();
            if (appUi && !appUi->IsDisplayingDialog())
                {
                // If the waiting control can't stop the scheduler immediately, try to show
                // a busy note to alert the user and prevent them from using the app till the
                // scheduler can return.
                // Some other service running in your app has started a scheduler wait, but not
                // stopped it before this waiting control exited. That service must stop it's scheduler wait
                // before this one can stop.
                //
                // The dialog is stored as member data with a reference count to ensure that it is deleted
                // on app exit and that it lasts as long as it should.
                CAknEnv* env = Static();
                if (!env->iBusyMsgDialog)
                    {
                    TRAP_IGNORE(
                        {
                        env->iBusyMsgDialog = new(ELeave) CAknWaitDialog(reinterpret_cast<CEikDialog**>(&env->iBusyMsgDialog), ETrue);
                        env->iBusyMsgDialog->ExecuteLD(R_SCHEDULER_STOP_BUSY_MESSAGE);
                        });
                    }
                env->iBusyMsgCount++;
                aWait.AsyncStop(TCallBack(SchedulerStoppedCallBack, env));
                }
            }
        }
    }

TInt CAknEnv::SchedulerStoppedCallBack(TAny* aThis)
    {
    CAknEnv* self = static_cast<CAknEnv*>(aThis);
    self->DoSchedulerStoppedCallBack();
    return 0;
    }

void CAknEnv::DoSchedulerStoppedCallBack()
    {
    iBusyMsgCount--;
    if (iBusyMsgCount<=0 && iBusyMsgDialog)
        {
        TRAP_IGNORE(iBusyMsgDialog->ProcessFinishedL());
        }
    }

NONSHARABLE_CLASS(CLBCommandObserver) : public MEikCommandObserver
    {
public:
    CLBCommandObserver(CEikButtonGroupContainer *aCba, CEikListBox *aListBox);
    void ProcessCommandL(TInt aCommandId);
    CEikButtonGroupContainer *iCba;
    CEikListBox *iListBox;
    };


CLBCommandObserver::CLBCommandObserver(CEikButtonGroupContainer *aCba, CEikListBox *aListBox)
     : iCba(aCba), iListBox(aListBox)
    {
    }

void CLBCommandObserver::ProcessCommandL(TInt aCommandId)
    {
    // We will be executing this code only when commandid is correct.
    // so no need to test for aCommandId.
    if (aCommandId == EAknSoftkeyOk)
    {
    // We need to send a key event that will cause redraw of application state.
    // This is because of multi-item fetch in phonebook works kinda odd and
    // we need to update it's state. (just need to make sure findbox does
    // not eat this key :-)
    TKeyEvent keyevent;
    keyevent.iCode = EKeyApplicationF;
    keyevent.iModifiers = 0;
    CEikonEnv::Static()->SimulateKeyEventL(keyevent, EEventKey);
    }

    CEikButtonGroupContainer *cba = iCba;
    AVKONENV->RemoveCbaObserver();
    // the next call is very likely to delete listbox and cba.
    // resend the event to the cba.
    STATIC_CAST(MEikCommandObserver*,cba)->ProcessCommandL(aCommandId);
    }


EXPORT_C void CAknEnv::CreateCbaObserverL(CEikButtonGroupContainer *aCba, CEikListBox *aListBox)
    {
    RemoveCbaObserver();
    iCbaCommandObserver = new(ELeave)CLBCommandObserver(aCba, aListBox);
    TRAPD(error, aCba->UpdateCommandObserverL(0, *iCbaCommandObserver));
    if (error)
        {
        delete iCbaCommandObserver;
        iCbaCommandObserver = NULL;
        User::Leave(error);
        }
    }

EXPORT_C void CAknEnv::RemoveCbaObserver()
    {
    if (iCbaCommandObserver)
        {
        STATIC_CAST(CLBCommandObserver*,iCbaCommandObserver)->iCba->RemoveCommandObserver(0);
        delete iCbaCommandObserver;
        iCbaCommandObserver = NULL;
        }
    }

EXPORT_C void CAknEnv::InformCbaDeletion(CEikButtonGroupContainer *aCba)
    {
    if (iCbaCommandObserver)
        {
        if (STATIC_CAST(CLBCommandObserver*, iCbaCommandObserver)->iCba == aCba)
            {
            RemoveCbaObserver();
            }
        }

    if ( iCommandMediator )
        {
        iCommandMediator->InformCbaDeletion( *aCba );
        }
    }

// ---------------------------------------------------------------------------
// Creates new command mediator if necessary, and sets it to mediate commands.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknEnv::RequestCommandMediationL(
    CEikButtonGroupContainer& aCba, MEikCommandObserver& aCommandObserver )
    {
    if ( !iCommandMediator )
        {
        iCommandMediator = new ( ELeave ) CAknCommandMediator;
        }

    iCommandMediator->SetCbaObserverL( aCba, aCommandObserver );
    }

EXPORT_C void CAknEnv::EndCommandMediation(
    MEikCommandObserver& aCommandObserver )
    {
    if ( iCommandMediator )
        {
        iCommandMediator->RemoveCbaObserver( aCommandObserver );
        }
    }


EXPORT_C void CAknEnv::GetCurrentLayoutId(TAknLayoutId& aCurrentLayoutId) const
    {
    aCurrentLayoutId = iSettingCache->LayoutId();
    }

EXPORT_C void CAknEnv::GetCurrentGlobalUiZoom(TAknUiZoom& aCurrentGlobalUiZoom) const
    {
    aCurrentGlobalUiZoom = iSettingCache->GlobalUiZoom();
    }
    

// -----------------------------------------------------------------------------
// CAknEnv::RequestWsBuffer
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknEnv::RequestWsBuffer( TInt aRequestedBufferSize )
    {
    TInt ret = KErrGeneral;

    if ( aRequestedBufferSize > 0 )
        {
        // Cut down to max size.
        if ( aRequestedBufferSize > KAknMaxWsBufferSize )
            {
            aRequestedBufferSize = KAknMaxWsBufferSize;
            }

        // Generate request ID, they start from 1.
        TInt requestID = ++iRequestIdCounter;

        TWsBufferRequest request = {requestID, aRequestedBufferSize};
        ret = iWsBufferRequestArray.Append( request );

        if ( ret == KErrNone )
            {
            if ( aRequestedBufferSize > iCurrentWsBufferRequest )
                {
                SetWsBufferSize();
                }

            // return the request ID
            ret = requestID;
            }
        }

    return ret;
    }

// -----------------------------------------------------------------------------
// CAknEnv::CancelWsBufferRequest
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknEnv::CancelWsBufferRequest( TInt aRequestID )
    {
    // Real request IDs are always positive, ignore others.
    if ( aRequestID > 0 )
        {
        TInt count = iWsBufferRequestArray.Count();

        for ( TInt i = 0 ; i < count ; i++ )
            {
            TWsBufferRequest& request = iWsBufferRequestArray[i];

            if ( request.iRequestID == aRequestID )
                {
                TInt canceledRequestSize = request.iRequestedSize;
                iWsBufferRequestArray.Remove( i );

                // If the canceled request was not lower than the currently
                // highest request, set WS buffer size again according to the
                // list of requests.

                if ( canceledRequestSize >= iCurrentWsBufferRequest )
                    {
                    SetWsBufferSize();
                    }
                break;
                }
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknEnv::SetWsBufferSize
// -----------------------------------------------------------------------------
//
void CAknEnv::SetWsBufferSize()
    {
    TInt count = iWsBufferRequestArray.Count();

    // Only if there are no requests, default to KAknDefaultWsBufferSize.
    // This allows requesting also smaller WS buffer sizes for saving RAM.
    TInt highestRequest = count ? 0 : KAknDefaultWsBufferSize;

    // Find out the highest request
    for ( TInt i = 0 ; i < count ; i++ )
        {
        TInt requestedSize = iWsBufferRequestArray[i].iRequestedSize;

        if ( requestedSize > highestRequest )
            {
            highestRequest = requestedSize;
            }
        }

    SetWsBufferSize( highestRequest );
    }

// -----------------------------------------------------------------------------
// CAknEnv::SetWsBufferSize
// -----------------------------------------------------------------------------
//
void CAknEnv::SetWsBufferSize( TInt aRequestedBufferSize )
    {
    TRAPD( err, iEikonEnv->WsSession().SetMaxBufferSizeL(
        aRequestedBufferSize ) );

    if ( !iWsBufferRequestArray.Count() )
        {
        iCurrentWsBufferRequest = 0;
        }

    else if ( err == KErrNone )
        {
        iCurrentWsBufferRequest = aRequestedBufferSize;
        }
    }

EXPORT_C CAknSettingCache& CAknEnv::SettingCache() const
    {
    return *iSettingCache;
    }

TBidirectionalState::TRunInfo* CAknEnv::RunInfoArray( TInt& aLength ) const
    {
    aLength = iRunInfoArrayLength;
    return  iRunInfoArray;
    }

TInt CAknEnv::PrepareRunInfoArray( const TDesC& aLogicalText )
    {
    TBidiLogicalToVisual converter(
        aLogicalText,
        iRunInfoArray,
        iRunInfoArrayLength ) ;

    TInt count = converter.Reorder();
    return SetRequiredRunInfoArraySize( count );
    }

TInt CAknEnv::SetRequiredRunInfoArraySize( TInt aLength )
    {
    TInt ret( KErrNone );

    if ( iRunInfoArrayLength < aLength )
        {
        TBidirectionalState::TRunInfo* array =
            new TBidirectionalState::TRunInfo[aLength];

        if ( array )
            {
            delete [] iRunInfoArray;
            iRunInfoArray = array;
            iRunInfoArrayLength = aLength;
            }
        else
            {
            ret = KErrNoMemory;
            }
        }

    return ret;
    }

struct SStatusPaneEquivResIds
    {
    TInt iElaf;
    TInt iAbrw;
    };

struct SStatusPaneOrientationEquivResIds
    {
    TInt iResId;
    TInt iEqvivResId;
    };


/**
* Mirrored (Arabic & Hebrew) mapping of status pane layout resources.
*
* Note that mirrored status pane layouts are not used anymore,
* so there is no actual mapping here.
*/
const SStatusPaneEquivResIds KStatusPaneEquivResIds[] =
    {
        { R_AVKON_STATUS_PANE_LAYOUT_IDLE,                   R_AVKON_STATUS_PANE_LAYOUT_IDLE },
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL,                  R_AVKON_STATUS_PANE_LAYOUT_USUAL },
        { R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE,     R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE },
        { R_AVKON_STATUS_PANE_LAYOUT_EMPTY,                  R_AVKON_STATUS_PANE_LAYOUT_EMPTY },
        { R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE, R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE },
        { R_AVKON_STATUS_PANE_LAYOUT_SMALL,                  R_AVKON_STATUS_PANE_LAYOUT_SMALL },
        { R_AVKON_STATUS_PANE_LAYOUT_VT,                     R_AVKON_STATUS_PANE_LAYOUT_VT }

//        {R_AVKON_STATUS_PANE_LAYOUT_IDLE, R_AVKON_STATUS_PANE_LAYOUT_IDLE_MIRRORED},
//        {R_AVKON_STATUS_PANE_LAYOUT_USUAL, R_AVKON_STATUS_PANE_LAYOUT_USUAL_MIRRORED},
//        {R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE, R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE_MIRRORED},
//        {R_AVKON_STATUS_PANE_LAYOUT_EMPTY, R_AVKON_STATUS_PANE_LAYOUT_EMPTY},
//        {R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE, R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE_MIRRORED},
//        {R_AVKON_STATUS_PANE_LAYOUT_SMALL, R_AVKON_STATUS_PANE_LAYOUT_SMALL},
//        {R_AVKON_STATUS_PANE_LAYOUT_VT, R_AVKON_STATUS_PANE_LAYOUT_VT_MIRRORED}
    };


/**
* Status pane layout resource mapping for landscape orientation with right softkeys.
* Here each of the status pane layout IDs which can not be used in RSK stacon mode are
* mapped to the equivalent RSK stacon mode status pane resource IDs.
*/
const SStatusPaneOrientationEquivResIds KStatusPaneSoftkeysRightEquivResIds[] =
    {
        { R_AVKON_STATUS_PANE_LAYOUT_IDLE,                   R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT },
        { R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT,              R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT },
        { R_AVKON_STATUS_PANE_LAYOUT_IDLE_EXT,               R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT },
        { R_AVKON_STATUS_PANE_LAYOUT_IDLE_MIRRORED,          R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT },
        
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL,                  R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT },
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT,              R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT },
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT,             R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT },
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL_MIRRORED,         R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT },
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL_WITH_BATTERY_PANE,R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT },
        
        { R_AVKON_STATUS_PANE_LAYOUT_EMPTY,                  R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT },
        
        { R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE, R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT },
        { R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE_MIRRORED, R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT },
        { R_AVKON_STATUS_PANE_LAYOUT_SMALL,                  R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT },
        
        { R_AVKON_STATUS_PANE_LAYOUT_VT,                     R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT },
        { R_AVKON_STATUS_PANE_LAYOUT_VT_MIRRORED,            R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT },
        
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL,              R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT },
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE,                   R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT },
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT,             R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT },
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT,              R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT },
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT_NO_SOFTKEYS, R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT },
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS,  R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT }
    };


/**
* Status pane layout resource mapping for landscape orientation with left softkeys.
* Here each of the status pane layout IDs which can not be used in LSK stacon mode are
* mapped to the equivalent LSK stacon mode status pane resource IDs.
*/
const SStatusPaneOrientationEquivResIds KStatusPaneSoftkeysLeftEquivResIds[] =
    {
        { R_AVKON_STATUS_PANE_LAYOUT_IDLE,                   R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT },
        { R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT,              R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT },
        { R_AVKON_STATUS_PANE_LAYOUT_IDLE_EXT,               R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT },
        { R_AVKON_STATUS_PANE_LAYOUT_IDLE_MIRRORED,          R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT },
        
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL,                  R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT },
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT,              R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT },
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT,             R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT },
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL_MIRRORED,         R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT },
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL_WITH_BATTERY_PANE,R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT },
        
        { R_AVKON_STATUS_PANE_LAYOUT_EMPTY,                  R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT },
        
        { R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE, R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT },
        { R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE_MIRRORED, R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT },
        { R_AVKON_STATUS_PANE_LAYOUT_SMALL,                  R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT },
        
        { R_AVKON_STATUS_PANE_LAYOUT_VT,                     R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT },
        { R_AVKON_STATUS_PANE_LAYOUT_VT_MIRRORED,            R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT },
        
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL,              R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT },
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE,                   R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT },
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT,             R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT },
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT,              R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT },
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT_NO_SOFTKEYS, R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT },
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS,  R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT }
    };


/**
* Status pane layout resource mapping for landscape orientation with bottom softkeys (flat status pane).
* Here each of the status pane layout IDs which can not be used in landscape BSK mode are
* mapped to the equivalent landscape BSK mode status pane resource IDs.
*/
const SStatusPaneOrientationEquivResIds KStatusPaneSoftkeysBottomEquivResIds[] =
    {
        { R_AVKON_STATUS_PANE_LAYOUT_IDLE,           R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS },
        { R_AVKON_STATUS_PANE_LAYOUT_IDLE_EXT,       R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS },
        { R_AVKON_STATUS_PANE_LAYOUT_IDLE_MIRRORED,  R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS },
        
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL,          R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT },
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT,      R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT },
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL_MIRRORED, R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT },
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL_WITH_BATTERY_PANE, R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT },
        
        { R_AVKON_STATUS_PANE_LAYOUT_VT,             R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT },
        { R_AVKON_STATUS_PANE_LAYOUT_VT_MIRRORED,    R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT },
        
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL,      R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT },
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE,       R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS },
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT,             R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT },
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT,  R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS },
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT_NO_SOFTKEYS, R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT },
    };


/**
* Status pane layout resource mapping for portrait orientation.
* Here each of the status pane layout IDs which can not be used in portrait mode are
* mapped to the equivalent portrait mode status pane resource IDs.
*/
const SStatusPaneOrientationEquivResIds KStatusPanePortraitEquivResIds[] =
    {
#ifndef __SERIES60_31__    
        { R_AVKON_STATUS_PANE_LAYOUT_IDLE, R_AVKON_STATUS_PANE_LAYOUT_IDLE_EXT },// UNCOMMENT this for enablling extended statuspane as default 
#else
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL, R_AVKON_STATUS_PANE_LAYOUT_USUAL },
#endif

#ifndef __SERIES60_31__    
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL, R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT }, // UNCOMMENT this for enablling extended statuspane as default 
#endif

#ifndef __SERIES60_31__    
        { R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT, R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT }, // UNCOMMENT this for enablling extended statuspane as default 
        { R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT,  R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT }, // UNCOMMENT this for enablling extended statuspane as default 
#else
        { R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT, R_AVKON_STATUS_PANE_LAYOUT_USUAL }, // COMMENT this for enablling extended statuspane as default 
        { R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT,  R_AVKON_STATUS_PANE_LAYOUT_USUAL }, // COMMENT this for enablling extended statuspane as default 
#endif
        { R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT, R_AVKON_STATUS_PANE_LAYOUT_IDLE },
        { R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT, R_AVKON_STATUS_PANE_LAYOUT_IDLE },
        { R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_RIGHT, R_AVKON_STATUS_PANE_LAYOUT_EMPTY },
        { R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_LEFT, R_AVKON_STATUS_PANE_LAYOUT_EMPTY },
        
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL, R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT },
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE,                   R_AVKON_STATUS_PANE_LAYOUT_IDLE_EXT },
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT,             R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT },
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT,              R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT },
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT_NO_SOFTKEYS, R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT },
        { R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS,  R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT }
    };


/**
* Status pane layout resource mapping for widescreen status pane mode (nHD landscape).
* Here each of the status pane layout IDs which can not be used in nHD mode are
* mapped to the equivalent nHD resource IDs.
*/
const SStatusPaneOrientationEquivResIds KStatusPaneWidescreenEquivResIds[] =
    {
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL,                   R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL },
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT,               R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL },
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT,              R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT },
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL_MIRRORED,          R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL },
        { R_AVKON_STATUS_PANE_LAYOUT_USUAL_WITH_BATTERY_PANE, R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL },
        { R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT,     R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL },
        { R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT,    R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL },
        
        { R_AVKON_STATUS_PANE_LAYOUT_IDLE,                 R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE },
        { R_AVKON_STATUS_PANE_LAYOUT_IDLE_EXT,             R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE },
        { R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT,            R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS },
        { R_AVKON_STATUS_PANE_LAYOUT_IDLE_MIRRORED,        R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE },
        { R_AVKON_STATUS_PANE_LAYOUT_VT,                   R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE },
        { R_AVKON_STATUS_PANE_LAYOUT_VT_MIRRORED,          R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE },
        { R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT,  R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE },
        { R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT,   R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE },
        
        { R_AVKON_STATUS_PANE_LAYOUT_SMALL,                           R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL },
        { R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE,          R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL },
        { R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE_MIRRORED, R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL },
        
        { R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_RIGHT, R_AVKON_STATUS_PANE_LAYOUT_EMPTY},
        { R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_LEFT,  R_AVKON_STATUS_PANE_LAYOUT_EMPTY}
    };


static TBool IsAreaSideRightPaneActive()
    {
    return EFalse;
    }


EXPORT_C TInt CAknEnv::StatusPaneResIdForCurrentLayout( TInt aResId ) const
    {
    TInt resId = aResId;
    
    // static mapping of usual layouts first.
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        // Map A&H first if needed
        const SStatusPaneEquivResIds* equiv = NULL;
        for (TUint ii=0; ii<sizeof(KStatusPaneEquivResIds)/sizeof(*KStatusPaneEquivResIds); ii++)
            {
            if (KStatusPaneEquivResIds[ii].iElaf == resId || KStatusPaneEquivResIds[ii].iAbrw == resId)
                {
                equiv = &KStatusPaneEquivResIds[ii];
                resId = equiv->iElaf;
                break;
                }
            }

        // Get the cba location.
		CAknLayoutConfig::TScreenMode screenMode = CAknSgcClient::ScreenMode();
		TAknPrivSoftkeyLocation softkeyLocation = screenMode.SoftkeyLocation();


        if ( IsAreaSideRightPaneActive() )
            {
            for ( TUint ii = 0;
                  ii < sizeof( KStatusPaneWidescreenEquivResIds ) /
                       sizeof( *KStatusPaneWidescreenEquivResIds );
                  ii++ )
                {
                if ( KStatusPaneWidescreenEquivResIds[ii].iResId == resId)
                    {
                    resId = KStatusPaneWidescreenEquivResIds[ii].iEqvivResId;
                    break;
                    }
                }
            }
        else if (softkeyLocation == EAknPrivSoftkeyLocationRight)
            {
            for ( TUint ii = 0;
                  ii < sizeof( KStatusPaneSoftkeysRightEquivResIds ) / 
                       sizeof( *KStatusPaneSoftkeysRightEquivResIds );
                  ii++)
                {
                if (KStatusPaneSoftkeysRightEquivResIds[ii].iResId == resId)
                    {
                    resId = KStatusPaneSoftkeysRightEquivResIds[ii].iEqvivResId;
                    break;
                    }
                }
            }
        else if (softkeyLocation == EAknPrivSoftkeyLocationLeft)
            {
            for ( TUint ii = 0;
                  ii < sizeof( KStatusPaneSoftkeysLeftEquivResIds ) /
                       sizeof( *KStatusPaneSoftkeysLeftEquivResIds );
                  ii++ )
                {
                if (KStatusPaneSoftkeysLeftEquivResIds[ii].iResId == resId)
                    {
                    resId = KStatusPaneSoftkeysLeftEquivResIds[ii].iEqvivResId;
                    break;
                    }
                }
            }
        else if (softkeyLocation == EAknPrivSoftkeyLocationBottom)
            {
            for ( TUint ii = 0;
                  ii < sizeof( KStatusPaneSoftkeysBottomEquivResIds ) /
                       sizeof( *KStatusPaneSoftkeysBottomEquivResIds );
                  ii++ )
                {
                if (KStatusPaneSoftkeysBottomEquivResIds[ii].iResId == resId)
                    {
                    resId = KStatusPaneSoftkeysBottomEquivResIds[ii].iEqvivResId;
                    break;
                    }
                }
            }
        }
    else
        {
        for ( TUint ii = 0;
              ii < sizeof( KStatusPanePortraitEquivResIds ) /
                   sizeof( *KStatusPanePortraitEquivResIds ); ii++ )
            {
            if (KStatusPanePortraitEquivResIds[ii].iResId == resId)
                {
                resId = KStatusPanePortraitEquivResIds[ii].iEqvivResId;
                break;
                }
            }
        }
    // end of static mapping

    const SStatusPaneEquivResIds* equiv = NULL;
    for ( TUint ii = 0;
          ii < sizeof( KStatusPaneEquivResIds ) /
               sizeof( *KStatusPaneEquivResIds );
          ii++ )
        {
        if ( KStatusPaneEquivResIds[ii].iElaf == resId ||
             KStatusPaneEquivResIds[ii].iAbrw == resId )
            {
            equiv = &KStatusPaneEquivResIds[ii];
            break;
            }
        }

    if (!equiv)
        {
        return resId;
        }

    if (iSettingCache->LayoutId() == EAknLayoutIdABRW)
        {
        return equiv->iAbrw;
        }
    else
        {
        return equiv->iElaf;
    }
    }

EXPORT_C TBool CAknEnv::LoadAknLayoutL()
    {
    // Get required layout parameters
    CAknLayoutConfig::TScreenMode screenMode = CAknSgcClient::ScreenMode();
    return LoadAknLayoutL(screenMode);
    }
    
EXPORT_C TBool CAknEnv::LoadAknLayoutL(const TAknLayoutConfigScreenMode& aScreenMode)
    {
    // Get required layout parameters
    TAknLayoutId id;
    GetCurrentLayoutId(id);
    TAknUiZoom zoom = ResolveCurrentUiZoom();

    // Check to see if the layout is already loaded
    if (id == iLastLayoutId &&
        aScreenMode.ModeNumber() == iLastScreenMode &&
        zoom == iLastZoom)
        return EFalse;

    return TryLoadAknLayoutL(id, aScreenMode, zoom);
    }

void CAknEnv::ReloadAknLayoutL()
    {
    // Get layout parameters for the current layout
    CAknLayoutConfig::TScreenMode screenMode = CAknSgcClient::ScreenMode();
    TAknLayoutId id;
    GetCurrentLayoutId(id);
    TAknUiZoom zoom = ResolveCurrentUiZoom();
    
    // always load the current layout
    TryLoadAknLayoutL(id, screenMode, zoom);
    }
    

void CleanupLayoutPacks(TAny* aPtr)
	{
	RPointerArray<LayoutPack::CInstance>* packPtr = (RPointerArray<LayoutPack::CInstance>*)aPtr;
	packPtr->ResetAndDestroy();
	delete packPtr;
	}

TInt CompareLayoutPacks(const LayoutPack::CInstance& aLeft, const LayoutPack::CInstance& aRight)
    {
    return aLeft.priority() - aRight.priority();
    }

TBool CAknEnv::TryLoadAknLayoutL(TAknLayoutId aId, const TAknLayoutConfigScreenMode& aScreenMode, TAknUiZoom aUiZoom)
	{
	// Load an appropriate layout
	TBool layoutLoaded = ETrue;
	if (!LoadAknLayoutL(aId, aScreenMode, aUiZoom))
	    {
	    // fall back to normal zoom
	    if (!LoadAknLayoutL(aId, aScreenMode, EAknUiZoomNormal))
	        {
	        // fall back to western layout
	        layoutLoaded = LoadAknLayoutL(EAknLayoutIdELAF, aScreenMode, EAknUiZoomNormal);
	        }
	    }
	
	// just in case the current required layout has changed, remember 
	// the new settings
    if (layoutLoaded)
        {
        iLastLayoutId = aId;
        iLastScreenMode = aScreenMode.ModeNumber();
        iLastZoom = aUiZoom;
        }	
    
	return layoutLoaded;
	}

TBool CAknEnv::LoadAknLayoutL(TAknLayoutId aId, const TAknLayoutConfigScreenMode& aScreenMode, TAknUiZoom aUiZoom)
    {
    RPointerArray<LayoutPack::CInstance>* bestPacks = new(ELeave) RPointerArray<LayoutPack::CInstance>(1);
    CleanupStack::PushL(TCleanupItem(CleanupLayoutPacks, bestPacks));

    CCdlRefs* refs = CdlEngine::FindInstancesLC(LayoutPack::KCdlInterfaceUid);

    TInt count = refs->CountRefs();
    TBool styleMatchAlreadyFound = EFalse;
    for (TInt ii=0; ii<count; ii++)
        {
        TCdlRef ref = refs->Ref(ii);
        LayoutPack::CInstance* pack = LayoutPack::CInstance::NewLC(ref);
        if (pack->id() == aId && pack->size() == aScreenMode.PixelsTwipsAndRotation().iPixelSize && pack->zoom() == aUiZoom)
            {
            TBool styleMatchInNewPack = pack->styleHash() == aScreenMode.ScreenStyleHash();
            if (styleMatchInNewPack && !styleMatchAlreadyFound)
                {
                bestPacks->ResetAndDestroy();
                styleMatchAlreadyFound = ETrue;
                }
            if (!styleMatchAlreadyFound || styleMatchInNewPack)
                {
            	bestPacks->AppendL(pack);
            	CleanupStack::Pop(pack);
            	continue;	// skip the PopAndDestroy below
            	}
            }
        CleanupStack::PopAndDestroy(pack);
        }

    CleanupStack::PopAndDestroy(refs);

    // now sort the best layout packs in priority order and load them
    TLinearOrder<LayoutPack::CInstance> order( CompareLayoutPacks );
    bestPacks->Sort(order);
    
    count = bestPacks->Count();
    if (count)
        {
        // record the current process SID and the current CDL_Font id
        RProcess process;
        TSecureId thisProcessId = process.SecureId();
        TCdlRef cdlFontRef = CDL_Font::CustomisationInstance().Ref();
		CCdlRefs* allRefs = CCdlRefs::NewLC();
        for (TInt ii=0; ii<count; ii++)
            {
            LayoutPack::CInstance* pack = (*bestPacks)[ii];
            TInt appUid(pack->appUid());
            if(appUid == 0 || appUid == thisProcessId)
                {
                // load this layout
				CCdlRefs* packRefs = CdlExplorerUtils::CreateRefsLC(*pack, pack->contents());
				allRefs->AppendL(*packRefs);
				CleanupStack::PopAndDestroy(packRefs);
                }
            }
		CdlEngine::SetLocalStateL(*allRefs);
		CleanupStack::PopAndDestroy(allRefs);
			
        // set the screen mode for this app
        iEikonEnv->ScreenDevice()->SetScreenSizeAndRotation(aScreenMode.PixelsTwipsAndRotation());
        // update the fonts only if the CDL_Font instance has changed
        if (cdlFontRef != CDL_Font::CustomisationInstance().Ref())
            {
            // Set the CCoeFontProvider font size array
            SetConeFontSizeArrayL();
            // Update Font system
            iEikonEnv->UpdateSystemFontsL();
            }
        }

    CleanupStack::PopAndDestroy();	// CleanupLayoutPacks

    return count;
    }

TAknUiZoom CAknEnv::ResolveCurrentUiZoom()
    {
    TAknUiZoom zoom = EAknUiZoomAutomatic;
    CAknAppUi* app = (CAknAppUi*)iEikonEnv->EikAppUi();
    if(app)
        {
        zoom = app->LocalUiZoom();
        }
    if(zoom == EAknUiZoomAutomatic)
        {
        GetCurrentGlobalUiZoom(zoom);
        }
    return zoom;
    }

void CAknEnv::SetLayoutRequirementsL()
    {
    // set the requirements that loaded layouts have to meet, such as being ROM-only
	// These are ordered in terms of most frequently accessed, to speed up lookups.
    Layout_Meta_Data::RequireCustomisationL();
	AknLayoutScalable_Avkon::RequireCustomisationL();
    AknLayout::RequireCustomisationL();
    AppLayout::RequireCustomisationL();
	AknLayoutScalable_Apps::RequireCustomisationL();
    AknApacLayout::RequireCustomisationL();
    AppApacLayout::RequireCustomisationL();
    CDL_Font::RequireCustomisationL();
    SkinLayout::RequireCustomisationL();
	LayoutPack::RequireCustomisationL();
    }

void CAknEnv::AssertLayoutLoaded()
    {
    // Check that all necessary layouts have customisation instances loaded.
    // These are not needed any more since all instances are always loaded.
    // __ASSERT_ALWAYS(AknLayout::IsCustomisationStarted(), Panic(EAknPanicLayoutMissing_AknLayout));
    // __ASSERT_ALWAYS(!FeatureManager::FeatureSupported(KFeatureIdAvkonApac) || AknApacLayout::IsCustomisationStarted(), Panic(EAknPanicLayoutMissing_ApacLayout));
    }


EXPORT_C void CAknEnv::InstallAknEnvAsExtensionL(CEikonEnv* aEnv)
    {
    FeatureManager::InitializeLibL();
    CAknEnv* aknEnv = new(ELeave) CAknEnv;
    aknEnv->iCoeEnv = aEnv;
    aEnv->SetExtension(aknEnv);
    aknEnv->iFontRegistry = CAknFontRegistry::NewL();
    }

CAknFontRegistry& CAknEnv::FontRegistry() const
    {
    return *iFontRegistry;
    }

EXPORT_C TRgb CAknEnv::AvkonColor(TInt aIndex)
	{
	return TRgb::Color256(ColorRemapTable[aIndex]);
	}

void CAknEnv::SetConeFontSizeArrayL() const
    {
    RArray<TInt> logicalToPixelSizes( TCoeFont::EExtraLarge + 1 ); // Granularity chosen to be the final size
    CleanupClosePushL( logicalToPixelSizes );
    
    // Three standard text layouts are used for the middle 3 of the 5 members of the pixel size array
    // The sizes for the 2 outsize (extra small and extra large) are generated by hand using hardcoded factors

    // Append in order. Extra small and then small:
    TAknTextComponentLayout textComponentLay = AknLayoutScalable_Avkon::text_secondary();
    TAknTextLineLayout layout = textComponentLay.LayoutLine();
    TAknFontSpecification spec( layout.FontId() );
    TInt textPaneHeight =  spec.TextPaneHeight();
           
    logicalToPixelSizes.AppendL( APPLY_CONE_FONT_EXTRA_SMALL_FACTOR(textPaneHeight) );
    logicalToPixelSizes.AppendL( textPaneHeight );

    // Medium:
    textComponentLay = AknLayoutScalable_Avkon::text_primary();
    layout = textComponentLay.LayoutLine();
    spec = TAknFontSpecification( layout.FontId() );
    textPaneHeight =  spec.TextPaneHeight();

    logicalToPixelSizes.AppendL( textPaneHeight );

    // Large and then Extra Large
    textComponentLay = AknLayoutScalable_Avkon::text_title();
    layout = textComponentLay.LayoutLine();
    spec = TAknFontSpecification( layout.FontId() );
    textPaneHeight =  spec.TextPaneHeight();

    logicalToPixelSizes.AppendL( textPaneHeight ); 
    logicalToPixelSizes.AppendL( APPLY_CONE_FONT_EXTRA_LARGE_FACTOR(textPaneHeight) );
    
    // Set this into the environment
    // Propagation to all CCoeFontProviders is performed by the framework itself
    CCoeControlStaticSettings::SetLogicalToPixelFontSizesL(logicalToPixelSizes);
	
    logicalToPixelSizes.Reset();
    CleanupStack::PopAndDestroy( &logicalToPixelSizes );
    }

	// Avkon layout
EXPORT_C const AknLayout::CInstance& CAknEnv::AknLayout() const
	{
	return *iLayout;
	}
CArrayPtr<CAknSystemFont>* CAknEnv::SystemFontArray() const
    {
    return iSystemFontArray;
    }

EXPORT_C TBool CAknEnv::SplitViewActive() const
    {
    return iSplitViewActive;
    }
    
#ifdef RD_SCALABLE_UI_V2
void CAknEnv::SplitViewActive( const TBool aSplitViewActive )
    {
    iSplitViewActive = aSplitViewActive;
    }
#endif // RD_SCALABLE_UI_V2

// ---------------------------------------------------------------------------
// Check if the feature language is same.
// ---------------------------------------------------------------------------
TBool CAknEnv::IsFeatureLanguage(TInt aFeatureLanguage)
    {
    return (iFeatureLanguage == aFeatureLanguage)? ETrue : EFalse;
    }
    
void CAknEnv::ShutOrHideAppL()
    {
    CEikonEnv* eikEnv = CEikonEnv::Static();
    CAknAppUi* base = (CAknAppUi*)eikEnv->EikAppUi();
    while (base && base->ContainerAppUi())
    	{
    	base = (CAknAppUi*)base->ContainerAppUi();
    	}

    if (base && base->ExitHidesInBackground())
    	{
    	if ( !base->IsAppHiddenInBackground() )
    	    {
    	    base->ProcessCommandL(EAknCmdHideInBackground);
    	    }
    	}
    else
    	{
        RunAppShutter();
    	}
    }

// End of File
