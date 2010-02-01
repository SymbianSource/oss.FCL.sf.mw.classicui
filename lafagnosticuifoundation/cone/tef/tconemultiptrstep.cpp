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

#include "TConeMultiPtrStep.h"
#include "tconemultiptrtestappui.h"
#include "tconemultiptrconst.h"
#include <hal.h>

// Global function for panic
void ConeTestPanic(TConeTestPanic aPanic)
	{
	User::Panic(_L("MultiPointerConeTest Panic"),aPanic);
	}



/**
 CTestStep derived class which implements RunTestStepL. It creates CoEnv & AppUi objects.
 Logic involved, RunTestStepL will call RunTestsL() which will create new control/s for each
 test case and calls NextSetOfEventsL() which does testing of all different use cases 
 i,e by simulating the events and adding the events to a buffer. 
 Then RunTestStepL() starts the active scheduler, which will result in a call to
 control's HandlePointerEventL, which will test expected event in buffer with actual event.
*/
CConeMultiPtrTestAppUi::CConeMultiPtrTestAppUi(CTmsTestStep* aStep) 
: CTestCoeAppUi(aStep)
	{
	}


void CConeMultiPtrTestAppUi::ConstructL()
	{
	RDebug::Print( _L(">CConeMultiPtrTestAppUi::ConstructL") );
	
	CTestCoeAppUi::ConstructL();
	iNormalPointerCursorArea = iCoeEnv->WsSession().PointerCursorArea();
	User::LeaveIfError( HAL::Get(HALData::EPointerMaxPointers, iMaxPointers) );
	User::LeaveIfError( HAL::Get(HALData::EPointerNumberOfPointers, iNumberOfPointers) );
	User::LeaveIfError( HAL::Get(HALData::EPointer3DMaxPressure, iMaxPressure) );
	User::LeaveIfError( HAL::Get(HALData::EPointer3DPressureStep, iPressureStep) );
	User::LeaveIfError( HAL::Get(HALData::EPointer3DMaxProximity, iMaxProximity) );
	User::LeaveIfError( HAL::Get(HALData::EPointer3DProximityStep, iProximityStep) );
	
	RDebug::Print( _L("CConeMultiPtrTestAppUi::ConstructL 1") );
	
	iPressureNominal = iPressureStep * (iMaxPressure / (iPressureStep * 2) ); // Somewhere in the middle
	iProximityNominal = iProximityStep * (iMaxProximity / (iProximityStep * 2) ); // Somewhere in the middle
		
	// Certain tests (MultiPointerGrab) can induce anomalous double-click key-modifiers.
	// Therefore, disable by setting the double-click max interval to zero.
	// This is restored in doTestStepPostambleL().
	RWsSession wsSession;
	TTimeIntervalMicroSeconds32 interval;
	TInt distance;
	
	User::LeaveIfError( wsSession.Connect() );
	wsSession.GetDoubleClickSettings( interval, distance);
	wsSession.SetDoubleClick( 0, distance);
	wsSession.Close();	

	
	AutoTestManager().StartAutoTest();
	
	RDebug::Print( _L("CConeMultiPtrTestAppUi::ConstructL>") );
	}


CConeMultiPtrTestAppUi::~CConeMultiPtrTestAppUi()
	{
	delete iControl;
	}


// Function called for each new test case from CTestManager active object.
void CConeMultiPtrTestAppUi::RunTestStepL(TInt /*aStepNum*/)
	{
    if (!ConfigurationSupportsPointerEventTesting())
        {
        INFO_PRINTF1(_L("Test skipped because config does not support pointer event testing"));
        AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
        return;
        }
	
	switch(iTestCase)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			RunTestsL();
			break;
			
		default:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
			break;
		}
	
	if (iFailed)
		{
		TEST(EFalse);
		iFailed=EFalse;
		}
	++iTestCase;
	}


/**
 Function called for each new test case from RunTestStepL.
 This creates control/s calls NextSetOfEventsL and starts activescheduler
 */
void CConeMultiPtrTestAppUi::RunTestsL()
	{
	iEventSet = 0;
	iCoeEnv->WsSession().SetAutoFlush(ETrue);

	iControl = CMultiPtrTestControl::NewL( KMultiPtrTestControlParentPosition, TSize(300,200) );
    AddToStackL(iControl);
    
    iEventCount = 0;
	TRAPD(err, NextSetOfEventsL());
	if (err != KErrNone)
		{
		INFO_PRINTF1( _L("ERROR INFO LOGGED IN epocwind.out") );
		
		iFailed = ETrue;
		return;
		}

	// Start nested activescheduler
	CActiveScheduler::Start();

	TInt eventsLeft = iControl->EventsLeft();
	if (eventsLeft > 0)
		{
		INFO_PRINTF1( _L("ERROR INFO LOGGED IN epocwind.out") );
		
		iFailed=ETrue;
		}

	RemoveFromStack(iControl);
	delete iControl;
	iControl = NULL;
	}

/**
 * Determine if the configuration supports pointer event testing.
 * 
 * There are certain circumstances where we want to skip pointer event
 * testing because we are simulating pointer events, and don't want to
 * simulate a pointer event from an impossible co-ordinate.  We'd rather
 * just identify that there is no point in doing the test and skip over
 * to the next test case.
 * 
 * In particular, when a ROM configured with a digitiser is deployed on a
 * Naviengine, with hardware configuration DIP switches which say that there
 * is an external screen connected, then no touch pad is active.
 * The base port under these conditions returns a digitiser area (0,0,0,0)
 * 
 * @return ETrue if the configuration supports pointer event testing, otherwise
 *         return EFalse.
 */
TBool CConeMultiPtrTestAppUi::ConfigurationSupportsPointerEventTesting() const
    {
    if (iNormalPointerCursorArea.IsEmpty())
        {
        return EFalse;
        }
    return ETrue;
    }


/**
 Simulates pointer event, by making use of UserSvr::AddEvent. Also takes a Z parameter.
*/
void CConeMultiPtrTestAppUi::SimulatePointer(TRawEvent::TType aType, TInt aX, TInt aY, TInt aZ, TUint8 aPointerNumber)
	{
	__ASSERT_DEBUG(ConfigurationSupportsPointerEventTesting(), ConeTestPanic(EConePanicNoDigitiser));
	
	TRawEvent rawEvent;

	rawEvent.Set(aType, aX, aY, aZ, aPointerNumber);
	UserSvr::AddEvent(rawEvent);
	}

void CConeMultiPtrTestAppUi::SimulatePointerDownUp(TInt aX, TInt aY, TInt aZ, TUint8 aPointerNumber)
	{
	SimulatePointer(TRawEvent::EButton1Down, aX, aY, aZ, aPointerNumber);
	SimulatePointer(TRawEvent::EButton1Up, aX, aY, aZ, aPointerNumber);
	}


void CConeMultiPtrTestAppUi::AddExpectedPointer( TAdvancedPointerEvent::TType aType, TPoint aPos, TInt aZ, TUint8 aPointerNumber, TInt /*Handle*/ )
	{
	TWsEvent event;
	TPoint3D point3D;
	
	point3D.iX = aPos.iX;
	point3D.iY = aPos.iY;
	point3D.iZ = aZ;
	
	// Note: this setter does not initialise the parent-position parameter.
	// Note: The modifier value is or'd in, as it is a bit-field. The TAdvancedPointerEvent Init()function 
	// should initialise it to EModifierAdvancedPointerEvent.
    event.InitAdvancedPointerEvent( aType, 0, point3D, aPointerNumber ); 
    event.Pointer()->iParentPosition.SetXY( KMultiPtrTestControlParentPosition.iX, KMultiPtrTestControlParentPosition.iY );
    
	iControl->AddExpectedEvent( *event.Pointer() );
	}


void CConeMultiPtrTestAppUi::AddExpectedPointerDownUp(TPoint aPos, TInt aZ, TUint8 aPointerNumber)
	{
	// Pointer position is with respect to the window's Top Left position
	// Here we may want to write a function which will set sent position with respect to control/window 
	// on which we are simulating the events. 
	aPos -= iControl->Position();
	AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, aPos, aZ, aPointerNumber );
	AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, aPos, aZ, aPointerNumber );
	}


/**
 once all the events for a given sub test are tested. So that next subtest case can proceed with it.
 */
void CConeMultiPtrTestAppUi::NextSetOfEventsL()
	{

	switch(iTestCase)
		{

	case 0:
		SetTestStepID(_L("UIF-WSERV-ADVANCEDPOINTER-0002"));
		MultiPointerEventsL();
		RecordTestResultL();
		break;
	
	case 1:
		SetTestStepID(_L("UIF-WSERV-ADVANCEDPOINTER-0006"));
		PressureAndProximityL();
		RecordTestResultL();
		break;	

	case 2:
		SetTestStepID(_L("UIF-WSERV-ADVANCEDPOINTER-0008"));		
		MoveAndDragL();
		RecordTestResultL();
		break;

	case 3:
		SetTestStepID(_L("UIF-WSERV-ADVANCEDPOINTER-0016"));
		MoveAndOutOfRangeL();
		RecordTestResultL();
		break;
		
	case 4:
		SetTestStepID(_L("UIF-WSERV-ADVANCEDPOINTER-0018"));
		PointerNumberOutOfRangeL();
		RecordTestResultL();
		break;

	case 5:
		SetTestStepID(_L("UIF-WSERV-ADVANCEDPOINTER-0020"));
		MultiPointerCaptureL();
		RecordTestResultL();
		break;
		
	case 6:
		SetTestStepID(_L("UIF-WSERV-ADVANCEDPOINTER-0022"));
		MultiPointerGrabL();
		RecordTestResultL();
		CloseTMSGraphicsStep();
		break;
		
	default:
		ConeTestPanic(EConeTestPanicWrongTest);
		break;
		}
	
	}


/**
@SYMTestCaseID 			UIF-WSERV-ADVANCEDPOINTER-0002
@SYMPREQ 				PREQ1226
@SYMTestType			UT
@SYMTestPriority		Critical
@SYMTestStatus 			Implemented
@SYMTestCaseDesc		Multi-touch pointer events in Cone.
@SYMTestActions			
@SYMTestExpectedResults  The received events should match the simulated raw events.
*/
void CConeMultiPtrTestAppUi::MultiPointerEventsL()
	{
	INFO_PRINTF1( _L(">MultiPointerEventsL") );
	RDebug::Print( _L(">MultiPointerEventsL") );
	
	if( iNumberOfPointers <= 1 )
		{
		User::Leave( KErrNotSupported );
		}
	
	switch( iEventSet++ )
		{
		case 0:
			{
			INFO_PRINTF1( _L("MultiPointerEventsL case 0") );
			
			TPoint ptrPos( 60, 60 );
			TInt z = iPressureNominal;
			TInt i = 0;
			
			for(; i < iNumberOfPointers; i++ )
				{
				ptrPos.iX += KMultiPtrTestCoOrdinateIncrement;
				ptrPos.iY += KMultiPtrTestCoOrdinateIncrement;
				
				SimulatePointerDownUp( ptrPos.iX, ptrPos.iY, z, i );
				AddExpectedPointerDownUp( ptrPos, z, i );
				}
			
			}
			break;
			 
		default:
			{
			CActiveScheduler::Stop();
			iEventSet = 0;
			INFO_PRINTF1( _L("MultiPointerEventsL STOP\n") );
			RDebug::Print( _L("MultiPointerEventsL STOP") );
			RDebug::Print( _L("") );
			}
			break;
		}
	
	}


/**
@SYMTestCaseID 			UIF-WSERV-ADVANCEDPOINTER-0006
@SYMPREQ 				PREQ1226
@SYMTestType			UT
@SYMTestPriority		Critical
@SYMTestStatus 			Implemented
@SYMTestCaseDesc		To check events received by the control (from different pointers) 
						have pressure and proximity and move events in them.
@SYMTestActions			
@SYMTestExpectedResults  Simulated events are correctly conveyed.
*/
void CConeMultiPtrTestAppUi::PressureAndProximityL()
	{
	INFO_PRINTF1( _L(">PressureAndProximityL") );
	RDebug::Print( _L(">PressureAndProximityL") );
	
	if( iNumberOfPointers <= 1 )
		{
		User::Leave( KErrNotSupported );
		}
	
	const TInt KPressureProximityInitialX = 60;
	const TInt KPressureProximityInitialY = 60;
	TPoint ptrPos( KPressureProximityInitialX, KPressureProximityInitialY );
	TPoint incPoint( KMultiPtrTestCoOrdinateIncrement, KMultiPtrTestCoOrdinateIncrement );

	iControl->SetDrags();
		
	switch( iEventSet++ )
		{ 
		case 0:
			{
			INFO_PRINTF1( _L("PressureAndProximityL case 0") );
			RDebug::Print( _L("PressureAndProximityL case 0") );
			// Two pointers. Some pressure. Position is wrt the screen
			SimulatePointer( TRawEvent::EButton1Down, ptrPos.iX, ptrPos.iY, iPressureNominal, KMultiPtrTestPointerNumberLowest );
			SimulatePointer( TRawEvent::EButton1Down, ptrPos.iX, ptrPos.iY, (iPressureNominal + iPressureStep), KMultiPtrTestPointerNumberLowest + 1 );
			// Reported position is wrt the control.
			ptrPos -= iControl->Position();
			AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, ptrPos, iPressureNominal, KMultiPtrTestPointerNumberLowest );
			AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, ptrPos, (iPressureNominal + iPressureStep), KMultiPtrTestPointerNumberLowest + 1 );
			}
			break;
			
		case 1:
			{
			INFO_PRINTF1( _L("PressureAndProximityL case 1") );
			RDebug::Print( _L("PressureAndProximityL case 1") );
			// Two pointers. Max pressure. Position is wrt the screen
			ptrPos += incPoint;
			SimulatePointer( TRawEvent::EButton1Down, ptrPos.iX, ptrPos.iY, iMaxPressure, KMultiPtrTestPointerNumberLowest );
			SimulatePointer( TRawEvent::EButton1Down, ptrPos.iX, ptrPos.iY, iMaxPressure, KMultiPtrTestPointerNumberLowest + 1 );
			// Reported position is wrt the control.
			ptrPos -= iControl->Position();
			AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, ptrPos, iMaxPressure, KMultiPtrTestPointerNumberLowest );
			AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, ptrPos, iMaxPressure, KMultiPtrTestPointerNumberLowest + 1 );
			}
			break;		
	
		case 2:
			{
			INFO_PRINTF1( _L("PressureAndProximityL case 2") );
			RDebug::Print( _L("PressureAndProximityL case 2") );
			// Two pointers. Some proximity plus pointer-move events. 
			//Differentiate ptr no's so WServe does not translate to EDrag because of the above button-down events.
			ptrPos += incPoint;
			SimulatePointer( TRawEvent::EPointerMove, ptrPos.iX, ptrPos.iY, iProximityNominal, KMultiPtrTestPointerNumberLowest + 2 );
			SimulatePointer( TRawEvent::EPointerMove, ptrPos.iX, ptrPos.iY, (iProximityNominal + iProximityStep), KMultiPtrTestPointerNumberLowest + 3 );
			
			ptrPos -= iControl->Position();
			AddExpectedPointer( TAdvancedPointerEvent::EMove, ptrPos, iProximityNominal, KMultiPtrTestPointerNumberLowest + 2 );
			AddExpectedPointer( TAdvancedPointerEvent::EMove, ptrPos, (iProximityNominal + iProximityStep), KMultiPtrTestPointerNumberLowest + 3 );
			}
			break;
			
		case 3:
			{
			INFO_PRINTF1( _L("PressureAndProximityL case 3") );
			RDebug::Print( _L("PressureAndProximityL case 3") );
			// Two pointers. Max proximity plus pointer-move events.
			ptrPos += incPoint;
			SimulatePointer( TRawEvent::EPointerMove, ptrPos.iX, ptrPos.iY, iMaxProximity, KMultiPtrTestPointerNumberLowest + 2 );
			SimulatePointer( TRawEvent::EPointerMove, ptrPos.iX, ptrPos.iY, iMaxProximity, KMultiPtrTestPointerNumberLowest + 3 );
			
			ptrPos -= iControl->Position();
			AddExpectedPointer( TAdvancedPointerEvent::EMove, ptrPos, iMaxProximity, KMultiPtrTestPointerNumberLowest + 2 );
			AddExpectedPointer( TAdvancedPointerEvent::EMove, ptrPos, iMaxProximity, KMultiPtrTestPointerNumberLowest + 3 );
			}
			break;		
	
		default:
			{
			INFO_PRINTF1( _L("PressureAndProximityL STOP\n") );
			RDebug::Print( _L("PressureAndProximityL STOP") );
			RDebug::Print( _L("") );
			
			CActiveScheduler::Stop();
			iEventSet = 0;
			}
			break;
		}	
	
	}


/**
@SYMTestCaseID 			UIF-WSERV-ADVANCEDPOINTER-0008
@SYMPREQ 				PREQ1226
@SYMTestType			UT
@SYMTestPriority		Critical
@SYMTestStatus 			Implemented
@SYMTestCaseDesc		To check the Control receives move and drags from different pointers 
						and that moves are delivered as moves, or translated to drags 
						dependent upon whether the pointer is up or down.
@SYMTestActions			
@SYMTestExpectedResults  The received events must match the simulated raw events. Moves being 
						 translated to drags in the button-down state.
*/
void CConeMultiPtrTestAppUi::MoveAndDragL()
	{
	INFO_PRINTF1( _L(">MoveAndDragL") );
	RDebug::Print( _L(">MoveAndDragL") );
	
	if( iNumberOfPointers <= 1 )
		{
		User::Leave( KErrNotSupported );
		}

	const TInt KMoveAndDragInitialX = 100;
	const TInt KMoveAndDragInitialY = 100;
	TPoint ptrPos( KMoveAndDragInitialX, KMoveAndDragInitialY );
	TPoint incPoint( KMultiPtrTestCoOrdinateIncrement, KMultiPtrTestCoOrdinateIncrement );
	TPoint exPos( ptrPos - iControl->Position() ); // The initial expected position adjusted for the control's offset
	
	iControl->SetDrags();
	
	switch( iEventSet++ )
		{
		case 0:
			{
			INFO_PRINTF1( _L("MoveAndDragL case 0") );
			RDebug::Print( _L("MoveAndDragL case 0") );
			
			// Anomalous: Send button-up so that EPointerMove -> EMove
			SimulatePointer( TRawEvent::EButton1Up, ptrPos.iX, ptrPos.iY, iProximityNominal, KMultiPtrTestPointerNumberLowest );
			AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, exPos, iProximityNominal, KMultiPtrTestPointerNumberLowest );			
			
			ptrPos += incPoint;
			exPos +=incPoint;
			SimulatePointer( TRawEvent::EPointerMove, ptrPos.iX, ptrPos.iY, (iProximityNominal + iProximityStep), KMultiPtrTestPointerNumberLowest );			
			AddExpectedPointer( TAdvancedPointerEvent::EMove, exPos, (iProximityNominal + iProximityStep), KMultiPtrTestPointerNumberLowest );
			// Send button-down so that EPointerMove -> EDrag
			SimulatePointer( TRawEvent::EButton1Down, ptrPos.iX, ptrPos.iY, (iProximityNominal + iProximityStep), KMultiPtrTestPointerNumberLowest );			
			AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, exPos, (iProximityNominal + iProximityStep), KMultiPtrTestPointerNumberLowest );
				
			ptrPos += incPoint;
			exPos +=incPoint;
			SimulatePointer( TRawEvent::EPointerMove, ptrPos.iX, ptrPos.iY, (iProximityNominal + (2 * iProximityStep)), KMultiPtrTestPointerNumberLowest );	
			AddExpectedPointer( TAdvancedPointerEvent::EDrag, exPos, (iProximityNominal + (2 * iProximityStep)), KMultiPtrTestPointerNumberLowest );
			// Anomalous: Send button-up so that EPointerMove -> EMove
			SimulatePointer( TRawEvent::EButton1Up, ptrPos.iX, ptrPos.iY, iProximityNominal, KMultiPtrTestPointerNumberLowest );
			AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, exPos, iProximityNominal, KMultiPtrTestPointerNumberLowest );			

			ptrPos += incPoint;
			exPos +=incPoint;
			SimulatePointer( TRawEvent::EPointerMove, ptrPos.iX, ptrPos.iY, (iProximityNominal + iProximityStep), KMultiPtrTestPointerNumberLowest );			
			AddExpectedPointer( TAdvancedPointerEvent::EMove, exPos, (iProximityNominal + iProximityStep), KMultiPtrTestPointerNumberLowest );
			}
			break;
		case 1:
			{
			INFO_PRINTF1( _L("MoveAndDragL case 1") );
			RDebug::Print( _L("MoveAndDragL case 1") );
			// Replicate case 0 for another pointer number.
			const TInt pointerNumber = KMultiPtrTestPointerNumberLowest + 1;
			
			// Anomalous: Send button-up so that EPointerMove -> EMove
			SimulatePointer( TRawEvent::EButton1Up, ptrPos.iX, ptrPos.iY, iProximityNominal, pointerNumber );
			AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, exPos, iProximityNominal, pointerNumber );			
			
			ptrPos += incPoint;
			exPos +=incPoint;
			SimulatePointer( TRawEvent::EPointerMove, ptrPos.iX, ptrPos.iY, (iProximityNominal + iProximityStep), pointerNumber );			
			AddExpectedPointer( TAdvancedPointerEvent::EMove, exPos, (iProximityNominal + iProximityStep), pointerNumber );
			// Send button-down so that EPointerMove -> EDrag
			SimulatePointer( TRawEvent::EButton1Down, ptrPos.iX, ptrPos.iY, (iProximityNominal + iProximityStep), pointerNumber );			
			AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, exPos, (iProximityNominal + iProximityStep), pointerNumber );
				
			ptrPos += incPoint;
			exPos +=incPoint;
			SimulatePointer( TRawEvent::EPointerMove, ptrPos.iX, ptrPos.iY, (iProximityNominal + (2 * iProximityStep)), pointerNumber );	
			AddExpectedPointer( TAdvancedPointerEvent::EDrag, exPos, (iProximityNominal + (2 * iProximityStep)), pointerNumber );
			// Anomalous: Send button-up so that EPointerMove -> EMove
			SimulatePointer( TRawEvent::EButton1Up, ptrPos.iX, ptrPos.iY, iProximityNominal, pointerNumber );
			AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, exPos, iProximityNominal, pointerNumber );			

			ptrPos += incPoint;
			exPos +=incPoint;
			SimulatePointer( TRawEvent::EPointerMove, ptrPos.iX, ptrPos.iY, (iProximityNominal + iProximityStep), pointerNumber );			
			AddExpectedPointer( TAdvancedPointerEvent::EMove, exPos, (iProximityNominal + iProximityStep), pointerNumber );
			}
			break;

		case 2:
			{
			INFO_PRINTF1( _L("MoveAndDragL case 2") );
			RDebug::Print( _L("MoveAndDragL case 2") );
			// Discriminate the pointers' attributes by position and prox/press.
			TPoint ptr0Pos( ptrPos );
			TPoint ptr0ExpectedPos( ptrPos - iControl->Position() );
			TPoint ptr1Pos( ptrPos += incPoint ); 
			TPoint ptr1ExpectedPos( ptr1Pos - iControl->Position() );
			TInt pointer0Proximity = iProximityNominal;
			TInt pointer1Proximity = iProximityNominal + iProximityStep;
			TInt pointer0Pressure = iPressureNominal;
			TInt pointer1Pressure = iPressureNominal + iPressureStep;

			const TInt pointerZero = KMultiPtrTestPointerNumberLowest;
			const TInt pointerOne = KMultiPtrTestPointerNumberLowest + 1;
			
			// Anomalous: Send button-up so that EPointerMove -> EMove
			SimulatePointer( TRawEvent::EButton1Up, ptr0Pos.iX, ptr0Pos.iY, pointer0Proximity, pointerZero );
			AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, ptr0ExpectedPos, pointer0Proximity, pointerZero );			
			
			SimulatePointer( TRawEvent::EButton1Up, ptr1Pos.iX, ptr1Pos.iY, pointer1Proximity, pointerOne );
			AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, ptr1ExpectedPos, pointer1Proximity, pointerOne );			
			
			
			ptr0Pos += incPoint;
			ptr1Pos +=incPoint;
			ptr0ExpectedPos +=incPoint;
			ptr1ExpectedPos +=incPoint;
			pointer0Proximity += iProximityStep;
			pointer1Proximity += iProximityStep;

			SimulatePointer( TRawEvent::EPointerMove, ptr0Pos.iX, ptr0Pos.iY, pointer0Proximity, pointerZero );			
			AddExpectedPointer( TAdvancedPointerEvent::EMove, ptr0ExpectedPos, pointer0Proximity, pointerZero );

			SimulatePointer( TRawEvent::EPointerMove, ptr1Pos.iX, ptr1Pos.iY, pointer1Proximity, pointerOne );			
			AddExpectedPointer( TAdvancedPointerEvent::EMove, ptr1ExpectedPos, pointer1Proximity, pointerOne );
			
			RDebug::Print( _L("Button down") );
			// Send button-down so that EPointerMove -> EDrag
			SimulatePointer( TRawEvent::EButton1Down, ptr1Pos.iX, ptr1Pos.iY, pointer0Pressure, pointerZero );			
			AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, ptr1ExpectedPos, pointer0Pressure, pointerZero );
				
			SimulatePointer( TRawEvent::EButton1Down, ptr1Pos.iX, ptr1Pos.iY, pointer1Pressure, pointerOne );			
			AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, ptr1ExpectedPos, pointer1Pressure, pointerOne );
			
		
			ptr0Pos += incPoint;
			ptr1Pos +=incPoint;
			ptr0ExpectedPos +=incPoint;
			ptr1ExpectedPos +=incPoint;
			pointer0Pressure += iPressureStep;
			pointer1Pressure += iPressureStep;

			// Perform moves in anticipation of drags.
			SimulatePointer( TRawEvent::EPointerMove, ptr0Pos.iX, ptr0Pos.iY, pointer0Pressure, pointerZero );	
			AddExpectedPointer( TAdvancedPointerEvent::EDrag, ptr0ExpectedPos, pointer0Pressure, pointerZero );

			SimulatePointer( TRawEvent::EPointerMove, ptr1Pos.iX, ptr1Pos.iY, pointer1Pressure, pointerOne );	
			AddExpectedPointer( TAdvancedPointerEvent::EDrag, ptr1ExpectedPos, pointer1Pressure, pointerOne );
			
			
			ptr0Pos += incPoint;
			ptr1Pos +=incPoint;
			ptr0ExpectedPos +=incPoint;
			ptr1ExpectedPos +=incPoint;
			pointer0Proximity += iProximityStep;
			pointer1Proximity += iProximityStep;

			// Send button-up so that EPointerMove -> EMove
			SimulatePointer( TRawEvent::EButton1Up, ptr0Pos.iX, ptr0Pos.iY, pointer0Proximity, pointerZero );
			AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, ptr0ExpectedPos, pointer0Proximity, pointerZero );			

			SimulatePointer( TRawEvent::EButton1Up, ptr1Pos.iX, ptr1Pos.iY, pointer1Proximity, pointerOne );
			AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, ptr1ExpectedPos, pointer1Proximity, pointerOne );			
			
			
			ptr0Pos += incPoint;
			ptr1Pos +=incPoint;
			ptr0ExpectedPos +=incPoint;
			ptr1ExpectedPos +=incPoint;

			SimulatePointer( TRawEvent::EPointerMove, ptr0Pos.iX, ptr0Pos.iY, pointer0Proximity, pointerZero );			
			AddExpectedPointer( TAdvancedPointerEvent::EMove, ptr0ExpectedPos, pointer0Proximity, pointerZero );

			SimulatePointer( TRawEvent::EPointerMove, ptr1Pos.iX, ptr1Pos.iY, pointer1Proximity, pointerOne );			
			AddExpectedPointer( TAdvancedPointerEvent::EMove, ptr1ExpectedPos, pointer1Proximity, pointerOne );
			}
			break;
		default:
			{
			INFO_PRINTF1( _L("MoveAndDragL STOP\n") );
			RDebug::Print( _L("MoveAndDragL STOP") );
			RDebug::Print( _L("") );
			
			CActiveScheduler::Stop();
			iEventSet = 0;
			}
			break;
		}
	
	}


/**
@SYMTestCaseID 			UIF-WSERV-ADVANCEDPOINTER-0016
@SYMPREQ 				PREQ1226
@SYMTestType			UT
@SYMTestPriority		Critical
@SYMTestStatus 			Implemented
@SYMTestCaseDesc		Out of range and move events in Cone.
@SYMTestActions			Simulate TRawEvent::EMove from 2 pointers.
						Simulate TRawEvent::EPointer3DOutOfRange from 2 pointers.
						cf GRAPHICS-WSERV-ADVANCEDPOINTER-0042
@SYMTestExpectedResults  The received events must match the events added to buffer.
*/
void CConeMultiPtrTestAppUi::MoveAndOutOfRangeL()
	{
	INFO_PRINTF1( _L(">MoveAndOutOfRangeL") );
	RDebug::Print( _L(">MoveAndOutOfRangeL") );
	
	if( iNumberOfPointers <= 1 )
		{
		User::Leave( KErrNotSupported );
		}
	
	iControl->SetDrags();
	
	switch( iEventSet++ )
		{
		case 0:
			{
			INFO_PRINTF1( _L("MoveAndOutOfRangeL case 0") );
			RDebug::Print( _L("MoveAndOutOfRangeL STOP\n") );
			const TInt KPressureProximityInitialX = 60;
			const TInt KPressureProximityInitialY = 60;
			TPoint ptrPos( KPressureProximityInitialX, KPressureProximityInitialY );
			TPoint incPoint( KMultiPtrTestCoOrdinateIncrement, KMultiPtrTestCoOrdinateIncrement );

			// Two pointers. Move events
			SimulatePointer( TRawEvent::EPointerMove, ptrPos.iX, ptrPos.iY, iProximityNominal, KMultiPtrTestPointerNumberLowest );
			SimulatePointer( TRawEvent::EPointerMove, ptrPos.iX, ptrPos.iY, iProximityNominal, KMultiPtrTestPointerNumberLowest + 1 );
			ptrPos -= iControl->Position();
			AddExpectedPointer( TAdvancedPointerEvent::EMove, TPoint(ptrPos.iX, ptrPos.iY), iProximityNominal, KMultiPtrTestPointerNumberLowest );
			AddExpectedPointer( TAdvancedPointerEvent::EMove, TPoint(ptrPos.iX, ptrPos.iY), iProximityNominal, KMultiPtrTestPointerNumberLowest + 1 );
			
			// Reset the position.
			ptrPos.SetXY( KPressureProximityInitialX, KPressureProximityInitialY );
			SimulatePointer( TRawEvent::EPointer3DOutOfRange, ptrPos.iX, ptrPos.iY, iProximityNominal, KMultiPtrTestPointerNumberLowest );
			SimulatePointer( TRawEvent::EPointer3DOutOfRange, ptrPos.iX, ptrPos.iY, iProximityNominal, KMultiPtrTestPointerNumberLowest + 1 );
			ptrPos -= iControl->Position();
			AddExpectedPointer( TAdvancedPointerEvent::EOutOfRange, TPoint(ptrPos.iX, ptrPos.iY), iProximityNominal, KMultiPtrTestPointerNumberLowest );			
			AddExpectedPointer( TAdvancedPointerEvent::EOutOfRange, TPoint(ptrPos.iX, ptrPos.iY), iProximityNominal, KMultiPtrTestPointerNumberLowest + 1 );			

			}
			break;
	
		default:
			{
			INFO_PRINTF1( _L("MoveAndOutOfRangeL STOP\n") );
			RDebug::Print( _L("MoveAndOutOfRangeL STOP\n") );
			RDebug::Print( _L("") );
			
			CActiveScheduler::Stop();
			iEventSet = 0;
			}
			break;
		}	
	
	}


/**
@SYMTestCaseID 			UIF-WSERV-ADVANCEDPOINTER-0018
@SYMPREQ 				PREQ1226
@SYMTestType			UT
@SYMTestPriority		Critical
@SYMTestStatus 			Implemented
@SYMTestCaseDesc		Check cone ignores pointer numbers greater than EPointerNumberOfPointers but less than EPointerMaxPointers.
@SYMTestActions			
@SYMTestExpectedResults  The first reported event should be the first legal one. The illegally-numbered-pointer event should be ignored.
*/
void CConeMultiPtrTestAppUi::PointerNumberOutOfRangeL()
	{
	INFO_PRINTF1( _L(">PointerNumberOutOfRange") );
	RDebug::Print( _L(">PointerNumberOutOfRange") );

	// Compose an illegitimately numbered pointer. (Pointers are numbered from 0)
	const TInt illegitimatePointerNumber = iNumberOfPointers; // One more than the maximally-numbered pointer
	const TInt nominalPressureOne = iPressureNominal;
	const TInt nominalPressureTwo = iPressureNominal + iPressureStep;
	
	if( (iNumberOfPointers <= 1)
	 || (illegitimatePointerNumber >= iMaxPointers) )
		{
		User::Leave( KErrNotSupported );
		}

	switch( iEventSet++ )
		{
		case 0:
			{
			INFO_PRINTF1( _L("PointerNumberOutOfRange case 0") );
			RDebug::Print( _L("PointerNumberOutOfRange case 0") );
			
			const TInt KPointerNumberOutOfRangeInitialX = 60;
			const TInt KPointerNumberOutOfRangeInitialY = 60;
			TPoint ptrPos( KPointerNumberOutOfRangeInitialX, KPointerNumberOutOfRangeInitialY );
			TPoint incPoint( KMultiPtrTestCoOrdinateIncrement, KMultiPtrTestCoOrdinateIncrement );
			// Generate a button-down event from an illegally numbered pointer
			SimulatePointer( TRawEvent::EButton1Down, ptrPos.iX, ptrPos.iY, nominalPressureOne, illegitimatePointerNumber );
			// Generate a legal event. Differentiate the event in terms of position and pressure also.
			ptrPos += incPoint;
			SimulatePointer( TRawEvent::EButton1Down, ptrPos.iX, ptrPos.iY, nominalPressureTwo, (iNumberOfPointers - 1) );
			ptrPos -= iControl->Position(); // Compensate for co-ordinate-within-control.
			AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, TPoint(ptrPos.iX, ptrPos.iY), nominalPressureTwo, (iNumberOfPointers - 1) );
			}
			break;
	
		default:
			{
			INFO_PRINTF1( _L("PointerNumberOutOfRange STOP\n") );
			RDebug::Print( _L("PointerNumberOutOfRange STOP") );
			RDebug::Print( _L("") );
			
			CActiveScheduler::Stop();
			iEventSet = 0;
			}
			break;
		}	
	
	}


/**
@SYMTestCaseID 			UIF-WSERV-ADVANCEDPOINTER-0020
@SYMPREQ 				PREQ1226
@SYMTestType			UT
@SYMTestPriority		Critical
@SYMTestStatus 			Implemented
@SYMTestCaseDesc		Check that Cone supports 'capture' in the case of multi-pointer events.
@SYMTestActions			Set the test-control to be capturing. Simulate EButton1Down from 2 pointers outside the control area. 
						Then simulate EButton1Down from a third pointer inside the control.
						cf GRAPHICS-WSERV-ADVANCEDPOINTER-0040
@SYMTestExpectedResults Pointer events inside and outside the control are delivered to the control.
*/
void CConeMultiPtrTestAppUi::MultiPointerCaptureL()
	{
	INFO_PRINTF1( _L(">MultiPointerCaptureL") );
	RDebug::Print( _L(">MultiPointerCaptureL") );
		
	if( iNumberOfPointers <= 1 )
		{
		User::Leave( KErrNotSupported );
		}
	
	switch( iEventSet++ )
		{		
		case 0:
			{
			INFO_PRINTF1( _L("MultiPointerCaptureL case 0") );
			RDebug::Print( _L("MultiPointerCaptureL case 0") );

			TPoint decPoint( KMultiPtrTestCoOrdinateDecrementSmall, KMultiPtrTestCoOrdinateDecrementSmall );
			TPoint incPoint( KMultiPtrTestCoOrdinateIncrementSmall, KMultiPtrTestCoOrdinateIncrementSmall );
			
			TPoint outsidePoint_1( iControl->Position() );
			outsidePoint_1 -= decPoint;
			// The negative co-ordinates supplied to the control
			TPoint outsideResult_1( outsidePoint_1 - iControl->Position() );
			
			TPoint outsidePoint_2( outsidePoint_1 );
			outsidePoint_2 -= decPoint;
			// The negative co-ordinates supplied to the control
			TPoint outsideResult_2( outsidePoint_2 - iControl->Position() );
			
			TPoint insidePoint_1( iControl->Position() );
			insidePoint_1 += incPoint;
			TPoint insideResult_1( insidePoint_1 - iControl->Position() );
			
			const TInt nominalPressureOne = iPressureNominal;
			const TInt nominalPressureTwo = iPressureNominal + iPressureStep;
			
			iControl->SetGloballyCapturing( ETrue );
			iControl->SetPointerCapture( ETrue );
	
			TInt i = 2;
			TInt first = 0;
			TInt second = 0; 
			TInt third = 0;
			
			for(; i < iNumberOfPointers; i++ )
				{
				first = i - 2;
				second = i - 1; 
				third = i;
				
				// First pointer. Outside the control.
				SimulatePointer( TRawEvent::EButton1Down, outsidePoint_1.iX, outsidePoint_1.iY, nominalPressureOne, first );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, outsideResult_1, nominalPressureOne, first );
				// Next pointer. Outside the control.
				SimulatePointer( TRawEvent::EButton1Down, outsidePoint_2.iX, outsidePoint_2.iY, nominalPressureOne, second );			
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, outsideResult_2, nominalPressureOne, second );			
				// Next pointer. Inside the control.
				SimulatePointer( TRawEvent::EButton1Down, insidePoint_1.iX, insidePoint_1.iY, nominalPressureTwo, third );			
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, insideResult_1, nominalPressureTwo, third );	

				// Discriminate the next suite of events by co-ordinate
				outsidePoint_1 -= decPoint;
				outsideResult_1 -= decPoint;
				
				outsidePoint_2 -= decPoint;
				outsideResult_2 -= decPoint;
				
				insidePoint_1 += incPoint;
				insideResult_1 += incPoint;
				}	
			
			}
			break;

		default:
			{
			INFO_PRINTF1( _L("MultiPointerCaptureL STOP\n") );
			RDebug::Print( _L("MultiPointerCaptureL STOP") );
			RDebug::Print( _L("") );
			
			CActiveScheduler::Stop();
			iEventSet = 0;
			}
			break;
		}	
	
	}




/**
@SYMTestCaseID 			UIF-WSERV-ADVANCEDPOINTER-0022
@SYMPREQ 				PREQ1226
@SYMTestType			UT
@SYMTestPriority		Critical
@SYMTestStatus 			Implemented
@SYMTestCaseDesc		Check that Cone supports 'grabbing' in the case of multi-pointer events.
						Ensure that events outside the control are not grabbed if grabbing has not been enabled.
@SYMTestActions			
@SYMTestExpectedResults Events outside the control are supplied to the control only when grabbing has been enabled.
*/
void CConeMultiPtrTestAppUi::MultiPointerGrabL()
	{
	INFO_PRINTF1( _L(">MultiPointerGrabL") );
	RDebug::Print( _L(">MultiPointerGrabL") );
	
	if( iNumberOfPointers <= 1 )
		{
		User::Leave( KErrNotSupported );
		}

	
	switch( iEventSet++ )
		{
		case 0:
			{
			// Events outside the control are not reported when grabbing has not been enabled
			INFO_PRINTF1( _L("MultiPointerGrabL case 0") );
			RDebug::Print( _L("MultiPointerGrabL case 0") );
			
			TPoint decPoint( KMultiPtrTestCoOrdinateDecrement, KMultiPtrTestCoOrdinateDecrement );
			TPoint incPoint( KMultiPtrTestCoOrdinateIncrement, KMultiPtrTestCoOrdinateIncrement );
			
			TPoint outsidePoint_1( iControl->Position() );
			outsidePoint_1 -= decPoint;
			TPoint reportedOutsidePoint_1( outsidePoint_1 );
			reportedOutsidePoint_1 -= iControl->Position(); // Compensate for the reported position within the control.
			
			TPoint outsidePoint_2( outsidePoint_1 );
			outsidePoint_2 -= decPoint;
			TPoint reportedOutsidePoint_2( outsidePoint_2 );
			reportedOutsidePoint_2 -= iControl->Position(); // Compensate for the reported position within the control.
			
			TPoint insidePoint_1( iControl->Position() );
			insidePoint_1 += incPoint; // Place the co-ordinates within the control.
			TPoint reportedInsidePoint_1( insidePoint_1 );
			reportedInsidePoint_1 -= iControl->Position(); // Compensate for the reported position within the control.
			
			TPoint insidePoint_2( insidePoint_1 );
			insidePoint_2 += incPoint; // differentiate from insidePoint_1.
			TPoint reportedInsidePoint_2( insidePoint_2 );
			reportedInsidePoint_2 -= iControl->Position(); // Compensate for the reported position within the control.
			
			const TInt nominalPressureOne = iPressureNominal;
			const TInt nominalPressureTwo = iPressureNominal + iPressureStep;
			const TInt nominalProximityOne = iProximityNominal;
			const TInt nominalProximityTwo = iProximityNominal + iProximityStep;
			
			// ****** Grabbing not enabled
			iControl->SetDrags();
			TInt i = 1;
			
			for(; i < iNumberOfPointers; i++ )
				{
				// Only events within the control should be reported.
				
				// First pointer down.
				SimulatePointer( TRawEvent::EButton1Down, insidePoint_1.iX, insidePoint_1.iY, nominalPressureOne, i - 1 );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, reportedInsidePoint_1, nominalPressureOne, i - 1 );
				// First button move outside.
				SimulatePointer( TRawEvent::EPointerMove, outsidePoint_1.iX, outsidePoint_1.iY, nominalPressureOne, i - 1 );
				// First button up
				SimulatePointer( TRawEvent::EButton1Up, outsidePoint_1.iX, outsidePoint_1.iY, nominalProximityOne, i - 1 );	
				
				// Second pointer down.
				SimulatePointer( TRawEvent::EButton1Down, insidePoint_2.iX, insidePoint_2.iY, nominalPressureTwo, i );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, reportedInsidePoint_2, nominalPressureTwo, i );
				// Second button move outside.
				SimulatePointer( TRawEvent::EPointerMove, outsidePoint_2.iX, outsidePoint_2.iY, nominalPressureTwo, i );	
				// Second button up
				SimulatePointer( TRawEvent::EButton1Up, outsidePoint_2.iX, outsidePoint_2.iY, nominalProximityTwo, i );
				}
						
			}
			break;

		case 1:
			{
			// Events outside the control should be reported to the control.
			
			// Pointer down, drag outside control, pointer up. Next pointer down...
			INFO_PRINTF1( _L("MultiPointerGrabL case 1") );
			RDebug::Print( _L("MultiPointerGrabL case 1") );
			
			TPoint decPoint( KMultiPtrTestCoOrdinateDecrement, KMultiPtrTestCoOrdinateDecrement );
			TPoint incPoint( KMultiPtrTestCoOrdinateIncrement, KMultiPtrTestCoOrdinateIncrement );
			
			TPoint outsidePoint_1( iControl->Position() );
			outsidePoint_1 -= decPoint;
			TPoint reportedOutsidePoint_1( outsidePoint_1 );
			reportedOutsidePoint_1 -= iControl->Position(); // Compensate for the reported position within the control.
			
			TPoint outsidePoint_2( outsidePoint_1 );
			outsidePoint_2 -= decPoint;
			TPoint reportedOutsidePoint_2( outsidePoint_2 );
			reportedOutsidePoint_2 -= iControl->Position(); // Compensate for the reported position within the control.
			
			TPoint insidePoint_1( iControl->Position() );
			insidePoint_1 += incPoint; // Place the co-ordinates within the control.
			TPoint reportedInsidePoint_1( insidePoint_1 );
			reportedInsidePoint_1 -= iControl->Position(); // Compensate for the reported position within the control.
			
			TPoint insidePoint_2( insidePoint_1 );
			insidePoint_2 += incPoint; // differentiate from insidePoint_1.
			TPoint reportedInsidePoint_2( insidePoint_2 );
			reportedInsidePoint_2 -= iControl->Position(); // Compensate for the reported position within the control.
			
			const TInt nominalPressureOne = iPressureNominal;
			const TInt nominalPressureTwo = iPressureNominal + iPressureStep;
			const TInt nominalProximityOne = iProximityNominal;
			const TInt nominalProximityTwo = iProximityNominal + iProximityStep;
			
			iControl->SetGrabs();
			iControl->SetDrags();
			TInt i = 1;
			
			for(; i < iNumberOfPointers; i++ )
				{
				// First pointer down.
				SimulatePointer( TRawEvent::EButton1Down, insidePoint_1.iX, insidePoint_1.iY, nominalPressureOne, i - 1 );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, reportedInsidePoint_1, nominalPressureOne, i - 1 );
				// First button move outside.
				SimulatePointer( TRawEvent::EPointerMove, outsidePoint_1.iX, outsidePoint_1.iY, nominalPressureOne, i - 1 );
				AddExpectedPointer( TAdvancedPointerEvent::EDrag, reportedOutsidePoint_1, nominalPressureOne, i - 1 );
				// First button up
				SimulatePointer( TRawEvent::EButton1Up, outsidePoint_1.iX, outsidePoint_1.iY, nominalProximityOne, i - 1 );	
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, reportedOutsidePoint_1, nominalProximityOne, i - 1 );
				
				// Second pointer down.
				SimulatePointer( TRawEvent::EButton1Down, insidePoint_2.iX, insidePoint_2.iY, nominalPressureTwo, i );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, reportedInsidePoint_2, nominalPressureTwo, i );
				// Second button move outside.
				SimulatePointer( TRawEvent::EPointerMove, outsidePoint_2.iX, outsidePoint_2.iY, nominalPressureTwo, i );	
				AddExpectedPointer( TAdvancedPointerEvent::EDrag, reportedOutsidePoint_2, nominalPressureTwo, i );
				// Second button up
				SimulatePointer( TRawEvent::EButton1Up, outsidePoint_2.iX, outsidePoint_2.iY, nominalProximityTwo, i );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, reportedOutsidePoint_2, nominalProximityTwo, i );	
				}
						
			}
			break;

		case 2:
			{
			// Events outside the control should be reported to the control. Interdigitate the events to ensure
			// that the pointer numbers are discriminated correctly
			
			// Ptr dn, next ptr dn, 1st ptr drag outside , next ptr drag outside, 1st ptr up, next ptr up			
			INFO_PRINTF1( _L("MultiPointerGrabL case 2") );
			RDebug::Print( _L("MultiPointerGrabL case 2") );
			
			TPoint decPoint( KMultiPtrTestCoOrdinateDecrement, KMultiPtrTestCoOrdinateDecrement );
			TPoint incPoint( KMultiPtrTestCoOrdinateIncrement, KMultiPtrTestCoOrdinateIncrement );
			
			TPoint outsidePoint_1( iControl->Position() );
			outsidePoint_1 -= decPoint;
			TPoint reportedOutsidePoint_1( outsidePoint_1 );
			reportedOutsidePoint_1 -= iControl->Position(); // Compensate for the reported position within the control.
			
			TPoint outsidePoint_2( outsidePoint_1 );
			outsidePoint_2 -= decPoint;
			TPoint reportedOutsidePoint_2( outsidePoint_2 );
			reportedOutsidePoint_2 -= iControl->Position(); // Compensate for the reported position within the control.
			
			TPoint insidePoint_1( iControl->Position() );
			insidePoint_1 += incPoint; // Place the co-ordinates within the control.
			TPoint reportedInsidePoint_1( insidePoint_1 );
			reportedInsidePoint_1 -= iControl->Position(); // Compensate for the reported position within the control.
			
			TPoint insidePoint_2( insidePoint_1 );
			insidePoint_2 += incPoint; // differentiate from insidePoint_1.
			TPoint reportedInsidePoint_2( insidePoint_2 );
			reportedInsidePoint_2 -= iControl->Position(); // Compensate for the reported position within the control.
		
			const TInt nominalPressureOne = iPressureNominal;
			const TInt nominalPressureTwo = iPressureNominal + iPressureStep;
			const TInt nominalProximityOne = iProximityNominal;
			const TInt nominalProximityTwo = iProximityNominal + iProximityStep;
			
			iControl->SetGrabs();
			iControl->SetDrags();
			TInt i = 1;
			
			for(; i < iNumberOfPointers; i++ )
				{
				// First pointer down.
				SimulatePointer( TRawEvent::EButton1Down, insidePoint_1.iX, insidePoint_1.iY, nominalPressureOne, i - 1 );
				// Second pointer down.
				SimulatePointer( TRawEvent::EButton1Down, insidePoint_2.iX, insidePoint_2.iY, nominalPressureTwo, i );
				// First button move outside.
				SimulatePointer( TRawEvent::EPointerMove, outsidePoint_1.iX, outsidePoint_1.iY, nominalPressureOne, i - 1 );
				// Second button move outside.
				SimulatePointer( TRawEvent::EPointerMove, outsidePoint_2.iX, outsidePoint_2.iY, nominalPressureTwo, i );			
				// First button up
				SimulatePointer( TRawEvent::EButton1Up, outsidePoint_1.iX, outsidePoint_1.iY, nominalProximityOne, i - 1 );	
				// Second button up
				SimulatePointer( TRawEvent::EButton1Up, outsidePoint_2.iX, outsidePoint_2.iY, nominalProximityTwo, i );
				
				// The corresponding anticipated events.
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, reportedInsidePoint_1, nominalPressureOne, i - 1 );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, reportedInsidePoint_2, nominalPressureTwo, i );
				
				AddExpectedPointer( TAdvancedPointerEvent::EDrag, reportedOutsidePoint_1, nominalPressureOne, i - 1 );
				AddExpectedPointer( TAdvancedPointerEvent::EDrag, reportedOutsidePoint_2, nominalPressureTwo, i );
				
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, reportedOutsidePoint_1, nominalProximityOne, i - 1 );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, reportedOutsidePoint_2, nominalProximityTwo, i );				
				}
						
			}
			break;
		default:
			{
			INFO_PRINTF1( _L("MultiPointerGrabL STOP\n") );
			RDebug::Print( _L("MultiPointerGrabL STOP") );
			RDebug::Print( _L("") );
			
			CActiveScheduler::Stop();
			iEventSet = 0;
			}
			break;
			
		}	
	
	}


// Stops the active scheduler and sets the flag to ETrue
void CConeMultiPtrTestAppUi::Failed()
	{
	CActiveScheduler::Stop();
	iFailed=ETrue;
	}


/**
 CTestStep derived class. It creates the control environment and App Ui class objects
*/
 void CTConeMultiPtrStep::ConstructConeMultiPtrAppL(CCoeEnv* aCoe)
 	{ // runs inside a TRAP harness
 	aCoe->ConstructL();
 	CConeMultiPtrTestAppUi* appUi=new(ELeave) CConeMultiPtrTestAppUi(this);
 	aCoe->SetAppUi(appUi);
 	aCoe->WsSession().SetDoubleClick(1000000,4);
 	appUi->ConstructL();
 	}
 
 
 CTConeMultiPtrStep::CTConeMultiPtrStep()
	 {
	 SetTestStepName(KTConeMultiPtrStep);
	 }
 
 
 CTConeMultiPtrStep::~CTConeMultiPtrStep()
	 {
	 
	 }


/**
Testexecute loads testserver and creates CTConeMultiPtrStep object and calls 
this function for each step in script file.
*/
TVerdict CTConeMultiPtrStep::doTestStepL()
	{
	INFO_PRINTF1(_L("Test Started"));

	// Need to check if wserv is NGA or Non-NGA
	// If NGA continue or else just return
	RWsSession wsSession;
	User::LeaveIfError(wsSession.Connect());
	if (wsSession.PreferredSurfaceConfigurationSize() == KErrNotSupported)
		{
		wsSession.Close();
		INFO_PRINTF1(_L("Tests should run only on NGA configuration. \n"));
		SetTestStepResult(EPass);
		return TestStepResult();
		}
	wsSession.Close();

	// Here check if the HAL configuration are correct if not then finish the test case
	TInt maxPtr=-1;
	TInt ret = HAL::Get(HALData::EPointerMaxPointers, maxPtr);
	if (ret != KErrNone || maxPtr < 2 || maxPtr > 8)
		{
		INFO_PRINTF2(_L("Incorrect HAL configuration (MaxPointers=%d). \n"),maxPtr);
		SetTestStepResult(EFail);
		return TestStepResult();
		}

	PreallocateHALBuffer();

	__UHEAP_MARK;

	CCoeEnv* coe = new(ELeave) CCoeEnv;
	TRAPD(err, ConstructConeMultiPtrAppL(coe));
	
	if (!err)
		{
		coe->ExecuteD();
		}
	else
		{
		INFO_PRINTF1(_L("Failed to contruct ControlEnvironment"));
		SetTestStepResult(EFail);
		if (coe)
			coe->DestroyEnvironment();
		}
	REComSession::FinalClose();

	__UHEAP_MARKEND;

	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}


TVerdict CTConeMultiPtrStep::doTestStepPreambleL()
	{
	// Remember the double-click settings.
	// Tests (may) adjust these values.
	RWsSession wsSession;
	User::LeaveIfError( wsSession.Connect() );

	wsSession.GetDoubleClickSettings( iDoubleClickMaxInterval, iDoubleClickMaxDistance );
	wsSession.Close();	

	return CTestStep::doTestStepPreambleL();
	}
	
	
TVerdict CTConeMultiPtrStep::doTestStepPostambleL()
	{
	// Restore the original system-wide double-click settings.
	RWsSession wsSession;
	User::LeaveIfError( wsSession.Connect() );

	wsSession.SetDoubleClick( iDoubleClickMaxInterval, iDoubleClickMaxDistance);
	wsSession.Close();
	
	return CTestStep::doTestStepPostambleL();
	}
