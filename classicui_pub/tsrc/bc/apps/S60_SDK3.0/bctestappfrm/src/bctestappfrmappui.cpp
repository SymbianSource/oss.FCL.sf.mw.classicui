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
#include "bctestappfrmappui.h"
#include "bctestappfrm.hrh"
#include "bctestappfrmview.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// ctro do nothing
// ---------------------------------------------------------------------------
//
CBCTestAppFrmAppUi::CBCTestAppFrmAppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase ctor
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

    // init view
    CBCTestAppFrmView* view = CBCTestAppFrmView::NewL(this);
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );    
    
    ActivateLocalViewL( view->Id() );
    }

// ----------------------------------------------------------------------------
// CBCTestAppFrmAppUi::~CBCTestAppFrmAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestAppFrmAppUi::~CBCTestAppFrmAppUi()
    { 
    }

// ----------------------------------------------------------------------------
// handle menu command events
// ----------------------------------------------------------------------------
//
void CBCTestAppFrmAppUi::HandleCommandL( TInt aCommand )
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

void CBCTestAppFrmAppUi::HandleStatusPaneSizeChange(){
    CAknViewAppUi::HandleStatusPaneSizeChange();
}

void CBCTestAppFrmAppUi::AppFrm_SetKeyBlockMode()
{
    SetKeyBlockMode(EDefaultBlockMode);
}

void CBCTestAppFrmAppUi::AppFrm_HandleStatusPaneSizeChange()
{
    CAknAppUi::HandleStatusPaneSizeChange();
}

void CBCTestAppFrmAppUi::AppFrm_HandleApplicationSpecificEventL(TInt aType,
        const TWsEvent& aEvent)
{
    CAknAppUiBase::HandleApplicationSpecificEventL(aType,aEvent);
}

void CBCTestAppFrmAppUi::AppFrm_HandleScreenDeviceChangedL()
{
    CAknAppUiBase::HandleScreenDeviceChangedL();
}

void CBCTestAppFrmAppUi::AppFrm_ReplaceKeySoundsL(TInt aUid)
{
    CAknAppUiBase::ReplaceKeySoundsL(aUid);
}
