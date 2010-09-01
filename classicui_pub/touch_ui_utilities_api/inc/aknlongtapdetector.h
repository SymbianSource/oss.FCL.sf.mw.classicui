/*
* Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Long Tap Detector with animation informing of long tap functionality
*
*/



#ifndef CAKNLONGTAPDETECTORCONTROLLER_H
#define CAKNLONGTAPDETECTORCONTROLLER_H

#include <w32std.h>
#include <e32base.h>
#include <coemain.h>

class CAknLongTapAnimation;

/**
 * Avkon LongTapDetector CallBack.
 *
 * Inherit from this class and implement HandleLongTapEventL to
 * get a callback when/if a long tap occurs.
 *
 * @lib avkon.lib
 * @since S60 5.0
 */
class MAknLongTapDetectorCallBack
    {
public:
    /**
    * Callback method. Get's called when a long tap occurs.
    * @param aPenEventLocation Long tap event location relative to parent control.
    * @param aPenEventScreenLocation Long tap event location relative to screen.
    */
    virtual void HandleLongTapEventL( const TPoint& aPenEventLocation, 
                                      const TPoint& aPenEventScreenLocation ) = 0;
    };


/**
 * Avkon Long Tap Detector. 
 *
 * Receives pointer events from owner application or owner control and returns
 * location if a long tap event occurs.
 * After short period of time (default 0,15s) animation is displayed next to stylus on the screen to
 * inform the user of long tap functionality. Animation can be turned OFF by application if wanted.
 *
 * @lib avkon.lib
 * @since S60 5.0
 */
NONSHARABLE_CLASS( CAknLongTapDetector ) : public CTimer, MCoeMessageMonitorObserver
    {
public: // Constructors and destructor	

    /**
     * Two-phased constructor.
     * @param aOwner Pointer to owner of this component. Ownership not transferred.
     */
    IMPORT_C static CAknLongTapDetector* NewL( MAknLongTapDetectorCallBack* aOwner );

    /**
     * Two-phased constructor.
     * @param aOwner Pointer to owner of this component. Ownership not transferred.
     */
    IMPORT_C static CAknLongTapDetector* NewLC( MAknLongTapDetectorCallBack* aOwner );

    /**
    * Destructor.
    */
    virtual ~CAknLongTapDetector();

public: // New functions

    /**
    * Receives and handles pointer events from owner's HandlePointerEventL() -method.
    * Used to control timers in detecting long tap events.
    * @param aEvent Pointer event from owner.
    */
    IMPORT_C void PointerEventL( const TPointerEvent& aEvent );

    /**
    * Sets new time delay before long tap detector animation starts. Default delay is 0,15s.	
    * @param aMicroSeconds New delay in microseconds.
    */
    IMPORT_C void SetTimeDelayBeforeAnimation( const TInt aMicroSeconds );

    /**
    * Sets new time delay before long tap detector event is returned. Default delay is 0,8s.
    * @param aMicroSeconds New delay in microseconds.
    */
    IMPORT_C void SetLongTapDelay( const TInt aMicroSeconds );

    /**
    * Sets long tap animation ON/OFF. Default is ON.
    * @param aAnimation ETrue turns animations ON and EFalse turns animations OFF.
    */
    IMPORT_C void EnableLongTapAnimation( const TBool aAnimation );

    /**
    * Checks if the animation is running
    * @return ETrue if the animation is running, EFalse if not
    */
    IMPORT_C TBool IsAnimationRunning() const;
    
    /**
    * Cancels the long tap animation
    */
    IMPORT_C void CancelAnimationL();

		/**
		 * This function is used to capture key events during the longtap animation.
		 * If such events are received, the longtap animation is then cancelled (TSW Error
		 * ASAA-79TCJP).
		 */
		void MonitorWsMessage(const TWsEvent& aEvent);

protected: // From CActive

    /**
    * Handles CTimer events. Called by system framework.
    */
    void RunL();
    
    /**
    * Cancels an outstanding request.
    */
    void DoCancel();

private: // Constructors

    /**
    * C++ default constructor.
    * @param aOwner Owner.
    */
    CAknLongTapDetector( MAknLongTapDetectorCallBack* aOwner );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

private: // New functions

    void StartAnimationL();
    void StopAnimation();	

private: // Data

    enum TLongTapDetectorState
        {
        EWaiting, 				// normal state
        EWaitingForAnimation,	// Only "Pen down" event received, CTimer started
        EShowingAnimation		// Long tap animation started
        };

    /**
    * Current state of LongTapDetector.
    */
    TLongTapDetectorState iState;
    
    /**
    * Pointer to owner of this LongTapDetector object.
    * Not own.
    */
    MAknLongTapDetectorCallBack* iOwner;

    /**
    * Delay before animation starts in microseconds.
    */
    TInt iTimeDelayBeforeAnimation;

    /**
    * Delay before long tap event is reported in microseconds.
    */
    TInt iLongTapDelay; 

    /**
    * Pointer event received from owner.
    */
    TPointerEvent iPointerEvent;

    /**
    * Is long tap animation shown or not.
    */
    TBool iShowAnimation;
    
    /**
    * Long tap animation.
    * Own.
    */
    CAknLongTapAnimation* iAnimation;
    };

#endif // CAKNLONGTAPDETECTOR_H

// End of File

