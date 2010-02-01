/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test aknedformaccessor.h
*
*/



// [INCLUDE FILES]
#include <aknedformaccessor.h>
#include <eikedwin.h>

#include "testdomeditor.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestAcceDefConsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestAcceDefConsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestAcceDefCons, "In AcceDefCons" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestAcceDefCons );
    // Print to log file
    iLog->Log( KTestAcceDefCons );

    CEikEdwin* edwin = new( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    CAknEdwinFormAccessor* accessor = new ( ELeave ) CAknEdwinFormAccessor( edwin );
    CleanupStack::PushL( accessor );
    STIF_ASSERT_NOT_NULL( accessor );

    CleanupStack::PopAndDestroy( accessor );
    CleanupStack::PopAndDestroy( edwin );
     return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestAcceSetEdwinL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestAcceSetEdwinL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestAcceSetEdwin, "In AcceSetEdwin" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestAcceSetEdwin );
    // Print to log file
    iLog->Log( KTestAcceSetEdwin );

    CEikEdwin* edwin = new( ELeave ) CEikEdwin;
    CleanupStack::PushL( edwin );
    CAknEdwinFormAccessor* accessor = new ( ELeave ) CAknEdwinFormAccessor( edwin );
    CleanupStack::PushL( accessor );

    accessor->SetEdwin( edwin );

    CleanupStack::PopAndDestroy( accessor );
    CleanupStack::PopAndDestroy( edwin );
     return KErrNone;

    }


