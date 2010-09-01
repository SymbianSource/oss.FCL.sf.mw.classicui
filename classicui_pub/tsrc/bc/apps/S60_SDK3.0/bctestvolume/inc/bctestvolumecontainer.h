/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Declares container control for application.
*
*/









#ifndef C_BCTESTVOLUMECONTAINER_H
#define C_BCTESTVOLUMECONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include <apadef.h>

// FORWARD DECLARATIONS
class CEikLabel;
class CAknNavigationControlContainer;
class CAknNavigationDecorator;
class CBCTestVolumeView;
class CBCTestVolumePopUpWindow;

class CAknVolumePopup;
// CLASS DECLARATION

/**
* CBCTestVolumeContainer container control class.
*/
class CBCTestVolumeContainer : public CCoeControl
    {

    private: // Enumerations

        enum TBCTestVolumeComponentControls
            {
            EBCTestVolumeComponent1,
            EBCTestVolumeComponent2
            };

    public: // Constructors and destructor

        /**
        * Overload constructor.
        * @param aView Pointer to view class object.
        */
        CBCTestVolumeContainer( CBCTestVolumeView* aView );

        /**
        * Symbian 2nd phase constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CBCTestVolumeContainer();

    public: // New functions

        /**
        * Displays each outline screen.
        * @param aOutlineId The ID of outline to display it.
        */
        void DisplayOutlineL( const TInt aOutlineId );

        /**
        * Delete all components and set them to NULL.
        */
        void ResetComponentsL();

        /**
        * Update components for redraw.
        */
        void UpdateComponentsL();

        /**
        * Getter of the navigation pane.
        */
        CAknNavigationControlContainer* NaviPane();

        /**
        * Setter of the decorator in the navigation pane.
        * @param aDecorator, the decorator you want to set.
        */
        void SetDecorator(CAknNavigationDecorator* aDecorator);

        /**
        * Creates the label object.
        * @param aResourceId The ID of resource to create that.
        */
        void CreateLabelL( const TInt aResourceId );

    private: // New function

        /**
        * Release the navigation pane as well as the decorator.
        */
        void ResetNaviPane();
        
    private: // From CCoeControl

        /**
        * From CCoeControl, OfferKeyEventL.
        * Handles the key events.
        * @return If key-event is consumed, EKeyWasConsumed.
        * Else EKeyWasNotConsumed.
        * @param aKeyEvent Key event
        * @param aType Type of key event(EEventKey, EEventKeyUp or
        * EEventKeyDown).
        */
        TKeyResponse OfferKeyEventL(
            const TKeyEvent& aKeyEvent,
            TEventCode aType );

        /**
        * From CoeControl,SizeChanged.
        * Called by framework when the view size is changed.
        */
        void SizeChanged();

        /**
        * From CoeControl,CountComponentControls.
        * Returns number of component.
        * @return Number of controls.
        */
        TInt CountComponentControls() const;

        /**
        * From CCoeControl,ComponentControl.
        * Returns pointer to particular component.
        * @return Pointer to Control's component control, identified by index.
        * @param aIndex Index of the control.
        */
        CCoeControl* ComponentControl( TInt aIndex ) const;

        /**
        * From CCoeControl,Draw.
        * @param aRect Region of the control to be (re)drawn.
        */
        void Draw( const TRect& aRect ) const;

        /**
        * From CCoeControl, HandleResourceChange.
        * Make dynamic resolution change smoother.
        * @param aType A message UID value.
        */
        void HandleResourceChange( TInt aType );
        
    private: // Data

        /**
        * lable to show the neccessary informations
        * own
        */
        CEikLabel* iLabel;

        /**
        * point to navigation pane
        * own
        */
        CAknNavigationControlContainer* iNaviPane;

        /**
        * point to decorator in the navigation pane.
        * own
        */
        CAknNavigationDecorator* iDecorator;

        /**
        * point to the active view
        * not own.
        */
        CBCTestVolumeView* iView;

        /**
        * record the the current outline ID
        */
        TInt iCurrentOutlineId;

        /**
        * a popup control for masking clock
        * own.
        */
        CBCTestVolumePopUpWindow* iPopUpControl;

        TInt             iVolume;
        TBool            iMuted;
        TInt32           iKeyHandle1;
        TInt32           iKeyHandle2;
        TInt32           iKeyHandle3;
        TInt32           iKeyHandle4;
        
    };

#endif  // C_BCTESTVOLUMECONTAINER_H

// End of File
