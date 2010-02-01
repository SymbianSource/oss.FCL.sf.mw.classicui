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
* Description:  
*
*/

#ifndef __AKN_CAP_SERVER_CLIENT__
#define __AKN_CAP_SERVER_CLIENT__

#include <babitflags.h>
#include <eikserverapp.h>
#include <aknanimdllstd.h>
#include <vwsdef.h>
#include <w32std.h>

class TAknDiscreetPopupData;


enum TAknDefaultKeyboardRepeatRate{
    EAknApplicationDefaulRepeatRate, 
    EAknEditorDefaulRepeatRate
    };

class RAknUiServer : public REikAppServiceBase 
    {
public:
    IMPORT_C TInt ConnectAndSendAppsKeySuppress(TBool aSuppress);
    IMPORT_C TInt HideApplicationFromFsw(TBool aHide, TInt aMyUid);
    IMPORT_C void UnlockMedia(TInt aDrive, TBool aStore, TRequestStatus& aStatus);
    IMPORT_C void CancelUnlockMedia();
    IMPORT_C TInt EnableTaskList(TBool aEnable);
    IMPORT_C TInt MakeTaskListVisible(TBool aShow);
    IMPORT_C TInt UpdateTaskList();
    IMPORT_C void ShutdownApps(const TUid aRequesterUID, const TInt aTimeoutInMicroseconds, 
        TRequestStatus& aStatus) const;
    IMPORT_C void CancelShutdownApps();
    // These functions are only for use by CAknSgcClient
    IMPORT_C TInt SetSgcParams(TInt aWgId, TBitFlags aAppFlags, TInt aSpLayout, TInt aSpFlags);
    IMPORT_C TInt SetSgcParams(TInt aWgId, TBitFlags aAppFlags, TInt aSpLayout, TInt aSpFlags, 
        TInt aAppScreenMode);
    IMPORT_C TInt BlockServerStatusPaneRedraws();
    IMPORT_C TInt RedrawServerStatusPane();
    IMPORT_C TInt PrepareForAppExit(TInt aWgId);
    IMPORT_C TInt SetSystemFaded(TBool aFade);
    IMPORT_C TInt IsSystemFaded(TBool& aFade) const;
    IMPORT_C TInt Connect();
    IMPORT_C TInt RelinquishPriorityToForegroundApp();
    IMPORT_C HBufC8* GetPackedConfigL() const;
    IMPORT_C TInt MoveAppInZOrder(TInt aAppWindowGroupId, TBool aBackgroundOrForeground);
    // Eiksrv replacements.
    IMPORT_C TInt SetStatusPaneFlags(TInt aFlags) const;
    IMPORT_C TInt SetStatusPaneLayout(TInt aLayoutResId) const;
    IMPORT_C TInt BlankScreen() const;
    IMPORT_C TInt UnblankScreen() const;
    // Basic functionality, allowed for every application. 
    IMPORT_C TInt SetKeyboardRepeatRate(TAknDefaultKeyboardRepeatRate aRate);
    IMPORT_C TInt SetKeyblockMode(TAknKeySoundOpcode aMode);
    IMPORT_C TInt DoEikonServerConnect();
    IMPORT_C TInt ShowKeysLockedNote(TBool& aIsKeyPadLocked);
    IMPORT_C TInt ShowGlobalNoteL(const TDesC& aNoteText, TInt aGlobalNoteType);
    IMPORT_C TInt StatusPaneResourceId();
    IMPORT_C TInt CreateActivateViewEventL(const TVwsViewId& aViewId, TUid aCustomMessageId, 
        const TDesC8& aCustomMessage);
    // Statuspane internal use.
    IMPORT_C TInt CurrentAppStatuspaneResource();
    IMPORT_C TInt SetCurrentAppStatuspaneResource(TInt aResourceId);
    IMPORT_C TInt SetFgSpDataSubscriberId(TInt aId);
    IMPORT_C TInt RotateScreen();
    // For querying Apps key status.
    IMPORT_C TBool TaskSwitchingSupressed();
    // Long tap animation related.
    IMPORT_C  TInt ShowLongTapAnimation( const TPointerEvent& aEvent );
    IMPORT_C  TInt HideLongTapAnimation();
    // Misc methods.
    IMPORT_C TInt GetAliasKeyCode(TUint& aCode, const TKeyEvent& aKeyEvent, TEventCode aType);
    IMPORT_C TInt GetPhoneIdleViewId( TVwsViewId& aViewId );
    // Entry point for starter.
    IMPORT_C static void StartAknCapserverL();
    // Internal to eikon server (Sid-based security check will fail on any other client).
    IMPORT_C TInt DoNotifierControllerCommand(TInt aNotifierControllerCommand);
    
    /**
     * Pre-allocates memory for dynamic soft note observation event.
     *
     * @param aNoteId Dynamic soft note id to be observed.
     * @return KErrNone if succesful. Otherwise a system-wide error code. 
     * @internal
     */ 
    IMPORT_C TInt PreAllocateDynamicSoftNoteEvent(TInt aNoteId);    
    
    /**
     * Registers a client as an observer for dynamic soft note events.
     * Method is asynchronous. Completes when soft note is accepted or canceled.
     *
     * @param aStatus On completion, KErrNone if successful. Otherwise a system-wide error code.
     * @param aActionId On completion, a value from TAknDynamicSNoteEvent.
     * @internal
     */ 
    IMPORT_C void NotifyDynamicSoftNoteEvent(TRequestStatus& aStatus, TDes8& aActionId);

    /**
     * Cancels dynamic soft note observing. 
     * @internal
     */ 
    IMPORT_C void CancelDynamicSoftNoteEventNotification();

    /**
     * Asks cap server to do discreet popup action.
     * Method is asynchronous if aStatus is not NULL.
     *
     * @since S60 v5.2
         * @internal
     * @param aData Discreet popup data.
     * @param aStatus Status code depending on action.
     */
    IMPORT_C void DoDiscreetPopupAction(
            TAknDiscreetPopupData* aData, TRequestStatus* aStatus = NULL );

    
    /**
     * Query cap server about in use global discreet popup's rectangle
     * 
     * @return the rectangle discreet popup occupied. return TRect::EUninitialized 
     *         if no global discreet popup displayed at present.
     * @since  S60 v5.2
     * 
     */
    IMPORT_C const TRect GetInUseGlobalDiscreetPopupRect();
    
private:
    TInt ConnectAknServer();
    IMPORT_C TUid ServiceUid() const; 

private:
    TInt iSpare;
    };

IMPORT_C TInt AknStartupApaServerProcess();
    
#endif // __AKN_CAP_SERVER_CLIENT__
