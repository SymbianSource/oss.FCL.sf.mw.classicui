/*
* Copyright (c) 2004-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Notifier server app wrapper implementation. 
*
*/

#include <coemain.h>
#include <aknenv.h>
#include <apgwgnam.h> 
#include <apgtask.h>
#include <eiknotapi.h>
#include <AknCapServerClient.h>
#include <aknnotewrappers.h>
#include <AknCapServerDefs.h>

#include <avkondomainpskeys.h>
#include <e32property.h>

#include "AknNotiferAppServerApplication.h" 
#include "AknNotifierAppServer.h"
#include "AknNotifierControllerUtilities.h"
#include "AknNotiferAppServerApplicationInterface.h"

#include <AknMediatorFacade.h>
#include <AknNotifyStd.h>
#include <SecondaryDisplay/AknSecondaryDisplayDefs.h>
#include <aknglobalpopupprioritycontroller.h>

//---- Awkward, but declaring base classes otherwise in Akncapserver entry would break app fw.
class CAknCapAppServerAppUiInterface : 
    public CAknNotifierAppServerAppUi, 
    public MAknCapServerInterface
    {
    };
//----

//----------------------------------
// Application
//----------------------------------
class CAknAsyncAppFader: public CBase
    {
public:
    CAknAsyncAppFader(CAknNotifierAppServerAppUi* aAppUi):iAppUi(aAppUi)
        {}
    ~CAknAsyncAppFader()
        {
        delete iIdle;
        }   
    TBool IsActive() 
        {
        return iIdle != 0;
        }
    void StartL(TBool aFade);
    void Cancel()
        {
        delete iIdle;
        iIdle = 0;
        }
    static TInt BaseCall(TAny* aThis);
    
    TBool iFade;
    CAknNotifierAppServerAppUi* iAppUi; // not owned
    CIdle* iIdle;   
    };

void CAknAsyncAppFader::StartL(TBool aFade)
    {
    if(!iIdle)
        {
        iFade = aFade;
        iIdle = CIdle::NewL(CActive::EPriorityStandard);
        iIdle->Start(TCallBack(BaseCall,this));
        }
    }

TInt CAknAsyncAppFader::BaseCall(TAny* aThis)
    {
    CAknAsyncAppFader* me = (CAknAsyncAppFader*) aThis;
    TRAPD(err, me->iAppUi->BaseCallFadeL(me->iFade));
    return err;
    }

    
class CAknNotifierManagerExtension: public CBase
    {
public:
    CAknNotifierManagerExtension()
        {
        iKeyLock = EKeyguardNotActive;    
        }
        
    ~CAknNotifierManagerExtension()
        {
        iAppsKeyClient.Close();
        delete iController;
        delete iAsynchFader;
        }
    TInt ConnectAndSendAppsKeySuppress(TBool aSuppress);
    MEikSrvNotifierManager* iManager; // Not owned
    CAknNotifierControllerUtility* iController;
    CAknAsyncAppFader* iAsynchFader;
    TBool iEikServBlocked;
    TInt iKeyLock;
    
private:
    RAknUiServer iAppsKeyClient;
    };

TInt CAknNotifierManagerExtension::ConnectAndSendAppsKeySuppress(TBool aSuppress)
    {
    return iAppsKeyClient.ConnectAndSendAppsKeySuppress(aSuppress);
    }

EXPORT_C CAknNotifierAppServerApplication::CAknNotifierAppServerApplication()
    {
    }
   
EXPORT_C CAknNotifierAppServerApplication::~CAknNotifierAppServerApplication()
    {
    }

EXPORT_C void CAknNotifierAppServerApplication::NewAppServerL(CApaAppServer*& aAppServer)
    { 
    // Default implementation just creates instance of server, it is ok to use this if 
    // old style notifier libraries are loaded on demand later.
    CAknNotifierAppServer* server = new (ELeave) CAknNotifierAppServer();
    aAppServer=&*server;
    }
    
EXPORT_C CApaDocument* CAknNotifierAppServerApplication::CreateDocumentL() 
    {
    return new (ELeave) CAknNotifierAppServerDocument(*this);
    }

CEikAppUi* CAknNotifierAppServerDocument::CreateAppUiL()
    {
    return new (ELeave) CAknNotifierAppServerAppUi();
    }

 
//----------------------------------
// AppUi
//----------------------------------
EXPORT_C CAknNotifierAppServerAppUi::CAknNotifierAppServerAppUi()
    {
    SetFullScreenApp(EFalse);
    }
 
EXPORT_C CAknNotifierAppServerAppUi::~CAknNotifierAppServerAppUi()
    {
    delete iExtension;
    }
 
EXPORT_C void CAknNotifierAppServerAppUi::ConstructL()
    {
    iExtension = new (ELeave) CAknNotifierManagerExtension();
    iExtension->iAsynchFader = new (ELeave) CAknAsyncAppFader(this);

    TInt flags = EStandardApp | ENoScreenFurniture | ENonStandardResourceFile | EAknEnableSkin | 
        EAknEnableMSK | EAknSingleClickCompatible;

    CAknAppUi::BaseConstructL(flags);
 
    // fetch name and hide 
    CCoeEnv* coe = CCoeEnv::Static();
    
    AknGlobalPopupPriorityController::EnablePriorityControlL();
    AknGlobalPopupPriorityController::AllowGlobalPopups(ETrue);

    CApaWindowGroupName* name = CApaWindowGroupName::NewLC(
        coe->WsSession(),coe->RootWin().Identifier());
        
    name->SetHidden(ETrue);
    RThread me;
    name->SetCaptionL(me.Name());
    name->SetAppUid(Document()->Application()->AppDllUid());
    name->SetWindowGroupName(coe->RootWin());

    CleanupStack::PopAndDestroy();
    
    // and send to background
    TApaTask task = TApaTask(coe->WsSession());
    task.SetWgId(coe->RootWin().Identifier());
    task.SendToBackground();
    
    // Creates window controller for system wide notifier hiding & cancellation       
    // value given is used to determine this app position if several wgs with same    
    // priority exist.                                                               
    SetOrdinalPositionL(0); 
    }
 
EXPORT_C void CAknNotifierAppServerAppUi::HandleCommandL(TInt aCommand)
    {
    if (aCommand == EEikCmdExit)
        {
        CAknEnv::Static()->RunAppShutter();
        }
    }
    
EXPORT_C TKeyResponse CAknNotifierAppServerAppUi::HandleKeyEventL(const TKeyEvent& /*aKeyEvent*/,
    TEventCode /*aType*/)
    {
    return EKeyWasConsumed;    
    }
 
EXPORT_C TInt CAknNotifierAppServerAppUi::SuppressAppSwitching(TBool aSuppress)
    {
    
    // Get key lock's status
    if (KErrNone !=  RProperty::Get( KPSUidAvkonDomain, KAknKeyguardStatus ,
                        iExtension->iKeyLock ) )
        {
    	iExtension->iKeyLock = EKeyguardNotActive;
        }
    
    RThread me;
    if (me.Name() == KAknCapServerThreadName) 
         {
         TRAPD(err, ((CAknCapAppServerAppUiInterface*)iAvkonAppUi)->SuppressAppSwitchingL(
             aSuppress ? EAknAppsKeyBlockAddCount : EAknAppsKeyBlockDecreaseCount, 0))
         return err;
         }
    else if (iExtension) 
         {
         return iExtension->ConnectAndSendAppsKeySuppress(aSuppress);    
         }
    
    return KErrNotReady; 
    }

    
EXPORT_C void CAknNotifierAppServerAppUi::SetManager(MEikSrvNotifierManager* aManager)
    {
    if (iExtension)
        {
        iExtension->iManager = aManager;
        }
    }
    
EXPORT_C MEikSrvNotifierManager* CAknNotifierAppServerAppUi::Manager()
    {
    // If non standard manager is set, return it, othewise return default ie. server.
    if (iExtension && iExtension->iManager )
        {
        return iExtension->iManager;
        }
    else 
        {
        return (CAknNotifierAppServer*) CEikonEnv::Static()->AppServer();
        }    
    }

EXPORT_C void CAknNotifierAppServerAppUi::SetOrdinalPositionL(TInt aPosition)
    {
    if (iExtension)
        {
        delete iExtension->iController;
        iExtension->iController = 0;
        iExtension->iController = new (ELeave) CAknNotifierControllerUtility(aPosition);
        }
    }

EXPORT_C void CAknNotifierAppServerAppUi::SetFadedL(TBool aFade)
    {

    // Don't unfade the screen when no global popup control in stack.
    // let the following window is unfaded during focus change in windows group.
    // If key guard locked, always fade/unfade.
    if (aFade || (iExtension->iKeyLock != EKeyguardNotActive))
      {
      CAknAppUi::SetFadedL(aFade);
      }
    return; 
    }

void CAknNotifierAppServerAppUi::BaseCallFadeL(TBool aFade)
    {
    CAknAppUi::SetFadedL(aFade);
    }

EXPORT_C TBool& CAknNotifierAppServerAppUi::EikSrvBlocked()
    {
    return iExtension->iEikServBlocked;
    }

EXPORT_C TErrorHandlerResponse CAknNotifierAppServerAppUi::HandleError(
    TInt aError, 
    const SExtendedError& /*aExtErr*/,  
    TDes& /*aErrorText*/, 
    TDes& /*aContextText*/ )
    {
    HBufC* buf = 0;
    TRAPD(err, HandleErrorL(aError, &buf, EFalse));

    if (!err && buf->Length() > 0)
        {
        CAknWarningNote* note = new CAknWarningNote;
        if (!note)
            {
            err = KErrNoMemory;
            }
        else 
            {
            // secondary display needs to be informed about the error note
            TRAP( err, note->PublishDialogL( EAknErrorNote, KAknSecondaryDisplayCategory ));
            if (!err)
                {
                CAknMediatorFacade* coverData = AknMediatorFacade(note);
                if(coverData)
                    {
                    SAknIntegerUpdate s = 
                        {
                        EAknTrappedError,
                        aError 
                        };
                    TPckg<SAknIntegerUpdate> pck(s);
                    coverData->BufStream() << pck;
                    TRAP_IGNORE( coverData->BufStream().CommitL() );
                    }            
                }
            TRAP(err, note->ExecuteLD(buf->Des()));
            }
        }

    delete buf;

    if ( !err )
        {
        return(ENoDisplay); // Error handled proper way.
        }
    
    return(EErrorNotHandled); // Error not handled, let EIKENV handle the error.
    }

EXPORT_C void CAknNotifierAppServerAppUi::HandleSystemEventL(const TWsEvent& aEvent)
    {
    switch (*(TApaSystemEvent*)(aEvent.EventData()))
        {
    case EApaSystemEventBroughtToForeground:
        { // ignore this event as it causes undesired effects on applications underneath
        break;
        }
    default:
        CAknAppUi::HandleSystemEventL(aEvent);
        }

    return;
    }

CAknNotifierControllerUtility* CAknNotifierAppServerAppUi::NotifierControllerUtility()
    {
    if (iExtension)
        {
        return iExtension->iController;
        }
    
    return 0;
    }

// End of file
