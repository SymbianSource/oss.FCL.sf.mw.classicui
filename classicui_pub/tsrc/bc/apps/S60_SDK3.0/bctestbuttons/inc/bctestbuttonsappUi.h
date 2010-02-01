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
* Description:         Test BC for Buttons control API.
*
*/









#ifndef C_BCTESTBUTTONSAPPUI_H
#define C_BCTESTBUTTONSAPPUI_H

#include <aknviewappui.h>

class CBCTestButtonsView;

/**
 *  Application UI class
 */
class CBCTestButtonsAppUi : public CAknViewAppUi
    {
public: // Constructors and destructor

    /**
     * ctor
     */
    CBCTestButtonsAppUi();

    /**
     * symbian 2nd ctor
     */
    void ConstructL();

    /**
     * dtor
     */
    virtual ~CBCTestButtonsAppUi();

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
    CBCTestButtonsView*  iView;
    };

#endif // C_BCTESTBUTTONSAPPUI_H


