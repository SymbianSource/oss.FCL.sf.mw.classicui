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
* Description:         Test utility, an interface of BCTest framework.
*
*/








#ifndef C_CBCTESTENDCASE_H
#define C_CBCTESTENDCASE_H

#include "bctestcase.h"

/**
 * End case class, suite will add the case to the end of case array, with the
 * case, test application will automatically exit.
 */
class CBCTestEndCase: public CBCTestCase
    {
public: 

// constructor and destructor
    
    /**
     * Symbian 2nd phase constructor
     */
    static CBCTestEndCase* NewL();
    
    /**
     * Destructor
     */
    virtual ~CBCTestEndCase();
    
// new functions
    
    /**
     * Build automatic test script.
     */
    void BuildScriptL();
    
private: 

// constructor
    
    /**
     * C++ default constructor
     */    
    CBCTestEndCase();
    
    /**
     * Symbian 2nd phase constructor
     */
    void ConstructL();
        
    };
    
#endif // C_CBCTESTENDCASE_H