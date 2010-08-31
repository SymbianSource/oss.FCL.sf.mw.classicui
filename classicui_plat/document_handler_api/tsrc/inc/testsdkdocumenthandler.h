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
* Description:  test document_handler_api 
*
*/


#ifndef C_TESTSDKDOCUMENTHANDLER_H
#define C_TESTSDKDOCUMENTHANDLER_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <eikenv.h>
#include <errorui.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkdocumenthandlerLogPath, "\\logs\\testframework\\testsdkdocumenthandler\\" ); 
// Log file
_LIT( KtestsdkdocumenthandlerLogFile, "testsdkdocumenthandler.txt" ); 
_LIT( KtestsdkdocumenthandlerLogFileWithTitle, "testsdkdocumenthandler_[%S].txt" );

/**
*  CTestSDKDocumentHandler test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKDocumentHandler ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKDocumentHandler* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKDocumentHandler();

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
    CTestSDKDocumentHandler( CTestModuleIf& aTestModuleIf );

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

private: // Test DocumentHandler.h
/*                               class CDocumentHandler                    */
    /**
     * TestDHNewPL test function for testing the 
     *     NewL function with CEikProcess
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHNewPL( CStifItemParser& aItem );
    
    /**
     * TestDHNewLC test function for testing the 
     *     NewLC function with CEikProcess
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHNewPLC( CStifItemParser& aItem );
    
    /**
     * TestDHNewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHNewL( CStifItemParser& aItem );
    
    /**
     * TestDHNewLC test function for testing the 
     *     NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHNewLC( CStifItemParser& aItem );
    
    /**
     * TestDHDeconstructorL test function for testing the 
     *     ~CDocumentHandler function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestDHOpenTempFileL test function for testing the 
     *     OpenTempFileL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHOpenTempFileL( CStifItemParser& aItem );
    
    /**
     * TestDHSaveTempFileL test function for testing the 
     *     SaveTempFileL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHSaveTempFileL( CStifItemParser& aItem );
    
    /**
     * TestDHInParamListL test function for testing the 
     *     InParamListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHInParamListL( CStifItemParser& aItem );
    
    /**
     * TestDHOutParamListL test function for testing the 
     *     OutParamList function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHOutParamListL( CStifItemParser& aItem );
    
    /**
     * TestDHOpenFileRL test function for testing the 
     *     OpenFileL function with RFile
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHOpenFileRL( CStifItemParser& aItem );
    
    /**
     * TestDHOpenFileEmbeddedGPL test function for testing the 
     *     OpenFileEmbeddedL function with CAiwGenericParamList
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHOpenFileEmbeddedGPL( CStifItemParser& aItem );
    
    /**
     * TestDHOpenFileEmbeddedRL test function for testing the 
     *     OpenFileEmbeddedL function with RFile
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHOpenFileEmbeddedRL( CStifItemParser& aItem );
    
    /**
     * TestDHOpenFileL test function for testing the 
     *     OpenFileL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHOpenFileL( CStifItemParser& aItem );
    
    /**
     * TestDHOpenFileEmbeddedL test function for testing the 
     *     OpenFileEmbeddedL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHOpenFileEmbeddedL( CStifItemParser& aItem );
    
    /**
     * TestDHSaveL test function for testing the 
     *     SaveL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHSaveL( CStifItemParser& aItem );
    
    /**
     * TestDHSaveNL test function for testing the 
     *     SaveL function with Name
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHSaveNL( CStifItemParser& aItem );
    
    /**
     * TestDHCopyL test function for testing the 
     *     CopyL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHCopyL( CStifItemParser& aItem );
    
    /**
     * TestDHCopyRL test function for testing the 
     *     CopyL function with RFile
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHCopyRL( CStifItemParser& aItem );
    
    /**
     * TestDHMoveL test function for testing the 
     *     MoveL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHMoveL( CStifItemParser& aItem );
    
    /**
     * TestDHSilentMoveL test function for testing the 
     *     SilentMoveL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHSilentMoveL( CStifItemParser& aItem );
    
    /**
     * TestDHCanHandleL test function for testing the 
     *     CanHandleL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHCanHandleL( CStifItemParser& aItem );
    
    /**
     * TestDHCanOpenL test function for testing the 
     *     CanOpenL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHCanOpenL( CStifItemParser& aItem );
    
    /**
     * TestDHCanSaveL test function for testing the 
     *     CanSaveL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHCanSaveL( CStifItemParser& aItem );
    
    /**
     * TestDHGetPathL test function for testing the 
     *     GetPath function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHGetPathL( CStifItemParser& aItem );
    
    /**
     * TestDHHandlerAppUidL test function for testing the 
     *     HandlerAppUid function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHHandlerAppUidL( CStifItemParser& aItem );
    
    /**
     * TestDHSetExitObserverL test function for testing the 
     *     SetExitObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHSetExitObserverL( CStifItemParser& aItem );
    
    /**
     * TestDHCheckFileNameExtensionL test function for testing the 
     *     CheckFileNameExtension function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHCheckFileNameExtensionL( CStifItemParser& aItem );
    
    /**
     * TestDHCanHandleProgressivelyL test function for testing the 
     *     CanHandleProgressivelyL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHCanHandleProgressivelyL( CStifItemParser& aItem );
    
    /**
     * TestDHGetProgressiveDownloadAppUidsL test function for testing the 
     *     GetProgressiveDownloadAppUidsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDHGetProgressiveDownloadAppUidsL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * CEikonEnv 
     */
    CEikonEnv* iEikonEnvPointer;
    
    };

#endif      // C_TESTSDKDOCUMENTHANDLER_H

// End of File
