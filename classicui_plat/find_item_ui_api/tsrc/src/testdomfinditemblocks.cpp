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
* Description:  test finditemdialog.h and finditemmenu.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testdomfinditem.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestdomfinditem::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 

        // test functions in finditemdialog.h
        ENTRY( "TestDialogNewL", Ctestdomfinditem::TestDialogNewL ),
        ENTRY( "TestDialogExecuteLD", Ctestdomfinditem::TestDialogExecuteLDL ),
        ENTRY( "TestDialogProcessCommandL", Ctestdomfinditem::TestDialogProcessCommandL ),
        ENTRY( "TestDialogOfferKeyEventL", Ctestdomfinditem::TestDialogOfferKeyEventL ),

        // test functions in finditemmenu.h
        ENTRY( "TestMenuNewL", Ctestdomfinditem::TestMenuNewL ),
        ENTRY( "TestMenuNewLC", Ctestdomfinditem::TestMenuNewLCL ),
        ENTRY( "TestMenuDisplayFindItemMenuItemL", Ctestdomfinditem::TestMenuDisplayFindItemMenuItemL ),
        ENTRY( "TestMenuDisplayFindItemCascadeMenuL", Ctestdomfinditem::TestMenuDisplayFindItemCascadeMenuL ),
        ENTRY( "TestMenuCommandIsValidL", Ctestdomfinditem::TestMenuCommandIsValidL ),
        ENTRY( "TestMenuSearchCase", Ctestdomfinditem::TestMenuSearchCaseL ),
        ENTRY( "TestMenuUpdateItemFinderMenuL", Ctestdomfinditem::TestMenuUpdateItemFinderMenuL ),
        ENTRY( "TestMenuHandleItemFinderCommandL", Ctestdomfinditem::TestMenuHandleItemFinderCommandL ),
        ENTRY( "TestMenuAttachItemFinderMenuL", Ctestdomfinditem::TestMenuAttachItemFinderMenuL ),
        ENTRY( "TestMenuSetCallbackNumber", Ctestdomfinditem::TestMenuSetCallbackNumberL ),
        ENTRY( "TestMenuHandleCallL", Ctestdomfinditem::TestMenuHandleCallL ),
        ENTRY( "TestMenuHandleVoIPCallL", Ctestdomfinditem::TestMenuHandleVoIPCallL ),
        ENTRY( "TestMenuSetSenderHighlightStatus", Ctestdomfinditem::TestMenuSetSenderHighlightStatusL ),
        ENTRY( "TestMenuSetSenderDisplayText", Ctestdomfinditem::TestMenuSetSenderDisplayTextL ),
        ENTRY( "TestMenuAddItemFindMenuL", Ctestdomfinditem::TestMenuAddItemFindMenuL ),
        ENTRY( "TestMenuSetSenderDescriptorType", Ctestdomfinditem::TestMenuSetSenderDescriptorTypeL ),
        ENTRY( "TestMenuSetMenuItemVisibilityL", Ctestdomfinditem::TestMenuSetMenuItemVisibilityL ),
        // [test cases entries]
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


//  [End of File]
