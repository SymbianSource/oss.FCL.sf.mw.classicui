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
* Description:  the header file of appui
*
*/


#ifndef C_CBCTESTDOMFNTLAYAPPUI_H
#define C_CBCTESTDOMFNTLAYAPPUI_H

#include <aknviewappui.h>

class CBCTestDomFntlayView;

class CBCTestDomFntlayAppUi : public CAknViewAppUi
    {
public: // Constructors and destructor

    /**
    * ctor
    */
    CBCTestDomFntlayAppUi();

    /**
    * symbian 2nd ctor
    */
    void ConstructL();

    /**
    * dtor
    */
    virtual ~CBCTestDomFntlayAppUi();

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
    CBCTestDomFntlayView*  iView;
    };

#endif // C_CBCTESTDOMFNTLAYAPPUI_H
