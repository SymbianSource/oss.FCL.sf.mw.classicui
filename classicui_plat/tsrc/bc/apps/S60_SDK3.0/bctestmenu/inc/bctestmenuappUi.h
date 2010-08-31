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
* Description:         Test BC for Menu control API.
*
*/









#ifndef C_BCTESTMENUAPPUI_H
#define C_BCTESTMENUAPPUI_H

#include <aknviewappui.h>

class CBCTestMenuView;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestMenuAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
         * ctor
         */
        CBCTestMenuAppUi();

        /**
         * symbian 2nd ctor
         */
        void ConstructL();

        /**
         * dtor
         */
        virtual ~CBCTestMenuAppUi();

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
        CBCTestMenuView*  iView;
    };

#endif // C_BCTESTMenuAPPUI_H

// End of File
