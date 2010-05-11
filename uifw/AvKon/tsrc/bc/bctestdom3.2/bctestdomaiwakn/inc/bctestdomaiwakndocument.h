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
* Description: 
*
*/

#ifndef C_CBCTESTDOMAIWAKNDOCUMENT_H
#define C_CBCTESTDOMAIWAKNDOCUMENT_H

#include <eikdoc.h>

class  CEikAppUi;

/**
 *  CBCTestDomAiwAknDocument class.
 *  
 *
 *  @code
 *    
 *  @endcode
 *
 *  @lib  
 *  @since S60 v5.0
 */ 

class CBCTestDomAiwAknDocument : public CEikDocument
    {
public: 
    /**
     * Symbian OS two-phased constructor.
     *
     * 
     * @return Pointer to created Document class object.
     * @param aApp Reference to Application class object.     
     */         
        static CBCTestDomAiwAknDocument* NewL( CEikApplication& aApp );

    /**
     * Destructor.
     *
     */         
    virtual ~CBCTestDomAiwAknDocument();

private:  

    /**
     * Overload constructor..
     *
     * @since S60 v5.0
     * @param aApp Reference to Application class object.
     */        
    CBCTestDomAiwAknDocument( CEikApplication& aApp );

// from base class CEikDocument

    /**
     * From CEikDocument.
     * Creates CBCTestDomAiwAknAppUi "App UI" object.
     *
     * @since S60 v5.0
     * @return Pointer to created AppUi class object.
     */
    CEikAppUi* CreateAppUiL();

    };

#endif  // C_CBCTESTDOMAIWAKNDOCUMENT_H

// End of File
