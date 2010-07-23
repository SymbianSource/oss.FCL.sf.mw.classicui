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
* Description:  test protected for CListItemDrawer
*
*/

#include "testsdklistslistitemdrawer.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKListsListItemDrawer::CTestSDKListsListItemDrawer()
// -----------------------------------------------------------------------------
//
CTestSDKListsListItemDrawer::CTestSDKListsListItemDrawer()
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKListsListItemDrawer::~CTestSDKListsListItemDrawer()
// -----------------------------------------------------------------------------
//
CTestSDKListsListItemDrawer::~CTestSDKListsListItemDrawer()
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKListsListItemDrawer::ResetGc()
// -----------------------------------------------------------------------------
//
void CTestSDKListsListItemDrawer::ResetGc() const
    {
    CListItemDrawer::ResetGc();
    }

// -----------------------------------------------------------------------------
// CTestSDKListsListItemDrawer::VerticalInterItemGap()
// -----------------------------------------------------------------------------
//
TInt CTestSDKListsListItemDrawer::VerticalInterItemGap() const
    {
    return CListItemDrawer::VerticalInterItemGap();
    }

// -----------------------------------------------------------------------------
// CTestSDKListsListItemDrawer::SetupGc()
// -----------------------------------------------------------------------------
//
void CTestSDKListsListItemDrawer::SetupGc(TInt aItemIndex) const
    {
    CListItemDrawer::SetupGc( aItemIndex );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsListItemDrawer::DrawActualItem()
// -----------------------------------------------------------------------------
//
void CTestSDKListsListItemDrawer::DrawActualItem(TInt /*aItemIndex*/, 
                                                 const TRect& /*aActualItemRect*/, 
                                                 TBool /*aItemIsCurrent*/, 
                                                 TBool /*aViewIsEmphasized*/, 
                                                 TBool /*aViewIsDimmed*/, 
                                                 TBool /*aItemIsSelected*/) const
    {
    }
