/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  container
*
*/

#ifndef C_BCTESTPHYSICSAPPUI_H
#define C_BCTESTPHYSICSAPPUI_H

#include <aknviewappui.h>

class CBCTestPhysicsView;
class CBCTestUtil;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestPhysicsAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
         * constructor
         */
        CBCTestPhysicsAppUi();

        /**
         * symbian 2nd constructor
         */
        void ConstructL();

        /**
         * destructor
         */
        virtual ~CBCTestPhysicsAppUi();

    private:

        /**
         * From CEikAppUi
         */
        void HandleCommandL( TInt aCommand );

    private: // data
        
        /**
         * pointor to the view.
         * own
         */
        CBCTestPhysicsView*  iView;

		/**
         * pointor to the BC Test framework utility.
         * own
         */
        CBCTestUtil*  iTestUtil;
    };

#endif // C_BCTESTPHYSICSAPPUI_H

// End of File
