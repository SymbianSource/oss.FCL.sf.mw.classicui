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
* Description:         test bc for template control api(s)
*
*/








#include <avkon.hrh>
#include <aknsutils.h>

#include "bctestfontinputAppUi.h"
#include "bctestfontinput.hrh"
#include "bctestfontinputview.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// ctro do nothing 
// ---------------------------------------------------------------------------
//
CBCTestFontInputAppUi::CBCTestFontInputAppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase ctor
// ---------------------------------------------------------------------------
// 
void CBCTestFontInputAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

    // init view
    CBCTestFontInputView* view = CBCTestFontInputView::NewL();
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );

    ActivateLocalViewL( view->Id() );
    }

// ----------------------------------------------------------------------------
// CBCTestFontInputAppUi::~CBCTestFontInputAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestFontInputAppUi::~CBCTestFontInputAppUi()
    {
    }

// ----------------------------------------------------------------------------
// handle menu command events
// ----------------------------------------------------------------------------
//
void CBCTestFontInputAppUi::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
        case EEikCmdExit:
            {
            Exit();
            return;
            }
        default:
            break;
        }
    }

// End of File
