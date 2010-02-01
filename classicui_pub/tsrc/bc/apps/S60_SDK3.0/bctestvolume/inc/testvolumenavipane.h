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
* Description:         test bc of the volume control API(s)
*
*/








#ifndef C_TESTVOLUMENAVIPANE_H
#define C_TESTVOLUMENAVIPANE_H

#include "bctestcase.h"

class CBCTestVolumeView;
class CBCTestVolumeContainer;
class CAknVolumeControl;

/**
* test case for testing volume control in navigation pane.
* @lib bctestutil.lib
*/
class CTestVolumeNaviPane: public CBCTestCase
    {
public:        
    /**
    * symbian NewL
    * @param aView, pointer to the active view.
    */
    static CTestVolumeNaviPane* NewL(CBCTestVolumeView* aView);

    /**
    * symbian NewLC
    * @param aView, pointer to the active view.
    */
    static CTestVolumeNaviPane* NewLC(CBCTestVolumeView* aView);

    /** dtor */
    virtual ~CTestVolumeNaviPane();
    
    /** 
    * from CBCTestCase 
    * @param aCmd, command ID this test case will response.
    */
    virtual void RunL(int aCmd);
    
protected: // new

    /**
    * do necessary setup things.
    */
    virtual void SetupL();

    /**
    * do necessary tear down things.
    */
    virtual void TearDownL();
    
    /**
    * ctor
    * @param aView, pointer to the active view.
    */
    CTestVolumeNaviPane(CBCTestVolumeView* aView);

    /**
    * symbian 2nd phase ctor
    */
    void ConstructL();

private: //new
    /** create the test scripts for this test case */
    void ScriptCreateL();

    /** test volume control creation API(s) related to navigation pane.*/
    void TestCreateL();

    /** 
    * performa a set of normal operation for the volume control
    * including volume adjustment
    */
    void TestNormalL();

    /** test create the volume control from IDLE state */
    void TestIdleL();

    /** test create the volume control from ICON_SET */
    void TestIconL();

    /** test navigation pane event for the volume API */
    void TestNaviEventL();

    /** 
    * try to create the volume control in the navigation pane
    * @param aResourceID, a resource ID for the volume control
    * @param aLabelID, a label ID for the description label in the main pane.
    */
    void TryCreateL(TInt aResourceID, TInt aLabelID);

    /**
    * try to adjust the volume value for the volume control.
    */
    void TryAdjustL();
    
    /** getter for the container */
    CBCTestVolumeContainer*  Container()  const;
    
private: // Data
    CBCTestVolumeView*  iView;       // not own, just reference
    CAknVolumeControl* iVolume;     // own
    };

#endif // C_TESTVOLUMENAVIPANE_H