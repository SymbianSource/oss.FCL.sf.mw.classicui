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
* Description:  test private_ui_framework_api
*
*/


//Include
#include <e32base.h>

#include "testsdkprivateuiframework.h"
#include "testsdkprivateuiframobserver.h"


// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramObserver::CTestSdkPrivateUiFramObserver
// -----------------------------------------------------------------------------
//

CTestSdkPrivateUiFramObserver::CTestSdkPrivateUiFramObserver()
    {
    }
// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramObserver::~CTestSdkPrivateUiFramObserver
// -----------------------------------------------------------------------------
//
CTestSdkPrivateUiFramObserver::~CTestSdkPrivateUiFramObserver()
    {
    }


// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramObserver::CTestSdkPrivateUiFramButtonPanel
// -----------------------------------------------------------------------------
//

CTestSdkPrivateUiFramButtonPanel::CTestSdkPrivateUiFramButtonPanel()
    {
    }
// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramObserver::~CTestSdkPrivateUiFramButtonPanel
// -----------------------------------------------------------------------------
//
CTestSdkPrivateUiFramButtonPanel::~CTestSdkPrivateUiFramButtonPanel()
    {
    }
// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramObserver::~DoWriteInternalStateL
// -----------------------------------------------------------------------------
//
void CTestSdkPrivateUiFramButtonPanel::DoWriteInternalStateL( RWriteStream& aWriteStream  ) const
    {
    CEikButtonPanel::WriteInternalStateL( aWriteStream );
    }


// End of File


