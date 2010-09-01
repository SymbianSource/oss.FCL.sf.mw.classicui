/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  view class for test
*
*/


#include <coeaui.h>
#include <eikenv.h>

#include <testsdkuifwutil.rsg>

#include "testsdkuifwutilview.h"
#include "testsdkuifwutilcontainer.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestUiFwUtilView::NewL
// -----------------------------------------------------------------------------
//
CTestUiFwUtilView* CTestUiFwUtilView::NewL()
    {
    CTestUiFwUtilView* self = new ( ELeave ) CTestUiFwUtilView;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CTestUiFwUtilView::CTestUiFwUtilView
// -----------------------------------------------------------------------------
//
CTestUiFwUtilView::CTestUiFwUtilView(){}

// -----------------------------------------------------------------------------
// CTestUiFwUtilView::~CTestUiFwUtilView
// -----------------------------------------------------------------------------
//
CTestUiFwUtilView::~CTestUiFwUtilView()
    {
    if ( iContainer )
        {
        CCoeEnv::Static()->AppUi()->RemoveFromViewStack( *this, iContainer );
        delete iContainer;
        }
    }

// -----------------------------------------------------------------------------
// CTestUiFwUtilView::Id
// -----------------------------------------------------------------------------
//
TUid CTestUiFwUtilView::Id() const
    {
    return KCTestUiFwUtilViewId;
    }

// -----------------------------------------------------------------------------
// CTestUiFwUtilView::ConstructL
// -----------------------------------------------------------------------------
//
void CTestUiFwUtilView::ConstructL()
    {
    BaseConstructL( R_TEST_VIEW );
    TRect rect = CEikonEnv::Static()->AppUiFactory()->ClientRect();
    iContainer = CTestUiFwUtilContainer::NewL( rect );
    CCoeEnv::Static()->AppUi()->AddToStackL( *this, iContainer );
    }

// -----------------------------------------------------------------------------
// CTestUiFwUtilView::DoActivateL
// -----------------------------------------------------------------------------
//
void CTestUiFwUtilView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,
    const TDesC8& /*aCustomMessage*/)
    {
    }

// -----------------------------------------------------------------------------
// CTestUiFwUtilView::DoDeactivate
// -----------------------------------------------------------------------------
//
void CTestUiFwUtilView::DoDeactivate()
    {
    CCoeEnv::Static()->AppUi()->RemoveFromViewStack( *this, iContainer );
    delete iContainer;
    iContainer = NULL;
    }
// -----------------------------------------------------------------------------
// CTestUiFwUtilView::GetContainer
// -----------------------------------------------------------------------------
//
CTestUiFwUtilContainer* CTestUiFwUtilView::GetContainer()
    {
    return iContainer;
    }

