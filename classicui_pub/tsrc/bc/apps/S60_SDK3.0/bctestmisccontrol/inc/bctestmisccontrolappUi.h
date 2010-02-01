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
* Description:         Declares test bc for misc control appui.
*
*/









#ifndef C_CBCTESTMISCCONTROLAPPUI_H
#define C_CBCTESTMISCCONTROLAPPUI_H

#include <aknviewappui.h>

class CBCTestMiscControlView;

/**
 * Application UI class
 */
class CBCTestMiscControlAppUi : public CAknViewAppUi
    {

public: // Constructors and destructor

    /**
     * ctor
     */
    CBCTestMiscControlAppUi();

    /**
     * symbian 2nd ctor
     */
    void ConstructL();

    /**
     * dtor
     */
    virtual ~CBCTestMiscControlAppUi();

private:

// From CEikAppUi
    /**
     * From CEikAppUi
     */
    void HandleCommandL( TInt aCommand );

private: // data

    /**
     * pointer to the view.
     * own
     */
    CBCTestMiscControlView*  iView;
    
    };

#endif // C_CBCTESTMISCCONTROLAPPUI_H
