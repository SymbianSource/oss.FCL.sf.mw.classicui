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
 *  [INCLUDE FILES]
 */
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testdomnumbergrouping.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestDOMNUMBERGROUPING::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestDOMNUMBERGROUPING::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMNUMBERGROUPING::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestPHONENUMGRPINGNewLCL", CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGNewLCL ),
        ENTRY( "TestPHONENUMGRPINGNewLL", CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGNewLL ),
        ENTRY( "TestPHONENUMGRPINGSetL", CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGSetL ),
        ENTRY( "TestPHONENUMGRPINGFormattedNumberL", CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGFormattedNumberL ),
        ENTRY( "TestPHONENUMGRPINGCopyFormattedNumberL", CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGCopyFormattedNumberL ),
        ENTRY( "TestPHONENUMGRPINGCreateGroupedPhoneNumberL", CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGCreateGroupedPhoneNumberL ),
        ENTRY( "TestPHONENUMGRPINGGroupPhoneNumberGroupL", CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGGroupPhoneNumberGroupL ),
        ENTRY( "TestPHONENUMGRPINGGroupPhoneNumberPhoneL", CTestDOMNUMBERGROUPING::TestPHONENUMGRPINGGroupPhoneNumberPhoneL ),
        
        ENTRY( "TestNUMGRPINGNewLL", CTestDOMNUMBERGROUPING::TestNUMGRPINGNewLL ),
        ENTRY( "TestNUMGRPINGNewLCL", CTestDOMNUMBERGROUPING::TestNUMGRPINGNewLCL ),
        ENTRY( "TestNUMGRPINGDestructorL", CTestDOMNUMBERGROUPING::TestNUMGRPINGDestructorL ),
        ENTRY( "TestNUMGRPINGInsertL", CTestDOMNUMBERGROUPING::TestNUMGRPINGInsertL ),
        ENTRY( "TestNUMGRPINGDeleteL", CTestDOMNUMBERGROUPING::TestNUMGRPINGDeleteL ),
        ENTRY( "TestNUMGRPINGAppendL", CTestDOMNUMBERGROUPING::TestNUMGRPINGAppendL ),
        ENTRY( "TestNUMGRPINGSetL", CTestDOMNUMBERGROUPING::TestNUMGRPINGSetL ),
        ENTRY( "TestNUMGRPINGLengthL", CTestDOMNUMBERGROUPING::TestNUMGRPINGLengthL ),
        ENTRY( "TestNUMGRPINGUnFormattedLengthL", CTestDOMNUMBERGROUPING::TestNUMGRPINGUnFormattedLengthL ),
        ENTRY( "TestNUMGRPINGMaxDisplayLengthL", CTestDOMNUMBERGROUPING::TestNUMGRPINGMaxDisplayLengthL ),
        ENTRY( "TestNUMGRPINGIsSpaceL", CTestDOMNUMBERGROUPING::TestNUMGRPINGIsSpaceL ),
        ENTRY( "TestNUMGRPINGFormattedNumberL", CTestDOMNUMBERGROUPING::TestNUMGRPINGFormattedNumberL ),
        ENTRY( "TestNUMGRPINGFormattedNumberNullL", CTestDOMNUMBERGROUPING::TestNUMGRPINGFormattedNumberNullL ),
        ENTRY( "TestNUMGRPINGReverseFormattedNumberL", CTestDOMNUMBERGROUPING::TestNUMGRPINGReverseFormattedNumberL ),
        ENTRY( "TestNUMGRPINGReverseFormattedNumberNullL", CTestDOMNUMBERGROUPING::TestNUMGRPINGReverseFormattedNumberNullL ),
        ENTRY( "TestNUMGRPINGSelectionL", CTestDOMNUMBERGROUPING::TestNUMGRPINGSelectionL ),
        ENTRY( "TestNUMGRPINGUnFormattedNumberL", CTestDOMNUMBERGROUPING::TestNUMGRPINGUnFormattedNumberL ),
        ENTRY( "TestNUMGRPINGUnFormattedNumberNullL", CTestDOMNUMBERGROUPING::TestNUMGRPINGUnFormattedNumberNullL ),
        ENTRY( "TestNUMGRPINGIsCharacterInsertedByNumberGroupingL", CTestDOMNUMBERGROUPING::TestNUMGRPINGIsCharacterInsertedByNumberGroupingL ),
        ENTRY( "TestNUMGRPINGIsChangedByGroupingL", CTestDOMNUMBERGROUPING::TestNUMGRPINGIsChangedByGroupingL ),
        
        

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

/*
 *   [End of File]
 */
