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
* Description:         Emulate key or pointer event.
*
*/









#ifndef C_CBCTESTKEYFEEDER_H
#define C_CBCTESTKEYFEEDER_H

#include    <eikenv.h>

#include    "bctestutil.h"

class CBCTestSuite;
class CEikonEnv;

/**
 *  CBCTestKeyFeeder for autotests
 */
class CBCTestKeyFeeder : public CBase
    {
public: 

// Constructors and destructor
    
    /**
     * C++ default constructor.
     */
    CBCTestKeyFeeder();    

    /**
     * Destructor.
     */
    virtual ~CBCTestKeyFeeder();

// New functions 

    /**
     * Periodic function called every 0.1 seconds
     * The function is a callback used by CPeriodic, so it have
     * to conform to demanded format, it has to return TInt.
     * @param aThis Pointer to this (CBCTestKeyFeeder)
     * @return Always return 0
     */
    static TInt PeriodicKeyFeederL(TAny* aThis);

    /**
     * Handles autotest commands (big switch case)
     */
    void HandleAutoCommandL();

    /**
     * Pauses timer temporarily
     */
    void PauseTimer();

    /**
     * Resumes timer
     */
    void ResumeTimer();

    /*
     * Start auto test
     * @param aAutoTest, a structure containes autotest scripts of every 
     * test case.
     */
    void StartAutoTestL(SAutoTest* aAutoTest);

    /**
     * Set test suite pointer, key feeder will pass some event to suite to 
     * handle durint automatic test process.
     */
    void SetSuite( CBCTestSuite* aSuite );

private: 

// new functions   

    /**
     * Simulates key down press using window server
     * @param aScanCode
     */
    void KeyDown(TInt aScanCode);

    /**
     * Simulates key down press using window server
     * @param aScanCode
     */
    void KeyUp(TInt aScanCode);

    /**
     * Simulates key press using window server
     * @param aScanCode
     */
    void KeyPress(TInt aCode, TInt aScanCode);
	
    /**
     * Simulates pointer event
     * @param aEvent
     */
	void PointerEvent(TRawEvent& aEvent);
		
private: //data
    
    /**
     * Not Own.
     */
    CBCTestSuite* iSuite;
    
    /**
     * Not Own.
     */
    CEikonEnv* iEikEnv;
    
    /**
     * For changing delays between key feeds
     */
    TInt iTickCount;
    TInt iTickCounter;

    /**
     * active object
     */
    CPeriodic* iPeriodic;
    
    /**
     * Not Own.
     */    
    SAutoTest* iAutoTest; 
    
    /**
     * Not Own.
     */
    const TInt* iScriptCommands;
    
    TInt iScriptIndex;
    TInt iIndex;

    TInt iWaitCount;            
    TInt iRepeat;
    TInt iCommand;
    TInt iRepeatCommand;

    /**
     * for key down presses
     */
    TBool iKeyDown;
    
    /**
     * for key up presses
     */
    TBool iKeyUp;
    
    /**
     * State of modifier keys
     */
    TUint iModifiers;    
    TUint iOldModifiers;

    TInt iOutlineCount;
    
    TBool iTimerPaused;

    /**
     * conditional sequence support
     */
    TBool      iDoElse;
    TInt       iIfCount;
    
    };

#endif // C_CBCTESTKEYFEEDER_H
