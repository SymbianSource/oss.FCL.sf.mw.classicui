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
* Description:         test bc for the volume control API(s)
*
*/








#ifndef C_TESTAKNVIEWAPPUI_H
#define C_TESTAKNVIEWAPPUI_H

#include "bctestcase.h"

class CAknViewAppUi;

/**
* test case for testing volume setting page.
*/
class CBCTestAknViewAppUi: public CBCTestCase
    {
public:
    /** 
    * symbian NewL
    * @param aView, pointer to the active view
    */
    static CBCTestAknViewAppUi* NewL(CAknViewAppUi* aUI, TUid aViewID);

    /** dtor */
    virtual ~CBCTestAknViewAppUi();
    
    /**
    * from CBCTestCase
    */
    virtual void RunL(int aCmd);
    
protected: // new
    /** do necessary setup things. */
    virtual void SetupL();

    /** do necessary teardown things. */
    virtual void TearDownL();
    
    /** ctor */
    CBCTestAknViewAppUi(CAknViewAppUi* aUI, TUid aViewID);

    /** symbian 2nd phase ctor */
    void ConstructL();

    /** build the necessary test scripts */
    void BuildScriptL();

    /** perform test */
    void TestL();

    void TestActiateViewL();

    void TestViewFacilityL();

    void TestSplitViewL();

    void TestOthersL();
    
private:

//data

    CAknViewAppUi* iUI;            //not own
    TUid           iViewID;
    };

#endif // C_TESTAKNVIEWAPPUI_H
