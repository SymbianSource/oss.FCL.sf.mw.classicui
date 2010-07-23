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
* Description:         test case
*
*/









#ifndef BCTEST_MISCELLCASE_H
#define BCTEST_MISCELLCASE_H

#include <eikdialg.h>
#include "bctestcase.h"

class CBCTesteikbctrlContainer;
class CCoeControl;

/**
* test case for various list classes
*/

class CBCTestMiscellCase: public CEikDialog 
    {
public: // constructor and destructor
    friend class CBCTesteikbdialgCase;  
    friend class CBCTesteikbctrlContainer;
    
    /**
     * C++ default constructor
     */
     CBCTestMiscellCase();

     
    /**
     * Symbian 2nd constructor
     */
     void ConstructL();

    /**
    * Destructor
    */
    virtual ~CBCTestMiscellCase();
 
    };

#endif // BCTEST_MISCELLCASE_H