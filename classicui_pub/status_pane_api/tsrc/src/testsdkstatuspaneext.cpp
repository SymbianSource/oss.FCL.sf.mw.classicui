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


#include "testsdkstatuspaneext.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKStatusPaneEXT::CTestSDKStatusPaneEXT
// -----------------------------------------------------------------------------
CTestSDKStatusPaneEXT::CTestSDKStatusPaneEXT( CEikonEnv& aEikEnv, 
            RWindowGroup* aParent ):CEikStatusPaneBase( aEikEnv, aParent )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPaneEXT::~CTestSDKStatusPaneEXT
// -----------------------------------------------------------------------------
CTestSDKStatusPaneEXT::~CTestSDKStatusPaneEXT()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPaneEXT::BaseConstructL
// -----------------------------------------------------------------------------
void CTestSDKStatusPaneEXT::BaseConstructL( TInt aCoreResId )
    {
    CEikStatusPaneBase::BaseConstructL( aCoreResId );
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPaneEXT::CreateModelL
// -----------------------------------------------------------------------------
CEikStatusPaneModelBase* CTestSDKStatusPaneEXT::CreateModelL( TInt /*aCoreResId*/ ) const 
    {
    return iModel;
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPaneEXT::Rect
// -----------------------------------------------------------------------------
TRect CTestSDKStatusPaneEXT::Rect() const
    {
    return CEikStatusPaneBase::Rect();
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPaneEXT::DisableClearer
// -----------------------------------------------------------------------------
void CTestSDKStatusPaneEXT::DisableClearer( TBool aDisabled )
    {
    CEikStatusPaneBase::DisableClearer( aDisabled );
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPaneEXT::CommonPrepareForAppExit
// -----------------------------------------------------------------------------
void CTestSDKStatusPaneEXT::CommonPrepareForAppExit()
    {
    CEikStatusPaneBase::CommonPrepareForAppExit();
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPaneEXT::CommonPrepareForAppExit
// -----------------------------------------------------------------------------
TBool CTestSDKStatusPaneEXT::IsApp() const
    {
    return ETrue;
    }
// End of file

