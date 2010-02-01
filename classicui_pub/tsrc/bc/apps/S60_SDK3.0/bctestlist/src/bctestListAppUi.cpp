/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Avkon list test application
*
*/









#include <avkon.hrh>

#include <aknsutils.h>

#include "bctestlist.hrh"
#include "bctestlistAppUi.h"                                        
#include "bctestlistview.h"

// ================= MEMBER FUNCTIONS =========================================
//
// ----------------------------------------------------------------------------
// CBCTestListAppUi::CBCTestListAppUi()
// Default constructor.
// ----------------------------------------------------------------------------
//
CBCTestListAppUi::CBCTestListAppUi()
    {
    }

// ----------------------------------------------------------------------------
// void CBCTestListAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// Creates view class object.
// ----------------------------------------------------------------------------
void CBCTestListAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );
    
    CBCTestListView* view = CBCTestListView::NewL();
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );    
    
    ActivateLocalViewL( view->Id() );   
    }

// ----------------------------------------------------------------------------
// CBCTestListAppUi::~CBCTestListAppUi()
// Destructor
// ----------------------------------------------------------------------------
CBCTestListAppUi::~CBCTestListAppUi()
    {
    }

// ----------------------------------------------------------------------------
// void CBCTestListAppUi::HandleCommandL( TInt )
// Handles the commands.
// ----------------------------------------------------------------------------
void CBCTestListAppUi::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
        case EEikCmdExit:
            Exit();
            break;
        
        default:
            break;
        }
    }

// End of File
