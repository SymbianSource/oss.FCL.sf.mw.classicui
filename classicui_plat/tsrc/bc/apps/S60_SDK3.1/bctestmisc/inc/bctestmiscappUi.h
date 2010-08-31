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
* Description:         Test BC for Misc control API.
*
*/









#ifndef C_CBCTESTMISCAPPUI_H
#define C_CBCTESTMISCAPPUI_H

#include <aknviewappui.h>

class CBCTestMiscView;
class CBCTestUtil;

/**
 *  Application UI class
 */
class CBCTestMiscAppUi : public CAknViewAppUi
    {
public: // Constructors and destructor

    /**
     * ctor
     */
    CBCTestMiscAppUi();

    /**
     * symbian 2nd ctor
     */
    void ConstructL();

    /**
     * dtor
     */
    virtual ~CBCTestMiscAppUi();

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
    CBCTestMiscView*  iView;

		/**
     * pointor to the BC Test framework utility.
     * own
     */
        CBCTestUtil*  iTestUtil;
    };

#endif // C_CBCTESTMISCAPPUI_H
