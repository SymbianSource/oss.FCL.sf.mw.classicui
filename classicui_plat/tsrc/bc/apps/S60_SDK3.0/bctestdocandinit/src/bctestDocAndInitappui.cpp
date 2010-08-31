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
* Description:         test bc for DocAndInit control api(s)
*
*/








#include <avkon.hrh>
#include <aknsutils.h>

#include "bctestdocandinitAppUi.h"
#include "bctestdocandinit.hrh"
#include "bctestdocandinitview.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// ctro do nothing
// ---------------------------------------------------------------------------
//
CBCTestDocAndInitAppUi::CBCTestDocAndInitAppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase ctor
// ---------------------------------------------------------------------------
//
void CBCTestDocAndInitAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

    // init view
    CBCTestDocAndInitView* view = CBCTestDocAndInitView::NewL();
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );    
    
    ActivateLocalViewL( view->Id() );
    }

// ----------------------------------------------------------------------------
// CBCTestDocAndInitAppUi::~CBCTestDocAndInitAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestDocAndInitAppUi::~CBCTestDocAndInitAppUi()
    { 
    }

// ----------------------------------------------------------------------------
// handle menu command events
// ----------------------------------------------------------------------------
//
void CBCTestDocAndInitAppUi::HandleCommandL( TInt aCommand )
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
