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
* Description:  Test AknBitmapAnimation.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknbitmapanimation.h>
#include <w32std.h>
#include <bmpancli.h>
#include <barsread.h>
#include <coeaui.h>
#include <avkon.rsg>
#include <aknsconstants.h>
#include <testsdkanimation.rsg>

#include "testsdkacontrol.h"
#include "testsdkanimation.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKAnimation::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKAnimation::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKAnimation::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKAnimation::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestBANewL", CTestSDKAnimation::TestBANewL ),
        ENTRY( "TestBADeconstructorL", CTestSDKAnimation::TestBADeconstructorL ),
        ENTRY( "TestBAAnimationL", CTestSDKAnimation::TestBAAnimationL ),
        ENTRY( "TestBABitmapAnimDataL", CTestSDKAnimation::TestBABitmapAnimDataL ),
        ENTRY( "TestBACancelAnimationL", CTestSDKAnimation::TestBACancelAnimationL ),
        ENTRY( "TestBASetFrameIndexL", CTestSDKAnimation::TestBASetFrameIndexL ),
        ENTRY( "TestBASetFrameIntervalL", CTestSDKAnimation::TestBASetFrameIntervalL ),
        ENTRY( "TestBAStartAnimationL", CTestSDKAnimation::TestBAStartAnimationL ),
        ENTRY( "TestBASetScaleModeForAnimationFramesL", CTestSDKAnimation::TestBASetScaleModeForAnimationFramesL ),
        ENTRY( "TestBASetScaleModeForAnimationBackgroundFrameL", CTestSDKAnimation::TestBASetScaleModeForAnimationBackgroundFrameL ),
        ENTRY( "TestBAExcludeAnimationFramesFromCacheL", CTestSDKAnimation::TestBAExcludeAnimationFramesFromCacheL ),
        ENTRY( "TestBAConstructFromSkinL", CTestSDKAnimation::TestBAConstructFromSkinL ),
        ENTRY( "TestBAConstructFromResourceL", CTestSDKAnimation::TestBAConstructFromResourceL ),
        ENTRY( "TestBAMinimumSizeL", CTestSDKAnimation::TestBAMinimumSizeL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

/*                               class CAknBitmapAnimation                    */
// -----------------------------------------------------------------------------
// CTestSDKAnimation::TestBANewL
// -----------------------------------------------------------------------------
TInt CTestSDKAnimation::TestBANewL( CStifItemParser& /*aItem*/ )
    {
    CAknBitmapAnimation* bitmapanimation = CAknBitmapAnimation::NewL();
    CleanupStack::PushL( bitmapanimation );
    
    STIF_ASSERT_NOT_NULL( bitmapanimation );
    
    CleanupStack::PopAndDestroy( bitmapanimation );
    
    return KErrNone;
    
    }
    
// -----------------------------------------------------------------------------
// CTestSDKAnimation::TestBADeconstructorL
// -----------------------------------------------------------------------------
TInt CTestSDKAnimation::TestBADeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknBitmapAnimation* bitmapanimation = CAknBitmapAnimation::NewL();
    CleanupStack::PushL( bitmapanimation );
    
    STIF_ASSERT_NOT_NULL( bitmapanimation );
    
    CleanupStack::Pop( bitmapanimation );
    delete bitmapanimation;
    
    return KErrNone;
    
    }
    
// -----------------------------------------------------------------------------
// CTestSDKAnimation::TestBAAnimationL
// -----------------------------------------------------------------------------
TInt CTestSDKAnimation::TestBAAnimationL( CStifItemParser& /*aItem*/ )
    {
    CAknBitmapAnimation* bitmapanimation = CAknBitmapAnimation::NewL();
    CleanupStack::PushL( bitmapanimation );
    
    STIF_ASSERT_NOT_NULL( bitmapanimation );
    
    RBitmapAnim& bitmapanim = bitmapanimation->Animation();
    STIF_ASSERT_NOT_NULL( &bitmapanim );
    
    CleanupStack::PopAndDestroy( bitmapanimation );
    
    return KErrNone;
    
    }
    
// -----------------------------------------------------------------------------
// CTestSDKAnimation::TestBABitmapAnimDataL
// -----------------------------------------------------------------------------
TInt CTestSDKAnimation::TestBABitmapAnimDataL( CStifItemParser& /*aItem*/ )
    {
    CAknBitmapAnimation* bitmapanimation = CAknBitmapAnimation::NewL();
    CleanupStack::PushL( bitmapanimation );
    
    STIF_ASSERT_NOT_NULL( bitmapanimation );
    
    CBitmapAnimClientData* clientdata = bitmapanimation->BitmapAnimData();
    
    STIF_ASSERT_NOT_NULL( clientdata );
    
    CleanupStack::PopAndDestroy( bitmapanimation );
    
    return KErrNone;
    
    }
    
// -----------------------------------------------------------------------------
// CTestSDKAnimation::TestBACancelAnimationL
// -----------------------------------------------------------------------------
TInt CTestSDKAnimation::TestBACancelAnimationL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    
    CCoeEnv::Static()->AppUi()->AddToStackL( control );
    
    control->TestCancelL();
    
    CCoeEnv::Static()->AppUi()->RemoveFromStack( control );
    
    CleanupStack::PopAndDestroy( control );

    return KErrNone;
    
    }
    
// -----------------------------------------------------------------------------
// CTestSDKAnimation::TestBASetFrameIndexL
// -----------------------------------------------------------------------------
TInt CTestSDKAnimation::TestBASetFrameIndexL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    
    CCoeEnv::Static()->AppUi()->AddToStackL( control );
    
    control->SetFrameIndexL( 0 );
    
    CCoeEnv::Static()->AppUi()->RemoveFromStack( control );
    
    CleanupStack::PopAndDestroy( control );

    return KErrNone;
    
    }
    
// -----------------------------------------------------------------------------
// CTestSDKAnimation::TestBASetFrameIntervalL
// -----------------------------------------------------------------------------
TInt CTestSDKAnimation::TestBASetFrameIntervalL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    
    CCoeEnv::Static()->AppUi()->AddToStackL( control );
    
    const TInt frameIntervalInMilliSeconds = 1500;
    control->SetFrameIntervalL(frameIntervalInMilliSeconds);
    
    CCoeEnv::Static()->AppUi()->RemoveFromStack( control );
    
    CleanupStack::PopAndDestroy( control );

    return KErrNone;
    
    }
    
// -----------------------------------------------------------------------------
// CTestSDKAnimation::TestBAStartAnimationL
// -----------------------------------------------------------------------------
TInt CTestSDKAnimation::TestBAStartAnimationL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    
    CCoeEnv::Static()->AppUi()->AddToStackL( control );
    
    control->TestRunL();
    
    CCoeEnv::Static()->AppUi()->RemoveFromStack( control );
    
    CleanupStack::PopAndDestroy( control );

    return KErrNone;
    
    }
    
// -----------------------------------------------------------------------------
// CTestSDKAnimation::TestBASetScaleModeForAnimationFramesL
// -----------------------------------------------------------------------------
TInt CTestSDKAnimation::TestBASetScaleModeForAnimationFramesL( CStifItemParser& /*aItem*/ )
    {
    CAknBitmapAnimation* bitmapanimation = CAknBitmapAnimation::NewL();
    CleanupStack::PushL( bitmapanimation );
    
    STIF_ASSERT_NOT_NULL( bitmapanimation );
    
    TScaleMode mode = TScaleMode( EAspectRatioPreserved );
    bitmapanimation->SetScaleModeForAnimationFrames( mode );
    
    CleanupStack::PopAndDestroy( bitmapanimation );
    
    return KErrNone;
    
    }
    
// -----------------------------------------------------------------------------
// CTestSDKAnimation::TestBASetScaleModeForAnimationBackgroundFrameL
// -----------------------------------------------------------------------------
TInt CTestSDKAnimation::TestBASetScaleModeForAnimationBackgroundFrameL( CStifItemParser& /*aItem*/ )
    {
    CAknBitmapAnimation* bitmapanimation = CAknBitmapAnimation::NewL();
    CleanupStack::PushL( bitmapanimation );
    
    STIF_ASSERT_NOT_NULL( bitmapanimation );
    
    TScaleMode mode = TScaleMode( EAspectRatioPreserved );
    bitmapanimation->SetScaleModeForAnimationBackgroundFrame( mode );
    
    CleanupStack::PopAndDestroy( bitmapanimation );
    
    return KErrNone;
    
    }
    
// -----------------------------------------------------------------------------
// CTestSDKAnimation::TestBAExcludeAnimationFramesFromCacheL
// -----------------------------------------------------------------------------
TInt CTestSDKAnimation::TestBAExcludeAnimationFramesFromCacheL( CStifItemParser& /*aItem*/ )
    {
    CAknBitmapAnimation* bitmapanimation = CAknBitmapAnimation::NewL();
    CleanupStack::PushL( bitmapanimation );
    
    STIF_ASSERT_NOT_NULL( bitmapanimation );

    bitmapanimation->ExcludeAnimationFramesFromCache();
    
    CleanupStack::PopAndDestroy( bitmapanimation );
    
    return KErrNone;
    
    }
    
// -----------------------------------------------------------------------------
// CTestSDKAnimation::TestBAConstructFromSkinL
// -----------------------------------------------------------------------------
TInt CTestSDKAnimation::TestBAConstructFromSkinL( CStifItemParser& /*aItem*/ )
    {
    CAknBitmapAnimation* bitmapanimation = CAknBitmapAnimation::NewL();
    CleanupStack::PushL( bitmapanimation );
    
    STIF_ASSERT_NOT_NULL( bitmapanimation );

    TBool flag = bitmapanimation->ConstructFromSkinL( KAknsIIDQsnBgScreen );
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( bitmapanimation );
    
    return KErrNone;
    
    }
    
// -----------------------------------------------------------------------------
// CTestSDKAnimation::TestBAConstructFromResourceL
// -----------------------------------------------------------------------------
TInt CTestSDKAnimation::TestBAConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    
    CCoeEnv::Static()->AppUi()->AddToStackL( control );
    
    control->TestRunL();
    
    CCoeEnv::Static()->AppUi()->RemoveFromStack( control );
    
    CleanupStack::PopAndDestroy( control );

    return KErrNone;
    
    }
    
// -----------------------------------------------------------------------------
// CTestSDKAnimation::TestBAMinimumSizeL
// -----------------------------------------------------------------------------
TInt CTestSDKAnimation::TestBAMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    CAknBitmapAnimation* bitmapanimation = CAknBitmapAnimation::NewL();
    CleanupStack::PushL( bitmapanimation );
    
    STIF_ASSERT_NOT_NULL( bitmapanimation );
    
    TSize size = bitmapanimation->MinimumSize();
    
    TPoint point( size.AsPoint() );
    
    STIF_ASSERT_EQUALS( 0, point.iX );
    STIF_ASSERT_EQUALS( 0, point.iY );
    
    CleanupStack::PopAndDestroy( bitmapanimation );
    
    return KErrNone;
    
    }

//  [End of File]
