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
* Description:         test bc for screenclearer control api(s)
*
*/








#include <avkon.hrh>
#include <aknsutils.h>

#include "bctestscreenclearerappui.h"
#include "bctestscreenclearer.hrh"
#include "bctestscreenclearerview.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// ctro do nothing
// ---------------------------------------------------------------------------
//
CBCTestScreenClearerAppUi::CBCTestScreenClearerAppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase ctor
// ---------------------------------------------------------------------------
//
void CBCTestScreenClearerAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

    // init view
    CBCTestScreenClearerView* view = CBCTestScreenClearerView::NewL();
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );    
    
    ActivateLocalViewL( view->Id() );
    }

// ----------------------------------------------------------------------------
// CBCTestScreenClearerAppUi::~CBCTestScreenClearerAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestScreenClearerAppUi::~CBCTestScreenClearerAppUi()
    { 
    }

// ----------------------------------------------------------------------------
// handle menu command events
// ----------------------------------------------------------------------------
//
void CBCTestScreenClearerAppUi::HandleCommandL( TInt aCommand )
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


