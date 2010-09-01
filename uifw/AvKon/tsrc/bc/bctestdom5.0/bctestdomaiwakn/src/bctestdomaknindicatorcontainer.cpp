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
* Description:  for indirectly testing APIs in aknindicator.h 
*
*/



#include <barsread.h> 
#include <aknenv.h> 
#include <avkon.rsg> 

#include "bctestdomaknindicatorcontainer.h"

 
// ======== MEMBER FUNCTIONS ========


// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknIndicatorContainer* CBCTestDomAknIndicatorContainer::NewL()
    {
    CBCTestDomAknIndicatorContainer* self = 
        CBCTestDomAknIndicatorContainer::NewLC();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknIndicatorContainer* CBCTestDomAknIndicatorContainer::NewLC( )
    {
    CBCTestDomAknIndicatorContainer* self = 
        new( ELeave ) CBCTestDomAknIndicatorContainer;
    CleanupStack::PushL( self );    
    self->ConstructL();
    return self;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
EXPORT_C CBCTestDomAknIndicatorContainer::~CBCTestDomAknIndicatorContainer()
    {
    
    
    }

// ---------------------------------------------------------------------------
// From class CAknIndicatorContainer.
//  
// ---------------------------------------------------------------------------
//
EXPORT_C CCoeControl* CBCTestDomAknIndicatorContainer::
    ComponentControl(TInt aIndex) const
	{	
	return CAknIndicatorContainer::ComponentControl( aIndex );    
    }

// ---------------------------------------------------------------------------
// From class CAknIndicatorContainer.
// ---------------------------------------------------------------------------
//
void CBCTestDomAknIndicatorContainer::Reserved_1()
	{
	
	}

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknIndicatorContainer::CBCTestDomAknIndicatorContainer()
:CAknIndicatorContainer( CAknIndicatorContainer::EFindIndicators )
    {

    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomAknIndicatorContainer::ConstructL( )
    {   
    //iIndicatorArray = new( ELeave ) CAknIconArray( 8 );
    //iIndicatorArray->ConstructFromResourceL( 
    //    R_AVKON_FIND_PANE_INDICATOR_ICONS );

    // construct CAknIndicatorContainer base

    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC( reader, 
        R_AVKON_NAVI_PANE_EDITOR_INDICATORS );
    this->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // reader    
    }



