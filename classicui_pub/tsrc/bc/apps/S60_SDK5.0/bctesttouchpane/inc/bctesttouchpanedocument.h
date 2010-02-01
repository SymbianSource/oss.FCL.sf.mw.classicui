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
* Description:       
*
*/









#ifndef C_CBCTESTTOUCHPANEDOCUMENT_H
#define C_CBCTESTTOUCHPANEDOCUMENT_H

// INCLUDES
#include <eikdoc.h>

// CONSTANTS

// FORWARD DECLARATIONS
class  CEikAppUi;

// CLASS DECLARATION

/**
* CBCTestTouchPaneDocument application class.
*/
class CBCTestTouchPaneDocument : public CEikDocument
    {
public: // Constructors and destructor

    /**
    * Symbian OS two-phased constructor.
    * @return Pointer to created Document class object.
    * @param aApp Reference to Application class object.
    */
    static CBCTestTouchPaneDocument* NewL( CEikApplication& aApp );

    /**
    * Destructor.
    */
    virtual ~CBCTestTouchPaneDocument();

private: // Constructors

    /**
    * Overload constructor.
    * @param aApp Reference to Application class object.
    */
    CBCTestTouchPaneDocument( CEikApplication& aApp );

private: // From CEikDocument

    /**
    * From CEikDocument, CreateAppUiL.
    * Creates CBCTestTouchPaneAppUi "App UI" object.
    * @return Pointer to created AppUi class object.
    */
    CEikAppUi* CreateAppUiL();

    };

#endif  // C_CBCTESTTOUCHPANEDOCUMENT_H
