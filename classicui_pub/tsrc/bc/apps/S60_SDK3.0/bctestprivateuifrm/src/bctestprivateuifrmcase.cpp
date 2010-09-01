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
#include <coecntrl.h>
#include <eikcapc.h>
#include <eikdpage.h>
#include <barsread.h>
#include <s32file.h>
#include <bctestprivateuifrm.rsg>

#include "bctestPrivateUIFrmcase.h"
#include "bctestPrivateUIFrmcontainer.h"
#include "bctestPrivateUIFrm.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestPrivateUIFrmCase* CBCTestPrivateUIFrmCase::NewL(
    CBCTestPrivateUIFrmContainer* aContainer )
    {
    CBCTestPrivateUIFrmCase* self = new( ELeave ) CBCTestPrivateUIFrmCase(
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
CBCTestPrivateUIFrmCase::CBCTestPrivateUIFrmCase(
    CBCTestPrivateUIFrmContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestPrivateUIFrmCase::~CBCTestPrivateUIFrmCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestPrivateUIFrmCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestPrivateUIFrmCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestPrivateUIFrmCase::BuildScriptL()
    {
    // Add script as your need.
	AddTestL( DELAY(1), TEND);
    AddTestL( LeftCBA, KeyOK, TEND );
    }

// ---------------------------------------------------------------------------
// CBCTestPrivateUIFrmCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestPrivateUIFrmCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline1 )
        {
        return;
        }
    // Call release before prepare to let container has time to draw the
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            TestFunctionL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestPrivateUIFrmCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestPrivateUIFrmCase::PrepareCaseL( TInt aCmd )
    {
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            // Here is a simple demo. You should create your control
            // instead of this.
            iControl = new( ELeave ) CCoeControl();
            iControl->SetContainerWindowL( *iContainer );
            iControl->MakeVisible( ETrue );
            break;
        default:
            break;
        }
    // Pass the owner of iControl to iContainer.
    iContainer->SetControl( iControl );
    }

// ---------------------------------------------------------------------------
// CBCTestPrivateUIFrmCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//
void CBCTestPrivateUIFrmCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestPrivateUIFrmCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//
void CBCTestPrivateUIFrmCase::TestFunctionL()
    {
    // Test some API here
    TestAlertL();
    TestBtpanL();
    TestProtectedBtpanL();
    TestDpageL();
    TestHfdlgL();
    TestHkeycL();
    }
  
// ---------------------------------------------------------------------------
// CBCTestDocAndInitCase::TestDocument2  (Test class CEikAlert)
// ---------------------------------------------------------------------------
// 
void CBCTestPrivateUIFrmCase::TestAlertL()
    {
    }
  
// ---------------------------------------------------------------------------
// CBCTestDocAndInitCase::TestDpageL  (Test class CEikDialogPage)
// ---------------------------------------------------------------------------
// 
void CBCTestPrivateUIFrmCase::TestDpageL()
    {
    CEikCaptionedControl *cControl = new ( ELeave ) CEikCaptionedControl();
    CleanupStack::PushL( cControl );
    const CEikDialogPage *iDPage = cControl->DialogPage();
//     iDPage->SetFormLayout(ESingle);
//     iDPage->FormLayout();
    CleanupStack::PopAndDestroy( cControl );
    }
  
// ---------------------------------------------------------------------------
// CBCTestDocAndInitCase::TestHfdlgL  (Test class CEikDebugKeys & CEikDebugWin)
// ---------------------------------------------------------------------------
// 
void CBCTestPrivateUIFrmCase::TestHfdlgL()
    {
    }
  
// ---------------------------------------------------------------------------
// CBCTestDocAndInitCase::TestBtpanL  (Test class CEikButtonPanel)
// ---------------------------------------------------------------------------
// 
void CBCTestPrivateUIFrmCase::TestBtpanL()
    {
	// construct from resource
	/////////////////////////////////////////////////////////////////
	CEikButtonPanel * panel = new ( ELeave )CEikButtonPanel();
	CleanupStack::PushL( panel );

	TResourceReader panelReader;
	CEikonEnv::Static()->CreateResourceReaderLC( panelReader, R_BCTEST_BUTTON_PANEL );
	panel->ConstructFromResourceL(panelReader);

	CleanupStack::PopAndDestroy( 2 );    //reader, panel;

	// construct manually
	/////////////////////////////////////////////////////////////////
    CEikButtonPanel * Panel = new ( ELeave )CEikButtonPanel();
	CleanupStack::PushL( Panel );
    _LIT( KCEikButtonPanel, "CEikButtonPanel::CEikButtonPanel() invoked" );
    AssertNotNullL( Panel, KCEikButtonPanel );
    
    Panel->ConstructL();
    _LIT( KConstructL, "CEikButtonPanel::ConstructL() invoked" );
    AssertTrueL( ETrue, KConstructL );

    TInt id = Panel->ButtonId( iContainer );
    _LIT( KButtonId , "CEikButtonPanel::ButtonId(CCoeControl*) invoked" );
    AssertIntL( id, id, KButtonId );

    Panel->ButtonById( id );
    _LIT( KButtonById , "CEikButtonPanel::ButtonById(TInt) invoked" );
    AssertTrueL( ETrue, KButtonById );

    Panel->ButtonForKey( 1, id );
    _LIT( KButtonForKey,
    "CEikButtonPanel::ButtonForKey(TInt ,TInt& ) invoked" );
    AssertTrueL( ETrue, KButtonForKey );

    Panel->LabeledButtonById( id );
    _LIT( KLabeledButtonById,
    "CEikButtonPanel::LabeledButtonById(TInt) invoked" );
    AssertTrueL( ETrue, KLabeledButtonById );

    CArrayFix<TCoeColorUse>* colorlist =
                             new ( ELeave ) CArrayFixFlat<TCoeColorUse>( 1 );
    CleanupStack::PushL( colorlist );
    Panel->GetColorUseListL( *colorlist );
    CleanupStack::Pop( colorlist );
    _LIT( KGetColorUseListL,
    "CEikButtonPanel::GetColorUseListL(CArrayFix<TCoeColorUse>) invoked" );
    AssertTrueL( ETrue, KGetColorUseListL );
    delete colorlist;

    CEikLabeledButton* labeledButton = new( ELeave ) CEikLabeledButton();
    CleanupStack::PushL( labeledButton );
    TResourceReader reader;
	CEikonEnv::Static()->CreateResourceReaderLC( reader, 
	                                             R_BCTESTPRIVATEUI_LBBUT );
    labeledButton->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); //reader 
	CleanupStack::Pop( labeledButton );
    _LIT( KConstructFromResourceL,
		"CEikButtonPanel::ConstructFromResourceL(TResourceReader&) invoked" );
    AssertTrueL( ETrue, KConstructFromResourceL );
    	
    //can not be zero, becuase it used Groups[aRow-1]
	Panel->AddButtonL( labeledButton, EBCTestPrivateUIBtn1, 1);	
    _LIT( KAddButtonL,
    "CEikButtonPanel::AddButtonL(CEikLabeledButton* ,TInt ,TInt) invoked" );
    AssertTrueL( ETrue, KAddButtonL );
    
    //should be: MCoeControlObserver::EEventStateChanged; but failed
	Panel->HandleControlEventL( labeledButton, 
		MCoeControlObserver::EEventRequestCancel);	
    _LIT( KHandleControlEventL,
    "CEikButtonPanel::HandleControlEventL(CCoeControl*,TCoeEvent) invoked" );
    AssertTrueL( ETrue, KHandleControlEventL );

    TPointerEvent PointerEvent;
    Panel->HandlePointerEventL( PointerEvent );
    _LIT( KHandlePointerEventL,
    "CEikButtonPanel::HandlePointerEventL(TPointerEvent) invoked" );
    AssertTrueL( ETrue, KHandlePointerEventL );

    Panel->HandleResourceChange( 10 );
    _LIT( KHandleResourceChange ,
    "CEikButtonPanel::HandleResourceChange(TInt) invoked" );
    AssertTrueL( ETrue, KHandleResourceChange );

    Panel->MakeButtonVisible( id, ETrue);
    _LIT( KMakeButtonVisible,
    "CEikButtonPanel::MakeButtonVisible(TInt,TBool) invoked" );
    AssertTrueL( ETrue, KMakeButtonVisible );

    Panel->MinimumSize();
    _LIT( KMinimumSize, "CEikButtonPanel::MinimumSize() invoked" );
    AssertTrueL( ETrue, KMinimumSize );

    TKeyEvent KeyEvent;
    TKeyResponse keyResponse = Panel->OfferKeyEventL( KeyEvent, EEventKey );
    _LIT( KOfferKeyEventL,
    "CEikButtonPanel::OfferKeyEventL(TKeyEvent,TEventCode) invoked" );
    AssertIntL( EKeyWasNotConsumed, keyResponse, KOfferKeyEventL );

    Panel->ResetMinimumSize();
    _LIT( KResetMinimumSize, "CEikButtonPanel::ResetMinimumSize() invoked" );
    AssertTrueL( ETrue, KResetMinimumSize );

    CBCTestObserver* CommandObserver = new ( ELeave )CBCTestObserver;
    CleanupStack::PushL( CommandObserver );
    Panel->SetCommandObserver( CommandObserver );
    _LIT( KSetCommandObserver,
    "CEikButtonPanel::SetCommandObserver(MEikCommandObserver* ) invoked" );
    AssertTrueL( ETrue, KSetCommandObserver );
    CleanupStack::PopAndDestroy( CommandObserver );

    Panel->SetHorizontal();
    _LIT( KSetHorizontal, "CEikButtonPanel::SetHorizontal() invoked" );
    AssertTrueL( ETrue, KSetHorizontal );

    Panel->SetMinButtonWidth( 10 );
    _LIT( KSetMinButtonWidth,
    "CEikButtonPanel::SetMinButtonWidth() invoked" );
    AssertTrueL( ETrue, KSetMinButtonWidth );

    CleanupStack::PopAndDestroy( Panel );    //delete Panel;
    _LIT( KUCEikButtonPanel, "CEikButtonPanel::~CEikButtonPanel invoked" );
    AssertTrueL( ETrue, KUCEikButtonPanel );

    }
  
// ---------------------------------------------------------------------------
// CBCTestDocAndInitCase::TestBtpanL  (Test class CEikButtonPanel)
// ---------------------------------------------------------------------------
// 
void CBCTestPrivateUIFrmCase::TestProtectedBtpanL()
    {
    CSonEikButtonPanel * subPanel = new (ELeave) CSonEikButtonPanel;
    CleanupStack::PushL(subPanel);
    _LIT( KPanelFileName, "C:\\BCTestLog\\Panel.txt" );

    RFs& fs = CEikonEnv::Static()->FsSession();
    RFile File1;
    if ( File1.Open( fs, KPanelFileName, EFileWrite | EFileShareAny ) 
                                                       != KErrNone ){
        File1.Create( fs, KPanelFileName, EFileWrite | EFileShareAny );
    }
    File1.Close();
    RFileWriteStream wStream;
    User::LeaveIfError( wStream.Replace( fs, KPanelFileName, EFileWrite ));
    wStream.PushL();
    subPanel->TestBP_WriteInternalStateL( wStream );
    wStream.Pop();
    wStream.Release();
    _LIT( KWriteInternalStateL, 
    "CEikButtonPanel::WriteInternalStateL invoked" );
    AssertTrueL( ETrue, KWriteInternalStateL );
    CleanupStack::PopAndDestroy( subPanel );    
    
    }
  
// ---------------------------------------------------------------------------
// CBCTestDocAndInitCase::TestBtpanL  
// (Test class CEikButtonPanel protect function)
// ---------------------------------------------------------------------------
// 
void CSonEikButtonPanel::TestBP_WriteInternalStateL( RWriteStream&
                                                    aWriteStream )
    {
        CEikButtonPanel::WriteInternalStateL( aWriteStream );
    }
  
// ---------------------------------------------------------------------------
// CBCTestDocAndInitCase::TestKC_WriteInternalStateL  
// (Test class CEikHotKeyControl protect function)
// ---------------------------------------------------------------------------
// 
void CSonEikHotKeyControl::TestKC_WriteInternalStateL( RWriteStream&
                                                       aWriteStream )
    {
        WriteInternalStateL( aWriteStream );
    }
  
// ---------------------------------------------------------------------------
// CBCTestPrivateUIFrmCase::TestHkeycL  (Test class CEikHotKeyControl)
// ---------------------------------------------------------------------------
// 
void CBCTestPrivateUIFrmCase::TestHkeycL()
    {
    }
 
// ---------------------------------------------------------------------------
// CBCTestObserver::ProcessCommandL  (from MAknServerAppExitObserver)
// ---------------------------------------------------------------------------
// 
void CBCTestObserver::ProcessCommandL(TInt /*aCommandId*/)
    {
    }
