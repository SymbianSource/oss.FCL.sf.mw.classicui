/*
* Copyright (c) 2006-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  AVKON input blocker.
*
*/


#include "akninputblock.h"
#include <eikenv.h>
#include <eikappui.h>
#include <eikbtgpc.h>
#include <avkon.rsg>
#include <eikcba.h>
#include <avkon.hrh>

//Define command for MSK.
const TInt KBlockCBAMSKEmptyID = -100;

EXPORT_C CAknInputBlock* CAknInputBlock::NewLC()
	{
	CAknInputBlock* self = new(ELeave) CAknInputBlock;
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

EXPORT_C CAknInputBlock* CAknInputBlock::NewCancelHandlerLC(MAknInputBlockCancelHandler* aHandlerToCancel)
	{
	CAknInputBlock* self = NewLC();
	self->SetCancelHandler(aHandlerToCancel);
	return self;
	}

EXPORT_C CAknInputBlock* CAknInputBlock::NewCancelActiveLC(CActive* aActiveObjectToCancel)
	{
	CAknInputBlock* self = NewLC();
	self->SetCancelActive(aActiveObjectToCancel);
	return self;
	}

EXPORT_C CAknInputBlock* CAknInputBlock::NewCancelDeleteLC(CBase* aObjectToDelete)
	{
	CAknInputBlock* self = NewLC();
	self->SetCancelDelete(aObjectToDelete);
	return self;
	}

EXPORT_C CAknInputBlock::~CAknInputBlock()
	{
	iAppUi->RemoveFromStack(this);
	if (CapturesPointer())
		SetPointerCapture(EFalse);
	delete iCba;
	Cancel();
	}

EXPORT_C void CAknInputBlock::SetCancelHandler(MAknInputBlockCancelHandler* aHandlerToCancel)
	{
	iHandlerToCancel = aHandlerToCancel;
	}

EXPORT_C void CAknInputBlock::SetCancelActive(CActive* aActiveObjectToCancel)
	{
	iActiveObjectToCancel = aActiveObjectToCancel;
	}

EXPORT_C void CAknInputBlock::SetCancelDelete(CBase* aObjectToDelete)
	{
	iObjectToDelete = aObjectToDelete;
	}

EXPORT_C void CAknInputBlock::Cancel()
	{
	// move ownership to stack in case this is deleted
	MAknInputBlockCancelHandler* handlerToCancel = iHandlerToCancel;
	iHandlerToCancel = NULL;
	
	CActive* activeObjectToCancel = iActiveObjectToCancel;
	iActiveObjectToCancel = NULL;
	
	CBase* objectToDelete = iObjectToDelete;
	iObjectToDelete = NULL;

	if (handlerToCancel)
		{
		handlerToCancel->AknInputBlockCancel();
		}

	if (activeObjectToCancel)
		{
		activeObjectToCancel->Cancel();
		}

	if (objectToDelete)
		{
		delete objectToDelete;
		}
	}

CAknInputBlock::CAknInputBlock()
: iAppUi(iEikonEnv->EikAppUi())
	{
	}


void CAknInputBlock::ConstructL()
	{
	CreateWindowL();
	SetExtent(TPoint(0,0), TSize(0,0));
	ActivateL();
	iAppUi->AddToStackL(this, ECoeStackPriorityDialog);

    iCba = CEikButtonGroupContainer::NewL(
        CEikButtonGroupContainer::ECba,
        CEikButtonGroupContainer::EHorizontal,
        this,
        R_AVKON_SOFTKEYS_EMPTY);
    
    iCba->ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition(ECoeWinPriorityNeverAtFront);
    
    static_cast<CEikCba*>( iCba->ButtonGroup() )->SetButtonGroupFlags(
        iCba->ButtonGroup()->ButtonGroupFlags() | EAknCBAFlagRespondWhenInvisible );
    
    //Set the msk command to consume the EKeyOk event.  
    TBuf<5> tmp(_L(""));    
    iCba->SetCommandL( CEikButtonGroupContainer::EMiddleSoftkeyPosition, KBlockCBAMSKEmptyID, tmp );
    iCba->MakeVisible( EFalse );
    iCba->SetBoundingRect(TRect(iEikonEnv->ScreenDevice()->SizeInPixels()));
	}


TKeyResponse CAknInputBlock::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	if (aType == EEventKey && aKeyEvent.iCode == EKeyEscape)
		{
#ifdef _DEBUG
		if (!IsCancellable())
			RDebug::Print(_L("CAknInputBlock received Escape key while not cancellable"));
#endif
		Cancel();
		}
    return (aKeyEvent.iScanCode == EStdKeyYes ? EKeyWasNotConsumed : EKeyWasConsumed);	
	}

void CAknInputBlock::ProcessCommandL(TInt /*aCommandId*/)
    {
    }

void CAknInputBlock::FocusChanged(TDrawNow /*aDrawNow*/)
	{
	if (IsFocused())
		{
		SetPointerCapture(ETrue);
		ClaimPointerGrab(ETrue);
		}
	else
		{
		SetPointerCapture(EFalse);
		}
	}

bool CAknInputBlock::IsCancellable() const
	{
	bool cancellable = 
		iHandlerToCancel || 
		iActiveObjectToCancel ||
		iObjectToDelete;
	return cancellable;
	}
