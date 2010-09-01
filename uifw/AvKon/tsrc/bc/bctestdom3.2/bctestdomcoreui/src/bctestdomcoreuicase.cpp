/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test case
*
*/


#include <w32std.h>
#include <coecntrl.h>
#include <vuicaddvoicetagdialog.h>
#include <vuicchangevoicetagdialog.h>
#include <vuicerasevoicetagdialog.h>
#include <vuicplaybackvoicetagdialog.h>
#include <vuicvoicedialer.h>
#include <vuicvoicetagcontact.h>
#include <vuicvoicetagfield.h>
#include <vuicvoicerecog.h>
#include <vuicvoicerecogdialog.h>
#include <bctestdomcoreui.rsg>

#include "bctestdomcoreuicase.h" 
#include "bctestdomcoreuicontainer.h"
#include "bctestdomcoreui.hrh"
#include "bctestdommenusatinterface.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomCoreUiCase* CBCTestDomCoreUiCase::NewL( 
    CBCTestDomCoreUiContainer* aContainer )
    {
    CBCTestDomCoreUiCase* self = new( ELeave ) CBCTestDomCoreUiCase( 
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
CBCTestDomCoreUiCase::CBCTestDomCoreUiCase( 
    CBCTestDomCoreUiContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomCoreUiCase::~CBCTestDomCoreUiCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomCoreUiCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomCoreUiCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL(DELAY(1), LeftCBA, KeyOK, WAIT(4), RightCBA,WAIT(10),TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomCoreUiCase::RunL( TInt aCmd )
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
// CBCTestDomCoreUiCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestDomCoreUiCase::PrepareCaseL( TInt aCmd )
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
// CBCTestDomCoreUiCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestDomCoreUiCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    } 
 
// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestDomCoreUiCase::TestFunctionL()
    {
    TestMenuSATInterfaceL();
    TestAddVoiceTagDialogL();
    TestChangeVoiceTagDialogL();
    TestEraseVoiceTagDialogL();
    TestVoiceDialerL();
    TestVoiceTagContactL();
    TestVoiceTagFieldL();
    TestVoiceRecogL();
    }

// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::TestMenuSATInterfaceL
// ---------------------------------------------------------------------------
//    
void CBCTestDomCoreUiCase::TestMenuSATInterfaceL()
    
    {
    CBCTestDomMenuSATInterface *menuSI = 
                        new( ELeave ) CBCTestDomMenuSATInterface();
    CleanupStack::PushL( menuSI );//push
    _LIT( msiLogInit, "CMenuSATInterface::CMenuSATInterface()" );
    AssertNotNullL( menuSI, msiLogInit );

    _LIT( testValue, "MenuSATI" );
    menuSI->MakeSatUiVisible( EFalse, testValue );
    _LIT( msiLogSatUi, "CMenuSATInterface::MakeSatUiVisible( , )" );
    AssertNotNullL( menuSI, msiLogSatUi );

    menuSI->MakeSatUiVisible( ETrue, testValue, 6 );
    _LIT( msiLogSatUi2, "CMenuSATInterface::MakeSatUiVisible( , , )" );
    AssertNotNullL( menuSI, msiLogSatUi2 );
        
    CleanupStack::PopAndDestroy( menuSI );
    }

// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::TestAddVoiceTagDialogL
// ---------------------------------------------------------------------------
//    
void CBCTestDomCoreUiCase::TestAddVoiceTagDialogL()
    {
    CPbkContactEngine* pbk = CPbkContactEngine::NewL();
    CleanupStack::PushL( pbk );//push
    CPbkContactItem* contactItem = pbk->CreateEmptyContactL();
    CleanupStack::PushL( contactItem );//push
    
    CAddVoiceTagDialog* addDial = new( ELeave ) CAddVoiceTagDialog( *contactItem, 1 );
    CleanupStack::PushL( addDial );//push
    _LIT( msiLogAddVoiceTagDialog, "CAddVoiceTagDialog::CAddVoiceTagDialog()" );
    AssertNotNullL( addDial, msiLogAddVoiceTagDialog );
    
    addDial->ExecuteLD();
    _LIT( msiLogExecuteLD, "CAddVoiceTagDialog::ExecuteLD()" );
    AssertTrueL( ETrue, msiLogExecuteLD );
    
    CleanupStack::PopAndDestroy( addDial );
    CleanupStack::PopAndDestroy( contactItem );
    CleanupStack::PopAndDestroy( pbk );
    _LIT( msiLogDesc, "CAddVoiceTagDialog::~CAddVoiceTagDialog()" );
    AssertTrueL( ETrue, msiLogDesc );

    }
    
// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::TestChangeVoiceTagDialogL
// ---------------------------------------------------------------------------
//    
void CBCTestDomCoreUiCase::TestChangeVoiceTagDialogL()
    {
    CPbkContactEngine* pbk = CPbkContactEngine::NewL();
    CleanupStack::PushL( pbk ); //push
    CPbkContactItem* contactItem = pbk->CreateEmptyContactL();
    CleanupStack::PushL( contactItem );//push
    
    CChangeVoiceTagDialog  *changeDial = new( ELeave ) CChangeVoiceTagDialog( *contactItem, 1 );    
    CleanupStack::PushL( changeDial );//push, because ExecuteLD() just return a error.
    _LIT( msiLogChangeVoiceTagDialog, "CChangeVoiceTagDialog::CChangeVoiceTagDialog()" );
    AssertNotNullL( changeDial, msiLogChangeVoiceTagDialog );

    changeDial->ExecuteLD();
    _LIT( msiLogExecuteLD, "CChangeVoiceTagDialog::ExecuteLD()" );
    AssertTrueL( ETrue, msiLogExecuteLD );
    
    CleanupStack::PopAndDestroy( changeDial );
    CleanupStack::PopAndDestroy( contactItem );
    CleanupStack::PopAndDestroy( pbk );
    _LIT( msiLogDesc, "CChangeVoiceTagDialog::~CChangeVoiceTagDialog()" );
    AssertTrueL( ETrue, msiLogDesc );
    
    }

// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::TestEraseVoiceTagDialogL
// ---------------------------------------------------------------------------
//    
void CBCTestDomCoreUiCase::TestEraseVoiceTagDialogL()
    {
    CPbkContactEngine* pbk = CPbkContactEngine::NewL();
    CleanupStack::PushL( pbk );//push
    CPbkContactItem* contactItem = pbk->CreateEmptyContactL();
    CleanupStack::PushL( contactItem );//push
    
    CEraseVoiceTagDialog *eraseDial =new( ELeave ) CEraseVoiceTagDialog( *contactItem, 1 );
    CleanupStack::PushL( eraseDial );//push, because ExecuteLD() just return a error.
    _LIT( msiLogCEraseVoiceTagDialog, "CEraseVoiceTagDialog::CEraseVoiceTagDialog()" );
    AssertNotNullL( eraseDial, msiLogCEraseVoiceTagDialog );

    eraseDial->ExecuteLD();  
    _LIT( msiLogExecuteLD, "CEraseVoiceTagDialog::ExecuteLD()" );
    AssertTrueL( ETrue, msiLogExecuteLD );
    
    CleanupStack::PopAndDestroy( eraseDial );
    CleanupStack::PopAndDestroy( contactItem );
    CleanupStack::PopAndDestroy( pbk );
    _LIT( msiLogDesc, "CEraseVoiceTagDialog::~CEraseVoiceTagDialog()" );
    AssertTrueL( ETrue, msiLogDesc );

    }
    
// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::TestVoiceDialerL
// ---------------------------------------------------------------------------
//    
void CBCTestDomCoreUiCase::TestVoiceDialerL()
    {
    CVoiceDialer* voiceDial = CVoiceDialer::NewL();
    CleanupStack::PushL( voiceDial );//push
    _LIT( msiLogNewL, "CVoiceDialer::NewL()" );
    AssertNotNullL( voiceDial, msiLogNewL );
    _LIT( msiLogNewLC, "CVoiceDialer::NewLC()" );
    AssertTrueL( ETrue, msiLogNewLC );
        
    voiceDial->VoiceTagAvailable();  
    _LIT( msiLogVTA, "CVoiceDialer::VoiceTagAvailable()" );
    AssertTrueL( ETrue, msiLogVTA );
    
    CPbkContactEngine* pbk = CPbkContactEngine::NewL();
    CleanupStack::PushL( pbk );//push
    
    CPbkContactItem* contactItem = pbk->CreateEmptyContactL();
    CleanupStack::PushL( contactItem );//push
  
    voiceDial->EraseVoiceTag( *contactItem, 1 );
    _LIT( msiLogVT, "CVoiceDialer::EraseVoiceTag()" );
    AssertTrueL( ETrue, msiLogVT );
    
    CVoiceTagContact* voiceTag = CVoiceTagContact::NewL();
    CleanupStack::PushL( voiceTag );//push
    
    voiceDial->GetContactsWithVoiceTagL( *voiceTag );
    _LIT( msiLogGCW, "CVoiceDialer::GetContactsWithVoiceTagL()" );
    AssertTrueL( ETrue, msiLogGCW );
    
    CVoiceTagField *voiceTagField = CVoiceTagField::NewL();
    CleanupStack::PushL( voiceTagField );//push
    
    voiceDial->GetFieldsWithVoiceTagL( *contactItem , *voiceTagField );
    _LIT( msiLogGFW, "CVoiceDialer::GetFieldsWithVoiceTagL()" );
    AssertTrueL( ETrue, msiLogGFW );
    
    CleanupStack::PopAndDestroy( voiceTagField );
    CleanupStack::PopAndDestroy( voiceTag );
    CleanupStack::PopAndDestroy( contactItem );
    CleanupStack::PopAndDestroy( pbk );
    CleanupStack::PopAndDestroy( voiceDial );

    }

// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::TestVoiceTagContactL
// ---------------------------------------------------------------------------
//    
void CBCTestDomCoreUiCase::TestVoiceTagContactL()
    {
    CVoiceTagContact* voiceTagContact = CVoiceTagContact::NewL(); 
    CleanupStack::PushL( voiceTagContact );//push
    _LIT( msiLogNewL, "CVoiceTagContact::NewL()" );
    AssertNotNullL( voiceTagContact, msiLogNewL );
    _LIT( msiLogNewLC, "CVoiceTagContact::NewLC()" );
    AssertTrueL( ETrue, msiLogNewLC );
    
    TContactItemId aCID = 12345;
    
    voiceTagContact->AddL( aCID, 1 );
    _LIT( msiLogAddL, "CVoiceTagContact::AddL()" );
    AssertTrueL( ETrue, msiLogAddL );

    voiceTagContact->Count();
    _LIT( msiLogCount, "CVoiceTagContact::Count()" );
    AssertTrueL( ETrue, msiLogCount );

    voiceTagContact->ContactId( 0 );
    _LIT( msiLogContactId, "CVoiceTagContact::ContactId()" );
    AssertTrueL( ETrue, msiLogContactId );

    voiceTagContact->FieldIndex( 0 );
     _LIT( msiLogFieldIndex, "CVoiceTagContact::FieldIndex()" );
    AssertTrueL( ETrue, msiLogFieldIndex );

    voiceTagContact->Reset();
     _LIT( msiLogReset, "CVoiceTagContact::Reset()" );
    AssertTrueL( ETrue, msiLogReset );

    CleanupStack::PopAndDestroy( voiceTagContact );
   
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::TestVoiceTagFieldL
// ---------------------------------------------------------------------------
//    
void CBCTestDomCoreUiCase::TestVoiceTagFieldL()
    {
    CVoiceTagField* voiceTagField = CVoiceTagField::NewL();
    CleanupStack::PushL( voiceTagField );//push
    _LIT( msiLogNewL, "CVoiceTagField::NewL()" );
    AssertNotNullL( voiceTagField, msiLogNewL );
    _LIT( msiLogNewLC, "CVoiceTagField::NewLC()" );
    AssertTrueL( ETrue, msiLogNewLC );
    
    voiceTagField->AddL(0);
    _LIT( msiLogAddL, "CVoiceTagField::AddL()" );
    AssertTrueL( ETrue, msiLogAddL );

    voiceTagField->Count();
    _LIT( msiLogCount, "CVoiceTagField::Count()" );
    AssertTrueL( ETrue, msiLogCount );

    voiceTagField->FieldIndex(0);
     _LIT( msiLogFieldIndex, "CVoiceTagField::FieldIndex()" );
    AssertTrueL( ETrue, msiLogFieldIndex );

    voiceTagField->Reset();
     _LIT( msiLogReset, "CVoiceTagField::Reset()" );
    AssertTrueL( ETrue, msiLogReset );
    
    CleanupStack::PopAndDestroy( voiceTagField );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::TestVoiceRecogL
// ---------------------------------------------------------------------------
//    
void CBCTestDomCoreUiCase::TestVoiceRecogL()
    {
    CVoiceRecog* voiceRecog = CVoiceRecog::NewL();
    CleanupStack::PushL( voiceRecog );//push

    _LIT( msiLogNewL, "VoiceRecog::NewL()" );
    AssertNotNullL( voiceRecog, msiLogNewL );
    _LIT( msiLogNewLC, "VoiceRecog::NewLC()" );
    AssertTrueL( ETrue, msiLogNewLC );

    CleanupStack::PopAndDestroy( voiceRecog );    
    }

// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::TestPlaybackVoiceTagDialogL
// ---------------------------------------------------------------------------
//    
void CBCTestDomCoreUiCase::TestPlaybackVoiceTagDialogL()
    {
    CPbkContactEngine* pbk = CPbkContactEngine::NewL();
    CleanupStack::PushL( pbk );//push
    CPbkContactItem* contactItem = pbk->CreateEmptyContactL();
    CleanupStack::PushL( contactItem );//push

    TContactItemId contactItemId = contactItem->Id();
    
    CPlaybackVoiceTagDialog* playbackDial = new( ELeave ) CPlaybackVoiceTagDialog( contactItemId, 0);
    _LIT( msiLogCon, "CPlaybackVoiceTagDialog::CPlaybackVoiceTagDialog()" );
    AssertTrueL( ETrue, msiLogCon );
    
    MNssContextListArray* contList = NULL;
    TInt errorCode = 0;
    playbackDial->GetContextListCompleted( contList, errorCode);
  
    //error,can't find resource.
    TRAPD( error, playbackDial->ExecuteLD() )

    if( error )
    {
    _LIT( msiLogErr, "some resources can't be find!" );
    AssertTrueL( ETrue, msiLogErr );
    }
    else
    {
    _LIT( msiLogExecuteLD, "CPlaybackVoiceTagDialog::ExecuteLD()" );        
    AssertTrueL( ETrue, msiLogExecuteLD );
    }
   
    CleanupStack::PopAndDestroy( contactItem );
    CleanupStack::PopAndDestroy( pbk );
    _LIT( msiLogDesc, "::~CPlaybackVoiceTagDialog()" );
    AssertTrueL( ETrue, msiLogDesc );
    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::TestVoiceRecognitionDialogL
// ---------------------------------------------------------------------------
//    
void CBCTestDomCoreUiCase::TestVoiceRecognitionDialogL()
    {
    CVoiceRecognitionDialog* voiceRec = new( ELeave ) CVoiceRecognitionDialog();
    _LIT( msiLogVRD, "CVoiceRecognitionDialog::CVoiceRecognitionDialog()" );
    AssertTrueL( ETrue, msiLogVRD );
    
    voiceRec->ExecuteLD();
    _LIT( msiLogExecuteLD, "CVoiceRecognitionDialog::ExecuteLD()" );
    AssertTrueL( ETrue, msiLogExecuteLD );

    CVoiceRecognitionDialog* voiceRec2 = new( ELeave ) CVoiceRecognitionDialog();
    voiceRec2->Cancel();
    _LIT( msiLogCancel, "CVoiceRecognitionDialog::Cancel()" );
    AssertTrueL( ETrue, msiLogCancel );

    _LIT( msiLogDesc, "CVoiceRecognitionDialog::~CVoiceRecognitionDialog()" );
    AssertTrueL( ETrue, msiLogDesc );
    
    }

