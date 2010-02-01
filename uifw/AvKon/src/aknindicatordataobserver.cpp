/*
* Copyright (c) 2006-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  This class updates the status indicator container control
*                in status pane.
*
*/


// SYSTEM INCLUDE FILES
#include <AknIndicatorContainer.h>
#include <AknIndicator.h>
#include "aknstatuspanedatasubscriber.h"
#include <eikspane.h>
#include <avkon.hrh>
#include <AknDef.h>

// USER INCLUDE FILES
#include "aknindicatordataobserver.h"
#include "aknstatuspanedata.h"
#include "AknIncallStatusBubble.h"

/** Value used to specify that an indicator is not shown. */
const TInt KEmpty = 0xFFFFFFFF;

// ============================ MEMBER FUNCTIONS =============================

// ---------------------------------------------------------------------------
// CAknIndicatorDataObserver::CAknIndicatorDataObserver
// C++ default constructor can NOT contain any code, that
// might leave.
// ---------------------------------------------------------------------------
//
CAknIndicatorDataObserver::CAknIndicatorDataObserver(
    CAknIndicatorContainer* aIndicatorPane )
	{
	iIndicatorPane = aIndicatorPane;
	iIndicatorPane->MopGetObject( iDataSubscriber );
	if ( iDataSubscriber )
		{
		iDataSubscriber->AddObserver( this );
		}

	iFirstUpdate = ETrue;
  	}


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknIndicatorDataObserver::~CAknIndicatorDataObserver()
	{
	if ( iDataSubscriber )
		{
		iDataSubscriber->RemoveObserver( this );
		}

    }


// ---------------------------------------------------------------------------
// CAknIndicatorDataObserver::HandleUpdateL
// Update state to UI control.
// ---------------------------------------------------------------------------
//
void CAknIndicatorDataObserver::HandleUpdateL(
    const TAknStatusPaneStateData& aData )
	{
	if ( !iDataSubscriber )
	    {
		return;
	    }

	TAknIndicatorState state = aData.iIndicatorState;

	TBool indicatorPaneIsInCurrentLayout = ETrue;

	// If this pane is not in current layout, no update.
	// Update happens when status pane layout is changed.
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
   	if ( !statusPane ||
   		 !statusPane->PaneCapabilities(
   		    TUid::Uid( EEikStatusPaneUidIndic ) ).IsInCurrentLayout() )
   		{
		indicatorPaneIsInCurrentLayout = EFalse;
   		}

    TBool updateAnimation =
    	( !iDataSubscriber->IsBackground() ||
    	  iDataSubscriber->RefreshLevel() > CAknStatusPaneDataSubscriber::ERefreshLevelMedium );

	// Incall bubble is shown when in foreground and in
	// the very first update (to avoid flicker).
    TBool showIncallBubble = !iDataSubscriber->IsBackground() || iFirstUpdate;

	TBool anyIndicatorChanged = EFalse;

	if ( indicatorPaneIsInCurrentLayout )
		{
		// If indicator does not yet exist, set its state
		// initially to "off" -> indicator gets created.
		for ( TInt j = 0; j < TAknIndicatorState::EMaxVisibleIndicators; j++ )
		    {
		    if ( state.visibleIndicators[j] != KEmpty &&
		    	 !iIndicatorPane->IndicatorExists(
		    	    TUid::Uid( state.visibleIndicators[j] ) ) )
		    	{
		    	iIndicatorPane->SetIndicatorState(
		    	    TUid::Uid( state.visibleIndicators[j] ),
		    	    MAknIndicator::EIndicatorOff,
		    	    EFalse );
		    	}
		    }

		TInt count = iIndicatorPane->iIndicators->Count();

		for ( TInt ii = 0; ii < count; ii++ )
		    {
		    CAknIndicator* indicator = iIndicatorPane->iIndicators->At( ii );
		    TInt indicState = indicator->IndicatorState();
		    TInt indicUid   = indicator->Uid().iUid;

		    TBool shownInCurrentLayoutMode = ( indicator->Priority() != -1 );

		    TBool found = EFalse;

		    for ( TInt jj = 0; jj < TAknIndicatorState::EMaxVisibleIndicators; jj++ )
		    	{
		    	if ( state.visibleIndicators[jj] == KEmpty )
		    		{
		    		break;
		    		}
			    else if ( state.visibleIndicators[jj] == indicUid )
		    		{
		    		found = ETrue;
			    	if ( state.visibleIndicatorStates[jj] != indicState &&
			    	     shownInCurrentLayoutMode )
			    		{
		           	    anyIndicatorChanged = ETrue;
						if ( state.visibleIndicatorStates[jj] == MAknIndicator::EIndicatorAnimate )
							{
							if ( updateAnimation )
								{
								// Update animations only in foreground (unless forced)
								indicator->SetIndicatorState( state.visibleIndicatorStates[jj] );
		        	        	indicator->SetAnimateState( iIndicatorPane->iSynchronizingValue );
								}
							else
								{
								// In background just set it on
							   	indicator->SetIndicatorState( MAknIndicator::EIndicatorOn );
								}

							}
						else
							{
							indicator->SetIndicatorState( state.visibleIndicatorStates[jj] );
							}
			    		}
		    		}
		    	}

			// If indicators was not in the list we assume its state to be OFF.
		    if ( !found )
		    	{
				if ( indicState != MAknIndicator::EIndicatorOff )
					{
					anyIndicatorChanged = ETrue;
					indicator->SetIndicatorState( MAknIndicator::EIndicatorOff );
					}
		    	}
		    }
		}

    if ( anyIndicatorChanged )
    	{
    	iIndicatorPane->PrioritizeIndicatorsL();
    	iIndicatorPane->SizeChanged();
		}


	// Incall bubble
	TInt modifiedFlags = state.iIncallBubbleFlags;

	if ( !showIncallBubble )
	    {
		modifiedFlags &= ~CIncallStatusBubble::ESBVisible; // Clear visible bit
	    }

	iIndicatorPane->SetIncallBubbleAllowedInIdle( state.iIncallBubbleAllowedInIdle );
	iIndicatorPane->SetIncallBubbleAllowedInUsual( state.iIncallBubbleAllowedInUsual );
	iIndicatorPane->SetIncallBubbleDisabled( state.iIncallBubbleDisabled );

	iIndicatorPane->SetIncallBubbleFlags( modifiedFlags );

    if ( anyIndicatorChanged || showIncallBubble )
    	{
    	iIndicatorPane->DrawDeferred();
		}

	iFirstUpdate = EFalse;
	}


//  End of File
