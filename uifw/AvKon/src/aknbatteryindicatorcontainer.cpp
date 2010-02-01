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
* Description:  Application side control in the status pane battery area. 
*
*/


// INCLUDE FILES
#include "aknbatteryindicatorcontainer.h"
#include "AknBattery.h"

#include <AknTasHook.h>
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknBatteryIndicatorContainer::CAknBatteryIndicatorContainer
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CAknBatteryIndicatorContainer::CAknBatteryIndicatorContainer()
	{
	AKNTASHOOK_ADD( this, "CAknBatteryIndicatorContainer" );
  	}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
CAknBatteryIndicatorContainer::~CAknBatteryIndicatorContainer()
	{
	AKNTASHOOK_REMOVE();
  	delete iPane;
  	}

// -----------------------------------------------------------------------------
// CAknBatteryIndicatorContainer::ConstructFromResourceL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknBatteryIndicatorContainer::ConstructFromResourceL(TResourceReader& aReader)
    {
    iPane = new (ELeave) CAknBatteryPane();
    iPane->SetContainerWindowL(*this);
    iPane->ConstructFromResourceL(aReader);     
    //iPane->ActivateL();
    MakeVisible( ETrue );
	}

// -----------------------------------------------------------------------------
// CAknBatteryIndicatorContainer::CountComponentControls
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CAknBatteryIndicatorContainer::CountComponentControls() const
    {
    if ( iPane )
        {
        return 1;
        }
    return 0;
    }

// -----------------------------------------------------------------------------
// CAknBatteryIndicatorContainer::ComponentControl
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
CCoeControl* CAknBatteryIndicatorContainer::ComponentControl(TInt /*aIndex*/) const
    {
    return iPane;
    }


// -----------------------------------------------------------------------------
// CAknBatteryIndicatorContainer::SizeChanged
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknBatteryIndicatorContainer::SizeChanged()
    {
    TPoint tl = Rect().iTl;
    if (iPane)
    	iPane->SetExtent( tl, Size() );	
    }
    


//  End of File  
