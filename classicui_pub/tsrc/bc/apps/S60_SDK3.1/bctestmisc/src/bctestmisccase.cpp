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
#include <aknscreenmode.h>
#include <aknappui.h>
#include <bctestmisc.rsg>
#include <aknsconstants.h>
#include <eikmenub.h>
#include <aknutils.h>

#include "bctestmisccase.h"
#include "bctestmisccontainer.h"
#include "bctestmisc.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestMiscCase* CBCTestMiscCase::NewL(
    CBCTestMiscContainer* aContainer )
    {
    CBCTestMiscCase* self = new( ELeave ) CBCTestMiscCase(
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
CBCTestMiscCase::CBCTestMiscCase(
    CBCTestMiscContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestMiscCase::~CBCTestMiscCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestMiscCase::ConstructL()
    {
    BuildScriptL();
    iEnv = CEikonEnv::Static();
    }

// ---------------------------------------------------------------------------
// CBCTestMiscCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestMiscCase::BuildScriptL()
    {
    // Add script as your need.
    AddTestL( DELAY(1), LeftCBA, KeyOK, TEND );
    }

// ---------------------------------------------------------------------------
// CBCTestMiscCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestMiscCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline1 )
        {
        return;
        }

    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            TestAknScreenModesL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestMiscCase::TestAknScreenModesL
// ---------------------------------------------------------------------------
//
void CBCTestMiscCase::TestAknScreenModesL()
    {
    //TAknScreenModes screenModes;
    TAknScreenModes screenModes = TAknScreenModes::GetModes();
    _LIT( KGetModes, "GetModes test" );
    AssertTrueL( ETrue, KGetModes );

    TInt count = screenModes.Count();
    _LIT( KCount, "Count test" );
    AssertTrueL( ETrue, KCount );

    TAknScreenMode screenMode = screenModes[0];
    _LIT( KOperator, "operator test" );
    AssertTrueL( ETrue, KOperator );

    CAknAppUiBase* uiBase = static_cast<CAknAppUiBase*>( iEnv->EikAppUi() );
    screenModes.SetAppUiScreenModeL( uiBase, screenMode );
    _LIT( KSetAppUiScreenModeL, "SetAppUiScreenModeL test" );
    AssertTrueL( ETrue, KSetAppUiScreenModeL );

    TSize size = screenMode.SizeInPixels();
    _LIT( KSizeInPixels, "SizeInPixels test" );
    AssertTrueL( ETrue, KSizeInPixels );

    TDisplayMode displayMode = screenMode.DisplayMode();
    _LIT( KDisplayMode, "DisplayMode test" );
    AssertTrueL( ETrue, KDisplayMode );

    TInt modeNumber = screenMode.ModeNumber();
    _LIT( KModeNumber, "ModeNumber test" );
    AssertTrueL( ETrue, KModeNumber );


    CEikMenuBar* menuBar = new( ELeave ) CEikMenuBar();
    CleanupStack::PushL( menuBar );

    menuBar->ConstructL( CAknEnv::Static()->FepMenuObserver(), 0, 0 );

    menuBar->SetContextMenuTitleResourceId( R_BCTESTMISC_MENU_TITLE );
    _LIT( KResource, "SetContextMenuTitleResourceId test" );
    AssertTrueL( ETrue, KResource );

    menuBar->TryDisplayContextMenuBarL();
    _LIT( KTry, "TryDisplayContextMenuBarL test" );
    AssertTrueL( ETrue, KTry );

    menuBar->SetMenuType( CEikMenuBar::EMenuOptions );
    _LIT( KSetMenuType , "SetMenuType test");
    AssertTrueL( ETrue, KSetMenuType );

    CleanupStack::PopAndDestroy( menuBar );

    TBool ret = AknLayoutUtils:: MSKEnabled();
    _LIT( KMSK, "MSKEnabled test" );
    AssertTrueL( ETrue, KMSK );
    }
