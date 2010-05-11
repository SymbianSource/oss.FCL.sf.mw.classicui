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
* Description:  Touch gesture framework constant definitions.
*
*/

#ifndef AKNTOUCHGESTUREFWDEFS_H
#define AKNTOUCHGESTUREFWDEFS_H

#include <e32std.h>

namespace AknTouchGestureFw
{

/// UID for testing features enabling
const TUint KAknTouchGestureFwTestingFeature( 0x20026806 );

/// Default threshold value for Long Tap (in microseconds).
const TInt KDefaultLongTapThreshold = 800000;

/// Default value for Long Tap initial delay (in microseconds).
const TInt KDefaultLongTapInitialDelay = 200000;

/// Default value for maximum long tap intensity.
const TInt KDefaultMaxLongTapIntensity = 100;

/// Default value for maximum long tap intensity steps.
const TInt KDefaultMaxLongTapIntensitySteps = 6;

/// Maximum time duration between two taps to recognize
/// a double tap (in microseconds).
const TInt KDefaultMaxDoubleTapDuration = 400000;

/// Pixel threshold value used for deciding if pointer movement is a tap.
/// This value should be less than KDragThreshold.
const TInt KTapThreshold = 20;

/// Pixel threshold value used for deciding if pointer has been dragged.
const TInt KDefaultDragThreshold = 40;

/// Initial threshold for pinch. This is used when both pointers are 
/// just set down.
const TInt KDefaultPinchInitialThreshold = 20;

/// Movement threshold for pinch. This is used after initial threshold
/// has been exceeded.
const TInt KDefaultPinchMovementThreshold = 10;

/// Direction change sensitivity for pinch.
const TInt KDefaultPinchDirectionChangeSensitivity = 2;

/// Direction reset sensitivity for pinch.
const TInt KDefaultPinchDirectionResetSensitivity = 3;

/// If height or width is below this value, then that dimension
/// is ignored.
const TInt KDefaultPinchDimensionThreshold = 20;

/// Maximum confirmation duration for pinch.
const TInt KDefaultPinchMaximumConfirmationDuration = 250000;

/// Flick speed threshold value (in pixels per sec).
const TInt KDefaultFlickSpeedThreshold = 100;

/// Flick detection time (in microseconds).
const TInt KDefaultFlickDetectionTime = 500000;

/// Direction change sensitivity.
const TInt KDefaultDirectionChangeSensitivity = 2;

/// Max number of points stored to array.
const TInt KMaxBufferLength = 100;

/// One second in microseconds.
const TInt KMicroSecondsInSecond = 1000000;

/// One millisecond in microseconds.
const TInt KMicroSecondsInMilliSecond = 1000;

/// Value used to indicate invalid pointer number.
const TInt KInvalidPointerNumber = -1;

/// Epsilon values that satisfy formula Abs(x) < KEpsilon are considered
/// to be zero.
const TReal KEpsilon = 0.00001f;

/// Value used to represent all gesture types in gesture group
const TUint32 KAknTouchGestureFwAllGestureTypes = 0x7fffffff;

/// Default feedback intensity.
const TInt KAknTouchGestureFwFeedbackIntensity = 100;

/// Pinch feedback timeout (in microseconds).
const TInt KAknTouchGestureFwPinchFeedbackTimeout = 200000;

/// Drag feedback timeout (in microseconds).
const TInt KAknTouchGestureFwDragFeedbackTimeout = 200000;

} // namespace AknTouchGestureFw

#endif // AKNTOUCHGESTUREFWDEFS_H
