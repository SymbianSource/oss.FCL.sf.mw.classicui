/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of the License "Eclipse Public License v1.0"
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



#ifndef AKNSLIDESTATUSNOTIFIER_H
#define AKNSLIDESTATUSNOTIFIER_H

#include <e32base.h>
#include <e32property.h>
//Grip keys
#include <hwrmdomainpskeys.h>

class MAknSlideStatusObserver
    {
    public:
    
   /**
    * Slide status notification
    * Called by the notifier when the Slide status value change 
	*
    * @param aValue the new status value
    * @return none
    */
    virtual void SlideStatusChangedL( const TInt& aValue ) = 0;
    
    };

/**
 *  Reacts to Slide status changes
 *
 *  Reacts to Slide status changes and notifies
 *  its client(s) about the status change
 */
class CAknSlideStatusNotifier : public CActive
    {
    public:
    	
        /**
         * Symbian two-phase constructor
	     *
	     * @param a pointer to Slide status observer
	     * @return a pointer to CSlideStatusNotifier instance
         */ 
        static CAknSlideStatusNotifier* NewL( MAknSlideStatusObserver* aObserver );

        /**
         * Symbian two-phase constructor leaving a pointer to the constructed 
         * object on the cleanup stack
	     *
	     * @param a pointer to Slide status observer
	     * @return a pointer to CSlideStatusNotifier instance
         */
        static CAknSlideStatusNotifier* NewLC( MAknSlideStatusObserver* aObserver );

        /**
         * Default destructor
         */
        virtual ~CAknSlideStatusNotifier();

    protected:
    
        // From base class CActive    
        /**
         * From CActive.
         * Implements cancellation of an outstanding request.
         *
         * @param none
         */
        void DoCancel();
    
        /**
         * From CActive.
         * Handles an active object's request completion event
         *
         * @param none
         */
        void RunL();
     
        /**
         * From CActive.
         * Handles an active object's request error event
         *
         * @param TInt aError
         */
        TInt RunError( TInt aError );
 

    private: 

        /** 
         * C++ default constructor
         * 
         * @param none 
         */
        CAknSlideStatusNotifier();

        /**
         * Symbian second phase constructor
         * 
         * @param a pointer to Slide status observer 
         */
        void ConstructL( MAknSlideStatusObserver* aObserver );


    private: // Data   

        /**
         * Property handle used to read P&S variables
         */
        RProperty iProperty;
    
        /**
         * The observer interested in the Slide status
         * Not own.  
         */
        MAknSlideStatusObserver* iObserver;
    };

#endif //AKNSLIDESTATUSNOTIFIER_H
