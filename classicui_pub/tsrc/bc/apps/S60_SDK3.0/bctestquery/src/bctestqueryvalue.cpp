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
* Description:         test case for query value classes
*
*/









#include <w32std.h>
#include <eikenv.h>
#include <aknqueryvaluedate.h>
#include <aknqueryvalueduration.h>
#include <aknqueryvaluenumber.h>
#include <aknqueryvaluephone.h>
#include <aknqueryvaluetext.h>
#include <aknqueryvaluetime.h>

#include "bctestqueryvalue.h"
#include "bctestquerycontainer.h"
#include "bctestquery.hrh"
#include <bctestquery.rsg>

const TInt KTextLength = 64;

_LIT( KValueDateTest1, "CAknQueryValueDateArray::NewL" );
_LIT( KValueDateTest2, "CAknQueryValueDateArray::SetArray" );
_LIT( KValueDateTest3, "CAknQueryValueDateArray::FormatString" );
_LIT( KValueDateTest4, "CAknQueryValueDateArray::FormattedStringSize" );
_LIT( KValueDateTest5, "CAknQueryValueDateArray::MdcaCount" );
_LIT( KValueDateTest6, "CAknQueryValueDateArray::MdcaPoint" );
_LIT( KValueDateTest7, "CAknQueryValueDate::NewL" );
_LIT( KValueDateTest8, "CAknQueryValueDate::SetQueryCaption" );
_LIT( KValueDateTest9, "CAknQueryValueDate::SetArrayL" );
_LIT( KValueDateTest10, "CAknQueryValueDate::MdcArray" );
_LIT( KValueDateTest11, "CAknQueryValueDate::SetCurrentValueIndex" );
_LIT( KValueDateTest12, "CAknQueryValueDate::CurrentValueIndex" );
_LIT( KValueDateTest13, "CAknQueryValueDate::Value" );
_LIT( KValueDateTest14, "CAknQueryValueDate::CurrentValueTextLC" );
_LIT( KValueDateTest15, "CAknQueryValueDate::CreateEditorL" );
_LIT( KValueDateTest16, "CAknQueryValue::AppendValueIfNewL" );
_LIT( KValueDateTest17, "CAknQueryValue::SetQueryMode" );
_LIT( KValueDateTest18, "CAknQueryValue::SetSettingPageResourceIds" );
_LIT( KValueDateTest19, "CAknQueryValueDate::SetAutoAppend" );

_LIT( KValueDurationTest1, "CAknQueryValueDurationArray::NewL" );
_LIT( KValueDurationTest2, "CAknQueryValueDurationArray::SetArray" );
_LIT( KValueDurationTest3, "CAknQueryValueDurationArray::FormatString" );
_LIT( KValueDurationTest4, "CAknQueryValueDurationArray::FormattedStringSize" );
_LIT( KValueDurationTest16, "CAknQueryValueDurationArray::FormatDuration" );
_LIT( KValueDurationTest5, "CAknQueryValueDurationArray::MdcaCount" );
_LIT( KValueDurationTest6, "CAknQueryValueDurationArray::MdcaPoint" );
_LIT( KValueDurationTest7, "CAknQueryValueDuration::NewL" );
_LIT( KValueDurationTest8, "CAknQueryValueDuration::SetQueryCaption" );
_LIT( KValueDurationTest9, "CAknQueryValueDuration::SetArrayL" );
_LIT( KValueDurationTest10, "CAknQueryValueDuration::MdcArray" );
_LIT( KValueDurationTest11, "CAknQueryValueDuration::SetCurrentValueIndex" );
_LIT( KValueDurationTest12, "CAknQueryValueDuration::CurrentValueIndex" );
_LIT( KValueDurationTest13, "CAknQueryValueDuration::Value" );
_LIT( KValueDurationTest14, "CAknQueryValueDuration::CurrentValueTextLC" );
_LIT( KValueDurationTest15, "CAknQueryValueDuration::CreateEditorL" );

_LIT( KValueNumberTest1, "CAknQueryValueNumberArray::NewL" );
_LIT( KValueNumberTest2, "CAknQueryValueNumberArray::SetArray" );
_LIT( KValueNumberTest3, "CAknQueryValueNumberArray::FormatString" );
_LIT( KValueNumberTest4, "CAknQueryValueNumberArray::FormattedStringSize" );
_LIT( KValueNumberTest5, "CAknQueryValueNumberArray::MdcaCount" );
_LIT( KValueNumberTest6, "CAknQueryValueNumberArray::MdcaPoint" );
_LIT( KValueNumberTest7, "CAknQueryValueNumber::NewL" );
_LIT( KValueNumberTest8, "CAknQueryValueNumber::SetQueryCaption" );
_LIT( KValueNumberTest9, "CAknQueryValueNumber::SetArrayL" );
_LIT( KValueNumberTest10, "CAknQueryValueNumber::MdcArray" );
_LIT( KValueNumberTest11, "CAknQueryValueNumber::SetCurrentValueIndex" );
_LIT( KValueNumberTest12, "CAknQueryValueNumber::CurrentValueIndex" );
_LIT( KValueNumberTest13, "CAknQueryValueNumber::Value" );
_LIT( KValueNumberTest14, "CAknQueryValueNumber::CurrentValueTextLC" );
_LIT( KValueNumberTest15, "CAknQueryValueNumber::CreateEditorL" );

_LIT( KValuePhoneTest1, "CAknQueryValuePhoneArray::NewL" );
_LIT( KValuePhoneTest2, "CAknQueryValuePhoneArray::SetArray" );
_LIT( KValuePhoneTest4, "CAknQueryValuePhoneArray::FormattedStringSize" );
_LIT( KValuePhoneTest5, "CAknQueryValuePhoneArray::MdcaCount" );
_LIT( KValuePhoneTest6, "CAknQueryValuePhoneArray::MdcaPoint" );
_LIT( KValuePhoneTest7, "CAknQueryValuePhone::NewL" );
_LIT( KValuePhoneTest8, "CAknQueryValuePhone::SetQueryCaption" );
_LIT( KValuePhoneTest9, "CAknQueryValuePhone::SetArrayL" );
_LIT( KValuePhoneTest10, "CAknQueryValuePhone::MdcArray" );
_LIT( KValuePhoneTest11, "CAknQueryValuePhone::SetCurrentValueIndex" );
_LIT( KValuePhoneTest12, "CAknQueryValuePhone::CurrentValueIndex" );
_LIT( KValuePhoneTest13, "CAknQueryValuePhone::Value" );
_LIT( KValuePhoneTest14, "CAknQueryValuePhone::CurrentValueTextLC" );
_LIT( KValuePhoneTest15, "CAknQueryValuePhone::CreateEditorL" );

_LIT( KValueTextTest1, "CAknQueryValueTextArray::NewL" );
_LIT( KValueTextTest2, "CAknQueryValueTextArray::SetArray" );
_LIT( KValueTextTest4, "CAknQueryValueTextArray::FormattedStringSize" );
_LIT( KValueTextTest5, "CAknQueryValueTextArray::MdcaCount" );
_LIT( KValueTextTest6, "CAknQueryValueTextArray::MdcaPoint" );
_LIT( KValueTextTest7, "CAknQueryValueText::NewL" );
_LIT( KValueTextTest8, "CAknQueryValueText::SetQueryCaption" );
_LIT( KValueTextTest9, "CAknQueryValueText::SetArrayL" );
_LIT( KValueTextTest10, "CAknQueryValueText::MdcArray" );
_LIT( KValueTextTest11, "CAknQueryValueText::SetCurrentValueIndex" );
_LIT( KValueTextTest12, "CAknQueryValueText::CurrentValueIndex" );
_LIT( KValueTextTest13, "CAknQueryValueText::Value" );
_LIT( KValueTextTest14, "CAknQueryValueText::CurrentValueTextLC" );
_LIT( KValueTextTest15, "CAknQueryValueText::CreateEditorL" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestQueryValue* CBCTestQueryValue::NewL( CBCTestQueryContainer* aContainer,
    CEikonEnv* aEnv )
    {
    CBCTestQueryValue* self = new( ELeave ) CBCTestQueryValue( 
        aContainer, aEnv );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestQueryValue::CBCTestQueryValue(  CBCTestQueryContainer* aContainer, 
    CEikonEnv* aEnv ): iContainer( aContainer ), iEnv( aEnv )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestQueryValue::~CBCTestQueryValue()
    {
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestQueryValue::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestQueryValue::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestQueryValue::BuildScriptL()
    {
    for ( TInt i = 0; i <= EBCTestCmdOutline19 - EBCTestCmdOutline14; i++ )
        {
        AddTestL( LeftCBA, REP( Down, 2 ), KeyOK, TEND );
        AddTestL( REP( Down, i ), KeyOK, LeftCBA, TEND );
        // for outline15
        if ( i == EBCTestCmdOutline15 - EBCTestCmdOutline14 )
            {
            AddTestL( LeftCBA, TEND );
            }
        }
    }
    
// ---------------------------------------------------------------------------
// CBCTestQueryValue::RunL
// ---------------------------------------------------------------------------
//
void CBCTestQueryValue::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline14 || aCmd > EBCTestCmdOutline19 )
        {
        return;
        }       
    switch ( aCmd )  
        {
        case EBCTestCmdOutline14:
            TestQueryValueDateL();            
            break;
        case EBCTestCmdOutline15:
            TestQueryValueDurationL();
            break;
        case EBCTestCmdOutline16:
            TestQueryValueNumberL();
            break;
        case EBCTestCmdOutline17:
            TestQueryValuePhoneL();
            break;
        case EBCTestCmdOutline18:
            TestQueryValueTextL();
            break;
        case EBCTestCmdOutline19:
            TestQueryValueTimeL();
            break;        
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// Test CAknQueryValueDate
// ---------------------------------------------------------------------------
//
void CBCTestQueryValue::TestQueryValueDateL()
    {
    CAknQueryValueDateArray* dateArray = CAknQueryValueDateArray::NewL(
        R_BCTESTQUERY_DATE_FORMAT );
    CleanupStack::PushL( dateArray );
    AssertNotNullL( dateArray, KValueDateTest1 );
    
    CArrayFix<TTime>* timeArray = new( ELeave ) CArrayFixFlat<TTime>( 4 );
    CleanupStack::PushL( timeArray );
    TTime time1;
    time1.HomeTime();
    TTime time2;
    time2 = time1 + TTimeIntervalDays( 3 );
    timeArray->AppendL( time1 );
    timeArray->AppendL( time2 );
    
    dateArray->SetArray( *timeArray );
    AssertTrueL( ETrue, KValueDateTest2 );
            
    const HBufC* buf = dateArray->FormatString();
    AssertTrueL( ETrue, KValueDateTest3 );
    
    const TInt size = dateArray->FormattedStringSize();
    AssertTrueL( ETrue, KValueDateTest4 );
    
    TInt mdcaCount = dateArray->MdcaCount();
    AssertTrueL( ETrue, KValueDateTest5 );
    for ( TInt i = 0; i < mdcaCount; i++ )
        {
        TPtrC text = dateArray->MdcaPoint( i );
        }
    AssertTrueL( ETrue, KValueDateTest6 );
    
    CAknQueryValueDate* date = CAknQueryValueDate::NewL();
    CleanupStack::PushL( date );
    AssertNotNullL( date, KValueDateTest7 );
    
    date->CAknQueryValue::AppendValueIfNewL();
    AssertTrueL( ETrue, KValueDateTest16 );
    
    date->SetQueryMode( MAknQueryValue::ESettingPageMode );
    date->SetQueryMode( MAknQueryValue::EQueryMode );
    AssertTrueL( ETrue, KValueDateTest17 );
    
    date->SetSettingPageResourceIds( 0, 0 );
    AssertTrueL( ETrue, KValueDateTest18 );
    
    date->SetQueryCaption( R_BCTESTQUERY_CAPTION );
    AssertTrueL( ETrue, KValueDateTest8 );
    
    date->SetArrayL( dateArray );
    AssertTrueL( ETrue, KValueDateTest9 );
        
    const MDesCArray* mdescArray = date->MdcArray();
    AssertTrueL( ETrue, KValueDateTest10 );
    
    date->SetCurrentValueIndex( 0 );
    AssertTrueL( ETrue, KValueDateTest11 );
    
    TInt index = date->CurrentValueIndex();
    AssertTrueL( ETrue, KValueDateTest12 );
    
    TTime dateTime = date->Value();
    AssertTrueL( ETrue, KValueDateTest13 );
    
    HBufC* text = date->CurrentValueTextLC();
    AssertTrueL( ETrue, KValueDateTest14 );
    
    TBool create = date->CreateEditorL();
    AssertTrueL( ETrue, KValueDateTest15 );
    
    date->SetAutoAppend( ETrue );
    date->SetAutoAppend( EFalse );
    AssertTrueL( ETrue, KValueDateTest19 );
        
    CleanupStack::PopAndDestroy( text );
    CleanupStack::PopAndDestroy( date );
    CleanupStack::PopAndDestroy( timeArray );
    CleanupStack::PopAndDestroy( dateArray );
    }
    
// ---------------------------------------------------------------------------
// Test CAknQueryValueDuration
// ---------------------------------------------------------------------------
//
void CBCTestQueryValue::TestQueryValueDurationL()
    {
    CArrayFix<TTimeIntervalSeconds>* durationArray = new( ELeave ) 
        CArrayFixFlat<TTimeIntervalSeconds>( 2 );
    CleanupStack::PushL( durationArray );
    TTimeIntervalSeconds dura1( 200 );
    TTimeIntervalSeconds dura2( 7800 );
    durationArray->AppendL( dura1 );
    durationArray->AppendL( dura2 );
    
    CAknQueryValueDurationArray* array = CAknQueryValueDurationArray::NewL(
        R_BCTESTQUERY_TIME_FORMAT );
    CleanupStack::PushL( array );
    AssertNotNullL( array, KValueDurationTest1 );
    
    array->SetArray( *durationArray );
    AssertTrueL( ETrue, KValueDurationTest2 );
    
    const HBufC* buf = array->FormatString();
    AssertTrueL( ETrue, KValueDurationTest3 );
    
    const TInt size = array->FormattedStringSize();
    AssertTrueL( ETrue, KValueDurationTest4 );
    
    TBufC<KTextLength> formatText;
    TPtr ptr( formatText.Des() );
    TTimeIntervalSeconds dura( 10000 );
    array->FormatDuration( ptr, dura );
    AssertTrueL( ETrue, KValueDurationTest16 );
    
    TInt mdcaCount = array->MdcaCount();
    AssertTrueL( ETrue, KValueDurationTest5 );
    for ( TInt i = 0; i < mdcaCount; i++ )
        {
        TPtrC text = array->MdcaPoint( i );
        }
    AssertTrueL( ETrue, KValueDurationTest6 );
    
    CAknQueryValueDuration* duration = CAknQueryValueDuration::NewL();
    CleanupStack::PushL( duration );
    AssertNotNullL( duration, KValueDurationTest7 );
    
    duration->SetQueryCaption( R_BCTESTQUERY_CAPTION );
    AssertNotNullL( duration, KValueDurationTest8 );
    
    duration->SetArrayL( array );
    AssertNotNullL( duration, KValueDurationTest9 );
    
    const MDesCArray* mdescArray = duration->MdcArray();    
    AssertNotNullL( duration, KValueDurationTest10 );
        
    duration->SetCurrentValueIndex( 1 );
    AssertNotNullL( duration, KValueDurationTest11 );
    
    TInt index = duration->CurrentValueIndex();
    AssertNotNullL( duration, KValueDurationTest12 );
    
    HBufC* text = duration->CurrentValueTextLC();
    AssertNotNullL( duration, KValueDurationTest13 );
    
    TTimeIntervalSeconds secondValue = duration->Value();
    AssertNotNullL( duration, KValueDurationTest14 );
    
    duration->CreateEditorL();
    AssertNotNullL( duration, KValueDurationTest15 );
    
    CleanupStack::PopAndDestroy( text );
    CleanupStack::PopAndDestroy( duration );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( durationArray );
    }
    
// ---------------------------------------------------------------------------
// Test CAknQueryValueNumber
// ---------------------------------------------------------------------------
//
void CBCTestQueryValue::TestQueryValueNumberL()
    {
    CArrayFix<TInt>* numberArray = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( numberArray );
    numberArray->AppendL( 134567 );
    numberArray->AppendL( 25890 );
    
    CAknQueryValueNumberArray* array = CAknQueryValueNumberArray::NewL(
        R_BCTESTQUERY_NUMBER_FORMAT );
    CleanupStack::PushL( array );
    AssertNotNullL( array, KValueNumberTest1 );
    
    array->SetArray( *numberArray );
    AssertTrueL( ETrue, KValueNumberTest2 );
    
    const HBufC* buf = array->FormatString();
    AssertTrueL( ETrue, KValueNumberTest3 );
    
    const TInt stringSize = array->FormattedStringSize();
    AssertTrueL( ETrue, KValueNumberTest4 );
    
    TInt mdcaCount = array->MdcaCount();
    AssertTrueL( ETrue, KValueNumberTest5 );
    for ( TInt i = 0; i < mdcaCount; i++ )
        {
        TPtrC text = array->MdcaPoint( i );
        }
    AssertTrueL( ETrue, KValueNumberTest6 );
        
    CAknQueryValueNumber* number = CAknQueryValueNumber::NewL();
    CleanupStack::PushL( number );
    AssertNotNullL( number, KValueNumberTest7 );
    
    number->SetQueryCaption( R_BCTESTQUERY_CAPTION );
    AssertTrueL( ETrue, KValueNumberTest8 );
    
    number->SetArrayL( array );
    AssertTrueL( ETrue, KValueNumberTest9 );
    
    const MDesCArray* mdcArray = number->MdcArray();
    AssertTrueL( ETrue, KValueNumberTest10 );
    
    number->SetCurrentValueIndex( 0 );
    AssertTrueL( ETrue, KValueNumberTest11 );
    
    TInt index = number->CurrentValueIndex();
    AssertTrueL( ETrue, KValueNumberTest12 );
    
    TInt numberValue = number->Value();
    AssertTrueL( ETrue, KValueNumberTest13 );
    
    HBufC* text = number->CurrentValueTextLC();
    AssertTrueL( ETrue, KValueNumberTest14 );
    
    number->CreateEditorL();
    AssertTrueL( ETrue, KValueNumberTest15 );
    
    CleanupStack::PopAndDestroy( text );
    CleanupStack::PopAndDestroy( number );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( numberArray );
    }
    
// ---------------------------------------------------------------------------
// Test CAknQueryValuePhone
// ---------------------------------------------------------------------------
//
void CBCTestQueryValue::TestQueryValuePhoneL()
    {
    CDesCArray* textArray = new( ELeave ) CDesCArrayFlat( 2 );
    CleanupStack::PushL( textArray );
    _LIT( KPhoneValue1, "010-12345678" );
    _LIT( KPhoneValue2, "13512345678" );
    textArray->AppendL( KPhoneValue1 );
    textArray->AppendL( KPhoneValue2 );
    
    CAknQueryValuePhoneArray* array = CAknQueryValuePhoneArray::NewL();
    CleanupStack::PushL( array );
    AssertNotNullL( array, KValuePhoneTest1 );
    
    array->SetArray( *textArray );
    AssertTrueL( ETrue, KValuePhoneTest2 );
    
    const TInt stringSize = array->FormattedStringSize();
    AssertTrueL( ETrue, KValuePhoneTest4 );
    
    TInt mdcaCount = array->MdcaCount();
    AssertTrueL( ETrue, KValuePhoneTest5 );
    for ( TInt i = 0; i < mdcaCount; i++ )
        {
        TPtrC text = array->MdcaPoint( i );
        }
    AssertTrueL( ETrue, KValuePhoneTest6 );
        
    CAknQueryValuePhone* phone = CAknQueryValuePhone::NewL();
    CleanupStack::PushL( phone );
    AssertNotNullL( phone, KValuePhoneTest7 );
    
    phone->SetQueryCaption( R_BCTESTQUERY_CAPTION );
    AssertTrueL( ETrue, KValuePhoneTest8 );
    
    phone->SetArrayL( array );
    AssertTrueL( ETrue, KValuePhoneTest9 );    
    
    const MDesCArray* mdcArray = phone->MdcArray();
    AssertTrueL( ETrue, KValuePhoneTest10 );
    
    phone->SetCurrentValueIndex( 0 );
    AssertTrueL( ETrue, KValuePhoneTest11 );
    
    TInt index = phone->CurrentValueIndex();
    AssertTrueL( ETrue, KValuePhoneTest12 );
    
    HBufC* phoneValue = phone->Value();
    AssertTrueL( ETrue, KValuePhoneTest13 );
    
    HBufC* text = phone->CurrentValueTextLC();
    AssertTrueL( ETrue, KValuePhoneTest14 );
    
    phone->CreateEditorL();
    AssertTrueL( ETrue, KValuePhoneTest15 );
    
    CleanupStack::PopAndDestroy( text );
    CleanupStack::PopAndDestroy( phone );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( textArray );
    }
    
// ---------------------------------------------------------------------------
// Test CAknQueryValueText
// ---------------------------------------------------------------------------
//
void CBCTestQueryValue::TestQueryValueTextL()
    {
    CDesCArray* textArray = new( ELeave ) CDesCArrayFlat( 2 );
    CleanupStack::PushL( textArray );
    _LIT( KTextValue1, "Text Value 1" );
    _LIT( KTextValue2, "Text Value 2" );
    textArray->AppendL( KTextValue1 );
    textArray->AppendL( KTextValue2 );
    
    CAknQueryValueTextArray* array = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( array );
    AssertNotNullL( array, KValueTextTest1 );
    
    array->SetArray( *textArray );
    AssertTrueL( ETrue, KValueTextTest2 );
    
    const TInt stringSize = array->FormattedStringSize();
    AssertTrueL( ETrue, KValueTextTest4 );
    
    TInt mdcaCount = array->MdcaCount();
    AssertTrueL( ETrue, KValueTextTest5 );
    for ( TInt i = 0; i < mdcaCount; i++ )
        {
        TPtrC text = array->MdcaPoint( i );
        }
    AssertTrueL( ETrue, KValueTextTest6 );
        
    CAknQueryValueText* queryText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryText );
    AssertNotNullL( queryText, KValueTextTest7 );
    
    queryText->SetQueryCaption( R_BCTESTQUERY_CAPTION );
    AssertTrueL( ETrue, KValueTextTest8 );
    
    queryText->SetArrayL( array );
    AssertTrueL( ETrue, KValueTextTest9 );
    
    const MDesCArray* mdcArray = queryText->MdcArray();
    AssertTrueL( ETrue, KValueTextTest10 );
    
    queryText->SetCurrentValueIndex( 0 );
    AssertTrueL( ETrue, KValueTextTest11 );
    
    TInt index = queryText->CurrentValueIndex();
    AssertTrueL( ETrue, KValueTextTest12 );
    
    HBufC* textValue = queryText->Value();
    AssertTrueL( ETrue, KValueTextTest13 );
    
    HBufC* text = queryText->CurrentValueTextLC();
    AssertTrueL( ETrue, KValueTextTest14 );
    
    queryText->CreateEditorL();
    AssertTrueL( ETrue, KValueTextTest15 );
    
    CleanupStack::PopAndDestroy( text );
    CleanupStack::PopAndDestroy( queryText );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( textArray );
    }
    
// ---------------------------------------------------------------------------
// Test CAknQueryValueTime
// ---------------------------------------------------------------------------
//
void CBCTestQueryValue::TestQueryValueTimeL()
    {
    _LIT( KValueTimeTest1, "CAknQueryValueTimeArray::NewL" );
    _LIT( KValueTimeTest2, "CAknQueryValueTimeArray::SetArray" );
    _LIT( KValueTimeTest3, "CAknQueryValueTimeArray::FormatString" );
    _LIT( KValueTimeTest4, "CAknQueryValueTimeArray::FormattedStringSize" );
    _LIT( KValueTimeTest5, "CAknQueryValueTimeArray::MdcaCount" );
    _LIT( KValueTimeTest6, "CAknQueryValueTimeArray::MdcaPoint" );
    _LIT( KValueTimeTest7, "CAknQueryValueTime::NewL" );
    _LIT( KValueTimeTest8, "CAknQueryValueTime::SetQueryCaption" );
    _LIT( KValueTimeTest9, "CAknQueryValueTime::SetArrayL" );
    _LIT( KValueTimeTest10, "CAknQueryValueTime::MdcArray" );
    _LIT( KValueTimeTest11, "CAknQueryValueTime::SetCurrentValueIndex" );
    _LIT( KValueTimeTest12, "CAknQueryValueTime::CurrentValueIndex" );
    _LIT( KValueTimeTest13, "CAknQueryValueTime::Value" );
    _LIT( KValueTimeTest14, "CAknQueryValueTime::CurrentValueTextLC" );
    _LIT( KValueTimeTest15, "CAknQueryValueTime::CreateEditorL" );
        CArrayFix<TTime>* timeArray = new( ELeave ) CArrayFixFlat<TTime>( 4 );
    CleanupStack::PushL( timeArray );
    TTime time1;
    time1.HomeTime();
    TTime time2;
    time2 = time1 + TTimeIntervalDays( 3 );
    timeArray->AppendL( time1 );
    timeArray->AppendL( time2 );
    
    CAknQueryValueTimeArray* array = CAknQueryValueTimeArray::NewL( 
        R_BCTESTQUERY_TIME_FORMAT );
    CleanupStack::PushL( array );
    AssertNotNullL( array, KValueTimeTest1 );
    
    array->SetArray( *timeArray );
    AssertTrueL( ETrue, KValueTimeTest2 );
    
    const HBufC* formatString = array->FormatString();
    AssertTrueL( ETrue, KValueTimeTest3 );
    
    const TInt stringSize = array->FormattedStringSize();
    AssertTrueL( ETrue, KValueTimeTest4 );
    
    TInt mdcaCount = array->MdcaCount();
    AssertTrueL( ETrue, KValueTimeTest5 );
    for ( TInt i = 0; i < mdcaCount; i++ )
        {
        TPtrC text = array->MdcaPoint( i );
        }
    AssertTrueL( ETrue, KValueTimeTest6 );
        
    CAknQueryValueTime* queryTime = CAknQueryValueTime::NewL();
    CleanupStack::PushL( queryTime );
    AssertNotNullL( queryTime, KValueTimeTest7 );
    
    queryTime->SetQueryCaption( R_BCTESTQUERY_CAPTION );
    AssertTrueL( ETrue, KValueTimeTest8 );
    
    queryTime->SetArrayL( array );
    AssertTrueL( ETrue, KValueTimeTest9 );
    
    const MDesCArray* mdcArray = queryTime->MdcArray();
    AssertTrueL( ETrue, KValueTimeTest10 );
    
    queryTime->SetCurrentValueIndex( 0 );
    AssertTrueL( ETrue, KValueTimeTest11 );
    
    TInt index = queryTime->CurrentValueIndex();
    AssertTrueL( ETrue, KValueTimeTest12 );
    
    TTime timeValue = queryTime->Value();
    AssertTrueL( ETrue, KValueTimeTest13 );
    
    HBufC* text = queryTime->CurrentValueTextLC();
    AssertTrueL( ETrue, KValueTimeTest14 );
    
    queryTime->CreateEditorL();
    AssertTrueL( ETrue, KValueTimeTest15 );
    
    CleanupStack::PopAndDestroy( text );
    CleanupStack::PopAndDestroy( queryTime );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( timeArray );
    }

