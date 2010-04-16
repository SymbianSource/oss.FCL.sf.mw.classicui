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
* Description:  Test number_grouping_api
*
*/



#ifndef C_TESTDOMNUMBERGROUPING_H
#define C_TESTDOMNUMBERGROUPING_H

/*
 * INCLUDES
 */
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

/*
 * Declare class
 */ 
class CAknPhoneNumberGrouping;
class CPNGNumberGrouping;
// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

/*
 *  Logging path
 */
_LIT( KtestdomnumbergroupingLogPath, "\\logs\\testframework\\testdomnumbergrouping\\" ); 
/*
 *  Log file
 */
_LIT( KtestdomnumbergroupingLogFile, "testdomnumbergrouping.txt" ); 
_LIT( KtestdomnumbergroupingLogFileWithTitle, "testdomnumbergrouping_[%S].txt" );

/**
*  CTestDOMNUMBERGROUPING test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestDOMNUMBERGROUPING) : public CScriptBase
    {
public:

    /**
    * Two-phased constructor.
    */
    static CTestDOMNUMBERGROUPING* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMNUMBERGROUPING();

public:

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
    CTestDOMNUMBERGROUPING( CTestModuleIf& aTestModuleIf );

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
     * TestPHONENUMGRPINGNewLCL test function for testing the NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPHONENUMGRPINGNewLCL( CStifItemParser& /*aItem*/ );
    /**
     * TestPHONENUMGRPINGNewLL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPHONENUMGRPINGNewLL( CStifItemParser& /*aItem*/ );
    /**
     * TestPHONENUMGRPINGSetL test function for testing the Set function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPHONENUMGRPINGSetL( CStifItemParser& /*aItem*/ );
    /**
     * TestPHONENUMGRPINGFormattedNumberL test function for testing the 
     * FormattedNumber function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPHONENUMGRPINGFormattedNumberL( CStifItemParser& /*aItem*/ );
    /**
     * TestPHONENUMGRPINGCopyFormattedNumberL test function for testing the 
     * FormattedNumber function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPHONENUMGRPINGCopyFormattedNumberL( CStifItemParser& /*aItem*/ );
    /**
     * TestPHONENUMGRPINGCreateGroupedPhoneNumberL test function for testing the 
     * CreateGroupedPhoneNumber function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPHONENUMGRPINGCreateGroupedPhoneNumberL( CStifItemParser& /*aItem*/ );
    /**
     * TestPHONENUMGRPINGGroupPhoneNumberGroupL test function for testing the 
     * GroupPhoneNumberGroup function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPHONENUMGRPINGGroupPhoneNumberGroupL( CStifItemParser& /*aItem*/ );
    /**
	 * TestPHONENUMGRPINGGroupPhoneNumberPhoneL test function for testing the
	 * GroupPhoneNumberPhone function
	 * @since S60 5.0
	 * @param aItem never used
	 * @return Symbian OS error code.
	 */
    virtual TInt TestPHONENUMGRPINGGroupPhoneNumberPhoneL( CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGNewLL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGNewLL( CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGNewLCL test function for testing the NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGNewLCL( CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGDestructorL( CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGInsertL test function for testing the Insert function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGInsertL( CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGDeleteL test function for testing the Delete function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGDeleteL( CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGAppendL test function for testing the Append function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGAppendL( CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGSetL test function for testing the Set function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGSetL( CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGLengthL test function for testing the Length function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGLengthL( CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGUnFormattedLengthL test function for testing the
     * UnFormattedLength function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGUnFormattedLengthL( CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGMaxDisplayLengthL test function for testing the 
     * MaxDisplayLength function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGMaxDisplayLengthL( CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGIsSpaceL test function for testing the IsSpace function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGIsSpaceL( CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGFormattedNumberL test function for testing the 
     * FormattedNumber function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGFormattedNumberL( CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGFormattedNumberNullL test function for testing the 
     * FormattedNumber function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGFormattedNumberNullL( CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGReverseFormattedNumberL test function for testing the 
     * ReverseFormattedNumber function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGReverseFormattedNumberL( CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGReverseFormattedNumberNullL test function for testing the 
     * ReverseFormattedNumber function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGReverseFormattedNumberNullL( CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGSelectionL test function for testing the Selection function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGSelectionL( CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGUnFormattedNumberL test function for testing the UnFormattedNumber 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGUnFormattedNumberL( CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGUnFormattedNumberNullL test function for testing the 
     * UnFormattedNumber function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGUnFormattedNumberNullL( CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGIsCharacterInsertedByNumberGroupingL test function for testing 
     * the IsCharacterInsertedByNumberGrouping function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGIsCharacterInsertedByNumberGroupingL( 
                CStifItemParser& /*aItem*/ );
    /**
     * TestNUMGRPINGIsChangedByGroupingL test function for testing the 
     * IsChangedByGrouping function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNUMGRPINGIsChangedByGroupingL( CStifItemParser& /*aItem*/ );
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private:    

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    


    };

#endif  

/*
 * 
 *  End of File
 */
