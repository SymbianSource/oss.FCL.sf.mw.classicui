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










#include <w32std.h>
#include <e32def.h>
#include <coecntrl.h>
#include <aknbutton.h>
#include <gulicon.h>
#include <AknIconUtils.h>
#include <BARSREAD.H>
#include <AknsItemID.h>
#include <avkon.mbg>
#include <GDI.h>
#include <FBS.H>
#include <coedef.h>
#include <e32cmn.h>


#include <bctestbutton.rsg>
#include "bctestbuttoncase.h"
#include "bctestbuttoncontainer.h"
#include "bctestbutton.hrh"
#include "bctestbuttonex.h"
// constant

const TInt KLeft = 0;
const TInt KTop = 0;
const TInt KRight = 50;
const TInt KBottom = 50;
const TInt KOne = 1;
const TInt KZero = 0;
const TInt KTwo = 2;
const TInt KThree = 3;
const TInt KFour = 4;
const TInt KHundred = 100;


_LIT( strOK, "OK" );
_LIT( strCancel, "Cancel" );
_LIT( strHelp, "Help" );


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestButtonCase* CBCTestButtonCase::NewL(
    CBCTestButtonContainer* aContainer )
    {
    CBCTestButtonCase* self = new( ELeave ) CBCTestButtonCase(
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestButtonCase::CBCTestButtonCase(
    CBCTestButtonContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestButtonCase::~CBCTestButtonCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestButtonCase::ConstructL()
    {
    BuildScriptL();
    eikEnv = CEikonEnv::Static();
    }

// ---------------------------------------------------------------------------
// CBCTestButtonCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestButtonCase::BuildScriptL()
    {
    // Add script as your need.
    const TInt scripts[] =
        {

        DELAY( 1 ),  // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        LeftCBA,

        //outline2
        LeftCBA,
        Down,
        LeftCBA,

        //outline3
        LeftCBA,
        REP( Down, KTwo ),
        LeftCBA,

        //outline4
        LeftCBA,
        REP( Down, KThree ),
        LeftCBA,

        //outline5
        LeftCBA,
        REP( Down, KFour ),
        LeftCBA,

        };
    AddTestScriptL( scripts, sizeof( scripts )/sizeof( TInt ) );
    }

// ---------------------------------------------------------------------------
// CBCTestButtonCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestButtonCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline5 )
        {
        return;
        }

    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            TestAknButtonStateL();
            break;

        case EBCTestCmdOutline2:
            TestAknButtonL();
            break;

        case EBCTestCmdOutline3:
            TestAknButtonExtL();
            break;

        case EBCTestCmdOutline4:
            TestAknButtonProL();
            break;

        case EBCTestCmdOutline5:
            TestAknButtonUtiL();
            break;
        default:
            break;
        }
    }


// ---------------------------------------------------------------------------
// CBCTestButtonCase::CreateIconL
// ---------------------------------------------------------------------------
//
CGulIcon* CBCTestButtonCase::CreateIconL()
    {
    CFbsBitmap *bitmap = new( ELeave ) CFbsBitmap();
    bitmap->Load( AknIconUtils::AvkonIconFileName(), 
                  EMbmAvkonQgn_prop_set_button );
    return CGulIcon::NewL( bitmap );
    }
// ---------------------------------------------------------------------------
// CBCTestButtonCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//
void CBCTestButtonCase::TestAknButtonStateL()
    {
    // Test some API here
    _LIT( strCAknButtonState,
          "Class CAknButtonState function CAknButtonState invoked" );
    _LIT( strCAknButtonStateDes,
          "Class CAknButtonState function ~CAknButtonState invoked" );
    CAknButtonStateEx *btnstat = new( ELeave ) CAknButtonStateEx( KOne );
    AssertNotNullL( btnstat, strCAknButtonState );

    _LIT( strNewL, "Class CAknButtonState function ConstructL invoked" );
    CleanupStack::PushL( btnstat );
    btnstat->ConstructL( CreateIconL(), NULL, NULL, NULL, strOK, strCancel );
    CleanupStack::Pop( btnstat );
    AssertNotNullL( btnstat, strNewL );

    delete btnstat;
    AssertTrueL( ETrue, strCAknButtonStateDes );
    btnstat = NULL;


    _LIT( strNewLOverLoad,
          "Class CAknButtonState function ConstructL( OverLoad ) invoked" );
    CAknButtonStateEx *btnstate = new( ELeave ) CAknButtonStateEx( KOne );
    CleanupStack::PushL( btnstate );
    btnstate->ConstructL( AknIconUtils::AvkonIconFileName(),
                          EMbmAvkonQgn_indi_button_decrease,
                          EMbmAvkonQgn_indi_button_decrease_mask,
                          EMbmAvkonQgn_indi_button_decrease_pressed,
                          EMbmAvkonQgn_indi_button_decrease_pressed_mask,
                          EMbmAvkonQgn_indi_button_increase,
                          EMbmAvkonQgn_indi_button_increase_mask,
                          EMbmAvkonQgn_indi_button_increase_pressed,
                          EMbmAvkonQgn_indi_button_increase_pressed_mask,
                          strOK, strCancel );

    AssertNotNullL( btnstate, strNewLOverLoad );


    _LIT( strHasText, "Class CAknButtonState function HasText invoked" );
    _LIT( strHasHelp, "Class CAknButtonState function HasHelp invoked" );
    TBool hasText = btnstate->HasText();
    AssertTrueL( hasText, strHasText );
    TBool hasHelp = btnstate->HasHelp();
    AssertTrueL( hasHelp, strHasHelp );

    _LIT( strSizeChanged,
          "Class CAknButtonState function SizeChanged invoked" );
    TRect client( KLeft, KTop, KRight, KBottom );
    btnstate->SizeChanged( client, EAspectRatioPreserved );
    AssertTrueL( ETrue, strSizeChanged );

    _LIT( strIcon, "Class CAknButtonState function Icon invoked" );
    _LIT( strDimmedIcon,
          "Class CAknButtonState function DimmedIcon invoked" );
    _LIT( strPressedIcon,
          "Class CAknButtonState function PressedIcon invoked" );
    _LIT( strHoverIcon,
          "Class CAknButtonState function HoverIcon invoked" );
    const CGulIcon *ico = btnstate->Icon();
    AssertNotNullL( const_cast<CGulIcon*>( ico ), strIcon );
    ico = btnstate->DimmedIcon();
    AssertNotNullL( const_cast<CGulIcon*>( ico ), strDimmedIcon );
    ico = btnstate->PressedIcon();
    AssertNotNullL( const_cast<CGulIcon*>( ico ), strPressedIcon );
    ico = btnstate->HoverIcon();
    AssertNotNullL( const_cast<CGulIcon*>( ico ), strHoverIcon );

    _LIT( strTxt, "Class CAknButtonState function Text invoked" );
    _LIT( strHelpText,
          "Class CAknButtonState function HelpText invoked" );
    TDesC strText = btnstate->Text();
    AssertTrueL( ETrue, strTxt );

    strText = btnstate->HelpText();
    AssertTrueL( ETrue, strHelpText );

    _LIT( strFlags, "Class CAknButtonState function Flags invoked" );
    TInt iFlag = btnstate->Flags();
    AssertTrueL( ETrue, strFlags );

    _LIT( strSetIcon,
          "Class CAknButtonState function SetIcon invoked" );
    _LIT( strSetDimmedIcon,
          "Class CAknButtonState function SetDimmedIcon invoked" );
    _LIT( strSetPressedIcon,
          "Class CAknButtonState function SetPressedIcon invoked" );
    _LIT( strSetHoverIcon,
          "Class CAknButtonState function SetHoverIcon invoked" );
    _LIT( strSetTextL,
          "Class CAknButtonState function SetTextL invoked" );
    _LIT( strSetHelpTextL,
          "Class CAknButtonState function SetHelpTextL invoked" );
    _LIT( strSetFlags,
          "Class CAknButtonState function SetFlags invoked" );


    btnstate->SetIcon( CreateIconL() );
    AssertTrueL( ETrue, strSetIcon );
    btnstate->SetDimmedIcon ( CreateIconL() );
    AssertTrueL( ETrue, strSetDimmedIcon );
    btnstate->SetPressedIcon( CreateIconL() );
    AssertTrueL( ETrue, strSetPressedIcon );
    btnstate->SetHoverIcon( CreateIconL() );
    AssertTrueL( ETrue, strSetHoverIcon );

    btnstate->SetTextL( strOK );
    AssertTrueL( ETrue, strSetTextL );
    btnstate->SetHelpTextL( strHelp );
    AssertTrueL( ETrue, strSetHelpTextL );
    btnstate->SetFlags ( KOne );
    AssertTrueL( ETrue, strSetFlags );

    CleanupStack::PopAndDestroy();

    _LIT( strConstructFromResourceL,
          "Class CAknButtonStateEx function ConstructFromResourceL invoked" );

    //CEikonEnv *eikEnv = CEikonEnv::Static();
    TResourceReader resourceReader;
    eikEnv->CreateResourceReaderLC( resourceReader,
                                    R_BCTESTAKN_BUTTON_STATE );
    CAknButtonStateEx *aknbtnst = new( ELeave ) CAknButtonStateEx( KZero );
    CleanupStack::PushL( aknbtnst );
    aknbtnst->ConstructFromResourceL( resourceReader );
    CleanupStack::Pop( aknbtnst );
    AssertNotNullL( aknbtnst, strConstructFromResourceL );
    delete aknbtnst;
    CleanupStack::PopAndDestroy();


    }
void CBCTestButtonCase::TestAknButtonL()
    {

    _LIT( strCAknButton,
          "Class CAknButton function CAknButton invoked" );
    _LIT( strCAknButtonDes,
          "Class CAknButton function ~CAknButton invoked" );
    CAknButton *aknbtn = new( ELeave ) CAknButtonEx( KZero );
    AssertNotNullL( aknbtn, strCAknButton );
    delete aknbtn;
    AssertTrueL( ETrue, strCAknButtonDes );
    aknbtn = NULL;

    _LIT( strNewL, "Class CAknButton function NewL invoked" );
    aknbtn = CAknButtonEx::NewL();
    AssertNotNullL( aknbtn, strNewL );
    delete aknbtn;
    aknbtn = NULL;

    _LIT( strNewLC, "Class CAknButton function NewLC invoked" );
    aknbtn = CAknButtonEx::NewLC();
    AssertNotNullL( aknbtn, strNewLC );
    CleanupStack::PopAndDestroy();
    aknbtn = NULL;

    //CEikonEnv *eikEnv = CEikonEnv::Static();
    TResourceReader resourceReader;
    eikEnv->CreateResourceReaderLC( resourceReader, R_BCTEST_AVKON_BUTTON );

    _LIT( strNewLr,
          "Class CAknButton function NewL( ResourceReader ) invoked" );
    aknbtn = CAknButtonEx::NewL( resourceReader );
    AssertNotNullL( aknbtn, strNewLr );
    delete aknbtn;
    CleanupStack::PopAndDestroy();
    aknbtn = NULL;

    TResourceReader reader;
    eikEnv->CreateResourceReaderLC( reader, R_BCTEST_AVKON_BUTTON );

    _LIT( strNewLCr,
      "Class CAknButton function NewLC( ResourceReader ) overload invoked" );
    aknbtn = CAknButtonEx::NewLC( reader );
    AssertNotNullL( aknbtn, strNewLCr );
    CleanupStack::PopAndDestroy();//aknbtn
    CleanupStack::PopAndDestroy();//reader
    aknbtn = NULL;

    _LIT( strNewLri,
          "Class CAknButton function NewL( TInt ResourceID ) invoked" );
    aknbtn = CAknButtonEx::NewL( R_BCTEST_AVKON_BUTTON );
    AssertNotNullL( aknbtn, strNewLri );
    delete aknbtn;
    aknbtn = NULL;

    _LIT( strNewLCri,
          "Class CAknButton function NewLC( TInt ResourceID ) invoked" );
    aknbtn = CAknButtonEx::NewLC( R_BCTEST_AVKON_BUTTON );
    AssertNotNullL( aknbtn, strNewLCri );
    CleanupStack::PopAndDestroy();
    aknbtn = NULL;


    _LIT( strNewLion,
          "Class CAknButton function NewL( CGulIcon... ) invoked" );
    aknbtn = CAknButtonEx::NewL( CreateIconL(), CreateIconL(),
                                 CreateIconL(), CreateIconL(),
                                 strOK, strHelp, KZero, KOne );
    AssertNotNullL( aknbtn, strNewLion );
    delete aknbtn;
    aknbtn = NULL;

    _LIT( strNewLCion,
          "Class CAknButton function NewLC( CGulIcon... ) invoked" );
    aknbtn = CAknButtonEx::NewLC( CreateIconL(), CreateIconL(),
                                  CreateIconL(), CreateIconL(),
                                  strOK, strHelp, KZero, KOne );
    AssertNotNullL( aknbtn, strNewLCion );
    CleanupStack::PopAndDestroy();//aknbtn
    aknbtn = NULL;

    _LIT( strNewLfile,
             "Class CAknButton function NewL( const TDesC...) invoked" );
    aknbtn = CAknButtonEx::NewL( AknIconUtils::AvkonIconFileName(),
                                 EMbmAvkonQgn_indi_button_decrease,
                                 EMbmAvkonQgn_indi_button_decrease_mask,
                                 EMbmAvkonQgn_indi_button_decrease_pressed,
                               EMbmAvkonQgn_indi_button_decrease_pressed_mask,
                                 EMbmAvkonQgn_indi_button_increase,
                                 EMbmAvkonQgn_indi_button_increase_mask,
                                 EMbmAvkonQgn_indi_button_increase_pressed,
                               EMbmAvkonQgn_indi_button_increase_pressed_mask,
                                 strOK, strHelp, KZero, KOne );
    AssertNotNullL( aknbtn, strNewLfile );
    delete aknbtn;
    aknbtn = NULL;

    _LIT( strNewLCfile,
            "Class CAknButton function NewLC( const TDesC...) invoked" );
    aknbtn = CAknButtonEx::NewLC( AknIconUtils::AvkonIconFileName(),
                                  EMbmAvkonQgn_indi_button_decrease,
                                  EMbmAvkonQgn_indi_button_decrease_mask,
                                  EMbmAvkonQgn_indi_button_decrease_pressed,
                                EMbmAvkonQgn_indi_button_decrease_pressed_mask,
                                  EMbmAvkonQgn_indi_button_increase,
                                  EMbmAvkonQgn_indi_button_increase_mask,
                                  EMbmAvkonQgn_indi_button_increase_pressed,
                                EMbmAvkonQgn_indi_button_increase_pressed_mask,
                                  strOK, strHelp, KZero, KOne );
    AssertNotNullL( aknbtn, strNewLCfile );

    CleanupStack::PopAndDestroy();
    aknbtn = NULL;

    }

void CBCTestButtonCase::TestAknButtonExtL()
    {
    //CEikonEnv *eikEnv = CEikonEnv::Static();
    TResourceReader iReader;
    eikEnv->CreateResourceReaderLC( iReader, R_BCTEST_AVKON_BUTTON );

    _LIT( strConstructL, "Class CAknButton function ConstructL invoked" );
    _LIT( strConstructFromRes,
          "Class CAknButton function ConstructFromResourceL invoked" );
    CAknButtonEx *aknbtn = new( ELeave ) CAknButtonEx( KZero );
    CleanupStack::PushL( aknbtn );
    aknbtn->ConstructL();
    AssertTrueL( ETrue, strConstructL );
    aknbtn->ConstructFromResourceL( iReader );
    AssertTrueL( ETrue, strConstructFromRes );


    _LIT( strHandleResChange,
          "Class CAknButton function HandleResourceChange invoked" );
    aknbtn->HandleResourceChange ( 0 );
    AssertTrueL( ETrue, strHandleResChange );

    _LIT( strMinimumSize, "Class CAknButton function MinimumSize invoked" );
    aknbtn->MinimumSize();
    AssertTrueL( ETrue, strMinimumSize );

    _LIT( strSetDimmed, "Class CAknButton function SetDimmed invoked" );
    aknbtn->SetDimmed( ETrue );
    AssertTrueL( ETrue, strSetDimmed );

    _LIT( strOfferKeyEventL,
          "Class CAknButton function OfferKeyEventL invoked" );
    TKeyEvent keyEvent = { EKeyPause, EStdKeySpace, 0, 0  };
    aknbtn->OfferKeyEventL( keyEvent, EEventKey );
    AssertTrueL( ETrue, strOfferKeyEventL );

    _LIT( strMakeVisible, "Class CAknButton function MakeVisible invoked" );
    aknbtn->MakeVisible( ETrue );
    AssertTrueL( ETrue, strMakeVisible );

    _LIT( strPrepareForFocusLossL,
          "Class CAknButton function PrepareForFocusLossL invoked" );
    aknbtn->PrepareForFocusLossL();
    AssertTrueL( ETrue, strPrepareForFocusLossL );

    _LIT( strPrepareForFocusGainL,
          "Class CAknButton function PrepareForFocusGainL invoked" );
    aknbtn->PrepareForFocusGainL();
    AssertTrueL( ETrue, strPrepareForFocusGainL );

    _LIT( strHandlePointerEventL,
          "Class CAknButton function HandlePointerEventL invoked" );
    TPointerEvent pointerEvent =
               { TPointerEvent::EButton1Up,
                 EModifierAutorepeatable,
                 TPoint( 20,20 ), TPoint( 0,0 ) };
    aknbtn->HandlePointerEventL( pointerEvent );
    AssertTrueL( ETrue, strHandlePointerEventL );

    CleanupStack::PopAndDestroy();//aknbtn
    CleanupStack::PopAndDestroy();//iReader
    aknbtn = NULL;

    _LIT( strConstructFromRIDL,
        "Class CAknButton function ConstructFromResourceL( TInt ) invoked" );
    aknbtn = new( ELeave ) CAknButtonEx( KZero );
    CleanupStack::PushL( aknbtn );
    aknbtn->ConstructL();
    aknbtn->ConstructFromResourceL( R_BCTEST_AVKON_BUTTON );
    AssertTrueL( ETrue, strConstructFromRIDL );

    _LIT( strSetHighlightRect,
          "Class CAknButton function SetHighlightRect invoked" );
    TRect rect( KLeft, KTop, KRight, KBottom );
    aknbtn->SetHighlightRect( rect );
    AssertTrueL( ETrue, strSetHighlightRect );

    _LIT( strHighlightRect,
          "Class CAknButton function HighlightRect invoked" );
    TRect hRect = aknbtn->HighlightRect();
    AssertTrueL( ETrue, strHighlightRect );

    aknbtn->SetContainerWindowL( *iContainer );
    _LIT( strActivateL, "Class CAknButton function ActivateL invoked" );
    aknbtn->ActivateL();
    AssertTrueL( ETrue, strActivateL );

    _LIT( strSetCurrentState,
          "Class CAknButton function SetCurrentState invoked" );
    aknbtn->SetCurrentState( 0, ETrue );
    AssertTrueL( ETrue, strSetCurrentState );

    CleanupStack::PopAndDestroy();
    aknbtn = NULL;

    }


void CBCTestButtonCase::TestAknButtonProL()
    {

    _LIT( strConstructProL,
          "Class CAknButton function ConstructL( const TDesC... ) invoked" );
    CAknButtonEx* aknbtn = new( ELeave ) CAknButtonEx( KOne );
    CleanupStack::PushL( aknbtn );
    aknbtn->ConstructL( AknIconUtils::AvkonIconFileName(),
                                  EMbmAvkonQgn_indi_button_decrease,
                                  EMbmAvkonQgn_indi_button_decrease_mask,
                                  EMbmAvkonQgn_indi_button_decrease_pressed,
                                EMbmAvkonQgn_indi_button_decrease_pressed_mask,
                                  EMbmAvkonQgn_indi_button_increase,
                                  EMbmAvkonQgn_indi_button_increase_mask,
                                  EMbmAvkonQgn_indi_button_increase_pressed,
                                EMbmAvkonQgn_indi_button_increase_pressed_mask,
                                  strOK, strHelp, KOne );
    AssertNotNullL( aknbtn, strConstructProL );

    _LIT( strSetCurrentState,
          "Class CAknButton function SetCurrentState invoked" );
    aknbtn->SetCurrentState( KOne, ETrue );
    AssertTrueL( ETrue, strSetCurrentState );

    _LIT( strAddStateL, "Class CAknButton function SetAddStateL invoked" );
    aknbtn->AddStateL( CreateIconL(), CreateIconL(),
                       CreateIconL(), CreateIconL(), strOK, strHelp, KOne );
    AssertTrueL( ETrue, strAddStateL );

    _LIT( strSetAddStateProL,
       "Class CAknButton function SetCurrentState( const TDesC...) invoked" );
    aknbtn->AddStateL( AknIconUtils::AvkonIconFileName(),
                       EMbmAvkonQgn_indi_button_decrease,
                       EMbmAvkonQgn_indi_button_decrease_mask,
                       EMbmAvkonQgn_indi_button_decrease_pressed,
                       EMbmAvkonQgn_indi_button_decrease_pressed_mask,
                       EMbmAvkonQgn_indi_button_increase,
                       EMbmAvkonQgn_indi_button_increase_mask,
                       EMbmAvkonQgn_indi_button_increase_pressed,
                       EMbmAvkonQgn_indi_button_increase_pressed_mask,
                       strOK, strHelp, KOne, KAknsIIDNone,
                       KAknsIIDNone, KAknsIIDNone, KAknsIIDNone );
    AssertTrueL( ETrue, strSetAddStateProL );

    _LIT( strSetButtonFlags,
          "Class CAknButton function SetButtonFlags invoked" );
    aknbtn->SetButtonFlags( KOne );
    AssertTrueL( ETrue, strSetButtonFlags );

    TAknsItemID id;
    id.Set( KAknsIIDDefault );
    _LIT( strSetFrameAndCenterIds,
          "Class CAknButton function SetFrameAndCenterIds invoked" );
    aknbtn->SetFrameAndCenterIds( id, id, id ,id ,id, id, id, id, id, id );
    AssertTrueL( ETrue, strSetFrameAndCenterIds );

    _LIT( strSetBackgroundIds,
          "Class CAknButton function SetSetBackgroundIds invoked" );
    aknbtn->SetBackgroundIds( id, id, id, id, id );
    AssertTrueL( ETrue, strSetBackgroundIds );

    //const CFont *font = CEikonEnv::Static()->NormalFont();
    const CFont *font = eikEnv->NormalFont();
    _LIT( strSetTextFont, "Class CAknButton function SetTextFont invoked" );
    aknbtn->SetTextFont( font );
    AssertTrueL( ETrue, strSetTextFont );

    _LIT( strSetTextColorIds,
          "Class CAknButton function SetTextColorIds invoked" );
    aknbtn->SetTextColorIds( id, 0 );
    AssertTrueL( ETrue, strSetTextColorIds );

    _LIT( strSetTextHorizontalAlignment,
          "Class CAknButton function SetTextHorizontalAlignment invoked" );
    aknbtn->SetTextHorizontalAlignment( CGraphicsContext::ELeft );
    AssertTrueL( ETrue, strSetTextHorizontalAlignment );

    _LIT( strSetTextVerticalAlignment,
          "Class CAknButton function SetTextVerticalAlignment invoked" );
    aknbtn->SetTextVerticalAlignment( CAknButton::EBottom );
    AssertTrueL( ETrue, strSetTextVerticalAlignment );

    _LIT( strSetTextUnderlineStyle,
          "Class CAknButton function SetTextUnderlineStyle invoked" );
    aknbtn->SetTextUnderlineStyle( EUnderlineOff );
    AssertTrueL( ETrue, strSetTextUnderlineStyle );

    // HS    
    _LIT( strSetTextAndIconAlignment,
          "Class CAknButton function SetTextAndIconAlignment invoked" );
    aknbtn->SetTextAndIconAlignment( CAknButton::EIconBeforeText );
    AssertTrueL( ETrue, strSetTextAndIconAlignment );

    _LIT( strSetIconScaleMode,
          "Class CAknButton function SetIconScaleMode invoked" );
    aknbtn->SetIconScaleMode( EAspectRatioPreserved );
    AssertTrueL( ETrue, strSetIconScaleMode );

    _LIT( strSetIconHorizontalAlignment,
          "Class CAknButton function SetIconHorizontalAlignment invoked" );
    aknbtn->SetIconHorizontalAlignment( CAknButton::EBottom );
    AssertTrueL( ETrue, strSetIconHorizontalAlignment );

    _LIT( strSetIconVerticalAlignment,
          "Class CAknButton function SetIconVerticalAlignment invoked" );
    aknbtn->SetIconVerticalAlignment( CAknButton::EBottom );
    AssertTrueL( ETrue, strSetIconVerticalAlignment );

    _LIT( strSetHelpNoteTimeouts,
          "Class CAknButton function SetHelpNoteTimeouts invoked" );
    aknbtn->SetHelpNoteTimeouts( KHundred, KHundred );
    AssertTrueL( ETrue, strSetHelpNoteTimeouts );

    _LIT( strSetKeyRepeatInterval,
          "Class CAknButton function SetKeyRepeatInterval invoked" );
    aknbtn->SetKeyRepeatInterval( KHundred, KHundred );
    AssertTrueL( ETrue, strSetKeyRepeatInterval );

    _LIT( strSetLongPressInterval,
          "Class CAknButton function SetLongPressInterval invoked" );
    aknbtn->SetLongPressInterval( KHundred );
    AssertTrueL( ETrue, strSetLongPressInterval );

    _LIT( strStateIndex, "Class CAknButton function StateIndex invoked" );
    aknbtn->StateIndex();
    AssertTrueL( ETrue, strStateIndex );

    _LIT( strDisablePictographs,
          "Class CAknButton function DisablePictographs invoked" );
    aknbtn->DisablePictographs();
    AssertTrueL( ETrue, strDisablePictographs );

    _LIT( strEnablePictographsL,
          "Class CAknButton function EnablePictographsL invoked" );
    CAknPictographInterface* interface = NULL;
    aknbtn->EnablePictographsL( *interface );
    AssertTrueL( ETrue, strEnablePictographsL );
    
    CleanupStack::PopAndDestroy();
    aknbtn = NULL;

    }


void CBCTestButtonCase::TestAknButtonUtiL()
    {

    _LIT( strConstructL,
          "Class CAknButton function ConstructL( CGulIcon... ) invoked" );
    CAknButtonEx* aknbtn = new( ELeave ) CAknButtonEx( KOne );
    CleanupStack::PushL( aknbtn );
    aknbtn->ConstructL( CreateIconL(), CreateIconL(),
                        CreateIconL(), CreateIconL(),
                        strOK, strHelp, KOne );
    AssertNotNullL( aknbtn, strConstructL );
    aknbtn->SetContainerWindowL( *iContainer );

    _LIT( strSetTooltipPosition,
          "Class CAknButton function SetTooltipPosition invoked" );
    aknbtn->SetTooltipPosition( CAknButton::EPositionTop );
    AssertTrueL( ETrue, strSetTooltipPosition );

    _LIT( strSetRequestExit,
          "Class CAknButton function SetTooltipPosition invoked" );
    aknbtn->SetRequestExit( ETrue );
    AssertTrueL( ETrue, strSetRequestExit );

    _LIT( strIsDimmed, "Class CAknButton function IsDimmed invoked" );
    aknbtn->IsDimmed();
    AssertTrueL( ETrue, strIsDimmed );

    _LIT( strSetDimmedHelpTextL,
          "Class CAknButton function SetDimmedHelpTextL invoked" );
    aknbtn->SetDimmedHelpTextL( strHelp );
    AssertTrueL( ETrue, strSetDimmedHelpTextL );


    _LIT( strState, "Class CAknButton function State invoked" );
    CAknButtonState* aknbst = aknbtn->State();
    AssertNotNullL( aknbst, strState );
    aknbst = NULL;

    _LIT( strStatePr, "Class CAknButton function State( TInt ) invoked" );
    aknbst = aknbtn->State( KZero );
    AssertNotNullL( aknbst, strStatePr );

    _LIT( strButtonFlags, "Class CAknButton function ButtonFlags invoked" );
    aknbtn->ButtonFlags();
    AssertTrueL( ETrue, strButtonFlags );

    TMargins8 margin;
    margin.iLeft = KLeft;
    margin.iRight = KRight;
    margin.iBottom = KBottom;
    margin.iTop = KTop;
    _LIT( strSetMargins, "Class CAknButton function SetMargins invoked" );
    aknbtn->SetMargins( margin );
    AssertTrueL( ETrue, strSetMargins );

    TSize size( KRight, KBottom );
    _LIT( strSetIconSize, "Class CAknButton function SetIconSize invoked" );
    aknbtn->SetIconSize( size );
    AssertTrueL( ETrue, strSetIconSize );

    _LIT( KResetState, "Class CAknButton function ResetState invoked" );
    aknbtn->ResetState();
    AssertTrueL( ETrue, KResetState );
    
   _LIT(KPositionChanged,"Class CAknButton function PositionChanged invoked");
    aknbtn->PositionChanged();
    AssertTrueL( ETrue, KPositionChanged );
    
    _LIT( strSizeChanged, "Class CAknButton function SizeChanged invoked" );
    aknbtn->SizeChanged();
    AssertTrueL( ETrue, strSizeChanged );

    _LIT( strFocusChanged,
          "Class CAknButton function FocusChanged invoked" );
    aknbtn->FocusChanged( EDrawNow );
    AssertTrueL( ETrue, strFocusChanged );

    _LIT( strExtensionInterface,
          "Class CAknButton function ExtensionInterface invoked" );
    TUid uid = TUid::Uid( KZero );
    aknbtn->ExtensionInterface( uid );
    AssertTrueL( ETrue, strExtensionInterface );


    _LIT( strChangeState, "Class CAknButton function ChangeState invoked" );
    aknbtn->ChangeState( ETrue );
    AssertTrueL( ETrue, strChangeState );

    _LIT( strGetCurrentText,
          "Class CAknButton function GetCurrentText invoked" );
    TDesC tdText = aknbtn->GetCurrentText();
    AssertTrueL( ETrue, strGetCurrentText );

    _LIT( strGetCurrentIcon,
          "Class CAknButton function GetCurrentIcon invoked" );
    const CGulIcon* icon = aknbtn->GetCurrentIcon();
    AssertNotNullL( const_cast< CGulIcon* >( icon ), strGetCurrentIcon );

    aknbtn->SetContainerWindowL( *iContainer );
    aknbtn->SetDimmed( EFalse );
    _LIT( strShowHelpL, "Class CAknButton function ShowHelpL invoked" );
    aknbtn->ShowHelpL();
    AssertTrueL( ETrue, strShowHelpL );

    _LIT( strHideHelp, "Class CAknButton function HideHelp invoked" );
    aknbtn->HideHelp();
    AssertTrueL( ETrue, strHideHelp );

    CleanupStack::PopAndDestroy();
    aknbtn = NULL;

    }
