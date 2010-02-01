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
* Description:         appui
*
*/








#include <avkon.hrh>
#include <aknsutils.h>

#include "bctesttoolbarappui.h"
#include "bctesttoolbar.hrh"
#include "bctesttoolbarview.h"

// ======== MEMBER FUNCTIONS ========

// --------------------------------------------------------------------------
// ctro do nothing
// --------------------------------------------------------------------------
//
CBCTestToolBarAppUi::CBCTestToolBarAppUi()
    {
    }

// --------------------------------------------------------------------------
// symbian 2nd phase ctor
// --------------------------------------------------------------------------
//
void CBCTestToolBarAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

    // init view
    CBCTestToolBarView* view = CBCTestToolBarView::NewL();
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );    
    
    ActivateLocalViewL( view->Id() );
    }

// --------------------------------------------------------------------------
// CBCTestToolBarAppUi::~CBCTestToolBarAppUi()
// Destructor.
// --------------------------------------------------------------------------
//
CBCTestToolBarAppUi::~CBCTestToolBarAppUi()
    { 
    }

// --------------------------------------------------------------------------
// handle menu command events
// --------------------------------------------------------------------------
//
void CBCTestToolBarAppUi::HandleCommandL( TInt aCommand )
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
