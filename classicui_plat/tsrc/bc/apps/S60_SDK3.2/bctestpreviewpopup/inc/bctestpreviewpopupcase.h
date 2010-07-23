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









#ifndef BCTEST_PREVIEWPOPUPCASE_H
#define BCTEST_PREVIEWPOPUPCASE_H

#include <AknPreviewPopUpObserver.h>
#include <AknPreviewPopUpContentProvider.h>
#include "bctestcase.h"

class CAknPreviewPopUpController;
class CBCTestPreviewPopupContainer;
class CCoeControl;

/**
* test case for various list classes
*/
class CBCTestPreviewPopupCase: public CBCTestCase, 
                               public MAknPreviewPopUpObserver,
                               public MAknPreviewPopUpContentProvider
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestPreviewPopupCase* NewL( CBCTestPreviewPopupContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestPreviewPopupCase();
    
public: // from CBCTestCase
    
    /**
    * Execute corresponding test functions for UI command
    * @param aCmd, UI command
    */
    void RunL( TInt aCmd );

public: // from MAknPreviewPopUpObserver

    void HandlePreviewPopUpEventL(
            CAknPreviewPopUpController* aController,
            TPreviewPopUpEvent aEvent );

public: // from MAknPreviewPopupContentProvider

    void StartContentBuildingL();
    
    void CancelContentBuilding();


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
    void TestFunction();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestPreviewPopupCase( CBCTestPreviewPopupContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
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
    CBCTestPreviewPopupContainer* iContainer;
    
    };

#endif // BCTEST_PREVIEWPOPUPCASE_H