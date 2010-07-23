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
* Description:         document
*
*/









#ifndef C_BCTESTQUERYDOCUMENT_H
#define C_BCTESTQUERYDOCUMENT_H

#include <akndoc.h>

class  CEikAppUi;

/**
* CBCTestQueryDocument application class.
*/
class CBCTestQueryDocument : public CAknDocument
    {
public: // Constructors and destructor

    /**
     * Symbian two-phased constructor.
     * @return Pointer to created Document class object.
     * @param aApp Reference to Application class object.
     */
    static CBCTestQueryDocument* NewL( CEikApplication& aApp );

    /**
     * Destructor.
     */
    virtual ~CBCTestQueryDocument();

    /**
     * Overload constructor.
     * @param aApp Reference to Application class object.
     */
    CBCTestQueryDocument( CEikApplication& aApp );

    /**
     * Symbian 2nd phase constructor.
     */
    void ConstructL();

private: // From CEikDocument

    /**
     * From CEikDocument, CreateAppUiL.
     * Creates CBCTestQueryAppUi "App UI" object.
     * @return Pointer to created AppUi class object.
     */
    CEikAppUi* CreateAppUiL();

    };

#endif // C_BCTESTQUERYDOCUMENT_H

