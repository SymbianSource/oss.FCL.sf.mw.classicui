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
* Description:         Test BC for ScreenClearer control API.
*
*/









#ifndef C_BCTESTSCREENCLEARERAPPUI_H
#define C_BCTESTSCREENCLEARERAPPUI_H

#include <aknviewappui.h>

class CBCTestScreenClearerView;

/**
 *  Application UI class
 */
class CBCTestScreenClearerAppUi : public CAknViewAppUi
    {
public: // Constructors and destructor

    /**
     * ctor
     */
    CBCTestScreenClearerAppUi();

    /**
     * symbian 2nd ctor
     */
    void ConstructL();

    /**
     * dtor
     */
    virtual ~CBCTestScreenClearerAppUi();

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
    CBCTestScreenClearerView*  iView;
    };

#endif // C_BCTESTSCREENCLEARERAPPUI_H


