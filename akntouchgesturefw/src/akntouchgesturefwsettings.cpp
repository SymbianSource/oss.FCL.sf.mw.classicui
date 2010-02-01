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
* Description:  Touch gesture framework settings provider.
*
*/

#include <centralrepository.h>

#include "akntouchgesturefwdefs.h"
#include "akntouchgesturefwsettings.h"
#include "akntouchgesturefwcrkeys.h"

using namespace AknTouchGestureFw;

/** Value for an unset parameter. */
const TInt KParamNotSet( -1 );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwSettings* CAknTouchGestureFwSettings::NewL()
    {
    CAknTouchGestureFwSettings* self = CAknTouchGestureFwSettings::NewLC();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwSettings* CAknTouchGestureFwSettings::NewLC()
    {
    CAknTouchGestureFwSettings* self
        = new ( ELeave ) CAknTouchGestureFwSettings();
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwSettings::~CAknTouchGestureFwSettings()
    {
    delete iListener;
    delete iCenRep;
    }


// ---------------------------------------------------------------------------
// Returns the flick buffer setting value.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwSettings::FlickBuffer() const
    {
    return iFlickBuffer;
    }


// ---------------------------------------------------------------------------
// Returns the long tap threshold setting value.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwSettings::LongTapThreshold() const
    {
    return iLongTapThreshold;
    }


// ---------------------------------------------------------------------------
// Returns the tap threshold setting value.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwSettings::TapThreshold() const
    {
    return iTapThreshold;
    }


// ---------------------------------------------------------------------------
// Returns the double tap maximum duration setting value.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwSettings::DoubleTapMaximumDuration() const
    {
    return iDoubleTapMaximumDuration;
    }


// ---------------------------------------------------------------------------
// Returns the drag threshold setting value.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwSettings::DragThreshold() const
    {
    return iDragThreshold;
    }


// ---------------------------------------------------------------------------
// Returns the flick speed threshold setting value.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwSettings::FlickSpeedThreshold() const
    {
    return iFlickSpeedThreshold;
    }


// ---------------------------------------------------------------------------
// Returns the flick detection time setting value.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwSettings::FlickDetectionTime() const
    {
    return iFlickDetectionTime;
    }


// ---------------------------------------------------------------------------
// Returns the flick change sensitivity setting value.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwSettings::FlickChangeSensitivity() const
    {
    return iFlickChangeSensitivity;
    }


// ---------------------------------------------------------------------------
// Returns pinch initial threshold setting value.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwSettings::PinchInitialThreshold() const
    {
    return iPinchInitialThreshold;
    }


// ---------------------------------------------------------------------------
// Returns pinch movement threshold setting value.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwSettings::PinchMovementThreshold() const
    {
    return iPinchMovementThreshold;
    }


// ---------------------------------------------------------------------------
// Returns pinch direction change sensitivity setting value.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwSettings::PinchDirectionChangeSensitivity() const
    {
    return iPinchDirectionChangeSensitivity;
    }


// ---------------------------------------------------------------------------
// Returns pinch direction reset sensitivity setting value.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwSettings::PinchDirectionResetSensitivity() const
    {
    return iPinchDirectionResetSensitivity;
    }

// ---------------------------------------------------------------------------
// Returns pinch dimension threshold.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwSettings::PinchDimensionThreshold() const
    {
    return iPinchDimensionThreshold;
    }

// ---------------------------------------------------------------------------
// Returns pinch maximum confirmation duration.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwSettings::PinchMaximumConfirmationDuration() const
    {
    return iPinchMaximumConfirmationDuration;
    }

// ---------------------------------------------------------------------------
// Called when the value of a touch gesture FW setting CenRep key changes
// to update the corresponding member variable.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwSettings::CenRepValueChanged( const TInt& aKey )
    {
    switch ( aKey )
        {
        case KFlickBuffer:
            {
            iCenRep->Get( KFlickBuffer, iFlickBuffer );
            break;
            }
        case KLongTapThreshold:
            {
            iCenRep->Get( KLongTapThreshold, iLongTapThreshold );
            break;
            }
        case KTapThreshold:
            {
            iCenRep->Get( KTapThreshold, iTapThreshold );
            break;
            }
        case KDoubleTapMaximumDuration:
            {
            iCenRep->Get( KDoubleTapMaximumDuration,
                          iDoubleTapMaximumDuration );
            break;
            }
        case KDragThreshold:
            {
            iCenRep->Get( KDragThreshold, iDragThreshold );
            break;
            }
        case KFlickSpeedThreshold:
            {
            iCenRep->Get( KFlickSpeedThreshold, iFlickSpeedThreshold );
            break;
            }
        case KFlickDetectionTime:
            {
            iCenRep->Get( KFlickDetectionTime, iFlickDetectionTime );
            break;
            }
        case KFlickDirectionChange:
            {
            iCenRep->Get( KFlickDirectionChange, iFlickChangeSensitivity );
            break;
            }
        case KPinchInitialThreshold:
		    {
            iCenRep->Get( KPinchInitialThreshold, iPinchInitialThreshold );
            break;
			}
        case KPinchMovementThreshold:
            {
            iCenRep->Get( KPinchMovementThreshold, iPinchMovementThreshold );
            break;
            }
        case KPinchDirectionChangeSensitivity:
            {
            iCenRep->Get( KPinchDirectionChangeSensitivity, 
                iPinchDirectionChangeSensitivity );
            break;
            }
        case KPinchDirectionResetSensitivity:
            {
            iCenRep->Get( KPinchDirectionResetSensitivity, 
                iPinchDirectionResetSensitivity );
            break;
            }
        case KPinchDimensionThreshold:
            {
            iCenRep->Get( KPinchDimensionThreshold, 
                iPinchDimensionThreshold );            
            break;
            }
        case KPinchMaximumConfirmationDuration:
            {
            iCenRep->Get( KPinchMaximumConfirmationDuration, 
                iPinchMaximumConfirmationDuration );            
            break;
            }
        default:
            {
            break;
            }
        }
    }


// ---------------------------------------------------------------------------
// Default C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwSettings::CAknTouchGestureFwSettings() :
    iCenRep( NULL ),
    iListener( NULL ),
    iFlickBuffer( KParamNotSet ),
    iLongTapThreshold( KParamNotSet ),
    iTapThreshold( KParamNotSet ),
    iDoubleTapMaximumDuration( KParamNotSet ),
    iDragThreshold( KParamNotSet ),
    iFlickSpeedThreshold( KParamNotSet ),
    iFlickDetectionTime( KParamNotSet ),
    iFlickChangeSensitivity( KParamNotSet ),
    iPinchInitialThreshold( KParamNotSet ),
    iPinchMovementThreshold( KParamNotSet ),
    iPinchDirectionChangeSensitivity( KParamNotSet ),
    iPinchDirectionResetSensitivity( KParamNotSet ),
    iPinchDimensionThreshold( KParamNotSet ),
    iPinchMaximumConfirmationDuration( KParamNotSet )
    {
    }


// ---------------------------------------------------------------------------
// Second-phase constructor.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwSettings::ConstructL()
    {
    TRAPD( err,
           iCenRep = CRepository::NewL( KCRUidAknTouchGestureFwSettings ) );
    if ( err )
        {
        SetDefaultValues( EFalse );
        return;
        }
    iListener = CAknTouchGestureFwCenRepListener::NewL( iCenRep, this );
    ReadValuesFromCenRep();
    if ( !ValuesAreSet() )
        {
        SetDefaultValues( ETrue );
        }
    }


// ---------------------------------------------------------------------------
// Reads the setting values from the central repository.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwSettings::ReadValuesFromCenRep()
    {
    iCenRep->Get( KFlickBuffer, iFlickBuffer );
    iCenRep->Get( KLongTapThreshold, iLongTapThreshold );
    iCenRep->Get( KTapThreshold, iTapThreshold );
    iCenRep->Get( KDoubleTapMaximumDuration, iDoubleTapMaximumDuration );
    iCenRep->Get( KDragThreshold, iDragThreshold );
    iCenRep->Get( KFlickSpeedThreshold, iFlickSpeedThreshold );
    iCenRep->Get( KFlickDetectionTime, iFlickDetectionTime );
    iCenRep->Get( KFlickDirectionChange, iFlickChangeSensitivity );
    iCenRep->Get( KPinchInitialThreshold, iPinchInitialThreshold );
    iCenRep->Get( KPinchMovementThreshold, iPinchMovementThreshold );
    iCenRep->Get( KPinchDirectionChangeSensitivity, 
        iPinchDirectionChangeSensitivity );
    iCenRep->Get( KPinchDirectionResetSensitivity, 
        iPinchDirectionResetSensitivity );
    iCenRep->Get( KPinchDimensionThreshold, 
        iPinchDimensionThreshold );
    iCenRep->Get( KPinchMaximumConfirmationDuration, 
        iPinchMaximumConfirmationDuration );
    }


// ---------------------------------------------------------------------------
// Sets the default values for the settings.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwSettings::SetDefaultValues( TBool aWriteToCenRep )
    {
    iFlickBuffer = KMaxBufferLength;
    iLongTapThreshold = KDefaultLongTapThreshold / KMicroSecondsInMilliSecond;
    iTapThreshold = KTapThreshold;
    iDoubleTapMaximumDuration =
        KDefaultMaxDoubleTapDuration / KMicroSecondsInMilliSecond;
    iDragThreshold = KDefaultDragThreshold;
    iFlickSpeedThreshold = KDefaultFlickSpeedThreshold;
    iFlickDetectionTime =
        KDefaultFlickDetectionTime / KMicroSecondsInMilliSecond;
    iFlickChangeSensitivity = KDefaultDirectionChangeSensitivity;
    iPinchInitialThreshold = KDefaultPinchInitialThreshold;
    iPinchMovementThreshold = KDefaultPinchMovementThreshold;
    iPinchDirectionChangeSensitivity = KDefaultPinchDirectionChangeSensitivity;
    iPinchDirectionResetSensitivity = KDefaultPinchDirectionResetSensitivity;
    iPinchDimensionThreshold = KDefaultPinchDimensionThreshold;
    iPinchMaximumConfirmationDuration = 
        KDefaultPinchMaximumConfirmationDuration;
    
    if ( aWriteToCenRep )
        {
        if ( !iCenRep )
            {
            TRAPD( err,
                iCenRep = CRepository::NewL(
                        KCRUidAknTouchGestureFwSettings ) );
            if ( err )
                {
                return;
                }
            }
        iCenRep->Set( KFlickBuffer, iFlickBuffer );
        iCenRep->Set( KLongTapThreshold, iLongTapThreshold );
        iCenRep->Set( KTapThreshold, iTapThreshold );
        iCenRep->Set(
                KDoubleTapMaximumDuration, iDoubleTapMaximumDuration );
        iCenRep->Set( KDragThreshold, iDragThreshold );
        iCenRep->Set( KFlickSpeedThreshold, iFlickSpeedThreshold );
        iCenRep->Set( KFlickDetectionTime, iFlickDetectionTime );
        iCenRep->Set( KFlickDirectionChange, iFlickChangeSensitivity );
        iCenRep->Set( KPinchInitialThreshold, iPinchInitialThreshold );
        iCenRep->Set( KPinchMovementThreshold, iPinchMovementThreshold );
        iCenRep->Set( KPinchDirectionChangeSensitivity, 
            iPinchDirectionChangeSensitivity );
        iCenRep->Set( KPinchDirectionResetSensitivity, 
            iPinchDirectionResetSensitivity );
        iCenRep->Set( KPinchDimensionThreshold, 
            iPinchDimensionThreshold );
        iCenRep->Set( KPinchMaximumConfirmationDuration, 
            iPinchMaximumConfirmationDuration );
        }
    }


// ---------------------------------------------------------------------------
// Checks if the setting values have been set.
// ---------------------------------------------------------------------------
//
TBool CAknTouchGestureFwSettings::ValuesAreSet() const
    {
    TBool areSet( ETrue );
    if ( iFlickBuffer == KParamNotSet
        || iLongTapThreshold == KParamNotSet
        || iTapThreshold == KParamNotSet
        || iDoubleTapMaximumDuration == KParamNotSet
        || iDragThreshold == KParamNotSet
        || iFlickSpeedThreshold == KParamNotSet
        || iFlickDetectionTime == KParamNotSet
        || iFlickChangeSensitivity == KParamNotSet
        || iPinchInitialThreshold == KParamNotSet 
        || iPinchMovementThreshold == KParamNotSet
        || iPinchDirectionChangeSensitivity == KParamNotSet
        || iPinchDirectionResetSensitivity == KParamNotSet 
        || iPinchDimensionThreshold == KParamNotSet
        || iPinchMaximumConfirmationDuration == KParamNotSet )
        {
        areSet = EFalse;
        }

    return areSet;
    }

// End of File
