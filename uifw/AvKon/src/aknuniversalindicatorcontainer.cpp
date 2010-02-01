/*
* Copyright (c) 2006-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Application side control in the status pane indicator area. 
*
*/



// INCLUDE FILES
#include "aknuniversalindicatorcontainer.h"
#include "AknIndicatorContainer.h"

#include <AknTasHook.h> // for testability hooks
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknUniversalIndicatorContainer::CAknUniversalIndicatorContainer
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CAknUniversalIndicatorContainer::CAknUniversalIndicatorContainer()
	{
	AKNTASHOOK_ADD( this, "CAknUniversalIndicatorContainer" );
  	}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
CAknUniversalIndicatorContainer::~CAknUniversalIndicatorContainer()
	{
	AKNTASHOOK_REMOVE();
  	delete iPane;
  	}

// -----------------------------------------------------------------------------
// CAknUniversalIndicatorContainer::ConstructFromResourceL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknUniversalIndicatorContainer::ConstructFromResourceL(TResourceReader& aReader)
    {
    iPane = new (ELeave) CAknIndicatorContainer();
    iPane->SetContainerWindowL(*this);
    iPane->ConstructFromResourceL(aReader);         
    MakeVisible( ETrue );
	}

// -----------------------------------------------------------------------------
// CAknUniversalIndicatorContainer::SizeChanged
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknUniversalIndicatorContainer::SizeChanged()
    {
    TPoint tl = Rect().iTl;
    if (iPane)
    	iPane->SetExtent( tl, Size() );	
    }

// -----------------------------------------------------------------------------
// CAknUniversalIndicatorContainer::CountComponentControls
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CAknUniversalIndicatorContainer::CountComponentControls() const
    {
    if ( iPane )
        {
        return 1;
        }
    return 0;
    }

// -----------------------------------------------------------------------------
// CAknUniversalIndicatorContainer::ComponentControl
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
CCoeControl* CAknUniversalIndicatorContainer::ComponentControl(TInt /*aIndex*/) const
    {
    return iPane;
    }
    

//  End of File  


