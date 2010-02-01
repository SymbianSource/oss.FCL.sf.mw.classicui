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
* Description:         Test BC for KeyLock control API.
*
*/









#ifndef C_BCTESTKeyLockAPPUI_H
#define C_BCTESTKeyLockAPPUI_H

#include <aknviewappui.h>

class CBCTestKeyLockView;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestKeyLockAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
         * ctor
         */
        CBCTestKeyLockAppUi();

        /**
         * symbian 2nd ctor
         */
        void ConstructL();

        /**
         * dtor
         */
        virtual ~CBCTestKeyLockAppUi();

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
        CBCTestKeyLockView*  iView;
    };

#endif // C_BCTESTKeyLockAPPUI_H

// End of File
