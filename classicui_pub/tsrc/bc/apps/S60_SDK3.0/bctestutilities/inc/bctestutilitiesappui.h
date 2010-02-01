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
* Description:         Test BC for Utilities control API.
*
*/









#ifndef C_BCTESRUTILITIESAPPUI_H
#define C_BCTESRUTILITIESAPPUI_H

#include <aknviewappui.h>

class CBCTestUtilitiesView;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestUtilitiesAppUi : public CAknViewAppUi
    {
public: // Constructors and destructor

    /**
     * constructor
     */
    CBCTestUtilitiesAppUi();

    /**
     * symbian 2nd constructor
     */
    void ConstructL();

    /**
     * destructor
     */
    virtual ~CBCTestUtilitiesAppUi();

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
    CBCTestUtilitiesView*  iView;

    };

#endif // C_BCTESTTEMPLATEAPPUI_H
