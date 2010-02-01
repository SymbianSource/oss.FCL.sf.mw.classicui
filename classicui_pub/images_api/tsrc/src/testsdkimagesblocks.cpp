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
* Description:  Test eikimage.h
*
*/



/*
 *  [INCLUDE FILES]
 */
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <eikimage.h>
#include <avkon.mbg>
#include <aknutils.h>
#include <fbs.h>
#include <w32std.h>
#include <testsdkimages.rsg>
#include <barsread.h>
#include <s32std.h>
#include <s32mem.h>
#include <s32file.h>
#include <bautils.h>
#include <f32file.h>
#include <akniconutils.h>

#include "testsdkimages.h"

/*
 * Descriptor declare
 * */
_LIT(KMbmFile,"\\resource\\apps\\avkon2.mbm");

/** 
 * Class CTestImage inherit from CEikImage for test 
 * CEikImage class's protected function
 */
class CTestImage:public CEikImage
    {
    /**
     * public function
     */
public:
    /**
     * construction
     */
    CTestImage()
        {
        
        }
    /**
     * destructor
     * */
    ~CTestImage()
        {
        
        }
    /**
     * This function is CEikImage's protected function,
     * It inherit from CEikImage class
     */ 
    void DoWriteInternalStateL( RWriteStream& aWriteStream )
        {
        WriteInternalStateL( aWriteStream );
        }
    };
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKIMAGES::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKIMAGES::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKIMAGES::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKIMAGES::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestIMAGESConstructorL", CTestSDKIMAGES::TestIMAGESConstructorL ),
        ENTRY( "TestIMAGESDestructorL", CTestSDKIMAGES::TestIMAGESDestructorL ),
        ENTRY( "TestIMAGESMinimumSizeL", CTestSDKIMAGES::TestIMAGESMinimumSizeL ),
        ENTRY( "TestIMAGESConstructFromResourceL", CTestSDKIMAGES::TestIMAGESConstructFromResourceL ),
        ENTRY( "TestIMAGESCreatePictureFromFileL", CTestSDKIMAGES::TestIMAGESCreatePictureFromFileL ),
        ENTRY( "TestIMAGESSetPictureL", CTestSDKIMAGES::TestIMAGESSetPictureL ),
        ENTRY( "TestIMAGESSetEmphasisL", CTestSDKIMAGES::TestIMAGESSetEmphasisL ),
        ENTRY( "TestIMAGESSetPictureOwnedExternallyL", CTestSDKIMAGES::TestIMAGESSetPictureOwnedExternallyL ),
        ENTRY( "TestIMAGESBitmapL", CTestSDKIMAGES::TestIMAGESBitmapL ),
        ENTRY( "TestIMAGESMaskL", CTestSDKIMAGES::TestIMAGESMaskL ),
        ENTRY( "TestIMAGESSetBitmapL", CTestSDKIMAGES::TestIMAGESSetBitmapL ),
        ENTRY( "TestIMAGESSetMaskL", CTestSDKIMAGES::TestIMAGESSetMaskL ),
        ENTRY( "TestIMAGESSetNewBitmapsL", CTestSDKIMAGES::TestIMAGESSetNewBitmapsL ),
        ENTRY( "TestIMAGESIsPictureOwnedExternallyL", CTestSDKIMAGES::TestIMAGESIsPictureOwnedExternallyL ),
        ENTRY( "TestIMAGESSetBrushStyleL", CTestSDKIMAGES::TestIMAGESSetBrushStyleL ),
        ENTRY( "TestIMAGESHandlePointerEventL", CTestSDKIMAGES::TestIMAGESHandlePointerEventL ),
        ENTRY( "TestIMAGESWriteInternalStateL", CTestSDKIMAGES::TestIMAGESWriteInternalStateL ),

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKIMAGES::TestIMAGESConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIMAGES::TestIMAGESConstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikImage *sampleimage = new( ELeave ) CEikImage;
    CleanupStack::PushL( sampleimage );
    STIF_ASSERT_NOT_NULL( sampleimage );
    CleanupStack::PopAndDestroy( sampleimage );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKIMAGES::TestIMAGESDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIMAGES::TestIMAGESDestructorL( CStifItemParser& /*aItem*/ )
    {
    CEikImage *sampleimage = new( ELeave ) CEikImage;
    CleanupStack::PushL( sampleimage );
    CleanupStack::Pop( sampleimage );
    delete sampleimage;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKIMAGES::TestIMAGESMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIMAGES::TestIMAGESMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    CEikImage *sampleimage = new( ELeave ) CEikImage;
    CleanupStack::PushL( sampleimage );
    TSize sizezero( 0, 0 );
    TSize returnsize;
    returnsize = sampleimage->MinimumSize();
    STIF_ASSERT_EQUALS( sizezero, returnsize );

    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) );
    CFbsBitmap* main = NULL;
    CFbsBitmap* mask = NULL;
    AknIconUtils::CreateIconL( main, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CleanupStack::PushL( mask );
    
    sampleimage->SetBitmap( main );
    returnsize = sizezero;
    returnsize = sampleimage->MinimumSize();
    STIF_ASSERT_NOT_EQUALS( &sizezero, &returnsize );
    
    CleanupStack::PopAndDestroy( mask );
    CleanupStack::PopAndDestroy( sampleimage );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKIMAGES::TestIMAGESConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIMAGES::TestIMAGESConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikImage* sampleimage = new( ELeave ) CEikImage;
    CleanupStack::PushL( sampleimage );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_IMAGE );
    sampleimage->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    const CFbsBitmap* returnbitmap( NULL );
    const CFbsBitmap* returnbitmapmask( NULL );
    returnbitmap = sampleimage->Bitmap();
    returnbitmapmask = sampleimage->Mask();
    STIF_ASSERT_NOT_NULL( returnbitmap );
    STIF_ASSERT_NOT_NULL( returnbitmapmask );
    
    CleanupStack::PopAndDestroy( sampleimage );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKIMAGES::TestIMAGESCreatePictureFromFileL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIMAGES::TestIMAGESCreatePictureFromFileL( CStifItemParser& /*aItem*/ )
    {
    CEikImage* sampleimage = new( ELeave ) CEikImage;
    CleanupStack::PushL( sampleimage );
    sampleimage->CreatePictureFromFileL( KMbmFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask  );
    
    const CFbsBitmap* returnbitmap( NULL );
    const CFbsBitmap* returnbitmapmask( NULL );
    returnbitmap = sampleimage->Bitmap();
    returnbitmapmask = sampleimage->Mask();
    STIF_ASSERT_NOT_NULL( returnbitmap );
    STIF_ASSERT_NOT_NULL( returnbitmapmask );
    
    returnbitmap = NULL;
    sampleimage->CreatePictureFromFileL( KMbmFile, EMbmAvkonQgn_indi_mic_mask );
    returnbitmap = sampleimage->Bitmap();
    STIF_ASSERT_NOT_NULL( returnbitmap );
    
    CleanupStack::PopAndDestroy( sampleimage );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKIMAGES::TestIMAGESSetPictureL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIMAGES::TestIMAGESSetPictureL( CStifItemParser& /*aItem*/ )
    {
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file )); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* bitmapmask = NULL;
    AknIconUtils::CreateIconL( bitmap, bitmapmask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
        
    CEikImage* sampleimage = new ( ELeave ) CEikImage;
    CleanupStack::PushL( sampleimage );
    sampleimage->SetPicture( bitmap, bitmapmask );
    
    const CFbsBitmap* returnbitmap;
    const CFbsBitmap* returnbitmapmask;
    returnbitmap = sampleimage->Bitmap();
    returnbitmapmask = sampleimage->Mask();
    STIF_ASSERT_EQUALS( bitmap, (CFbsBitmap*)returnbitmap );
    STIF_ASSERT_EQUALS( bitmapmask, CONST_CAST(CFbsBitmap*,returnbitmapmask ) );
    
    returnbitmap = NULL;
    returnbitmapmask = NULL;
    sampleimage->SetPicture( bitmap, bitmap );
    
    returnbitmap = sampleimage->Bitmap();
    returnbitmapmask = sampleimage->Mask();
    STIF_ASSERT_EQUALS( bitmap, (CFbsBitmap*)returnbitmap );
    STIF_ASSERT_EQUALS( bitmap, (CFbsBitmap*)returnbitmapmask );
    STIF_ASSERT_EQUALS( returnbitmap, returnbitmapmask );
    
    CleanupStack::Pop( sampleimage );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKIMAGES::TestIMAGESSetEmphasisL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIMAGES::TestIMAGESSetEmphasisL( CStifItemParser& /*aItem*/ )
    {
    CEikImage* sampleimage = new( ELeave ) CEikImage;
    CleanupStack::PushL( sampleimage );
    TBool value( ETrue );
    sampleimage->SetEmphasis( value );
    value = EFalse;
    sampleimage->SetEmphasis( value );
    CleanupStack::PopAndDestroy( sampleimage );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKIMAGES::TestIMAGESSetPictureOwnedExternallyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIMAGES::TestIMAGESSetPictureOwnedExternallyL( CStifItemParser& /*aItem*/ )
    {
    CEikImage* sampleimage = new( ELeave ) CEikImage;
    CleanupStack::PushL( sampleimage );
    TBool value( ETrue );
    sampleimage->SetPictureOwnedExternally( value );
    value = EFalse;
    sampleimage->SetPictureOwnedExternally( value );
    CleanupStack::PopAndDestroy( sampleimage );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKIMAGES::TestIMAGESBitmapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIMAGES::TestIMAGESBitmapL( CStifItemParser& aItem )
    {
    TInt err( KErrNone );
    err = TestIMAGESSetBitmapL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKIMAGES::TestIMAGESMaskL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIMAGES::TestIMAGESMaskL( CStifItemParser& aItem )
    {
    TInt err( KErrNone );
    err = TestIMAGESSetNewBitmapsL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKIMAGES::TestIMAGESSetBitmapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIMAGES::TestIMAGESSetBitmapL( CStifItemParser& /*aItem*/ )
    {
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* bitmapmask = NULL;
    AknIconUtils::CreateIconL( bitmap, bitmapmask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CleanupStack::PushL( bitmap );
    CleanupStack::PushL( bitmapmask );
    
    CEikImage* sampleimage = new( ELeave ) CEikImage;
    CleanupStack::PushL( sampleimage );

    sampleimage->SetBitmap( bitmap );
    const CFbsBitmap* returnbitmap;
    returnbitmap = sampleimage->Bitmap();
    STIF_ASSERT_EQUALS( bitmap, (CFbsBitmap*)returnbitmap );
    
    
    CFbsBitmap* newbitmap = NULL;
    CFbsBitmap* newbitmapmask = NULL;
    AknIconUtils::CreateIconL( newbitmap, newbitmapmask, file, 
        EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CleanupStack::PushL( newbitmap );
    CleanupStack::PushL( newbitmapmask );
    sampleimage->SetNewBitmaps( newbitmap, newbitmapmask );
    CleanupStack::Pop( newbitmapmask );
    CleanupStack::Pop( newbitmap );
    
    CleanupStack::PopAndDestroy( sampleimage );
    CleanupStack::PopAndDestroy( bitmapmask );
    CleanupStack::Pop( bitmap );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKIMAGES::TestIMAGESSetMaskL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIMAGES::TestIMAGESSetMaskL( CStifItemParser& /*aItem*/ )
    {
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* bitmapmask = NULL;
    AknIconUtils::CreateIconL( bitmap, bitmapmask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CleanupStack::PushL( bitmap );
        
    CEikImage* sampleimage = new( ELeave ) CEikImage;
    CleanupStack::PushL( sampleimage );

    sampleimage->SetMask( bitmapmask );
    const CFbsBitmap* returnbitmap;
    returnbitmap = sampleimage->Mask();
    STIF_ASSERT_EQUALS( bitmapmask, (CFbsBitmap*)returnbitmap );
    
    CleanupStack::PopAndDestroy( sampleimage );
    CleanupStack::Pop( bitmap );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKIMAGES::TestIMAGESSetNewBitmapsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIMAGES::TestIMAGESSetNewBitmapsL( CStifItemParser& aItem )
    {
    TInt err(KErrNone);
    err = TestIMAGESSetPictureL( aItem );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKIMAGES::TestIMAGESIsPictureOwnedExternallyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIMAGES::TestIMAGESIsPictureOwnedExternallyL( CStifItemParser& /*aItem*/ )
    {
    CEikImage* sampleimage = new( ELeave ) CEikImage;
    CleanupStack::PushL( sampleimage );
    sampleimage->SetEmphasis( ETrue );
    TBool flag( ETrue );
    flag = sampleimage->IsPictureOwnedExternally();
    STIF_ASSERT_FALSE( flag );
    sampleimage->SetPictureOwnedExternally( ETrue );
    flag = sampleimage->IsPictureOwnedExternally();
    STIF_ASSERT_TRUE( flag );
    CleanupStack::PopAndDestroy( sampleimage );
	
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKIMAGES::TestIMAGESSetBrushStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIMAGES::TestIMAGESSetBrushStyleL( CStifItemParser& /*aItem*/ )
    {
    CEikImage* sampleimage = new( ELeave ) CEikImage;
    CleanupStack::PushL( sampleimage );
    sampleimage->SetBrushStyle( CGraphicsContext::ESolidBrush );

    CleanupStack::PopAndDestroy( sampleimage );
    return KErrNone;
    }

TInt CTestSDKIMAGES::TestIMAGESHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CEikImage* sampleimage = new( ELeave ) CEikImage;
    CleanupStack::PushL( sampleimage );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TInt err = KErrNone;
    TRAP( err, sampleimage->HandlePointerEventL( event ) );
    
    CleanupStack::PopAndDestroy( sampleimage );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKIMAGES::TestIMAGESSetBrushStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIMAGES::TestIMAGESWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    CTestImage* testimage = new( ELeave ) CTestImage;
    CleanupStack::PushL( testimage );
    const TInt KHBufSize = 4096;
    HBufC8* buf = HBufC8::NewL( KHBufSize );
    CleanupStack::PushL( buf );
    TPtr8 ptr = buf->Des();
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    stream.Open( ptr );
    testimage->DoWriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();
    CleanupStack::PopAndDestroy( 3 );//testimage, buf, stream
    
    return KErrNone;
    }

//End file



