/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         container control
*
*/









#ifndef BCTestFormCONTAINER_H
#define BCTestFormCONTAINER_H

const TUid KCRUidAknFep = { 0x101F876D };
const TUint32 KAknFepPredTxtFlag           = 0x00000007;
// INCLUDES
#include <coecntrl.h>

 // turn T9 on/off
#include <CentralRepository.h>

// FORWARD DECLARATIONS
class CBCTestFormView;
class CEikLabel;

// CLASS DECLARATION

/**
* CBCTestFormContainer container control class.
*/
class CBCTestFormContainer : public CCoeControl
    {
    private: // Enumerations

        enum TBCTestFormComponentControls
            {
            EBCTestFormComponentLabel
            };

    public: // Constructors and destructor

        /**
        * Overload constructor.
        * @param aView Pointer to view class object.
        */
        CBCTestFormContainer( CBCTestFormView* aView );

        /**
        * Symbian 2nd phase constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CBCTestFormContainer();

    public: // New functions

        /**
        *
        * @param aResourceId
        */
        void SetTextToLabelL( TInt aResourceId );

        /**
        *
        * @param aResourceId
        */
        void DisplayFormL( TInt aResourceId );

    private: // New functions

        /**
        * Creates the label object.
        */
        void CreateLabelL();

    private: // From CCoeControl

        /**
        * From CCoeControl, OfferKeyEventL.
        * Handles the key events.
        * @return EKeyWasConsumed, EKeyWasNotConsumed
        * @param aKeyEvent Key event
        * @param aType Type of key event (EEventKey, EEventKeyUp, EEventKeyDown)
        */
        TKeyResponse OfferKeyEventL(
            const TKeyEvent& aKeyEvent,
            TEventCode aType );

        /**
        * From CCoeControl, HandleResourceChange.
        * Make dynamic resolution change smoother.
        * @param aType A message UID value.
        */
        void HandleResourceChange( TInt aType );

        /**
        * From CCoeControl, SizeChanged.
        *
        */
        void SizeChanged();

        /**
        * From CCoeControl, CountComponentControls.
        * Returns number of component.
        * @return Number of controls
        */
        TInt CountComponentControls() const;

        /**
        * From CCoeControl, ComponentControl.
        * Returns pointer to particular component.
        * @return Pointer to Control's component control, identified by index
        * @param aIndex Index of the control
        */
        CCoeControl* ComponentControl( TInt aIndex ) const;

        /**
        * From CCoeControl, Draw.
        *
        * @param aRect Region of the control to be (re)drawn.
        */
        void Draw( const TRect& aRect ) const;

    private: // Data

        CBCTestFormView* iView;
        CEikLabel* iLabel;

    };

#endif //BCTestFormCONTAINER_H

// End of File
