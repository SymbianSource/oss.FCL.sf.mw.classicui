/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  for testing the indicators api module
*
*/


#include "testsdkindicatorsindicators.h"

// -----------------------------------------------------------------------------
// CTestSDKIndicatorsIndicators::CTestSDKIndicatorsIndicators
// -----------------------------------------------------------------------------
//
CTestSDKIndicatorsIndicators::CTestSDKIndicatorsIndicators()
    :CAknIndicatorContainer()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CTestSDKIndicatorsIndicators::~CTestSDKIndicatorsIndicators
// -----------------------------------------------------------------------------
//
CTestSDKIndicatorsIndicators::~CTestSDKIndicatorsIndicators()
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKIndicatorsIndicators::ConstructFromResourceL
// -----------------------------------------------------------------------------
//
void CTestSDKIndicatorsIndicators::ConstructFromResourceL( TResourceReader& aReader )
    {
    CAknIndicatorContainer::ConstructFromResourceL( aReader );
    }

// -----------------------------------------------------------------------------
// CTestSDKIndicatorsIndicators::HandleResourceChange
// -----------------------------------------------------------------------------
//
void CTestSDKIndicatorsIndicators::HandleResourceChange( TInt aType )
    {
    CAknIndicatorContainer::HandleResourceChange( aType );
    }

// -----------------------------------------------------------------------------
// CTestSDKIndicatorsIndicators::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestSDKIndicatorsIndicators::SizeChanged()
    {
    CAknIndicatorContainer::SizeChanged();
    }


// -----------------------------------------------------------------------------
// CTestSDKIndicatorsIndicators::PositionChanged
// -----------------------------------------------------------------------------
//
void CTestSDKIndicatorsIndicators::PositionChanged()
    {
    CAknIndicatorContainer::PositionChanged();
    }


// -----------------------------------------------------------------------------
// CTestSDKIndicatorsIndicators::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicatorsIndicators::CountComponentControls() const
    {
    return CAknIndicatorContainer::CountComponentControls();
    }


// -----------------------------------------------------------------------------
// CTestSDKIndicatorsIndicators::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestSDKIndicatorsIndicators::ComponentControl( TInt aIndex ) const
    {
    return CAknIndicatorContainer::ComponentControl( aIndex );
    }


// -----------------------------------------------------------------------------
// CTestSDKIndicatorsIndicators::Reserved_1
// -----------------------------------------------------------------------------
//
void CTestSDKIndicatorsIndicators::Reserved_1()
    {
    
    }

// End of files
