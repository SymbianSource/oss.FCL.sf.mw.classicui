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
* Description:   Test uikon core controls 
*
*/


// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <eikbtgpc.h>
#include <testsdkuikoncc.rsg>
#include <aknenv.h>

#include "testsdkuikoncc.h"
#include "testsdkuikonccobserver.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSdkUikoncc::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSdkUikoncc::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestSdkUikoncc::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSdkUikoncc::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestBGAnimateCommandL", CTestSdkUikoncc::TestBGAnimateCommandL ),
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestSdkUikoncc::TestEIKBTGRPAnimateCommandL
// -----------------------------------------------------------------------------
//

TInt CTestSdkUikoncc::TestBGAnimateCommandL( CStifItemParser& /*aItem*/ )
    {
    MEikMenuObserver* iObserver = CAknEnv::Static()->FepMenuObserver();
    TInt toolbarresid= R_TESTBUTTONS_TOOLBAR;
    RWindowGroup& parentwg = iEnv->RootWin();
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
            CEikButtonGroupContainer::EView,
            CEikButtonGroupContainer::EVertical, iObserver,
            toolbarresid, parentwg, CEikButtonGroupContainer::EAddToStack );
    CleanupStack::PushL( btgroupcontainer );

    MEikButtonGroup *eikcba = btgroupcontainer->ButtonGroup() ;
    
    eikcba->AnimateCommand( 0);
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

//LIBRARY         avkon.lib 
//LIBRARY         eikcoctl.lib
//LIBRARY         eikctl.lib 
//LIBRARY         form.lib 
//LIBRARY         uiklaf.lib 
//
//
//
//LIBRARY         apparc.lib
//LIBRARY         cone.lib
//LIBRARY         eikcore.lib
//
//
//LIBRARY         ws32.lib
//LIBRARY         AknSkins.lib
//LIBRARY         apgrfx.lib
//LIBRARY         efsrv.lib
//LIBRARY         estor.lib
//LIBRARY         aknicon.lib
//LIBRARY         bafl.lib
//  [End of File]
