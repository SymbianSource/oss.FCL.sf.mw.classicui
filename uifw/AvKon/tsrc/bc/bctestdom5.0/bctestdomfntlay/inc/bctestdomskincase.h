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
* Description:  test case 
*
*/


#ifndef C_CBCTESTDOMSKINCASE_H
#define C_CBCTESTDOMSKINCASE_H

#include "bctestcase.h"

/**
* test case for various list classes
*/
class CBCTestDomSkinCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestDomSkinCase* NewL( );
    
    /**
    * Destructor
    */
    virtual ~CBCTestDomSkinCase();
    
    // from CBCTestDomCase
    
    /**
    * Execute corresponding test functions for UI command
    * @param aCmd, UI command
    */
    void RunL( TInt aCmd );

protected: // new functions
    
    /**
    * Build autotest script
    */
    void BuildScriptL();
            
private: // constructor
    
    /**
    * C++ default constructor
    */
    CBCTestDomSkinCase(  );
    
    /**
    * Symbian 2nd constructor
    */
    void ConstructL();
    
    /**
    * Test EffectAnim
    */
    void TestEffectAnimL();
    
    /**
    * Test ItemDef
    */
    void TestItemDefL();
    
    /**
    * Test ItemDef,because a lot of APIs
    */
    void TestItemDef2L();
    
    /**
    * Test PkgID
    */
    void TestPkgIDL();
    
    /**
    * Test PointerStore
    */
    void TestPointerStoreL();
    
    /**
    * Test RendererWrapper
    */
    void TestRendererWrapperL();
    
    /**
    * Test SrvChunkLookup
    */
    void TestSrvChunkLookupL(); 
    
    /**
    * Test SrvChunkLookup
    */
    void TestSrvClientL(); 
    
    /**
    * Test SrvSkinInformationPkg
    */
    void TestSrvSkinInformationPkgL(); 
    
    };

#endif // C_CBCTESTDOMSKINCASE_H
