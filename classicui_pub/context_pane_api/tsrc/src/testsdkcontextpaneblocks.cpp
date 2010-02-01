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
* Description:  Description
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <akncontext.h>
#include <barsread.h>
#include <eikenv.h>
#include <eikimage.h>
#include <akniconutils.h>
#include <fbs.h>
#include <coeaui.h>

#include <avkon.mbg>
#include <testsdkcontextpane.rsg>
#include "testsdkcontextpane.h"
#include "testsdkcpcontainer.h"
#include "testsdkcpcontextpane.h"

const TInt KUnexpected = 0;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdkcontextpane::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKContextPane::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctestsdkcontextpane::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKContextPane::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestCTXTPConstructor", CTestSDKContextPane::TestCTXTPConstructorL ),
        ENTRY( "TestCTXTPDestructor", CTestSDKContextPane::TestCTXTPDestructor ),
        ENTRY( "TestCTXTPConstructL", CTestSDKContextPane::TestCTXTPConstructL ),
        ENTRY( "TestCTXTPConstructFromResourceL", CTestSDKContextPane::TestCTXTPConstructFromResourceL ),
        ENTRY( "TestCTXTPSetPictureUseBitmap", CTestSDKContextPane::TestCTXTPSetPictureUseBitmapL ),
        ENTRY( "TestCTXTPSetPictureUseImage", CTestSDKContextPane::TestCTXTPSetPictureUseImageL ),
        ENTRY( "TestCTXTPSetPictureFromFileL", CTestSDKContextPane::TestCTXTPSetPictureFromFileL ),
        ENTRY( "TestCTXTPSetFromResourceL", CTestSDKContextPane::TestCTXTPSetFromResourceL ),
        ENTRY( "TestCTXTPSetPictureToDefaultL", CTestSDKContextPane::TestCTXTPSetPictureToDefaultL ),
        ENTRY( "TestCTXTPPicture", CTestSDKContextPane::TestCTXTPPicture ),
        ENTRY( "TestCTXTPSwapPicture", CTestSDKContextPane::TestCTXTPSwapPictureL ),
        ENTRY( "TestCTXTPHandlePointerEventL", CTestSDKContextPane::TestCTXTPHandlePointerEventL ),
        ENTRY( "TestCTXTPSizeChanged", CTestSDKContextPane::TestCTXTPSizeChangedL ),
        ENTRY( "TestCTXTPHandleResourceChange", CTestSDKContextPane::TestCTXTPHandleResourceChangeL ),
        ENTRY( "TestCTXTPCountComponentControls", CTestSDKContextPane::TestCTXTPCountComponentControlsL ),
        ENTRY( "TestCTXTPComponentControl", CTestSDKContextPane::TestCTXTPComponentControlL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestCTXTPConstructor
// constructor test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKContextPane::TestCTXTPConstructorL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkcontextpane, "testsdkcontextpane" );
    _LIT( KTestCTXTPConstructor, "In TestCTXTPConstructor" );
    TestModuleIf().Printf( 0, Ktestsdkcontextpane, KTestCTXTPConstructor );
    // Print to log file
    iLog->Log( KTestCTXTPConstructor );

    iContextPane = new( ELeave ) CAknContextPane();
    STIF_ASSERT_NOT_NULL( iContextPane );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestCTXTPDestructor
// destructor test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKContextPane::TestCTXTPDestructor( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkcontextpane, "testsdkcontextpane" );
    _LIT( KTestCTXTPDestructor, "In TestCTXTPDestructor" );
    TestModuleIf().Printf( 0, Ktestsdkcontextpane, KTestCTXTPDestructor );
    // Print to log file
    iLog->Log( KTestCTXTPDestructor );

    delete iContextPane;
    iContextPane = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestCTXTPConstructL
// ConstructL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKContextPane::TestCTXTPConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkcontextpane, "testsdkcontextpane" );
    _LIT( KTestCTXTPConstructL, "In TestCTXTPConstructL" );
    TestModuleIf().Printf( 0, Ktestsdkcontextpane, KTestCTXTPConstructL );
    // Print to log file
    iLog->Log( KTestCTXTPConstructL );

    iContextPane->SetContainerWindowL( *iContainer );
    TInt err = KErrNone;
    TRAP( err, iContextPane->ConstructL() );

    return err;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestCTXTPConstructFromResourceL
// ConstructFromResourceL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKContextPane::TestCTXTPConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkcontextpane, "testsdkcontextpane" );
    _LIT( KTestCTXTPConstructFromResourceL, "In TestCTXTPConstructFromResourceL" );
    TestModuleIf().Printf( 0, Ktestsdkcontextpane, KTestCTXTPConstructFromResourceL );
    // Print to log file
    iLog->Log( KTestCTXTPConstructFromResourceL );

    
    TInt err = KErrNone;
    TResourceReader reader;
    iEikonEnvPointer = CCoeEnv::Static();
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTSDK_CONTEXT_PANE );

    TRAP( err, iContextPane->ConstructFromResourceL( reader ) );

    CleanupStack::Pop();
    return err;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestCTXTPSetPictureUseBitmap
// SetPictureUseBitmapL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKContextPane::TestCTXTPSetPictureUseBitmapL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkcontextpane, "testsdkcontextpane" );
    _LIT( KTestCTXTPSetPictureUseBitmap, "In TestCTXTPSetPictureUseBitmap" );
    TestModuleIf().Printf( 0, Ktestsdkcontextpane, KTestCTXTPSetPictureUseBitmap );
    // Print to log file
    iLog->Log( KTestCTXTPSetPictureUseBitmap );

    const TSize KSize( 100, 80 );
    CFbsBitmap* bmp = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bmp );
    bmp->Create( KSize, ERgb );        
    iContextPane->SetPicture( bmp );
    CleanupStack::Pop( bmp );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestCTXTPSetPictureUseImage
// SetPictureUseImageL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKContextPane::TestCTXTPSetPictureUseImageL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkcontextpane, "testsdkcontextpane" );
    _LIT( KTestCTXTPSetPictureUseImage, "In TestCTXTPSetPictureUseImage" );
    TestModuleIf().Printf( 0, Ktestsdkcontextpane, KTestCTXTPSetPictureUseImage );
    // Print to log file
    iLog->Log( KTestCTXTPSetPictureUseImage );

    CEikImage* image = new( ELeave ) CEikImage();
    CleanupStack::PushL( image );
    image->CreatePictureFromFileL( AknIconUtils::AvkonIconFileName(), 
        EMbmAvkonQgn_indi_signal_strength,
        EMbmAvkonQgn_indi_signal_strength_mask );
    iContextPane->SetPicture( image );
    CleanupStack::Pop( image );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestCTXTPSetPictureFromFileL
// SetPictureFromFileL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKContextPane::TestCTXTPSetPictureFromFileL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkcontextpane, "testsdkcontextpane" );
    _LIT( KTestCTXTPDestructor, "In TestCTXTPDestructor" );
    TestModuleIf().Printf( 0, Ktestsdkcontextpane, KTestCTXTPDestructor );
    // Print to log file
    iLog->Log( KTestCTXTPDestructor );

    TInt err = KErrNone;
    TRAP( err, iContextPane->SetPictureFromFileL( AknIconUtils::AvkonIconFileName(), 
        EMbmAvkonQgn_indi_signal_strength,
        EMbmAvkonQgn_indi_signal_strength_mask ) );

    return err;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestCTXTPSetFromResourceL
// SetFromResourceL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKContextPane::TestCTXTPSetFromResourceL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkcontextpane, "testsdkcontextpane" );
    _LIT( KTestCTXTPDestructor, "In TestCTXTPDestructor" );
    TestModuleIf().Printf( 0, Ktestsdkcontextpane, KTestCTXTPDestructor );
    // Print to log file
    iLog->Log( KTestCTXTPDestructor );

    TInt err = KErrNone;
    TResourceReader reader;
    iEikonEnvPointer = CCoeEnv::Static();
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTSDK_CONTEXT_PANE );

    TRAP( err, iContextPane->SetFromResourceL( reader ) );

    CleanupStack::Pop();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestCTXTPSetPictureToDefaultL
// SetPictureToDefaultL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKContextPane::TestCTXTPSetPictureToDefaultL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkcontextpane, "testsdkcontextpane" );
    _LIT( KTestCTXTPDestructor, "In TestCTXTPDestructor" );
    TestModuleIf().Printf( 0, Ktestsdkcontextpane, KTestCTXTPDestructor );
    // Print to log file
    iLog->Log( KTestCTXTPDestructor );

    TInt err = KErrNone;
    TRAP( err, iContextPane->SetPictureToDefaultL() );

    return err;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestCTXTPPicture
// Picture test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKContextPane::TestCTXTPPicture( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkcontextpane, "testsdkcontextpane" );
    _LIT( KTestCTXTPDestructor, "In TestCTXTPDestructor" );
    TestModuleIf().Printf( 0, Ktestsdkcontextpane, KTestCTXTPDestructor );
    // Print to log file
    iLog->Log( KTestCTXTPDestructor );

    const CEikImage& image = iContextPane->Picture();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestCTXTPSwapPicture
// SwapPicture test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKContextPane::TestCTXTPSwapPictureL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkcontextpane, "testsdkcontextpane" );
    _LIT( KTestCTXTPDestructor, "In TestCTXTPDestructor" );
    TestModuleIf().Printf( 0, Ktestsdkcontextpane, KTestCTXTPDestructor );
    // Print to log file
    iLog->Log( KTestCTXTPDestructor );

    CEikImage* image = new( ELeave ) CEikImage();
    CleanupStack::PushL( image );
    image->CreatePictureFromFileL( AknIconUtils::AvkonIconFileName(), 
        EMbmAvkonQgn_indi_signal_strength,
        EMbmAvkonQgn_indi_signal_strength_mask );
    iContextPane->SetPicture( image );

    CEikImage* oldImage = iContextPane->SwapPicture( NULL );
    
    STIF_ASSERT_EQUALS( image, oldImage );
    CleanupStack::Pop( image );
    delete oldImage;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestCTXTPHandlePointerEventL
// HandlePointerEventL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKContextPane::TestCTXTPHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkcontextpane, "testsdkcontextpane" );
    _LIT( KTestCTXTPDestructor, "In TestCTXTPDestructor" );
    TestModuleIf().Printf( 0, Ktestsdkcontextpane, KTestCTXTPDestructor );
    // Print to log file
    iLog->Log( KTestCTXTPDestructor );

    iContextPane->SetContainerWindowL( *iContainer );
    iContextPane->ConstructL();

    TInt err = KErrNone;
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    const TPoint KEventPos( 10, 30 ); 
    event.iPosition = KEventPos;
    event.iParentPosition = KEventPos;
    
    TRAP( err, iContextPane->HandlePointerEventL( event ) );

    return err;
    }
//==============================FOR PROTECTED FUNCTIONS=========================
//
// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestCTXTPSizeChanged
// SizeChanged test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKContextPane::TestCTXTPSizeChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkcontextpane, "testsdkcontextpane" );
    _LIT( KTestCTXTPDestructor, "In TestCTXTPDestructor" );
    TestModuleIf().Printf( 0, Ktestsdkcontextpane, KTestCTXTPDestructor );
    // Print to log file
    iLog->Log( KTestCTXTPDestructor );

    CTestSDKCPContextPane* context = new( ELeave ) CTestSDKCPContextPane();
    CleanupStack::PushL( context );
    context->SetContainerWindowL( *iContainer );
    context->ConstructL();
    
    context->SizeChanged();

    CleanupStack::PopAndDestroy( context );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestCTXTPHandleResourceChange
// HandleResourceChange test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKContextPane::TestCTXTPHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkcontextpane, "testsdkcontextpane" );
    _LIT( KTestCTXTPDestructor, "In TestCTXTPDestructor" );
    TestModuleIf().Printf( 0, Ktestsdkcontextpane, KTestCTXTPDestructor );
    // Print to log file
    iLog->Log( KTestCTXTPDestructor );

    CTestSDKCPContextPane* context = new( ELeave ) CTestSDKCPContextPane();
    CleanupStack::PushL( context );
    context->SetContainerWindowL( *iContainer );
    context->ConstructL();
    
    context->HandleResourceChange( KEikColorResourceChange );

    CleanupStack::PopAndDestroy( context );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestCTXTPCountComponentControls
// CountComponentControls test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKContextPane::TestCTXTPCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkcontextpane, "testsdkcontextpane" );
    _LIT( KTestCTXTPDestructor, "In TestCTXTPDestructor" );
    TestModuleIf().Printf( 0, Ktestsdkcontextpane, KTestCTXTPDestructor );
    // Print to log file
    iLog->Log( KTestCTXTPDestructor );

    
    CTestSDKCPContextPane* context = new( ELeave ) CTestSDKCPContextPane();
    CleanupStack::PushL( context );
    context->SetContainerWindowL( *iContainer );
    context->ConstructL();
    
    TInt count = context->CountComponentControls();
    
    STIF_ASSERT_NOT_EQUALS( KUnexpected, count );

    CleanupStack::PopAndDestroy( context );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestCTXTPComponentControl
// ComponentControl test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKContextPane::TestCTXTPComponentControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkcontextpane, "testsdkcontextpane" );
    _LIT( KTestCTXTPDestructor, "In TestCTXTPDestructor" );
    TestModuleIf().Printf( 0, Ktestsdkcontextpane, KTestCTXTPDestructor );
    // Print to log file
    iLog->Log( KTestCTXTPDestructor );

    CTestSDKCPContextPane* context = new( ELeave ) CTestSDKCPContextPane();
    CleanupStack::PushL( context );
    context->SetContainerWindowL( *iContainer );
    context->ConstructL();

    TInt count = context->CountComponentControls();
    CCoeControl* ctrl = context->ComponentControl( count - 1 );
    STIF_ASSERT_NOT_NULL( ctrl );
    
    CleanupStack::PopAndDestroy( context );

    return KErrNone;
    }

//  [End of File]
