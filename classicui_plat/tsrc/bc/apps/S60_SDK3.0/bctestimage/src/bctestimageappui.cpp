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

#include "bctestimageAppUi.h"
#include "bctestimage.hrh"
#include "bctestimageview.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// ctro do nothing
// ---------------------------------------------------------------------------
//
CBCTestImageAppUi::CBCTestImageAppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase ctor
// ---------------------------------------------------------------------------
//
void CBCTestImageAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

    // init view
    CBCTestImageView* view = CBCTestImageView::NewL();
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );    
    
    ActivateLocalViewL( view->Id() );
    }

// ----------------------------------------------------------------------------
// CBCTestImageAppUi::~CBCTestImageAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestImageAppUi::~CBCTestImageAppUi()
    { 
    }

// ----------------------------------------------------------------------------
// handle menu command events
// ----------------------------------------------------------------------------
//
void CBCTestImageAppUi::HandleCommandL( TInt aCommand )
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
