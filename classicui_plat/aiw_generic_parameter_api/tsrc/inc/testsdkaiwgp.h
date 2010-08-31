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
* Description:    test classes and functions in AiwGenericParam.h and AiwVariant.h
 *
*/




#ifndef C_TESTSDKAIWGP_H
#define C_TESTSDKAIWGP_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stifitemparser.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <aiwvariant.h>
#include <aiwvarianttype.hrh>
#include <aiwgenericparam.h>
#include <aiwgenericparam.hrh>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkaiwgpLogPath, "\\logs\\testframework\\testsdkaiwgp\\" );
// Log file
_LIT( KtestsdkaiwgpLogFile, "testsdkaiwgp.txt" );
_LIT( KtestsdkaiwgpLogFileWithTitle, "testsdkaiwgp_[%S].txt" );

/**
 *  CTestSDKAiwgp test class for STIF Test Framework TestScripter.
 *  @since S60 5.0
 */
NONSHARABLE_CLASS(CTestSDKAiwgp) : public CScriptBase
    {
public: // Constructors and destructor

    /**
     * Two-phased constructor.
     */
    static CTestSDKAiwgp* NewL( CTestModuleIf& aTestModuleIf );

    /**
     * Destructor.
     */
    virtual ~CTestSDKAiwgp();

public: // Functions from base classes

    /**
     * From CScriptBase Runs a script line.
     * @since ?Series60_version
     * @param aItem Script line containing method name and parameters
     * @return Symbian OS error code
     */
    virtual TInt RunMethodL( CStifItemParser& aItem );

private:

    /**
     * C++ default constructor.
     */
    CTestSDKAiwgp( CTestModuleIf& aTestModuleIf );

    /**
     * By default Symbian 2nd phase constructor is private.
     */
    void ConstructL();

    /**
     * Frees all resources allocated from test methods.
     * @since ?Series60_version
     */
    void Delete();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // test functions
    /**
     * TestTAiwVariantL test TAiwVariant function
     * @since S60 5.0
     * @param aItem never used
     * return Symbian OS error code.
     */
    virtual TInt TestTAiwVariantL( CStifItemParser& aItem );
    /**
     * test some function of TAiwVariant in default constructor
     * @since S60 5.0
     * @param aItem never used
     * return Symbian OS error code.
     */
    virtual TInt TestAiwVFuncByDefaultConstructor();
    /**
     * test some function in of TAiwVariant TInt32 constructor
     * @since S60 5.0
     * @param aItem never used
     * return Symbian OS error code.
     */
    virtual TInt TestAiwVFuncByTInt32Constructor();
    /**
     * test some function of TAiwVariant in TUid constructor
     * @since S60 5.0
     * @param aItem never used
     * return Symbian OS error code.
     */
    virtual TInt TestAiwVFuncByTUidConstructor();
    /**
     * test some function in of TAiwVariant TDesC constructor
     * @since S60 5.0
     * @param aItem never used
     * return Symbian OS error code.
     */
    virtual TInt TestAiwVFuncByTDesCConstructor();
    /**
     * test some function in of TAiwVariant HBufC constructor
     * @since S60 5.0
     * @param aItem never used
     * return Symbian OS error code.
     */
    virtual TInt TestAiwVFuncByHBufCConstructorL();
    /**
     * test some function in of TAiwVariant TDesC8 constructor
     * @since S60 5.0
     * @param aItem never used
     * return Symbian OS error code.
     */
    virtual TInt TestAiwVFuncByTDesC8Constructor();
    /**
     * test some function in of TAiwVariant TTime constructor
     * @since S60 5.0
     * @param aItem never used
     * return Symbian OS error code.
     */
    virtual TInt TestAiwVFuncByTTimeConstructor();
    /**
     * test some function in of TAiwVariant RFile constructor
     * @since S60 5.0
     * @param aItem never used
     * return Symbian OS error code.
     */
    virtual TInt TestAiwVFuncByRFileConstructorL();
    /**
     * test some function in of TAiwVariant Copy constructor
     * @since S60 5.0
     * @param aItem never used
     * return Symbian OS error code.
     */
    virtual TInt TestAiwVFuncByCopyConstructor();

    /**
     * TestTAiwGP test TAiwGenericParam function
     * @since S60 5.0
     * @aItem is three number of TAiwGenericParam SemanticId
     * return Symbian OS error code.
     */
    virtual TInt TestTAiwGP( CStifItemParser& aItem );
    /**
     * test TAiwGenericParam function in default constructor
     * @since S60 5.0
     * @aItem is the number for id set testting 
     * return Symbian OS error code.
     */
    virtual TInt TestAiwGPFuncByDefaultConstructor( CStifItemParser& aItem );
    /**
     * test TAiwGenericParam function in constructor with one parameter
     * @since S60 5.0
     * @aItem is the number for id set testting
     * return Symbian OS error code.
     */
    virtual TInt TestAiwGPFuncByConstructorOnePara( CStifItemParser& aItem );
    /**
     * test TAiwGenericParam function in constructor with two parameters
     * @since S60 5.0
     * @aItem is the number for id set testting
     * return Symbian OS error code.
     */
    virtual TInt TestAiwGPFuncByConstructorTwoPara( CStifItemParser& aItem );

    /**
     * Test CAiwGenericParamList, test four new functions
     * @since S60 5.0
     * @param aItem never used
     * return Symbian OS error code.
     */
    virtual TInt TestTAiwGPListNewFunctionsL( CStifItemParser& aItem );
   
    /**
    * Test Count function of CAiwGenericParamList
    * @since S60 5.0
    * @aItem 1 is the list count, 2 is the count of some type
    * return Symbian OS error code.
    */
    virtual TInt TestTAiwGPListCountL( CStifItemParser& aItem );
  
    /**
    * Test [] operator of CAiwGenericParamList
    * @since S60 5.0
    * @param aItem never used
    * return Symbian OS error code.
    */
    virtual TInt TestTAiwGPListSquareBracketL( CStifItemParser& aItem );
    
    /**
    * Test two AppendL functions of CAiwGenericParamList
    * @since S60 5.0
    * @aItem is a number 1 append a item, 2 append a list
    * return Symbian OS error code.
    */
    virtual TInt TestTAiwGPListAppendL( CStifItemParser& aItem );
    
    /**
    * Test Reset function of CAiwGenericParamList
    * @since S60 5.0
    * @param aItem never used
    * return Symbian OS error code.
    */
    virtual TInt TestTAiwGPListResetL( CStifItemParser& aItem );
    
    /**
    * Test two Find functions of CAiwGenericParamList
    * @since S60 5.0
    * @aItem is a number, 1 is find the first item, 2 is find the next item
    * return Symbian OS error code.
    */
    virtual TInt TestTAiwGPListFindL( CStifItemParser& aItem );
    
    /**
    * Test Size function of CAiwGenericParamList
    * @since S60 5.0
    * @param aItem never used
    * return Symbian OS error code.
    */
    virtual TInt TestTAiwGPListSizeL( CStifItemParser& aItem );
    
    /**
    * Test Remove function of CAiwGenericParamList
    * @since S60 5.0
    * @param aItem never used
    * return Symbian OS error code.
    */
    virtual TInt TestTAiwGPListRemoveL( CStifItemParser& aItem );
    
    /**
    * Test InternalizeL and ExternalizeL function of CAiwGenericParamList
    * @since S60 5.0
    * @param aItem never used
    * return Symbian OS error code.
    */
    virtual TInt TestTAiwGPListInternalizeLAndExternalizeL( CStifItemParser& aItem );
    
    /**
    * Test PackForServerL function of CAiwGenericParamList
    * @since S60 5.0
    * @param aItem never used
    * return Symbian OS error code.
    */
    virtual TInt TestTAiwGPListPackForServerL( CStifItemParser& aItem );
    
    /**
    * Test UnpackFromClientL function of CAiwGenericParamList
    * @since S60 5.0
    * @param aItem never used
    * return Symbian OS error code.
    */
    virtual TInt TestTAiwGPListUnpackFromClientL( CStifItemParser& aItem );

private: // Data
    
    enum TSwitchId
        {
        ECaseOne = 1,
        ECaseTwo
        };
    
    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    };

#endif      // C_TESTSDKAIWGP_H
// End of File
