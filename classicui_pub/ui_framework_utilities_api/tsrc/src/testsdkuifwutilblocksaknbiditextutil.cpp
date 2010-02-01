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
* Description:  test functions in aknbiditextutils.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkuifwutil.h"

// CONSTANTS
const TInt KBufSize = 64;
const TInt KGeneralWidth = 50;
const TInt KArraySize = 10;
_LIT( KTextExample, "textexample" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknBidiTextUtilsConvertToVisualAndClipL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknBidiTextUtilsConvertToVisualAndClipL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    TBuf<KBufSize> text( KTextExample );
    
    TBool result = EFalse;
    switch ( num )
        {
        case ECaseZero:
            {
            result = AknBidiTextUtils::ConvertToVisualAndClipL( text, *iFont, KGeneralWidth, KGeneralWidth );
            break;
            }
        case ECaseOne:
            {
            TBuf<KBufSize + KBufSize> visualtext;
            result = AknBidiTextUtils::ConvertToVisualAndClip( text, visualtext, *iFont, KGeneralWidth, KGeneralWidth );
            break;
            }
        default:
            {
            return KErrNotSupported;
            }
        }
    
    STIF_ASSERT_TRUE( result );
    
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknBidiTextUtilsPrepareRunInfoArray
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknBidiTextUtilsPrepareRunInfoArray( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> text( KTextExample );
    TInt err = AknBidiTextUtils::PrepareRunInfoArray( text );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknBidiTextUtilsConvertToVisualAndWrapToArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknBidiTextUtilsConvertToVisualAndWrapToArrayL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    TBuf<KBufSize> text( KTextExample );
    CArrayFixFlat<TInt>* linearray = new( ELeave ) CArrayFixFlat<TInt>( KArraySize );
    CleanupStack::PushL( linearray );
    TInt addnum = 0;
    linearray->AppendL( addnum );
    
    CArrayFixFlat<TPtrC>* wraparray = new( ELeave ) CArrayFixFlat<TPtrC>( KArraySize );
    CleanupStack::PushL( wraparray );
    switch ( num )
        {
        case ECaseZero:
            {
            AknBidiTextUtils::ConvertToVisualAndWrapToArrayL( text, *linearray, *iFont, *wraparray, ETrue );
            break;
            }
        case ECaseOne:
            {
            AknBidiTextUtils::ConvertToVisualAndWrapToArrayL( text, KGeneralWidth, *iFont, *wraparray );
            break;
            }
        default:
            {
            CleanupStack::PopAndDestroy( 2 );
            return KErrNotSupported;
            }
        }
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknBidiTextUtilsConvertToVisualAndChopToArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknBidiTextUtilsConvertToVisualAndChopToArrayL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    TBuf<KBufSize> text( KTextExample );
    CArrayFixFlat<TInt>* linearray = new( ELeave ) CArrayFixFlat<TInt>( KArraySize );
    CleanupStack::PushL( linearray );
    TInt addnum = 0;
    linearray->AppendL( addnum );
    
    CArrayFixFlat<TPtrC>* wraparray = new( ELeave ) CArrayFixFlat<TPtrC>( KArraySize );
    CleanupStack::PushL( wraparray );
    switch ( num )
        {
        case ECaseZero:
            {
            AknBidiTextUtils::ConvertToVisualAndChopToArrayL( text, *linearray, *iFont, *wraparray );
            break;
            }
        case ECaseOne:
            {
            AknBidiTextUtils::ConvertToVisualAndChopToArrayL( text, KGeneralWidth, *iFont, *wraparray );
            break;
            }
        default:
            {
            CleanupStack::PopAndDestroy( 2 );
            return KErrNotSupported;
            }
        }
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknBidiTextUtilsConvertToVisualAndWrapToStringL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknBidiTextUtilsConvertToVisualAndWrapToStringL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> text( KTextExample );
    TBuf<KBufSize> wrapstr;
    CArrayFixFlat<TInt>* linearray = new( ELeave ) CArrayFixFlat<TInt>( KArraySize );
    CleanupStack::PushL( linearray );
    TInt addnum = 0;
    linearray->AppendL( addnum );
    
    CArrayFixFlat<TPtrC>* wraparray = new( ELeave ) CArrayFixFlat<TPtrC>( KArraySize );
    CleanupStack::PushL( wraparray );
    
    AknBidiTextUtils::ConvertToVisualAndWrapToStringL( text, *linearray, *iFont, wrapstr, ETrue );
    AknBidiTextUtils::ConvertToVisualAndWrapToStringL( text, *linearray, *iFont, wrapstr, EFalse );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknBidiTextUtilsConvertToVisualAndWrapToArrayWholeTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknBidiTextUtilsConvertToVisualAndWrapToArrayWholeTextL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> text( KTextExample );
    CArrayFixFlat<TInt>* linearray = new( ELeave ) CArrayFixFlat<TInt>( KArraySize );
    CleanupStack::PushL( linearray );
    TInt addnum = 0;
    linearray->AppendL( addnum );
    
    CArrayFixFlat<TPtrC>* wraparray = new( ELeave ) CArrayFixFlat<TPtrC>( KArraySize );
    CleanupStack::PushL( wraparray );
    
    AknBidiTextUtils::ConvertToVisualAndWrapToArrayWholeTextL( text, *linearray, *iFont, *wraparray );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestAknBidiTextUtilsMeasureTextBoundsWidth
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestAknBidiTextUtilsMeasureTextBoundsWidth( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> text( KTextExample );
    
    AknBidiTextUtils::MeasureTextBoundsWidth( *iFont, text, CFont::TMeasureTextInput::EFVisualOrder );
    
    return KErrNone;
    }

// End of file



