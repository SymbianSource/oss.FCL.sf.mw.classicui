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


#ifndef C_BCTESTMIXMCLAPPUI_H
#define C_BCTESTMIXMCLAPPUI_H

#include <aknviewappui.h>

class CBCTestMixMCLView;
class CBCTestUtil;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 *  @since S60 v5.0
 */
class CBCTestMixMCLAppUi : public CAknViewAppUi
    {

public: // Constructors and destructor

    /**
     * constructor
     */
    CBCTestMixMCLAppUi();

    /**
     * symbian 2nd constructor
     */
    void ConstructL();

    /**
     * destructor
     */
    virtual ~CBCTestMixMCLAppUi();

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
    CBCTestMixMCLView*  iView;

    /**
     * pointor to the BC Test framework utility.
     * own
     */
    CBCTestUtil*  iTestUtil;

    };

#endif // C_BCTESTMIX50APPUI_H
