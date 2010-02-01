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
* Description:  
*
*/

#include "testdompslnfwbv.h"

#include "testdompslnfwappui.h"

//===============================CTestDOMPslnFWAppUi==========================
//
// ---------------------------------------------------------------------------
// CTestDOMPslnFWAppUi::CTestDOMPslnFWAppUi()
// ---------------------------------------------------------------------------
//  
CTestDOMPslnFWAppUi::CTestDOMPslnFWAppUi()
    {

    }

// ---------------------------------------------------------------------------
// CTestDOMPslnFWAppUi::~CTestDOMPslnFWAppUi()
// ---------------------------------------------------------------------------
//  
CTestDOMPslnFWAppUi::~CTestDOMPslnFWAppUi()
    {
    delete iFWBView;
    iFWBView = NULL;
    }

void CTestDOMPslnFWAppUi::InitializeContainersL()
    {
    iFWBView = new( ELeave ) CTestPslnFWBaseView();
    AddViewL( iFWBView );
    SetDefaultViewL( *iFWBView );
    }

// ---------------------------------------------------------------------------
// CTestDOMPslnFWAppUi::HandleCommandL()
// ---------------------------------------------------------------------------
//  
void CTestDOMPslnFWAppUi::HandleCommandL( TInt aCommand )
    {
    TBool commandHandled = EFalse;
    switch ( aCommand )
        {
        default:
            break;
        }
    
        
    if ( !commandHandled ) 
        {
        if ( aCommand == EAknSoftkeyExit || aCommand == EEikCmdExit )
            {
            Exit();
            }
        }
    }

// ---------------------------------------------------------------------------
// CTestDOMPslnFWAppUi::HandleResourceChangeL()
// ---------------------------------------------------------------------------
//  
void CTestDOMPslnFWAppUi::HandleResourceChangeL( TInt aType )
    {
    CAknViewAppUi::HandleResourceChangeL( aType );
    
    }
                
// ---------------------------------------------------------------------------
// CTestDOMPslnFWAppUi::HandleKeyEventL()
// ---------------------------------------------------------------------------
//  
TKeyResponse CTestDOMPslnFWAppUi::HandleKeyEventL(
        const TKeyEvent& /*aKeyEvent*/, TEventCode /*aType*/ )
    {
    return EKeyWasNotConsumed;
    }

// ---------------------------------------------------------------------------
// CTestDOMPslnFWAppUi::HandleViewDeactivation()
// ---------------------------------------------------------------------------
//  
void CTestDOMPslnFWAppUi::HandleViewDeactivation( 
        const TVwsViewId& aViewIdToBeDeactivated, 
        const TVwsViewId& aNewlyActivatedViewId )
    {
    CAknViewAppUi::HandleViewDeactivation( 
            aViewIdToBeDeactivated, 
            aNewlyActivatedViewId );
    }

// ---------------------------------------------------------------------------
// CTestDOMPslnFWAppUi::ConstructL()
// ---------------------------------------------------------------------------
//  
void CTestDOMPslnFWAppUi::ConstructL()
    {
    BaseConstructL( ); 
    InitializeContainersL();
    iFWBView->HandleCommandL( 0 );
    }

