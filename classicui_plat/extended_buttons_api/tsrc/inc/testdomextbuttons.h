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
* Description:  test functions in extended_buttons_api
*
*/



#ifndef C_TESTDOMEXTBUTTONS_H
#define C_TESTDOMEXTBUTTONS_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

#include <eikimage.h>
#include <eiksoftkeyimage.h>
#include <eiksoftkeypostingtransparency.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestdomextbuttonsLogPath, "\\logs\\testframework\\testdomextbuttons\\" ); 
// Log file
_LIT( KtestdomextbuttonsLogFile, "testdomextbuttons.txt" ); 
_LIT( KtestdomextbuttonsLogFileWithTitle, "testdomextbuttons_[%S].txt" );

/**
*  CTestDomExtButtons test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDomExtButtons ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDomExtButtons* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDomExtButtons();

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
    CTestDomExtButtons( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // [TestMethods]
    /**
    * TestEikSoftkeyImageSetImageL tests SetImage
    * of EikSoftkeyImage in EikSoftkeyImage.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEikSoftkeyImageSetImageL( CStifItemParser& aItem );
    
    /**
    * TestEikSoftkeyImageSetLabelL tests SetLabel
    * of EikSoftkeyImage in EikSoftkeyImage.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEikSoftkeyImageSetLabelL( CStifItemParser& aItem );
    
    /**
    * TestEikSoftkeyPostTransMakeTransparentL tests MakeTransparent
    * of EikSoftkeyPostingTransparency in eiksoftkeypostingtransparency.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEikSoftkeyPostTransMakeTransparentL( CStifItemParser& aItem );
    

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    };

#endif      // C_TESTDOMEXTBUTTONS_H

// End of File
