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
* Description:         test bc for servicehandler control api(s)
*
*/








#include <avkon.hrh>
#include <aknsutils.h>
#include <aiwservicehandler.h>

#include "bctestservicehandlerAppUi.h"
#include "bctestservicehandler.hrh"
#include "bctestservicehandlerview.h"
#include "bctestutil.h"
#include "bctestservicehandlercase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// ctro do nothing
// ---------------------------------------------------------------------------
//
CBCTestServiceHandlerAppUi::CBCTestServiceHandlerAppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase ctor
// ---------------------------------------------------------------------------
//
void CBCTestServiceHandlerAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

    // init view
    CBCTestServiceHandlerView* view = CBCTestServiceHandlerView::NewL();
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );    
    
    ActivateLocalViewL( view->Id() );
    }

// ----------------------------------------------------------------------------
// CBCTestServiceHandlerAppUi::~CBCTestServiceHandlerAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestServiceHandlerAppUi::~CBCTestServiceHandlerAppUi()
    {
    }

// ----------------------------------------------------------------------------
// handle menu command events
// ----------------------------------------------------------------------------
//
void CBCTestServiceHandlerAppUi::HandleCommandL( TInt aCommand )
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
