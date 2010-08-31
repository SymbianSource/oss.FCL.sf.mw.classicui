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
* Description:  for testing the indicators api module
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknindicatorcontainer.h>
#include <avkon.hrh>
#include <avkon.rsg>
#include <barsread.h>
#include <avkon.mbg>
#include <testsdkindicators.rsg>
#include <fbs.h>
#include <akndef.h>

#include "testsdkindicators.h"
#include "testsdkindicatorsext.h"
#include "testsdkindicatorsindicators.h"



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdkindicators::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 

        ENTRY( "TestIndiCntnerCAknIndicatorContainer", 
                CTestSDKIndicators::TestIndiCntnerCAknIndicatorContainerL ),
        ENTRY( "TestIndiCntnerDelete", 
                CTestSDKIndicators::TestIndiCntnerDelete ),
        ENTRY( "TestIndiCntnerConstructL", 
                CTestSDKIndicators::TestIndiCntnerConstructL ),
        ENTRY( "TestIndiCntnerSetIndicatorState", 
                CTestSDKIndicators::TestIndiCntnerSetIndicatorState ),
        ENTRY( "TestIndiCntnerIndicatorState", 
                CTestSDKIndicators::TestIndiCntnerIndicatorState ),
        ENTRY( "TestIndiCntnerSetIndicatorValueL", 
                CTestSDKIndicators::TestIndiCntnerSetIndicatorValueL ),
        ENTRY( "TestIndiCntnerSetIncallBubbleFlags", 
                CTestSDKIndicators::TestIndiCntnerSetIncallBubbleFlags ),
        ENTRY( "TestIndiCntnerConstructFromResourceL", 
                CTestSDKIndicators::TestIndiCntnerConstructFromResourceL ),
        ENTRY( "TestIndiCntnerIndicatorContext", 
                CTestSDKIndicators::TestIndiCntnerIndicatorContext ),
        ENTRY( "TestIndiCntnerHandleStatusPaneSizeChange", 
                CTestSDKIndicators::TestIndiCntnerHandleStatusPaneSizeChange ),
        ENTRY( "TestIndiCntnerHandlePointerEventL", 
                CTestSDKIndicators::TestIndiCntnerHandlePointerEventL ),
        ENTRY( "TestIndiCntnerSetIndicatorValue", 
                CTestSDKIndicators::TestIndiCntnerSetIndicatorValue ),
        ENTRY( "TestIndiCntnerSetIncallBubbleAllowedInIdle", 
                CTestSDKIndicators::TestIndiCntnerSetIncallBubbleAllowedInIdle ),
        ENTRY( "TestIndiCntnerSetIncallBubbleAllowedInUsual", 
                CTestSDKIndicators::TestIndiCntnerSetIncallBubbleAllowedInUsual ),
        ENTRY( "TestIndiCntnerSetIndicatorObserver", 
                CTestSDKIndicators::TestIndiCntnerSetIndicatorObserverL ),
        ENTRY( "TestIndiCntnerCreateIndicatorFromResourceL", 
                CTestSDKIndicators::TestIndiCntnerCreateIndicatorFromResourceL ),
        ENTRY( "TestIndiCntnerReplaceIndicatorIconL", 
                CTestSDKIndicators::TestIndiCntnerReplaceIndicatorIconL ),
        ENTRY( "TestIndiCntnerHandleResourceChange", 
                CTestSDKIndicators::TestIndiCntnerHandleResourceChangeL ),
        ENTRY( "TestIndiCntnerSizeChanged", 
                CTestSDKIndicators::TestIndiCntnerSizeChangedL ),
        ENTRY( "TestIndiCntnerPositionChanged", 
                CTestSDKIndicators::TestIndiCntnerPositionChangedL ),
        ENTRY( "TestIndiCntnerCountComponentControls", 
                CTestSDKIndicators::TestIndiCntnerCountComponentControlsL ),
        ENTRY( "TestIndiCntnerComponentControl", 
                CTestSDKIndicators::TestIndiCntnerComponentControlL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerCAknIndicatorContainerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerCAknIndicatorContainerL( CStifItemParser& aItem )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerCAknIndicatorContainer, "In TestIndiCntnerCAknIndicatorContainer" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerCAknIndicatorContainer );
    // Print to log file
    iLog->Log( KTestIndiCntnerCAknIndicatorContainer );
    
    TInt count;
    aItem.GetNextInt( count );
    
    
    switch( count )
        {
        case 0:
            {
            TInt err = KErrNone;
            
            iIndicatorContn =  new (ELeave) CAknIndicatorContainer();
            
            STIF_ASSERT_NOT_NULL( iIndicatorContn );
            
            return err;
            }
        case 1:
            {
            TInt err = KErrNone;
            
            iIndicatorContn =  new (ELeave) CAknIndicatorContainer( 
                    CAknIndicatorContainer::EUniversalIndicators );
            
            STIF_ASSERT_NOT_NULL( iIndicatorContn );
            
            return err;
            }
        default:
            return KErrNone;
        }
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerDelete
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerDelete( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerDelete, "In TestIndiCntnerDelete" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerDelete );
    // Print to log file
    iLog->Log( KTestIndiCntnerDelete );
    
    TInt err = KErrNone;
    
    delete iIndicatorContn;
    iIndicatorContn = NULL;
    
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerConstructL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerConstructL, "In TestIndiCntnerConstructL" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerConstructL );
    // Print to log file
    iLog->Log( KTestIndiCntnerConstructL );
    
    TInt err = KErrNone;
    
    TRAP( err, iIndicatorContn->ConstructL() );
    
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerSetIndicatorState
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerSetIndicatorState( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerSetIndicatorState, "In TestIndiCntnerSetIndicatorState" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerSetIndicatorState );
    // Print to log file
    iLog->Log( KTestIndiCntnerSetIndicatorState );
    
    TInt err = KErrNone;
    TUid Id = { EAknNaviPaneEditorIndicatorLowerCase };
    
    
    iIndicatorContn->SetIndicatorState( Id, EAknIndicatorStateOn );
    
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerIndicatorState
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerIndicatorState( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerIndicatorState, "In TestIndiCntnerIndicatorState" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerIndicatorState );
    // Print to log file
    iLog->Log( KTestIndiCntnerIndicatorState );
    
    TInt err = KErrNone;

    TUid Id = { EAknNaviPaneEditorIndicatorLowerCase };
    TInt state;
    
    state = iIndicatorContn->IndicatorState( Id );
    
    STIF_ASSERT_EQUALS( state, 0 );
    
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerSetIndicatorValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerSetIndicatorValueL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerSetIndicatorValueL, "In TestIndiCntnerSetIndicatorValueL" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerSetIndicatorValueL );
    // Print to log file
    iLog->Log( KTestIndiCntnerSetIndicatorValueL );
    
    TInt err = KErrNone;

    TUid Id = { EAknNaviPaneEditorIndicatorLowerCase };
    TBuf<20> buf = _L("indicator value");
    
    TRAP( err, iIndicatorContn->SetIndicatorValueL( Id, buf ) );
    
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerSetIncallBubbleFlags
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerSetIncallBubbleFlags( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerSetIncallBubbleFlags, "In TestIndiCntnerSetIncallBubbleFlags" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerSetIncallBubbleFlags );
    // Print to log file
    iLog->Log( KTestIndiCntnerSetIncallBubbleFlags );
    
    TInt err = KErrNone;
    
    iIndicatorContn->SetIncallBubbleFlags( 1 );
    
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerConstructFromResourceL, "In TestIndiCntnerConstructFromResourceL" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerConstructFromResourceL );
    // Print to log file
    iLog->Log( KTestIndiCntnerConstructFromResourceL );
    
    TInt err = KErrNone;
    
    TResourceReader read;
    
    CCoeEnv::Static()->CreateResourceReaderLC( read, R_AVKON_NAVI_PANE_EDITOR_INDICATORS );
    
    TRAP( err, iIndicatorContn->ConstructFromResourceL( read ) );
    
    CleanupStack::PopAndDestroy();
    
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerIndicatorContext
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerIndicatorContext( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerIndicatorContext, "In TestIndiCntnerIndicatorContext" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerIndicatorContext );
    // Print to log file
    iLog->Log( KTestIndiCntnerIndicatorContext );
    
    TInt err = KErrNone;
    
    TInt context = iIndicatorContn->IndicatorContext();
    
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerHandleStatusPaneSizeChange
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerHandleStatusPaneSizeChange( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerHandleStatusPaneSizeChange, "In TestIndiCntnerHandleStatusPaneSizeChange" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerHandleStatusPaneSizeChange );
    // Print to log file
    iLog->Log( KTestIndiCntnerHandleStatusPaneSizeChange );
    
    TInt err = KErrNone;
    
    iIndicatorContn->HandleStatusPaneSizeChange();
    
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerHandlePointerEventL, "In TestIndiCntnerHandlePointerEventL" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestIndiCntnerHandlePointerEventL );
    
    TInt err = KErrNone;
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
            
    
    TRAP( err, iIndicatorContn->HandlePointerEventL( event ) );
    
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerSetIndicatorValue
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerSetIndicatorValue( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerSetIndicatorValue, "In TestIndiCntnerSetIndicatorValue" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerSetIndicatorValue );
    // Print to log file
    iLog->Log( KTestIndiCntnerSetIndicatorValue );
    
    TInt err = KErrNone;

    TUid Id = { EAknNaviPaneEditorIndicatorLowerCase };
    
    iIndicatorContn->SetIndicatorValue( Id, 1, 10 );
    
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerSetIncallBubbleAllowedInIdle
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerSetIncallBubbleAllowedInIdle( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerSetIncallBubbleAllowedInIdle, "In TestIndiCntnerSetIncallBubbleAllowedInIdle" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerSetIncallBubbleAllowedInIdle );
    // Print to log file
    iLog->Log( KTestIndiCntnerSetIncallBubbleAllowedInIdle );
    
    TInt err = KErrNone;
    
    iIndicatorContn->SetIncallBubbleAllowedInIdle( ETrue );
    
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerSetIncallBubbleAllowedInUsual
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerSetIncallBubbleAllowedInUsual( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerSetIncallBubbleAllowedInUsual, "In TestIndiCntnerSetIncallBubbleAllowedInUsual" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerSetIncallBubbleAllowedInUsual );
    // Print to log file
    iLog->Log( KTestIndiCntnerSetIncallBubbleAllowedInUsual );
    
    TInt err = KErrNone;
    
    iIndicatorContn->SetIncallBubbleAllowedInUsual( ETrue );
    
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerSetIndicatorObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerSetIndicatorObserverL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerSetIndicatorObserver, "In TestIndiCntnerSetIndicatorObserver" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerSetIndicatorObserver );
    // Print to log file
    iLog->Log( KTestIndiCntnerSetIndicatorObserver );
    
    TInt err = KErrNone;
    
    TUid Id = { EAknNaviPaneEditorIndicatorLowerCase };
    CAknIndicatorObserverExt* observer = new (ELeave) CAknIndicatorObserverExt();
    
    iIndicatorContn->SetIndicatorObserver( observer, Id );
    
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerCreateIndicatorFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerCreateIndicatorFromResourceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerCreateIndicatorFromResourceL, "In TestIndiCntnerCreateIndicatorFromResourceL" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerCreateIndicatorFromResourceL );
    // Print to log file
    iLog->Log( KTestIndiCntnerCreateIndicatorFromResourceL );
    
    TInt err = KErrNone;

    TRAP( err, iIndicatorContn->CreateIndicatorFromResourceL( R_TEST_INDICATOR, 
            CAknIndicatorContainer::EMultiColorIndicator ) );
        
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerReplaceIndicatorIconL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerReplaceIndicatorIconL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerReplaceIndicatorIconL, "In TestIndiCntnerReplaceIndicatorIconL" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerReplaceIndicatorIconL );
    // Print to log file
    iLog->Log( KTestIndiCntnerReplaceIndicatorIconL );
    
    TInt err = KErrNone;

    TUid Id = { EAknIndicatorEnvelope };
    
    _LIT( KFileName, "z:\\resource\\apps\\avkon2.mbm" );

    CFbsBitmap* bmp = new (ELeave) CFbsBitmap();
    bmp->Load( KFileName, EMbmAvkonQgn_stat_cyphering_on );
    CFbsBitmap* bmpMask = new (ELeave) CFbsBitmap();
    bmpMask->Load( KFileName, EMbmAvkonQgn_stat_cyphering_on_mask );
    
    iIndicatorContn->CreateIndicatorFromResourceL( R_TEST_INDICATOR, 
                CAknIndicatorContainer::EMultiColorIndicator );
    
    iIndicatorContn->ReplaceIndicatorIconL( 
            Id, 
            EAknIndicatorStateOn, 
            CAknIndicatorContainer::ELayoutModeUsual, 
            bmp, bmpMask);
    
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerHandleResourceChange
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerHandleResourceChange, "In TestIndiCntnerHandleResourceChange" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerHandleResourceChange );
    // Print to log file
    iLog->Log( KTestIndiCntnerHandleResourceChange );
    
    TInt err = KErrNone;
    
    CTestSDKIndicatorsIndicators* indicatorExt = new (ELeave) CTestSDKIndicatorsIndicators();
    
    CleanupStack::PushL( indicatorExt );
    
    TResourceReader read;
    
    CCoeEnv::Static()->CreateResourceReaderLC( read, R_AVKON_NAVI_PANE_EDITOR_INDICATORS );
    
    indicatorExt->ConstructFromResourceL( read );
    
    TInt type = KEikDynamicLayoutVariantSwitch;
    indicatorExt->HandleResourceChange( type );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerSizeChanged
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerSizeChanged, "In TestIndiCntnerSizeChanged" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerSizeChanged );
    // Print to log file
    iLog->Log( KTestIndiCntnerSizeChanged );
    
    TInt err = KErrNone;
    
    CTestSDKIndicatorsIndicators* indicatorExt = new (ELeave) CTestSDKIndicatorsIndicators();
    
    CleanupStack::PushL( indicatorExt );
    
    TResourceReader read;
    
    CCoeEnv::Static()->CreateResourceReaderLC( read, R_AVKON_NAVI_PANE_EDITOR_INDICATORS );
    
    indicatorExt->ConstructFromResourceL( read );
    
    indicatorExt->SizeChanged();
    
    CleanupStack::PopAndDestroy( 2 );
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerPositionChanged
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerPositionChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerPositionChanged, "In TestIndiCntnerPositionChanged" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerPositionChanged );
    // Print to log file
    iLog->Log( KTestIndiCntnerPositionChanged );
    
    TInt err = KErrNone;
    
    CTestSDKIndicatorsIndicators* indicatorExt = new (ELeave) CTestSDKIndicatorsIndicators();
    
    CleanupStack::PushL( indicatorExt );
    
    TResourceReader read;
    
    CCoeEnv::Static()->CreateResourceReaderLC( read, R_AVKON_NAVI_PANE_EDITOR_INDICATORS );
    
    indicatorExt->ConstructFromResourceL( read );
    
    indicatorExt->PositionChanged();
    
    CleanupStack::PopAndDestroy( 2 );
    
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerCountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerCountComponentControls, "In TestIndiCntnerCountComponentControls" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerCountComponentControls );
    // Print to log file
    iLog->Log( KTestIndiCntnerCountComponentControls );
    
    TInt err = KErrNone;
    
    CTestSDKIndicatorsIndicators* indicatorExt = new (ELeave) CTestSDKIndicatorsIndicators();
    
    CleanupStack::PushL( indicatorExt );
    
    TResourceReader read;
    
    CCoeEnv::Static()->CreateResourceReaderLC( read, R_AVKON_NAVI_PANE_EDITOR_INDICATORS );
    
    indicatorExt->ConstructFromResourceL( read );
    
    TInt count = indicatorExt->CountComponentControls();
    
    CleanupStack::PopAndDestroy( 2 );
    
    STIF_ASSERT_TRUE( (count==0) );
    
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestsdkindicators::TestIndiCntnerComponentControl
// -----------------------------------------------------------------------------
//
TInt CTestSDKIndicators::TestIndiCntnerComponentControlL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkindicators, "testsdkindicators" );
    _LIT( KTestIndiCntnerComponentControl, "In TestIndiCntnerComponentControl" );
    TestModuleIf().Printf( 0, Ktestsdkindicators, KTestIndiCntnerComponentControl );
    // Print to log file
    iLog->Log( KTestIndiCntnerComponentControl );
    
    TInt err = KErrNone;
    
    CTestSDKIndicatorsIndicators* indicatorExt = new (ELeave) CTestSDKIndicatorsIndicators();
    
    CleanupStack::PushL( indicatorExt );
    
    TResourceReader read;
    
    CCoeEnv::Static()->CreateResourceReaderLC( read, R_AVKON_NAVI_PANE_EDITOR_INDICATORS );
    
    indicatorExt->ConstructFromResourceL( read );
    
    TInt count = indicatorExt->CountComponentControls();
    
    CCoeControl* control = indicatorExt->ComponentControl( count );
    
    CleanupStack::PopAndDestroy( 2 );
    
    STIF_ASSERT_NULL( control );
    
    return err;
    }

//  [End of File]
