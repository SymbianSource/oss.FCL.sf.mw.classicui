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
* Description:         Document
*
*/








#ifndef C_CBCTESTLISTDOCUMENT_H
#define C_CBCTESTLISTDOCUMENT_H

#include <akndoc.h>

class  CEikAppUi;

/**
* CBCTestListDocument application class.
*/
class CBCTestListDocument : public CAknDocument
    {
    public: // Constructors and destructor

        /**
        * Symbian two-phased constructor.
        * @return Pointer to created Document class object.
        * @param aApp Reference to Application class object.
        */
        static CBCTestListDocument* NewL( CEikApplication& aApp );

        /**
        * Destructor.
        */
        virtual ~CBCTestListDocument();

        /**
        * Overload constructor.
        * @param aApp Reference to Application class object.
        */
        CBCTestListDocument( CEikApplication& aApp );

        /**
        * Symbian 2nd phase constructor.
        */
        void ConstructL();

    private: // From CEikDocument

        /**
        * From CEikDocument, CreateAppUiL.
        * Creates CBCTestListAppUi "App UI" object.
        * @return Pointer to created AppUi class object.
        */
        CEikAppUi* CreateAppUiL();

    };

#endif // C_CBCTESTLISTDOCUMENT_H
