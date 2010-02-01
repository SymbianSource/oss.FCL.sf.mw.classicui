/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#include <eikbutb.h>
#include <coemain.h>
#include "LAFBUTB.H"

const TInt KButtonStateMask             =0x000f;
const TInt KButtonPressedMask           =0x0010;
const TInt KButtonDrawStateMask         =0x001f;
const TInt KButtonReportOnPointerDown	=0x0020;
const TInt KButtonTristate	            =0x0040;
const TInt KButtonAllowTristate	        =0x0080;
const TInt KButtonBehaviorMask			=0x0f00;

const TInt KAnimationDelayInMicroSeconds=50000;

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U 
 */
EXPORT_C void CEikButtonBase::GetColorUseListL(CArrayFix<TCoeColorUse>& /*aColorUseList*/) const
	{
	}

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U 
 */
EXPORT_C void CEikButtonBase::HandleResourceChange(TInt aType)
	{
	CCoeControl::HandleResourceChange(aType);
	}

EXPORT_C CEikButtonBase::~CEikButtonBase()
    {
	}

EXPORT_C CEikButtonBase::CEikButtonBase()
    {
	__DECLARE_NAME(_S("CEikButtonBase"));
    }

EXPORT_C void CEikButtonBase::SetCoordinator(TEikButtonCoordinator* aButCoord)
	{
	iButCoord=aButCoord;
	}

EXPORT_C CEikButtonBase::TState CEikButtonBase::State() const
    {
    return((TState)(iButFlags&KButtonStateMask));
    }

EXPORT_C void CEikButtonBase::SetState(TState aState)
    {
    iButFlags&=(~KButtonStateMask);
    iButFlags|=aState;
    if (aState==EIndeterminate && iButFlags&KButtonAllowTristate)
        iButFlags|=KButtonTristate;
	if (aState==ESet && iButCoord)
		iButCoord->SetChosenButton(this);
    StateChanged();
    }

EXPORT_C void CEikButtonBase::StateChanged()
	{
	}

EXPORT_C TBool CEikButtonBase::IsPressed() const
    {
    return(iButFlags&KButtonPressedMask);
    }

EXPORT_C CEikButtonBase::TDrawState CEikButtonBase::DrawState() const
    {
    return((TDrawState)(iButFlags&KButtonDrawStateMask));
    }

EXPORT_C void CEikButtonBase::CopyDrawStateTo(CEikButtonBase* aTargetButton) const
    { // intended to be called from inside the StateChanged() function of a container button
    aTargetButton->iButFlags&=(~KButtonDrawStateMask);
    aTargetButton->iButFlags|=DrawState();
    }

EXPORT_C void CEikButtonBase::SetReportOnPointerDown()
    {
    iButFlags|=KButtonReportOnPointerDown;
    }

EXPORT_C void CEikButtonBase::SetBehavior(TButtonBehavior aType)
    {
    if (aType&EEikButtonReportsOnPointerDown)
		SetReportOnPointerDown();
	iButFlags&=(~KButtonBehaviorMask);
    iButFlags|=(aType&(~EEikButtonReportsOnPointerDown));
    }

EXPORT_C TKeyResponse CEikButtonBase::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
	const TInt code=aKeyEvent.iCode;
	if (code==EKeyDownArrow || code ==EKeyUpArrow)
		return(EKeyWasNotConsumed);
    if (aType!=EEventKey)
        return(EKeyWasConsumed);
	CEikButtonBase::TState oldState=State();
   	switch (code)
        {
	case EKeyLeftArrow:
	case EKeyTab:
    case EKeyRightArrow:
		Animate();
	default:
		;
		}
	TKeyResponse ret=EKeyWasNotConsumed;
	if (State()!=oldState)
		{
		ReportEventL(MCoeControlObserver::EEventStateChanged);
		ret=EKeyWasConsumed;
		}
    return ret;
	}

EXPORT_C void CEikButtonBase::HandlePointerEventL(const TPointerEvent& /*aPointerEvent*/)
    {
    }

EXPORT_C void* CEikButtonBase::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C TCoeInputCapabilities CEikButtonBase::InputCapabilities() const
	{
	return LafButtonBase::InputCapabilities();
	}

TBool CEikButtonBase::ClickCompleted()
    {
    TButtonBehavior behav=(TButtonBehavior)(iButFlags&KButtonBehaviorMask);
    switch (State())
        {
    case EClear:
        if (behav==EEikButtonStaysClear)
            return(EFalse);
        SetState(iButFlags&KButtonTristate? EIndeterminate: ESet);
        break;
    case ESet:
		if (iButCoord || behav==EEikButtonStaysSet)
            return(EFalse);
        SetState(EClear);
        break;
    case EIndeterminate:
        SetState(ESet);
        break;
        }
    return(ETrue); // means SetState() was called
    }

EXPORT_C void CEikButtonBase::Animate()
    {
    iButFlags|=KButtonPressedMask;
    StateChanged();
    DrawNow();
    iCoeEnv->Flush(KAnimationDelayInMicroSeconds);
    iButFlags&=(~KButtonPressedMask);
    if (!ClickCompleted())
        StateChanged();
    DrawNow();
	iCoeEnv->WsSession().Flush();
    }

EXPORT_C void CEikButtonBase::SetAllowTristate()
    {
    iButFlags|=KButtonAllowTristate;
    }

EXPORT_C void CEikButtonBase::SetIgnoreNextPointerUp()
	{
	iButFlags|=EIgnoreNextPointerUp;
	}

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @internal
 * @since App-Framework_6.1
 */
#ifndef _DEBUG
EXPORT_C void CEikButtonBase::WriteInternalStateL(RWriteStream&) const
	{}
#else
EXPORT_C void CEikButtonBase::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	_LIT(KEikLitCmdButBaseCtlStart,"<CEikButtonBase>");
	_LIT(KEikLitCmdButBaseCtlEnd,"<\\CEikButtonBase>");
	_LIT(KEikLitCmdButBaseFlags,"<iButFlags>");
	_LIT(KEikLitCmdButBaseFlagsEnd,"<\\iButFlags>");
	
	aWriteStream << KEikLitCmdButBaseCtlStart;
	aWriteStream << KEikLitCmdButBaseFlags;
	aWriteStream.WriteInt32L(iButFlags);
	aWriteStream << KEikLitCmdButBaseFlagsEnd;
	CEikBorderedControl::WriteInternalStateL(aWriteStream);
	aWriteStream << KEikLitCmdButBaseCtlEnd;
	}
#endif

EXPORT_C void CEikButtonBase::Reserved_2()
	{}
EXPORT_C void CEikButtonBase::Reserved_3()
	{}

//
// class TEikButtonCoordinator
//

EXPORT_C TEikButtonCoordinator::TEikButtonCoordinator()
	: iChosenButton(NULL)
	{}

EXPORT_C void TEikButtonCoordinator::SetChosenButton(CEikButtonBase* aChosenButton)
	{
	if (iChosenButton==aChosenButton)
		return;
	if (iChosenButton)
		{
		iChosenButton->SetState(CEikButtonBase::EClear);
		iChosenButton->DrawNow();
		}
	iChosenButton=aChosenButton;
	}
