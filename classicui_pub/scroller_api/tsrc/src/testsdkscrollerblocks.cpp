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
* Description:  test aknscbut.h, eiksbfrm.h, eikscbut.h and eikscrlb.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkscroller.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKScroller::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 


        /**
         *  test funcitons in aknscbut.h
         */
        ENTRY( "TestSDKAknScbNewL", CTestSDKScroller::TestSDKAknScbNewL ),
        ENTRY( "TestSDKAknScbNewLWithScBarL",
                CTestSDKScroller::TestSDKAknScbNewLWithScBarL ),
        ENTRY( "TestSDKAknScbType", CTestSDKScroller::TestSDKAknScbTypeL ),
        ENTRY( "TestSDKAknScbCreWinOnlyForArrsL",
                CTestSDKScroller::TestSDKAknScbCreWinOnlyForArrsL ),
        ENTRY( "TestSDKAknScbIsNormalSbUsingBut",
                CTestSDKScroller::TestSDKAknScbIsNormalSbUsingButL ),
        ENTRY( "TestSDKAknScbSetTypeOfSbUsingBut",
                CTestSDKScroller::TestSDKAknScbSetTypeOfSbUsingButL ),
        ENTRY( "TestSDKAknScbSetPosition",
                CTestSDKScroller::TestSDKAknScbSetPositionL ),


        /**
         *  test functions in eiksbfrm.h
         */

        // methods of TEikScrollBarFrameLayout class
        ENTRY( "TestSDKSbFrmLaDefCons", CTestSDKScroller::TestSDKSbFrmLaDefConsL ),
        ENTRY( "TestSDKSbFrmLaSetInclusiveMargin",
                CTestSDKScroller::TestSDKSbFrmLaSetInclusiveMarginL ),
        ENTRY( "TestSDKSbFrmLaSetClientMargin",
                CTestSDKScroller::TestSDKSbFrmLaSetClientMarginL ),

        // methods of TEikScrollBarFrame class
        ENTRY( "TestSDKSbFrmDefConsWithPa",
                CTestSDKScroller::TestSDKSbFrmDefConsWithPaL ),
        ENTRY( "TestSDKSbFrmDrawSbsNow",
                CTestSDKScroller::TestSDKSbFrmDrawSbsNowL ),
        ENTRY( "TestSDKSbFrmSetSbVisibilityL",
                CTestSDKScroller::TestSDKSbFrmSetSbVisibilityL ),
        ENTRY( "TestSDKSbFrmVSbVisibilityL",
                CTestSDKScroller::TestSDKSbFrmVSbVisibilityL ),
        ENTRY( "TestSDKSbFrmSetSbfrmObserverL",
                CTestSDKScroller::TestSDKSbFrmSetSbfrmObserverL ),
        ENTRY( "TestSDKSbFrmTile", CTestSDKScroller::TestSDKSbFrmTileL ),
        ENTRY( "TestSDKSbFrmTileWithSbfrmLa",
                CTestSDKScroller::TestSDKSbFrmTileWithSbfrmLaL ),
        ENTRY( "TestSDKSbFrmMoveThumbsBy",
                CTestSDKScroller::TestSDKSbFrmMoveThumbsByL ),
        ENTRY( "TestSDKSbFrmMoveHThumbTo",
                CTestSDKScroller::TestSDKSbFrmMoveHThumbToL ),
        ENTRY( "TestSDKSbFrmMoveVThumbTo",
                CTestSDKScroller::TestSDKSbFrmMoveVThumbToL ),
        ENTRY( "TestSDKSbFrmSetVFocusPosToThumbPos", 
                CTestSDKScroller::TestSDKSbFrmSetVFocusPosToThumbPosL ),
        ENTRY( "TestSDKSbFrmSbBreadth", CTestSDKScroller::TestSDKSbFrmSbBreadthL ),
        ENTRY( "TestSDKSbFrmSetAdjustsHModel",
                CTestSDKScroller::TestSDKSbFrmSetAdjustsHModelL ),
        ENTRY( "TestSDKSbFrmSetAdjustsVModel",
                CTestSDKScroller::TestSDKSbFrmSetAdjustsVModelL ),
        ENTRY( "TestSDKSbFrmSetSbfrmFlags",
                CTestSDKScroller::TestSDKSbFrmSetSbfrmFlagsL ),
        ENTRY( "TestSDKSbFrmSbExists", CTestSDKScroller::TestSDKSbFrmSbExistsL ),
        ENTRY( "TestSDKSbFrmCountComCtrls",
                CTestSDKScroller::TestSDKSbFrmCountComCtrlsL ),
        ENTRY( "TestSDKSbFrmComponentControl",
                CTestSDKScroller::TestSDKSbFrmComponentControlL ),
        ENTRY( "TestSDKSbFrmGetSbHandle",
                CTestSDKScroller::TestSDKSbFrmGetSbHandleL ),
        ENTRY( "TestSDKSbFrmVScrollBar",
                CTestSDKScroller::TestSDKSbFrmVScrollBarL ),
        ENTRY( "TestSDKSbFrmSetTypeOfHSb",
                CTestSDKScroller::TestSDKSbFrmSetTypeOfHSbL ),
        ENTRY( "TestSDKSbFrmSetTypeOfVSb",
                CTestSDKScroller::TestSDKSbFrmSetTypeOfVSbL ),
        ENTRY( "TestSDKSbFrmTypeOfHSb", CTestSDKScroller::TestSDKSbFrmTypeOfHSbL ),
        ENTRY( "TestSDKSbFrmTypeOfVSb", CTestSDKScroller::TestSDKSbFrmTypeOfVSbL ),
        ENTRY( "TestSDKSbFrmIsArrowHeadSb",
                CTestSDKScroller::TestSDKSbFrmIsArrowHeadSbL ),
        ENTRY( "TestSDKSbFrmCreDoubleSpanSbsL",
                CTestSDKScroller::TestSDKSbFrmCreDoubleSpanSbsL ),
        ENTRY( "TestSDKSbFrmCreDoubleSpanSbsWithSbPaL",
                CTestSDKScroller::TestSDKSbFrmCreDoubleSpanSbsWithSbPaL ),
        ENTRY( "TestSDKSbFrmTileWithRect",
                CTestSDKScroller::TestSDKSbFrmTileWithRectL ),
        ENTRY( "TestSDKSbFrmTileWithSbModel",
                CTestSDKScroller::TestSDKSbFrmTileWithSbModelL ),
        ENTRY( "TestSDKSbFrmSbVisibility",
                CTestSDKScroller::TestSDKSbFrmSbVisibilityL ),
        ENTRY( "TestSDKSbFrmDrawBg", CTestSDKScroller::TestSDKSbFrmDrawBgL ),
        ENTRY( "TestSDKSbFrmDrawBgState",
                CTestSDKScroller::TestSDKSbFrmDrawBgStateL ),


        /**
         *  test functions in eikscbut.h
         */

        // methods of CEikScrollButton class
        ENTRY( "TestSDKEikScbDefConsWithPa",
                CTestSDKScroller::TestSDKEikScbDefConsWithPaL ),
        ENTRY( "TestSDKEikScbType", CTestSDKScroller::TestSDKEikScbTypeL ),
        ENTRY( "TestSDKEikScbHanPoiEveL",
                CTestSDKScroller::TestSDKEikScbHanPoiEveL ),

        // methods of CEikArrowHeadScrollButton class
        ENTRY( "TestSDKEikAhSbNewL", CTestSDKScroller::TestSDKEikAhSbNewL ),


        /**
         *  test functions in eiksbfrm.h
         */

        // methods of TEikScrollBarModel class
        ENTRY( "TestSDKEikSbmDefCons", CTestSDKScroller::TestSDKEikSbmDefConsL ),
        ENTRY( "TestSDKEikSbmDefConsWithPa",
                CTestSDKScroller::TestSDKEikSbmDefConsWithPaL ),
        ENTRY( "TestSDKEikSbmEquOpa", CTestSDKScroller::TestSDKEikSbmEquOpaL ),
        ENTRY( "TestSDKEikSbmNotEquOpa",
                CTestSDKScroller::TestSDKEikSbmNotEquOpaL ),
        ENTRY( "TestSDKEikSbmSbUseful", CTestSDKScroller::TestSDKEikSbmSbUsefulL ),
        ENTRY( "TestSDKEikSbmMaxThumbPos",
                CTestSDKScroller::TestSDKEikSbmMaxThumbPosL ),
        ENTRY( "TestSDKEikSbmCheckBounds",
                CTestSDKScroller::TestSDKEikSbmCheckBoundsL ),

        // methods of TAknDoubleSpanScrollBarModel class
        ENTRY( "TestSDKDsModelDefCons", CTestSDKScroller::TestSDKDsModelDefConsL ),
        ENTRY( "TestSDKDsModelDefConsWithPa",
                CTestSDKScroller::TestSDKDsModelDefConsWithPaL ),
        ENTRY( "TestSDKDsModelSetScrollSpan",
                CTestSDKScroller::TestSDKDsModelSetScrollSpanL ),
        ENTRY( "TestSDKDsModelSetFocusPos",
                CTestSDKScroller::TestSDKDsModelSetFocusPosL ),
        ENTRY( "TestSDKDsModelSetWinSize",
                CTestSDKScroller::TestSDKDsModelSetWinSizeL ),
        ENTRY( "TestSDKDsModelSetFieldSize",
                CTestSDKScroller::TestSDKDsModelSetFieldSizeL ),
        ENTRY( "TestSDKDsModelSetFieldPos",
                CTestSDKScroller::TestSDKDsModelSetFieldPosL ),
        ENTRY( "TestSDKDsModelScrollSpan",
                CTestSDKScroller::TestSDKDsModelScrollSpanL ),
        ENTRY( "TestSDKDsModelFocusPos",
                CTestSDKScroller::TestSDKDsModelFocusPosL ),
        ENTRY( "TestSDKDsModelWinSize", CTestSDKScroller::TestSDKDsModelWinSizeL ),
        ENTRY( "TestSDKDsModelFieldSize",
                CTestSDKScroller::TestSDKDsModelFieldSizeL ),
        ENTRY( "TestSDKDsModelFieldPos",
                CTestSDKScroller::TestSDKDsModelFieldPosL ),

        // methods of CEikScrollBar class
        ENTRY( "TestSDKEikSbDefCons", CTestSDKScroller::TestSDKEikSbDefConsL ),
        ENTRY( "TestSDKEikSbConstructL",
                CTestSDKScroller::TestSDKEikSbConstructL ),
        ENTRY( "TestSDKEikSbSetLengthL",
                CTestSDKScroller::TestSDKEikSbSetLengthL ),
        ENTRY( "TestSDKEikSbSetModelL", CTestSDKScroller::TestSDKEikSbSetModelL ),
        ENTRY( "TestSDKEikSbSetModel", CTestSDKScroller::TestSDKEikSbSetModeL ),
        ENTRY( "TestSDKEikSbSetLenAndModL",
                CTestSDKScroller::TestSDKEikSbSetLenAndModL ),
        ENTRY( "TestSDKEikSbSetModThuPos",
                CTestSDKScroller::TestSDKEikSbSetModThuPosL ),
        ENTRY( "TestSDKEikSbSetFoPosToThPos",
                CTestSDKScroller::TestSDKEikSbSetFoPosToThPosL ),
        ENTRY( "TestSDKEikSbDefSbBreadth",
                CTestSDKScroller::TestSDKEikSbDefSbBreadth ),
        ENTRY( "TestSDKEikSbPoModel", CTestSDKScroller::TestSDKEikSbPoModelL ),
        ENTRY( "TestSDKEikSbThumbPos", CTestSDKScroller::TestSDKEikSbThumbPosL ),
        ENTRY( "TestSDKEikSbScBarBrea", CTestSDKScroller::TestSDKEikSbScBarBreaL ),
        ENTRY( "TestSDKEikSbMinVisLen", CTestSDKScroller::TestSDKEikSbMinVisLen ),
        ENTRY( "TestSDKEikSbSetDecButDimmed",
                CTestSDKScroller::TestSDKEikSbSetDecButDimmedL ),
        ENTRY( "TestSDKEikSbSetIncButDimmed",
                CTestSDKScroller::TestSDKEikSbSetIncButDimmedL ),
        ENTRY( "TestSDKEikSbSetAllButDimmed",
                CTestSDKScroller::TestSDKEikSbSetAllButDimmedL ),
        ENTRY( "TestSDKEikSbIncNudgeBut",
                CTestSDKScroller::TestSDKEikSbIncNudgeButL ),
        ENTRY( "TestSDKEikSbDecNudgeBut",
                CTestSDKScroller::TestSDKEikSbDecNudgeButL ),
        ENTRY( "TestSDKEikSbSetContCba",
                CTestSDKScroller::TestSDKEikSbSetContCbaL ),
        ENTRY( "TestSDKEikSbMakeVisible",
                CTestSDKScroller::TestSDKEikSbMakeVisibleL ),
        ENTRY( "TestSDKEikSbHanPointEveL",
                CTestSDKScroller::TestSDKEikSbHanPointEveL ),
        ENTRY( "TestSDKEikSbCompCtrl", CTestSDKScroller::TestSDKEikSbCompCtrlL ),
        ENTRY( "TestSDKEikSbCountCompCtrls",
                CTestSDKScroller::TestSDKEikSbCountCompCtrlsL ),
        ENTRY( "TestSDKEikSbSetButPosL", CTestSDKScroller::TestSDKEikSbSetButPosL ),
        ENTRY( "TestSDKEikSbSetExtensionAreaTypeL",
                CTestSDKScroller::TestSDKEikSbSetExtensionAreaTypeL ),

        // methods of CEikArrowHeadScrollBar class
        ENTRY( "TestSDKArrHeSbDefCons", CTestSDKScroller::TestSDKArrHeSbDefConsL ),
        ENTRY( "TestSDKArrHeSbConstructL",
                CTestSDKScroller::TestSDKArrHeSbConstructL ),
        ENTRY( "TestSDKArrHeSbHanPointEveL",
                CTestSDKScroller::TestSDKArrHeSbHanPointEveL ),

        // methods of CAknDoubleSpanScrollBar class
        ENTRY( "TestSDKDbSpaSbDefCons", CTestSDKScroller::TestSDKDbSpaSbDefConsL ),
        ENTRY( "TestSDKDbSpaSbSetFlRect",
                CTestSDKScroller::TestSDKDbSpaSbSetFlRectL ),
        ENTRY( "TestSDKDbSpaSbConstructL",
                CTestSDKScroller::TestSDKDbSpaSbConstructL ),
        ENTRY( "TestSDKDbSpaSbSetSpInfoTextL",
                CTestSDKScroller::TestSDKDbSpaSbSetSpInfoTextL ),
        ENTRY( "TestSDKDbSpaSbConstructExtL",
                CTestSDKScroller::TestSDKDbSpaSbConstructExtL ),
        ENTRY( "TestSDKDbSpaSbMakeVisible",
                CTestSDKScroller::TestSDKDbSpaSbMakeVisibleL ),
        ENTRY( "TestSDKDbSpaSbHanPointEveL",
                CTestSDKScroller::TestSDKDbSpaSbHanPointEveL ),
        ENTRY( "TestSDKDbSpaSbCompCtrl",
                CTestSDKScroller::TestSDKDbSpaSbCompCtrlL ),
        ENTRY( "TestSDKDbSpaSbCountCompCtrls",
                CTestSDKScroller::TestSDKDbSpaSbCountCompCtrlsL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


//  [End of File]
