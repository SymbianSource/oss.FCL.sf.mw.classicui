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
#ifndef C_TESTSDKOPTIONSMENU_H
#define C_TESTSDKOPTIONSMENU_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <eikmenub.h>
#include <eikmenup.h>
#include <eikenv.h>
#include <coecntrl.h>
#include <eikmobs.h>
#include <coeaui.h>
#include <eikmenub.h>
#include <eikmenup.h>
#include <eikenv.h>
#include <eikon.hrh>
#include <eikbutb.h> 
#include <eikdialg.h> 
#include <coemop.h>
#include <e32cmn.h>

#include "testsdkoptionsmenucontainer.h"
#include "testoptionsmenu.h"

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkoptionsmenuLogPath, "\\logs\\testframework\\testsdkoptionsmenu\\" );
// Log file
_LIT( KtestsdkoptionsmenuLogFile, "testsdkoptionsmenu.txt" );
_LIT( KtestsdkoptionsmenuLogFileWithTitle, "testsdkoptionsmenu_[%S].txt" );

/**
 *  Ctestsdkoptionsmenu test class for STIF Test Framework TestScripter.
 *  @since S60 5.0
 */
NONSHARABLE_CLASS( CTestSDKOptionsMenu ) : public CScriptBase 

    {
public: // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKOptionsMenu* NewL( CTestModuleIf& aTestModuleIf );

    /**
     * Destructor.
    */
    virtual ~CTestSDKOptionsMenu();

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
    CTestSDKOptionsMenu( CTestModuleIf& aTestModuleIf );

    /**
     * ConstructL
     * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
    * Method used to log version of test class
    */
    void SendTestClassVersion();

private: // Test EikMenuB.h
    /**
    * TestMBCEikMenuBarTitleL test function of class CEikMenuBarTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestMBTCEikMenuBarTitleL( CStifItemParser& aItem );

    /**
    * TestMBTSetIconLL test SetIconL of class CEikMenuBarTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
	virtual TInt TestMBTSetIconL( CStifItemParser& aItem );
    /**
    * TestMBSetBitmapsOwnedExternallyL test function of class CEikMenuBarTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
	virtual TInt TestMBTSetBitmapsOwnedExternallyL( CStifItemParser& aItem );
    /**
    * TestMBDrawIconL test function of class CEikMenuBarTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
	virtual TInt TestMBTDrawIconL( CStifItemParser& aItem );
    /**
    * TestMBCreateIconL test function of class CEikMenuBarTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
	virtual TInt TestMBTCreateIconL( CStifItemParser& aItem );
    /**
    * TestMBTSetIconLBitmapL test of class CEikMenuBarTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
	virtual TInt TestMBTSetIconBitmapL( CStifItemParser& aItem );
    /**
    * TestMBTSetIconLMaskL test of class CEikMenuBarTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
	virtual TInt TestMBTSetIconMaskL( CStifItemParser& aItem );

    /**
    * TestMBIconBitmapL test function of class CEikMenuBarTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
	virtual TInt TestMBTIconBitmapL( CStifItemParser& aItem );

    /**
    * TestMBIconMaskL test function of class CEikMenuBarTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
	virtual TInt TestMBTIconMaskL( CStifItemParser& aItem );
    /**
    * TestMBCEikMenuBarL test function of class CEikMenuBarTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
	virtual TInt TestMBCEikMenuBarL( CStifItemParser& aItem );

    /**
    * TestMBOfferKeyEventL test function of CEikMenuBar for in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
	virtual TInt TestMBOfferKeyEventL( CStifItemParser& aItem );

    /**
    * TestMBHandlePointerEventL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
	virtual TInt TestMBHandlePointerEventL( CStifItemParser& aItem );

    /**
    * TestMBDraw test function of class CEikMenuBar for in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
	virtual TInt TestMBDraw( CStifItemParser& aItem );

    /**
    * TestMBCTitleArrayL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestMBTACTitleArrayL( CStifItemParser& aItem );
    /**
     * TestMBAddTitleL test function of class CEikMenuBar in EikMenuB.h
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMBTAAddTitleL( CStifItemParser& aItem );

    /**
    * TestMBConstructL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestMBConstructL( CStifItemParser& aItem );

    /**
    * TestMBConstructFromResourceL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBConstructFromResourceL( CStifItemParser& aItem );
    
    /**
    * TestMBChangeMenuBarL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBChangeMenuBarL( CStifItemParser& aItem );
    
    /**
    * TestMBChangeMenuBarL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBSetHotKeyTableL( CStifItemParser& aItem );
    
    /**
    * TestMBSetMenuTitleResourceIdL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBSetMenuTitleResourceIdL( CStifItemParser& aItem );
    
    /**
    * TestMBSetContextMenuTitleResourceIdL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBSetContextMenuTitleResourceIdL( CStifItemParser& aItem );
    
    /**
    * TestMBSetMenuTitleArrayL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBSetMenuTitleArrayL( CStifItemParser& aItem );
    
    /**
    * TestMBSetTitleArrayOwnedExternallyL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBSetTitleArrayOwnedExternallyL( CStifItemParser& aItem );
    
    /**
    * TestMBSetMenuCursorL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBSetMenuCursorL( CStifItemParser& aItem );
    
    /**
    * TestMBStopDisplayingMenuBarL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBStopDisplayingMenuBarL( CStifItemParser& aItem );
    
    /**
    * TestMBTryDisplayMenuBarL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBTryDisplayMenuBarL( CStifItemParser& aItem );
    
    /**
    * TestMBTryDisplayContextMenuBarL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBTryDisplayContextMenuBarL( CStifItemParser& aItem );
    
    /**
    * TestMBTryDisplayMenuBarWithoutFepMenusL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBTryDisplayMenuBarWithoutFepMenusL( CStifItemParser& aItem );
    
    /**
    * TestMBMoveHighlightToL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBMoveHighlightToL( CStifItemParser& aItem );
    
    /**
    * TestMBDrawItemL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBDrawItemL( CStifItemParser& aItem );
    
    /**
    * TestMBSelectedTitleL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBSelectedTitleL( CStifItemParser& aItem );
    
    /**
    * TestMBSelectedItemL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBSelectedItemL( CStifItemParser& aItem );
    
    /**
    * TestMBFindCommandIdInResourceL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBFindCommandIdInResourceL( CStifItemParser& aItem );
    
    /**
    * TestMBMenuPaneL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBMenuPaneL( CStifItemParser& aItem );
    
    /**
    * TestMBReduceRectL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBReduceRectL( CStifItemParser& aItem );
    
    /**
    * TestMBTitleArrayL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBTitleArrayL( CStifItemParser& aItem );
    
    /**
    * TestMBTitleArrayL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBSetEditMenuObserverL( CStifItemParser& aItem );
    
    /**
    * TestMBRemoveEditMenuObserverL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBRemoveEditMenuObserverL( CStifItemParser& aItem );
    
    /**
    * TestMBIsDisplayedL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBIsDisplayedL( CStifItemParser& aItem );
    
    /**
    * TestMBSetMenuTypeL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBSetMenuTypeL( CStifItemParser& aItem );
    
    /**
    * TestMBGetColorUseListL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBGetColorUseListL( CStifItemParser& aItem );
    
    /**
    * TestMBHandleResourceChangeL test function of class CEikMenuBar in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMBHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
    * TestMPTCEikMenuPaneTitleL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPTCEikMenuPaneTitleL( CStifItemParser& aItem );
    
    /**
    * TestMPTConstructL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPTConstructL( CStifItemParser& aItem );
    
    /**
    * TestMPTSetSelectedTitleL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPTSetSelectedTitleL( CStifItemParser& aItem );
    /**
    * TestMPTDrawL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPTDrawL( CStifItemParser& aItem );
    
    /**
    * TestMPTMarginsL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPTMarginsL( CStifItemParser& aItem );
    
    /**
    * TestMPTMarginsL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPTCloseL( CStifItemParser& aItem );
    
    /**
    * TestMPTHandlePointerEventL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPTHandlePointerEventL( CStifItemParser& aItem );
    
    /**
    * TestMPTGetColorUseListL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPTGetColorUseListL( CStifItemParser& aItem );
    
    /**
    * TestMPTHandleResourceChangeL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPTHandleResourceChangeL( CStifItemParser& aItem );
    
private: // Test EikMenuP.h
    /**
    * TestMPICEikMenuPaneItemL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPICEikMenuPaneItemL( CStifItemParser& aItem );
    
    /**
    * TestMPISetIconL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPISetIconL( CStifItemParser& aItem );
    
    /**
    * TestMPIDrawItemIcon test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPIDrawItemIcon( CStifItemParser& aItem );
    
    /**
    * TestMPICreateIconLL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPICreateIconL( CStifItemParser& aItem );

    /**
    * TestMPIIconBitmap test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    
    virtual TInt TestMPIIconBitmap( CStifItemParser& aItem );
    /**
    * TestMPIIconMask test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPIIconMask( CStifItemParser& aItem );
    
    /**
    * TestMPISetBitmapsOwnedExternallyL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPISetBitmapsOwnedExternallyL( CStifItemParser& aItem );
    /**
    * TestMPISetIconBitmapL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPISetIconBitmapL( CStifItemParser& aItem );
    
    /**
    * TestMPISetIconBitmapL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPISetIconMaskL( CStifItemParser& aItem );
    
    /**
    * TestMPIScaleableTextL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPIScaleableTextL( CStifItemParser& aItem );
    
    /**
    * TestMPISetScaleableTextL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPISetScaleableTextL( CStifItemParser& aItem );
    
    /**
    * TestMPIACItemArrayL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPIACItemArrayL( CStifItemParser& aItem );
    
    /**
    * TestMPIAAddItemL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPIAAddItemL( CStifItemParser& aItem );
    
    /**
    * TestMPCEikMenuPaneL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPCEikMenuPaneL( CStifItemParser& aItem );
    
    /**
    * TestMPConstructL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPConstructL( CStifItemParser& aItem );
    
    /**
    * TestMPResetL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPResetL( CStifItemParser& aItem );
    
    
    /**
    * TestMPOfferKeyEventL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPOfferKeyEventL( CStifItemParser& aItem );
    
    /**
    * TestMPHandlePointerEventL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPHandlePointerEventL( CStifItemParser& aItem );
    
    /**
    * TestMPGetColorUseListL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
     */
    virtual TInt TestMPGetColorUseListL( CStifItemParser& aItem );
    
    /**
      * TestMPHandleResourceChangeL test function of class CEikMenuPaneTitle in EikMenuB.h
      * @since S60 5.0
      * @param aItem never used
      * @return Symbian OS error code.
       */
    virtual TInt TestMPHandleResourceChangeL( CStifItemParser& aItem );
     
    /**
     * TestMPInputCapabilitiesL test function of class CEikMenuPaneTitle in EikMenuB.h
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPInputCapabilitiesL( CStifItemParser& aItem );
     
     /**
      * TestMPDrawL test function of class CEikMenuPaneTitle in EikMenuB.h
      * @since S60 5.0
      * @param aItem never used
      * @return Symbian OS error code.
     */
    virtual TInt TestMPDrawL( CStifItemParser& aItem );
    
    
    /**
     * TestMPFocusChangedL test function of class CEikMenuPaneTitle in EikMenuB.h
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPFocusChangedL( CStifItemParser& aItem );
    
    /**
     * TestMPConstructFromResourceL test function of class CEikMenuPaneTitle in EikMenuB.h
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPConstructFromResourceL( CStifItemParser& aItem );
   
   /**
    * TestMPAddMenuItemL test function of class CEikMenuPaneTitle in EikMenuB.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
   */
    virtual TInt TestMPAddMenuItemL( CStifItemParser& aItem );
    /**
     * TestMPAddMenuItemIntL test function of class CEikMenuPaneTitle in EikMenuB.h
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
     virtual TInt TestMPAddMenuItemIntL( CStifItemParser& aItem );
     
     /**
      * TestMPAddMenuItemsL test function of class CEikMenuPaneTitle in EikMenuB.h
      * @since S60 5.0
      * @param aItem never used
      * @return Symbian OS error code.
     */
    virtual TInt TestMPAddMenuItemsL( CStifItemParser& aItem );
      
      /**
       * TestMPAddMenuItemsL test function of class CEikMenuPaneTitle in EikMenuB.h
       * @since S60 5.0
       * @param aItem never used
       * @return Symbian OS error code.
      */
    virtual TInt TestMPDeleteMenuItemL( CStifItemParser& aItem );
    
    /**
     * TestMPDeleteBetweenMenuItemsL test function of class CEikMenuPaneTitle in EikMenuB.h
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPDeleteBetweenMenuItemsL( CStifItemParser& aItem );
    
    /**
     * TestMPItemDataL test function of class CEikMenuPaneTitle in EikMenuB.h
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPItemDataL( CStifItemParser& aItem );
    
    /**
     * TestMPItemAndPosL test function of class CEikMenuPaneTitle in EikMenuB.h
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPItemAndPosL( CStifItemParser& aItem );
    
    /**
     * TestMPStartDisplayingMenuPaneL test function of class CEikMenuPaneTitle in EikMenuB.h
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPStartDisplayingMenuPaneL( CStifItemParser& aItem );
    
    
    /**
     * TestMPSetItemTextDesCL test function of class CEikMenuPaneTitle in EikMenuB.h
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPSetItemTextDesCL( CStifItemParser& aItem );
    /**
     * TestMPSetItemTextIntL test function of class CEikMenuPaneTitle in EikMenuB.h
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPSetItemTextIntL( CStifItemParser& aItem );
    
    /**
     * TestMPSetItemDimmedL test function of class CEikMenuPaneTitle in EikMenuB.h
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPSetItemDimmedL( CStifItemParser& aItem );
    
    /**
     * TestMPSetItemButtonStateL test function of class CEikMenuPaneTitle in EikMenuB.h
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPSetItemButtonStateL( CStifItemParser& aItem );
    
    /**
     * TestMPSetSelectedItemL test function of class CEikMenuPaneTitle in EikMenuB.h
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPSetSelectedItemL( CStifItemParser& aItem );
    
    /**
     * TestMPSelectedItemL test function of class CEikMenuPaneTitle in EikMenuB.h
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPSelectedItemL( CStifItemParser& aItem );
    
    /**
     * TestMPCloseCascadeMenuL test function of class CEikMenuPaneTitle in EikMenuB.h
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPCloseCascadeMenuL( CStifItemParser& aItem );
    
    /**
     * TestMPSetItemArrayL test function of class CEikMenuPaneTitle in EikMenuB.h
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPSetItemArrayL( CStifItemParser& aItem );
    
    /**
     * TestMPSetItemArrayOwnedExternallyL test function for testing the SetItemArrayOwnedExternallyL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPSetItemArrayOwnedExternallyL( CStifItemParser& aItem );
    
    /**
     * TestMPSetLaunchingButtonL test function for testing the SetLaunchingButton function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPSetLaunchingButtonL( CStifItemParser& aItem );
    
    /**
     * TestMPMoveHighlightToL test function for testing the MoveHighlightTo function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPMoveHighlightToL( CStifItemParser& aItem );
    
    /**
     * TestMPNumberOfItemsInPaneL test function for testing the NumberOfItemsInPane function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPNumberOfItemsInPaneL( CStifItemParser& aItem );
    
    /**
     * TestMPCloseL test function for testing the CloseL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPCloseL( CStifItemParser& aItem );
    
    /**
     * TestMPOfferKeyEventL test function for testing the OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPOfferKeyEventBoolL( CStifItemParser& aItem );
    
    /**
     * TestMPSetScrollBarOnLeftL test function for testing the SetScrollBarOnLeft function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPSetScrollBarOnLeftL( CStifItemParser& aItem );
    
    /**
     * TestMPSetArrowHeadScrollBarL test function for testing the SetArrowHeadScrollBarL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPSetArrowHeadScrollBarL( CStifItemParser& aItem );
    
    /**
     * TestMPNavigateToNextItemL test function for testing the SetArrowHeadScrollBarL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPNavigateToNextItemL( CStifItemParser& aItem );
    
    /**
     * TestMPInsertMenuItemL test function for testing the InsertMenuItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPInsertMenuItemL( CStifItemParser& aItem );
    
    /**
     * TestMPMenuItemExistsL test function for testing the MenuItemExistsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPMenuItemExistsL( CStifItemParser& aItem );
    
    /**
     * TestMPIsCascadeMenuPaneL test function for testing the IsCascadeMenuPaneL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPIsCascadeMenuPaneL( CStifItemParser& aItem );
    
    /**
     * TestMPCascadeMenuPaneL test function for testing the CascadeMenuPaneL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPCascadeMenuPaneL( CStifItemParser& aItem );
    
    /**
     * TestMPItemDataByIndexL test function for testing the ItemDataByIndexL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPItemDataByIndexL( CStifItemParser& aItem );

    /**
     * TestMPEnableMarqueeL test function for testing the EnableMarqueeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPEnableMarqueeL( CStifItemParser& aItem );
    
    /**
     * TestMPConstructMenuSctRowL test function for testing the ConstructMenuSctRowL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPConstructMenuSctRowL( CStifItemParser& aItem );
    
    /**
     * TestMPMenuItemCommandIdL test function for testing the TestMPMenuItemCommandIdLuctMenuSctRowL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPMenuItemCommandIdL( CStifItemParser& aItem );
    
    /**
     * TestMPConstructMenuSctRowIdL test function for testing the TestMPMenuItemCommandIdLuctMenuSctRowL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPConstructMenuSctRowIdL( CStifItemParser& aItem );
    
    /**
     * TestMPConstructMenuSctRowFromDialogL test function for testing the ConstructMenuSctRowFromDialogL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPConstructMenuSctRowFromDialogL( CStifItemParser& aItem );
    
    /**
     * TestMPMopSupplyObjectL test function for testing the MopSupplyObjectL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPMopSupplyObjectL( CStifItemParser& aItem );
    /**
     * TestMPCountComponentControlsL test function for testing the CountComponentControlsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPCountComponentControlsL( CStifItemParser& aItem );
    
    /**
     * TestMPComponentControlL test function for testing the ComponentControlL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPComponentControlL( CStifItemParser& aItem );

    /**
     * TestMPSetItemSpecific test function for testing the SetItemSpecific function
     * @since S60 5.2
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMPSetItemSpecific( CStifItemParser& aItem );

    /**
     * TestMBItemSpecificCommandsEnabled test function for testing the 
     * ItemSpecificCommandsEnabled function
     * @since S60 5.2
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestMBItemSpecificCommandsEnabled( CStifItemParser& aItem );

private: // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    /**
     * Control pointer for test CEikMenuPaneItem
     * Own
     */
    CCoeControl* iControl;
    /**
     * Pointer for test CEikMenuBar
     * own
     */
    CEikMenuBar* iEikMenuBar;
    /**
     * Pointer for test CEikMenuBarTitle
     * own
     */
    CEikMenuBarTitle* iEikMenuBarTitle;
    /**
     * Pointer for test CEikMenuPaneTitle
     * own
     */
    CEikMenuPaneTitle* iEikMenuPaneTitle;
    /**
     * Pointer for test CEikMenuPaneItem
     * own
     */
    CEikMenuPaneItem* iEikMenuPaneItem;
    /**
     * Pointer for test CEikonEnv
     * own
     */
    CEikonEnv* iEikEnv;
    /**
     * Pointer for test CEikMenuPaneItem
     * own
     */
    CTestSDKOptionsMenuContainer * iContainer;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKOPTIONSMENU_H
// End of File
