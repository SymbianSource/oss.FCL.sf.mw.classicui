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
* Description:  Test AknClearer.h & eikspace.h
*
*/



#ifndef C_TESTSDKSCREENCLEARER_H
#define C_TESTSDKSCREENCLEARER_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

// MACROS
//#define ?macro ?macro_def
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkscreenclearerLogPath, "\\logs\\testframework\\testsdkscreenclearer\\" ); 
// Log file
_LIT( KtestsdkscreenclearerLogFile, "testsdkscreenclearer.txt" ); 
_LIT( KtestsdkscreenclearerLogFileWithTitle, "testsdkscreenclearer_[%S].txt" );


// FORWARD DECLARATIONS
class CTestsSDKScreenClearer;
class CEikSpacer;
/**
*  Ctestsdkscreenclearer test class for STIF Test Framework TestScripter.
*
*  @lib 
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestsSDKScreenClearer) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CTestsSDKScreenClearer* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTestsSDKScreenClearer();

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
        CTestsSDKScreenClearer( CTestModuleIf& aTestModuleIf );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

        /**
        * Frees all resources allocated from test methods.
        * @since s60 5.0
        */
        void Delete();

private: //acknclearer.h  class CAknLocalScreenClearer
    /**
     * TestLSCNewL test function for testing the NewL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLSCNewL( CStifItemParser& aItem );
    /**
     * TestLSCNewLC test function for testing the NewLC function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLSCNewLC( CStifItemParser& aItem );
    /**
     * TestLSCSNewLC test function for testing the NewLC function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLSCSNewLC( CStifItemParser& aItem );
    /**
     * TestSCBHandleStatusPaneSizeChangeL test function for 
     * testing the HandleStatusPaneSizeChangeL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSCBHandleStatusPaneSizeChangeL( CStifItemParser& aItem );
     /**
     * TestSCBHandlePointerEventL test function for testing the HandlePointerEventL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSCBHandlePointerEventL( CStifItemParser& aItem );
    /**
     * TestSCBHandleResourceChangeL test function for testing the HandleResourceChange function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestSCBHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
     * TestSCBDeleteL test function for testing the Destruction function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestSCBDeleteL( CStifItemParser& aItem );
    
    /**
     * TestSCBDeleteL test function for testing the Destruction function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
    */
    virtual TInt TestSCBConstructL( CStifItemParser& aItem );

private://eikspace.h
    /**
     * TestSpacerConstructorL test function for testing the Constructor function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSpacerConstructorL( CStifItemParser& aItem );
    /**
     * TestSpacerSConstructorL test function for testing the Constructor function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSpacerSConstructorL( CStifItemParser& aItem );
    /**
     * TestSpacerDestructor test function for testing the Destructor function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSpacerDestructor( CStifItemParser& aItem );
    /**
     * TestSpacerSetWidth test function for testing the SetWidth function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSpacerSetWidth( CStifItemParser& aItem );
    /**
     * TestSpacerSetHeight test function for testing the SetHeight function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSpacerSetHeight( CStifItemParser& aItem );
    /**
     * TestSpacerSetColor test function for testing the SetColor function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSpacerSetColor( CStifItemParser& aItem );
    /**
     * TestSpacerSetClear test function for testing the SetClear function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSpacerSetClear( CStifItemParser& aItem );
    /**
     * TestSpacerHandlePointerEventL test function for testing the 
     * HandlePointerEventL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSpacerHandlePointerEventL( CStifItemParser& aItem );
    
private:    // Data
    /**
     * Not own, for test CEikSpacer
     */
    CEikSpacer* iSpacer;
    };
#endif      // C_TESTSDKSCREENCLEARER_H

// End of File
