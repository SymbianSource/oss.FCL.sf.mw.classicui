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
* Description:         Declares test bc for ocr appui.
*
*/









#ifndef C_CBCTESTOCRAPPUI_H
#define C_CBCTESTOCRAPPUI_H

#include <aknviewappui.h>

class CBCTestOCRView;

/**
 * Application UI class
 */
class CBCTestOCRAppUi : public CAknViewAppUi
    {
public: // Constructors and destructor

    /**
     * ctor
     */
    CBCTestOCRAppUi();

    /**
     * symbian 2nd ctor
     */
    void ConstructL();

    /**
     * dtor
     */
    virtual ~CBCTestOCRAppUi();

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
    CBCTestOCRView*  iView;
    
    };

#endif // C_CBCTESTOCRAPPUI_H
