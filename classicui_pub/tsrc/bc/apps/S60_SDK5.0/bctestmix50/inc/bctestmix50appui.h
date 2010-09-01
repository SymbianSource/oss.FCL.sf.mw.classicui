/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         declaration of appui.
*
*/









#ifndef C_BCTESTMIX50APPUI_H
#define C_BCTESTMIX50APPUI_H

#include <aknviewappui.h>

class CBCTestMix50View;
class CBCTestUtil;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestMix50AppUi : public CAknViewAppUi
    {

public: // Constructors and destructor

    /**
     * constructor
     */
    CBCTestMix50AppUi();

    /**
     * symbian 2nd constructor
     */
    void ConstructL();

    /**
     * destructor
     */
    virtual ~CBCTestMix50AppUi();

private:

//From base class CEikAppUi

    /**
     * From CEikAppUi
     * @param aCommand, ID of the command to respond to 
     */
    void HandleCommandL( TInt aCommand );

private: // member data

    /**
     * pointor to the view.
     * own
     */
    CBCTestMix50View*  iView;

    /**
     * pointor to the BC Test framework utility.
     * own
     */
    CBCTestUtil*  iTestUtil;

    };

#endif // C_BCTESTMIX50APPUI_H
