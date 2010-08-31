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
* Description:  test api in eikalign.h
*
*/


// [INCLUDE FILES]
#include <s32mem.h>
#include "testsdkbasecontrols.h"

// CONSTANTS
const TInt KMarginSize = 10;
const TInt KPointerCoordinate = 40;
const TInt KHbufSize = 1000;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKBaseControls::TestCEikAlignedControlContructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKBaseControls::TestCEikAlignedControlContructorL( CStifItemParser& /*aItem*/ )
    {
    CEikAlignedControl* control = new ( ELeave )CEikAlignedControl;
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKBaseControls::TestCEikAlignedControlDecontructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKBaseControls::TestCEikAlignedControlDecontructorL( CStifItemParser& /*aItem*/ )
    {
    CEikAlignedControl* control = new ( ELeave )CEikAlignedControl;
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKBaseControls::TestCEikAlignedControlSetAllMarginsToL
// -----------------------------------------------------------------------------
//
TInt CTestSDKBaseControls::TestCEikAlignedControlSetAllMarginsToL( CStifItemParser& /*aItem*/ )
    {
    CEikAlignedControl* control = new ( ELeave )CEikAlignedControl;
    CleanupStack::PushL( control );
    control->SetAllMarginsTo( KMarginSize );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKBaseControls::TestCEikAlignedControlSetAlignmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKBaseControls::TestCEikAlignedControlSetAlignmentL( CStifItemParser& /*aItem*/ )
    {
    CEikAlignedControl* control = new ( ELeave )CEikAlignedControl;
    CleanupStack::PushL( control );
    TGulAlignmentValue align = EHLeftVTop;
    control->SetAlignment( align );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKBaseControls::TestCEikAlignedControlHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKBaseControls::TestCEikAlignedControlHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CEikAlignedControl* control = new ( ELeave )CEikAlignedControl;
    CleanupStack::PushL( control );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KPointerCoordinate, KPointerCoordinate );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    control->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKBaseControls::TestCEikAlignedControlWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKBaseControls::TestCEikAlignedControlWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    class CTestCEikAlignedControl : public CEikAlignedControl
        {
    public:
        void DoWriteInternalStateL( RWriteStream& aWriteStream ){ WriteInternalStateL( aWriteStream ); }
        };
    CTestCEikAlignedControl* control = new ( ELeave )CTestCEikAlignedControl;
    CleanupStack::PushL( control );
    
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    HBufC8* buf = HBufC8::NewL( KHbufSize );
    CleanupStack::PushL( buf );
    TPtr8 ptr = buf->Des();
    stream.Open( ptr );
    control->DoWriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();
    
    CleanupStack::PopAndDestroy( 3 );
    
    return KErrNone;
    }

//End of file

