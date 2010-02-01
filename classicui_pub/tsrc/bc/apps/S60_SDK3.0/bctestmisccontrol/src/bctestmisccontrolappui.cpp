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
* Description:         Implements test bc for misc control appui.
*
*/








#include <avkon.hrh>
#include <aknsutils.h> 

#include "bctestmisccontrolappui.h"
#include "bctestmisccontrol.hrh" 
#include "bctestmisccontrolview.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// ctro do nothing
// ---------------------------------------------------------------------------
//
CBCTestMiscControlAppUi::CBCTestMiscControlAppUi()
    { 
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase ctor
// ---------------------------------------------------------------------------
//
void CBCTestMiscControlAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

    // init view
    CBCTestMiscControlView* view = CBCTestMiscControlView::NewL();
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );

    ActivateLocalViewL( view->Id() );
    }

// ----------------------------------------------------------------------------
// CBCTestMiscControlAppUi::~CBCTestMiscControlAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestMiscControlAppUi::~CBCTestMiscControlAppUi()
    {
    }

// ----------------------------------------------------------------------------
// handle menu command events
// ----------------------------------------------------------------------------
//
void CBCTestMiscControlAppUi::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EEikCmdExit:
        case EAknSoftkeyExit:
            {
            Exit();
            return;
            }
        default:
            break;
        }
    }
