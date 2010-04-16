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
* Description:  test aknstyluspopupmenu.h
*
*/



#ifndef C_TESTSDKSTYLUSPOPUPMENU_H
#define C_TESTSDKSTYLUSPOPUPMENU_H

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
_LIT( KtestsdkstyluspopupmenuLogPath, "\\logs\\testframework\\testsdkstyluspopupmenu\\" ); 
// Log file
_LIT( KtestsdkstyluspopupmenuLogFile, "testsdkstyluspopupmenu.txt" ); 
_LIT( KtestsdkstyluspopupmenuLogFileWithTitle, "testsdkstyluspopupmenu_[%S].txt" );

/**
*  CTestSDKStylusPopupMenu test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKStylusPopupMenu ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKStylusPopupMenu* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKStylusPopupMenu();

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
    CTestSDKStylusPopupMenu( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // Test aknstyluspopupmenu.h
/*                               class CAknStylusPopUpMenu                  */
    /**
     * TestSPMNewTL test function for testing the 
     *     NewL function with three parameters
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPMNewTL( CStifItemParser& aItem );
    
    /**
     * TestSPMNewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPMNewL( CStifItemParser& aItem );
    
    /**
     * TestSPMNewLC test function for testing the 
     *     NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPMNewLC( CStifItemParser& aItem );
    
    /**
     * TestSPMAddMenuItemL test function for testing the 
     *     AddMenuItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPMAddMenuItemL( CStifItemParser& aItem );
    
    /**
     * TestSPMRemoveMenuItemL test function for testing the 
     *     RemoveMenuItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPMRemoveMenuItemL( CStifItemParser& aItem );
    
    /**
     * TestSPMSetItemDimmedL test function for testing the 
     *     SetItemDimmed function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPMSetItemDimmedL( CStifItemParser& aItem );
    
    /**
     * TestSPMShowMenuL test function for testing the 
     *     ShowMenu function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPMShowMenuL( CStifItemParser& aItem );
    
    /**
     * TestSPMSetPositionL test function for testing the 
     *     SetPosition function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPMSetPositionL( CStifItemParser& aItem );
    
    /**
     * TestSPMSetPositionTL test function for testing the 
     *     SetPosition function with two parameters
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPMSetPositionTL( CStifItemParser& aItem );
    
    /**
     * TestSPMConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPMConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestSPMHandleControlEventL test function for testing the 
     *     HandleControlEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPMHandleControlEventL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKSTYLUSPOPUPMENU_H

// End of File
