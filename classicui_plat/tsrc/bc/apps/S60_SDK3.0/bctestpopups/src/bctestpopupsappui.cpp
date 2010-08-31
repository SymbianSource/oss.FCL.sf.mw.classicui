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
* Description:         Implements test bc for popups control appui.
*
*/








#include <avkon.hrh>
#include <aknsutils.h>

#include "bctestpopupsappui.h"
#include "bctestpopups.hrh"
#include "bctestpopupsview.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// ctro do nothing
// ---------------------------------------------------------------------------
//
CBCTestPopupsAppUi::CBCTestPopupsAppUi()
    { 
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase ctor
// ---------------------------------------------------------------------------
//
void CBCTestPopupsAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

    // init view
    CBCTestPopupsView* view = CBCTestPopupsView::NewL();
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );

    ActivateLocalViewL( view->Id() ); 
    }

// ----------------------------------------------------------------------------
// CBCTestPopupsAppUi::~CBCTestPopupsAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestPopupsAppUi::~CBCTestPopupsAppUi()
    {
    }

// ----------------------------------------------------------------------------
// handle menu command events
// ----------------------------------------------------------------------------
//
void CBCTestPopupsAppUi::HandleCommandL( TInt aCommand ) 
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
