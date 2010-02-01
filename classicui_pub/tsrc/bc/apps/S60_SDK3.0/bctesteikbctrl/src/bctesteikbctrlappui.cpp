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
* Description:         test bc for eikbctrl control api(s)
*
*/









#include <avkon.hrh>
#include <aknsutils.h>

#include "bctesteikbctrlAppUi.h"
#include "bctesteikbctrl.hrh"
#include "bctesteikbctrlview.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// ctro do nothing
// ---------------------------------------------------------------------------
//
CBCTesteikbctrlAppUi::CBCTesteikbctrlAppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase ctor
// ---------------------------------------------------------------------------
//
void CBCTesteikbctrlAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

    // init view
    CBCTesteikbctrlView* view = CBCTesteikbctrlView::NewL();
    CleanupStack::PushL( view ); 
    AddViewL( view );
    CleanupStack::Pop( view );     
    
    ActivateLocalViewL( view->Id() );
    }

// ----------------------------------------------------------------------------
// CBCTesteikbctrlAppUi::~CBCTesteikbctrlAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTesteikbctrlAppUi::~CBCTesteikbctrlAppUi()
    { 
    }

// ----------------------------------------------------------------------------
// handle menu command events
// ----------------------------------------------------------------------------
//
void CBCTesteikbctrlAppUi::HandleCommandL( TInt aCommand )
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
