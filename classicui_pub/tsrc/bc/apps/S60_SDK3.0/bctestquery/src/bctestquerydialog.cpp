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
* Description:         test case for query dialog
*
*/









#include <w32std.h>
#include <eikenv.h>
#include <aknquerydialog.h>
#include <barsread.h>
#include <aknutils.h>
#include <akniconutils.h>
#include <avkon.mbg>

#include "bctestquerydialog.h"
#include "bctestquerycontainer.h"
#include "bctestquery.hrh"
#include <bctestquery.rsg>

const TInt KBufLength = 64;

_LIT( KDataText, "Data text" );
_LIT( KTestQueryTest1, "CAknTextQueryDialog::NewL" );
_LIT( KTestQueryTest2, "CAknTextQueryDialog constructor" );
_LIT( KTestQueryTest3, "CAknTextQueryDialog::RemoveEditorIndicator" );
_LIT( KTestQueryTest4, "CAknTextQueryDialog::SetEmergencyCallSupport" );
_LIT( KTestQueryTest5, "CAknTextQueryDialog::SetPredictiveTextInputPermitted" );
_LIT( KTestQueryTest6, "CAknTextQueryDialog::Prompt" );
_LIT( KTestQueryTest7, "CAknTextQueryDialog::Heading" );
_LIT( KTestQueryTest8, "CAknTextQueryDialog::PreLayoutDynInitL" );
_LIT( KTestQueryTest9, "CAknTextQueryDialog::QueryControl" );
_LIT( KTestQueryTest10, "CAknTextQueryDialog::SetMaxLength" );
_LIT( KTestQueryTest11, "CAknTextQueryDialog::MaxTextLength" );
_LIT( KTestQueryTest12, "CAknTextQueryDialog::HandleQueryEditorSizeEventL" );
_LIT( KTestQueryTest13, "CAknTextQueryDialog::CheckIfEntryTextOk" );
_LIT( KTestQueryTest14, "CAknTextQueryDialog::SetDefaultInputMode" );
_LIT( KTestQueryTest15, "CAknTextQueryDialog::HandleQueryEditorSizeEventL" );
_LIT( KTestQueryTest16, "CAknTextQueryDialog::HandlePointerEventL" );
_LIT( KTestQueryTest17, "CAknQueryControl::SetImageL" );
_LIT( KTestQueryTest18, "CAknQueryControl::SetAnimationL" );
_LIT( KTestQueryTest19, "CAknQueryControl::CancelAnimation" );
_LIT( KTestQueryTest20, "CAknQueryControl::HandlePointerEventL" );
_LIT( KTestQueryTest21, "CAknQueryControl::SetNumberOfEditorLines" );
_LIT( KTestQueryTest22, "CAknQueryControl::HandleEdwinEventL" );
_LIT( KTestQueryTest23, "CAknQueryControl::HandleControlEventL" );
_LIT( KTestQueryTest24, "CAknTextQueryDialog::OkToExitL" );
_LIT( KTestQueryTest25, "CAknTextQueryDialog::DismissQueryL" );

_LIT( KNumberQueryTest1, "CAknNumberQueryDialog::NewL" );
_LIT( KNumberQueryTest2, "CAknNumberQueryDialog constructor" );
_LIT( KNumberQueryTest3, "CAknNumberQueryDialog::PreLayoutDynInitL" );
_LIT( KNumberQueryTest4, "CAknNumberQueryDialog::SetMinimumAndMaximum" );
_LIT( KNumberQueryTest5, "CAknNumberQueryDialog::HandlePointerEventL" );
_LIT( KNumberQueryTest6, "CAknNumberQueryDialog::OkToExitL" );

_LIT( KTimeQueryTest1, "CAknTimeQueryDialog::NewL" );
_LIT( KTimeQueryTest2, "CAknTimeQueryDialog constructor" );
_LIT( KTimeQueryTest3, "CAknTimeQueryDialog::PreLayoutDynInitL" );
_LIT( KTimeQueryTest4, "CAknTimeQueryDialog::SetMinimumAndMaximum" );
_LIT( KTimeQueryTest5, "CAknTimeQueryDialog::HandlePointerEventL" );
_LIT( KTimeQueryTest6, "CAknTimeQueryDialog::OkToExitL" );

_LIT( KDurationQueryTest1, "CAknDurationQueryDialog::NewL" );
_LIT( KDurationQueryTest2, "CAknDurationQueryDialog constructor" );
_LIT( KDurationQueryTest3, "CAknDurationQueryDialog::PreLayoutDynInitL" );
_LIT( KDurationQueryTest4, "CAknDurationQueryDialog::SetMinimumAndMaximum" );
_LIT( KDurationQueryTest5, "CAknDurationQueryDialog::HandlePointerEventL" );
_LIT( KDurationQueryTest6, "CAknDurationQueryDialog::OkToExitL" );

_LIT( KFloatingQueryTest1, "CAknFloatingPointQueryDialog::NewL" );
_LIT( KFloatingQueryTest2, "CAknFloatingPointQueryDialog constructor" );
_LIT( KFloatingQueryTest3, "CAknFloatingPointQueryDialog::PreLayoutDynInitL" );
_LIT( KFloatingQueryTest4, "CAknFloatingPointQueryDialog::SetMinimumAndMaximum" );
_LIT( KFloatingQueryTest5, "CAknFloatingPointQueryDialog::HandlePointerEventL" );
_LIT( KFloatingQueryTest6, "CAknFloatingPointQueryDialog::OkToExitL" );

_LIT( KMultiDataQueryTest1, "CAknMultiLineDataQueryDialog::NewL( TTime, TTime )" );
_LIT( KMultiDataQueryTest2, "CAknMultiLineDataQueryDialog::NewL( TDes, TDes )" );
_LIT( KMultiDataQueryTest3, "CAknMultiLineDataQueryDialog::NewL( TDes, TTime )" );
_LIT( KMultiDataQueryTest4, "CAknMultiLineDataQueryDialog::NewL( TDes, TInt )" );
_LIT( KMultiDataQueryTest5, "CAknMultiLineDataQueryDialog::NewL( TDes, TTimeIntervalSeconds )" );
_LIT( KMultiDataQueryTest6, "CAknMultiLineDataQueryDialog::NewL( TTime, TTimeIntervalSeconds )" );
_LIT( KMultiDataQueryTest7, "CAknMultiLineDataQueryDialog::NewL( TInt, TInt )" );
_LIT( KMultiDataQueryTest8, "CAknMultiLineDataQueryDialog constructor" );
_LIT( KMultiDataQueryTest9, "CAknMultiLineDataQueryDialog::PreLayoutDynInitL" );
_LIT( KMultiDataQueryTest10, "CAknMultiLineDataQueryDialog::SetPromptL" );
_LIT( KMultiDataQueryTest11, "CAknMultiLineDataQueryDialog::DoSetPromptL" );
_LIT( KMultiDataQueryTest12, "CAknMultiLineDataQueryDialog::SetMaxLengthOfFirstEditor" );
_LIT( KMultiDataQueryTest13, "CAknMultiLineDataQueryDialog::SetMaxLengthOfSecondEditor" );
_LIT( KMultiDataQueryTest14, "CAknMultiLineDataQueryDialog::HandleResourceChange" );
_LIT( KMultiDataQueryTest15, "CAknMultiLineDataQueryDialog::HandlePointerEventL" );
_LIT( KMultiDataQueryTest16, "CAknMultiLineDataQueryDialog::UpdateLeftSoftKeyL" );
_LIT( KMultiDataQueryTest17, "CAknMultiLineDataQueryDialog::FirstControl" );
_LIT( KMultiDataQueryTest18, "CAknMultiLineDataQueryDialog::SecondControl" );
_LIT( KMultiDataQueryTest19, "CAknMultilineQueryControl::HandlePointerEventL" );
_LIT( KMultiDataQueryTest20, "CAknMultiLineDataQueryDialog::QueryControl" );
_LIT( KMultiDataQueryTest21, "CAknMultiLineDataQueryDialog::QueryHeading" );
_LIT( KMultiDataQueryTest22, "CAknMultiLineDataQueryDialog::NeedToDismissQueryL" );
_LIT( KMultiDataQueryTest23, "CAknMultiLineDataQueryDialog::SecondPrompt" );
_LIT( KMultiDataQueryTest24, "CAknMultiLineDataQueryDialog::OkToExitL" );
_LIT( KMultiDataQueryTest25, "CAknExtMultilineQueryControl::HandlePointerEventL" );

_LIT( KIpQueryTest1, "CAknIpAddressQueryDialog::NewL" );
_LIT( KIpQueryTest2, "CAknIpAddressQueryDialog::SetMinimumAndMaximum" );
_LIT( KIpQueryTest3, "CAknIpAddressQueryDialog::ExecuteLD" );
_LIT( KIpQueryTest4, "CAknExtQueryControl constructor" );
_LIT( KIpQueryTest5, "CAknExtQueryControl::HandlePointerEventL" );
_LIT( KIpQueryTest6, "CAknExtQueryControl::SetMinimumAndMaximum( TInt, TInt )" );
_LIT( KIpQueryTest7, "CAknExtQueryControl::SetMinimumAndMaximum" );

_LIT( KFixedPointQueryTest1, "CAknFixedPointQueryDialog::NewL" );
_LIT( KFixedPointQueryTest2, "CAknFixedPointQueryDialog::SetMinimumAndMaximum" );
_LIT( KFixedPointQueryTest3, "CAknFixedPointQueryDialog::ExecuteLD" );

_LIT( KFirstPrompt, "Ip address" );
_LIT( KMultiIpQueryTest1, "CAknMultiLineIpQueryDialog::NewL" );
_LIT( KMultiIpQueryTest2, "CAknMultiLineIpQueryDialog::SetPromptL" );
_LIT( KMultiIpQueryTest3, "CAknMultiLineIpQueryDialog::SetMaxLengthOfFirstEditor" );
_LIT( KMultiIpQueryTest4, "CAknMultiLineIpQueryDialog::SetMaxLengthOfSecondEditor" );
_LIT( KMultiIpQueryTest5, "CAknMultiLineIpQueryDialog::ExecuteLD" );

_LIT( KQueryDlgText, "Query dialog text" );
_LIT( KQueryTest1, "CAknQueryDialog::NewL( TTone )" );
_LIT( KQueryTest2, "CAknQueryDialog::NewL( TDesC, TTone )" );
_LIT( KQueryTest3, "CAknQueryDialog::NewL( TInt, TTone )" );
_LIT( KQueryTest4, "CAknQueryDialog::NewL( TTime, TTone )" );
_LIT( KQueryTest5, "CAknQueryDialog::NewL( TTimeIntervalSeconds, TTone )" );
_LIT( KQueryTest6, "CAknQueryDialog::NewL( TReal, TTone )" );
_LIT( KQueryTest7, "CAknQueryDialog::NewL( TInetAddr, TTone )" );

_LIT( KAknDlgTest1, "CAknDialog constructor" );
_LIT( KAknDlgTest2, "CAknDialog::ExecuteLD" );
_LIT( KAknDlgTest3, "CAknDialog::DynInitMenuPaneL" );
_LIT( KAknDlgTest4, "CAknDialog::DisplayMenuL" );
_LIT( KAknDlgTest5, "CAknDialog::MenuShowing" );
_LIT( KAknDlgTest6, "CAknDialog::OkToExitL" );


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestQueryDialog* CBCTestQueryDialog::NewL( CBCTestQueryContainer* aContainer,
    CEikonEnv* aEnv )
    {
    CBCTestQueryDialog* self = new( ELeave ) CBCTestQueryDialog( 
        aContainer, aEnv );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestQueryDialog::CBCTestQueryDialog(  CBCTestQueryContainer* aContainer, 
    CEikonEnv* aEnv ): iContainer( aContainer ), iEnv( aEnv )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestQueryDialog::~CBCTestQueryDialog()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestQueryDialog::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestQueryDialog::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestQueryDialog::BuildScriptL()
    {    
    // outline03 - outline08
    for ( TInt i=0; i <= EBCTestCmdOutline08 - EBCTestCmdOutline03; i++ )
        {
        AddTestL( LeftCBA, Down, KeyOK, TEND );
        AddTestL( REP( Down, i ), KeyOK, TEND );
        }
    
    // outline09
    AddTestL( LeftCBA, Down, KeyOK, TEND );
    AddTestL( REP( Down, 6 ), KeyOK, TEND );
    AddTestL( REP( Key2, 10 ), REP( KeyBackspace, 10 ), TEND );
    AddTestL( Key1, Key2, Key3, LeftCBA, TEND );
    
    // outline10
    AddTestL( LeftCBA, Down, KeyOK, TEND );
    AddTestL( REP( Down, 7 ), KeyOK, TEND );
    AddTestL( REP( Key2, 3 ), REP( Key3, 3 ), Right, Key1, Key0, Right, 
        Key1, Key2, Key3, LeftCBA, TEND );
        
    // outline11
    AddTestL( LeftCBA, Down, KeyOK, TEND );
    AddTestL( REP( Down, 8 ), KeyOK, TEND );
    AddTestL( REP( Key2, 3 ), REP( Key3, 3 ), Right, Key1, Key0, Right, 
        Key1, Key2, Key3, TEND );
    AddTestL( Down, Up, Down, REP( Key2, 12 ), LeftCBA, TEND );
    
    // outline12
    AddTestL( LeftCBA, Down, KeyOK, TEND );
    AddTestL( REP( Down, 9 ), KeyOK, TEND );
    
    // outline13
    AddTestL( LeftCBA, Down, KeyOK, TEND );
    AddTestL( REP( Down, 10 ), KeyOK, LeftCBA, TEND );
    }
    
// ---------------------------------------------------------------------------
// CBCTestQueryDialog::RunL
// ---------------------------------------------------------------------------
//
void CBCTestQueryDialog::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline03 || aCmd > EBCTestCmdOutline13 )
        {
        return;
        }    
    switch ( aCmd )  
        {
        case EBCTestCmdOutline03:
            TestTextQueryDialogL();
            break;
        case EBCTestCmdOutline04:
            TestNumberQueryDialogL();
            break;
        case EBCTestCmdOutline05:
            TestTimeQueryDialogL();
            break;
        case EBCTestCmdOutline06:
            TestDurationQueryDialogL();
            break;
        case EBCTestCmdOutline07:
            TestFloatingPointQueryDialogL();
            break;
        case EBCTestCmdOutline08:
            TestMultilineDataQueryDialogL();
            break;
        case EBCTestCmdOutline09:
            TestFixedPointQueryDialogL();
            break;
        case EBCTestCmdOutline10:
            TestIpAddressQueryDialogL();
            break;
        case EBCTestCmdOutline11:
            TestMultiLineIpQueryDialogL();
            break;
        case EBCTestCmdOutline12:
            TestQueryDialogL();
            break;
        case EBCTestCmdOutline13:
            TestAknDialogL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// Test CAknTextQueryDialog
// ---------------------------------------------------------------------------
//
void CBCTestQueryDialog::TestTextQueryDialogL()
    {
    TBuf<100> dataText( KDataText );
    CAknTextQueryDialog* textDlg = CAknTextQueryDialog::NewL( dataText, 
        CAknQueryDialog::ENoTone );
    CleanupStack::PushL( textDlg );
    AssertNotNullL( textDlg, KTestQueryTest1 );
    CleanupStack::PopAndDestroy( textDlg );
    
    CBCTestTextQueryDialog* dlg = new( ELeave ) CBCTestTextQueryDialog( 
        dataText, CAknQueryDialog::EWarningTone );
    dlg->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_TEXT );
    AssertTrueL( ETrue, KTestQueryTest2 );
    
    dlg->RemoveEditorIndicator();
    AssertTrueL( ETrue, KTestQueryTest3 );
    
    dlg->SetEmergencyCallSupport( ETrue );
    AssertTrueL( ETrue, KTestQueryTest4 );
        
    dlg->SetPredictiveTextInputPermitted( ETrue );
    AssertTrueL( ETrue, KTestQueryTest5 );
    
    TPtrC prompt = dlg->Prompt();
    AssertTrueL( ETrue, KTestQueryTest6 );
    
    CAknPopupHeadingPane* headingPane = dlg->Heading();
    AssertTrueL( ETrue, KTestQueryTest7 );
    
    dlg->PreLayoutDynInitL();
    AssertTrueL( ETrue, KTestQueryTest8 );
    
    CAknQueryControl* ctrl = dlg->QueryControl();
    AssertTrueL( ETrue, KTestQueryTest9 );
        
    const TInt maxLength = 60;
    dlg->SetMaxLength( maxLength );
    AssertTrueL( ETrue, KTestQueryTest10 );
    
    TInt maxLen = dlg->MaxTextLength( ctrl, dataText, 10 );
    AssertTrueL( ETrue, KTestQueryTest11 );
    
    dlg->HandleQueryEditorSizeEventL( ctrl, 
        MAknQueryControlObserver::EQueryControltSizeChanging );
    AssertTrueL( ETrue, KTestQueryTest12 );
    
    TBool check = dlg->CheckIfEntryTextOk();
    AssertTrueL( ETrue, KTestQueryTest13 );
    
    dlg->SetDefaultInputMode( EAknEditorSecretAlphaInputMode );
    AssertTrueL( ETrue, KTestQueryTest14 );
    
    dlg->HandleQueryEditorSizeEventL( ctrl, 
        MAknQueryControlObserver::EQueryControltSizeChanging );
    dlg->HandleQueryEditorSizeEventL( ctrl, 
        MAknQueryControlObserver::EQueryControlEditorStateChanging );
    AssertTrueL( ETrue, KTestQueryTest15 );        
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton2Up;
    event.iModifiers = 0;
    TPoint eventPos(0, 30);
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    dlg->HandlePointerEventL( event );
    AssertTrueL( ETrue, KTestQueryTest16 );
        
    ctrl->SetImageL( AknIconUtils::AvkonIconFileName(), 
        EMbmAvkonQgn_indi_marked_add, 
        EMbmAvkonQgn_indi_marked_add_mask );
    AssertTrueL( ETrue, KTestQueryTest17 );
    
    ctrl->SetAnimationL( R_BCTESTQUERY_BMP_ANIMATION );
    AssertTrueL( ETrue, KTestQueryTest18 );
    
    ctrl->CancelAnimation();
    AssertTrueL( ETrue, KTestQueryTest19 );
    
    ctrl->HandlePointerEventL( event );
    AssertTrueL( ETrue, KTestQueryTest20 );
    
    ctrl->SetNumberOfEditorLines( 1 );
    AssertTrueL( ETrue, KTestQueryTest21 );
        
    ctrl->HandleEdwinEventL( NULL, MEikEdwinObserver::EEventTextUpdate );
    AssertTrueL( ETrue, KTestQueryTest22 );
    
    ctrl->HandleControlEventL( ctrl, 
        MCoeControlObserver::EEventStateChanged );
    AssertTrueL( ETrue, KTestQueryTest23 );
        
    dlg->OkToExitL( EAknSoftkeyOk );
    AssertTrueL( ETrue, KTestQueryTest24 );
    
    dlg->DismissQueryL();
    AssertTrueL( ETrue, KTestQueryTest25 );
    
    CleanupStack::Pop( dlg );       
    } 

// ---------------------------------------------------------------------------
// Test CAknNumberQueryDialog
// ---------------------------------------------------------------------------
//
void CBCTestQueryDialog::TestNumberQueryDialogL()
    {
    TInt number = 10;
    CAknNumberQueryDialog* numDlg = CAknNumberQueryDialog::NewL( number, 
        CAknQueryDialog::ENoTone );
    CleanupStack::PushL( numDlg );
    AssertNotNullL( numDlg, KNumberQueryTest1 );
    CleanupStack::PopAndDestroy( numDlg );
    
    CBCTestNumberQueryDialog* dlg = new( ELeave ) CBCTestNumberQueryDialog(
        number, CAknQueryDialog::EConfirmationTone );
    dlg->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_NUMBER );
    AssertTrueL( ETrue, KNumberQueryTest2 );
    
    dlg->PreLayoutDynInitL();
    AssertTrueL( ETrue, KNumberQueryTest3 );
    
    dlg->SetMinimumAndMaximum( 0, 100 );
    AssertTrueL( ETrue, KNumberQueryTest4 );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos(0, 30);
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    dlg->HandlePointerEventL( event );
    AssertTrueL( ETrue, KNumberQueryTest5 );
    
    dlg->OkToExitL( EAknSoftkeyOk );
    AssertTrueL( ETrue, KNumberQueryTest6 );

    CleanupStack::PopAndDestroy( dlg );
    }
    
// ---------------------------------------------------------------------------
// Test CAknTimeQueryDialog
// ---------------------------------------------------------------------------
//
void CBCTestQueryDialog::TestTimeQueryDialogL()
    {
    TTime time;
    time.HomeTime();
    CAknTimeQueryDialog* timeDlg = CAknTimeQueryDialog::NewL( time, 
        CAknQueryDialog::ENoTone );
    CleanupStack::PushL( timeDlg );
    AssertNotNullL( timeDlg, KTimeQueryTest1 );
    CleanupStack::PopAndDestroy( timeDlg );
    
    CBCTestTimeQueryDialog* dlg = new( ELeave ) CBCTestTimeQueryDialog(
        time, CAknQueryDialog::EConfirmationTone );
    dlg->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_TIME );
    AssertTrueL( ETrue, KTimeQueryTest2 );
    
    dlg->PreLayoutDynInitL();
    AssertTrueL( ETrue, KTimeQueryTest3 );
    
    TTime maxTime;
    TTimeIntervalYears years( 3 );
    maxTime = time + years;
    dlg->SetMinimumAndMaximum( time, maxTime );
    AssertTrueL( ETrue, KTimeQueryTest4 );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos(0, 30);
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    dlg->HandlePointerEventL( event );
    AssertTrueL( ETrue, KTimeQueryTest5 );
    
    dlg->OkToExitL( EAknSoftkeyOk );
    AssertTrueL( ETrue, KTimeQueryTest6 );
    
    CleanupStack::PopAndDestroy( dlg );
    }

// ---------------------------------------------------------------------------
// Test CAknDurationQueryDialog
// ---------------------------------------------------------------------------
//
void CBCTestQueryDialog::TestDurationQueryDialogL()
    {
    TTimeIntervalSeconds time( 3000 );
    CAknDurationQueryDialog* durationDlg = CAknDurationQueryDialog::NewL(
        time, CAknQueryDialog::ENoTone );
    CleanupStack::PushL( durationDlg );
    AssertNotNullL( durationDlg, KDurationQueryTest1 );
    CleanupStack::PopAndDestroy( durationDlg );
        
    CBCTestDurationQueryDialog* dlg = new( ELeave ) 
        CBCTestDurationQueryDialog( time, 
            CAknQueryDialog::EConfirmationTone );
    dlg->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_DURATION );
    AssertTrueL( ETrue, KDurationQueryTest2 );
    
    dlg->PreLayoutDynInitL();
    AssertTrueL( ETrue, KDurationQueryTest3 );
    
    TTimeIntervalSeconds maxTime( 30000 );
    dlg->SetMinimumAndMaximum( time, maxTime );
    AssertTrueL( ETrue, KDurationQueryTest4 );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos(0, 30);
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    dlg->HandlePointerEventL( event );
    AssertTrueL( ETrue, KDurationQueryTest5 );
    
    dlg->OkToExitL( EAknSoftkeyOk );  
    AssertTrueL( ETrue, KDurationQueryTest6 );
    
    CleanupStack::PopAndDestroy( dlg );
    }

// ---------------------------------------------------------------------------
// Test CAknFloatingPointQueryDialog
// ---------------------------------------------------------------------------
//
void CBCTestQueryDialog::TestFloatingPointQueryDialogL()
    {
    TReal number = 1005.74;
    CAknFloatingPointQueryDialog* floatDlg = CAknFloatingPointQueryDialog::NewL(
        number, 
        CAknQueryDialog::ENoTone );
    CleanupStack::PushL( floatDlg );
    AssertNotNullL( floatDlg, KFloatingQueryTest1 );
    CleanupStack::PopAndDestroy( floatDlg );
    
    CBCTestFloatingPointQueryDialog* dlg = new( ELeave ) 
        CBCTestFloatingPointQueryDialog(
            number, CAknQueryDialog::EConfirmationTone );
    dlg->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_NUMBER );
    AssertTrueL( ETrue, KFloatingQueryTest2 );
    
    dlg->PreLayoutDynInitL();
    AssertTrueL( ETrue, KFloatingQueryTest3 );
    
    TReal maxNumber = 20000.987;
    dlg->SetMinimumAndMaximum( number, maxNumber );
    AssertTrueL( ETrue, KFloatingQueryTest4 );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos(0, 30);
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    dlg->HandlePointerEventL( event );
    AssertTrueL( ETrue, KFloatingQueryTest5 );
    
    dlg->OkToExitL( EAknSoftkeyOk );
    AssertTrueL( ETrue, KFloatingQueryTest6 );

    CleanupStack::PopAndDestroy( dlg );
    }
    
// ---------------------------------------------------------------------------
// Test CAknMultiLineDataQueryDialog
// ---------------------------------------------------------------------------
//    
void CBCTestQueryDialog::TestMultilineDataQueryDialogL()
    {
    TTime time;
    time.HomeTime();
    TTimeIntervalYears years( 2 );
    TTime time2;
    time2 = time + years;
    CAknMultiLineDataQueryDialog* mulDlg = CAknMultiLineDataQueryDialog::
        NewL( time, time2 );
    CleanupStack::PushL( mulDlg );
    AssertNotNullL( mulDlg, KMultiDataQueryTest1 );
    CleanupStack::PopAndDestroy( mulDlg );
    mulDlg = NULL;
        
    _LIT( KMulDlgText1, "Test text 1" );
    _LIT( KMulDlgText2, "Test text 2" );
    TBuf<KBufLength> buf1( KMulDlgText1 );
    TBuf<KBufLength> buf2( KMulDlgText2 );
    mulDlg = CAknMultiLineDataQueryDialog::NewL( buf1, buf2 );
    CleanupStack::PushL( mulDlg );
    AssertNotNullL( mulDlg, KMultiDataQueryTest2 );
    CleanupStack::PopAndDestroy( mulDlg );
    mulDlg = NULL;
    
    mulDlg = CAknMultiLineDataQueryDialog::NewL( buf1, time2 );
    CleanupStack::PushL( mulDlg );
    AssertNotNullL( mulDlg, KMultiDataQueryTest3 );
    CleanupStack::PopAndDestroy( mulDlg );
    mulDlg = NULL;
    
    TInt number = 5;
    mulDlg = CAknMultiLineDataQueryDialog::NewL( buf1, number );
    CleanupStack::PushL( mulDlg );
    AssertNotNullL( mulDlg, KMultiDataQueryTest4 );
    CleanupStack::PopAndDestroy( mulDlg );
    mulDlg = NULL;
    
    TTimeIntervalSeconds seconds( 100 );
    mulDlg = CAknMultiLineDataQueryDialog::NewL( buf1, seconds );
    CleanupStack::PushL( mulDlg );
    AssertNotNullL( mulDlg, KMultiDataQueryTest5 );
    CleanupStack::PopAndDestroy( mulDlg );
    mulDlg = NULL;
    
    mulDlg = CAknMultiLineDataQueryDialog::NewL( time, seconds );
    CleanupStack::PushL( mulDlg );
    AssertNotNullL( mulDlg, KMultiDataQueryTest6 );
    CleanupStack::PopAndDestroy( mulDlg );
    mulDlg = NULL;
    
    TInt number2 = 10;
    mulDlg = CAknMultiLineDataQueryDialog::NewL( number, number2 );
    CleanupStack::PushL( mulDlg );
    AssertNotNullL( mulDlg, KMultiDataQueryTest7 );
    CleanupStack::PopAndDestroy( mulDlg );
    mulDlg = NULL;
    
    CBCTestMultiLineDataQueryDialog* dlg = new( ELeave )
        CBCTestMultiLineDataQueryDialog( CAknQueryDialog::EConfirmationTone );
    dlg->PrepareLC( R_BCTESTQUERY_MULTI_LINE_NUMBER_AND_NUMBER ); 
    AssertTrueL( ETrue, KMultiDataQueryTest8 );
    
    dlg->PreLayoutDynInitL();
    AssertTrueL( ETrue, KMultiDataQueryTest9 );
    
    dlg->SetPromptL( KMulDlgText1, KMulDlgText2 );
    AssertTrueL( ETrue, KMultiDataQueryTest10 );
    
    dlg->DoSetPromptL();
    AssertTrueL( ETrue, KMultiDataQueryTest11 );
    
    TInt maxLength = 100;
    dlg->SetMaxLengthOfFirstEditor( maxLength );
    AssertTrueL( ETrue, KMultiDataQueryTest12 );
    
    dlg->SetMaxLengthOfSecondEditor( maxLength );
    AssertTrueL( ETrue, KMultiDataQueryTest13 );
    
    dlg->HandleResourceChange( KAknsMessageSkinChange );
    AssertTrueL( ETrue, KMultiDataQueryTest14 );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos(0, 30);
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    dlg->HandlePointerEventL( event );
    AssertTrueL( ETrue, KMultiDataQueryTest15 );
    
    dlg->UpdateLeftSoftKeyL();
    AssertTrueL( ETrue, KMultiDataQueryTest16 );
    
    CAknMultilineQueryControl* firstControl = dlg->FirstControl();
    AssertTrueL( ETrue, KMultiDataQueryTest17 );
    
    CAknMultilineQueryControl* secondControl = dlg->SecondControl();
    AssertTrueL( ETrue, KMultiDataQueryTest18 );
    
    firstControl->HandlePointerEventL( event );
    AssertTrueL( ETrue, KMultiDataQueryTest19 );
    
    CAknQueryControl* queryControl = dlg->QueryControl();
    AssertTrueL( ETrue, KMultiDataQueryTest20 );
    
    CAknPopupHeadingPane* headingPane = dlg->QueryHeading();
    AssertTrueL( ETrue, KMultiDataQueryTest21 );
    
    TKeyEvent eventHash = { 0, EStdKeyHash, 0, 0 };
    TBool dismiss = dlg->NeedToDismissQueryL( eventHash );
    AssertTrueL( ETrue, KMultiDataQueryTest22 );
    
    TPtrC secondPrompt = dlg->SecondPrompt();
    AssertTrueL( ETrue, KMultiDataQueryTest23 );    
    
    dlg->OkToExitL( EAknSoftkeyOk );
    AssertTrueL( ETrue, KMultiDataQueryTest24 );
    
    CleanupStack::PopAndDestroy( dlg );
    
    CAknExtMultilineQueryControl* extCtrl = new( ELeave )
        CAknExtMultilineQueryControl();
    CleanupStack::PushL( extCtrl );
    extCtrl->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_BCTESTQUERY_MULTI_CONTROL );
    extCtrl->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // reader
    
    extCtrl->HandlePointerEventL( event );
    AssertTrueL( ETrue, KMultiDataQueryTest25 );
    
    CleanupStack::PopAndDestroy( extCtrl );
    }
    
// ---------------------------------------------------------------------------
// Test CAknIpAddressQueryDialog
// ---------------------------------------------------------------------------
//
void CBCTestQueryDialog::TestIpAddressQueryDialogL()
    {
    TInetAddr addr;    
    TBuf<KBufLength> textData;

    CAknIpAddressQueryDialog* dlg = NULL;
    TInetAddr minAddr( 0, 0 );
    TUint32 maxAddrValue = 0xffffffff;
    TInetAddr maxAddr( maxAddrValue, 65535 );    
    dlg = CAknIpAddressQueryDialog::NewL( addr, 
        CAknIpAddressQueryDialog::ENoTone );
    CleanupStack::PushL( dlg );
    AssertNotNullL( dlg, KIpQueryTest1 );
    
    dlg->SetMinimumAndMaximum( minAddr, maxAddr );
    AssertTrueL( ETrue, KIpQueryTest2 );
    
    CleanupStack::Pop( dlg );
    dlg->ExecuteLD( R_BCTESTQUERY_IP_ADDRESS );
    AssertTrueL( ETrue, KIpQueryTest3 );
    
    CAknExtQueryControl* extCtrl = new( ELeave ) CAknExtQueryControl();
    CleanupStack::PushL( extCtrl );
    AssertNotNullL( extCtrl, KIpQueryTest4 );
    
    extCtrl->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_BCTESTQUERY_EXTCONTROL );
    extCtrl->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // reader
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos(0, 30);
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    extCtrl->HandlePointerEventL( event );
    AssertTrueL( ETrue, KIpQueryTest5 );
    
    TInt minValue = 0;
    TInt maxValue = 10000;
    extCtrl->SetMinimumAndMaximum( minValue, maxValue );
    AssertTrueL( ETrue, KIpQueryTest6 );
    
    extCtrl->SetMinimumAndMaximum( minAddr, maxAddr );
    AssertTrueL( ETrue, KIpQueryTest7 );
    
    CleanupStack::PopAndDestroy( extCtrl ); 
    }
    
// ---------------------------------------------------------------------------
// Test CAknFixedPointQueryDialog
// ---------------------------------------------------------------------------
//
void CBCTestQueryDialog::TestFixedPointQueryDialogL()
    {
    TInt initial = 5;
    TBuf<10> textData;

    CAknFixedPointQueryDialog* dlg = NULL;
    TInt minValue = 0;
    TInt maxValue = 100000;    
    dlg = CAknFixedPointQueryDialog::NewL( initial, 
        CAknFixedPointQueryDialog::ENoTone );
    CleanupStack::PushL( dlg );
    AssertNotNullL( dlg, KFixedPointQueryTest1 );
    
    dlg->SetMinimumAndMaximum( minValue, maxValue );
    AssertTrueL( ETrue, KFixedPointQueryTest2 );
    
    CleanupStack::Pop( dlg );
    dlg->ExecuteLD( R_BCTESTQUERY_FIXED_POINT );
    AssertTrueL( ETrue, KFixedPointQueryTest3 );
    }

// ---------------------------------------------------------------------------
// Test CAknMultiLineIpQueryDialog
// ---------------------------------------------------------------------------
//
void CBCTestQueryDialog::TestMultiLineIpQueryDialogL()
    {
    TInetAddr addr1;
    TInetAddr addr2;
    TBuf<KBufLength> textData;
    TBuf<KBufLength> tmp;

    CAknMultiLineIpQueryDialog* dlg;
    dlg = CAknMultiLineIpQueryDialog::NewL( addr1, addr2, 
        CAknMultiLineIpQueryDialog::ENoTone );
    CleanupStack::PushL( dlg );
    AssertNotNullL( dlg, KMultiIpQueryTest1 );
    
    dlg->SetPromptL( KFirstPrompt, KFirstPrompt );
    AssertTrueL( ETrue, KMultiIpQueryTest2 );
    
    const TInt KMaxLength = 64;
    dlg->SetMaxLengthOfFirstEditor( KMaxLength );
    AssertTrueL( ETrue, KMultiIpQueryTest3 );
    
    dlg->SetMaxLengthOfSecondEditor( KMaxLength );
    AssertTrueL( ETrue, KMultiIpQueryTest4 );
    
    CleanupStack::Pop( dlg );
    dlg->ExecuteLD( R_BCTESTQUERY_MULTI_LINE_IP_ADDRESS );
    AssertTrueL( ETrue, KMultiIpQueryTest5 );
    }
    
// ---------------------------------------------------------------------------
// Test CAknQueryDialog
// ---------------------------------------------------------------------------
//
void CBCTestQueryDialog::TestQueryDialogL()
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( 
        CAknQueryDialog::EConfirmationTone );
    CleanupStack::PushL( dlg );
    AssertNotNullL( dlg, KQueryTest1 );
    CleanupStack::PopAndDestroy( dlg );
    dlg = NULL;
        
    TBuf<KBufLength> text( KQueryDlgText );
    dlg = CAknQueryDialog::NewL( text, CAknQueryDialog::EConfirmationTone );
    CleanupStack::PushL( dlg );
    AssertNotNullL( dlg, KQueryTest2 );
    CleanupStack::PopAndDestroy( dlg );
    dlg = NULL;
    
    TInt number = 10;
    dlg = CAknQueryDialog::NewL( number, CAknQueryDialog::EConfirmationTone );
    CleanupStack::PushL( dlg );
    AssertNotNullL( dlg, KQueryTest3 );
    CleanupStack::PopAndDestroy( dlg );
    dlg = NULL;
    
    TTime time;
    time.HomeTime();
    dlg = CAknQueryDialog::NewL( time, CAknQueryDialog::EConfirmationTone );
    CleanupStack::PushL( dlg );
    AssertNotNullL( dlg, KQueryTest4 );
    CleanupStack::PopAndDestroy( dlg );
    dlg = NULL;
    
    TTimeIntervalSeconds seconds( 1000 );
    dlg = CAknQueryDialog::NewL( seconds, CAknQueryDialog::EConfirmationTone );
    CleanupStack::PushL( dlg );
    AssertNotNullL( dlg, KQueryTest5 );
    CleanupStack::PopAndDestroy( dlg );
    dlg = NULL;
    
    TReal real( 100.56 );
    dlg = CAknQueryDialog::NewL( real, CAknQueryDialog::EConfirmationTone );
    CleanupStack::PushL( dlg );
    AssertNotNullL( dlg, KQueryTest6 );
    CleanupStack::PopAndDestroy( dlg );
    dlg = NULL;
    
    TInetAddr addr( 23 );
    dlg = CAknQueryDialog::NewL( addr, CAknQueryDialog::EConfirmationTone );
    CleanupStack::PushL( dlg );
    AssertNotNullL( dlg, KQueryTest7 );
    CleanupStack::PopAndDestroy( dlg );
    dlg = NULL;
    }
    
// ---------------------------------------------------------------------------
// Test CAknDialog
// ---------------------------------------------------------------------------
//
void CBCTestQueryDialog::TestAknDialogL()
    {
    CBCTestAknDialog* dlg = new( ELeave ) CBCTestAknDialog();    
    dlg->ExecuteLD( R_AVKON_DIALOG_QUERY_VALUE_NUMBER );
    AssertTrueL( ETrue, KAknDlgTest1 );
    AssertTrueL( ETrue, KAknDlgTest2 );
    
    dlg = new( ELeave ) CBCTestAknDialog();
    dlg->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_NUMBER );
    
    CEikMenuPane* menuPane = new( ELeave ) CEikMenuPane( dlg );
    CleanupStack::PushL( menuPane );    
    dlg->DynInitMenuPaneL( R_BCTESTQUERY_LISTQUERY_MENU, menuPane );    
    AssertTrueL( ETrue, KAknDlgTest3 );
    
    dlg->DisplayMenuL();
    AssertTrueL( ETrue, KAknDlgTest4 );
    
    TBool show = dlg->MenuShowing();
    AssertTrueL( ETrue, KAknDlgTest5 );
    
    dlg->OkToExitL( EAknSoftkeyOk );
    AssertTrueL( ETrue, KAknDlgTest6 );
        
    CleanupStack::PopAndDestroy( menuPane );
    CleanupStack::PopAndDestroy( dlg );
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CBCTestTextQueryDialog::CBCTestTextQueryDialog( TDes& aDataText, 
    const TTone& aTone ) : CAknTextQueryDialog( aDataText, aTone )
    {    
    }
    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CBCTestNumberQueryDialog::CBCTestNumberQueryDialog( TInt& aNumber, 
    const TTone& aTone ) : CAknNumberQueryDialog( aNumber, aTone )
    {    
    }
    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CBCTestTimeQueryDialog::CBCTestTimeQueryDialog( TTime& aTime, 
    const TTone& aTone ) : CAknTimeQueryDialog( aTime, aTone )
    {    
    }
    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CBCTestDurationQueryDialog::CBCTestDurationQueryDialog( 
    TTimeIntervalSeconds& aTime, const TTone& aTone ) 
    : CAknDurationQueryDialog( aTime, aTone )
    {    
    }
    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CBCTestFloatingPointQueryDialog::CBCTestFloatingPointQueryDialog( 
    TReal& aNumber, const TTone& aTone ) 
    : CAknFloatingPointQueryDialog( aNumber, aTone )
    {    
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//    
CBCTestMultiLineDataQueryDialog::CBCTestMultiLineDataQueryDialog( 
    const TTone& aTone ) : CAknMultiLineDataQueryDialog( aTone )
    {    
    }
