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
* Description:  Test aknnavi.h
 *
*/


// [INCLUDE FILES]
#include <aknnavi.h>
#include <testsdknavipane.rsg>
#include <barsread.h>
#include <coemain.h>
#include <aknviewappui.h>
#include <aknnavide.h> 
#include <coecobs.h>

#include "testsdknavipane.h"
#include "testsdknavitabobserver.h"
#include "testsdknavipanenaviext.h"



// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestNaviCAknNavigationControlContainer
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviCAknNavigationControlContainerL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviCAknNavigationControlContainerL, "In TestNaviCAknNavigationControlContainerL" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviCAknNavigationControlContainerL );
    // Print to log file
    iLog->Log( KTestNaviCAknNavigationControlContainerL );

    if ( iNaviContainer != NULL )
        {
        delete iNaviContainer;
        iNaviContainer = NULL;
        }
    
    iNaviContainer = new (ELeave) CAknNavigationControlContainer;
    STIF_ASSERT_NOT_NULL( iNaviContainer );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDelete
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDelete( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDelete, "In TestNaviDelete" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviDelete );
    // Print to log file
    iLog->Log( KTestNaviDelete );


    delete iNaviContainer;
    iNaviContainer = NULL;


    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviConstructL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviConstructL, "In TestNaviConstructL" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviConstructL );
    // Print to log file
    iLog->Log( KTestNaviConstructL );
    
    TInt err = KErrNone;
    TRAP( err, iNaviContainer->ConstructL() );
    
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviConstructFromResourceL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviConstructFromResourceL, "In TestNaviConstructFromResourceL" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviConstructFromResourceL );
    // Print to log file
    iLog->Log( KTestNaviConstructFromResourceL );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKNAVIPANE_NAVIDECORATOR );
    
    TInt err = KErrNone;
    TRAP( err, iNaviContainer->ConstructFromResourceL( reader ) );
    
    CleanupStack::PopAndDestroy();
    
    return err;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviConstructNavigationDecoratorFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviConstructNavigationDecoratorFromResourceL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestPlsnFWPHNewL, "In TestPlsnFWPHNewL" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestPlsnFWPHNewL );
    // Print to log file
    iLog->Log( KTestPlsnFWPHNewL );
    
    CAknNavigationDecorator* navidecorator;

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKNAVIPANE_NAVIDECORATOR );
    
    navidecorator = iNaviContainer->ConstructNavigationDecoratorFromResourceL( reader );
    STIF_ASSERT_NOT_NULL( navidecorator );
    
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviCreateTabGroupL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviCreateTabGroupL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviConstructNavigationDecoratorFromResourceL, "In TestNaviConstructNavigationDecoratorFromResourceL" );
    TestModuleIf().Printf( 0, testsdknavipane, 
        KTestNaviConstructNavigationDecoratorFromResourceL );
    // Print to log file
    iLog->Log( KTestNaviConstructNavigationDecoratorFromResourceL );
    
    CAknNavigationDecorator* navidecorator = iNaviContainer->CreateTabGroupL();
    CleanupStack::PushL( navidecorator );
    
    STIF_ASSERT_NOT_NULL( navidecorator );
    
    CleanupStack::Pop();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviCreateTabGroupLWithObserver
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviCreateTabGroupLWithObserverL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviCreateTabGroupLWithObserver, "In TestNaviCreateTabGroupLWithObserver" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviCreateTabGroupLWithObserver );
    // Print to log file
    iLog->Log( KTestNaviCreateTabGroupLWithObserver );
    
    CAknNavigationDecorator* navidecorator;
    CTestSDKNaviTabObserver observer;
    
  
    navidecorator = iNaviContainer->CreateTabGroupL(&observer);
    STIF_ASSERT_NOT_NULL( navidecorator );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviCreateTabGroupLWithRes
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviCreateTabGroupLWithResL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviCreateTabGroupLWithRes, "In TestNaviCreateTabGroupLWithRes" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviCreateTabGroupLWithRes );
    // Print to log file
    iLog->Log( KTestNaviCreateTabGroupLWithRes );
    
    CAknNavigationDecorator* navidecorator;
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKNAVIPANE_TABGROUP );
    
    navidecorator = iNaviContainer->CreateTabGroupL( reader);
    
    CleanupStack::PopAndDestroy();
    STIF_ASSERT_NOT_NULL( navidecorator );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviCreateTabGroupLWithResAndObserver
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviCreateTabGroupLWithResAndObserverL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviCreateTabGroupLWithResAndObserver, "In TestNaviCreateTabGroupLWithResAndObserver" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviCreateTabGroupLWithResAndObserver );
    // Print to log file
    iLog->Log( KTestNaviCreateTabGroupLWithResAndObserver );
    
    CAknNavigationDecorator* navidecorator;
    CTestSDKNaviTabObserver observer;
    
    TResourceReader reader;    
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKNAVIPANE_TABGROUP );
        
    navidecorator = iNaviContainer->CreateTabGroupL( reader, &observer );
    STIF_ASSERT_NOT_NULL( navidecorator );
    
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviCreateNavigationLabelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviCreateNavigationLabelL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviCreateNavigationLabelL, "In TestNaviCreateNavigationLabelL" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviCreateNavigationLabelL );
    // Print to log file
    iLog->Log( KTestNaviCreateNavigationLabelL );

    TInt err = KErrNone;
    
    _LIT( KLabel, "NavigationPane Label" );
    TRAP( err, iNaviContainer->CreateNavigationLabelL( KLabel ) );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviCreateNavigationLabelLWithResL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviCreateNavigationLabelLWithResL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviCreateNavigationLabelLWithResL, "In TestNaviCreateNavigationLabelLWithResL" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviCreateNavigationLabelLWithResL );
    // Print to log file
    iLog->Log( KTestNaviCreateNavigationLabelLWithResL );

    TInt err = KErrNone;
    
    TResourceReader reader;    
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKNAVIPANE_NAVILABEL );
    
    TRAP( err, iNaviContainer->CreateNavigationLabelL( reader ) );
    
    CleanupStack::PopAndDestroy();
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviCreateNavigationImageL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviCreateNavigationImageL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviCreateNavigationImageL, "In TestNaviCreateNavigationImageL" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviCreateNavigationImageL );
    // Print to log file
    iLog->Log( KTestNaviCreateNavigationImageL );

    TInt err = KErrNone;
    
    TSize size( 100, 80 );
    CFbsBitmap* bmp = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bmp );
    bmp->Create( size, ERgb );
    
    CAknNavigationDecorator* navidecorator;
    navidecorator = iNaviContainer->CreateNavigationImageL( bmp );
    
    STIF_ASSERT_NOT_NULL( navidecorator );
    
    CleanupStack::Pop( bmp );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviCreateNavigationImageLWithResL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviCreateNavigationImageLWithResL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviCreateNavigationImageLWithResL, "In TestNaviCreateNavigationImageLWithResL" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviCreateNavigationImageLWithResL );
    // Print to log file
    iLog->Log( KTestNaviCreateNavigationImageLWithResL );

    TInt err = KErrNone;
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKNAVIPANE_NAVIIMAGE );
    
    CAknNavigationDecorator* navidecorator;
    navidecorator = iNaviContainer->CreateNavigationImageL( reader );
    
    STIF_ASSERT_NOT_NULL( navidecorator );
    
    CleanupStack::PopAndDestroy(); // reader          
        
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviCreateMessageLabelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviCreateMessageLabelL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviCreateMessageLabelL, "In TestNaviCreateMessageLabelL" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviCreateMessageLabelL );
    // Print to log file
    iLog->Log( KTestNaviCreateMessageLabelL );

    TInt err = KErrNone;
    
    _LIT( KNaviMsgLabel, "Navigation message" );
    
    CAknNavigationDecorator* navidecorator;
    navidecorator = iNaviContainer->CreateMessageLabelL( KNaviMsgLabel );
        
    STIF_ASSERT_NOT_NULL( navidecorator );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviCreateMessageLabelLWithResL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviCreateMessageLabelLWithResL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviCreateMessageLabelLWithResL, "In TestNaviCreateMessageLabelLWithResL" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviCreateMessageLabelLWithResL );
    // Print to log file
    iLog->Log( KTestNaviCreateMessageLabelLWithResL );

    TInt err = KErrNone;
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKNAVIPANE_NAVILABEL );
    
    CAknNavigationDecorator* navidecorator;
    navidecorator = iNaviContainer->CreateMessageLabelL( reader );
    
    STIF_ASSERT_NOT_NULL( navidecorator );
    
    CleanupStack::PopAndDestroy(); // reader
        
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviCreateVolumeIndicatorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviCreateVolumeIndicatorL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviCreateVolumeIndicatorL, "In TestNaviCreateVolumeIndicatorL" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviCreateVolumeIndicatorL );
    // Print to log file
    iLog->Log( KTestNaviCreateVolumeIndicatorL );

    TInt err = KErrNone;
    
    CAknNavigationDecorator* navidecorator;
    navidecorator = iNaviContainer->CreateVolumeIndicatorL( R_TESTSDKNAVIPANE_VOLUME_INDICATOR );
    
    STIF_ASSERT_NOT_NULL( navidecorator );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviCreateEditorIndicatorContainerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviCreateEditorIndicatorContainerL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviCreateEditorIndicatorContainerL, "In TestNaviCreateEditorIndicatorContainerL" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviCreateEditorIndicatorContainerL );
    // Print to log file
    iLog->Log( KTestNaviCreateEditorIndicatorContainerL );

    TInt err = KErrNone;
    
    CAknNavigationDecorator* navidecorator;
    navidecorator = iNaviContainer->CreateEditorIndicatorContainerL( );
    
    STIF_ASSERT_NOT_NULL( navidecorator );
    
    return err;
    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviPushDefaultL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviPushDefaultL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviPushDefaultL, "In TestNaviPushDefaultL" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviPushDefaultL );
    // Print to log file
    iLog->Log( KTestNaviPushDefaultL );

    TInt err = KErrNone;
        
    TRAP( err, iNaviContainer->PushDefaultL() );
    
    return err;
    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviPushL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviPushL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviPushL, "In TestNaviPushL" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviPushL );
    // Print to log file
    iLog->Log( KTestNaviPushL );

    TInt err = KErrNone;
    
    _LIT( KNaviLabel, "Navigation Label" );
    CAknNavigationDecorator* newNaviDe = 
        iNaviContainer->CreateMessageLabelL( KNaviLabel );
    
    TRAP( err, iNaviContainer->PushL( *newNaviDe ) );
    iNaviContainer->Pop();
    
    return err;
    }




// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviPop
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviPop( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviPop, "In TestNaviPop" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviPop );
    // Print to log file
    iLog->Log( KTestNaviPop );

    TInt err = KErrNone;
   
    TRAP( err, iNaviContainer->Pop() );
    
    return err;
    }




// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviPopWithControl
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviPopWithControl( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviPopWithControl, "In TestNaviPopWithControl" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviPopWithControl );
    // Print to log file
    iLog->Log( KTestNaviPopWithControl );

    TInt err = KErrNone;
     
    CAknNavigationDecorator* oldNaviDe = iNaviContainer->Top();
    TRAP( err, iNaviContainer->Pop( oldNaviDe ) );
    
    return err;
    }




// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviTop
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviTopL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviTop, "In TestNaviTop" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviTop );
    // Print to log file
    iLog->Log( KTestNaviTop );

    TInt err = KErrNone;
    
    _LIT( KNaviLabel, "Navigation Label" );
    CAknNavigationDecorator* newNaviDe = 
        iNaviContainer->CreateMessageLabelL( KNaviLabel );
    iNaviContainer->PushL( *newNaviDe );
    
    CAknNavigationDecorator* oldNaviDe = iNaviContainer->Top();
    
    STIF_ASSERT_NOT_NULL( oldNaviDe );
    
    iNaviContainer->Pop();
    
    return err;
    }




// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviTopWithBool
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviTopWithBoolL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviTopWithBool, "In TestNaviTopWithBool" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviTopWithBool );
    // Print to log file
    iLog->Log( KTestNaviTopWithBool );

    TInt err = KErrNone;
    
    _LIT( KNaviLabel, "Navigation Label" );
    CAknNavigationDecorator* newNaviDe = 
        iNaviContainer->CreateMessageLabelL( KNaviLabel );
    iNaviContainer->PushL( *newNaviDe );
    
    CAknNavigationDecorator* naviDe = iNaviContainer->Top(ETrue);
    
    STIF_ASSERT_NOT_NULL( naviDe );
    
    iNaviContainer->Pop();
    
    return err;
    }




// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviReplaceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviReplaceL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviReplaceL, "In TestNaviReplaceL" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviReplaceL );
    // Print to log file
    iLog->Log( KTestNaviReplaceL );

    TInt err = KErrNone;
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKNAVIPANE_NAVILABEL );
    
    CAknNavigationDecorator* oldNaviDe;
    oldNaviDe = iNaviContainer->CreateMessageLabelL( reader ); 
    
    CleanupStack::PopAndDestroy();
    
    iNaviContainer->PushL( *oldNaviDe );
    
    _LIT( KNaviLabel, "Navigation Label" );
    CAknNavigationDecorator* newNaviDe = 
        iNaviContainer->CreateMessageLabelL( KNaviLabel );
    
    CleanupStack::PushL( newNaviDe );
    
    TRAP( err, iNaviContainer->ReplaceL( *oldNaviDe, *newNaviDe ) );
    
    iNaviContainer->Pop();
    
    CleanupStack::PopAndDestroy( newNaviDe ); 
    
    return err;
    }




// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviResourceDecorator
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviResourceDecorator( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviResourceDecorator, "In TestNaviResourceDecorator" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviResourceDecorator );
    // Print to log file
    iLog->Log( KTestNaviResourceDecorator );

    TInt err = KErrNone;
        
    CAknNavigationDecorator* navidecorator = iNaviContainer->ResourceDecorator();
    
    STIF_ASSERT_NOT_NULL( navidecorator );
    
    return err;
    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviSetPreferredNaviDecoratorLayoutStyle
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviSetPreferredNaviDecoratorLayoutStyle( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviSetPreferredNaviDecoratorLayoutStyle, "In TestNaviSetPreferredNaviDecoratorLayoutStyle" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviSetPreferredNaviDecoratorLayoutStyle );
    // Print to log file
    iLog->Log( KTestNaviSetPreferredNaviDecoratorLayoutStyle );

    TInt err = KErrNone;
    TInt layoutType = CAknNavigationDecorator::ENaviControlLayoutNormal;    
    
    TRAP( err, iNaviContainer->SetPreferredNaviDecoratorLayoutStyle( layoutType ) );
    
    return err;
    }



// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviColorScheme
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviColorScheme( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviColorScheme, "In TestNaviColorScheme" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviColorScheme );
    // Print to log file
    iLog->Log( KTestNaviColorScheme );

    TInt err = KErrNone;    
        
    TRAP( err, TInt colorScheme = CAknNavigationControlContainer::ColorScheme() );
    
    return err;
    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviHandlePointerEventL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviHandlePointerEventL, "In TestNaviHandlePointerEventL" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestNaviHandlePointerEventL );

    TInt err = KErrNone;
        
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    TRAP( err, iNaviContainer->HandlePointerEventL( event ) );
    
    return err;
    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviSizeChangedL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviSizeChangedL, "In TestNaviSizeChangedL" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviSizeChangedL );
    // Print to log file
    iLog->Log( KTestNaviSizeChangedL );

    TInt err = KErrNone;
        
    iNaviContainerExt = new (ELeave) CAknNavigationControlContainerExt;
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKNAVIPANE_NAVIDECORATOR );
    
    iNaviContainerExt->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TRAP( err, iNaviContainerExt->SizeChanged() );
    
    return err;
    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviHandleResourceChangeL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviHandleResourceChangeL, "In TestNaviHandleResourceChangeL" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviHandleResourceChangeL );
    // Print to log file
    iLog->Log( KTestNaviHandleResourceChangeL );

    TInt err = KErrNone;
    
    iNaviContainerExt = new (ELeave) CAknNavigationControlContainerExt;
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKNAVIPANE_NAVIDECORATOR );
    
    iNaviContainerExt->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TInt type = KEikMessageWindowsFadeChange;
    
    TRAP( err, iNaviContainerExt->HandleResourceChange( type ) );
        
    return err;
    }



// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviCountComponentControlsL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviCountComponentControls, "In TestNaviCountComponentControls" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviCountComponentControls );
    // Print to log file
    iLog->Log( KTestNaviCountComponentControls );

    TInt err = KErrNone;
    
    iNaviContainerExt = new (ELeave) CAknNavigationControlContainerExt;
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKNAVIPANE_NAVIDECORATOR );
    
    iNaviContainerExt->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TInt count = iNaviContainerExt->CountComponentControls();
    
    STIF_ASSERT_EQUALS( count, 2 );
        
    return err;
    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviComponentControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviComponentControlL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviComponentControl, "In TestNaviComponentControl" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviComponentControl );
    // Print to log file
    iLog->Log( KTestNaviComponentControl );

    TInt err = KErrNone;
        
    iNaviContainerExt = new (ELeave) CAknNavigationControlContainerExt;
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKNAVIPANE_NAVIDECORATOR );
    
    iNaviContainerExt->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CCoeControl* control = iNaviContainerExt->ComponentControl( 1 );
    
    STIF_ASSERT_NOT_NULL( control );
        
    return err;
    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviHandleControlEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviHandleControlEventL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviHandleControlEventL, "In TestNaviHandleControlEventL" );
    TestModuleIf().Printf( 0, testsdknavipane, KTestNaviHandleControlEventL );
    // Print to log file
    iLog->Log( KTestNaviHandleControlEventL );

    TInt err = KErrNone;
        
    iNaviContainerExt = new (ELeave) CAknNavigationControlContainerExt();
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKNAVIPANE_NAVIDECORATOR );
    
    iNaviContainerExt->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    MCoeControlObserver::TCoeEvent eventType = MCoeControlObserver::EEventStateChanged;
    CCoeControl* control = iNaviContainerExt->ComponentControl( 1 );
    
    TRAP( err, iNaviContainerExt->HandleControlEventL( control, eventType ) );
                    
    return err;
    }

// End of file
