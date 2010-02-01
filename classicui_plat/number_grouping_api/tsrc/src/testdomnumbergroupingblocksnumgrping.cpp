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
* Description:  Test number_grouping_api
*
*/


/*
 * Include files
 */
#include <numbergrouping.h>

#include "testdomnumbergrouping.h"

/*
 * Descriptor declare
 */
_LIT( KNormalNumber, "13548130726" );
_LIT( KMoreLengthNumber, "1354813072688" );
_LIT( KLessLengthNumber, "135481307" );
_LIT( KNormalNumberSpace, "         " );
_LIT( KNormalNumberChar, "abcdefghijk" );
_LIT( KNoStandardNumber, "12  43 32" );

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGNewLL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGNewLL( CStifItemParser& /*aItem*/ )
    {
    TBool reserved( ETrue );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewL( maxlength,
        reserved );
    CleanupStack::PushL( numbergrouping );
    STIF_ASSERT_NOT_NULL( numbergrouping );
    CleanupStack::PopAndDestroy( numbergrouping );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGNewLCL
// -----------------------------------------------------------------------------
//   
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGNewLCL( CStifItemParser& /*aItem*/ )
    {
    TBool reserved( ETrue );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewLC( maxlength,
        reserved );
    STIF_ASSERT_NOT_NULL( numbergrouping );
    CleanupStack::PopAndDestroy( numbergrouping );
    
    return KErrNone;
    }
  
// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGDestructorL( CStifItemParser& /*aItem*/ )
    {
    TBool reserved( ETrue );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewL( maxlength,
        reserved );
    CleanupStack::PushL( numbergrouping );
    STIF_ASSERT_NOT_NULL( numbergrouping );
    CleanupStack::PopAndDestroy( numbergrouping );
    
    return KErrNone;
    }
  
// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGInsertL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGInsertL( CStifItemParser& /*aItem*/ )
    {
    TBool reserved( ETrue );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewLC( maxlength,
        reserved );
    
    TDesC testlesslengthnumber( KLessLengthNumber );
    numbergrouping->Set( KLessLengthNumber );
    
    TInt einsertposition( 13 );
    TInt err( KErrNone );
    TText value( 1 );
    
    err = numbergrouping->Insert( einsertposition, value );
    STIF_ASSERT_EQUALS( KErrIndexOutOfRange, err );
    
    einsertposition = 9;
    err = numbergrouping->Insert( 9 , value );
    STIF_ASSERT_EQUALS( KErrNone, err );
    
    einsertposition = -8;
    err = numbergrouping->Insert( -8, value );
    STIF_ASSERT_EQUALS( KErrIndexOutOfRange, err );
    CleanupStack::PopAndDestroy( numbergrouping );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGDeleteL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGDeleteL( CStifItemParser& /*aItem*/ )
    {
    TBool reserved( ETrue );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewLC( maxlength,
        reserved );
    
    TDesC testnormalnumber( KNormalNumber );
    numbergrouping->Set( testnormalnumber );
    TInt einsertposition( 13 );
    TInt err( KErrNone );
    
    err = numbergrouping->Delete( einsertposition );
    STIF_ASSERT_EQUALS( KErrIndexOutOfRange, err );
    
    einsertposition = 7;
    err = numbergrouping->Delete( einsertposition );
    STIF_ASSERT_EQUALS( KErrNone, err );
    CleanupStack::PopAndDestroy( numbergrouping );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGAppendL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGAppendL( CStifItemParser& /*aItem*/ )
    {
    TBool reserved( ETrue );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewLC( maxlength, 
        reserved );
    
    TDesC testnormalnumber( KNormalNumber );
    numbergrouping->Set( testnormalnumber );
    
    TText value( 1 );
    TInt err( KErrNone );
    
    err = numbergrouping->Append( value );
    STIF_ASSERT_EQUALS( KErrOverflow, err );
    CleanupStack::PopAndDestroy( numbergrouping );
    
    CPNGNumberGrouping* numbergroup = CPNGNumberGrouping::NewLC( maxlength, 
        reserved );
    
    TDesC testlesslengthnumber( KLessLengthNumber );
    numbergroup->Set( testlesslengthnumber );
    
    err = numbergrouping->Append( value );
    STIF_ASSERT_EQUALS( KErrNone, err );
    CleanupStack::PopAndDestroy( numbergroup );
    
    return err;
    }
  
// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGSetL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGSetL( CStifItemParser& /*aItem*/ )
    {
    TBool reserved( ETrue );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewLC( maxlength,
        reserved );
    
    TDesC testmorelengthnumber( KMoreLengthNumber );
    TDesC testnormalnumber( KNormalNumber );
    TDesC testlesslengthnumber( KLessLengthNumber );
    TInt err( KErrNone );
    
    err = numbergrouping->Set( testmorelengthnumber );
    STIF_ASSERT_EQUALS( KErrOverflow, err );
    
    err = numbergrouping->Set( testnormalnumber );
    STIF_ASSERT_EQUALS( KErrNone, err );
    
    err = numbergrouping->Set( testlesslengthnumber );
    STIF_ASSERT_EQUALS( KErrNone, err );
    CleanupStack::PopAndDestroy( numbergrouping );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGLengthL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGLengthL( CStifItemParser& /*aItem*/ )
    {
    TBool reserved( ETrue );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewLC( maxlength,
        reserved );
    
    TDesC testnormalnumber( KNormalNumber );
    numbergrouping->Set( testnormalnumber );
    
    TInt beginposition( 2 );
    TInt endposition( 10 );
    TInt length( 0 );
    
    numbergrouping->FormattedNumber( beginposition, endposition );
    length = numbergrouping->Length();
    STIF_ASSERT_NOT_EQUALS( 0, length );
    CleanupStack::PopAndDestroy( numbergrouping );
    
    CPNGNumberGrouping* numbergroup = CPNGNumberGrouping::NewLC( 0, reserved );
    numbergroup->Set( testnormalnumber );
    
    length = 0;
    length = numbergroup->Length();
    STIF_ASSERT_EQUALS( 0, length );
    CleanupStack::PopAndDestroy( numbergroup );
    
    return KErrNone;
    }
  
// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGUnFormattedLengthL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGUnFormattedLengthL( CStifItemParser& 
         /*aItem*/ )
    {
    TBool reserved( ETrue );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewLC( maxlength,
        reserved );
    
    TDesC testnormalnumber( KNormalNumber );
    numbergrouping->Set( testnormalnumber );
    
    TInt length( 0 );
    length = numbergrouping->UnFormattedLength();
    STIF_ASSERT_NOT_EQUALS( 0, length );
    CleanupStack::PopAndDestroy( numbergrouping );
    
    CPNGNumberGrouping* numbergroup = CPNGNumberGrouping::NewLC( maxlength,
        reserved );
    length = 0;
    length = numbergroup->UnFormattedLength();
    STIF_ASSERT_EQUALS( 0, length );
    CleanupStack::PopAndDestroy( numbergroup );
    
    return KErrNone;
    }
  
// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGMaxDisplayLengthL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGMaxDisplayLengthL( CStifItemParser& 
         /*aItem*/ )
    {
    TBool reserved( ETrue );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewLC( maxlength, 
        reserved );
    TInt length( 0 );
    length = numbergrouping->MaxDisplayLength();
    STIF_ASSERT_EQUALS( maxlength, length );
    
    TDesC testnormalnumber( KNormalNumber );
    numbergrouping->Set( testnormalnumber );
    length = 0;
    length = numbergrouping->MaxDisplayLength();
    STIF_ASSERT_EQUALS( maxlength, length );
    CleanupStack::PopAndDestroy( numbergrouping );
    
    return KErrNone;
    }
  
// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGIsSpaceL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGIsSpaceL( CStifItemParser& /*aItem*/ )
    {
    TBool reserved( ETrue );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewLC( maxlength,
        reserved );
    
    TInt checkposition( 3 );
    TBool flag = numbergrouping->IsSpace( checkposition );
    STIF_ASSERT_FALSE( flag );
    
    TDesC testnormalnumberspace( KNormalNumberSpace );
    numbergrouping->Set( testnormalnumberspace );
    
    flag = ETrue;
    flag = numbergrouping->IsSpace( checkposition );
    STIF_ASSERT_FALSE( flag );
    
    flag = ETrue;
    numbergrouping->FormattedNumber( 0, 11 );
    flag = numbergrouping->IsSpace( checkposition );
    STIF_ASSERT_FALSE( flag );
    CleanupStack::PopAndDestroy( numbergrouping );

    return KErrNone;
    }
  
// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGFormattedNumberL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGFormattedNumberL( CStifItemParser& 
         /*aItem*/ )
    {
    TBool reserved( ETrue );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewLC( 0, reserved );
    
    TDesC nulldesc( KNullDesC );
    TDesC returndesc( KNullDesC );
    TInt beginposition( 0 );
    TInt endposition( 4 );
    
    returndesc = numbergrouping->FormattedNumber( beginposition, endposition );
    STIF_ASSERT_EQUALS( nulldesc, returndesc );
    CleanupStack::PopAndDestroy( numbergrouping );
    
    CPNGNumberGrouping* numbergroup = CPNGNumberGrouping::NewLC( maxlength, 
        reserved );
    TDesC testnormalnumber( KNormalNumber );
    numbergroup->Set( testnormalnumber );
    returndesc = numbergroup->FormattedNumber( beginposition, endposition );
    STIF_ASSERT_NOT_EQUALS( nulldesc, returndesc );
    CleanupStack::PopAndDestroy( numbergroup );
    
    return KErrNone;
    }
  
// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGFormattedNumberNullL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGFormattedNumberNullL( CStifItemParser&
         /*aItem*/ )
    {
    TBool reserved( ETrue );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewLC( maxlength, 
        reserved );
    TDesC testnormalnumber( KNormalNumber );
    numbergrouping->Set( testnormalnumber );
    TDesC nulldesc( KNullDesC );
    TDesC returndesc( KNullDesC );
    returndesc = numbergrouping->FormattedNumber();
    STIF_ASSERT_NOT_EQUALS( nulldesc, returndesc );    
    CleanupStack::PopAndDestroy( numbergrouping );
    
    return KErrNone;
    }
  
// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGReverseFormattedNumberL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGReverseFormattedNumberL( 
         CStifItemParser& /*aItem*/ )
    {
    TBool reserved( EFalse );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewLC( maxlength,
        reserved );
    
    TDesC nulldesc( KNullDesC );
    TDesC returndesc( KNullDesC );
    TInt beginposition( 3 );
    TInt endposition( 8 );
    
    returndesc = numbergrouping->ReverseFormattedNumber( beginposition,
        endposition );
    STIF_ASSERT_EQUALS( nulldesc, returndesc );
    
    TDesC testnormalnumber( KNormalNumber );
    numbergrouping->Set( testnormalnumber );
    returndesc = numbergrouping->ReverseFormattedNumber( beginposition, 
        endposition );
    STIF_ASSERT_EQUALS( nulldesc, returndesc );
    
    beginposition = -3;
    returndesc = numbergrouping->ReverseFormattedNumber( beginposition, 
        endposition );
    STIF_ASSERT_EQUALS( nulldesc, returndesc );
    
    beginposition = 3;
    endposition = 15;
    returndesc = numbergrouping->ReverseFormattedNumber( beginposition, 
        endposition );
    STIF_ASSERT_EQUALS( nulldesc, returndesc );
    
    endposition = -8;
    returndesc = numbergrouping->ReverseFormattedNumber( beginposition,
        endposition );
    STIF_ASSERT_EQUALS( nulldesc, returndesc );
    CleanupStack::PopAndDestroy( numbergrouping );
    
    reserved = ETrue;
    CPNGNumberGrouping* numbergroup = CPNGNumberGrouping::NewLC( maxlength, 
        reserved );
    
    beginposition = 3;
    endposition = 8;
    returndesc = numbergroup->ReverseFormattedNumber( beginposition, 
        endposition );
    STIF_ASSERT_EQUALS( nulldesc, returndesc );
    
    numbergroup->Set( testnormalnumber );
    returndesc = numbergroup->ReverseFormattedNumber( beginposition, 
        endposition );
    STIF_ASSERT_NOT_EQUALS( nulldesc, returndesc );
    
    beginposition = -3;
    returndesc = numbergroup->ReverseFormattedNumber( beginposition, 
        endposition );
    STIF_ASSERT_EQUALS( nulldesc, returndesc );
    
    beginposition = 3;
    endposition = 15;
    returndesc = numbergroup->ReverseFormattedNumber( beginposition, 
        endposition );
    STIF_ASSERT_EQUALS( nulldesc, returndesc );
    
    endposition = -8;
    returndesc = numbergroup->ReverseFormattedNumber( beginposition, 
        endposition );
    STIF_ASSERT_EQUALS( nulldesc, returndesc );
    CleanupStack::PopAndDestroy( numbergroup );
    
    return KErrNone;
    }
  
// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGReverseFormattedNumberNullL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGReverseFormattedNumberNullL( 
         CStifItemParser& /*aItem*/ )
    {
    TBool reserved( EFalse );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewLC( maxlength, 
        reserved );
    
    TDesC nulldesc( KNullDesC );
    TDesC returndesc( KNullDesC );
    returndesc = numbergrouping->ReverseFormattedNumber();
    STIF_ASSERT_EQUALS( nulldesc, returndesc );
    
    TDesC testnormalnumber( KNormalNumber );
    numbergrouping->Set( testnormalnumber );
    returndesc = numbergrouping->ReverseFormattedNumber();
    STIF_ASSERT_EQUALS( nulldesc, returndesc );
    CleanupStack::PopAndDestroy( numbergrouping );
        
    reserved = ETrue;
    CPNGNumberGrouping* numbergroup = CPNGNumberGrouping::NewLC( maxlength,
        reserved );
    returndesc = numbergroup->ReverseFormattedNumber();
    STIF_ASSERT_EQUALS( nulldesc, returndesc );    
    
    numbergroup->Set( testnormalnumber );
    returndesc = numbergroup->ReverseFormattedNumber(); 
    CleanupStack::PopAndDestroy( numbergroup );
    
    return KErrNone;
    }
  
// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGSelectionL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGSelectionL( CStifItemParser& /*aItem*/ )
    {
    TBool reserved( ETrue );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewLC( maxlength,
        reserved );
    
    TDesC nulldesc( KNullDesC );
    TDesC returndesc( KNullDesC );
    TInt beginposition( 0 );
    TInt endposition( 7 );
    returndesc = numbergrouping->Selection( beginposition, endposition );
    STIF_ASSERT_EQUALS( nulldesc, returndesc );  
    
    returndesc = numbergrouping->Selection( endposition, beginposition );
    STIF_ASSERT_EQUALS( nulldesc, returndesc ); 
    
    beginposition = 20;
    returndesc = numbergrouping->Selection( beginposition, endposition );
    STIF_ASSERT_EQUALS( nulldesc, returndesc );  
    
    TDesC testnormalnumber( KNormalNumber );
    numbergrouping->Set( testnormalnumber );
    beginposition = 0;
    returndesc = numbergrouping->Selection( beginposition, endposition );
    STIF_ASSERT_NOT_EQUALS( nulldesc, returndesc );   
    CleanupStack::PopAndDestroy( numbergrouping );
    
    return KErrNone;
    }
  
// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGUnFormattedNumberL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGUnFormattedNumberL( CStifItemParser& 
         /*aItem*/ )
    {
    TBool reserved( ETrue );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewLC( maxlength, 
        reserved );
    
    TDesC nulldesc( KNullDesC );
    TDesC returndesc( KNullDesC );
    TInt beginposition( 0 );
    TInt endposition( 7 );
    TDesC testnormalnumber( KNormalNumber );
    numbergrouping->Set( testnormalnumber );
    returndesc = numbergrouping->UnFormattedNumber( beginposition, endposition );
    STIF_ASSERT_NOT_EQUALS( nulldesc, returndesc );
    
    beginposition = -10;
    returndesc = KNullDesC;
    returndesc = numbergrouping->UnFormattedNumber( beginposition, endposition );
    STIF_ASSERT_EQUALS( nulldesc, returndesc );
    
    beginposition = 10;
    returndesc = numbergrouping->UnFormattedNumber( beginposition, endposition );
    STIF_ASSERT_EQUALS( nulldesc, returndesc );
    
    beginposition = 0;
    endposition = 20;
    returndesc = numbergrouping->UnFormattedNumber( beginposition, endposition );
    STIF_ASSERT_EQUALS( nulldesc, returndesc );
    CleanupStack::PopAndDestroy( numbergrouping );
    
    return KErrNone;
    }
  
// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGUnFormattedNumberNullL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGUnFormattedNumberNullL( 
         CStifItemParser& /*aItem*/ )
    {
    TBool reserved( ETrue );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewLC( maxlength,
        reserved );
    
    TDesC nulldesc( KNullDesC );
    TDesC returndesc( KNullDesC );
    returndesc = numbergrouping->UnFormattedNumber();
    STIF_ASSERT_EQUALS( nulldesc, returndesc );
    
    TDesC testmorelengthnumber( KMoreLengthNumber );
    TDesC testnormalnumber( KNormalNumber );
    numbergrouping->Set( testmorelengthnumber );
    returndesc = numbergrouping->UnFormattedNumber();
    STIF_ASSERT_EQUALS( nulldesc, returndesc );
    
    numbergrouping->Set( testnormalnumber );
    returndesc = numbergrouping->UnFormattedNumber();
    STIF_ASSERT_NOT_EQUALS( nulldesc, returndesc );
    CleanupStack::PopAndDestroy( numbergrouping );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGIsCharacterInsertedByNumberGroupingL
// -----------------------------------------------------------------------------
//    
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGIsCharacterInsertedByNumberGroupingL( 
         CStifItemParser& /*aItem*/ )
    {
    TDesC normalnumberchar( KNormalNumberChar );
    TDesC testnormalnumber( KNormalNumber );
    TBool reserved( ETrue );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewLC( maxlength, 
        reserved );
    
    numbergrouping->Set( testnormalnumber );
    numbergrouping->FormattedNumber();
    TBool flag( EFalse );
    TInt position( 3 );
    flag = numbergrouping->IsCharacterInsertedByNumberGrouping( position );
    STIF_ASSERT_FALSE( flag );
    CleanupStack::PopAndDestroy( numbergrouping );
    
    CPNGNumberGrouping* numbergroup = CPNGNumberGrouping::NewLC( maxlength, 
        reserved );
    numbergroup->Set( normalnumberchar );
    flag = numbergroup->IsCharacterInsertedByNumberGrouping( position );
    STIF_ASSERT_FALSE( flag );
    CleanupStack::PopAndDestroy( numbergroup );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestNUMGRPINGIsChangedByGroupingL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestNUMGRPINGIsChangedByGroupingL( CStifItemParser&
         /*aItem*/ )
    {
    TDesC nostandardnumber( KNoStandardNumber );
    TDesC testnormalnumber( KNormalNumber );
    TBool reserved( ETrue );
    TInt maxlength( 11 );
    CPNGNumberGrouping* numbergrouping = CPNGNumberGrouping::NewLC( maxlength, 
        reserved );
    numbergrouping->Set( testnormalnumber );
    numbergrouping->FormattedNumber();
    TBool flag( EFalse );
    flag = numbergrouping->IsChangedByGrouping();
    STIF_ASSERT_FALSE( flag );
    CleanupStack::PopAndDestroy( numbergrouping );
    
    CPNGNumberGrouping* numbergroup = CPNGNumberGrouping::NewLC( maxlength, 
        reserved );
    numbergroup->Set( nostandardnumber );
    flag = ETrue;
    flag = numbergroup->IsChangedByGrouping();
    STIF_ASSERT_FALSE( flag );
    CleanupStack::PopAndDestroy( numbergroup );
     
    return KErrNone;
    }

/*
 *   [End of File]
 */
