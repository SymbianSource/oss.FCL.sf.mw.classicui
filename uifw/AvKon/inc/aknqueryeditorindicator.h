/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
*   Implementation of Avkon queries, editor indicator icons. Move here from
*   aknquerydialog.h
*
*/


#ifndef __AKNQUERY_EDIT_INDICATOR__
#define __AKNQUERY_EDIT_INDICATOR__

#include <aknEditStateIndicator.h>
#include <AknIndicatorContainer.h>
#include <AknIndicator.h>

// FORWARD DECLARATIONS
class CCoeControl;

/**
 * QueryEditIndicator class.
 */
NONSHARABLE_CLASS(CAknQueryEditIndicator) : public CAknIndicatorContainer, public MAknEditingStateIndicator
	{
    public: // Constructors and destructor
        /**
         * C++ Constructor.
         */
	    static CAknQueryEditIndicator* NewL(CCoeControl* aControl);
        /**
         * C++ Destructor.
         */
	    ~CAknQueryEditIndicator();

    public: 

 		/**
         * Handles pointer events.
         *
         * @param aPointerEvent The pointer event.
         */
        void HandlePointerEventL( const TPointerEvent& aPointerEvent );

        /**
        * From MAknEditingStateIndicator
        *   Set editor indicator's state
        * @param aState State to be set
        */
        virtual void SetState(TAknEditingState aState); 

        /**
        * From MAknEditingStateIndicator
        *   Returns indicator container
        * @return   Pointer to indicator container
        */
        virtual CAknIndicatorContainer* IndicatorContainer();

    public: // new functions

        /**
        * Sets the information about the query flags.
        */
        void SetFlags(TBitFlags16 aFlags);
        TAknEditingState State(); 
        void SetQueryType(TInt aQueryType);

    private:
        /**
        * Constructor
        */
	    CAknQueryEditIndicator();

        /**
        * ConstructL
        */
        void ConstructL(CCoeControl* aControl);

        /**
        * Sets new indicator to container
        * @param aIndicator Indicator id
        * @param aState     State of the indicator
        * @param aDrawNow   Should the indicator be drawn now
        */
        void SetIndicator(TInt aIndicator, TInt aState, TBool aDrawNow);

    private:
	    TBitFlags16 iFlags;
	    TAknEditingState iState;
	    TInt iQueryType;
	};

#endif
