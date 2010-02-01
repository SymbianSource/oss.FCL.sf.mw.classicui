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








#ifndef C_TESTVOLUMESETTINGPAGE_H
#define C_TESTVOLUMESETTINGPAGE_H

#include "bctestcase.h"

class CBCTestVolumeView;
class CBCTestVolumeContainer;

/**
* test case for testing volume setting page.
* @lib bctestutil.lib
*/
class CTestVolumeSettingPage: public CBCTestCase
    {
public:
    /** 
    * symbian NewL
    * @param aView, pointer to the active view
    */
    static CTestVolumeSettingPage* NewL(CBCTestVolumeView* aView);

    /** 
    * symbian NewLC
    * @param aView, pointer to the active view
    */
    static CTestVolumeSettingPage* NewLC(CBCTestVolumeView* aView);

    /** dtor */
    virtual ~CTestVolumeSettingPage();
    
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
    CTestVolumeSettingPage(CBCTestVolumeView* aView);

    /** symbian 2nd phase ctor */
    void ConstructL();

    /** build the necessary test scripts */
    void BuildScriptL();

    /** perform test */
    void TestL();
    
protected: // new
    /** getter of the container */
    CBCTestVolumeContainer*  Container()  const;
    
private: // Data
    CBCTestVolumeView*  iView;      // not own, just reference
    };

#endif // C_TESTVOLUMESETTINGPAGE_H
