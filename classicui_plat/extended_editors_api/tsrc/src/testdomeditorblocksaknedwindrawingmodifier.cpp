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
* Description:  test aknedwindrawingmodifier.h
*
*/



#include <aknedwindrawingmodifier.h>

#include "testdomeditor.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestModifSetInhibitL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestModifSetInhibitL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestModifSetInhibit, "In ModifSetInhibit" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestModifSetInhibit );
    // Print to log file
    iLog->Log( KTestModifSetInhibit );

    CAknEdwinDrawingModifier* modifier = new ( ELeave ) CAknEdwinDrawingModifier;
    CleanupStack::PushL( modifier );

    modifier->SetInhibitNotifyNewFormatDrawing( ETrue );

    CleanupStack::PopAndDestroy( modifier );
     return KErrNone;

    }


