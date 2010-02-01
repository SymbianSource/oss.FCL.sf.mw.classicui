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
* Description:    Test aiwserviceifmenu
*
*/




#include "testserviceifmenuprotected.h"

// -----------------------------------------------------------------------------
// CServiceIfMenu::CServiceIfMenu
// -----------------------------------------------------------------------------
//
CTestServiceIfMenu::CTestServiceIfMenu()
{
}

// -----------------------------------------------------------------------------
// CServiceIfMenu::~CServiceIfMenu
// -----------------------------------------------------------------------------
//
CTestServiceIfMenu::~CTestServiceIfMenu()
{
}

// -----------------------------------------------------------------------------
// CServiceIfMenu::InitializeMenuPaneL
// -----------------------------------------------------------------------------
//
void CTestServiceIfMenu::InitializeMenuPaneL(
        CAiwMenuPane& /*aMenuPane*/,
        TInt /*aIndex*/,
        TInt /*aCascadeId*/,
        const CAiwGenericParamList& /*aInParamList*/)
    {
    
    }

// -----------------------------------------------------------------------------
// CServiceIfMenu::HandleMenuCmdL
// -----------------------------------------------------------------------------
//
void CTestServiceIfMenu::HandleMenuCmdL(
    TInt /*aMenuCmdId*/,
    const CAiwGenericParamList& /*aInParamList*/,
    CAiwGenericParamList& /*aOutParamList*/,
    TUint /*aCmdOptions*/,
    const MAiwNotifyCallback* /*aCallback*/)
    {
    
    }

// -----------------------------------------------------------------------------
// CServiceIfMenu::InitialiseL
// -----------------------------------------------------------------------------
//
void CTestServiceIfMenu::InitialiseL(
        MAiwNotifyCallback& /*aFrameworkCallback*/,
        const RCriteriaArray& /*aInterest*/)
    {
    
    }

// -----------------------------------------------------------------------------
// CServiceIfMenu::HandleServiceCmdL
// -----------------------------------------------------------------------------
//
void CTestServiceIfMenu::HandleServiceCmdL(
    const TInt& /*aCmdId*/,
    const CAiwGenericParamList& /*aInParamList*/,
    CAiwGenericParamList& /*aOutParamList*/,
    TUint /*aCmdOptions*/,
    const MAiwNotifyCallback* /*aCallback*/ )
    {
    
    }

// -----------------------------------------------------------------------------
// CServiceIfMenu::ExtensionInterface
// -----------------------------------------------------------------------------
//
void* CTestServiceIfMenu::ExtensionInterface(TUid /*aInterface*/)
    {
    return NULL;
    }
