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
* Description:  test functions for testing aknAnimData.h
 *
*/


// [INCLUDE FILES]
#include <fbs.h>
#include <testdomextanimation.rsg>
#include <barsread.h>

#include "testbitmapcontext.h"
#include "testdomextanimation.h"

// CONSTANTS
const TUint8 KAnimStepType = 1;
const TInt KScreenSize = 50;

// FORWARD DECLARATION
// CTestAnimationData for testing protected functions of CAknAnimationData
class CTestAnimationData : public CAknAnimationData
    {
public:
    // CTestAnimationData::ConstructL
    void ConstructL()
        {
        CAknAnimationData::ConstructL();
        }
    
    // CTestAnimationData::DrawUserAnimationStep
    TBool DrawUserAnimationStep( CBitmapContext& aGc, TAnimMultiStep& aStep )
        {
        return CAknAnimationData::DrawUserAnimationStep( aGc, aStep );
        }
    
    // CTestAnimationData::ConstructUserAnimationStepL
    void ConstructUserAnimationStepL( TAnimStep& aAnimStep, TResourceReader& aReader )
        {
        CAknAnimationData::ConstructUserAnimationStepL( aAnimStep, aReader );
        }
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestTAnimStepTAnimStepL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestTAnimStepTAnimStepL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestTAnimStepTAnimStepL, "In TestTAnimStepTAnimStepL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestTAnimStepTAnimStepL );
    // Print to log file
    iLog->Log( KTestTAnimStepTAnimStepL );

    TAnimStep* animstep = new ( ELeave ) TAnimStep();
    CleanupStack::PushL( animstep );

    STIF_ASSERT_NOT_NULL( animstep );

    CleanupStack::PopAndDestroy( animstep );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestTAnimStepLineDrawStep
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestTAnimStepLineDrawStep( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestTAnimStepLineDrawStep, "In TestTAnimStepLineDrawStep" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestTAnimStepLineDrawStep );
    // Print to log file
    iLog->Log( KTestTAnimStepLineDrawStep );

    TAnimStep animstep;

    animstep.LineDrawStep();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestTAnimStepBlitStep
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestTAnimStepBlitStep( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestTAnimStepBlitStep, "In TestTAnimStepBlitStep" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestTAnimStepBlitStep );
    // Print to log file
    iLog->Log( KTestTAnimStepBlitStep );

    TAnimStep animstep;

    animstep.BlitStep();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestTAnimStepSetColorStep
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestTAnimStepSetColorStep( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestTAnimStepSetColorStep, "In TestTAnimStepSetColorStep" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestTAnimStepSetColorStep );
    // Print to log file
    iLog->Log( KTestTAnimStepSetColorStep );

    TAnimStep animstep;

    animstep.SetColorStep();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestTAnimStepSlideStep
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestTAnimStepSlideStep( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestTAnimStepSlideStep, "In TestTAnimStepSlideStep" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestTAnimStepSlideStep );
    // Print to log file
    iLog->Log( KTestTAnimStepSlideStep );

    TAnimStep animstep;

    animstep.SlideStep();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestTAnimStepWaitStep
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestTAnimStepWaitStep( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestTAnimStepWaitStep, "In TestTAnimStepWaitStep" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestTAnimStepWaitStep );
    // Print to log file
    iLog->Log( KTestTAnimStepWaitStep );

    TAnimStep animstep;

    animstep.WaitStep();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestTAnimStepSetType
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestTAnimStepSetType( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestTAnimStepSetType, "In TestTAnimStepSetType" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestTAnimStepSetType );
    // Print to log file
    iLog->Log( KTestTAnimStepSetType );

    TAnimStep animstep;

    animstep.SetType( KAnimStepType );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestTAnimStepType
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestTAnimStepType( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestTAnimStepType, "In TestTAnimStepType" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestTAnimStepType );
    // Print to log file
    iLog->Log( KTestTAnimStepType );

    TAnimStep animstep;

    animstep.Type();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestTAnimMultiStepTAnimMultiStepL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestTAnimMultiStepTAnimMultiStepL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestTAnimMultiStepTAnimMultiStepL, "In TestTAnimMultiStepTAnimMultiStepL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestTAnimMultiStepTAnimMultiStepL );
    // Print to log file
    iLog->Log( KTestTAnimMultiStepTAnimMultiStepL );

    TAnimStep animstep;

    TAnimMultiStep* multistep = new ( ELeave ) TAnimMultiStep( animstep );
    CleanupStack::PushL( multistep );

    STIF_ASSERT_NOT_NULL( multistep );

    CleanupStack::PopAndDestroy( multistep );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestCAknAnimDataCAknAnimationDataL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestCAknAnimDataCAknAnimationDataL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestCAknAnimDataCAknAnimationDataL, "In TestCAknAnimDataCAknAnimationDataL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestCAknAnimDataCAknAnimationDataL );
    // Print to log file
    iLog->Log( KTestCAknAnimDataCAknAnimationDataL );

    CAknAnimationData* animdata= new ( ELeave ) CAknAnimationData();
    CleanupStack::PushL( animdata );

    STIF_ASSERT_NOT_NULL( animdata );

    CleanupStack::PopAndDestroy( animdata );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestCAknAnimDataConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestCAknAnimDataConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestCAknAnimDataConstructFromResourceL, "In TestCAknAnimDataConstructFromResourceL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestCAknAnimDataConstructFromResourceL );
    // Print to log file
    iLog->Log( KTestCAknAnimDataConstructFromResourceL );

    CAknAnimationData* animdata= new ( ELeave ) CAknAnimationData();
    CleanupStack::PushL( animdata );

    animdata->ConstructFromResourceL( R_QGN_NOTE_BATT_FULL_ANIM );

    CleanupStack::PopAndDestroy( animdata );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestCAknAnimDataSetScreenSizeL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestCAknAnimDataSetScreenSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestCAknAnimDataSetScreenSizeL, "In TestCAknAnimDataSetScreenSizeL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestCAknAnimDataSetScreenSizeL );
    // Print to log file
    iLog->Log( KTestCAknAnimDataSetScreenSizeL );

    CAknAnimationData* animdata= new ( ELeave ) CAknAnimationData();
    CleanupStack::PushL( animdata );

    animdata->SetScreenSize( TSize( KScreenSize, KScreenSize) );

    CleanupStack::PopAndDestroy( animdata );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestCAknAnimDataSetViewBitmapL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestCAknAnimDataSetViewBitmapL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestCAknAnimDataSetViewBitmapL, "In TestCAknAnimDataSetViewBitmapL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestCAknAnimDataSetViewBitmapL );
    // Print to log file
    iLog->Log( KTestCAknAnimDataSetViewBitmapL );

    CAknAnimationData* animdata= new ( ELeave ) CAknAnimationData();
    CleanupStack::PushL( animdata );

    CFbsBitmap* viewBitmap = new ( ELeave ) CFbsBitmap();
    CleanupStack::PushL( viewBitmap );

    animdata->SetViewBitmap( viewBitmap );

    CleanupStack::PopAndDestroy( viewBitmap );
    CleanupStack::PopAndDestroy( animdata );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestCAknAnimDataSetOldBitmapL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestCAknAnimDataSetOldBitmapL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestCAknAnimDataSetOldBitmapL, "In TestCAknAnimDataSetOldBitmapL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestCAknAnimDataSetOldBitmapL );
    // Print to log file
    iLog->Log( KTestCAknAnimDataSetOldBitmapL );

    CAknAnimationData* animdata= new ( ELeave ) CAknAnimationData();
    CleanupStack::PushL( animdata );

    CFbsBitmap* oldBitmap = new ( ELeave ) CFbsBitmap();
    CleanupStack::PushL( oldBitmap );

    animdata->SetOldBitmap( oldBitmap );

    CleanupStack::PopAndDestroy( oldBitmap );
    CleanupStack::PopAndDestroy( animdata );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestCAknAnimDataSetClearOldViewL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestCAknAnimDataSetClearOldViewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestCAknAnimDataSetClearOldViewL, "In TestCAknAnimDataSetClearOldViewL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestCAknAnimDataSetClearOldViewL );
    // Print to log file
    iLog->Log( KTestCAknAnimDataSetClearOldViewL );

    CAknAnimationData* animdata= new ( ELeave ) CAknAnimationData();
    CleanupStack::PushL( animdata );

    animdata->SetClearOldView();

    CleanupStack::PopAndDestroy( animdata );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestCAknAnimDataClearOldViewL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestCAknAnimDataClearOldViewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestCAknAnimDataClearOldViewL, "In TestCAknAnimDataClearOldViewL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestCAknAnimDataClearOldViewL );
    // Print to log file
    iLog->Log( KTestCAknAnimDataClearOldViewL );

    CAknAnimationData* animdata= new ( ELeave ) CAknAnimationData();
    CleanupStack::PushL( animdata );

    animdata->ClearOldView();

    CleanupStack::PopAndDestroy( animdata );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestCAknAnimDataWaitBetweenSectionsL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestCAknAnimDataWaitBetweenSectionsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestCAknAnimDataWaitBetweenSectionsL, "In TestCAknAnimDataWaitBetweenSectionsL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestCAknAnimDataWaitBetweenSectionsL );
    // Print to log file
    iLog->Log( KTestCAknAnimDataWaitBetweenSectionsL );

    CAknAnimationData* animdata= new ( ELeave ) CAknAnimationData();
    CleanupStack::PushL( animdata );

    animdata->WaitBetweenSections();

    CleanupStack::PopAndDestroy( animdata );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestCAknAnimDataSetWaitForeverAtEndL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestCAknAnimDataSetWaitForeverAtEndL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestCAknAnimDataSetWaitForeverAtEndL, "In TestCAknAnimDataSetWaitForeverAtEndL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestCAknAnimDataSetWaitForeverAtEndL );
    // Print to log file
    iLog->Log( KTestCAknAnimDataSetWaitForeverAtEndL );

    CAknAnimationData* animdata= new ( ELeave ) CAknAnimationData();
    CleanupStack::PushL( animdata );

    animdata->SetWaitForeverAtEnd();

    CleanupStack::PopAndDestroy( animdata );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestCAknAnimDataWaitForeverAtEndL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestCAknAnimDataWaitForeverAtEndL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestCAknAnimDataWaitForeverAtEndL, "In TestCAknAnimDataWaitForeverAtEndL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestCAknAnimDataWaitForeverAtEndL );
    // Print to log file
    iLog->Log( KTestCAknAnimDataWaitForeverAtEndL );

    CAknAnimationData* animdata= new ( ELeave ) CAknAnimationData();
    CleanupStack::PushL( animdata );

    animdata->WaitForeverAtEnd();

    CleanupStack::PopAndDestroy( animdata );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestCAknAnimDataDrawNextAnimationStepL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestCAknAnimDataDrawNextAnimationStepL( CStifItemParser& /*aItem*/ ) 
    {
    
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestCAknAnimDataDrawNextAnimationStepL, "In TestCAknAnimDataDrawNextAnimationStepL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestCAknAnimDataDrawNextAnimationStepL );
    // Print to log file
    iLog->Log( KTestCAknAnimDataDrawNextAnimationStepL );
    
    CAknAnimationData* animdata= new ( ELeave ) CAknAnimationData();
    CleanupStack::PushL( animdata );
    
    CTestBitmapContext* bitmapCtx = new ( ELeave ) CTestBitmapContext;
    CleanupStack::PushL( bitmapCtx );
    
    animdata->ConstructFromResourceL( R_TEST_ANIMDATA );
    animdata->DrawNextAnimationStep( *bitmapCtx );
    
    CleanupStack::PopAndDestroy( bitmapCtx );
    CleanupStack::PopAndDestroy( animdata );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestCAknAnimDataIntervalL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestCAknAnimDataIntervalL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestCAknAnimDataIntervalL, "In TestCAknAnimDataIntervalL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestCAknAnimDataIntervalL );
    // Print to log file
    iLog->Log( KTestCAknAnimDataIntervalL );

    CAknAnimationData* animdata= new ( ELeave ) CAknAnimationData();
    CleanupStack::PushL( animdata );

    animdata->Interval();

    CleanupStack::PopAndDestroy( animdata );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestCAknAnimDataConstructL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestCAknAnimDataConstructL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestCAknAnimDataConstructL, "In TestCAknAnimDataConstructL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestCAknAnimDataConstructL );
    // Print to log file
    iLog->Log( KTestCAknAnimDataConstructL );

    CTestAnimationData* animdata= new ( ELeave ) CTestAnimationData;
    CleanupStack::PushL( animdata );

    animdata->ConstructL();

    CleanupStack::PopAndDestroy( animdata );

    return KErrNone;
    }

//  [End of File]
