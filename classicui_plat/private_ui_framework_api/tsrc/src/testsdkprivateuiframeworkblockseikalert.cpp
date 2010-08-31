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



// [INCLUDE FILES]
#include "testsdkprivateuiframework.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestEAHandlePointerEventL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestEAHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog *noteDialog = new ( ELeave )CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    TPointerEvent pointerEvent;
    pointerEvent.iType = TPointerEvent::EButton1Up;
    CEikAlert * eikalert = static_cast <CEikAlert*> ( noteDialog );
    STIF_ASSERT_NOT_NULL( eikalert );
    eikalert->CEikAlert::HandlePointerEventL( pointerEvent );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// End of File


