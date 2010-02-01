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


#ifndef C_BCTESTTEMPLATEDOCUMENT_H
#define C_BCTESTTEMPLATEDOCUMENT_H

#include <eikdoc.h>

class  CEikAppUi;

/**
* CBCTestTemplateDocument class.
*/
class CBCTestTemplateDocument : public CEikDocument
    {
    public: // Constructors and destructor

        /**
        * Symbian OS two-phased constructor.
        * @return Pointer to created Document class object.
        * @param aApp Reference to Application class object.
        */
        static CBCTestTemplateDocument* NewL( CEikApplication& aApp );

        /**
        * Destructor.
        */
        virtual ~CBCTestTemplateDocument();

    private: // Constructors

        /**
        * Overload constructor.
        * @param aApp Reference to Application class object.
        */
        CBCTestTemplateDocument( CEikApplication& aApp );

    private: // From CEikDocument

        /**
        * From CEikDocument, CreateAppUiL.
        * Creates CBCTestTemplateAppUi "App UI" object.
        * @return Pointer to created AppUi class object.
        */
        CEikAppUi* CreateAppUiL();

    };

#endif  // C_BCTESTTEMPLATEDOCUMENT_H

// End of File
