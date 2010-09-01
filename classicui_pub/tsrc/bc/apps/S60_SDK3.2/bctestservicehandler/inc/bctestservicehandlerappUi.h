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
* Description:         Test BC for ServiceHandler control API.
*
*/









#ifndef C_BCTESTSERVICEHANDLERAPPUI_H
#define C_BCTESTSERVICEHANDLERAPPUI_H

#include <aknviewappui.h>

class CBCTestServiceHandlerView;
class CBCTestUtil;
class CAiwServiceHandler;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestServiceHandlerAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
         * ctor
         */
        CBCTestServiceHandlerAppUi();

        /**
         * symbian 2nd ctor
         */
        void ConstructL();

        /**
         * dtor
         */
        virtual ~CBCTestServiceHandlerAppUi();

    private:

        /**
         * From CEikAppUi
         */
        void HandleCommandL( TInt aCommand );

    private: // data
        
        /**
         * pointor to the view.
         * Owned
         */
        CBCTestServiceHandlerView*  iView;
    };

#endif // C_BCTESTSERVICEHANDLERAPPUI_H

// End of File
