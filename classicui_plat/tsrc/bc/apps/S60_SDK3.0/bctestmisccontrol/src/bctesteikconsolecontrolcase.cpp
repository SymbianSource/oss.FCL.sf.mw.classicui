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
* Description:         Implements test bc for eik console control.
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <bctestmisccontrol.rsg>
#include <bctestmisccontrol.mbg>
#include <eikconso.h>       // CEikConsoleControl
#include <s32mem.h>         // RBufWriteStream
#include <gdi.h>            // TFontSpec

#include "bctesteikconsolecontrolcase.h"
#include "bctestsubeikconsolecontrol.h"
#include "bctestmisccontrolcontainer.h"
#include "bctestmisccontrol.hrh"
#include "autotestcommands.h"
 
//Constant for CEikConsoleControl
_LIT( KECCEikConsoleControl, "Eik console control created" );
_LIT( KECCConstructL, "Invoke CEikConsoleControl's ConstructL()" );
_LIT( KECCSetFontL, "Invoke CEikConsoleControl's SetFontL()" );
_LIT( KECCConstructLOver, "Invoke CEikConsoleControl's ConstructL() again" );
_LIT( KECCSetRedrawer, "Invoke CEikConsoleControl's SetRedrawer()" );
_LIT( KECCVisibleSize, "Invoke CEikConsoleControl's VisibleSize()" );
_LIT( KECCSetCursorHeight, "Invoke CEikConsoleControl's SetCursorHeight()" );
_LIT( KECCDrawCursor, "Invoke CEikConsoleControl's DrawCursor()" );
_LIT( KECCHideCursor, "Invoke CEikConsoleControl's HideCursor()" );
_LIT( KString, "This is eik console control" );
_LIT( KECCDrawChars, "Invoke CEikConsoleControl's DrawChars()" );
_LIT( KECCClearChars, "Invoke CEikConsoleControl's ClearChars()" );
_LIT( KECCInvertChars, "Invoke CEikConsoleControl's InvertChars()" );
_LIT( KECCScrollChars, "Invoke CEikConsoleControl's ScrollChars()" );
_LIT( KECCSetScrollBarVisibilityL, 
    "Invoke CEikConsoleControl's SetScrollBarVisibilityL()" );
_LIT( KECCUpdateScrollbarsL, 
    "Invoke CEikConsoleControl's UpdateScrollbarsL()" );
_LIT( KECCHandleScrollEventL, 
    "Invoke CEikConsoleControl's HandleScrollEventL()" );
_LIT( KECCGetColorUseListL, 
    "Invoke CEikConsoleControl's GetColorUseListL()" );
_LIT( KECCHandleResourceChange, 
    "Invoke CEikConsoleControl's HandleResourceChange()" );
_LIT( KECCHandlePointerEventL, 
    "Invoke CEikConsoleControl's HandlePointerEventL()" );
_LIT( KECCSizeChanged, "Invoke CEikConsoleControl's SizeChanged()" );
_LIT( KECCFocusChanged, "Invoke CEikConsoleControl's FocusChanged()" );
_LIT( KECCCountComponentControls, 
    "Invoke CEikConsoleControl's CountComponentControls()" );
_LIT( KECCComponentControl, 
    "Invoke CEikConsoleControl's ComponentControl()" );
_LIT( KECCWriteInternalStateL, 
    "Invoke CEikConsoleControl's WriteInternalStateL()" );
_LIT( KECCDraw, "Invoke CEikConsoleControl's Draw()" );

// Constant for CEikConsoleControl
_LIT( KECSEikConsoleScreen, "Create EikConsoleScreen" );
_LIT( KECSTitle, "Console Screen" );
_LIT( KECSConstructL, "Invoke CEikConsoleScreen's ConstructL()" );
_LIT( KECSConstructLOver, 
    "Invoke CEikConsoleScreen's ConstructL() again" );
_LIT( KECSConstructLOverLoad,  
    "Invoke CEikConsoleScreen's ConstructL() last time" );
_LIT( KECSCreate, "Invoke CEikConsoleScreen's Create()" );
_LIT( KECSRead, "Invoke CEikConsoleScreen's Read()" );
_LIT( KECSReadCancel, "Invoke CEikConsoleScreen's ReadCancel()" );
_LIT( KECSKeyCode, "Invoke CEikConsoleScreen's KeyCode()" );
_LIT( KECSKeyModifiers, "Invoke CEikConsoleScreen's KeyModifiers()" );
_LIT( KECSSetTitle, "Invoke CEikConsoleScreen's SetTitle()" );
_LIT( KECSScreenSize, "Invoke CEikConsoleScreen's ScreenSize()" );
_LIT( KECSFlushChars, "Invoke CEikConsoleScreen's FlushChars()" );
_LIT( KECSCursorPos, "Invoke CEikConsoleScreen's CursorPos()" );
_LIT( KECSSetCursorPosAbs, 
    "Invoke CEikConsoleScreen's SetCursorPosAbs()" );
_LIT( KECSSetCursorPosRel, 
    "Invoke CEikConsoleScreen's SetCursorPosRel()" );
_LIT( KECSSetCursorHeight, 
    "Invoke CEikConsoleScreen's SetCursorHeight()" );        
_LIT( KWriteBuf, "This is Eik Console Screen" );
_LIT( KECSWrite, "Invoke CEikConsoleScreen's Write()" );
_LIT( KECSClearScreen, "Invoke CEikConsoleScreen's ClearScreen()" );
_LIT( KECSClearToEndOfLine, 
    "Invoke CEikConsoleScreen's ClearToEndOfLine()" );
_LIT( KECSClearChars, "Invoke CEikConsoleScreen's ClearChars()" );
_LIT( KECSDrawCursorInSight, 
    "Invoke CEikConsoleScreen's DrawCursorInSight()" );
_LIT( KECSDrawInSight, "Invoke CEikConsoleScreen's DrawInSight()" );
_LIT( KECSDrawCursor, "Invoke CEikConsoleScreen's DrawCursor()" );
_LIT( KECSHideCursor, "Invoke CEikConsoleScreen's HideCursor()" );
_LIT( KECSUp, "Invoke CEikConsoleScreen's Up()" );
_LIT( KECSDown, "Invoke CEikConsoleScreen's Down()" );
_LIT( KECSLeft, "Invoke CEikConsoleScreen's Left()" );
_LIT( KECSRight, "Invoke CEikConsoleScreen's Right()" );
_LIT( KECSCr, "Invoke CEikConsoleScreen's Cr()" );
_LIT( KECSLf, "Invoke CEikConsoleScreen's Lf()" );
_LIT( KECSScrollChars, "Invoke CEikConsoleScreen's ScrollChars()" );
_LIT( KECSRedraw, "Invoke CEikConsoleScreen's Redraw()" );
_LIT( KECSMoveTopLeft, "Invoke CEikConsoleScreen's MoveTopLeft()" );
_LIT( KECSSetHistorySizeL, 
    "Invoke CEikConsoleScreen's SetHistorySizeL()" );
_LIT( KECSSetAtt, "Invoke CEikConsoleScreen's SetAtt()" );
_LIT( KECSSetAttOverLoad, "Invoke CEikConsoleScreen's SetAtt() again" );
_LIT( KECSFont, "Invoke CEikConsoleScreen's Font()" );
_LIT( KECSSetFontL, "Invoke CEikConsoleScreen's SetFontL()" );
_LIT( KECSSelection, "Invoke CEikConsoleScreen's Selection()" );
_LIT( KECSSetSelection, "Invoke CEikConsoleScreen's SetSelection()" );
_LIT( KECSSelectCursor, "Invoke CEikConsoleScreen's SelectCursor()" );
_LIT( KECSRetrieveL, "Invoke CEikConsoleScreen's RetrieveL()" );
_LIT( KECSSetPureCRLF, "Invoke CEikConsoleScreen's SetPureCRLF()" );
_LIT( KECSSetAllPrintable, 
    "Invoke CEikConsoleScreen's SetAllPrintable()" );
_LIT( KECSSetScrollLock, "Invoke CEikConsoleScreen's SetScrollLock()" );
_LIT( KECSSetKeepCursorInSight, 
    "Invoke CEikConsoleScreen's SetKeepCursorInSight()" );
_LIT( KECSSetScrollBarVisibilityL, 
    "Invoke CEikConsoleScreen's SetScrollBarVisibilityL()" );
_LIT( KECSUpdateScrollBars, 
    "Invoke CEikConsoleScreen's UpdateScrollBars()" );

const TInt KZero = 0;
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KFour = 4;
const TInt KTen = 10;
const TInt KFifteen = 15;
const TInt KTwenty = 20;
const TInt KThirty = 30;
const TInt KFourty = 40;
const TInt KFifty = 50;
const TInt KOneHundred = 100;
const TInt KOneHundredAndFifty = 150;
const TInt KTwoHundred = 200;
const TUint KPercentage = 1;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestEikConsoleControlCase* CBCTestEikConsoleControlCase::NewL(
    CBCTestMiscControlContainer* aContainer )
    {
    CBCTestEikConsoleControlCase* self = 
        new( ELeave ) CBCTestEikConsoleControlCase( aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestEikConsoleControlCase::CBCTestEikConsoleControlCase(
    CBCTestMiscControlContainer* aContainer ) : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestEikConsoleControlCase::~CBCTestEikConsoleControlCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestEikConsoleControlCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestEikConsoleControlCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestEikConsoleControlCase::BuildScriptL()
    {
    const TInt scripts[] =
        {
        //outline4
        DELAY( KOne ),  // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        Down,
        KeyOK,
        KeyOK,

        //outline5
        LeftCBA,
        Down,
        KeyOK,
        Down,
        KeyOK,
        
        //outline6
        LeftCBA,
        Down,
        KeyOK,
        REP( Down, KTwo ),
        KeyOK        
        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );    
    }

// ---------------------------------------------------------------------------
// CBCTestEikConsoleControlCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestEikConsoleControlCase::RunL( TInt aCmd )
    {
    if ( ( aCmd < EBCTestMiscControlCmdOutline04 ) 
        || ( aCmd > EBCTestMiscControlCmdOutline06 ) )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestMiscControlCmdOutline04:
            TestFunctionsForEikConsoleControlL();
            break;
        case EBCTestMiscControlCmdOutline05:
            TestProtectedFunctionsForEikConsoleControlL();
            break;
        case EBCTestMiscControlCmdOutline06:
            TestFunctionsForEikConsoleScreenL();
            break;            
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestEikConsoleControlCase::TestFunctionsForEikConsoleControlL
// ---------------------------------------------------------------------------
//
void CBCTestEikConsoleControlCase::TestFunctionsForEikConsoleControlL()
    {
    //Invoke CEikConsoleControl's CEikConsoleControl();
    CEikConsoleControl* eikConsoleControl = 
        new( ELeave ) CEikConsoleControl();
    CleanupStack::PushL( eikConsoleControl );
    AssertNotNullL( eikConsoleControl, KECCEikConsoleControl );
    
    //Invoke CEikConsoleControl's ConstructL();
    eikConsoleControl->ConstructL( CEikConsoleScreen::EUseBackedUpWindow );
    AssertTrueL( ETrue, KECCConstructL );
    
    //Invoke CEikConsoleControl's SetFontL();
    TFontSpec* fontSpec = new( ELeave ) TFontSpec();
    CleanupStack::PushL( fontSpec );
    CFbsFont*  editorFont = iContainer->GetCoeEnv()->CreateScreenFontL( 
                                                      *fontSpec );
    CleanupStack::PushL( editorFont );
    eikConsoleControl->SetFontL( *fontSpec, editorFont );
    AssertTrueL( ETrue, KECCSetFontL );    
    iContainer->GetCoeEnv()->ReleaseScreenFont( editorFont ); 
    CleanupStack::Pop( editorFont );            
    CleanupStack::PopAndDestroy( fontSpec );  
    
    CleanupStack::PopAndDestroy( eikConsoleControl );
    eikConsoleControl = NULL;
    
    //Invoke CEikConsoleControl's ConstructL();
    eikConsoleControl = new( ELeave ) CEikConsoleControl();
    CleanupStack::PushL( eikConsoleControl );
    TPoint point( KZero, KZero );
    TSize  ss( KTwenty, KTwenty );
    eikConsoleControl->ConstructL( point, ss, 
        CEikConsoleScreen::EUseBackedUpWindow, EEikConsWinInPixels );
    AssertTrueL( ETrue, KECCConstructLOver );
    
    //Invoke CEikConsoleScreen's CEikConsoleScreen();
    CEikConsoleScreen* eikConsoleScreen = new( ELeave ) CEikConsoleScreen();
    CleanupStack::PushL( eikConsoleScreen );
    
    //Invoke CEikConsoleControl's HandleScrollEventL();
    CEikScrollBar* eikScrollBar = new( ELeave ) CEikScrollBar();
    CleanupStack::PushL( eikScrollBar );    
    eikScrollBar->ConstructL( eikConsoleControl, iContainer, 
        CEikScrollBar::EVertical, KOneHundred );
    //TInt newThumbPos = aScrollBar->ThumbPosition();
    //TInt pageSize = aScrollBar->Model()->iThumbSpan;
    //eikConsoleControl->HandleScrollEventL( eikScrollBar, EEikScrollPageLeft );
    AssertTrueL( ETrue, KECCHandleScrollEventL );
    CleanupStack::PopAndDestroy( eikScrollBar );    

    //Invoke CEikConsoleControl's SetRedrawer();
    eikConsoleControl->SetRedrawer( eikConsoleScreen );
    AssertTrueL( ETrue, KECCSetRedrawer );

    //Invoke CEikConsoleControl's VisibleSize();
    eikConsoleControl->VisibleSize();
    AssertTrueL( ETrue, KECCVisibleSize );    
    
    //Invoke CEikConsoleControl's SetCursorHeight();
    eikConsoleControl->SetCursorHeight( KPercentage );
    AssertTrueL( ETrue, KECCSetCursorHeight ); 
    
    //Invoke CCoeControl's SetFocus();
    eikConsoleControl->SetFocus( ETrue );
    
    //Invoke CEikConsoleControl's DrawCursor();
    TPoint cursor( KTen, KTen );
    eikConsoleControl->DrawCursor( cursor );
    AssertTrueL( ETrue, KECCDrawCursor );     
 
     //Invoke CEikConsoleControl's HideCursor();
    eikConsoleControl->HideCursor();
    AssertTrueL( ETrue, KECCHideCursor );
    
     //Invoke CEikConsoleControl's DrawChars();
    TPoint drawCharPoint( KTen, KTen );
    eikConsoleControl->DrawChars( KString, drawCharPoint, KFour );
    AssertTrueL( ETrue, KECCDrawChars );
    
     //Invoke CEikConsoleControl's ClearChars();
    TRect rect( KTen, KTen, KOneHundredAndFifty, KThirty );
    eikConsoleControl->ClearChars( rect, KFour );
    AssertTrueL( ETrue, KECCClearChars );

     //Invoke CEikConsoleControl's InvertChars();
    eikConsoleControl->InvertChars( rect );
    AssertTrueL( ETrue, KECCInvertChars );    
    
     //Invoke CEikConsoleControl's ScrollChars();
    TPoint vPoint( KOneHundredAndFifty, KTen );
    eikConsoleControl->ScrollChars( rect, vPoint );
    AssertTrueL( ETrue, KECCScrollChars );
    
    //Invoke CEikConsoleControl's SetScrollBarVisibilityL();
    eikConsoleControl->SetScrollBarVisibilityL( CEikScrollBarFrame::EAuto,
        CEikScrollBarFrame::EAuto );
    AssertTrueL( ETrue, KECCSetScrollBarVisibilityL );
    
    //Invoke CEikConsoleControl's UpdateScrollbarsL();
    TSize dataSize( KThirty, KTen );
    TSize visibleSize( KFourty, KFourty );
    TPoint pt( KTen, KTen );
    eikConsoleControl->UpdateScrollbarsL( dataSize, visibleSize, pt );    
    AssertTrueL( ETrue, KECCUpdateScrollbarsL );
    
    //Invoke CEikConsoleControl's GetColorUseListL();
    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
        CArrayFixFlat<TCoeColorUse>( KFour );
    CleanupStack::PushL( colorUseList );
    eikConsoleControl->GetColorUseListL( *colorUseList );
    AssertTrueL( ETrue, KECCGetColorUseListL );
    colorUseList->Reset();
    CleanupStack::PopAndDestroy( colorUseList );
    
    //Invoke CEikConsoleControl's HandleResourceChange();
    eikConsoleControl->HandleResourceChange( KZero );
    AssertTrueL( ETrue, KECCHandleResourceChange ); 

    //Invoke CEikConsoleControl's HandlePointerEventL();
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down; 
    eikConsoleControl->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KECCHandlePointerEventL );
           
    CleanupStack::PopAndDestroy( eikConsoleScreen );   
    CleanupStack::PopAndDestroy( eikConsoleControl );
    
    }
    
// ---------------------------------------------------------------------------
// CBCTestEikConsoleControlCase::TestProtectedFunctionsForEikConsoleControlL
// ---------------------------------------------------------------------------
//
void CBCTestEikConsoleControlCase
    ::TestProtectedFunctionsForEikConsoleControlL()
    {
    CBCTestSubEikConsoleControl* subConsoleControl = 
        new( ELeave ) CBCTestSubEikConsoleControl();   
    CleanupStack::PushL( subConsoleControl );
    subConsoleControl->ConstructL( CEikConsoleScreen::EUseBackedUpWindow );
    AssertTrueL( ETrue, KECCConstructL );
    
    //Invoke CEikConsoleControl's SizeChanged();
    subConsoleControl->SizeChanged();
    AssertTrueL( ETrue, KECCSizeChanged );
    
    //Invoke CEikConsoleControl's FocusChanged();
    subConsoleControl->FocusChanged( ENoDrawNow );
    AssertTrueL( ETrue, KECCFocusChanged );

    //Invoke CEikConsoleControl's CountComponentControls();
    TInt cCount;
    cCount = subConsoleControl->CountComponentControls();
    AssertTrueL( ETrue, KECCCountComponentControls );
    
    //Invoke CEikConsoleControl's ComponentControl();
    subConsoleControl->ComponentControl( cCount - KOne );
    AssertTrueL( ETrue, KECCComponentControl );
    
    //Invoke CEikConsoleControl's Draw();
    subConsoleControl->Draw( iContainer->Rect() );
    AssertTrueL( ETrue, KECCDraw );
    
    //Invoke CEikConsoleControl's WriteInternalStateL();
    CBufFlat* buf = CBufFlat::NewL( KTwoHundred );
    CleanupStack::PushL( buf );
    RBufWriteStream stream;
    stream.Open( *buf );
    subConsoleControl->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KECCWriteInternalStateL ); 
    stream.Close();
    CleanupStack::PopAndDestroy( buf );
            
    CleanupStack::PopAndDestroy( subConsoleControl );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestEikConsoleControlCase::TestFunctionsForEikConsoleScreenL
// ---------------------------------------------------------------------------
//
void CBCTestEikConsoleControlCase::TestFunctionsForEikConsoleScreenL()
    { 
    CEikConsoleScreen* consoleScreen = new( ELeave ) CEikConsoleScreen();
    CleanupStack::PushL( consoleScreen );
    AssertNotNullL( consoleScreen, KECSEikConsoleScreen ); 
    
    //Invoke CEikConsoleScreen's ConstructL();
    TPoint ltPoint( KZero, KZero );
    TSize csSize( KOneHundred, KOneHundred );
    consoleScreen->ConstructL( KECSTitle, ltPoint, csSize, 
        CEikConsoleScreen::ENoInitialCursor );
    AssertTrueL( ETrue, KECSConstructL );
    
    CleanupStack::PopAndDestroy( consoleScreen );
    consoleScreen = NULL;    

    consoleScreen = new( ELeave ) CEikConsoleScreen();
    CleanupStack::PushL( consoleScreen );
    //Invoke CEikConsoleScreen's ConstructL() again;
    consoleScreen->ConstructL( KECSTitle, csSize,
        CEikConsoleScreen::ENoInitialCursor );
    AssertTrueL( ETrue, KECSConstructLOver );    
    CleanupStack::PopAndDestroy( consoleScreen );
    consoleScreen = NULL;
    
    consoleScreen = new( ELeave ) CEikConsoleScreen();
    CleanupStack::PushL( consoleScreen );
    //Invoke CEikConsoleScreen's ConstructL() last time;
    consoleScreen->ConstructL( KECSTitle, 
        CEikConsoleScreen::ENoInitialCursor );
    AssertTrueL( ETrue, KECSConstructLOverLoad );
    
    //Invoke CEikConsoleScreen's ConstructL();
    consoleScreen->Create( KECSTitle, csSize );
    AssertTrueL( ETrue, KECSCreate );
    
    //Invoke CEikConsoleScreen's Read();
    TRequestStatus status;
    consoleScreen->Read( status );
    AssertTrueL( ETrue, KECSRead );
    
    //Invoke CEikConsoleScreen's ReadCancel();
    consoleScreen->ReadCancel();
    AssertTrueL( ETrue, KECSReadCancel ); 
    
    //Invoke CEikConsoleScreen's KeyCode();
    consoleScreen->KeyCode();
    AssertTrueL( ETrue, KECSKeyCode );       
    
    //Invoke CEikConsoleScreen's KeyModifiers();
    consoleScreen->KeyModifiers();
    AssertTrueL( ETrue, KECSKeyModifiers );   

    //Invoke CEikConsoleScreen's SetTitle();
    consoleScreen->SetTitle( KECSTitle );
    AssertTrueL( ETrue, KECSSetTitle );      
    
    //Invoke CEikConsoleScreen's ScreenSize();
    consoleScreen->ScreenSize();
    AssertTrueL( ETrue, KECSScreenSize );     
    
    //Invoke CEikConsoleScreen's FlushChars();
    consoleScreen->FlushChars();
    AssertTrueL( ETrue, KECSFlushChars ); 
    
    //Invoke CEikConsoleScreen's CursorPos();
    TPoint cursorPos;
    cursorPos = consoleScreen->CursorPos();
    AssertTrueL( ETrue, KECSCursorPos );           

    //Invoke CEikConsoleScreen's SetCursorPosAbs();
    consoleScreen->SetCursorPosAbs( cursorPos );
    AssertTrueL( ETrue, KECSSetCursorPosAbs );  
    
    //Invoke CEikConsoleScreen's SetCursorPosRel();
    consoleScreen->SetCursorPosRel( cursorPos );
    AssertTrueL( ETrue, KECSSetCursorPosRel ); 
    
    //Invoke CEikConsoleScreen's SetCursorHeight();
    consoleScreen->SetCursorHeight( KOne );
    AssertTrueL( ETrue, KECSSetCursorHeight );  
    
    //Invoke CEikConsoleScreen's Write();
    consoleScreen->Write( KWriteBuf );
    AssertTrueL( ETrue, KECSWrite );

    //Invoke CEikConsoleScreen's ClearScreen();
    consoleScreen->ClearScreen();
    AssertTrueL( ETrue, KECSClearScreen );
    
    //Invoke CEikConsoleScreen's ClearToEndOfLine();
    consoleScreen->ClearToEndOfLine();
    AssertTrueL( ETrue, KECSClearToEndOfLine );    
    
    //Invoke CEikConsoleScreen's ClearChars();
    TRect rect( KTen, KTen, KOneHundredAndFifty, KThirty );
    consoleScreen->ClearChars( rect, KFour );    
    AssertTrueL( ETrue, KECSClearChars );
    
    //Invoke CEikConsoleScreen's DrawCursorInSight();
    consoleScreen->DrawCursorInSight();    
    AssertTrueL( ETrue, KECSDrawCursorInSight );
    
    //Invoke CEikConsoleScreen's DrawInSight();
    TPoint pInSight( KTwenty, KTwenty );
    consoleScreen->DrawInSight( pInSight );    
    AssertTrueL( ETrue, KECSDrawInSight );
    
    //Invoke CEikConsoleScreen's DrawCursor();
    consoleScreen->DrawCursor();    
    AssertTrueL( ETrue, KECSDrawCursor ); 
    
    //Invoke CEikConsoleScreen's HideCursor();
    consoleScreen->HideCursor();    
    AssertTrueL( ETrue, KECSHideCursor );  
    
    //Invoke CEikConsoleScreen's Up();
    consoleScreen->Up();    
    AssertTrueL( ETrue, KECSUp ); 
    
    //Invoke CEikConsoleScreen's Down();
    consoleScreen->Down();    
    AssertTrueL( ETrue, KECSDown ); 
    
    //Invoke CEikConsoleScreen's Left();
    consoleScreen->Left();    
    AssertTrueL( ETrue, KECSLeft ); 
    
    //Invoke CEikConsoleScreen's Right();
    consoleScreen->Right();    
    AssertTrueL( ETrue, KECSRight );  
    
    //Invoke CEikConsoleScreen's Cr();
    consoleScreen->Cr();    
    AssertTrueL( ETrue, KECSCr );  

    //Invoke CEikConsoleScreen's Lf();
    consoleScreen->Lf();    
    AssertTrueL( ETrue, KECSLf ); 
    
    //Invoke CEikConsoleScreen's ScrollChars();
    TPoint vPoint( KOneHundredAndFifty, KTen );
    consoleScreen->ScrollChars( rect, vPoint );   // rect define before  
    AssertTrueL( ETrue, KECSScrollChars ); 
    
    //Invoke CEikConsoleScreen's Redraw();
    consoleScreen->Redraw( rect );  // rect define before  
    AssertTrueL( ETrue, KECSRedraw ); 

    //Invoke CEikConsoleScreen's MoveTopLeft();
    consoleScreen->MoveTopLeft( ltPoint ); // ltPoint define before   
    AssertTrueL( ETrue, KECSMoveTopLeft ); 
    
    //Invoke CEikConsoleScreen's SetHistorySizeL();
    consoleScreen->SetHistorySizeL( KFifty, KFifty ); 
    AssertTrueL( ETrue, KECSSetHistorySizeL );
    
    //Invoke CEikConsoleScreen's SetAtt();
    consoleScreen->SetAtt( KFour ); 
    AssertTrueL( ETrue, KECSSetAtt );
    
    //Invoke CEikConsoleScreen's SetAtt();
    consoleScreen->SetAtt( KTen, KFifteen ); 
    AssertTrueL( ETrue, KECSSetAttOverLoad );    
    
    //Invoke CEikConsoleScreen's Font();
    TFontSpec fontSpec = consoleScreen->Font(); 
    AssertTrueL( ETrue, KECSFont ); 
    
    //Invoke CEikConsoleScreen's SetFontL();
    consoleScreen->SetFontL( fontSpec ); 
    AssertTrueL( ETrue, KECSSetFontL ); 
    
    //Invoke CEikConsoleScreen's Selection();
    TRect rectSelection = consoleScreen->Selection(); 
    AssertTrueL( ETrue, KECSSelection ); 

    //Invoke CEikConsoleScreen's SetSelection();
    consoleScreen->SetSelection( rectSelection ); 
    AssertTrueL( ETrue, KECSSetSelection );     

    //Invoke CEikConsoleScreen's SelectCursor();
    consoleScreen->SelectCursor(); 
    AssertTrueL( ETrue, KECSSelectCursor );         

    //Invoke CEikConsoleScreen's RetrieveL();
    HBufC* selection = consoleScreen->RetrieveL( rectSelection ); 
    AssertTrueL( ETrue, KECSRetrieveL );
    delete selection;
    
    //Invoke CEikConsoleScreen's SetPureCRLF();
    consoleScreen->SetPureCRLF( CEikConsoleScreen::ENoInitialCursor ); 
    AssertTrueL( ETrue, KECSSetPureCRLF );
    
    //Invoke CEikConsoleScreen's SetAllPrintable();
    consoleScreen->SetAllPrintable( CEikConsoleScreen::ENoInitialCursor ); 
    AssertTrueL( ETrue, KECSSetAllPrintable );
    
    //Invoke CEikConsoleScreen's SetScrollLock();
    consoleScreen->SetScrollLock( CEikConsoleScreen::ENoInitialCursor ); 
    AssertTrueL( ETrue, KECSSetScrollLock );
    
    //Invoke CEikConsoleScreen's SetKeepCursorInSight();
    consoleScreen->SetKeepCursorInSight( 
        CEikConsoleScreen::ENoInitialCursor ); 
    AssertTrueL( ETrue, KECSSetKeepCursorInSight );

    //Invoke CEikConsoleScreen's SetScrollBarVisibilityL();
    consoleScreen->SetScrollBarVisibilityL( 
        CEikScrollBarFrame::EAuto, CEikScrollBarFrame::EAuto ); 
    AssertTrueL( ETrue, KECSSetScrollBarVisibilityL );
    
    //Invoke CEikConsoleScreen's UpdateScrollBars();
    consoleScreen->UpdateScrollBars(); 
    AssertTrueL( ETrue, KECSUpdateScrollBars );        
            
    CleanupStack::PopAndDestroy( consoleScreen );
    }
    





    
   

    
