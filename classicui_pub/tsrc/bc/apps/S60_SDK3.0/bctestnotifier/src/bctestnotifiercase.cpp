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
#include <coemain.h>
#include <S32MEM.h>

#include "bctestnotifiercase.h"
#include "bctestnotifiercontainer.h"
#include "bctestactiveengine.h"
#include "bctestnotifier.hrh"
#include <bctestnotifier.rsg>

#include <AknGlobalConfirmationQuery.h>
//#include <aknSDData.h>
#include <AknGlobalListQuery.h>
#include <AknGlobalMsgQuery.h>
#include <AknGlobalNote.h>
#include <AknGlobalProgressDialog.h>
#include <AknPopupNotify.h>

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestNotifierCase* CBCTestNotifierCase::NewL(
    CBCTestNotifierContainer* aContainer )
    {
    CBCTestNotifierCase* self = new( ELeave ) CBCTestNotifierCase(
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
CBCTestNotifierCase::CBCTestNotifierCase(
    CBCTestNotifierContainer* aContainer )
    : iContainer( aContainer ),
      iActiveEngine( NULL ),
      iActiveEngine1( NULL ),
      iActiveEngine2( NULL ),
      iActiveEngine3( NULL ),
      iActiveEngine4( NULL ),
      iActive(NULL)
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestNotifierCase::~CBCTestNotifierCase()
    {
    delete iActiveEngine;
    delete iActiveEngine1;
    delete iActiveEngine2;
    delete iActiveEngine3;
    delete iActiveEngine4;
    delete iActive;
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestNotifierCase::ConstructL()
    {
    iActiveEngine = new (ELeave) CBCTestActiveEngine;
    iActiveEngine1 = new (ELeave) CBCTestActiveEngine;
    iActiveEngine2 = new (ELeave) CBCTestActiveEngine;
    iActiveEngine3 = new (ELeave) CBCTestActiveEngine;
    iActiveEngine4 = new (ELeave) CBCTestActiveEngine;
    iActive = CWaitGlobalNote::NewL();
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestNotifierCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestNotifierCase::BuildScriptL()
    {
    // Add script as your need.
    AddTestL( DELAY(1), LeftCBA, LeftCBA, WAIT(10), TEND );
    
    }

// ---------------------------------------------------------------------------
// CBCTestNotifierCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestNotifierCase::RunL( TInt aCmd )
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
            TestAllL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestNotifierCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestNotifierCase::PrepareCaseL( TInt aCmd )
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
// CBCTestSettingPageCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//
void CBCTestNotifierCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

void CBCTestNotifierCase::TestAllL()
    {
    TestPopupNotifyL();
    TestGlobalConfirmationQueryL();
    TestGlobalListQueryL();
    TestGlobalMsgQueryL();
    TestGlobalNoteL();
    TestGlobalProgressDlgL();
    }
    
void CBCTestNotifierCase::TestGlobalConfirmationQueryL()
	{
	_LIT(KTITLE, "TEST");
	CAknGlobalConfirmationQuery* globalConfirmationQuery = CAknGlobalConfirmationQuery::NewL();
	AssertNotNullL( globalConfirmationQuery, _L( "CAknGlobalConfirmationQuery newl called" ));
	AssertNotNullL( globalConfirmationQuery, _L( "CAknGlobalConfirmationQuery newlc called" ));
	
	CleanupStack::PushL( globalConfirmationQuery );
	TAknsItemID id;
	globalConfirmationQuery->SetImageSkinId( id );
	AssertTrueL( ETrue, _L( "CAknGlobalConfirmationQuery SetImageSkinId called" ));
	if (!iActiveEngine->Active() )
	{
	globalConfirmationQuery->ShowConfirmationQueryL( *(iActiveEngine->GetStatus()), KTITLE,
		R_AVKON_SOFTKEYS_OK_CANCEL );
	AssertTrueL( ETrue, _L( "CAknGlobalConfirmationQuery ShowConfirmationQueryL called" ));
	iActiveEngine->MakeActive();
	}
	globalConfirmationQuery->UpdateConfirmationQuery( R_AVKON_SOFTKEYS_BACK );
	AssertTrueL( ETrue, _L( "CAknGlobalConfirmationQuery UpdateConfirmationQuery called" ));
	globalConfirmationQuery->CancelConfirmationQuery();
	AssertTrueL( ETrue, _L( "CAknGlobalConfirmationQuery CancelConfirmationQuery called" ));
	
	CleanupStack::PopAndDestroy( globalConfirmationQuery );
	AssertTrueL( ETrue, _L( "CAknGlobalConfirmationQuery destructor called" ));

	}
	
void CBCTestNotifierCase::TestGlobalListQueryL()
	{
	_LIT(KTITLE, "TEST");
	CAknGlobalListQuery* listQuery = CAknGlobalListQuery::NewL();
	AssertNotNullL( listQuery, _L( "CAknGlobalListQuery newl called" ));
	AssertNotNullL( listQuery, _L( "CAknGlobalListQuery newlc called" ));
	CleanupStack::PushL( listQuery );
	CDesCArrayFlat* array = new (ELeave)CDesCArrayFlat(1);
	array->AppendL( _L( "test1" ) );
	array->AppendL( _L( "test2" ) );
	array->AppendL( _L( "test3" ) );
	array->AppendL( _L( "test4" ) );
	if ( !iActiveEngine1->Active() )
		{
		listQuery->ShowListQueryL( array, *( iActiveEngine1->GetStatus() ) );
		AssertTrueL( ETrue, _L( "CAknGlobalListQuery ShowListQueryL called" ));
		iActiveEngine1->MakeActive();
		}
	listQuery->MoveSelectionUp();
	AssertTrueL( ETrue, _L( "CAknGlobalListQuery MoveSelectionUp called" ));
	listQuery->MoveSelectionDown();
	AssertTrueL( ETrue, _L( "CAknGlobalListQuery MoveSelectionDown called" ));
	listQuery->SelectItem();
	AssertTrueL( ETrue, _L( "CAknGlobalListQuery SelectItem called" ));
	listQuery->SetHeadingL( KTITLE );
	AssertTrueL( ETrue, _L( "CAknGlobalListQuery SetHeadingL called" ));
	listQuery->CancelListQuery();
    AssertTrueL( ETrue, _L( "CAknGlobalListQuery CancelListQuery called" ));
    
	delete array;
	CleanupStack::PopAndDestroy( listQuery );
    AssertTrueL( ETrue, _L( "CAknGlobalListQuery destructor called" ));
		
	}
	

void CBCTestNotifierCase::TestGlobalMsgQueryL()	
	{
	_LIT(KMSG, "MESSAGE");
	_LIT(KTITLE, "TEST");	
	CAknGlobalMsgQuery* msgQuery = CAknGlobalMsgQuery::NewL();
	AssertNotNullL( msgQuery, _L( "CAknGlobalMsgQuery newl called" ));
	AssertNotNullL( msgQuery, _L( "CAknGlobalMsgQuery newlc called" ));
	CleanupStack::PushL( msgQuery );
	TAknsItemID id;
	msgQuery->SetImageSkinId( id );
	AssertTrueL( ETrue, _L( "CAknGlobalMsgQuery SetImageSkinId called" ));
	if ( !iActiveEngine2->Active() )
		{
		msgQuery->ShowMsgQueryL( *( iActiveEngine2->GetStatus() ), KMSG,
			R_AVKON_SOFTKEYS_BACK, KTITLE, _L("") );
		AssertTrueL( ETrue, _L( "CAknGlobalMsgQuery ShowListQueryL called" ));
		iActiveEngine2->MakeActive();
		}
		
	msgQuery->UpdateMsgQuery( R_AVKON_SOFTKEYS_BACK );
	AssertTrueL( ETrue, _L( "CAknGlobalMsgQuery UpdateMsgQuery called" ));
	msgQuery->SetExitDelay( 1 );
	AssertTrueL( ETrue, _L( "CAknGlobalMsgQuery SetExitDelay called" ));
	msgQuery->CancelMsgQuery();
	AssertTrueL( ETrue, _L( "CAknGlobalMsgQuery CancelMsgQuery called" ));
	
	CleanupStack::PopAndDestroy( msgQuery );
    AssertTrueL( ETrue, _L( "CAknGlobalMsgQuery destructor called" ));	
	}
	
void CBCTestNotifierCase::TestGlobalNoteL()
	{
	_LIT(KNOTETEXT, "MESSAGE");
	CAknGlobalNote* globalNote = CAknGlobalNote::NewL();
	CleanupStack::PushL( globalNote );
	AssertNotNullL( globalNote, _L( "CAknGlobalNote newl called" ));
	AssertNotNullL( globalNote, _L( "CAknGlobalNote newlc called" ));
	globalNote->SetSoftkeys( R_AVKON_SOFTKEYS_OK_EMPTY );
	AssertTrueL( ETrue, _L( "CAknGlobalNote SetSoftkeys called" ));
	TInt noteID = globalNote->ShowNoteL( EAknGlobalInformationNote, KNOTETEXT );
	AssertTrueL( ETrue, _L( "CAknGlobalNote ShowNoteL called" ));
	AssertTrueL( ETrue, _L( "CAknGlobalNote DoGlobaNoteBufferL called" ));
	globalNote->CancelNoteL( noteID );
	AssertTrueL( ETrue, _L( "CAknGlobalNote CancelNoteL called" ));

    iActive->ShowGlobalNoteAsyncL();
    AssertTrueL( ETrue, _L( "CAknGlobalMsgQuery ShowNoteL Async called" ));

	CleanupStack::PopAndDestroy( globalNote );
	AssertTrueL( ETrue, _L( "CAknGlobalNote destructor called" ));
	AssertTrueL( ETrue, _L( "CAknNotifyBase destructor called" ));
	
	globalNote = CAknGlobalNote::NewL();
	globalNote->SetTextProcessing( ETrue );
	AssertTrueL( ETrue, _L( "CAknGlobalNote SetTextProcessing called" ));
	globalNote->SetPriority( 1 );
	AssertTrueL( ETrue, _L( "CAknGlobalNote SetPriority called" ));
	globalNote->SetGraphic( 10 );
	AssertTrueL( ETrue, _L( "CAknGlobalNote SetGraphic called" ));
	globalNote->SetAnimation( 10 );
	AssertTrueL( ETrue, _L( "CAknGlobalNote SetAnimation called" ));
	globalNote->SetTone( 10 );
	AssertTrueL( ETrue, _L( "CAknGlobalNote SetTone called" ));
	delete globalNote;		
	}
	
void CBCTestNotifierCase::TestGlobalProgressDlgL()
	{
	_LIT(KNOTETEXT, "MESSAGE");
	CAknGlobalProgressDialog* progressDlg = CAknGlobalProgressDialog::NewL();
	AssertNotNullL( progressDlg, _L( "CAknGlobalProgressDialog newl called" ));
	AssertNotNullL( progressDlg, _L( "CAknGlobalProgressDialog newlc called" ));
	CleanupStack::PushL( progressDlg );
	progressDlg->SetIconL( _L(""), _L("") );
	AssertTrueL( ETrue, _L( "CAknGlobalProgressDialog SetIconL called" ));
	progressDlg->SetImageL( _L("") );
	AssertTrueL( ETrue, _L( "CAknGlobalProgressDialog SetImageL called" ));
	progressDlg->UpdateProgressDialog( 200, 400 );
	AssertTrueL( ETrue, _L( "CAknGlobalProgressDialog UpdateProgressDialog called" ));
	
	TAknsItemID id1, id2;
	progressDlg->SetImageSkinIds( id1, id2 );
	AssertTrueL( ETrue, _L( "CAknGlobalProgressDialog SetImageSkinIds called" ));
	if ( !iActiveEngine4->Active() )
		{
		progressDlg->ShowProgressDialogL( *( iActiveEngine4->GetStatus() ), 
			KNOTETEXT );
		AssertTrueL( ETrue, _L( "CAknGlobalProgressDialog ShowProgressDialogL Async called" ));
		iActiveEngine4->MakeActive();
		}
	progressDlg->CancelProgressDialog();
	AssertTrueL( ETrue, _L( "CAknGlobalProgressDialog CancelProgressDialog called" ));
	progressDlg->ProcessFinished();
	AssertTrueL( ETrue, _L( "CAknGlobalProgressDialog ProcessFinished called" ));
	
	CleanupStack::PopAndDestroy( progressDlg );
    AssertTrueL( ETrue, _L( "CAknGlobalProgressDialog destructor called" ));	
		

	
	}
	
void CBCTestNotifierCase::TestPopupNotifyL()
	{
	CAknPopupNotify* popupNotify = CAknPopupNotify::NewL();
	AssertNotNullL( popupNotify, _L( "CAknPopupNotify newl called" ));
	AssertNotNullL( popupNotify, _L( "CAknPopupNotify newlc called" ));
	CleanupStack::PushL( popupNotify );
	CleanupStack::PopAndDestroy( popupNotify );
    AssertTrueL( ETrue, _L( "CAknPopupNotify destructor called" ));	
	}
	
	
