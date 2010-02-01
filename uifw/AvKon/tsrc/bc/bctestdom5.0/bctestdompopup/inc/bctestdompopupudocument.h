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


#ifndef C_BCTESTDOMAPOPUPDOCUMENT_H
#define C_BCTESTDOMAPOPUPDOCUMENT_H

#include <eikdoc.h>

class  CEikAppUi;

/**
* CBCDomainTestPopupDocument class.
*/
class CBCDomainTestPopupDocument : public CEikDocument
    {
    public: // Constructors and destructor

        /**
        * Symbian OS two-phased constructor.
        * @return Pointer to created Document class object.
        * @param aApp Reference to Application class object.
        */
        static CBCDomainTestPopupDocument* NewL( CEikApplication& aApp );

        /**
        * Destructor.
        */
        virtual ~CBCDomainTestPopupDocument();

    private: // Constructors

        /**
        * Overload constructor.
        * @param aApp Reference to Application class object.
        */
        CBCDomainTestPopupDocument( CEikApplication& aApp );

    private: // From CEikDocument

        /**
        * From CEikDocument, CreateAppUiL.
        * Creates CBCDomainTestPopupAppUi "App UI" object.
        * @return Pointer to created AppUi class object.
        */
        CEikAppUi* CreateAppUiL();

    };

#endif  // C_BCTESTDOMAPOPUPDOCUMENT_H

// End of File
