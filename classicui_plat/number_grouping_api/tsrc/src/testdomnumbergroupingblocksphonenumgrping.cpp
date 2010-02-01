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
#include <aknphonenumbergrouping.h>
#include <e32cmn.h>

#include "testdomnumbergrouping.h"

const TInt KTwo = 2;

/*
 * Descriptor declare
 */
_LIT( KNormalNumber, "13548130726" );
_LIT( KMoreLengthNumber, "1354813072688" );
_LIT( KLessLengthNumber, "135481307" );
// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGNewLCL( CStifItemParser& /*aItem*/ )
    {
    TInt unformattedLength( 11 );
    CAknPhoneNumberGrouping* phonenumbergrouping = 
        CAknPhoneNumberGrouping::NewLC( unformattedLength );
    STIF_ASSERT_NOT_NULL( phonenumbergrouping );
    CleanupStack::PopAndDestroy( phonenumbergrouping );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGNewLL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGNewLL( CStifItemParser& /*aItem*/ )
    {
    TInt unformattedLength( 11 );
    CAknPhoneNumberGrouping* phonenumbergrouping = 
        CAknPhoneNumberGrouping::NewL( unformattedLength );
    CleanupStack::PushL( phonenumbergrouping );
    STIF_ASSERT_NOT_NULL( phonenumbergrouping );
    CleanupStack::PopAndDestroy( phonenumbergrouping );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGSetL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGSetL( CStifItemParser& /*aItem*/ )
    {
    TInt unformattedLength( 11 );
    CAknPhoneNumberGrouping* phonenumbergrouping = 
        CAknPhoneNumberGrouping::NewLC( unformattedLength );
    
    TInt err( KErrNone );
    TDesC testmorelengthnumber( KMoreLengthNumber );
    TDesC testnormalnumber( KNormalNumber );
    TDesC testlesslengthnumber( KLessLengthNumber );
    
    err = phonenumbergrouping->Set( testnormalnumber );
    STIF_ASSERT_EQUALS( KErrNone, err );
    
    err = phonenumbergrouping->Set( testmorelengthnumber );
    STIF_ASSERT_EQUALS( KErrOverflow, err );
    
    err = phonenumbergrouping->Set( testlesslengthnumber );
    STIF_ASSERT_EQUALS( KErrNone, err );
    
    CleanupStack::PopAndDestroy( phonenumbergrouping );
        
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGFormattedNumberL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGFormattedNumberL( 
         CStifItemParser& /*aItem*/ )
    {
    TInt unformattedLength( 11 );
    CAknPhoneNumberGrouping* phonenumbergrouping = 
        CAknPhoneNumberGrouping::NewLC( unformattedLength );
    
    TDesC testmorelengthnumber( KMoreLengthNumber );
    TDesC testnormalnumber( KNormalNumber );
    TDesC testlesslengthnumber( KLessLengthNumber );
    TDesC nulldesc( KNullDesC );
    TDesC returnvalue( KNullDesC );
    
    returnvalue = phonenumbergrouping->FormattedNumber();  
    STIF_ASSERT_EQUALS( nulldesc, returnvalue );
    
    phonenumbergrouping->Set( testnormalnumber );
    returnvalue = phonenumbergrouping->FormattedNumber();  
    STIF_ASSERT_NOT_EQUALS( nulldesc, returnvalue );
    CleanupStack::PopAndDestroy( phonenumbergrouping );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGCopyFormattedNumberL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGCopyFormattedNumberL( 
         CStifItemParser& /*aItem*/ )
    {
    TInt unformattedLength( 11 );
    CAknPhoneNumberGrouping* phonenumbergrouping = 
        CAknPhoneNumberGrouping::NewLC( unformattedLength );
    
    TDesC testnormalnumber( KNormalNumber );
    phonenumbergrouping->Set( testnormalnumber );
    
    HBufC* buf = HBufC::NewL( 12 ); 
    CleanupStack::PushL( buf );
    TPtr16 tmp( buf->Des() ); 
    
    phonenumbergrouping->CopyFormattedNumber( tmp );
    CleanupStack::PopAndDestroy( KTwo );
    
    return KErrNone;;
    }

// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGCreateGroupedPhoneNumberL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGCreateGroupedPhoneNumberL( 
         CStifItemParser& /*aItem*/ )
    {
    TInt unformattedLength( 11 );
    CAknPhoneNumberGrouping* phonenumbergrouping = 
        CAknPhoneNumberGrouping::NewLC( unformattedLength );
    
    TDesC testnormalnumber( KNormalNumber );
    HBufC* returnvalue( NULL );
    returnvalue = phonenumbergrouping->CreateGroupedPhoneNumberL( testnormalnumber );
    STIF_ASSERT_NOT_NULL( returnvalue );
    CleanupStack::PopAndDestroy( phonenumbergrouping );
        
    return KErrNone;
    }
 
// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGGroupPhoneNumberGroupL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGGroupPhoneNumberGroupL( 
         CStifItemParser& /*aItem*/ )
    {
    TInt unformattedLength( 11 );
    CAknPhoneNumberGrouping* phonenumbergrouping = 
        CAknPhoneNumberGrouping::NewLC( unformattedLength );
    
    TDesC testnormalnumber( KNormalNumber );
    HBufC* buf = HBufC::NewL( 12 ); 
    CleanupStack::PushL( buf );
    TPtr16 tmp( buf->Des() ); 
    TInt returnvalue( 0 );
    
    returnvalue = phonenumbergrouping->GroupPhoneNumber( 
        testnormalnumber, tmp );
    STIF_ASSERT_NOT_EQUALS( 0 , returnvalue );
    CleanupStack::PopAndDestroy( KTwo );
    
    return KErrNone;
    }
 
// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGGroupPhoneNumberPhoneL
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGGroupPhoneNumberPhoneL( 
         CStifItemParser& /*aItem*/ )
    {
    TInt unformattedLength( 11 );
    CAknPhoneNumberGrouping* phonenumbergrouping = 
        CAknPhoneNumberGrouping::NewLC( unformattedLength );
    
    HBufC* buf = HBufC::NewL( 12 ); 
    CleanupStack::PushL( buf );
    *buf = _L( "324345" );
    TPtr16 tmp( buf->Des() ); 
    TInt returnvalue( 0 );
    
    returnvalue = phonenumbergrouping->GroupPhoneNumber( tmp, tmp );
    STIF_ASSERT_NOT_EQUALS( 0, returnvalue );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }
    
/*
 *   [End of File]
 */
