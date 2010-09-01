/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test BC for DomInputMethods control API.
*
*/


#ifndef C_CBCTESTDOMINPUTMETHODSAPPUI_H
#define C_CBCTESTDOMINPUTMETHODSAPPUI_H

#include <aknviewappui.h>

class CBCTestDomInputMethodsView;

/**
 *  Application UI class
 */
class CBCTestDomInputMethodsAppUi : public CAknViewAppUi
    {
public: // Constructors and destructor

    /**
         * ctor
         */
    CBCTestDomInputMethodsAppUi();

    /**
         * symbian 2nd ctor
         */
    void ConstructL();

    /**
         * dtor
         */
    virtual ~CBCTestDomInputMethodsAppUi();

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
    CBCTestDomInputMethodsView*  iView;
    };

#endif 


