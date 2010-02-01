/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Anim Ctrl
*
*/


// AknAnimCtrl.CPP
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Animation Control


#include "aknAnimCtrl.h"
#include "aknanimdata.h"
#include "AknPanic.h"
#include <coemain.h>
#include <eikenv.h>
#include <eikappui.h>
#include <AknLayout.lag>
#include <AknUtils.h>
#include <aknappui.h>

CAknAnimationKeyWatcher* CAknAnimationKeyWatcher::NewL()
	{
	CAknAnimationKeyWatcher* self = new(ELeave)CAknAnimationKeyWatcher();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();		//self
	return self;
	}

CAknAnimationKeyWatcher::CAknAnimationKeyWatcher()
	{
	}

CAknAnimationKeyWatcher::~CAknAnimationKeyWatcher()
	{
	iEikonEnv->EikAppUi()->RemoveFromStack(this);
	}

void CAknAnimationKeyWatcher::ConstructL()
	{
	iEikonEnv->EikAppUi()->AddToStackL(this,ECoeStackPriorityEnvironmentFilter);
	ActivateL();
	}

TKeyResponse CAknAnimationKeyWatcher::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,TEventCode /*aType*/)
	{
	// If the animation animation is playing, cancel it but do not consume the key.
	// The underlying view then receives the key as normal.
	if (iAnimationCtrl)
		{
		// Animation is playing, so cancel it
		iAnimationCtrl->CancelAnimation();
		return EKeyWasNotConsumed;
		}

	// If the view has not yet been drawn, consume the key since this could
	// cause the view to change before the animation starts.
	return EKeyWasConsumed;
	}

void CAknAnimationKeyWatcher::SetAnimationControl(CAknAnimationCtrl* aAnimationCtrl)
	{
	iAnimationCtrl = aAnimationCtrl;
	}

CAknAnimationCtrl* CAknAnimationCtrl::NewL(CWindowGc& aWindowGc, CFbsBitmap& aViewBitmap, CFbsBitmap& aOriginalBitmap, CAknAnimationData* aData)
	{
	CAknAnimationCtrl* self = new(ELeave)CAknAnimationCtrl(aWindowGc, aViewBitmap, aOriginalBitmap, aData);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}


CAknAnimationCtrl::CAknAnimationCtrl(CWindowGc& aWindowGc, CFbsBitmap& aViewBitmap, CFbsBitmap& aOriginalBitmap, CAknAnimationData* aAnimationData)
:iWindowGc(aWindowGc), iViewBitmap(aViewBitmap), iOriginalBitmap(aOriginalBitmap), iAnimationData(aAnimationData)
	{
	}

CAknAnimationCtrl::~CAknAnimationCtrl()
	{
	}

void CAknAnimationCtrl::ConstructL()
	{
	CreateWindowL();
	__ASSERT_DEBUG(iAnimationData, Panic(EAknPanicNoAnimationData));
    iAnimationData->SetScreenSize(iAvkonAppUi->ApplicationRect().Size());
	//iAnimationData->SetScreenSize(TSize(AKN_LAYOUT_WINDOW_screen.iW,AKN_LAYOUT_WINDOW_screen.iH));
	iAnimationData->SetViewBitmap(&iViewBitmap);
	iAnimationData->SetOldBitmap(&iOriginalBitmap);
	}

void CAknAnimationCtrl::Draw(const TRect& /*aRect*/) const
	{
	if (iAnimationData->ClearOldView())
		iWindowGc.Clear();
	else
		iWindowGc.BitBlt(TPoint(0,0), &iOriginalBitmap);
	}


TBool CAknAnimationCtrl::DrawStep()
	{
	// Check if the animation has been cancelled
	if (iCancelled)
		return ETrue;

	iWindowGc.Activate(Window());
	TBool done = iAnimationData->DrawNextAnimationStep(iWindowGc);
	iWindowGc.Deactivate();
	return done;
	}


void CAknAnimationCtrl::CancelAnimation()
	{
	iCancelled = ETrue;
	}

// End of File
