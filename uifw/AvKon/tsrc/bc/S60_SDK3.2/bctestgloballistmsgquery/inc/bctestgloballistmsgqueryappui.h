/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  AppUI declaration for BCTestGlobalListMsgQuery.
*
*/

#ifndef BCTESTGLOBALLISTMSGQUERYAPPUI_H
#define BCTESTGLOBALLISTMSGQUERYAPPUI_H

#include <aknviewappui.h>

class CBCTestGlobalListMsgQueryView;

/**
 *  Application UI class
 */
class CBCTestGlobalListMsgQueryAppUi : public CAknViewAppUi
    {
public: // Constructors and destructor
    /**
     * Constructor.
     */
    CBCTestGlobalListMsgQueryAppUi();

    /**
     * Symbian 2nd phase constructor.
     */
    void ConstructL();

    /**
     * Destructor.
     */
    virtual ~CBCTestGlobalListMsgQueryAppUi();

private:
    /**
     * From CEikAppUi.
     * 
     * Handles command.
     * @param aCommand A command id.
     */
    void HandleCommandL( TInt aCommand );

private: // data
    /**
     * Pointer to the view.
     * own
     */
    CBCTestGlobalListMsgQueryView*  iView;
    };

#endif

// End of file
