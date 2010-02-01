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

#include <coemain.h>
#include <coecntrl.h>
#include <coeaui.h>
#include "eikvcurs.h"
#include <eikenv.h>
#include <eikappui.h>
#include <uiklaf/private/lafvcurs.h>
#include <hal.h>
#include <eikpanic.h>

//
// class TEikVirtualCursor
//

TEikVirtualCursor::TEikVirtualCursor()
	:iState(ESuspended) 
/** Constructor.

Sets the cursor's state to ESuspended so that the call to switch off the virtual 
cursor will succeed when the application starts. Required due to the efficient 
implementation of SetCursorState(). */
	{}

EXPORT_C void TEikVirtualCursor::SetCursorStateL(TState aState, CCoeEnv& aEnv)
/** Sets the virtual cursor's state.

The suspended state is for use by clients that wish to temporarily disable the cursor 
but not to switch it off completely.

@param aState The virtual cursor's required state. 
@param aEnv The environment in which the virtual cursor exists. */
	{
#ifndef __X86GCC__
	if(aState!=iState) // more efficient to check than send all broadcasts
		{
		switch(aState)
			{
		case EOff:
		case ESuspended:
			SwitchOffEmulationAndBitmap(aEnv);
			break;
		case EOn:
			SwitchOnEmulationAndBitmap(aEnv);
			break;
			}
		
		CEikAppUi* appUi=static_cast<CEikAppUi*>(aEnv.AppUi());

		// Controls only need to act when state involves a switch to or from 'off'
		// Suspended is same as On to the Controls
		TBool reportNeeded=((aState!=EOff && iState==EOff) || (iState!=EOff && aState==EOff));
		iState=aState;
		if(appUi && reportNeeded)
			appUi->ReportResourceChangedToAppL(KEikMessageVirtualCursorStateChange);
		}
#endif // __X86GCC__ Disable virtual cursor updates for this platform
	}

EXPORT_C TEikVirtualCursor::TState TEikVirtualCursor::CursorState(CCoeEnv& /*aEnv*/)
/** Gets the virtual cursor's state.

@param aEnv The environment in which the virtual cursor exists. 
@return The virtual cursor's state. */
	{
	return iState;
	}

/**
Switches mouse/pointer cursor on and off according to cursor state.
@param aEnv 
@internalTechnology
*/
void TEikVirtualCursor::HandleAppToForeground(CCoeEnv& aEnv)
	{
#ifndef __X86GCC__
	if(iState==EOn)
		SwitchOnEmulationAndBitmap(aEnv); 
	else
		SwitchOffEmulationAndBitmap(aEnv); 
#endif // __X86GCC__
	}


/**
@internalComponent
*/
void TEikVirtualCursor::SwitchOnEmulationAndBitmap(CCoeEnv& aEnv)
	{		
#ifndef __X86GCC__
	RWsSession& wsSession=aEnv.WsSession();
	ASSERT(wsSession.Handle());

#ifdef _DEBUG
	TInt error=HAL::Set(HAL::EMouseState, HAL::EMouseState_Visible);
	__ASSERT_DEBUG((error==KErrNone || error==KErrNotSupported),Panic(EEikPanicVirtualCursorUndefinedError));
#else
	HAL::Set(HAL::EMouseState, HAL::EMouseState_Visible);
#endif
	wsSession.SetPointerCursorMode(LafVirtualCursor::PointerCursorOnMode());
#endif // __X86GCC__
	}

/**
@internalComponent
*/
void TEikVirtualCursor::SwitchOffEmulationAndBitmap(CCoeEnv& aEnv)
	{
#ifndef __X86GCC__
	RWsSession& wsSession=aEnv.WsSession();
	ASSERT(wsSession.Handle());

#ifdef _DEBUG
	TInt error=HAL::Set(HAL::EMouseState, HAL::EMouseState_Invisible);
	__ASSERT_DEBUG((error==KErrNone || error==KErrNotSupported),Panic(EEikPanicVirtualCursorUndefinedError));
#else
	HAL::Set(HAL::EMouseState, HAL::EMouseState_Invisible);
#endif
	wsSession.SetPointerCursorMode(EPointerCursorNone);
#endif // __X86GCC__
	}

