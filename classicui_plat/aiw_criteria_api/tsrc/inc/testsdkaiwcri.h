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
* Description:    Test aiw_criteria_api
 *
*/




#ifndef C_TESTSDKAIWCRI_H
#define C_TESTSDKAIWCRI_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <coemain.h>
#include <coeaui.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkaiwcriLogPath, "\\logs\\testframework\\testsdkaiwcri\\" );
// Log file
_LIT( KtestsdkaiwcriLogFile, "testsdkaiwcri.txt" );
_LIT( KtestsdkaiwcriLogFileWithTitle, "testsdkaiwcri_[%S].txt" );

// FORWARD DECLARATIONS
class CTestSDKAiwCri;
class CAiwCriteriaItem;

/**
 *  CTestSDKAiwCri test class for STIF Test Framework TestScripter.
 *  ?other_description_lines
 *
 *  @lib ?library
 *  @since ?Series60_version
 */
NONSHARABLE_CLASS( CTestSDKAiwCri ) : public CScriptBase
    {
public: // Constructors and destructor

    /**
     * Two-phased constructor.
     */
    static CTestSDKAiwCri* NewL( CTestModuleIf& aTestModuleIf );

    /**
     * Destructor.
     */
    virtual ~CTestSDKAiwCri();

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
    CTestSDKAiwCri( CTestModuleIf& aTestModuleIf );

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

private: // Test AiwCommon.h
    /**
     * TestACINewL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACINewL( CStifItemParser& /*aItem*/ );

    /**
     * TestACINewLC test function for testing the NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACINewLC( CStifItemParser& /*aItem*/ );

    /**
     * TestACINewLIDL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACINewLIDL( CStifItemParser& /*aItem*/ );

    /**
     * TestACINewLCIDL test function for testing the NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACINewLCIDL( CStifItemParser& /*aItem*/ );

    /**
     * TestACISetId test function for testing the SetId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACISetId( CStifItemParser& /*aItem*/ );

    /**
     * TestACISetServiceClass test function for testing the SetServiceClass function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACISetServiceClass( CStifItemParser& /*aItem*/ );

    /**
     * TestACISetServiceCmd test function for testing the SetServiceCmd function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACISetServiceCmd( CStifItemParser& /*aItem*/ );

    /**
     * TestACISetContentTypeL test function for testing the SetContentTypeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACISetContentTypeL( CStifItemParser& /*aItem*/ );

    /**
     * TestACIId test function for testing the Id function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACIId( CStifItemParser& /*aItem*/ );

    /**
     * TestACIServiceClass test function for testing the ServiceClass function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACIServiceClass( CStifItemParser& /*aItem*/ );

    /**
     * TestACIServiceCmd test function for testing the ServiceCmd function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACIServiceCmd( CStifItemParser& /*aItem*/ );

    /**
     * TestACIContentType test function for testing the ContentType function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACIContentType( CStifItemParser& /*aItem*/ );

    /**
     * TestACISetOptions test function for testing the SetOptions function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACISetOptions( CStifItemParser& /*aItem*/ );

    /**
     * TestACIOptions test function for testing the Options function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACIOptions( CStifItemParser& /*aItem*/ );

    /**
     * TestACIMaxProviders test function for testing the MaxProviders function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACIMaxProviders( CStifItemParser& /*aItem*/ );

    /**
     * TestACIReadFromResoureL test function for testing the ReadFromResoureL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACIReadFromResoureL( CStifItemParser& /*aItem*/ );

    /**
     * TestACIDefaultProvider test function for testing the DefaultProvider function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACIDefaultProvider( CStifItemParser& /*aItem*/ );

    /**
     * TestACISetDefaultProvider test function for testing the SetDefaultProvider function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACISetDefaultProvider( CStifItemParser& /*aItem*/ );

    /**
     * TestACIOperatorL test function for testing the Operator function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACIOperatorL( CStifItemParser& /*aItem*/ );

    /**
     * TestACISetMaxProviders test function for testing the SetMaxProviders function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACISetMaxProviders( CStifItemParser& /*aItem*/ );

    /**
     * TestACIRomOnly test function for testing the RomOnly function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACIRomOnly( CStifItemParser& /*aItem*/ );

    /**
     * TestACIDelete test function for testing the destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACIDelete( CStifItemParser& /*aItem*/) ;


private: // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    //Own : test functions in AiwCommon.h
    CAiwCriteriaItem* iAiwCriItem;

    // Resource file offset
    TInt iOffset;


    };

#endif      // C_TESTSDKAIWCRI_H
// End of File
