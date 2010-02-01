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
* Description:         Test BC for PrivateUIFrm control API.
*
*/









#ifndef C_BCTESTPrivateUIFrmAPPUI_H
#define C_BCTESTPrivateUIFrmAPPUI_H

#include <aknviewappui.h>

class CBCTestPrivateUIFrmView;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestPrivateUIFrmAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
         * ctor
         */
        CBCTestPrivateUIFrmAppUi();

        /**
         * symbian 2nd ctor
         */
        void ConstructL();

        /**
         * dtor
         */
        virtual ~CBCTestPrivateUIFrmAppUi();

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
        CBCTestPrivateUIFrmView*  iView;
    };

#endif // C_BCTESTPrivateUIFrmAPPUI_H

// End of File
