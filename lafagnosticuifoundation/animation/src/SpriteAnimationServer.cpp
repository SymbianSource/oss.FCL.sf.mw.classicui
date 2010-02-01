// Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "SpriteAnimationServer.h"
#include "AnimationCmd.h"
#include "Animator.h"
#include "AnimationConfig.h"
#include "AnimationTls.h"
#include "AnimationTicker.h"

// Creates a CSpriteAnimationServer and returns a pointer to the object.
CSpriteAnimationServer* CSpriteAnimationServer::NewL()
	{
	CSpriteAnimationServer* self = new (ELeave) CSpriteAnimationServer();
	return self;
	}

CSpriteAnimationServer::~CSpriteAnimationServer()
	{
	iFunctions->GetRawEvents(EFalse);
	while (iFreezeCount > 0)
		{
		--iFreezeCount;
		iTls->Ticker()->Unfreeze();
		}
	delete iAnimator;
	delete iSpriteGc;
	delete iBitmapDevice;
	delete iMaskDevice;
	delete iDataType;
	if (iTls)
		iTls->Close();
	}

CSpriteAnimationServer::CSpriteAnimationServer()
	{
	}

void CSpriteAnimationServer::ConstructL(TAny* aArgs)
	{
	iTls = CAnimationTls::NewL();
	HBufC8* data = static_cast<HBufC8*>(aArgs);
	iDataType = HBufC8::NewL(data->Length());
	*iDataType = *data;
	iSpriteGc = CFbsBitGc::NewL();
	iAnimator = CAnimator::NewL(this);
	}

// Pure virtual function from CAnim.
void CSpriteAnimationServer::Command(TInt aOpcode, TAny* aArgs)
	{
	switch (aOpcode)
		{
		case EAnimationCmdStart:
			iAnimator->Start(*(static_cast<TAnimationConfig*>(aArgs)));
			break;
		case EAnimationCmdStop:
			iAnimator->Stop();
			break;
		case EAnimationCmdPause:
			iAnimator->Pause();
			break;
		case EAnimationCmdResume:
			iAnimator->Resume();
			break;
		case EAnimationCmdHold:
			iAnimator->Hold();
			break;
		case EAnimationCmdUnhold:
			iAnimator->Unhold();
			break;
		case EAnimationCmdFreeze:
			++iFreezeCount;
			iTls->Ticker()->Freeze();
			break;
		case EAnimationCmdUnfreeze:
			--iFreezeCount;
			iTls->Ticker()->Unfreeze();
			break;
		case EAnimationCmdHostHandle:
			iHostHandle = *(static_cast<TInt*>(aArgs));
			break;
		}
	}

// Pure virtual function from CAnim it handles the command received by the related client.
// aOpcode determines the action that has to be taken while aArgs contains the information
// packed by the client. It returns KErrNone if no problem has occurred.
TInt CSpriteAnimationServer::CommandReplyL(TInt aOpcode, TAny* aArgs)
	{
	TInt error = KErrNone;
	switch (aOpcode)
		{
		case EAnimationCmdDataEvent:
			ReceiveEventL(aArgs);
			break;
		case EAnimationCmdSize:
			error = ((iSize.iWidth & ((1 << 15)-1)) << 16) | (iSize.iHeight & ((1 << 15)-1));
			break;
		default:
			error = KErrNotSupported;
		}
	return error;
	}

void CSpriteAnimationServer::ReceiveEventL(TAny* aArgs)
	{
	TInt aEvent;
	TAny* aData;
	TInt aDataLength;
	aEvent = *(TInt*)aArgs;
	aDataLength = *(((TInt*)aArgs) + 1);
	aData = (((TInt*)aArgs) + 2);
	iAnimator->DataEventL(aEvent, aData, aDataLength);
	}

void CSpriteAnimationServer::Animate(TDateTime* /*aDateTime*/)
	{ // Empty implementation
	}

TBool CSpriteAnimationServer::OfferRawEvent(const TRawEvent& /*aRawEvent*/)
	{
	return EFalse;
	}

void CSpriteAnimationServer::PostHostEvent()
	{
	const TInt KUiqDummyKeyCode = 0xBABE;
	TKeyEvent event;
	event.iCode = KUiqDummyKeyCode ;
	event.iScanCode = KUiqDummyKeyCode ;
	event.iModifiers = 0;
	event.iRepeats = 0;
	iFunctions->PostKeyEvent(event);
	}


void CSpriteAnimationServer::AnimatorDraw()
	{
	if(iSpriteFunctions->SpriteCanBeSeen())
		{
		if(iFlags & EVirtualHold)
			{
			iFlags &= ~EVirtualHold;
			iAnimator->Hold();
			iAnimator->Unhold();
			}
		else
			{
			iSpriteGc->Activate(iBitmapDevice);
			iAnimator->Draw(*iSpriteGc);
			iSpriteGc->Activate(iMaskDevice);
			iAnimator->DrawMask(*iSpriteGc);

			iSpriteFunctions->UpdateMember(0, iSize, ETrue);
			}
		}
	else
		{
		// Virtual hold exists because if we actually hold the animator, we would no longer receive
		// calls to AnimatorDraw, and so we would never unhold it.
		iFlags |= EVirtualHold;
		}
	}

void CSpriteAnimationServer::AnimatorInitialisedL(const TSize& aSize)
	{
	iSize = aSize;
	TSpriteMember& spriteMember = *iSpriteFunctions->GetSpriteMember(0);
	spriteMember.iBitmap->Resize(iSize);
	spriteMember.iMaskBitmap->Resize(iSize);
	iSpriteFunctions->SizeChangedL();

	delete iBitmapDevice;
	iBitmapDevice = NULL;
	delete iMaskDevice;
	iMaskDevice = NULL;
	iBitmapDevice = CFbsBitmapDevice::NewL(spriteMember.iBitmap);
	iMaskDevice = CFbsBitmapDevice::NewL(spriteMember.iMaskBitmap);

	iSpriteGc->Activate(iMaskDevice);
	iSpriteGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
	iSpriteGc->SetBrushColor(KRgbBlack);
	iSpriteGc->DrawRect(iSize);
	iSpriteFunctions->UpdateMember(0, iSize, ETrue);

	iFunctions->GetRawEvents(ETrue);
	iSpriteFunctions->Activate(ETrue);
	
	PostHostEvent();
	}
	
void CSpriteAnimationServer::AnimatorResetL()
	{
	iSize.iWidth = 0;
	iSize.iHeight = 0;

	TSpriteMember& spriteMember = *iSpriteFunctions->GetSpriteMember(0);
	spriteMember.iBitmap->Resize(iSize);
	spriteMember.iMaskBitmap->Resize(iSize);
	iSpriteFunctions->SizeChangedL();
	
	iSpriteFunctions->Activate(EFalse);
	iFunctions->GetRawEvents(EFalse);
	delete iBitmapDevice;
	iBitmapDevice = NULL;
	delete iMaskDevice;
	iMaskDevice = NULL;
	iFlags = 0;
	}
	
const TPtrC8 CSpriteAnimationServer::AnimatorDataType() const
	{
	return *iDataType;
	}

CAnimationTicker& CSpriteAnimationServer::AnimatorTicker()
	{
	return *iTls->Ticker();
	}
