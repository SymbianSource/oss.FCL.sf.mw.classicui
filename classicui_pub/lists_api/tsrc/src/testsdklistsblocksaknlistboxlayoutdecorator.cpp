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
* Description:  Test CAknListBoxLayoutDecorator.H
*
*/



// [INCLUDE FILES]
#include <e32base.h>
#include <badesca.h>
#include <aknlistboxlayoutdecorator.h>
#include <testsdklists.rsg>
#include <coemain.h>
#include <coeaui.h>

#include "testsdklists.h"

_LIT( KTextLeading, "Leading text" );
_LIT( KTextTrailing, "Trailing text" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLDNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLDNewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknListBoxLayoutDecoratorTestModule" );
    _LIT( KTestLBLDNewL, "In TestLBLDNewL" );
    TestModuleIf().Printf( 0, KTestModule, KTestLBLDNewL );
    // Print to log file
    iLog->Log( KTestLBLDNewL );

    iLBLDecorator = CAknListBoxLayoutDecorator::NewL();
    STIF_ASSERT_NOT_NULL( iLBLDecorator );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLDNewLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLDNewLC( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknListBoxLayoutDecoratorTestModule" );
    _LIT( KTestLBLDNewLC, "In TestLBLDNewLC" );
    TestModuleIf().Printf( 0, KTestModule, KTestLBLDNewLC );
    // Print to log file
    iLog->Log( KTestLBLDNewLC );

    CAknListBoxLayoutDecorator* lBLDecorator = CAknListBoxLayoutDecorator::NewLC();
    STIF_ASSERT_NOT_NULL( lBLDecorator );
    CleanupStack::Pop();
    
    delete lBLDecorator;
    lBLDecorator = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLDDelete
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLDDelete( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknListBoxLayoutDecoratorTestModule" );
    _LIT( KTestLBLDDelete, "In TestLBLDDelete" );
    TestModuleIf().Printf( 0, KTestModule, KTestLBLDDelete );
    // Print to log file
    iLog->Log( KTestLBLDDelete );

    delete iLBLDecorator;
    iLBLDecorator = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLDArray
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLDArrayL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknListBoxLayoutDecoratorTestModule" );
    _LIT( KTestLBLDArray, "In TestLBLDArray" );
    TestModuleIf().Printf( 0, KTestModule, KTestLBLDArray );
    // Print to log file
    iLog->Log( KTestLBLDArray );

    CDesCArray* textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );
    iLBLDecorator->SetArray( textArray );

    const MDesCArray* textGetArray = iLBLDecorator->Array();
    STIF_ASSERT_TRUE( textArray == textGetArray );
    CleanupStack::PopAndDestroy( textArray );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLDSetArray
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLDSetArrayL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknListBoxLayoutDecoratorTestModule" );
    _LIT( KTestLBLDSetArray, "In TestLBLDSetArray" );
    TestModuleIf().Printf( 0, KTestModule, KTestLBLDSetArray );
    // Print to log file
    iLog->Log( KTestLBLDSetArray );

    CDesCArray* textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );
    iLBLDecorator->SetArray( textArray );
    CleanupStack::PopAndDestroy( textArray );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLDSetLeadingDecorationTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLDSetLeadingDecorationTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknListBoxLayoutDecoratorTestModule" );
    _LIT( KTestLBLDSetLeadingDecorationTextL, "In TestLBLDSetLeadingDecorationTextL" );
    TestModuleIf().Printf( 0, KTestModule, KTestLBLDSetLeadingDecorationTextL );
    // Print to log file
    iLog->Log( KTestLBLDSetLeadingDecorationTextL );

    TInt err = KErrNone;
    TRAP( err, iLBLDecorator->SetLeadingDecorationTextL( KTextLeading ) );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLDSetTrailingDecorationTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLDSetTrailingDecorationTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknListBoxLayoutDecoratorTestModule" );
    _LIT( KTestLBLDSetTrailingDecorationTextL, "In TestLBLDSetTrailingDecorationTextL" );
    TestModuleIf().Printf( 0, KTestModule, KTestLBLDSetTrailingDecorationTextL );
    // Print to log file
    iLog->Log( KTestLBLDSetTrailingDecorationTextL );

    TInt err = KErrNone;
    TRAP( err, iLBLDecorator->SetTrailingDecorationTextL( KTextTrailing ) );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLDSetActive
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLDSetActive( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknListBoxLayoutDecoratorTestModule" );
    _LIT( KTestLBLDSetActive, "In TestLBLDSetActive" );
    TestModuleIf().Printf( 0, KTestModule, KTestLBLDSetActive );
    // Print to log file
    iLog->Log( KTestLBLDSetActive );

    iLBLDecorator->SetActive( ETrue );
    iLBLDecorator->SetActive( EFalse );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLDMdcaCountL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLDMdcaCountL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknListBoxLayoutDecoratorTestModule" );
    _LIT( KTestLBLDMdcaCount, "In TestLBLDMdcaCount" );
    TestModuleIf().Printf( 0, KTestModule, KTestLBLDMdcaCount );
    // Print to log file
    iLog->Log( KTestLBLDMdcaCount );

    CDesCArray* textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );
    iLBLDecorator->SetArray( textArray );

    TInt expected = textArray->Count();
    TInt count = iLBLDecorator->MdcaCount();
    STIF_ASSERT_EQUALS( expected, count )
    CleanupStack::PopAndDestroy( textArray );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLDMdcaPointL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLDMdcaPointL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknListBoxLayoutDecoratorTestModule" );
    _LIT( KTestLBLDMdcaPoint, "In TestLBLDMdcaPoint" );
    TestModuleIf().Printf( 0, KTestModule, KTestLBLDMdcaPoint );
    // Print to log file
    iLog->Log( KTestLBLDMdcaPoint );

    CDesCArray* textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );
    iLBLDecorator->SetArray( textArray );
    
    iLBLDecorator->SetActive( ETrue );

    for ( TInt i=0; i< iLBLDecorator->MdcaCount(); i++)
        {
        TPtrC ptr = iLBLDecorator->MdcaPoint( i );
        }

    CleanupStack::PopAndDestroy( textArray );

    return KErrNone;
    }
