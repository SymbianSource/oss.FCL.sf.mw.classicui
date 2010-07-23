/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  misc_controls_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <eikcapc.h>
#include <eikcapca.h>
#include <eikconso.h>
#include <s32mem.h>
#include <testsdkmisccontrols.rsg>

#include "testsdkconsoprotectedclass.h"
#include "testsdkmisccontrols.h"
#include "testsdkmisccontrolcontainer.h"
#include "testsdkmisccontrolview.h"
// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSDefaultConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSDefaultConstructorL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSDefaultConstructorL, "In TestCSDefaultConstructorL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSDefaultConstructorL );
    // Print to log file
    iLog->Log( KTestCSDefaultConstructorL );

    iConsoleScreen = new (ELeave) CEikConsoleScreen();
    STIF_ASSERT_NOT_NULL( iConsoleScreen );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSDestructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSDestructor( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSDestructor, "In TestCSDestructor" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSDestructor );
    // Print to log file
    iLog->Log( KTestCSDestructor );

    delete iConsoleScreen;
    iConsoleScreen = NULL;
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSConstructL, "In TestCSConstructL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSConstructL );
    // Print to log file
    iLog->Log( KTestCSConstructL );
    
    TBool err = KErrNone;
    TBufC<128> buf( _L("test") );
    TRAP( err, iConsoleScreen->ConstructL( buf, CEikConsoleScreen::ENoInitialCursor) );
  
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSConstructWithSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSConstructWithSizeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSConstructWithSizeL, "In TestCSConstructWithSizeL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSConstructWithSizeL );
    // Print to log file
    iLog->Log( KTestCSConstructWithSizeL );
    
    TBool err = KErrNone;
    TBufC<128> buf( _L("test") );
    TSize size( 100, 100 );
    TRAP( err, iConsoleScreen->ConstructL( buf, size, CEikConsoleScreen::ENoInitialCursor) );
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSConstructWithSizeAndPointL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSConstructWithSizeAndPointL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSConstructWithSizeAndPointL, "In TestCSConstructWithSizeAndPointL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSConstructWithSizeAndPointL );
    // Print to log file
    iLog->Log( KTestCSConstructWithSizeAndPointL );
    
    TBool err = KErrNone;
    TBufC<128> buf( _L("test") );
    TSize size( 100, 100 );
    TPoint topLeft( 0, 0);
    TRAP( err, iConsoleScreen->ConstructL( buf, topLeft, size, CEikConsoleScreen::ENoInitialCursor) );
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSCreate
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSCreate( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSCreate, "In TestCSCreate" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSCreate );
    // Print to log file
    iLog->Log( KTestCSCreate );

    TBufC<128> buf( _L("test") );
    TSize size( 100, 100 );
    TInt code = iConsoleScreen->Create( buf, size );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSRead
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSRead( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSRead, "In TestCSRead" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSRead );
    // Print to log file
    iLog->Log( KTestCSRead );

    TRequestStatus status;
    iConsoleScreen->Read( status );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSReadCancel
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSReadCancel( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSReadCancel, "In TestCSReadCancel" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSReadCancel );
    // Print to log file
    iLog->Log( KTestCSReadCancel );

    iConsoleScreen->ReadCancel();
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSKeyCode
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSKeyCode( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSKeyCode, "In TestCSKeyCode" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSKeyCode );
    // Print to log file
    iLog->Log( KTestCSKeyCode );

    TKeyCode code = iConsoleScreen->KeyCode();
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSKeyModifiers
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSKeyModifiers( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSKeyModifiers, "In TestCSKeyModifiers" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSKeyModifiers );
    // Print to log file
    iLog->Log( KTestCSKeyModifiers );

    TUint code = iConsoleScreen->KeyModifiers();
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSSetConsWinL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSSetConsWinL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSSetConsWinL, "In TestCSSetConsWinL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSSetConsWinL );
    // Print to log file
    iLog->Log( KTestCSSetConsWinL );
    CEikConsoleControl *consWin = new (ELeave) CEikConsoleControl();
    CleanupStack::PushL( consWin );
    TPoint point( 0, 0);
    TSize size( 100,100 );
    TEikConsWinUnits unit=EEikConsWinInChars;
    
    consWin->ConstructL( point,size,CEikConsoleScreen::ENoInitialCursor, unit);
    iConsoleScreen->SetConsWin( consWin );
    CleanupStack::Pop( consWin );   
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSConsoleControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSConsoleControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSConsoleControl, "In TestCSConsoleControl" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSConsoleControl );
    // Print to log file
    iLog->Log( KTestCSConsoleControl );

    CEikConsoleControl* consoleControl = iConsoleScreen->ConsoleControl();
    STIF_ASSERT_NOT_NULL( consoleControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSSetTitle
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSSetTitle( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSSetTitle, "In TestCSSetTitle" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSSetTitle );
    // Print to log file
    iLog->Log( KTestCSSetTitle );
    TBufC<128> title( _L( "test" ) );
    iConsoleScreen->SetTitle( title );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSSetTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSSetTitleL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSSetTitleL, "In TestCSSetTitleL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSSetTitleL );
    // Print to log file
    iLog->Log( KTestCSSetTitleL );
    TBufC<128> title( _L( "test" ) );
    TBool err = KErrNone;
    TRAP( err, iConsoleScreen->SetTitleL( title ) );
    
    return err;

    }


// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSTitleL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSTitle, "In TestCSTitle" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSTitle );
    // Print to log file
    iLog->Log( KTestCSTitle );

    HBufC* title = iConsoleScreen->Title();
    STIF_ASSERT_NOT_NULL( title );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSScreenSize
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSScreenSize( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSScreenSize, "In TestCSScreenSize" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSScreenSize );
    // Print to log file
    iLog->Log( KTestCSScreenSize );
    TSize size = iConsoleScreen->ScreenSize();
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSFlushChars
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSFlushChars( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSFlushChars, "In TestCSFlushChars" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSFlushChars );
    // Print to log file
    iLog->Log( KTestCSFlushChars );
    iConsoleScreen->FlushChars();

    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSCursorPos
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSCursorPos( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSCursorPos, "In TestCSCursorPos" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSCursorPos );
    // Print to log file
    iLog->Log( KTestCSCursorPos );
    TPoint point = iConsoleScreen->CursorPos();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSSetCursorPosAbs
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSSetCursorPosAbs( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSSetCursorPosAbs, "In TestCSSetCursorPosAbs" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSSetCursorPosAbs );
    // Print to log file
    iLog->Log( KTestCSSetCursorPosAbs );
    TPoint point( 0, 0);
    iConsoleScreen->SetCursorPosAbs( point );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSSetCursorPosRel
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSSetCursorPosRel( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSSetCursorPosRel, "In TestCSSetCursorPosRel" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSSetCursorPosRel );
    // Print to log file
    iLog->Log( KTestCSSetCursorPosRel );
    TPoint point( 0, 0);
    iConsoleScreen->SetCursorPosRel( point );

    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSSetCursorHeight
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSSetCursorHeight( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSSetCursorHeight, "In TestCSSetCursorHeight" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSSetCursorHeight );
    // Print to log file
    iLog->Log( KTestCSSetCursorHeight );
    TInt percentage = 0;
    iConsoleScreen->SetCursorHeight( percentage );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSWrite
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSWrite( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSWrite, "In TestCSWrite" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSWrite );
    // Print to log file
    iLog->Log( KTestCSWrite );
    TBufC<128> buf( _L( "test" ) );
    iConsoleScreen->Write( buf );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSClearScreen
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSClearScreen( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSClearScreen, "In TestCSClearScreen" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSClearScreen );
    // Print to log file
    iLog->Log( KTestCSClearScreen );
    iConsoleScreen->ClearScreen();
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSClearToEndOfLine
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSClearToEndOfLine( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSClearToEndOfLine, "In TestCSClearToEndOfLine" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSClearToEndOfLine );
    // Print to log file
    iLog->Log( KTestCSClearToEndOfLine );
    iConsoleScreen->ClearToEndOfLine();
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSClearChars
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSClearChars( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSClearChars, "In TestCSClearChars" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSClearChars );
    // Print to log file
    iLog->Log( KTestCSClearChars );
    TRect rect( 10, 10, 150, 30 );
    TUint characterAttributes = 4;
    iConsoleScreen->ClearChars( rect, characterAttributes );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSHideCursor
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSHideCursor( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSHideCursor, "In TestCSHideCursor" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSHideCursor );
    // Print to log file
    iLog->Log( KTestCSHideCursor );
    TInt expect = 0;
    TInt cursor = iConsoleScreen->HideCursor();

    STIF_ASSERT_EQUALS( expect, cursor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSDrawCursor
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSDrawCursor( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSDrawCursor, "In TestCSDrawCursor" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSDrawCursor );
    // Print to log file
    iLog->Log( KTestCSDrawCursor );
    iConsoleScreen->DrawCursor();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSDrawInSight
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSDrawInSight( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSDrawInSight, "In TestCSDrawInSight" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSDrawInSight );
    // Print to log file
    iLog->Log( KTestCSDrawInSight );
    TPoint point( 0 ,0 );
    iConsoleScreen->DrawInSight( point );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSDrawCursorInSight
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSDrawCursorInSight( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSDrawCursorInSight, "In TestCSDrawCursorInSight" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSDrawCursorInSight );
    // Print to log file
    iLog->Log( KTestCSDrawCursorInSight );

    iConsoleScreen->DrawCursorInSight();

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSUp
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSUp( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSUp, "In TestCSUp" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSUp );
    // Print to log file
    iLog->Log( KTestCSUp );

    iConsoleScreen->Up();

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSDown
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSDown( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSDown, "In TestCSDown" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSDown );
    // Print to log file
    iLog->Log( KTestCSDown );

    iConsoleScreen->Down();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSRight
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSRight( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSRight, "In TestCSRight" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSRight );
    // Print to log file
    iLog->Log( KTestCSRight );

    iConsoleScreen->Right();

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSLeft
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSLeft( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSLeft, "In TestCSLeft" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSLeft );
    // Print to log file
    iLog->Log( KTestCSLeft );

    iConsoleScreen->Left();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSCr
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSCr( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSCr, "In TestCSCr" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSCr );
    // Print to log file
    iLog->Log( KTestCSCr );

    iConsoleScreen->Cr();

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSLf
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSLf( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSLf, "In TestCSLf" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSLf );
    // Print to log file
    iLog->Log( KTestCSLf );

    iConsoleScreen->Lf();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSScrollChars
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSScrollChars( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSScrollChars, "In TestCSScrollChars" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSScrollChars );
    // Print to log file
    iLog->Log( KTestCSScrollChars );
    TRect rect( 10, 10, 10, 10 );
    TPoint point( 10, 10 );

    iConsoleScreen->ScrollChars( rect, point );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSRedraw
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSRedraw( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSRedraw, "In TestCSRedraw" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSRedraw );
    // Print to log file
    iLog->Log( KTestCSRedraw );
    TRect rect( 10, 10, 10, 10 );
    iConsoleScreen->Redraw( rect );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSMoveTopLeft
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSMoveTopLeft( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSMoveTopLeft, "In TestCSMoveTopLeft" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSMoveTopLeft );
    // Print to log file
    iLog->Log( KTestCSMoveTopLeft );
    TPoint point( 10, 10 );
    iConsoleScreen->MoveTopLeft( point );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSHistorySize
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSHistorySize( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSHistorySize, "In TestCSHistorySize" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSHistorySize );
    // Print to log file
    iLog->Log( KTestCSHistorySize );
    TUint expect = 0;
    TUint size = iConsoleScreen->HistorySize();
    STIF_ASSERT_EQUALS( expect, size );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSSetHistorySizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSSetHistorySizeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSSetHistorySizeL, "In TestCSSetHistorySizeL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSSetHistorySizeL );
    // Print to log file
    iLog->Log( KTestCSSetHistorySizeL );
    TUint maxChrExtra = 100;
    TUint maxAttExtra = 100;
    iConsoleScreen->SetHistorySizeL( maxChrExtra, maxAttExtra );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSAtt
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSAtt( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSAtt, "In TestCSAtt" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSAtt );
    // Print to log file
    iLog->Log( KTestCSAtt );
    TUint expect = 0;
    TUint countAtt = iConsoleScreen->Att();
    STIF_ASSERT_EQUALS( expect, countAtt );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSSetAtt
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSSetAtt( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSSetAtt, "In TestCSSetAtt" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSSetAtt );
    // Print to log file
    iLog->Log( KTestCSSetAtt );
    TUint cAtt = 4;
    iConsoleScreen->SetAtt( cAtt );
   
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSSetAttWithGround
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSSetAttWithGround( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSSetAttWithGround, "In TestCSSetAttWithGround" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSSetAttWithGround );
    // Print to log file
    iLog->Log( KTestCSSetAttWithGround );
    TUint foregroundGray = 10;
    TUint backgroundGray = 15;
    iConsoleScreen->SetAtt( foregroundGray, backgroundGray );
   
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSSetFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSSetFontL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSSetFontL, "In TestCSSetFontL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSSetFontL );
    // Print to log file
    iLog->Log( KTestCSSetFontL );
    TBool err = KErrNone;
    TFontSpec fontSpec = iConsoleScreen->Font(); 
    TRAP( err, iConsoleScreen->SetFontL( fontSpec ) );
   
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSFont
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSFont( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSFont, "In TestCSFont" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSFont );
    // Print to log file
    iLog->Log( KTestCSFont );
   
    TFontSpec fontSpec = iConsoleScreen->Font(); 

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSSetSelection
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSSetSelection( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSSetSelection, "In TestCSSetSelection" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSSetSelection );
    // Print to log file
    iLog->Log( KTestCSSetSelection );
    TRect rectSelection = iConsoleScreen->Selection(); 
    iConsoleScreen->SetSelection( rectSelection ); 
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSSelectCursor
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSSelectCursor( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSSelectCursor, "In TestCSSelectCursor" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSSelectCursor );
    // Print to log file
    iLog->Log( KTestCSSelectCursor );
    iConsoleScreen->SelectCursor(); 
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSSelection
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSSelection( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSSelection, "In TestCSSelection" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSSelection );
    // Print to log file
    iLog->Log( KTestCSSelection );
    TRect rectSelection = iConsoleScreen->Selection(); 

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSRetrieveL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSRetrieveL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSRetrieveL, "In TestCSRetrieveL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSRetrieveL );
    // Print to log file
    iLog->Log( KTestCSRetrieveL );
    TRect rectSelection = iConsoleScreen->Selection(); 
    HBufC* selection = iConsoleScreen->RetrieveL( rectSelection ); 
    STIF_ASSERT_NULL( selection );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSSetPureCRLF
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSSetPureCRLF( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSSetPureCRLF, "In TestCSSetPureCRLF" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSSetPureCRLF );
    // Print to log file
    iLog->Log( KTestCSSetPureCRLF );

    iConsoleScreen->SetPureCRLF( CEikConsoleScreen::ENoInitialCursor ); 
    
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSSetAllPrintable
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSSetAllPrintable( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSSetAllPrintable, "In TestCSSetAllPrintable" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSSetAllPrintable );
    // Print to log file
    iLog->Log( KTestCSSetAllPrintable );

    iConsoleScreen->SetAllPrintable( CEikConsoleScreen::ENoInitialCursor ); 
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSSetScrollLock
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSSetScrollLock( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSSetScrollLock, "In TestCSSetScrollLock" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSSetScrollLock );
    // Print to log file
    iLog->Log( KTestCSSetScrollLock );

    iConsoleScreen->SetScrollLock( CEikConsoleScreen::ENoInitialCursor ); 
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSSetKeepCursorInSight
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSSetKeepCursorInSight( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSSetKeepCursorInSight, "In TestCSSetKeepCursorInSight" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSSetKeepCursorInSight );
    // Print to log file
    iLog->Log( KTestCSSetKeepCursorInSight );

    iConsoleScreen->SetKeepCursorInSight( CEikConsoleScreen::ENoInitialCursor ); 
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSSetScrollBarVisibilityL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSSetScrollBarVisibilityL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSSetScrollBarVisibilityL, "In TestCSSetScrollBarVisibilityL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSSetScrollBarVisibilityL );
    // Print to log file
    iLog->Log( KTestCSSetScrollBarVisibilityL );
    TBool err = KErrNone;
    TRAP( err, iConsoleScreen->SetScrollBarVisibilityL( CEikScrollBarFrame::EAuto, CEikScrollBarFrame::EAuto ) ); 
    
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCSUpdateScrollBars
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCSUpdateScrollBars( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCSUpdateScrollBars, "In TestCSUpdateScrollBars" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCSUpdateScrollBars );
    // Print to log file
    iLog->Log( KTestCSUpdateScrollBars );

    TBool scrollbars = iConsoleScreen->UpdateScrollBars(); 
    
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCDefaultConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCDefaultConstructorL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCDefaultConstructorL, "In TestCCDefaultConstructorL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCDefaultConstructorL );
    // Print to log file
    iLog->Log( KTestCCDefaultConstructorL );

    iConsoleControl = new (ELeave) CEikConsoleControl(); 
    STIF_ASSERT_NOT_NULL( iConsoleControl );
    
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCDestructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCDestructor( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCDestructor, "In TestCCDestructor" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCDestructor );
    // Print to log file
    iLog->Log( KTestCCDestructor );

    delete iConsoleControl; 
    iConsoleControl = NULL;
    
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCConstructL, "In TestCCConstructL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCConstructL );
    // Print to log file
    iLog->Log( KTestCCConstructL );
    TBool err = KErrNone;
    TRAP( err, iConsoleControl->ConstructL( CEikConsoleScreen::EUseBackedUpWindow ) ); 

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCConstructWithPointL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCConstructWithPointL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCConstructWithPointL, "In TestCCConstructWithPointL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCConstructWithPointL );
    // Print to log file
    iLog->Log( KTestCCConstructWithPointL );
    TBool err = KErrNone;
    TPoint topLeft( 0, 0 );
    TSize size( 100, 100 );
    TEikConsWinUnits unit=EEikConsWinInChars;
    TRAP( err, iConsoleControl->ConstructL
            ( topLeft, size, CEikConsoleScreen::EUseBackedUpWindow, unit ) ); 

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCSetRedrawer
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCSetRedrawer( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCSetRedrawer, "In TestCCSetRedrawer" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCSetRedrawer );
    // Print to log file
    iLog->Log( KTestCCSetRedrawer );
    iConsoleControl->SetRedrawer( iConsoleScreen );
            
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCSetFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCSetFontL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCSetFontL, "In TestCCSetFontL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCSetFontL );
    // Print to log file
    iLog->Log( KTestCCSetFontL );
    TBool err = KErrNone;
    TFontSpec* fontSpec = new( ELeave ) TFontSpec();
    CleanupStack::PushL( fontSpec );
    iConsoleContainer = new (ELeave) CMiscControlsContainer();

    CFbsFont* editorFont = iConsoleContainer->GetCoeEnv()->CreateScreenFontL( *fontSpec );
    CleanupStack::PushL( editorFont );
    TRAP( err, iConsoleControl->SetFontL( *fontSpec, editorFont ) );
    iConsoleContainer->GetCoeEnv()->ReleaseScreenFont( editorFont ); 
    CleanupStack::Pop( editorFont );

    CleanupStack::PopAndDestroy( fontSpec );
            
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCFont
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCFont( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCFont, "In TestCCFont" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCFont );
    // Print to log file
    iLog->Log( KTestCCFont );
    TFontSpec fontSpec = iConsoleControl->Font();
            
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCCharSize
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCCharSize( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCCharSize, "In TestCCCharSize" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCCharSize );
    // Print to log file
    iLog->Log( KTestCCCharSize );
    TSize size = iConsoleControl->CharSize();
            
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCVisibleSize
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCVisibleSize( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCVisibleSize, "In TestCCVisibleSize" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCVisibleSize );
    // Print to log file
    iLog->Log( KTestCCVisibleSize );
    TSize size = iConsoleControl->VisibleSize();

            
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCSetCursorHeight
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCSetCursorHeight( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCSetCursorHeight, "In TestCCSetCursorHeight" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCSetCursorHeight );
    // Print to log file
    iLog->Log( KTestCCSetCursorHeight );
    TUint percentage = 1;
    iConsoleControl->SetCursorHeight( percentage );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCDrawCursor
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCDrawCursor( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCDrawCursor, "In TestCCDrawCursor" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCDrawCursor );
    // Print to log file
    iLog->Log( KTestCCDrawCursor );
    TPoint position( 100, 100 );

    iConsoleControl->SetFocus( ETrue );
    iConsoleControl->DrawCursor( position );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCHideCursor
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCHideCursor( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCHideCursor, "In TestCCHideCursor" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCHideCursor );
    // Print to log file
    iLog->Log( KTestCCHideCursor );
    TPoint position( 100, 100 );
    iConsoleControl->SetFocus( ETrue );
    iConsoleControl->DrawCursor( position );
    iConsoleControl->HideCursor();
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCDrawChars
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCDrawChars( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCDrawChars, "In TestCCDrawChars" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCDrawChars );
    // Print to log file
    iLog->Log( KTestCCDrawChars );
    _LIT( KString, "This is eik console control" );
    TPoint drawCharPoint( 10, 10 );
    TUint characterAttributes = 4;
    iConsoleControl->DrawChars( KString, drawCharPoint, characterAttributes );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCClearChars
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCClearChars( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCClearChars, "In TestCCClearChars" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCClearChars );
    // Print to log file
    iLog->Log( KTestCCClearChars );
    TRect rect( 10, 10, 150, 30 );
    TUint characterAttributes = 4;
    iConsoleControl->ClearChars( rect, characterAttributes );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCInvertChars
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCInvertChars( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCInvertChars, "In TestCCInvertChars" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCInvertChars );
    // Print to log file
    iLog->Log( KTestCCInvertChars );
    TRect rect( 10, 10, 150, 30 );
    iConsoleControl->InvertChars( rect );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCScrollChars
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCScrollChars( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCScrollChars, "In TestCCScrollChars" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCScrollChars );
    // Print to log file
    iLog->Log( KTestCCScrollChars );
    TRect rect( 10, 10, 150, 30 );
    TPoint vector( 10, 10 );
    iConsoleControl->ScrollChars( rect, vector );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCSetScrollBarVisibilityL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCSetScrollBarVisibilityL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCSetScrollBarVisibilityL, "In TestCCSetScrollBarVisibilityL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCSetScrollBarVisibilityL );
    // Print to log file
    iLog->Log( KTestCCSetScrollBarVisibilityL );
    TBool err = KErrNone;
    TRAP( err, TInt scroll = iConsoleControl->SetScrollBarVisibilityL( CEikScrollBarFrame::EAuto, CEikScrollBarFrame::EAuto ) );
    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCUpdateScrollbarsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCUpdateScrollbarsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCUpdateScrollbarsL, "In TestCCUpdateScrollbarsL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCUpdateScrollbarsL );
    // Print to log file
    iLog->Log( KTestCCUpdateScrollbarsL );
    TBool err = KErrNone;
    TSize dataSize( 30, 10 );
    TSize visibleSize( 40, 40 );
    TPoint pt( 10, 10 );
    TRAP( err, TBool result = iConsoleControl->UpdateScrollbarsL( dataSize, visibleSize, pt ) );
    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCHandleScrollEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCHandleScrollEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCHandleScrollEventL, "In TestCCHandleScrollEventL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCHandleScrollEventL );
    // Print to log file
    iLog->Log( KTestCCHandleScrollEventL );
    TBool err = KErrNone;
    CEikScrollBar* eikScrollBar = new( ELeave ) CEikScrollBar();
    CleanupStack::PushL( eikScrollBar );    
    iConsoleContainer = new (ELeave) CMiscControlsContainer();
    iConsoleView = CMiscControlView::NewL();

    iConsoleContainer->SetMopParent( iConsoleView );
    iConsoleContainer->ConstructL( iConsoleView->ClientRect() );
    CCoeEnv::Static()->AppUi()->AddToStackL( iConsoleContainer );
    iConsoleContainer->MakeVisible(ETrue);
    iConsoleScreen->SetConsWin( iConsoleControl );
    iConsoleControl->SetContainerWindowL( *iConsoleContainer );
    eikScrollBar->ConstructL( iConsoleControl, iConsoleContainer, 
            CEikScrollBar::EVertical, 100 );
    TEikScrollEvent event = EEikScrollPageLeft;
    iConsoleControl->SetFocus( ETrue );

    TPoint position( 100, 100 );
    iConsoleControl->DrawCursor( position );

    iConsoleControl->HandleScrollEventL( eikScrollBar, event ) ;
    CleanupStack::PopAndDestroy( eikScrollBar );

    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCUpdateArea
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCUpdateArea( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCUpdateArea, "In TestCCUpdateArea" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCUpdateArea );
    // Print to log file
    iLog->Log( KTestCCUpdateArea );
    iConsoleControl->UpdateArea();
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCGetColorUseListL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCGetColorUseListL, "In TestCCGetColorUseListL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCGetColorUseListL );
    // Print to log file
    iLog->Log( KTestCCGetColorUseListL );
    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) CArrayFixFlat<TCoeColorUse>( 4 );
    CleanupStack::PushL( colorUseList );
    TBool err = KErrNone;
    TRAP( err, iConsoleControl->GetColorUseListL( *colorUseList ) );
    
    colorUseList->Reset();
    CleanupStack::PopAndDestroy(colorUseList);

    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCHandleResourceChange
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCHandleResourceChange( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCHandleResourceChange, "In TestCCHandleResourceChange" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCHandleResourceChange );
    // Print to log file
    iLog->Log( KTestCCHandleResourceChange );
    TInt type = 0;

    iConsoleControl->HandleResourceChange( type );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCHandlePointerEventL, "In TestCCHandlePointerEventL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestCCHandlePointerEventL );
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;
    TBool err = KErrNone;
    TRAP( err, iConsoleControl->HandlePointerEventL( pointEvent ) );

    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCDrawL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCDrawL, "In TestCCDrawL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCDrawL );
    // Print to log file
    iLog->Log( KTestCCDrawL );
    CTestConsoleControl* consoleControl = new (ELeave) CTestConsoleControl();
    CleanupStack::PushL( consoleControl );
    TRect rect( 10, 10, 10, 10 );
    consoleControl->Draw( rect );
    CleanupStack::Pop();

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCSizeChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCSizeChangedL, "In TestCCSizeChangedL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCSizeChangedL );
    // Print to log file
    iLog->Log( KTestCCSizeChangedL );
    CTestConsoleControl* consoleControl = new (ELeave) CTestConsoleControl();
    CleanupStack::PushL( consoleControl );
    consoleControl->SizeChanged();
    CleanupStack::Pop();

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCFocusChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCFocusChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCFocusChangedL, "In TestCCFocusChangedL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCFocusChangedL );
    // Print to log file
    iLog->Log( KTestCCFocusChangedL );
    CTestConsoleControl* consoleControl = new (ELeave) CTestConsoleControl();
    CleanupStack::PushL( consoleControl );
    consoleControl->FocusChanged( ENoDrawNow );
    CleanupStack::Pop();

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCCountComponentControlsL, "In TestCCCountComponentControlsL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCCountComponentControlsL );
    // Print to log file
    iLog->Log( KTestCCCountComponentControlsL );
    CTestConsoleControl* consoleControl = new (ELeave) CTestConsoleControl();
    CleanupStack::PushL( consoleControl );
    TInt control = consoleControl->CountComponentControls();
    CleanupStack::Pop();

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCComponentControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCComponentControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCComponentControlL, "In TestCCComponentControlL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCComponentControlL );
    // Print to log file
    iLog->Log( KTestCCComponentControlL );
    CTestConsoleControl* consoleControl = new (ELeave) CTestConsoleControl();
    CleanupStack::PushL( consoleControl );

    TInt dex = consoleControl->CountComponentControls();
    CCoeControl* control = consoleControl->ComponentControl( dex-1 );
    CleanupStack::Pop( consoleControl );
    STIF_ASSERT_NULL( control );
   

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCCWriteInternalStateL, "In TestCCWriteInternalStateL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCCWriteInternalStateL );
    // Print to log file
    iLog->Log( KTestCCWriteInternalStateL );
    CTestConsoleControl* consoleControl = new (ELeave) CTestConsoleControl();
    CleanupStack::PushL( consoleControl );
    CBufFlat* buf = CBufFlat::NewL( 200 );
    CleanupStack::PushL( buf );
    RBufWriteStream stream;

    stream.Open( *buf );
    TBool err = KErrNone;
    TRAP( err, consoleControl->WriteInternalStateL( stream ) );
    stream.Close();

    CleanupStack::PopAndDestroy( buf );

    CleanupStack::Pop( consoleControl );

    return err;
    }
