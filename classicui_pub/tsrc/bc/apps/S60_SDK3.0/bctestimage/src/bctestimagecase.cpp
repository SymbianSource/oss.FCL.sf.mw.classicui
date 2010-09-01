/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <fbs.h>
#include <eikimage.h>
#include <barsread.h>
#include <barsc.h>
#include <eikenv.h>
#include <bctestimage.rsg>

#include "bctestimagecase.h"
#include "bctestimagecontainer.h"
#include "bctestimage.hrh"
#include "bctestimage_pro.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestImageCase* CBCTestImageCase::NewL( 
    CBCTestImageContainer* aContainer )
    {
    CBCTestImageCase* self = new( ELeave ) CBCTestImageCase( 
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestImageCase::CBCTestImageCase( 
    CBCTestImageContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestImageCase::~CBCTestImageCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestImageCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestImageCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestImageCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( LeftCBA, KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestImageCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestImageCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline1 )
        {
        return;
        }
    // Call release before prepare to let container has time to draw the 
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    switch ( aCmd )  
        {
        case EBCTestCmdOutline1:
            TestFunctionL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestImageCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestImageCase::PrepareCaseL( TInt aCmd )
    {        
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            // Here is a simple demo. You should create your control 
            // instead of this.
            iControl = new( ELeave ) CCoeControl();            
            iControl->SetContainerWindowL( *iContainer );
            iControl->MakeVisible( ETrue );
            break;
        default:
            break;
        }
    // Pass the owner of iControl to iContainer.
    iContainer->SetControl( iControl );
    }

// ---------------------------------------------------------------------------
// CBCTestImageCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestImageCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestImageCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestImageCase::TestFunctionL()
    {
    _LIT( strBitmap,"Class CEikImage Function Bitmap tested" );
    _LIT( strConstructFromResourceL,"Class CEikImage Function ConstructFromResourceL tested" );
    _LIT( strCreatePictureFromFileL,"Class CEikImage Function CreatePictureFromFileL tested" );
    _LIT( strHandlePointerEventL,"Class CEikImage Function HandlePointerEventL tested" );
    _LIT( strIsPictureOwnedExternally,"Class CEikImage Function IsPictureOwnedExternally tested" );
    _LIT( strMask,"Class CEikImage Function Masktested" );
    _LIT( strMinimumSize,"Class CEikImage Function MinimumSize tested" );
    _LIT( strSetBitmap,"Class CEikImage Function SetBitmap tested" );
    _LIT( strSetBrushStyle,"Class CEikImage Function SetBrushStyle tested" );
    _LIT( strSetEmphasis,"Class CEikImage Function SetSetEmphasis tested" );
    _LIT( strSetMask,"Class CEikImage Function SetMask tested" );
    _LIT( strSetNewBitmaps,"Class CEikImage Function SetNewBitmaps tested" );
    _LIT( strSetPicture,"Class CEikImage Function SetPicture tested" );
    _LIT( strSetPictureOwnedExternally,"Class CEikImage Function SetPictureOwnedExternally tested" );
    _LIT( strWriteInternalStateL,"Class CEikImage Function WriteInternalStateL tested" );
    
    //create hEikImge, hBitmap, hMask
    CEikImage* hEikImage = new ( ELeave ) CEikImage();
   
    CFbsBitmap* hBitmap = new (ELeave) CFbsBitmap();
    CFbsBitmap* hMask = new (ELeave) CFbsBitmap();
    
    
    hEikImage ->SetBitmap(hBitmap);
    AssertNotNullL( hEikImage, strSetBitmap );
    
    hEikImage->SetMask(hMask);
    AssertNotNullL( hEikImage, strSetMask );
    
    hEikImage->Bitmap();
    AssertNotNullL( hEikImage, strBitmap );
    
    hEikImage->Mask();
    AssertNotNullL( hEikImage, strMask);
    
    
    hEikImage->SetPicture(hBitmap, hMask);
    AssertNotNullL( hEikImage, strSetPicture);
    
    
    CFbsBitmap* jBitmap = new (ELeave) CFbsBitmap();
    CFbsBitmap* jMask = new (ELeave) CFbsBitmap();
    
    hEikImage->SetNewBitmaps(jBitmap, jMask);
    AssertNotNullL( hEikImage, strSetNewBitmaps);
    

    //=================================================
    
    hEikImage->SetEmphasis(ETrue);
    AssertTrueL( ETrue, strSetEmphasis);
    
    hEikImage->SetPictureOwnedExternally(ETrue);
    AssertTrueL( ETrue, strSetPictureOwnedExternally);
    
    TBool abool = hEikImage->IsPictureOwnedExternally();
    AssertTrueL( ETrue, strIsPictureOwnedExternally);
    
    hEikImage->SetBrushStyle(CGraphicsContext::ESolidBrush);
    AssertTrueL( ETrue, strSetBrushStyle);
    
    TPointerEvent pointerEvent;
    CleanupStack::PushL( hEikImage );
    hEikImage->HandlePointerEventL( pointerEvent );
    AssertNotNullL( hEikImage,strHandlePointerEventL );
    
    CleanupStack::PopAndDestroy(hEikImage );
    hEikImage = NULL;
    
    //==================================================
            
    CEikImage* jEikImage = new ( ELeave ) CEikImage();
    CleanupStack::PushL( jEikImage );
    _LIT(KAknResourceFileName, "z:\\resource\\apps\\BCTestImage_Aif.mbm");
    jEikImage->CreatePictureFromFileL(KAknResourceFileName, 0);
    AssertTrueL( ETrue,strCreatePictureFromFileL );
    
    
    jEikImage->MinimumSize();
    AssertTrueL( ETrue, strMinimumSize );
    
    CleanupStack::PopAndDestroy(jEikImage);
    jEikImage=NULL;
    
    //==================================================
    CEikImage* kEikImage = new ( ELeave ) CEikImage();
    CleanupStack::PushL( kEikImage );
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_BCTESTIMAGE_AIMAGE );
    kEikImage->ConstructFromResourceL( reader );
    AssertTrueL( ETrue,strConstructFromResourceL );
    CleanupStack::PopAndDestroy(2, kEikImage);
    kEikImage=NULL;
    
    //==================================================
    CBCTestImage_pro* testImagePtr = new (ELeave) CBCTestImage_pro();
    CleanupStack::PushL(testImagePtr);
    testImagePtr->testWriteInternalL();
    AssertTrueL( ETrue, strWriteInternalStateL);
    CleanupStack::PopAndDestroy(testImagePtr);
    testImagePtr=NULL;
    }
    
