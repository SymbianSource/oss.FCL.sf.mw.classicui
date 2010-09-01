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
* Description:         Emulate key and pointer event.
*
*/








#include <eikon.hrh>

#include "AutotestCommands.h" // test commands are defined in here
#include "bctestkeyfeeder.h"
#include "bctestlogger.h"
#include "bctestsuite.h"

const TInt KInitDelay = 1000000; // 1 second
const TInt KInterval = 100000; // 1/10 second
const TInt KTickCount = 10; // default one second between key feeds
const TText KKey1 = '1';
const TText KKey2 = '2';
const TText KKey3 = '3';
const TText KKey4 = '4';
const TText KKey5 = '5';
const TText KKey6 = '6';
const TText KKey7 = '7';
const TText KKey8 = '8';
const TText KKey9 = '9';
const TText KKey0 = '0';
const TText KKeyAsterisk = '*';
const TText KKeyHash = '#';

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// C++ default constructor
// -----------------------------------------------------------------------------
//
CBCTestKeyFeeder::CBCTestKeyFeeder()
    {
    }

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
CBCTestKeyFeeder::~CBCTestKeyFeeder()
    {
    if ( iPeriodic )
        {
        iPeriodic->Cancel();
        delete iPeriodic;
        }
    }

// -----------------------------------------------------------------------------
// CBCTestKeyFeeder::StartAutoTestL
// Initialize member variables and start timer.
// -----------------------------------------------------------------------------
//
void CBCTestKeyFeeder::StartAutoTestL( SAutoTest* aAutoTest )
    {    
    if ( aAutoTest )
        {
        iAutoTest = aAutoTest;        
        iScriptCommands = iAutoTest->scripts[0];        
        }    
    if ( !iAutoTest || !iScriptCommands )
        {
        return;
        }   
    
    iSuite->HandleTestEventL( ETestCaseStart, iScriptIndex );
    
    iPeriodic=CPeriodic::NewL( CActive::EPriorityHigh );
    // Start periodic function after 1 seconds and after that call
    // it every 1/10th of second    
    iPeriodic->Start( KInitDelay, KInterval, TCallBack( PeriodicKeyFeederL, this ) );

    // member variables don't need to be cleared before use,
    // but do it anyway - just in case
    iIndex = 0;
    iScriptIndex = 0;
    iCommand = 0;
    iRepeatCommand = 0;
    iRepeat = 0;
    iWaitCount = 0;
    
    iTickCount = KTickCount;
    iTickCounter = iTickCount;

    iKeyUp = EFalse;
    iKeyDown = EFalse;
    
    // ensure sane values for conditional stuff
    iIfCount = 0;    
    
    if ( !iEikEnv )
        {
        iEikEnv = CEikonEnv::Static();
        }    
    }

// -----------------------------------------------------------------------------
// CBCTestKeyFeeder::PeriodicKeyFeeder
// This method is called every 0.1 seconds, calls HandleAutoCommand
// -----------------------------------------------------------------------------
//
TInt CBCTestKeyFeeder::PeriodicKeyFeederL( TAny* aThis )
    {
    CBCTestKeyFeeder* feeder = 
        static_cast<CBCTestKeyFeeder*>( aThis );

    feeder->HandleAutoCommandL();
    return 0;
    }

// -----------------------------------------------------------------------------
// CBCTestKeyFeeder::HandleAutoCommand
// Does the actual key feeding
// -----------------------------------------------------------------------------
//
void CBCTestKeyFeeder::HandleAutoCommandL()
    {    
    if ( iTimerPaused ) // timer paused, do nothing
        {
        return;
        }
    if ( iTickCounter > 0 )
        {
        iTickCounter--;
        return; // tick count not yet full, do nothing
        }
    iTickCounter=iTickCount; // reset tick counter and continue

    //commands in one script done
    if ( iIndex >= iAutoTest->countArray[iScriptIndex] )
        {
        iSuite->HandleTestEventL( ETestCaseEnd, iScriptIndex );
        iScriptIndex++;      
        TBool continueRun = ETrue;        
        if ( iScriptIndex >= iAutoTest->scriptCount ) // all scripts done
            {
            continueRun = EFalse;            
            }
        else
            {            
            iScriptCommands = iAutoTest->scripts[iScriptIndex];            
            iIndex = 0; 
            if ( !iScriptCommands )
                {                
                iSuite->HandleTestEventL( ETestCaseNoScript, iScriptIndex );
                iIndex = iAutoTest->countArray[iScriptIndex];              
                }
            else
                {
                iSuite->HandleTestEventL( ETestCaseStart, iScriptIndex );
                }
            }        
        
        if ( iIfCount != 0 )
            {
            iSuite->HandleTestEventL( ETestCaseUnbalancedIf, iScriptIndex - 1 );            
            iIfCount = 0;
            }
        
        if ( !continueRun )
            {
            iPeriodic->Cancel(); // stop periodic timer
            }
                
        return;
        }

    if ( iWaitCount > 0 ) // still waiting (WAIT command)
        {
        iWaitCount--;
        return;    // waiting - do nothing
        }

    if ( iRepeat == 0 ) // not repeating, parse next command
        {
        iCommand = iScriptCommands[iIndex];
        iIndex++;
        }
    else // still doing REPEAT
        {
        iCommand = iRepeatCommand; // command being repeated
        iRepeat--;
        }
    
    switch ( iCommand )
        {
        case LeftCBA:
            KeyPress( EKeyDevice0, EStdKeyDevice0 );
            break;
        case RightCBA:
            KeyPress( EKeyDevice1, EStdKeyDevice1 );
            break;
        case KeyOK:
            KeyPress( EKeyDevice3, EStdKeyDevice3 );
            break;
        case Up:
            KeyPress( EKeyUpArrow, EStdKeyUpArrow );
            break;
        case Down:
            KeyPress( EKeyDownArrow, EStdKeyDownArrow );
            break;
        case Left:
            KeyPress( EKeyLeftArrow, EStdKeyLeftArrow );
            break;
        case Right:
            KeyPress( EKeyRightArrow, EStdKeyRightArrow );
            break;
        case Key1:
            KeyPress( KKey1, KKey1 );
            break;
        case Key2:
            KeyPress( KKey2, KKey2 );
            break;
        case Key3:
            KeyPress( KKey3, KKey3 );
            break;
        case Key4:
            KeyPress( KKey4, KKey4 );
            break;
        case Key5:
            KeyPress( KKey5, KKey5 );
            break;
        case Key6:
            KeyPress( KKey6, KKey6 );
            break;
        case Key7:
            KeyPress( KKey7, KKey7 );
            break;
        case Key8:
            KeyPress( KKey8, KKey8 );
            break;
        case Key9:
            KeyPress( KKey9, KKey9 );
            break;
        case Key0:
            KeyPress( KKey0, KKey0 );
            break;
        case KeyAsterisk:
            KeyPress( KKeyAsterisk, EStdKeyNkpAsterisk );
            break;
        case KeyHash:
            KeyPress( KKeyHash, EStdKeyHash );
            break;
        case KeyApplication:
            KeyPress( EKeyApplication, EStdKeyApplication0 );
            break;
        case KeyPhoneSend:
            KeyPress( EKeyPhoneSend, EStdKeyYes );
            break;
        case KeyPhoneEnd:
            KeyPress( EKeyPhoneEnd, EStdKeyNo );
            break;
        case KeyPower:
            KeyPress( EKeyPowerOff, EStdKeyDevice2 );
            break;
        case KeyVoice:
            KeyPress( EKeySide, EStdKeyDevice6 );
            break;
        case KeyBackspace:
            KeyPress( EKeyBackspace, EStdKeyBackspace );
            break;
        case KeyABC:  // may not work as ABC key, should work as shift, tough
            KeyPress( EStdKeyRightShift, EStdKeyRightShift );
            break;
        case GripOpen:
            KeyPress( EKeyGripOpen, EStdKeyDevice4 );
            break;
        case GripClose:
            KeyPress( EKeyGripClose, EStdKeyDevice5 );
            break;
        case REPEAT: // one round missed because no commands executed
            iRepeatCommand = iScriptCommands[iIndex++];
            iRepeat = iScriptCommands[iIndex++];
            break;
        case WAITCOMMAND:
            iWaitCount = iScriptCommands[iIndex++];
            break;        
        case SETTICKCOUNT:
            iTickCount = iScriptCommands[iIndex++];
            iTickCounter = iTickCount;
            break;
        case JUSTKEYDOWN:
            iKeyDown = ETrue;
            break;
        case JUSTKEYUP:
            iKeyUp = ETrue;            
            break;        
        case PointerDown:
        	{
        	TInt pointerX = iScriptCommands[iIndex++];
        	TInt pointerY = iScriptCommands[iIndex++];
        	TRawEvent event;
        	event.Set( TRawEvent::EButton1Down, pointerX, pointerY );
        	PointerEvent( event );
        	}
        	break;
        case PointerUp:    
        	{
        	TInt pointerX = iScriptCommands[iIndex++];
        	TInt pointerY = iScriptCommands[iIndex++];
        	TRawEvent event;
        	event.Set( TRawEvent::EButton1Up, pointerX, pointerY );
        	PointerEvent( event );
        	}
            break;
        case PointerMove:
	    	{
        	TInt pointerX = iScriptCommands[iIndex++];
        	TInt pointerY = iScriptCommands[iIndex++];
        	TRawEvent event;
        	event.Set( TRawEvent::EPointerMove, pointerX, pointerY );
        	PointerEvent( event );
	    	break;	
	    	}        
        default:
            break;
        }
    }

/******************* autotest key feeder implementations **********************/

// -----------------------------------------------------------------------------
// CBCTestKeyFeeder::KeyDown
// -----------------------------------------------------------------------------
//
void CBCTestKeyFeeder::KeyDown( TInt aScanCode )
    {
    if ( aScanCode == EStdKeyRightShift )
        {
        iOldModifiers = iEikEnv->WsSession().GetModifierState();
        iModifiers = EModifierShift | iOldModifiers;
        }
    
    TRawEvent event;
    event.Set( TRawEvent::EKeyDown, aScanCode );
    iEikEnv->WsSession().SimulateRawEvent( event );
    }

// -----------------------------------------------------------------------------
// CBCTestKeyFeeder::KeyUp
// -----------------------------------------------------------------------------
//
void CBCTestKeyFeeder::KeyUp( TInt aScanCode )
    {
    if ( aScanCode == EStdKeyRightShift )
        {
        iModifiers = iOldModifiers;
        }

    TRawEvent event;
    event.Set( TRawEvent::EKeyUp, aScanCode );
    iEikEnv->WsSession().SimulateRawEvent( event );
    }

// -----------------------------------------------------------------------------
// CBCTestKeyFeeder::KeyPress
// -----------------------------------------------------------------------------
//
void CBCTestKeyFeeder::KeyPress( TInt aCode, TInt aScanCode )
    {
    User::ResetInactivityTime();// Reset user inactivity timers

    if ( iKeyDown ) // Long key press -> do just key down
        {
        KeyDown( aScanCode );
        iKeyDown = EFalse;
        return; // ends key press
        }

    if ( iKeyUp ) // Ends long key press -> do just key up
        {
        KeyUp( aScanCode );
        iKeyUp = EFalse;
        return; // ends key press
        }

    // there seems to be no keycode for abc-key, simulate by pressing
    // key down and up
    if ( aCode == EStdKeyRightShift )
        {
        KeyDown( aCode );
        KeyUp( aCode );
        return; 
        }

    // Do normal key press
    TKeyEvent event = { aCode, aScanCode, iModifiers, 0 };
    iEikEnv->WsSession().SimulateKeyEvent( event );
    }

// -----------------------------------------------------------------------------
// CBCTestKeyFeeder::PauseTimer
// -----------------------------------------------------------------------------
//
void CBCTestKeyFeeder::PauseTimer()
    {
    iTimerPaused = ETrue;
    }

// -----------------------------------------------------------------------------
// CBCTestKeyFeeder::ResumeTimer
// -----------------------------------------------------------------------------
//
void CBCTestKeyFeeder::ResumeTimer()
    {
    iTimerPaused = EFalse;
    }

// -----------------------------------------------------------------------------
// CBCTestKeyFeeder::PointerEvent
// -----------------------------------------------------------------------------
//
void CBCTestKeyFeeder::PointerEvent( TRawEvent& aEvent )
	{	
    iEikEnv->WsSession().SimulateRawEvent( aEvent );
	}

// -----------------------------------------------------------------------------
// CBCTestKeyFeeder::SetSuite
// -----------------------------------------------------------------------------
//
void CBCTestKeyFeeder::SetSuite( CBCTestSuite* aSuite )
    {
    iSuite = aSuite;
    }
