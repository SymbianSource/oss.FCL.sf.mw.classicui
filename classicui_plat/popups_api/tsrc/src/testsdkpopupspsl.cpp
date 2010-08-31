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
* Description:  test AknPopupSettingPage.h
*
*/


//  INCLUDES
#include <coecobs.h>
#include <aknpopupheadingpane.h>
#include <barsread.h>
#include <coemain.h>
#include <testsdkpopups.rsg>

#include "testsdkpopupspsl.h"
// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKPopupSPSL::CTestSDKPopupSPSL
// -----------------------------------------------------------------------------
CTestSDKPopupSPSL::CTestSDKPopupSPSL():CAknPopupSettingList()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupSPSL::~CTestSDKPopupSPSL
// -----------------------------------------------------------------------------
CTestSDKPopupSPSL::~CTestSDKPopupSPSL()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupSPSL::CreateMenuListL
// -----------------------------------------------------------------------------
void CTestSDKPopupSPSL::CreateMenuListL()
    {
    CAknPopupSettingList::CreateMenuListL();
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupSPSL::ActivateMenuListL
// -----------------------------------------------------------------------------
void CTestSDKPopupSPSL::ActivateMenuListL()
    {
    CAknPopupSettingList::ActivateMenuListL();
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupSPSL::ConfigureMenuListL
// -----------------------------------------------------------------------------
void CTestSDKPopupSPSL::ConfigureMenuListL()
    {
    CAknPopupSettingList::ConfigureMenuListL();
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupSPSL::DestroyMenuList
// -----------------------------------------------------------------------------
void CTestSDKPopupSPSL::DestroyMenuList()
    {
    CAknPopupSettingList::DestroyMenuList();
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupSPSL::DestroyMenuList
// -----------------------------------------------------------------------------
void CTestSDKPopupSPSL::HandleListBoxEventL( CEikListBox* aListBox, TListBoxEvent aEventType )
    {
    CAknPopupSettingList::HandleListBoxEventL( aListBox, aEventType );
    }
