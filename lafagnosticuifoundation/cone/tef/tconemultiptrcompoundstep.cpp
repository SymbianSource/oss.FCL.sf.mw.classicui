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

#include "tconemultiptrcompoundstep.h"
#include "tmultiptrtestcompoundcontrolcontainer.h"
#include "tconemultiptrconst.h"
#include <hal.h>

/*
 Layout of the compound control/s. 
 The window-owning container control has two overlapping child controls.
 Co-ordinates are wrt the screen origin. Parenthesised co-ordinates are wrt the container.
-------------------------------------------------------------------------------------------
|          Small simple-control 280,0|     |                                              |
|    40,40                           |     |320,40 360,40                                 |
|    ----------------------------------- ---       -----------------------------------    |
|    |    (20,20) 60,60                 |          |    (20,20) 380,60                |   |
|    |    -----------------             |          |    -----------------             |   |
|    |    |                |            |          |    |                |            |   |
|    |    |                             |          |    |                             |   |
|    |    |         (80,60) 120,100     |          |    |    (80,60) 420,100          |   |
|    |    |         ----------------    |          |    |         ----------------    |   |
|    |    |         |              |    |          |    |         |              |    |   |
|    |    |         | Child 2      |    |          |    |         | Child 2      |    |   |
|    |    |         ----------------    |          |    |         ----------------    |   |
|    |    | Child 1        |  200,120   |          |    | Child 1        |  540,120   |   |
|    |    |----------------             |          |    |----------------             |   |
|    | Container        (120,120)       |          | Container        (120,120)       |   |
|    |----------------------------------           |----------------------------------    |
|                                  300,200                                                |
|                                                                                         |
|                                                                                         |
|                                                                                         |
-------------------------------------------------------------------------------------------
*/





// Global function for panic
void ConeTestCompoundPanic(TConeTestPanic aPanic)
	{
	User::Panic(_L("MultiPtrCmpnd"),aPanic);
	}


/**
 CTestStep derived class which implements RunTestStepL. It creates CoeEnv & AppUi objects.
 Logic involved, RunTestStepL will call RunTestsL() which will create new control/s for each
 test case and calls NextSetOfEventsL() which does testing of all different use cases 
 i,e by simulating the events and adding the events to a buffer. 
 Then RunTestStepL() starts the active scheduler, which will result in a call to
 control's HandlePointerEventL, which will test expected event in buffer with actual event.
*/
CConeMultiPtrCompoundTestAppUi::CConeMultiPtrCompoundTestAppUi(CTmsTestStep* aStep) : 
	CTestCoeAppUi(aStep)
	{
	}


void CConeMultiPtrCompoundTestAppUi::ConstructL()
	{
	iNormalPointerCursorArea = iCoeEnv->WsSession().PointerCursorArea();
	RDebug::Print( _L(">CConeMultiPtrComppoundTestAppUi::ConstructL") );
	CTestCoeAppUi::ConstructL();

	User::LeaveIfError( HAL::Get(HALData::EPointerNumberOfPointers, iNumberOfPointers) );
	if( KErrNone != iCoeEnv->WsSession().SetCloseProximityThresholds(KControlTestEnterCloseProximityThreshold, KControlTestExitCloseProximityThreshold) ||
	    KErrNone != iCoeEnv->WsSession().SetHighPressureThresholds(KControlTestEnterHighPressureThreshold, KControlTestExitHighPressureThreshold) )
		{
		User::Leave( KErrCorrupt );
		}
	if( KControlTestEnterCloseProximityThreshold != iCoeEnv->WsSession().GetEnterCloseProximityThreshold() ||
	    KControlTestExitCloseProximityThreshold != iCoeEnv->WsSession().GetExitCloseProximityThreshold() ||
	    KControlTestEnterHighPressureThreshold != iCoeEnv->WsSession().GetEnterHighPressureThreshold() ||
	    KControlTestExitHighPressureThreshold != iCoeEnv->WsSession().GetExitHighPressureThreshold() )
		{
		User::Leave( KErrCorrupt );
		}

	AutoTestManager().StartAutoTest();
	
	RDebug::Print( _L("CConeMultiPtrComppoundTestAppUi::ConstructL>") );
	}


CConeMultiPtrCompoundTestAppUi::~CConeMultiPtrCompoundTestAppUi()
	{
	DeleteControlClusterOne();
	DeleteControlClusterTwo();
	}


// Function called for each new test case from CTestManager active object.
void CConeMultiPtrCompoundTestAppUi::RunTestStepL( TInt )
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
		case 6:
		case 8:
			RunTestsSingleClusterL();
			break;
			
		case 5:
		case 7:
			RunTestsClusterPlusSimpleL();
			break;
			
		default:
			RDebug::Print( _L("End of test cases") );
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

TBool CConeMultiPtrCompoundTestAppUi::ConfigurationSupportsPointerEventTesting() const
    {
    if (iNormalPointerCursorArea.IsEmpty())
        {
        return EFalse;
        }
    return ETrue;
    }

/**
 Function called for each new test case from RunTestStepL.
 This creates control/s calls NextSetOfEventsL and starts activescheduler.
 */
void CConeMultiPtrCompoundTestAppUi::RunTestsSingleClusterL()
	{
	iEventSet = 0;

	// Instantiate afresh for each test-case.
	InstantiateControlClusterOneL();
	
    iEventCount = 0;
	TRAPD(err, NextSetOfEventsL());
	if (err != KErrNone)
		{
		INFO_PRINTF1( _L("ERROR INFO LOGGED IN epocwind.out") );
		
		iFailed = ETrue;
		return;
		}
	// Start nested active scheduler
	CActiveScheduler::Start();

	
	if ( (iControlCluster_1->iChildTwo->EventsLeft() > 0) || (iControlCluster_1->iChildOne->EventsLeft() > 0) )
		{
		INFO_PRINTF1( _L("ERROR INFO LOGGED IN epocwind.out") );
		
		iFailed=ETrue;
		}

	DeleteControlClusterOne();
	}


void CConeMultiPtrCompoundTestAppUi::RunTestsDualClusterL()
	{
	iEventSet = 0;

	// Instantiate afresh for each test-case.
	InstantiateControlClusterOneL();
	InstantiateControlClusterTwoL();
	
    iEventCount = 0;
	TRAPD(err, NextSetOfEventsL());
	if (err != KErrNone)
		{
		INFO_PRINTF1( _L("ERROR INFO LOGGED IN epocwind.out") );
		
		iFailed = ETrue;
		return;
		}
	// Start nested active scheduler
	CActiveScheduler::Start();

	
	if ( (iControlCluster_1->iChildTwo->EventsLeft() > 0) || (iControlCluster_1->iChildOne->EventsLeft() > 0) )
		{
		INFO_PRINTF1( _L("ERROR INFO LOGGED IN epocwind.out") );
		
		iFailed=ETrue;
		}
	
	DeleteControlClusterTwo();
	DeleteControlClusterOne();	
	}


void CConeMultiPtrCompoundTestAppUi::RunTestsClusterPlusSimpleL()
	{
	iEventSet = 0;

	// Instantiate afresh for each test-case.
	InstantiateControlClusterOneL();
	iControlSimple = CMultiPtrTestCompoundAppUiControl::NewL( KMultPtrSmallSimplePosition, KMultPtrSmallSimpleSize );
	
    iEventCount = 0;
	TRAPD(err, NextSetOfEventsL());
	if (err != KErrNone)
		{
		INFO_PRINTF1( _L("ERRORS LOGGED IN epocwind.out") );
		
		iFailed = ETrue;
		return;
		}
	// Start nested active scheduler
	CActiveScheduler::Start();

	
	if ( (iControlCluster_1->iChildTwo->EventsLeft() > 0) || (iControlCluster_1->iChildOne->EventsLeft() > 0) )
		{
		INFO_PRINTF1( _L("ERROR INFO LOGGED IN epocwind.out") );
		
		iFailed=ETrue;
		}
	
	delete iControlSimple;
	iControlSimple = NULL;
	DeleteControlClusterOne();	
	}


void CConeMultiPtrCompoundTestAppUi::RunTestsSimpleL()
	{
	iEventSet = 0;

	// Instantiate afresh for each test-case.
	iControlSimple = CMultiPtrTestCompoundAppUiControl::NewL( KMultPtrSmallSimplePosition, KMultPtrSmallSimpleSize );
	
    iEventCount = 0;
	TRAPD(err, NextSetOfEventsL());
	if (err != KErrNone)
		{
		INFO_PRINTF1( _L("ERRORS LOGGED IN epocwind.out") );
		
		iFailed = ETrue;
		return;
		}
	// Start nested active scheduler
	CActiveScheduler::Start();

	
	if ( iControlSimple->EventsLeft() > 0 )
		{
		INFO_PRINTF1( _L("ERROR INFO LOGGED IN epocwind.out") );
		
		iFailed=ETrue;
		}
	
	delete iControlSimple;
	iControlSimple = NULL;
	}


void CConeMultiPtrCompoundTestAppUi::InstantiateControlClusterOneL()
	{
	iCoeEnv->WsSession().SetAutoFlush(ETrue);
	iControlCluster_1 = new(ELeave) CMultPtrTestCompoundControlContainer();
	CleanupStack::PushL( iControlCluster_1 );
	iControlCluster_1->ConstructL( KMultPtrTestContainerRect );
    AddToStackL( iControlCluster_1 );
    CleanupStack::Pop();
	}


void CConeMultiPtrCompoundTestAppUi::DeleteControlClusterOne()
	{
	if( iControlCluster_1 )
		{
		RemoveFromStack( iControlCluster_1 );
		delete iControlCluster_1;
		iControlCluster_1 = NULL;	
		}
	
	}


void CConeMultiPtrCompoundTestAppUi::InstantiateControlClusterTwoL()
	{
	iControlCluster_2 = new(ELeave) CMultPtrTestCompoundControlContainer();
	CleanupStack::PushL( iControlCluster_2 );
	iControlCluster_2->ConstructL( KMultPtrTestContainerRectTwo );
    AddToStackL( iControlCluster_2 );
    CleanupStack::Pop();
    
    iControlCluster_2->iChildOne->SetAppUiCallback( EFalse );
    iControlCluster_2->iChildTwo->SetAppUiCallback( EFalse );
	}


void CConeMultiPtrCompoundTestAppUi::DeleteControlClusterTwo()
	{
	if( iControlCluster_2 )
		{
		RemoveFromStack( iControlCluster_2 );
		delete iControlCluster_2;
		iControlCluster_2 = NULL;	
		}
	
	}


/**
 Simulates pointer event, by making use of UserSvr::AddEvent. Also takes a Z parameter.
*/
void CConeMultiPtrCompoundTestAppUi::SimulatePointer(TRawEvent::TType aType, TInt aX, TInt aY, TInt aZ, TUint8 aPointerNumber)
	{
	__ASSERT_DEBUG(ConfigurationSupportsPointerEventTesting(), ConeTestCompoundPanic(EConePanicNoDigitiser));
	TRawEvent rawEvent;

	rawEvent.Set(aType, aX, aY, aZ, aPointerNumber);
	UserSvr::AddEvent(rawEvent);
	}

void CConeMultiPtrCompoundTestAppUi::SimulatePointerDownUp(TInt aX, TInt aY, TInt aZ, TUint8 aPointerNumber)
	{
	SimulatePointer(TRawEvent::EButton1Down, aX, aY, aZ, aPointerNumber);
	SimulatePointer(TRawEvent::EButton1Up, aX, aY, aZ, aPointerNumber);
	}


void CConeMultiPtrCompoundTestAppUi::AddExpectedPointer( TAdvancedPointerEvent::TType aType, TPoint aPos, TInt aZ, TUint8 aPointerNumber, CMultiPtrTestControlBase* aControl )
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
    event.Pointer()->iParentPosition.SetXY( aControl->Position().iX, aControl->Position().iY );
    
	aControl->AddExpectedEvent( *event.Pointer() );
	}


void CConeMultiPtrCompoundTestAppUi::AddExpectedPointerDownUp( TPoint aPos, TInt aZ, TUint8 aPointerNumber, CMultiPtrTestControlBase* aControl )
	{
	// Pointer position is with respect to the window's Top Left position
	// Here we may want to write a function which will set sent position with respect to control/window 
	// on which we are simulating the events. 
	//aPos -= iControl->Position();
	AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, aPos, aZ, aPointerNumber, aControl );
	AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, aPos, aZ, aPointerNumber, aControl );
	}


/**
 once all the events for a given sub test are tested. So that next subtest case can proceed with it.
 */
void CConeMultiPtrCompoundTestAppUi::NextSetOfEventsL()
	{
	
	switch( iTestCase )
		{
	case 0:
		SetTestStepID(_L("UIF-WSERV-ADVANCEDPOINTER-0043"));
		PreliminaryStimuliL();
		RecordTestResultL();
		break;

 	case 1:
 		SetTestStepID(_L("UIF-WSERV-ADVANCEDPOINTER-0036"));
		SinglePtrProximityAndPressureL();
		RecordTestResultL();
		break;	
	
 	case 2:
 		SetTestStepID(_L("UIF-WSERV-ADVANCEDPOINTER-0037"));
 		MultiplePtrProximityAndPressureL();
		RecordTestResultL();
 		break;
 		
 	case 3:
 		SetTestStepID(_L("UIF-WSERV-ADVANCEDPOINTER-0043"));
 		PointerGrabbingL();
		RecordTestResultL();
 		break;

	case 4:
		SetTestStepID(_L("UIF-WSERV-ADVANCEDPOINTER-0038"));
		ClaimPointerGrabbingL();
		RecordTestResultL();
		break;
	
	case 5:
		SetTestStepID(_L("UIF-WSERV-ADVANCEDPOINTER-0039"));
		ClaimPointerGrabbingTwoWindowsL();
		RecordTestResultL();
		break;

	case 6:
		SetTestStepID(_L("UIF-WSERV-ADVANCEDPOINTER-0040"));
		CapturePointerNotDeliveredToChildL();
		RecordTestResultL();
		break;
	
	case 7:
		SetTestStepID(_L("UIF-WSERV-ADVANCEDPOINTER-0044"));
		CapturePointerCycleL();
		RecordTestResultL();
		break;

	case 8:
		SetTestStepID(_L("UIF-WSERV-ADVANCEDPOINTER-0042"));
		CycleToOutOfRangeL();
		RecordTestResultL();
		CloseTMSGraphicsStep();
		break;

	default:
		{
		ConeTestCompoundPanic( EConeTestPanicWrongTest );
		}
		break;
		
		}
	
	}


/**
@SYMTestCaseID 			UIF-WSERV-ADVANCEDPOINTER-0043
@SYMPREQ 				PREQ1226
@SYMTestType			UT
@SYMTestPriority		Critical
@SYMTestStatus 			Implemented
@SYMTestCaseDesc		Compound control, preliminary stimuli.
@SYMTestActions			Instantiate the compound test-control. Perform pointer-down, pointer-up, pointer-exit-close-proximity events for each pointer in turn on one of the control’s children.
						cf GRAPHICS-WSERV-ADVANCEDPOINTER-0002

@SYMTestExpectedResults  The received events should match the simulated raw events.
*/
void CConeMultiPtrCompoundTestAppUi::PreliminaryStimuliL()
	{
	INFO_PRINTF1( _L(">PreliminaryStimuli") );
	RDebug::Print( _L(">PreliminaryStimuli") );
	
	if( iNumberOfPointers <= 1 )
		{
		User::Leave( KErrNotSupported );
		}
	
	switch( iEventSet++ )
		{
		case 0:
			{
			INFO_PRINTF1( _L("PreliminaryStimuli case 0") );
	
			TPoint ptrPos( 140, 120 );
			TInt z = KControlTestLessThanHighPressure;
			TInt pointerNumber = 0;
			
			for(; pointerNumber < iNumberOfPointers; pointerNumber++ )
				{
				SimulatePointerDownUp( ptrPos.iX, ptrPos.iY, z, pointerNumber );
				AddExpectedPointerDownUp( (ptrPos - iControlCluster_1->PositionRelativeToScreen()), z, pointerNumber, iControlCluster_1->iChildTwo );
				
				// Do this in order that the pointer states are neutral for the test/s that follow.
				SimulatePointer( TRawEvent::EPointerMove, ptrPos.iX, ptrPos.iY, KControlTestExitCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EExitCloseProximity, (ptrPos - iControlCluster_1->PositionRelativeToScreen()), KControlTestExitCloseProximity, pointerNumber, iControlCluster_1->iChildTwo );

				ptrPos.iX += KMultiPtrTestCoOrdinateIncrementSmall;
				ptrPos.iY += KMultiPtrTestCoOrdinateIncrementSmall;
				}

			}
			break;
			
		default:
			{
			CActiveScheduler::Stop();
			iEventSet = 0;
			INFO_PRINTF1( _L("PreliminaryStimuli STOP\n") );
			RDebug::Print( _L("PreliminaryStimuli STOP") );
			RDebug::Print( _L("") );
			}
			break;
		}
	
	}


/**
@SYMTestCaseID 			UIF-WSERV-ADVANCEDPOINTER-0036
@SYMPREQ 				PREQ1226
@SYMTestType			UT
@SYMTestPriority		Critical
@SYMTestStatus 			Implemented
@SYMTestCaseDesc		Single pointer proximity and pressure events in Cone.
@SYMTestActions			
@SYMTestExpectedResults  The received events should match the simulated raw events.

Note: The events generated by this test are quite numerous and so they are partitioned in order 
	  to avoid exceeding the capacity of the window-server-side buffers. 
*/
void CConeMultiPtrCompoundTestAppUi::SinglePtrProximityAndPressureL()
	{
	INFO_PRINTF1( _L(">SinglePtrProximityAndPressureL") );
	RDebug::Print( _L(">SinglePtrProximityAndPressureL") );
	
	if( iNumberOfPointers <= 1 )
		{
		User::Leave( KErrNotSupported );
		}
	
	TInt pointerNumber = 0;
	const TInt KIntermediatePointerNumber = iNumberOfPointers / 2; 
	const TInt KContainer_1_Child_2_X = 140;
	const TInt KContainer_1_Child_2_Y = 120;
	TPoint point( KContainer_1_Child_2_X, KContainer_1_Child_2_Y );
	TPoint incPoint( KMultiPtrTestCoOrdinateIncrementSmall, KMultiPtrTestCoOrdinateIncrementSmall );
	TPoint parentPosition( iControlCluster_1->Position() );
	TPoint expectedPoint( point - parentPosition );
	CMultiPtrTestControlBase* expectedControl = iControlCluster_1->iChildTwo;
	iControlCluster_1->iChildTwo->SetDrags();

	
	switch( iEventSet++ )
		{
		case 0:
			{	
			INFO_PRINTF1( _L("SinglePtrProximityAndPressureL case 0") );
			RDebug::Print( _L("SinglePtrProximityAndPressureL case 0") );

			for(; pointerNumber < KIntermediatePointerNumber; pointerNumber++ )
				{
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestExitCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EMove, expectedPoint, KControlTestExitCloseProximity, pointerNumber, expectedControl );	
				// Should be reported as EEnterCloseProximity
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestEnterCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EEnterCloseProximity, expectedPoint, KControlTestEnterCloseProximity, pointerNumber, expectedControl );
				// EButton1Down (Not High pressure)
				SimulatePointer( TRawEvent::EButton1Down, point.iX, point.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, expectedPoint, KControlTestLessThanHighPressure, pointerNumber, expectedControl );
				// EEnterHighPressure
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestEnterHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EEnterHighPressure, expectedPoint, KControlTestEnterHighPressure, pointerNumber, expectedControl );
				// EExitHighPressure
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EExitHighPressure, expectedPoint, KControlTestLessThanHighPressure, pointerNumber, expectedControl );
				// EButton1up
				SimulatePointer( TRawEvent::EButton1Up, point.iX, point.iY, KControlTestEnterCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, expectedPoint, KControlTestEnterCloseProximity, pointerNumber, expectedControl );
				// EExitCloseProximity
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestExitCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EExitCloseProximity, expectedPoint, KControlTestExitCloseProximity, pointerNumber, expectedControl );
				
				// Discriminate each pointer's event-sequence by position.
				point += incPoint;
				expectedPoint += incPoint;
				}
			
			}
			break;

		case 1:
			{	
			INFO_PRINTF1( _L("SinglePtrProximityAndPressureL case 1") );
			RDebug::Print( _L("SinglePtrProximityAndPressureL case 1") );
			
			pointerNumber = KIntermediatePointerNumber;
			
			for(; pointerNumber < iNumberOfPointers; pointerNumber++ )
				{
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestExitCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EMove, expectedPoint, KControlTestExitCloseProximity, pointerNumber, expectedControl );	
				// Should be reported as EEnterCloseProximity
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestEnterCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EEnterCloseProximity, expectedPoint, KControlTestEnterCloseProximity, pointerNumber, expectedControl );
				// EButton1Down (Not High pressure)
				SimulatePointer( TRawEvent::EButton1Down, point.iX, point.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, expectedPoint, KControlTestLessThanHighPressure, pointerNumber, expectedControl );
				// EEnterHighPressure
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestEnterHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EEnterHighPressure, expectedPoint, KControlTestEnterHighPressure, pointerNumber, expectedControl );
				// EExitHighPressure
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EExitHighPressure, expectedPoint, KControlTestLessThanHighPressure, pointerNumber, expectedControl );
				// EButton1up
				SimulatePointer( TRawEvent::EButton1Up, point.iX, point.iY, KControlTestEnterCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, expectedPoint, KControlTestEnterCloseProximity, pointerNumber, expectedControl );
				// EExitCloseProximity
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestExitCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EExitCloseProximity, expectedPoint, KControlTestExitCloseProximity, pointerNumber, expectedControl );
				
				// Discriminate each pointer's event-sequence by position.
				point += incPoint;
				expectedPoint += incPoint;
				}
			
			}
			break;

		default:
			{
			CActiveScheduler::Stop();
			iEventSet = 0;
			
			INFO_PRINTF1( _L("SinglePtrProximityAndPressureL STOP\n") );
			INFO_PRINTF1( _L("") );
			RDebug::Print( _L("SinglePtrProximityAndPressureL STOP") );
			RDebug::Print( _L("") );
			}
			break;
			
		}	
	
	}



/**
@SYMTestCaseID 			UIF-WSERV-ADVANCEDPOINTER-0037
@SYMPREQ 				PREQ1226
@SYMTestType			UT
@SYMTestPriority		Critical
@SYMTestStatus 			Implemented
@SYMTestCaseDesc		Multiple (interdigitated) pointer proximity and pressure events in cone.
@SYMTestActions			
@SYMTestExpectedResults  The received events should match the simulated raw events.
*/
void CConeMultiPtrCompoundTestAppUi::MultiplePtrProximityAndPressureL()
	{
	INFO_PRINTF1( _L(">MultiplePtrProximityAndPressureL") );
	RDebug::Print( _L(">MultiplePtrProximityAndPressureL") );

	if( iNumberOfPointers <= 1 )
		{
		User::Leave( KErrNotSupported );
		}
	
	TInt pointerNumber = 0;
	const TInt KContainer_1_Child_2_X = 140;
	const TInt KContainer_1_Child_2_Y = 120;
	TPoint point( KContainer_1_Child_2_X, KContainer_1_Child_2_Y );
	TPoint incPoint( KMultiPtrTestCoOrdinateIncrementSmall, KMultiPtrTestCoOrdinateIncrementSmall );
	TPoint parentPosition( iControlCluster_1->Position() );
	TPoint expectedPoint( point - parentPosition );
	CMultiPtrTestControlBase* expectedControl = iControlCluster_1->iChildTwo;
	iControlCluster_1->iChildTwo->SetDrags();


	switch( iEventSet++ )
		{	
		case 0:
			{
			INFO_PRINTF1( _L("MultiplePtrProximityAndPressureL case 0") );
			RDebug::Print( _L("MultiplePtrProximityAndPressureL case 0") );
			
			for(; pointerNumber < iNumberOfPointers; pointerNumber++ )
				{
				// Should be reported as EMove
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestExitCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EMove, expectedPoint, KControlTestExitCloseProximity, pointerNumber, expectedControl );
			
				// Discriminate each pointer's event-sequence by position.
				point += incPoint;
				expectedPoint += incPoint;
				}
			
			}
			break;
		
		case 1:
			{
			INFO_PRINTF1( _L("MultiplePtrProximityAndPressureL case 1") );
			RDebug::Print( _L("MultiplePtrProximityAndPressureL case 1") );
			
			for(; pointerNumber < iNumberOfPointers; pointerNumber++ )
				{
				// Should be reported as EEnterCloseProximity
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestEnterCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EEnterCloseProximity, expectedPoint, KControlTestEnterCloseProximity, pointerNumber, expectedControl );
				
				// Discriminate each pointer's event-sequence by position.
				point += incPoint;
				expectedPoint += incPoint;
				}
			
			}
			break;
		
		case 2:
			{
			INFO_PRINTF1( _L("MultiplePtrProximityAndPressureL case 2") );
			RDebug::Print( _L("MultiplePtrProximityAndPressureL case 2") );
			
			for(; pointerNumber < iNumberOfPointers; pointerNumber++ )
				{
				// EButton1Down (Not High pressure)
				SimulatePointer( TRawEvent::EButton1Down, point.iX, point.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, expectedPoint, KControlTestLessThanHighPressure, pointerNumber, expectedControl );
				
				// Discriminate each pointer's event-sequence by position.
				point += incPoint;
				expectedPoint += incPoint;
				}
			
			}
			break;		
		
		
		case 3:
			{
			INFO_PRINTF1( _L("MultiplePtrProximityAndPressureL case 3") );
			RDebug::Print( _L("MultiplePtrProximityAndPressureL case 3") );
			
			for(; pointerNumber < iNumberOfPointers; pointerNumber++ )
				{
				// EEnterHighPressure
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestEnterHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EEnterHighPressure, expectedPoint, KControlTestEnterHighPressure, pointerNumber, expectedControl );
				
				// Discriminate each pointer's event-sequence by position.
				point += incPoint;
				expectedPoint += incPoint;
				}
			
			}
			break;		

		case 4:
			{
			INFO_PRINTF1( _L("MultiplePtrProximityAndPressureL case 4") );
			RDebug::Print( _L("MultiplePtrProximityAndPressureL case 4") );
			
			for(; pointerNumber < iNumberOfPointers; pointerNumber++ )
				{
				// EExitHighPressure
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EExitHighPressure, expectedPoint, KControlTestLessThanHighPressure, pointerNumber, expectedControl );
				
				// Discriminate each pointer's event-sequence by position.
				point += incPoint;
				expectedPoint += incPoint;
				}
			
			}
			break;	

		case 5:
			{
			INFO_PRINTF1( _L("MultiplePtrProximityAndPressureL case 5") );
			RDebug::Print( _L("MultiplePtrProximityAndPressureL case 5") );
			
			for(; pointerNumber < iNumberOfPointers; pointerNumber++ )
				{
				// EButton1up
				SimulatePointer( TRawEvent::EButton1Up, point.iX, point.iY, KControlTestEnterCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, expectedPoint, KControlTestEnterCloseProximity, pointerNumber, expectedControl );
	
				// Discriminate each pointer's event-sequence by position.
				point += incPoint;
				expectedPoint += incPoint;
				}
			
			}
			break;	
		
		case 6:
			{
			INFO_PRINTF1( _L("MultiplePtrProximityAndPressureL case 6") );
			RDebug::Print( _L("MultiplePtrProximityAndPressureL case 6") );
			
			for(; pointerNumber < iNumberOfPointers; pointerNumber++ )
				{
				// EExitCloseProximity
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestExitCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EExitCloseProximity, expectedPoint, KControlTestExitCloseProximity, pointerNumber, expectedControl );
				
				// Discriminate each pointer's event-sequence by position.
				point += incPoint;
				expectedPoint += incPoint;
				}
			
			}
			break;	
		
		default:
			{
			CActiveScheduler::Stop();
			iEventSet = 0;
			
			INFO_PRINTF1( _L("MultiplePtrProximityAndPressureL STOP\n") );
			INFO_PRINTF1( _L("") );
			RDebug::Print( _L("MultiplePtrProximityAndPressureL STOP") );
			RDebug::Print( _L("") );
			}
			break;
		
		}	

	}



/**
@SYMTestCaseID 			UIF-WSERV-ADVANCEDPOINTER-0038
@SYMPREQ 				PREQ1226
@SYMTestType			UT
@SYMTestPriority		Critical
@SYMTestStatus 			Implemented
@SYMTestCaseDesc		Grabbing in cone.
@SYMTestActions			Simulate Pointer-down, pointer-move (outside of control), pointer-up events for each individual pointer.
						Simulate interdigitated Pointer-down, pointer-move (outside of control), pointer-up events for each individual pointer.
						Additionally, in each case discriminate each pointer's events by co-ordinate for clarity.

@SYMTestExpectedResults  The grabbing control should receive the anticipated events.
*/
void CConeMultiPtrCompoundTestAppUi::PointerGrabbingL()
	{
	INFO_PRINTF1( _L(">PointerGrabbingL") );
	RDebug::Print( _L(">PointerGrabbingL") );
	
	if( iNumberOfPointers <= 1 )
		{
		User::Leave( KErrNotSupported );
		}
	
	TInt pointerNumber = 0;
	const TInt KContainer_1_Child_2_X = 140;
	const TInt KContainer_1_Child_2_Y = 120;
	
	TPoint incPoint( KMultiPtrTestCoOrdinateIncrementSmall, KMultiPtrTestCoOrdinateIncrementSmall );
	TPoint downPoint( KContainer_1_Child_2_X, KContainer_1_Child_2_Y );
	TPoint upPoint( KMultPtrTestCentreScreen );
	upPoint -= incPoint; // Move in from centre screen
	
	TPoint parentPosition( iControlCluster_1->Position() );
	TPoint expectedDownPoint( downPoint - parentPosition );
	TPoint expectedUpPoint( upPoint - parentPosition );
	
	CMultiPtrTestControlBase* expectedControl = iControlCluster_1->iChildTwo;
	iControlCluster_1->iChildTwo->SetDrags();
	iControlCluster_1->iChildTwo->SetGrabs();


	switch( iEventSet++ )
		{
		case 0:
			{	
			INFO_PRINTF1( _L("PointerGrabbingL case 0") );
			RDebug::Print( _L("PointerGrabbingL case 0") );
			// Simulate Pointer-down, pointer-move (outside of control), pointer-up events for each individual pointer in turn.
			
			for(; pointerNumber < iNumberOfPointers; pointerNumber++ )
				{
				SimulatePointer( TRawEvent::EButton1Down, downPoint.iX, downPoint.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, expectedDownPoint, KControlTestLessThanHighPressure, pointerNumber, expectedControl );
				
				SimulatePointer( TRawEvent::EPointerMove, upPoint.iX, upPoint.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EDrag, expectedUpPoint, KControlTestLessThanHighPressure, pointerNumber, expectedControl );

				SimulatePointer( TRawEvent::EButton1Up, upPoint.iX, upPoint.iY, KControlTestExitCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, expectedUpPoint, KControlTestExitCloseProximity, pointerNumber, expectedControl );

				// Discriminate each pointer's events by co-ordinate for clarity.
				downPoint += incPoint;
				expectedDownPoint += incPoint;
				upPoint -= incPoint; // Move inward from the centre/edge of the screen
				expectedUpPoint -= incPoint;
				}
			
			}
			break;

			// Cases 1,2 and 3 form the interdigitated down-move-up sequence.
		case 1:
			{	
			INFO_PRINTF1( _L("PointerGrabbingL case 1") );
			RDebug::Print( _L("PointerGrabbingL case 1") );

			for(; pointerNumber < iNumberOfPointers; pointerNumber++ )
				{
				SimulatePointer( TRawEvent::EButton1Down, downPoint.iX, downPoint.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, expectedDownPoint, KControlTestLessThanHighPressure, pointerNumber, expectedControl );
			
				downPoint += incPoint;
				expectedDownPoint += incPoint;
				}
			
			}
			break;	

		case 2:
			{	
			INFO_PRINTF1( _L("PointerGrabbingL case 2") );
			RDebug::Print( _L("PointerGrabbingL case 2") );
		
			for(; pointerNumber < iNumberOfPointers; pointerNumber++ )
				{
				SimulatePointer( TRawEvent::EPointerMove, upPoint.iX, upPoint.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EDrag, expectedUpPoint, KControlTestLessThanHighPressure, pointerNumber, expectedControl );

				upPoint -= incPoint; // Move inward from the centre/edge of the screen
				expectedUpPoint -= incPoint;
				}
			
			}
			break;	
			
		case 3:
			{	
			INFO_PRINTF1( _L("PointerGrabbingL case 3") );
			RDebug::Print( _L("PointerGrabbingL case 3") );
		
			for(; pointerNumber < iNumberOfPointers; pointerNumber++ )
				{
				SimulatePointer( TRawEvent::EButton1Up, upPoint.iX, upPoint.iY, KControlTestExitCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, expectedUpPoint, KControlTestExitCloseProximity, pointerNumber, expectedControl );

				upPoint -= incPoint; // Move inward from the centre/edge of the screen
				expectedUpPoint -= incPoint;
				}
			
			}
			break;

		default:
			{
			CActiveScheduler::Stop();
			iEventSet = 0;
			
			INFO_PRINTF1( _L("PointerGrabbingL STOP\n") );
			INFO_PRINTF1( _L("") );
			RDebug::Print( _L("PointerGrabbingL STOP") );
			RDebug::Print( _L("") );
			}
			break;
			
		}	
	
	}


/**
@SYMTestCaseID 			UIF-WSERV-ADVANCEDPOINTER-0039
@SYMPREQ 				PREQ1226
@SYMTestType			UT
@SYMTestPriority		Critical
@SYMTestStatus 			Implemented
@SYMTestCaseDesc		Claim grabbing in cone.
@SYMTestActions			

Phase 1
Set child 2 of the compound test control to be grabbing.
Simulate a pointer down event in child 2.
Ensure it is delivered to Child2

Set child 1 to claim the pointer grab using ClaimPointerGrab(TBool aSendUpEvent, TInt aPointerNumber )
Simulate a drag and a pointer-up event.
Ensure they are delivered to child 1

Repeat for the range of pointer numbers


Phase 2
Simulate a pointer down event in child 2.
Ensure it is delivered to Child2.

Set child 1 to claim the pointer grab using ClaimPointerGrab(TBool aSendUpEvent, TInt aPointerNumber ).
Simulate enter-high-pressure outside of the control.
Simulate a drag outside of the control.
Simulate exit high pressure outside of control.
Simulate pointer-up outside of control (within proximity ).
Ensure these events are delivered to child 1.

Simulate exit-close-proximity outside of the control 
Ensure it is not delivered.

Repeat for the range of pointer numbers.


@SYMTestExpectedResults  The anticipated events are delivered to the intended child controls.
*/
void CConeMultiPtrCompoundTestAppUi::ClaimPointerGrabbingL()
	{
	
	INFO_PRINTF1( _L(">ClaimPointerGrabbingL") );
	RDebug::Print( _L(">ClaimPointerGrabbingL") );
	
	if( iNumberOfPointers <= 1 )
		{
		User::Leave( KErrNotSupported );
		}
	
	TInt pointerNumber = 0;
	const TInt KContainer_1_Child_2_X = 140;
	const TInt KContainer_1_Child_2_Y = 120;
	
	TPoint incPoint( KMultiPtrTestCoOrdinateIncrementSmall, KMultiPtrTestCoOrdinateIncrementSmall );
	TPoint downPoint( KContainer_1_Child_2_X, KContainer_1_Child_2_Y );
	TPoint upPoint( KMultPtrTestCentreScreen );
	upPoint -= incPoint; // move in from the centre/edge of the screen
	TPoint parentPosition( iControlCluster_1->Position() );
	TPoint expectedDownPoint( downPoint - parentPosition );
	TPoint expectedUpPoint( upPoint - parentPosition );
	
	CMultiPtrTestControlBase* childTwoAsExpectedControl = iControlCluster_1->iChildTwo;
	CMultiPtrTestControlBase* childOneAsExpectedControl = iControlCluster_1->iChildOne;
	iControlCluster_1->iChildTwo->SetDrags();
	iControlCluster_1->iChildTwo->SetGrabs();


	switch( iEventSet++ )
		{
		case 0:
			{
			INFO_PRINTF1( _L("ClaimPointerGrabbingL case 0") );
			RDebug::Print( _L("ClaimPointerGrabbingL case 0") );
			
			for(; pointerNumber < iNumberOfPointers; pointerNumber++ )
				{
				// Down in Child2
				SimulatePointer( TRawEvent::EButton1Down, downPoint.iX, downPoint.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, expectedDownPoint, KControlTestLessThanHighPressure, pointerNumber, childTwoAsExpectedControl );	  
				// Grabbed by Child1
				iControlCluster_1->iChildOne->ClaimPointerGrab( pointerNumber, EFalse );
				// Drag-event reported in Child1
				SimulatePointer( TRawEvent::EPointerMove, upPoint.iX, upPoint.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EDrag, expectedUpPoint, KControlTestLessThanHighPressure, pointerNumber, childOneAsExpectedControl );				
				// Up-event reported in Child1
				SimulatePointer( TRawEvent::EButton1Up, upPoint.iX, upPoint.iY, KControlTestExitCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, expectedUpPoint, KControlTestExitCloseProximity, pointerNumber, childOneAsExpectedControl );

				downPoint += incPoint;
				expectedDownPoint += incPoint;
				
				if( (pointerNumber + 1) == iNumberOfPointers )
					{
					// This prevents Chilld2 precipitating the destruction of the control before Child1 has reported the last event/s.
					iControlCluster_1->iChildTwo->SetAppUiCallback( EFalse );
					}
				
				}

			}
			break;

		case 1:
			{
			INFO_PRINTF1( _L("ClaimPointerGrabbingL case 1") );
			RDebug::Print( _L("ClaimPointerGrabbingL case 1") );
			
			iControlCluster_1->iChildTwo->SetAppUiCallback( ETrue );
			
			for(; pointerNumber < iNumberOfPointers; pointerNumber++ )
			//for(; pointerNumber < 2; pointerNumber++ )
				{
				// Down in Child2
				SimulatePointer( TRawEvent::EButton1Down, downPoint.iX, downPoint.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, expectedDownPoint, KControlTestLessThanHighPressure, pointerNumber, childTwoAsExpectedControl );	  
				// Grabbed by Child1
				iControlCluster_1->iChildOne->ClaimPointerGrab( pointerNumber, EFalse );
				// Enter high presssure reported in Child1
				SimulatePointer( TRawEvent::EPointerMove, downPoint.iX, downPoint.iY, KControlTestEnterHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EEnterHighPressure, expectedDownPoint, KControlTestEnterHighPressure, pointerNumber, childOneAsExpectedControl );
				// Drag-event reported in Child1
				SimulatePointer( TRawEvent::EPointerMove, upPoint.iX, upPoint.iY, KControlTestEnterHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EDrag, expectedUpPoint, KControlTestEnterHighPressure, pointerNumber, childOneAsExpectedControl );
				// Exit high pressure reported in Child1
				SimulatePointer( TRawEvent::EPointerMove, upPoint.iX, upPoint.iY, KControlTestExitHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EExitHighPressure, expectedUpPoint, KControlTestExitHighPressure, pointerNumber, childOneAsExpectedControl );
				// up,  reported in Child1
				SimulatePointer( TRawEvent::EButton1Up, upPoint.iX, upPoint.iY, KControlTestEnterCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, expectedUpPoint, KControlTestEnterCloseProximity, pointerNumber, childOneAsExpectedControl );

				// exit close proximity. Outside both controls so not reported
				SimulatePointer( TRawEvent::EPointerMove, upPoint.iX, upPoint.iY, KControlTestExitCloseProximity, pointerNumber );
		
				downPoint += incPoint;
				expectedDownPoint += incPoint;
				
				if( (pointerNumber + 1) == iNumberOfPointers )
					{
					// This prevents Chilld2 precipitating the destruction of the control before Child1 has reported the last event/s.
					iControlCluster_1->iChildTwo->SetAppUiCallback( EFalse );
					}
				
				}

			}
			break;
	
		case 2:
			{
			INFO_PRINTF1( _L("ClaimPointerGrabbingL case 2") );
			RDebug::Print( _L("ClaimPointerGrabbingL case 2") );

			// Down in Child2
			SimulatePointer( TRawEvent::EButton1Down, downPoint.iX, downPoint.iY, KControlTestLessThanHighPressure, TAdvancedPointerEvent::EDefaultPointerNumber );
			AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, expectedDownPoint, KControlTestLessThanHighPressure, TAdvancedPointerEvent::EDefaultPointerNumber, childTwoAsExpectedControl );	  
			// Grabbed by Child1 (the original method)
			iControlCluster_1->iChildOne->ClaimPointerGrab( EFalse );
			// Drag-event reported in Child1
			SimulatePointer( TRawEvent::EPointerMove, upPoint.iX, upPoint.iY, KControlTestLessThanHighPressure, TAdvancedPointerEvent::EDefaultPointerNumber );
			AddExpectedPointer( TAdvancedPointerEvent::EDrag, expectedUpPoint, KControlTestLessThanHighPressure, TAdvancedPointerEvent::EDefaultPointerNumber, childOneAsExpectedControl );
			// Up-event reported in Child1
			SimulatePointer( TRawEvent::EButton1Up, upPoint.iX, upPoint.iY, KControlTestExitCloseProximity, TAdvancedPointerEvent::EDefaultPointerNumber );
			AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, expectedUpPoint, KControlTestExitCloseProximity, TAdvancedPointerEvent::EDefaultPointerNumber, childOneAsExpectedControl );

			// This prevents Chilld2 precipitating the destruction of the control before Child1 has reported the last event/s.
			iControlCluster_1->iChildTwo->SetAppUiCallback( EFalse );
			}
			break;
			
		default:
			{
			CActiveScheduler::Stop();
			iEventSet = 0;
	
			INFO_PRINTF1( _L("ClaimPointerGrabbingL STOP\n") );
			INFO_PRINTF1( _L("") );
			RDebug::Print( _L("ClaimPointerGrabbingL STOP") );
			RDebug::Print( _L("") );
			}
			break;
		
		}		
	}


/**
@SYMTestCaseID 			UIF-WSERV-ADVANCEDPOINTER-0039 Part 2
@SYMPREQ 				PREQ1226
@SYMTestType			UT
@SYMTestPriority		Critical
@SYMTestStatus 			Implemented
@SYMTestCaseDesc		Claim grabbing in cone.
@SYMTestActions			

Instantiate a compound test-control and a simple window-owning control

Phase 3
Simulate a pointer-down event on simple window-owning control.
This will not be reported

Set control 1, child 1 to claim the grab using ClaimPointerGrab(TBool aSendUpEvent, TInt aPointerNumber )

Simulate a drag outside of both controls.
Simulate a pointer-up event, within close proximity.
Ensure these events are delivered to Control 1, child 1.

Repeat for the range of supported pointers.

Phase 4
Set the simple window-owning control to be grabbing.
Simulate a pointer-down event on the simple control.

Set control 1, child 1 to claim the grab using ClaimPointerGrab(TBool aSendUpEvent, TInt aPointerNumber )

Simulate a drag outside of both controls.
Simulate an Enter-high-pressure event  outside of both controls.
Simulate an exit-high-pressure event outside of both controls.
Simulate a pointer-up event, within close proximity.
Ensure these are delivered to Control1, child1

Simulate an exit-close-proximity event outside both controls. This should not be delivered.

Repeat for the range of pointer numbers.


@SYMTestExpectedResults  The anticipated events are delivered to the expected controls.
*/
void CConeMultiPtrCompoundTestAppUi::ClaimPointerGrabbingTwoWindowsL()
	{
	
	INFO_PRINTF1( _L(">ClaimPointerGrabbingTwoWindowsL") );
	RDebug::Print( _L(">ClaimPointerGrabbingTwoWindowsL") );
	
	if( iNumberOfPointers <= 1 )
		{
		User::Leave( KErrNotSupported );
		}
	
	TInt pointerNumber = 0;
	
	const TInt KControlSimplePoint_X = KMultPtrSmallSimplePosition.iX + 5;
	const TInt KControlSimplePoint_Y = KMultPtrSmallSimplePosition.iY + 5;
	
	TPoint incPoint( KMultiPtrTestCoOrdinateIncrementSmall, KMultiPtrTestCoOrdinateIncrementSmall );
	TPoint downPoint( KControlSimplePoint_X, KControlSimplePoint_Y );
	TPoint upPoint( KMultPtrTestCentreScreen );
	upPoint -= incPoint; // Move in from the centre/edge of the screen.
	TPoint parentPosition( iControlCluster_1->Position() );
	TPoint expectedUpPoint( upPoint - parentPosition );
	
	CMultiPtrTestControlBase* childOneAsExpectedControl = iControlCluster_1->iChildOne;
	iControlCluster_1->iChildTwo->SetDrags();
	iControlCluster_1->iChildTwo->SetGrabs();
	
	iControlSimple->SetDrags();
	iControlSimple->SetGrabs();
	iControlSimple->SetPassive();
	
	switch( iEventSet++ )
		{
		case 0:
			{
			INFO_PRINTF1( _L("ClaimPointerGrabbingTwoWindowsL case 0") );
			RDebug::Print( _L("ClaimPointerGrabbingTwoWindowsL case 0") );
			
			for(; pointerNumber < iNumberOfPointers; pointerNumber++ )
				{
				// Down in the Simple control. Not reported.
				SimulatePointer( TRawEvent::EButton1Down, downPoint.iX, downPoint.iY, KControlTestLessThanHighPressure, pointerNumber );
				// Grabbed by Cluster1, Child1
				iControlCluster_1->iChildOne->ClaimPointerGrab( pointerNumber, EFalse );
				// Drag-event reported in Cluster1, Child1
				SimulatePointer( TRawEvent::EPointerMove, upPoint.iX, upPoint.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EDrag, expectedUpPoint, KControlTestLessThanHighPressure, pointerNumber, childOneAsExpectedControl );
				// Up-event reported in Cluster1, Child1
				SimulatePointer( TRawEvent::EButton1Up, upPoint.iX, upPoint.iY, KControlTestExitCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, expectedUpPoint, KControlTestExitCloseProximity, pointerNumber, childOneAsExpectedControl );
				}

			}
			break;

		case 1:
			{
			INFO_PRINTF1( _L("ClaimPointerGrabbingTwoWindowsL case 1") );
			RDebug::Print( _L("ClaimPointerGrabbingTwoWindowsL case 1") );
			
			for(; pointerNumber < iNumberOfPointers; pointerNumber++ )
				{
				// Down in the Simple control. Not reported.
				SimulatePointer( TRawEvent::EButton1Down, downPoint.iX, downPoint.iY, KControlTestLessThanHighPressure, pointerNumber );
				// Grabbed by Cluster1, Child1
				iControlCluster_1->iChildOne->ClaimPointerGrab( pointerNumber, EFalse );
				// Drag-event reported in Cluster1, Child1
				SimulatePointer( TRawEvent::EPointerMove, upPoint.iX, upPoint.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EDrag, expectedUpPoint, KControlTestLessThanHighPressure, pointerNumber, childOneAsExpectedControl );
				// Enter high pressure
				SimulatePointer( TRawEvent::EPointerMove, upPoint.iX, upPoint.iY, KControlTestEnterHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EEnterHighPressure, expectedUpPoint, KControlTestEnterHighPressure, pointerNumber, childOneAsExpectedControl );			
				// Exit high pressure
				SimulatePointer( TRawEvent::EPointerMove, upPoint.iX, upPoint.iY, KControlTestExitHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EExitHighPressure, expectedUpPoint, KControlTestExitHighPressure, pointerNumber, childOneAsExpectedControl );
				// Up event (in proximity)
				SimulatePointer( TRawEvent::EButton1Up, upPoint.iX, upPoint.iY, KControlTestEnterCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, expectedUpPoint, KControlTestEnterCloseProximity, pointerNumber, childOneAsExpectedControl );
				
				// Exit close proximity (not reported).
				SimulatePointer( TRawEvent::EPointerMove, upPoint.iX, upPoint.iY, KControlTestExitCloseProximity, pointerNumber );
				}

			}
			break;
					
		default:
			{
			CActiveScheduler::Stop();
			iEventSet = 0;
			
			INFO_PRINTF1( _L("ClaimPointerGrabbingTwoWindowsL STOP\n") );
			INFO_PRINTF1( _L("") );
			RDebug::Print( _L("ClaimPointerGrabbingTwoWindowsL STOP") );
			RDebug::Print( _L("") );
			}
			break;
		
		}	

	}


/**
@SYMTestCaseID 			UIF-WSERV-ADVANCEDPOINTER-0044
@SYMPREQ 				PREQ1226
@SYMTestType			UT
@SYMTestPriority		Critical
@SYMTestStatus 			Implemented
@SYMTestCaseDesc		Capture the cycle of pointer events.
@SYMTestActions			Instantiate a compound control and a simple control. Set the simple control to 
						capture pointer events. Simulate events on child-2 of the compound control. Ensure they are
						delivered to the capturing simple control.
						
@SYMTestExpectedResults  The capturing simple-control should receive the simulated events
*/
void CConeMultiPtrCompoundTestAppUi::CapturePointerCycleL()
	{
	INFO_PRINTF1( _L(">CapturePointerCycleL") );
	RDebug::Print( _L(">CapturePointerCycleL") );	
	
	if( iNumberOfPointers <= 1 )
		{
		User::Leave( KErrNotSupported );
		}	
	
	const TInt KIntermediatePointerNumber = iNumberOfPointers / 2;
	const TInt KContainer_1_Child_2_X = 140;
	const TInt KContainer_1_Child_2_Y = 120;
	
	TInt pointerNumber = 0;
	TPoint incPoint( KMultiPtrTestCoOrdinateIncrementSmall, KMultiPtrTestCoOrdinateIncrementSmall );
	TPoint actionPoint( KContainer_1_Child_2_X, KContainer_1_Child_2_Y );
	TPoint resultPoint( actionPoint - KMultPtrSmallSimplePosition );

	
	switch( iEventSet++ )
		{
		case 0:
			{
			INFO_PRINTF1( _L("CapturePointerCycleL case 0") );
			RDebug::Print( _L("CapturePointerCycleL case 0") );
			
			iControlSimple->SetDrags();
			iControlSimple->SetGloballyCapturing( ETrue );
			iControlSimple->SetPointerCapture( ETrue );

			for(; pointerNumber < KIntermediatePointerNumber; pointerNumber++ )
				{
				SimulatePointer( TRawEvent::EPointerMove, actionPoint.iX, actionPoint.iY, KControlTestExitCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EMove, resultPoint, KControlTestExitCloseProximity, pointerNumber, iControlSimple );
				// Should be reported as EEnterCloseProximity
				SimulatePointer( TRawEvent::EPointerMove, actionPoint.iX, actionPoint.iY, KControlTestEnterCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EEnterCloseProximity, resultPoint, KControlTestEnterCloseProximity, pointerNumber, iControlSimple );
				// EButton1Down (Not High pressure)
				SimulatePointer( TRawEvent::EButton1Down, actionPoint.iX, actionPoint.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, resultPoint, KControlTestLessThanHighPressure, pointerNumber, iControlSimple );
				// EEnterHighPressure
				SimulatePointer( TRawEvent::EPointerMove, actionPoint.iX, actionPoint.iY, KControlTestEnterHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EEnterHighPressure, resultPoint, KControlTestEnterHighPressure, pointerNumber, iControlSimple );
				// EExitHighPressure
				SimulatePointer( TRawEvent::EPointerMove, actionPoint.iX, actionPoint.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EExitHighPressure, resultPoint, KControlTestLessThanHighPressure, pointerNumber, iControlSimple );
				// EButton1up
				SimulatePointer( TRawEvent::EButton1Up, actionPoint.iX, actionPoint.iY, KControlTestEnterCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, resultPoint, KControlTestEnterCloseProximity, pointerNumber, iControlSimple );
				// EExitCloseProximity
				SimulatePointer( TRawEvent::EPointerMove, actionPoint.iX, actionPoint.iY, KControlTestExitCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EExitCloseProximity, resultPoint, KControlTestExitCloseProximity, pointerNumber, iControlSimple );

				// EOutOfRange  ** Note: The three co-ordinates received with the EOutOfRange event are the last known co-ordinates of the pointer.
				//						 ie the co-ordinates of the previous event
				TPoint madeUpPoint( 1, 2 );
				SimulatePointer( TRawEvent::EPointer3DOutOfRange, madeUpPoint.iX, madeUpPoint.iY, KControlTestOutOfRange, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EOutOfRange, resultPoint, KControlTestExitCloseProximity, pointerNumber, iControlSimple );

				actionPoint += incPoint; // Differentiate each pointer's events by co-ordinate.
				resultPoint += incPoint;
				}
				
			}
			break;

		case 1:
			{
			INFO_PRINTF1( _L("CapturePointerCycleL case 1") );
			RDebug::Print( _L("CapturePointerCycleL case 1") );

			for( pointerNumber = KIntermediatePointerNumber; pointerNumber < iNumberOfPointers; pointerNumber++ )
				{
				SimulatePointer( TRawEvent::EPointerMove, actionPoint.iX, actionPoint.iY, KControlTestExitCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EMove, resultPoint, KControlTestExitCloseProximity, pointerNumber, iControlSimple );
				// Should be reported as EEnterCloseProximity
				SimulatePointer( TRawEvent::EPointerMove, actionPoint.iX, actionPoint.iY, KControlTestEnterCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EEnterCloseProximity, resultPoint, KControlTestEnterCloseProximity, pointerNumber, iControlSimple );
				// EButton1Down (Not High pressure)
				SimulatePointer( TRawEvent::EButton1Down, actionPoint.iX, actionPoint.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, resultPoint, KControlTestLessThanHighPressure, pointerNumber, iControlSimple );
				// EEnterHighPressure
				SimulatePointer( TRawEvent::EPointerMove, actionPoint.iX, actionPoint.iY, KControlTestEnterHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EEnterHighPressure, resultPoint, KControlTestEnterHighPressure, pointerNumber, iControlSimple );
				// EExitHighPressure
				SimulatePointer( TRawEvent::EPointerMove, actionPoint.iX, actionPoint.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EExitHighPressure, resultPoint, KControlTestLessThanHighPressure, pointerNumber, iControlSimple );
				// EButton1up
				SimulatePointer( TRawEvent::EButton1Up, actionPoint.iX, actionPoint.iY, KControlTestEnterCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, resultPoint, KControlTestEnterCloseProximity, pointerNumber, iControlSimple );
				// EExitCloseProximity
				SimulatePointer( TRawEvent::EPointerMove, actionPoint.iX, actionPoint.iY, KControlTestExitCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EExitCloseProximity, resultPoint, KControlTestExitCloseProximity, pointerNumber, iControlSimple );

				// EOutOfRange  ** Note: The three co-ordinates received with the EOutOfRange event are the last known co-ordinates of the pointer.
				//						 ie the co-ordinates of the previous event
				TPoint madeUpPoint( 1, 2 );
				SimulatePointer( TRawEvent::EPointer3DOutOfRange, madeUpPoint.iX, madeUpPoint.iY, KControlTestOutOfRange, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EOutOfRange, resultPoint, KControlTestExitCloseProximity, pointerNumber, iControlSimple );

				actionPoint += incPoint; // Differentiate each pointer's events by co-ordinate.
				resultPoint += incPoint;
				}
				
			}
			break;
			
		default:
			{
			CActiveScheduler::Stop();
			iEventSet = 0;
			
			INFO_PRINTF1( _L("CapturePointerCycleL STOP\n") );
			INFO_PRINTF1( _L("") );
			RDebug::Print( _L("CapturePointerCycleL STOP") );
			RDebug::Print( _L("") );
			}
			break;
	
		}
			
	}


/**
@SYMTestCaseID 			UIF-WSERV-ADVANCEDPOINTER-0040
@SYMPREQ 				PREQ1226
@SYMTestType			UT
@SYMTestPriority		Critical
@SYMTestStatus 			Implemented
@SYMTestCaseDesc		Ensure that captured pointer events are discarded by Cone and not delivered to child controls.
@SYMTestActions			Configure one of the compound control's children to capture. Perform the full sequence of pointer 
						z-events outside the parent. Ensure that Cone does not deliver these events to the 
						child controls. cf GRAPHICS-WSERV-ADVANCEDPOINTER-0020.

@SYMTestExpectedResults  The nominated child control should _not_ receive the generated events.
*/
void CConeMultiPtrCompoundTestAppUi::CapturePointerNotDeliveredToChildL()
	{
	INFO_PRINTF1( _L(">CapturePointerNotDeliveredToChildL") );
	RDebug::Print( _L(">CapturePointerNotDeliveredToChildL") );
	
	if( iNumberOfPointers <= 1 )
		{
		User::Leave( KErrNotSupported );
		}
	
	const TInt KIntermediatePointerNumber = iNumberOfPointers / 2;
	TInt pointerNumber = 0;
	const TInt KContainer_1_Child_2_X = 140;
	const TInt KContainer_1_Child_2_Y = 120;
	
	TPoint incPoint( KMultiPtrTestCoOrdinateIncrementSmall, KMultiPtrTestCoOrdinateIncrementSmall );
	TPoint actionPoint( KMultPtrTestCentreScreen );
	actionPoint -= incPoint;
	TPoint finishPoint( KContainer_1_Child_2_X, KContainer_1_Child_2_Y );

	switch( iEventSet++ )
		{
		case 0:
			{
			INFO_PRINTF1( _L("CapturePointerNotDeliveredToChildL case 0") );
			RDebug::Print( _L("CapturePointerNotDeliveredToChildL case 0") );

			iControlCluster_1->iChildOne->SetGloballyCapturing( ETrue );
			iControlCluster_1->iChildOne->SetPointerCapture( ETrue );
			
			for(; pointerNumber < KIntermediatePointerNumber; pointerNumber++ )
				{
				SimulatePointer( TRawEvent::EPointerMove, actionPoint.iX, actionPoint.iY, KControlTestEnterCloseProximity, pointerNumber );
				SimulatePointer( TRawEvent::EButton1Down, actionPoint.iX, actionPoint.iY, KControlTestLessThanHighPressure, pointerNumber );
				SimulatePointer( TRawEvent::EPointerMove, actionPoint.iX, actionPoint.iY, KControlTestEnterHighPressure, pointerNumber );
				SimulatePointer( TRawEvent::EPointerMove, actionPoint.iX, actionPoint.iY, KControlTestExitHighPressure, pointerNumber );
				SimulatePointer( TRawEvent::EButton1Up, actionPoint.iX, actionPoint.iY, KControlTestEnterCloseProximity, pointerNumber );
				SimulatePointer( TRawEvent::EPointerMove, actionPoint.iX, actionPoint.iY, KControlTestExitCloseProximity, pointerNumber );	
				SimulatePointer( TRawEvent::EPointer3DOutOfRange, actionPoint.iX, actionPoint.iY, KControlTestExitCloseProximity, pointerNumber );
				
				actionPoint -= incPoint; // Move inward from the centre/edge of the screen
				}

			// Simulate some events which _will be delivered (in order to finish the test).
			pointerNumber = 0;

			SimulatePointerDownUp( finishPoint.iX, finishPoint.iY, KControlTestLessThanHighPressure, pointerNumber );
			AddExpectedPointerDownUp( (finishPoint - iControlCluster_1->PositionRelativeToScreen()), KControlTestLessThanHighPressure, pointerNumber, iControlCluster_1->iChildTwo );
			// Do this in order that the pointer states are neutral for the test/s that follow.
			SimulatePointer( TRawEvent::EPointerMove, finishPoint.iX, finishPoint.iY, KControlTestExitCloseProximity, pointerNumber );
			AddExpectedPointer( TAdvancedPointerEvent::EExitCloseProximity, (finishPoint - iControlCluster_1->PositionRelativeToScreen()), KControlTestExitCloseProximity, pointerNumber, iControlCluster_1->iChildTwo );
			}
			break;

		case 1:
			{
			INFO_PRINTF1( _L("CapturePointerNotDeliveredToChildL case 1") );
			RDebug::Print( _L("CapturePointerNotDeliveredToChildL case 1") );

			iControlCluster_1->iChildOne->SetGloballyCapturing( ETrue );
			iControlCluster_1->iChildOne->SetPointerCapture( ETrue );
			pointerNumber = KIntermediatePointerNumber;
			
			for(; pointerNumber < iNumberOfPointers; pointerNumber++ )
				{
				SimulatePointer( TRawEvent::EPointerMove, actionPoint.iX, actionPoint.iY, KControlTestEnterCloseProximity, pointerNumber );
				SimulatePointer( TRawEvent::EButton1Down, actionPoint.iX, actionPoint.iY, KControlTestLessThanHighPressure, pointerNumber );
				SimulatePointer( TRawEvent::EPointerMove, actionPoint.iX, actionPoint.iY, KControlTestEnterHighPressure, pointerNumber );
				SimulatePointer( TRawEvent::EPointerMove, actionPoint.iX, actionPoint.iY, KControlTestExitHighPressure, pointerNumber );
				SimulatePointer( TRawEvent::EButton1Up, actionPoint.iX, actionPoint.iY, KControlTestEnterCloseProximity, pointerNumber );
				SimulatePointer( TRawEvent::EPointerMove, actionPoint.iX, actionPoint.iY, KControlTestExitCloseProximity, pointerNumber );	
				SimulatePointer( TRawEvent::EPointer3DOutOfRange, actionPoint.iX, actionPoint.iY, KControlTestExitCloseProximity, pointerNumber );
				
				actionPoint -= incPoint; // Move inward from the centre/edge of the screen
				}
			
			// Simulate some events which _will be delivered  (in order to finish the test).
			pointerNumber = 0;

			SimulatePointerDownUp( finishPoint.iX, finishPoint.iY, KControlTestLessThanHighPressure, pointerNumber );
			AddExpectedPointerDownUp( (finishPoint - iControlCluster_1->PositionRelativeToScreen()), KControlTestLessThanHighPressure, pointerNumber, iControlCluster_1->iChildTwo );	
			// Do this in order that the pointer states are neutral for the test/s that follow.
			SimulatePointer( TRawEvent::EPointerMove, finishPoint.iX, finishPoint.iY, KControlTestExitCloseProximity, pointerNumber );
			AddExpectedPointer( TAdvancedPointerEvent::EExitCloseProximity, (finishPoint - iControlCluster_1->PositionRelativeToScreen()), KControlTestExitCloseProximity, pointerNumber, iControlCluster_1->iChildTwo );
			}
			break;
			
		default:
			{
			CActiveScheduler::Stop();
			iEventSet = 0;
			
			INFO_PRINTF1( _L("CapturePointerNotDeliveredToChildL STOP\n") );
			INFO_PRINTF1( _L("") );
			RDebug::Print( _L("CapturePointerNotDeliveredToChildL STOP") );
			RDebug::Print( _L("") );
			}
			break;
		}
	
	}


/**
@SYMTestCaseID 			UIF-WSERV-ADVANCEDPOINTER-0042
@SYMPREQ 				PREQ1226
@SYMTestType			UT
@SYMTestPriority		Critical
@SYMTestStatus 			Implemented
@SYMTestCaseDesc		Pointers cycle to out of range.
@SYMTestActions			Simulate the full cycle of each pointer's z-events
						cf GRAPHICS-WSERV-ADVANCEDPOINTER-0016

@SYMTestExpectedResults  The designated child control should receive the anticipated events,
						 culminating in the EOutOfRange event, which should bear the last known co-ordinates, ie
						 the previous event's co-ordinates.
*/
void CConeMultiPtrCompoundTestAppUi::CycleToOutOfRangeL()
	{
	INFO_PRINTF1( _L(">MoveAndOutOfRangeL") );
	RDebug::Print( _L(">MoveAndOutOfRangeL") );
	
	if( iNumberOfPointers <= 1 )
		{
		User::Leave( KErrNotSupported );
		}
	
	TInt pointerNumber = 0;
	const TInt KIntermediatePointerNumber = iNumberOfPointers / 2;
	const TInt KContainer_1_Child_2_X = 140;
	const TInt KContainer_1_Child_2_Y = 120;
	TPoint point( KContainer_1_Child_2_X, KContainer_1_Child_2_Y );
	TPoint incPoint( KMultiPtrTestCoOrdinateIncrementSmall, KMultiPtrTestCoOrdinateIncrementSmall );
	TPoint parentPosition( iControlCluster_1->Position() );
	TPoint expectedPoint( point - parentPosition );
	TPoint madeUpPoint( 1234, 2345 );
	CMultiPtrTestControlBase* expectedControl = iControlCluster_1->iChildTwo;
	iControlCluster_1->iChildTwo->SetDrags();
	
	switch( iEventSet++ )
		{
		case 0:
			{	
			INFO_PRINTF1( _L("MoveAndOutOfRangeL case 0") );
			RDebug::Print( _L("MoveAndOutOfRangeL case 0") );

			for(; pointerNumber < KIntermediatePointerNumber; pointerNumber++ )
				{
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestExitCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EMove, expectedPoint, KControlTestExitCloseProximity, pointerNumber, expectedControl );
			
				// Should be reported as EEnterCloseProximity
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestEnterCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EEnterCloseProximity, expectedPoint, KControlTestEnterCloseProximity, pointerNumber, expectedControl );
				// EButton1Down (Not High pressure)
				SimulatePointer( TRawEvent::EButton1Down, point.iX, point.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, expectedPoint, KControlTestLessThanHighPressure, pointerNumber, expectedControl );
				// EEnterHighPressure
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestEnterHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EEnterHighPressure, expectedPoint, KControlTestEnterHighPressure, pointerNumber, expectedControl );
				// EExitHighPressure
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EExitHighPressure, expectedPoint, KControlTestLessThanHighPressure, pointerNumber, expectedControl );
				// EButton1up
				SimulatePointer( TRawEvent::EButton1Up, point.iX, point.iY, KControlTestEnterCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, expectedPoint, KControlTestEnterCloseProximity, pointerNumber, expectedControl );
				// EExitCloseProximity
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestExitCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EExitCloseProximity, expectedPoint, KControlTestExitCloseProximity, pointerNumber, expectedControl );
				// EOutOfRange  ** Note: The three co-ordinates received with the EOutOfRange event are the last known co-ordinates of the pointer.
				//						 ie the co-ordinates of the previous event
				SimulatePointer( TRawEvent::EPointer3DOutOfRange, madeUpPoint.iX, madeUpPoint.iY, KControlTestOutOfRange, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EOutOfRange, expectedPoint, KControlTestExitCloseProximity, pointerNumber, expectedControl );
				
				// Discriminate each pointer's event-sequence by position.
				point += incPoint;
				expectedPoint += incPoint;
				}
			
			}
			break;

		case 1:
			{	
			INFO_PRINTF1( _L("MoveAndOutOfRangeL case 1") );
			RDebug::Print( _L("MoveAndOutOfRangeL case 1") );

			pointerNumber = KIntermediatePointerNumber;
			
			for(; pointerNumber < iNumberOfPointers; pointerNumber++ )
				{
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestExitCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EMove, expectedPoint, KControlTestExitCloseProximity, pointerNumber, expectedControl );
			
				// Should be reported as EEnterCloseProximity
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestEnterCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EEnterCloseProximity, expectedPoint, KControlTestEnterCloseProximity, pointerNumber, expectedControl );
				// EButton1Down (Not High pressure)
				SimulatePointer( TRawEvent::EButton1Down, point.iX, point.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Down, expectedPoint, KControlTestLessThanHighPressure, pointerNumber, expectedControl );
				// EEnterHighPressure
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestEnterHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EEnterHighPressure, expectedPoint, KControlTestEnterHighPressure, pointerNumber, expectedControl );
				// EExitHighPressure
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestLessThanHighPressure, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EExitHighPressure, expectedPoint, KControlTestLessThanHighPressure, pointerNumber, expectedControl );
				// EButton1up
				SimulatePointer( TRawEvent::EButton1Up, point.iX, point.iY, KControlTestEnterCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EButton1Up, expectedPoint, KControlTestEnterCloseProximity, pointerNumber, expectedControl );
				// EExitCloseProximity
				SimulatePointer( TRawEvent::EPointerMove, point.iX, point.iY, KControlTestExitCloseProximity, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EExitCloseProximity, expectedPoint, KControlTestExitCloseProximity, pointerNumber, expectedControl );
				// EOutOfRange  ** Note: The three co-ordinates received with the EOutOfRange event are the last known co-ordinates of the pointer.
				//						 ie the co-ordinates of the previous event
				SimulatePointer( TRawEvent::EPointer3DOutOfRange, madeUpPoint.iX, madeUpPoint.iY, KControlTestOutOfRange, pointerNumber );
				AddExpectedPointer( TAdvancedPointerEvent::EOutOfRange, expectedPoint, KControlTestExitCloseProximity, pointerNumber, expectedControl );
				
				// Discriminate each pointer's event-sequence by position.
				point += incPoint;
				expectedPoint += incPoint;
				}
			
			}
			break;
			
		default:
			{
			CActiveScheduler::Stop();
			iEventSet = 0;
			
			INFO_PRINTF1( _L("MoveAndOutOfRangeL STOP\n") );
			INFO_PRINTF1( _L("") );
			RDebug::Print( _L("MoveAndOutOfRangeL STOP") );
			RDebug::Print( _L("") );
			}
			break;
			
		}	
	
	}



// Stops the active scheduler and sets the flag to ETrue
void CConeMultiPtrCompoundTestAppUi::Failed()
	{
	CActiveScheduler::Stop();
	iFailed = ETrue;
	}


/**
 CTestStep derived class. It creates the control environment and App Ui class objects
*/
 void CTConeMultiPtrCompoundStep::ConstructConeMultiPtrAppL(CCoeEnv* aCoe)
 	{ // runs inside a TRAP harness
 	aCoe->ConstructL();
 	CConeMultiPtrCompoundTestAppUi* appUi=new(ELeave) CConeMultiPtrCompoundTestAppUi(this);
 	aCoe->SetAppUi(appUi);
 	aCoe->WsSession().SetDoubleClick(1000000,4);
 	appUi->ConstructL();
 	}
 
 
 CTConeMultiPtrCompoundStep::CTConeMultiPtrCompoundStep()
	 {
	 SetTestStepName(KTConeMultiPtrCompoundStep);
	 }
 
 
 CTConeMultiPtrCompoundStep::~CTConeMultiPtrCompoundStep()
	 {
	 
	 }


/**
Testexecute loads testserver and creates CTConeMultiPtrCompoundStep object and calls 
this function for each step in script file.
*/
TVerdict CTConeMultiPtrCompoundStep::doTestStepL()
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


TVerdict CTConeMultiPtrCompoundStep::doTestStepPreambleL()
	{
	// Remember the double-click settings.
	// Tests (may) adjust these values.
	RWsSession wsSession;
	User::LeaveIfError( wsSession.Connect() );

	wsSession.GetDoubleClickSettings( iDoubleClickMaxInterval, iDoubleClickMaxDistance );
	wsSession.Close();	

	return CTestStep::doTestStepPreambleL();
	}
	
	
TVerdict CTConeMultiPtrCompoundStep::doTestStepPostambleL()
	{
	// Restore the original system-wide double-click settings.
	RWsSession wsSession;
	User::LeaveIfError( wsSession.Connect() );

	wsSession.SetDoubleClick( iDoubleClickMaxInterval, iDoubleClickMaxDistance);
	wsSession.Close();
	
	return CTestStep::doTestStepPostambleL();
	}
