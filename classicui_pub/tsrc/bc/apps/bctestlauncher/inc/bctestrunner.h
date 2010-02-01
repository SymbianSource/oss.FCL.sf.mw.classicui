/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Handles test application runs.
*
*/









#ifndef C_CBCTESTRUNNER_H
#define C_CBCTESTRUNNER_H

#include <eikenv.h>

class CAknAtLogWriter;
class CBCTestApplication;

/**
 * TestRunner, manage all test applications
 */
class CBCTestRunner : public CBase
    {
public:  // Constructors and destructor
    
    /**
    * Two-phased constructor.
    */
    static CBCTestRunner* NewL();
    
    /**
    * Destructor.
    */
    virtual ~CBCTestRunner();

// New methods

    /**
    * Starts test application and returns after test is over
	* @param aCommand, a command to indicate run full test, partial test,
	* or selected test.
	* @return ETrue if run sucessfully, else it will return EFalse.
    */
    TBool RunL( TInt aCommand );

	/**
	* Add new BC test application to the test runner.
	* @param aApp, the pointer to the bc test application.
	*/
    void AddTestAppL(CBCTestApplication* aApp);

	/**
	* return the BC test application list
	*/
	RArray<CBCTestApplication*>* Apps();

private:

    /**
    * C++ default constructor.
    */
    CBCTestRunner();

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
    * Creates time stamp for log file
    */
    void CreateTimeStamp();


private: // data

    RArray<CBCTestApplication*> iTestApps;
    TBuf8<1024> iBuf;   // temp storage for log writing
    TBuf<50> iTempBuf;   // for timestamp creating
    
    };

#endif //C_CBCTESTRUNNER_H
