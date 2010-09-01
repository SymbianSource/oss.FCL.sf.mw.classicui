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
* Description:  Test aknqueryvalueduration.h
*
*/

//INCLUDE
#include <aknqueryvalueduration.h>
#include <testsdkqueries.rsg>

#include "testsdkqueries.h"

const TInt KZero = 0;
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KThree = 3;
const TInt KDurationOne = 200;
const TInt KDurationTwo = 780;
const TInt KBufSize = 32;
const TInt KTimeIntervalSeconds = 10000;

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDurationNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDurationNewL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDuration* duration = CAknQueryValueDuration::NewL();
    CleanupStack::PushL( duration );
    
    STIF_ASSERT_NOT_NULL( duration );
    
    CleanupStack::PopAndDestroy( duration );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDurationNewLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDurationNewLCL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDuration* duration = CAknQueryValueDuration::NewLC();
    
    STIF_ASSERT_NOT_NULL( duration );
    
    CleanupStack::PopAndDestroy( duration );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDurationDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDurationDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDuration* duration = CAknQueryValueDuration::NewLC();
    CleanupStack::PopAndDestroy( duration );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDurationSetArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDurationSetArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDuration* duration = CAknQueryValueDuration::NewLC();
    
    CAknQueryValueDurationArray* mArray = 
        CAknQueryValueDurationArray::NewL( R_TESTQUERY_TIME_FORMAT );
    CleanupStack::PushL( mArray );
    
    duration->SetArrayL( mArray );
    
    CleanupStack::Pop( mArray );
    CleanupStack::PopAndDestroy( duration );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDurationSetQueryCaptionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDurationSetQueryCaptionL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDuration* duration = CAknQueryValueDuration::NewLC();
    
    duration->SetQueryCaption( R_TESTQUERY_CAPTION );
    
    CleanupStack::PopAndDestroy( duration );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDurationValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDurationValueL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDuration* duration = CAknQueryValueDuration::NewLC();
    
    TTimeIntervalSeconds value = duration->Value();
    
    TTimeIntervalSeconds compareValue( KZero );
    STIF_ASSERT_EQUALS( compareValue, value );
    
    CleanupStack::PopAndDestroy( duration );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDurationMdcArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDurationMdcArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDuration* duration = CAknQueryValueDuration::NewLC();
    
    const MDesCArray* returnArray = duration->MdcArray();
    STIF_ASSERT_NULL( returnArray );
    
    CAknQueryValueDurationArray* mArray = 
        CAknQueryValueDurationArray::NewL( R_TESTQUERY_TIME_FORMAT );
    CleanupStack::PushL( mArray );
    
    duration->SetArrayL( mArray );
    
    const MDesCArray* returnArrayTwo = duration->MdcArray();
    
    STIF_ASSERT_EQUALS( mArray, ( CAknQueryValueDurationArray* )returnArrayTwo );
    
    CleanupStack::Pop( mArray );
    CleanupStack::PopAndDestroy( duration );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDurationCurrentValueTextLCL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDurationCurrentValueTextLCL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDuration* duration = CAknQueryValueDuration::NewLC();
    
    CArrayFix<TTimeIntervalSeconds>* durationArray = new( ELeave ) 
        CArrayFixFlat<TTimeIntervalSeconds>( 2 );
    CleanupStack::PushL( durationArray );
    TTimeIntervalSeconds dura1( KDurationOne );
    TTimeIntervalSeconds dura2( KDurationTwo );
    
    durationArray->AppendL( dura1 );
    durationArray->AppendL( dura2 );
    
    CAknQueryValueDurationArray* mArray = CAknQueryValueDurationArray::NewL(
        R_TESTQUERY_TIME_FORMAT );
    CleanupStack::PushL( mArray );
    
    mArray->SetArray( *durationArray );
    
    duration->SetArrayL( mArray );
    
    HBufC* text = duration->CurrentValueTextLC();
    STIF_ASSERT_NOT_NULL( text );
    
    CleanupStack::Pop( KThree );
    CleanupStack::PopAndDestroy( duration );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDurationCurrentValueIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDurationCurrentValueIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDuration* duration = CAknQueryValueDuration::NewLC();
    
    TInt mIndex = duration->CurrentValueIndex();
    STIF_ASSERT_EQUALS( KZero, mIndex );
    
    CArrayFix<TTimeIntervalSeconds>* durationArray = new( ELeave ) 
        CArrayFixFlat<TTimeIntervalSeconds>( 2 );
    CleanupStack::PushL( durationArray );
    TTimeIntervalSeconds dura1( KDurationOne );
    TTimeIntervalSeconds dura2( KDurationTwo );
    
    durationArray->AppendL( dura1 );
    durationArray->AppendL( dura2 );
    
    CAknQueryValueDurationArray* mArray = CAknQueryValueDurationArray::NewL(
        R_TESTQUERY_TIME_FORMAT );
    CleanupStack::PushL( mArray );
    
    mArray->SetArray( *durationArray );
    
    duration->SetArrayL( mArray );
    
    duration->SetCurrentValueIndex( KOne );
    
    mIndex = duration->CurrentValueIndex();
    STIF_ASSERT_EQUALS( KOne, mIndex );
    
    CleanupStack::Pop( KTwo );
    CleanupStack::PopAndDestroy( duration );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDurationSetCurrentValueIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDurationSetCurrentValueIndexL( CStifItemParser& aItem )
    {
    TInt err = TestQVDurationCurrentValueIndexL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDurationCreateEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDurationCreateEditorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDuration* duration = CAknQueryValueDuration::NewLC();
    
    CArrayFix<TTimeIntervalSeconds>* durationArray = new( ELeave ) 
        CArrayFixFlat<TTimeIntervalSeconds>( 2 );
    CleanupStack::PushL( durationArray );
    TTimeIntervalSeconds dura1( KDurationOne );
    TTimeIntervalSeconds dura2( KDurationTwo );
    
    durationArray->AppendL( dura1 );
    durationArray->AppendL( dura2 );
    
    CAknQueryValueDurationArray* mArray = CAknQueryValueDurationArray::NewL(
        R_TESTQUERY_TIME_FORMAT );
    CleanupStack::PushL( mArray );
    
    mArray->SetArray( *durationArray );
    
    duration->SetArrayL( mArray );
    
    duration->SetCurrentValueIndex( KZero );
    
    TBool flag = duration->CreateEditorL();
    STIF_ASSERT_TRUE( flag );
    
    CleanupStack::Pop( KTwo );
    CleanupStack::PopAndDestroy( duration );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDArrayNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDArrayNewL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDurationArray* durationArray = 
        CAknQueryValueDurationArray::NewL( R_TESTQUERY_TIME_FORMAT );
    CleanupStack::PushL( durationArray );
    
    STIF_ASSERT_NOT_NULL( durationArray );
    
    CleanupStack::PopAndDestroy( durationArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDArrayNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDArrayNewLCL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDurationArray* durationArray = 
        CAknQueryValueDurationArray::NewLC( R_TESTQUERY_TIME_FORMAT );
    
    STIF_ASSERT_NOT_NULL( durationArray );
    
    CleanupStack::PopAndDestroy( durationArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDArrayDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDArrayDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDurationArray* durationArray = 
        CAknQueryValueDurationArray::NewLC( R_TESTQUERY_TIME_FORMAT );
    CleanupStack::PopAndDestroy( durationArray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDArraySetArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDArraySetArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDurationArray* durationArray = 
        CAknQueryValueDurationArray::NewLC( R_TESTQUERY_TIME_FORMAT );
    
    CArrayFix<TTimeIntervalSeconds>* returnArray = durationArray->Array();
    STIF_ASSERT_NULL( returnArray );
    
    CArrayFix<TTimeIntervalSeconds>* mArray = new( ELeave ) 
        CArrayFixFlat<TTimeIntervalSeconds>( 2 );
    CleanupStack::PushL( mArray );
    
    TTimeIntervalSeconds dura1( KDurationOne );
    TTimeIntervalSeconds dura2( KDurationTwo );
    
    mArray->AppendL( dura1 );
    mArray->AppendL( dura2 );
    
    durationArray->SetArray( *mArray );
    
    returnArray = durationArray->Array();
    STIF_ASSERT_EQUALS( mArray, returnArray );
    
    CleanupStack::Pop( mArray );
    CleanupStack::PopAndDestroy( durationArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDArrayArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDArrayArrayL( CStifItemParser& aItem )
    {
    TInt err = TestQVDArraySetArrayL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDArrayFormatStringL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDArrayFormatStringL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDurationArray* durationArray = 
        CAknQueryValueDurationArray::NewLC( R_TESTQUERY_TIME_FORMAT );
    
    CArrayFix<TTimeIntervalSeconds>* mArray = new( ELeave ) 
        CArrayFixFlat<TTimeIntervalSeconds>( 2 );
    CleanupStack::PushL( mArray );
    
    TTimeIntervalSeconds dura1( KDurationOne );
    TTimeIntervalSeconds dura2( KDurationTwo );
    
    mArray->AppendL( dura1 );
    mArray->AppendL( dura2 );
    
    durationArray->SetArray( *mArray );
    
    const HBufC* text = durationArray->FormatString();
    STIF_ASSERT_NOT_NULL( text );
    
    CleanupStack::Pop( mArray );
    CleanupStack::PopAndDestroy( durationArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDArrayFormattedStringSizeOneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDArrayFormattedStringSizeOneL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDurationArray* durationArray = 
        CAknQueryValueDurationArray::NewLC( R_TESTQUERY_TIME_FORMAT );
    
    CArrayFix<TTimeIntervalSeconds>* mArray = new( ELeave ) 
        CArrayFixFlat<TTimeIntervalSeconds>( 2 );
    CleanupStack::PushL( mArray );
    
    TTimeIntervalSeconds dura1( KDurationOne );
    TTimeIntervalSeconds dura2( KDurationTwo );
    
    mArray->AppendL( dura1 );
    mArray->AppendL( dura2 );
    
    durationArray->SetArray( *mArray );
    
    const TInt size = durationArray->FormattedStringSize();
    STIF_ASSERT_NOT_EQUALS( KZero, size );
    
    CleanupStack::Pop( mArray );
    CleanupStack::PopAndDestroy( durationArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDArrayFormattedStringSizeTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDArrayFormattedStringSizeTwoL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDurationArray* durationArray = 
        CAknQueryValueDurationArray::NewLC( R_TESTQUERY_TIME_FORMAT );
    
    CArrayFix<TTimeIntervalSeconds>* mArray = new( ELeave ) 
        CArrayFixFlat<TTimeIntervalSeconds>( 2 );
    CleanupStack::PushL( mArray );
    
    TTimeIntervalSeconds dura1( KDurationOne );
    TTimeIntervalSeconds dura2( KDurationTwo );
    
    mArray->AppendL( dura1 );
    mArray->AppendL( dura2 );
    
    durationArray->SetArray( *mArray );
    
    TInt size = durationArray->FormattedStringSize();
    STIF_ASSERT_NOT_EQUALS( KZero, size );
    
    CleanupStack::Pop( mArray );
    CleanupStack::PopAndDestroy( durationArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDArrayFormatDurationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDArrayFormatDurationL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDurationArray* durationArray = 
        CAknQueryValueDurationArray::NewLC( R_TESTQUERY_TIME_FORMAT );
    
    CArrayFix<TTimeIntervalSeconds>* mArray = new( ELeave ) 
        CArrayFixFlat<TTimeIntervalSeconds>( 2 );
    CleanupStack::PushL( mArray );
    
    TTimeIntervalSeconds dura1( KDurationOne );
    TTimeIntervalSeconds dura2( KDurationTwo );
    
    mArray->AppendL( dura1 );
    mArray->AppendL( dura2 );
    
    durationArray->SetArray( *mArray );
    
    TBufC< KBufSize > formatText;
    TPtr ptr( formatText.Des() );
    TTimeIntervalSeconds dura = KTimeIntervalSeconds;
    
    durationArray->FormatDuration( ptr, dura );
    
    CleanupStack::Pop( mArray );
    CleanupStack::PopAndDestroy( durationArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDArrayMdcaCountL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDArrayMdcaCountL( CStifItemParser& aItem )
    {
    TInt err = TestQVDArrayMdcaPointL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDArrayMdcaPointL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDArrayMdcaPointL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDurationArray* durationArray = 
        CAknQueryValueDurationArray::NewLC( R_TESTQUERY_TIME_FORMAT );
    
    CArrayFix<TTimeIntervalSeconds>* mArray = new( ELeave ) 
        CArrayFixFlat<TTimeIntervalSeconds>( 2 );
    CleanupStack::PushL( mArray );
    
    TTimeIntervalSeconds dura1( KDurationOne );
    TTimeIntervalSeconds dura2( KDurationTwo );
    
    mArray->AppendL( dura1 );
    mArray->AppendL( dura2 );
    
    durationArray->SetArray( *mArray );
    
    for ( TInt mark = 0; mark < durationArray->MdcaCount(); mark++ )
        {
        TPtrC text = durationArray->MdcaPoint( mark );
        STIF_ASSERT_NOT_NULL( &text );
        }
    
    CleanupStack::Pop( mArray );
    CleanupStack::PopAndDestroy( durationArray );
    return KErrNone;
    }

//End file


