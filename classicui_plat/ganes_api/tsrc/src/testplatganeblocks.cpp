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
* Description:  ganes_api
*
*/


// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testplatgane.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestPlatGane::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestPlatGane::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 

        // [test cases entries]
        //HgDoubleGraphicList.h
        ENTRY( "TestCHgDoubleGraphicListL", CTestPlatGane::TestCHgDoubleGraphicListL ), 
        ENTRY( "TestCHgDoubleGraphicListPreferredImageSizeL", CTestPlatGane::TestCHgDoubleGraphicListPreferredImageSize ), 
        //HgDoubleGraphicListFlat.h
        ENTRY( "TestCHgDoubleGraphicListFlatL", CTestPlatGane::TestCHgDoubleGraphicListFlatL ), 
        ENTRY( "TestCHgDoubleGraphicListFlatPreferredImageSizeL", CTestPlatGane::TestCHgDoubleGraphicListFlatPreferredImageSize ), 
        //HgDoubleTextList.h
        ENTRY( "TestCHgDoubleTextListL", CTestPlatGane::TestCHgDoubleTextListL ), 
        ENTRY( "TestCHgDoubleTextListPreferredImageSize", CTestPlatGane::TestCHgDoubleTextListPreferredImageSize ), 
        //HgGrid.h
        ENTRY( "TestCHgGridNewL", CTestPlatGane::TestCHgGridNewL ), 
        ENTRY( "TestCHgGridPreferredImageSizeL", CTestPlatGane::TestCHgGridPreferredImageSize ), 
        ENTRY( "TestCHgGridSetLandscapeScrollingSupport", CTestPlatGane::TestCHgGridSetLandscapeScrollingSupport ), 
        //HgItem.h
        ENTRY( "TestCHgItemNewL", CTestPlatGane::TestCHgItemNewL ), 
        ENTRY( "TestCHgItemNewLCL", CTestPlatGane::TestCHgItemNewLCL ), 
        ENTRY( "TestCHgItemIconL", CTestPlatGane::TestCHgItemIconL ), 
        ENTRY( "TestCHgItemTitleL", CTestPlatGane::TestCHgItemTitleL ), 
        ENTRY( "TestCHgItemTextL", CTestPlatGane::TestCHgItemTextL ), 
        ENTRY( "TestCHgItemTimeL", CTestPlatGane::TestCHgItemTimeL ), 
        ENTRY( "TestCHgItemSetIconL", CTestPlatGane::TestCHgItemSetIconL ), 
        ENTRY( "TestCHgItemSetTitleL", CTestPlatGane::TestCHgItemSetTitleL ), 
        ENTRY( "TestCHgItemSetTextL", CTestPlatGane::TestCHgItemSetTextL ), 
        ENTRY( "TestCHgItemSetTimeL", CTestPlatGane::TestCHgItemSetTimeL ), 
        ENTRY( "TestCHgItemFlagsL", CTestPlatGane::TestCHgItemFlagsL ), 
        ENTRY( "TestCHgItemSetFlagsL", CTestPlatGane::TestCHgItemSetFlagsL ), 
        ENTRY( "TestCHgItemClearFlagsL", CTestPlatGane::TestCHgItemClearFlagsL ), 
        //HgScroller.h
        ENTRY( "TestCHgScrollerInitScreenL1L", CTestPlatGane::TestCHgScrollerInitScreenL1 ), 
        ENTRY( "TestCHgScrollerInitScreenL2L", CTestPlatGane::TestCHgScrollerInitScreenL2L ), 
        ENTRY( "TestCHgScrollerRefreshScreenL", CTestPlatGane::TestCHgScrollerRefreshScreenL ), 
        ENTRY( "TestCHgScrollerFirstIndexOnScreenL", CTestPlatGane::TestCHgScrollerFirstIndexOnScreenL ), 
        ENTRY( "TestCHgScrollerItemsOnScreenL", CTestPlatGane::TestCHgScrollerItemsOnScreenL ), 
        ENTRY( "TestCHgScrollerItemL", CTestPlatGane::TestCHgScrollerItemL ), 
        ENTRY( "TestCHgScrollerSetItemL", CTestPlatGane::TestCHgScrollerSetItemL ), 
        ENTRY( "TestCHgScrollerAddItemL", CTestPlatGane::TestCHgScrollerAddItemL ), 
        ENTRY( "TestCHgScrollerInsertItemL", CTestPlatGane::TestCHgScrollerInsertItemL ), 
        ENTRY( "TestCHgScrollerRemoveItemL", CTestPlatGane::TestCHgScrollerRemoveItemL ), 
        ENTRY( "TestCHgScrollerSelectedIndexL", CTestPlatGane::TestCHgScrollerSelectedIndexL ), 
        ENTRY( "TestCHgScrollerSetSelectedIndexL", CTestPlatGane::TestCHgScrollerSetSelectedIndexL ), 
        ENTRY( "TestCHgScrollerMarkL", CTestPlatGane::TestCHgScrollerMarkL ), 
        ENTRY( "TestCHgScrollerUnMarkL", CTestPlatGane::TestCHgScrollerUnMarkL ), 
        ENTRY( "TestCHgScrollerMarkAllL", CTestPlatGane::TestCHgScrollerMarkAllL ), 
        ENTRY( "TestCHgScrollerUnMarkAllL", CTestPlatGane::TestCHgScrollerUnMarkAllL ), 
        ENTRY( "TestCHgScrollerGetMarkedItemsL", CTestPlatGane::TestCHgScrollerGetMarkedItemsL ),  
        ENTRY( "TestCHgScrollerResetL", CTestPlatGane::TestCHgScrollerResetL ), 
        ENTRY( "TestCHgScrollerResizeL", CTestPlatGane::TestCHgScrollerResizeL ), 
        ENTRY( "TestCHgScrollerSetEmptyTextL", CTestPlatGane::TestCHgScrollerSetEmptyTextL ), 
        ENTRY( "TestCHgScrollerItemCountL", CTestPlatGane::TestCHgScrollerItemCountL ), 
        ENTRY( "TestCHgScrollerSetScrollBarTypeL", CTestPlatGane::TestCHgScrollerSetScrollBarTypeL ), 
        ENTRY( "TestCHgScrollerSetFlagsL", CTestPlatGane::TestCHgScrollerSetFlagsL ), 
        ENTRY( "TestCHgScrollerClearFlagsL", CTestPlatGane::TestCHgScrollerClearFlagsL ), 
        ENTRY( "TestCHgScrollerFlagsL", CTestPlatGane::TestCHgScrollerFlagsL ), 
        ENTRY( "TestCHgScrollerHightlightItemL", CTestPlatGane::TestCHgScrollerHightlightItemL ), 
        ENTRY( "TestCHgScrollerSetDefaultIconL", CTestPlatGane::TestCHgScrollerSetDefaultIconL ), 
        ENTRY( "TestCHgScrollerDisableScrollBufferL", CTestPlatGane::TestCHgScrollerDisableScrollBufferL ), 
        ENTRY( "TestCHgScrollerEnableScrollBufferL", CTestPlatGane::TestCHgScrollerEnableScrollBufferL ), 
        ENTRY( "TestCHgScrollerSetSelectionObserver", CTestPlatGane::TestCHgScrollerSetSelectionObserver ), 
        ENTRY( "TestCHgScrollerSetMarkingObserver", CTestPlatGane::TestCHgScrollerSetMarkingObserver ), 
        //HgScrollerWithTitle.h
        ENTRY( "TestCHgScrollerWithTitleNewL", CTestPlatGane::TestCHgScrollerWithTitleNewL ), 
        ENTRY( "TestCHgScrollerWithTitleInitScreenL", CTestPlatGane::TestCHgScrollerWithTitleInitScreenL ), 
        ENTRY( "TestCHgScrollerWithTitleScrollerL", CTestPlatGane::TestCHgScrollerWithTitleScrollerL ), 
        ENTRY( "TestCHgScrollerWithTitleTitleItemL", CTestPlatGane::TestCHgScrollerWithTitleTitleItemL ), 
        ENTRY( "TestCHgScrollerWithTitlePreferredImageSizeL", CTestPlatGane::TestCHgScrollerWithTitlePreferredImageSize ), 
        //HgSingleGraphicList.h
        ENTRY( "TestCHgSingleGraphicListNewL", CTestPlatGane::TestCHgSingleGraphicListNewL ), 
        ENTRY( "TestCHgSingleGraphicListPreferredImageSizeL", CTestPlatGane::TestCHgSingleGraphicListPreferredImageSize ), 
        //HgSingleLargeList.h
        ENTRY( "TestCHgSingleLargeListNewL", CTestPlatGane::TestCHgSingleLargeListNewL ), 
        ENTRY( "TestCHgSingleLargeListPreferredImageSizeL", CTestPlatGane::TestCHgSingleLargeListPreferredImageSize ), 
        //HgSingleTextList.h
        ENTRY( "TestCHgSingleTextListL", CTestPlatGane::TestCHgSingleTextListL ), 
        // HgVgMediaWall.h
        ENTRY( "TestCHgVgMediaWallNewL", CTestPlatGane::TestCHgVgMediaWallNewL ), 
        ENTRY( "TestCHgVgMediaWallInitScreenL", CTestPlatGane::TestCHgVgMediaWallInitScreenL ), 
        ENTRY( "TestCHgVgMediaWallRefreshScreen", CTestPlatGane::TestCHgVgMediaWallRefreshScreen ), 
        ENTRY( "TestCHgVgMediaWallFirstIndexOnScreen", CTestPlatGane::TestCHgVgMediaWallFirstIndexOnScreen ), 
        ENTRY( "TestCHgVgMediaWallItemsOnScreen", CTestPlatGane::TestCHgVgMediaWallItemsOnScreen ), 
        ENTRY( "TestCHgVgMediaWallItemL", CTestPlatGane::TestCHgVgMediaWallItemL ), 
        ENTRY( "TestCHgVgMediaWallSetItem", CTestPlatGane::TestCHgVgMediaWallSetItem ), 
        ENTRY( "TestCHgVgMediaWallAddItem", CTestPlatGane::TestCHgVgMediaWallAddItem ), 
        ENTRY( "TestCHgVgMediaWallInsertItem", CTestPlatGane::TestCHgVgMediaWallInsertItem ), 
        ENTRY( "TestCHgVgMediaWallRemoveItem", CTestPlatGane::TestCHgVgMediaWallRemoveItem ), 
        ENTRY( "TestCHgVgMediaWallSelectedIndex", CTestPlatGane::TestCHgVgMediaWallSelectedIndex ), 
        ENTRY( "TestCHgVgMediaWallSetSelectedIndex", CTestPlatGane::TestCHgVgMediaWallSetSelectedIndex ), 
        ENTRY( "TestCHgVgMediaWallEnableScrollBufferL", CTestPlatGane::TestCHgVgMediaWallEnableScrollBufferL ), 
        ENTRY( "TestCHgVgMediaWallSetSelectionObserver", CTestPlatGane::TestCHgVgMediaWallSetSelectionObserver ), 
        ENTRY( "TestCHgVgMediaWallReset", CTestPlatGane::TestCHgVgMediaWallReset ), 
        ENTRY( "TestCHgVgMediaWallResizeL", CTestPlatGane::TestCHgVgMediaWallResizeL ), 
        ENTRY( "TestCHgVgMediaWallSetEmptyTextL", CTestPlatGane::TestCHgVgMediaWallSetEmptyTextL ), 
        ENTRY( "TestCHgVgMediaWallItemCount", CTestPlatGane::TestCHgVgMediaWallItemCount ), 
        ENTRY( "TestCHgVgMediaWallSetDefaultIconL", CTestPlatGane::TestCHgVgMediaWallSetDefaultIconL ), 
        ENTRY( "TestCHgVgMediaWallDisableScrollBuffer", CTestPlatGane::TestCHgVgMediaWallDisableScrollBuffer ), 
        ENTRY( "TestCHgVgMediaWallChangeStyleL", CTestPlatGane::TestCHgVgMediaWallChangeStyleL ), 
        ENTRY( "TestCHgVgMediaWallSetObserver", CTestPlatGane::TestCHgVgMediaWallSetObserver ), 
        ENTRY( "TestCHgVgMediaWallSetOpeningAnimationType", CTestPlatGane::TestCHgVgMediaWallSetOpeningAnimationType ), 
        ENTRY( "TestCHgVgMediaWallStyle", CTestPlatGane::TestCHgVgMediaWallStyle ), 
        ENTRY( "TestCHgVgMediaWallOpeningAnimationType", CTestPlatGane::TestCHgVgMediaWallOpeningAnimationType ), 
        ENTRY( "TestCHgVgMediaWallStartOpeningAnimationL", CTestPlatGane::TestCHgVgMediaWallStartOpeningAnimationL ),
        // HgVgItem.h
        ENTRY( "TestCHgVgItemNewL", CTestPlatGane::TestCHgVgItemNewL ),
        ENTRY( "TestCHgVgItemNewLC", CTestPlatGane::TestCHgVgItemNewLC ),
        ENTRY( "TestCHgVgItemSetIcon", CTestPlatGane::TestCHgVgItemSetIcon ),
        // HgSingleTextListWithIcon.h
        ENTRY( "TestCHgSingleTextListWithIconNewL", CTestPlatGane::TestCHgSingleTextListWithIconNewL )        
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

