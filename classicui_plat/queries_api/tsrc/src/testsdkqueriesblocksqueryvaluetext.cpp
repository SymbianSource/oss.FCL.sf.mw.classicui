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
* Description:  Test aknqueryvaluetext.h
*
*/

//INCLUDE
#include <aknqueryvaluetext.h>
#include <testsdkqueries.rsg>

#include "testsdkqueries.h"

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextNewL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueText* valueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( valueText );
    STIF_ASSERT_NOT_NULL( valueText );
    
    CleanupStack::PopAndDestroy( valueText );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextNewLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextNewLC( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueText* valueText = CAknQueryValueText::NewLC();
    STIF_ASSERT_NOT_NULL( valueText );
    
    CleanupStack::PopAndDestroy( valueText );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueText* valueText = CAknQueryValueText::NewLC();
    STIF_ASSERT_NOT_NULL( valueText );
    
    CleanupStack::Pop( valueText );
    delete valueText;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextSetArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextSetArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueText* valueText = CAknQueryValueText::NewLC();
    STIF_ASSERT_NOT_NULL( valueText );
    
    CAknQueryValueTextArray* array = CAknQueryValueTextArray::NewLC();
    STIF_ASSERT_NOT_NULL( array );
    
    valueText->SetArrayL( array );
    
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( valueText );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextSetQueryCaptionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextSetQueryCaptionL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueText* valueText = CAknQueryValueText::NewLC();
    STIF_ASSERT_NOT_NULL( valueText );
    
    valueText->SetQueryCaption( R_QUERY_VALUETEXT_STRING );
    
    CleanupStack::PopAndDestroy( valueText );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextValueL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueText* valueText = CAknQueryValueText::NewLC();
    STIF_ASSERT_NOT_NULL( valueText );
    
    HBufC* value = valueText->Value();
    CleanupStack::PushL( value );
    STIF_ASSERT_TRUE( value->Length() == 0 );
    
    CleanupStack::Pop( value );
    CleanupStack::PopAndDestroy( valueText );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextMdcArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextMdcArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueText* valueText = CAknQueryValueText::NewLC();
    STIF_ASSERT_NOT_NULL( valueText );
    
    CAknQueryValueTextArray* array = CAknQueryValueTextArray::NewLC();
    STIF_ASSERT_NOT_NULL( array );
    
    valueText->SetArrayL( array );
    
    const MDesCArray* mdcArray = valueText->MdcArray();
    STIF_ASSERT_NOT_NULL( mdcArray );
    
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( valueText );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextCurrentValueTextLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextCurrentValueTextLC( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueText* valueText = CAknQueryValueText::NewLC();
    STIF_ASSERT_NOT_NULL( valueText );
    
    CAknQueryValueTextArray* array = CAknQueryValueTextArray::NewLC();
    STIF_ASSERT_NOT_NULL( array );
    
    CDesCArray* textArray = new (ELeave) CDesCArrayFlat( 1 );
    CleanupStack::PushL( textArray );
    _LIT( KValue, "value1" );
    textArray->AppendL( KValue );
    
    array->SetArray( *textArray );
    valueText->SetArrayL( array );
    
    valueText->SetCurrentValueIndex( 0 );
    HBufC* value = valueText->CurrentValueTextLC();
    STIF_ASSERT_TRUE( value->Compare( KValue ) == 0 );
    
    CleanupStack::PopAndDestroy( value );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( valueText );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextCurrentValueIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextCurrentValueIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueText* valueText = CAknQueryValueText::NewLC();
    STIF_ASSERT_NOT_NULL( valueText );
    
    CAknQueryValueTextArray* array = CAknQueryValueTextArray::NewLC();
    STIF_ASSERT_NOT_NULL( array );
    
    CDesCArray* textArray = new (ELeave) CDesCArrayFlat( 1 );
    CleanupStack::PushL( textArray );
    _LIT( KValue, "value1" );
    textArray->AppendL( KValue );
    
    array->SetArray( *textArray );
    valueText->SetArrayL( array );
    
    valueText->SetCurrentValueIndex( 0 );
    STIF_ASSERT_TRUE( valueText->CurrentValueIndex() == 0 );
    
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( valueText );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextSetCurrentValueIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextSetCurrentValueIndexL( CStifItemParser& aItem )
    {

    return TestTextCurrentValueIndexL( aItem );
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextCreateEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextCreateEditorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueText* valueText = CAknQueryValueText::NewLC();
    STIF_ASSERT_NOT_NULL( valueText );
    
    CAknQueryValueTextArray* array = CAknQueryValueTextArray::NewLC();
    STIF_ASSERT_NOT_NULL( array );
    
    CDesCArray* textArray = new (ELeave) CDesCArrayFlat( 1 );
    CleanupStack::PushL( textArray );
    _LIT( KValue, "value1" );
    textArray->AppendL( KValue );
    
    array->SetArray( *textArray );
    valueText->SetArrayL( array );
    
    valueText->SetCurrentValueIndex( 0 );
    
    TBool flag = valueText->CreateEditorL();
    STIF_ASSERT_TRUE( flag );
    
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( valueText );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextArrayNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextArrayNewL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTextArray* valueTextArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( valueTextArray );
    STIF_ASSERT_NOT_NULL( valueTextArray );
    
    CleanupStack::PopAndDestroy( valueTextArray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextArrayNewLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextArrayNewLC( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTextArray* valueTextArray = CAknQueryValueTextArray::NewLC();
    STIF_ASSERT_NOT_NULL( valueTextArray );
    
    CleanupStack::PopAndDestroy( valueTextArray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextArrayDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextArrayDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTextArray* valueTextArray = CAknQueryValueTextArray::NewLC();
    STIF_ASSERT_NOT_NULL( valueTextArray );
    
    CleanupStack::Pop( valueTextArray );
    delete valueTextArray;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextArraySetArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextArraySetArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTextArray* valueTextArray = CAknQueryValueTextArray::NewLC();
    STIF_ASSERT_NOT_NULL( valueTextArray );
    
    CDesCArray* textArray = new (ELeave) CDesCArrayFlat( 1 );
    CleanupStack::PushL( textArray );
    _LIT( KValue, "value1" );
    textArray->AppendL( KValue );
    
    valueTextArray->SetArray( *textArray );
    CDesCArray* arrayGet = valueTextArray->Array();
    STIF_ASSERT_TRUE( arrayGet == textArray );
    
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( valueTextArray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextArrayArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextArrayArrayL( CStifItemParser& aItem )
    {
    return TestTextArraySetArrayL( aItem );
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextArrayFormattedStringSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextArrayFormattedStringSizeL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTextArray* valueTextArray = CAknQueryValueTextArray::NewLC();
    STIF_ASSERT_NOT_NULL( valueTextArray );
    
    CDesCArray* textArray = new (ELeave) CDesCArrayFlat( 1 );
    CleanupStack::PushL( textArray );
    _LIT( KValue, "value1" );
    textArray->AppendL( KValue );
    
    valueTextArray->SetArray( *textArray );
    
    TInt size = valueTextArray->FormattedStringSize();
    STIF_ASSERT_NOT_EQUALS( 0, size );
    
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( valueTextArray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextArrayMdcaCountL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextArrayMdcaCountL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTextArray* valueTextArray = CAknQueryValueTextArray::NewLC();
    STIF_ASSERT_NOT_NULL( valueTextArray );
    
    CDesCArray* textArray = new (ELeave) CDesCArrayFlat( 1 );
    CleanupStack::PushL( textArray );
    _LIT( KValue, "value1" );
    textArray->AppendL( KValue );
    
    valueTextArray->SetArray( *textArray );
    
    TInt count = valueTextArray->MdcaCount();
    STIF_ASSERT_TRUE( 1 == count );
    
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( valueTextArray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextArrayMdcaPointL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextArrayMdcaPointL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueTextArray* valueTextArray = CAknQueryValueTextArray::NewLC();
    STIF_ASSERT_NOT_NULL( valueTextArray );
    
    CDesCArray* textArray = new (ELeave) CDesCArrayFlat( 1 );
    CleanupStack::PushL( textArray );
    _LIT( KValue, "value1" );
    textArray->AppendL( KValue );
    
    valueTextArray->SetArray( *textArray );
    
    TPtrC point = valueTextArray->MdcaPoint( 0 );
    STIF_ASSERT_TRUE( point.Compare( KValue ) == 0 );
    
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( valueTextArray );
    
    return KErrNone;
    }

//End file


