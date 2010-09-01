/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  extended class for abstruct class declaration
*
*/


#ifndef C_TESTDOMPSLNFWBC_H
#define C_TESTDOMPSLNFWBC_H

#include <pslnfwbasecontainer.h>

/**
 *  Test Class CTestPslnFWBaseContainer 
 */    
class CTestPslnFWBaseContainer : public CPslnFWBaseContainer
    {

public:

    /**
     * C++ default constructor
     */ 
    CTestPslnFWBaseContainer();
    
    /**
     * Symbian 2nd static constructor
     */
    void ConstructL( const TRect& aRect );
    
    /**
     * C++ default destructor
     */ 
    ~CTestPslnFWBaseContainer();
    
    /**
     * Construct ListBox from resource id
     */ 
    void ConstructListBoxL( TInt aResLbxId );
    };


#endif /*C_TESTDOMPSLNFWBC_H*/
