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

#ifndef __TCONEMULTIPTRCONST_H__
#define __TCONEMULTIPTRCONST_H__


const TRect KMultPtrTestContainerRect( 40, 40, 300, 200 );
const TRect KMultPtrTestContainerRectTwo( 340, 40, 600, 200 );

const TPoint KMultPtrSmallSimplePosition( 280, 0 );
const TSize KMultPtrSmallSimpleSize( 40, 40 );

const TPoint KMultiPtrTestControlParentPosition( 20, 20 );
const TPoint KMultiPtrTestControlPositionOrigin( 0, 0 );
const TPoint KMultPtrTestCentreScreen( 320, 120 );

const TInt8 KMultiPtrTestPointerNumberLowest = 0;
const TInt KMultiPtrTestCoOrdinateIncrement = 10;
const TInt KMultiPtrTestCoOrdinateDecrement = 5;
const TInt KMultiPtrTestCoOrdinateIncrementSmall = 2;
const TInt KMultiPtrTestCoOrdinateDecrementSmall = 2;

// The thresholds we configure
const TInt KControlTestEnterCloseProximityThreshold = -10; // millimetres
const TInt KControlTestExitCloseProximityThreshold = -20;  // millimetres
const TInt KControlTestEnterHighPressureThreshold = 2000;  // milliNewtons
const TInt KControlTestExitHighPressureThreshold = 1000;   // milliNewtons
// The values used to stimulate the frameworks
const TInt KControlTestEnterCloseProximity = -5; // millimetres
const TInt KControlTestExitCloseProximity = -25; // millimetres
const TInt KControlTestOutOfRange = 1000;        // millimetres
const TInt KControlTestEnterHighPressure = 2500; // milliNewtons
const TInt KControlTestExitHighPressure = 500;   // milliNewtons
const TInt KControlTestLessThanHighPressure = KControlTestExitHighPressure;


enum TMultiPtrTestLeaves
	{
	ETestPassed=0,
	ETestFailed=1,
	};

#endif // __TCONEMULTIPTRCONST_H__
