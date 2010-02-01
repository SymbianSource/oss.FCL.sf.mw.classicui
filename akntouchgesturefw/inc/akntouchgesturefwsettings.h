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

#ifndef C_AKNTOUCHGESTUREFWSETTINGS_H
#define C_AKNTOUCHGESTUREFWSETTINGS_H

#include <e32base.h>

#include "akntouchgesturefwcenreplistener.h"

class CRepository;

namespace AknTouchGestureFw {

/**
 * Touch gesture framework parameter provider.
 *
 */
NONSHARABLE_CLASS( CAknTouchGestureFwSettings )
    : public CBase,
      public MAknTouchGestureFwCenRepObserver
    {

public:

    /**
     * Two-phased constructor.
     */
    static CAknTouchGestureFwSettings* NewL();

    /**
     * Two-phased constructor.
     */
    static CAknTouchGestureFwSettings* NewLC();

    /**
     * Destructor.
     */
    virtual ~CAknTouchGestureFwSettings();

    /**
     * Returns flick point buffer value.
     *
     * @return Flick point buffer.
     */
    TInt FlickBuffer() const;

    /**
     * Returns long tap threshold value.
     *
     * @return Long tap threshold.
     */
    TInt LongTapThreshold() const;

    /**
     * Returns tap threshold value.
     *
     * @return Tap threshold.
     */
    TInt TapThreshold() const;

    /**
     * Returns double tap maximum duration value.
     *
     * @return Double tap maximum duration.
     */
    TInt DoubleTapMaximumDuration() const;

    /**
     * Returns drag threshold.
     *
     * @return Drag threshold.
     */
    TInt DragThreshold() const;

    /**
     * Returns flick speed threshold.
     *
     * @return Flick speed threshold.
     */
    TInt FlickSpeedThreshold() const;

    /**
     * Returns flick detection time.
     *
     * @return Flick detection time.
     */
    TInt FlickDetectionTime() const;

    /**
     * Returns flick direction change sensitivity.
     *
     * @return Flick direction change sensitivity.
     */
    TInt FlickChangeSensitivity() const;

    /**
     * Returns pinch initial threshold.
     *
     * @return Pinch initial threshold.
     */
    TInt PinchInitialThreshold() const;

    /**
     * Returns pinch movement threshold.
     *
     * @return Pinch movement threshold.
     */
    TInt PinchMovementThreshold() const;

    /**
     * Returns pinch direction change sensitivity.
     *
     * @return Pinch direction change sensitivity.
     */
    TInt PinchDirectionChangeSensitivity() const;

    /**
     * Returns pinch direction reset sensitivity.
     *
     * @return Pinch direction reset sensitivity.
     */
    TInt PinchDirectionResetSensitivity() const;

    /**
     * Returns pinch dimension threshold.
     * 
     * @return Pinch dimension threshold.
     */
    TInt PinchDimensionThreshold() const;
    
    /**
     * Returns maximum confirmation duration for pinch.
     * 
     * @return Pinch maximum confirmation duration.
     */
    TInt PinchMaximumConfirmationDuration() const;
    
public: // From base class MAknTouchGestureFwCenRepObserver.

    /**
     * Informs the observer that the Central Repository
     * value has been changed.
     *
     * @param  aKey  CenRep value key.
     */
    void CenRepValueChanged( const TInt& aKey );

private:

    /**
     * C++ constructor.
     */
    CAknTouchGestureFwSettings();

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();

    /**
     * Reads the touch gesture framework parameters from the central
     * repository.
     */
    void ReadValuesFromCenRep();

    /**
     * Sets the touch gesture framework parameters to default values.
     *
     * @param  aWriteToCenRep  @c ETrue if values should be written to CenRep.
     */
    void SetDefaultValues( TBool aWriteToCenRep );

    /**
     * Checks if the values are set.
     *
     * @return @c ETrue if values are set, @c EFalse otherwise.
     */
    TBool ValuesAreSet() const;

private: // data

    /**
     * Central repository.
     * Own.
     */
    CRepository* iCenRep;

    /**
     * CenRep listener.
     * Own.
     */
    CAknTouchGestureFwCenRepListener* iListener;

    /**
     * Flick buffer value.
     */
    TInt iFlickBuffer;

    /**
     * Long tap threshold.
     */
    TInt iLongTapThreshold;

    /**
     * Tap threshold.
     */
    TInt iTapThreshold;

    /**
     * Double tap maximum duration.
     */
    TInt iDoubleTapMaximumDuration;

    /**
     * Drag threshold.
     */
    TInt iDragThreshold;

    /**
     * Flick speed threshold.
     */
    TInt iFlickSpeedThreshold;

    /**
     * Flick detection time.
     */
    TInt iFlickDetectionTime;

    /**
     * Flick direction change sensitivity.
     */
    TInt iFlickChangeSensitivity;

    /**
     * Pinch threshold.
     */
    TInt iPinchInitialThreshold;

    /**
     * Pinch movement threshold.
     */
    TInt iPinchMovementThreshold;

    /**
     * Pinch direction change sensitivity.
     */
    TInt iPinchDirectionChangeSensitivity;

    /**
     * Pinch direction reset sensitivity.
     */
    TInt iPinchDirectionResetSensitivity;

    /**
     * Pinch dimension threshold.
     */
    TInt iPinchDimensionThreshold;
    
    /**
     * Pinch maximum confirmation duration. 
     */
    TInt iPinchMaximumConfirmationDuration;
    
    };

} // AknTouchGestureFw

#endif // C_AKNTOUCHGESTUREFWSETTINGS_H
