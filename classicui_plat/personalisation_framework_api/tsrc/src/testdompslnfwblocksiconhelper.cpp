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
* Description:  Test PslnFWIconHelper.h
 *
*/


// [INCLUDE FILES]
#include <pslnfwiconhelper.h>
#include <testdompslnframework.rsg>
#include <eikclb.h>
#include <coeaui.h>

#include "testdompslnframework.h"
#include "testdompslnfwbc.h"
#include "testdompslnfwbv.h"

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWIHNewL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWIHNewL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWIHNewL, "In TestPlsnFWIHNewL" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWIHNewL );
    // Print to log file
    iLog->Log( KTestPlsnFWIHNewL );

    iHelper = CPslnFWIconHelper::NewL();
    STIF_ASSERT_NOT_NULL( iHelper );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWIHDelete
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWIHDelete( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWIHDelete, "In TestPlsnFWIHDelete" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWIHDelete );
    // Print to log file
    iLog->Log( KTestPlsnFWIHDelete );

    delete iHelper;
    iHelper = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWIHAddIconsToSettingItemsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWIHAddIconsToSettingItemsL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWIHAddIconsToSettingItemsL, "In TestPlsnFWIHAddIconsToSettingItemsL" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWIHAddIconsToSettingItemsL );
    // Print to log file
    iLog->Log( KTestPlsnFWIHAddIconsToSettingItemsL );

    iFWBView = new( ELeave ) CTestPslnFWBaseView();
    
    iFWBContainer = new( ELeave ) CTestPslnFWBaseContainer();
    iFWBContainer->SetMopParent( iFWBView );
    iFWBContainer->ConstructL( iFWBView->ClientRect() );
    iFWBContainer->MakeVisible( ETrue );
    CCoeEnv::Static()->AppUi()->AddToStackL( iFWBContainer );
    CEikColumnListBox* textList = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( textList );
    textList->ConstructL( iFWBContainer );

    iHelper->AddIconsToSettingItemsL(ETrue, 0 , textList );
    CleanupStack::Pop( textList );
    CCoeEnv::Static()->AppUi()->RemoveFromStack( iFWBContainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWIHGetLocalizedStringLC
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWIHGetLocalizedStringLC( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWIHGetLocalizedStringLC, "In TestPlsnFWIHGetLocalizedStringLC" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWIHGetLocalizedStringLC );
    // Print to log file
    iLog->Log( KTestPlsnFWIHGetLocalizedStringLC );

    iFWBView = new( ELeave ) CTestPslnFWBaseView();
    
    iFWBContainer = new( ELeave ) CTestPslnFWBaseContainer();
    iFWBContainer->SetMopParent( iFWBView );
    iFWBContainer->ConstructL( iFWBView->ClientRect() );
    iFWBContainer->MakeVisible( ETrue );
    CCoeEnv::Static()->AppUi()->AddToStackL( iFWBContainer );
    CEikColumnListBox* textList = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( textList );
    textList->ConstructL( iFWBContainer );

    iHelper->AddIconsToSettingItemsL(ETrue, 0, textList );
    CleanupStack::Pop( textList );
    CCoeEnv::Static()->AppUi()->RemoveFromStack( iFWBContainer );

    iHelper->GetLocalizedStringLC( KFilePath, R_BUFFER, CCoeEnv::Static() );
    CleanupStack::Pop();
    return KErrNone;
    }
