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



#ifndef C_TESTSDKSCROLLER_H
#define C_TESTSDKSCROLLER_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KTestSDKScrollerLogPath, "\\logs\\testframework\\testsdkscroller\\" ); 
// Log file
_LIT( KTestSDKScrollerLogFile, "testsdkscroller.txt" ); 
_LIT( KTestSDKScrollerLogFileWithTitle, "testsdkscroller_[%S].txt" );

/**
*  CTestSDKScroller test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKScroller ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKScroller* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKScroller();

public: // Functions from base classes

    /**
    * From CScriptBase Runs a script line.
    * @since S60 5.0
    * @param aItem Script line containing method name and parameters
    * @return Symbian OS error code
    */
    virtual TInt RunMethodL( CStifItemParser& aItem );

private:

    /**
    * C++ default constructor.
    */
    CTestSDKScroller( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // test methods from CAknScrollButton class

    /**
    * test NewL method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKAknScbNewL( CStifItemParser& aItem );

    /**
    * test NewL method with type of scrollbar.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKAknScbNewLWithScBarL( CStifItemParser& aItem );

    /**
    * test Type method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKAknScbTypeL( CStifItemParser& aItem );

    /**
    * test CreateWindowOnlyForArrowsL method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKAknScbCreWinOnlyForArrsL( CStifItemParser& aItem );

    /**
    * test IsNormalScrollBarUsingButton method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKAknScbIsNormalSbUsingButL( CStifItemParser& aItem );

    /**
    * test SetTypeOfScrollBarUsingButton method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKAknScbSetTypeOfSbUsingButL( CStifItemParser& aItem );

    /**
    * test SetPosition method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKAknScbSetPositionL( CStifItemParser& aItem );

private: // test methods from TEikScrollBarFrameLayout class

    /**
    * test default constructor method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmLaDefConsL( CStifItemParser& aItem );

    /**
    * test SetInclusiveMargin method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmLaSetInclusiveMarginL( CStifItemParser& aItem );

    /**
    * test SetClientMargin method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmLaSetClientMarginL( CStifItemParser& aItem );

private: // test methods from CEikScrollBarFrame class

    /**
    * test default constructor method with param.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmDefConsWithPaL( CStifItemParser& aItem );

    /**
    * test DrawScrollBarsNow method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmDrawSbsNowL( CStifItemParser& aItem );

    /**
    * test SetScrollBarVisibilityL method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmSetSbVisibilityL( CStifItemParser& aItem );

    /**
    * test VScrollBarVisibility method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmVSbVisibilityL( CStifItemParser& aItem );

    /**
    * test SetScrollBarFrameObserver method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmSetSbfrmObserverL( CStifItemParser& aItem );

    /**
    * test Tile method with TEikScrollBarModel param only.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmTileL( CStifItemParser& aItem );

    /**
    * test TileL method with TEikScrollBarFrameLayout param.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmTileWithSbfrmLaL( CStifItemParser& aItem );

    /**
    * test MoveThumbsBy method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmMoveThumbsByL( CStifItemParser& aItem );

    /**
    * test MoveHorizThumbTo method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmMoveHThumbToL( CStifItemParser& aItem );

    /**
    * test MoveVertThumbTo method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmMoveVThumbToL( CStifItemParser& aItem );

    /**
    * test SetVFocusPosToThumbPos method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmSetVFocusPosToThumbPosL( CStifItemParser& aItem );

    /**
    * test ScrollBarBreadth method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmSbBreadthL( CStifItemParser& aItem );

    /**
    * test SetAdjustsHorizontalModel method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmSetAdjustsHModelL( CStifItemParser& aItem );

    /**
    * test SetAdjustsVerticalModel method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmSetAdjustsVModelL( CStifItemParser& aItem );

    /**
    * test SetScrollBarFrameFlags method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmSetSbfrmFlagsL( CStifItemParser& aItem );

    /**
    * test ScrollBarExists method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmSbExistsL( CStifItemParser& aItem );

    /**
    * test CountComponentControls method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmCountComCtrlsL( CStifItemParser& aItem );

    /**
    * test ComponentControl method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmComponentControlL( CStifItemParser& aItem );

    /**
    * test GetScrollBarHandle method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmGetSbHandleL( CStifItemParser& aItem );

    /**
    * test VerticalScrollBar method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmVScrollBarL( CStifItemParser& aItem );

    /**
    * test SetTypeOfHScrollBar method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmSetTypeOfHSbL( CStifItemParser& aItem );

    /**
    * test SetTypeOfVScrollBar method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmSetTypeOfVSbL( CStifItemParser& aItem );

    /**
    * test TypeOfHScrollBar method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmTypeOfHSbL( CStifItemParser& aItem );

    /**
    * test TypeOfVScrollBar method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmTypeOfVSbL( CStifItemParser& aItem );

    /**
    * test IsArrowHeadScrollBar method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmIsArrowHeadSbL( CStifItemParser& aItem );

    /**
    * test CreateDoubleSpanScrollBarsL method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmCreDoubleSpanSbsL( CStifItemParser& aItem );

    /**
    * test CreateDoubleSpanScrollBarsL method with ScrollBar param.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmCreDoubleSpanSbsWithSbPaL( CStifItemParser& aItem );

    /**
    * test Tile method with TRect param and no return value.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmTileWithRectL( CStifItemParser& aItem );

    /**
    * test Tile method with TEikScrollBarModel param and no return value.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmTileWithSbModelL( CStifItemParser& aItem );

    /**
    * test ScrollBarVisibility method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmSbVisibilityL( CStifItemParser& aItem );

    /**
    * test DrawBackground method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmDrawBgL( CStifItemParser& aItem );

    /**
    * test DrawBackgroundState method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKSbFrmDrawBgStateL( CStifItemParser& aItem );

private: // test methods from CEikScrollButton class

    /**
    * test default constructor method with param.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikScbDefConsWithPaL( CStifItemParser& aItem );

    /**
    * test Type method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikScbTypeL( CStifItemParser& aItem );

    /**
    * test HandlePointerEventL method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikScbHanPoiEveL( CStifItemParser& aItem );

private: // test methods from CEikArrowHeadScrollButton class

    /**
    * test NewL method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikAhSbNewL( CStifItemParser& aItem );

private: // test methods from TEikScrollBarModel class

    /**
    * test default constructor method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbmDefConsL( CStifItemParser& aItem );

    /**
    * test default constructor method with param.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbmDefConsWithPaL( CStifItemParser& aItem );

    /**
    * test equals operator method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbmEquOpaL( CStifItemParser& aItem );

    /**
    * test not equals operator method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbmNotEquOpaL( CStifItemParser& aItem );

    /**
    * test ScrollBarUseful method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbmSbUsefulL( CStifItemParser& aItem );

    /**
    * test MaxThumbPos method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbmMaxThumbPosL( CStifItemParser& aItem );

    /**
    * test CheckBounds method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbmCheckBoundsL( CStifItemParser& aItem );

private: // test methods from TAknDoubleSpanScrollBarModel class

    /**
    * test default constructor method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDsModelDefConsL( CStifItemParser& aItem );

    /**
    * test default constructor method with param.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDsModelDefConsWithPaL( CStifItemParser& aItem );

    /**
    * test SetScrollSpan method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDsModelSetScrollSpanL( CStifItemParser& aItem );

    /**
    * test SetFocusPosition method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDsModelSetFocusPosL( CStifItemParser& aItem );

    /**
    * test SetWindowSize method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDsModelSetWinSizeL( CStifItemParser& aItem );

    /**
    * test SetFieldSize method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDsModelSetFieldSizeL( CStifItemParser& aItem );

    /**
    * test SetFieldPosition method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDsModelSetFieldPosL( CStifItemParser& aItem );

    /**
    * test ScrollSpan method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDsModelScrollSpanL( CStifItemParser& aItem );

    /**
    * test FocusPosition method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDsModelFocusPosL( CStifItemParser& aItem );

    /**
    * test WindowSize method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDsModelWinSizeL( CStifItemParser& aItem );

    /**
    * test FieldSize method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDsModelFieldSizeL( CStifItemParser& aItem );

    /**
    * test FieldPosition method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDsModelFieldPosL( CStifItemParser& aItem );

private: // test methods from CEikScrollBar class

    /**
    * test default constructor method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbDefConsL( CStifItemParser& aItem );

    /**
    * test ConstructL method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbConstructL( CStifItemParser& aItem );

    /**
    * test SetLengthL method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbSetLengthL( CStifItemParser& aItem );

    /**
    * test SetModelL method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbSetModelL( CStifItemParser& aItem );

    /**
    * test SetModel method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbSetModeL( CStifItemParser& aItem );

    /**
    * test SetLengthAndModelL method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbSetLenAndModL( CStifItemParser& aItem );

    /**
    * test SetModelThumbPosition method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbSetModThuPosL( CStifItemParser& aItem );

    /**
    * test SetFocusPosToThumbPos method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbSetFoPosToThPosL( CStifItemParser& aItem );

    /**
    * test DefaultScrollBarBreadth method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbDefSbBreadth( CStifItemParser& aItem );

    /**
    * test Model method with point return value.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbPoModelL( CStifItemParser& aItem );

    /**
    * test ThumbPosition method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbThumbPosL( CStifItemParser& aItem );

    /**
    * test ScrollBarBreadth method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbScBarBreaL( CStifItemParser& aItem );

    /**
    * test MinVisibleLength method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbMinVisLen( CStifItemParser& aItem );

    /**
    * test SetDecreaseButtonsDimmed method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbSetDecButDimmedL( CStifItemParser& aItem );

    /**
    * test SetIncreaseButtonsDimmed method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbSetIncButDimmedL( CStifItemParser& aItem );

    /**
    * test SetAllButtonsDimmed method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbSetAllButDimmedL( CStifItemParser& aItem );

    /**
    * test IncreaseNudgeButton method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbIncNudgeButL( CStifItemParser& aItem );

    /**
    * test DecreaseNudgeButton method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbDecNudgeButL( CStifItemParser& aItem );

    /**
    * test SetContainingCba method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbSetContCbaL( CStifItemParser& aItem );

    /**
    * test MakeVisible method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbMakeVisibleL( CStifItemParser& aItem );

    /**
    * test HandlePointerEventL method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbHanPointEveL( CStifItemParser& aItem );

    /**
    * test ComponentControl method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbCompCtrlL( CStifItemParser& aItem );

    /**
    * test CountComponentControls method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbCountCompCtrlsL( CStifItemParser& aItem );

    /**
    * test SetButtonPositionL method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbSetButPosL( CStifItemParser& aItem );

    /**
    * test SetExtensionAreaType method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKEikSbSetExtensionAreaTypeL( CStifItemParser& aItem );

private: // test methods from CEikArrowHeadScrollBar class

    /**
    * test default constructor method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKArrHeSbDefConsL( CStifItemParser& aItem );

    /**
    * test ConstructL method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKArrHeSbConstructL( CStifItemParser& aItem );

    /**
    * test HandlePointerEventL method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKArrHeSbHanPointEveL( CStifItemParser& aItem );

private: // test methods from CAknDoubleSpanScrollBar class

    /**
    * test default constructor method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDbSpaSbDefConsL( CStifItemParser& aItem );

    /**
    * test SetFixedLayoutRect method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDbSpaSbSetFlRectL( CStifItemParser& aItem );

    /**
    * test ConstructL method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDbSpaSbConstructL( CStifItemParser& aItem );

    /**
    * test SetScrollPopupInfoTextL method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDbSpaSbSetSpInfoTextL( CStifItemParser& aItem );

    /**
    * test ConstructL method derived from CEikScrollBar.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDbSpaSbConstructExtL( CStifItemParser& aItem );

    /**
    * test MakeVisible method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDbSpaSbMakeVisibleL( CStifItemParser& aItem );

    /**
    * test HandlePointerEventL method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDbSpaSbHanPointEveL( CStifItemParser& aItem );

    /**
    * test ComponentControl method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDbSpaSbCompCtrlL( CStifItemParser& aItem );

    /**
    * test CountComponentControls method.
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSDKDbSpaSbCountCompCtrlsL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    };

#endif      // C_TESTSDKSCROLLER_H

// End of File
