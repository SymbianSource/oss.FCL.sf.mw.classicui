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

#include "coeenvextra.h"
#include "coepanic.h"
#include <fepplugin.h>	// Needed only for deletion of iFepPlugIn member in CCoeEnvExtra::TFep
#include <hal.h>
#include "coedefkeys.h"

//
// Class CCoeEnvExtra
//

CCoeEnvExtra::CCoeEnvExtra()
	:iResFileAccessCount(2),
	 iCoeStaticList(_FOFF(CCoeStatic,iCsLink)),
	 iControlState(ETrue),
	 iArrayOfObserversOfLoadedFep(2),
	 iArrayOfFocusObservers(2),
	 iArrayOfForegroundObservers(2),
	 iArrayOfMessageObservers(2),
	 iArrayOfFepObservers(2),
	 iArrayOfResourceChangeObservers(2),
	 iArrayOfMessageMonitorObservers(2)	 

	{
	}

void CCoeEnvExtra::ConstructL()
	{
	// Short-circuit op.
	if( (KErrNone != HAL::Get( HALData::EPointerNumberOfPointers, iSupportedPointers))
	 || (0 == iSupportedPointers) )
		{
		iSupportedPointers = 1;
		}
	else if( iSupportedPointers > KConeMaxSupportedPointers )
		{
		User::Leave( KErrTooBig );
		}
	}

CCoeEnvExtra::~CCoeEnvExtra()
	{
	iArrayOfObserversOfLoadedFep.Close();
	iArrayOfFocusObservers.Close();
	iArrayOfForegroundObservers.Close();
	iArrayOfMessageObservers.Close();
	iArrayOfFepObservers.Close();
	iArrayOfResourceChangeObservers.Close();
	iArrayOfMessageMonitorObservers.Close();	
	}

void CCoeEnvExtra::HandleChangeInLoadedFep()
	{
	for (TInt i=iArrayOfObserversOfLoadedFep.Count()-1; i>=0; --i)
		{
		static_cast<MCoeObserverOfLoadedFep*>(iArrayOfObserversOfLoadedFep[i])->HandleChangeInLoadedFep();
		}
	}

void CCoeEnvExtra::NotifyFocusObserversOfChangeInFocus()
	{
	for (TInt i=iArrayOfFocusObservers.Count()-1; i>=0; --i)
		{
		static_cast<MCoeFocusObserver*>(iArrayOfFocusObservers[i])->HandleChangeInFocus();
		}
	}

void CCoeEnvExtra::NotifyFocusObserversOfDestructionOfFocusedItem()
	{
	for (TInt i=iArrayOfFocusObservers.Count()-1; i>=0; --i)
		{
		static_cast<MCoeFocusObserver*>(iArrayOfFocusObservers[i])->HandleDestructionOfFocusedItem();
		}
	}

void CCoeEnvExtra::NotifyForegroundObserversOfGainingForeground()
	{
	for (TInt i=iArrayOfForegroundObservers.Count()-1; i>=0; --i)
		{
		static_cast<MCoeForegroundObserver*>(iArrayOfForegroundObservers[i])->HandleGainingForeground();
		}
	}

void CCoeEnvExtra::NotifyForegroundObserversOfLosingForeground()
	{
	for (TInt i=iArrayOfForegroundObservers.Count()-1; i>=0; --i)
		{
		static_cast<MCoeForegroundObserver*>(iArrayOfForegroundObservers[i])->HandleLosingForeground();
		}
	}

void CCoeEnvExtra::NotifyResourceObserversOfChangeInResource()
	{
	for (TInt i=iArrayOfResourceChangeObservers.Count()-1; i>=0; --i)
		{
		static_cast<MCoeResourceChangeObserver*>(iArrayOfResourceChangeObservers[i])->HandleResourceChange();
		}
	}

void CCoeEnvExtra::NotifyMessageObserversOfMessageL(TUint32 aClientHandleOfTargetWindowGroup, const TUid& aMessageUid, const TDesC8& aMessageParameters)
	{
	TInt error=KErrNone;
	TInt previousErr=KErrNone;
	//Make this variable "volatile" to prevent the compiler putting it in a register
	volatile TInt i=iArrayOfMessageObservers.Count()-1;
	// Using two for loops like this optimizes the normal (no leave) case so that there is only one TRAP, but means that all message observers will get a chance to run, regardless of whether one of them leaves.
	for (; i>=0; --i)
		{
		TRAP(error,
			for (; i>=0; --i)
				{
				static_cast<MCoeMessageObserver*>(iArrayOfMessageObservers[i])->HandleMessageL(aClientHandleOfTargetWindowGroup, aMessageUid, aMessageParameters); // ignore the return value of HandleMessageL (which is just there in case it is needed in the future)
				}
			);
		if(previousErr==KErrNone)
			{
			previousErr=error; //Propagate the first error value if message observer leaves.
			}
		}
	User::LeaveIfError(previousErr);
	}

void CCoeEnvExtra::NotifyMessageMonitorObserversOfEvent(const TWsEvent &aEvent)
/**Systematically passes received window visibility events to the registered observers in sequence
*/
	{
	for (TInt i=iArrayOfMessageMonitorObservers.Count()-1; i>=0; --i)
		{
		static_cast<MCoeMessageMonitorObserver*>(iArrayOfMessageMonitorObservers[i])->MonitorWsMessage(aEvent); 
		}
	}

void CCoeEnvExtra::ForEachFepObserverCall(TCoeFepObserverFunction aFepObserverFunction)
	{
	for (TInt i=iArrayOfFepObservers.Count()-1; i>=0; --i)
		{
		(*aFepObserverFunction)(*(MCoeFepObserver*)iArrayOfFepObservers[i]);
		}
	}

void CCoeEnvExtra::DestroyFep(TAny* aFep)
	{
	DestroyFep(*(CCoeEnvExtra::TFep*)aFep);
	}

void CCoeEnvExtra::DestroyFep(TFep& aFep)
	{
	delete (CBase*)aFep.iFep;
	aFep.iFep=NULL;
	aFep.iFepUid=KNullUid;
	delete aFep.iFepPlugIn;
	aFep.iFepPlugIn = NULL;
	}

void CCoeEnvExtra::AddObserverL(RArray<TAny*>& aArrayOfObservers, TAny* aObserver)
	{
	__ASSERT_ALWAYS(aObserver!=NULL, Panic(ECoePanicIllegalNullParameter3));
	CleanupClosePushL(aArrayOfObservers);
	for (TInt i=aArrayOfObservers.Count()-1; i>=0; --i)
		{
		__ASSERT_ALWAYS(aArrayOfObservers[i]!=aObserver, Panic(ECoePanicFocusObserverHasAlreadyBeenAdded));
		}
	User::LeaveIfError(aArrayOfObservers.Append(aObserver));
	CleanupStack::Pop(&aArrayOfObservers);
	}

void CCoeEnvExtra::RemoveObserver(RArray<TAny*>& aArrayOfObservers, const TAny* aObserver)
	{
	__ASSERT_ALWAYS(aObserver!=NULL, Panic(ECoePanicIllegalNullParameter4));
	for (TInt i=aArrayOfObservers.Count()-1; i>=0; --i)
		{
		if (aArrayOfObservers[i]==aObserver)
			{
			aArrayOfObservers.Remove(i);
			break;
			}
		}
	}

//
// Class CCoeEnvExtra::CHighPriorityActive
//

CCoeEnvExtra::CHighPriorityActive* CCoeEnvExtra::CHighPriorityActive::NewL(CCoeEnvExtra& aCoeEnvExtra)
	{
	return new(ELeave) CHighPriorityActive(aCoeEnvExtra);
	}

CCoeEnvExtra::CHighPriorityActive::~CHighPriorityActive()
	{
	Cancel();
	}

void CCoeEnvExtra::CHighPriorityActive::QueueNotificationToFocusObserversOfChangeInFocus()
	{
	if (!IsActive())
		{
		TRequestStatus* requestStatus=&iStatus;
		User::RequestComplete(requestStatus, KErrNone);
		SetActive();
		}
	}

TInt CCoeEnvExtra::CHighPriorityActive::FocusObserverNotificationIdentifier() const
	{
	__ASSERT_DEBUG(IsActive(), Panic(ECoePanicFocusObserverNotificationIsNotPending));
	return iFocusObserverNotificationIdentifier;
	}

TBool CCoeEnvExtra::CHighPriorityActive::FocusObserverNotificationIsStillPending(TInt aFocusObserverNotificationIdentifier) const
	{
	return IsActive() && (iFocusObserverNotificationIdentifier==aFocusObserverNotificationIdentifier);
	}

CCoeEnvExtra::CHighPriorityActive::CHighPriorityActive(CCoeEnvExtra& aCoeEnvExtra)
	:CActive(EActivePriorityWsEvents+50), // this priority must be greater than CCoeFep::CHighPriorityActive's priority (a FEPBASE class) so that FEPs receive notification of any change in focus (resulting from them calling HandleStartOfTransactionL) *before* any deferred function (i.e. one overriding MDeferredFunctionCall::ExecuteFunctionL) is called - this is necessary as the deferred function may depend on the deferred capabilities of the newly focused control (e.g. for inline editing)
	 iCoeEnvExtra(aCoeEnvExtra),
	 iFocusObserverNotificationIdentifier(0)
	{
	CActiveScheduler::Add(this);
	}

void CCoeEnvExtra::CHighPriorityActive::DoCancel()
	{
	}

void CCoeEnvExtra::CHighPriorityActive::RunL()
	{
	NotifyFocusObserversOfChangeInFocus();
	}

void CCoeEnvExtra::CHighPriorityActive::NotifyFocusObserversOfChangeInFocus()
	{
    iCoeEnvExtra.NotifyFocusObserversOfChangeInFocus();
    ++iFocusObserverNotificationIdentifier;
	}

/** Default Constructor for TScreenItem
*/
CCoeEnvExtra::CScreenItem::CScreenItem(CWsScreenDevice* aScreenDevice, RWindowGroup* aWindowGroup)
		:iScreenDevice(aScreenDevice),iWindowGroup(aWindowGroup)
	{
	}

CCoeEnvExtra::CScreenItem::~CScreenItem()
	{
	delete iScreenDevice;
	if (iWindowGroup)
		iWindowGroup->Close();
	delete iWindowGroup;
	}

/**
@return The screen device
*/
CWsScreenDevice* CCoeEnvExtra::CScreenItem::ScreenDevice()
	{
	return iScreenDevice;	
	}
		
/**
@return The window group
*/
RWindowGroup* CCoeEnvExtra::CScreenItem::WindowGroup()
	{
	return iWindowGroup;	
	}

/**
This function is used only to set the value of iArrayOfScreenItems's first entry's iScreenDevice to NULL. 
The data to which the first entry points to cannot be deleted in DeleteArrayOfScreensItems.
*/
void CCoeEnvExtra::CScreenItem::SetScreenDevice(CWsScreenDevice* aScreenDevice)
	{
	iScreenDevice = aScreenDevice;	
	}

/**
This function is used only to set the value of iArrayOfScreenItems's first entry's iWindowGroup to NULL.
The data to which the first entry points to cannot be deleted in DeleteArrayOfScreensItems.
*/	
void CCoeEnvExtra::CScreenItem::SetWindowGroup(RWindowGroup* aWindowGroup)
	{
	iWindowGroup = aWindowGroup;	
	}

