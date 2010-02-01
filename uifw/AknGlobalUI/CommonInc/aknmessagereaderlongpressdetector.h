/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  System soft notifications.
*
*/


#ifndef __AKNMESSAGEREADERLONGPRESSDETECTOR_H__
#define __AKNMESSAGEREADERLONGPRESSDETECTOR_H__

#include <coecntrl.h>

class MEikButtonGroup;
class CPeriodic;
class CAknPhoneLockObserver;
class CEikButtonGroupContainer;

/**
*  MAknMessageReaderLongPressDetector interface, used by CAknCapAppServerAppUi::HandleWsEventL. 
*
*  @lib   AknOldStyleNotif.lib
*  @since 5.0
*/  
class MAknMessageReaderLongPressDetector
    {
public:    

    /**
    * Observe key and pointer events for long press detection
    * @param ws events received by the process
    * @param aDestionation control where wsevent is targeted at
    * @return whether ws event should be consumed or nto
    */
    virtual TBool HandleWsEventL( const TWsEvent& aEvent, 
                                  CCoeControl* aDestination ) = 0;
    };

/**
*  MAknMessageNotifierObserver interface, used by CAknSoftNotificationSubject. 
*
*  @lib   AknOldStyleNotif.lib
*  @since 5.0
*/  
class MAknMessageNotifierObserver
    {
public:
    virtual TBool MessageNotifierShown() = 0;
    virtual CEikButtonGroupContainer* ButtonGroupContainer() = 0;
    };
        
/**
*  CAknMessageReaderLongPressDetector class. 
*  Detects whether user has long pressed left soft key or not.
*
*  @lib   AknOldStyleNotif.lib
*  @since 5.0
*/      
NONSHARABLE_CLASS(CAknMessageReaderLongPressDetector): public CCoeControl, public MAknMessageReaderLongPressDetector
{
    public: // Constructors and destructor

        /**
        * Two-phased constructor.
        * @param aButtonGroup soft notification dialog button group (cba)
        */
        static CAknMessageReaderLongPressDetector* NewL( CEikButtonGroupContainer* aGlobalNoteBGContainer, RWindow& aGlobalNoteWindow );
        
        /**
        * Destructor.
        */
        virtual ~CAknMessageReaderLongPressDetector();

        /**
        * Disable long press evaluation
        * @return ETrue if message reader has been installed on the device
        */    
        static TBool MessageReaderInstalled();

    
        /**
        * Soft notification is on the screen
        */
        void SoftNotifierVisible( TBool aVisible );
        
        /**
        * Phone keys are locked
        * @param aLocked ETrue if locked
        */
        void KeysLocked( TBool aLocked );
    
        /**
        * Give a access to the grouped note information
        */
        void SetMessageNotifierObserver( MAknMessageNotifierObserver* aMessageNotifierObserver );
        
   public: // from MAknMessageReaderLongPressDetector
   
        /**
        * Observe key and pointer events for long press detection
        * @param ws events received by the process
        * @param aDestionation control where wsevent is targeted at
        * @return whether ws event should be consumed or nto
        */
        TBool HandleWsEventL( const TWsEvent& aEvent, CCoeControl* aDestination );
        
    private:

        /**
        * C++ constructor
        * @param aButtonGroup soft notification dialog button group (cba)
        */
        CAknMessageReaderLongPressDetector( CEikButtonGroupContainer* aGlobalNoteBGContainer, RWindow& aGlobalNoteWindow );
        
        /**
        * Symbian OS 2nd phase constructor.
        */
        void ConstructL();
        
    private:
    
        /**
        * Enable long press evaluation
        */
        void Enable();
        
        /**
        * Disable long press evaluation
        */    
        void Disable();
        
    private:
    
        /**
        * Determine if left soft button has been long touched
        *
        * @param aPointerEvent received pointer event
        * @return if pointer event should be consumed
        * @param aDestionation the control where wsevent is targeted at
        */
        TBool HandleLongTouchL( const TPointerEvent& aPointerEvent, 
                                CCoeControl* aDestination );
        
        TBool IsPointerInLeftSoftKeyRect(TPoint aPoint, CCoeControl* aDestination);
        
        /**
        * If left soft key was long pressed, launch message reader
        */
        void LaunchMessageReaderL();
        
        /**
        * Start long press timer
        */
        void StartLongPressTimerL();
        
        /**
        * Static function to be called when long press is detected
        * @param pointer to the class
        */
        static TInt ReportLongPressL( TAny* aThis );

        /**
        * Handle long press detection, called by ReportLongPressL
        */
        void DoReportLongPressL();    
                
        /**
        * Stop long press timer
        */
        void StopLongPressTimer();

    private:
    
        // only detect long press if soft notifier is visible
        TBool iSoftNotifierVisible;
        
        // if detector has been enabled or not
        TBool iDetectorEnabled;
        
        // prevent pointer event leakage 
        TBool iIgnoreEventsUntilNextPointerUp;
        
        // for pointer presses we store pointer destination
        CCoeControl* iPointerDestination;
        
        // detects long pointer presses
        CPeriodic* iLongPressTimer;
        
        // left soft key control
        CCoeControl* iLeftSoftKeyControl;       
        
        // we create a separate phone lock observer as we do not want to 
        // couple our implementation with keylock notifier, keeps track of 
        // keyguard and devicelock status
        CAknPhoneLockObserver* iPhoneLockObserver;

        // Handle to the left soft key long capture        
        TInt32 iCaptureLongKeyHandle;
        
        // access to global note and grouped notes
        MAknMessageNotifierObserver* iMessageNotifierObserver;
        CEikButtonGroupContainer* iGlobalNoteBGContainer;
        RWindow& iGlobalNoteWindow;
        
        //Detect whether LSK has been keydowned
        TBool iLSKKeyDownDetect;
};

#endif  // __AKNMESSAGEREADERLONGPRESSDETECTOR_H__

// End of file


