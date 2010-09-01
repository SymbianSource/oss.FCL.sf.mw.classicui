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
* Description:  Test BC for DomCoreUi control API.
*
*/



#ifndef C_CBCTESTDOMCOREUIAPPUI_H
#define C_CBCTESTDOMCOREUIAPPUI_H

#include <aknviewappui.h>

class CBCTestDomCoreUiView;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestDomCoreUiAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
         * ctor
         */
        CBCTestDomCoreUiAppUi();

        /**
         * symbian 2nd ctor
         */
        void ConstructL();

        /**
         * dtor
         */
        virtual ~CBCTestDomCoreUiAppUi();

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
        CBCTestDomCoreUiView*  iView;
    };

#endif 


