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

#include "TransitionParticipant.h"
#include <graphics/remotegc.h>

//----------------
// Utility function
//----------------
//#define RECURSIVE_GC_SETTING 

#ifdef RECURSIVE_GC_SETTING

void DrawControl(const CCoeControl *aControl, CTransitionParticipant::TCaptureType aCaptureType, CRemoteGc* aGc)
	{
	const TRect rect = aControl->Rect();
	if(aControl->Background())
		{
		aControl->DrawBackground(rect);
		}
	aControl->DrawForeground(rect);
	if(aCaptureType == CTransitionParticipant::EDeep)
		{
		
		TInt count = aControl->CountComponentControls();
		for(TInt i = 0 ; i < count; i++)
			{
			CCoeControl *child = aControl->ComponentControl(i);
			if(child->OwnsWindow())
			    child->SetGc(aGc); //Set gc for each WO child control.
			//Is it correct to check if windowowning? maybe not... :)
			if(child->IsVisible()/* && !child->OwnsWindow()*/)
				{
				DrawControl(child, aCaptureType, aGc);
				}
			}
		}
	}

#else
void DrawControl(const CCoeControl *aControl, CTransitionParticipant::TCaptureType aCaptureType)
	{
	const TRect rect = aControl->Rect();
	if(aControl->Background())
		{
		aControl->DrawBackground(rect);
		}
	aControl->DrawForeground(rect);
	if(aCaptureType == CTransitionParticipant::EDeep)
		{
		
		TInt count = aControl->CountComponentControls();
		for(TInt i = 0 ; i < count; i++)
			{
			CCoeControl *child = aControl->ComponentControl(i);
			//Is it correct to check if windowowning?
			if(child->IsVisible() && !child->OwnsWindow())
				{
				DrawControl(child, aCaptureType);
				}
			}
		}
	}
#endif

void ResetRemoteGc(const CCoeControl* aControl)
    {
    aControl->SetGc(NULL);
#ifdef RECURSIVE_GC_SETTING
    for(TInt i = aControl->CountComponentControls() - 1; i >= 0; i--) 
        {
        ResetRemoteGc(aControl->ComponentControl(i));
        }
#endif
    }



TInt DrawUptoControlRec(CWindowGc& aGc, const CCoeControl* aCurrent, const TRect& aRect,const CCoeControl* aUpto)
	{
	TInt err = KErrNone;
	if(aCurrent != aUpto)
		{
		CWindowGc* oldGc = aCurrent->GetGc();
		err = aCurrent->SetGc(&aGc);
		if(!err)
			{
			if(aCurrent->Background())
				{
				//if we have a background, draw it
				aCurrent->DrawBackground(aRect);
				}
			else if(aCurrent->OwnsWindow())
				{
				// try to find background
				const CCoeControl* bgOwningParent = aCurrent;
				do
					{
					if(const MCoeControlBackground* bg = bgOwningParent->Background())
						{
						bg->Draw(aGc,*aCurrent,aRect);
						break; // mission complete
						}
					bgOwningParent = bgOwningParent->Parent();
					} while(bgOwningParent);
				}
			//draw foreground
			aCurrent->DrawForeground(aRect);
			
			// draw component controls
			for(TInt i=0; (i < aCurrent->CountComponentControls()) && !err; i++)
				{
				const CCoeControl* child = aCurrent->ComponentControl(i);
				if(child->IsVisible() && !child->OwnsWindow())
					{
					TRect childRect = child->Rect();
					if(childRect.Intersects(aRect))
						{
						childRect.Intersection(aRect);
						err = DrawUptoControlRec(aGc,child,childRect,aUpto);
						}
					}
				}
			//set back the old gc
			err = const_cast<CCoeControl*>(aCurrent)->SetGc(oldGc);
			}
		}
	return err;
	}

TInt DrawUptoControl(CWindowGc& aGc,const CCoeControl* aControl)
	{
	const CCoeControl* aWindowOwningParent = aControl;
	//find the windowowing parent
	while(!aWindowOwningParent->OwnsWindow() && aWindowOwningParent->Parent())
		{
		aWindowOwningParent = aWindowOwningParent->Parent();
		}
	return DrawUptoControlRec(aGc, aWindowOwningParent, aControl->Rect(), aControl);
	}



//----------------
// Construct/Destruct
//----------------
CTransitionParticipant *CTransitionParticipant::New(const CCoeControl *aKey, 
													CTransitionControl *aTransControl,
													TUint aFlags)
	{
	CTransitionParticipant *participant = new CTransitionParticipant(aTransControl);
	if(!participant)
		{
		return NULL;
		}
	if(NULL == (participant->iData = new CParticipantData()))
		{
		delete participant;
		return NULL;
		}
	participant->iData->iKey = aKey;
	participant->iData->iBeginZ = -1;
	participant->iData->iEndZ = -1;
	participant->iData->iBeginCapture = 0;
	participant->iData->iEndCapture = 0;
	participant->iData->iLayerType = TUid::Uid(0);
	participant->iData->iFlags = aFlags;
	//create remote gc
	TRAPD(err, participant->iRemoteGc = CRemoteGc::NewL(aTransControl->ScreenDevice()));
	if(err < KErrNone || !(participant->iRemoteGc))
		{
		delete participant;
		return NULL;
		}
	participant->iRemoteGc->SetCommandBufferObserver(participant);
	
	return participant;
	}

CTransitionParticipant::CTransitionParticipant(CTransitionControl *aTransControl)
	{
	iTransControl = aTransControl;
	iInvalidated = EFalse;
	iCaptureState = ENoCapture;
	iCaptureEndCalled = EFalse;
	iCoordRefBegin = CTransitionParticipant::EWindowOwning;
	iCoordRefEnd = CTransitionParticipant::EWindowOwning;
	}

CTransitionParticipant::~CTransitionParticipant()
	{ 		
	if(iData)
		{
		ResetRemoteGc(Control());
		delete iData;
		}

	if(iRemoteGc)
		{
		delete iRemoteGc;
		}
	}


//----------------
// Capture
//----------------
TInt CTransitionParticipant::CaptureBegin(const CCoeControl *aControl, TCaptureType aCaptureType, TInt aZDepth)
	{
	if(iTransControl->Policy() == ESupported)
		{	
		//capture begin
		iRemoteGc->ResetCommandBuffer();
		if(KErrNone != aControl->SetGc(iRemoteGc))
			{
			return KErrAbort;
			}
		iCapturedGc = ETrue;
		iInCapture = ETrue;
		iRemoteGc->BeginDraw(aControl->Rect());
#ifdef RECURSIVE_GC_SETTING
        DrawControl(aControl, aCaptureType, iRemoteGc);
#else
		DrawControl(aControl, aCaptureType);
#endif		
		iRemoteGc->EndDraw();
		iInCapture = EFalse;	
		if(NULL == (iData->iBeginCapture = new RWsGraphicMsgBuf()))
			{
            ResetRemoteGc(Control());
			return KErrAbort;
			}
			
		TRAPD(err, iRemoteGc->ExternalizeL(*(iData->iBeginCapture), ETrue));
		if(err < KErrNone)
			{
            ResetRemoteGc(Control());
			return err;
			}
			
		iRemoteGc->ResetCommandBuffer();
	
		}
		
	//capture begin rect
	iData->iBeginRect = aControl->Rect();
	iCaptureState = (TCaptureState)(iCaptureState | EBeginCapture);
	//set z depth
	iData->iBeginZ = aZDepth;
	return KErrNone;
	}

TInt CTransitionParticipant::CaptureEnd(const CCoeControl *aControl, TCaptureType aCaptureType, TInt aZDepth)
	{
	if(iTransControl->Policy() == ESupported)
		{
		// check if we need to capture image
		if(!HaveImageCapture() || Invalidated())
			{
			// Capture End image
			iRemoteGc->ResetCommandBuffer();
			if(KErrNone != aControl->SetGc(iRemoteGc))
				{
				return KErrAbort;
				}
			iCapturedGc = ETrue;	
			iInCapture = ETrue;
			iRemoteGc->BeginDraw(aControl->Rect());
#ifdef RECURSIVE_GC_SETTING
            DrawControl(aControl, aCaptureType, iRemoteGc);
#else
			DrawControl(aControl, aCaptureType);
#endif		
			iRemoteGc->EndDraw();
			iInCapture = EFalse;
			if(NULL == (iData->iEndCapture = new RWsGraphicMsgBuf()))
				{
                ResetRemoteGc(Control());
				return KErrNoMemory;
				}
			
			TRAPD(err, iRemoteGc->ExternalizeL(*(iData->iEndCapture), ETrue));
			if(err < KErrNone)
				{
                ResetRemoteGc(Control());
				return err;
				}
			}
		else if(iCommandsReceived)
			{
			// Draw commands received between begin and end.
			if(NULL == (iData->iEndCapture = new RWsGraphicMsgBuf()))
				{
                ResetRemoteGc(Control());
				return KErrNoMemory;
				}
			
			TRAPD(err, iRemoteGc->ExternalizeL(*(iData->iEndCapture), ETrue));
			if(err < KErrNone)
				{
                ResetRemoteGc(Control());
				return err;
				}
			}
		else
			{
			iData->iEndCapture = iData->iBeginCapture;
			}
		
		iRemoteGc->ResetCommandBuffer();
		}
	//check if we need to capture end rect
	if(!(iCaptureState & EEndCapture))
		{
		iData->iEndRect = aControl->Rect();
		iCaptureState = (TCaptureState) (iCaptureState | EEndCapture);
		}
	iData->iEndZ = aZDepth;
	iCaptureEndCalled = ETrue;
	return KErrNone;
	}

//----------------
// Demarcations
//----------------

void CTransitionParticipant::SetBeginDemarcation(TRect& aBeginRect, TCoordinateRef aCoordRef)
	{
	iCoordRefBegin = aCoordRef;
	iData->iBeginRect = aBeginRect;
	iCaptureState = (TCaptureState)(iCaptureState | EBeginCapture);
	}
	
void CTransitionParticipant::SetEndDemarcation(TRect& aEndRect, TCoordinateRef aCoordRef)
	{
	iCoordRefEnd = aCoordRef;
	iData->iEndRect = aEndRect;
	iCaptureState = (TCaptureState)(iCaptureState | EEndCapture);
	}

void CTransitionParticipant::ModifyCoordinates(TPoint& aBeginRef, TPoint& aEndRef)
	{
	if(iCoordRefBegin == CTransitionParticipant::EScreen)
		{
		iData->iBeginRect.iTl-=aBeginRef;
		iData->iBeginRect.iBr-=aBeginRef;
		}
	if(iCoordRefEnd == CTransitionParticipant::EScreen)
		{
		iData->iEndRect.iTl-=aEndRef;
		iData->iEndRect.iBr-=aEndRef;
		}
	}

//----------------
// MCommandBufferObserver functions
//----------------

void CTransitionParticipant::CommandBufferUpdated(const TRect& aDrawRect, const TRect& aBoundingRect)
	{
	if(!iInCapture) 
		{
		if(!iCaptureEndCalled)
			{
			iCommandsReceived = ETrue;
			}
		else if(iListensForUpdates)
			{
			RWsGraphicMsgBuf* commandbuffer = new RWsGraphicMsgBuf;
			if(commandbuffer) 
				{
				TRAPD(err, iRemoteGc->ExternalizeL(*(commandbuffer), ETrue));
				if(err == KErrNone)
					{
					iTransControl->ParticipantUpdated(this, commandbuffer, aDrawRect, aBoundingRect);
					}
			    commandbuffer->Close();
				delete commandbuffer;
				}
			}
		}
	}
