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
* Description:         Assert tool for checking test result and write log.
*
*/









#include "bctestassert.h"
#include "bctestlogger.h"

_LIT( KFailedTest, "Failed test ");
_LIT( KTestSucceed, "Test succeeded." );    
_LIT( KTrueFail, "Return value is false." );
_LIT( KNotNullFail, "Verified pointer is NULL." );
_LIT( KIntFailFormat, "Return value is not expected. It is %d." );
_LIT( KCommentFormat, "%d. %s. " ); 

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
EXPORT_C CBCTestAssert::CBCTestAssert()
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
EXPORT_C CBCTestAssert::~CBCTestAssert()
    {    
    }
    
// ---------------------------------------------------------------------------
// CBCTestAssert::SetLogger
// Setor for iLogger.
// ---------------------------------------------------------------------------
//
void CBCTestAssert::SetLogger( CBCTestLogger* aLogger )
    {
    if ( aLogger )
        {
        iLogger = aLogger;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestAssert::AssertLogL
// Write assert result to log file.
// ---------------------------------------------------------------------------
//
void CBCTestAssert::AssertLogL( TAssertType aType, TBool aSuccess, 
    const TDesC& aComments, SAssertParam* aParam )
    {
    if ( !iLogger || aType >= EAssertEnd || aType < EAssertInt )
        {
        return;
        }      
       
    iTestCount++;
    TDes& buf = iLogger->Buffer();
    buf.Zero();
    
    if ( !aSuccess )
        {
        buf.Append( KFailedTest );
        iFailedCount++;
        }
    buf.AppendFormat( 
        TPtrC( KCommentFormat ), iTestCount, aComments.Ptr() );
    if ( !aSuccess )
        {
        switch ( aType )
            { 
            case EAssertInt:                
                if ( aParam )
                    {
                    buf.AppendFormat( 
                        TPtrC( KIntFailFormat ), aParam->intValue );
                    }             
                break;
            case EAssertTrue:
                buf.Append( KTrueFail );
                break;
            case EAssertNotNull:
                buf.Append( KNotNullFail );
                break;
            default:
                break;
            }
        }
    else
        {
        buf.Append( KTestSucceed );
        }
    iLogger->CreateTimeStamp( buf );
    iLogger->WriteLogL( buf );
    }

// ---------------------------------------------------------------------------
// CBCTestAssert::AssertIntL
// ---------------------------------------------------------------------------
//
EXPORT_C void CBCTestAssert::AssertIntL( TInt aExpect, TInt aActual, const TDesC& aComments )
    {          
    SAssertParam param;
    param.intValue = aActual;
    AssertLogL( EAssertInt, ( aExpect == aActual ), aComments, &param );
    }
    
// ---------------------------------------------------------------------------
// CBCTestAssert::AssertTrueL
// ---------------------------------------------------------------------------
//
EXPORT_C void CBCTestAssert::AssertTrueL( TBool aActual, const TDesC& aComments )
    { 
    AssertLogL( EAssertTrue, aActual, aComments );
    }
    
// ---------------------------------------------------------------------------
// CBCTestAssert::AssertNotNullL
// ---------------------------------------------------------------------------
//
EXPORT_C void CBCTestAssert::AssertNotNullL( TAny* aActual, const TDesC& aComments )
    {    
    AssertLogL( EAssertNotNull, ( aActual != NULL ), aComments );
    }
    
// ---------------------------------------------------------------------------
// CBCTestAssert::WriteLogL
// Write a sentence of information to log file.
// ---------------------------------------------------------------------------
//
EXPORT_C void CBCTestAssert::WriteLogL( const TDesC& aLogText )
    {
    TDes& buf = iLogger->Buffer();
    buf.Zero();
    buf.Append( aLogText );    
    buf.Append( KLogLine );
    iLogger->WriteLogL( buf );
    }
    
// ---------------------------------------------------------------------------
// CBCTestAssert::GetTestSummary
// ---------------------------------------------------------------------------
//
void CBCTestAssert::GetTestSummary( TInt& aTestCount, 
    TInt& aFailedCount ) const
    {
    aTestCount = iTestCount;
    aFailedCount = iFailedCount;
    }
    
// ---------------------------------------------------------------------------
// CBCTestAssert::ClearTestSummary
// ---------------------------------------------------------------------------
//
void CBCTestAssert::ClearTestSummary()
    {
    iTestCount = 0;
    iFailedCount = 0;
    }
