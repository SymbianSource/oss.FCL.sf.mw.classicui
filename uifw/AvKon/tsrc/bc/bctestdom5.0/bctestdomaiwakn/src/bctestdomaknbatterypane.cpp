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
* Description:  test APIs in aknbattery.h
*
*/


#include "bctestdomaknbatterypane.h"

 
// ======== MEMBER FUNCTIONS ========


// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknBatteryPane::CBCTestDomAknBatteryPane()
    {

    } 

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
EXPORT_C CBCTestDomAknBatteryPane::~CBCTestDomAknBatteryPane()
    {

    }    
 
// ---------------------------------------------------------------------------
// From class CAknBatteryPane.
//  
// ---------------------------------------------------------------------------
//
EXPORT_C void CBCTestDomAknBatteryPane::HandleResourceChange( TInt aType )
    {
    CAknBatteryPane::HandleResourceChange( aType );    
    }    

// ---------------------------------------------------------------------------
// From class CAknBatteryPane.
//  
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CBCTestDomAknBatteryPane::CountComponentControls() const
    {
    return CAknBatteryPane::CountComponentControls();
    }

// ---------------------------------------------------------------------------
// From class CAknBatteryPane.
//  
// ---------------------------------------------------------------------------
//
EXPORT_C CCoeControl*  CBCTestDomAknBatteryPane::ComponentControl( 
    TInt aIndex ) const
    {
    return CAknBatteryPane::ComponentControl( aIndex );
    }        
  
// ---------------------------------------------------------------------------
// From class CAknBatteryPane.
//  
// ---------------------------------------------------------------------------
//
void CBCTestDomAknBatteryPane::HandlePointerEventL( 
    const TPointerEvent& /*aPointerEvent*/ )
    {
    
    }



