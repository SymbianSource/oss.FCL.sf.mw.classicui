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
* Description:  declaration of document
*
*/


#ifndef C_BCTESTDOMAVKONPSLNDOCUMENT_H
#define C_BCTESTDOMAVKONPSLNDOCUMENT_H

#include <eikdoc.h>

class  CEikAppUi;

/**
* CBCTestDomAvkonPslnDocument class.
*/
class CBCTestDomAvkonPslnDocument : public CEikDocument
    {
    
public: 
// Constructors and destructor

    /**
    * Symbian OS two-phased constructor.
    * @return Pointer to created Document class object.
    * @param aApp Reference to Application class object.
    */
    static CBCTestDomAvkonPslnDocument* NewL( CEikApplication& aApp );

    /**
    * Destructor.
    */
    virtual ~CBCTestDomAvkonPslnDocument();

private: 
// Constructors

    /**
    * Overload constructor.
    * @param aApp Reference to Application class object.
    */
    CBCTestDomAvkonPslnDocument( CEikApplication& aApp );

private: 
// From CEikDocument

    /**
    * From CEikDocument, CreateAppUiL.
    * Creates CBCTestDomAvkonPslnAppUi "App UI" object.
    * @return Pointer to created AppUi class object.
    */
    CEikAppUi* CreateAppUiL();

    };

#endif  // C_BCTESTDOMAVKONPSLNDOCUMENT_H

// End of File
