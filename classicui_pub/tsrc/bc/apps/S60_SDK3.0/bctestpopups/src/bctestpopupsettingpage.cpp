/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Implements test bc for popup field text testcase.
*
*/









#include <aknquerydialog.h>
#include <eikenv.h>

#include "bctestpopupsettingpage.h"
#include "bctestcase.h"
#include "bctestpopups.hrh"  

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestPopupSettingPage::CBCTestPopupSettingPage(
    const TInt aResourceId,
    CAknQueryValueText& aQueryValue )
    : CAknPopupSettingPage(aResourceId, aQueryValue)
    {
    }

CBCTestPopupSettingPage::CBCTestPopupSettingPage( 
        const TDesC* aSettingTitleText,
        TInt aSettingNumber,
        TInt aControlType,
        TInt aEditorResourceId,
        TInt aSettingPageResourceId,
        MAknQueryValue& aQueryValue )
    : CAknPopupSettingPage(
       aSettingTitleText,
       aSettingNumber,
       aControlType,
       aEditorResourceId,
       aSettingPageResourceId,
       aQueryValue)
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestPopupSettingPage::~CBCTestPopupSettingPage()
    {
    }

