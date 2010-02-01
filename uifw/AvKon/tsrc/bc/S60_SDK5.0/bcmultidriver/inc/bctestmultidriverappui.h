/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test BC for MultiDriver API.
*
*/


#ifndef C_MultiDriverAPPUI_H
#define C_MultiDriverAPPUI_H

#include <aknviewappui.h>

class CMultiDriverView;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CMultiDriverAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
         * ctor
         */
        CMultiDriverAppUi();

        /**
         * symbian 2nd ctor
         */
        void ConstructL();

        /**
         * dtor
         */
        virtual ~CMultiDriverAppUi();

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
        CMultiDriverView*  iView;
    };

#endif // C_MultiDriverAPPUI_H

// End of File
