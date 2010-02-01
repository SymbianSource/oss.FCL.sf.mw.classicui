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
* Description:         Test BC for BCPopupChoicelist API.
*
*/









#ifndef C_PBK2TESTAPPUI_H
#define C_PBK2TESTAPPUI_H

#include <aknviewappui.h>

class CBCPopupChoicelistView;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCPopupChoicelistAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
         * ctor
         */
        CBCPopupChoicelistAppUi();

        /**
         * symbian 2nd ctor
         */
        void ConstructL();

        /**
         * dtor
         */
        virtual ~CBCPopupChoicelistAppUi();

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
        CBCPopupChoicelistView*  iView;
    };

#endif // C_PBK2TESTAPPUI_H

// End of File
