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
* Description:  Test aknqueryvaluedate.h
*
*/

//INCLUDE
#include <aknqueryvaluedate.h>
#include <testsdkqueries.rsg>

#include "testsdkqueries.h"

const TInt KZero = 0;
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KThree = 3;

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVSetQueryModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDNewL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDate* date = CAknQueryValueDate::NewL();
    CleanupStack::PushL( date );
    
    STIF_ASSERT_NOT_NULL( date );
    
    CleanupStack::PopAndDestroy( date );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVSetQueryModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDNewLCL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDate* date = CAknQueryValueDate::NewLC();
    
    STIF_ASSERT_NOT_NULL( date );
    
    CleanupStack::PopAndDestroy( date );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVSetQueryModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDate* date = CAknQueryValueDate::NewLC();
    CleanupStack::PopAndDestroy( date );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVSetQueryModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDSetArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDate* date = CAknQueryValueDate::NewL();
    CleanupStack::PushL( date );
    
    CAknQueryValueDateArray* dateArray = CAknQueryValueDateArray::NewL( R_TESTQUERY_DATE_FORMAT );
    CleanupStack::PushL( dateArray );
    
    date->SetArrayL( dateArray );
    
    CleanupStack::Pop( dateArray );
    CleanupStack::PopAndDestroy( date );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVSetQueryModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDSetQueryCaptionL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDate* date = CAknQueryValueDate::NewL();
    CleanupStack::PushL( date );
    
    date->SetQueryCaption( R_TESTQUERY_CAPTION );
    
    CleanupStack::PopAndDestroy( date );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVSetQueryModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDValueL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDate* date = CAknQueryValueDate::NewL();
    CleanupStack::PushL( date );
    
    TTime compareTime( KZero );
    TTime returnTime = date->Value();
    STIF_ASSERT_EQUALS( compareTime, returnTime );
    
    CleanupStack::PopAndDestroy( date );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVSetQueryModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDMdcArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDate* date = CAknQueryValueDate::NewL();
    CleanupStack::PushL( date );
    
    const MDesCArray* returnArray = date->MdcArray();
    STIF_ASSERT_NULL( returnArray );
    
    CAknQueryValueDateArray* dateArray = CAknQueryValueDateArray::NewL( R_TESTQUERY_DATE_FORMAT );
    CleanupStack::PushL( dateArray );
        
    date->SetArrayL( dateArray );
    
    const MDesCArray* returnArrayTwo = date->MdcArray();
    
    STIF_ASSERT_EQUALS( dateArray, ( CAknQueryValueDateArray* )returnArrayTwo );
    
    CleanupStack::Pop( dateArray );
    CleanupStack::PopAndDestroy( date );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVSetQueryModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDCurrentValueTextLCL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDate* date = CAknQueryValueDate::NewL();
    CleanupStack::PushL( date );
    
    CAknQueryValueDateArray* dateArray = CAknQueryValueDateArray::NewL( R_TESTQUERY_DATE_FORMAT );
    CleanupStack::PushL( dateArray );
    
    CArrayFix<TTime>* timeArray = new( ELeave ) CArrayFixFlat<TTime>( 4 );
    CleanupStack::PushL( timeArray );
    
    TTime time1;
    time1.HomeTime();
    TTime time2;
    time2 = time1 + TTimeIntervalDays( 3 );
    
    timeArray->AppendL( time1 );
    timeArray->AppendL( time2 );
    
    dateArray->SetArray( *timeArray );
    
    date->SetArrayL( dateArray );
    
    HBufC* text = date->CurrentValueTextLC();
    STIF_ASSERT_NOT_NULL( text );
    
    CleanupStack::Pop( KThree );
    CleanupStack::PopAndDestroy( date );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVSetQueryModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDCurrentValueIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDate* date = CAknQueryValueDate::NewL();
    CleanupStack::PushL( date );
    
    TInt mIndex = date->CurrentValueIndex();
    STIF_ASSERT_EQUALS( KZero, mIndex );
    
    CAknQueryValueDateArray* dateArray = CAknQueryValueDateArray::NewL( R_TESTQUERY_DATE_FORMAT );
    CleanupStack::PushL( dateArray );
    
    CArrayFix<TTime>* timeArray = new( ELeave ) CArrayFixFlat<TTime>( 4 );
    CleanupStack::PushL( timeArray );
    
    TTime time1;
    time1.HomeTime();
    TTime time2;
    time2 = time1 + TTimeIntervalDays( 3 );
    
    timeArray->AppendL( time1 );
    timeArray->AppendL( time2 );
    
    dateArray->SetArray( *timeArray );
    
    date->SetArrayL( dateArray );
    
    date->SetCurrentValueIndex( KOne );
    
    mIndex = date->CurrentValueIndex();
    STIF_ASSERT_EQUALS( KOne, mIndex );
    
    CleanupStack::Pop( KTwo );
    CleanupStack::PopAndDestroy( date );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVSetQueryModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDSetCurrentValueIndexL( CStifItemParser& aItem )
    {
    TInt err = TestQVDCurrentValueIndexL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVSetQueryModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDCreateEditorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDate* date = CAknQueryValueDate::NewL();
    CleanupStack::PushL( date );
    
    CAknQueryValueDateArray* dateArray = CAknQueryValueDateArray::NewL( R_TESTQUERY_DATE_FORMAT );
    CleanupStack::PushL( dateArray );
    
    CArrayFix<TTime>* timeArray = new( ELeave ) CArrayFixFlat<TTime>( 4 );
    CleanupStack::PushL( timeArray );
    
    TTime time1;
    time1.HomeTime();
    TTime time2;
    time2 = time1 + TTimeIntervalDays( 3 );
    
    timeArray->AppendL( time1 );
    timeArray->AppendL( time2 );
    
    dateArray->SetArray( *timeArray );
    
    date->SetArrayL( dateArray );

    date->SetCurrentValueIndex( KZero );
    
    TBool flag = date->CreateEditorL();
    STIF_ASSERT_TRUE( flag );
    
    CleanupStack::Pop( KTwo );
    CleanupStack::PopAndDestroy( date );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDANewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDANewL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDateArray* dateArray = CAknQueryValueDateArray::NewL( R_TESTQUERY_DATE_FORMAT );
    CleanupStack::PushL( dateArray );
    
    STIF_ASSERT_NOT_NULL( dateArray );
    
    CleanupStack::PopAndDestroy( dateArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDANewLCL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDANewLCL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDateArray* dateArray = CAknQueryValueDateArray::NewLC( R_TESTQUERY_DATE_FORMAT );
    
    STIF_ASSERT_NOT_NULL( dateArray );
    
    CleanupStack::PopAndDestroy( dateArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDADestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDADestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDateArray* dateArray = CAknQueryValueDateArray::NewLC( R_TESTQUERY_DATE_FORMAT );
    CleanupStack::PopAndDestroy( dateArray );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDASetArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDASetArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDateArray* dateArray = CAknQueryValueDateArray::NewL( R_TESTQUERY_DATE_FORMAT );
    CleanupStack::PushL( dateArray );
    
    CArrayFix<TTime>* timeArray = new( ELeave ) CArrayFixFlat<TTime>( 4 );
    CleanupStack::PushL( timeArray );
    
    TTime time1;
    time1.HomeTime();
    TTime time2;
    time2 = time1 + TTimeIntervalDays( 3 );
    
    timeArray->AppendL( time1 );
    timeArray->AppendL( time2 );
    
    dateArray->SetArray( *timeArray );
    
    CleanupStack::Pop( timeArray );
    CleanupStack::PopAndDestroy( dateArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDAArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDAArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDateArray* dateArray = CAknQueryValueDateArray::NewL( R_TESTQUERY_DATE_FORMAT );
    CleanupStack::PushL( dateArray );
    
    CArrayFix<TTime>* returnArray = dateArray->Array();
    STIF_ASSERT_NULL( returnArray );
    
    CArrayFix<TTime>* timeArray = new( ELeave ) CArrayFixFlat<TTime>( 4 );
    CleanupStack::PushL( timeArray );
    
    TTime time1;
    time1.HomeTime();
    TTime time2;
    time2 = time1 + TTimeIntervalDays( 3 );
    
    timeArray->AppendL( time1 );
    timeArray->AppendL( time2 );
    
    dateArray->SetArray( *timeArray );
    
    returnArray = dateArray->Array();
    STIF_ASSERT_EQUALS( timeArray, returnArray );
    
    CleanupStack::Pop( timeArray );
    CleanupStack::PopAndDestroy( dateArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDAFormatStringL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDAFormatStringL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDateArray* dateArray = CAknQueryValueDateArray::NewL( R_TESTQUERY_DATE_FORMAT );
    CleanupStack::PushL( dateArray );
    
    CArrayFix<TTime>* timeArray = new( ELeave ) CArrayFixFlat<TTime>( 4 );
    CleanupStack::PushL( timeArray );
    
    TTime time1;
    time1.HomeTime();
    TTime time2;
    time2 = time1 + TTimeIntervalDays( 3 );
    
    timeArray->AppendL( time1 );
    timeArray->AppendL( time2 );
    
    dateArray->SetArray( *timeArray );
    
    const HBufC* buf = dateArray->FormatString();
    STIF_ASSERT_NOT_NULL( buf );
    
    CleanupStack::Pop( timeArray );
    CleanupStack::PopAndDestroy( dateArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDAFormattedStringSizeOneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDAFormattedStringSizeOneL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDateArray* dateArray = CAknQueryValueDateArray::NewL( R_TESTQUERY_DATE_FORMAT );
    CleanupStack::PushL( dateArray );
    
    CArrayFix<TTime>* timeArray = new( ELeave ) CArrayFixFlat<TTime>( 4 );
    CleanupStack::PushL( timeArray );
    
    TTime time1;
    time1.HomeTime();
    TTime time2;
    time2 = time1 + TTimeIntervalDays( 3 );
    
    timeArray->AppendL( time1 );
    timeArray->AppendL( time2 );
    
    dateArray->SetArray( *timeArray );
    
    const TInt size = dateArray->FormattedStringSize();
    STIF_ASSERT_NOT_EQUALS( KZero, size );
    
    CleanupStack::Pop( timeArray );
    CleanupStack::PopAndDestroy( dateArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDAFormattedStringSizeTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDAFormattedStringSizeTwoL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDateArray* dateArray = CAknQueryValueDateArray::NewL( R_TESTQUERY_DATE_FORMAT );
    CleanupStack::PushL( dateArray );
    
    CArrayFix<TTime>* timeArray = new( ELeave ) CArrayFixFlat<TTime>( 4 );
    CleanupStack::PushL( timeArray );
    
    TTime time1;
    time1.HomeTime();
    TTime time2;
    time2 = time1 + TTimeIntervalDays( 3 );
    
    timeArray->AppendL( time1 );
    timeArray->AppendL( time2 );
    
    dateArray->SetArray( *timeArray );
    
    TInt size = dateArray->FormattedStringSize();
    STIF_ASSERT_NOT_EQUALS( KZero, size );
    
    CleanupStack::Pop( timeArray );
    CleanupStack::PopAndDestroy( dateArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDAMdcaCountL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDAMdcaCountL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDateArray* dateArray = CAknQueryValueDateArray::NewL( R_TESTQUERY_DATE_FORMAT );
    CleanupStack::PushL( dateArray );
    
    CArrayFix<TTime>* timeArray = new( ELeave ) CArrayFixFlat<TTime>( 4 );
    CleanupStack::PushL( timeArray );
    
    TTime time1;
    time1.HomeTime();
    TTime time2;
    time2 = time1 + TTimeIntervalDays( 3 );
    
    timeArray->AppendL( time1 );
    timeArray->AppendL( time2 );
    
    dateArray->SetArray( *timeArray );
        
    TInt count = dateArray->MdcaCount();
    STIF_ASSERT_NOT_EQUALS( KZero, count );
    
    CleanupStack::Pop( timeArray );
    CleanupStack::PopAndDestroy( dateArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVDAMdcaPointL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVDAMdcaPointL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValueDateArray* dateArray = CAknQueryValueDateArray::NewL( R_TESTQUERY_DATE_FORMAT );
    CleanupStack::PushL( dateArray );
    
    CArrayFix<TTime>* timeArray = new( ELeave ) CArrayFixFlat<TTime>( 4 );
    CleanupStack::PushL( timeArray );
    
    TTime time1;
    time1.HomeTime();
    TTime time2;
    time2 = time1 + TTimeIntervalDays( 3 );
    
    timeArray->AppendL( time1 );
    timeArray->AppendL( time2 );
    
    dateArray->SetArray( *timeArray );
    
    for ( TInt mark = 0; mark < dateArray->MdcaCount(); mark++ )
        {
        TPtrC text = dateArray->MdcaPoint( mark );
        STIF_ASSERT_NOT_NULL( &text );
        }
    
    CleanupStack::Pop( timeArray );
    CleanupStack::PopAndDestroy( dateArray );
    return KErrNone;
    }

//End file


