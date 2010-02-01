/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  System Graphics Coordination Server.
*
*/

#ifndef EIKSGCS_H
#define EIKSGCS_H

#include <e32base.h>
#include <eikdef.h>
#include <w32std.h>
#include <babitflags.h>
#include <AknSgcc.h>
#include <ecompluginnotifier.h>

class CEikServStatusPane;
class CLayoutChangeCallBack;
class CAknCapAppServerAppUi;
class CWindowChangeMonitor;
class CAknCompaIf;

class CEikSgcServer : public CBase
    {
public:
    static CEikSgcServer* NewL();
    ~CEikSgcServer();

    void SetStatusPane(CEikServStatusPane* aSp);
    void SetAknCapAppServerAppUi(CAknCapAppServerAppUi* aAknCapAppServerAppUi);

    void HandleWindowGroupListChangeL();
    
    void HandleWindowGroupParamChangeL(
        TInt aWgId, 
        TBitFlags aAppFlags, 
        TInt aSpLayout, 
        TInt aSpFlags, 
        TInt aAppScreenMode);
        
    void PrepareForAppExitL(TInt aWgId);

    void HandleLayoutChangeCallBackL();
    void RelinquishPriorityToForegroundAppL(const RMessage2& aMessage);

    void RotateScreenL();

    void UpdateNotificationsInIdleAllowedKey();
	void FadeBitmapGenerationL();   
	void FadeColorGenerationL(); 
	
	void MoveAppL(TInt aAppWindowGroupId, TSgcMoveAppToWhere aWhere);

    static TInt LayoutInstallationCallBack(TAny* aPtr);
    
private:
    class TWgState
        {
    public:
        TWgState();
        TWgState(TInt aWgId);
        
        inline TInt WgId() const;
        inline void SetWgId(TInt aWgId);
        inline TInt SpLayout() const;
        inline void SetSpLayout(TInt aSpLayout);
        inline TInt SpFlags() const;
        inline void SetSpFlags(TInt aSpFlags);
        inline TBool IsFullScreen() const;
        inline void SetFullScreen(TBool aFullScreen);
        inline TBool IsPartialForeground() const;
        inline void SetPartialForeground(TBool aPartialForeground);
        inline TBool UnderstandsPartialForeground() const;
        inline void SetUnderstandsPartialForeground(TBool aPartialForeground);
        inline TBool IsLegacyLayout() const;
        inline void SetLegacyLayout(TBool aLegacyLayout);
        inline TBool IsOrientationSpecified() const;
        inline void SetOrientationSpecified(TBool aOrientationSpecified);
        inline TBool IsOrientationLandscape() const;
        inline void SetOrientationLandscape(TBool aOrientationLandscape);
        inline TInt AppScreenMode() const;
        inline void SetAppScreenMode(TInt aAppScreenMode);

    private:
        TInt iWgId;
        TBitFlags iFlags;
        TInt iSpLayout;
        TInt iSpFlags;
        TInt iAppScreenMode;
        };

    typedef CArrayFixFlat<TWgState> CWgStates;
    typedef CArrayFixFlat<TInt> CWgIds;

    enum TConstants { KStartAtTheTop = -1 };

private:
    CEikSgcServer();
    void ConstructL();

    TInt WgStateIndex(TInt aWgId) const;
    CWgIds* CreateWgIdListLC() const;
    void ReOrderWgStatesL(CWgIds* aWgIds);
    void SetStatusPaneShapeAndFlagsL(TInt aSpIndex);
    void SetPartialForegroundStatusesL();
    void PostChangeRecalcL();
    TWgState& GetWgStateL(TInt aWgId);
    TBool TestWgListOrderOk(CWgIds* aWgIds) const;
    TInt FocusWgIndex() const;
    void SetWgPartialFg(TWgState& aWgState);
    void ClearWgPartialFg(TWgState& aWgState);
    TInt TopSpIndex(TInt aAfter = KStartAtTheTop) const;
    void SetLayoutL(TInt aSpIndex);
    static TInt RemoveBlankCallBack(TAny* aThis);
    void DoRemoveBlank();
    static TInt CEikSgcServer::RestoreThreadPriorities(TAny* aThis);
    void DoRestoreThreadPriorities();
    void ActivateEffectL();
    void SetLayoutBlankScreenL(TBool aBlank, TInt aStep);
    void SetLayoutBlankScreenL(TBool aBlank, TInt aStep, TInt aCnt);
    TBool IsGlobalNoteForeground();
    void DoMoveApp();
    TInt RefreshLayoutIfRequiredL();
    
private:
    CWgStates* iWgStates;
    RWsSession& iWs;
    CEikServStatusPane* iSp;
    RWindowGroup* iSpWg;
    TInt iLayout;
    TInt iFlags;
    TInt iLastTopSpWg;
    TInt iLastScreenModeSet;
    CLayoutChangeCallBack* iLayoutChangeCallBack;
    struct SRelinquishedThread
        {
        RThread iThread;
        TThreadId iId;
        TProcessPriority iPriority;
        };
    typedef RArray<SRelinquishedThread> RRelinquishedThreadList;
    RRelinquishedThreadList iRelinquishedThreads;
    CPeriodic* iRelinquishedThreadCallBack;
    CAknCapAppServerAppUi* iAknCapAppServerAppUi;
    TInt iFirstFullScreenWg; // Not sure if iLastTopSpWg could be used directly.
    TInt iBlankCount;
    CPeriodic* iRemoveBlankCallBack;
    TInt iRemoveBlankCount;
private:
    CWindowChangeMonitor* iWinChange;
    TBool iNotificationsInIdleAllowed;
private:
    CFbsBitmap *iFadeBitmap;
    CFbsBitmap *iFadeMask;
    TInt iSetLayoutBlankStep;
   	TInt iMoveAppWdId;
	TSgcMoveAppToWhere iMoveAppWhere;
    // Touch compatibility mode interface and screen mode
	CAknCompaIf* iTouchCompaModeIf;
	TInt iTouchCompaScreenMode;
    CEComPluginNotifier* iLayoutNotifier; // Owned
    REComPluginInfoArray iPrevPluginInfo;
    };

#endif // EIKSGCS_H
