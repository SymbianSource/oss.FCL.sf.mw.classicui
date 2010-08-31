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

//#include "aknconfsettingitem.h"
#include "aknconfgesturesettinglist.h"
//#include "aknconf.hrh"
//#include "akntouchgesturefwcrkeys.h"

//_LIT( KResourceFile, "\\resource\\apps\\aknconfgesture.rsc" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknConfGestureSettingList::NewL()
// -----------------------------------------------------------------------------
//
CAknConfGestureSettingList* CAknConfGestureSettingList::NewL()
    {
    CAknConfGestureSettingList* self = new ( ELeave ) CAknConfGestureSettingList();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }


// -----------------------------------------------------------------------------
// CAknConfGestureSettingList::~CAknConfGestureSettingList()
// -----------------------------------------------------------------------------
//
CAknConfGestureSettingList::~CAknConfGestureSettingList()
    {
    }


// -----------------------------------------------------------------------------
// CAknConfGestureSettingList::ResetValues()
// -----------------------------------------------------------------------------
//
void CAknConfGestureSettingList::ResetValues()
    {/*
    if ( iCenRep )
        {
        iCenRep->Reset();
        TInt cenRepKey( -1 );
        ValueFromCenRep( EAknConfGestureSettingFlickBuffer, cenRepKey );
        ValueFromCenRep( EAknConfGestureSettingTapThreshold, cenRepKey );
        ValueFromCenRep( EAknConfGestureSettingLongTapThreshold, cenRepKey );
        ValueFromCenRep( EAknConfGestureSettingDoubleTapThreshold, cenRepKey );
        ValueFromCenRep( EAknConfGestureSettingDragThreshold, cenRepKey );
        ValueFromCenRep( EAknConfGestureSettingFlickSpeedThreshold, cenRepKey );
        ValueFromCenRep( EAknConfGestureSettingFlickDetectionTime, cenRepKey );
        ValueFromCenRep( EAknConfGestureSettingFlickDirectionChange, cenRepKey );
        ValueFromCenRep( EAknConfGestureSettingPinchInitialThreshold, cenRepKey );
        ValueFromCenRep( EAknConfGestureSettingPinchMovementThreshold, cenRepKey );
        ValueFromCenRep( 
            EAknConfGestureSettingPinchDirectionChangeSensitivity, 
            cenRepKey );
        ValueFromCenRep( 
            EAknConfGestureSettingPinchDirectionResetSensitivity, 
            cenRepKey );
        ValueFromCenRep( 
            EAknConfGestureSettingPinchDimensionThreshold, 
            cenRepKey );
        ValueFromCenRep( 
            EAknConfGestureSettingPinchMaximumConfirmationDuration, 
            cenRepKey );
            
        TRAP_IGNORE( LoadSettingsL() );
        DrawDeferred();
        }
    */}


// -----------------------------------------------------------------------------
// CAknConfGestureSettingList::CAknConfGestureSettingList()
// -----------------------------------------------------------------------------
//
CAknConfGestureSettingList::CAknConfGestureSettingList()
    :
    CAknConfSettingList(),
    iTapThreshold( 0 ),
    iLongTapThreshold( 0 ),
    iDoubleTapThreshold( 0 ),
    iDragThreshold( 0 ),
    iFlickBuffer( 0 ),
    iFlickSpeedThreshold( 0 ),
    iFlickDetectionTime( 0 ),
    iFlickChangeSensitivity( 0 ),
    iPinchInitialThreshold( 0 ),
    iPinchMovementThreshold( 0 ),
    iPinchDirectionChangeSensitivity( 0 ),
    iPinchDirectionResetSensitivity( 0 ),
    iPinchDimensionThreshold( 0 ),
    iPinchMaximumConfirmationDuration( 0 )
    {
    }


// -----------------------------------------------------------------------------
// CAknConfGestureSettingList::ConstructL()
// -----------------------------------------------------------------------------
//
void CAknConfGestureSettingList::ConstructL()
    {/*
    CAknConfSettingList::ConstructL(
            KCRUidAknTouchGestureFwSettings, KResourceFile );
    CAknConfSettingList::ConstructFromResourceL(
            R_AKNCONF_GESTURE_SETTINGITEMLIST );
    */}


// -----------------------------------------------------------------------------
// CAknConfGestureSettingList::DataValuePointer()
// -----------------------------------------------------------------------------
//
TInt* CAknConfGestureSettingList::DataValuePointer( const TInt& aId, TInt& aCenRepKey )
    {
    TInt* valuePtr( NULL );/*
    switch ( aId )
        {
        case EAknConfGestureSettingTapThreshold:
            valuePtr = &iTapThreshold;
            aCenRepKey = KTapThreshold;
            break;
        case EAknConfGestureSettingLongTapThreshold:
            valuePtr = &iLongTapThreshold;
            aCenRepKey = KLongTapThreshold;
            break;
        case EAknConfGestureSettingDoubleTapThreshold:
            valuePtr = &iDoubleTapThreshold;
            aCenRepKey = KDoubleTapMaximumDuration;
            break;
        case EAknConfGestureSettingDragThreshold:
            valuePtr = &iDragThreshold;
            aCenRepKey = KDragThreshold;
            break;
        case EAknConfGestureSettingFlickBuffer:
            valuePtr = &iFlickBuffer;
            aCenRepKey = KFlickBuffer;
            break;
        case EAknConfGestureSettingFlickSpeedThreshold:
            valuePtr = &iFlickSpeedThreshold;
            aCenRepKey = KFlickSpeedThreshold;
            break;
        case EAknConfGestureSettingFlickDetectionTime:
            valuePtr = &iFlickDetectionTime;
            aCenRepKey = KFlickDetectionTime;
            break;
        case EAknConfGestureSettingFlickDirectionChange:
            valuePtr = &iFlickChangeSensitivity;
            aCenRepKey = KFlickDirectionChange;
            break;
        case EAknConfGestureSettingPinchInitialThreshold:
            valuePtr = &iPinchInitialThreshold;
            aCenRepKey = KPinchInitialThreshold;
            break;
        case EAknConfGestureSettingPinchMovementThreshold:
            valuePtr = &iPinchMovementThreshold;
            aCenRepKey = KPinchMovementThreshold;
            break;
        case EAknConfGestureSettingPinchDirectionChangeSensitivity:
            valuePtr = &iPinchDirectionChangeSensitivity;
            aCenRepKey = KPinchDirectionChangeSensitivity;
            break;
        case EAknConfGestureSettingPinchDirectionResetSensitivity:
            valuePtr = &iPinchDirectionResetSensitivity;
            aCenRepKey = KPinchDirectionResetSensitivity;
            break;
        case EAknConfGestureSettingPinchDimensionThreshold:
            valuePtr = &iPinchDimensionThreshold;
            aCenRepKey = KPinchDimensionThreshold;
            break;
        case EAknConfGestureSettingPinchMaximumConfirmationDuration:
            valuePtr = &iPinchMaximumConfirmationDuration;
            aCenRepKey = KPinchMaximumConfirmationDuration;
            break;
        default:
            break;
        }*/
    return valuePtr;
    }

// End of File
