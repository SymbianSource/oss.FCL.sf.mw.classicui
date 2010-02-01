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
* Description:  Test extended_notes_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknsitemid.h>
#include <coeccntx.h>
#include <aknlongtapanimation.h>
#include <babitflags.h>
#include <aknnoteattributes.h>

#include "testdomextnotes.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMExtNotes::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMExtNotes::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestExtNotesGetSkinnedBitmapID", CTestDOMExtNotes::TestExtNotesGetSkinnedBitmapID ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMExtNotes::TestExtNotesGetSkinnedBitmapID
// -----------------------------------------------------------------------------
//
TInt CTestDOMExtNotes::TestExtNotesGetSkinnedBitmapID( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMExtNotes, "testdomextnotes" );
    _LIT( KTestExtNotesGetSkinnedBitmapID, "TestExtNotesGetSkinnedBitmapID" );
    TestModuleIf().Printf( 0, KTestDOMExtNotes, KTestExtNotesGetSkinnedBitmapID );
    // Print to log file
    iLog->Log( KTestExtNotesGetSkinnedBitmapID );

    CAknNoteAttributes::GetSkinnedBitmapID( 0 );

    return KErrNone;

    }


//  [End of File]
