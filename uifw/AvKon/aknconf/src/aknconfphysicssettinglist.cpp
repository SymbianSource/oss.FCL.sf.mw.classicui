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
* Description:  
 *
*/


// INCLUDE FILES
#include <aknconfphysics.rsg>
#include <akntextsettingpage.h>
#include <centralrepository.h>
#include <aknphysicscrkeys.h>

#include "aknconfsettingitem.h"
#include "aknconfphysicssettinglist.h"
#include "aknconf.hrh"

const TUid KPhysicsCenRepUid( KCRUidAknPhysicsSettings );
const TInt KPhysicsCenRepMassKey( KViewMass );
const TInt KPhysicsCenRepGravityKey( KGravity );
const TInt KPhysicsCenRepSurfaceSoftErpKey( KSurfaceErp );
const TInt KPhysicsCenRepSurfaceSoftCfmKey( KSurfaceCfm );
const TInt KPhysicsCenRepHighlightTimeoutKey( KHighlightTimeout );
const TInt KPhysicsCenRepDragThresholdKey( KDragTreshold );
const TInt KPhysicsCenRepFrameDelay( KFrameDelay );
const TInt KPhysicsCenRepMinFrameInterval( KMinFrameInterval );
const TInt KPhysicsCenRepFeatureEnabledKey( KFeatureEnabled );
const TInt KPhysicsCenRepFpsLoggingEnabledKey( KFpsLoggingEnabled );

_LIT( KResourceFile, "\\resource\\apps\\aknconfphysics.rsc" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknConfPhysicsSettingList::NewL()
// -----------------------------------------------------------------------------
//
CAknConfPhysicsSettingList* CAknConfPhysicsSettingList::NewL()
    {
    CAknConfPhysicsSettingList* self = new ( ELeave ) CAknConfPhysicsSettingList();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }


// -----------------------------------------------------------------------------
// CAknConfPhysicsSettingList::~CAknConfPhysicsSettingList()
// -----------------------------------------------------------------------------
//
CAknConfPhysicsSettingList::~CAknConfPhysicsSettingList()
    {
    }

// -----------------------------------------------------------------------------
// CAknConfPhysicsSettingList::ResetValues()
// -----------------------------------------------------------------------------
//
void CAknConfPhysicsSettingList::ResetValues()
    {
    if ( iCenRep )
        {
        iCenRep->Reset();
        TInt cenRepKey( -1 );
        ValueFromCenRep( EAknConfPhysicsSettingMass, cenRepKey );
        ValueFromCenRep( EAknConfPhysicsSettingGravity, cenRepKey );
        ValueFromCenRep( EAknConfPhysicsSettingSurfaceSoftErp, cenRepKey );
        ValueFromCenRep( EAknConfPhysicsSettingSurfaceSoftCfm, cenRepKey );
        ValueFromCenRep( EAknConfPhysicsSettingHighlightTimeout, cenRepKey );
        ValueFromCenRep( EAknConfPhysicsSettingDragThreshold, cenRepKey );
        ValueFromCenRep( EAknConfPhysicsSettingFrameDelay, cenRepKey );
        ValueFromCenRep( EAknConfPhysicsSettingMinFrameInterval, cenRepKey );
        ValueFromCenRep( EAknConfPhysicsSettingFeatureEnabled, cenRepKey );
        ValueFromCenRep( EAknConfPhysicsSettingShortListEmptySpace, cenRepKey );
        ValueFromCenRep( EAknConfPhysicsSettingLongListEmptySpace, cenRepKey );
        ValueFromCenRep( EAknConfPhysicsSettingFpsLoggingEnabled, cenRepKey );
        TRAP_IGNORE( LoadSettingsL() );
        DrawDeferred();
        }
    }


// -----------------------------------------------------------------------------
// CAknConfPhysicsSettingList::CreateSettingItemL()
// -----------------------------------------------------------------------------
//
CAknSettingItem* CAknConfPhysicsSettingList::CreateSettingItemL( TInt aIdentifier )
    {
    if ( aIdentifier != EAknConfPhysicsSettingShortListEmptySpace
            && aIdentifier != EAknConfPhysicsSettingLongListEmptySpace
            && aIdentifier != EAknConfPhysicsSettingFeatureEnabled
            && aIdentifier != EAknConfPhysicsSettingFpsLoggingEnabled )
        {
        return CAknConfSettingList::CreateSettingItemL( aIdentifier );
        }
    CAknSettingItem* settingItem = NULL;
    TInt cenRepKey( 0 );

    TInt* settingValue( ValueFromCenRep( aIdentifier, cenRepKey ) );

    if ( aIdentifier == EAknConfPhysicsSettingShortListEmptySpace
        || aIdentifier == EAknConfPhysicsSettingLongListEmptySpace )
        {
        settingItem = 
            new ( ELeave ) CAknConfSliderSettingItem( 
                this, *settingValue, aIdentifier, cenRepKey );
        }
    else if ( aIdentifier == EAknConfPhysicsSettingFeatureEnabled
        || aIdentifier == EAknConfPhysicsSettingFpsLoggingEnabled )
        {
        settingItem 
            =  new ( ELeave ) CAknConfBinarySettingItem( 
                this, *settingValue, aIdentifier, cenRepKey );
        }
    return settingItem;
    }


// -----------------------------------------------------------------------------
// CAknConfPhysicsSettingList::CAknConfPhysicsSettingList()
// -----------------------------------------------------------------------------
//
CAknConfPhysicsSettingList::CAknConfPhysicsSettingList()
    :
    CAknConfSettingList(),
    iMass( 0 ),
    iGravity( 0 ),
    iSurfaceSoftErp( 0 ),
    iSurfaceSoftCfm( 0 ),
    iHighlightTimeout( 0 ),
    iDragThreshold( 0 ),
    iFrameDelay( 0 ),
    iMinFrameInterval( 0 ),
    iShortListEmptySpace( 0 ),
    iLongListEmptySpace( 0 )
    {
    }


// -----------------------------------------------------------------------------
// CAknConfPhysicsSettingList::ConstructL()
// -----------------------------------------------------------------------------
//
void CAknConfPhysicsSettingList::ConstructL()
    {
    CAknConfSettingList::ConstructL( KPhysicsCenRepUid, KResourceFile );
    CAknConfSettingList::ConstructFromResourceL( R_AKNCONF_PHYSICS_SETTINGITEMLIST );
    }


// -----------------------------------------------------------------------------
// CAknConfPhysicsSettingList::DataValuePointer()
// -----------------------------------------------------------------------------
//
TInt* CAknConfPhysicsSettingList::DataValuePointer( const TInt& aId, TInt& aCenRepKey )
    {
    TInt* valuePtr( NULL );
    switch ( aId )
        {
        case EAknConfPhysicsSettingMass:
            valuePtr = &iMass;
            aCenRepKey = KPhysicsCenRepMassKey;
            break;
        case EAknConfPhysicsSettingGravity:
            valuePtr = &iGravity;
            aCenRepKey = KPhysicsCenRepGravityKey;
            break;
        case EAknConfPhysicsSettingSurfaceSoftErp:
            valuePtr = &iSurfaceSoftErp;
            aCenRepKey = KPhysicsCenRepSurfaceSoftErpKey;
            break;
        case EAknConfPhysicsSettingSurfaceSoftCfm:
            valuePtr = &iSurfaceSoftCfm;
            aCenRepKey = KPhysicsCenRepSurfaceSoftCfmKey;
            break;
        case EAknConfPhysicsSettingHighlightTimeout:
            valuePtr = &iHighlightTimeout;
            aCenRepKey = KPhysicsCenRepHighlightTimeoutKey;
            break;
        case EAknConfPhysicsSettingDragThreshold:
            valuePtr = &iDragThreshold;
            aCenRepKey = KPhysicsCenRepDragThresholdKey;
            break;
        case EAknConfPhysicsSettingFrameDelay:
            valuePtr = &iFrameDelay;
            aCenRepKey = KPhysicsCenRepFrameDelay;
            break;   
        case EAknConfPhysicsSettingMinFrameInterval:
            valuePtr = &iMinFrameInterval;
            aCenRepKey = KPhysicsCenRepMinFrameInterval;
            break;   
        case EAknConfPhysicsSettingFeatureEnabled:
            valuePtr = &iFeatureEnabled;
            aCenRepKey = KPhysicsCenRepFeatureEnabledKey;
            break;
        case EAknConfPhysicsSettingShortListEmptySpace:
            valuePtr = &iShortListEmptySpace;
            aCenRepKey = KShortListEmptySpace;
            break;
        case EAknConfPhysicsSettingLongListEmptySpace:
            valuePtr = &iLongListEmptySpace;
            aCenRepKey = KLongListEmptySpace;
            break;
        case EAknConfPhysicsSettingFpsLoggingEnabled:
            valuePtr = &iFpsLoggingEnabled;
            aCenRepKey = KPhysicsCenRepFpsLoggingEnabledKey;
            break;
        default:
            break;
        }
    return valuePtr;
    }


// -----------------------------------------------------------------------------
// CAknConfPhysicsSettingList::ValueFromCenRep()
// -----------------------------------------------------------------------------
//
TInt* CAknConfPhysicsSettingList::ValueFromCenRep( const TInt& aId, 
                                            TInt& aCenRepKey )
    {
    aCenRepKey = 0;
    TInt* settingValue( DataValuePointer( aId, aCenRepKey ) );
    if ( !settingValue || !aCenRepKey )
        {
        return NULL;
        }

    TInt value( -1 );
    if ( iCenRep )
        {
        iCenRep->Get( aCenRepKey, value );
        }
    *settingValue = value;
    return settingValue;
    }
// End of File
