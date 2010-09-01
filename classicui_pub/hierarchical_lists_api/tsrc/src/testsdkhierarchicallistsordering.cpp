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
* Description:  test akntreelist.h
*
*/


// [INCLUDE FILES]

#include "testsdkhierarchicallistsordering.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKOrdering::CTestSDKOrdering
// -----------------------------------------------------------------------------
//
CTestSDKOrdering::CTestSDKOrdering()
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKOrdering::~CTestSDKOrdering
// -----------------------------------------------------------------------------
//
CTestSDKOrdering::~CTestSDKOrdering()
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKOrdering::Compare
// -----------------------------------------------------------------------------
//
TInt CTestSDKOrdering::Compare( TAknTreeItemID /*aFirst*/, TAknTreeItemID /*aSecond*/ )
    {
    return 1;
    }

// -----------------------------------------------------------------------------
// CTestSDKOrdering::HandleTreeListEvent
// -----------------------------------------------------------------------------
//
TInt CTestSDKOrdering::HandleTreeListEvent( CAknTreeList& /*aList*/, 
                                            TAknTreeItemID /*aItem*/, TEvent /*aEvent*/ )
    {
    return 0;
    }
