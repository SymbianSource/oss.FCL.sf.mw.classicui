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
* Description:  Internal Central Repository keys.
 *
*/


#ifndef AKNPHYSICSCRKEYS_H
#define AKNPHYSICSCRKEYS_H

const TUid KCRUidAknPhysicsSettings = { 0x20021192 };

/**
 * Mass of the view
 */
const TInt KViewMass( 0x00000001 );

/**
 * Gravity
 */
const TInt KGravity( 0x00000002 );

/**
 * Surface erp
 */
const TInt KSurfaceErp( 0x00000003 );

/**
 * Surface cfm
 */
const TInt KSurfaceCfm( 0x00000004 );

/**
 * Highlight timeout
 */
const TInt KHighlightTimeout( 0x00000005 );

/**
 * Drag treshold
 */
const TInt KDragTreshold( 0x00000006 );

/**
 * Frame delay
 */
const TInt KFrameDelay( 0x00000007 );

/**
 * Min frame interval
 */
const TInt KMinFrameInterval( 0x00000008 );

/**
 * Ode enabled
 */
const TInt KFeatureEnabled( 0x00000009 );

/**
 * Short list empty space
 */
const TInt KShortListEmptySpace( 0x0000000A );

/**
 * Long list empty space
 */
const TInt KLongListEmptySpace( 0x0000000B );

/**
 * Fps logging enabled
 */
const TInt KFpsLoggingEnabled( 0x0000000C );

#endif // AKNPHYSICSCRKEYS_H