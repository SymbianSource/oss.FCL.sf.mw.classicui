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
* Description:  test aknsinglecolumnstyletreelist.h aknsinglestyletreelist.h 
*                     akntreelist.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkhierarchicallists.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKHierarchicalLists::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKHierarchicalLists::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestHLSCLNewL", CTestSDKHierarchicalLists::TestHLSCLNewL ),
        ENTRY( "TestHLSCLCNewL", CTestSDKHierarchicalLists::TestHLSCLCNewL ),
        ENTRY( "TestHLSCLNewLC", CTestSDKHierarchicalLists::TestHLSCLNewLC ),
        ENTRY( "TestHLSCLCNewLC", CTestSDKHierarchicalLists::TestHLSCLCNewLC ),
        ENTRY( "TestHLSCLAddSimpleDataRowL", CTestSDKHierarchicalLists::TestHLSCLAddSimpleDataRowL ),
        ENTRY( "TestHLSCLAddCoreDataRowL", CTestSDKHierarchicalLists::TestHLSCLAddCoreDataRowL ),
        ENTRY( "TestHLSCLAddCoreDataRowCL", CTestSDKHierarchicalLists::TestHLSCLAddCoreDataRowCL ),
        ENTRY( "TestHLSCLAddSubtitleRowL", CTestSDKHierarchicalLists::TestHLSCLAddSubtitleRowL ),
        ENTRY( "TestHLSCLTextL", CTestSDKHierarchicalLists::TestHLSCLTextL ),
        ENTRY( "TestHLSCLTextCIL", CTestSDKHierarchicalLists::TestHLSCLTextCIL ),
        ENTRY( "TestHLSCLSetTextL", CTestSDKHierarchicalLists::TestHLSCLSetTextL ),
        ENTRY( "TestHLSCLSetTextCIL", CTestSDKHierarchicalLists::TestHLSCLSetTextCIL ),
        ENTRY( "TestHLSCLIsEmphasisedL", CTestSDKHierarchicalLists::TestHLSCLIsEmphasisedL ),
        ENTRY( "TestHLSCLSetEmphasisL", CTestSDKHierarchicalLists::TestHLSCLSetEmphasisL ),
        ENTRY( "TestHLSCLIsThirdColumnEnabledL", CTestSDKHierarchicalLists::TestHLSCLIsThirdColumnEnabledL ),
        ENTRY( "TestHLSCLEnableThirdColumnL", CTestSDKHierarchicalLists::TestHLSCLEnableThirdColumnL ),
        ENTRY( "TestHLSCLIconL", CTestSDKHierarchicalLists::TestHLSCLIconL ),
        ENTRY( "TestHLSCLSetIconL", CTestSDKHierarchicalLists::TestHLSCLSetIconL ),
        ENTRY( "TestHLSCLItemTypeL", CTestSDKHierarchicalLists::TestHLSCLItemTypeL ),

        ENTRY( "TestHLSSLNewL", CTestSDKHierarchicalLists::TestHLSSLNewL ),
        ENTRY( "TestHLSSLCNewL", CTestSDKHierarchicalLists::TestHLSSLCNewL ),
        ENTRY( "TestHLSSLNewLC", CTestSDKHierarchicalLists::TestHLSSLNewLC ),
        ENTRY( "TestHLSSLCNewLC", CTestSDKHierarchicalLists::TestHLSSLCNewLC ),
        ENTRY( "TestHLSSLAddLeafL", CTestSDKHierarchicalLists::TestHLSSLAddLeafL ),
        ENTRY( "TestHLSSLAddNodeL", CTestSDKHierarchicalLists::TestHLSSLAddNodeL ),
        ENTRY( "TestHLSSLSortL", CTestSDKHierarchicalLists::TestHLSSLSortL ),
        ENTRY( "TestHLSSLSetTextL", CTestSDKHierarchicalLists::TestHLSSLSetTextL ),
        ENTRY( "TestHLSSLTextL", CTestSDKHierarchicalLists::TestHLSSLTextL ),
        ENTRY( "TestHLSSLSetIconL", CTestSDKHierarchicalLists::TestHLSSLSetIconL ),
        ENTRY( "TestHLSSLIconL", CTestSDKHierarchicalLists::TestHLSSLIconL ),
        
        ENTRY( "TestHLTLSetFlagsL", CTestSDKHierarchicalLists::TestHLTLSetFlagsL ),
        ENTRY( "TestHLTLFlagsL", CTestSDKHierarchicalLists::TestHLTLFlagsL ),
        ENTRY( "TestHLTLMoveItemL", CTestSDKHierarchicalLists::TestHLTLMoveItemL ),
        ENTRY( "TestHLTLRemoveItemL", CTestSDKHierarchicalLists::TestHLTLRemoveItemL ),
        ENTRY( "TestHLTLExpandNodeL", CTestSDKHierarchicalLists::TestHLTLExpandNodeL ),
        ENTRY( "TestHLTLCollapseNodeL", CTestSDKHierarchicalLists::TestHLTLCollapseNodeL ),
        ENTRY( "TestHLTLIsExpandedL", CTestSDKHierarchicalLists::TestHLTLIsExpandedL ),
        ENTRY( "TestHLTLFocusedItemL", CTestSDKHierarchicalLists::TestHLTLFocusedItemL ),
        ENTRY( "TestHLTLSetFocusedItemL", CTestSDKHierarchicalLists::TestHLTLSetFocusedItemL ),
        ENTRY( "TestHLTLHighlightRectL", CTestSDKHierarchicalLists::TestHLTLHighlightRectL ),
        ENTRY( "TestHLTLAddIconL", CTestSDKHierarchicalLists::TestHLTLAddIconL ),
        ENTRY( "TestHLTLAddIIconL", CTestSDKHierarchicalLists::TestHLTLAddIIconL ),
        ENTRY( "TestHLTLAddColorIconL", CTestSDKHierarchicalLists::TestHLTLAddColorIconL ),
        ENTRY( "TestHLTLAssignIconL", CTestSDKHierarchicalLists::TestHLTLAssignIconL ),
        ENTRY( "TestHLTLAssignIIconL", CTestSDKHierarchicalLists::TestHLTLAssignIIconL ),
        ENTRY( "TestHLTLAssignColorIconL", CTestSDKHierarchicalLists::TestHLTLAssignColorIconL ),
        ENTRY( "TestHLTLRemoveIconL", CTestSDKHierarchicalLists::TestHLTLRemoveIconL ),
        ENTRY( "TestHLTLChildCountL", CTestSDKHierarchicalLists::TestHLTLChildCountL ),
        ENTRY( "TestHLTLChildL", CTestSDKHierarchicalLists::TestHLTLChildL ),
        ENTRY( "TestHLTLParentL", CTestSDKHierarchicalLists::TestHLTLParentL ),
        ENTRY( "TestHLTLContainsL", CTestSDKHierarchicalLists::TestHLTLContainsL ),
        ENTRY( "TestHLTLIsNodeL", CTestSDKHierarchicalLists::TestHLTLIsNodeL ),
        ENTRY( "TestHLTLIsLeafL", CTestSDKHierarchicalLists::TestHLTLIsLeafL ),
        ENTRY( "TestHLTLIsMarkedL", CTestSDKHierarchicalLists::TestHLTLIsMarkedL ),
        ENTRY( "TestHLTLSetMarkedL", CTestSDKHierarchicalLists::TestHLTLSetMarkedL ),
        ENTRY( "TestHLTLEnableMarkingL", CTestSDKHierarchicalLists::TestHLTLEnableMarkingL ),
        ENTRY( "TestHLTLGetMarkedRItemsL", CTestSDKHierarchicalLists::TestHLTLGetMarkedRItemsL ),
        ENTRY( "TestHLTLGetMarkedItemsL", CTestSDKHierarchicalLists::TestHLTLGetMarkedItemsL ),
        ENTRY( "TestHLTLIsEmptyL", CTestSDKHierarchicalLists::TestHLTLIsEmptyL ),
        ENTRY( "TestHLTLSetNonEmptyL", CTestSDKHierarchicalLists::TestHLTLSetNonEmptyL ),
        ENTRY( "TestHLTLIsPersistentL", CTestSDKHierarchicalLists::TestHLTLIsPersistentL ),
        ENTRY( "TestHLTLSetPersistentL", CTestSDKHierarchicalLists::TestHLTLSetPersistentL ),
        ENTRY( "TestHLTLSortL", CTestSDKHierarchicalLists::TestHLTLSortL ),
        ENTRY( "TestHLTLNSortL", CTestSDKHierarchicalLists::TestHLTLNSortL ),
        ENTRY( "TestHLTLAddObserverL", CTestSDKHierarchicalLists::TestHLTLAddObserverL ),
        ENTRY( "TestHLTLRemoveObserverL", CTestSDKHierarchicalLists::TestHLTLRemoveObserverL ),
        ENTRY( "TestHLTLTabModeFunctionIndicatorsL", CTestSDKHierarchicalLists::TestHLTLTabModeFunctionIndicatorsL ),
        ENTRY( "TestHLTLEnableTabModeFunctionIndicatorsL", CTestSDKHierarchicalLists::TestHLTLEnableTabModeFunctionIndicatorsL ),
        ENTRY( "TestHLTLSetFocusedItemIDL", CTestSDKHierarchicalLists::TestHLTLSetFocusedItemIDL ),
        ENTRY( "TestHLTLFocusedItemIndexL", CTestSDKHierarchicalLists::TestHLTLFocusedItemIndexL ),
        ENTRY( "TestHLTLVisibleItemIndexL", CTestSDKHierarchicalLists::TestHLTLVisibleItemIndexL ),
        ENTRY( "TestHLTLOSortL", CTestSDKHierarchicalLists::TestHLTLOSortL ),
        ENTRY( "TestHLTLFBSortL", CTestSDKHierarchicalLists::TestHLTLFBSortL ),
        ENTRY( "TestHLTLSetEmptyTextL", CTestSDKHierarchicalLists::TestHLTLSetEmptyTextL ),
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


//  [End of File]
