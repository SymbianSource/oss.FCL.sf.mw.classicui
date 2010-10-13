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
* Description:  Updates the signal level control in status pane. 
*
*/


// INCLUDE FILES
#include "aknsignaldataobserver.h"
#include "aknstatuspanedata.h"
#include "AknSignal.h"
#include "AknSignalStrength.h"

#include "aknstatuspanedatasubscriber.h"
#include <eikspane.h>
#include <avkon.hrh>
#include <eikapp.h>
#include <eikappui.h>


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknSignalDataObserver::CAknSignalDataObserver
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CAknSignalDataObserver::CAknSignalDataObserver(CAknSignalPane* aSignalPane)
	{
	iSignalPane = aSignalPane;
	iSignalPane->MopGetObject(iDataSubscriber);
	if (iDataSubscriber)
		{
		iDataSubscriber->AddObserver(this); 
		}
    }


// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
CAknSignalDataObserver::~CAknSignalDataObserver()
	{
	if (iDataSubscriber)
		{
		iDataSubscriber->RemoveObserver(this); 
		}
    }

// -----------------------------------------------------------------------------
// CAknSignalDataObserver::HandleUpdateL
// Updates UI control.    
// -----------------------------------------------------------------------------
//
void CAknSignalDataObserver::HandleUpdateL(const TAknStatusPaneStateData& aData)
	{
	if (!iDataSubscriber)
		return;	
	
  	TAknSignalState state = aData.iSignalState;	

	// If this pane is not in current layout, no update. Update happens 
	// when status pane layout is changed.
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
   	if (!statusPane || 
   		!statusPane->PaneCapabilities(TUid::Uid(EEikStatusPaneUidSignal)).IsInCurrentLayout())
   		{
		return;
   		}
	
   	// Animation is not shown in the background unless update level has been 
   	// set above ERefreshLevelMedium.
    TBool updateAnimation = 
    	(!iDataSubscriber->IsBackground() || 
    	 iDataSubscriber->RefreshLevel() > CAknStatusPaneDataSubscriber::ERefreshLevelMedium);
	
	// Update only if changed to avoid unncessary redraws etc.
	TBool strengthChanged = state.iSignalStrength != iSignalPane->SignalLevel();	
	TBool iconChanged = state.iIconState != iSignalPane->SignalState();
	
	// Set signal strenght (this handles also Offline status)
	if (strengthChanged)
		iSignalPane->SetSignalLevel(state.iSignalStrength);
	
	// Set signal icon
	if (iconChanged)
		{
		if (state.iIconState >= EAknSignalGprsIndicatorOff &&
		    state.iIconState < EAknSignalCommonPacketDataIndicatorOff)
		    {
		    // GPRS
		    iSignalPane->ShowGprsIcon(state.iIconState);
		    }
		else if (state.iIconState >= EAknSignalCommonPacketDataIndicatorOff &&
		    state.iIconState < EAknSignalWcdmaIndicatorOff)
			{
			// Common packet data
		    iSignalPane->ShowCommonPacketDataIcon(state.iIconState);				
			}    
		else if (state.iIconState >= EAknSignalWcdmaIndicatorOff &&
		    state.iIconState < EAknSignalCdmaIndicatorOff)
			{
			// WCDMA
		    iSignalPane->ShowWcdmaIcon(state.iIconState);
			}    
		else if (state.iIconState >= EAknSignalCdmaIndicatorOff &&
		    state.iIconState < EAknSignalEdgeIndicatorOff)
			{
			// CDMA
		    iSignalPane->ShowCdmaIcon(state.iIconState);
			}    
		else if (state.iIconState >= EAknSignalEdgeIndicatorOff &&
		    state.iIconState <= EAknSignalEdgeIndicatorMultipdp)
			{
			// EDGE
		    iSignalPane->ShowEdgeIcon(state.iIconState);
			}    			
		else if (state.iIconState >= EAknSignalHsdpaIndicatorOff &&
		    state.iIconState <= EAknSignalHsdpaIndicatorMultipdp)
			{
			// HSPDA
		    iSignalPane->ShowHsdpaIcon(state.iIconState);
			}    			
		}

	if (!updateAnimation)
		{
		iSignalPane->DisableAnimation();
		}	
		
	if (iconChanged || strengthChanged)
		iSignalPane->DrawDeferred();			
}		
		

//  End of File  
