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
* Description:  Define node test case
*
*/


#ifndef C_CBCTESTDOMM3GNODECASE_H
#define C_CBCTESTDOMM3GNODECASE_H

#include "bctestcase.h"

class CBCTestDomM3gContainer;
class CCoeControl;

/**
 * test case for m3g node classes
 */
class CBCTestDomM3gNodeCase : public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestDomM3gNodeCase* NewL( CBCTestDomM3gContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestDomM3gNodeCase();
    
// from CBCTestCase
    
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
    
    /*
     * Test RM3GTransformable API(s).
     */
    void TestRM3GTransformableL();
 
     /*
     * Test RM3GNode API(s).
     */   
    void TestRM3GNodeL();
    
    /*
     * Test RM3GLight API(s).
     */   
    void TestRM3GLightL();

    /*
     * Test RM3GCamera API(s).
     */     
    void TestRM3GCameraL();

    /*
     * Test RM3GGroup API(s).
     */      
    void TestRM3GGroupL();
    
    /*
     * Test RM3GWorld API(s).
     */      
    void TestRM3GWorldL(); 

    /*
     * Test RM3GSprite API(s).
     */      
    void TestRM3GSpriteL(); 

    /*
     * Test RM3Mesh API(s).
     */    
    void TestRM3MeshL(); 
 
    /*
     * Test RM3GMorphingMesh API(s).
     */     
    void TestRM3GMorphingMeshL(); 
    
    /*
     * Test RM3GSkinnedMesh API(s).
     */     
    void TestRM3GSkinnedMeshL();    
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestDomM3gNodeCase( CBCTestDomM3gContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data
    
    /**
     * Pointer to container.
     * not own
     */
    CBCTestDomM3gContainer* iContainer;
    
    };

#endif //C_CBCTESTDOMM3GNODECASE_H

