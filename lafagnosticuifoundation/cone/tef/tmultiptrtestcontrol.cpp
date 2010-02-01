// Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "tmultiptrtestcontrol.h"
#include "tconemultiptrtestappui.h"
#include "tconemultiptrconst.h"
#include "tconemultiptrcompoundstep.h"


/**
 CCoeControl derived class. Acts as both event handler for events comming from wserv and an 
 event buffer for storing of events. 
 
 @param aWindowOwning defaulted to EFalse
*/
void CMultiPtrTestControlBase::ConstructL()
    {
    iEventBuffer.SetLengthL(EEventBufferSize);
    }


CMultiPtrTestControlBase::~CMultiPtrTestControlBase()
    {
    }


TInt CMultiPtrTestControlBase::EventsLeft()
	{
	return iEventBuffer.Count();
	}


void CMultiPtrTestControlBase::AddExpectedEvent( TAdvancedPointerEvent& aEvent)
	{
	iEventBuffer.Add( &aEvent );
	}


/**
 Handles events from wserv and does the testing by comparing those with the events from
 event buffer. If any test fails, it calls the Failed function of CConeMultiPtrTestAppUi
 which stops the activescheduler. Once all the evnts in buffer are tested it calls 
 NextSetOfEvents function to continue with other sub test case.
 */ 
void CMultiPtrTestControlBase::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
	CCoeControl::HandlePointerEventL( aPointerEvent );

	if( iPassive )
		{
		return;
		}
	
	const TAdvancedPointerEvent* advancedPointerEvent = aPointerEvent.AdvancedPointerEvent();
	
	TAdvancedPointerEvent expectedPtrEvent;
	
	if( 0 == iEventBuffer.Remove(&expectedPtrEvent) )
		{
		NotifyControlL( EMultiPtrTestFailed );
		return;
		}
	
	TRAPD( err, CheckEventL(expectedPtrEvent, *advancedPointerEvent) );
	
	if( ETestFailed == err )
		{
		NotifyControlL( EMultiPtrTestFailed );
		}
	else if( iEventBuffer.Count() == 0 )
		{
		NotifyControlL( EmultiPtrNext );
		}	
	
	}


/**
 Compare the parameters of the received event with those of the anticipated event.
*/
void CMultiPtrTestControlBase::CheckEventL(const TAdvancedPointerEvent& aExpectedEvent, const TAdvancedPointerEvent& aActualEvent)
	{
	RDebug::Print( _L("ExPtr %d AcPtr %d"), aExpectedEvent.PointerNumber(), aActualEvent.PointerNumber() );
	RDebug::Print( _L("ExType %d AcType %d"),aExpectedEvent.iType, aActualEvent.iType );
	RDebug::Print( _L("ExProx %d AcProx %d"), aExpectedEvent.ProximityAndPressure(), aActualEvent.ProximityAndPressure() );
	RDebug::Print( _L("ExPos X %d Y %d"), aExpectedEvent.iPosition.iX, aExpectedEvent.iPosition.iY );
	RDebug::Print( _L("AcPos X %d Y %d"), aActualEvent.iPosition.iX, aActualEvent.iPosition.iY );
	RDebug::Print( _L("ExMod 0x%X AcMod 0x%X"), aExpectedEvent.iModifiers, aActualEvent.iModifiers );
	
	TInt err = ETestPassed;
	
	if( aExpectedEvent.PointerNumber() != aActualEvent.PointerNumber() )
		{		
		RDebug::Print( _L("*** Pointer numbers differ") );
		err = ETestFailed;
		}

	if ( aExpectedEvent.iPosition != aActualEvent.iPosition )
		{	
		RDebug::Print( _L("*** Position data differs") );
		err = ETestFailed;
		}
	
	if ( aExpectedEvent.iParentPosition == aActualEvent.iParentPosition )
		{
		RDebug::Print( _L("*** ParentPosition data differs") );
		err = ETestFailed;
		}
	
	if( aExpectedEvent.iType != aActualEvent.iType )
		{
		RDebug::Print( _L("*** Type data differs") );
		err = ETestFailed;
		}

	// Disregard other modifiers, as build machines often have numlock, scroll-lock etc on.
	if( !(aActualEvent.iModifiers & EModifierAdvancedPointerEvent) )
		{	
		RDebug::Print( _L("*** Key modifier flags differ") );
		err = ETestFailed;
		}

	if( aExpectedEvent.ProximityAndPressure() != aActualEvent.ProximityAndPressure() )
		{
		RDebug::Print( _L("*** Proximity/pressure data differs") );
		err = ETestFailed;
		}

	
	if( ETestPassed != err )
		{
		RDebug::Print( _L("") );
		User::Leave( err );
		}
	
	RDebug::Print( _L("") );
	}


TBool CMultiPtrTestControlBase::Captures()
	{
	return CapturesPointer();
	}


void CMultiPtrTestControlBase::SetDrags()
	{
	Window().PointerFilter( (EPointerFilterMove | EPointerFilterDrag), 0 );
	}


void CMultiPtrTestControlBase::SetGrabs()
	{
	Window().SetPointerGrab( ETrue );
	}


void CMultiPtrTestControlBase::SetPassive( TBool aPassive )
	{
	iPassive = aPassive;
	}


//
/**
 A derived simple control
 for use with CConeMultiPtrTestAppUi
*/

/**
 PV in CMultiPtrTestControlBase
*/
void CMultiPtrTestControl::NotifyControlL( TInt aNotify )
	{
	switch( aNotify )
		{
	case EMultiPtrTestFailed:
		iAppUi->Failed();
		break;
		
	case EmultiPtrNext:	
		iAppUi->NextSetOfEventsL();
		break;
		
	default:
		User::Leave( KErrArgument );
		break;
		}
	}


void CMultiPtrTestControl::Draw( const TRect& ) const
	{
	CWindowGc& gc=SystemGc();
	
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(KRgbBlue);
	gc.DrawRect(Rect());	
	}



CMultiPtrTestControl* CMultiPtrTestControl::NewL( TPoint aOrigin, TSize aSize )
	{
	CMultiPtrTestControl* self = new(ELeave) CMultiPtrTestControl;
	CleanupStack::PushL( self );
	self->ConstructL( aOrigin, aSize );
	CleanupStack::Pop();
	
	return self;
	}


CMultiPtrTestControl::CMultiPtrTestControl()
	{
	
	}


void CMultiPtrTestControl::ConstructL( TPoint aOrigin, TSize aSize )
	{
	CMultiPtrTestControlBase::ConstructL();
	iAppUi  = static_cast<CConeMultiPtrTestAppUi*>(ControlEnv()->AppUi());
	
	CreateWindowL();
	Window().EnableAdvancedPointers();
	SetExtent( aOrigin, aSize );
    ActivateL();	
	}


CMultiPtrTestControl::~CMultiPtrTestControl()
	{
	}


//
/**
 A derived simple control
 for use with CConeMultiPtrCompoundTestAppUi
*/

/**
 PV in CMultiPtrTestControlBase
*/
void CMultiPtrTestCompoundAppUiControl::NotifyControlL( TInt aNotify )
	{
	switch( aNotify )
		{
	case EMultiPtrTestFailed:
		iAppUi->Failed();
		break;
		
	case EmultiPtrNext:	
		iAppUi->NextSetOfEventsL();
		break;
		
	default:
		User::Leave( KErrArgument );
		break;
		}
	}


void CMultiPtrTestCompoundAppUiControl::Draw( const TRect& ) const
	{
	CWindowGc& gc=SystemGc();
	
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(KRgbRed);
	gc.DrawRect(Rect());	
	}



CMultiPtrTestCompoundAppUiControl* CMultiPtrTestCompoundAppUiControl::NewL( TPoint aOrigin, TSize aSize )
	{
	CMultiPtrTestCompoundAppUiControl* self = new(ELeave) CMultiPtrTestCompoundAppUiControl;
	CleanupStack::PushL( self );
	self->ConstructL( aOrigin, aSize );
	CleanupStack::Pop();
	
	return self;
	}


CMultiPtrTestCompoundAppUiControl::CMultiPtrTestCompoundAppUiControl()
	{
	
	}


void CMultiPtrTestCompoundAppUiControl::ConstructL( TPoint aOrigin, TSize aSize )
	{
	CMultiPtrTestControlBase::ConstructL();
	iAppUi  = static_cast<CConeMultiPtrCompoundTestAppUi*>(ControlEnv()->AppUi());
	
	CreateWindowL();
	Window().EnableAdvancedPointers();
	SetExtent( aOrigin, aSize );
    ActivateL();	
	}


CMultiPtrTestCompoundAppUiControl::~CMultiPtrTestCompoundAppUiControl()
	{
	}

