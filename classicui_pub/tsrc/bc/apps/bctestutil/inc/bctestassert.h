/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Assert tool for checking test result
*
*/









#ifndef C_CBCTESTASSERT_H
#define C_CBCTESTASSERT_H

#include <e32std.h>
#include <e32base.h>

class CBCTestLogger;

/**
 *  CBCTestAssert
 */
class CBCTestAssert: public CBase
    {    
public: 

// constructor and destructor
    
    /**
     * C++ default constructor.
     */
    IMPORT_C CBCTestAssert();
    
    /**
     * Destructor.
     */
    IMPORT_C virtual ~CBCTestAssert();
        
// exported functions 

    /**
     * Assert tool functions. Using to verify the return value of tested API.
     * @param aExpect, the expected value.
     * @param aActual, the actual value.
     * @param aComments, one sentence of comments.
     */
    IMPORT_C void AssertIntL( TInt aExpect, TInt aActual, 
        const TDesC& aComments = KNullDesC );
        
    IMPORT_C void AssertTrueL( TBool aActual, 
        const TDesC& aComments = KNullDesC );
        
    IMPORT_C void AssertNotNullL( TAny* aActual, 
        const TDesC& aComments = KNullDesC );    
    
    /**
     * Write one sentence of log.
     * @param aLogText
     */
    IMPORT_C void WriteLogL( const TDesC& aLogText );
    
// new functions
    
    /**
     * Set a pointer to logger.
     * @param aLogger, a pointer to a logger object.
     */
    void SetLogger( CBCTestLogger* aLogger );
    
    /**
     * Clear test statistic data. i.e. iTestCount and iFailedCount
     */
    void ClearTestSummary();
    
    /**
     * Get test statistic data.
     */    
    void GetTestSummary( TInt& aTestCount, TInt& aFailedCount ) const;

protected:

// declaration
    
    /**
     * The type of assert function.
     */
    enum TAssertType        
        {
        EAssertInt,
        EAssertTrue,
        EAssertNotNull,
        EAssertEnd
        };
    
    struct SAssertParam
        {
        TInt intValue;
        TAny* ptValue;        
        };
        
// new functions
    
    /**
     * Wrtie log of assert result.
     * @param aType, what type of value has been checked.
     * @param aSuccess, whether the test passed.
     * @param aComments, comments about the assert.
     */
    void AssertLogL( TAssertType aType, TBool aSuccess, 
        const TDesC& aComments, SAssertParam* param = NULL );
        
private: // data
    
    /**
     * Used to write log.
     * Not own.
     */
    CBCTestLogger* iLogger;
    
    /**
     * How many asserts failed totally.
     */
    TInt iFailedCount;
    
    /**
    * How many assert done totally.
    */
    TInt iTestCount;
    
    };
    
#endif // C_CBCTESTASSERT_H