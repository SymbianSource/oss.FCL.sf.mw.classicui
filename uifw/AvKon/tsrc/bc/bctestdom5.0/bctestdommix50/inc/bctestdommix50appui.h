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
* Description:  declaration of appui.
*
*/


#ifndef C_BCTESTDOMMIX50APPUI_H
#define C_BCTESTDOMMIX50APPUI_H

#include <aknviewappui.h>

class CBCTestDomMix50View;
class CBCTestUtil;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestDomMix50AppUi : public CAknViewAppUi
    {

public: // Constructors and destructor

    /**
     * constructor
     */
    CBCTestDomMix50AppUi();

    /**
     * symbian 2nd constructor
     */
    void ConstructL();

    /**
     * destructor
     */
    virtual ~CBCTestDomMix50AppUi();

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
    CBCTestDomMix50View*  iView;

    /**
     * pointor to the BC Test framework utility.
     * own
     */
    CBCTestUtil*  iTestUtil;

    };

#endif // C_BCTESTDOMMIX50APPUI_H
