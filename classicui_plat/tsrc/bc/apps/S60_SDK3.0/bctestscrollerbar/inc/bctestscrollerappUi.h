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
* Description:         Test BC for Scroller control API.
*
*/









#ifndef C_BCTESTScrollerAPPUI_H
#define C_BCTESTScrollerAPPUI_H

#include <aknviewappui.h>

class CBCTestScrollerView;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestScrollerAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
         * ctor
         */
        CBCTestScrollerAppUi();

        /**
         * symbian 2nd ctor
         */
        void ConstructL();

        /**
         * dtor
         */
        virtual ~CBCTestScrollerAppUi();

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
        CBCTestScrollerView*  iView;
    };

#endif // C_BCTESTScrollerAPPUI_H

// End of File
