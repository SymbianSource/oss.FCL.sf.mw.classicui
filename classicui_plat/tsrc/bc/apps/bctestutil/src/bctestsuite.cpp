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
* Description:         Test suite.
*
*/









#include <eikenv.h>
#include <coeaui.h>
#include <eikappui.h>
#include <eikapp.h>

#include "bctestlogger.h"
#include "bctestsuite.h"
#include "bctestcase.h"
#include "bctestendcase.h"

_LIT( KLeaveLog, "\r\n\r\nTest case %s leaved. Leave reason is %d." );
_LIT( KNoCommandsInCase, 
                "No automatic test commands defined in test case %s!\r\n" );
_LIT( KUnbalancedIf, 
                "Unbalanced ifs/endifs in test case %s!\r\n\r\n" );
_LIT( KCaseStartLog, ", case %d start " );
_LIT( KCaseEndLog, ", case %d end " );
_LIT( KUnnamedCase, "Unnamed case" );
_LIT( KStartInfo, 
    " Total %d cases will be tested in the application. \r\n\r\n\r\n" );
_LIT( KCompletedTest, "%s completed testing work." );
_LIT( KSummary, "\r\nSummary:\r\nTotal %d cases were tested.\r\nThere are \
%d cases including failed tests.\r\nTotal %d asserted tests and %d \
failed tests.\r\n" );
_LIT( KSummaryFailLog, "Those cases including failed tests are " );
_LIT( KSummaryComma, ", " );
_LIT( KSummaryDot, ". " );
_LIT( KSummaryFailFormat, "case %d");    

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestSuite::CBCTestSuite( CBCTestLogger* aLogger )
    : iLogger( aLogger )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestSuite::~CBCTestSuite()
    {
    for ( TInt i=0; i<iTestCases.Count(); i++ )
        {
        delete iTestCases[i];
        }
    iTestCases.Close();
    }

// ---------------------------------------------------------------------------
// CBCTestSuite::RunL
// Pass an command to test case for executing some test work.
// ---------------------------------------------------------------------------
//
void CBCTestSuite::RunL(int aCmd)
    {
    for ( TInt i=0; i<iTestCases.Count(); i++ )
        {
        TRAPD( errno, iTestCases[i]->RunL(aCmd) );
        if ( errno != KErrNone )
            {            
            TDes& buf = iLogger->Buffer();
            buf.AppendFormat( 
                TPtrC( KLeaveLog ), iTestCases[i]->Name().Ptr(), errno );            
            iLogger->CreateTimeStamp( buf );            
            buf.Append( KLogLine );
            iLogger->WriteLogL( buf );
            }
        }
    }

// ---------------------------------------------------------------------------
// CBCTestSuite::AddTestCaseL
// Add a test case pointer and name of the test case.
// ---------------------------------------------------------------------------
//
void CBCTestSuite::AddTestCaseL( CBCTestCase* aTestCase, const TDesC& aName )
    {
    aTestCase->SetLogger( iLogger );
    aTestCase->SetName( aName );
    iTestCases.AppendL( aTestCase );
    }

// ---------------------------------------------------------------------------
// CBCTestSuite::AddTestCaseL
// Build parameter of automatic test.
// ---------------------------------------------------------------------------
//
void CBCTestSuite::BuildScriptsL( SAutoTest* aAutoTest )
    {  
    if ( !aAutoTest )
        {
        return;
        }
    TInt type = iTestCases[iTestCases.Count() - 1]->Type();    
    if ( type != CBCTestCase::EEndCase )
        {
        CBCTestEndCase* endCase = CBCTestEndCase::NewL();        
        CleanupStack::PushL( endCase );
        endCase->SetType( CBCTestCase::EEndCase );
        AddTestCaseL( endCase, KNullDesC );
        CleanupStack::Pop( endCase );
        }
    
    aAutoTest->scriptCount = iTestCases.Count();
    aAutoTest->countArray = new( ELeave ) TInt[aAutoTest->scriptCount];    
    aAutoTest->scripts = new( ELeave ) TInt*[aAutoTest->scriptCount];
    
    for ( TInt i=0; i< aAutoTest->scriptCount; i++ )
        {        
        aAutoTest->countArray[i] = iTestCases[i]->ScriptCount();
        aAutoTest->scripts[i] = iTestCases[i]->TestScripts();
        aAutoTest->nameArray.Append( iTestCases[i]->Name() );        
        }
    }

// -----------------------------------------------------------------------------
// CBCTestSuite::HandleTestEvent
// -----------------------------------------------------------------------------
//
void CBCTestSuite::HandleTestEventL( TBCTestEvent aEvent, TInt aParam )
    {
    TInt scriptIndex = aParam;
    if ( scriptIndex < 0 || scriptIndex >= iTestCases.Count() )
        {
        return;
        }
    switch ( aEvent )
        {
        case ETestCaseStart:
            {
            iTestCases[scriptIndex]->ClearTestSummary();
            if ( scriptIndex == 0)
                {
                WriteStartLogL();
                }
            WriteTestCaseLogL( scriptIndex, ETrue );            
            }
            break;
        case ETestCaseEnd:
            {
            WriteTestCaseLogL( scriptIndex, EFalse );
            // The end case is not considered by user. So the test case 
            // before end case is actually the fianl case.
            TInt actualCaseCount = iTestCases.Count() - 1;            
            // The last index is actualCaseCount - 1
            if ( scriptIndex == actualCaseCount - 1 )
                {                
                WriteSummaryLogL();
                }            
            }
            break;
        case ETestCaseNoScript:
            {            
            TDes& buf = iLogger->Buffer();
            buf.Zero();
            buf.AppendFormat( TPtrC( KNoCommandsInCase ), 
                iTestCases[scriptIndex]->Name().Ptr() );
            iLogger->WriteLogL( buf );
            }
            break;
        case ETestCaseUnbalancedIf:
            {            
            TDes& buf = iLogger->Buffer();
            buf.Zero();            
            buf.AppendFormat( TPtrC( KUnbalancedIf ),
                iTestCases[scriptIndex]->Name().Ptr() );            
            iLogger->WriteLogL( buf );
            }
            break;
        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// CBCTestSuite::WriteTestCaseLogL
// Creates test case log start (and end) separator.
// -----------------------------------------------------------------------------
//
void CBCTestSuite::WriteTestCaseLogL( TInt aScriptIndex, TBool aStart )
    {   
    if ( !iLogger )
        {
        return;
        }       
    
    TDes& buf = iLogger->Buffer();
    buf.Zero(); // reset buffer    
    TInt type = iTestCases[aScriptIndex]->Type();
    if ( type == CBCTestCase::EEndCase )
        {        
        buf.Append( KLogTwoLine );
        iLogger->WriteLogL( buf );
        return;
        }
    TDesC& name = iTestCases[aScriptIndex]->Name();
    buf.Append( KLogRow80 ); // first separator row
    if ( name.Length() > 0 )
        {
        buf.Append( name );
        }
    else
        {        
        buf.Append( KUnnamedCase );
        }
        
    if ( aStart )
        {
        buf.AppendFormat( TPtrC( KCaseStartLog ), aScriptIndex + 1 );
        }
    else
        {
        buf.AppendFormat( TPtrC( KCaseEndLog ), aScriptIndex + 1 );
        }
    iLogger->CreateTimeStamp( buf );
    buf.Append( KLogRow80 );    
    if ( !aStart ) // insert some empty lines
        {
        buf.Append( KLogTwoLine );
        }
    iLogger->WriteLogL( buf );
    }

// -----------------------------------------------------------------------------
// CBCTestSuite::WriteStartLogL
// -----------------------------------------------------------------------------
//
void CBCTestSuite::WriteStartLogL()
    {
    if ( !iLogger )
        {
        return;
        }    
    
    TDes& buf = iLogger->Buffer();
    buf.Zero();    
    buf.AppendFormat( TPtrC( KStartInfo ), iTestCases.Count() - 1 );    
    iLogger->WriteLogL( buf );
    }
    
// -----------------------------------------------------------------------------
// CBCTestSuite::WriteSummaryLogL
// -----------------------------------------------------------------------------
//
void CBCTestSuite::WriteSummaryLogL()
    {
    TDes& buf = iLogger->Buffer();
    
    // write main log    
    buf.Zero();
    const TDesC& appCaption = iLogger->AppCaption();      
    buf.AppendFormat( KCompletedTest, appCaption.Ptr() );        
    iLogger->CreateTimeStamp( buf );
    iLogger->WriteMainLogL( buf );
    
    // write summary log    
    TInt testCount = 0;
    TInt failCases = 0;
    TInt failCount = 0;    
    TInt* failedInfo = new( ELeave ) TInt[iTestCases.Count()];
    CleanupStack::PushL( failedInfo );
    for( TInt i=0; i<iTestCases.Count(); i++ )
        {
        TInt count = 0;
        iTestCases[i]->GetTestSummary( count, failedInfo[i] );
        testCount += count;
        if ( failedInfo[i] > 0)
            {
            failCases++;
            failCount += failedInfo[i];
            }
        }
    
    buf.Zero();      
    buf.AppendFormat( TPtrC( KSummary ), iTestCases.Count() - 1, failCases, 
        testCount, failCount );
    
    if ( failCases > 0 )
        {        
        buf.Append( KSummaryFailLog );
        TInt failRecord = 0;    
        for( TInt i=0; i<iTestCases.Count(); i++ )
            {        
            if ( failedInfo[i] > 0)
                {
                if ( failRecord > 0)
                    {
                    buf.Append( KSummaryComma );
                    }
                buf.AppendFormat( TPtrC( KSummaryFailFormat ), i + 1 );
                failRecord++;            
                }
            }
        buf.Append( KSummaryDot );
        buf.Append( KLogTwoLine );
        }
    CleanupStack::PopAndDestroy( failedInfo );
    iLogger->WriteLogL( buf );
    iLogger->WriteMainLogL( buf );    
    }
