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
* Description:  test AknPopupHeadingPane.h 
*
*/



// [INCLUDE FILES]

#include <aknpopupheadingpane.h>
#include <barsread.h>
#include <coemain.h>
#include <coeaui.h>
#include <eiklabel.h>
#include <akniconutils.h>
#include <testsdkpopups.rsg>
#include <avkon.mbg>

#include "testsdkpopups.hrh"
#include "testsdkpopups.h"
#include "testsdkpopupscontrol.h"

const TInt KLength = 20;
// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPHPCAknPopupHeadingPaneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPHPCAknPopupHeadingPaneL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupHeadingPane* headingPane = new (ELeave) CAknPopupHeadingPane;
    CleanupStack::PushL( headingPane );
    STIF_ASSERT_NOT_NULL( headingPane );
    
    CleanupStack::PopAndDestroy( headingPane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPHPDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPHPDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupHeadingPane* headingPane = new (ELeave) CAknPopupHeadingPane;
    CleanupStack::PushL( headingPane );
    STIF_ASSERT_NOT_NULL( headingPane );
    
    CleanupStack::Pop( headingPane );
    delete headingPane;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPHPSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPHPSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupHeadingPane* headingPane = new (ELeave) CAknPopupHeadingPane;
    CleanupStack::PushL( headingPane );
    STIF_ASSERT_NOT_NULL( headingPane );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_HEADING );
    headingPane->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    headingPane->SizeChanged();
    
    CleanupStack::PopAndDestroy( headingPane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPHPMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPHPMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupHeadingPane* headingPane = new (ELeave) CAknPopupHeadingPane;
    CleanupStack::PushL( headingPane );
    STIF_ASSERT_NOT_NULL( headingPane );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_HEADING );
    headingPane->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TSize size = headingPane->MinimumSize();
    TPoint point = size.AsPoint();
    STIF_ASSERT_NOT_EQUALS( point.iX, 0 );
    STIF_ASSERT_NOT_EQUALS( point.iY, 0 );
    
    CleanupStack::PopAndDestroy( headingPane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPHPConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPHPConstructL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupHeadingPane* headingPane = new (ELeave) CAknPopupHeadingPane;
    CleanupStack::PushL( headingPane );
    STIF_ASSERT_NOT_NULL( headingPane );
    
    _LIT( KText, "text" );
    TBuf<KLength> text( KText );
    headingPane->ConstructL( text );
    
    CleanupStack::PopAndDestroy( headingPane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPHPConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPHPConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupHeadingPane* headingPane = new (ELeave) CAknPopupHeadingPane;
    CleanupStack::PushL( headingPane );
    STIF_ASSERT_NOT_NULL( headingPane );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_HEADING );
    headingPane->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CleanupStack::PopAndDestroy( headingPane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPHPPromptL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPHPPromptL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupHeadingPane* headingPane = new (ELeave) CAknPopupHeadingPane;
    CleanupStack::PushL( headingPane );
    STIF_ASSERT_NOT_NULL( headingPane );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_HEADING );
    headingPane->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CEikLabel* label = headingPane->Prompt();
    STIF_ASSERT_NOT_NULL( label );
    
    _LIT( KLabel, "label" );
    STIF_ASSERT_TRUE( label->Text()->Compare( KLabel ) == 0 );
    
    CleanupStack::PopAndDestroy( headingPane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPHPPromptTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPHPPromptTextL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupHeadingPane* headingPane = new (ELeave) CAknPopupHeadingPane;
    CleanupStack::PushL( headingPane );
    STIF_ASSERT_NOT_NULL( headingPane );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_HEADING );
    headingPane->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    _LIT( KLabel, "label" );
    STIF_ASSERT_TRUE( headingPane->PromptText().Compare( KLabel ) == 0 );
    
    CleanupStack::PopAndDestroy( headingPane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPHPSetTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPHPSetTextL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupHeadingPane* headingPane = new (ELeave) CAknPopupHeadingPane;
    CleanupStack::PushL( headingPane );
    STIF_ASSERT_NOT_NULL( headingPane );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_HEADING );
    headingPane->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    _LIT( KText, "text" );
    TBuf<KLength> text( KText );
    headingPane->SetTextL( text );
    
    STIF_ASSERT_TRUE( headingPane->PromptText().Compare( text ) == 0 );
    
    CleanupStack::PopAndDestroy( headingPane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPHPSetHeaderImageOwnedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPHPSetHeaderImageOwnedL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupHeadingPane* headingPane = new (ELeave) CAknPopupHeadingPane;
    CleanupStack::PushL( headingPane );
    STIF_ASSERT_NOT_NULL( headingPane );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_HEADING );
    headingPane->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CEikImage* image =new (ELeave) CEikImage;
    CleanupStack::PushL( image );
    STIF_ASSERT_NOT_NULL( image );
    TResourceReader readerimage;
    CCoeEnv::Static()->CreateResourceReaderLC(readerimage, R_TESTSDK_IMAGE );
    image->ConstructFromResourceL( readerimage );
    CleanupStack::PopAndDestroy();
    
    headingPane->SetHeaderImageOwnedL( image );
    
    CleanupStack::Pop( image );
    CleanupStack::PopAndDestroy( headingPane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPHPSetHeaderImageL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPHPSetHeaderImageL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupHeadingPane* headingPane = new (ELeave) CAknPopupHeadingPane;
    CleanupStack::PushL( headingPane );
    STIF_ASSERT_NOT_NULL( headingPane );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_HEADING );
    headingPane->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    const TInt MaxLength = 50;
    _LIT( KFile, "\\resource\\apps\\avkon2.mbm" );
    TBuf<MaxLength> iconFile( KFile );

    CEikImage* image = new( ELeave ) CEikImage;
    CleanupStack::PushL( image );
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* bitmapM = NULL;
    AknIconUtils::CreateIconL( bitmap, bitmapM, iconFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask ); 

    CleanupStack::PushL( bitmap );
    CleanupStack::PushL( bitmapM );

    image->SetPictureOwnedExternally( TBool( 0 ) );
    image->SetPicture( bitmap, bitmapM );

    headingPane->SetHeaderImageL( image );

    CleanupStack::Pop( bitmapM );  
    CleanupStack::Pop( bitmap );
    CleanupStack::Pop( image );
    CleanupStack::PopAndDestroy( headingPane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPHPSetHeaderAnimationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPHPSetHeaderAnimationL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupHeadingPane* headingPane = new (ELeave) CAknPopupHeadingPane;
    CleanupStack::PushL( headingPane );
    STIF_ASSERT_NOT_NULL( headingPane );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_HEADING );
    headingPane->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    headingPane->SetHeaderAnimationL( R_TESTSDK_ANIMATION );
    
    CleanupStack::PopAndDestroy( headingPane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPHPSetLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPHPSetLayoutL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupHeadingPane* headingPane = new (ELeave) CAknPopupHeadingPane;
    CleanupStack::PushL( headingPane );
    STIF_ASSERT_NOT_NULL( headingPane );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_HEADING );
    headingPane->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    headingPane->SetLayout( CAknPopupHeadingPane::EListHeadingPane );
    
    CleanupStack::PopAndDestroy( headingPane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPHPStartAnimationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPHPStartAnimationL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKPopupsControl* control = new (ELeave) CTestSDKPopupsControl;
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknPopupHeadingPane* headingPane = new (ELeave) CAknPopupHeadingPane;
    CleanupStack::PushL( headingPane );
    STIF_ASSERT_NOT_NULL( headingPane );
    
    headingPane->SetContainerWindowL( *control );
    
    _LIT( KText, "text" );
    TBuf<KLength> text( KText );
    headingPane->ConstructL( text );
    
    headingPane->SetLayout( CAknPopupHeadingPane::EListHeadingPane );
    headingPane->SizeChanged();
    
    const TInt MaxLength = 50;
    _LIT( KFile, "\\resource\\apps\\avkon2.mbm" );
    TBuf<MaxLength> iconFile( KFile );

    CEikImage* image = new( ELeave ) CEikImage;
    CleanupStack::PushL( image );
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* bitmapM = NULL;
    AknIconUtils::CreateIconL( bitmap, bitmapM, iconFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask ); 

    CleanupStack::PushL( bitmap );
    CleanupStack::PushL( bitmapM );

    image->SetPictureOwnedExternally( TBool( 0 ) );
    image->SetPicture( bitmap, bitmapM );

    headingPane->SetHeaderImageL( image );

    CleanupStack::Pop( bitmapM );  
    CleanupStack::Pop( bitmap );
    CleanupStack::Pop( image );
    
    headingPane->SetHeaderAnimationL( R_TESTSDK_ANIMATION );
    
    TAknsItemID aknsItemID;
    headingPane->SetSkinFrameId( aknsItemID );
    headingPane->SetSkinFrameCenterId( aknsItemID );
    
    headingPane->StartAnimationL();
    
    CleanupStack::PopAndDestroy( headingPane );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPHPCancelAnimationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPHPCancelAnimationL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupHeadingPane* headingPane = new (ELeave) CAknPopupHeadingPane;
    CleanupStack::PushL( headingPane );
    STIF_ASSERT_NOT_NULL( headingPane );
    
//    TResourceReader reader;
//    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_HEADING );
//    headingPane->ConstructFromResourceL( reader );
//    CleanupStack::PopAndDestroy();
    
    _LIT( KText, "text" );
    TBuf<KLength> text( KText );
    headingPane->ConstructL( text );
    
    headingPane->SetLayout( CAknPopupHeadingPane::EListHeadingPane );
    
    const TInt MaxLength = 50;
    _LIT( KFile, "\\resource\\apps\\avkon2.mbm" );
    TBuf<MaxLength> iconFile( KFile );

    CEikImage* image = new( ELeave ) CEikImage;
    CleanupStack::PushL( image );
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* bitmapM = NULL;
    AknIconUtils::CreateIconL( bitmap, bitmapM, iconFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask ); 

    CleanupStack::PushL( bitmap );
    CleanupStack::PushL( bitmapM );

    image->SetPictureOwnedExternally( TBool( 0 ) );
    image->SetPicture( bitmap, bitmapM );

    headingPane->SetHeaderImageL( image );

    CleanupStack::Pop( bitmapM );  
    CleanupStack::Pop( bitmap );
    CleanupStack::Pop( image );
    
    CTestSDKPopupsControl* control = new (ELeave) CTestSDKPopupsControl;
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    headingPane->SetContainerWindowL( *control );
    
    headingPane->SetHeaderAnimationL( R_TESTSDK_ANIMATION );
    
    headingPane->StartAnimationL();
    headingPane->CancelAnimation();
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::Pop( headingPane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPHPHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPHPHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupHeadingPane* headingPane = new (ELeave) CAknPopupHeadingPane;
    CleanupStack::PushL( headingPane );
    STIF_ASSERT_NOT_NULL( headingPane );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_HEADING );
    headingPane->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    headingPane->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( headingPane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPHPHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPHPHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupHeadingPane* headingPane = new (ELeave) CAknPopupHeadingPane;
    CleanupStack::PushL( headingPane );
    STIF_ASSERT_NOT_NULL( headingPane );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_HEADING );
    headingPane->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    headingPane->HandleResourceChange( KAknsMessageSkinChange );
    headingPane->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    
    CleanupStack::PopAndDestroy( headingPane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPHPSetSkinFrameIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPHPSetSkinFrameIdL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupHeadingPane* headingPane = new (ELeave) CAknPopupHeadingPane;
    CleanupStack::PushL( headingPane );
    STIF_ASSERT_NOT_NULL( headingPane );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_HEADING );
    headingPane->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CTestSDKPopupsControl* control = new (ELeave) CTestSDKPopupsControl;
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    headingPane->SetContainerWindowL( *control );
    
    TAknsItemID aknsItemID;
    headingPane->SetSkinFrameId( aknsItemID );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( headingPane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPHPSetSkinFrameCenterIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPHPSetSkinFrameCenterIdL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupHeadingPane* headingPane = new (ELeave) CAknPopupHeadingPane;
    CleanupStack::PushL( headingPane );
    STIF_ASSERT_NOT_NULL( headingPane );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_HEADING );
    headingPane->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CTestSDKPopupsControl* control = new (ELeave) CTestSDKPopupsControl;
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    headingPane->SetContainerWindowL( *control );
    
    TAknsItemID aknsItemID;
    headingPane->SetSkinFrameCenterId( aknsItemID );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( headingPane );
    
    return KErrNone;
    
    }
