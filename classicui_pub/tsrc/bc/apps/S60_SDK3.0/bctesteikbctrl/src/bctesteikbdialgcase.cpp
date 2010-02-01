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
#include <eikdialg.h>
#include <bctesteikbctrl.rsg>
#include <eiklabel.h>
#include <avkon.rsg>
#include <eikenv.h>
#include <eikmfne.h>
#include <s32mem.h>
#include <eikcapc.h>
#include <s32file.h>

#include "bctesteikbdialgcase.h"
#include "bctesteikbctrlcontainer.h"
#include "bctesteikbctrl.hrh"
#include "avkon.hrh"
#include "bctestmiscellcase.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTesteikbdialgCase* CBCTesteikbdialgCase::NewL( 
    CBCTesteikbctrlContainer* aContainer )
    {
    CBCTesteikbdialgCase* self = new( ELeave ) CBCTesteikbdialgCase( 
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
CBCTesteikbdialgCase::CBCTesteikbdialgCase( 
    CBCTesteikbctrlContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTesteikbdialgCase::~CBCTesteikbdialgCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTesteikbdialgCase::ConstructL()
    {    
    BuildScriptL();   
    }
    
// ---------------------------------------------------------------------------
// CBCTesteikbdialgCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTesteikbdialgCase::BuildScriptL()
    { 
    // Add script as your need.   
     const TInt scripts[] =
        {
        DELAY(1),
        LeftCBA,        // delay between commands is 1*0.1 seconds = 0.1 seconds 
		REP(Down, 2),
		Right,
		KeyOK,
		KeyOK,
        LeftCBA,
        REP(Down, 2),
        Right,
        REP(Down, 1), 
        KeyOK,
        KeyOK,        
        LeftCBA,
        REP(Down, 2),
        Right,
        REP(Down, 2),
        KeyOK,
        KeyOK,
        TEND
        };
     AddTestScriptL(scripts, sizeof(scripts)/sizeof(TInt));
    }
    
// ---------------------------------------------------------------------------
// CBCTesteikbdialgCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTesteikbdialgCase::RunL( TInt aCmd )
    {
     if ( aCmd > EBCTestCmdMaxOutline || aCmd < EBCTestCmdEmptyOutline )
       {
      	return;
        }
    
    switch ( aCmd ) 
        {        
        case EBCTestBCtrlCmdOutline01:
        	TestFunctionL();
        	break;
        case EBCTestBCtrlCmdOutline02:
            Test();            
        	break;
        case EBCTestBCtrlCmdOutline03:
            TestSetFromResL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTesteikbdialgCase::TestFunctionL
// ---------------------------------------------------------------------------
//
void CBCTesteikbdialgCase::TestFunctionL()
    {
    
    _LIT( eikdialg, " CEikDialog test for EikbDialog! " ) ;
    _LIT( tstPrepare," test CEikDialog->PrepareLC() ");
    _LIT( tstSetTitle,"test CEikDialog->SetTitleL()");   
    _LIT( dimValue," set value = 1");
    _LIT( lineFocus," call SetLineNonFocusing " );
    _LIT(  rTitle, "reset title" );
    TBuf16<50> dlgTstTxt(rTitle);
    
    // Test some API here
    CBCTestMiscellCase* dialog = new ( ELeave ) CBCTestMiscellCase();    
    dialog->ConstructAutoDialogLC( EEikDialogFlagNoDrag, 
        R_AVKON_SOFTKEYS_OK_BACK ); 
    AssertNotNullL( dialog, eikdialg);
    _LIT( KEikDialog12, "CEikDialog::ConstructAutoDialogLC" );
    AssertTrueL( ETrue, KEikDialog12 );
    CleanupStack::PopAndDestroy( dialog );
    
    dialog = new ( ELeave ) CBCTestMiscellCase();    
    dialog->PrepareLC( R_DEMO_SINGLEPAGE_DIALOG );
    AssertTrueL(ETrue,tstPrepare);        
    
    dialog->SetTitleL( dlgTstTxt );
    AssertTrueL( ETrue,tstSetTitle );    

	dialog->SetLineNonFocusing( EsinglePageDlgC2Id );	
	AssertTrueL( ETrue,lineFocus );
                    
    dialog->MakeLineVisible( EsinglePageDlgC2Id,ETrue);
    AssertNotNullL(dialog,dimValue);
    
    dialog->SetLineDimmedNow( EsinglePageDlgC2Id,ETrue);
    _LIT( setLnDim," Test SetLineDimmedNow() " );
    AssertTrueL( ETrue,setLnDim );
    
    dialog->MakeWholeLineVisible( EsinglePageDlgC2Id,ETrue);
    AssertNotNullL(dialog,dimValue);
    
    //delete a line from resoure
    dialog->DeleteLine( ESinglePageDlgC1Id );
    _LIT( delLine, " call DeleteLine() ");
    AssertTrueL( ETrue, delLine);
    
    dialog->SetInitialCurrentLine();
    CEikCaptionedControl* curLine = dialog->CurrentLine();
    
    if(curLine)
    	{
    		dialog->TryChangeFocusToL( EsinglePageDlgC2Id );
    		_LIT( chgFocus," test TryChangeFocusToL()" );
				AssertTrueL( ETrue,chgFocus);
			}
    
    TInt pgID = dialog->ActivePageId();
    dialog->SetPageDensePacking( pgID ,ETrue);
    _LIT( pgDensePack," invoke SetPageDensePacking()" );
	AssertTrueL( ETrue, pgDensePack);
	
  	dialog->SetPageDimmedNow( pgID,ETrue );
  	AssertTrueL( ETrue, dimValue);
  	  
  	dialog->Title();
  	_LIT( tT,"Test Title()" );
  	AssertTrueL( ETrue,tT );
  	
  	dialog->Control( EsinglePageDlgC2Id );
  	_LIT( ctrl,"Test Control " );
  	AssertTrueL( ETrue,ctrl );
  	
  	dialog->ControlOrNull( EsinglePageDlgC2Id );
  	_LIT( ctrlOrNull," Test ControlOrNull()" );
  	AssertTrueL( ETrue,ctrlOrNull);
  	
  	dialog->ControlCaption( EsinglePageDlgC2Id );
  	_LIT( cntrlCaption," Test ControlCaption ");
  	AssertTrueL( ETrue,cntrlCaption);
  	
  	dialog->ActivateFirstPageL();
  	_LIT( actvFirstPg," Test ActivateFirstPageL()" );
  	AssertTrueL( ETrue,actvFirstPg );
  	
  	dialog->SetControlCaptionL( EsinglePageDlgC2Id, dimValue);
  	_LIT( setCtrlCaption," Test SetControlCaptionL()" );
  	AssertTrueL(ETrue ,setCtrlCaption );
  	
  	dialog->SetControlCaptionL( EsinglePageDlgC2Id, R_TITLE_TEXT1 );
  	_LIT( KEikDialog7, "CEikDialog::SetControlCaptionL with resource Id" );
    AssertTrueL( ETrue, KEikDialog7 );
  	
    CArrayFix<TCoeColorUse>* clrList =
		new (ELeave) CArrayFixFlat<TCoeColorUse>(1);
    CleanupStack::PushL(clrList);
    dialog->GetColorUseListL( *clrList ); 
    CleanupStack::Pop();
    delete clrList;
   
    dialog->IsEditable();
    _LIT( isEdit," Test IsEditable " );
    AssertTrueL( ETrue,isEdit );
    
    dialog->MakeVisible(ETrue);
    _LIT( mkVisible,"Test MakeVisible() " );
    AssertTrueL( ETrue, mkVisible);
    
    TKeyEvent kEvnt;
    kEvnt.iCode = '0';
    dialog->OfferKeyEventL(kEvnt,EEventNull);
    _LIT( ofKeyEvent," Test OfferKeyEventL() " );
    AssertTrueL( ETrue, ofKeyEvent );
    
    dialog->SetEditableL( ETrue );
    _LIT( setEdit," Test SetEditableL() " );
    AssertTrueL( ETrue, setEdit );
    
    TInt activePageIndex = dialog->ActivePageIndex();
    _LIT( KEikDialog1, "CEikDialog::ActivePageIndex" );
    AssertTrueL( ETrue, KEikDialog1 );
    
    MEikCommandObserver* observer = dialog->ButtonCommandObserver();
    _LIT( KEikDialog2, "CEikDialog::ButtonCommandObserver" );
    AssertNotNullL( observer, KEikDialog2 );
    
    dialog->AdjustAllIdsOnPage( 0, 0 );
    _LIT( KEikDialog3, "CEikDialog::AdjustAllIdsOnPage" );
    AssertTrueL( ETrue, KEikDialog3 );
    
    dialog->HandleInteractionRefused( 0 );
    _LIT( KEikDialog4, "CEikDialog::HandleInteractionRefused" );
    AssertTrueL( ETrue, KEikDialog4 );
            
    dialog->SetTitleL( R_TITLE_TEXT1 );
    _LIT( KEikDialog5, "CEikDialog::SetTitleL" );
    AssertTrueL( ETrue, KEikDialog5 );
    
    dialog->PageChangedL( EsinglePageDlgC3Id );
    _LIT( KEikDialog6, "CEikDialog::PageChangedL" );
    AssertTrueL( ETrue, KEikDialog6 );
    
    TInt delta = 5;
    dialog->RotateFocusByL( delta );
    _LIT( KEikDialog8, "CEikDialog::RotateFocusByL" );
    AssertTrueL( ETrue, KEikDialog8 );
    
    CEikCaptionedControl* becomesLatent = dialog->Line( 
        EsinglePageDlgC2Id );
    CEikCaptionedControl* nolongerLatent = dialog->Line( 
        EsinglePageDlgC3Id );
    becomesLatent->SetLatent( EFalse );
    nolongerLatent->SetLatent( ETrue );
    dialog->SwitchLineLatency( EsinglePageDlgC2Id, EsinglePageDlgC3Id );
    _LIT( KEikDialog9, "CEikDialog::SwitchLineLatency" );
    AssertTrueL( ETrue, KEikDialog9 );
    becomesLatent->SetLatent( EFalse );
    nolongerLatent->SetLatent( EFalse );
          
    dialog->InsertLineL( 0, R_LINE_PAGE );
    _LIT(insertLine, "CEikDialog::InsertLineL" );
    AssertTrueL( ETrue,insertLine );
    
    CEikButtonGroupContainer* currentBtGrp = CEikButtonGroupContainer::Current();
    CEikButtonGroupContainer* btGrp = dialog->SwapButtonGroupContainer( 
        currentBtGrp );
    dialog->SwapButtonGroupContainer( btGrp );
    _LIT( KEikDialog10, "CEikDialog::SwapButtonGroupContainer" );
    AssertNotNullL( btGrp, KEikDialog10 );
    
    dialog->MakePanelButtonVisible( EAknSoftkeyBack, ETrue );
    _LIT( KEikDialog11, "CEikDialog::MakePanelButtonVisible" );
    AssertTrueL( ETrue, KEikDialog11 );
    
    _LIT( KStreamName, "c:\\BCTestLog\\baseControl.txt" );
    RFs& tempServer = CEikonEnv::Static()->FsSession();    
    tempServer.Delete( KStreamName );    
    RFileWriteStream fWrite;
    User::LeaveIfError( fWrite.Create( tempServer, 
        KStreamName, EFileWrite ) );
    CleanupClosePushL( fWrite );
    dialog->WriteInternalStateL( fWrite );
    _LIT( KEikDialog13, "CEikDialog::WriteInternalStateL" );
    AssertTrueL( ETrue, KEikDialog13 );
    CleanupStack::PopAndDestroy( &fWrite );
    tempServer.Delete( KStreamName );
            
    dialog->RunLD();      
    }
 
void CBCTesteikbdialgCase::Test()
    {
    CBCTestMiscellCase *miscell = new ( ELeave ) CBCTestMiscellCase();
    CleanupStack::PushL( miscell );
    
    miscell->ConstructSleepingAlertDialogL( R_DEMO_SINGLEPAGE_DIALOG );
    _LIT( cstSlpAlrtDlg," Test ConstructSleepingAlertDialog()" );
    AssertTrueL( ETrue,cstSlpAlrtDlg );
            
    miscell->RouseSleepingDialog();
    _LIT( rusSleepingDlg," Test RouseSleepingDialog() " );
    AssertTrueL( ETrue,rusSleepingDlg);
        
    miscell->ExitSleepingDialog();
    _LIT(extSlpDlg," Test ExitSleepingDialog() " );
    AssertTrueL( ETrue,extSlpDlg );
    
    CleanupStack::Pop();
    delete miscell;
    
    miscell = new ( ELeave ) CBCTestMiscellCase(); 
    miscell->ConstructSleepingDialogL( R_DEMO_SINGLEPAGE_DIALOG );
    _LIT( cstSlpDlg," Test ConstructSleepingDialog()" );
    AssertTrueL( ETrue,cstSlpDlg);
    
    miscell->ExitSleepingDialog();
    
    delete miscell;

    iContainer->DrawNow();
    _LIT( preContext," Test PrepareContext() " );
    AssertTrueL( ETrue,preContext );

    }

void CBCTesteikbdialgCase::TestSetFromResL()
    {
  	_LIT( dialgCreat," if dialg have been created" );
    TBuf<32> tmpBuf(dialgCreat);

    CEikDialog *dialog = new ( ELeave ) CEikDialog();
    AssertNotNullL( dialog, dialgCreat );	

    dialog->ExecuteLD( R_DEMO_SINGLEPAGE_DIALOG );    
    }

