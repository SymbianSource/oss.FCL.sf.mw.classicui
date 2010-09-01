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
* Description:         Test BC for BCTestToolBar API.
*
*/









#ifndef C_BCTESTTOOLBARAPPUI_H
#define C_BCTESTTOOLBARAPPUI_H

#include <aknviewappui.h>

class CBCTestToolBarView;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestToolBarAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
         * ctor
         */
        CBCTestToolBarAppUi();

        /**
         * symbian 2nd ctor
         */
        void ConstructL();

        /**
         * dtor
         */
        virtual ~CBCTestToolBarAppUi();

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
        CBCTestToolBarView*  iView;
    };

#endif // C_BCTESTTOOLBARAPPUI_H

// End of File
