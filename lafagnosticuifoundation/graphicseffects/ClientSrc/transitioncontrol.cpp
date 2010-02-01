// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// GFXTRANSEFFECT.CPP
// 
//


#include "TransitionControl.h"
#include "RegisteredControl.h"
#include "GfxTransUtils.h"
#include "GfxTransEffect.h"
#include <coecntrl.h>

//----------------
// InTransition List
//----------------
TInt RInTransitionList::Append(CTransitionControl* aTransControl)
	{
	TInt err = RPointerArray<CTransitionControl>::Append(aTransControl);
 	return err;
	}
 
void RInTransitionList::Remove(TInt aIndex)
	{
    RPointerArray<CTransitionControl>::Remove(aIndex);
	#ifdef _DEBUG
		Compress(); // so that __UHEAP_MARK can be used
	#endif
	}

TInt RInTransitionList::Find(const CRegisteredControl * aRegControl) const
	{
	const TInt count = Count();
	for(TInt i=0; i<count; i++)
		{
		if(aRegControl == (*this)[i]->RegControl())
			{
			return i;
			}
		}
	return KErrNotFound;
	}

TInt RInTransitionList::Find(TInt aHandle) const
	{
	const TInt count = Count();
	for(TInt i=0; i<count; i++)
		{
		if(aHandle == (*this)[i]->Handle())
			{
			return i;
			}
		}
	return KErrNotFound;
	}
//----------------
// Active Stack
//----------------
TInt RActiveStack::Push(CTransitionControl* aTransControl)
	{
	TInt err = Append(aTransControl);
	return err;
	}

TInt RActiveStack::PushLC(CTransitionControl* aTransControl)
	{
	TInt err = Append(aTransControl);
	if(err == KErrNone) 
		{
		//push to cleanupstack
   		aTransControl->iOnCleanupStack = ETrue;
		CleanupStack::PushL(TCleanupItem(CleanupOperation,this));
		}
	return err;
	}

CTransitionControl* RActiveStack::Pop()
	{
	TInt last = Count()-1;
	CTransitionControl* ctrl = (*this)[last];
	if(ctrl->iOnCleanupStack)
		{
		CleanupStack::Pop(this);
		ctrl->iOnCleanupStack = EFalse;
		}
	Remove(last);
	#ifdef _DEBUG
	Compress(); // so that __UHEAP_MARK can be used
	#endif
	return ctrl;
	}


void RActiveStack::CleanupOperation(TAny *aAny)
	{
 	RActiveStack* activeStack = reinterpret_cast<RActiveStack*>(aAny);
 	TInt last = activeStack->Count()-1;
	CTransitionControl* ctrl = (*activeStack)[last];
	activeStack->Remove(last);
	delete ctrl;
	#ifdef _DEBUG
	activeStack->Compress(); // so that __UHEAP_MARK can be used
    #endif
 	}
 	
CTransitionControl* RActiveStack::Top()
	{
	TInt last = Count()-1;
	return last < 0 ? NULL :(*this)[last];	
	}

TInt RActiveStack::ClearAbove(TInt aIndex)
	{
	for(TInt i = Count()-1; i > aIndex; i--) 
		{
		CTransitionControl* ctrl = Pop();	
		delete ctrl;			
		}
	return KErrNone;
	}


TInt RActiveStack::Find(const CRegisteredControl * aRegControl) const
	{
	const TInt count = Count();
	for(TInt i=count-1; i>=0; i--)
		{
		if(aRegControl == (*this)[i]->RegControl())
			{
			return i;
			}
		}
	return KErrNotFound;
	}

TInt RActiveStack::Find(const CCoeControl * aControl) const
	{
	CRegisteredControl* regctrl;
	const TInt count = Count();
	for(TInt i=count-1; i>=0; i--)
		{
		if((NULL != (regctrl = (*this)[i]->RegControl())) &&
		   (aControl == regctrl->Control()))
			{
			return i;
			}
		}
	return KErrNotFound;
	}

TInt RActiveStack::FindView(TVwsViewId const &aView) const
	{
	CRegisteredControl* regctrl;
	const TInt count = Count();
	for(TInt i=count-1; i>=0; i--)
		{
		if((NULL != (regctrl = (*this)[i]->RegControl())) &&
		   (aView == regctrl->ViewId()))
			{
			return i;
			}
		}
	return KErrNotFound;
	}

TInt RActiveStack::Find(TInt aHandle) const
	{
	const TInt count = Count();
	for(TInt i=count-1; i>=0; i--)
		{
		if(aHandle == (*this)[i]->Handle())
			{
			return i;
			}
		}
	return KErrNotFound;
	}

//----------------
// Transition Control
//----------------
	
CTransitionControl* CTransitionControl::New(CRegisteredControl* aRegControl, MTransitionControlObserver *aObserver,
											TUint aAction, TPolicy aPolicy, TInt aHandle)
	{	
	CTransitionControl *control = new CTransitionControl(aRegControl, aObserver, aHandle);
	if(!control)
		{
		return NULL;
		}
	control->iData = new CTransitionData();
	if(!(control->iData))
		{
		delete control;
		return NULL;
		}
	control->iData->iAction = aAction;
	control->iData->iPolicy = aPolicy;
	return control;
	}

CTransitionControl::CTransitionControl(	CRegisteredControl* aRegControl, MTransitionControlObserver *aObserver, 
										TInt aHandle) :
										iObserver (aObserver),
										iRegControl (aRegControl),
										iBaseControl (NULL),
										iHandle (aHandle),
										iHasBeginWOPos (EFalse)
	{
	}

CTransitionControl::~CTransitionControl()
	{
	RegControl()->RemoveTransition(this);
	delete iData;

	iSubControls.ResetAndDestroy();
	delete iBaseControl;

	iSubControls.Close();
	}

void CTransitionControl::Reset()
	{
	iData->iFailed = ETrue; // if active it has failed, if in transition the data is invalid
	//reset
	iSubControls.ResetAndDestroy();
	if(iBaseControl)
		{
		delete iBaseControl;
		iBaseControl = NULL;
		}
	}

//----------------
// Capture
//----------------
void CTransitionControl::CaptureBegin()
	{
	TInt zdepth = 0;
	const CCoeControl *control = iRegControl->Control();
	iScreenDevice = control->ControlEnv()->ScreenDevice();
	//copy data to CTransitionData
	iData->iUid = iRegControl->Uid();
	iData->iNLayered = iRegControl->IsNLayered();
	iData->iKey = control;
	iData->iFailed = EFalse;
	
	if(!control->IsVisible() || control->Size() == TSize(0,0))
		{
		//Create even though invisible for non-N-layered controls.
		if(Policy() == ESupported && !iRegControl->IsNLayered()) 
		    {
        	TUint flags = iRegControl->Flags();
        	if(NULL == (iBaseControl = CTransitionParticipant::New(control, this, flags)))
        		{
        		Fallback();
        		return;
        		}
    		iData->iBaseControl = iBaseControl->Data();
    		control->SetGc(iBaseControl->RemoteGc());
		    }
		return;
		}
	
	//get/set screen coords
	if(control->OwnsWindow())
		{
		iData->iBeginWOPos = control->PositionRelativeToScreen();
		}
	else
		{
		iData->iBeginWOPos = control->PositionRelativeToScreen() - control->Position();
		}
		
	iHasBeginWOPos = ETrue;
	
	TUint flags = iRegControl->Flags();
	//create and capture base control
	if(NULL == (iBaseControl = CTransitionParticipant::New(control, this, flags)))
		{
		Fallback();
		return;
		}
	//add base control data to transition data
	iData->iBaseControl = iBaseControl->Data();
	

	if(KErrNone != iBaseControl->CaptureBegin(	control, iData->iNLayered ? 
												CTransitionParticipant::EShallow : CTransitionParticipant::EDeep,
												zdepth++))
		{
		Fallback();
		return;
		}
	
	//create and capture child controls
	if(iData->iNLayered)
		{
		TInt count = control->CountComponentControls();
		for(TInt i=0; i<count; i++)
			{
			const CCoeControl *childcontrol = control->ComponentControl(i);
			if(childcontrol->IsVisible() && childcontrol->Size() != TSize(0,0))
				{
				//create and capture participant
				CTransitionParticipant *subcontrol = CreateSubControl(childcontrol, flags);
				if(!subcontrol)
					{
					Fallback();
					return;
					}
				if(KErrNone != subcontrol->CaptureBegin( childcontrol, CTransitionParticipant::EDeep, zdepth++ ))
					{
					Fallback();
					return;
					}
				}
			}
		}
	}

void CTransitionControl::CaptureEnd()
	{
	TInt zdepth = 0;
	if(iData->iFailed)
		return;
	
	const CCoeControl *control = iRegControl->Control();
	
	if(!iBaseControl)
		{
		//iFailed if no start state exists
		Fallback();
		return;
		}
	
	//capture end state
	if(control->IsVisible() && control->Size() != TSize(0,0))
		{
		if(control->OwnsWindow())
			{
			iData->iEndWOPos = control->PositionRelativeToScreen();
			}
		else
			{
			iData->iEndWOPos = control->PositionRelativeToScreen() - control->Position();
			}
		
		//Set beginWOpos if not allready existing
		if(!iHasBeginWOPos)
			{
			iData->iBeginWOPos = iData->iEndWOPos;
			}
		
		if(KErrNone != iBaseControl->CaptureEnd(control, iData->iNLayered ? 
												CTransitionParticipant::EShallow : CTransitionParticipant::EDeep,
												zdepth++))
			{
			Fallback();
			return;
			}
	
		if(iData->iNLayered)
			{
			const TInt count = control->CountComponentControls();
			for(TInt i = 0; i < count; i++)
				{
				const CCoeControl *childcontrol = control->ComponentControl(i);
				if(childcontrol->IsVisible() && childcontrol->Size() != TSize(0,0))
					{
					TInt idx = FindParticipant(childcontrol);
					if(!IsValidIndex(idx))
						{
						Fallback();
						return;
						}
					if(KErrNone != iSubControls[idx]->CaptureEnd(childcontrol, CTransitionParticipant::EDeep, zdepth++))
						{
						Fallback();
						return;
						}
					}
				}
			}
		}
	else 
		{
		iData->iEndWOPos = iData->iBeginWOPos;
		}
				
	// check so that there are no errors
	// it is an error if not all participants has both begin coordinates (EBeginCapture)
	// and end coordinates (EEndCapture). All participants must also have at least one
	// image capture
	if(	!(iBaseControl->CaptureState() == 
		(CTransitionParticipant::EBeginCapture | CTransitionParticipant::EEndCapture)) ||
		((Policy() == ESupported) && !iBaseControl->HaveImageCapture()))
		{
		Fallback();
		return;
		}
	iBaseControl->ModifyCoordinates(iData->iBeginWOPos, iData->iEndWOPos);
	if(iData->iNLayered)
		{
		const TInt count = iSubControls.Count();
		for(TInt i = 0; i < count; i++)
			{	
			if(	((Policy() == ESupported) && !iSubControls[i]->HaveImageCapture()) ||
				!(iSubControls[i]->CaptureState() == 
				(CTransitionParticipant::EBeginCapture | CTransitionParticipant::EEndCapture)))
				{
				Fallback();
				return;
				}
			iSubControls[i]->ModifyCoordinates(iData->iBeginWOPos, iData->iEndWOPos);
			}
		}
	}

//----------------
// Demarcations
//----------------

void CTransitionControl::DoSetDemarcation(const CCoeControl *aKey, TRect aDemarcation)
	{
	if(iData->iFailed)
		return;
	if((aKey == iData->iKey))
		{
		if(iBaseControl)
			{
			//exists
			if(iBaseControl->CaptureState() & CTransitionParticipant::EBeginCapture)
				{ //set end demarcation
				iBaseControl->SetEndDemarcation(aDemarcation, aKey->OwnsWindow() ? CTransitionParticipant::EScreen : 
												CTransitionParticipant::EWindowOwning);
				}
			else
				{ 	//set begin demarcation
				iBaseControl->SetBeginDemarcation(	aDemarcation, aKey->OwnsWindow() ? CTransitionParticipant::EScreen : 
													CTransitionParticipant::EWindowOwning);
				}
			}
		else 
			{
			//create it
			if(NULL == (iBaseControl = CTransitionParticipant::New(aKey, this, iRegControl->Flags())))
				{
				Fallback();
				return;
				}
			iData->iBaseControl = iBaseControl->Data();
			//set begin demarcation
			iBaseControl->SetBeginDemarcation(	aDemarcation, aKey->OwnsWindow() ? CTransitionParticipant::EScreen : 
												CTransitionParticipant::EWindowOwning);
			}
		}
	else if(iData->iNLayered)
		{
		TInt idx = FindParticipant(aKey);
		if(IsValidIndex(idx))
			{
			if(iSubControls[idx]->CaptureState() & CTransitionParticipant::EBeginCapture)
				{ 	//set end demarcation
				iSubControls[idx]->SetEndDemarcation(	aDemarcation, aKey->OwnsWindow() ? CTransitionParticipant::EScreen : 
														CTransitionParticipant::EWindowOwning);
				}
			else
				{ 	//set begin demarcation
				iSubControls[idx]->SetBeginDemarcation(	aDemarcation, aKey->OwnsWindow() ? CTransitionParticipant::EScreen : 
														CTransitionParticipant::EWindowOwning);
				}
			}
		else 
			{
			//create it
			CTransitionParticipant *subcontrol = CreateSubControl(aKey, iRegControl->Flags());
			if(!subcontrol)
				{
				Fallback();
				return;
				}
			//set begin demarcation
			subcontrol->SetBeginDemarcation(aDemarcation, aKey->OwnsWindow() ? CTransitionParticipant::EScreen : 
											CTransitionParticipant::EWindowOwning);
			}
		}
	}

void CTransitionControl::DoSetDemarcation(const CCoeControl *aKey, const CCoeControl *aSrc, TRect aDemarcation)
	{
	if(iData->iFailed)
		return;
	TPoint screenPos = aSrc->PositionRelativeToScreen();
	aDemarcation.iTl += screenPos;
	aDemarcation.iBr += screenPos;
	if(aKey == iData->iKey)
		{
		if(iBaseControl)
			{
			//exists
			if(iBaseControl->CaptureState() & CTransitionParticipant::EBeginCapture)
				{ 	//set end demarcation
				iBaseControl->SetEndDemarcation(aDemarcation, CTransitionParticipant::EScreen);
				}
			else
				{ 	//set begin demarcation
				iBaseControl->SetBeginDemarcation(aDemarcation, CTransitionParticipant::EScreen);
				}
			}
		else 
			{
			//create it
			if(NULL == (iBaseControl = CTransitionParticipant::New(aKey, this, iRegControl->Flags())))
				{
				Fallback();
				return;
				}
			iData->iBaseControl = iBaseControl->Data();
			//set begin demarcation
			iBaseControl->SetBeginDemarcation(aDemarcation, CTransitionParticipant::EScreen);
			}
		}
	else if(iData->iNLayered)
		{
		TInt idx = FindParticipant(aKey);
		if(IsValidIndex(idx))
			{
			if(iSubControls[idx]->CaptureState() & CTransitionParticipant::EBeginCapture)
				{ 	//set end demarcation
				iSubControls[idx]->SetEndDemarcation(aDemarcation, CTransitionParticipant::EScreen);
				}
			else
				{ 	//set begin demarcation
				iSubControls[idx]->SetBeginDemarcation(aDemarcation, CTransitionParticipant::EScreen);
				}
			}
		else 
			{
			//create it
			CTransitionParticipant *subcontrol = CreateSubControl(aKey, iRegControl->Flags());
			if(!subcontrol)
				{
				Fallback();
				return;
				}
			//set begin demarcation
			subcontrol->SetBeginDemarcation(aDemarcation, CTransitionParticipant::EScreen);
			}
		}
	}

void CTransitionControl::DoSetBeginDemarcation(const CCoeControl *aKey, TRect aDemarcation)
	{
	if(iData->iFailed)
		return;
	if(aKey == iData->iKey)
		{
		if(!iBaseControl)
			{
			//create it
			if(NULL == (iBaseControl = CTransitionParticipant::New(aKey, this, iRegControl->Flags())))
				{
				Fallback();
				return;
				}
			iData->iBaseControl = iBaseControl->Data();
			}
		iBaseControl->SetBeginDemarcation(	aDemarcation, aKey->OwnsWindow() ? CTransitionParticipant::EScreen : 
											CTransitionParticipant::EWindowOwning);
		}
	else if(iData->iNLayered)
		{
		TInt idx = FindParticipant(aKey);
		CTransitionParticipant *subcontrol;
		if(!IsValidIndex(idx))
			{
			//Create it	
			if(NULL == (subcontrol = CreateSubControl(aKey, iRegControl->Flags())))
				{
				Fallback();
				return;
				}
			}
		else 
			{
			subcontrol = iSubControls[idx];
			}
		subcontrol->SetBeginDemarcation(aDemarcation, aKey->OwnsWindow() ? CTransitionParticipant::EScreen : 
										 CTransitionParticipant::EWindowOwning);
		}
	}
	
void CTransitionControl::DoSetEndDemarcation(const CCoeControl *aKey, TRect aDemarcation)
	{
	if(iData->iFailed)
		return;
	if(aKey == iData->iKey)
		{
		if(!iBaseControl)
			{
			return;
			}
		iBaseControl->SetEndDemarcation(aDemarcation, aKey->OwnsWindow() ? CTransitionParticipant::EScreen : 
										CTransitionParticipant::EWindowOwning);
		}
	else if(iData->iNLayered)
		{
		TInt idx = FindParticipant(aKey);
		if(!IsValidIndex(idx))
			{
			return;
			}
		iSubControls[idx]->SetEndDemarcation(aDemarcation, aKey->OwnsWindow() ? CTransitionParticipant::EScreen : 
											 CTransitionParticipant::EWindowOwning);
		}
	}
		
		
//----------------
// Hints
//----------------

void CTransitionControl::Invalidate(const CCoeControl *aKey)
	{
	if(iData->iFailed)
		return;
	if((aKey == iData->iKey) && iBaseControl)
		{
		iBaseControl->Invalidate();
		}
	else 
		{
		TInt idx = FindParticipant(aKey);
		if(IsValidIndex(idx))
			{
			iSubControls[idx]->Invalidate();
			}
		}
	}
	
void CTransitionControl::SetHints(const CCoeControl *aKey, TUid aLayerType)
	{
	if(iData->iFailed)
		return;
	if(aKey == iRegControl->Control())
		{
		//basecontrol layertype is the Registered Uid
		}
	else if(iData->iNLayered)
		{
		TInt idx = FindParticipant(aKey);
		if(!IsValidIndex(idx))
			{
			// create the subcontrol
			CTransitionParticipant *subcontrol = CreateSubControl(aKey, iRegControl->Flags());
			if(!subcontrol)
				{
				Fallback();
				return;
				}
			subcontrol->SetLayerType(aLayerType);
			}
		else 
			{
			iSubControls[idx]->SetLayerType(aLayerType);
			}
		}
	}
	
void CTransitionControl::SetHints(const CCoeControl *aKey, TUint aFlags)
	{
	if(iData->iFailed)
		return;
	if(aKey == iRegControl->Control())
		{
		//the main ctrl
		iRegControl->SetFlags(aFlags);
		if(iBaseControl)
			{
			iBaseControl->SetFlags(aFlags);
			}
		//set the flags on all existing layers
		if(iData->iNLayered)
			{
			const TInt count = iSubControls.Count();
			for(TInt i = 0; i < count; i++)
				{
				iSubControls[i]->SetFlags(aFlags);
				}
			}
		}
	else if(iData->iNLayered)
		{
		TInt idx = FindParticipant(aKey);
		if(!IsValidIndex(idx))
			{
			//create the subcontrol
			CTransitionParticipant *subcontrol = CreateSubControl(aKey, aFlags);
			if(!subcontrol)
				{
				Fallback();
				return;
				}
			}
		else 
			{
			//set flags
			iSubControls[idx]->SetFlags(aFlags);
			}
		}
	}
	
TUint CTransitionControl::GetHints(const CCoeControl *aKey)
	{
	if(iData->iFailed)
		return GfxTransEffect::ENone;
	if(aKey == iRegControl->Control())
		{
		return iRegControl->Flags();
		}
	else if(iData->iNLayered)
		{
		TInt idx = FindParticipant(aKey);
		if(IsValidIndex(idx))
			{
			return iSubControls[idx]->Flags();
			}
		}
	return GfxTransEffect::ENone;
	}

//----------------
// Get/set data
//----------------

void CTransitionControl::SetTransitionData(TUint aType, const TDesC8& aData)
	{
	iData->iExDataType = aType;
	iData->iExData = &aData; 
	}

void CTransitionControl::GetTransitionData(const CTransitionData*& aTransData)
	{
	aTransData = iData;
	}

TInt CTransitionControl::GetUpdatedRegion(RRegion& aRegion)
	{
	if(iData->iFailed)
		return KErrAbort;
	aRegion.Clear();
	if((iBaseControl->Data()->iBeginRect != iBaseControl->Data()->iEndRect) || 
		iBaseControl->Invalidated())
		{
		aRegion.AddRect(RegControl()->Control()->Rect());
		}
	else if(iData->iNLayered)
		{
		const TInt count = iSubControls.Count();
		CTransitionParticipant *subcontrol;
		for(TInt i = 0; i < count; i++)
			{
			subcontrol = iSubControls[i];
			if(subcontrol->Data()->iBeginRect != subcontrol->Data()->iEndRect)
				{
				aRegion.AddRect(subcontrol->Data()->iBeginRect);
				aRegion.AddRect(subcontrol->Data()->iEndRect);
				}
			else if(subcontrol->Invalidated())
				{
				aRegion.AddRect(subcontrol->Data()->iEndRect);
				}		
			}
		}	
	return KErrNone;
	}
//---------------------------------
// participant callback  
//---------------------------------
void CTransitionControl::ParticipantUpdated(CTransitionParticipant *aParticipant, 
											RWsGraphicMsgBuf* aCommandBuffer, const TRect& aDrawRect, const TRect& aBoundingRect)
	{
	iObserver->ParticipantUpdated(this, aParticipant, aCommandBuffer,aDrawRect, aBoundingRect);
	}

//---------------------------------
// private functions  
//---------------------------------

void CTransitionControl::Fallback()
	{
	iData->iFailed = ETrue;
	//reset
	Reset();
	}

TInt CTransitionControl::FindParticipant(const CCoeControl *aKey)
	{
	TInt count = iSubControls.Count();
	for(TInt i = 0 ; i < count; i++) 
		{
		if(iSubControls[i]->Control() == aKey)
			{
			return i;
			}
		}
	return KErrNotFound;
	}

CTransitionParticipant *CTransitionControl::CreateSubControl(const CCoeControl *aKey, TUint aFlags)
	{
	CTransitionParticipant *subcontrol;
	if(NULL == (subcontrol = CTransitionParticipant::New(aKey, this, aFlags))) 
		{
		return NULL;
		}
	//add to list
	if(KErrNone != iSubControls.Append(subcontrol))
		{
		delete subcontrol;
		return NULL;
		}
	//add subcontrol data to transition data
	if(KErrNone != iData->iSubControls.Append(subcontrol->Data()))
		{
		return NULL;
		}
	return subcontrol;
	}

void CTransitionControl::SetListenForUpdates(TBool aListen)
	{
	if(iBaseControl) 
		{
		iBaseControl->SetListenForUpdates(aListen);
		}
	for(TInt i = iSubControls.Count() - 1; i >= 0; i--) 
		{
		iSubControls[i]->SetListenForUpdates(aListen);
		}
	}


