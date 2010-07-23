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
* Description:  Test aknqueryvaluephone.h
*
*/

//INCLUDE
#include <aknqueryvaluephone.h>
#include <testsdkqueries.rsg>

#include "testsdkqueries.h"

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestPhoneNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestPhoneNewL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValuePhone* valuePhone = CAknQueryValuePhone::NewL();
    CleanupStack::PushL( valuePhone );
    STIF_ASSERT_NOT_NULL( valuePhone );
    
    CleanupStack::PopAndDestroy( valuePhone );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestPhoneNewLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestPhoneNewLC( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValuePhone* valuePhone = CAknQueryValuePhone::NewLC();
    STIF_ASSERT_NOT_NULL( valuePhone );
    
    CleanupStack::PopAndDestroy( valuePhone );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestPhoneDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestPhoneDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValuePhone* valuePhone = CAknQueryValuePhone::NewLC();
    STIF_ASSERT_NOT_NULL( valuePhone );
    
    CleanupStack::Pop( valuePhone );
    delete valuePhone;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestPhoneSetArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestPhoneSetArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValuePhone* valuePhone = CAknQueryValuePhone::NewLC();
    STIF_ASSERT_NOT_NULL( valuePhone );
    
    CAknQueryValuePhoneArray* array = CAknQueryValuePhoneArray::NewLC();
    STIF_ASSERT_NOT_NULL( array );
    
    valuePhone->SetArrayL( array );
    
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( valuePhone );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestPhoneSetQueryCaptionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestPhoneSetQueryCaptionL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValuePhone* valuePhone = CAknQueryValuePhone::NewLC();
    STIF_ASSERT_NOT_NULL( valuePhone );
    
    valuePhone->SetQueryCaption( R_QUERY_VALUEPHONE_STRING );
    
    CleanupStack::PopAndDestroy( valuePhone );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestPhoneValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestPhoneValueL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValuePhone* valuePhone = CAknQueryValuePhone::NewLC();
    STIF_ASSERT_NOT_NULL( valuePhone );
    
    HBufC* value = valuePhone->Value();
    CleanupStack::PushL( value );
    STIF_ASSERT_TRUE( value->Length() == 0 );
    
    CleanupStack::Pop( value );
    CleanupStack::PopAndDestroy( valuePhone );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestPhoneMdcArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestPhoneMdcArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValuePhone* valuePhone = CAknQueryValuePhone::NewLC();
    STIF_ASSERT_NOT_NULL( valuePhone );
    
    CAknQueryValuePhoneArray* array = CAknQueryValuePhoneArray::NewLC();
    STIF_ASSERT_NOT_NULL( array );
    
    valuePhone->SetArrayL( array );
    
    const MDesCArray* mdcArray = valuePhone->MdcArray();
    STIF_ASSERT_NOT_NULL( mdcArray );
    
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( valuePhone );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestPhoneCurrentValueTextLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestPhoneCurrentValueTextLC( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValuePhone* valuePhone = CAknQueryValuePhone::NewLC();
    STIF_ASSERT_NOT_NULL( valuePhone );
    
    CAknQueryValuePhoneArray* array = CAknQueryValuePhoneArray::NewLC();
    STIF_ASSERT_NOT_NULL( array );
    
    CDesCArray* textArray = new (ELeave) CDesCArrayFlat( 1 );
    CleanupStack::PushL( textArray );
    _LIT( KValue, "123456" );
    textArray->AppendL( KValue );
    
    array->SetArray( *textArray );
    valuePhone->SetArrayL( array );
    
    valuePhone->SetCurrentValueIndex( 0 );
    HBufC* value = valuePhone->CurrentValueTextLC();
    STIF_ASSERT_TRUE( value->Compare( KValue ) == 0 );
    
    CleanupStack::PopAndDestroy( value );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( valuePhone );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestPhoneCurrentValueIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestPhoneCurrentValueIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValuePhone* valuePhone = CAknQueryValuePhone::NewLC();
    STIF_ASSERT_NOT_NULL( valuePhone );
    
    CAknQueryValuePhoneArray* array = CAknQueryValuePhoneArray::NewLC();
    STIF_ASSERT_NOT_NULL( array );
    
    CDesCArray* textArray = new (ELeave) CDesCArrayFlat( 1 );
    CleanupStack::PushL( textArray );
    _LIT( KValue, "123456" );
    textArray->AppendL( KValue );
    
    array->SetArray( *textArray );
    valuePhone->SetArrayL( array );
    
    valuePhone->SetCurrentValueIndex( 0 );
    STIF_ASSERT_TRUE( valuePhone->CurrentValueIndex() == 0 );
    
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( valuePhone );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestPhoneSetCurrentValueIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestPhoneSetCurrentValueIndexL( CStifItemParser& aItem )
    {

    return TestPhoneCurrentValueIndexL( aItem );
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestPhoneCreateEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestPhoneCreateEditorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValuePhone* valuePhone = CAknQueryValuePhone::NewLC();
    STIF_ASSERT_NOT_NULL( valuePhone );
    
    CAknQueryValuePhoneArray* array = CAknQueryValuePhoneArray::NewLC();
    STIF_ASSERT_NOT_NULL( array );
    
    CDesCArray* textArray = new (ELeave) CDesCArrayFlat( 1 );
    CleanupStack::PushL( textArray );
    _LIT( KValue, "123456" );
    textArray->AppendL( KValue );
    
    array->SetArray( *textArray );
    valuePhone->SetArrayL( array );
    
    valuePhone->SetCurrentValueIndex( 0 );
    
    TBool flag = valuePhone->CreateEditorL();
    STIF_ASSERT_TRUE( flag );
    
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( valuePhone );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestPhoneArrayNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestPhoneArrayNewL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValuePhoneArray* valuePhoneArray = CAknQueryValuePhoneArray::NewL();
    CleanupStack::PushL( valuePhoneArray );
    STIF_ASSERT_NOT_NULL( valuePhoneArray );
    
    CleanupStack::PopAndDestroy( valuePhoneArray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestPhoneArrayNewLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestPhoneArrayNewLC( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValuePhoneArray* valuePhoneArray = CAknQueryValuePhoneArray::NewLC();
    STIF_ASSERT_NOT_NULL( valuePhoneArray );
    
    CleanupStack::PopAndDestroy( valuePhoneArray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestPhoneArrayDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestPhoneArrayDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValuePhoneArray* valuePhoneArray = CAknQueryValuePhoneArray::NewLC();
    STIF_ASSERT_NOT_NULL( valuePhoneArray );
    
    CleanupStack::Pop( valuePhoneArray );
    delete valuePhoneArray;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestPhoneArraySetArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestPhoneArraySetArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValuePhoneArray* valuePhoneArray = CAknQueryValuePhoneArray::NewLC();
    STIF_ASSERT_NOT_NULL( valuePhoneArray );
    
    CDesCArray* textArray = new (ELeave) CDesCArrayFlat( 1 );
    CleanupStack::PushL( textArray );
    _LIT( KValue, "123456" );
    textArray->AppendL( KValue );
    
    valuePhoneArray->SetArray( *textArray );
    CDesCArray* arrayGet = valuePhoneArray->Array();
    STIF_ASSERT_TRUE( arrayGet == textArray );
    
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( valuePhoneArray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestPhoneArrayArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestPhoneArrayArrayL( CStifItemParser& aItem )
    {
    return TestPhoneArraySetArrayL( aItem );
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestPhoneArrayFormattedStringSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestPhoneArrayFormattedStringSizeL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValuePhoneArray* valuePhoneArray = CAknQueryValuePhoneArray::NewLC();
    STIF_ASSERT_NOT_NULL( valuePhoneArray );
    
    CDesCArray* textArray = new (ELeave) CDesCArrayFlat( 1 );
    CleanupStack::PushL( textArray );
    _LIT( KValue, "123456" );
    textArray->AppendL( KValue );
    
    valuePhoneArray->SetArray( *textArray );
    
    TInt size = valuePhoneArray->FormattedStringSize();
    STIF_ASSERT_NOT_EQUALS( 0, size );
    
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( valuePhoneArray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestPhoneArrayMdcaCountL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestPhoneArrayMdcaCountL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValuePhoneArray* valuePhoneArray = CAknQueryValuePhoneArray::NewLC();
    STIF_ASSERT_NOT_NULL( valuePhoneArray );
    
    CDesCArray* textArray = new (ELeave) CDesCArrayFlat( 1 );
    CleanupStack::PushL( textArray );
    _LIT( KValue, "123456" );
    textArray->AppendL( KValue );
    
    valuePhoneArray->SetArray( *textArray );
    
    TInt count = valuePhoneArray->MdcaCount();
    STIF_ASSERT_TRUE( 1 == count );
    
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( valuePhoneArray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestPhoneArrayMdcaPointL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestPhoneArrayMdcaPointL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValuePhoneArray* valuePhoneArray = CAknQueryValuePhoneArray::NewLC();
    STIF_ASSERT_NOT_NULL( valuePhoneArray );
    
    CDesCArray* textArray = new (ELeave) CDesCArrayFlat( 1 );
    CleanupStack::PushL( textArray );
    _LIT( KValue, "123456" );
    textArray->AppendL( KValue );
    
    valuePhoneArray->SetArray( *textArray );
    
    TPtrC point = valuePhoneArray->MdcaPoint( 0 );
    STIF_ASSERT_TRUE( point.Compare( KValue ) == 0 );
    
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( valuePhoneArray );
    
    return KErrNone;
    }

//End file


