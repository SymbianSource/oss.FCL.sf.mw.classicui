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



#ifndef C_TESTSDKTOOLBAR_H
#define C_TESTSDKTOOLBAR_H

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
_LIT( KTestSDKToolbarLogPath, "\\logs\\testframework\\testsdktoolbar\\" ); 
// Log file
_LIT( KTestSDKToolbarLogFile, "testsdktoolbar.txt" ); 
_LIT( KTestSDKToolbarLogFileWithTitle, "testsdktoolbar_[%S].txt" );

/**
*  CTestSDKToolbar test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKToolbar ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKToolbar* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKToolbar();

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
    CTestSDKToolbar( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // Test Methods in akntoolbar.h

    /**
    * test NewL function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarNewL( CStifItemParser& aItem );

    /**
    * test NewLC function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarNewLCL( CStifItemParser& aItem );

    /**
    * test CountComponentControls function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarCountComponentControlsL( CStifItemParser& aItem );

    /**
    * test ComponentControl function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarComponentControlL( CStifItemParser& aItem );

    /**
    * test HandlePointerEventL function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarHandlePointerEventL( CStifItemParser& aItem );

    /**
    * test HandleResourceChange function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarHandleResourceChangeL( CStifItemParser& aItem );

    /**
    * test HandleControlEventL function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarHandleControlEventL( CStifItemParser& aItem );

    /**
    * test PositionChanged function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarPositionChangedL( CStifItemParser& aItem );

    /**
    * test ProcessCommandL function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarProcessCommandL( CStifItemParser& aItem );

    /**
    * test SetDimmed function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarSetDimmedL( CStifItemParser& aItem );

    /**
    * test OfferKeyEventL function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarOfferKeyEventL( CStifItemParser& aItem );

    /**
    * test InputCapabilities function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarInputCapabilitiesL( CStifItemParser& aItem );

    /**
    * test Draw function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarDrawL( CStifItemParser& aItem );

    /**
    * test ControlOrNull function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarControlOrNullL( CStifItemParser& aItem );

    /**
    * test SetToolbarVisibility function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarSetToolbarVisibilityL( CStifItemParser& aItem );

    /**
    * test SetItemDimmed function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarSetItemDimmedL( CStifItemParser& aItem );

    /**
    * test HideItem function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarHideItemL( CStifItemParser& aItem );

    /**
    * test SetToolbarObserver function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarSetToolbarObserverL( CStifItemParser& aItem );

    /**
    * test ToolbarObserver function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarToolbarObserverL( CStifItemParser& aItem );

    /**
    * test AddItemL function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarAddItemL( CStifItemParser& aItem );

    /**
    * test RemoveItem function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarRemoveItemL( CStifItemParser& aItem );

    /**
    * test IsSupportedItemType function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarIsSupportedItemTypeL( CStifItemParser& aItem );

    /**
    * test SetInitialFocusedItem function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarSetInitialFocusedItemL( CStifItemParser& aItem );

    /**
    * test SetEmphasis function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarSetEmphasisL( CStifItemParser& aItem );

    /**
    * test IsShown function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarIsShownL( CStifItemParser& aItem );

    /**
    * test SetWithSliding function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarSetWithSlidingL( CStifItemParser& aItem );

    /**
    * test SetCloseOnCommand function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarSetCloseOnCommandL( CStifItemParser& aItem );

    /**
    * test SetCloseOnAllCommands function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarSetCloseOnAllCommandsL( CStifItemParser& aItem );

    /**
    * test SetOrientation function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarSetOrientationL( CStifItemParser& aItem );

    /**
    * test UpdateBackground function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarUpdateBackgroundL( CStifItemParser& aItem );

    /**
    * test DisableToolbarL function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarDisableToolbarL( CStifItemParser& aItem );

    /**
    * test IsToolbarDisabled function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarIsToolbarDisabledL( CStifItemParser& aItem );

    /**
    * test SetFocusedItemL function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarSetFocusedItemL( CStifItemParser& aItem );

    /**
    * test FocusedItem function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarFocusedItemL( CStifItemParser& aItem );

    /**
    * test EventModifiers function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarEventModifiersL( CStifItemParser& aItem );

    /**
    * test ToolbarFlags function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarToolbarFlagsL( CStifItemParser& aItem );

    /**
    * test SetSoftkeyResourceIdL function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarSetSoftkeyResourceIdL( CStifItemParser& aItem );

    /**
    * test ToolbarExtension function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarToolbarExtensionL( CStifItemParser& aItem );

    /**
    * test HideItemsAndDrawOnlyBackground function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarHideItemsAndDrawOnlyBackgroundL( CStifItemParser& aItem );

    /**
    * test SizeChanged function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarSizeChangedL( CStifItemParser& aItem );

    /**
    * test FocusChanged function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarFocusChangedL( CStifItemParser& aItem );

    /**
    * test ExtensionInterface function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarExtensionInterfaceL( CStifItemParser& aItem );

    /**
    * test MopSupplyObject function of AknToolbar
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarMopSupplyObjectL( CStifItemParser& aItem );

private: // Test Methods in akntoolbarextension.h

    /**
    * test NewL function of AknToolbarExtension
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarExtNewL( CStifItemParser& aItem );

    /**
    * test NewLC function of AknToolbarExtension
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarExtNewLCL( CStifItemParser& aItem );

    /**
    * test AddItemL function of AknToolbarExtension
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarExtAddItemL( CStifItemParser& aItem );

    /**
    * test ControlOrNull function of AknToolbarExtension
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarExtControlOrNullL( CStifItemParser& aItem );

    /**
    * test RemoveItemL function of AknToolbarExtension
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarExtRemoveItemL( CStifItemParser& aItem );

    /**
    * test SetShown function of AknToolbarExtension
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarExtSetShownL( CStifItemParser& aItem );

    /**
    * test IsShown function of AknToolbarExtension
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarExtIsShownL( CStifItemParser& aItem );

    /**
    * test SetItemDimmed function of AknToolbarExtension
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarExtSetItemDimmedL( CStifItemParser& aItem );

    /**
    * test HideItemL function of AknToolbarExtension
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarExtHideItemL( CStifItemParser& aItem );

private: // Test Methods in akntoolbarobserver.h

    /**
    * test DynInitToolbarL function of AknToolbarObserver
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarObserverDynInitToolbarL( CStifItemParser& aItem );

    /**
    * test DynInitToolbarL function of AknToolbarObserver
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarObserverReservedL( CStifItemParser& aItem );

    /**
    * test DynInitToolbarL function of AknToolbarObserver
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestToolbarObserverReservedTwoL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKTOOLBAR_H

// End of File
