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
* Description:  test case of font
*
*/


#ifndef C_CBCTESTDOMFNTLAYCASE_H
#define C_CBCTESTDOMFNTLAYCASE_H

#include "bctestcase.h"

class CBCTestDomFntlayContainer;

/**
* test case for various list classes
*/
class CBCTestDomFntlayCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestDomFntlayCase* NewL( CBCTestDomFntlayContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestDomFntlayCase();
    
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
    CBCTestDomFntlayCase( CBCTestDomFntlayContainer* aContainer );
    
    /**
    * Symbian 2nd constructor
    */
    void ConstructL();
    
    /**
    * Test fontid 
    * 
    */
    void TestFontIdL();
    
    /**
    * Test font Provider
    * 
    */
    void TestFontProviderL();
    
    /**
    * Test font Provider Supplied Metrics
    * 
    */
    void TestProviderSuppliedMetricsL();
    
    
private: // data
        
    /**
     * Pointer to container.
     * not own
     */
    CBCTestDomFntlayContainer* iContainer;
    
    };

#endif // C_CBCTESTDOMFNTLAYCASE_H
