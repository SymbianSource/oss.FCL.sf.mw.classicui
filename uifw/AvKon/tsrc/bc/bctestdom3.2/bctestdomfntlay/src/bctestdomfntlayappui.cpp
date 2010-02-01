/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  bctestdomfntlay control api(s)
 *
*/

#include <avkon.hrh>
#include <aknsutils.h>

#include "bctestdomfntlayappui.h"
#include "bctestdomfntlay.hrh"
#include "bctestdomfntlayview.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// ctro do nothing
// ---------------------------------------------------------------------------
//
CBCTestDomFntlayAppUi::CBCTestDomFntlayAppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase ctor
// ---------------------------------------------------------------------------
//
void CBCTestDomFntlayAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

    // init view
    CBCTestDomFntlayView* view = CBCTestDomFntlayView::NewL();
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );    
    
    ActivateLocalViewL( view->Id() );
    }

// ----------------------------------------------------------------------------
// CBCTestDomFntlayAppUi::~CBCTestDomFntlayAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestDomFntlayAppUi::~CBCTestDomFntlayAppUi()
    { 
    }

// ----------------------------------------------------------------------------
// handle menu command events
// ----------------------------------------------------------------------------
//
void CBCTestDomFntlayAppUi::HandleCommandL( TInt aCommand )
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
