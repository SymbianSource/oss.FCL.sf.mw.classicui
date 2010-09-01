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
* Description:         Test BC for Grids control API.
*
*/









#ifndef C_BCTESTGRIDSAPPUI_H
#define C_BCTESTGRIDSAPPUI_H

#include <aknviewappui.h>

class CBCTestGridsView;

/**
 *  Application UI class
 */
class CBCTestGridsAppUi : public CAknViewAppUi
    {
public: // Constructors and destructor

    /**
     * ctor
     */
    CBCTestGridsAppUi();

    /**
     * symbian 2nd ctor
     */
    void ConstructL();

    /**
     * dtor
     */
    virtual ~CBCTestGridsAppUi();

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
    CBCTestGridsView*  iView;
    };

#endif // C_BCTESTGRIDSAPPUI_H

