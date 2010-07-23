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
* Description:  
*
*/

// [INCLUDE FILES]
#include <e32base.h>
#include <aknlists.h>
#include <testsdklists.rsg>
#include <coemain.h>
#include <coeaui.h>
#include <eiklbv.h>
#include <barsread.h>
#include <eikclb.h>
#include <stringloader.h>

#include "testsdklists.h"
#include "testsdkcontainer.h"
#include "testsdklistslistboxview.h"
#include "testsdklistssnakinglistboxView.h"

const TInt KZero = 0;
const TInt KFive = 5;
const TInt KEight = 8;
const TInt KTen = 10;
const TInt KHundred = 100;

_LIT( KListEmptyText, "list empty text" );
// ============================ MEMBER FUNCTIONS ===============================

// ============================class CListBoxView===============================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CListBoxView* view = new( ELeave ) CListBoxView();
    CleanupStack::PushL( view );
    STIF_ASSERT_NOT_NULL( view );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVDestructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVDestructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CListBoxView* view = new( ELeave ) CListBoxView();
    CleanupStack::PushL( view );
    STIF_ASSERT_NOT_NULL( view );
    CleanupStack::Pop( view );
    delete view;
    view = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVConstructL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVConstructL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    // CEikColumListBox::ConstructFromResourceL() will call CListBoxView::ConstructL()
    listBox->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVViewRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVViewRectL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVViewRectL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->ViewRect();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSetViewRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSetViewRectL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSetViewRectL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    TRect rect( 1, 1, 1, 1 );
    view->SetViewRect( rect );
    TRect getRect = view->ViewRect();
    STIF_ASSERT_EQUALS( rect, getRect );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVCurrentItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVCurrentItemIndexL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVCurrentItemIndexL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->CurrentItemIndex();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSetCurrentItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSetCurrentItemIndexL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSetCurrentItemIndexL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetCurrentItemIndex( KFive );
    TInt index = view->CurrentItemIndex();
    STIF_ASSERT_EQUALS( KFive, index );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVTopItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVTopItemIndexL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVTopItemIndexL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->TopItemIndex();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSetTopItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSetTopItemIndexL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSetTopItemIndexL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetTopItemIndex( KFive );
    TInt index = view->TopItemIndex();
    STIF_ASSERT_EQUALS( KFive, index );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVBottomItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVBottomItemIndexL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVBottomItemIndexL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->BottomItemIndex();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVCalcBottomItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVCalcBottomItemIndexL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVCalcBottomItemIndexL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->CalcBottomItemIndex();
    view->BottomItemIndex();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSetItemHeightL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSetItemHeightL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSetItemHeightL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetItemHeight( KTen );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSetMatcherCursorColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSetMatcherCursorColorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSetMatcherCursorColorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetMatcherCursorColor( KRgbGray );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSetMatcherCursorPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSetMatcherCursorPosL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSetMatcherCursorPosL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetMatcherCursorPos( KFive );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVMatcherCursorPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVMatcherCursorPosL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVMatcherCursorPosL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetMatcherCursorPos( KFive );
    TInt pos = view->MatcherCursorPos();
    STIF_ASSERT_EQUALS( KFive, pos );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVDrawMatcherCursorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVDrawMatcherCursorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVDrawMatcherCursorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->DrawMatcherCursor();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVHideMatcherCursorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVHideMatcherCursorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVHideMatcherCursorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->HideMatcherCursor();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSetMatcherCursorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSetMatcherCursorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSetMatcherCursorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetMatcherCursor( ETrue );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSetEmphasizedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSetEmphasizedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSetEmphasizedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetEmphasized( ETrue );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSetDimmedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSetDimmedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSetDimmedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetDimmed( ETrue );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSetDisableRedrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSetDisableRedrawL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSetDisableRedrawL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetDisableRedraw( ETrue );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVRedrawDisabledL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVRedrawDisabledL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVRedrawDisabledL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetDisableRedraw( ETrue );
    TBool flag = view->RedrawDisabled();
    STIF_ASSERT_TRUE( flag );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSetPaintedSelectionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSetPaintedSelectionL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSetPaintedSelectionL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetPaintedSelection( ETrue );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSelectionIndexesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSelectionIndexesL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSelectionIndexesL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    const CListBoxView::CSelectionIndexArray* selectionArray = view->SelectionIndexes();
    STIF_ASSERT_NOT_NULL( selectionArray );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVGetSelectionIndexesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVGetSelectionIndexesL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVGetSelectionIndexesL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    CArrayFixFlat<TInt>* selectionArray = new( ELeave ) CArrayFixFlat<TInt>( 5 );
    CleanupStack::PushL( selectionArray );
    view->GetSelectionIndexesL( selectionArray );
    STIF_ASSERT_NOT_NULL( selectionArray );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy( 2 );
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSetSelectionIndexesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSetSelectionIndexesL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSetSelectionIndexesL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    CArrayFixFlat<TInt>* selectionArray = new( ELeave ) CArrayFixFlat<TInt>( 5 );
    CleanupStack::PushL( selectionArray );
    selectionArray->AppendL( 0 );
    selectionArray->AppendL( 1 );
    selectionArray->AppendL( 2 );
    view->SetSelectionIndexesL( selectionArray );
    selectionArray->Reset();  

    view->GetSelectionIndexesL( selectionArray );
    STIF_ASSERT_TRUE( ( selectionArray->Length() == 4 && 
        selectionArray->At(0) == 0) );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy( 2 );
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVClearSelectionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVClearSelectionL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVClearSelectionL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->ClearSelection();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVUpdateSelectionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVUpdateSelectionL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVUpdateSelectionL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->UpdateSelectionL( CListBoxView::ENoSelection );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVToggleItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVToggleItemL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVToggleItemL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    TInt err = KErrNone;
    TRAP( err, view->ToggleItemL( 0 ) );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSelectItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSelectItemL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSelectItemL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    TInt err = KErrNone;
    TRAP( err, view->SelectItemL( 0 ) );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVDeselectItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVDeselectItemL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVDeselectItemL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    TInt err = KErrNone;
    TRAP( err, view->DeselectItem( 0 ) );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSetAnchorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSetAnchorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSetAnchorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetAnchor( 0 );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVClearSelectionAnchorAndActiveIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVClearSelectionAnchorAndActiveIndexL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVClearSelectionAnchorAndActiveIndexL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetAnchor( 0 );
    view->ClearSelectionAnchorAndActiveIndex();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVScrollToMakeItemVisibleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVScrollToMakeItemVisibleL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVScrollToMakeItemVisibleL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->ScrollToMakeItemVisible( KFive );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVVScrollToL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVVScrollToL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVVScrollToL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->VScrollTo( KEight );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVVScrollToWithTRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVVScrollToWithTRectL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVVScrollToWithTRectL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    TRect rect( 1, 1, 1, 1 );
    view->VScrollTo( KEight, rect );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVHScrollL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVHScrollL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVHScrollL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->HScroll( KTen );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVHScrollOffsetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVHScrollOffsetL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVHScrollOffsetL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->HScrollOffset();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSetHScrollOffsetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSetHScrollOffsetL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSetHScrollOffsetL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetHScrollOffset( KTen );
    TInt offset = view->HScrollOffset();
    STIF_ASSERT_EQUALS( KTen, offset );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVDataWidthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVDataWidthL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVDataWidthL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->DataWidth();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVCalcDataWidthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVCalcDataWidthL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVCalcDataWidthL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->CalcDataWidth();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVVisibleWidthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVVisibleWidthL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVVisibleWidthL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    TRect rect = listBox->Rect();
    view->VisibleWidth( rect );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVCalcNewTopItemIndexSoItemIsVisibleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVCalcNewTopItemIndexSoItemIsVisibleL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVCalcNewTopItemIndexSoItemIsVisibleL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->CalcNewTopItemIndexSoItemIsVisible( KEight );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVDrawL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVDrawL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    TRect rect = listBox->Rect();
    view->Draw( &rect );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVDrawItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVDrawItemL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVDrawItemL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->DrawItem( 0 );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSetListEmptyTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSetListEmptyTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSetListEmptyTextL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetListEmptyTextL( KListEmptyText );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVEmptyListTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVEmptyListTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVEmptyListTextL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetListEmptyTextL( KListEmptyText );
    const TDesC* ptr = view->EmptyListText();
    TInt compare = ptr->Compare( KListEmptyText );
    STIF_ASSERT_EQUALS( KZero, compare );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVItemIsSelectedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVItemIsSelectedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVItemIsSelectedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SelectItemL( 0 );
    TBool flag = view->ItemIsSelected( 0 );
    STIF_ASSERT_TRUE( flag );
    
    view->DeselectItem( 0 );
    flag = view->ItemIsSelected( 0 );
    STIF_ASSERT_FALSE( flag );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVItemIsVisibleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVItemIsVisibleL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVItemIsVisibleL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    TBool flag = view->ItemIsVisible( 0 );
    STIF_ASSERT_TRUE( flag );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVItemPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVItemPosL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVItemPosL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->ItemPos( 0 );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVItemSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVItemSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVItemSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->ItemSize( 0 );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSetTextColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSetTextColorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSetTextColorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetTextColor( KRgbBlue );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSetBackColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSetBackColorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSetBackColorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetBackColor( KRgbGray );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVTextColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVTextColorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVTextColorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetTextColor( KRgbBlue );
    TRgb color = view->TextColor();
    STIF_ASSERT_EQUALS( color, KRgbBlue );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVBackColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVBackColorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVBackColorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->SetBackColor( KRgbGray );
    TRgb color = view->BackColor();
    STIF_ASSERT_EQUALS( color, KRgbGray );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVMoveCursorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVMoveCursorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVMoveCursorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->MoveCursorL( CListBoxView::ECursorNextItem, CListBoxView::ENoSelection );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVVerticalMoveToItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVVerticalMoveToItemL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVVerticalMoveToItemL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    view->VerticalMoveToItemL( 0, CListBoxView::ENoSelection );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVXYPosToItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVXYPosToItemIndexL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVXYPosToItemIndexL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    TPoint point = view->ItemPos( 0 );
    TInt index = 0;
    TBool flag = view->XYPosToItemIndex( point, index );
    STIF_ASSERT_TRUE( flag );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVNumberOfItemsThatFitInRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVNumberOfItemsThatFitInRectL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVNumberOfItemsThatFitInRectL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    TRect rect = listBox->Rect();
    view->NumberOfItemsThatFitInRect( rect );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVIsVisibleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVIsVisibleL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVIsVisibleL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    TBool flag = view->IsVisible();
    STIF_ASSERT_TRUE( flag );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    CListItemDrawer* drawer = view->ItemDrawer();
    STIF_ASSERT_NOT_NULL( drawer );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVDrawEmptyListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVDrawEmptyListL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVDrawEmptyListL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CEikTextListBox* listBox = new( ELeave ) CEikTextListBox();
    CleanupStack::PushL( listBox );
    listBox->ConstructL( iContainer, flags );
    listBox->Model()->SetItemTextArray( textArray );
    listBox->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    TRect rect = listBox->Rect();
    view->DrawEmptyList( rect );

    iContainer->ResetControl();
    CleanupStack::Pop( listBox );
    CleanupStack::Pop( textArray );

    listBox = NULL;
    textArray = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVDeselectRangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVDeselectRangeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVDeselectRangeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->View();
    TInt err = KErrNone;
    TRAP( err, view->DeselectRangeL( KZero, KFive ) );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVFlagsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVFlagsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CTestSDKListsListBoxView* view = static_cast< CTestSDKListsListBoxView* > ( listBox->View() );
    view->DoTestFlags();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSetFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSetFlagsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSetFlagsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CTestSDKListsListBoxView* view = static_cast< CTestSDKListsListBoxView* > ( listBox->View() );
    CListBoxView::TFlags flag = CListBoxView::EMarkSelection;
    view->DoTestSetFlags( flag );
    TInt getflag = view->DoTestFlags();
    STIF_ASSERT_TRUE( flag==getflag );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVClearFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVClearFlagsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVClearFlagsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CTestSDKListsListBoxView* view = static_cast< CTestSDKListsListBoxView* > ( listBox->View() );

    CListBoxView::TFlags flag = CListBoxView::EMarkSelection;
    view->DoTestSetFlags( flag );
    TInt getflag = view->DoTestFlags();
    STIF_ASSERT_TRUE( flag==getflag );

    flag = CListBoxView::EUnmarkSelection;
    view->DoTestClearFlags( flag );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBVSelectRangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBVSelectRangeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestLBVSelectRangeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );

    CTestSDKListsListBoxView* view = static_cast< CTestSDKListsListBoxView* > ( listBox->View() );
    view->DoTestSelectRangeL( KZero, KFive );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    listBox = NULL;

    return KErrNone;
    }

// ============================class CListBoxView===============================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    iTLBModel = new( ELeave ) CTextListBoxModel();
    iTLBModel->ConstructL( textArray );

    const CFont* font = iEikonEnvPointer->NormalFont();

    CTextListItemDrawer* drawer = new( ELeave ) CTextListItemDrawer( iTLBModel, font );
    CleanupStack::PushL( drawer );

    iSLBView = new( ELeave ) CSnakingListBoxView();
    STIF_ASSERT_NOT_NULL( iSLBView );

    CWsScreenDevice* device = iEikonEnvPointer->ScreenDevice();
    RWindowGroup& parent = iEikonEnvPointer->RootWin();
    RWindow* window = ( RWindow* )iContainer->DrawableWindow();
    TRect rect = iContainer->Rect();
    iSLBView->ConstructL( iTLBModel, drawer, device, &parent, window, rect, KEight );

    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVDestructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVDestructor( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVDestructor" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    delete iSLBView;
    iSLBView = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVColumnWidth
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVColumnWidth( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVDestructor" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    TInt width = iSLBView->ColumnWidth();
    STIF_ASSERT_EQUALS( KHundred, width );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVSetColumnWidth
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVSetColumnWidth( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVDestructor" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    iSLBView->SetColumnWidth( KTen );
    TInt width = iSLBView->ColumnWidth();
    STIF_ASSERT_EQUALS( KTen, width );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVMoveCursorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVMoveCursorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVMoveCursorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    TInt err = KErrNone;
    TRAP( err,
            iSLBView->MoveCursorL( CListBoxView::ECursorNextItem,
                                   CListBoxView::ENoSelection ) );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVSetTopItemIndex
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVSetTopItemIndex( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVSetTopItemIndex" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    iSLBView->SetTopItemIndex( KEight );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVSetItemHeight
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVSetItemHeight( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVSetItemHeight" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    iSLBView->SetItemHeight( KTen );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVXYPosToItemIndex
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVXYPosToItemIndex( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVXYPosToItemIndex" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    TPoint point = iSLBView->ItemPos( 0 );
    TInt index = 0;
    iSLBView->XYPosToItemIndex( point, index );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVNumberOfItemsThatFitInRect
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVNumberOfItemsThatFitInRect( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVNumberOfItemsThatFitInRect" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    TRect rect = iContainer->Rect();
    iSLBView->NumberOfItemsThatFitInRect( rect );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVHScroll
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVHScroll( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVHScroll" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    iSLBView->HScroll( KTen );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVCalcDataWidth
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVCalcDataWidth( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVCalcDataWidth" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    iSLBView->CalcDataWidth();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVCalcBottomItemIndex
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVCalcBottomItemIndex( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVCalcBottomItemIndex" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    iSLBView->CalcBottomItemIndex();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVDraw
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVDraw( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVDraw" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    TRect rect = iContainer->Rect();
    iSLBView->Draw( &rect );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVVisibleWidth
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVVisibleWidth( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVVisibleWidth" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    TRect rect = iContainer->Rect();
    iSLBView->VisibleWidth( rect );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVScrollToMakeItemVisible
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVScrollToMakeItemVisible( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVScrollToMakeItemVisible" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    iSLBView->ScrollToMakeItemVisible( 0 );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVCalculateHScrollOffsetSoItemIsVisible
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVCalculateHScrollOffsetSoItemIsVisible( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVCalculateHScrollOffsetSoItemIsVisible" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    iSLBView->CalculateHScrollOffsetSoItemIsVisible( KFive );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVCalcNewTopItemIndexSoItemIsVisible
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVCalcNewTopItemIndexSoItemIsVisible( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVCalcNewTopItemIndexSoItemIsVisible" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    iSLBView->CalcNewTopItemIndexSoItemIsVisible( KEight );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVItemPos
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVItemPos( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVItemPos" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    iSLBView->ItemPos( KEight );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVItemSize
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVItemSize( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVItemSize" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    iSLBView->ItemSize( 0 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVCalcRowAndColIndexesFromItemIndex
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVCalcRowAndColIndexesFromItemIndex( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVCalcRowAndColIndexesFromItemIndex" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    TInt rowIndex;
    TInt colIndex;
    iSLBView->CalcRowAndColIndexesFromItemIndex( KEight, rowIndex, colIndex );
    STIF_ASSERT_EQUALS( KZero, colIndex );
    STIF_ASSERT_EQUALS( KEight, rowIndex );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVCalcItemIndexFromRowAndColIndexes
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVCalcItemIndexFromRowAndColIndexes( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVCalcItemIndexFromRowAndColIndexes" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    TInt index = -1;
    iSLBView->CalcItemIndexFromRowAndColIndexes( index, KZero, KZero );
    STIF_ASSERT_EQUALS( KZero, index );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVNumberOfItemsPerColumn
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVNumberOfItemsPerColumn( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVNumberOfItemsPerColumn" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    iSLBView->NumberOfItemsPerColumn();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVDrawItemRangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVDrawItemRangeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVDrawItemRangeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    iTLBModel = new( ELeave ) CTextListBoxModel();
    iTLBModel->ConstructL( textArray );

    const CFont* font = iEikonEnvPointer->NormalFont();

    CTextListItemDrawer* drawer = new( ELeave ) CTextListItemDrawer( iTLBModel, font );
    CleanupStack::PushL( drawer );

    CTestSDKListsSnakingListBoxView* view =
            new( ELeave ) CTestSDKListsSnakingListBoxView();
    CleanupStack::PushL( view );
    STIF_ASSERT_NOT_NULL( view );

    CWsScreenDevice* device = iEikonEnvPointer->ScreenDevice();
    RWindowGroup& parent = iEikonEnvPointer->RootWin();
    RWindow* window = ( RWindow* )iContainer->DrawableWindow();
    TRect rect = iContainer->Rect();
    view->ConstructL( iTLBModel, drawer, device, &parent, window, rect, KEight );

    view->DoTestDrawItemRange( 0, KEight );

    CleanupStack::PopAndDestroy( view );
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVDrawColumnRangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVDrawColumnRangeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVDrawColumnRangeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    iTLBModel = new( ELeave ) CTextListBoxModel();
    iTLBModel->ConstructL( textArray );

    const CFont* font = iEikonEnvPointer->NormalFont();

    CTextListItemDrawer* drawer = new( ELeave ) CTextListItemDrawer( iTLBModel, font );
    CleanupStack::PushL( drawer );

    CTestSDKListsSnakingListBoxView* view =
            new( ELeave ) CTestSDKListsSnakingListBoxView();
    CleanupStack::PushL( view );
    STIF_ASSERT_NOT_NULL( view );

    CWsScreenDevice* device = iEikonEnvPointer->ScreenDevice();
    RWindowGroup& parent = iEikonEnvPointer->RootWin();
    RWindow* window = ( RWindow* )iContainer->DrawableWindow();
    TRect rect = iContainer->Rect();
    view->ConstructL( iTLBModel, drawer, device, &parent, window, rect, KEight );

    view->DoTestDrawColumnRange( 0, 0 );

    CleanupStack::PopAndDestroy( view );
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVMoveToPreviousColumnL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVMoveToPreviousColumnL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVMoveToPreviousColumnL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    iTLBModel = new( ELeave ) CTextListBoxModel();
    iTLBModel->ConstructL( textArray );

    const CFont* font = iEikonEnvPointer->NormalFont();

    CTextListItemDrawer* drawer = new( ELeave ) CTextListItemDrawer( iTLBModel, font );
    CleanupStack::PushL( drawer );

    CTestSDKListsSnakingListBoxView* view =
            new( ELeave ) CTestSDKListsSnakingListBoxView();
    CleanupStack::PushL( view );
    STIF_ASSERT_NOT_NULL( view );

    CWsScreenDevice* device = iEikonEnvPointer->ScreenDevice();
    RWindowGroup& parent = iEikonEnvPointer->RootWin();
    RWindow* window = ( RWindow* )iContainer->DrawableWindow();
    TRect rect = iContainer->Rect();
    view->ConstructL( iTLBModel, drawer, device, &parent, window, rect, KEight );

    view->DoTestMoveToPreviousColumnL( CListBoxView::ESingleSelection );

    CleanupStack::PopAndDestroy( view );
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVMoveToNextColumnL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVMoveToNextColumnL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVMoveToNextColumnL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    iTLBModel = new( ELeave ) CTextListBoxModel();
    iTLBModel->ConstructL( textArray );

    const CFont* font = iEikonEnvPointer->NormalFont();

    CTextListItemDrawer* drawer = new( ELeave ) CTextListItemDrawer( iTLBModel, font );
    CleanupStack::PushL( drawer );

    CTestSDKListsSnakingListBoxView* view =
            new( ELeave ) CTestSDKListsSnakingListBoxView();
    CleanupStack::PushL( view );
    STIF_ASSERT_NOT_NULL( view );

    CWsScreenDevice* device = iEikonEnvPointer->ScreenDevice();
    RWindowGroup& parent = iEikonEnvPointer->RootWin();
    RWindow* window = ( RWindow* )iContainer->DrawableWindow();
    TRect rect = iContainer->Rect();
    view->ConstructL( iTLBModel, drawer, device, &parent, window, rect, KEight );

    view->DoTestMoveToNextColumnL( CListBoxView::ESingleSelection );

    CleanupStack::PopAndDestroy( view );
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVClearUnusedItemSpaceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVClearUnusedItemSpaceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVClearUnusedItemSpaceL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    iTLBModel = new( ELeave ) CTextListBoxModel();
    iTLBModel->ConstructL( textArray );

    const CFont* font = iEikonEnvPointer->NormalFont();

    CTextListItemDrawer* drawer = new( ELeave ) CTextListItemDrawer( iTLBModel, font );
    CleanupStack::PushL( drawer );

    CTestSDKListsSnakingListBoxView* view =
            new( ELeave ) CTestSDKListsSnakingListBoxView();
    CleanupStack::PushL( view );
    STIF_ASSERT_NOT_NULL( view );

    CWsScreenDevice* device = iEikonEnvPointer->ScreenDevice();
    RWindowGroup& parent = iEikonEnvPointer->RootWin();
    RWindow* window = ( RWindow* )iContainer->DrawableWindow();
    TRect rect = iContainer->Rect();
    view->ConstructL( iTLBModel, drawer, device, &parent, window, rect, KEight );

    view->DoTestClearUnusedItemSpace( KZero, KEight );

    CleanupStack::PopAndDestroy( view );
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVUpdateHScrollOffsetBasedOnTopItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVUpdateHScrollOffsetBasedOnTopItemIndexL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVUpdateHScrollOffsetBasedOnTopItemIndexL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    iTLBModel = new( ELeave ) CTextListBoxModel();
    iTLBModel->ConstructL( textArray );

    const CFont* font = iEikonEnvPointer->NormalFont();

    CTextListItemDrawer* drawer = new( ELeave ) CTextListItemDrawer( iTLBModel, font );
    CleanupStack::PushL( drawer );

    CTestSDKListsSnakingListBoxView* view =
            new( ELeave ) CTestSDKListsSnakingListBoxView();
    CleanupStack::PushL( view );
    STIF_ASSERT_NOT_NULL( view );

    CWsScreenDevice* device = iEikonEnvPointer->ScreenDevice();
    RWindowGroup& parent = iEikonEnvPointer->RootWin();
    RWindow* window = ( RWindow* )iContainer->DrawableWindow();
    TRect rect = iContainer->Rect();
    view->ConstructL( iTLBModel, drawer, device, &parent, window, rect, KEight );

    view->DoTestUpdateHScrollOffsetBasedOnTopItemIndex();

    CleanupStack::PopAndDestroy( view );
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBVSetItemOffsetInPixelsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBVSetItemOffsetInPixelsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBVTestModule" );
    _LIT( KTestEIKLBV, "In TestSLBVSetItemOffsetInPixelsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBV );
    // Print to log file
    iLog->Log( KTestEIKLBV );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    iTLBModel = new( ELeave ) CTextListBoxModel();
    iTLBModel->ConstructL( textArray );

    const CFont* font = iEikonEnvPointer->NormalFont();

    CTextListItemDrawer* drawer = new( ELeave ) CTextListItemDrawer( iTLBModel, font );
    CleanupStack::PushL( drawer );

    CTestSDKListsSnakingListBoxView* view =
            new( ELeave ) CTestSDKListsSnakingListBoxView();
    CleanupStack::PushL( view );
    STIF_ASSERT_NOT_NULL( view );

    CWsScreenDevice* device = iEikonEnvPointer->ScreenDevice();
    RWindowGroup& parent = iEikonEnvPointer->RootWin();
    RWindow* window = ( RWindow* )iContainer->DrawableWindow();
    TRect rect = iContainer->Rect();
    view->ConstructL( iTLBModel, drawer, device, &parent, window, rect, KEight );

    view->SetItemOffsetInPixels( 1 );
    view->ItemOffsetInPixels();

    CleanupStack::PopAndDestroy( view );
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// [End of file]
