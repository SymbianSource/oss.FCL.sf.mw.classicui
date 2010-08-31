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
* Description:  Test akncheckboxsettingpage.h
*
*/


//INCLUDE
#include "testakncheckboxsettingpageprotected.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestCheckBoxSettingPage::CTestCheckBoxSettingPage
// -----------------------------------------------------------------------------
//
CTestCheckBoxSettingPage::CTestCheckBoxSettingPage( TInt aResourceID, 
    CSelectionItemList* aItemArray ):CAknCheckBoxSettingPage( aResourceID, aItemArray )
    {
    
    }

// -----------------------------------------------------------------------------
//CTestCheckBoxSettingPage::CTestCheckBoxSettingPage
// -----------------------------------------------------------------------------
//
CTestCheckBoxSettingPage::CTestCheckBoxSettingPage( const TDesC* aSettingTitleText, 
        TInt aSettingNumber, 
        TInt aControlType,
        TInt aEditorResourceId, 
        TInt aSettingPageResourceId,
        CSelectionItemList* aItemArray ):CAknCheckBoxSettingPage( aSettingTitleText,
            aSettingNumber, 
            aControlType,
            aEditorResourceId, 
            aSettingPageResourceId,
            aItemArray )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestCheckBoxSettingPage::~CTestCheckBoxSettingPage
// -----------------------------------------------------------------------------
//
CTestCheckBoxSettingPage::~CTestCheckBoxSettingPage()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestCheckBoxSettingPage::TestUpdateSettingL
// -----------------------------------------------------------------------------
//
void CTestCheckBoxSettingPage::TestUpdateSettingL()
    {
    UpdateSettingL();
    }

// -----------------------------------------------------------------------------
// CTestCheckBoxSettingPage::TestDynamicInitL
// -----------------------------------------------------------------------------
//
void CTestCheckBoxSettingPage::TestDynamicInitL()
    {
    DynamicInitL();
    }

// -----------------------------------------------------------------------------
// CTestCheckBoxSettingPage::TestProcessCommandL
// -----------------------------------------------------------------------------
//
void CTestCheckBoxSettingPage::TestProcessCommandL(TInt aCommandId)
    {
    ProcessCommandL( aCommandId );
    }

// -----------------------------------------------------------------------------
// CTestCheckBoxSettingPage::TestSelectCurrentItemL
// -----------------------------------------------------------------------------
//
void CTestCheckBoxSettingPage::TestSelectCurrentItemL()
    {
    SelectCurrentItemL();
    }

// -----------------------------------------------------------------------------
// CTestCheckBoxSettingPage::TestWriteInternalStateL
// -----------------------------------------------------------------------------
//
void CTestCheckBoxSettingPage::TestWriteInternalStateL(RWriteStream& aWriteStream) const
    {
    WriteInternalStateL( aWriteStream );
    }

//End file

