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
* Description:  Test aknquerycontrol.h
*
*/

//INCLUDE
#include <aknquerycontrol.h>
#include <aknquerydialog.h>
#include <testsdkqueries.rsg>
#include <barsread.h>
#include <eikimage.h>
#include <avkon.mbg>
#include <bautils.h>
#include <in_sock.h>

#include "testsdkqueries.h"
#include "testsdkaknquerydialogprotected.h"
#include "testsdkqueriescontainer.h"
#include "testsdkaknquerycontrolprotected.h"

const TUint32 KMaxAddrValue = 0xffffffff;
const TInt KZero = 0;
const TInt KOne = 1;
const TInt KFive = 5;
const TReal KRealvalue = 2.12345; 
const TReal KCompareValue = 0.0;
const TReal KMinRealTime = 1000.5456;
const TReal KMaxRealTime = 3000.2321;
const TInt KTwo = 2;
const TInt KTen = 10;
const TInt KBufSize = 32;
const TInt KHundred = 100;
const TInt KIntervalue = 3000;

_LIT( KTestString, "It is a test!" );
_LIT( KTestTime, "20000111:200600.000000" );
_LIT( KTestMinTime, "10000000:000000.000000" );
_LIT( KTestMaxTime, "30000000:000000.000000" );
_LIT( KTestMbmFile,"\\resource\\apps\\avkon2.mbm" );

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcConstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryControl* dlg = new( ELeave ) CAknQueryControl;
    CleanupStack::PushL( dlg );
    STIF_ASSERT_NOT_NULL( dlg );
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryControl* dlg = new( ELeave ) CAknQueryControl;
    CleanupStack::PushL( dlg );
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryControl* dlg = new( ELeave ) CAknQueryControl;
    CleanupStack::PushL( dlg );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CONFIRMATION_QUERY );
    dlg->ConstructFromResourceL( reader );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcSetQueryControlObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcSetQueryControlObserverL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryControl* dlgControl = new( ELeave ) CAknQueryControl;
    CleanupStack::PushL( dlgControl );
    
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( CAknQueryDialog::ENoTone );
    dlg->PrepareLC( R_QUERY_DIALOG );
    
    dlgControl->SetQueryControlObserver( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::PopAndDestroy( dlgControl );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcReadPromptL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcReadPromptL( CStifItemParser& aItem )
    {
    TInt err = TestQcConstructFromResourceL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcSetPromptL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcSetPromptL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryControl* dlg = new( ELeave ) CAknQueryControl;
    CleanupStack::PushL( dlg );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CONFIRMATION_QUERY );
    dlg->ConstructFromResourceL( reader );
    
    TBuf< KBufSize > message( KTestString );
    dlg->SetPromptL( message );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcGetTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcGetTextL( CStifItemParser& aItem )
    {
    TInt err = TestQcSetTextL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcGetTimeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcGetTimeL( CStifItemParser& /*aItem*/ )
    {
    TTime time( KTestTime );
    CAknTimeQueryDialog* timeDlg = CAknTimeQueryDialog::NewL( time, CAknQueryDialog::ENoTone); 
    timeDlg->PrepareLC( R_AKNEXQUERY_TIME_QUERY );
    
    CTestCAknTimeQueryDialog* testTimeDlg = static_cast<CTestCAknTimeQueryDialog*>( timeDlg );
    CAknQueryControl* dlgControl = testTimeDlg->QueryControl();
    
    TTime compareTime( KZero );
    TTime returnTime = dlgControl->GetTime();
    STIF_ASSERT_NOT_EQUALS( compareTime, returnTime );
    
    dlgControl->SetTime( time );
    returnTime = dlgControl->GetTime();
    STIF_ASSERT_NOT_EQUALS( compareTime, returnTime );
    
    CleanupStack::PopAndDestroy( timeDlg );

    TBuf< KBufSize > message( KTestString );
    TTime topDateTime;
    topDateTime.Set( message );
    topDateTime.HomeTime();
    TTimeIntervalSeconds bottomDuration = KHundred;
    
    CAknMultiLineDataQueryDialog* dateDlg = CAknMultiLineDataQueryDialog::NewL(topDateTime,bottomDuration);
    dateDlg->PrepareLC( R_AKNEXQUERY_MULTI_LINE_DATE_AND_DURATION_LAYOUT );
    
    CTestCAknMultiLineDataQueryDialog* testDateDlg = static_cast<CTestCAknMultiLineDataQueryDialog*>( dateDlg );
    dlgControl = testDateDlg->QueryControl();
    returnTime = dlgControl->GetTime();
    STIF_ASSERT_NOT_EQUALS( compareTime, returnTime );
    
    dlgControl->SetTime( time );
    returnTime = dlgControl->GetTime();
    STIF_ASSERT_NOT_EQUALS( compareTime, returnTime );
    
    CleanupStack::PopAndDestroy( dateDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcGetNumberL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcGetNumberL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTwo;
    CAknNumberQueryDialog* numberDlg = new (ELeave) CAknNumberQueryDialog ( number );
    numberDlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    CTestCAknNumberQueryDialog* testNumberDlg = static_cast<CTestCAknNumberQueryDialog*>( numberDlg );
    CAknQueryControl* dlgControl = testNumberDlg->QueryControl();
    
    TBuf< KBufSize > message( KTestString );
    TInt returnNumber = dlgControl->GetNumber();
    STIF_ASSERT_NOT_EQUALS( KZero, returnNumber );
    
    dlgControl->SetNumberL( KHundred );
    returnNumber = dlgControl->GetNumber();
    STIF_ASSERT_EQUALS( KHundred, returnNumber );
    
    CleanupStack::PopAndDestroy( numberDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcGetFloatingPointNumberL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcGetFloatingPointNumberL( CStifItemParser& /*aItem*/ )
    {
    TReal value = KRealvalue;
    CAknFloatingPointQueryDialog* floatDlg = new (ELeave) CAknFloatingPointQueryDialog ( value ); 
    floatDlg->PrepareLC( R_DEMO_FLOATING_QUERY );
    
    CTestCAknFloatingPointQueryDialog* testfloatDlg = static_cast<CTestCAknFloatingPointQueryDialog*>( floatDlg );
    CAknQueryControl* dlgControl = testfloatDlg->QueryControl();
    
    TReal returnValue = dlgControl->GetFloatingPointNumberL();
    TReal compareValue = KCompareValue;
    STIF_ASSERT_EQUALS( compareValue, returnValue );
    
    dlgControl->SetFloatingPointNumberL( &value );
    returnValue = dlgControl->GetFloatingPointNumberL();
    STIF_ASSERT_EQUALS( value, returnValue );
    
    CleanupStack::PopAndDestroy( floatDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcGetDurationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcGetDurationL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds duration;
    
    CAknDurationQueryDialog* durationDlg = CAknDurationQueryDialog::NewL( duration, CAknQueryDialog::ENoTone );
    durationDlg->PrepareLC( R_AKNEXQUERY_DURATION_LAYOUT );
    
    CTestCAknDurationQueryDialog* testDurationDlg = static_cast<CTestCAknDurationQueryDialog*>( durationDlg );
    CAknQueryControl* dlgControl = testDurationDlg->QueryControl();
    
    TTimeIntervalSeconds returnDuration = dlgControl->GetDuration();
    TTimeIntervalSeconds compareDuration = KZero;
    STIF_ASSERT_EQUALS( compareDuration, returnDuration );
    
    TTimeIntervalSeconds bottomDuration = KHundred;
    dlgControl->SetDuration( bottomDuration );
    returnDuration = dlgControl->GetDuration();
    STIF_ASSERT_EQUALS( bottomDuration, returnDuration );
    
    CleanupStack::PopAndDestroy( durationDlg );
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcGetLocationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcGetLocationL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryControl* dlg = new( ELeave ) CAknQueryControl;
    CleanupStack::PushL( dlg );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CONFIRMATION_QUERY );
    dlg->ConstructFromResourceL( reader );
    
    TTime time( KTestTime );
    TCoordinate coord( 01.00, 01.0 );
    TLocality loc( coord, 0.1 );
    TPosition position( loc, time );
    TPosition returnPosition;
    
    dlg->SetLocation( position );
    dlg->GetLocation( returnPosition );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcSetTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcSetTextL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTwo;
    CAknNumberQueryDialog* numberDlg = new (ELeave) CAknNumberQueryDialog ( number );
    numberDlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    CTestCAknNumberQueryDialog* testNumberDlg = static_cast<CTestCAknNumberQueryDialog*>( numberDlg );
    CTestCAknQueryControl* dlgControl = 
        static_cast<CTestCAknQueryControl*>( testNumberDlg->QueryControl() );
    
    TBuf< KBufSize > message( KTestString );
    TBuf< KBufSize > getMessage;
    
    dlgControl->iNumberEdwin->SetMaxLength( KHundred );
    
    dlgControl->SetTextL( message );
    dlgControl->GetText( getMessage );
    STIF_ASSERT_EQUALS( message, getMessage );
    
    CleanupStack::PopAndDestroy( numberDlg );
    
    TBuf< KBufSize > text;
    CAknTextQueryDialog* textDlg = new( ELeave ) CAknTextQueryDialog( text, message );
    textDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CTestCAknTextQueryDialog* testTextDlg = static_cast<CTestCAknTextQueryDialog*>( textDlg );
    dlgControl = static_cast<CTestCAknQueryControl*>( testTextDlg->QueryControl() );
    
    dlgControl->iEdwin->SetMaxLength( KHundred );
    
    dlgControl->SetTextL( message );
    dlgControl->GetText( getMessage );
    STIF_ASSERT_EQUALS( message, getMessage );
    
    CleanupStack::PopAndDestroy( textDlg );
    
    TReal value = KRealvalue;
    CAknFloatingPointQueryDialog* floatDlg = new (ELeave) CAknFloatingPointQueryDialog ( value ); 
    floatDlg->PrepareLC( R_DEMO_FLOATING_QUERY );
    
    CTestCAknFloatingPointQueryDialog* testfloatDlg = static_cast<CTestCAknFloatingPointQueryDialog*>( floatDlg );
    dlgControl = static_cast<CTestCAknQueryControl*>( testfloatDlg->QueryControl() );
    
    dlgControl->iFloatingPointEditor->SetMaxLength( KHundred );
    
    dlgControl->SetTextL( message );
    dlgControl->GetText( getMessage );
    STIF_ASSERT_EQUALS( message, getMessage );
    
    CleanupStack::PopAndDestroy( floatDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcSetTimeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcSetTimeL( CStifItemParser& aItem )
    {
    TInt err = TestQcGetTimeL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcSetDurationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcSetDurationL( CStifItemParser& aItem )
    {
    TInt err = TestQcGetDurationL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcSetNumberL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcSetNumberL( CStifItemParser& aItem )
    {
    TInt err = TestQcGetNumberL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcSetFloatingPointNumberL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcSetFloatingPointNumberL( CStifItemParser& aItem )
    {
    TInt err = TestQcGetFloatingPointNumberL( aItem );
    return err;
    }

//some problem
// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcSetLocationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcSetLocationL( CStifItemParser& aItem )
    {
    TInt err = TestQcGetLocationL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcSetTextEntryLengthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcSetTextEntryLengthL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTwo;
    CAknNumberQueryDialog* numberDlg = new (ELeave) CAknNumberQueryDialog ( number );
    numberDlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    CTestCAknNumberQueryDialog* testNumberDlg = static_cast<CTestCAknNumberQueryDialog*>( numberDlg );
    CAknQueryControl* dlgControl = testNumberDlg->QueryControl();
    
    dlgControl->SetTextEntryLength( KHundred );
    TInt length = dlgControl->GetTextEntryLength();
    STIF_ASSERT_EQUALS( KHundred, length );
    
    CleanupStack::PopAndDestroy( numberDlg );
    
    TBuf< KBufSize > text;
    TBuf< KBufSize > message( KTestString );
    CAknTextQueryDialog* textDlg = new( ELeave ) CAknTextQueryDialog( text, message );
    textDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CTestCAknTextQueryDialog* testTextDlg = static_cast<CTestCAknTextQueryDialog*>( textDlg );
    dlgControl = testTextDlg->QueryControl();
    
    length = KZero;
    dlgControl->SetTextEntryLength( KHundred );
    length = dlgControl->GetTextEntryLength();
    STIF_ASSERT_EQUALS( KHundred, length );
    
    CleanupStack::PopAndDestroy( textDlg );
    
    TReal value = KRealvalue;
    CAknFloatingPointQueryDialog* floatDlg = new (ELeave) CAknFloatingPointQueryDialog ( value ); 
    floatDlg->PrepareLC( R_DEMO_FLOATING_QUERY );
    
    CTestCAknFloatingPointQueryDialog* testfloatDlg = static_cast<CTestCAknFloatingPointQueryDialog*>( floatDlg );
    dlgControl = testfloatDlg->QueryControl();
    
    length = KZero;
    dlgControl->SetTextEntryLength( KHundred );
    length = dlgControl->GetTextEntryLength();
    STIF_ASSERT_EQUALS( KHundred, length );
    
    CleanupStack::PopAndDestroy( floatDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcGetTextEntryLengthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcGetTextEntryLengthL( CStifItemParser& aItem )
    {
    TInt err = TestQcSetTextEntryLengthL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcSetMinimumAndMaximumOneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcSetMinimumAndMaximumOneL( CStifItemParser& /*aItem*/ )
    {
    TTime minTime( KTestMinTime );
    TTime maxTime( KTestMaxTime );
    
    CAknTimeQueryDialog* timeDlg = CAknTimeQueryDialog::NewL( minTime, CAknQueryDialog::ENoTone );
    timeDlg->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_TIME );
    
    CTestCAknTimeQueryDialog* testTimeDlg = static_cast<CTestCAknTimeQueryDialog*>( timeDlg );
    CAknQueryControl* dlgControl = testTimeDlg->QueryControl();
    
    dlgControl->SetMinimumAndMaximum( minTime, maxTime );
    
    CleanupStack::PopAndDestroy( timeDlg );
    
    TBuf< KBufSize > message( KTestString );
    TTime topDateTime;
    topDateTime.Set( message );
    topDateTime.HomeTime();
    TTimeIntervalSeconds bottomDuration = KHundred;
    
    CAknMultiLineDataQueryDialog* dateDlg = CAknMultiLineDataQueryDialog::NewL(topDateTime,bottomDuration);
    dateDlg->PrepareLC( R_AKNEXQUERY_MULTI_LINE_DATE_AND_DURATION_LAYOUT );
    
    CTestCAknMultiLineDataQueryDialog* testDateDlg = static_cast<CTestCAknMultiLineDataQueryDialog*>( dateDlg );
    dlgControl = testDateDlg->QueryControl();
    
    dlgControl->SetMinimumAndMaximum( minTime, maxTime );
    
    CleanupStack::PopAndDestroy( dateDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcSetMinimumAndMaximumTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcSetMinimumAndMaximumTwoL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds time( KIntervalue );
    
    CAknDurationQueryDialog* durationDlg = CAknDurationQueryDialog::NewL( time, CAknQueryDialog::ENoTone );
    durationDlg->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_DURATION );
    
    CTestCAknDurationQueryDialog* testDurationDlg = static_cast<CTestCAknDurationQueryDialog*>( durationDlg );
    CAknQueryControl* dlgControl = testDurationDlg->QueryControl();
    
    TTimeIntervalSeconds maxTime = KTwo*KIntervalue;
    dlgControl->SetMinimumAndMaximum( time, maxTime );
    
    CleanupStack::PopAndDestroy( durationDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcSetMinimumAndMaximumThreeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcSetMinimumAndMaximumThreeL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    CAknNumberQueryDialog* numDlg = CAknNumberQueryDialog::NewL( number, CAknQueryDialog::ENoTone );
    numDlg->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_NUMBER );
    
    CTestCAknNumberQueryDialog* testnumDlg = static_cast<CTestCAknNumberQueryDialog*>( numDlg );
    CAknQueryControl* dlgControl = testnumDlg->QueryControl();
    
    dlgControl->SetMinimumAndMaximum( KZero, KIntervalue );
    
    CleanupStack::PopAndDestroy( numDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcCheckNumberL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcCheckNumberL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    CAknNumberQueryDialog* numDlg = CAknNumberQueryDialog::NewL( number, CAknQueryDialog::ENoTone );
    numDlg->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_NUMBER );
    
    CTestCAknNumberQueryDialog* testnumDlg = static_cast<CTestCAknNumberQueryDialog*>( numDlg );
    CAknQueryControl* dlgControl = testnumDlg->QueryControl();
    
    TBool mIfLegal = dlgControl->CheckNumber();
    STIF_ASSERT_TRUE( mIfLegal );
    
    CleanupStack::PopAndDestroy( numDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcSetNumberOfEditorLinesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcSetNumberOfEditorLinesL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryControl* dlg = new( ELeave ) CAknQueryControl;
    CleanupStack::PushL( dlg );
    dlg->SetNumberOfEditorLines( KTen );
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcSetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcSetMinimumAndMaximumL( CStifItemParser& /*aItem*/ )
    {
    TReal minRealTime = KMinRealTime;
    
    CAknFloatingPointQueryDialog* floatDlg = 
        CAknFloatingPointQueryDialog::NewL( minRealTime, CAknQueryDialog::ENoTone );
    floatDlg->PrepareLC( R_DEMO_FLOATING_QUERY );
    
    CTestCAknFloatingPointQueryDialog* testFloatDlg = 
        static_cast<CTestCAknFloatingPointQueryDialog*>( floatDlg );
    CAknQueryControl* dlgControl = testFloatDlg->QueryControl();
    
    dlgControl->SetMinimumAndMaximum( KMinRealTime, KMaxRealTime );
    
    CleanupStack::PopAndDestroy( floatDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcGetTextLengthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcGetTextLengthL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTwo;
    CAknNumberQueryDialog* numberDlg = new (ELeave) CAknNumberQueryDialog ( number );
    numberDlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    CTestCAknNumberQueryDialog* testNumberDlg = static_cast<CTestCAknNumberQueryDialog*>( numberDlg );
    CAknQueryControl* dlgControl = testNumberDlg->QueryControl();
    
    TBuf< KBufSize > compareMessage( KTestString );
    TBuf< KBufSize > message( KTestString );
    
    TInt length = dlgControl->GetTextLength();
    STIF_ASSERT_EQUALS( KZero, length );
    
    CleanupStack::PopAndDestroy( numberDlg );
    
    TBuf< KBufSize > text;
    CAknTextQueryDialog* textDlg = new( ELeave ) CAknTextQueryDialog( text, message );
    textDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CTestCAknTextQueryDialog* testTextDlg = static_cast<CTestCAknTextQueryDialog*>( textDlg );
    dlgControl = testTextDlg->QueryControl();
    
    length = dlgControl->GetTextLength();
    STIF_ASSERT_EQUALS( KZero, length );
    
    CleanupStack::PopAndDestroy( textDlg );
    
    TReal value = KRealvalue;
    CAknFloatingPointQueryDialog* floatDlg = new (ELeave) CAknFloatingPointQueryDialog ( value ); 
    floatDlg->PrepareLC( R_DEMO_FLOATING_QUERY );
    
    CTestCAknFloatingPointQueryDialog* testfloatDlg = static_cast<CTestCAknFloatingPointQueryDialog*>( floatDlg );
    dlgControl = testfloatDlg->QueryControl();
    
    length = dlgControl->GetTextLength();
    STIF_ASSERT_NOT_EQUALS( KZero, length );
    
    CleanupStack::PopAndDestroy( floatDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcNbrOfEditorLinesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcNbrOfEditorLinesL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text;
    TBuf< KBufSize > message( KTestString );
    CAknTextQueryDialog* textDlg = new( ELeave ) CAknTextQueryDialog( text, message );
    textDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CTestCAknTextQueryDialog* testTextDlg = static_cast<CTestCAknTextQueryDialog*>( textDlg );
    CAknQueryControl* dlgControl = testTextDlg->QueryControl();
    
    TInt numberOfLine = dlgControl->NbrOfEditorLines();
    STIF_ASSERT_EQUALS( KOne, numberOfLine );
    
    CleanupStack::PopAndDestroy( textDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcNbrOfPromptLinesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcNbrOfPromptLinesL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text;
    TBuf< KBufSize > message( KTestString );
    CAknTextQueryDialog* textDlg = new( ELeave ) CAknTextQueryDialog( text, message );
    textDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CTestCAknTextQueryDialog* testTextDlg = static_cast<CTestCAknTextQueryDialog*>( textDlg );
    CAknQueryControl* dlgControl = testTextDlg->QueryControl();
    
    TInt numberOfLine = dlgControl->NbrOfPromptLines();
    STIF_ASSERT_EQUALS( KOne, numberOfLine );
    
    CleanupStack::PopAndDestroy( textDlg );
    
    CAknQueryControl* dlg = new( ELeave ) CAknQueryControl;
    CleanupStack::PushL( dlg );

    numberOfLine = dlg->NbrOfPromptLines();
    STIF_ASSERT_EQUALS( KOne, numberOfLine );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcControlByLayoutOrNullL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcControlByLayoutOrNullL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text;
    TBuf< KBufSize > message( KTestString );
    CAknTextQueryDialog* textDlg = new( ELeave ) CAknTextQueryDialog( text, message );
    textDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CTestCAknTextQueryDialog* testTextDlg = static_cast<CTestCAknTextQueryDialog*>( textDlg );
    CAknQueryControl* dlgControl = testTextDlg->QueryControl();
    
    CCoeControl* control = dlgControl->ControlByLayoutOrNull( EStaticSizeDataLayout );
    STIF_ASSERT_NOT_NULL( control );
    
    control = dlgControl->ControlByLayoutOrNull( ECodeLayout );
    STIF_ASSERT_NULL( control );
    
    control = dlgControl->ControlByLayoutOrNull( EDateLayout );
    STIF_ASSERT_NULL( control );
    
    control = dlgControl->ControlByLayoutOrNull( ETimeLayout );
    STIF_ASSERT_NULL( control );
    
    control = dlgControl->ControlByLayoutOrNull( EDurationLayout );
    STIF_ASSERT_NULL( control );
    
    control = dlgControl->ControlByLayoutOrNull( ENumberLayout );
    STIF_ASSERT_NULL( control );
    
    control = dlgControl->ControlByLayoutOrNull( EPinLayout );
    STIF_ASSERT_NULL( control );
    
    control = dlgControl->ControlByLayoutOrNull( EFloatingPointLayout );
    STIF_ASSERT_NULL( control );
    
    control = dlgControl->ControlByLayoutOrNull( ELocationLayout );
    STIF_ASSERT_NULL( control );
    
    CleanupStack::PopAndDestroy( textDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcSetImageL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcSetImageL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text;
    TBuf< KBufSize > message( KTestString );
    
    CAknTextQueryDialog* textDlg = new( ELeave ) CAknTextQueryDialog( text, message );
    textDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CTestCAknTextQueryDialog* testTextDlg = static_cast<CTestCAknTextQueryDialog*>( textDlg );
    CAknQueryControl* dlgControl = testTextDlg->QueryControl();
    
    CEikImage* mImage = new( ELeave ) CEikImage;
    CleanupStack::PushL( mImage );
    
    dlgControl->SetImageL( mImage );
    
    CleanupStack::Pop( mImage );
    CleanupStack::PopAndDestroy( textDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcSetImageFullL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcSetImageFullL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text;
    TBuf< KBufSize > message( KTestString );
    
    CAknTextQueryDialog* textDlg = new( ELeave ) CAknTextQueryDialog( text, message );
    textDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CTestCAknTextQueryDialog* testTextDlg = static_cast<CTestCAknTextQueryDialog*>( textDlg );
    CAknQueryControl* dlgControl = testTextDlg->QueryControl();
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    dlgControl->SetImageL( file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    
    CleanupStack::PopAndDestroy( textDlg );
    return KErrNone;
    }

//There is a problem here 
// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcSetAnimationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcSetAnimationL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text;
    TBuf< KBufSize > message( KTestString );
    
    CAknTextQueryDialog* textDlg = new( ELeave ) CAknTextQueryDialog( text, message );
    textDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CTestCAknTextQueryDialog* testTextDlg = static_cast<CTestCAknTextQueryDialog*>( textDlg );
    CAknQueryControl* dlgControl = testTextDlg->QueryControl();
    
    dlgControl->SetAnimationL( R_TESTQUERY_BMP_ANIMATION );
    
    CleanupStack::PopAndDestroy( textDlg );
    return KErrNone;
    }

//There is a problem here
// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcStartAnimationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcStartAnimationL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text;
    TBuf< KBufSize > message( KTestString );
    
    CAknTextQueryDialog* textDlg = new( ELeave ) CAknTextQueryDialog( text, message );
    textDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CTestCAknTextQueryDialog* testTextDlg = static_cast<CTestCAknTextQueryDialog*>( textDlg );
    CAknQueryControl* dlgControl = testTextDlg->QueryControl();
    
    dlgControl->SetAnimationL( R_TESTQUERY_BMP_ANIMATION );
    dlgControl->StartAnimationL();
    
    CleanupStack::PopAndDestroy( textDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcCancelAnimationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcCancelAnimationL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text;
    TBuf< KBufSize > message( KTestString );
    
    CAknTextQueryDialog* textDlg = new( ELeave ) CAknTextQueryDialog( text, message );
    textDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CTestCAknTextQueryDialog* testTextDlg = static_cast<CTestCAknTextQueryDialog*>( textDlg );
    CAknQueryControl* dlgControl = testTextDlg->QueryControl();
    
    TInt captureErr = dlgControl->CancelAnimation();
    STIF_ASSERT_EQUALS( KErrGeneral, captureErr );
    
    dlgControl->SetAnimationL( R_TESTQUERY_BMP_ANIMATION );
    captureErr = dlgControl->CancelAnimation();
    STIF_ASSERT_NOT_EQUALS( KErrGeneral, captureErr );
    
    CleanupStack::PopAndDestroy( textDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text;
    TBuf< KBufSize > message( KTestString );
    
    CAknTextQueryDialog* textDlg = new( ELeave ) CAknTextQueryDialog( text, message );
    textDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CTestCAknTextQueryDialog* testTextDlg = static_cast<CTestCAknTextQueryDialog*>( textDlg );
    CAknQueryControl* dlgControl = testTextDlg->QueryControl();
    
    TKeyEvent event;
    event.iCode = EKeyYes;
    TKeyResponse response = dlgControl->OfferKeyEventL( event, EEventKey );
    STIF_ASSERT_EQUALS( EKeyWasConsumed, response );
    
    CleanupStack::PopAndDestroy( textDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text;
    TBuf< KBufSize > message( KTestString );
    
    CAknTextQueryDialog* textDlg = new( ELeave ) CAknTextQueryDialog( text, message );
    textDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CTestCAknTextQueryDialog* testTextDlg = static_cast<CTestCAknTextQueryDialog*>( textDlg );
    CAknQueryControl* dlgControl = testTextDlg->QueryControl();
    
    TSize size = dlgControl->MinimumSize();
    TSize returnSize( KZero, KZero );
    STIF_ASSERT_NOT_EQUALS( returnSize, size );
    
    CleanupStack::PopAndDestroy( textDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcHandleEdwinEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcHandleEdwinEventL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text;
    TBuf< KBufSize > message( KTestString );
    
    CAknTextQueryDialog* textDlg = new( ELeave ) CAknTextQueryDialog( text, message );
    textDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CTestCAknTextQueryDialog* testTextDlg = static_cast<CTestCAknTextQueryDialog*>( textDlg );
    CAknQueryControl* dlgControl = testTextDlg->QueryControl();
    
    CEikEdwin* edwin = new( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    
    dlgControl->HandleEdwinEventL( edwin, MEikEdwinObserver::EEventFormatChanged );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcHandleEdwinSizeEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcHandleEdwinSizeEventL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text;
    TBuf< KBufSize > message( KTestString );
    
    CAknTextQueryDialog* textDlg = new( ELeave ) CAknTextQueryDialog( text, message );
    textDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CTestCAknTextQueryDialog* testTextDlg = static_cast<CTestCAknTextQueryDialog*>( textDlg );
    CAknQueryControl* dlgControl = testTextDlg->QueryControl();
    
    CEikEdwin* edwin = new( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    TSize size( KZero, KZero );
    
    TBool flag = dlgControl->HandleEdwinSizeEventL( edwin, 
        MEikEdwinSizeObserver::EEventSizeChanging, size );
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcHandleControlEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcHandleControlEventL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text;
    TBuf< KBufSize > message( KTestString );
    
    CAknTextQueryDialog* textDlg = new( ELeave ) CAknTextQueryDialog( text, message );
    textDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CTestCAknTextQueryDialog* testTextDlg = static_cast<CTestCAknTextQueryDialog*>( textDlg );
    CAknQueryControl* dlgControl = testTextDlg->QueryControl();
    
    CCoeControl* control = NULL;
    dlgControl->HandleControlEventL( control, MCoeControlObserver::EEventStateChanged );
    
    CleanupStack::PopAndDestroy( textDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcQueryTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcQueryTypeL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryControl* dlg = new( ELeave ) CAknQueryControl;
    CleanupStack::PushL( dlg );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CONFIRMATION_QUERY );
    dlg->ConstructFromResourceL( reader );
    
    TInt queryType = dlg->QueryType();
    TInt compareType = EConfirmationQueryLayout;
    STIF_ASSERT_EQUALS( compareType, queryType );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text;
    TBuf< KBufSize > message( KTestString );
    
    CAknTextQueryDialog* textDlg = new( ELeave ) CAknTextQueryDialog( text, message );
    textDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CTestCAknTextQueryDialog* testTextDlg = static_cast<CTestCAknTextQueryDialog*>( textDlg );
    CAknQueryControl* dlgControl = testTextDlg->QueryControl();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = KZero;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TInt err = KErrNone;
    TRAP( err, dlgControl->HandlePointerEventL( event ) );
    
    CleanupStack::PopAndDestroy( textDlg );
    return KErrNone;
    }

//There is a problem with animation id
// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQcHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQcHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text;
    TBuf< KBufSize > message( KTestString );
    
    CAknTextQueryDialog* textDlg = new( ELeave ) CAknTextQueryDialog( text, message );
    textDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CTestCAknTextQueryDialog* testTextDlg = static_cast<CTestCAknTextQueryDialog*>( textDlg );
    CAknQueryControl* dlgControl = testTextDlg->QueryControl();
    
    dlgControl->SetAnimationL( R_TESTQUERY_BMP_ANIMATION );
    
    dlgControl->HandleResourceChange( KAknsMessageSkinChange );
    dlgControl->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    
    CleanupStack::PopAndDestroy( textDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtQcConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtQcConstructorL( CStifItemParser& /*aItem*/ )
    { 
    CAknExtQueryControl* extControl = new( ELeave ) CAknExtQueryControl();
    CleanupStack::PushL( extControl );
    STIF_ASSERT_NOT_NULL( extControl );
    CleanupStack::PopAndDestroy( extControl );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtQcDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtQcDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknExtQueryControl* extControl = new( ELeave ) CAknExtQueryControl();
    CleanupStack::PushL( extControl );
    CleanupStack::PopAndDestroy( extControl );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtQcGetInetAddressL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtQcGetInetAddressL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddr;
    TInetAddr minAddr( KZero, KZero );

    CAknIpAddressQueryDialog* dlg = CAknIpAddressQueryDialog::NewL( mAddr, CAknIpAddressQueryDialog::ENoTone );
    dlg->PrepareLC( R_TESTQUERY_IP_ADDRESS );
    
    CTestCAknIpAddressQueryDialog* testDlg = static_cast<CTestCAknIpAddressQueryDialog*>( dlg );
    CAknExtQueryControl* dlgControl = static_cast<CAknExtQueryControl*>( testDlg->QueryControl() );
    
    dlgControl->SetInetAddress( minAddr );
    TInetAddr returnAddr = dlgControl->GetInetAddress();
    STIF_ASSERT_EQUALS( minAddr, returnAddr );
    
    CleanupStack::PopAndDestroy( dlg );
    
    CAknExtQueryControl* extCtrl = new( ELeave ) CAknExtQueryControl();
    CleanupStack::PushL( extCtrl );

    extCtrl->SetInetAddress( minAddr );
    returnAddr = extCtrl->GetInetAddress();
    STIF_ASSERT_NOT_EQUALS( minAddr, returnAddr );
    
    CleanupStack::PopAndDestroy( extCtrl );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtQcSetInetAddressL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtQcSetInetAddressL( CStifItemParser& aItem )
    {
    TInt err = TestExtQcGetInetAddressL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtQcGetFixedPointNumberL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtQcGetFixedPointNumberL( CStifItemParser& /*aItem*/ )
    {
    TInt mInitial = KFive;
    CAknFixedPointQueryDialog* dlg = CAknFixedPointQueryDialog::NewL( mInitial, CAknFixedPointQueryDialog::ENoTone );
    dlg->PrepareLC( R_TESTQUERY_FIXED_POINT );
    
    CTestCAknFixedPointQueryDialog* testDlg = static_cast<CTestCAknFixedPointQueryDialog*>( dlg );
    CAknExtQueryControl* dlgControl = static_cast<CAknExtQueryControl*>( testDlg->QueryControl() );
    
    dlgControl->SetFixedPointNumberL( &mInitial );
    TInt number = dlgControl->GetFixedPointNumber();
    STIF_ASSERT_EQUALS( KFive, number );
    
    CleanupStack::PopAndDestroy( dlg );
    
    CAknExtQueryControl* extCtrl = new( ELeave ) CAknExtQueryControl();
    CleanupStack::PushL( extCtrl );

    extCtrl->SetFixedPointNumberL( &mInitial );
    number = extCtrl->GetFixedPointNumber();
    STIF_ASSERT_NOT_EQUALS( KFive, number );
    
    CleanupStack::PopAndDestroy( extCtrl );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtQcSetFixedPointNumberL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtQcSetFixedPointNumberL( CStifItemParser& aItem )
    {
    TInt err = TestExtQcGetFixedPointNumberL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtQcSetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtQcSetMinimumAndMaximumL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddr;
    TInetAddr minAddr( KZero, KZero );
    TInetAddr maxAddr( KMaxAddrValue );

    CAknIpAddressQueryDialog* dlg = CAknIpAddressQueryDialog::NewL( mAddr, CAknIpAddressQueryDialog::ENoTone );
    dlg->PrepareLC( R_TESTQUERY_IP_ADDRESS );
    
    CTestCAknIpAddressQueryDialog* testDlg = static_cast<CTestCAknIpAddressQueryDialog*>( dlg );
    CAknExtQueryControl* dlgControl = static_cast<CAknExtQueryControl*>( testDlg->QueryControl() );
    
    dlgControl->SetMinimumAndMaximum( minAddr, maxAddr );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtQcSetMinimumAndMaximumLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtQcSetMinimumAndMaximumLL( CStifItemParser& /*aItem*/ )
    {
    TInt mInitial = KFive;
    CAknFixedPointQueryDialog* dlg = CAknFixedPointQueryDialog::NewL( mInitial, CAknFixedPointQueryDialog::ENoTone );
    dlg->PrepareLC( R_TESTQUERY_FIXED_POINT );
    
    CTestCAknFixedPointQueryDialog* testDlg = static_cast<CTestCAknFixedPointQueryDialog*>( dlg );
    CAknExtQueryControl* dlgControl = static_cast<CAknExtQueryControl*>( testDlg->QueryControl() );
    
    dlgControl->SetMinimumAndMaximum( KZero, KIntervalue );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtQcControlByLayoutOrNullL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtQcControlByLayoutOrNullL( CStifItemParser& /*aItem*/ )
    {
    TInt mInitial = KFive;
    CAknFixedPointQueryDialog* dlg = CAknFixedPointQueryDialog::NewL( mInitial, CAknFixedPointQueryDialog::ENoTone );
    dlg->PrepareLC( R_TESTQUERY_FIXED_POINT );
    
    CTestCAknFixedPointQueryDialog* testDlg = static_cast<CTestCAknFixedPointQueryDialog*>( dlg );
    CAknExtQueryControl* dlgControl = static_cast<CAknExtQueryControl*>( testDlg->QueryControl() );
    
    CCoeControl* control = dlgControl->ControlByLayoutOrNull( EIpLayout );
    STIF_ASSERT_NULL( control );
    
    control = dlgControl->ControlByLayoutOrNull( EFixedPointLayout );
    STIF_ASSERT_NOT_NULL( control );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtQcHandleControlEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtQcHandleControlEventL( CStifItemParser& /*aItem*/ )
    {
    TInt mInitial = KFive;
    CAknFixedPointQueryDialog* dlg = CAknFixedPointQueryDialog::NewL( mInitial, CAknFixedPointQueryDialog::ENoTone );
    dlg->PrepareLC( R_TESTQUERY_FIXED_POINT );
    
    CTestCAknFixedPointQueryDialog* testDlg = static_cast<CTestCAknFixedPointQueryDialog*>( dlg );
    CAknExtQueryControl* dlgControl = static_cast<CAknExtQueryControl*>( testDlg->QueryControl() );
    
    CCoeControl* control = NULL;
    dlgControl->HandleControlEventL( control, MCoeControlObserver::EEventStateChanged );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtQcHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtQcHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    TInt mInitial = KFive;
    CAknFixedPointQueryDialog* dlg = CAknFixedPointQueryDialog::NewL( mInitial, CAknFixedPointQueryDialog::ENoTone );
    dlg->PrepareLC( R_TESTQUERY_FIXED_POINT );
    
    CTestCAknFixedPointQueryDialog* testDlg = static_cast<CTestCAknFixedPointQueryDialog*>( dlg );
    CAknExtQueryControl* dlgControl = static_cast<CAknExtQueryControl*>( testDlg->QueryControl() );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = KZero;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TInt err = KErrNone;
    TRAP( err, dlgControl->HandlePointerEventL( event ) );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

//End file



