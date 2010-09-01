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
* Description:  Aid class
*
*/


#ifndef C_CBCTESTMCDLCHANGEOBSERVER_H
#define C_CBCTESTMCDLCHANGEOBSERVER_H

class MCdlChangeObserver;

#include <cdlengine.h>
#include <cdlexplorer.h>
#include <cdluserpackageexplorer.h>

/** 
* inherited from MCdlChangeObserver, for TestCdlEngineL() function.
*/
class CBCTestMCdlChangeObserver : public CBase, public MCdlChangeObserver
    {
public:
    /**
    * Constructor
    */
    CBCTestMCdlChangeObserver();

    /**
    * Destructor
    */
    ~CBCTestMCdlChangeObserver();
    };

/** 
* for test pure virtual class CCdlInstanceExplorerBase.
*/

class CBCTestDomCdlInst : public CCdlInstanceExplorerBase
    {
public:

    /**
    * Constructor
    */
    CBCTestDomCdlInst();

    /**
    * Destructor
    */
    ~CBCTestDomCdlInst();

    /**
    * implement pure virtual function.
    */
    CCdlInstance* CreateInstanceLC(const TCdlRef& aRef, 
                                   const CCdlInstance* aSubLayer);

    /**
    * implement pure virtual function.
    */
    TCdlInstanceComparison CallCompare(const CCdlInstance& aFirst,
                                       const CCdlInstance& aSecond)const;

     /**
    * implement pure virtual function.
    */
    TBool CallIsValid(const CCdlInstance& aInstance)const;

    /**
    * call CCdlInstanceExplorerBase::FindLC().
    */
    void FindLC();
    
    };
    
#endif
