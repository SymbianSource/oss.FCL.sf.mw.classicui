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
* Description:  Server side implementation of AVKON System
*                Graphics Coordinator.
*
*/


#include "AknEikSgcs.h"
#include <eikenv.h>
#include "eiksrvsp.h"
#include <AknSgcc.h>
#include <aknenv.h>
#include <AknDef.h>
#include <aknappui.h>
#include <e32property.h>
#include <UikonInternalPSKeys.h>
#include <avkondomainpskeys.h>
#include <AknSettingCache.h>
#include "AknCapServerEntry.h"
#include <aknconsts.h>
#include "winchangemonitor.h"
#include "akncapserverdebug.h"
#include "akncompaif.h"

#include <AknsConstants.h>
#include <AknsUtils.h>
#include <AknIconUtils.h>
#include <AknUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include "avkoninternalpskeys.h"
#include <layoutmetadata.cdl.h>
#include <AknTaskList.h>
#ifdef RD_UI_TRANSITION_EFFECTS_LAYOUT_SWITCH
#include <akntranseffect.h>
#include <akntransitionutils.h>
#endif

#include <layoutpack.cdl.h>
#include <CdlRefs.h>
const TInt KCdlEComInterfaceId = 0x101f8243;

const TInt KLayoutChangeTimeout = 2000000; // 2s
const TInt KWgStatesGranularity = 4;
const TInt KRelinquishedThreadListGranularity = 4;
const TInt KRemoveBlankDelay = 200000; // 0.2s
// Drawing is slower when transparency is enabled. The time needs to be
// big enough to account for slowest drawing application.
const TInt KRemoveBlankDelayTransparency = 1500000; // 1.5s

// 4s should be enough for foreground app's operations to complete.
const TInt KRestoreThreadPriorityDelay = 4000000; 

// Screensaver application UID
const TUid KScreensaverAppUid = { 0x100056CF };

// Read pass policy
_LIT_SECURITY_POLICY_PASS(KPassReadPolicy);    

// Policy requiring write device data capability.
_LIT_SECURITY_POLICY_C1(KWriteDDPolicy, ECapabilityWriteDeviceData);

enum TWgStateFlags
    {
    EWgStateFullScreen,
    EWgStatePartialForeground,
    EWgStateUnderstandsPartialForeground,
    EWgStateLegacyLayout,
    EWgStateOrientationSpecified,
    EWgStateOrientationLandscape
    };

enum TSetLayoutBlankStep
	{
	ESetLayoutBlankBeforeLayoutLoad,
	ESetLayoutBlankBetweenLayoutLoadAndScreenRotate,
	ESetLayoutBlankAfterScreenRotate,
	ESetLayoutBlankNever
	};

NONSHARABLE_CLASS(CAknSgcServerImpl) : public CAknSgcImpl
	{
public:
	CAknSgcServerImpl(CEikSgcServer* aServer);
    void MoveApp(TInt aAppWindowGroupId, TSgcMoveAppToWhere aWhere);
    
private:
	CEikSgcServer* iServer;
	};


class CLayoutChangeCallBack : public CActive
    {
public:
    CLayoutChangeCallBack(CEikSgcServer* aSgc);
    void ConstructL();
    ~CLayoutChangeCallBack();
    
    void RestartTimerL();

private:
    void DoCancel();
    void RunL();

    static TInt ThreadFunc(TAny* aStat);

    static TInt TimeoutCallback(TAny* aThis);
    void DoTimeout();

private:
    CEikSgcServer* iSgc;
    RThread iThread;
    TThreadId iMain;
    CPeriodic* iTimeout;
    };

CLayoutChangeCallBack::CLayoutChangeCallBack(CEikSgcServer* aSgc)
: CActive(CActive::EPriorityLow), iSgc(aSgc), iMain(RThread().Id())
    {
    CActiveScheduler::Add(this);
    }

void CLayoutChangeCallBack::ConstructL()
    {
    // Create the thread.
    User::LeaveIfError(iThread.Create(KNullDesC, ThreadFunc, 0x400, NULL, this));
    iThread.SetPriority(EPriorityAbsoluteBackground);
    
    // Set the active status & start the thread.
    iStatus = KRequestPending;
    SetActive();
    iThread.Resume();
    
    RestartTimerL();
    }
    
void CLayoutChangeCallBack::RestartTimerL()
    {
    delete iTimeout;
    iTimeout = NULL;
    iTimeout = CPeriodic::NewL(CActive::EPriorityStandard);
    iTimeout->Start(KLayoutChangeTimeout, KLayoutChangeTimeout, TCallBack(TimeoutCallback, this));
    }

CLayoutChangeCallBack::~CLayoutChangeCallBack()
    {   
    Cancel();
    iThread.Close();
    delete iTimeout;
    }

void CLayoutChangeCallBack::DoCancel()
    {
    iThread.Terminate(0);
    
    // Only complete the request if not yet completed by the background thread.
    if ( iStatus == KRequestPending )
        {
        TRequestStatus* pStatus = &iStatus;
        User::RequestComplete(pStatus, KErrCancel);     
        }
    }

void CLayoutChangeCallBack::RunL()
    {
    iSgc->HandleLayoutChangeCallBackL();
    }


// ---------------------------------------------------------------------------
// CLayoutChangeCallBack::ThreadFunc
// Thread entry point function.
// ---------------------------------------------------------------------------
//
TInt CLayoutChangeCallBack::ThreadFunc( TAny* aLayoutChangeCallBack )
    {
    CLayoutChangeCallBack* self =
        static_cast<CLayoutChangeCallBack*>(aLayoutChangeCallBack);
    RThread main;
    if (KErrNone == main.Open(self->iMain))
        {
        TRequestStatus* pStatus = &self->iStatus;
        main.RequestComplete(pStatus, KErrNone);
        main.Close();
        }
    return KErrNone;
    }

TInt CLayoutChangeCallBack::TimeoutCallback( TAny* aThis )
    {
    static_cast<CLayoutChangeCallBack*>( aThis )->DoTimeout();
    return EFalse;
    }
    
void CLayoutChangeCallBack::DoTimeout()
    {
    TRAP_IGNORE( iSgc->HandleLayoutChangeCallBackL() );
    }


CEikSgcServer::TWgState::TWgState()
: iWgId(0), iSpLayout(0), iSpFlags(0), iAppScreenMode(KAknScreenModeUnset)
    {
    // Default state for window groups is full screen - handles non
    // avkon apps.
    iFlags.Set(EWgStateFullScreen);
    }

CEikSgcServer::TWgState::TWgState(TInt aWgId)
: iWgId(aWgId), iSpLayout(0), iSpFlags(0), iAppScreenMode(KAknScreenModeUnset)
    {
    // Default state for window groups is full screen - handles non
    // avkon apps.
    iFlags.Set(EWgStateFullScreen);
    }

inline TInt CEikSgcServer::TWgState::WgId() const
    {
    return iWgId;
    }

inline void CEikSgcServer::TWgState::SetWgId(TInt aWgId)
    {
    iWgId = aWgId;
    }

inline TInt CEikSgcServer::TWgState::SpLayout() const
    {
    return iSpLayout;
    }

inline void CEikSgcServer::TWgState::SetSpLayout(TInt aSpLayout)
    {
    iSpLayout = aSpLayout;
    }

inline TInt CEikSgcServer::TWgState::SpFlags() const
    {
    return iSpFlags;
    }

inline void CEikSgcServer::TWgState::SetSpFlags(TInt aSpFlags)
    {
    iSpFlags = aSpFlags;
    }

inline TBool CEikSgcServer::TWgState::IsFullScreen() const
    {
    return iFlags[EWgStateFullScreen];
    }

inline void CEikSgcServer::TWgState::SetFullScreen(TBool aFullScreen)
    {
    iFlags.Assign(EWgStateFullScreen, aFullScreen);
    }

inline TBool CEikSgcServer::TWgState::IsPartialForeground() const
    {
    return iFlags[EWgStatePartialForeground];
    }

inline void CEikSgcServer::TWgState::SetPartialForeground(TBool aPartialForeground)
    {
    iFlags.Assign(EWgStatePartialForeground, aPartialForeground);
    }

inline TBool CEikSgcServer::TWgState::UnderstandsPartialForeground() const
    {
    return iFlags[EWgStateUnderstandsPartialForeground];
    }

inline void CEikSgcServer::TWgState::SetUnderstandsPartialForeground(TBool aPartialForeground)
    {
    iFlags.Assign(EWgStateUnderstandsPartialForeground, aPartialForeground);
    }

inline TBool CEikSgcServer::TWgState::IsLegacyLayout() const
    {
    return iFlags[EWgStateLegacyLayout];
    }

inline void CEikSgcServer::TWgState::SetLegacyLayout(TBool aLegacyLayout)
    {
    iFlags.Assign(EWgStateLegacyLayout, aLegacyLayout);
    }

inline TBool CEikSgcServer::TWgState::IsOrientationSpecified() const
    {
    return iFlags[EWgStateOrientationSpecified];
    }

inline void CEikSgcServer::TWgState::SetOrientationSpecified(TBool aOrientationSpecified)
    {
    iFlags.Assign(EWgStateOrientationSpecified, aOrientationSpecified);
    }

inline TBool CEikSgcServer::TWgState::IsOrientationLandscape() const
    {
    return iFlags[EWgStateOrientationLandscape];
    }

inline void CEikSgcServer::TWgState::SetOrientationLandscape(TBool aOrientationLandscape)
    {
    iFlags.Assign(EWgStateOrientationLandscape, aOrientationLandscape);
    }

inline TInt CEikSgcServer::TWgState::AppScreenMode() const
    {
    return iAppScreenMode;
    }

inline void CEikSgcServer::TWgState::SetAppScreenMode(TInt aAppScreenMode)
    {
    iAppScreenMode = aAppScreenMode;
    }

CEikSgcServer* CEikSgcServer::NewL()
    {
    CEikSgcServer* self = new(ELeave) CEikSgcServer();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

CEikSgcServer::CEikSgcServer()
: iWs(CEikonEnv::Static()->WsSession()),
  iLastScreenModeSet(-1), 
  iRelinquishedThreads(KRelinquishedThreadListGranularity),
  iSetLayoutBlankStep(ESetLayoutBlankBeforeLayoutLoad)
    {
    }

void CEikSgcServer::ConstructL()
    {
    iWgStates = new(ELeave) CWgStates(KWgStatesGranularity);
    
    TInt err = RProperty::Define(KPSUidUikon, KUikPreferredOrientation, RProperty::EInt);
    User::LeaveIfError(err);
    
    err = RProperty::Define(
        KPSUidAvkonDomain, 
        KAknNotificationsInIdleAllowed, 
        RProperty::EInt,
        KPassReadPolicy,
        KWriteDDPolicy);
    User::LeaveIfError(err);
#if FADE_BITMAP

	err = RProperty::Define(KPSUidAvkonInternal, KAknFadeBitmapHandle,
							RProperty::EInt,
							KPassReadPolicy,
							KWriteDDPolicy);
	User::LeaveIfError(err);
	err = RProperty::Define(KPSUidAvkonInternal, KAknFadeMaskHandle,
							RProperty::EInt,
							KPassReadPolicy,
							KWriteDDPolicy);
	User::LeaveIfError(err);
#endif
	
	err = RProperty::Define(KPSUidAvkonInternal, KAknFadeColorHandle,
							RProperty::EInt,
							KPassReadPolicy,
							KWriteDDPolicy);
	User::LeaveIfError(err);

	err = RProperty::Define(KPSUidAvkonInternal, KAknFadeBlackMapHandle,
							RProperty::EInt,
							KPassReadPolicy,
							KWriteDDPolicy);
	User::LeaveIfError(err);
	err = RProperty::Define(KPSUidAvkonInternal, KAknFadeWhiteMapHandle,
							RProperty::EInt,
							KPassReadPolicy,
							KWriteDDPolicy);
	User::LeaveIfError(err);

	
		
    
#ifndef TFX_USE_WCHANGE_EVENT
    iWinChange = CWindowChangeMonitor::NewL(iWs);
#endif

	CAknSgcServerImpl* sgcImpl = new(ELeave) CAknSgcServerImpl(this);
	// CAknSgcClient takes ownership of sgcImpl and replaces
	// existing client impl with it.
	CAknSgcClient::SetImpl(sgcImpl);	

    // Touch compatibility mode
    iAvkonAppUiBase->MopGetObjectNoChaining(iTouchCompaModeIf);
    iTouchCompaScreenMode = KErrNotFound;
    if (iTouchCompaModeIf)
        {
        iTouchCompaScreenMode = iTouchCompaModeIf->FindCompaScreenMode();
        }

    // ECom notifier for ILD installations
	TCallBack callback(CEikSgcServer::LayoutInstallationCallBack, this);
	iLayoutNotifier = CEComPluginNotifier::NewL(KNullUid, callback);
	iLayoutNotifier->Start();
	EComPluginUtils::GetInfoArrayL(TUid::Uid(KCdlEComInterfaceId), iPrevPluginInfo);
    }

TInt CEikSgcServer::LayoutInstallationCallBack(TAny* aPtr)
	{
	return ((CEikSgcServer*)aPtr)->RefreshLayoutIfRequiredL();
	}
 
TInt CEikSgcServer::RefreshLayoutIfRequiredL()
	{
	REComPluginInfoArray newPlugins;
	EComPluginUtils::GetInfoArrayL(TUid::Uid(KCdlEComInterfaceId), newPlugins);
	REComPluginInfoArray newPluginsCopy = newPlugins;
	
	// Remove any plugins that haven't changed from the arrays
	TInt prevCount = iPrevPluginInfo.Count();
	while(prevCount > 0)
		{
		prevCount--;
		TUid prevUid = (iPrevPluginInfo[prevCount]).iUid;
		TInt prevVer = (iPrevPluginInfo[prevCount]).iVersion;
		TInt newCount = newPlugins.Count();
		while(newCount > 0)
			{
			newCount--;
			TUid newUid = (newPlugins[newCount]).iUid;
			TInt newVer = (newPlugins[newCount]).iVersion;
			if(prevUid == newUid && prevVer == newVer)
				{
				newPlugins.Remove(newCount);
				iPrevPluginInfo.Remove(prevCount);
				break;
				}
			}
		}
	
	TBool refreshRequired = EFalse;
	if(iPrevPluginInfo.Count() > 0)
		{
		// A plugin has been removed, but we can't check what it contained.
		refreshRequired = ETrue;
		}
	else
		{
		// Check through the changed plugins to see whether any contain layout packs
		_LIT(KLitDllPath, "%S%08x.dll");
		const TInt KPathLength = 14;	// Drive letter + ":" + UID + ".dll"
		for(TInt i=0; i<newPlugins.Count(); i++)
			{
			TEComPluginInfo imp = newPlugins[i];
			TBuf<KPathLength> buf;
			TDriveName drive(imp.iDrive.Name());
			buf.Format(KLitDllPath, &drive, imp.iUid.iUid);
			
			CCdlRefCollection* refsInFile = CdlEngine::FileContentsLC(buf);
			CCdlRefs* refs = CCdlRefs::NewLC();
			refs->AppendL(*refsInFile);
			CCdlRefs* layoutsInFile = refs->SubsetByUidLC(LayoutPack::KCdlInterfaceUid);
			TInt numLayouts = layoutsInFile->CountRefs();
			CleanupStack::PopAndDestroy(3, refsInFile);
			
			if(numLayouts > 0)
				{
				// Plugin added with layouts, refresh required
				refreshRequired = ETrue;
				break;
				}
			}
		}

	// Send the event if it's needed
	TInt result = KErrNone;
	if(refreshRequired)
		{
		RWsSession session;
		TInt err = session.Connect();
        if ( err == KErrNone )
            {
            TWsEvent event;
            event.SetType(KAknILDInstallationLayoutSwitch);
            result = session.SendEventToAllWindowGroups(event);
            session.Close();
            }
		}

	// Store the copy of the new list of plugins for next time
	iPrevPluginInfo.Reset();
	iPrevPluginInfo = newPluginsCopy;
	
	return result;
    }

CEikSgcServer::~CEikSgcServer()
    {
	delete iFadeBitmap;
	delete iFadeMask;

    delete iWinChange;
    delete iLayoutChangeCallBack;
    delete iWgStates;
    delete iRemoveBlankCallBack;
    delete iLayoutNotifier;
    }

void CEikSgcServer::HandleWindowGroupListChangeL()
    {
    CWgIds* wgIds = CreateWgIdListLC();
    if (!TestWgListOrderOk(wgIds))
        {
        ReOrderWgStatesL(wgIds);
        PostChangeRecalcL();
        UpdateNotificationsInIdleAllowedKey();
        }
    CleanupStack::PopAndDestroy( wgIds );
    }

void CEikSgcServer::HandleWindowGroupParamChangeL(TInt aWgId, TBitFlags aAppFlags, TInt aSpLayout, 
    TInt aSpFlags, TInt aAppScreenMode)
    {
    LOGTEXT0("CEikSgcServer::HandleWindowGroupParamChangeL - ENTER");
    
    TBool understandsPartialForegroundChanged = EFalse;
    TBool fullScreenChanged = EFalse;
    
    TWgState& state = GetWgStateL(aWgId);

    const TBool wasFullScreen = state.IsFullScreen();
    state.SetFullScreen(aAppFlags[CAknSgcClient::EFullScreen]);
    const TBool isFullScreen = state.IsFullScreen();
    
    state.SetLegacyLayout(aAppFlags[CAknSgcClient::ELegacyLayout]);
    state.SetSpLayout(aSpLayout);
    state.SetSpFlags(aSpFlags);
    
    // Check whether understands partial foreground is changed. 
    if (!state.UnderstandsPartialForeground())
        {
        understandsPartialForegroundChanged = ETrue;
        }
    state.SetUnderstandsPartialForeground(ETrue);
    
    state.SetOrientationSpecified(aAppFlags[CAknSgcClient::EOrientationSpecified]);
    state.SetOrientationLandscape(aAppFlags[CAknSgcClient::EOrientationLandscape]);
    state.SetAppScreenMode(aAppScreenMode);
    PostChangeRecalcL();
    
    // Check whether full screen mode has been changed.
    fullScreenChanged = (wasFullScreen && !isFullScreen) || (!wasFullScreen && isFullScreen);
    
    if (understandsPartialForegroundChanged || fullScreenChanged)
        {
        LOGTEXT1("  understandsPartialForegroundChanged: %d", understandsPartialForegroundChanged);
        LOGTEXT1("  fullScreenChanged: %d",                   fullScreenChanged);        
        
        UpdateNotificationsInIdleAllowedKey();
        }
    
    LOGTEXT0("CEikSgcServer::HandleWindowGroupParamChangeL - EXIT");
    }

CEikSgcServer::TWgState& CEikSgcServer::GetWgStateL(TInt aWgId)
    {
    TInt index = WgStateIndex(aWgId);
    if (index == KErrNotFound)
        {
        iWgStates->AppendL(TWgState(aWgId));
        index = iWgStates->Count()-1;
        }
    return iWgStates->At(index);
    }

TInt CEikSgcServer::WgStateIndex(TInt aWgId) const
    {
    TInt count = iWgStates->Count();
    for (TInt ii=0; ii<count; ii++)
        {
        if (iWgStates->At(ii).WgId() == aWgId)
            {
            return ii;
            }
        }
    return KErrNotFound;
    }

CEikSgcServer::CWgIds* CEikSgcServer::CreateWgIdListLC() const
    {
    CWgIds* wgIds = new(ELeave) CWgIds(1);
    CleanupStack::PushL(wgIds);
    iWs.WindowGroupList(wgIds);
    return wgIds;
    }

void CEikSgcServer::ReOrderWgStatesL(CWgIds* aWgIds)
    {
    CWgStates* newStates = new(ELeave) CWgStates(KWgStatesGranularity);
    CleanupStack::PushL(newStates);
    TInt count = aWgIds->Count();
    newStates->ResizeL(count);
    for (TInt ii=0; ii<count; ii++)
        {
        newStates->At(ii) = GetWgStateL(aWgIds->At(ii));
        }
    CleanupStack::Pop(newStates);
    delete iWgStates;
    iWgStates = newStates;
    }

void CEikSgcServer::SetStatusPaneShapeAndFlagsL(TInt aSpIndex)
    {
    if (aSpIndex == KErrNotFound)
        {
        return;
        }
    TWgState& topState = iWgStates->At(aSpIndex);

    TInt layout = topState.SpLayout();
    if (iLayout != layout)
        {
        iSp->SwitchLayoutL(layout);
        iLayout = layout;
        }

    TInt flags = topState.SpFlags();
    if (iFlags != flags)
        {
        iSp->SetFlags(flags);
        iFlags = flags;
        }
    }

#ifndef TFX_USE_WCHANGE_EVENT   
void CEikSgcServer::ActivateEffectL()
    {
    if(iWinChange == NULL)
        {
        return; // nobody there
        }
    
//  CWindowChangeMonitor::TWinGroupEvent event =
//   iWinChange->WinGroupEvent();   
        
    const TInt index = FocusWgIndex();
    //WgStateIndex(iWinChange-> GetFocusWg());  
        
    const TInt focusWgIndex = index < 0 ? 0 : index;
    
    const TInt count = iWgStates->Count();
    
    for (TInt i = focusWgIndex; i < count; i++)
        {
        const TWgState& state = iWgStates->At(focusWgIndex);
        const TInt wgId = state.WgId();
    
        if(state.UnderstandsPartialForeground())
            {
            if(wgId != iFirstFullScreenWg)
                {
                iWinChange->WgChangeL(wgId);
                }

            // Note that exits also for non fullscreen (unlike SetPartialForegroundStatusesL).
            return; 
            }   
        }
    }
#endif

void CEikSgcServer::SetPartialForegroundStatusesL()
    {
    TInt count = iWgStates->Count();
    TInt ii;
    TBool partialFg = EFalse;
    for (ii = FocusWgIndex(); ii < count; ii++)
        {
        TWgState& state = iWgStates->At(ii);
        if (state.UnderstandsPartialForeground())
            {
            if (partialFg)
                {
                SetWgPartialFg(state);
                }
            if (!state.IsFullScreen())
                {
                partialFg = ETrue;
                }
            else
                {
                // Notify first full-screen app that it is topmost application though does not 
                // have kb focus.
                if (iFirstFullScreenWg != iWgStates->At(ii).WgId() )
                    { 
                    // same event instance will be recycled for both of events...
                    TWsEvent event;
                    event.SetTimeNow();
                    
                    if (iFirstFullScreenWg) // notify old that it has lost its focus
                        {
                        event.SetType(KAknFullOrPartialForegroundLost); 
                        iWs.SendEventToWindowGroup(iFirstFullScreenWg, event);
                        }
                    
                    iFirstFullScreenWg = iWgStates->At(ii).WgId();
                    event.SetType(KAknFullOrPartialForegroundGained);
                    iWs.SendEventToWindowGroup(iFirstFullScreenWg, event);
                    }
                break;                   
                }
            }
        }
    for (++ii; ii<count; ii++)
        {
        TWgState& state = iWgStates->At(ii);
        if (state.UnderstandsPartialForeground())
            {
            ClearWgPartialFg(state);
            }
        }
        
#ifndef TFX_USE_WCHANGE_EVENT   
    if(iWinChange != NULL)
        {
        iWinChange->SetWgL(iFirstFullScreenWg); 
        }
#endif
    }

void CEikSgcServer::PostChangeRecalcL()
    {
#ifndef TFX_USE_WCHANGE_EVENT
    ActivateEffectL();
#endif

    TInt topSp = TopSpIndex();
    SetLayoutL(topSp);
    SetStatusPaneShapeAndFlagsL(topSp);
    SetPartialForegroundStatusesL();
    }

TBool CEikSgcServer::TestWgListOrderOk(CWgIds* aWgIds) const
    {
    TInt count = aWgIds->Count();
    if (count != iWgStates->Count())
        {
        return EFalse;
        }
    for (TInt ii = 0; ii < count; ii++)
        {
        if (aWgIds->At(ii) != iWgStates->At(ii).WgId())
            {
            return EFalse;
            }
        }
    return ETrue;
    }

TInt CEikSgcServer::FocusWgIndex() const
    {
    TInt index = WgStateIndex(iWs.GetFocusWindowGroup());
    if (index == KErrNotFound)
        {
        index = 0;
        }
    return index;
    }

void CEikSgcServer::SetWgPartialFg(TWgState& aWgState)
    {
    if (!aWgState.IsPartialForeground())
        {
        aWgState.SetPartialForeground(ETrue);
        }
    }

void CEikSgcServer::ClearWgPartialFg(TWgState& aWgState)
    {
    if (aWgState.IsPartialForeground())
        {
        aWgState.SetPartialForeground(EFalse);
        }
    }

void CEikSgcServer::SetStatusPane(CEikServStatusPane* aSp)
    {
    ASSERT(aSp);
    iSp = aSp;
    iSpWg = aSp->WindowGroup();
    }

TInt CEikSgcServer::TopSpIndex(TInt aAfter) const
    {
    TInt count = iWgStates->Count();
    for (TInt topSp=aAfter+1; topSp<count; topSp++)
        {
        if (iWgStates->At(topSp).SpLayout())
            {
            return topSp;
            }
        }
    return KErrNotFound;
    }

void CEikSgcServer::PrepareForAppExitL(TInt aWgId)
    {
    TInt topSp = TopSpIndex();
    if (topSp != KErrNotFound)
        {
        TWgState& topState = iWgStates->At(topSp);
        if (topState.WgId() == aWgId)
            {
            TInt focusWg = FocusWgIndex();
            if (focusWg != KErrNotFound && iWgStates->At(focusWg).IsPartialForeground())
                { // we trust that wg order is valid at this point.
                if ( focusWg < iWgStates->Count()-1 )
                    {
                    TWsEvent event;
                    event.SetType(EEventUser);
                    *(TApaSystemEvent*)(event.EventData())=EApaSystemEventBroughtToForeground;
                    event.SetTimeNow();
                    iWs.SendEventToWindowGroup(iWgStates->At(focusWg+1).WgId(), event);
                    }
                }
               
            // remove the status pane from the exiting wg
            topState.SetSpLayout(0);

            // Set the status pane to the shape for the app below
            topSp = TopSpIndex(topSp);
            SetLayoutL(topSp);
            SetStatusPaneShapeAndFlagsL(topSp);
            if (iSp)
                {
                iSp->PrepareForAppExit();
                }
            }
        }
    }

#define FADE_COLOR_17 1
//#define FADE_COLOR_TEXT 1

inline TUint8 GetColorIntensity(TUint32 aColor)
	{
	// Separate R, G, B
	register TUint32 r = (aColor >> 16) & 0xFF;
	register TUint32 g = (aColor >> 8) & 0xFF;
	register TUint32 b = (aColor) & 0xFF;
	
	// Calculate and return intensity
	return TUint8( (r*306 + g*601 + b*117) >> 10 );
	}

void CEikSgcServer::FadeColorGenerationL()
	{
	MAknsSkinInstance *skin = AknsUtils::SkinInstance();
	bool b = false;
#if FADE_COLOR_17
	TAknsItemID skinid = KAknsIIDQsnOtherColors; 
	TRgb colorrgb; 
	TInt err = AknsUtils::GetCachedColor(skin, colorrgb, skinid, 19-1); 
	if (err != KErrNone)
	{
		colorrgb = TRgb(255,255,255,0);	

		CFbsBitmap *bitmap=NULL, *mask=NULL;
		TAknsItemID skinid = KAknsIIDQsnFrPopupCenter ; 
		TRAP(err, AknsUtils::CreateIconL(skin, skinid, bitmap, mask, _L(""), -1, -1));
		if (err == KErrNone)
			{
			TSize size(30,30);
			AknIconUtils::DisableCompression(bitmap);
			AknIconUtils::SetSize(bitmap, size, EAspectRatioNotPreserved);
			TPoint point(15,15);

			//TBuf8<4> buf;
			//bitmap->GetScanLine(buf, point, 1, bitmap->DisplayMode());
			//colorrgb = TRgb(buf[3], buf[2], buf[1], buf[0]);

			//colorrgb.SetAlpha(buf[0]);
			//colorrgb.SetBlue(buf[1]);
			//colorrgb.SetGreen(buf[2]);
			//colorrgb.SetRed(buf[3]);
			bitmap->GetPixel(colorrgb, point);
	
			delete bitmap;
			delete mask;
			b=true;
			}
	}
	TRgb blackmap, whitemap;
	TInt err1 = AknsUtils::GetCachedColor(skin, blackmap, skinid, 17-1); 
	TInt err2 = AknsUtils::GetCachedColor(skin, whitemap, skinid, 18-1); 

	if (err1 != KErrNone) blackmap = TRgb(0,0,0,0);
	if (err2 != KErrNone) whitemap = TRgb(255,255,255,0);

	TInt blackcolor = (blackmap.Red()<<16) + (blackmap.Green()<<8) + blackmap.Blue();
	TInt whitecolor = (whitemap.Red()<<16) + (whitemap.Green()<<8) + whitemap.Blue();

	TInt blackmapint = GetColorIntensity(blackcolor);
	TInt whitemapint = GetColorIntensity(whitecolor);

#endif

#if FADE_COLOR_TEXT
	TAknsItemID skinid = KAknsIIDQsnOtherColors; 
	TRgb colorrgb; 
	TInt err = AknsUtils::GetCachedColor(skin, colorrgb, skinid, 17); 
	if (err != KErrNone)
		{

		TAknsItemID skinid = KAknsIIDQsnTextColors ;
		TInt err = AknsUtils::GetCachedColor(skin, colorrgb, skinid, EAknsCIQsnTextColorsCG19 ); 
		}	
	TInt blackmapint = 0;
	TInt whitemapint = 255;
#endif

	TInt color = (colorrgb.Red()<<16) + (colorrgb.Green()<<8) + colorrgb.Blue();

	if (b) 
	{
		TInt intensity = GetColorIntensity(color);
		if (intensity < 127) 
			{ // background color dark
			blackmapint = 0;
			whitemapint = 64;
			color = 0xffffff;
			}
		else
			{
			blackmapint = 192;
			whitemapint = 255;
			color = 0xffffff;
			}
	}
	RProperty::Set(KPSUidAvkonInternal, KAknFadeBlackMapHandle, blackmapint);
	RProperty::Set(KPSUidAvkonInternal, KAknFadeWhiteMapHandle, whitemapint);
	RProperty::Set(KPSUidAvkonInternal, KAknFadeColorHandle, color);
	
	}

void CEikSgcServer::FadeBitmapGenerationL()
	{
#if FADE_BITMAP
	//
	// Generates bitmap and mask for fade wserv plugin and
	// publishes them in publish&subscribe.
	//
	delete iFadeBitmap;
	delete iFadeMask;
	iFadeBitmap = NULL;
	iFadeMask = NULL;

	MAknsSkinInstance *skin = AknsUtils::SkinInstance();

	TInt err= KErrNone;
	if (!Layout_Meta_Data::IsLandscapeOrientation())
		{
		TAknsItemID skinid = KAknsIIDQgnGrafBgDimmingPrt; // TODO
		TRAP(err, AknsUtils::CreateIconL(skin, skinid, iFadeBitmap, iFadeMask, _L(""), -1, -1));
		}
	else
		{
		TAknsItemID skinid = KAknsIIDQgnGrafBgDimmingLsc; // TODO
		TRAP(err, AknsUtils::CreateIconL(skin, skinid, iFadeBitmap, iFadeMask, _L(""), -1, -1));
		}
	if (err != KErrNone)
		{
		TAknsItemID skinid = KAknsIIDQgnGrafBgDimming   ; // TODO
		TRAP(err, AknsUtils::CreateIconL(skin, skinid, iFadeBitmap, iFadeMask, _L(""), -1, -1));
		}

	if (err == KErrNone)
		{ // found from skins

		TRect rect = TRect(0,0,0,0);
		TAknLayoutRect r;
		r.LayoutRect(rect, AknLayoutScalable_Avkon::Screen().LayoutLine());		
		TSize size = r.Rect().Size();

		AknIconUtils::SetSize(iFadeBitmap, size, EAspectRatioNotPreserved);


		TInt bitmaphandle = iFadeBitmap->Handle();
		TInt maskhandle = iFadeMask->Handle();
		RProperty::Set(KPSUidAvkonInternal, KAknFadeBitmapHandle, bitmaphandle);
		RProperty::Set(KPSUidAvkonInternal, KAknFadeMaskHandle, maskhandle);
		}
#endif						   
	}
void CEikSgcServer::SetLayoutL(TInt aSpIndex)
    {
    if (aSpIndex == KErrNotFound)
        {
        return;
        }

    TWgState& topState = iWgStates->At(aSpIndex);

    CEikonEnv* eikEnv = CEikonEnv::Static();
    
    CAknLayoutConfig::TScreenMode mode = CAknSgcClient::CalculateScreenMode(
        ETrue, 
        topState.IsOrientationSpecified(), 
        topState.IsOrientationLandscape(), 
        topState.AppScreenMode());
        
    TInt modeIndex = mode.ModeNumber();
    TBool blank = iLastScreenModeSet != -1;
    if (modeIndex != iLastScreenModeSet)
        {

        // Touch compatibility mode. Disable transition effects if compa-mode
        // application becomes foreground. Restore back in opposite case.
        if (iTouchCompaModeIf)
            {
            // Disable or restore transition
            iTouchCompaModeIf->DisableTransEffects(
                iTouchCompaScreenMode == modeIndex);
            }

        TBool tfxOn = EFalse;
#ifdef RD_UI_TRANSITION_EFFECTS_LAYOUT_SWITCH    
		tfxOn = CAknTransitionUtils::TransitionsEnabled(
	            AknTransEffect::ELayoutswitchTransitionsOff );
	    if ( tfxOn )
	        {
	        iSetLayoutBlankStep = ESetLayoutBlankAfterScreenRotate;
	        }
	    else
	   	    {
	  		iSetLayoutBlankStep = ESetLayoutBlankBeforeLayoutLoad;
	   	    }
#endif

		if (!tfxOn)
	    	eikEnv->WsSession().ClearAllRedrawStores();
		
        // If AknNfySrv or EikSrv is displaying a global note,
        // the screen blanker is allowed to stay on until it times
        // out (like when AknCapSrv is displaying a note).
        TInt blankCnt = 1;
        if (IsGlobalNoteForeground())
            {
		    // For some reason, AknNfySrv and EikSrv unblank twice on target hardware.
		    // therefore blank is done 3 times to allow it to remain on until timeout.
            blankCnt += 2;
            }

		SetLayoutBlankScreenL(blank, ESetLayoutBlankBeforeLayoutLoad,
		    blankCnt);

        const TAknLayoutConfigScreenMode& modeRef = (const TAknLayoutConfigScreenMode&) mode;
        TBool newLayoutLoaded = CAknEnv::Static()->LoadAknLayoutL(modeRef);

		FadeBitmapGenerationL();
		FadeColorGenerationL();
        SetLayoutBlankScreenL(blank, ESetLayoutBlankBetweenLayoutLoadAndScreenRotate);

 		if (tfxOn)
	    	eikEnv->WsSession().ClearAllRedrawStores();
   	
		// if layout change is preemptive for app change, move the app here
        DoMoveApp();
        	
        // Set wserv screen mode
        iLastScreenModeSet = modeIndex;
        eikEnv->ScreenDevice()->SetScreenMode(modeIndex);

		SetLayoutBlankScreenL(blank, ESetLayoutBlankAfterScreenRotate,
		    blankCnt);

        // Set legacy mode in eiksrv app UI
        iAvkonAppUiBase->SetLayoutAwareApp(!topState.IsLegacyLayout());

        // Start callback for handling new layout
        if (newLayoutLoaded)
            {
            // Swap the screen blanker to update the foreground app's layout
            if (blank && iSetLayoutBlankStep < ESetLayoutBlankAfterScreenRotate) 
                {
                iAknCapAppServerAppUi->SwapLayoutSwitchBlankScreenL();
                }

            CAknAppUi* appUi = static_cast<CAknAppUi*>(eikEnv->EikAppUi());
            if (appUi->IsForeground())
                {
                for (; appUi; appUi = static_cast<CAknAppUi*>(appUi->ContainerAppUi()))
                    {
                    appUi->ReportResourceChangedToAppL(KEikDynamicLayoutVariantSwitch);
                    }
                }
                
            if (iLayoutChangeCallBack)
                {
                // Restart the app delay callback timer if another layout change has happened 
                // before it triggers.
                iLayoutChangeCallBack->RestartTimerL();
                }
            else
                {
                iLayoutChangeCallBack = new(ELeave) CLayoutChangeCallBack(this);
                iLayoutChangeCallBack->ConstructL();
                }
                
            // stop any existing timer to unblank the screen, iLayoutChangeCallBack will restart it
            delete iRemoveBlankCallBack;
            iRemoveBlankCallBack = NULL;
            }
        else
            {
            if (!iLayoutChangeCallBack && blank)
                {
                // The callback will not remove the screen blanker,
                // so remove it now.
                iBlankCount--;
                iAknCapAppServerAppUi->BlankScreenL(EFalse);
                }
            }
        }
    }

void CEikSgcServer::SetLayoutBlankScreenL(TBool aBlank, TInt aStep)
	{
    // Use a screen blanker to hide the screen change
    if (aBlank && aStep == iSetLayoutBlankStep)
        {
        // blank the screen and keep track of how many times it's been blanked
        iBlankCount++;
        iAknCapAppServerAppUi->BlankScreenL(ETrue, ETrue);
        }
	}

void CEikSgcServer::HandleLayoutChangeCallBackL()
    {
    // delete the active object
    delete iLayoutChangeCallBack;
    iLayoutChangeCallBack = NULL;   
    
    CEikonEnv* eikEnv = CEikonEnv::Static();
    
    // Report the layout change to the UI controls
    for (CEikAppUi* appUi = eikEnv->EikAppUi(); appUi; appUi = appUi->ContainerAppUi())
        {
        appUi->ReportResourceChangedToAppL(KEikDynamicLayoutVariantSwitch);
        }
    
    // if visible tasklist must be updated during layout change event
    iAknCapAppServerAppUi->UpdateTaskListL( ETrue );
    
    // Remove any remaining screen blanker after a delay.
    // Normally the foreground app will have removed all blanking
    // before this function triggers. This is really just a backup
    // in-case the app is behaving badly, or if some unfortuante
    // timing has caused this function to trigger before the foreground app
    // finished its redraw. The delay should give the foreground app
    // sufficient time.
    iRemoveBlankCount += iBlankCount;
    iBlankCount = 0;
    delete iRemoveBlankCallBack;
    iRemoveBlankCallBack = NULL;
    iRemoveBlankCallBack = CPeriodic::NewL(CActive::EPriorityLow);

    TInt removeBlankDelay = CAknEnv::Static()->TransparencyEnabled() ?
        KRemoveBlankDelayTransparency : KRemoveBlankDelay;
    
    if(iAknCapAppServerAppUi->IsShortTimeGlobalNoteDisplaying())
        {
        removeBlankDelay = KRemoveBlankDelay;
        }
    
    iRemoveBlankCallBack->Start(
        removeBlankDelay,
        removeBlankDelay,
        TCallBack(RemoveBlankCallBack, this));
    }

void CEikSgcServer::RelinquishPriorityToForegroundAppL(const RMessage2& aMessage)
    {
    // get the client thread
    SRelinquishedThread rel;
    aMessage.ClientL(rel.iThread);
    CleanupClosePushL(rel.iThread);
    rel.iId = rel.iThread.Id();
    rel.iPriority = rel.iThread.ProcessPriority();

    // reset the callback timer, ensure that failure does not stop existing timer
    CPeriodic* newCallBack = CPeriodic::NewL(CActive::EPriorityStandard);
    delete iRelinquishedThreadCallBack;
    iRelinquishedThreadCallBack = newCallBack;
    
    iRelinquishedThreadCallBack->Start(
        KRestoreThreadPriorityDelay, 
        KRestoreThreadPriorityDelay, 
        TCallBack(RestoreThreadPriorities, this));

    // look for an existing thread
    TInt count = iRelinquishedThreads.Count();
    TInt pos;
    for ( pos = 0; pos < count; pos++ )
        {
        if (iRelinquishedThreads[pos].iId == rel.iId)
            {
            break;
            }
        }

    if (pos<count)
        {
        // thread is already recorded. Make sure it's background and stop
        rel.iThread.SetProcessPriority(EPriorityBackground);
        CleanupStack::PopAndDestroy(&rel.iThread);
        }
    else
        {
        // add thread to array
        iRelinquishedThreads.AppendL(rel);
        CleanupStack::Pop(&rel.iThread);
         // set the thread to background priority when all recovery mechanisms are in place
        rel.iThread.SetProcessPriority(EPriorityBackground);
        }

    aMessage.Complete(KErrNone);
    }

TInt CEikSgcServer::RestoreThreadPriorities( TAny* aThis )
    {
    static_cast<CEikSgcServer*>( aThis )->DoRestoreThreadPriorities();
    return EFalse;
    }

void CEikSgcServer::DoRestoreThreadPriorities()
    {
    delete iRelinquishedThreadCallBack;
    iRelinquishedThreadCallBack = NULL;
    TInt count = iRelinquishedThreads.Count();
    for (TInt ii=0; ii<count; ii++)
        {
        SRelinquishedThread& rel = iRelinquishedThreads[ii];
        rel.iThread.SetProcessPriority(rel.iPriority);
        rel.iThread.Close();
        }
    iRelinquishedThreads.Reset();
    }

void CEikSgcServer::SetAknCapAppServerAppUi(CAknCapAppServerAppUi* aAknCapAppServerAppUi)
    {
    iAknCapAppServerAppUi = aAknCapAppServerAppUi;      
    }

void CEikSgcServer::RotateScreenL()
    {
    // Toggle preferred orientation
    TInt orientation;
    TInt err = RProperty::Get(KPSUidUikon, KUikPreferredOrientation, orientation);
    User::LeaveIfError(err);
    
    if (orientation == EPreferredOrientationNormal)
        {
        orientation = EPreferredOrientationAlternate;
        }
    else // alternate screen orientation
        {
        orientation = EPreferredOrientationNormal;
        }

    err = RProperty::Set(KPSUidUikon, KUikPreferredOrientation, orientation);
    User::LeaveIfError(err);

    CWsScreenDevice* device = CEikonEnv::Static()->ScreenDevice();
    TInt screenMode = device->CurrentScreenMode();

    CEikonEnv* eikEnv = CEikonEnv::Static();
    
    // Update the setting cache and get SGCS to process the screen mode
    // change, this may broadcast a screen device change to the apps,
    // to inform them of the update
    CAknEnv::Static()->SettingCache().Update( KAknHardwareLayoutSwitch );
    HandleWindowGroupParamChangeL(
        eikEnv->RootWin().Identifier(),
        0,
        0,
        0,
        KAknScreenModeUnset );

    if (screenMode == device->CurrentScreenMode())
        {
        // Apps will not have received a screen device changed event
        // so send a KAknHardwareLayoutSwitch to the apps to ensure
        // they get to know about the key
        TWsEvent event;
        event.SetType(KAknHardwareLayoutSwitch);
        event.SetHandle(0);
        eikEnv->WsSession().SendEventToAllWindowGroups( 0, event );
        }
    }

void CEikSgcServer::UpdateNotificationsInIdleAllowedKey()
    {
    // First, get screensaver window group identifier.
    TApaTaskList taskList(CEikonEnv::Static()->WsSession());
    const TApaTask screensaverTask = taskList.FindApp(KScreensaverAppUid);
    const TInt screensaverWgId = screensaverTask.WgId();
    
    // Get also idle window group identifier.
    TVwsViewId idleView;
    if (AknDef::GetPhoneIdleViewId(idleView) != KErrNone)
        {
        return;
        }
        
    const TApaTask idleTask = taskList.FindApp(idleView.iAppUid);
    const TInt idleWgId = idleTask.WgId();
    
    // Then go through window groups skipping partial apps and screensaver - 
    // check if idleWgId follows.
    TBool result = EFalse;
    TBool found = EFalse;
    const TInt wgCount = iWgStates->Count();
    TInt ii = FocusWgIndex();
        
    LOGTEXT0("======================================");
    LOGTEXT1("Window groups: %d",      wgCount);
    LOGTEXT1("Idle wg id: %d",         idleWgId);
    LOGTEXT1("Screensaver wg id: %d",  screensaverWgId);
    LOGTEXT1("Focus window group: %d", ii);
    LOGTEXT0("======================================");
                
    // Loops window groups from top to bottom, starting from focus window group.
    // (Index 0 contains the foreground window group.)
    while (ii < wgCount && !found)
        {
        const TWgState& state = iWgStates->At(ii);
        const TInt currentWgId = state.WgId();
        
        LOGTEXT0("\n");
        LOGTEXT1("  Window group id: %d",              currentWgId);
        LOGTEXT1("  UnderstandsPartialForeground: %d", state.UnderstandsPartialForeground());
        LOGTEXT1("  IsFullScreen: %d",                 state.IsFullScreen());
        
        // Ignores non-application window groups (e.g. incall bubble), partial screen
        // applications and screensaver. 
        if (state.UnderstandsPartialForeground() &&
            state.IsFullScreen()                 && 
            currentWgId != screensaverWgId)        
            {
            // Check if current app is idle.
            result = (idleWgId == currentWgId);
            found = ETrue;
            
            LOGTEXT0("\n");
            LOGTEXT1("Window group found. Result: %d", result);
            }
            
        ii++;
        }
        
    // Update the P&S key only if the value has been changed.
    if ((iNotificationsInIdleAllowed && !result) || (!iNotificationsInIdleAllowed && result))
        {
        iNotificationsInIdleAllowed = result;
        RProperty::Set(KPSUidAvkonDomain, KAknNotificationsInIdleAllowed, result);
        }
    } 
    

TInt CEikSgcServer::RemoveBlankCallBack( TAny* aThis )
    {
    static_cast<CEikSgcServer*>( aThis )->DoRemoveBlank();
    return EFalse;
    }

void CEikSgcServer::DoRemoveBlank()
    {
    // remove any remaining screen blanker
    for (; iRemoveBlankCount>0; iRemoveBlankCount--)
        {
        TRAP_IGNORE( iAknCapAppServerAppUi->BlankScreenL( EFalse ) );
        }
        
    iRemoveBlankCount = 0;
    
    // readjust the status pane wg since we pushed it forward with the screen blanker
    iLastTopSpWg = -1;

    delete iRemoveBlankCallBack;
    iRemoveBlankCallBack = NULL;
    }

void CEikSgcServer::SetLayoutBlankScreenL(TBool aBlank, TInt aStep,
    TInt aCnt)
    {
    while(aCnt--)
        {
        SetLayoutBlankScreenL(aBlank, aStep);
        }
    }

// Check if AknNfySrv or EikSrv is displaying a global note
TBool CEikSgcServer::IsGlobalNoteForeground()
    {
    TBool isForeground = EFalse;
    TThreadId threadId;
    if (iWs.GetWindowGroupClientThreadId(iWs.GetFocusWindowGroup(),
        threadId) == KErrNone)
        {
        RThread thread;
        if (thread.Open(threadId) == KErrNone)
            {
            TSecureId secId = thread.SecureId();
            thread.Close();
            const TUid KEikSrvUid = {0x10003a4a};
            isForeground =
                secId.iId == KCommonNotifierAppSrvUid.iUid ||
                secId.iId == KEikSrvUid.iUid;
            }
        }
    return isForeground;
    }

void CEikSgcServer::MoveAppL(TInt aAppWindowGroupId, TSgcMoveAppToWhere aWhere)
	{
	CAknTaskList* taskList = CAknTaskList::NewLC(iWs);
	
	// step 1: Find root (going to foreground) or tip (going to background) of 
	// aAppWindowGroupId's window group chain
	TInt wgId = aAppWindowGroupId;
	for (TInt next=wgId; next;)
		{
		wgId = next;
		next = (aWhere == ESgcMoveAppToForeground) ?
			taskList->FindParentWgId(wgId) :
			taskList->FindChildWgId(wgId);
		}
	
	// step 2: Move whole window group chain
	while (wgId)
		{
		// move the window group
	    TInt index = WgStateIndex(wgId);
	    if (index >= 0)
	    	{
		    TWgState state = iWgStates->At(index);
		    iWgStates->Delete(index);
			if (aWhere == ESgcMoveAppToForeground)
				iWgStates->InsertL(0, state);
			else
				iWgStates->AppendL(state);
	    	}
		
		// get the next window group in the chain
		wgId = (aWhere == ESgcMoveAppToForeground) ?
			taskList->FindChildWgId(wgId) :
			taskList->FindParentWgId(wgId);
		}
		
	CleanupStack::PopAndDestroy(taskList);
	
	// Step 3: do screen rotation and move app
	iMoveAppWdId = aAppWindowGroupId;
	iMoveAppWhere = aWhere;
	
    PostChangeRecalcL();
    
    // if no layout switch occured, move app here
    DoMoveApp();
   	}

void CEikSgcServer::DoMoveApp()
	{
    if (iMoveAppWdId)
    	{
		TApaTask task(iWs);
		task.SetWgId(iMoveAppWdId);
		if (iMoveAppWhere == ESgcMoveAppToForeground)
			task.BringToForeground();
		else
			task.SendToBackground();	
		iMoveAppWdId = 0;
    	}
	}


//
// CAknSgcServerImpl
//
CAknSgcServerImpl::CAknSgcServerImpl(CEikSgcServer* aServer)
: iServer(aServer)
	{
	}

void CAknSgcServerImpl::MoveApp(TInt aAppWindowGroupId, TSgcMoveAppToWhere aWhere)
	{
	TRAP_IGNORE(iServer->MoveAppL(aAppWindowGroupId, aWhere));
	}

// End of file
