/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  for testing APIs in bctestdomaknanimdata.h
*
*/


#include <aknviewappui.h>
#include <bctestdomaiwakn.rsg>

#include "bctestdomaiwakn.hrh"
#include "bctestdomaknanimdata.h"

 

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknAnimationData* CBCTestDomAknAnimationData::NewLC( )
    {
    CBCTestDomAknAnimationData* self = 
        new( ELeave ) CBCTestDomAknAnimationData();
    CleanupStack::PushL( self );
    self->ConstructL( );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknAnimationData::CBCTestDomAknAnimationData()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomAknAnimationData::ConstructL( )
    {
    CAknAnimationData::ConstructL( );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknAnimationData::~CBCTestDomAknAnimationData()
    {
    }

// ---------------------------------------------------------------------------
// From CAknAnimationData
// CBCTestDomAknAnimationData::DrawUserAnimationStep
// ---------------------------------------------------------------------------
//
TBool CBCTestDomAknAnimationData::DrawUserAnimationStep(
    CBitmapContext& aGc, 
    TAnimMultiStep& aStep)
    {
    return CAknAnimationData::DrawUserAnimationStep(aGc, aStep);
    }

// ---------------------------------------------------------------------------
// From CAknAnimationData
// CBCTestDomAknAnimationData::ConstructUserAnimationStepL
// ---------------------------------------------------------------------------
//
EXPORT_C void CBCTestDomAknAnimationData::ConstructUserAnimationStepL(
    TAnimStep&          aAnimStep, 
    TResourceReader&    aReader)
    {
    CAknAnimationData::ConstructUserAnimationStepL(
        aAnimStep, aReader);
    }
    


