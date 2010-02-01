/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  AknCapServer constant definitions.
*
*/

#ifndef __AKNCAPSERVERDEF_H__
#define __AKNCAPSERVERDEF_H__

#include <e32std.h>
#include <babitflags.h>

#define KAknCapServerUid TUid::Uid( 0x10207218 )
#define KAknCapServiceUid TUid::Uid( 0x10207219 )

enum EAknCapServerOps
    {
    EAknSLaunchView = 50, // to avoid collision to notifier related commands
    EAknSKillApp,
    EAknSKillAllApps,
    EAknSUnlockMedia,
    EAknSEnableTaskList,
    EAknsLaunchTaskList,
    EAknSRefreshTaskList,
    EAknSSuppressAppsKey,
    EAknSHideApplicationFromFWS,
    // sgc
    EAknEikAppUiSetSgcParams,
    EAknEikAppUiBlockServerStatusPaneRedraws,
    EAknEikAppUiRedrawServerStatusPane,
    EAknEikAppUiPrepareForAppExit,
    EAknEikAppUiSetSystemFaded,
    EAknEikAppUiIsSystemFaded,
    EAknEikAppUiRelinquishPriorityToForegroundApp,
    EAknEikAppUiLayoutConfigSize,
    EAknEikAppUiGetLayoutConfig,
    EAknEikAppUiMoveAppInZOrder,
    // eiksrv support
    EAknSSetStatusPaneFlags,
    EAknSSetStatusPaneLayout,
    EAknSBlankScreen,
    EAknSUnblankScreen,
    EAknSSetKeyboardRepeatRate,
    EAknSUpdateKeyBlockMode,
    EAknSShowLockedNote,
    EAknSShutdownApps,
    EAknSStatusPaneResourceId,
    EAknSStatusPaneAppResourceId,
    EAknSSetStatusPaneAppResourceId,
    EAknSRotateScreen,
    EAknSAppsKeyBlocked,
    EAknSShowLongTapAnimation,
    EAknSHideLongTapAnimation,
    EAknGetAliasKeyCode,
    EAknSetFgSpDataSubscriberId,
    EAknSCancelShutdownApps,
    EAknSGetPhoneIdleViewId,
    EAknSPreAllocateDynamicSoftNoteEvent,
    EAknSNotifyDynamicSoftNoteEvent,
    EAknSCancelDynamicSoftNoteEventNotification,
    EAknSDiscreetPopupAction
    };

enum TSuppressFunction
    {
    EAknAppsKeyBlockDecreaseCount = -1,
    EAknAppsKeyBlockRemoveClient,
    EAknAppsKeyBlockAddCount        
    };  

// Flag that menu's option has a task swapper or not
enum TAknMenuOptionNoTaskSwapper
	{
	ETaskSwapper,
	ENoTaskSwapper
	};

struct SAknCapServerSetSgcParams
    {
    TInt iWgId;
    TBitFlags iAppFlags;
    TInt iSpLayout;
    TInt iSpFlags;
    TInt iAppScreenMode;
    };

//----------------------------------------------
// Avkon alarm support related consts
//----------------------------------------------

#define KAknAlarmServiceUid TUid::Uid( 0x102072D4 )

// Complete interface must implement: public CAknAppServiceBase, public MAknAlarmServiceStartup !!! 
class MAknAlarmServiceStartup
    {
public: 
    virtual void StartupNewSessionL(TAny* aAny = 0) = 0;    
    };       

_LIT(KAknAlarmServiceLibrary, "aknalarmservice.dll");    
_LIT(KAknCapServerThreadName, "akncapserver");
_LIT(KRDSupport, "c:\\resource\\errrd"); // moved to be available for everyone
       
#endif // __AKNCAPSERVERDEF_H__
