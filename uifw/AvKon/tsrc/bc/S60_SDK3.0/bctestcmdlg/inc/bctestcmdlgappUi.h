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
* Description:  Test BC for Template control API.
*
*/


#ifndef C_BCTESTCMDLGAPPUI_H
#define C_BCTESTCMDLGAPPUI_H

#include <aknviewappui.h>

class CBCTestCmDlgView;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestCmDlgAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
         * ctor
         */
        CBCTestCmDlgAppUi();

        /**
         * symbian 2nd ctor
         */
        void ConstructL();

        /**
         * dtor
         */
        virtual ~CBCTestCmDlgAppUi();

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
        CBCTestCmDlgView*  iView;
    };

#endif // C_BCTESTCMDLGAPPUI_H

// End of File
