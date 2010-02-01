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









#ifndef C_BCTESTQUERYAPPUI_H
#define C_BCTESTQUERYAPPUI_H

#include <aknviewappui.h>

class CBCTestUtil;

/**
* Application UI class.
*/
class CBCTestQueryAppUi : public CAknViewAppUi
    {
public: // Constructors and destructor
        
    /**
     * Default constructor.
     */
    CBCTestQueryAppUi();
        
    /**
     * Symbian 2nd phase constructor.
     */
    void ConstructL();
        
    /**
     * Destructor.
     */
    virtual ~CBCTestQueryAppUi();

private:

    /**
     * From CEikAppUi, HandleCommandL.
     * Handles the commands.
     * @param aCommand Command to be handled.
     */
    void HandleCommandL( TInt aCommand );

private: // Data

    /**
     * Own
     */
    CBCTestUtil* iTestUtil;

    };

#endif // C_BCTESTQUERYAPPUI_H


