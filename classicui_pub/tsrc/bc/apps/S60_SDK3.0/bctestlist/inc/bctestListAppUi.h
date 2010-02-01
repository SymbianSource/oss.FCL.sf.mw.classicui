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
* Description:         AppUi
*
*/








#ifndef C_CBCTESTLISTAPPUI_H
#define C_CBCTESTLISTAPPUI_H

#include <aknviewappui.h>

class CBCTestUtil;

/**
* Application UI class.
*/
class CBCTestListAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor
        
        /**
        * Default constructor.
        */
        CBCTestListAppUi();
        
        /**
        * Symbian 2nd phase constructor.
        */
        void ConstructL();
        
        /**
        * Destructor.
        */
        virtual ~CBCTestListAppUi();

    private:
        /**
        * From CEikAppUi, HandleCommandL.
        * Handles the commands.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL( TInt aCommand );

    private: // Data
        TInt iCurrentOutline;

        // Container for screen capturing.
        CBCTestUtil* iTestUtil;

    };

#endif // C_CBCTESTLISTAPPUI_H
