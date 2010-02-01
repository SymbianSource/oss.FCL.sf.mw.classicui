/*
* Copyright (c) 2006,2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  This internal Avkon class updates the battery indicator 
*                control in status pane.
*
*/


// INCLUDE FILES
#include "aknbatterydataobserver.h"
#include "aknstatuspanedata.h"
#include "AknBattery.h"
#include "AknBatteryStrength.h"

#include "aknstatuspanedatasubscriber.h"
#include <eikspane.h>
#include <avkon.hrh>
#include <eikapp.h>
#include <eikappui.h>


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknBatteryDataObserver::CAknBatteryDataObserver
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CAknBatteryDataObserver::CAknBatteryDataObserver(
    CAknBatteryPane* aBatteryPane )
	{
	iBatteryPane = aBatteryPane;
	iBatteryPane->MopGetObject( iDataSubscriber );
	if ( iDataSubscriber )
		{
		iDataSubscriber->AddObserver( this ); 
		}
    }


// -----------------------------------------------------------------------------
// Destructor.
// -----------------------------------------------------------------------------
//
CAknBatteryDataObserver::~CAknBatteryDataObserver()
	{
	if ( iDataSubscriber )
		{
		iDataSubscriber->RemoveObserver( this ); 
		}
  }


// -----------------------------------------------------------------------------
// CAknBatteryDataObserver::HandleUpdateL
// Updates UI control state.    
// -----------------------------------------------------------------------------
//
void CAknBatteryDataObserver::HandleUpdateL(
    const TAknStatusPaneStateData& aData )
	{
	if ( !iDataSubscriber )
	    {
		return;
	    }
		   	
	// If this pane is not in current layout, no update. Update happens when 
	// status pane layout is changed.
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
   	if ( !statusPane || 
   		 !statusPane->PaneCapabilities(
   		    TUid::Uid( EEikStatusPaneUidBattery ) ).IsInCurrentLayout() )
   		{
		return;
   		}
   	
    TAknBatteryState state = aData.iBatteryState;		
	TBool levelChanged     = EFalse;
	TBool rechargeChanged  = EFalse;
	TBool iconChanged      = EFalse;
   	
   	// Animation is not shown in the background unless update level has been 
   	// set above ERefreshLevelMedium.
    TBool updateAnimation = 
        ( !iDataSubscriber->IsBackground() ||     	
    	  iDataSubscriber->RefreshLevel() > CAknStatusPaneDataSubscriber::ERefreshLevelMedium );
	
	if ( iBatteryPane->BatteryState() != state.iIconState )
	    {
	    iBatteryPane->SetBatteryStateL( state.iIconState );
	    iconChanged = ETrue;
	    }
			
	if ( iBatteryPane->BatteryLevel() != state.iBatteryStrength )
		{
		iBatteryPane->SetBatteryLevel( state.iBatteryStrength );
		levelChanged = ETrue;		
		}
		
	if ( updateAnimation )
		{
		if ( iBatteryPane->Recharging() != state.iRecharging )
			{
			iBatteryPane->SetRecharge( state.iRecharging );										
			rechargeChanged = ETrue;
			}
		}
	else
		{
		if ( iBatteryPane->Recharging() != EFalse )
			{
			iBatteryPane->SetRecharge( EFalse );
			rechargeChanged = ETrue;
			}
		}

	if ( levelChanged || rechargeChanged || iconChanged )
		{
		iBatteryPane->DrawDeferred();	
		}
	}

//  End of File  
