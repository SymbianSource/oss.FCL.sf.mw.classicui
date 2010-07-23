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
#include <testsdkprivateuiframework.rsg>

#include "testsdkprivateuiframework.h"
#include "testsdkprivateuiframework.hrh"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestDKHandlePointerEventL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestDKHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CCoeControl *cControl = new ( ELeave ) CCoeControl();
    CleanupStack::PushL( cControl );
    TPointerEvent pointerEvent;
    CEikDebugKeys * eikalert = static_cast <CEikDebugKeys*> ( cControl );
    eikalert->CEikDebugKeys::HandlePointerEventL( pointerEvent );
    CleanupStack::PopAndDestroy( cControl );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestDWHandlePointerEventL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestDWHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CCoeControl *cControl = new ( ELeave ) CCoeControl();
    CleanupStack::PushL( cControl );
    TPointerEvent pointerEvent;
    CEikDebugWin * eikalert = static_cast <CEikDebugWin*> ( cControl );
    eikalert->CEikDebugWin::HandlePointerEventL( pointerEvent );
    CleanupStack::PopAndDestroy( cControl );
    return KErrNone;
    }

// End of File


