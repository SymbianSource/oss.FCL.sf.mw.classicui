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
* Description:  test options_menu_api
 *
*/


#include <e32base.h>
#include "testoptionsmenu.h"
#include "testsdkoptionsmenu.h"


// -----------------------------------------------------------------------------
// CTestOptionsMenu::CTestOptionsMenu
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//

CTestOptionsMenu::CTestOptionsMenu( MEikMenuObserver* aObserver ):CEikMenuPane( aObserver )
{
}
// -----------------------------------------------------------------------------
// CTestOptionsMenu::~CTestOptionsMenu
// Destructor.
// -----------------------------------------------------------------------------
//
CTestOptionsMenu::~CTestOptionsMenu()
{
}
// -----------------------------------------------------------------------------
// CTestOptionsMenu::DoDraw
// -----------------------------------------------------------------------------
//
void CTestOptionsMenu::DoDraw( const TRect& aRect )
    {
    Draw( aRect );
    }
// -----------------------------------------------------------------------------
// CTestOptionsMenu::DoFocusChanged
// -----------------------------------------------------------------------------
//
void CTestOptionsMenu::DoFocusChanged( TDrawNow aDrawNow )
    {
    FocusChanged( aDrawNow );
    }
// -----------------------------------------------------------------------------
// CTestOptionsMenu::DoConstructFromResourceL
// -----------------------------------------------------------------------------
//
void CTestOptionsMenu::DoConstructFromResourceL( TResourceReader& aReader )
    {
    ConstructFromResourceL( aReader );
    }
// -----------------------------------------------------------------------------
// CTestOptionsMenuMop::DoMopSupplyObject
// -----------------------------------------------------------------------------
//
TTypeUid::Ptr CTestOptionsMenuMop::DoMopSupplyObject( TTypeUid aId )
    {
    return MopSupplyObject( aId );
    }

// -----------------------------------------------------------------------------
// CTestOptionsMenuMop::CTestOptionsMenuMop
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//

CTestOptionsMenuMop::CTestOptionsMenuMop( MEikMenuObserver* aMenuObserver ):CEikMenuPane( aMenuObserver )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestOptionsMenuMop::~CTestOptionsMenuMop
// Destructor.
// -----------------------------------------------------------------------------
//
CTestOptionsMenuMop::~CTestOptionsMenuMop()
    {
    
    }
// -----------------------------------------------------------------------------
// CTestOptionsMenu::DoActivateGc
// -----------------------------------------------------------------------------
//
void CTestOptionsMenu::DoActivateGc()
    {
    ActivateGc();
    }
// -----------------------------------------------------------------------------
// CTestOptionsMenu::DoDeactivateGc
// -----------------------------------------------------------------------------
//
void CTestOptionsMenu::DoDeactivateGc()
    {
    DeactivateGc();
    }

//end of file
