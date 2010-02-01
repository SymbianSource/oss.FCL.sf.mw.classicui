// Copyright (c) 2000-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "COEVWMAN.H"
#include "coepriv.h"	// CCoeView
#include <coeaui.h>
#include "coepanic.h"
#include <coecntss.h>

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <viewclipartner.h>
#endif

const TInt KViewArrayGranularity=5;

//
// Class CCoeViewObserver
//

class CCoeViewObserver : public CBase, public MCoeViewObserver
	{
public:
	CCoeViewObserver(CCoeViewManager& aViewManager);
	~CCoeViewObserver();
public: // from MCoeViewObserver
	void HandleViewEventL(const TVwsViewEvent& aEvent);
private:
	CCoeViewManager& iViewManager;
	};

CCoeViewObserver::~CCoeViewObserver()
	{}

CCoeViewObserver::CCoeViewObserver(CCoeViewManager& aViewManager)
	: iViewManager(aViewManager)
	{}

void CCoeViewObserver::HandleViewEventL(const TVwsViewEvent& aEvent)
	{
	switch (aEvent.iEventType)
		{
		case TVwsViewEvent::EVwsDeactivateView:
			{
			TVwsViewId viewId;
			if (iViewManager.GetActiveViewId(viewId) != KErrNotFound)
				iViewManager.DoDeactivation(viewId, aEvent.iViewTwoId, TVwsViewEvent::EVwsDeactivateView);
			}
			break;
		default:
			break;
		}
	}

//
// Class CCoeViewManager
//

CCoeViewManager::CCoeViewManager(CCoeEnv& aCoeEnv,CCoeAppUi& aAppUi,CCoeAppUi* aPreviousAppUi)
	: iAppUi(aAppUi), iCoeEnv(aCoeEnv), iPreviousAppUi(aPreviousAppUi), iRegisteredApplicationView(EFalse),
	  iViewArray(KViewArrayGranularity), iViewDeactivationObserverArray(KViewArrayGranularity),
	  iViewActivationObserverArray(KViewArrayGranularity), iViewObserverArray(KViewArrayGranularity),
	  iActiveViewIndex(KErrNotFound), iDefaultViewId(KNullViewId),
	  iLastActiveViewId(KNullViewId), iActiveViewId(KNullViewId), iApplicationViewId(KNullViewId)
	{
	}

void CCoeViewManager::ConstructL()
	{
	iVwsSession=iCoeEnv.InitViewServerSessionL(*this);
	if (iPreviousAppUi)
		{
		iViewObserver=new(ELeave) CCoeViewObserver(*this);
		AddViewObserverL(iViewObserver);
		}
	}

CCoeViewManager* CCoeViewManager::NewL(CCoeEnv& aCoeEnv,CCoeAppUi& aAppUi,CCoeAppUi* aPreviousAppUi)
	{
	CCoeViewManager* self=new(ELeave) CCoeViewManager(aCoeEnv,aAppUi,aPreviousAppUi);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();	// self
	return self;
	}

CCoeViewManager::~CCoeViewManager()
	{
	if (iRegisteredApplicationView)
		{
		DeregisterApplicationView();
		}

	if (iPreviousAppUi)
		{
		RemoveViewObserver(iViewObserver);
		delete iViewObserver;
		}

	iViewArray.ResetAndDestroy();
	iViewDeactivationObserverArray.Reset();
	iViewActivationObserverArray.Reset();
	iViewObserverArray.Reset();
	}

void CCoeViewManager::HandleViewEventL(const TVwsViewEvent& aEvent)
	{
	switch (aEvent.iEventType)
		{
		case TVwsViewEvent::EVwsActivateView:
			DoActivationL(aEvent.iViewOneId,aEvent.iViewTwoId,aEvent.iCustomMessageId,aEvent.iCustomMessageLength);
			break;
		case TVwsViewEvent::EVwsDeactivateView:
		case TVwsViewEvent::EVwsDeactivateViewDifferentInstance:
			DoDeactivation(aEvent.iViewOneId, aEvent.iViewTwoId, aEvent.iEventType);
			break;
		case TVwsViewEvent::EVwsScreenDeviceChanged:
			{
			TVwsViewIdAndMessage event;
			TRAP_IGNORE(event=HandleScreenDeviceChangedL(aEvent.iViewOneId));
			iVwsSession->ActivateViewViaViewEvent(event);
			}
			break;
		case TVwsViewEvent::EVwsDeactivationNotification:
			HandleViewDeactivationNotification(aEvent.iViewOneId,aEvent.iViewTwoId);
			break;
		case TVwsViewEvent::EVwsActivationNotification:
			HandleViewActivationNotification(aEvent.iViewOneId,aEvent.iViewTwoId);
			break;
		default:
			Panic(ECoePanicViewEventNotHandled);
			break;
		}

	const TInt numObservers=iViewObserverArray.Count();
	for (TInt ii=0;ii<numObservers;ii++)
		{
		iViewObserverArray[ii]->HandleViewEventL(aEvent);
		}
	}

void CCoeViewManager::ActivateViewL(const TVwsViewId& aViewId, TBool aActivatingTopView)
 	{
	ActivateViewL(aViewId,TUid::Null(),KNullDesC8,aActivatingTopView);
 	}

void ClearActivatingTopViewFlag(TAny* aFlagPtr)
 	{
	*(TBool*)aFlagPtr = EFalse;
 	}

void CCoeViewManager::ActivateViewL(const TVwsViewId& aViewId,const TUid& aCustomMessageId,const TDesC8& aCustomMessage,TBool aActivatingTopView)
 	{
 	// Ignore duplicate ActivatingTopView request when there is already one outstanding.
 	if (iActivatingTopView && aActivatingTopView)
 	    {
 	    return;
 	    }
	iActivatingTopView = aActivatingTopView;
	CleanupStack::PushL(TCleanupItem(ClearActivatingTopViewFlag, &iActivatingTopView));
	if (iPreviousAppUi)
		{
		if (ViewIndex(aViewId)!=KErrNotFound || aViewId==iApplicationViewId)
			{
			iCustomMessage.Set(aCustomMessage);
			TVwsViewId viewIdToDeactivate = (aViewId==iLastActiveViewId) ? KNullViewId : iLastActiveViewId;
			DoActivationL(aViewId,viewIdToDeactivate,aCustomMessageId,iCustomMessage.Length());
			if (viewIdToDeactivate!=KNullViewId && viewIdToDeactivate!=aViewId)
				{
				DoDeactivation(viewIdToDeactivate, aViewId, TVwsViewEvent::EVwsDeactivateView);
				}
			}
		else
			{
			iPreviousAppUi->ActivateViewL(aViewId,aCustomMessageId,aCustomMessage);
			}
		}
	else
		{
		if (aViewId == iDefaultViewId && aViewId.iAppUid == aViewId.iViewUid)
			{
			// If were activating the default view of a non-view based app, don't wait for viewsrv to respond.
			CreateActivateViewEventL(aViewId, aCustomMessageId, aCustomMessage);
			// record this view as activated to prevent it getting activated twice.
			iActiveViewId = aViewId;
			}
		else
			{
			iCustomMessage.Set(KNullDesC8);
			TInt err=iVwsSession->ActivateView(aViewId,aCustomMessageId,aCustomMessage, iCustomControl);
			if (err == KErrOverflow)
				{
				// avkon hides overflow messages on view activation
				err = KLeaveWithoutAlert;
				}
			User::LeaveIfError(err);
			}
		}
	CleanupStack::Pop(); // flag cleanup item
	}

void CCoeViewManager::DeactivateActiveViewL()
	{
	if (iPreviousAppUi)
		{
		iPreviousAppUi->DeactivateActiveViewL();
		}
	else
		{
		User::LeaveIfError(iVwsSession->DeactivateActiveView());
		}
	}
void CCoeViewManager::DeactivateActiveViewIfOwnerMatchL()
	{
 	if (iPreviousAppUi)
 		{
 		iPreviousAppUi->DeactivateActiveViewIfOwnerMatchL();
 		}
 	else
 		{
 		User::LeaveIfError(iVwsSession->DeactivateActiveViewIfOwnerMatch());
 		}
 	}
 

void CCoeViewManager::ActivateTopViewL()
	{
	if (iPreviousAppUi)
		{
		iPreviousAppUi->ActivateTopViewL();
		}
	
	if (iActiveViewId!=KNullViewId)
		{
		TVwsViewId activeViewId;
		TInt err = iVwsSession->GetCurrentActiveViewInSystem(activeViewId);
		if ((err == KErrNone) && (iActiveViewId == activeViewId))
			{
			return;
			}
		}

	if (iLastActiveViewId!=KNullViewId)
		{
		ActivateViewL(iLastActiveViewId, ETrue);
		}
	else if (iDefaultViewId!=KNullViewId)
		{
		ActivateViewL(iDefaultViewId, ETrue);
		}
	else if (iViewArray.Count())
		{
		ActivateViewL(iViewArray[0]->iView.ViewId(), ETrue);
		}
	else if (iApplicationViewId!=KNullViewId)
		{
		ActivateViewL(iApplicationViewId, ETrue);
		}
	}

TInt CCoeViewManager::GetActiveViewId(TVwsViewId& aViewId) const
	{
	if (iActiveViewId!=KNullViewId)
		{
		aViewId=iActiveViewId;
		return KErrNone;
		}

	return KErrNotFound;
	}

void CCoeViewManager::RegisterViewL(MCoeView& aView)
	{
	CCoeView* newView=CCoeView::NewLC(aView);
	iViewArray.AppendL(newView);
	CleanupStack::Pop(); // newView
	if (!iPreviousAppUi)
		{
		TInt err=iVwsSession->AddView(aView.ViewId());
		if (err)
			{
			iViewArray.Delete(ViewIndex(aView));
			User::Leave(err);
			}
		}
	}

void CCoeViewManager::RegisterApplicationViewL(const TUid& aAppUid)
	{
	TVwsViewId viewId(aAppUid,aAppUid);
	if (!iPreviousAppUi)
		{
		TInt err=iVwsSession->AddView(viewId);
		if (err!=KErrCouldNotConnect && err!=KErrNone)
			{
			User::Leave(err);
			}
		}
	iApplicationViewId=viewId;
	iDefaultViewId=viewId;
	}

void CCoeViewManager::DeregisterApplicationView()
	{
	if (!iPreviousAppUi && iApplicationViewId!=KNullViewId)
		{
		iVwsSession->RemoveView(iApplicationViewId);	// ignore error
		}
	iApplicationViewId=KNullViewId;
	}

void CCoeViewManager::SetDefaultViewL(const MCoeView& aView)
	{
	iDefaultViewId=aView.ViewId();
	}

void CCoeViewManager::SetApplicationViewAsDefaultL()
	{
	__ASSERT_DEBUG(iApplicationViewId!=KNullViewId,Panic(ECoePanicViewNotFound));
	iDefaultViewId=iApplicationViewId;
	}

void CCoeViewManager::CheckInitializeViewsL(const TUid& aAppUid)
	{
	const TInt count=iViewArray.Count();
	
	// Register application view if there are no views
	if (count==0 && iApplicationViewId==KNullViewId)
		{
		RegisterApplicationViewL(aAppUid);
		iRegisteredApplicationView=ETrue;
		}
	
	// Set default view if none set
	if (iDefaultViewId==KNullViewId)
		{
		if (count==0)
			{
			SetApplicationViewAsDefaultL();
			}
		else
			{
			iDefaultViewId=iViewArray[0]->iView.ViewId();
			}
		}
	}

TInt CCoeViewManager::GetDefaultViewId(TVwsViewId& aViewId) const
	{
	if (iDefaultViewId!=KNullViewId)
		{
		aViewId=iDefaultViewId;
		return KErrNone;
		}

	return KErrNotFound;
	}

void CCoeViewManager::DeregisterView(const MCoeView& aView)
	{
	const TInt viewIndex=ViewIndex(aView);
	if (viewIndex == KErrNotFound)
		return;

	if (!iPreviousAppUi)
		{
		__ASSERT_ALWAYS(iVwsSession,Panic(ECoePanicNoViewServerConnection));
		iVwsSession->RemoveView(aView.ViewId());	// Ignore error.
		if(aView.ViewId()==iLastActiveViewId)
			{
			iLastActiveViewId=KNullViewId;
			}
		}
	
	if (iActiveViewIndex>viewIndex)
		{
		iActiveViewIndex--;
		if (iPreviousAppUi)
			{
			if (iActiveViewIndex>=0)
				{
				iActiveViewId=iViewArray[iActiveViewIndex]->iView.ViewId();
				}
			else
				{
				iActiveViewId=KNullViewId;
				}
			iAppUi.SetCurrentControlStackGroupId(iActiveViewId.iViewUid.iUid);
			}
		}

	delete iViewArray[viewIndex];
	iViewArray.Delete(viewIndex);
	}

void CCoeViewManager::AddViewDeactivationObserverL(MCoeViewDeactivationObserver* aViewDeactivationObserver)
	{
	iViewDeactivationObserverArray.AppendL(aViewDeactivationObserver);
	}

void CCoeViewManager::RemoveViewDeactivationObserver(MCoeViewDeactivationObserver* aViewDeactivationObserver)
	{
	TInt pos;
	TKeyArrayFix key(0,ECmpTInt);
	if (iViewDeactivationObserverArray.Find(aViewDeactivationObserver,key,pos)==KErrNone)
		{
		iViewDeactivationObserverArray.Delete(pos);
		}
	}

void CCoeViewManager::NotifyNextDeactivation(const TVwsViewId& aViewId, MCoeViewDeactivationObserver& aViewDeactivationObserver)
	{
	__ASSERT_DEBUG(iNextViewDeactivationObserver==NULL,Panic(ECoePanicViewNotificationObserverAlreadyExists));
	__ASSERT_ALWAYS(iVwsSession,Panic(ECoePanicNoViewServerConnection));

	iNextViewDeactivationObserver=&aViewDeactivationObserver;
	iVwsSession->NotifyNextDeactivation(aViewId);
	}

void CCoeViewManager::NotifyNextDeactivation(MCoeViewDeactivationObserver& aViewDeactivationObserver)
	{
	__ASSERT_DEBUG(iNextViewDeactivationObserver==NULL,Panic(ECoePanicViewNotificationObserverAlreadyExists));
	__ASSERT_ALWAYS(iVwsSession,Panic(ECoePanicNoViewServerConnection));

	iNextViewDeactivationObserver=&aViewDeactivationObserver;
	iVwsSession->NotifyNextDeactivation();
	}

void CCoeViewManager::AddViewActivationObserverL(MCoeViewActivationObserver* aViewActivationObserver)
	{
	iViewActivationObserverArray.AppendL(aViewActivationObserver);
	}

void CCoeViewManager::RemoveViewActivationObserver(MCoeViewActivationObserver* aViewActivationObserver)
	{
	TInt pos;
	TKeyArrayFix key(0,ECmpTInt);
	if (iViewActivationObserverArray.Find(aViewActivationObserver,key,pos)==KErrNone)
		{
		iViewActivationObserverArray.Delete(pos);
		}
#ifdef _DEBUG
	else
		{
		RDebug::Printf("CCoeViewManager::RemoveViewActivationObserver. Coe view observer not found.");		
		}
#endif
	}

void CCoeViewManager::NotifyNextActivation(const TVwsViewId& aViewId, MCoeViewActivationObserver& aViewActivationObserver)
	{
	__ASSERT_DEBUG(iNextViewActivationObserver==NULL,Panic(ECoePanicViewNotificationObserverAlreadyExists));
	__ASSERT_ALWAYS(iVwsSession,Panic(ECoePanicNoViewServerConnection));

	iNextViewActivationObserver=&aViewActivationObserver;
	iVwsSession->NotifyNextActivation(aViewId);
	}

void CCoeViewManager::NotifyNextActivation(MCoeViewActivationObserver& aViewActivationObserver)
	{
	__ASSERT_DEBUG(iNextViewActivationObserver==NULL,Panic(ECoePanicViewNotificationObserverAlreadyExists));
	__ASSERT_ALWAYS(iVwsSession,Panic(ECoePanicNoViewServerConnection));

	iNextViewActivationObserver=&aViewActivationObserver;
	iVwsSession->NotifyNextActivation();
	}

void CCoeViewManager::AddViewObserverL(MCoeViewObserver* aViewObserver)
	{
	if (iPreviousAppUi)
		{
		iPreviousAppUi->AddViewObserverL(aViewObserver);
		}
	else
		{
		iViewObserverArray.AppendL(aViewObserver);
		}
	}

void CCoeViewManager::RemoveViewObserver(MCoeViewObserver* aViewObserver)
	{
	if (iPreviousAppUi)
		{
		iPreviousAppUi->RemoveViewObserver(aViewObserver);
		}
	else
		{
		TInt pos;
		TKeyArrayFix key(0,ECmpTInt);
		if (iViewObserverArray.Find(aViewObserver,key,pos)==KErrNone)
			{
			iViewObserverArray.Delete(pos);
			}
		}
	}

TInt CCoeViewManager::ViewIndex(const MCoeView& aView) const
	{
	const TInt numViews=iViewArray.Count();
	
	for (TInt ii=0;ii<numViews;ii++)
		{
		const MCoeView& view=iViewArray[ii]->iView;
		if (&view==&aView)
			{
			return ii;
			}
		}

	return KErrNotFound;
	}

TInt CCoeViewManager::ViewIndex(const TVwsViewId& aViewId) const
	{
	const TInt numViews=iViewArray.Count();
	
	for (TInt ii=0;ii<numViews;ii++)
		{
		if (iViewArray[ii]->iView.ViewId()==aViewId)
			{
			return ii;
			}
		}

	return KErrNotFound;
	}

void CCoeViewManager::DoActivationL(const TVwsViewId& aViewId,const TVwsViewId& aPreviousViewId,const TUid& aCustomMessageId,TInt aCustomMessageLength)
	{
	// Retrieve custom message from server if necessary.
	HBufC8* customMessage=NULL;
	if (aCustomMessageLength)
		{
		if (!iPreviousAppUi)
			{
			customMessage=HBufC8::NewLC(aCustomMessageLength);
			TPtr8 msgPtr=customMessage->Des();
			User::LeaveIfError(iVwsSession->RequestCustomMessage(msgPtr));
			}
		else
			{
			customMessage=iCustomMessage.AllocLC();
			}
		}

	if (aViewId.iViewUid.iUid==aViewId.iAppUid.iUid)
		{
		if (customMessage)
			{
			CleanupStack::PopAndDestroy(customMessage); 
			}
		CompleteActivation(-1,aViewId,aPreviousViewId);
		return;
		}

	// Find the index to activate
	TInt indexToActivate=ViewIndex(aViewId);
	__ASSERT_ALWAYS(indexToActivate!=KErrNotFound, Panic(ECoePanicViewNotFound));
	CCoeView& viewToActivate=*(iViewArray[indexToActivate]);

	// If first activation, construct.
	if (!(viewToActivate.iConstructed))
		{
		viewToActivate.iView.ViewConstructL();
		viewToActivate.iConstructed=ETrue;
		}
		
	// check if view has a preferred screen mode
	viewToActivate.iView.PrepareForViewActivation();
	
	// check view can cope with screenmode
	const TInt screenMode=iCoeEnv.ScreenDevice()->CurrentScreenMode();
	if (!viewToActivate.iView.ViewScreenModeCompatible(screenMode))
		{
		User::Leave(KErrViewWrongMode);
		}
	iActivatingViewId = aViewId;
	// Do the activation.
	if (customMessage)
		{
		viewToActivate.iView.ViewActivatedL(aPreviousViewId,aCustomMessageId,*customMessage);
		CleanupStack::PopAndDestroy(customMessage);  
		}
	else
		{
		viewToActivate.iView.ViewActivatedL(aPreviousViewId,aCustomMessageId,KNullDesC8);
		}
	CompleteActivation(indexToActivate,aViewId,aPreviousViewId);
	}

TBool CCoeViewManager::CheckSourceOfViewSwitchL(const TSecurityPolicy& aSecurityPolicy,const char* aDiagnostic) const
	{
	if (iPreviousAppUi!=NULL)
		{
		return iPreviousAppUi->CheckSourceOfViewSwitchL(aSecurityPolicy,aDiagnostic);
		}
	TBool result=EFalse;
	User::LeaveIfError(iVwsSession->CheckSourceOfViewSwitch(result,aSecurityPolicy,aDiagnostic));
	return result;
	}

void CCoeViewManager::CompleteActivation(TInt aActiveViewIndex,const TVwsViewId& aViewId,const TVwsViewId& aPreviousViewId)
	{
	const TInt numObservers=iViewActivationObserverArray.Count();
	for (TInt ii=0;ii<numObservers;ii++)
		{
		iViewActivationObserverArray[ii]->HandleViewActivation(aViewId,aPreviousViewId);
		}
	
	// 	Should the ordinal only be set as long as the top view is not active?
	if(CCoeControlStaticSettings::OrdinalForAllViews() == EFalse) // default behaviour
		{
		if (!iActivatingTopView)
			{
			if(!iCustomControl)
				{
				iCoeEnv.WsSession().SetWindowGroupOrdinalPosition(iCoeEnv.RootWin().Identifier(),iWindowGroupOrdinal);	
				}
			}
			// else do nothing
		}
	else // Set for all views
		{
		if(!iCustomControl)
			{
			iCoeEnv.WsSession().SetWindowGroupOrdinalPosition(iCoeEnv.RootWin().Identifier(),iWindowGroupOrdinal);
			}
		}
		
	iActivatingTopView = EFalse;
	iActiveViewIndex=aActiveViewIndex;
	iActiveViewId=aViewId;
	iAppUi.SetCurrentControlStackGroupId(iActiveViewId.iViewUid.iUid);
	iLastActiveViewId=aViewId;
	}

void CCoeViewManager::DoDeactivation(const TVwsViewId& aViewId, const TVwsViewId& aActiveViewId, const TVwsViewEvent::TVwsViewEventType aType)
	{
	const TInt numObservers=iViewDeactivationObserverArray.Count();
	for (TInt ii=0;ii<numObservers;ii++)
		{
		iViewDeactivationObserverArray[ii]->HandleViewDeactivation(aViewId,aActiveViewId);
		}

	if (aViewId.iViewUid.iUid != aViewId.iAppUid.iUid)
		{	// Only deactive if not a pseudo-application view.
		TInt indexToDeactivate=ViewIndex(aViewId);
		__ASSERT_ALWAYS(indexToDeactivate!=KErrNotFound, Panic(ECoePanicViewNotFound));
		iViewArray[indexToDeactivate]->iView.ViewDeactivated();
		}
		
	/**	Reset active view record if:
	1. Newly activated view is not in this app
	2. The view to activate and view to deactivate are from different instances of the same application
	*/
	if ((aViewId.iAppUid!=aActiveViewId.iAppUid) || (aType == TVwsViewEvent::EVwsDeactivateViewDifferentInstance))
		{
		iActiveViewIndex=-1;
		iActiveViewId=KNullViewId;
		}
	}

TVwsViewIdAndMessage CCoeViewManager::HandleScreenDeviceChangedL(const TVwsViewId& aViewId)
	{
	CCoeScreenDeviceChangeDefaultHandler* screenChangeHandler=CCoeScreenDeviceChangeDefaultHandler::Self();
	if (screenChangeHandler)
		screenChangeHandler->HandleScreenDeviceChangedL();
	if (aViewId.iViewUid.iUid == aViewId.iAppUid.iUid)
		{
		if (screenChangeHandler)
			{
			return screenChangeHandler->DefaultViewOnScreenDeviceChanged();
			}
		return TVwsViewIdAndMessage(aViewId);
		}
	else
		{
		TInt index=ViewIndex(aViewId);
		__ASSERT_ALWAYS(index!=KErrNotFound, Panic(ECoePanicViewNotFound));
		return iViewArray[index]->iView.ViewScreenDeviceChangedL();
		}
	}

void CCoeViewManager::HandleViewDeactivationNotification(const TVwsViewId& aViewId,const TVwsViewId& aActiveViewId)
	{
	ASSERT(iNextViewDeactivationObserver);
	MCoeViewDeactivationObserver* observer=iNextViewDeactivationObserver;
	iNextViewDeactivationObserver=NULL;
	observer->HandleViewDeactivation(aViewId,aActiveViewId);
	}

void CCoeViewManager::HandleViewActivationNotification(const TVwsViewId& aActiveViewId,const TVwsViewId& aViewToDeactivatedId)
	{
	ASSERT(iNextViewActivationObserver);
	MCoeViewActivationObserver* observer=iNextViewActivationObserver;
	iNextViewActivationObserver=NULL;
	observer->HandleViewActivation(aActiveViewId,aViewToDeactivatedId);
	}

void CCoeViewManager::CreateActivateViewEventL(const TVwsViewId& aViewId,const TUid& aCustomMessageId,const TDesC8& aCustomMessage)
	{
	TInt err = iVwsSession->CreateActivateViewEvent(aViewId,aCustomMessageId,aCustomMessage, iCustomControl);
	if (err == KErrOverflow)
		{
		err = KLeaveWithoutAlert;
		}
	User::LeaveIfError(err);
	}

void CCoeViewManager::SetSystemDefaultViewL(const TVwsViewId& aViewId,TInt aMode)
	{
	if(iPreviousAppUi)
		{
		iPreviousAppUi->SetSystemDefaultViewL(aViewId, aMode);
		}
	else
		{
		User::LeaveIfError(iVwsSession->SetSystemDefaultView(aViewId, aMode));
		}
	}

void CCoeViewManager::SetSystemDefaultViewL(const TVwsViewId& aViewId)
	{
	if(iPreviousAppUi)
		{
		iPreviousAppUi->SetSystemDefaultViewL(aViewId);
		}
	else
		{
		User::LeaveIfError(iVwsSession->SetSystemDefaultView(aViewId));
		}
	}

void CCoeViewManager::GetSystemDefaultViewL(TVwsViewId& aViewId)
	{
	User::LeaveIfError(iVwsSession->GetSystemDefaultView(aViewId));
	}
	
TBool CCoeViewManager::IsViewConstructed(const TVwsViewId& aViewId) const
	{
	const TInt viewCount = iViewArray.Count();
	for (TInt viewIndex = 0; viewIndex < viewCount; viewIndex++)
		{
		if (iViewArray[viewIndex]->iView.ViewId() == aViewId && iViewArray[viewIndex]->iConstructed)
			{
			return ETrue;
			}
		}
	return EFalse;
	}

TInt CCoeViewManager::EnableExternalViewSwitches(TBool aEnable)
	{
	return iVwsSession->EnableExternalViewSwitches(aEnable);
	}

TInt CCoeViewManager::GetTopViewId(TVwsViewId& aViewId) const
	{
	if (iActivatingViewId!=KNullViewId)
		{
		aViewId = iActivatingViewId;
		return KErrNone;
		}
	if (iLastActiveViewId!=KNullViewId)
		{
		aViewId = iLastActiveViewId;
		return KErrNone;
		}
	if (iDefaultViewId!=KNullViewId)
		{
		aViewId = iDefaultViewId;
		return KErrNone;
		}
	if (iViewArray.Count())
		{
		aViewId = iViewArray[0]->iView.ViewId();
		return KErrNone;
		}
	if (iApplicationViewId!=KNullViewId)
		{
		aViewId = iApplicationViewId;
		return KErrNone;
		}
	if (iPreviousAppUi)
		{
		return iPreviousAppUi->GetTopViewId(aViewId);
		}
	return KErrNotFound;
	}

void CCoeViewManager::SetCustomControl(const TInt aCustomControl)
	{
	iCustomControl=aCustomControl;
	}

void CCoeViewManager::SetWindowGroupOrdinal(const TInt aWindowGroupOrdinal)
	{
	iWindowGroupOrdinal=aWindowGroupOrdinal;
	}

void CCoeViewManager::UpdateViewServerBackgroundColor(const TRgb& aBgColor)
	{
	iVwsSession->SetWindowBackgroundColor(aBgColor);
	}

	

