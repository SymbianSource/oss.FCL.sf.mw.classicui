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
* Description:  test AknToolbar.h,akntoolbarextension.h and AknToolbarObserver.h
*
*/


// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdktoolbar.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKToolbar::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 

        // akntoolbar.h
        ENTRY( "TestToolbarNewL", CTestSDKToolbar::TestToolbarNewL ),
        ENTRY( "TestToolbarNewLC", CTestSDKToolbar::TestToolbarNewLCL ),
        ENTRY( "TestToolbarCountComponentControls",
                CTestSDKToolbar::TestToolbarCountComponentControlsL ),
        ENTRY( "TestToolbarComponentControl",
                CTestSDKToolbar::TestToolbarComponentControlL ),
        ENTRY( "TestToolbarHandlePointerEventL",
                CTestSDKToolbar::TestToolbarHandlePointerEventL ),
        ENTRY( "TestToolbarHandleResourceChange",
                CTestSDKToolbar::TestToolbarHandleResourceChangeL ),
        ENTRY( "TestToolbarHandleControlEventL",
                CTestSDKToolbar::TestToolbarHandleControlEventL ),
        ENTRY( "TestToolbarPositionChanged",
                CTestSDKToolbar::TestToolbarPositionChangedL ),
        ENTRY( "TestToolbarProcessCommandL",
                CTestSDKToolbar::TestToolbarProcessCommandL ),
        ENTRY( "TestToolbarSetDimmed", CTestSDKToolbar::TestToolbarSetDimmedL ),
        ENTRY( "TestToolbarOfferKeyEventL",
                CTestSDKToolbar::TestToolbarOfferKeyEventL ),
        ENTRY( "TestToolbarInputCapabilities",
                CTestSDKToolbar::TestToolbarInputCapabilitiesL ),
        ENTRY( "TestToolbarDraw", CTestSDKToolbar::TestToolbarDrawL ),
        ENTRY( "TestToolbarControlOrNull",
                CTestSDKToolbar::TestToolbarControlOrNullL ),
        ENTRY( "TestToolbarSetToolbarVisibility",
                CTestSDKToolbar::TestToolbarSetToolbarVisibilityL ),
        ENTRY( "TestToolbarSetItemDimmed",
                CTestSDKToolbar::TestToolbarSetItemDimmedL ),
        ENTRY( "TestToolbarHideItem",
                CTestSDKToolbar::TestToolbarHideItemL ),
        ENTRY( "TestToolbarSetToolbarObserver",
                CTestSDKToolbar::TestToolbarSetToolbarObserverL ),
        ENTRY( "TestToolbarToolbarObserver",
                CTestSDKToolbar::TestToolbarToolbarObserverL ),
        ENTRY( "TestToolbarAddItemL", CTestSDKToolbar::TestToolbarAddItemL ),
        ENTRY( "TestToolbarRemoveItem", CTestSDKToolbar::TestToolbarRemoveItemL ),
        ENTRY( "TestToolbarIsSupportedItemType",
                CTestSDKToolbar::TestToolbarIsSupportedItemTypeL ),
        ENTRY( "TestToolbarSetInitialFocusedItem",
                CTestSDKToolbar::TestToolbarSetInitialFocusedItemL ),
        ENTRY( "TestToolbarSetEmphasis",
                CTestSDKToolbar::TestToolbarSetEmphasisL ),
        ENTRY( "TestToolbarIsShown", CTestSDKToolbar::TestToolbarIsShownL ),
        ENTRY( "TestToolbarSetWithSliding",
                CTestSDKToolbar::TestToolbarSetWithSlidingL ),
        ENTRY( "TestToolbarSetCloseOnCommand",
                CTestSDKToolbar::TestToolbarSetCloseOnCommandL ),
        ENTRY( "TestToolbarSetCloseOnAllCommands",
                CTestSDKToolbar::TestToolbarSetCloseOnAllCommandsL ),
        ENTRY( "TestToolbarSetOrientation",
                CTestSDKToolbar::TestToolbarSetOrientationL ),
        ENTRY( "TestToolbarUpdateBackground",
                CTestSDKToolbar::TestToolbarUpdateBackgroundL ),
        ENTRY( "TestToolbarDisableToolbarL",
                CTestSDKToolbar::TestToolbarDisableToolbarL ),
        ENTRY( "TestToolbarIsToolbarDisabled",
                CTestSDKToolbar::TestToolbarIsToolbarDisabledL ),
        ENTRY( "TestToolbarSetFocusedItemL",
                CTestSDKToolbar::TestToolbarSetFocusedItemL ),
        ENTRY( "TestToolbarFocusedItem",
                CTestSDKToolbar::TestToolbarFocusedItemL ),
        ENTRY( "TestToolbarEventModifiers",
                CTestSDKToolbar::TestToolbarEventModifiersL ),
        ENTRY( "TestToolbarToolbarFlags",
                CTestSDKToolbar::TestToolbarToolbarFlagsL ),
        ENTRY( "TestToolbarSetSoftkeyResourceIdL",
                CTestSDKToolbar::TestToolbarSetSoftkeyResourceIdL ),
        ENTRY( "TestToolbarToolbarExtension",
                CTestSDKToolbar::TestToolbarToolbarExtensionL ),
        ENTRY( "TestToolbarHideItemsAndDrawOnlyBackground",
                CTestSDKToolbar::TestToolbarHideItemsAndDrawOnlyBackgroundL ),
        ENTRY( "TestToolbarSizeChanged",
                CTestSDKToolbar::TestToolbarSizeChangedL ),
        ENTRY( "TestToolbarFocusChanged",
                CTestSDKToolbar::TestToolbarFocusChangedL ),
        ENTRY( "TestToolbarExtensionInterface",
                CTestSDKToolbar::TestToolbarExtensionInterfaceL ),
        ENTRY( "TestToolbarMopSupplyObject",
                CTestSDKToolbar::TestToolbarMopSupplyObjectL ),

        // akntoolbarextension.h
        ENTRY( "TestToolbarExtNewL", CTestSDKToolbar::TestToolbarExtNewL ),
        ENTRY( "TestToolbarExtNewLC", CTestSDKToolbar::TestToolbarExtNewLCL ),
        ENTRY( "TestToolbarExtAddItemL",
                CTestSDKToolbar::TestToolbarExtAddItemL ),
        ENTRY( "TestToolbarExtControlOrNull",
                CTestSDKToolbar::TestToolbarExtControlOrNullL ),
        ENTRY( "TestToolbarExtRemoveItemL",
                CTestSDKToolbar::TestToolbarExtRemoveItemL ),
        ENTRY( "TestToolbarExtSetShown",
                CTestSDKToolbar::TestToolbarExtSetShownL ),
        ENTRY( "TestToolbarExtIsShown", CTestSDKToolbar::TestToolbarExtIsShownL ),
        ENTRY( "TestToolbarExtSetItemDimmed",
                CTestSDKToolbar::TestToolbarExtSetItemDimmedL ),
        ENTRY( "TestToolbarExtHideItemL",
                CTestSDKToolbar::TestToolbarExtHideItemL ),
        ENTRY( "TestToolbarObserverDynInitToolbarL",
                CTestSDKToolbar::TestToolbarObserverDynInitToolbarL ),
        ENTRY( "TestToolbarObserverReserved_1L",
                CTestSDKToolbar::TestToolbarObserverReservedL ),
        ENTRY( "TestToolbarObserverReserved_2L",
                CTestSDKToolbar::TestToolbarObserverReservedTwoL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

//  [End of File]
