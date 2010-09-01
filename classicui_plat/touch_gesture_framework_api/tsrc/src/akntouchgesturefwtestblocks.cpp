/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: This file contains testclass implementation.
*
*/

// [INCLUDE FILES] - do not remove
#include <e32svr.h>
#include <f32file.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <akntouchgesturefw.h>
#include "akntouchgesturefwtest.h"
#include "akntouchgesturefwsimulation.h"

using namespace AknTouchGestureFw;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknTouchGestureFwTest::Delete
// Delete here all resources allocated and opened from test methods.
// Called from destructor.
// -----------------------------------------------------------------------------
//
void CAknTouchGestureFwTest::Delete()
    {
    iGestures.Reset();
    iGestures.Close();
    }

// -----------------------------------------------------------------------------
// CAknTouchGestureFwTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CAknTouchGestureFwTest::RunMethodL(
    CStifItemParser& aItem )
    {

    static TStifFunctionInfo const KFunctions[] =
        {
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function.
        ENTRY( "MAknTouchGestureFwTest_CreateFwL",
                CAknTouchGestureFwTest::MAknTouchGestureFwTest_CreateFwL ),
        ENTRY( "MAknTouchGestureFwTest_SetGestureInterestL",
                CAknTouchGestureFwTest::MAknTouchGestureFwTest_SetGestureInterestL ),
        ENTRY( "MAknTouchGestureFwTest_SetFeedbackForGroupsL",
                CAknTouchGestureFwTest::MAknTouchGestureFwTest_SetFeedbackForGroupsL ),
        ENTRY( "MAknTouchGestureFwTest_SetFeedbackForTypesL",
                CAknTouchGestureFwTest::MAknTouchGestureFwTest_SetFeedbackForTypesL ),                   
        ENTRY( "MAknTouchGestureFwTest_SimulateGesturesL",
                CAknTouchGestureFwTest::MAknTouchGestureFwTest_SimulateGesturesL ),
        //ADD NEW ENTRY HERE
        // [test cases entries] - Do not remove

        };

    const TInt count = sizeof( KFunctions ) /
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// ---------------------------------------------------------------------------
// Tests the gesture framework construction.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwTest::MAknTouchGestureFwTest_CreateFwL(
    CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KAknTouchGestureFwTest, "AknTouchGestureFwTest" );
    _LIT( KTestName, "MAknTouchGestureFwTest_CreateFwL" );
    TestModuleIf().Printf( 0, KAknTouchGestureFwTest, KTestName );

    // Print to log file
    iLog->Log( KTestName );
    CAknTouchGestureFwTestObserver* observer =
        CAknTouchGestureFwTestObserver::NewLC( this );
    CAknTouchGestureFw* gestureFw
        = CAknTouchGestureFw::NewL( *observer, *observer->TestControl() );
    CleanupStack::PushL( gestureFw );
    STIF_ASSERT_NOT_NULL( gestureFw );
    CleanupStack::PopAndDestroy( gestureFw );
    CleanupStack::PopAndDestroy( observer );

    return KErrNone;
    }


// ---------------------------------------------------------------------------
// Tests setting the gesture interest.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwTest::MAknTouchGestureFwTest_SetGestureInterestL(
    CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KAknTouchGestureFwTest, "AknTouchGestureFwTest" );
    _LIT( KTestName, "MAknTouchGestureFwTest_SetGestureInterestL" );
    TestModuleIf().Printf( 0, KAknTouchGestureFwTest, KTestName );

    // Print to log file
    iLog->Log( KTestName );

    CAknTouchGestureFwTestObserver* observer =
        CAknTouchGestureFwTestObserver::NewLC( this );
    CAknTouchGestureFw* gestureFw
        = CAknTouchGestureFw::NewL( *observer, *observer->TestControl() );
    CleanupStack::PushL( gestureFw );
    gestureFw->SetGestureInterestL( EAknTouchGestureFwAll );
    gestureFw->SetGestureInterestL( EAknTouchGestureFwGroupFlick );
    gestureFw->SetGestureInterestL( EAknTouchGestureFwGroupDrag | 
                                    EAknTouchGestureFwGroupTap );
    gestureFw->SetGestureInterestL( EAknTouchGestureFwNoGroup );
    CleanupStack::PopAndDestroy( gestureFw );
    CleanupStack::PopAndDestroy( observer );

    return KErrNone;
    }


// ---------------------------------------------------------------------------
// Tests setting the gesture feedbacks for groups.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwTest::MAknTouchGestureFwTest_SetFeedbackForGroupsL(
    CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KAknTouchGestureFwTest, "AknTouchGestureFwTest" );
    _LIT( KTestName, "MAknTouchGestureFwTest_SetFeedbackForGroupsL" );
    TestModuleIf().Printf( 0, KAknTouchGestureFwTest, KTestName );

    // Print to log file
    iLog->Log( KTestName );

    CAknTouchGestureFwTestObserver* observer =
        CAknTouchGestureFwTestObserver::NewLC( this );
    CAknTouchGestureFw* gestureFw
        = CAknTouchGestureFw::NewL( *observer, *observer->TestControl() );
    CleanupStack::PushL( gestureFw );
    gestureFw->SetFeedbackForGroupsL( EAknTouchGestureFwAll );
    gestureFw->SetFeedbackForGroupsL( EAknTouchGestureFwGroupFlick );
    gestureFw->SetFeedbackForGroupsL( EAknTouchGestureFwGroupDrag | 
                                      EAknTouchGestureFwGroupTap );
    gestureFw->SetFeedbackForGroupsL( EAknTouchGestureFwNoGroup ); 
    CleanupStack::PopAndDestroy( gestureFw );
    CleanupStack::PopAndDestroy( observer );

    return KErrNone;
    }


// ---------------------------------------------------------------------------
// Tests setting the gesture feedbacks for groups.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwTest::MAknTouchGestureFwTest_SetFeedbackForTypesL(
    CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KAknTouchGestureFwTest, "AknTouchGestureFwTest" );
    _LIT( KTestName, "MAknTouchGestureFwTest_SetFeedbackForTypesL" );
    TestModuleIf().Printf( 0, KAknTouchGestureFwTest, KTestName );

    // Print to log file
    iLog->Log( KTestName );

    CAknTouchGestureFwTestObserver* observer =
        CAknTouchGestureFwTestObserver::NewLC( this );
    CAknTouchGestureFw* gestureFw
        = CAknTouchGestureFw::NewL( *observer, *observer->TestControl() );
    CleanupStack::PushL( gestureFw );
    gestureFw->SetFeedbackForTypesL( EAknTouchGestureFwAll, 
                                     EAknTouchGestureFwDoubleTap |
                                     EAknTouchGestureFwLongTap,
                                     EAknTouchGestureFwDoubleTap |
                                     EAknTouchGestureFwLongTap);
    gestureFw->SetFeedbackForTypesL( EAknTouchGestureFwAll, 0, 0 );   
    
    gestureFw->SetFeedbackForTypesL( EAknTouchGestureFwGroupTap, 
                                     EAknTouchGestureFwDoubleTap |
                                     EAknTouchGestureFwLongTap, 0 );  
    gestureFw->SetFeedbackForTypesL( EAknTouchGestureFwGroupTap, 0,
                                     EAknTouchGestureFwDoubleTap |
                                     EAknTouchGestureFwLongTap );    
    gestureFw->SetFeedbackForTypesL( EAknTouchGestureFwGroupTap,
                                     EAknTouchGestureFwDoubleTap |
                                     EAknTouchGestureFwLongTap ,
                                     EAknTouchGestureFwDoubleTap |
                                     EAknTouchGestureFwLongTap );   
    gestureFw->SetFeedbackForTypesL( EAknTouchGestureFwGroupTap, 0, 0 ); 
    
    gestureFw->SetFeedbackForTypesL( EAknTouchGestureFwNoGroup, 
                                     EAknTouchGestureFwDoubleTap |
                                     EAknTouchGestureFwLongTap,
                                     EAknTouchGestureFwDoubleTap |
                                     EAknTouchGestureFwLongTap);
    gestureFw->SetFeedbackForTypesL( EAknTouchGestureFwNoGroup, 0, 0 );     
    
    CleanupStack::PopAndDestroy( gestureFw );
    CleanupStack::PopAndDestroy( observer );

    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CAknTouchGestureFwTest::MAknTouchGestureFwTest_SimulateGesturesL
// -----------------------------------------------------------------------------
//
TInt CAknTouchGestureFwTest::MAknTouchGestureFwTest_SimulateGesturesL(
    CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KAknTouchGestureFwTest, "AknTouchGestureFwTest" );
    _LIT( KTestName, "MAknTouchGestureFwTest_SimulateGesturesL" );
    TestModuleIf().Printf( 0, KAknTouchGestureFwTest, KTestName );
    // Print to log file
    iLog->Log( KTestName );

    CAknTouchGestureFwTestObserver* observer =
        CAknTouchGestureFwTestObserver::NewLC( this );

    CAknTouchGestureFw* gestureFw =
        CAknTouchGestureFw::NewL( *observer, *observer->TestControl() );
    CleanupStack::PushL( gestureFw );
    gestureFw->SetGestureInterestL( EAknTouchGestureFwAll );

    // IDs for accessing gesture simulation instance
    const TUint KAknTouchGestureFwTestingFeature( 0x20026806 );
    const TUid KAknTouchGestureFwSimulation = { 0x20026770 };

    TAny* dummyPtr( NULL );
    gestureFw->Extension_( KAknTouchGestureFwTestingFeature, dummyPtr, NULL );

    AknTouchGestureFw::MAknTouchGestureFwSimulator* simulator =
        static_cast<CAknTouchGestureFwSimulation*>(
            CCoeEnv::Static( KAknTouchGestureFwSimulation ) );

    // Append gestures to expected results array.

    // Tap X: 107, Y: 184
    AddGestureL( EAknTouchGestureFwGroupTap,
                 EAknTouchGestureFwTap, 1 );
    // Double Tap X: 107, Y: 184
    AddGestureL( EAknTouchGestureFwGroupTap,
                 EAknTouchGestureFwDoubleTap, 1 );
    // Drag Start & Drag Stop
    AddGestureL( EAknTouchGestureFwGroupDrag,
                 EAknTouchGestureFwDrag, 2 );
    // Flick Left 497 pixels/second
    AddGestureL( EAknTouchGestureFwGroupFlick,
                 EAknTouchGestureFwFlickLeft, 1 );
    // Drag Start & Drag Stop
    AddGestureL( EAknTouchGestureFwGroupDrag,
                 EAknTouchGestureFwDrag, 2 );
    // Flick Right 1068 pixels/second
    AddGestureL( EAknTouchGestureFwGroupFlick,
                 EAknTouchGestureFwFlickRight, 1 );
    // Drag Start & Drag Stop
    AddGestureL( EAknTouchGestureFwGroupDrag,
                 EAknTouchGestureFwDrag, 2 );
    // Flick Up 716 pixels/second
    AddGestureL( EAknTouchGestureFwGroupFlick,
                 EAknTouchGestureFwFlickUp, 1 );
    // Drag Start & Drag Stop
    AddGestureL( EAknTouchGestureFwGroupDrag,
                 EAknTouchGestureFwDrag, 2 );
    // Flick Down 706 pixels/second
    AddGestureL( EAknTouchGestureFwGroupFlick,
                 EAknTouchGestureFwFlickDown, 1 );
    // Pinch
    AddGestureL( EAknTouchGestureFwGroupPinch,
                 EAknTouchGestureFwPinch, 5 );
    
    RFs fileServer;
    RFile file;

    _LIT( KFileName, "C:\\testing\\data\\gesturefw_unit_tests.txt" );

    User::LeaveIfError( fileServer.Connect() );
    User::LeaveIfError( file.Open( fileServer,
                                   KFileName,
                                   EFileRead |
                                   EFileShareReadersOnly ) );
    TInt size;
    file.Size( size );

    // read data from file
    HBufC8* buffer = HBufC8::NewLC( size );
    TPtr8 ptr = buffer->Des();
    file.Read( ptr );
    TLex8 lex( ptr );

    TPointerEvent event;
    TInt pointerNumber;
    TInt pointerTime;

    iTestIndex = 0;
    iTestResult = KErrNone;

    while ( ReadPointerEvent( lex, event, pointerNumber, pointerTime ) )
        {
        simulator->SimulateL(
                gestureFw,
                event,
                pointerNumber,
                pointerTime );

        if( iTestResult != KErrNone )
            {
            break;
            }
        }

    file.Close();
    fileServer.Close();

    CleanupStack::PopAndDestroy( buffer );
    CleanupStack::PopAndDestroy( gestureFw );
    CleanupStack::PopAndDestroy( observer );

    return iTestResult;
    }


// -----------------------------------------------------------------------------
// CAknTouchGestureFwTest::DoGestureTest
// -----------------------------------------------------------------------------
//
void CAknTouchGestureFwTest::DoGestureTest( MAknTouchGestureFwEvent& aEvent )
    {
    // Print to UI
    _LIT( KAknTouchGestureFwTest, "AknTouchGestureCallback" );
    _LIT( KTestName, "EAknTouchGestures" );
    TestModuleIf().Printf( 0, KAknTouchGestureFwTest, KTestName );
    // Print to log file
    iLog->Log( KTestName );

    if ( iTestIndex >= iGestures.Count() - 1 )
        {
        // Index out of bounds
        iTestResult = KErrGeneral;
        return;
        }

    TInt gestureGroup = iGestures[ iTestIndex ];
    TInt gestureType = iGestures[ iTestIndex + 1 ];

    // Check if event callback matches to test data
    if ( gestureGroup != aEvent.Group() ||
         gestureType != aEvent.Type() )
        {
        // Test failed
        iTestResult = KErrGeneral;
        }
    
    // Check methods of each gesture group
    switch ( aEvent.Group() )
        {
        case EAknTouchGestureFwGroupTap:
            {
            MAknTouchGestureFwTapEvent* tapEvent = 
                AknTouchGestureFwEventTap( aEvent );
            tapEvent->Position();
            break;
            }

        case EAknTouchGestureFwGroupDrag:
            {
            MAknTouchGestureFwDragEvent* dragEvent = 
                AknTouchGestureFwEventDrag( aEvent );
            dragEvent->State();
            dragEvent->StartPosition();
            dragEvent->CurrentPosition();
            dragEvent->PreviousPosition();           
            break;
            }
            
        case EAknTouchGestureFwGroupFlick:
            {
            MAknTouchGestureFwFlickEvent* flickEvent = 
                AknTouchGestureFwEventFlick( aEvent );
            flickEvent->Position();
            flickEvent->Speed();
            break;
            }  

        case EAknTouchGestureFwGroupPinch:
            {
            MAknTouchGestureFwPinchEvent* pinchEvent = 
                AknTouchGestureFwEventPinch( aEvent );
            pinchEvent->State();
            pinchEvent->Movement();
            break;
            }  
            
        default:
            {
            // Unknown group
            iTestResult = KErrGeneral;
            }
        }
    // Jump to next case
    iTestIndex = iTestIndex + 2;
    }


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwTest::AddGestureL( TInt aGroup,
                                          TInt aType,
                                          TInt aAmount )
    {
    for ( TInt i = 0 ; i < aAmount; i++ )
        {
        iGestures.AppendL( aGroup );
        iGestures.AppendL( aType );
        }
    }


// ---------------------------------------------------------------------------
// Reads a single pointer event data from a record.
// ---------------------------------------------------------------------------
//
TBool CAknTouchGestureFwTest::ReadPointerEvent( TLex8& aLex,
    TPointerEvent& aEvent, TInt& aPointerNumber, TInt& aPointerTime )
    {
    // read time ( microseconds )
    if ( !ReadValue( aLex, aPointerTime ) )
        {
        return EFalse;
        }

    // read event type
    TInt eventType;
    if ( !ReadValue( aLex, eventType ) )
        {
        return EFalse;
        }

    switch ( eventType )
        {
        case TPointerEvent::EButton1Down:
            {
            aEvent.iType = TPointerEvent::EButton1Down;
            break;
            }

        case TPointerEvent::EButton1Up:
            {
            aEvent.iType = TPointerEvent::EButton1Up;
            break;
            }

        case TPointerEvent::EDrag:
            {
            aEvent.iType = TPointerEvent::EDrag;
            break;
            }

        default:
            {
            return EFalse;
            }
        }

    // Read X-coordinate
    if ( !ReadValue( aLex, aEvent.iPosition.iX ) )
        {
        return EFalse;
        }

    // Read Y-coordinate
    if ( !ReadValue( aLex, aEvent.iPosition.iY ) )
        {
        return EFalse;
        }

    // Read pointer number
    if ( !ReadValue( aLex, aPointerNumber ) )
        {
        return EFalse;
        }

    return ETrue;
    }


// ---------------------------------------------------------------------------
// Reads an integer value from the given string.
// ---------------------------------------------------------------------------
//
TBool CAknTouchGestureFwTest::ReadValue( TLex8& lex, TInt& aValue )
    {
    TPtrC8 token = lex.NextToken();
    if ( token.Length() <= 0 )
        {
        return EFalse;
        }

    TLex8 var( token );

    if ( var.Val( aValue ) != KErrNone )
        {
        return EFalse;
        }

    return ETrue;
    }

//  [End of File] - Do not remove
