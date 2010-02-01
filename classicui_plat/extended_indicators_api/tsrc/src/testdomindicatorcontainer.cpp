/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test aknindicator.h
*
*/


#include <barsread.h> 
#include <aknenv.h> 
#include <avkon.rsg> 

#include "testdomindicatorcontainer.h"

 
// ======== MEMBER FUNCTIONS ========


// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CTestDomIndicatorContainer* CTestDomIndicatorContainer::NewL()
    {
    CTestDomIndicatorContainer* self = CTestDomIndicatorContainer::NewLC();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CTestDomIndicatorContainer* CTestDomIndicatorContainer::NewLC( )
    {
    CTestDomIndicatorContainer* self = new( ELeave ) CTestDomIndicatorContainer;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CTestDomIndicatorContainer::~CTestDomIndicatorContainer()
    {
    }

// ---------------------------------------------------------------------------
// From class CAknIndicatorContainer.
//  
// ---------------------------------------------------------------------------
//
CCoeControl* CTestDomIndicatorContainer::ComponentControl(TInt aIndex) const
    {   
    return CAknIndicatorContainer::ComponentControl( aIndex );
    }

// ---------------------------------------------------------------------------
// From class CAknIndicatorContainer.
// ---------------------------------------------------------------------------
//
void CTestDomIndicatorContainer::Reserved_1()
    {
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CTestDomIndicatorContainer::CTestDomIndicatorContainer() : 
        CAknIndicatorContainer( CAknIndicatorContainer::EFindIndicators )
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CTestDomIndicatorContainer::ConstructL( )
    {   
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC( reader,
            R_AVKON_NAVI_PANE_EDITOR_INDICATORS );
    this->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    }



