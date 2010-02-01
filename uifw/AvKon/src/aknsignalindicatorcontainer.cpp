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
* Description:  Application side control in the status pane signal area. 
*
*/


// INCLUDE FILES
#include "aknsignalindicatorcontainer.h"
#include "AknSignal.h"

#include <AknTasHook.h>
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknSignalIndicatorContainer::CAknSignalIndicatorContainer
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CAknSignalIndicatorContainer::CAknSignalIndicatorContainer()
	{
	AKNTASHOOK_ADD( this, "CAknSignalIndicatorContainer" );
  	}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
CAknSignalIndicatorContainer::~CAknSignalIndicatorContainer()
	{
	AKNTASHOOK_REMOVE();
  	delete iPane;
  	}

// -----------------------------------------------------------------------------
// CAknSignalIndicatorContainer::ConstructFromResourceL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknSignalIndicatorContainer::ConstructFromResourceL(TResourceReader& aReader)
    {
    iPane = new (ELeave) CAknSignalPane();
    iPane->SetContainerWindowL(*this);
    iPane->ConstructFromResourceL(aReader);
    iPane->ActivateL();
    MakeVisible( ETrue );
	}

// -----------------------------------------------------------------------------
// CAknSignalIndicatorContainer::SizeChanged
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknSignalIndicatorContainer::SizeChanged()
    {
    TPoint tl = Rect().iTl;
    if (iPane)
    	iPane->SetExtent( tl, Size() );	
    }

// -----------------------------------------------------------------------------
// CAknSignalIndicatorContainer::CountComponentControls
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CAknSignalIndicatorContainer::CountComponentControls() const
    {
    if ( iPane )
        {
        return 1;
        }
    return 0;
    }

// -----------------------------------------------------------------------------
// CAknSignalIndicatorContainer::ComponentControl
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
CCoeControl* CAknSignalIndicatorContainer::ComponentControl(TInt /*aIndex*/) const
    {
    return iPane;
    }


//  End of File  


