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
* Description:  test aknpopupfader.h aknpopupfield.h aknpopupsettingpage.h
*
*/


//  INCLUDES

#include <coecobs.h>
#include <aknpopupheadingpane.h>
#include <barsread.h>
#include <coemain.h>
#include <testsdkpopups.rsg>

#include "testsdkpopupspf.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKPopupsPF::CountFadedComponents
// -----------------------------------------------------------------------------
TInt CTestSDKPopupsPF::CountFadedComponents()
    {
    return MAknFadedComponent::CountFadedComponents();
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPF::FadedComponent
// -----------------------------------------------------------------------------
CCoeControl* CTestSDKPopupsPF::FadedComponent( TInt aIndex )
    {
    return MAknFadedComponent::FadedComponent( aIndex );
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPF::FadedComponent
// -----------------------------------------------------------------------------
CTestSDKPopupsPF::CTestSDKPopupsPF()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPF::~CTestSDKPopupsPF
// -----------------------------------------------------------------------------
CTestSDKPopupsPF::~CTestSDKPopupsPF()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPF::HandlePopupFieldEventL
// -----------------------------------------------------------------------------
void CTestSDKPopupsPF::HandlePopupFieldEventL ( CAknPopupField* /*aPopupField*/, 
         TAknPopupFieldEvent /*aEventType*/, TInt /*aHint*/ )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPF::HandlePopupFieldEventL
// -----------------------------------------------------------------------------
void CTestSDKPopupsPF::HandlePopupSettingListEventL( CAknPopupSettingList* /*aPopupSettingList*/, 
             TAknPopupSettingListEvent /*aEventType*/, TInt /*aHint*/ )
    {
    
    }
