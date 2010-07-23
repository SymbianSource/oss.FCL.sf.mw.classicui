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
* Description:         Implements test bc for eik control group.
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <bctestmisccontrol.rsg>
#include <bctestmisccontrol.mbg>
#include <eikenv.h>
#include <eikctgrp.h>       // CEikControlGroup
#include <eikcba.h>         // CEikCba
#include <s32mem.h>         // RBufWriteStream
#include <eikkwin.h>        // CEikKeyWindow
#include <eikmover.h>       // CEikMover
#include <barsread.h>       // TResourceRead
#include <eiktbar.h>        // CEikToolBar
#include <eikbutb.h>        // TEikButtonCoordinator

#include "bctesteikcontrolgroupcase.h"
#include "bctestsubeikcontrolgroup.h"
#include "bctestsubeikmover.h"
#include "bctestsubeiktoolbar.h"
#include "bctestsubcommandobserver.h"
#include "bctestmisccontrolcontainer.h"
#include "bctestmisccontrol.hrh"
#include "autotestcommands.h"

//Constant for CEikControlGroup
_LIT( KECGEikControlGroup, "Eik control group created" );
_LIT( KECGConstructL, "Invoke CEikControlGroup's ConstructL()" );
_LIT( KECGAddControlL, "Invoke CEikControlGroup's AddControlL()" );
_LIT( KECGIndexById, "Invoke CEikControlGroup's IndexById()" );
_LIT( KECGControl, "Invoke CEikControlGroup's Control()" );
_LIT( KECGInsertControlL, "Invoke CEikControlGroup's InsertControlL()" );
_LIT( KECGControlArray, "Invoke CEikControlGroup's ControlArray()" );
_LIT( KECGControlId, "Invoke CEikControlGroup's ControlId()" );
_LIT( KECGControlById, "Invoke CEikControlGroup's ControlById()" );
_LIT( KECGSetControlSpacing, 
    "Invoke CEikControlGroup's SetControlSpacing()" );
_LIT( KECGControlSpacing, "Invoke CEikControlGroup's ControlSpacing()" );
_LIT( KECGGetColorUseListL, 
    "Invoke CEikControlGroup's GetColorUseListL()" );
_LIT( KECGHandlePointerEventL, 
    "Invoke CEikControlGroup's HandlePointerEventL()" );
_LIT( KECGLayoutControls, 
    "Invoke CEikControlGroup's LayoutControls()" );
_LIT( KECGSetBreadthInPixels, 
    "Invoke CEikControlGroup's SetBreadthInPixels()" );
_LIT( KECGSetControlLayout, 
    "Invoke CEikControlGroup's SetControlLayout()" );
_LIT( KECGSetControlsAllSameSize, 
    "Invoke CEikControlGroup's SetControlsAllSameSize()" );
_LIT( KECGDeleteControl, "Invoke CEikControlGroup's DeleteControl()" );
_LIT( KECGReset, "Invoke CEikControlGroup's Reset()" );
_LIT( KECGWriteInternalStateL, 
    "Invoke CEikControlGroup's WriteInternalStateL()" );
    
//Constant for CEikKeyWindow
_LIT( KEKWEikKeyWindow, "Eik key window created" );
_LIT( KEKWConstructL, "Invoke CEikKeyWindow's ConstructL()" );
_LIT( KEKWHandlePointerEventL, 
    "Invoke CEikKeyWindow's HandlePointerEventL()" );

//Constant for CEikMover
_LIT( KEMEikMover, "Eik mover created" );
_LIT( KEMConstructFromResourceL, 
    "Invoke CEikMover's ConstructFromResourceL" );
_LIT( KEMText, "Eik Mover Text" );
_LIT( KEMSetText, "Invoke CEikMover's SetText" );
_LIT( KEMOtherText, "Other Eik Mover Text" );
_LIT( KEMSetTextL, "Invoke CEikMover's SetTextL" );
_LIT( KEMActive, "Invoke CEikMover's Active" );
_LIT( KEMSetActive, "Invoke CEikMover's SetActive" );
_LIT( KEMMinimumSize, "Invoke CEikMover's MinimumSize" );
_LIT( KEMGetColorUseListL, "Invoke CEikMover's GetColorUseListL()" );
_LIT( KEMHandlePointerEventL, "Invoke CEikMover's HandlePointerEventL()" );
_LIT( KEMSetTitleLeftMargin, "Invoke CEikMover's SetTitleLeftMargin()" );
_LIT( KEMSetFont, "Invoke CEikMover's SetFont()" );
_LIT( KEMWriteInternalStateL, "Invoke CEikMover's WriteInternalStateL()" );

//Constant for CEikToolBar
_LIT( KETBEikToolBar, "Eik tool bar created" );
_LIT( KETBConstructFromResourceL, 
    "Invoke CEikToolBar's ConstructFromResourceL()" );
_LIT( KETBAddControlL, "Invoke CEikToolBar's AddControlL()" );
_LIT( KETBAddControlLOver, "Invoke CEikToolBar's AddControlL() again" );
_LIT( KETBDelayActivation, "Invoke CEikToolBar's DelayActivation()" );
_LIT( KETBSetDimmed, "Invoke CEikToolBar's SetDimmed()" );
_LIT( KETBSetBoundingRect, "Invoke CEikToolBar's SetBoundingRect()" );
_LIT( KETBReduceRect, "Invoke CEikToolBar's ReduceRect()" );
_LIT( KETBGetColorUseListL, "Invoke CEikToolBar's GetColorUseListL()" );
_LIT( KETBHandlePointerEventL, "Invoke CEikToolBar's HandlePointerEventL()" );
_LIT( KETBHandleResourceChange, 
    "Invoke CEikToolBar's HandleResourceChange()" );
_LIT( KETBCoordinateButtons, 
    "Invoke CEikToolBar's CoordinateButtons()" );
_LIT( KETBConstructL, "Invoke CEikToolBar's ConstructL()" );
_LIT( KETBSetCommandObserver, 
    "Invoke CEikToolBar's SetCommandObserver()" );
_LIT( KETBSetButtonStateOn, 
    "Invoke CEikToolBar's SetButtonStateOn()" );
_LIT( KETBWriteInternalStateL, "Invoke CEikToolBar's WriteInternalStateL()" );

const TInt KZero = 0;
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KThree = 3;
const TInt KFour = 4;
const TInt KFive = 5;
const TInt KTen = 10;
const TInt KTwenty = 20;
const TInt KTwentyFive = 25;
const TInt KFifty = 50;
const TInt KTwoHundred = 200;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestEikControlGroupCase* CBCTestEikControlGroupCase::NewL(
    CBCTestMiscControlContainer* aContainer )
    {
    CBCTestEikControlGroupCase* self = 
        new( ELeave ) CBCTestEikControlGroupCase( aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestEikControlGroupCase::CBCTestEikControlGroupCase(
    CBCTestMiscControlContainer* aContainer ) : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestEikControlGroupCase::~CBCTestEikControlGroupCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestEikControlGroupCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestEikControlGroupCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestEikControlGroupCase::BuildScriptL()
    {
    const TInt scripts[] =
        {
        //outline7
        DELAY( KOne ),  // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        REP( Down, KTwo ),
        KeyOK,
        KeyOK,

        //outline8
        LeftCBA,
        REP( Down, KThree ),
        KeyOK,
        KeyOK,
        
        //outline9
        LeftCBA,
        REP( Down, KFour ),
        KeyOK,
        KeyOK, 
        
        //outline10
        LeftCBA,
        REP( Down, KFive ),
        KeyOK,
        KeyOK               
        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );    
    }

// ---------------------------------------------------------------------------
// CBCTestEikControlGroupCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestEikControlGroupCase::RunL( TInt aCmd )
    {
    if ( ( aCmd < EBCTestMiscControlCmdOutline07 ) 
        || ( aCmd > EBCTestMiscControlCmdOutline10 ) )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestMiscControlCmdOutline07:
            TestFunctionsForEikControlGroupL();
            break;
        case EBCTestMiscControlCmdOutline08:
            TestFunctionsForEikKeyWindowL();
            break;
        case EBCTestMiscControlCmdOutline09:
            TestFunctionsForEikMoverL();
            break;   
        case EBCTestMiscControlCmdOutline10:
            TestFunctionsForEikToolBarL();
            break;                      
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestEikControlGroupCase::TestFunctionsForEikControlGroupL
// ---------------------------------------------------------------------------
//
void CBCTestEikControlGroupCase::TestFunctionsForEikControlGroupL()
    {
    // Invoke CEikControlGroup's CEikControlGroup()
    CEikControlGroup* controlGroup = new( ELeave ) CEikControlGroup();
    CleanupStack::PushL( controlGroup );
    AssertNotNullL( controlGroup, KECGEikControlGroup );
    
    // Invoke CEikControlGroup's ConstructL()
    controlGroup->ConstructL( CEikControlGroup::EFromTopLeft, 
        CEikControlGroup::ELayHorizontally );
    AssertTrueL( ETrue,KECGConstructL ); 
    
    // Invoke CEikControlGroup's AddControlL()
    CCoeControl* coeControl = new( ELeave ) CCoeControl();
    CleanupStack::PushL( coeControl );
    controlGroup->AddControlL( coeControl, KOne );
    CleanupStack::Pop( coeControl );
    AssertTrueL( ETrue, KECGAddControlL ); 
    
    // Invoke CEikControlGroup's IndexById()
    TInt index = controlGroup->IndexById( KOne );
    AssertIntL( KZero, index, KECGIndexById ); 
    
    // Invoke CEikControlGroup's Control()
    controlGroup->Control( index );
    AssertTrueL( ETrue, KECGControl );
    
    // Invoke CEikControlGroup's InsertControlL()
    CCoeControl* inserterControl = new( ELeave ) CCoeControl();
    TEikGroupControl ctrl;
    ctrl.iControl = inserterControl;
    ctrl.iId = KTwo;
    controlGroup->InsertControlL( ctrl, KOne );
    AssertTrueL( ETrue, KECGInsertControlL );
    
    // Invoke CEikControlGroup's ControlArray()
    controlGroup->ControlArray();
    AssertTrueL( ETrue, KECGControlArray );
    
    // Invoke CEikControlGroup's ControlId()
    controlGroup->ControlId( inserterControl );
    AssertTrueL( ETrue, KECGControlId );
    
    // Invoke CEikControlGroup's ControlById()
    controlGroup->ControlById( KOne );
    AssertTrueL( ETrue, KECGControlById );
    

    // Invoke CEikControlGroup's SetControlSpacing()
    controlGroup->SetControlSpacing( KThree, KThree );
    AssertTrueL( ETrue, KECGSetControlSpacing );

    // Invoke CEikControlGroup's ControlSpacing()
    TInt vSpacing;
    TInt hSpacing;
    controlGroup->ControlSpacing( vSpacing, hSpacing );
    AssertTrueL( ETrue, KECGControlSpacing );
    
    // Invoke CEikControlGroup's GetColorUseListL()
    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
        CArrayFixFlat<TCoeColorUse>( KFour );
    CleanupStack::PushL( colorUseList );
    controlGroup->GetColorUseListL( *colorUseList );
    AssertTrueL( ETrue, KECGGetColorUseListL );
    colorUseList->Reset();
    CleanupStack::PopAndDestroy( colorUseList );
    
    // Invoke CEikControlGroup's HandlePointerEventL()  
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;  
    controlGroup->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KECGHandlePointerEventL );
   
    // Invoke CEikControlGroup's LayoutControls()  
    controlGroup->LayoutControls();
    AssertTrueL( ETrue, KECGLayoutControls );
    
    // Invoke CEikControlGroup's SetBreadthInPixels()  
    controlGroup->SetBreadthInPixels( KTwo );
    AssertTrueL( ETrue, KECGSetBreadthInPixels ); 
    
    // Invoke CEikControlGroup's SetControlLayout()  
    controlGroup->SetControlLayout( CEikControlGroup::EFromTopLeft, 
        CEikControlGroup::ELayHorizontally );
    AssertTrueL( ETrue, KECGSetControlLayout );        
    
    // Invoke CEikControlGroup's SetControlsAllSameSize()  
    controlGroup->SetControlsAllSameSize();
    AssertTrueL( ETrue, KECGSetControlsAllSameSize );     
    
    // Invoke CEikControlGroup's DeleteControl()
    controlGroup->DeleteControl( KZero, KOne );
    AssertTrueL( ETrue, KECGDeleteControl );    
    
    // Invoke CEikControlGroup's Reset()
    controlGroup->Reset();
    AssertTrueL( ETrue, KECGReset ); 
    
    CBCTestSubEikControlGroup* subEikControlGroup = 
        static_cast<CBCTestSubEikControlGroup*> ( controlGroup );
    
    //Invoke CEikControlGroup's WriteInternalStateL();
    CBufFlat* buf = CBufFlat::NewL( KTwoHundred );
    CleanupStack::PushL( buf );
    RBufWriteStream stream;
    stream.Open( *buf );
    subEikControlGroup->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KECGWriteInternalStateL ); 
    stream.Close();
    CleanupStack::PopAndDestroy( buf );

    CleanupStack::PopAndDestroy( controlGroup );
    }
    
// ---------------------------------------------------------------------------
// CBCTestEikControlGroupCase::TestFunctionsForEikKeyWindowL
// ---------------------------------------------------------------------------
//
void CBCTestEikControlGroupCase::TestFunctionsForEikKeyWindowL()
    {
    CEikKeyWindow* eikKeyWindow = new( ELeave ) CEikKeyWindow();
    CleanupStack::PushL( eikKeyWindow );
    AssertNotNullL( eikKeyWindow, KEKWEikKeyWindow );
        
    // Invoke CEikKeyWindow's ConstructL()
    TPoint point( KTen, KTen );
    TSize ss( KFifty, KFifty );
    eikKeyWindow->ConstructL( point, ss, KFive, KTen, KThree, KThree, 
        CEikKeyWindow::EHorizontal );
    AssertTrueL( ETrue, KEKWConstructL );     
    
    // Invoke CEikKeyWindow's HandlePointerEventL()  
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;  
    eikKeyWindow->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KEKWHandlePointerEventL );
        
    CleanupStack::PopAndDestroy ( eikKeyWindow );
    }
    
// ---------------------------------------------------------------------------
// CBCTestEikControlGroupCase::TestFunctionsForEikMoverL
// ---------------------------------------------------------------------------
//
void CBCTestEikControlGroupCase::TestFunctionsForEikMoverL()
    {
    // Invoke CEikMover's CEikMover()  
    CEikMover* eikMover = new( ELeave ) CEikMover();
    CleanupStack::PushL( eikMover ); 
    AssertNotNullL( eikMover, KEMEikMover );
    
    // Invoke CEikMover's ConstructFromResourceL()  
    TResourceReader reader;
    iContainer->GetCoeEnv()->CreateResourceReaderLC( 
        reader, R_BCTESTMISCCONTROL_EIK_MOVER_DIALOG );
    eikMover->ConstructFromResourceL( reader );
    AssertTrueL( ETrue, KEMConstructFromResourceL );  
    CleanupStack::PopAndDestroy(); //reader 
    
    // Invoke CEikMover's SetText()  
    TBufC<KTwenty> statckbuf( KEMText );
    HBufC* heapBuf = statckbuf.AllocL();
    eikMover->SetText( heapBuf );
    AssertTrueL( ETrue, KEMSetText );  
    
    // Invoke CEikMover's SetTextL()  
    TBufC<KTwentyFive> bufC( KEMOtherText );
    eikMover->SetTextL( bufC );
    AssertTrueL( ETrue, KEMSetTextL );     

    // Invoke CEikMover's Active() 
    TBool flag = eikMover->Active();
    AssertTrueL( ETrue, KEMActive );

    // Invoke CEikMover's SetActive() 
    eikMover->SetActive( EFalse );
    eikMover->SetActive( ETrue );
    AssertTrueL( ETrue, KEMSetActive );
    
    // Invoke CEikMover's MinimumSize() 
    eikMover->MinimumSize();
    AssertTrueL( ETrue, KEMMinimumSize );    
    
    // Invoke CEikMover's GetColorUseListL()
    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
        CArrayFixFlat<TCoeColorUse>( KFour );
    CleanupStack::PushL( colorUseList );
    eikMover->GetColorUseListL( *colorUseList );
    AssertTrueL( ETrue, KEMGetColorUseListL );
    colorUseList->Reset();
    CleanupStack::PopAndDestroy( colorUseList );
    
    // Invoke CEikMover's HandlePointerEventL()  
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;  
    eikMover->HandlePointerEventL( pointEvent );
    pointEvent.iType = TPointerEvent::EButton1Up;  
    eikMover->HandlePointerEventL( pointEvent );    
    AssertTrueL( ETrue, KEMHandlePointerEventL );  
    
    // Invoke CEikMover's SetTitleLeftMargin()  
    eikMover->SetTitleLeftMargin( KFive );
    AssertTrueL( ETrue, KEMSetTitleLeftMargin ); 
      
    // Invoke CEikMover's SetFont()
    CEikonEnv* eikEnv = static_cast<CEikonEnv*> ( iContainer->GetCoeEnv() ); 
    CleanupStack::PushL( eikEnv );
    const CFont* ff = eikEnv->TitleFont();
    eikMover->SetFont( ff );
    AssertTrueL( ETrue, KEMSetFont );
    CleanupStack::Pop( eikEnv );
    
    CBCTestSubEikMover* subEikMover = 
        static_cast<CBCTestSubEikMover*> ( eikMover );
    
    //Invoke CEikMover's WriteInternalStateL();
    CBufFlat* buf = CBufFlat::NewL( KTwoHundred );
    CleanupStack::PushL( buf );
    RBufWriteStream stream;
    stream.Open( *buf );
    subEikMover->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KEMWriteInternalStateL ); 
    stream.Close();
    CleanupStack::PopAndDestroy( buf );
    
    CleanupStack::PopAndDestroy( eikMover );    
           
    }    
    
// ---------------------------------------------------------------------------
// CBCTestEikControlGroupCase::TestFunctionsForEikToolBarL
// ---------------------------------------------------------------------------
//
void CBCTestEikControlGroupCase::TestFunctionsForEikToolBarL()
    {
    CEikToolBar* toolBar = new( ELeave ) CEikToolBar();
    CleanupStack::PushL( toolBar ); 
    AssertNotNullL( toolBar, KETBEikToolBar );

    TResourceReader reader;
    iContainer->GetCoeEnv()->CreateResourceReaderLC( 
        reader, R_BCTESTMISCCONTROL_EIK_TOOL_BAR );    
    toolBar->ConstructFromResourceL( reader );
    AssertTrueL( ETrue, KETBConstructFromResourceL );  
    CleanupStack::PopAndDestroy();      //reader 
     
    // Invoke CEikToolBar's AddControlL()
    CCoeControl* coeControl = new( ELeave ) CCoeControl();
    CleanupStack::PushL( coeControl );
    toolBar->AddControlL( coeControl, KOne );
    CleanupStack::Pop( coeControl );    
    AssertTrueL( ETrue, KETBAddControlL ); 
    
    // Invoke CEikToolBar's AddControlL()
    CEikButtonBase* buttonBase = new( ELeave ) CEikButtonBase();
    TEikGroupControl ctrl;
    ctrl.iControl = buttonBase;
    ctrl.iId = KTwo;
    toolBar->AddControlL( ctrl );
    AssertTrueL( ETrue, KETBAddControlLOver );
    
    // Invoke CEikToolBar's SetButtonStateOn()
    toolBar->SetButtonStateOn( KTwo, EFalse );
    toolBar->SetButtonStateOn( KTwo, ETrue );
    AssertTrueL( ETrue, KETBSetButtonStateOn );    
    
    // Invoke CEikToolBar's DelayActivation()
    toolBar->DelayActivation();
    AssertTrueL( ETrue, KETBDelayActivation );

    // Invoke CEikToolBar's SetDimmed()
    toolBar->SetDimmed( ETrue );
    AssertTrueL( ETrue, KETBSetDimmed );
    
    // Invoke CEikToolBar's SetBoundingRect()
    TRect rect( KFive, KFive, KFifty, KFifty );
    toolBar->SetBoundingRect( rect );
    AssertTrueL( ETrue, KETBSetBoundingRect ); 
    
    // Invoke CEikToolBar's ReduceRect()
    toolBar->ReduceRect( rect );
    AssertTrueL( ETrue, KETBReduceRect ); 
    
    // Invoke CEikToolBar's GetColorUseListL()
    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
        CArrayFixFlat<TCoeColorUse>( KFour );
    CleanupStack::PushL( colorUseList );
    toolBar->GetColorUseListL( *colorUseList );
    AssertTrueL( ETrue, KETBGetColorUseListL );
    colorUseList->Reset();
    CleanupStack::PopAndDestroy( colorUseList );
    
    // Invoke CEikToolBar's HandlePointerEventL()  
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;  
    toolBar->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KETBHandlePointerEventL );
    
    // Invoke CEikToolBar's HandleResourceChange()  
    toolBar->HandleResourceChange( KZero );
    AssertTrueL( ETrue, KETBHandleResourceChange );
    
    // Invoke CEikToolBar's CoordinateButtons()
    TEikButtonCoordinator* ebc = new( ELeave ) TEikButtonCoordinator;
    CleanupStack::PushL( ebc );
    toolBar->CoordinateButtons( KOne, KZero, ebc );
    AssertTrueL( ETrue, KETBCoordinateButtons );    
    CleanupStack::PopAndDestroy( ebc );
    
    CleanupStack::PopAndDestroy( toolBar ); 
    toolBar = NULL;  
    
    toolBar = new( ELeave ) CEikToolBar();
    CleanupStack::PushL( toolBar ); 
     
    // Invoke CEikToolBar's ConstructL()
    TBCTestSubCommandObserver* obs = new( ELeave ) TBCTestSubCommandObserver;
    CleanupStack::PushL( obs );
    toolBar->ConstructL( obs, R_BCTESTMISCCONTROL_EIK_TOOL_BAR, rect );
    AssertTrueL( ETrue, KETBConstructL );    
    
    // Invoke CEikToolBar's SetCommandObserver()
    toolBar->SetCommandObserver( obs );
    AssertTrueL( ETrue, KETBSetCommandObserver );
    
    CBCTestSubEikToolBar* subEikToolBar = 
        static_cast<CBCTestSubEikToolBar*> ( toolBar );
    
    //Invoke CEikToolBar's WriteInternalStateL();
    CBufFlat* buf = CBufFlat::NewL( KTwoHundred );
    CleanupStack::PushL( buf );
    RBufWriteStream stream;
    stream.Open( *buf );
    subEikToolBar->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KETBWriteInternalStateL ); 
    stream.Close();
    CleanupStack::PopAndDestroy( buf );
    
    CleanupStack::PopAndDestroy( obs );
    CleanupStack::PopAndDestroy( toolBar ); 
    }
    

    





    
   

    
