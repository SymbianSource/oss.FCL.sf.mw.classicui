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
* Description:  test aknjavalists.h, aknshortcuts.h and eikslbd.h
*
*/



#ifndef C_TESTDOMLISTS_H
#define C_TESTDOMLISTS_H

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
_LIT( KTestDOMListsLogPath, "c:\\logs\\testframework\\testdomlists\\" ); 
// Log file
_LIT( KTestDOMListsLogFile, "testdomlists.txt" ); 
_LIT( KTestDOMListsLogFileWithTitle, "testdomlists_[%S].txt" );

/**
*  CTestDOMLists test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDOMLists ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMLists* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMLists();

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
    CTestDOMLists( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // test functions in aknjavalists.h

    /**
    * test default construct method of CAknDouble2GraphicLargeStyleListBox.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestLargeListDefConL( CStifItemParser& aItem );

    /**
    * test SizeChanged method of CAknDouble2GraphicLargeStyleListBox.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestLargeListSizeChangedL( CStifItemParser& aItem );

    /**
    * test MinimumSize method of CAknDouble2GraphicLargeStyleListBox.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestLargeListMinimumSizeL( CStifItemParser& aItem );

    /**
    * test CreateItemDrawerL method of CAknDouble2GraphicLargeStyleListBox.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestLargeListCreateItemDrawerL( CStifItemParser& aItem );

    /**
    * test default construct method of CAknSingle2GraphicStyleListBox.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestListDefConL( CStifItemParser& aItem );

    /**
    * test SizeChanged method of CAknDouble2GraphicStyleListBox.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestListSizeChangedL( CStifItemParser& aItem );

    /**
    * test MinimumSize method of CAknDouble2GraphicStyleListBox.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestListMinimumSizeL( CStifItemParser& aItem );

    /**
    * test UseEmptyIconSpace method of CAknDouble2GraphicStyleListBox.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestListUseEmptyIconSpaceL( CStifItemParser& aItem );

    /**
    * test CreateItemDrawerL method of CAknDouble2GraphicStyleListBox.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestListCreateItemDrawerL( CStifItemParser& aItem );

private: // test functions in aknshortcuts.h

    /**
    * test ConstructL method of AknListBoxShortCutTemplate.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTempConstructL( CStifItemParser& aItem );

    /**
    * test ConstructFromResourceL method of AknListBoxShortCutTemplate.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTempConstructFromResourceL( CStifItemParser& aItem );

    /**
    * test OfferKeyEventL method of AknListBoxShortCutTemplate.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTempOfferKeyEventL( CStifItemParser& aItem );

    /**
    * test ShortcutValueForNextList method of AknListBoxShortCutTemplate.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTempShortcutValueForNextListL( CStifItemParser& aItem );

    /**
    * test SetShortcutValueFromPrevList method of AknListBoxShortCutTemplate.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTempSetShortcutValueFromPrevListL( CStifItemParser& aItem );

    /**
    * test SetShortcutEnabledL method of AknListBoxShortCutTemplate.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTempSetShortcutEnabledL( CStifItemParser& aItem );

    /**
    * test default construct method of AknListBoxShortCuts.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCutsDefConL( CStifItemParser& aItem );

    /**
    * test ConstructL method of AknListBoxShortCuts.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCutsConstructL( CStifItemParser& aItem );

    /**
    * test OfferKeyEventL method of AknListBoxShortCuts.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCutsOfferKeyEventL( CStifItemParser& aItem );

    /**
    * test RecursionLock method of AknListBoxShortCuts.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCutsRecursionLockL( CStifItemParser& aItem );

    /**
    * test RecursionUnlock method of AknListBoxShortCuts.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCutsRecursionUnlockL( CStifItemParser& aItem );

    /**
    * test RunL method of AknListBoxShortCuts.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCutsRunL( CStifItemParser& aItem );

    /**
    * test ChangeStateL method of AknListBoxShortCuts.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCutsChangeStateL( CStifItemParser& aItem );

    /**
    * test DoProcedureL method of AknListBoxShortCuts.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCutsDoProcedureL( CStifItemParser& aItem );

    /**
    * test StartTimerL method of AknListBoxShortCuts.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCutsStartTimerL( CStifItemParser& aItem );

    /**
    * test EndTimer method of AknListBoxShortCuts.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCutsEndTimerL( CStifItemParser& aItem );

    /**
    * test default construct method of AknListBoxShortCutsImplementation.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestImpleDefConL( CStifItemParser& aItem );

    /**
    * test ConstructL method of AknListBoxShortCutsImplementation.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestImpleConstructL( CStifItemParser& aItem );

    /**
    * test DoTest method of AknListBoxShortCutsImplementation.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestImpleDoTestL( CStifItemParser& aItem );

    /**
    * test DoActionL method of AknListBoxShortCutsImplementation.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestImpleDoActionL( CStifItemParser& aItem );

    /**
    * test OfferKeyEventL method of AknListBoxShortCutsImplementation.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestImpleOfferKeyEventL( CStifItemParser& aItem );

    /**
    * test ShortcutValueForNextList method of AknListBoxShortCutsImplementation.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestImpleShortcutValueForNextListL( CStifItemParser& aItem );

    /**
    * test SetShortcutValueFromPrevList method of AknListBoxShortCutsImplementation.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestImpleSetShortcutValueFromPrevListL( CStifItemParser& aItem );

    /**
    * test ProcessCommandL method of AknListBoxShortCutsImplementation.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestImpleProcessCommandL( CStifItemParser& aItem );

private: // test functions in eikslbd.h

    /**
    * test NewL method of CSettingsListBoxData.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetDataNewL( CStifItemParser& aItem );

    /**
    * test Draw method of CSettingsListBoxData.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetDataDrawL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTDOMLISTS_H

// End of File
