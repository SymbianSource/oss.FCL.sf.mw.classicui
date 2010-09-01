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


#ifndef C_BCTESTDOMNOTIFIERDOCUMENT_H
#define C_BCTESTDOMNOTIFIERDOCUMENT_H

#include <eikdoc.h>

class  CEikAppUi;

/**
* CBCDomainTestNotifierDocument class.
*/
class CBCDomainTestNotifierDocument : public CEikDocument
    {
public: 
// Constructors and destructor

    /**
    * Symbian OS two-phased constructor.
    * @return Pointer to created Document class object.
    * @param aApp Reference to Application class object.
    */
    static CBCDomainTestNotifierDocument* NewL( CEikApplication& aApp );

    /**
    * Destructor.
    */
    virtual ~CBCDomainTestNotifierDocument();

private: 
// Constructors

    /**
    * Overload constructor.
    * @param aApp Reference to Application class object.
    */
    CBCDomainTestNotifierDocument( CEikApplication& aApp );

private: 
// From CEikDocument

    /**
    * From CEikDocument, CreateAppUiL.
    * Creates CBCDomainTestNotifierAppUi "App UI" object.
    * @return Pointer to created AppUi class object.
    */
    CEikAppUi* CreateAppUiL();

    };

#endif  // C_BCTESTDOMNOTIFIERDOCUMENT_H

// End of File
