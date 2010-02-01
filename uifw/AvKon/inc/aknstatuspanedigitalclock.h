/*
* Copyright (c) 2005-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  A default control in the status pane's digital clock pane.
*                This class is used as container control
*                for the digital clock.
*
*/


#ifndef C_AKNSTATUSPANEDIGITALCLOCK_H
#define C_AKNSTATUSPANEDIGITALCLOCK_H

#include <AknControl.h>
#include <e32property.h>
#include <hwrmlight.h>

class CAknDigitalClock;
class CAknStatuspaneDigitalClock;

/**
 * Statuspane digital clock control that contains simple digital clock.
 *
 * This class is not intended for further derivation.
 *
 * @since 3.1
 *
 * @internal
 */
NONSHARABLE_CLASS( CAknStatuspaneDigitalClock ) :
    public CAknControl,
    public MCoeMessageMonitorObserver, 
    public MHWRMLightObserver
    {
public:

    /**
    * Standard constructor.
    */
    CAknStatuspaneDigitalClock();

    /**
    * Destructor.
    */
    ~CAknStatuspaneDigitalClock();

    /**
    * Construct from resources.
    *
    * @param  aReader  Not used.
    */
    void ConstructFromResourceL( TResourceReader& aReader );

public: // From base class @c CCoeControl.

    /**
    * Returns the number of component controls.
    *
    * @return  Amount of component controls.
    */
    TInt CountComponentControls() const;

    /**
    * Returns the specified component control.
    *
    * @param  aIndex  Index of the component control.
    * @return The component control.
    */
    CCoeControl* ComponentControl( TInt aIndex ) const;

    /**
    * Sets dimming.
    *
    * @param  aDimmed  @c ETrue to set dimmed.
    */
    void SetDimmed( TBool aDimmed );

    /**
    * Handles the resource change events.
    *
    * @param  aType  Resource change event type.
    */
    void HandleResourceChange( TInt aType );

    virtual void MakeVisible( TBool aVisible );

public: // From base class @c MCoeMessageMonitorObserver.

    /**
    * Used to receive event from window server
    * when the visibility of the window changes.
    *
    * @param  aEvent  The window server event.
    */
    void MonitorWsMessage( const TWsEvent &aEvent );

private: // New functions.

    /**
    * Called when the clock control receives foreground.
    */
    void ForegroundGainedL();

protected: // From base class @c CCoeControl.

    /**
    * Handles the size change events.
    */
    void SizeChanged();

private: // From base class @c CCoeControl.

    /**
    * Draws the control.
    *
    * @param  aRect  Not used.
    */
    void Draw( const TRect& aRect ) const;

private:

    /**
    * Sets window behaviour in fade situations.
    *
    * @param  aNonFading  @c ETrue to set the window non-fading.
    */
    void SetContainerWindowNonFading( TBool aNonFading );

    /**
     * From MHWRMLightObserver
     * @since Series 60 3.1
     */
    void LightStatusChanged(TInt aTarget, CHWRMLight::TLightStatus aStatus);


private: // Member data

    /** Digital clock */
    CAknDigitalClock* iClock;

    TInt iSpare1;
    TInt iSpare2;

    TBool iInForeground;

    /** For registering MHWRMLightObserver. */
    CHWRMLight* iLight;
    };

#endif // C_AKNSTATUSPANEDIGITALCLOCK_H
