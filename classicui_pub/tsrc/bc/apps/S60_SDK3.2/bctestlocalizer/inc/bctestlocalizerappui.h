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
* Description:         Test BC for BCTestLocalizer API.
*
*/









#ifndef C_BCTESTLOCALIZERAPPUI_H
#define C_BCTESTLOCALIZERAPPUI_H

#include <aknviewappui.h>

class CBCTestLocalizerView;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestLocalizerAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
         * ctor
         */
        CBCTestLocalizerAppUi();

        /**
         * symbian 2nd ctor
         */
        void ConstructL();

        /**
         * dtor
         */
        virtual ~CBCTestLocalizerAppUi();

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
        CBCTestLocalizerView*  iView;
    };

#endif // C_BCTESTLOCALIZERAPPUI_H

// End of File
