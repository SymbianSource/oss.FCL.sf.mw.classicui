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
* Description:  test functions for EikSoftkeyImage.h
*
*/



// INCLUDE FILES
#include <eikbtgpc.h>
#include <akniconutils.h>
#include <eikimage.h>
#include <avkon.mbg>
#include <avkon.rsg>

#include "testdomextbuttons.h"
#include "testaknview.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtButtons::TestEikSoftkeyImageSetImageL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtButtons::TestEikSoftkeyImageSetImageL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtButtons, "TestDomExtButtons" );
    _LIT( KTestEikSoftkeyImageSetImageL, "TestEikSoftkeyImageSetImageL" );
    TestModuleIf().Printf( 0, KTestDomExtButtons, KTestEikSoftkeyImageSetImageL );
    // Print to log file
    iLog->Log( KTestEikSoftkeyImageSetImageL );
    
    CTestAknView* observer = new ( ELeave ) CTestAknView();
    CleanupStack::PushL( observer );
    observer->BaseConstructL();
    
    CEikButtonGroupContainer* container =
            CEikButtonGroupContainer::NewL( CEikButtonGroupContainer::ECba,
                    CEikButtonGroupContainer::EHorizontal, observer,
                    R_AVKON_SOFTKEYS_SELECT_CANCEL__SELECT );
    
    CEikImage* image = new ( ELeave ) CEikImage;
    CleanupStack::PushL( image );
    CFbsBitmap* bmp = AknIconUtils::CreateIconL( AknIconUtils::AvkonIconFileName(),
                                                EMbmAvkonQgn_indi_speaker_active );
    image->SetPicture( bmp );
   
    EikSoftkeyImage::SetImage( container, *image, ETrue );
    
    CleanupStack::PopAndDestroy( image );
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtButtons::TestEikSoftkeyImageSetLabelL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtButtons::TestEikSoftkeyImageSetLabelL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtButtons, "TestDomExtButtons" );
    _LIT( KTestEikSoftkeyImageSetLabelL, "TestEikSoftkeyImageSetLabelL" );
    TestModuleIf().Printf( 0, KTestDomExtButtons, KTestEikSoftkeyImageSetLabelL );
    // Print to log file
    iLog->Log( KTestEikSoftkeyImageSetLabelL );
    
    CTestAknView* observer = new ( ELeave ) CTestAknView();
    CleanupStack::PushL( observer );
    observer->BaseConstructL();
    
    CEikButtonGroupContainer* container =
            CEikButtonGroupContainer::NewL( CEikButtonGroupContainer::ECba,
                    CEikButtonGroupContainer::EHorizontal, observer,
                    R_AVKON_SOFTKEYS_SELECT_CANCEL__SELECT );
    
    EikSoftkeyImage::SetLabel( container, ETrue );
    
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    }


//  End of File
