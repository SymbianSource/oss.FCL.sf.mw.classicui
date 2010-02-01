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
* Description:  Test aknqueryvaluetime.h
*
*/

//INCLUDE
#include <aknqueryvaluetime.h>
#include <testsdkqueries.rsg>
#include <avkon.rsg>

#include "testsdkqueries.h"

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeNewL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTime* valueTime = CAknQueryValueTime::NewL();
    CleanupStack::PushL( valueTime );
    STIF_ASSERT_NOT_NULL( valueTime );
    
    CleanupStack::PopAndDestroy( valueTime );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeNewLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeNewLC( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTime* valueTime = CAknQueryValueTime::NewLC();
    STIF_ASSERT_NOT_NULL( valueTime );
    
    CleanupStack::PopAndDestroy( valueTime );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTime* valueTime = CAknQueryValueTime::NewLC();
    STIF_ASSERT_NOT_NULL( valueTime );
    
    CleanupStack::Pop( valueTime );
    delete valueTime;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeSetArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeSetArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTime* valueTime = CAknQueryValueTime::NewLC();
    STIF_ASSERT_NOT_NULL( valueTime );
    
    CAknQueryValueTimeArray* array = 
        CAknQueryValueTimeArray::NewLC( R_AVKON_TBUF_POPUP_FIELD_DEFAULT_TIME_FORMAT );
    STIF_ASSERT_NOT_NULL( array );
    
    valueTime->SetArrayL( array );
    
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( valueTime );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeSetQueryCaptionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeSetQueryCaptionL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTime* valueTime = CAknQueryValueTime::NewLC();
    STIF_ASSERT_NOT_NULL( valueTime );
    
    valueTime->SetQueryCaption( R_QUERY_VALUETEXT_STRING );
    
    CleanupStack::PopAndDestroy( valueTime );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeValueL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTime* valueTime = CAknQueryValueTime::NewLC();
    STIF_ASSERT_NOT_NULL( valueTime );
    
    TTime time = valueTime->Value();
    TTime compareTime( 0 );
    STIF_ASSERT_EQUALS( compareTime, time );
    
    CleanupStack::PopAndDestroy( valueTime );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeMdcArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeMdcArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTime* valueTime = CAknQueryValueTime::NewLC();
    STIF_ASSERT_NOT_NULL( valueTime );
    
    CAknQueryValueTimeArray* array = 
        CAknQueryValueTimeArray::NewLC( R_AVKON_TBUF_POPUP_FIELD_DEFAULT_TIME_FORMAT );
    STIF_ASSERT_NOT_NULL( array );
    
    valueTime->SetArrayL( array );
    
    const MDesCArray* mdcArray = valueTime->MdcArray();
    STIF_ASSERT_NOT_NULL( mdcArray );
    
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( valueTime );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeCurrentValueTextLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeCurrentValueTextLC( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTime* valueTime = CAknQueryValueTime::NewLC();
    STIF_ASSERT_NOT_NULL( valueTime );
    
    CAknQueryValueTimeArray* array = 
        CAknQueryValueTimeArray::NewLC( R_AVKON_TBUF_POPUP_FIELD_DEFAULT_TIME_FORMAT );
    STIF_ASSERT_NOT_NULL( array );
    
    CArrayFix<TTime>* textArray = new (ELeave) CArrayFixFlat<TTime>( 1 );
    CleanupStack::PushL( textArray );
    TTime time;
    textArray->AppendL( time );
    
    array->SetArray( *textArray );
    valueTime->SetArrayL( array );
    
    valueTime->SetCurrentValueIndex( 0 );
    HBufC* value = valueTime->CurrentValueTextLC();
    
    CleanupStack::PopAndDestroy( value );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( valueTime );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeCurrentValueIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeCurrentValueIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTime* valueTime = CAknQueryValueTime::NewLC();
    STIF_ASSERT_NOT_NULL( valueTime );
    
    CAknQueryValueTimeArray* array = 
        CAknQueryValueTimeArray::NewLC( R_AVKON_TBUF_POPUP_FIELD_DEFAULT_TIME_FORMAT );
    STIF_ASSERT_NOT_NULL( array );
    
    CArrayFix<TTime>* textArray = new (ELeave) CArrayFixFlat<TTime>( 1 );
    CleanupStack::PushL( textArray );
    TTime time;
    textArray->AppendL( time );
    
    array->SetArray( *textArray );
    valueTime->SetArrayL( array );
    
    valueTime->SetCurrentValueIndex( 0 );
    STIF_ASSERT_TRUE( valueTime->CurrentValueIndex() == 0 );
    
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( valueTime );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeSetCurrentValueIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeSetCurrentValueIndexL( CStifItemParser& aItem )
    {

    return TestTimeCurrentValueIndexL( aItem );
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeCreateEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeCreateEditorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTime* valueTime = CAknQueryValueTime::NewLC();
    STIF_ASSERT_NOT_NULL( valueTime );
    
    CAknQueryValueTimeArray* array = 
        CAknQueryValueTimeArray::NewLC( R_AVKON_TBUF_POPUP_FIELD_DEFAULT_TIME_FORMAT );
    STIF_ASSERT_NOT_NULL( array );
    
    CArrayFix<TTime>* textArray = new (ELeave) CArrayFixFlat<TTime>( 1 );
    CleanupStack::PushL( textArray );
    TTime time;
    textArray->AppendL( time );
    
    array->SetArray( *textArray );
    valueTime->SetArrayL( array );
    
    valueTime->SetCurrentValueIndex( 0 );
    
    TBool flag = valueTime->CreateEditorL();
    STIF_ASSERT_TRUE( flag );
    
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( valueTime );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeArrayNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeArrayNewL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTimeArray* valueTimeArray = 
        CAknQueryValueTimeArray::NewL( R_AVKON_TBUF_POPUP_FIELD_DEFAULT_TIME_FORMAT );
    CleanupStack::PushL( valueTimeArray );
    STIF_ASSERT_NOT_NULL( valueTimeArray );
    
    CleanupStack::PopAndDestroy( valueTimeArray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeArrayNewLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeArrayNewLC( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTimeArray* valueTimeArray = 
        CAknQueryValueTimeArray::NewLC( R_AVKON_TBUF_POPUP_FIELD_DEFAULT_TIME_FORMAT );
    STIF_ASSERT_NOT_NULL( valueTimeArray );
    
    CleanupStack::PopAndDestroy( valueTimeArray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeArrayDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeArrayDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTimeArray* valueTimeArray = 
        CAknQueryValueTimeArray::NewLC( R_AVKON_TBUF_POPUP_FIELD_DEFAULT_TIME_FORMAT );
    STIF_ASSERT_NOT_NULL( valueTimeArray );
    
    CleanupStack::Pop( valueTimeArray );
    delete valueTimeArray;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeArraySetArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeArraySetArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTimeArray* valueTimeArray = 
        CAknQueryValueTimeArray::NewLC( R_AVKON_TBUF_POPUP_FIELD_DEFAULT_TIME_FORMAT );
    STIF_ASSERT_NOT_NULL( valueTimeArray );
    
    CArrayFix<TTime>* textArray = new (ELeave) CArrayFixFlat<TTime>( 1 );
    CleanupStack::PushL( textArray );
    TTime time;
    textArray->AppendL( time );
    
    valueTimeArray->SetArray( *textArray );
    CArrayFix<TTime>* arrayGet = valueTimeArray->Array();
    STIF_ASSERT_TRUE( arrayGet == textArray );
    
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( valueTimeArray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeArrayArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeArrayArrayL( CStifItemParser& aItem )
    {
    return TestTimeArraySetArrayL( aItem );
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeArrayFormatStringL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeArrayFormatStringL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTimeArray* valueTimeArray = 
        CAknQueryValueTimeArray::NewLC( R_AVKON_TBUF_POPUP_FIELD_DEFAULT_TIME_FORMAT );
    STIF_ASSERT_NOT_NULL( valueTimeArray );
    
    CArrayFix<TTime>* textArray = new (ELeave) CArrayFixFlat<TTime>( 1 );
    CleanupStack::PushL( textArray );
    TTime time;
    textArray->AppendL( time );
    
    const HBufC* string = valueTimeArray->FormatString();
    STIF_ASSERT_NOT_NULL( string );
    
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( valueTimeArray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeArrayFormattedStringSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeArrayFormattedStringSizeL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTimeArray* valueTimeArray = 
        CAknQueryValueTimeArray::NewLC( R_AVKON_TBUF_POPUP_FIELD_DEFAULT_TIME_FORMAT );
    STIF_ASSERT_NOT_NULL( valueTimeArray );
    
    CArrayFix<TTime>* textArray = new (ELeave) CArrayFixFlat<TTime>( 1 );
    CleanupStack::PushL( textArray );
    TTime time;
    textArray->AppendL( time );
    
    valueTimeArray->SetArray( *textArray );
    
    TInt size = valueTimeArray->FormattedStringSize();
    STIF_ASSERT_NOT_EQUALS( 0, size );
    
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( valueTimeArray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeArrayMdcaCountL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeArrayMdcaCountL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTimeArray* valueTimeArray = 
        CAknQueryValueTimeArray::NewLC( R_AVKON_TBUF_POPUP_FIELD_DEFAULT_TIME_FORMAT );
    STIF_ASSERT_NOT_NULL( valueTimeArray );
    
    CArrayFix<TTime>* textArray = new (ELeave) CArrayFixFlat<TTime>( 1 );
    CleanupStack::PushL( textArray );
    TTime time;
    textArray->AppendL( time );
    
    valueTimeArray->SetArray( *textArray );
    
    TInt count = valueTimeArray->MdcaCount();
    STIF_ASSERT_TRUE( 1 == count );
    
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( valueTimeArray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeArrayMdcaPointL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeArrayMdcaPointL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTimeArray* valueTimeArray = 
        CAknQueryValueTimeArray::NewLC( R_AVKON_TBUF_POPUP_FIELD_DEFAULT_TIME_FORMAT );
    STIF_ASSERT_NOT_NULL( valueTimeArray );
    
    CArrayFix<TTime>* textArray = new (ELeave) CArrayFixFlat<TTime>( 1 );
    CleanupStack::PushL( textArray );
    TTime time;
    textArray->AppendL( time );
    
    valueTimeArray->SetArray( *textArray );
    
    TPtrC point = valueTimeArray->MdcaPoint( 0 );
    STIF_ASSERT_NOT_NULL( &point );
    
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( valueTimeArray );
    
    return KErrNone;
    }

//End file


