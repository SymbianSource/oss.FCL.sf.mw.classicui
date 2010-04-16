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
* Description:  test finditemdialog.h and finditemmenu.h
*
*/

#ifndef C_TESTDOMFINDITEM_H
#define C_TESTDOMFINDITEM_H

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
_LIT( KtestdomfinditemLogPath, "\\logs\\testframework\\testdomfinditem\\" ); 
// Log file
_LIT( KtestdomfinditemLogFile, "testdomfinditem.txt" ); 
_LIT( KtestdomfinditemLogFileWithTitle, "testdomfinditem_[%S].txt" );

/**
*  Ctestdomfinditem test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( Ctestdomfinditem ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static Ctestdomfinditem* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~Ctestdomfinditem();

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
    Ctestdomfinditem( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // test functions in finditemdialog.h

    /**
    * test NewL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestDialogNewL( CStifItemParser& aItem );

    /**
    * test ExecuteLD method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestDialogExecuteLDL( CStifItemParser& aItem );

    /**
    * test ProcessCommandL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestDialogProcessCommandL( CStifItemParser& aItem );

    /**
    * test OfferKeyEventL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestDialogOfferKeyEventL( CStifItemParser& aItem );

private: // test functions in finditemmenu.h

    /**
    * test NewL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuNewL( CStifItemParser& aItem );

    /**
    * test NewLC method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuNewLCL( CStifItemParser& aItem );

    /**
    * test DisplayFindItemMenuItemL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuDisplayFindItemMenuItemL( CStifItemParser& aItem );

    /**
    * test DisplayFindItemCascadeMenuL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuDisplayFindItemCascadeMenuL( CStifItemParser& aItem );

    /**
    * test CommandIsValidL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuCommandIsValidL( CStifItemParser& aItem );

    /**
    * test SearchCase method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuSearchCaseL( CStifItemParser& aItem );

    /**
    * test UpdateItemFinderMenuL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuUpdateItemFinderMenuL( CStifItemParser& aItem );

    /**
    * test HandleItemFinderCommandL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuHandleItemFinderCommandL( CStifItemParser& aItem );

    /**
    * test AttachItemFinderMenuL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuAttachItemFinderMenuL( CStifItemParser& aItem );

    /**
    * test SetCallbackNumber method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuSetCallbackNumberL( CStifItemParser& aItem );

    /**
    * test HandleCallL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuHandleCallL( CStifItemParser& aItem );

    /**
    * test HandleVoIPCallL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuHandleVoIPCallL( CStifItemParser& aItem );

    /**
    * test SetSenderHighlightStatus method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuSetSenderHighlightStatusL( CStifItemParser& aItem );

    /**
    * test SetSenderDisplayText method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuSetSenderDisplayTextL( CStifItemParser& aItem );

    /**
    * test AddItemFindMenuL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuAddItemFindMenuL( CStifItemParser& aItem );

    /**
    * test SetSenderDescriptorType method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuSetSenderDescriptorTypeL( CStifItemParser& aItem );

    /**
    * test SetMenuItemVisibility method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestMenuSetMenuItemVisibilityL( CStifItemParser& aItem );
    
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTDOMFINDITEM_H

// End of File
