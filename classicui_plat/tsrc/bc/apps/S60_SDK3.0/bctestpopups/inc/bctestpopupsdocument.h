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
* Description:         Declares test bc for popups control document.
*
*/









#ifndef C_CBCTESTPOPUPSDOCUMENT_H
#define C_CBCTESTPOPUPSDOCUMENT_H

#include <eikdoc.h>

class  CEikAppUi;

/**
* CBCTestPopupsDocument application class.
*/
class CBCTestPopupsDocument : public CEikDocument
    {
public: // Constructors and destructor

    /**
    * Symbian OS two-phased constructor.
    * @return Pointer to created Document class object.
    * @param aApp Reference to Application class object.
    */
    static CBCTestPopupsDocument* NewL( CEikApplication& aApp );

    /**
    * Destructor.
    */
    virtual ~CBCTestPopupsDocument();

private: // Constructors

    /**
    * Overload constructor.
    * @param aApp Reference to Application class object.
    */
    CBCTestPopupsDocument( CEikApplication& aApp );

// From CEikDocument

    /**
    * From CEikDocument, CreateAppUiL.
    * Creates CBCTestPopupsAppUi "App UI" object.
    * @return Pointer to created AppUi class object.
    */
    CEikAppUi* CreateAppUiL();

};

#endif  // C_CBCTESTPOPUPSDOCUMENT_H
