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
* Description:  test eikspane.h
*
*/


#include "testsdkstatuspanepane.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKStatusPanePane::NewL
// -----------------------------------------------------------------------------
CTestSDKStatusPanePane* CTestSDKStatusPanePane::NewL( CEikonEnv& aEikEnv, 
        RWindowGroup* aParent, TInt aCoreStatusPaneModelResId )
    {
    return static_cast<CTestSDKStatusPanePane*>( CEikStatusPane::NewL( aEikEnv, 
            aParent, aCoreStatusPaneModelResId ) );
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPanePane::Rect
// -----------------------------------------------------------------------------
TRect CTestSDKStatusPanePane::Rect() const
    {
    return CEikStatusPaneBase::Rect();
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPanePane::DisableClearer
// -----------------------------------------------------------------------------
void CTestSDKStatusPanePane::DisableClearer( TBool aDisabled )
    {
    CEikStatusPaneBase::DisableClearer( aDisabled );
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPanePane::CommonPrepareForAppExit
// -----------------------------------------------------------------------------
void CTestSDKStatusPanePane::CommonPrepareForAppExit()
    {
    CEikStatusPaneBase::CommonPrepareForAppExit();
    }
// End of file

