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
* Description:         Test BC for Editor control API.
*
*/









#ifndef C_BCTESTEDITORAPPUI_H
#define C_BCTESTEDITORAPPUI_H

#include <aknviewappui.h>

class CBCTestEditorView;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestEditorAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
         * ctor
         */
        CBCTestEditorAppUi();

        /**
         * symbian 2nd ctor
         */
        void ConstructL();

        /**
         * dtor
         */
        virtual ~CBCTestEditorAppUi();

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
        CBCTestEditorView*  iView;
    };

#endif // C_BCTESTEditorAPPUI_H

// End of File
