/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#include <uikon/eikdefmacros.h>
#endif
#include "AknSgcc.h"
#include <eikspane.h>
#include <eikappui.h>
#include <eikenv.h>
#include <barsread.h>
#include <AknPriv.hrh>
#include <aknenv.h>
#include <aknconsts.h>
#include "AknDef.h"
#include <aknappui.h>
#include "AknSettingCache.h"
#include "AknLayoutConfig.h"
#include "UikonInternalPSKeys.h"
#include "AknPanic.h"

#define KLegacyScreenSize TSize(176, 208)

const TUid KAknSgcClientStaticId = { 0x101f7674 };
const TUint32 KPeninputServerUid = 0x10281855;

const TInt KStartupUnblankPriority = 10000;

enum TSgcClientFlags
	{
	EHandlingChange,
	EInAknSrv,
	ESystemFaded,
	ENeverRelinquish
	};


NONSHARABLE_CLASS(CAknSgcClientImpl) : public CAknSgcImpl
	{
public:
	CAknSgcClientImpl(RAknUiServer& aAknSrv);
    void MoveApp(TInt aAppWindowGroupId, TSgcMoveAppToWhere aWhere);

private:
	RAknUiServer& iAknSrv;
	};


NONSHARABLE_CLASS(CAknSgcClientServerInst) : public CAknSgcClient
	{
public:
	CAknSgcClientServerInst();
	~CAknSgcClientServerInst();
private: // from CAknSgcClient
    const TDesC8& DoLayoutConfigBuf();
	void ConstructL();
private:
	HBufC8* iPackedLayoutConfigBuf;
	};


EXPORT_C void MAknSgcStatusPaneRedrawCoordinator::MAknSgcStatusPaneRedrawCoordinator_Reserved_1() {}
EXPORT_C void MAknSgcStatusPaneRedrawCoordinator::MAknSgcStatusPaneRedrawCoordinator_Reserved_2() {}


inline CAknSgcClient* CAknSgcClient::Static()
	{ return static_cast<CAknSgcClient*>(CCoeEnv::Static(KAknSgcClientStaticId)); }



NONSHARABLE_CLASS(TSgcClientStatusPaneRedrawCoordinator) : public MAknSgcStatusPaneRedrawCoordinator
	{
public:
	TSgcClientStatusPaneRedrawCoordinator(RAknUiServer& aAknSrv);
	void BlockServerStatusPaneRedrawsL();
	void RedrawServerStatusPane();
	
private:
	RAknUiServer& iAknSrv;
	};

TSgcClientStatusPaneRedrawCoordinator::TSgcClientStatusPaneRedrawCoordinator(RAknUiServer& aAknSrv)
: iAknSrv(aAknSrv)
	{
	}

void TSgcClientStatusPaneRedrawCoordinator::BlockServerStatusPaneRedrawsL()
	{
	}

void TSgcClientStatusPaneRedrawCoordinator::RedrawServerStatusPane()
	{
	iAknSrv.RedrawServerStatusPane();
	}



EXPORT_C void CAknSgcClient::CreateL()
	{
	CAknSgcClient* self=CAknSgcClient::Static();
	if (!self)
		{
		RThread thread;
		if (thread.Name() == _L("akncapserver"))
			self = new(ELeave) CAknSgcClientServerInst();  // CCoeEnv takes ownership immediately
		else
			self = new(ELeave) CAknSgcClient(); // CCoeEnv takes ownership immediately
		self->ConstructL();
		}
	}

CAknSgcClient::~CAknSgcClient()
	{
	delete iImpl;
	delete iLayoutConfig;
	if (!iFlags[EInAknSrv])
		{
    	DoStartupUnblank();
		// iSpRedrawCoord and iAknSrv are only owned/opened if this object
		// is not running in the AknSrv process (see ConstructL()).
		delete static_cast<TSgcClientStatusPaneRedrawCoordinator*>(iSpRedrawCoord);
		iAknSrv.Close();
		}
	delete iDrawSync;
	}

void CAknSgcClient::ClearHandlingChangeFlag(TAny* aThis)
	{
	static_cast<CAknSgcClient*>(aThis)->iFlags.Clear(EHandlingChange);
	}

EXPORT_C void CAknSgcClient::HandleChangeL()
	{
	CAknSgcClient* self = Static();
	if (self)
		self->DoHandleChangeL();
	}

void CAknSgcClient::DoHandleChangeL()
	{
	if (iFlags[EInAknSrv])
		return;

	CAknAppUi* topAppUi = iAvkonAppUi;

	if (!topAppUi)
		return;

	if (iFlags[EHandlingChange])
		return;
	iFlags.Set(EHandlingChange);
	CleanupStack::PushL(TCleanupItem(ClearHandlingChangeFlag, this));

	TInt spLayout = 0;
	TInt spFlags = 0;
	TBitFlags appFlags;
	TInt screenMode = KAknScreenModeUnset;
	SetLegacyOrientationAndScreenModeAppUiFlags(appFlags, screenMode, topAppUi);
	appFlags.Assign(EFullScreen, topAppUi->IsFullScreenApp());
	TBool partialFg = topAppUi->IsPartialForeground();
	TBool foreground = topAppUi->IsForeground();

	// loop over app UIs from most embedded to base app
	for (CAknAppUiBase* appUi = static_cast<CAknAppUiBase*>(topAppUi); appUi; appUi = static_cast<CAknAppUiBase*>(appUi->ContainerAppUi()))
		{
		CEikStatusPane* sp = StatusPane(appUi);
		if (sp && !spLayout)
			{
			spLayout = sp->CurrentLayoutResId();
			spFlags = sp->Flags();
			}

		if (appUi != topAppUi)
			{
			SetLegacyOrientationAndScreenModeAppUiFlags(appFlags, screenMode, appUi);

			partialFg = (foreground || partialFg) && !appFlags[EFullScreen];
			foreground = EFalse;
			appFlags.Assign(EFullScreen, appFlags[EFullScreen] || appUi->IsFullScreenApp());

			SetAppUiForegroundL(appUi, foreground);
			SetAppUiPartialFgL(appUi, partialFg);
			}
		}

	if (spLayout != iSpLayout || 
	    !(appFlags == iAppFlags) || 
	    spFlags != iSpFlags ||
	    screenMode != iAppScreenMode)
		{
		iSpLayout = spLayout;
		iSpFlags = spFlags;
		iAppFlags = appFlags;
		iAppScreenMode = screenMode;
		User::LeaveIfError(iAknSrv.SetSgcParams(iEikonEnv->RootWin().Identifier(), appFlags, spLayout, spFlags, screenMode));
		}

	CleanupStack::PopAndDestroy();
	}

CAknSgcClient::CAknSgcClient()
: CCoeStatic(KAknSgcClientStaticId), iCoeEnv(CCoeEnv::Static())
	{
	}

void CAknSgcClient::BaseConstructL()
	{
	RProcess process;
	if( process.SecureId() == KPeninputServerUid )
	    {
	    iFlags.Set(ENeverRelinquish);
	    }
	
	iDrawSync = CAknDrawSynchronizer::NewL();
	iLayoutConfig = new(ELeave) CAknLayoutConfig;
	}
	
void CAknSgcClient::ConstructL()
	{
	BaseConstructL();
	
	User::LeaveIfError(iAknSrv.Connect());
	iSpRedrawCoord = new(ELeave) TSgcClientStatusPaneRedrawCoordinator(iAknSrv);
	SetImpl(new(ELeave) CAknSgcClientImpl(iAknSrv));

    if(iAvkonEnv->HasBlank())
        StartupBlankL();

	HBufC8* packedBuf;
	if (iAknSrv.Handle())
		{
		packedBuf = iAknSrv.GetPackedConfigL();
		}
	else
		{	// eiksrv will end up here
		packedBuf = iLayoutConfig->CreatePackedBufL();
		}
	iLayoutConfig->ConstructL(packedBuf);
	}

CEikStatusPane* CAknSgcClient::StatusPane(CEikAppUi* aAppUi)
	{
	MEikAppUiFactory* factory = iEikonEnv->AppUiFactory(*aAppUi);
	if (factory)
		return factory->StatusPane();
	else
		return NULL;
	}

void CAknSgcClient::SetAppUiForegroundL(CAknAppUiBase* aAppUi, TBool aForeground)
	{
	if (!COMPARE_BOOLS(aAppUi->IsForeground(), aForeground))
		SimulateWsEventL(aAppUi, aForeground ? EEventFocusGained : EEventFocusLost);
	}

void CAknSgcClient::SetAppUiPartialFgL(CAknAppUiBase* aAppUi, TBool aPartialFg)
	{
	if (!COMPARE_BOOLS(aAppUi->IsPartialForeground(), aPartialFg))
		SimulateWsEventL(aAppUi, aPartialFg ? KEikPartialForeground : KEikClearPartialForegroundState);
	}

void CAknSgcClient::SimulateWsEventL(CEikAppUi* aAppUi, TInt aEventId)
	{
	TWsEvent event;
	event.SetType(aEventId);
	event.SetHandle(0);
#if (defined(SYMBIAN_SUPPORT_UI_FRAMEWORKS_V1) || defined(__SERIES60_27__) || defined(__SERIES60_28__)) 
	static_cast<CCoeAppUiBase*>(aAppUi)->HandleWsEventL(event, NULL);	
#else 
	static_cast<CCoeAppUi*>(aAppUi)->HandleWsEventL(event, NULL);
#endif 
	}

EXPORT_C RAknUiServer* CAknSgcClient::AknSrv()
	{
	CAknSgcClient* self = Static();
	if (self)
		return &self->iAknSrv;
	else
		return NULL;
	}

EXPORT_C void CAknSgcClient::SetStatusPaneRedrawCoordinator(MAknSgcStatusPaneRedrawCoordinator* aSpRedrawCoord)
	{
	CAknSgcClient* self = Static();
	if (self)
		{
		ASSERT(!self->iSpRedrawCoord || !aSpRedrawCoord);
		self->iSpRedrawCoord = aSpRedrawCoord;
		}
	}

EXPORT_C void CAknSgcClient::BlockServerStatusPaneRedrawsL()
	{
	}

EXPORT_C void CAknSgcClient::RedrawServerStatusPane()
	{
	CAknSgcClient* self = Static();
	if (self && self->iSpRedrawCoord)
		self->iSpRedrawCoord->RedrawServerStatusPane();
	}

EXPORT_C CAknDrawSynchronizer* CAknSgcClient::DrawSynchronizer()
	{
	CAknSgcClient* self = Static();
	if (self)
		return self->iDrawSync;
	else
		return NULL;
	}

EXPORT_C void CAknSgcClient::PrepareForAppExit()
	{
	CAknSgcClient* self = Static();
	if (self)
		self->DoPrepareForAppExit();
	}

void CAknSgcClient::DoPrepareForAppExit()
	{
	if (!iFlags[EInAknSrv])
		{
		iAknSrv.PrepareForAppExit(iEikonEnv->RootWin().Identifier());
		}
	}

EXPORT_C void CAknSgcClient::SetSystemFaded(TBool aFade)
	{
	CAknSgcClient* self = Static();
	if (self)
		self->DoSetSystemFaded(aFade);
	}

EXPORT_C TBool CAknSgcClient::IsSystemFaded()
	{
	CAknSgcClient* self = Static();
	if (self)
		return self->DoIsSystemFaded();
	else
		return EFalse;
	}

void CAknSgcClient::DoSetSystemFaded(TBool aFade)
	{
	if (iFlags[EInAknSrv])
		{
		if (!COMPARE_BOOLS(iFlags[ESystemFaded], aFade))
			{
			if (aFade)
				{
				RedrawServerStatusPane();
				}
			}
		iEikonEnv->WsSession().SetSystemFaded(aFade);
		iFlags.Assign(ESystemFaded, aFade);	
		}
	else
		{
		iAknSrv.SetSystemFaded(aFade);
		}
	}

TBool CAknSgcClient::DoIsSystemFaded() const
	{
	if (iFlags[EInAknSrv])
		{
		return iFlags[ESystemFaded];
		}
	else
		{
		TBool fade;
		iAknSrv.IsSystemFaded(fade);
		return fade;
		}
	}

void CAknSgcClient::SetLegacyOrientationAndScreenModeAppUiFlags(TBitFlags& aAppFlags, TInt& aScreenMode, CAknAppUiBase* aAppUi)
	{
	if (!aAppFlags[EFullScreen] && aAppUi->IsFullScreenApp())
		{
	//	aAppFlags.Assign(ELegacyLayout, !aAppUi->IsLayoutAwareApp()); // Fix Me !!
		CAknAppUiBase::TAppUiOrientation r = aAppUi->Orientation();
		aAppFlags.Assign(EOrientationSpecified, r != CAknAppUiBase::EAppUiOrientationUnspecified);
		aAppFlags.Assign(EOrientationLandscape, r == CAknAppUiBase::EAppUiOrientationLandscape);
		aScreenMode = aAppUi->ScreenMode();
		}
	}

EXPORT_C TPixelsTwipsAndRotation CAknSgcClient::PixelsAndRotation()
	{
	CAknSgcClient* self = Static();
	if (self)
		{
		TBitFlags& flags = self->iAppFlags;
    	TInt mode = self->iAppScreenMode;
		return self->DoCalculatePixelsAndRotation(flags[EFullScreen], flags[ELegacyLayout], flags[EOrientationSpecified], flags[EOrientationLandscape], mode);
		}
	else
		{
		TPixelsTwipsAndRotation r;
		CEikonEnv::Static()->ScreenDevice()->GetDefaultScreenSizeAndRotation(r);
		return r;
		}
	}

inline TBool AspectIsLandscape(const TPixelsTwipsAndRotation& aR)
	{
	return aR.iPixelSize.iWidth > aR.iPixelSize.iHeight;
	}

EXPORT_C TPixelsTwipsAndRotation CAknSgcClient::CalculatePixelsAndRotation(TBool aFullScreen, TBool aLegacyApp, TBool aAppOrientationSpecified, TBool aAppOrientationLandscape)
	{
	CAknSgcClient* self = Static();
	if (self)
		{
		return self->DoCalculatePixelsAndRotation(aFullScreen, aLegacyApp, aAppOrientationSpecified, aAppOrientationLandscape, KAknScreenModeUnset);
		}
	else
		{
		TPixelsTwipsAndRotation r;
		CEikonEnv::Static()->ScreenDevice()->GetDefaultScreenSizeAndRotation(r);
		return r;
		}
	}

TPixelsTwipsAndRotation CAknSgcClient::DoCalculatePixelsAndRotation(TBool aFullScreen, TBool aLegacyApp, TBool aAppOrientationSpecified, TBool aAppOrientationLandscape, TInt aAppScreenMode)
	{
	CAknLayoutConfig::TScreenMode screenMode = DoCalculateScreenMode(aFullScreen, aAppOrientationSpecified, aAppOrientationLandscape, aAppScreenMode);
	TPixelsTwipsAndRotation r = screenMode.PixelsTwipsAndRotation();

	// legacy mode
	if (aLegacyApp && aFullScreen)
		r.iPixelSize = KLegacyScreenSize;

	return r;
	}
	
EXPORT_C CAknLayoutConfig::TScreenMode CAknSgcClient::ScreenMode()
	{
	CAknSgcClient* self = Static();
	__ASSERT_ALWAYS(self, Panic(EAknPanicSgccNull));
	TBitFlags& flags = self->iAppFlags;
	TInt mode = self->iAppScreenMode;
	return self->DoCalculateScreenMode(flags[EFullScreen], flags[EOrientationSpecified], flags[EOrientationLandscape], mode);
	}

EXPORT_C CAknLayoutConfig::TScreenMode CAknSgcClient::CalculateScreenMode(TBool aFullScreen, TBool aAppOrientationSpecified, TBool aAppOrientationLandscape)
	{
	return CalculateScreenMode(aFullScreen, aAppOrientationSpecified, aAppOrientationLandscape, KAknScreenModeUnset);
	}

EXPORT_C CAknLayoutConfig::TScreenMode CAknSgcClient::CalculateScreenMode(TBool aFullScreen, TBool aAppOrientationSpecified, TBool aAppOrientationLandscape, TInt aAppScreenMode)
	{
	CAknSgcClient* self = Static();
	__ASSERT_ALWAYS(self, Panic(EAknPanicSgccNull));
	return self->DoCalculateScreenMode(aFullScreen, aAppOrientationSpecified, aAppOrientationLandscape, aAppScreenMode);
	}

CAknLayoutConfig::TScreenMode CAknSgcClient::DoCalculateScreenMode(TBool aFullScreen, TBool aAppOrientationSpecified, TBool aAppOrientationLandscape, TInt aAppScreenMode)
	{
	if (!aFullScreen)
		{
		// return current screen mode for partial screen apps
		return iLayoutConfig->ScreenModes().Find(iEikonEnv->ScreenDevice()->CurrentScreenMode());
		}

    if (aAppScreenMode != KAknScreenModeUnset)
		{
		// return current screen mode set by the app
		return iLayoutConfig->ScreenModes().Find(aAppScreenMode);
		}

	TInt hwStateNum = iAvkonEnv->SettingCache().HardwareLayoutState();
	CAknLayoutConfig::THardwareState hwScreen = iLayoutConfig->HardwareStates().Find(hwStateNum);

    TInt mode;
    TInt orientation = iAvkonEnv->SettingCache().PreferredOrientation();
    if ( orientation == EPreferredOrientationNormal )
        {
        mode = hwScreen.ScreenMode();
        }
    else
        {
        mode = hwScreen.AlternateScreenMode();
        }

	CAknLayoutConfig::TScreenMode screenMode = iLayoutConfig->ScreenModes().Find(mode);
	
	if (aAppOrientationSpecified &&
		!COMPARE_BOOLS(aAppOrientationLandscape, AspectIsLandscape(screenMode.PixelsTwipsAndRotation())))
		{
        if ( orientation == EPreferredOrientationNormal )
            {
    		// App rotation specificied but orientation is different to hw state
	    	// so use alternate mode
            mode = hwScreen.AlternateScreenMode();
            }
        else 
            {
            mode = hwScreen.ScreenMode();
            }
		return iLayoutConfig->ScreenModes().Find(mode);
		}
		
	return screenMode;
	}

EXPORT_C void CAknSgcClient::SetKeyBlockMode(TAknKeySoundOpcode aMode)
    {
	CAknSgcClient* self = Static();
	if (self)
        {
        self->DoSetKeyBlockMode(aMode);
        }
    }

EXPORT_C void CAknSgcClient::SetKeyboardRepeatRate(TAknDefaultKeyboardRepeatRate aRate)
    {
	CAknSgcClient* self = Static();
	if (self)
        {
        self->DoSetKeyboardRepeatRate(aRate);
        }
    }

EXPORT_C TInt CAknSgcClient::CurrentStatuspaneResource()
    {
	CAknSgcClient* self = Static();
	if (self)
        {
        return self->DoAskCurrentStatuspaneResource();
        }
        
    return 0; // not able to resolve
    }
    

TInt CAknSgcClient::DoAskCurrentStatuspaneResource()
    {
    if (CEikStatusPaneBase::Current())
        {
        return CEikStatusPaneBase::Current()->CurrentLayoutResId();
        }
    else 
        return iAknSrv.StatusPaneResourceId();   
    }

void CAknSgcClient::DoSetKeyBlockMode(TAknKeySoundOpcode aMode)
    {
	if (iFlags[EInAknSrv])
		{
        TRawEvent event;
        TAknKeySoundOpcode opcode = EEnableKeyBlock; // default
	    if (aMode == ENoKeyBlock)
		    {
		    opcode = EDisableKeyBlock;
		    }
	    event.Set((TRawEvent::TType)opcode);
        iEikonEnv->WsSession().SimulateRawEvent(event);		
		}
	else
		{
		iAknSrv.SetKeyblockMode(aMode);
		}
    }

void CAknSgcClient::DoSetKeyboardRepeatRate(TAknDefaultKeyboardRepeatRate aRate)
    {
	if (iFlags[EInAknSrv])
		{
        TInt repeatRate = KAknStandardKeyboardRepeatRate; // default 
        if (aRate == EAknEditorDefaulRepeatRate)
            {
            repeatRate = KAknEditorKeyboardRepeatRate;
            }
        iEikonEnv->WsSession().SetKeyboardRepeatRate(KAknKeyboardRepeatInitialDelay,repeatRate);
        }
	else
		{
		iAknSrv.SetKeyboardRepeatRate(aRate);
		}
    }

void CAknSgcClient::RelinquishPriorityToForegroundAppLC(TBool aIsForeground)
	{
	CAknSgcClient* self = Static();
	if (self)
		self->DoRelinquishPriorityToForegroundAppLC(aIsForeground);
	}

void RestorePriority(TAny* aPriority)
    {
    if (!aPriority)
        return;
	RThread myThread;
	TProcessPriority priority = *(TProcessPriority*)&aPriority;
	myThread.SetProcessPriority(priority);
    }

void CAknSgcClient::DoRelinquishPriorityToForegroundAppLC(TBool aIsForeground)
	{
	RThread myThread;
	TProcessPriority priority = myThread.ProcessPriority();

	if( IsSystemFaded() )
		{
		// Solution for EKKG-7RQ9U8:
		// If the system is faded we have a popup on screen.
		// Get the process behind the foreground process. 
		TApaTask task = TApaTaskList(iEikonEnv->WsSession()).FindByPos(1);

		// Check if this application is next behind the foreground app.
		if( task.Exists() && myThread.Id() == task.ThreadId())
			{
			// Act as if we were foreground because some portion of the app might be visible.
			// The actual foreground application might only be displaying the popup and therefore
			// would not update the entire screen. 	
			aIsForeground = ETrue;
			}
		}

	if (!aIsForeground && priority > EPriorityBackground && !iFlags[ENeverRelinquish] )
	    {
	    // App is not visible, but has priority higher than background
	    // Temporarily move it to background priority
        CleanupStack::PushL(TCleanupItem(RestorePriority, (TAny*)priority));
        iAknSrv.RelinquishPriorityToForegroundApp();
	    }
	else if (aIsForeground && priority < EPriorityForeground)
	    {
	    // App is visible, but has priority lower than foreground
	    // Temporarily move it to foreground priority
        CleanupStack::PushL(TCleanupItem(RestorePriority, (TAny*)priority));
        myThread.SetProcessPriority(EPriorityForeground);
	    }
	else
	    {
	    // App has correct priority
	    // push a dummy cleanup item onto the cleanup stack
        CleanupStack::PushL(TCleanupItem(RestorePriority, NULL));
	    }
	}

EXPORT_C CAknLayoutConfig& CAknSgcClient::LayoutConfig()
	{
	CAknSgcClient* self = Static();
	__ASSERT_ALWAYS(self && self->iLayoutConfig, Panic(EAknPanicSgccLayoutConfigNull));
	return *self->iLayoutConfig;
	}

EXPORT_C const TDesC8& CAknSgcClient::LayoutConfigBuf()
	{
	CAknSgcClient* self = Static();
	if (!self)
		return KNullDesC8;
	else
		return self->DoLayoutConfigBuf();
	}

const TDesC8& CAknSgcClient::DoLayoutConfigBuf()
	{
	return KNullDesC8;
	}

void CAknSgcClient::StartupBlankL()
	{
	// Only use blanker when this app is focused, ie foreground
	if (iEikonEnv->WsSession().GetFocusWindowGroup() == iEikonEnv->RootWin().Identifier())
		{
	    iStartupBlank = CIdle::New(KStartupUnblankPriority);
	    iStartupBlank->Start(TCallBack(StartupUnblank, this));
		User::LeaveIfError(iAknSrv.BlankScreen());
		}
	}

TInt CAknSgcClient::StartupUnblank(TAny* aThis)
	{
	((CAknSgcClient*)aThis)->DoStartupUnblank();
	return 0;
	}

void CAknSgcClient::DoStartupUnblank()
	{
    if (iStartupBlank)
    	{
		iAknSrv.UnblankScreen();
		delete iStartupBlank;
		iStartupBlank = NULL;
    	}
	}

EXPORT_C void CAknSgcClient::MoveApp(TInt aAppWindowGroupId, TSgcMoveAppToWhere aWhere)
	{
	CAknSgcClient* self = Static();
	if (self && self->iImpl)
		self->iImpl->MoveApp(aAppWindowGroupId, aWhere);
	}

EXPORT_C void CAknSgcClient::SetImpl(CAknSgcImpl* aImpl)
	{
	CAknSgcClient* self = Static();
	if (self)
		{
		delete self->iImpl;
		self->iImpl = aImpl;
		}
	}

//
// CAknSgcClientServerInst
//
CAknSgcClientServerInst::CAknSgcClientServerInst()
	{
	iFlags.Set(EInAknSrv);
	iFlags.Set(ENeverRelinquish);
	}

CAknSgcClientServerInst::~CAknSgcClientServerInst()
	{
	delete iPackedLayoutConfigBuf;
	}

const TDesC8& CAknSgcClientServerInst::DoLayoutConfigBuf()
	{
	return *iPackedLayoutConfigBuf;
	}

void CAknSgcClientServerInst::ConstructL()
	{
	BaseConstructL();
	
	iPackedLayoutConfigBuf = iLayoutConfig->CreatePackedBufL();
	iLayoutConfig->ConstructL(iPackedLayoutConfigBuf->AllocL());
	}


//
// CAknSgcClientImpl
//
CAknSgcClientImpl::CAknSgcClientImpl(RAknUiServer& aAknSrv)
: iAknSrv(aAknSrv)
	{
	}
	
void CAknSgcClientImpl::MoveApp(TInt aAppWindowGroupId, TSgcMoveAppToWhere aWhere)
	{
	iAknSrv.MoveAppInZOrder(aAppWindowGroupId, aWhere);
	}


// End of File
