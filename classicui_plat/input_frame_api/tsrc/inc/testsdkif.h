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
* Description:  akninfrm.h
*
*/



#ifndef C_TESTSDKIF_H
#define C_TESTSDKIF_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include "testsdkifcontainer.h"

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkifLogPath, "\\logs\\testframework\\testsdkif\\" ); 
// Log file
_LIT( KtestsdkifLogFile, "testsdkif.txt" ); 
_LIT( KtestsdkifLogFileWithTitle, "testsdkif_[%S].txt" );

class CAknInputFrame;
class CInputFrameContainer;
/**
*  CTestSDKIF test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKIF) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKIF* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKIF();

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
    CTestSDKIF( CTestModuleIf& aTestModuleIf );

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

    //[TestMethods]akninfrm.h
private:
    /**
    * NewL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFNewL( CStifItemParser& aItem );    
    /**
    * NewLWithIcon test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFNewWithIconL( CStifItemParser& aItem );    
    /**
    * delete test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFdelete( CStifItemParser& aItem );    
    /**
    * Field test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFField( CStifItemParser& aItem );    
    /**
    * SetInfoTextL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFSetInfoTextL( CStifItemParser& aItem );    
    /**
    * SetLineState test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFSetLineState( CStifItemParser& aItem );    
    /**
     * HandleControlEventL test method.
     * @since S60 5.0
     * @param aItem Script line containing parameters.
     * @return Symbian OS error code.
     */
       virtual TInt TestIFHandleControlEventL( CStifItemParser& aItem );    
    /**
    * OfferKeyEventL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFOfferKeyEventL( CStifItemParser& aItem );
    /**
    * MinimumSize test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFMinimumSize( CStifItemParser& aItem );
    /**
    * ConstructFromResourceL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFConstructFromResourceL( CStifItemParser& aItem );
    /**
    * ConstructFromResourceL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFSetInputContextL( CStifItemParser& aItem );
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    //Own for test the akninfrm.h
    CAknInputFrame* iInputFrame;
    CInputFrameContainer *iInputFrameContainer;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKIF_H

// End of File
