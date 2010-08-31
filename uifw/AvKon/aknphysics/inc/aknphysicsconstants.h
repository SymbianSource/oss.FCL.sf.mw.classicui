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
* Description:  AknPhysics constant definitions
*
*/


#ifndef AKNPHYSICSCONSTANTS_H
#define AKNPHYSICSCONSTANTS_H

// Physics Constants
const TInt KDefaultFriction( 10 );
const TInt KFps( 50 ); // desired framerate
const TInt KPhysicsTime( 1000000/KFps ); // timer value
const TInt KPhysicsMinTime( 17000 ); // ~1000000/(2*KFps);
const TInt KAknHighResMinWait( 500 ); // minimum wait time between callbacks
const TInt KAknHighResMaxWait( 100000 ); // maximum wait time between callbacks
const TInt KMaxContacts( 2 ); // max amount of contacts with 2 objects
const TInt KZDepth( 1000 ); // Just something
const TInt KSwipeDuration( 800000 ); // 800ms
const TReal KStepFactor( .00000001 ); // used in drag calculations
const TReal KErpFactor( 0.5 );
const TReal KCfmFactor( 0.001 );
const TReal KCfmSoftFactor( .01 );
const TReal KBounceFactor( .001 );
const TInt KFlickMaxDuration( 500000 );

#endif // AKNPHYSICSCONSTANTS_H
