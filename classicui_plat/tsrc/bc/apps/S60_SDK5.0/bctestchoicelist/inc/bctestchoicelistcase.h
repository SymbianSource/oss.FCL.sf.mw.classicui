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









#ifndef C_PBK2TESTCASE_H
#define C_PBK2TESTCASE_H

#include <aknlongtapdetector.h>
#include "bctestcase.h"

class CBCPopupChoicelistContainer;
class CCoeControl;

/**
* test case for various list classes
*/
class CBCPopupChoicelistCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCPopupChoicelistCase* NewL( CBCPopupChoicelistContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCPopupChoicelistCase();
    
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
     * Test functions
     */
    void TestFunctionL();
    void TestDetectorFunctionL();
    void TestPopMenuFunctionL();
    
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCPopupChoicelistCase( CBCPopupChoicelistContainer* aContainer );
    
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
    CBCPopupChoicelistContainer* iContainer;
    
    };

class CBCTapDetectorCallBack : public CBase, public MAknLongTapDetectorCallBack
{
	public:
	void HandleLongTapEventL( const TPoint& aPenEventLocation,
														const TPoint& aPenEventScreenLocation );

};
#endif // C_PBK2TESTCASE_H