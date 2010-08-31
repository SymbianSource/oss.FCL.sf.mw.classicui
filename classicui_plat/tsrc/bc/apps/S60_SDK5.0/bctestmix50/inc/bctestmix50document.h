/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         declaration of document
*
*/









#ifndef C_BCTESTMIX50DOCUMENT_H
#define C_BCTESTMIX50DOCUMENT_H

#include <eikdoc.h>

class  CEikAppUi;

/**
 * CBCTestMix50Document class.
 */
class CBCTestMix50Document : public CEikDocument
    {

public: // Constructors and destructor

    /**
     * Symbian OS two-phased constructor.
     * @return Pointer to created Document class object.
     * @param aApp Reference to Application class object.
     */
    static CBCTestMix50Document* NewL( CEikApplication& aApp );

    /**
     * Destructor.
     */
    virtual ~CBCTestMix50Document();

private: // Constructors

    /**
     * Overload constructor.
     * @param aApp Reference to Application class object.
     */
    CBCTestMix50Document( CEikApplication& aApp );

// From CEikDocument

    /**
     * From CEikDocument, CreateAppUiL.
     * Creates CBCTestMix50AppUi "App UI" object.
     * @return Pointer to created AppUi class object.
     */
    CEikAppUi* CreateAppUiL();

    };

#endif  // C_BCTESTMIX50DOCUMENT_H
