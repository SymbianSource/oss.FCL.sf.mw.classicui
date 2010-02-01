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
* Description:  Define test case
*
*/


#ifndef C_CBCTESTDOMM3GCASE_H
#define C_CBCTESTDOMM3GCASE_H

#include "bctestcase.h"

class CBCTestDomM3gContainer;
class CCoeControl;

/**
* test case for various list classes
*/
class CBCTestDomM3gCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestDomM3gCase* NewL( CBCTestDomM3gContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestDomM3gCase();
    
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
     * Test CM3gLoader API(s).
     */
    void TestCM3gLoaderL();

    /*
     * Test CM3GRenderingContext API(s).
     */    
    void TestCM3GRenderingContextL();
    
    /*
     * Test RM3gObject API(s).
     */
    void TestRM3gObjectL(); 
    
    /*
     * Test RM3GBackground API(s).
     */    
    void TestRM3GBackgroundL(); 

    /*
     * Test RM3GAppearance API(s).
     */     
    void TestRM3GAppearanceL();  

    /*
     * Test RM3GCompositingMode API(s).
     */    
    void TestRM3GCompositingModeL(); 
    
    /*
     * Test RM3GFog API(s).
     */
    void TestRM3GFogL();

    /*
     * Test RM3GMaterial API(s).
     */    
    void TestRM3GMaterialL();
    
    /*
     * Test RM3GPolygonMode API(s).
     */ 
    void TestRM3GPolygonModeL();

    /*
     * Test RM3GTexture API(s).
     */     
    void TestRM3GTextureL();

    /*
     * Test RM3GKeyframeSequence API(s).
     */     
    void TestRM3GKeyframeSequenceL();

    /*
     * Test RM3GVertexBuffer API(s).
     */     
    void TestRM3GVertexBufferL();

    /*
     * Test RM3GVertexArray API(s).
     */   
    void TestRM3GVertexArrayL();
    
    /*
     * Test RM3GTriangleStripArray API(s).
     */     
    void TestRM3GTriangleStripArrayL();
    
    /*
     * Test RM3GIndexBuffer API(s).
     */ 
    void TestRM3GIndexBufferL();

    /*
     * Test RM3GAnimationController API(s).
     */     
    void TestRM3GAnimationControllerL();    

    /*
     * Test RM3GImage API(s).
     */      
    void TestRM3GImageL();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestDomM3gCase( CBCTestDomM3gContainer* aContainer );
    
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

#endif //C_CBCTESTDOMM3GCASE_H
