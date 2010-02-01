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
* Description:  misc_controls_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <eikcapc.h>
#include <eikcapca.h>
#include <eikconso.h>
#include <testsdkmisccontrols.rsg>

#include "testsdkmisccontrols.h"



// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCAConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCAConstructorL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkdialogs, "testsdkdialogs" );
    _LIT( KTestCCAConstructorL, "In TestCCAConstructorL" );
    TestModuleIf().Printf( 0, Ktestsdkdialogs, KTestCCAConstructorL );
    // Print to log file
    iLog->Log( KTestCCAConstructorL );

    TInt granularity = 4;

    iCapCArray = new (ELeave) CEikCapCArray( granularity );

    STIF_ASSERT_NOT_NULL( iCapCArray );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCADestructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCADestructor( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkdialogs, "testsdkdialogs" );
    _LIT( KTestCCAConstructorL, "In TestCCAConstructorL" );
    TestModuleIf().Printf( 0, Ktestsdkdialogs, KTestCCAConstructorL );
    // Print to log file
    iLog->Log( KTestCCAConstructorL );
    
    delete iCapCArray;
    iCapCArray = NULL;

    
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCAMinimumSize
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCAMinimumSize( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkdialogs, "testsdkdialogs" );
    _LIT( KTestCCAMinimumSize, "In TestCCAMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkdialogs, KTestCCAMinimumSize );
    // Print to log file
    iLog->Log( KTestCCAMinimumSize );
    TSize size = iCapCArray->MinimumSize();

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCASetRect
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCASetRect( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkdialogs, "testsdkdialogs" );
    _LIT( KTestCCASetRect, "In TestCCASetRect" );
    TestModuleIf().Printf( 0, Ktestsdkdialogs, KTestCCASetRect );
    // Print to log file
    iLog->Log( KTestCCASetRect );
    TRect rect( 120, 100, 200, 150 );
    iCapCArray->SetRect( rect );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCAResetMinimumSizes
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCAResetMinimumSizes( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkdialogs, "testsdkdialogs" );
    _LIT( KTestCCAResetMinimumSizes, "In TestCCAResetMinimumSizes" );
    TestModuleIf().Printf( 0, Ktestsdkdialogs, KTestCCAResetMinimumSizes );
    // Print to log file
    iLog->Log( KTestCCAResetMinimumSizes );
   
    iCapCArray->ResetMinimumSizes();
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCALineIndexFromId
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCALineIndexFromId( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkdialogs, "testsdkdialogs" );
    _LIT( KTestCCALineIndexFromId, "In TestCCALineIndexFromId" );
    TestModuleIf().Printf( 0, Ktestsdkdialogs, KTestCCALineIndexFromId );
    // Print to log file
    iLog->Log( KTestCCALineIndexFromId );
    TInt count = 0;
    TInt capCArray = iCapCArray->LineIndexFromId( count );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCAFindLineIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCAFindLineIndexL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkdialogs, "testsdkdialogs" );
    _LIT( KTestCCAFindLineIndexL, "In TestCCAFindLineIndexL" );
    TestModuleIf().Printf( 0, Ktestsdkdialogs, KTestCCAFindLineIndexL );
    // Print to log file
    iLog->Log( KTestCCAFindLineIndexL );
    iCaptionedControl= new (ELeave) CEikCaptionedControl();
    iCapCArray->AppendL( iCaptionedControl );
    TInt capCArray = iCapCArray->FindLineIndex( iCaptionedControl );
  
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCAFindLineIndex
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCADeleteLineL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkdialogs, "testsdkdialogs" );
    _LIT( KTestCCADeleteLineL, "In TestCCADeleteLineL" );
    TestModuleIf().Printf( 0, Ktestsdkdialogs, KTestCCADeleteLineL );
    // Print to log file
    iLog->Log( KTestCCADeleteLineL );

    iCaptionedControl= new (ELeave) CEikCaptionedControl();
    iCapCArray->AppendL( iCaptionedControl );
    TInt dex = iCapCArray->FindLineIndex( iCaptionedControl );;

    iCapCArray->DeleteLine( dex );


    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCAAdjustAllIds
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCAAdjustAllIds( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkdialogs, "testsdkdialogs" );
    _LIT( KTestCCAAdjustAllIds, "In TestCCAAdjustAllIds" );
    TestModuleIf().Printf( 0, Ktestsdkdialogs, KTestCCAAdjustAllIds );
    // Print to log file
    iLog->Log( KTestCCAAdjustAllIds );
    TInt controlIdDelta = 0;

    iCapCArray->AdjustAllIds( controlIdDelta );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCCASetDensePacking
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCCASetDensePacking( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkdialogs, "testsdkdialogs" );
    _LIT( KTestCCASetDensePacking, "In TestCCASetDensePacking" );
    TestModuleIf().Printf( 0, Ktestsdkdialogs, KTestCCASetDensePacking );
    // Print to log file
    iLog->Log( KTestCCASetDensePacking );

    iCapCArray->SetDensePacking( ETrue );

    return KErrNone;

    }

