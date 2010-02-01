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

#ifndef TCONEMULTIPTRCOMPOUNDSTEP_H_
#define TCONEMULTIPTRCOMPOUNDSTEP_H_

#include <coemain.h>
#include <coecntrl.h>
#include <coeaui.h>
#include <test/testexecutestepbase.h>
#include "TConeTestServer.h"
#include "appfwk_test_AppUi.h"
#include "tmultiptrtestcontrol.h"


// TConeMultiPtrCompound Test Step Name.\n
_LIT( KTConeMultiPtrCompoundStep,"TConeMultiPtrCompound" );


class CTConeMultiPtrCompoundStep : public CTmsTestStep
	{
public:
	CTConeMultiPtrCompoundStep();
	~CTConeMultiPtrCompoundStep();
	virtual TVerdict doTestStepL();
	TVerdict doTestStepPreambleL();
	TVerdict doTestStepPostambleL();
	
	void ConstructConeMultiPtrAppL( CCoeEnv* aCoe );
	
public:
	TTimeIntervalMicroSeconds32 iDoubleClickMaxInterval;
	TInt iDoubleClickMaxDistance;
	};



class CMultPtrTestCompoundControlContainer;
class CConeMultiPtrCompoundTestAppUi : public CTestCoeAppUi
    {
public:
	CConeMultiPtrCompoundTestAppUi( CTmsTestStep* aStep );
	~CConeMultiPtrCompoundTestAppUi();
	
public:	
	// from CCoeAppUi
	void ConstructL();
	
	void NextSetOfEventsL();
	
	// The tests
	void PreliminaryStimuliL();
	void SinglePtrProximityAndPressureL();
	void MultiplePtrProximityAndPressureL();
	void PointerGrabbingL();
	void ClaimPointerGrabbingL();
	void ClaimPointerGrabbingTwoWindowsL();
	void CapturePointerCycleL();
	void CapturePointerNotDeliveredToChildL();
	void CycleToOutOfRangeL();
	TBool ConfigurationSupportsPointerEventTesting() const;
	// The infrastructural methods
	void SimulatePointer( TRawEvent::TType aType, TInt aX, TInt aY, TInt aZ, TUint8 aPointerNumber );
	void SimulatePointerDownUp( TInt aX, TInt aY, TInt aZ, TUint8 aPointerNumber );
	void AddExpectedPointer( TAdvancedPointerEvent::TType aType, TPoint aPos, TInt aZ, TUint8 aPointerNumber, CMultiPtrTestControlBase* aControl );
	void AddExpectedPointerDownUp( TPoint aPos, TInt aZ, TUint8 aPointerNumber, CMultiPtrTestControlBase* aControl );
	void Failed();
	
private:
	void RunTestStepL( TInt aStepNum );

	void RunTestsSingleClusterL();
	void RunTestsDualClusterL();
	void RunTestsClusterPlusSimpleL();
	void RunTestsSimpleL();
	void InstantiateControlClusterOneL();
	void DeleteControlClusterOne();
	void InstantiateControlClusterTwoL();
	void DeleteControlClusterTwo();
	
public:
	CMultPtrTestCompoundControlContainer* iControlCluster_1;
	CMultPtrTestCompoundControlContainer* iControlCluster_2;
	CMultiPtrTestCompoundAppUiControl* iControlSimple;
	
private:	
	TInt iTestCase;
	TInt iEventCount;
	TBool iFailed;
	TInt iEventSet;
	TInt iNumberOfPointers;
	TRect iNormalPointerCursorArea;
    };


#endif // TCONEMULTIPTRCOMPOUNDSTEP_H_

