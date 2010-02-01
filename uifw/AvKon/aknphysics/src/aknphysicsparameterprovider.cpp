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
* Description:  ODE parameter provider
*
*/


#include <centralrepository.h>
#include <e32debug.h>
#include <AknUtils.h>

#include "aknphysicsparameterprovider.h"
#include <aknphysicscrkeys.h>

const TInt KParamNotSet( -1 );
const TInt KDefaultMass( 10 );
const TInt KDefaultGravity( 10 );
const TInt KDefaultSurfaceErp( 20 );
const TInt KDefaultSurfaceCfm( 20 );
const TInt KDefaultHighlightTimeout( 20 );
const TInt KDefaultDragThreshold( 200 );
const TInt KDefaultFrameDelay( 17 );
const TInt KDefaultMinFrameInterval( 60 );
const TBool KDefaultFeatureEnabled( ETrue );
const TInt KDefaultShortListEmptySpace( 33 );
const TInt KDefaultLongListEmptySpace( 33 );
const TBool KDefaultFpsLoggingEnabled( EFalse );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::NewL
// ---------------------------------------------------------------------------
//
CAknPhysicsParameterProvider* CAknPhysicsParameterProvider::NewL()
    {
    CAknPhysicsParameterProvider* self = CAknPhysicsParameterProvider::NewLC();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::NewLC
// ---------------------------------------------------------------------------
//
CAknPhysicsParameterProvider* CAknPhysicsParameterProvider::NewLC()
    {
    CAknPhysicsParameterProvider* self 
        = new ( ELeave ) CAknPhysicsParameterProvider();
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::~CAknPhysicsParameterProvider
// ---------------------------------------------------------------------------
//
CAknPhysicsParameterProvider::~CAknPhysicsParameterProvider()
    {
    delete iListener;
    delete iCenRep;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::ViewMass
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsParameterProvider::ViewMass() const
    {
    return iViewMass;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::Gravity
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsParameterProvider::Gravity() const
    {
    return iGravity;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::SurfaceErp
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsParameterProvider::SurfaceErp() const
    {
    return iSurfaceErp;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::SurfaceCfm
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsParameterProvider::SurfaceCfm() const
    {
    return iSurfaceCfm;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::HighlightTimeout
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsParameterProvider::HighlightTimeout() const
    {
    return iHighlightTimeout;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::DragTreshold
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsParameterProvider::DragThreshold() const
    {
    return iDragThreshold;
    }

// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::FrameDelay
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsParameterProvider::FrameDelay() const
    {
    return iFrameDelay;
    }

// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::MinFrameInterval
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsParameterProvider::MinFrameInterval() const
    {
    return iMinFrameInterval;
    }

// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::FeatureEnabled
// ---------------------------------------------------------------------------
//
TBool CAknPhysicsParameterProvider::FeatureEnabled()
    {
	if ( AknLayoutUtils::PenEnabled() )
		{
	    CRepository* cenRep = NULL;
    	TRAPD( err, cenRep = CRepository::NewL( KCRUidAknPhysicsSettings ) )
	    if( err || !cenRep )
    	    {
        	return KDefaultFeatureEnabled;
	        }
    	TBool featureEnabled( KDefaultFeatureEnabled );
    	cenRep->Get( KFeatureEnabled, featureEnabled );
    	delete cenRep;
    	return featureEnabled;
		}
	else
		{
		return EFalse;
		}
    }


// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::ShortListEmptySpace
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsParameterProvider::ShortListEmptySpace() const
    {
    return iShortListEmptySpace;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::LongListEmptySpace
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsParameterProvider::LongListEmptySpace() const
    {
    return iLongListEmptySpace;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::FpsLoggingEnabled
// ---------------------------------------------------------------------------
//
TBool CAknPhysicsParameterProvider::FpsLoggingEnabled() const
    {
    return iFpsLoggingEnabled;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::CenRepValueChanged
// ---------------------------------------------------------------------------
//
void CAknPhysicsParameterProvider::CenRepValueChanged( const TInt& aKey )
    {
    if ( !iCenRep )
        {
        return;
        }
    switch ( aKey )
        {
        case KViewMass:
            iCenRep->Get( KViewMass, iViewMass );
            break;
        case KGravity:
            iCenRep->Get( KGravity, iGravity );
            break;
        case KSurfaceErp:
            iCenRep->Get( KSurfaceErp, iSurfaceErp );
            break;
        case KSurfaceCfm:
            iCenRep->Get( KSurfaceCfm, iSurfaceCfm );
            break;
        case KHighlightTimeout:
            iCenRep->Get( KHighlightTimeout, iHighlightTimeout );
            break;
        case KDragTreshold:
            iCenRep->Get( KDragTreshold, iDragThreshold );
            break;
        case KFrameDelay:
            iCenRep->Get( KFrameDelay, iFrameDelay );
            break;    
		case KMinFrameInterval:
            iCenRep->Get( KMinFrameInterval, iMinFrameInterval );
            break;	
        case KShortListEmptySpace:
            iCenRep->Get( KShortListEmptySpace, iShortListEmptySpace );
            break;
        case KLongListEmptySpace:
            iCenRep->Get( KLongListEmptySpace, iLongListEmptySpace );
            break;
        case KFpsLoggingEnabled:
            iCenRep->Get( KFpsLoggingEnabled, iFpsLoggingEnabled );
            break;
        default:
            break;
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::CAknPhysicsParameterProvider
// ---------------------------------------------------------------------------
//
CAknPhysicsParameterProvider::CAknPhysicsParameterProvider()
    : 
    iViewMass( KParamNotSet ),
    iGravity( KParamNotSet ),
    iSurfaceErp( KParamNotSet ),
    iSurfaceCfm( KParamNotSet ),
    iHighlightTimeout( KParamNotSet ),
    iDragThreshold( KParamNotSet ),
    iFrameDelay( KParamNotSet ),
	iMinFrameInterval( KParamNotSet ),
    iShortListEmptySpace( KParamNotSet ),
    iLongListEmptySpace( KParamNotSet ),
    iFpsLoggingEnabled( EFalse ),
    iListener( NULL )
    {
    }


// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::ConstructL
// ---------------------------------------------------------------------------
//
void CAknPhysicsParameterProvider::ConstructL()
    {
    if ( !iCenRep )
        {
        TRAPD( err, iCenRep = CRepository::NewL( KCRUidAknPhysicsSettings ) );
        if( err )
            {
            SetDefaultValues( EFalse );
            return;
            }
        }
    iListener = CAknPhysicsCenRepListener::NewL( iCenRep, this );
    ReadValuesFromCenRepL();
    if ( !ValuesAreSet() )
        {
        SetDefaultValues( ETrue );
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::ReadValuesFromCenRepL
// ---------------------------------------------------------------------------
//
void CAknPhysicsParameterProvider::ReadValuesFromCenRepL()
    {
    iCenRep->Get( KViewMass, iViewMass );
    iCenRep->Get( KGravity, iGravity );
    iCenRep->Get( KSurfaceErp, iSurfaceErp );
    iCenRep->Get( KSurfaceCfm, iSurfaceCfm );
    iCenRep->Get( KHighlightTimeout, iHighlightTimeout );
    iCenRep->Get( KDragTreshold, iDragThreshold );
    iCenRep->Get( KFrameDelay, iFrameDelay );
	iCenRep->Get( KMinFrameInterval, iMinFrameInterval );
    iCenRep->Get( KShortListEmptySpace, iShortListEmptySpace );
    iCenRep->Get( KLongListEmptySpace, iLongListEmptySpace );
    iCenRep->Get( KFpsLoggingEnabled, iFpsLoggingEnabled );
    }


// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::SetDefaultValues
// ---------------------------------------------------------------------------
//
void CAknPhysicsParameterProvider::SetDefaultValues( TBool aWriteToCenRep )
    {
    iViewMass = KDefaultMass;
    iGravity = KDefaultGravity;
    iSurfaceErp = KDefaultSurfaceErp;
    iSurfaceCfm = KDefaultSurfaceCfm;
    iHighlightTimeout = KDefaultHighlightTimeout;
    iDragThreshold = KDefaultDragThreshold;
    iFrameDelay = KDefaultFrameDelay; 
	iMinFrameInterval = KDefaultMinFrameInterval;
	iFpsLoggingEnabled = EFalse;
	
    if ( aWriteToCenRep )
        {
        if ( !iCenRep )
            {
            TRAPD( err, 
                iCenRep = CRepository::NewL( KCRUidAknPhysicsSettings ) );
            if ( err )
                {
                return;
                }
            }
        iCenRep->Set( KViewMass, KDefaultMass );
        iCenRep->Set( KGravity, KDefaultGravity );
        iCenRep->Set( KSurfaceErp, KDefaultSurfaceErp );
        iCenRep->Set( KSurfaceCfm, KDefaultSurfaceCfm );
        iCenRep->Set( KHighlightTimeout, KDefaultHighlightTimeout );
        iCenRep->Set( KDragTreshold, KDefaultDragThreshold );
        iCenRep->Set( KFrameDelay, KDefaultFrameDelay );
		iCenRep->Set( KMinFrameInterval, KDefaultMinFrameInterval );
        iCenRep->Set( KFeatureEnabled, KDefaultFeatureEnabled );
        iCenRep->Set( KShortListEmptySpace, KDefaultShortListEmptySpace );
        iCenRep->Set( KLongListEmptySpace, KDefaultLongListEmptySpace );
        iCenRep->Set( KFpsLoggingEnabled, KDefaultFpsLoggingEnabled );
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysicsParameterProvider::ValuesAreSet
// ---------------------------------------------------------------------------
//
TBool CAknPhysicsParameterProvider::ValuesAreSet()
    {
    if ( iViewMass == KParamNotSet
        || iGravity == KParamNotSet
        || iSurfaceErp == KParamNotSet
        || iSurfaceCfm == KParamNotSet
        || iHighlightTimeout == KParamNotSet
        || iDragThreshold == KParamNotSet
        || iShortListEmptySpace == KParamNotSet
        || iLongListEmptySpace == KParamNotSet
		|| iFrameDelay == KParamNotSet 
        || iMinFrameInterval == KParamNotSet )
        {
        return EFalse;
        }
    return ETrue;
    }
