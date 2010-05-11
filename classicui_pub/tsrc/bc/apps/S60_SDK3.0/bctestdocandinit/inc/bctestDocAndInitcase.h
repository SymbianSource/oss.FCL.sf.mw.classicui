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









#ifndef BCTEST_DOCANDINITCASE_H
#define BCTEST_DOCANDINITCASE_H

#include <documenthandler.h>
#include <eikcolib.h>
#include <eikctlib.h>
#include <AknServerApp.h> 

#include "bctestcase.h"

class CBCTestDocAndInitContainer;
class CCoeControl;
class CDocumentHandler;

/**
* test case for various list classes
*/
class CBCTestDocAndInitCase: public CBCTestCase, public MAknServerAppExitObserver
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestDocAndInitCase* NewL( CBCTestDocAndInitContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestDocAndInitCase();
    
public: // from CBCTestCase
    
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
    
    /**
     * Create control or allocate resource for test
     * @param aCmd UI command, maybe you need to do some work 
     * for different outline
     */
    void PrepareCaseL( TInt aCmd );
    
    /**
     * Release resource used in test
     */
    void ReleaseCaseL();
    
    /**
     * Test functions
     */
    void     TestDocument1L();
    void     TestDocument2L();
    void     TestInitializationL();
    void    TestAppUiFactoryL();
    void    TestCoCtlLibraryL();
    void    TestCtlLibraryL();    
    void Cleanup();
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestDocAndInitCase( CBCTestDocAndInitContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
private: // from MAknServerAppExitObserver
    void HandleServerAppExit( TInt aReason );
       
private: // data
    
    /**
     * Pointer to a control, maybe you need one in your test
     * own
     */
    CCoeControl* iControl;

    /**
     * Pointer to container.
     * not own
     */
    CBCTestDocAndInitContainer* iContainer;

    };

#endif // BCTEST_DOCANDINITCASE_H