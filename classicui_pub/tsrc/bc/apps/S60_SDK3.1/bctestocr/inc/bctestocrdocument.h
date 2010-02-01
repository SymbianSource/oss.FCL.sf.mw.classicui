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
* Description:         Declares test bc for ocr document.
*
*/









#ifndef C_CBCTESTOCRDOCUMENT_H
#define C_CBCTESTOCRDOCUMENT_H

#include <eikdoc.h>

class  CEikAppUi;

/**
* CBCTestOCRDocument application class.
*/
class CBCTestOCRDocument : public CEikDocument
    {
public: // Constructors and destructor

    /**
    * Symbian OS two-phased constructor.
    * @return Pointer to created Document class object.
    * @param aApp Reference to Application class object.
    */
    static CBCTestOCRDocument* NewL( CEikApplication& aApp );

    /**
    * Destructor.
    */
    virtual ~CBCTestOCRDocument();

private: // Constructors

    /**
    * Overload constructor.
    * @param aApp Reference to Application class object.
    */
    CBCTestOCRDocument( CEikApplication& aApp );

// From CEikDocument

    /**
    * From CEikDocument, CreateAppUiL.
    * Creates CBCTestOCRAppUi "App UI" object.
    * @return Pointer to created AppUi class object.
    */
    CEikAppUi* CreateAppUiL();

};

#endif  // C_CBCTESTOCRDOCUMENT_H
