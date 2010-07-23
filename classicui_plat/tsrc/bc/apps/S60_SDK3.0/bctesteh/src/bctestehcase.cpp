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
#include <eikhkeyt.h>
#include <errorui.h>
#include <bctesteh.rsg>
#include <textresolver.hrh>

#include "bctestehcase.h"
#include "bctestehcontainer.h"
#include "bctesteh.hrh"

// constant
const TInt KErrCode = KErrAbort;
const TInt KModifierCode = 0;


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestEHCase* CBCTestEHCase::NewL(
    CBCTestEHContainer* aContainer )
    {
    CBCTestEHCase* self = new( ELeave ) CBCTestEHCase(
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
CBCTestEHCase::CBCTestEHCase(
    CBCTestEHContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestEHCase::~CBCTestEHCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestEHCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestEHCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestEHCase::BuildScriptL()
    {
    // Add script as your need.
    AddTestL( LeftCBA, KeyOK, KeyOK, TEND );
    }

// ---------------------------------------------------------------------------
// CBCTestEHCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestEHCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline1 )
        {
        return;
        }

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
// CBCTestEHCase::TestErrorUiL
// ---------------------------------------------------------------------------
//
void CBCTestEHCase::TestErrorUiL()
    {
    CErrorUI* ui = CErrorUI::NewL();
    CleanupStack::PushL( ui );
    _LIT( KNewL, "CErrorUI::NewL Used by servers" );
    AssertNotNullL( ui, KNewL );

    CErrorUI* errUi = CErrorUI::NewLC() ;
    _LIT( KNewLC, "CErrorUI::NewLC Used by servers" );
    AssertNotNullL( errUi, KNewLC );
    CleanupStack::PopAndDestroy( errUi );

    CCoeEnv* env = CCoeEnv::Static();
    CErrorUI* uiForApp = CErrorUI::NewL( *env );
    CleanupStack::PushL( uiForApp );
    _LIT( KNewL2, "CErrorUI::NewL Used by applications" );
    AssertNotNullL( uiForApp, KNewL2 );
    CleanupStack::PopAndDestroy( uiForApp );

    uiForApp = CErrorUI::NewLC( *env );
    _LIT( KNewLC2, "CErrorUI::NewLC Used by applications" );
    AssertNotNullL( uiForApp, KNewLC2 );
    CleanupStack::PopAndDestroy( uiForApp );

    TBool errQuery = EFalse;
    TUint flags = 0;
    TInt resourceID = 0;
    ui->TextResolver().ResolveErrorString(KErrCode, resourceID, flags,
                            CTextResolver::ECtxAutomatic);
    errQuery = ui->ShowGlobalErrorQueryL( KErrCode );
    _LIT( KShowGlobalErrorQueryL, "CErrorUI::ShowGlobalErrorQueryL" );
    if ( !(flags & ETextResolverBlankErrorFlag) )
        {
        //should display
        AssertTrueL( errQuery, KShowGlobalErrorQueryL );
        }
    else
        {
        AssertTrueL( !errQuery, KShowGlobalErrorQueryL );
        }

    errQuery = EFalse;
    ui->TextResolver().ResolveErrorString(KErrCode, resourceID, flags,
                            CTextResolver::ECtxAutomatic);
    errQuery = ui->ShowGlobalErrorNoteL( KErrCode );
    _LIT( KShowGlobalErrorNoteL, "CErrorUI::ShowGlobalErrorNoteL" );
    if ( !(flags & ETextResolverBlankErrorFlag) )
        {
        //should display
        AssertTrueL( errQuery, KShowGlobalErrorNoteL );
        }
    else
        {
        AssertTrueL( !errQuery, KShowGlobalErrorNoteL );
        }


    CleanupStack::Pop( ui );
    delete ui;
    ui = NULL;

    }

// ---------------------------------------------------------------------------
// CBCTestEHCase::TestHotkeysL
// ---------------------------------------------------------------------------
//
void CBCTestEHCase::TestHotkeysL()
    {
    CEikHotKeyTable* hotKey = new( ELeave) CEikHotKeyTable();
    CleanupStack::PushL( hotKey );
    _LIT( KCEikHotKeyTable, "CEikHotKeyTable::CEikHotKeyTable" );
    AssertNotNullL( hotKey, KCEikHotKeyTable );

    hotKey->ConstructFromResourceL( R_BCTESTEH_HOTKEY_COMMAND );
    _LIT( KConstructFromResourceL, "CEikHotKeyTable::ConstructFromResourceL" );
    AssertNotNullL( hotKey, KConstructFromResourceL );

    hotKey->AddItemL( EBCTestCmdOutline1, Key1, KModifierCode );
    _LIT( KAddItemL, "CEikHotKeyTable::AddItemL" );
    AssertNotNullL( hotKey, KAddItemL );

    hotKey->AddItemL( EBCTestCmdOutline1, Key1, EModifierCtrl );
    _LIT( KAddItemL1, "CEikHotKeyTable::AddItemL 1" );
    AssertNotNullL( hotKey, KAddItemL1 );

    hotKey->AddItemL( EProgCmdAutoTest, Key2,
        EModifierShift|EModifierCtrl );
    _LIT( KAddItemL2, "CEikHotKeyTable::AddItemL 2" );
    AssertNotNullL( hotKey, KAddItemL2 );

    TInt cmdId = hotKey->CommandIdFromHotKey( Key1, EModifierCtrl );
    _LIT( KCommandIdFromHotKey, "CEikHotKeyTable::CommandIdFromHotKey" );
    AssertNotNullL( hotKey, KCommandIdFromHotKey );

    cmdId = hotKey->CommandIdFromHotKey( Key2, EModifierShift|EModifierCtrl );
    _LIT( KCommandIdFromHotKey2, "CEikHotKeyTable::CommandIdFromHotKey 2" );
    AssertNotNullL( hotKey, KCommandIdFromHotKey2 );

    TInt keyCode;
    TInt kModifier;
    TBool flag = hotKey->HotKeyFromCommandId( EBCTestCmdOutline1, keyCode,
        kModifier );
    _LIT( KHotKeyFromCommandId, "CEikHotKeyTable::HotKeyFromCommandId" );
    AssertTrueL( flag, KHotKeyFromCommandId );

    flag = hotKey->HotKeyFromCommandId( EProgCmdAutoTest, keyCode,
        kModifier );
    _LIT( KHotKeyFromCommandId1, "CEikHotKeyTable::HotKeyFromCommandId 1" );
    AssertTrueL( flag, KHotKeyFromCommandId1 );

    hotKey->RemoveItem( EBCTestCmdOutline1 );
    _LIT( KRemoveItem, "CEikHotKeyTable::RemoveItem" );
    AssertNotNullL( hotKey, KRemoveItem );

    hotKey->RemoveItem( EProgCmdAutoTest );
    _LIT( KRemoveItem2, "CEikHotKeyTable::RemoveItem 2" );
    AssertNotNullL( hotKey, KRemoveItem2 );

    hotKey->Reset();
    _LIT( KReset, "CEikHotKeyTable::Reset" );
    AssertNotNullL( hotKey, KReset );

    CleanupStack::Pop( hotKey );
    delete hotKey;
    hotKey = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestEHCase::TestFunctionL
// ---------------------------------------------------------------------------
//
void CBCTestEHCase::TestFunctionL()
    {
    TestErrorUiL();
    TestHotkeysL();
    }

