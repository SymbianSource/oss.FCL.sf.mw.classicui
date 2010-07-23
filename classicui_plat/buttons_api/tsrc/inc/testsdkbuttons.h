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
* Description:  test buttons api.
*
*/



#ifndef C_TESTSDKBUTTONS_H
#define C_TESTSDKBUTTONS_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <eikbgfty.h>
#include <eikbtgpc.h>
#include <eikbtgps.h>
#include <eikbutb.h>
#include <eikcba.h>
#include <eikcmbut.h>
#include <eiklbbut.h>
#include <eikmnbut.h>
#include <barsread.h>
#include <eikmobs.h>
#include <eikenv.h>
#include <eikappui.h>
#include <coemain.h>

#include "testsdkbuttonscontainer.h"

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkbuttonsLogPath, "\\logs\\testframework\\testsdkbuttons\\" ); 
// Log file
_LIT( KtestsdkbuttonsLogFile, "testsdkbuttons.txt" ); 
_LIT( KtestsdkbuttonsLogFileWithTitle, "testsdkbuttons_[%S].txt" );


/**
*  CTestSDKButtons test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKButtons) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKButtons* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKButtons();

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
    CTestSDKButtons( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
    * Frees all resources allocated from test methods.
    * @since S60 5.0
    */
    void Delete();
    
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private:
    /**
    * TestMenuBtConstructorL test constructor and 
    * deconstructor of CEikMenuButton in eikmnbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuBtConstructorL( CStifItemParser& aItem );
    
    /**
    * TestMenuBtConstructorL test ConstructFromResourceL 
    * of CEikMenuButton in eikmnbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuBtConstructFromResourceL( CStifItemParser& aItem );
    
    /**
    * TestMenuBtLaunchPopupMenuL test LaunchPopupMenuL 
    * of CEikMenuButton in eikmnbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuBtLaunchPopupMenuL( CStifItemParser& aItem );
    
    /**
    * TestMenuBtSetMenuPaneIdL test SetMenuPaneId 
    * of CEikMenuButton in eikmnbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuBtSetMenuPaneIdL( CStifItemParser& aItem );
    
    /**
    * TestMenuBtAnimateL test Animate of CEikMenuButton in eikmnbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuBtAnimateL( CStifItemParser& aItem );
    
    /**
    * TestMenuBtWriteInternalStateL test WriteInternalStateL 
    * of CEikMenuButton in eikmnbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuBtWriteInternalStateL( CStifItemParser& aItem );
    /**
    * TestLabelBtConstructorL test constructor and 
    * deconstructor of CEikLabeledButton in eiklbbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestLabelBtConstructorL( CStifItemParser& aItem );
    
    /**
    * TestLabelBtConstructL test second constructor 
    * of CEikLabeledButton in eiklbbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestLabelBtConstructL( CStifItemParser& aItem );
    
    /**
    * TestLabelBtConstructFromResourceL test resource constructor 
    * of CEikLabeledButton in eiklbbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestLabelBtConstructFromResourceL( CStifItemParser& aItem );
    
    /**
    * TestLabelBtButtonoL test Button function 
    * of CEikLabeledButton in eiklbbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestLabelBtButtonoL( CStifItemParser& aItem );
    
    /**
    * TestLabelBtLabelL test Label function 
    * of CEikLabeledButton in eiklbbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestLabelBtLabelL( CStifItemParser& aItem );
    
    /**
    * TestLabelBtHotKeyFunctionsL test HotKeyCode,ShowsHotKey,
    * UpdateHotKey,PlainHotKey,four functions of CEikLabeledButton in eiklbbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestLabelBtHotKeyFunctionsL( CStifItemParser& aItem );
    
    /**
    * TestLabelBtAnimateL test Animate of CEikLabeledButton in eiklbbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestLabelBtAnimateL( CStifItemParser& aItem );
    
    /**
    * TestLabelBtOfferKeyEvnetL test OfferKeyEvnetL and HandlePointerEventL
    * of CEikLabeledButton in eiklbbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestLabelBtOfferKeyEvnetL( CStifItemParser& aItem );
    
    /**
    * TestLabelBtSetContainerWindowL test SetContainerWindow of CEikLabeledButton 
    * in eiklbbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestLabelBtSetContainerWindowL( CStifItemParser& aItem );
    
    /**
    * TestLabelBtMiniSizeL test MinimumSize of CEikLabeledButton 
    * in eiklbbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestLabelBtMiniSizeL( CStifItemParser& aItem );
    
    /**
    * TestLabelBtSetdimL test SetDimmed of CEikLabeledButton 
    * in eiklbbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestLabelBtSetdimL( CStifItemParser& aItem );
    
    /**
    * TestLabelBtHandleResourceChangeL test HandleResourceChange
    * of CEikLabeledButton in eiklbbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestLabelBtHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
    * TestLabelBtInputCapabilitiesL test InputCapabilities
    * of CEikLabeledButton in eiklbbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestLabelBtInputCapabilitiesL( CStifItemParser& aItem );
    
    /**
    * TestLabelBtGetColorUseListL test GetColorUseListL
    * of CEikLabeledButton in eiklbbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestLabelBtGetColorUseListL( CStifItemParser& aItem );
    
    /**
    * TestLabelBtWriteInternalStateL test WriteInternalStateL
    * of CEikLabeledButton in eiklbbut.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestLabelBtWriteInternalStateL( CStifItemParser& aItem );
    
    
    /**
    * TestCEikCmdBtBaseConstrutorL test constructor
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseConstrutorL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseSetButtonLayoutL test SetButtonLayout
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseSetButtonLayoutL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseSetExcessSpaceL test SetExcessSpace
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseSetExcessSpaceL( CStifItemParser& aItem );
    
    
    /**
    * TestCEikCmdBtBaseSetDisplayContentL test SetDisplayContent
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseSetDisplayContentL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseLayoutComponentsL test LayoutComponents
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseLayoutComponentsL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseStartConstructFromResourceL test StartConstructFromResourceL
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseStartConstructFromResourceL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseConstructLabelAndImageFromResourceL test ConstructLabelFromResourceL
    * and ConstructImageFromResourceL of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseConstructLabelAndImageFromResourceL( CStifItemParser& aItem );

    
    /**
    * TestCEikCmdBtBaseUpdateComponentAlignmentL test UpdateComponentAlignment
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseUpdateComponentAlignmentL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseSetDefaultL test SetDefault
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseSetDefaultL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseSetDimmedL test SetDimmed
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseSetDimmedL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseMinimumSizeL test MinimumSize
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseMinimumSizeL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseCountComponentControlsL test CountComponentControls
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseCountComponentControlsL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseComponentControlL test ComponentControl
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseComponentControlL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseSetContainerWindowLAndActivateL test ActivateL and
    * SetContainerWindowL of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseSetContainerWindowLAndActivateL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseFocusChangedL test FocusChanged
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseFocusChangedL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseOfferKeyEventL test OfferKeyEventL
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseOfferKeyEventL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseGetColorUseListL test GetColorUseListL
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseGetColorUseListL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseHandleResourceChangeL test HandleResourceChange
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseStateChangedL test StateChanged
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseStateChangedL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseSetTextL test SetTextL
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseSetTextL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseSetPictureL test SetPictureL
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseSetPictureL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseSetPictureFromFileL test SetPictureFromFileL
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseSetPictureFromFileL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseDrawL test Draw
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseDrawL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtBaseDrawL test Draw
    * of CEikCommandButtonBase in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtBaseWriteInternalStateL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtConstructorL test constructor
    * of CEikCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtConstructorL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtConstructFromResourceL test ConstructFromResourceL
    * of CEikCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtConstructFromResourceL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtSetPictureL test SetPictureL, SetPictureFromFileL and Picture
    * of CEikCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is a number, 1 test SetPictureL, 2 test SetPictureFromFileL.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtSetPictureL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtSetThreeEnumL test SetButtonLayout, SetExcessSpace and SetDisplayContent
    * of CEikCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtSetThreeEnumL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtSetTextL test SetTextL
    * of CEikCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtSetTextL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtLabelL test Label
    * of CEikCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtLabelL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtCmdSetL test SetCommandL
    * of CEikCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtCmdSetL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtUpdateComponentAlignmentL test UpdateComponentAlignment
    * and HandlePointerEventL of CEikCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtUpdateComponentAlignmentL( CStifItemParser& aItem );
    
    /**
    * TestCEikTwoPicCmdBtConstructorL test constructor
    * of CEikTwoPictureCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikTwoPicCmdBtConstructorL( CStifItemParser& aItem );
    
    /**
    * TestCEikTwoPicCmdBtConstructorL test constructor
    * of CEikTwoPictureCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikTwoPicCmdBtConstructFromResourceL( CStifItemParser& aItem );
    
    /**
    * TestCEikTwoPicCmdBtIsSecondPictureOwnedExternallyL test IsSecondPictureOwnedExternally
    * of CEikTwoPictureCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikTwoPicCmdBtIsSecondPictureOwnedExternallyL( CStifItemParser& aItem );
    
    /**
    * TestCEikTwoPicCmdBtPictureL test Picture and HandlePointerEventL
    * of CEikTwoPictureCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikTwoPicCmdBtPictureL( CStifItemParser& aItem );
    
    /**
    * TestCEikTwoPicCmdBtSetTextL test SetTextL
    * of CEikTwoPictureCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikTwoPicCmdBtSetTextL( CStifItemParser& aItem );
    
    /**
    * TestCEikTwoPicCmdBtPictureSetL test SetTwoPicturesL, SetSecondPicture, 
    * SetPictureFromFileL and SetSecondPictureFromFileL
    * of CEikTwoPictureCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikTwoPicCmdBtPictureSetL( CStifItemParser& aItem );
    
    /**
    * TestCEikTwoPicCmdBtConstructImagesFromResourceL test ConstructImagesFromResourceL
    * of CEikTwoPictureCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikTwoPicCmdBtConstructImagesFromResourceL( CStifItemParser& aItem );
    
    /**
    * TestCEikTwoPicCmdBtSetSecondPictureOwnedExternallyL test SetSecondPictureOwnedExternally
    * of CEikTwoPictureCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikTwoPicCmdBtSetSecondPictureOwnedExternallyL( CStifItemParser& aItem );
    
    /**
    * TestCEikTwoPicCmdBtActivateL test ActivateL
    * of CEikTwoPictureCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikTwoPicCmdBtActivateL( CStifItemParser& aItem );
    
    /**
    * TestCEikTwoPicCmdBtWriteInternalStateL test WriteInternalStateL
    * of CEikTwoPictureCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikTwoPicCmdBtWriteInternalStateL( CStifItemParser& aItem );
    
    /**
    * TestCEikInverterCmdBtConstructorL test constructor
    * of CEikInverterCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikInverterCmdBtConstructorL( CStifItemParser& aItem );
    
    /**
    * TestCEikInverterCmdBtWriteInternalStateL test WriteInternalStateL
    * of CEikInverterCommandButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikInverterCmdBtWriteInternalStateL( CStifItemParser& aItem );
    
    /**
    * TestCEikTxtBtConstructorL test constructor
    * of CEikTextButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikTxtBtConstructorL( CStifItemParser& aItem );
    
    /**
    * TestCEikTxtBtConstructFromResourceL test ConstructFromResourceL
    * of CEikTextButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikTxtBtConstructFromResourceL( CStifItemParser& aItem );
    
    /**
    * TestCEikTxtBtSetTextL test SetTextL
    * of CEikTextButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikTxtBtSetTextL( CStifItemParser& aItem );
    
    /**
    * TestCEikTxtBtLabelL test Label
    * of CEikTextButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikTxtBtLabelL( CStifItemParser& aItem );
    
    /**
    * TestCEikBmpBtConstructorL test constructor
    * of CEikBitmapButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBmpBtConstructorL( CStifItemParser& aItem );
    
    /**
    * TestCEikBmpBtConstructFromResourceL test ConstructFromResourceL
    * of CEikBitmapButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBmpBtConstructFromResourceL( CStifItemParser& aItem );
    
    /**
    * TestCEikBmpBtPictureSetL test SetPictureL, SetPictureFromFileL, Picture
    * and HandlePointerEventL of CEikBitmapButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBmpBtPictureSetL( CStifItemParser& aItem );
    
    /**
    * TestCEikCmdBtProcessCmdStackL test AddCommandToStackL, 
    * RemoveCommandFromStack and PopCommandFromStack
    * of CEikBitmapButton in eikcmbut.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCmdBtProcessCmdStackL( CStifItemParser& aItem );
    
    
    /**
    * TestCEikBtBaseConstructorL test constructor and 
    * deconstructor of CEikButtonBase in eikbutb.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtBaseConstructorL( CStifItemParser& aItem );
    
    //SetIgnoreNextPointerUp and IsPressed in eikbutb.h is ignore for pointer reason
    
    /**
    * TestCEikBtBaseSetAndGetStateL test State and 
    * SetState of CEikButtonBase in eikbutb.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtBaseSetAndGetStateL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtBaseAnimateL test Animate 
    * of CEikButtonBase in eikbutb.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtBaseAnimateL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtBaseSetCoordinatorL test SetCoordinator 
    * of CEikButtonBase in eikbutb.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtBaseSetCoordinatorL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtBaseSetCoordinatorL test SetBehavior 
    * of CEikButtonBase and test constructor, SetChosenButton of 
    * TEikButtonCoordinator in eikbutb.h 
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtBaseSetBehaviorL( CStifItemParser& aItem );
                 
    /**
    * TestCEikBtBaseGetColorUseListL test GetColorUseListL 
    * of CEikButtonBase in eikbutb.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtBaseGetColorUseListL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtBaseHandleResourceChangeL test HandleResourceChange 
    * of CEikButtonBase in eikbutb.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtBaseHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtBaseWriteInternalStateL test WriteInternalStateL 
    * of CEikButtonBase in eikbutb.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtBaseWriteInternalStateL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtBaseDrawStateL test DrawState 
    * of CEikButtonBase in eikbutb.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtBaseDrawStateL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtBaseSetAllowTristateL test SetAllowTristate 
    * of CEikButtonBase in eikbutb.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtBaseSetAllowTristateL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtBaseCopyDrawStateToL test CopyDrawStateTo 
    * of CEikButtonBase in eikbutb.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtBaseCopyDrawStateToL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtBaseOfferKeyEventL test OfferKeyEventL 
    * of CEikButtonBase in eikbutb.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtBaseOfferKeyEventL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtBaseOfferKeyEventL test OfferKeyEventL 
    * of CEikButtonBase in eikbutb.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtBaseInputCapabilitiesL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupStackMinimumSize test MinimumSize 
    * of CEikButtonGroupStack in eikbtgps.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupStackMinimumSize( CStifItemParser& aItem );
    
    /**
    * TestCEikCbaOfferCommandListL test two overload OfferCommandListL 
    * of CEikCba in eikcba.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCbaOfferCommandListL( CStifItemParser& aItem );
    
    /**
    * TestCEikCbaIsCommandInGroupL test IsCommandInGroup 
    * of CEikCba in eikcba.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCbaIsCommandInGroupL( CStifItemParser& aItem );
    
    /**
    * TestCEikCbaSetButtonGroupFlagsL test SetButtonGroupFlags 
    * of CEikCba in eikcba.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCbaSetButtonGroupFlagsL( CStifItemParser& aItem );
    
    /**
    * TestCEikCbaReplaceCommandL test ReplaceCommand 
    * of CEikCba in eikcba.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCbaReplaceCommandL( CStifItemParser& aItem );

    /**
    * TestCEikCbaEnableItemSpecificSoftkey test EnableItemSpecificSoftkey 
    * of CEikCba in eikcba.h
    * @since S60 5.2
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCbaEnableItemSpecificSoftkey( CStifItemParser& aItem );
    
    /**
    * TestCEikCbaReplaceCommandL test ReplaceCommand 
    * of CEikCba in eikcba.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCbaSetSkinBackgroundIdL( CStifItemParser& aItem );
    
    /**
    * TestCEikCbaIsEmptyL test IsEmpty 
    * of CEikCba in eikcba.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikCbaIsEmptyL( CStifItemParser& aItem );
    /**
    * TestCEikBtGroupFactoryCbaTCreationDataL test TCreationData class constructor 
    * of EikButtonGroupFactory in eikbgfty.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupFactoryCbaTCreationDataL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupFactoryArrayAddAndRemoveFuncL test AppendFactoryFunctionL
    * and RemoveFactoryFunction of EikButtonGroupFactoryArray in eikbgfty.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupFactoryArrayAddAndRemoveFuncL( CStifItemParser& aItem );
    
    
    /**
    * TestCEikBtGroupContainerNewL test NewL function 
    * of CEikButtonGroupContainer in eikbtgpc.h
    * @since S60 5.0
    * @param aItem is a number
    * 1 tests NewL with five parameters
    * 2 tests NewL with parant control
    * 3 tests NewL with parant control group
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerNewL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerCurrent test Current function 
    * of CEikButtonGroupContainer in eikbtgpc.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerCurrent( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerSetCommandL test SetCommandL 
    * of CEikButtonGroupContainer in eikbtgpc.h
    * @since S60 5.0
    * @param aItem is a number from 1 to 11, to test overloaded SetCommandL
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerSetCommandL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerSetCommandSetL test SetCommandSetL 
    * of CEikButtonGroupContainer in eikbtgpc.h
    * @since S60 5.0
    * @param aItem is not used
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerSetCommandSetL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerAddCommandL test AddCommandL 
    * of CEikButtonGroupContainer in eikbtgpc.h
    * @since S60 5.0
    * @param aItem is a number from 1 to 5, to test overloaded AddCommandL
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerAddCommandL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerAddCommandToStackL test AddCommandToStackL 
    * of CEikButtonGroupContainer in eikbtgpc.h
    * @since S60 5.0
    * @param aItem is a number from 1 to 6, to test overloaded AddCommandToStackL
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerAddCommandToStackL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerAddCommandSetToStackL test AddCommandSetToStackL 
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerAddCommandSetToStackL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerRemoveCommandFromStackL test RemoveCommandFromStack 
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerRemoveCommandFromStackL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerSetDefaultCommandL test SetDefaultCommand 
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerSetDefaultCommandL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerCalcMinimumSizeL test CalcMinimumSizeL
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerCalcMinimumSizeL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerCleanupFunctionL test five CleanupCommand profix function
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerCleanupFunctionL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerBtNumberL test MaxCommands and ButtonCount
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerBtNumberL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerCmdDimL test DimCommand, IsCommandDimmed, 
    * DimCommandByPosition and IsCommandDimmedByPosition
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerCmdDimL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerCmdAnimateL test AnimateCommand and AnimateCommandByPosition
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerCmdAnimateL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerCmdAnimateL test MakeCommandVisible, IsCommandVisible,
    * MakeCommandVisibleByPosition and IsCommandVisibleByPosition
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerCmdVisibleL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerLocationL test Location
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerLocationL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerCommandButtonOrNullL test CommandButtonOrNull
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerCommandButtonOrNullL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerControlOrNullL test ControlOrNull
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerControlOrNullL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerSetBoundingRectL test SetBoundingRect
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerSetBoundingRectL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerGetBtAndBtPositionAndBtTypeL test ButtonById, PositionById
    * and ButtonGroupType of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerGetBtAndBtPositionAndBtTypeL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerReduceRectL test ReduceRect
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerReduceRectL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerUpdateHotKeyL test UpdateHotKeyL
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerUpdateHotKeyL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerUpdateCommandObserverL test UpdateCommandObserverL
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerUpdateCommandObserverL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerRemoveCommandObserverL test RemoveCommandObserverL
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerRemoveCommandObserverL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerUpdatedCommandObserverExistsL test UpdatedCommandObserverExists
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerUpdatedCommandObserverExistsL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerDelayActivationL test DelayActivation
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerDelayActivationL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerButtonGroupL test ButtonGroup
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerButtonGroupL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerReservedFunctionL test Reserved_MtsmPosition and
    * Reserved_MtsmObject of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerReservedFunctionL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerOfferCommandListL test two overloaded OfferCommandListL 
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerOfferCommandListL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerIsCommandInGroupL test IsCommandInGroup 
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerIsCommandInGroupL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerReplaceCommandL test ReplaceCommand 
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerReplaceCommandL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerMinimumSizeL test MinimumSize 
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerMinimumSizeL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerOfferKeyEventL test OfferKeyEventL 
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerOfferKeyEventL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerMakeVisibleL test MakeVisible 
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerMakeVisibleL( CStifItemParser& aItem );
    
    /**
    * TestCEikBtGroupContainerWriteInternalStateL test WriteInternalStateL 
    * of CEikButtonGroupContainer in eikbtgpc.h.
    * @since S60 5.0.
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBtGroupContainerWriteInternalStateL( CStifItemParser& aItem );
    
    //[TestMethods]

private:    // Data
    
     /*
      * Switch Cmd
      */
    enum TCaseId
        {
        ECaseOne = 1,
        ECaseTwo,
        ECaseThree,
        ECaseFour,
        ECaseFive,
        ECaseSix,
        ECaseSeven,
        ECaseEight,
        ECaseNine,
        ECaseTen,
        ECaseEleven
        
        };
    
    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * CCoeControl pointer
     * Own.
     */
    CButtonControl* iContainer;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKBUTTONS_H

// End of File
