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
* Description:  test functions for testing CAknLongTapDetector class
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdktouchuiutil.h"

// CONSTANTS
const TInt KMicroSeconds = 2000;

// FORWARD DECLARE
// This test class for new the CAknLongTapDetector object
class CTestTapDetectorCallBack : public CBase, public MAknLongTapDetectorCallBack
    {
public:
    /**
     * from MAknLongTapDetectorCallBack
     */
    void HandleLongTapEventL( const TPoint& /*aPenEventLocation*/, const TPoint& /*aPenEventScreenLocation*/ ){}
    };


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKTouchUiUtil::TestCAknLongTapDetectorNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchUiUtil::TestCAknLongTapDetectorNewL( CStifItemParser& /*aItem*/ )
    {
    CTestTapDetectorCallBack* callback = new ( ELeave ) CTestTapDetectorCallBack;
    CleanupStack::PushL( callback );
    CAknLongTapDetector* tapdetector = CAknLongTapDetector::NewL( callback );
    CleanupStack::PushL( tapdetector );
    STIF_ASSERT_NOT_NULL( tapdetector );
    CleanupStack::PopAndDestroy( tapdetector );
    CleanupStack::PopAndDestroy( callback );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchUiUtil::TestCAknLongTapDetectorNewLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchUiUtil::TestCAknLongTapDetectorNewLC( CStifItemParser& /*aItem*/ )
    {
    CTestTapDetectorCallBack* callback = new ( ELeave ) CTestTapDetectorCallBack;
    CleanupStack::PushL( callback );
    CAknLongTapDetector* tapdetector = CAknLongTapDetector::NewLC( callback );
    STIF_ASSERT_NOT_NULL( tapdetector );
    CleanupStack::PopAndDestroy( tapdetector );
    CleanupStack::PopAndDestroy( callback );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchUiUtil::TestCAknLongTapDetectorPointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchUiUtil::TestCAknLongTapDetectorPointerEventL( CStifItemParser& /*aItem*/ )
    {
    CTestTapDetectorCallBack* callback = new ( ELeave ) CTestTapDetectorCallBack;
    CleanupStack::PushL( callback );
    CAknLongTapDetector* tapdetector = CAknLongTapDetector::NewL( callback );
    CleanupStack::PushL( tapdetector );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    tapdetector->PointerEventL( event );
    
    CleanupStack::PopAndDestroy( tapdetector );
    CleanupStack::PopAndDestroy( callback );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchUiUtil::TestCAknLongTapDetectorSetTimeDelayBeforeAnimationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchUiUtil::TestCAknLongTapDetectorSetTimeDelayBeforeAnimationL( CStifItemParser& /*aItem*/ )
    {
    CTestTapDetectorCallBack* callback = new ( ELeave ) CTestTapDetectorCallBack;
    CleanupStack::PushL( callback );
    CAknLongTapDetector* tapdetector = CAknLongTapDetector::NewL( callback );
    CleanupStack::PushL( tapdetector );
    
    tapdetector->SetTimeDelayBeforeAnimation( KMicroSeconds );
    
    CleanupStack::PopAndDestroy( tapdetector );
    CleanupStack::PopAndDestroy( callback );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchUiUtil::TestCAknLongTapDetectorSetLongTapDelayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchUiUtil::TestCAknLongTapDetectorSetLongTapDelayL( CStifItemParser& /*aItem*/ )
    {
    CTestTapDetectorCallBack* callback = new ( ELeave ) CTestTapDetectorCallBack;
    CleanupStack::PushL( callback );
    CAknLongTapDetector* tapdetector = CAknLongTapDetector::NewL( callback );
    CleanupStack::PushL( tapdetector );
    
    tapdetector->SetLongTapDelay( KMicroSeconds );
    
    CleanupStack::PopAndDestroy( tapdetector );
    CleanupStack::PopAndDestroy( callback );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchUiUtil::TestCAknLongTapDetectorEnableLongTapAnimationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchUiUtil::TestCAknLongTapDetectorEnableLongTapAnimationL( CStifItemParser& /*aItem*/ )
    {
    CTestTapDetectorCallBack* callback = new ( ELeave ) CTestTapDetectorCallBack;
    CleanupStack::PushL( callback );
    CAknLongTapDetector* tapdetector = CAknLongTapDetector::NewL( callback );
    CleanupStack::PushL( tapdetector );
    
    tapdetector->EnableLongTapAnimation( ETrue );
    tapdetector->EnableLongTapAnimation( EFalse );
    
    CleanupStack::PopAndDestroy( tapdetector );
    CleanupStack::PopAndDestroy( callback );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchUiUtil::TestCAknLongTapDetectorIsAnimationRunningL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchUiUtil::TestCAknLongTapDetectorIsAnimationRunningL( CStifItemParser& /*aItem*/ )
    {
    CTestTapDetectorCallBack* callback = new ( ELeave ) CTestTapDetectorCallBack;
    CleanupStack::PushL( callback );
    CAknLongTapDetector* tapdetector = CAknLongTapDetector::NewL( callback );
    CleanupStack::PushL( tapdetector );
    
    tapdetector->IsAnimationRunning();
    
    CleanupStack::PopAndDestroy( tapdetector );
    CleanupStack::PopAndDestroy( callback );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchUiUtil::TestCAknLongTapDetectorCancelAnimationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchUiUtil::TestCAknLongTapDetectorCancelAnimationL( CStifItemParser& /*aItem*/ )
    {
    CTestTapDetectorCallBack* callback = new ( ELeave ) CTestTapDetectorCallBack;
    CleanupStack::PushL( callback );
    CAknLongTapDetector* tapdetector = CAknLongTapDetector::NewL( callback );
    CleanupStack::PushL( tapdetector );
    
    tapdetector->CancelAnimationL();
    
    CleanupStack::PopAndDestroy( tapdetector );
    CleanupStack::PopAndDestroy( callback );
    
    return KErrNone;
    }

// End of file

