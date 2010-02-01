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
* Description:  for protected functions of CListBoxView
*
*/


#include "testsdklistslistboxview.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKLists::DoTestFlags
// -----------------------------------------------------------------------------
//
TInt CTestSDKListsListBoxView::DoTestFlags() const
    {
    return Flags();
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::DoTestSetFlags
// -----------------------------------------------------------------------------
//
void CTestSDKListsListBoxView::DoTestSetFlags(TInt aMask)
    {
    SetFlags( aMask );
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::DoTestClearFlags
// -----------------------------------------------------------------------------
//
void CTestSDKListsListBoxView::DoTestClearFlags(TInt aMask)
    {
    ClearFlags( aMask );
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::DoTestSelectRangeL
// -----------------------------------------------------------------------------
//
void CTestSDKListsListBoxView::DoTestSelectRangeL(TInt aItemIndex1, TInt aItemIndex2)
    {
    SelectRangeL( aItemIndex1, aItemIndex2 );
    }
