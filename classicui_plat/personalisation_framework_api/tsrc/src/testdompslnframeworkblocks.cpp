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
* Description:  
*
*/



// [INCLUDE FILES] - do not remove
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include "testdompslnframework.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestdompslnframework::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestDOMPSLNFramework::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctestdompslnframework::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        // PslnFWBaseContainer.h
        ENTRY( "TestPlsnFWBCConstructL", CTestDOMPSLNFramework::TestPlsnFWBCConstructL ),
        ENTRY( "TestPlsnFWBCBaseConstructL", CTestDOMPSLNFramework::TestPlsnFWBCBaseConstructL ),
        ENTRY( "TestPlsnFWBCCPslnFWBaseContainer", 
            CTestDOMPSLNFramework::TestPlsnFWBCCPslnFWBaseContainerL ),
        ENTRY( "TestPlsnFWBCDelete", CTestDOMPSLNFramework::TestPlsnFWBCDelete ),
        ENTRY( "TestPlsnFWBCSetMiddleSoftkeyObserver", 
            CTestDOMPSLNFramework::TestPlsnFWBCSetMiddleSoftkeyObserverL ),
            
        // PslnPluginInterface.h
        ENTRY( "TestPlsnFWBVCPslnFWBaseView", 
            CTestDOMPSLNFramework::TestPlsnFWBVCPslnFWBaseViewL ),
        ENTRY( "TestPlsnFWBVConstructL", CTestDOMPSLNFramework::TestPlsnFWBVConstructL ),
        ENTRY( "TestPlsnFWBVDelete", CTestDOMPSLNFramework::TestPlsnFWBVDelete ),
        ENTRY( "TestPlsnFWBVSetCurrentItem", 
            CTestDOMPSLNFramework::TestPlsnFWBVSetCurrentItem ),
        ENTRY( "TestPlsnFWBVContainer", CTestDOMPSLNFramework::TestPlsnFWBVContainer ),
        ENTRY( "TestPlsnFWBVOpenLocalizedResourceFileL",
            CTestDOMPSLNFramework::TestPlsnFWBVOpenLocalizedResourceFileL ),
        ENTRY( "TestPlsnFWBVOpenLocalizedResourceFileLWithPathL",
            CTestDOMPSLNFramework::TestPlsnFWBVOpenLocalizedResourceFileLWithPathL ),
        ENTRY( "TestPlsnFWBVSetNaviPaneDecorator",
            CTestDOMPSLNFramework::TestPlsnFWBVSetNaviPaneDecoratorL ),
        ENTRY( "TestPlsnFWBVDoActivateL", CTestDOMPSLNFramework::TestPlsnFWBVDoActivateL ),
        ENTRY( "TestPlsnFWBVDoDeactivate", CTestDOMPSLNFramework::TestPlsnFWBVDoDeactivateL ),
        ENTRY( "TestPlsnFWBVSetTabIndex", CTestDOMPSLNFramework::TestPlsnFWBVSetTabIndex ),
        ENTRY( "TestPlsnFWBVGetTabIndex", CTestDOMPSLNFramework::TestPlsnFWBVGetTabIndex ),
        //protected
        ENTRY( "TestPlsnFWBVSetNaviPaneL", CTestDOMPSLNFramework::TestPlsnFWBVSetNaviPaneL ),
        ENTRY( "TestPlsnFWBVCreateNaviPaneContextL",
            CTestDOMPSLNFramework::TestPlsnFWBVCreateNaviPaneContextL ),
        ENTRY( "TestPlsnFWBVCreateContainerL", CTestDOMPSLNFramework::TestPlsnFWBVCreateContainerL ),
        ENTRY( "TestPlsnFWBVNewContainerL", CTestDOMPSLNFramework::TestPlsnFWBVNewContainerL ),
        ENTRY( "TestPlsnFWBVSetNaviPaneLWithTIntL",
            CTestDOMPSLNFramework::TestPlsnFWBVSetNaviPaneLWithTIntL ),
        ENTRY( "TestPlsnFWBVSetMiddleSoftKeyLabelL",
            CTestDOMPSLNFramework::TestPlsnFWBVSetMiddleSoftKeyLabelL ),
        ENTRY( "TestPlsnFWBVHandleCommandL", CTestDOMPSLNFramework::TestPlsnFWBVHandleCommandL ),
        ENTRY( "TestPlsnFWBVSetTitlePaneL", CTestDOMPSLNFramework::TestPlsnFWBVSetTitlePaneL ),
            
        // PslnFWIconHelper.h
        ENTRY( "TestPlsnFWIHNewL", CTestDOMPSLNFramework::TestPlsnFWIHNewL ),
        ENTRY( "TestPlsnFWIHDelete", CTestDOMPSLNFramework::TestPlsnFWIHDelete ),
        ENTRY( "TestPlsnFWIHAddIconsToSettingItemsL",
            CTestDOMPSLNFramework::TestPlsnFWIHAddIconsToSettingItemsL ),
        ENTRY( "TestPlsnFWIHGetLocalizedStringLC",
            CTestDOMPSLNFramework::TestPlsnFWIHGetLocalizedStringLC ),
            
        //PslnFWPluginHandler.h
        ENTRY( "TestPlsnFWPHNewL",CTestDOMPSLNFramework::TestPlsnFWPHNewL ),
        ENTRY( "TestPlsnFWPHNewLWithArray", CTestDOMPSLNFramework::TestPlsnFWPHNewLWithArrayL ),
        ENTRY( "TestPlsnFWPHDelete", CTestDOMPSLNFramework::TestPlsnFWPHDelete ),
        ENTRY( "TestPlsnFWPHLoadPluginsLWithArray",
            CTestDOMPSLNFramework::TestPlsnFWPHLoadPluginsLWithArrayL ),
        ENTRY( "TestPlsnFWPHLoadPluginsLWithId",
            CTestDOMPSLNFramework::TestPlsnFWPHLoadPluginsLWithId ),
            
            
        //ADD NEW ENTRY HERE
        // [test cases entries] - Do not remove

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

//  [End of File] - Do not remove
