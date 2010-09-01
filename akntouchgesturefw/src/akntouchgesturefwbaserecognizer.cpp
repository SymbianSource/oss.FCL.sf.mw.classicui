/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Base class for touch gesture recognizers.
*
*/

#include "akntouchgesturefwdefs.h"
#include "akntouchgesturefwrecognitionengine.h"
#include "akntouchgesturefwbaserecognizer.h"
#include "akntouchgesturefwsettings.h"

using namespace AknTouchGestureFw;

// ---------------------------------------------------------------------------
// Checks if the recognizer is currently enabled.
// ---------------------------------------------------------------------------
//
TBool CAknTouchGestureFwBaseRecognizer::Enabled() const
    {
    return iEnabled;
    }


// ---------------------------------------------------------------------------
// Sets the recognizer enabled or disabled.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwBaseRecognizer::SetEnabled( TBool aEnable )
    {
    CancelRecognizing();
    iEnabled = aEnable;
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwBaseRecognizer::CAknTouchGestureFwBaseRecognizer(
    CAknTouchGestureFwRecognitionEngine& aEngine )
    : iEngine( aEngine ),
      iEnabled( EFalse ),
      iGestureTypesForTactile( 0 ),
      iGestureTypesForAudio( 0 )
    {
    }


// ---------------------------------------------------------------------------
// Sends a gesture event to the observer.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwBaseRecognizer::SendGestureEventL(
        MAknTouchGestureFwEvent& aEvent )
    {
    iEngine.NotifyObserverL( aEvent );
    }


// ---------------------------------------------------------------------------
// Returns the framework settings provider.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwSettings& CAknTouchGestureFwBaseRecognizer::Settings() const
    {
    return iEngine.Settings();
    }


// ---------------------------------------------------------------------------
// Returns the value of the drag threshold setting.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwBaseRecognizer::DragThreshold() const
    {
    return Settings().DragThreshold();
    }


// -----------------------------------------------------------------------------
// CAknTouchGestureFwBaseRecognizer::ImmediateFeedback
// -----------------------------------------------------------------------------
//
void CAknTouchGestureFwBaseRecognizer::ImmediateFeedback(
    TTouchLogicalFeedback aLogicalFeedback,
    TTouchFeedbackType aFeedbackType )
    {
    iEngine.ImmediateFeedback( aLogicalFeedback, aFeedbackType );
    }


// -----------------------------------------------------------------------------
// CAknTouchGestureFwBaseRecognizer::StartContinuousFeedback
// -----------------------------------------------------------------------------
//
void CAknTouchGestureFwBaseRecognizer::StartContinuousFeedback(
    TTouchContinuousFeedback aType,
    TInt aIntensity,
    TTimeIntervalMicroSeconds32 aTimeout )
    {
    iEngine.StartContinuousFeedback( aType, aIntensity, aTimeout );
    }


// -----------------------------------------------------------------------------
// CAknTouchGestureFwBaseRecognizer::ModifyContinuousFeedback
// -----------------------------------------------------------------------------
//
void CAknTouchGestureFwBaseRecognizer::ModifyContinuousFeedback(
    TInt aIntensity )
    {
    iEngine.ModifyContinuousFeedback( aIntensity );
    }



// -----------------------------------------------------------------------------
// CAknTouchGestureFwBaseRecognizer::StopContinuousFeedback
// -----------------------------------------------------------------------------
//
void CAknTouchGestureFwBaseRecognizer::StopContinuousFeedback()
    {
    iEngine.StopContinuousFeedback();
    }


// ---------------------------------------------------------------------------
// Sets gesture types which generate tactile and audio feedback.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwBaseRecognizer::SetFeedbackForTypesL(
    TUint aGestureTypesForTactile,
    TUint aGestureTypesForAudio )
    {
    iGestureTypesForTactile = aGestureTypesForTactile;
    iGestureTypesForAudio = aGestureTypesForAudio;
    }


// ---------------------------------------------------------------------------
// Returns feedback types of requested gesture type.
// ---------------------------------------------------------------------------
//
TTouchFeedbackType CAknTouchGestureFwBaseRecognizer::FeedbackType(
    TAknTouchGestureFwType aGestureType )
    {
    TUint feedbackType( 0 );
    if ( iGestureTypesForTactile & aGestureType )
        {
        feedbackType |= ETouchFeedbackVibra;
        }
    if ( iGestureTypesForAudio & aGestureType )
        {
        feedbackType |= ETouchFeedbackAudio;         
        }
    return TTouchFeedbackType( feedbackType );
    }

// End of File
