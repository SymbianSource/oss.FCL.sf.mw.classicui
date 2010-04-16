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
* Description:  test special_character_table_api
*
*/

#ifndef C_TESTDOMSPECIALCHARTAB_H
#define C_TESTDOMSPECIALCHARTAB_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <avkon.hrh>
#include <avkon.rsg>
#include <eikdef.h>
#include <coeaui.h>
#include <aknSctDialog.h>

#include "testdomcontainer.h"


// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestdomspecialchartabLogPath, "\\logs\\testframework\\testdomspecialchartab\\" ); 
// Log file
_LIT( KtestdomspecialchartabLogFile, "testdomspecialchartab.txt" ); 
_LIT( KtestdomspecialchartabLogFileWithTitle, "testdomspecialchartab_[%S].txt" );

/**
*  CTestDomSpecialCharTab test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDomSpecialCharTab ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDomSpecialCharTab* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDomSpecialCharTab();

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
    CTestDomSpecialCharTab( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // Test aknsctdialog.h
    /**
    * TestCMDCAknCharMapDialogL test function of class CAknCharMapDialog in aknsctdialog.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMDCAknCharMapDialogL( CStifItemParser& aItem );
    
    /**
    * TestCMDExecuteLDL test function of class CAknCharMapDialog in aknsctdialog.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMDExecuteLDL( CStifItemParser& aItem );
    
    /**
    * TestCMDOfferKeyEventL test function of class CAknCharMapDialog in aknsctdialog.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMDOfferKeyEventL( CStifItemParser& aItem );
    
    /**
    * TestCMDHandleResourceChangeL test function of class CAknCharMapDialog in aknsctdialog.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMDHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
    * TestCMDShowNoPictographsL test function of class CAknCharMapDialog in aknsctdialog.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMDShowNoPictographsL( CStifItemParser& aItem );
    
    /**
    * TestCMDShowPictographsFirstL test function of class CAknCharMapDialog in aknsctdialog.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMDShowPictographsFirstL( CStifItemParser& aItem );
    
    /**
    * TestCMDShowAnotherTableL test function of class CAknCharMapDialog in aknsctdialog.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMDShowAnotherTableL( CStifItemParser& aItem );
    
    /**
    * TestCMDHandleControlEventL test function of class CAknCharMapDialog in aknsctdialog.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMDHandleControlEventL( CStifItemParser& aItem );
    
    /**
    * TestCMDHandleDialogPageEventL test function of class CAknCharMapDialog in aknsctdialog.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMDHandleDialogPageEventL( CStifItemParser& aItem );
    
    /**
    * TestCMDLockNumericKeysL test function of class CAknCharMapDialog in aknsctdialog.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMDLockNumericKeysL( CStifItemParser& aItem );
    
    /**
    * TestCMDDisableRecentCharsRowL test function of class CAknCharMapDialog in aknsctdialog.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMDDisableRecentCharsRowL( CStifItemParser& aItem );
    
    /**
    * TestCMDHandlePointerEventLL test function of class CAknCharMapDialog in aknsctdialog.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMDHandlePointerEventLL( CStifItemParser& aItem );
    
private: // Test akncharmap.h
    /**
    * TestCMCAknCharMapL test function of class CAknCharMap in akncharmap.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMCAknCharMapL( CStifItemParser& aItem );
    
    /**
    * TestCMSetBufferL test function of class CAknCharMap in akncharmap.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMSetBufferL( CStifItemParser& aItem );
    
    /**
    * TestCMMinimumSizeL test function of class CAknCharMap in akncharmap.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMMinimumSizeL( CStifItemParser& aItem );
    
    /**
    * TestCMOfferKeyEventL test function of class CAknCharMap in akncharmap.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMOfferKeyEventL( CStifItemParser& aItem );
    
    /**
    * TestCMInputCapabilitiesL test function of class CAknCharMap in akncharmap.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMInputCapabilitiesL( CStifItemParser& aItem );
    
    /**
    * TestCMActivateL test function of class CAknCharMap in akncharmap.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMActivateL( CStifItemParser& aItem );
    
    /**
    * TestCMDoSizeChangedL test function of class CAknCharMap in akncharmap.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMDoSizeChangedL( CStifItemParser& aItem );
    
    /**
    * TestCMDoHandleResourceChangeL test function of class CAknCharMap in akncharmap.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMDoHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
    * TestCMDoCountComponentControlsL test function of class CAknCharMap in akncharmap.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMDoCountComponentControlsL( CStifItemParser& aItem );
    
    /**
    * TestCMDoComponentControlL test function of class CAknCharMap in akncharmap.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMDoComponentControlL( CStifItemParser& aItem );
    
    /**
    * TestCMHandlePointerEventL test function of class CAknCharMap in akncharmap.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMHandlePointerEventL( CStifItemParser& aItem );
    
    /**
    * TestCMSetObserverL test function of class CAknCharMap in akncharmap.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMSetObserverL( CStifItemParser& aItem );
    
    /**
    * TestCMConstructMenuSctRowL test function of class CAknCharMap in akncharmap.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMConstructMenuSctRowL( CStifItemParser& aItem );
    
    /**
    * TestCMSetMenuSctRectL test function of class CAknCharMap in akncharmap.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMSetMenuSctRectL( CStifItemParser& aItem );
    
    /**
    * TestCMConstructMenuSctRowIdL test function of class CAknCharMap in akncharmap.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMConstructMenuSctRowIdL( CStifItemParser& aItem );
    
    /**
    * TestCMHighlightSctRowL test function of class CAknCharMap in akncharmap.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    TInt TestCMHighlightSctRowL( CStifItemParser& aItem );
    
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * Pointer to component control.
     * own
     */
    CTestDomContainer *iContainer;
    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTDOMSPECIALCHARTAB_H

// End of File


