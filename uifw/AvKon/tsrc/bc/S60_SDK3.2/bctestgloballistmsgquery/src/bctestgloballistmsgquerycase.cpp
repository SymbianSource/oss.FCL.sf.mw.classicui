/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test cases implementation for BCTestGlobalListMsgQuery.
*
*/

#include <w32std.h>
#include <coecntrl.h>
#include <coemain.h>
#include <s32mem.h>

#include "bctestgloballistmsgquerycase.h"
#include "bctestgloballistmsgquerycontainer.h"
#include "bctestactiveengine.h"
#include "bctestgloballistmsgquery.hrh"
#include <bctestgloballistmsgquery.rsg>

//#include <aknsddata.h>
#include <akngloballistmsgquery.h>

#include <avkon.mbg>
#include <aknconsts.h>

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryCase::NewL()
// ---------------------------------------------------------------------------
//
CBCTestGlobalListMsgQueryCase* CBCTestGlobalListMsgQueryCase::NewL(
    CBCTestGlobalListMsgQueryContainer* aContainer )
    {
    CBCTestGlobalListMsgQueryCase* self = new( ELeave ) CBCTestGlobalListMsgQueryCase( aContainer );
        
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryCase::CBCTestGlobalListMsgQueryCase()
// ---------------------------------------------------------------------------
//
CBCTestGlobalListMsgQueryCase::CBCTestGlobalListMsgQueryCase(
    CBCTestGlobalListMsgQueryContainer* aContainer )
    : iContainer( aContainer ), iActiveEngine( NULL )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryCase::~CBCTestGlobalListMsgQueryCase()
// ---------------------------------------------------------------------------
//
CBCTestGlobalListMsgQueryCase::~CBCTestGlobalListMsgQueryCase()
    {
    delete iActiveEngine;
    }

// ---------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryCase::ConstructL()
// ---------------------------------------------------------------------------
//
void CBCTestGlobalListMsgQueryCase::ConstructL()
    {
    iActiveEngine = new (ELeave) CBCTestActiveEngine;
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryCase::BuildScriptL()
// ---------------------------------------------------------------------------
//
void CBCTestGlobalListMsgQueryCase::BuildScriptL()
    {
    // Add script as your need.
    AddTestL( DELAY(1), LeftCBA, LeftCBA, WAIT(10), TEND );
    }

// ---------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryCase::RunL()
// ---------------------------------------------------------------------------
//
void CBCTestGlobalListMsgQueryCase::RunL( TInt aCmd )
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
// CBCTestGlobalListMsgQueryCase::PrepareCaseL()
// ---------------------------------------------------------------------------
//
void CBCTestGlobalListMsgQueryCase::PrepareCaseL( TInt aCmd )
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
// CBCTestSettingPageCase::ReleaseCaseL()
// ---------------------------------------------------------------------------
//
void CBCTestGlobalListMsgQueryCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestSettingPageCase::TestAllL()
// ---------------------------------------------------------------------------
//
void CBCTestGlobalListMsgQueryCase::TestAllL()
    {
    TestGlobalListMsgQueryL();
    }
 
// ---------------------------------------------------------------------------
// CBCTestSettingPageCase::TestGlobalListMsgQueryL()
// ---------------------------------------------------------------------------
//    
void CBCTestGlobalListMsgQueryCase::TestGlobalListMsgQueryL()
    {
    _LIT(KMSG, "MESSAGE");
    _LIT(KTITLE, "TITLE");
    const TInt KItemArrayGranularity = 4;
        
    CAknGlobalListMsgQuery* listMsgQuery = CAknGlobalListMsgQuery::NewL();
    CleanupStack::PushL( listMsgQuery );
    AssertNotNullL( listMsgQuery, _L( "CAknGlobalListMsgQuery NewL called" ));
    AssertNotNullL( listMsgQuery, _L( "CAknGlobalListMsgQuery NewLC called" ));
    
    CDesCArrayFlat* array = new ( ELeave ) CDesCArrayFlat( KItemArrayGranularity );
    CleanupStack::PushL( array );
    array->AppendL( _L( "test1" ) );
    array->AppendL( _L( "test2" ) );
    array->AppendL( _L( "test3" ) );
    array->AppendL( _L( "test4" ) );
    
    // Set skin id for the image.
    TAknsItemID skinId;
    skinId.Set( EAknsMajorGeneric, EAknsMinorGenericQgnNoteAlarmCalendar );

    listMsgQuery->SetImageSkinId( skinId );
    AssertTrueL( ETrue, _L( "CAknGlobalListMsgQuery SetImageSkinId called" ));

    if ( !iActiveEngine->Active() )
        {
        listMsgQuery->ShowListMsgQueryL( 
            array, 
            *( iActiveEngine->GetStatus() ),
            KTITLE,
            KMSG,
            0,
            R_AVKON_SOFTKEYS_OPTIONS_BACK__SELECT,
            EAknSoftkeyOptions,
            EAknSoftkeyBack,
            KAvkonBitmapFile,
            EMbmAvkonQgn_note_alarm_calendar,
            EMbmAvkonQgn_note_alarm_calendar_mask,
            CAknQueryDialog::EErrorTone);
             
        AssertTrueL( ETrue, _L( "CAknGlobalListMsgQuery ShowListMsgQueryL called" ));
        iActiveEngine->MakeActive();
        }
        
    listMsgQuery->MoveSelectionUp();
    AssertTrueL( ETrue, _L( "CAknGlobalListMsgQuery MoveSelectionUp called" ));
    listMsgQuery->MoveSelectionDown();
    AssertTrueL( ETrue, _L( "CAknGlobalListMsgQuery MoveSelectionDown called" ));
    listMsgQuery->SelectItem();
    AssertTrueL( ETrue, _L( "CAknGlobalListMsgQuery SelectItem called" ));
    listMsgQuery->CancelListMsgQuery();
    AssertTrueL( ETrue, _L( "CAknGlobalListMsgQuery CancelListMsgQuery called" ));
    
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( listMsgQuery );
    AssertTrueL( ETrue, _L( "CAknGlobalListMsgQuery destructor called" ));
    }   

// End of file
