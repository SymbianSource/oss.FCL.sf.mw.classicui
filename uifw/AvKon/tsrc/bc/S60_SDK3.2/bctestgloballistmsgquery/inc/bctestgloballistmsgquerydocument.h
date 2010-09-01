/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Document declaration for BCTestGlobalListMsgQuery.
*
*/

#ifndef BCTESTGLOBALLISTMSGQUERYDOCUMENT_H
#define BCTESTGLOBALLISTMSGQUERYDOCUMENT_H

// INCLUDES
#include <eikdoc.h>

// CONSTANTS

// FORWARD DECLARATIONS
class CEikAppUi;

// CLASS DECLARATION

/**
* CBCTestSettingPageDocument application class.
*/
class CBCTestGlobalListMsgQueryDocument : public CEikDocument
    {
public: // Constructors and destructor
    /**
    * Symbian OS two-phased constructor.
    *
    * @param aApp Reference to Application class object.
    * @return Pointer to created Document class object.
    */
    static CBCTestGlobalListMsgQueryDocument* NewL( CEikApplication& aApp );

    /**
    * Destructor.
    */
    virtual ~CBCTestGlobalListMsgQueryDocument();

private: // Constructors
    /**
    * Overloaded constructor.
    *
    * @param aApp Reference to Application class object.
    */
    CBCTestGlobalListMsgQueryDocument( CEikApplication& aApp );

private: // From CEikDocument
    /**
    * From CEikDocument.
    * Creates CBCTestTemplateAppUi "App UI" object.
    *
    * @return Pointer to created AppUi class object.
    */
    CEikAppUi* CreateAppUiL();
    };

#endif

// End of file
