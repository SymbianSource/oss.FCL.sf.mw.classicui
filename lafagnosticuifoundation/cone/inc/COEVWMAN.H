// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#ifndef __COEVWMAN_H__
#define __COEVWMAN_H__

#include <viewcli.h>	// class MVwsSessionWrapperObserver

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <vwsdefpartner.h>
#endif

class CCoeAppUi;
class CCoeEnv;
class MCoeView;
class MCoeViewDeactivationObserver;
class MCoeViewActivationObserver;
class CCoeControl;
class CCoeView;
class MCoeViewObserver;
class CCoeViewObserver;
class CVwsSessionWrapper;


/**
 * The CCoeViewManager class provides Cone's view management and implements the view specific functionality accessed
 * through the CCoeAppUi API.
 *
 */
class CCoeViewManager : public CBase, public MVwsSessionWrapperObserver
	{
public:
	static CCoeViewManager* NewL(CCoeEnv& aCoeEnv,CCoeAppUi& aAppUi,CCoeAppUi* aPreviousAppUi);
	~CCoeViewManager();
private:
	CCoeViewManager(CCoeEnv& aCoeEnv,CCoeAppUi& aAppUi,CCoeAppUi* aPreviousAppUi);
	void ConstructL();
public: // view activation
	void ActivateViewL(const TVwsViewId& aViewId, TBool aActivatingTopView = EFalse);
	void ActivateViewL(const TVwsViewId& aViewId,const TUid& aCustomMessageId,const TDesC8& aCustomMessage, TBool aActivatingTopView = EFalse);
	void ActivateTopViewL();
	void DeactivateActiveViewL();
	void DeactivateActiveViewIfOwnerMatchL();
	void CreateActivateViewEventL(const TVwsViewId& aViewId,const TUid& aCustomMessageId,const TDesC8& aCustomMessage);
public: // view registration
	void RegisterViewL(MCoeView& aView);
	void DeregisterView(const MCoeView& aView);
	void RegisterApplicationViewL(const TUid& aAppUid);			
	void DeregisterApplicationView();
	void CheckInitializeViewsL(const TUid& aAppUid);
	void SetDefaultViewL(const MCoeView& aView);
	void SetApplicationViewAsDefaultL();
	TInt GetDefaultViewId(TVwsViewId& aViewId) const;
	TInt GetActiveViewId(TVwsViewId& aViewId) const;
public: // view switch observation
	void AddViewDeactivationObserverL(MCoeViewDeactivationObserver* aViewDeactivationObserver);
	void RemoveViewDeactivationObserver(MCoeViewDeactivationObserver* aViewDeactivationObserver);
	void NotifyNextDeactivation(const TVwsViewId& aViewId, MCoeViewDeactivationObserver& aViewDeactivationObserver);
	void NotifyNextDeactivation(MCoeViewDeactivationObserver& aViewDeactivationObserver);
	void AddViewActivationObserverL(MCoeViewActivationObserver* aViewActivationObserver);
	void RemoveViewActivationObserver(MCoeViewActivationObserver* aViewActivationObserver);
	void NotifyNextActivation(const TVwsViewId& aViewId, MCoeViewActivationObserver& aViewActivationObserver);
	void NotifyNextActivation(MCoeViewActivationObserver& aViewActivationObserver);
	void AddViewObserverL(MCoeViewObserver* aViewObserver);
	void RemoveViewObserver(MCoeViewObserver* aViewObserver);
public: // View session configuration
	TInt EnableExternalViewSwitches(TBool aEnable);
private: // From MVwsSessionWrapperObserver.
	void HandleViewEventL(const TVwsViewEvent& aEvent);
public: // view related interfaces.
	void DoActivationL(const TVwsViewId& aViewId,const TVwsViewId& aPreviousViewId,const TUid& aCustomMessageId,TInt aCustomMessageLength);
	void DoDeactivation(const TVwsViewId& aViewId, const TVwsViewId& aActiveViewId, const TVwsViewEvent::TVwsViewEventType aType);
	void HandleViewDeactivationNotification(const TVwsViewId& aViewId,const TVwsViewId& aActiveViewId);
	void HandleViewActivationNotification(const TVwsViewId& aActiveViewId,const TVwsViewId& aViewToDeactivatedId);
	TVwsViewIdAndMessage HandleScreenDeviceChangedL(const TVwsViewId& aViewId);
	TInt ViewIndex(const MCoeView& aView) const;
	TInt ViewIndex(const TVwsViewId& aViewId) const;
 	void SetSystemDefaultViewL(const TVwsViewId& aViewId,TInt aMode);
	void SetSystemDefaultViewL(const TVwsViewId& aViewId);
 	TBool IsViewConstructed(const TVwsViewId& aViewId) const;
	void GetSystemDefaultViewL(TVwsViewId& aViewId);
	TBool CheckSourceOfViewSwitchL(const TSecurityPolicy& aSecurityPolicy,const char* aDiagnostic) const;
	TInt GetTopViewId(TVwsViewId& aViewId) const;
	void SetCustomControl(const TInt aCustomControl);
	void SetWindowGroupOrdinal(const TInt aWindowGroupOrdinal);
	void UpdateViewServerBackgroundColor(const TRgb& aBgColor);
private:
	friend class CTestDriver;
private:
	void CompleteActivation(TInt aActiveViewIndex,const TVwsViewId& aViewId,const TVwsViewId& aPreviousViewId);
private:
	CCoeAppUi& iAppUi;
	CCoeEnv& iCoeEnv;
	TPtrC8 iCustomMessage;
	CCoeAppUi* iPreviousAppUi;
	TBool iRegisteredApplicationView;
	CCoeViewObserver* iViewObserver;
	CArrayPtrFlat<CCoeView> iViewArray;
	CVwsSessionWrapper* iVwsSession;
	CArrayPtrFlat<MCoeViewDeactivationObserver> iViewDeactivationObserverArray;
	MCoeViewDeactivationObserver* iNextViewDeactivationObserver;
	CArrayPtrFlat<MCoeViewActivationObserver> iViewActivationObserverArray;
	MCoeViewActivationObserver* iNextViewActivationObserver;
	CArrayPtrFlat<MCoeViewObserver> iViewObserverArray;
	TInt iActiveViewIndex;
	TVwsViewId iDefaultViewId;
	TVwsViewId iLastActiveViewId;
	TVwsViewId iActiveViewId;
	TVwsViewId iApplicationViewId;
	TBool iActivatingTopView;
	TVwsViewId iActivatingViewId;
	TInt iCustomControl;
	TInt iWindowGroupOrdinal;
	};

#endif // __COEVWMAN_H__
