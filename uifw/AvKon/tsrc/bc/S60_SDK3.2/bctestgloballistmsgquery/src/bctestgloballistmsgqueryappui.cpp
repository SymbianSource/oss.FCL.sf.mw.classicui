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
* Description:  AppUI implementation for BCTestGlobalListMsgQuery.
*
*/

#include <avkon.hrh>
#include <aknsutils.h>

#include "bctestgloballistmsgqueryappui.h"
#include "bctestgloballistmsgquery.hrh"
#include "bctestgloballistmsgqueryview.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryAppUi::CBCTestGlobalListMsgQueryAppUi()
// ---------------------------------------------------------------------------
//
CBCTestGlobalListMsgQueryAppUi::CBCTestGlobalListMsgQueryAppUi()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryAppUi::ConstructL()
// ---------------------------------------------------------------------------
//
void CBCTestGlobalListMsgQueryAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );
    // init view
    CBCTestGlobalListMsgQueryView* view = CBCTestGlobalListMsgQueryView::NewL();
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );

    ActivateLocalViewL( view->Id() );
    }

// ----------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryAppUi::~CBCTestGlobalListMsgQueryAppUi()
// ----------------------------------------------------------------------------
//
CBCTestGlobalListMsgQueryAppUi::~CBCTestGlobalListMsgQueryAppUi()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryAppUi::HandleCommandL()
// ----------------------------------------------------------------------------
//
void CBCTestGlobalListMsgQueryAppUi::HandleCommandL( TInt aCommand )
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

// End of file
