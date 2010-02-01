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
* Description:  Test aknqueryvaluenumber.h
*
*/

//INCLUDE
#include <aknqueryvaluenumber.h>
#include <testsdkqueries.rsg>

#include "testsdkqueries.h"

const TInt KZero = 0;
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KThree = 3;
const TInt KNumber1 = 1234567;
const TInt KNumber2 = 25890;

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNumberNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNumberNewL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueNumber* number = CAknQueryValueNumber::NewL();
    CleanupStack::PushL( number );
    
    STIF_ASSERT_NOT_NULL( number );
    
    CleanupStack::PopAndDestroy( number );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNumberNewLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNumberNewLC( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueNumber* number = CAknQueryValueNumber::NewLC();
    
    STIF_ASSERT_NOT_NULL( number );
    
    CleanupStack::PopAndDestroy( number );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNumberDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNumberDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueNumber* number = CAknQueryValueNumber::NewLC();
    CleanupStack::PopAndDestroy( number );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNumberSetArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNumberSetArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueNumber* number = CAknQueryValueNumber::NewLC();
    
    const MDesCArray* returnArray = number->MdcArray();
    STIF_ASSERT_NULL( returnArray );
    
    CArrayFix<TInt>* mArray = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( mArray );
    
    mArray->AppendL( KNumber1 );
    mArray->AppendL( KNumber2 );
    
    CAknQueryValueNumberArray* numberArray = 
        CAknQueryValueNumberArray::NewL( R_TESTQUERY_NUMBER_FORMAT );
    CleanupStack::PushL( numberArray );
    
    numberArray->SetArray( *mArray );
    
    number->SetArrayL( numberArray );
    
    returnArray = number->MdcArray();
    STIF_ASSERT_EQUALS( numberArray, ( CAknQueryValueNumberArray* )returnArray );
    
    CleanupStack::Pop( KTwo );
    CleanupStack::PopAndDestroy( number );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNumberSetQueryCaptionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNumberSetQueryCaptionL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueNumber* number = CAknQueryValueNumber::NewLC();
    
    CArrayFix<TInt>* mArray = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( mArray );
    
    mArray->AppendL( KNumber1 );
    mArray->AppendL( KNumber2 );
    
    CAknQueryValueNumberArray* numberArray = 
        CAknQueryValueNumberArray::NewL( R_TESTQUERY_NUMBER_FORMAT );
    CleanupStack::PushL( numberArray );
    
    numberArray->SetArray( *mArray );
    
    number->SetArrayL( numberArray );
    
    number->SetQueryCaption( R_TESTQUERY_CAPTION );
    
    CleanupStack::Pop( KTwo );
    CleanupStack::PopAndDestroy( number );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNumberValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNumberValueL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueNumber* number = CAknQueryValueNumber::NewLC();
    
    TInt returnNumber = number->Value();
    STIF_ASSERT_EQUALS( KZero, returnNumber );
    
    CleanupStack::PopAndDestroy( number );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNumberMdcArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNumberMdcArrayL( CStifItemParser& aItem )
    {
    TInt err = TestQVNumberSetArrayL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNumberCurrentValueTextLCL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNumberCurrentValueTextLCL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueNumber* number = CAknQueryValueNumber::NewLC();
    
    CArrayFix<TInt>* mArray = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( mArray );
    
    mArray->AppendL( KNumber1 );
    mArray->AppendL( KNumber2 );
    
    CAknQueryValueNumberArray* numberArray = 
        CAknQueryValueNumberArray::NewL( R_TESTQUERY_NUMBER_FORMAT );
    CleanupStack::PushL( numberArray );
    
    numberArray->SetArray( *mArray );
    
    number->SetArrayL( numberArray );
    
    HBufC* text = number->CurrentValueTextLC();
    STIF_ASSERT_NOT_NULL( text );
    
    CleanupStack::Pop( KThree );
    CleanupStack::PopAndDestroy( number );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNumberCurrentValueIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNumberCurrentValueIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueNumber* number = CAknQueryValueNumber::NewLC();
    
    TInt mIndex = number->CurrentValueIndex();
    STIF_ASSERT_EQUALS( KZero, mIndex );
    
    CArrayFix<TInt>* mArray = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( mArray );
    
    mArray->AppendL( KNumber1 );
    mArray->AppendL( KNumber2 );
    
    CAknQueryValueNumberArray* numberArray = 
        CAknQueryValueNumberArray::NewL( R_TESTQUERY_NUMBER_FORMAT );
    CleanupStack::PushL( numberArray );
    
    numberArray->SetArray( *mArray );
    
    number->SetArrayL( numberArray );
    
    number->SetCurrentValueIndex( KOne );
    
    mIndex = number->CurrentValueIndex();
    STIF_ASSERT_EQUALS( KOne, mIndex );
    
    CleanupStack::Pop( KTwo );
    CleanupStack::PopAndDestroy( number );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNumberSetCurrentValueIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNumberSetCurrentValueIndexL( CStifItemParser& aItem )
    {
    TInt err = TestQVNumberCurrentValueIndexL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNumberCreateEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNumberCreateEditorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueNumber* number = CAknQueryValueNumber::NewLC();
    
    CArrayFix<TInt>* mArray = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( mArray );
    
    mArray->AppendL( KNumber1 );
    mArray->AppendL( KNumber2 );
    
    CAknQueryValueNumberArray* numberArray = 
        CAknQueryValueNumberArray::NewL( R_TESTQUERY_NUMBER_FORMAT );
    CleanupStack::PushL( numberArray );
    
    numberArray->SetArray( *mArray );
    
    number->SetArrayL( numberArray );
    
    number->SetCurrentValueIndex( KZero );
    
    TBool flag = number->CreateEditorL();
    STIF_ASSERT_TRUE( flag );
    
    CleanupStack::Pop( KTwo );
    CleanupStack::PopAndDestroy( number );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNArrayNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNArrayNewL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueNumberArray* numberArray = 
        CAknQueryValueNumberArray::NewL( R_TESTQUERY_NUMBER_FORMAT );
    CleanupStack::PushL( numberArray );
    
    STIF_ASSERT_NOT_NULL( numberArray );
    
    CleanupStack::PopAndDestroy( numberArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNArrayNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNArrayNewLCL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueNumberArray* numberArray = 
        CAknQueryValueNumberArray::NewLC( R_TESTQUERY_NUMBER_FORMAT );
    
    STIF_ASSERT_NOT_NULL( numberArray );
    
    CleanupStack::PopAndDestroy( numberArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNArrayDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNArrayDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueNumberArray* numberArray = 
        CAknQueryValueNumberArray::NewLC( R_TESTQUERY_NUMBER_FORMAT );
    CleanupStack::PopAndDestroy( numberArray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNArraySetArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNArraySetArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueNumberArray* numberArray = 
        CAknQueryValueNumberArray::NewL( R_TESTQUERY_NUMBER_FORMAT );
    CleanupStack::PushL( numberArray );
    
    CArrayFix<TInt>* returnArray = numberArray->Array();
    STIF_ASSERT_NULL( returnArray );
    
    CArrayFix<TInt>* mArray = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( mArray );
    
    mArray->AppendL( KNumber1 );
    mArray->AppendL( KNumber2 );
    
    numberArray->SetArray( *mArray );
    
    returnArray = numberArray->Array();
    STIF_ASSERT_EQUALS( mArray, returnArray );
    
    CleanupStack::Pop( mArray );
    CleanupStack::PopAndDestroy( numberArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNArrayArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNArrayArrayL( CStifItemParser& aItem )
    {
    TInt err = TestQVNArraySetArrayL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNArrayFormatStringL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNArrayFormatStringL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueNumberArray* numberArray = 
        CAknQueryValueNumberArray::NewL( R_TESTQUERY_NUMBER_FORMAT );
    CleanupStack::PushL( numberArray );
    
    CArrayFix<TInt>* mArray = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( mArray );
    
    mArray->AppendL( KNumber1 );
    mArray->AppendL( KNumber2 );
    
    numberArray->SetArray( *mArray );
    
    const HBufC* text = numberArray->FormatString();
    STIF_ASSERT_NOT_NULL( text );
    
    CleanupStack::Pop( mArray );
    CleanupStack::PopAndDestroy( numberArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNArrayFormattedStringSizeOneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNArrayFormattedStringSizeOneL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueNumberArray* numberArray = 
        CAknQueryValueNumberArray::NewL( R_TESTQUERY_NUMBER_FORMAT );
    CleanupStack::PushL( numberArray );
    
    CArrayFix<TInt>* mArray = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( mArray );
    
    mArray->AppendL( KNumber1 );
    mArray->AppendL( KNumber2 );
    
    numberArray->SetArray( *mArray );
    
    const TInt size = numberArray->FormattedStringSize();
    STIF_ASSERT_NOT_EQUALS( KZero, size );
    
    CleanupStack::Pop( mArray );
    CleanupStack::PopAndDestroy( numberArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNArrayFormattedStringSizeTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNArrayFormattedStringSizeTwoL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueNumberArray* numberArray = 
        CAknQueryValueNumberArray::NewL( R_TESTQUERY_NUMBER_FORMAT );
    CleanupStack::PushL( numberArray );
    
    CArrayFix<TInt>* mArray = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( mArray );
    
    mArray->AppendL( KNumber1 );
    mArray->AppendL( KNumber2 );
    
    numberArray->SetArray( *mArray );
    
    TInt size = numberArray->FormattedStringSize();
    STIF_ASSERT_NOT_EQUALS( KZero, size );
    
    CleanupStack::Pop( mArray );
    CleanupStack::PopAndDestroy( numberArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNArrayMdcaCountL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNArrayMdcaCountL( CStifItemParser& aItem )
    {
    TInt err = TestQVNArrayMdcaPointL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVNArrayMdcaPointL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVNArrayMdcaPointL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueNumberArray* numberArray = 
        CAknQueryValueNumberArray::NewL( R_TESTQUERY_NUMBER_FORMAT );
    CleanupStack::PushL( numberArray );
    
    CArrayFix<TInt>* mArray = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( mArray );
    
    mArray->AppendL( KNumber1 );
    mArray->AppendL( KNumber2 );
    
    numberArray->SetArray( *mArray );
    
    for ( TInt mark = 0; mark < numberArray->MdcaCount(); mark++ )
        {
        TPtrC text = numberArray->MdcaPoint( mark );
        STIF_ASSERT_NOT_NULL( &text );
        }
    
    CleanupStack::Pop( mArray );
    CleanupStack::PopAndDestroy( numberArray );
    return KErrNone;
    }

//End file



