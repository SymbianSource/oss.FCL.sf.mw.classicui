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
* Description:         Implements test bc for labelinfoindicators appui.
*
*/








#include <avkon.hrh>
#include <aknsutils.h>

#include "bctestlabelinfoindicatorsappui.h"
#include "bctestlabelinfoindicators.hrh" 
#include "bctestlabelinfoindicatorsview.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// ctro do nothing
// ---------------------------------------------------------------------------
//
CBCTestLabelInfoIndicatorsAppUi::CBCTestLabelInfoIndicatorsAppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase ctor
// ---------------------------------------------------------------------------
//
void CBCTestLabelInfoIndicatorsAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

    // init view
    CBCTestLabelInfoIndicatorsView* view = 
        CBCTestLabelInfoIndicatorsView::NewL();
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );

    ActivateLocalViewL( view->Id() );
    }

// ----------------------------------------------------------------------------
// CBCTestLabelInfoIndicatorsAppUi::~CBCTestLabelInfoIndicatorsAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestLabelInfoIndicatorsAppUi::~CBCTestLabelInfoIndicatorsAppUi()
    {
    }

// ----------------------------------------------------------------------------
// handle menu command events
// ----------------------------------------------------------------------------
//
void CBCTestLabelInfoIndicatorsAppUi::HandleCommandL( TInt aCommand )
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
