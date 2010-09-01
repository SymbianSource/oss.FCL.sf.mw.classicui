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
* Description: Touch gesture fw internal central repository keys.
*
*/


#ifndef AKNTOUCHGESTUREFWCRKEYS_H
#define AKNTOUCHGESTUREFWCRKEYS_H

/**
 * UID for the touch gesture framework central repository.
 */
const TUid KCRUidAknTouchGestureFwSettings = { 0x2002676F };

/**
 * Flick point buffer.
 */
const TInt KFlickBuffer( 0x00000001 );

/**
 * Long tap threshold.
 */
const TInt KLongTapThreshold( 0x00000002 );

/**
 * Tap threshold.
 */
const TInt KTapThreshold( 0x00000003 );

/**
 * Double tap maximum duration.
 */
const TInt KDoubleTapMaximumDuration( 0x00000004 );

/**
 * Drag threshold.
 */
const TInt KDragThreshold( 0x00000005 );

/**
 * Flick speed threshold.
 */
const TInt KFlickSpeedThreshold( 0x00000006 );

/**
 * Flick direction change sensitivity.
 */
const TInt KFlickDirectionChange( 0x00000007 );

/**
 * Flick detection time.
 */
const TInt KFlickDetectionTime( 0x00000008 );

/**
 * Pinch initial threshold.
 */
const TInt KPinchInitialThreshold( 0x00000009 );

/**
 * Pinch movement threshold.
 */
const TInt KPinchMovementThreshold( 0x0000000A );

/**
 * Pinch direction change sensitivity.
 */
const TInt KPinchDirectionChangeSensitivity( 0x0000000C );

/**
 * Pinch direction reset sensitivity.
 */
const TInt KPinchDirectionResetSensitivity( 0x0000000D );

/**
 * Pinch dimension threshold. If bounding rect width/height
 * is below this variable limit, then it is considered to
 * be inaccurate.
 */
const TInt KPinchDimensionThreshold( 0x0000000E );

/**
 * Pinch duration threshold. If pinch recognizer has
 * determined pinch to occur & we get confirmation within
 * duration specified in this variable, then that pinch
 * event is really sent.
 */
const TInt KPinchMaximumConfirmationDuration( 0x0000000F );

#endif // AKNTOUCHGESTUREFWCRKEYS_H
