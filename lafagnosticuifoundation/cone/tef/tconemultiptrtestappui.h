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


#ifndef __TCONEMULTIPTRTESTAPPUI_H__
#define __TCONEMULTIPTRTESTAPPUI_H__

#include "appfwk_test_appui.h"



class CConeMultiPtrTestAppUi : public CTestCoeAppUi
    {
public:
	CConeMultiPtrTestAppUi(CTmsTestStep* aStep);
	~CConeMultiPtrTestAppUi();
	
public:	
	// from CCoeAppUi
	void ConstructL();
	
	void NextSetOfEventsL();
	
	// The tests
	void MultiPointerEventsL();
	void PressureAndProximityL();
	void MoveAndDragL();
	void MoveAndOutOfRangeL();
	void PointerNumberOutOfRangeL();
	void MultiPointerCaptureL();
	void MultiPointerGrabL();
	
	void SimulatePointer(TRawEvent::TType aType, TInt aX, TInt aY, TInt aZ, TUint8 aPointerNumber);
	void SimulatePointerDownUp(TInt aX, TInt aY, TInt aZ, TUint8 aPointerNumber);
	void AddExpectedPointer(TAdvancedPointerEvent::TType aType, TPoint aPos, TInt aZ, TUint8 aPointerNumber, TInt aHandle = 0);
	void AddExpectedPointerDownUp(TPoint aPos, TInt aZ, TUint8 aPointerNumber);
	void Failed();
	TBool ConfigurationSupportsPointerEventTesting() const;
	
private:
	void RunTestStepL(TInt aStepNum);

	void RunTestsL();
	
public:
	CMultiPtrTestControl* iControl;
	
private:	
	TInt iTestCase;
	TInt iEventCount;
	TBool iFailed;
	TInt iEventSet;

	TInt iNumberOfPointers;
	TInt iMaxPointers;
	TInt iMaxPressure;
	TInt iPressureStep;
	TInt iPressureNominal;
	TInt iMaxProximity;
	TInt iProximityStep;
	TInt iProximityNominal;
	TRect iNormalPointerCursorArea;
    };


#endif // __TCONEMULTIPTRTESTAPPUI_H__
