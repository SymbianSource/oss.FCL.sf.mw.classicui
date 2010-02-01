/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Avkon view navigator.
*
*/


#ifndef __AKNVIEWNAVIGATOR_H__
#define __AKNVIEWNAVIGATOR_H__

//  INCLUDES
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CAknViewAppUi;

// CLASS DECLARATION

/**
*  Avkon view navigator. Handles keyboard-initiated moving between views in 
*  split view architecture.
*
*  @lib avkon.lib
*  @since Series 60 5.0
*/
NONSHARABLE_CLASS(CAknViewNavigator) : public CCoeControl
    {
    public: // constructors and destructor
        
        /**
        * C++ default constructor.
        * @param aAppUi Application UI.
        */
        CAknViewNavigator( CAknViewAppUi* aAppUi );

        /**
        * Destructor.
        */
        virtual ~CAknViewNavigator();

    protected: // functions from base classes
        
        /**
        * From CCoeControl. Handles key events in order to initiate switching 
        * between split views.
    	* @since Series 60 5.0
    	* @param aKeyEvent The key event.
    	* @param aType The type of the key event.
        */
        TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

        /**
        * From CCoeControl. Returns control's input capabilities.
    	* @since Series 60 5.0
    	* @return Control's input capabilities.
        */
        TCoeInputCapabilities InputCapabilities() const;
        
    private: // data
        // pointer to application UI
        CAknViewAppUi* iAppUi;
    };

#endif // __AKNVIEWNAVIGATOR_H__
            
// End of File
