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
* Description:  AppUI class of bctestsingleclick.
*
*/

#ifndef C_BCTESTSINGLECLICKAPPUI_H
#define C_BCTESTSINGLECLICKAPPUI_H

#include <aknviewappui.h>

class CBCTESTSingleClickAppUi;
class CBCTestUtil;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTESTSingleClickAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
         * constructor
         */
        CBCTESTSingleClickAppUi();

        /**
         * symbian 2nd constructor
         */
        void ConstructL();

        /**
         * destructor
         */
        virtual ~CBCTESTSingleClickAppUi();

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
        CBCTESTSingleClickAppUi*  iView;

		/**
         * pointor to the BC Test framework utility.
         * own
         */
        CBCTestUtil*  iTestUtil;
    };

#endif // C_BCTESTSINGLECLICKAPPUI_H

// End of File
