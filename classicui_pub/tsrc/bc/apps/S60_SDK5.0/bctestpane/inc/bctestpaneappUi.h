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









#ifndef C_BCTESTPANEAPPUI_H
#define C_BCTESTPANEAPPUI_H

#include <aknviewappui.h>

class CBCTestPaneView;
class CBCTestUtil;

/**
 *  Application UI class 
 */
class CBCTestPaneAppUi : public CAknViewAppUi
    {
public: // Constructors and destructor

    /**
     * ctor
     */
    CBCTestPaneAppUi();

    /**
     * symbian 2nd ctor
     */
    void ConstructL();

    /**
     * dtor
     */
    virtual ~CBCTestPaneAppUi();

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
    CBCTestPaneView*  iView;

    /**
     * pointor to BCTesting framework.
     * Own
     */
    CBCTestUtil*  iTestUtil;

    };

#endif // C_BCTESTPANEAPPUI_H

