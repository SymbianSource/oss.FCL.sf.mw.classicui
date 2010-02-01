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
* Description:  test AknDlgShut.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <akndlgshut.h>
#include <eikdialg.h> 
#include <eikenv.h>
#include <testsdkdialogshutter.rsg>

#include "testsdkdialogshutter.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKDialogShutter::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKDialogShutter::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKDialogShutter::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKDialogShutter::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestDSShutDialogsL", CTestSDKDialogShutter::TestDSShutDialogsL ),

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKDialogShutter::TestDSShutDialogsL
// -----------------------------------------------------------------------------
TInt CTestSDKDialogShutter::TestDSShutDialogsL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    
    dialog->PrepareLC( R_TESTSDK_DIALOGSHUTTER );
    CleanupStack::Pop( dialog );
    
    CEikonEnv* env = CEikonEnv::Static();
    AknDialogShutter::ShutDialogsL( *env );
    
    return KErrNone;
    
    }

//  [End of File]
