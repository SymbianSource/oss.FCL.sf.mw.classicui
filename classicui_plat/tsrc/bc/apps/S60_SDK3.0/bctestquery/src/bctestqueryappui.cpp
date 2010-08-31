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
* Description:         AppUi
*
*/









#include <avkon.hrh>

#include <aknsutils.h>

#include "bctestquery.hrh"
#include "bctestqueryappui.h"                                        
#include "bctestqueryview.h"
#include "bctestutil.h"

// ================= MEMBER FUNCTIONS =========================================
//
// ----------------------------------------------------------------------------
// CBCTestQueryAppUi::CBCTestQueryAppUi()
// Default constructor.
// ----------------------------------------------------------------------------
//
CBCTestQueryAppUi::CBCTestQueryAppUi()
    {
    }

// ----------------------------------------------------------------------------
// void CBCTestQueryAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// Creates view class object.
// ----------------------------------------------------------------------------
void CBCTestQueryAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );
    
    iTestUtil = CBCTestUtil::NewL();
    
    CBCTestQueryView* view = CBCTestQueryView::NewL( iTestUtil );
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );    
    
    ActivateLocalViewL( view->Id() );
    
    }

// ----------------------------------------------------------------------------
// CBCTestQueryAppUi::~CBCTestQueryAppUi()
// Destructor
// ----------------------------------------------------------------------------
CBCTestQueryAppUi::~CBCTestQueryAppUi()
    {
    delete iTestUtil;
    }

// ----------------------------------------------------------------------------
// void CBCTestQueryAppUi::HandleCommandL( TInt )
// Handles the commands.
// ----------------------------------------------------------------------------
void CBCTestQueryAppUi::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
        case EEikCmdExit:
            Exit();
            break;
        case EProgCmdAutoTest:
            iTestUtil->RunL();
            break;
        }
    }

