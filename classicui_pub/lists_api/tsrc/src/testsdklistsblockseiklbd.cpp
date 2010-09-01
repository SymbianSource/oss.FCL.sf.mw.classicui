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
* Description:  Test eikclb.H
*
*/

// [INCLUDE FILES]
#include <e32base.h>
#include <eiklbd.h>
#include <testsdklists.rsg>
#include <coemain.h>
#include <coeaui.h>
#include <eiklbi.h>

#include "testsdklists.h"
#include "testsdkcontainer.h"
#include "testsdklistslistboxdata.h"
#include "aknsbasicbackgroundcontrolcontext.h"

const TInt KTen = 10;
_LIT( KSearchString, "search string" );
_LIT( KItemText, "item text" );
// ============================ MEMBER FUNCTIONS ===============================

// ===========================TListFontBoundValues==============================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestLFBVConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLFBVConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLFBVConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    TListFontBoundValues* value = new( ELeave ) TListFontBoundValues();
    CleanupStack::PushL( value );
    STIF_ASSERT_NOT_NULL( value );
    CleanupStack::PopAndDestroy( value );
    return KErrNone;
    }

// ================================CListBoxData=================================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDConstructor" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    iLBData = new( ELeave ) CListBoxData();
    STIF_ASSERT_NOT_NULL( iLBData );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDDestructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDDestructor( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDDestructor" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    delete iLBData;
    iLBData = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDConstructL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDConstructL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    const CFont* font = CCoeEnv::Static()->NormalFont();
    iLBData->ConstructL( font );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDFont
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDFont( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDFont" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    TListItemProperties property;
    const CFont* getFont = iLBData->Font( property );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDSetupGc
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDSetupGc( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDSetupGc" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    TListItemProperties property;
    iLBData->SetupGc( property, gc );
    iContainer->DeactivateGc();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDFontBoundValues
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDFontBoundValues( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDFontBoundValues" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    TListFontBoundValues value = iLBData->FontBoundValues();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDSetFontHeight
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDSetFontHeight( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDSetFontHeight" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    TInt err = iLBData->SetFontHeight( KTen );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDSetSearchStringL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDSetSearchStringL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDSetSearchStringL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    iLBData->SetSearchStringL( &KSearchString );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDIsSearchStringL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDIsSearchStringL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDSetSearchStringL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    iLBData->SetSearchStringL( &KSearchString );
    TBool flag = iLBData->IsSearchString();
    STIF_ASSERT_TRUE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDDrawItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDDrawItemL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDDrawItem" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    iLBData->SetSearchStringL( &KSearchString );

    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    TRect rect = iContainer->Rect();
    const CFont& font = *iEikonEnvPointer->NormalFont();
    gc.UseFont( &font );
    iLBData->DrawItem( gc, rect, KItemText, font, KTen );
    iContainer->DeactivateGc();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDSetAlignmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDSetAlignmentL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDSetAlignmentL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    CGraphicsContext::TTextAlign align =  CGraphicsContext::ELeft;
    iLBData->SetAlignmentL( align );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDAlignmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDAlignmentL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDSetAlignmentL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    CGraphicsContext::TTextAlign align =  CGraphicsContext::ELeft;
    iLBData->SetAlignmentL( align );
    CGraphicsContext::TTextAlign getAlign = iLBData->Alignment();
    STIF_ASSERT_EQUALS( align, getAlign );
    

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDSkinBackgroundControlContext
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDSkinBackgroundControlContext( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDSkinBackgroundControlContext" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    iLBData->SkinBackgroundControlContext();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDSetSkinBackgroundControlContextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDSetSkinBackgroundControlContextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDSetSkinBackgroundControlContextL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    CTestSDKListsListBoxData* data = new( ELeave ) CTestSDKListsListBoxData();
    CleanupStack::PushL( data );
    const CFont* font = CCoeEnv::Static()->NormalFont();
    data->ConstructL( font );

    TAknsItemID itemID;
    itemID.Set( 0x2001CB80, 1 );
    TRect rect = iContainer->Rect();
    CAknsBasicBackgroundControlContext* context =
        CAknsBasicBackgroundControlContext::NewL( itemID, rect, ETrue );
    CleanupStack::PushL( context );
    data->TestSetSkinBackgroundControlContextL( context );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDSetSkinEnabledL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDSetSkinEnabledL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDSetSkinEnabledL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    CTestSDKListsListBoxData* data = new( ELeave ) CTestSDKListsListBoxData();
    CleanupStack::PushL( data );
    const CFont* font = CCoeEnv::Static()->NormalFont();
    data->ConstructL( font );

    data->TestSetSkinEnabledL( ETrue );
    CleanupStack::PopAndDestroy( data );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDConstructFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDConstructFontL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDConstructFontL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    CTestSDKListsListBoxData* data = new( ELeave ) CTestSDKListsListBoxData();
    CleanupStack::PushL( data );
    const CFont* font = CCoeEnv::Static()->NormalFont();
    data->ConstructL( font );

    data->TestConstructFontL( font );
    CleanupStack::PopAndDestroy( data );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDUpdateFontBoundValuesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDUpdateFontBoundValuesL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDUpdateFontBoundValuesL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    CTestSDKListsListBoxData* data = new( ELeave ) CTestSDKListsListBoxData();
    CleanupStack::PushL( data );
    const CFont* font = CCoeEnv::Static()->NormalFont();
    data->ConstructL( font );

    data->TestUpdateFontBoundValues( font );
    CleanupStack::PopAndDestroy( data );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDRegenerateFontsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDRegenerateFontsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDRegenerateFontsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    CTestSDKListsListBoxData* data = new( ELeave ) CTestSDKListsListBoxData();
    CleanupStack::PushL( data );
    const CFont* font = CCoeEnv::Static()->NormalFont();
    data->ConstructL( font );

    data->TestRegenerateFonts();
    CleanupStack::PopAndDestroy( data );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDFWSReleaseFontsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDFWSReleaseFontsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDFWSReleaseFontsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    CTestSDKListsListBoxData* data = new( ELeave ) CTestSDKListsListBoxData();
    CleanupStack::PushL( data );
    const CFont* font = CCoeEnv::Static()->NormalFont();
    data->ConstructL( font );

    data->TestReleaseFonts();
    CleanupStack::PopAndDestroy( data );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDFWSFontStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDFWSFontStyleL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDFWSFontStyleL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    CTestSDKListsListBoxData* data = new( ELeave ) CTestSDKListsListBoxData();
    CleanupStack::PushL( data );
    const CFont* font = CCoeEnv::Static()->NormalFont();
    data->ConstructL( font );

    data->TestFontStyle();
    CleanupStack::PopAndDestroy( data );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBDFWSSetFontStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBDFWSSetFontStyleL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestEIKLBD, "In TestLBDFWSSetFontStyleL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBD );
    // Print to log file
    iLog->Log( KTestEIKLBD );

    CTestSDKListsListBoxData* data = new( ELeave ) CTestSDKListsListBoxData();
    CleanupStack::PushL( data );
    const CFont* font = CCoeEnv::Static()->NormalFont();
    data->ConstructL( font );

    TBool isEqual = data->TestSetFontStyle();
    STIF_ASSERT_TRUE( isEqual );
    CleanupStack::PopAndDestroy( data );

    return KErrNone;
    }
