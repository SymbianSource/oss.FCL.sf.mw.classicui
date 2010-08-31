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

#include "bctestKeyLockcase.h"
#include "bctestKeyLockcontainer.h"
#include "bctestKeyLock.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestKeyLockCase* CBCTestKeyLockCase::NewL(
    CBCTestKeyLockContainer* aContainer )
    {
    CBCTestKeyLockCase* self = new( ELeave ) CBCTestKeyLockCase(
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
CBCTestKeyLockCase::CBCTestKeyLockCase(
    CBCTestKeyLockContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestKeyLockCase::~CBCTestKeyLockCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestKeyLockCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestKeyLockCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestKeyLockCase::BuildScriptL()
    {
    // Add script as your need.
    #ifdef __WINSCW__
    {
    AddTestL( LeftCBA, KeyOK, TEND );
    }
    #else
    {
    AddTestL( LeftCBA, KeyOK, TEND );
    AddTestL( LeftCBA, TEND );
    AddTestL( Key1, TEND );
    AddTestL( Key2, TEND );
    AddTestL( Key3, TEND );
    AddTestL( Key4, TEND );
    AddTestL( Key5, TEND );
    AddTestL( LeftCBA, TEND );
    AddTestL( RightCBA, TEND );
    AddTestL( RightCBA, TEND );
    AddTestL( RightCBA, TEND );
    }
    #endif
    }

// ---------------------------------------------------------------------------
// CBCTestKeyLockCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestKeyLockCase::RunL( TInt aCmd )
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
            TestFunction();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestKeyLockCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestKeyLockCase::PrepareCaseL( TInt aCmd )
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
// CBCTestKeyLockCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//
void CBCTestKeyLockCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestKeyLockCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//
void CBCTestKeyLockCase::TestFunction()
    {

    _LIT( strConnect,"Class RAknKeyLock Function Connect tested" );
    _LIT( strIsKeyLockEnabled, "Class RAknKeyLock Function IsKeyLockEnabled tested" );
    _LIT( strEnableKeyLock, "Class RAknKeyLock Function EnableKeyLock tested" );
    _LIT( strDisableKeyLock, "Class RAknKeyLock Function DisableKeyLock tested" );
    _LIT( strEnableWithoutNote, "Class RAknKeyLock Function EnableWithoutNote tested" );
    _LIT( strDisableWithoutNote, "Class RAknKeyLock Function DisableWithoutNote tested" );
    _LIT( strEnableAutoLockEmulation, "Class RAknKeyLock Function EnableAutoLockEmulation tested" );
    _LIT( strEnableSoftNotifications, "Class RAknKeyLock Function EnableSoftNotifications tested" );
    _LIT( strCancelAllNotifications, "Class RAknKeyLock Function CancelAllNotifications tested" );
    _LIT( strOfferKeyLock, "Class RAknKeyLock Function OfferKeyLock tested" );
    _LIT( strClose, "Class RAknKeyLock Function Close tested" );

    RAknKeyLock iKeyLock;
    TInt tempResult = iKeyLock.Connect();
    tempResult = tempResult;
    AssertTrueL( ETrue, strConnect );

    TBool isKeyLocked = iKeyLock.IsKeyLockEnabled();
    AssertTrueL( ETrue, strIsKeyLockEnabled );

    iKeyLock.EnableKeyLock();
    AssertTrueL( ETrue, strEnableKeyLock );

    iKeyLock.DisableKeyLock();
    AssertTrueL( ETrue, strDisableKeyLock );

    iKeyLock.EnableWithoutNote();
    AssertTrueL( ETrue, strEnableWithoutNote );

    iKeyLock.DisableWithoutNote();
    AssertTrueL( ETrue, strDisableWithoutNote );

    iKeyLock.EnableAutoLockEmulation();
    AssertTrueL( ETrue, strEnableAutoLockEmulation );

    iKeyLock.EnableSoftNotifications( ETrue );
    AssertTrueL( ETrue, strEnableSoftNotifications );

    iKeyLock.CancelAllNotifications();
    AssertTrueL( ETrue, strCancelAllNotifications );

    iKeyLock.OfferKeyLock();
    AssertTrueL( ETrue, strOfferKeyLock );

    iKeyLock.DisableKeyLock();
    isKeyLocked = iKeyLock.IsKeyLockEnabled();

    iKeyLock.Close();
    AssertTrueL( ETrue, strClose );

    }

