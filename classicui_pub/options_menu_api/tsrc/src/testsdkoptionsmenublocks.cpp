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
* Description:  test options_menu_api
*
*/


// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkoptionsmenu.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenu::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 

        ENTRY( "TestMBTCEikMenuBarTitleL", CTestSDKOptionsMenu::TestMBTCEikMenuBarTitleL ),
        ENTRY( "TestMBTSetIconL", CTestSDKOptionsMenu::TestMBTSetIconL ),
        ENTRY( "TestMBTSetBitmapsOwnedExternallyL", CTestSDKOptionsMenu::TestMBTSetBitmapsOwnedExternallyL ),
        ENTRY( "TestMBTDrawIconL", CTestSDKOptionsMenu::TestMBTDrawIconL ),
        ENTRY( "TestMBTCreateIconL", CTestSDKOptionsMenu::TestMBTCreateIconL ),
        ENTRY( "TestMBTSetIconBitmapL", CTestSDKOptionsMenu::TestMBTSetIconBitmapL ),
        ENTRY( "TestMBTSetIconMaskL", CTestSDKOptionsMenu::TestMBTSetIconMaskL ),
        ENTRY( "TestMBTIconBitmapL", CTestSDKOptionsMenu::TestMBTIconBitmapL ),
        ENTRY( "TestMBTIconMaskL", CTestSDKOptionsMenu::TestMBTIconMaskL ),
        ENTRY( "TestMBCEikMenuBarL", CTestSDKOptionsMenu::TestMBCEikMenuBarL ),        
        ENTRY( "TestMBOfferKeyEventL", CTestSDKOptionsMenu::TestMBOfferKeyEventL ), 
        ENTRY( "TestMBHandlePointerEventL", CTestSDKOptionsMenu::TestMBHandlePointerEventL ),         
        ENTRY( "TestMBDraw", CTestSDKOptionsMenu::TestMBDraw ),        
        ENTRY( "TestMBTACTitleArrayL", CTestSDKOptionsMenu::TestMBTACTitleArrayL ),        
        ENTRY( "TestMBTAAddTitleL", CTestSDKOptionsMenu::TestMBTAAddTitleL ),
        ENTRY( "TestMBConstructL", CTestSDKOptionsMenu::TestMBConstructL ),
        ENTRY( "TestMBConstructFromResourceL", CTestSDKOptionsMenu::TestMBConstructFromResourceL ),
        ENTRY( "TestMBChangeMenuBarL", CTestSDKOptionsMenu::TestMBChangeMenuBarL ),
        ENTRY( "TestMBSetHotKeyTableL", CTestSDKOptionsMenu::TestMBSetHotKeyTableL ),
        ENTRY( "TestMBSetMenuTitleResourceIdL", CTestSDKOptionsMenu::TestMBSetMenuTitleResourceIdL ),
        ENTRY( "TestMBSetContextMenuTitleResourceIdL", CTestSDKOptionsMenu::TestMBSetContextMenuTitleResourceIdL ),
        ENTRY( "TestMBSetMenuTitleArrayL", CTestSDKOptionsMenu::TestMBSetMenuTitleArrayL ),
        ENTRY( "TestMBSetTitleArrayOwnedExternallyL", CTestSDKOptionsMenu::TestMBSetTitleArrayOwnedExternallyL ),
        ENTRY( "TestMBSetMenuCursorL", CTestSDKOptionsMenu::TestMBSetMenuCursorL ),
        ENTRY( "TestMBStopDisplayingMenuBarL", CTestSDKOptionsMenu::TestMBStopDisplayingMenuBarL ),
        ENTRY( "TestMBTryDisplayMenuBarL", CTestSDKOptionsMenu::TestMBTryDisplayMenuBarL ),
        ENTRY( "TestMBTryDisplayContextMenuBarL", CTestSDKOptionsMenu::TestMBTryDisplayContextMenuBarL ),
        ENTRY( "TestMBTryDisplayMenuBarWithoutFepMenusL", CTestSDKOptionsMenu::TestMBTryDisplayMenuBarWithoutFepMenusL ),
        ENTRY( "TestMBMoveHighlightToL", CTestSDKOptionsMenu::TestMBMoveHighlightToL ),
        ENTRY( "TestMBDrawItemL", CTestSDKOptionsMenu::TestMBDrawItemL ),
        ENTRY( "TestMBSelectedTitleL", CTestSDKOptionsMenu::TestMBSelectedTitleL ),
        ENTRY( "TestMBSelectedItemL", CTestSDKOptionsMenu::TestMBSelectedItemL ),
        ENTRY( "TestMBFindCommandIdInResourceL", CTestSDKOptionsMenu::TestMBFindCommandIdInResourceL ),
        ENTRY( "TestMBMenuPaneL", CTestSDKOptionsMenu::TestMBMenuPaneL ),
        ENTRY( "TestMBReduceRectL", CTestSDKOptionsMenu::TestMBReduceRectL ),
        ENTRY( "TestMBTitleArrayL", CTestSDKOptionsMenu::TestMBTitleArrayL ),
        ENTRY( "TestMBSetEditMenuObserverL", CTestSDKOptionsMenu::TestMBSetEditMenuObserverL ),
        ENTRY( "TestMBRemoveEditMenuObserverL", CTestSDKOptionsMenu::TestMBRemoveEditMenuObserverL ),
        ENTRY( "TestMBIsDisplayedL", CTestSDKOptionsMenu::TestMBIsDisplayedL ),
        ENTRY( "TestMBSetMenuTypeL", CTestSDKOptionsMenu::TestMBSetMenuTypeL ),
        ENTRY( "TestMBGetColorUseListL", CTestSDKOptionsMenu::TestMBGetColorUseListL ),
        ENTRY( "TestMBHandleResourceChangeL", CTestSDKOptionsMenu::TestMBHandleResourceChangeL ),
        ENTRY( "TestMPTCEikMenuPaneTitleL", CTestSDKOptionsMenu::TestMPTCEikMenuPaneTitleL ),
        ENTRY( "TestMPTConstructL", CTestSDKOptionsMenu::TestMPTConstructL ),
        ENTRY( "TestMPTSetSelectedTitleL", CTestSDKOptionsMenu::TestMPTSetSelectedTitleL ),
        ENTRY( "TestMPTDrawL", CTestSDKOptionsMenu::TestMPTDrawL ),
        ENTRY( "TestMPTMarginsL", CTestSDKOptionsMenu::TestMPTMarginsL ),
        ENTRY( "TestMPTCloseL", CTestSDKOptionsMenu::TestMPTCloseL ),
        ENTRY( "TestMPTHandlePointerEventL", CTestSDKOptionsMenu::TestMPTHandlePointerEventL ),
        ENTRY( "TestMPTGetColorUseListL", CTestSDKOptionsMenu::TestMPTGetColorUseListL ),
        ENTRY( "TestMPTHandleResourceChangeL", CTestSDKOptionsMenu::TestMPTHandleResourceChangeL ),
        ENTRY( "TestMBItemSpecificCommandsEnabled", CTestSDKOptionsMenu::TestMBItemSpecificCommandsEnabled ),
        ENTRY( "TestMPICEikMenuPaneItemL", CTestSDKOptionsMenu::TestMPICEikMenuPaneItemL ),
        ENTRY( "TestMPISetIconL", CTestSDKOptionsMenu::TestMPISetIconL ),
        ENTRY( "TestMPIDrawItemIcon", CTestSDKOptionsMenu::TestMPIDrawItemIcon ),
        ENTRY( "TestMPICreateIconL", CTestSDKOptionsMenu::TestMPICreateIconL ),
        ENTRY( "TestMPIIconBitmap", CTestSDKOptionsMenu::TestMPIIconBitmap ),
        ENTRY( "TestMPIIconMask", CTestSDKOptionsMenu::TestMPIIconMask ),
        ENTRY( "TestMPISetBitmapsOwnedExternallyL", CTestSDKOptionsMenu::TestMPISetBitmapsOwnedExternallyL ),
        ENTRY( "TestMPISetIconBitmapL", CTestSDKOptionsMenu::TestMPISetIconBitmapL ),
        ENTRY( "TestMPISetIconMaskL", CTestSDKOptionsMenu::TestMPISetIconMaskL ),
        ENTRY( "TestMPIScaleableTextL", CTestSDKOptionsMenu::TestMPIScaleableTextL ),
        ENTRY( "TestMPISetScaleableTextL", CTestSDKOptionsMenu::TestMPISetScaleableTextL ),
        ENTRY( "TestMPIACItemArrayL", CTestSDKOptionsMenu::TestMPIACItemArrayL ),
        ENTRY( "TestMPIAAddItemL", CTestSDKOptionsMenu::TestMPIAAddItemL ),
        ENTRY( "TestMPCEikMenuPaneL", CTestSDKOptionsMenu::TestMPCEikMenuPaneL ),
        ENTRY( "TestMPConstructL", CTestSDKOptionsMenu::TestMPConstructL ),
        ENTRY( "TestMPResetL", CTestSDKOptionsMenu::TestMPResetL ),
        ENTRY( "TestMPOfferKeyEventL", CTestSDKOptionsMenu::TestMPOfferKeyEventL ),
        ENTRY( "TestMPHandlePointerEventL", CTestSDKOptionsMenu::TestMPHandlePointerEventL ),
        ENTRY( "TestMPGetColorUseListL", CTestSDKOptionsMenu::TestMPGetColorUseListL ),
        ENTRY( "TestMPHandleResourceChangeL", CTestSDKOptionsMenu::TestMPHandleResourceChangeL ),
        ENTRY( "TestMPInputCapabilitiesL", CTestSDKOptionsMenu::TestMPInputCapabilitiesL ),
        ENTRY( "TestMPDrawL", CTestSDKOptionsMenu::TestMPDrawL ),
        ENTRY( "TestMPFocusChangedL", CTestSDKOptionsMenu::TestMPFocusChangedL ),
        ENTRY( "TestMPConstructFromResourceL", CTestSDKOptionsMenu::TestMPConstructFromResourceL ),
        ENTRY( "TestMPAddMenuItemL", CTestSDKOptionsMenu::TestMPAddMenuItemL ),
        ENTRY( "TestMPAddMenuItemIntL", CTestSDKOptionsMenu::TestMPAddMenuItemIntL ),
        ENTRY( "TestMPAddMenuItemsL", CTestSDKOptionsMenu::TestMPAddMenuItemsL ),
        ENTRY( "TestMPDeleteMenuItemL", CTestSDKOptionsMenu::TestMPDeleteMenuItemL ),
        ENTRY( "TestMPDeleteBetweenMenuItemsL", CTestSDKOptionsMenu::TestMPDeleteBetweenMenuItemsL ),
        ENTRY( "TestMPItemDataL", CTestSDKOptionsMenu::TestMPItemDataL ),
        ENTRY( "TestMPItemAndPosL", CTestSDKOptionsMenu::TestMPItemAndPosL ),
        ENTRY( "TestMPStartDisplayingMenuPaneL", CTestSDKOptionsMenu::TestMPStartDisplayingMenuPaneL ),
        ENTRY( "TestMPSetItemTextDesCL", CTestSDKOptionsMenu::TestMPSetItemTextDesCL ),
        ENTRY( "TestMPSetItemTextIntL", CTestSDKOptionsMenu::TestMPSetItemTextIntL ),
        ENTRY( "TestMPSetItemDimmedL", CTestSDKOptionsMenu::TestMPSetItemDimmedL ),
        ENTRY( "TestMPSetItemButtonStateL", CTestSDKOptionsMenu::TestMPSetItemButtonStateL ),
        ENTRY( "TestMPSetSelectedItemL", CTestSDKOptionsMenu::TestMPSetSelectedItemL ),
        ENTRY( "TestMPSelectedItemL", CTestSDKOptionsMenu::TestMPSelectedItemL ),
        ENTRY( "TestMPCloseCascadeMenuL", CTestSDKOptionsMenu::TestMPCloseCascadeMenuL ),
        ENTRY( "TestMPSetItemArrayL", CTestSDKOptionsMenu::TestMPSetItemArrayL ),
        ENTRY( "TestMPSetItemArrayOwnedExternallyL", CTestSDKOptionsMenu::TestMPSetItemArrayOwnedExternallyL ),
        ENTRY( "TestMPSetLaunchingButtonL", CTestSDKOptionsMenu::TestMPSetLaunchingButtonL ),
        ENTRY( "TestMPMoveHighlightToL", CTestSDKOptionsMenu::TestMPMoveHighlightToL ),
        ENTRY( "TestMPNumberOfItemsInPaneL", CTestSDKOptionsMenu::TestMPNumberOfItemsInPaneL ),
        ENTRY( "TestMPCloseL", CTestSDKOptionsMenu::TestMPCloseL ),
        ENTRY( "TestMPOfferKeyEventBoolL", CTestSDKOptionsMenu::TestMPOfferKeyEventBoolL ),
        ENTRY( "TestMPSetScrollBarOnLeftL", CTestSDKOptionsMenu::TestMPSetScrollBarOnLeftL ),
        ENTRY( "TestMPSetArrowHeadScrollBarL", CTestSDKOptionsMenu::TestMPSetArrowHeadScrollBarL ),
        ENTRY( "TestMPNavigateToNextItemL", CTestSDKOptionsMenu::TestMPNavigateToNextItemL ),
        ENTRY( "TestMPInsertMenuItemL", CTestSDKOptionsMenu::TestMPInsertMenuItemL ),
        ENTRY( "TestMPMenuItemExistsL", CTestSDKOptionsMenu::TestMPMenuItemExistsL ),
        ENTRY( "TestMPIsCascadeMenuPaneL", CTestSDKOptionsMenu::TestMPIsCascadeMenuPaneL ),
        ENTRY( "TestMPCascadeMenuPaneL", CTestSDKOptionsMenu::TestMPCascadeMenuPaneL ),
        ENTRY( "TestMPItemDataByIndexL", CTestSDKOptionsMenu::TestMPItemDataByIndexL ),
        ENTRY( "TestMPEnableMarqueeL", CTestSDKOptionsMenu::TestMPEnableMarqueeL ),
        ENTRY( "TestMPConstructMenuSctRowL", CTestSDKOptionsMenu::TestMPConstructMenuSctRowL ),
        ENTRY( "TestMPMenuItemCommandIdL", CTestSDKOptionsMenu::TestMPMenuItemCommandIdL ),
        ENTRY( "TestMPConstructMenuSctRowIdL", CTestSDKOptionsMenu::TestMPConstructMenuSctRowIdL ),
        ENTRY( "TestMPConstructMenuSctRowFromDialogL", CTestSDKOptionsMenu::TestMPConstructMenuSctRowFromDialogL ),
        ENTRY( "TestMPMopSupplyObjectL", CTestSDKOptionsMenu::TestMPMopSupplyObjectL ),
        ENTRY( "TestMPCountComponentControlsL", CTestSDKOptionsMenu::TestMPCountComponentControlsL ),
        ENTRY( "TestMPComponentControlL", CTestSDKOptionsMenu::TestMPComponentControlL ),
        ENTRY( "TestMPSetItemSpecific", CTestSDKOptionsMenu::TestMPSetItemSpecific ),
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }




//  [End of File]
