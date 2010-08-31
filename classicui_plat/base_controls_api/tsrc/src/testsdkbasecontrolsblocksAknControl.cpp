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
* Description:  test api in akncontrols.h
*
*/



// [INCLUDE FILES]
#include "testsdkbasecontrols.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKBaseControls::TestCAknControlContructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKBaseControls::TestCAknControlContructorL( CStifItemParser& /*aItem*/ )
    {
    CAknControl* control = new ( ELeave ) CAknControl;
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKBaseControls::TestCAknControlContructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKBaseControls::TestCAknControlDecontructorL( CStifItemParser& /*aItem*/ )
    {
    CAknControl* control = new ( ELeave ) CAknControl;
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    }

//End of file

