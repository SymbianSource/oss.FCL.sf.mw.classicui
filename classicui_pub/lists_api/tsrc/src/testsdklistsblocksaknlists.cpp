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
* Description:  Test aknlists.h
*
*/

// [INCLUDE FILES]
#include <e32base.h>
#include <eikclb.h>
#include <testsdklists.rsg>
#include <coemain.h>
#include <coeaui.h>
#include <aknlists.h>
#include <barsread.h>
#include <eikdialg.h>
#include <eikclbd.h>

#include "testsdklists.h"
#include "testsdkcontainer.h"
#include "testsdklistscashslistbox.h"
#include "testsdklistssghslistbox.h"
#include "testsdklistssnhslistbox.h"
#include "testsdklistsspmslistbox.h"
#include "testsdklistssgpmslistbox.h"
#include "testsdklistsshpmslistbox.h"
#include "testsdklistssghpmslistbox.h"
#include "testsdklistsdpmslistbox.h"
#include "testsdklistsdlgpmslistbox.h"
#include "testsdklistsd2pmslistbox.h"
#include "testsdklistss2gpmslistbox.h"
#include "testsdklistsdgpmslistbox.h"
#include "testsdklistssetstylelistbox.h"

const TInt KThirty = 30;
// ============================ MEMBER FUNCTIONS ===============================

//========================== class CAknColumnListBox ===========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestACLBMakeViewClassInstanceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestACLBMakeViewClassInstanceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestCLBIDConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknColumnListBox* listBox = new( ELeave ) CAknColumnListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->MakeViewClassInstanceL();
    STIF_ASSERT_NOT_NULL( view );
    delete view;
    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestACLBCreateModelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestACLBCreateModelL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestACLBCreateModelL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknColumnListBox* listBox = new( ELeave ) CAknColumnListBox();
    CleanupStack::PushL( listBox );

    listBox->CreateModelL();

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestACLBAdjustRectHeightToWholeNumberOfItemsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestACLBAdjustRectHeightToWholeNumberOfItemsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestACLBAdjustRectHeightToWholeNumberOfItemsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknColumnListBox* listBox = new( ELeave ) CAknColumnListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    TRect rect = iContainer->Rect();
    listBox->AdjustRectHeightToWholeNumberOfItems( rect );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestACLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestACLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestACLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknColumnListBox* listBox = new( ELeave ) CAknColumnListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

//======================= class AknListBoxLinesTemplate ========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestLinesTemplateConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLinesTemplateConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLinesTemplateConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CEikColumnListBoxTypedef* linesTemplate = new( ELeave ) CEikColumnListBoxTypedef( 0 );
    CleanupStack::PushL( linesTemplate );
    STIF_ASSERT_NOT_NULL( linesTemplate );
    CleanupStack::Pop( linesTemplate );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLinesTemplateSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLinesTemplateSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLinesTemplateConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CEikColumnListBoxTypedef* listBox = new( ELeave ) CEikColumnListBoxTypedef( 0 );
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    listBox->SizeChanged();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLinesTemplateDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLinesTemplateDrawL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLinesTemplateDrawL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CEikColumnListBoxTypedef* listBox = new( ELeave ) CEikColumnListBoxTypedef( 0 );
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    TRect rect = iContainer->Rect();
    listBox->Draw( rect );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLinesTemplateCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLinesTemplateCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLinesTemplateCountComponentControlsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CEikColumnListBoxTypedef* listBox = new( ELeave ) CEikColumnListBoxTypedef( 0 );
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    listBox->CountComponentControls();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLinesTemplateComponentControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLinesTemplateComponentControlL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLinesTemplateComponentControlL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CEikColumnListBoxTypedef* listBox = new( ELeave ) CEikColumnListBoxTypedef( 0 );
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    listBox->ComponentControl( 0 );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

//======================== class CAknSingleStyleListBox ========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestASSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleStyleListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleStyleListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    listBox->SizeChanged();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleStyleListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    listBox->MinimumSize();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleStyleListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

//===================== class CAknSingleNumberStyleListBox =====================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestASNSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASNSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASNSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleNumberStyleListBox* listBox = new( ELeave ) CAknSingleNumberStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASNSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASNSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASNSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleNumberStyleListBox* listBox = new( ELeave ) CAknSingleNumberStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_NUMBER_STYLE );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    listBox->SizeChanged();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASNSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASNSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASNSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleNumberStyleListBox* listBox = new( ELeave ) CAknSingleNumberStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_NUMBER_STYLE );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    listBox->MinimumSize();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASNSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASNSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASNSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleNumberStyleListBox* listBox = new( ELeave ) CAknSingleNumberStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_NUMBER_STYLE );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

//==================== class CAknSingleHeadingStyleListBox =====================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestASHSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASHSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASHSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleHeadingStyleListBox* listBox = new( ELeave ) CAknSingleHeadingStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASHSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASHSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASHSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleHeadingStyleListBox* listBox = new( ELeave ) CAknSingleHeadingStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_HEADING_STYLE );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    listBox->SizeChanged();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASHSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASHSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASHSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleHeadingStyleListBox* listBox = new( ELeave ) CAknSingleHeadingStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_HEADING_STYLE );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    listBox->MinimumSize();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASHSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASHSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASHSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleHeadingStyleListBox* listBox = new( ELeave ) CAknSingleHeadingStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_HEADING_STYLE );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASHSLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASHSLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASHSLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsCASHSListBox* listBox = new( ELeave ) CTestSDKListsCASHSListBox();
    CleanupStack::PushL( listBox );

    listBox->CreateItemDrawerL();

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASHSLBMakeViewClassInstanceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASHSLBMakeViewClassInstanceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASHSLBMakeViewClassInstanceL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsCASHSListBox* listBox = new( ELeave ) CTestSDKListsCASHSListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_HEADING_STYLE );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->MakeViewClassInstanceL();
    STIF_ASSERT_NOT_NULL( view );
    delete view;
    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

//===================== class CAknSingleGraphicStyleListBox ====================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestASGSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASGSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASGSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleGraphicStyleListBox* listBox = new( ELeave ) CAknSingleGraphicStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASGSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASGSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASGSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleGraphicStyleListBox* listBox = new( ELeave ) CAknSingleGraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_GRAPHIC_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASGSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASGSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASGSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleGraphicStyleListBox* listBox = new( ELeave ) CAknSingleGraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_GRAPHIC_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASGSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASGSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASGSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleGraphicStyleListBox* listBox = new( ELeave ) CAknSingleGraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_GRAPHIC_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//================= class CAknSingleGraphicHeadingStyleListBox =================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestASGHSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASGHSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASGHSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleGraphicHeadingStyleListBox* listBox =
        new( ELeave ) CAknSingleGraphicHeadingStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASGHSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASGHSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASGHSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleGraphicHeadingStyleListBox* listBox =
        new( ELeave ) CAknSingleGraphicHeadingStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_GRAPHIC_HEADING_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASGHSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASGHSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASGHSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleGraphicHeadingStyleListBox* listBox =
        new( ELeave ) CAknSingleGraphicHeadingStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_GRAPHIC_HEADING_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASGHSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASGHSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASGHSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleGraphicHeadingStyleListBox* listBox =
        new( ELeave ) CAknSingleGraphicHeadingStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_GRAPHIC_HEADING_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASGHSLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASGHSLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASGHSLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsSGHSListBox* listBox = new( ELeave ) CTestSDKListsSGHSListBox();
    CleanupStack::PushL( listBox );

    listBox->CreateItemDrawerL();

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASGHSLBMakeViewClassInstanceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASGHSLBMakeViewClassInstanceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASGHSLBMakeViewClassInstanceL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsSGHSListBox* listBox = new( ELeave ) CTestSDKListsSGHSListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_GRAPHIC_HEADING_STYLE );
    listBox->ConstructFromResourceL( reader );

    CListBoxView* view = listBox->MakeViewClassInstanceL();
    STIF_ASSERT_NOT_NULL( view );
    delete view;
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//================= class CAknSingleNumberHeadingStyleListBox ==================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestASNHSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASNHSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASNHSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleNumberHeadingStyleListBox* listBox =
        new( ELeave ) CAknSingleNumberHeadingStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASNHSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASNHSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASNHSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleNumberHeadingStyleListBox* listBox =
        new( ELeave ) CAknSingleNumberHeadingStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_NUMBER_HEADING_STYLE );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    listBox->SizeChanged();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASNHSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASNHSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASNHSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleNumberHeadingStyleListBox* listBox =
        new( ELeave ) CAknSingleNumberHeadingStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_NUMBER_HEADING_STYLE );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    listBox->MinimumSize();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASNHSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASNHSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASNHSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleNumberHeadingStyleListBox* listBox =
        new( ELeave ) CAknSingleNumberHeadingStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_NUMBER_HEADING_STYLE );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASNHSLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASNHSLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASNHSLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsSNHSListBox* listBox = new( ELeave ) CTestSDKListsSNHSListBox();
    CleanupStack::PushL( listBox );

    listBox->CreateItemDrawerL();

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASNHSLBMakeViewClassInstanceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASNHSLBMakeViewClassInstanceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASNHSLBMakeViewClassInstanceL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsSNHSListBox* listBox = new( ELeave ) CTestSDKListsSNHSListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_NUMBER_HEADING_STYLE );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    CListBoxView* view = listBox->MakeViewClassInstanceL();
    STIF_ASSERT_NOT_NULL( view );
    delete view;
    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

//===================== class CAknSingleLargeStyleListBox ======================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestASLSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASLSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASLSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleLargeStyleListBox* listBox =
        new( ELeave ) CAknSingleLargeStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASLSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASLSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASLSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleLargeStyleListBox* listBox =
        new( ELeave ) CAknSingleLargeStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_LARGE_STYLE );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    listBox->SizeChanged();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASLSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASLSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASLSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleLargeStyleListBox* listBox =
        new( ELeave ) CAknSingleLargeStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_LARGE_STYLE );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    listBox->MinimumSize();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestASLSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestASLSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestASLSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleLargeStyleListBox* listBox =
        new( ELeave ) CAknSingleLargeStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_LARGE_STYLE );
    listBox->ConstructFromResourceL( reader );
    iContainer->SetControlL( listBox );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

//======================== class CAknDoubleStyleListBox ========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestADSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleStyleListBox* listBox = new( ELeave ) CAknDoubleStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestADSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleStyleListBox* listBox = new( ELeave ) CAknDoubleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestADSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleStyleListBox* listBox = new( ELeave ) CAknDoubleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestADSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleStyleListBox* listBox = new( ELeave ) CAknDoubleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//======================= class CAknDoubleStyle2ListBox ========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestADS2LBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADS2LBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADS2LBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleStyle2ListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_STYLE2 );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestADS2LBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADS2LBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADS2LBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleStyle2ListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );

    listBox->CreateItemDrawerL();

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestADS2LBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADS2LBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADS2LBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleStyle2ListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_STYLE2 );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//===================== class CAknDoubleNumberStyleListBox =====================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestADNSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADNSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADNSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleNumberStyleListBox* listBox =
        new( ELeave ) CAknDoubleNumberStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestADNSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADNSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADNSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleNumberStyleListBox* listBox =
        new( ELeave ) CAknDoubleNumberStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_NUMBER_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestADNSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADNSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADNSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleNumberStyleListBox* listBox =
        new( ELeave ) CAknDoubleNumberStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_NUMBER_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestADNSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADNSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADNSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleNumberStyleListBox* listBox =
        new( ELeave ) CAknDoubleNumberStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_NUMBER_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//====================== class CAknDoubleTimeStyleListBox ======================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestADTSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADTSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADTSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleTimeStyleListBox* listBox =
        new( ELeave ) CAknDoubleTimeStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestADTNSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADTSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADTSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleTimeStyleListBox* listBox =
        new( ELeave ) CAknDoubleTimeStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestADTSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADTSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADTSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleTimeStyleListBox* listBox =
        new( ELeave ) CAknDoubleTimeStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestADTSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADTSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADTSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleTimeStyleListBox* listBox =
        new( ELeave ) CAknDoubleTimeStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//====================== class CAknDoubleLargeStyleListBox ======================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestADLSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADLSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADLSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleLargeStyleListBox* listBox =
        new( ELeave ) CAknDoubleLargeStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestADLNSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADLSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADLSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleLargeStyleListBox* listBox =
        new( ELeave ) CAknDoubleLargeStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_LARGE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestADLSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADLSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADLSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleLargeStyleListBox* listBox =
        new( ELeave ) CAknDoubleLargeStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_LARGE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestADLSLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADLSLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADLSLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleLargeStyleListBox* listBox =
        new( ELeave ) CAknDoubleLargeStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    listBox->CreateItemDrawerL();
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestADLSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADLSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADLSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleLargeStyleListBox* listBox =
        new( ELeave ) CAknDoubleLargeStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_LARGE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//==================== class CAknDoubleGraphicStyleListBox =====================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestADGSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADGSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADGSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleGraphicStyleListBox* listBox =
        new( ELeave ) CAknDoubleGraphicStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestADGNSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADGSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADGSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleGraphicStyleListBox* listBox =
        new( ELeave ) CAknDoubleGraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_GRAPHIC_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestADGSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADGSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADGSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleGraphicStyleListBox* listBox =
        new( ELeave ) CAknDoubleGraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_GRAPHIC_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestADGSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestADGSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestADGSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleGraphicStyleListBox* listBox =
        new( ELeave ) CAknDoubleGraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_GRAPHIC_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//==================== class CAknDouble2GraphicStyleListBox ====================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestAD2GSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestAD2GSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestAD2GSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDouble2GraphicStyleListBox* listBox =
        new( ELeave ) CAknDouble2GraphicStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestAD2GNSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestAD2GSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestAD2GSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDouble2GraphicStyleListBox* listBox =
        new( ELeave ) CAknDouble2GraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_GRAPHIC_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestAD2GSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestAD2GSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestAD2GSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDouble2GraphicStyleListBox* listBox =
        new( ELeave ) CAknDouble2GraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_GRAPHIC_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestAD2GSLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestAD2GSLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestAD2GSLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDouble2GraphicStyleListBox* listBox =
        new( ELeave ) CAknDouble2GraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->CreateItemDrawerL();

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestAD2GSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestAD2GSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestAD2GSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDouble2GraphicStyleListBox* listBox =
        new( ELeave ) CAknDouble2GraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_GRAPHIC_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//===================== class CAknDouble2LargeStyleListBox =====================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestAD2LSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestAD2LSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestAD2LSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDouble2LargeStyleListBox* listBox =
        new( ELeave ) CAknDouble2LargeStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestAD2LNSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestAD2LSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestAD2LSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDouble2LargeStyleListBox* listBox =
        new( ELeave ) CAknDouble2LargeStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_LARGE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestAD2LSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestAD2LSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestAD2LSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDouble2LargeStyleListBox* listBox =
        new( ELeave ) CAknDouble2LargeStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_LARGE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestAD2LSLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestAD2LSLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestAD2LSLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDouble2LargeStyleListBox* listBox =
        new( ELeave ) CAknDouble2LargeStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    listBox->CreateItemDrawerL();
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestAD2LSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestAD2LSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestAD2LSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDouble2LargeStyleListBox* listBox =
        new( ELeave ) CAknDouble2LargeStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_LARGE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//============== class CAknDouble2GraphicLargeGraphicStyleListBox ==============
// -----------------------------------------------------------------------------
// CTestSDKLists::TestAD2GLGSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestAD2GLGSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestAD2GLGSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDouble2GraphicLargeGraphicStyleListBox* listBox =
        new( ELeave ) CAknDouble2GraphicLargeGraphicStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestAD2GLGNSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestAD2GLGSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestAD2GLGSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDouble2GraphicLargeGraphicStyleListBox* listBox =
        new( ELeave ) CAknDouble2GraphicLargeGraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_LARGE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestAD2GLGSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestAD2GLGSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestAD2GLGSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDouble2GraphicLargeGraphicStyleListBox* listBox =
        new( ELeave ) CAknDouble2GraphicLargeGraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_LARGE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestAD2GLGSLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestAD2GLGSLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestAD2GLGSLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDouble2GraphicLargeGraphicStyleListBox* listBox =
        new( ELeave ) CAknDouble2GraphicLargeGraphicStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    listBox->CreateItemDrawerL();
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestAD2GLGSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestAD2GLGSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestAD2GLGSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDouble2GraphicLargeGraphicStyleListBox* listBox =
        new( ELeave ) CAknDouble2GraphicLargeGraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_LARGE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//================== class CAknFormDoubleGraphicStyleListBox ===================

// -----------------------------------------------------------------------------
// CTestSDKLists::TestAFDGSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestAFDGSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestAFDGSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknFormDoubleGraphicStyleListBox* listBox =
        new( ELeave ) CAknFormDoubleGraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_FORM_DOUBLE_GRAPHIC_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestAFDGSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestAFDGSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestAFDGSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknFormDoubleGraphicStyleListBox* listBox =
        new( ELeave ) CAknFormDoubleGraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_FORM_DOUBLE_GRAPHIC_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//====================== class CAknFormDoubleStyleListBox ======================

// -----------------------------------------------------------------------------
// CTestSDKLists::TestAFDSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestAFDSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestAFDSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknFormDoubleStyleListBox* listBox =
        new( ELeave ) CAknFormDoubleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_FORM_DOUBLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestAFDSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestAFDSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestAFDSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknFormDoubleStyleListBox* listBox =
        new( ELeave ) CAknFormDoubleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_FORM_DOUBLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//======================= class CAknSettingStyleListBox ========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSettingSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSettingSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSettingSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSettingStyleListBox* listBox = new( ELeave ) CAknSettingStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSettingSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSettingSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSettingSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSettingStyleListBox* listBox = new( ELeave ) CAknSettingStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSettingSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSettingSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSettingSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSettingStyleListBox* listBox = new( ELeave ) CAknSettingStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSettingSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSettingSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSettingSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSettingStyleListBox* listBox = new( ELeave ) CAknSettingStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//==================== class CAknSettingNumberStyleListBox =====================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSettingNSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSettingNSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSettingNSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSettingNumberStyleListBox* listBox =
        new( ELeave ) CAknSettingNumberStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSettingNSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSettingNSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSettingNSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSettingNumberStyleListBox* listBox =
        new( ELeave ) CAknSettingNumberStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSettingNSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSettingNSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSettingNSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSettingNumberStyleListBox* listBox =
        new( ELeave ) CAknSettingNumberStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSettingNSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSettingNSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSettingNSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSettingNumberStyleListBox* listBox =
        new( ELeave ) CAknSettingNumberStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//=================== class CAknSinglePopupMenuStyleListBox ====================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSPMSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSPMSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSPMSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSinglePopupMenuStyleListBox* listBox =
        new( ELeave ) CAknSinglePopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSPMSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSPMSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSPMSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSinglePopupMenuStyleListBox* listBox =
        new( ELeave ) CAknSinglePopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSPMSLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSPMSLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSPMSLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsSPMSListBox* listBox =
        new( ELeave ) CTestSDKListsSPMSListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    listBox->CreateItemDrawerL();
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSPMSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSPMSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSPMSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsSPMSListBox* listBox =
        new( ELeave ) CTestSDKListsSPMSListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//================ class CAknSingleGraphicPopupMenuStyleListBox ================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSGPMSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSGPMSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSGPMSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleGraphicPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknSingleGraphicPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSGPMSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSGPMSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSGPMSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleGraphicPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknSingleGraphicPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSGPMSLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSGPMSLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSGPMSLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsSGPMSListBox* listBox =
        new( ELeave ) CTestSDKListsSGPMSListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    listBox->CreateItemDrawerL();
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSGPMSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSGPMSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSGPMSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsSGPMSListBox* listBox =
        new( ELeave ) CTestSDKListsSGPMSListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//=============== class CAknSingleGraphicBtPopupMenuStyleListBox ===============
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSGBPMSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSGBPMSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSGBPMSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleGraphicBtPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknSingleGraphicBtPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSGBPMSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSGBPMSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSGBPMSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleGraphicBtPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknSingleGraphicBtPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//================ class CAknSingleHeadingPopupMenuStyleListBox ================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSHPMSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSHPMSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSHPMSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleHeadingPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknSingleHeadingPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSHPMSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSHPMSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSHPMSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleHeadingPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknSingleHeadingPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSHPMSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSHPMSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSHPMSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleHeadingPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknSingleHeadingPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSHPMSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSHPMSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSHPMSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleHeadingPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknSingleHeadingPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSHPMSLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSHPMSLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSHPMSLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsSHPMSListBox* listBox =
        new( ELeave ) CTestSDKListsSHPMSListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    listBox->CreateItemDrawerL();
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

//============= class CAknSingleGraphicHeadingPopupMenuStyleListBox ============
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSGHPMSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSGHPMSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSGHPMSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleGraphicHeadingPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknSingleGraphicHeadingPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSGHPMSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSGHPMSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSGHPMSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleGraphicHeadingPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknSingleGraphicHeadingPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSGHPMSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSGHPMSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSGHPMSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleGraphicHeadingPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknSingleGraphicHeadingPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSGHPMSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSGHPMSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSGHPMSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleGraphicHeadingPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknSingleGraphicHeadingPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSGHPMSLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSGHPMSLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSGHPMSLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsSGHPMSListBox* listBox =
        new( ELeave ) CTestSDKListsSGHPMSListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    listBox->CreateItemDrawerL();
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

//==================== class CAknDoublePopupMenuStyleListBox ===================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestDPMSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestDPMSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestDPMSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoublePopupMenuStyleListBox* listBox =
        new( ELeave ) CAknDoublePopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestDPMSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestDPMSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestDPMSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoublePopupMenuStyleListBox* listBox =
        new( ELeave ) CAknDoublePopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestDPMSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestDPMSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestDPMSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoublePopupMenuStyleListBox* listBox =
        new( ELeave ) CAknDoublePopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestDPMSLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestDPMSLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestDPMSLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsDPMSListBox* listBox =
        new( ELeave ) CTestSDKListsDPMSListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    listBox->CreateItemDrawerL();
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

//================== class CAknSinglePopupSubmenuStyleListBox ==================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSPSSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSPSSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSPSSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSinglePopupSubmenuStyleListBox* listBox =
        new( ELeave ) CAknSinglePopupSubmenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSPSSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSPSSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSPSSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSinglePopupSubmenuStyleListBox* listBox =
        new( ELeave ) CAknSinglePopupSubmenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSPSSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSPSSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSPSSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSinglePopupSubmenuStyleListBox* listBox =
        new( ELeave ) CAknSinglePopupSubmenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//============== class CAknDoubleLargeGraphicPopupMenuStyleListBox =============
// -----------------------------------------------------------------------------
// CTestSDKLists::TestDLGPMSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestDLGPMSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestDLGPMSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleLargeGraphicPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknDoubleLargeGraphicPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestDLGPMSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestDLGPMSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestDLGPMSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleLargeGraphicPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknDoubleLargeGraphicPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestDLGPMSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestDLGPMSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestDLGPMSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleLargeGraphicPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknDoubleLargeGraphicPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestDLGPMSLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestDLGPMSLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestDLGPMSLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsDLGPMSListBox* listBox =
        new( ELeave ) CTestSDKListsDLGPMSListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    listBox->CreateItemDrawerL();
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

//==================== class CAknDouble2PopupMenuStyleListBox ===================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestD2PMSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestD2PMSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestD2PMSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDouble2PopupMenuStyleListBox* listBox =
        new( ELeave ) CAknDouble2PopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestD2PMSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestD2PMSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestD2PMSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDouble2PopupMenuStyleListBox* listBox =
        new( ELeave ) CAknDouble2PopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestD2PMSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestD2PMSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestD2PMSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDouble2PopupMenuStyleListBox* listBox =
        new( ELeave ) CAknDouble2PopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestD2PMSLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestD2PMSLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestD2PMSLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsD2PMSListBox* listBox =
        new( ELeave ) CTestSDKListsD2PMSListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    listBox->CreateItemDrawerL();
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

//================ class CAknSingle2GraphicPopupMenuStyleListBox ===============
// -----------------------------------------------------------------------------
// CTestSDKLists::TestS2GPMSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestS2GPMSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestS2GPMSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingle2GraphicPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknSingle2GraphicPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestS2GPMSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestS2GPMSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestS2GPMSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingle2GraphicPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknSingle2GraphicPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestS2GPMSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestS2GPMSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestS2GPMSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingle2GraphicPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknSingle2GraphicPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestS2GPMSLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestS2GPMSLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestS2GPMSLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsS2GPMSListBox* listBox =
        new( ELeave ) CTestSDKListsS2GPMSListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    listBox->CreateItemDrawerL();
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestS2GPMSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestS2GPMSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestS2GPMSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsS2GPMSListBox* listBox =
        new( ELeave ) CTestSDKListsS2GPMSListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//================ class CAknDoubleGraphicPopupMenuStyleListBox ================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestDGPMSLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestDGPMSLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestDGPMSLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleGraphicPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknDoubleGraphicPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestDGPMSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestDGPMSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestDGPMSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleGraphicPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknDoubleGraphicPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestDGPMSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestDGPMSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestDGPMSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleGraphicPopupMenuStyleListBox* listBox =
        new( ELeave ) CAknDoubleGraphicPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestDGPMSLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestDGPMSLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestDGPMSLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsDGPMSListBox* listBox =
        new( ELeave ) CTestSDKListsDGPMSListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    listBox->CreateItemDrawerL();
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestDGPMSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestDGPMSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestDGPMSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsDGPMSListBox* listBox =
        new( ELeave ) CTestSDKListsDGPMSListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//========================== class CAknSetStyleListBox =========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSetSLBConstructWithWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSetSLBConstructWithWindowL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSetSLBConstructWithWindowL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSetStyleListBox* listBox = new( ELeave ) CAknSetStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    listBox->ConstructWithWindowL( iContainer, 0 );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSetSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSetSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSetSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSetStyleListBox* listBox = new( ELeave ) CAknSetStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSetSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSetSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSetSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSetStyleListBox* listBox = new( ELeave ) CAknSetStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSetSLBDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSetSLBDrawL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSetSLBDrawL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSetStyleListBox* listBox = new( ELeave ) CAknSetStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TRect rect = iContainer->Rect();
    listBox->Draw( rect );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSetSLBMopSupplyObjectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSetSLBMopSupplyObjectL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSetSLBMopSupplyObjectL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSetStyleListBox* listBox = new( ELeave ) CAknSetStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TTypeUid::Ptr ptr = TTypeUid::Null();
    ptr = listBox->MopSupplyObject( CEikDialog::ETypeId );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSetSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSetSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSetSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSetStyleListBox* listBox = new( ELeave ) CAknSetStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSetSLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSetSLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSetSLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsSetStyleListBox* listBox =
        new( ELeave ) CTestSDKListsSetStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    listBox->CreateItemDrawerL();
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSetSLBMakeViewClassInstanceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSetSLBMakeViewClassInstanceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSetSLBMakeViewClassInstanceL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CTestSDKListsSetStyleListBox* listBox =
        new( ELeave ) CTestSDKListsSetStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    listBox->ConstructWithWindowL( iContainer, 0 );

    CListBoxView* view = listBox->MakeViewClassInstanceL();
    STIF_ASSERT_NOT_NULL( view );
    delete view;
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

//====================== class CAknFormGraphicStyleListBox =====================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestFGSLBConstructWithWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFGSLBConstructWithWindowL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestFGSLBConstructWithWindowL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknFormGraphicStyleListBox* listBox = new( ELeave ) CAknFormGraphicStyleListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    listBox->ConstructWithWindowL( iContainer, 0 );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFGSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFGSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestFGSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknFormGraphicStyleListBox* listBox = new( ELeave ) CAknFormGraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFGSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFGSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSetSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknFormGraphicStyleListBox* listBox = new( ELeave ) CAknFormGraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFGSLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFGSLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestFGSLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknFormGraphicStyleListBox* listBox = new( ELeave ) CAknFormGraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->CreateItemDrawerL();

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFGSLBAdjustRectHeightToWholeNumberOfItemsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFGSLBAdjustRectHeightToWholeNumberOfItemsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestFGSLBAdjustRectHeightToWholeNumberOfItemsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknFormGraphicStyleListBox* listBox = new( ELeave ) CAknFormGraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TRect rect = iContainer->Rect();
    listBox->AdjustRectHeightToWholeNumberOfItems( rect );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFGSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFGSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestFGSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknFormGraphicStyleListBox* listBox = new( ELeave ) CAknFormGraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//==================== class CAknFormGraphicWideStyleListBox ===================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestFGWSLBSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFGWSLBSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestFGWSLBSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknFormGraphicWideStyleListBox* listBox =
        new( ELeave ) CAknFormGraphicWideStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFGWSLBMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFGWSLBMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestFGWSLBMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknFormGraphicWideStyleListBox* listBox =
        new( ELeave ) CAknFormGraphicWideStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFGWSLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFGWSLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestFGWSLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknFormGraphicWideStyleListBox* listBox =
        new( ELeave ) CAknFormGraphicWideStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//=========================== class CAknPinbStyleGrid ==========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestPSGSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestPSGSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestPSGSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknPinbStyleGrid* listBox = new( ELeave ) CAknPinbStyleGrid();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_SELECTION_GRID );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestPSGMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestPSGMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestPSGMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknPinbStyleGrid* listBox = new( ELeave ) CAknPinbStyleGrid();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_SELECTION_GRID );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestPSGHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestPSGHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestPSGHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknPinbStyleGrid* listBox = new( ELeave ) CAknPinbStyleGrid();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_SELECTION_GRID );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//========================== class CAknQdialStyleGrid ==========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestQSGSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestQSGSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestQSGSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknQdialStyleGrid* listBox = new( ELeave ) CAknQdialStyleGrid();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_SELECTION_GRID );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestQSGMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestQSGMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestQSGMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknQdialStyleGrid* listBox = new( ELeave ) CAknQdialStyleGrid();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_SELECTION_GRID );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestQSGHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestQSGHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestQSGHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknQdialStyleGrid* listBox = new( ELeave ) CAknQdialStyleGrid();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_SELECTION_GRID );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//======================== class CAknCaleMonthStyleGrid ========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestCMSGSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCMSGSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestCMSGSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknCaleMonthStyleGrid* listBox = new( ELeave ) CAknCaleMonthStyleGrid();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_SELECTION_GRID );
    listBox->ConstructFromResourceL( reader );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCMSGMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCMSGMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestCMSGMinimumSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknCaleMonthStyleGrid* listBox = new( ELeave ) CAknCaleMonthStyleGrid();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_SELECTION_GRID );
    listBox->ConstructFromResourceL( reader );

    listBox->MinimumSize();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCMSGHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCMSGHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestCMSGHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknCaleMonthStyleGrid* listBox = new( ELeave ) CAknCaleMonthStyleGrid();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_SELECTION_GRID );
    listBox->ConstructFromResourceL( reader );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    listBox->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//======================== class CAknColumnListBoxView =========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestACLBVEnableFindEmptyListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestACLBVEnableFindEmptyListL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestACLBVEnableFindEmptyListL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknColumnListBox* listBox = new( ELeave ) CAknColumnListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CAknColumnListBoxView* view =
        static_cast<CAknColumnListBoxView*> ( listBox->View() );
    STIF_ASSERT_NOT_NULL( view );

    view->EnableFindEmptyList();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestACLBVSetFindEmptyListStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestACLBVSetFindEmptyListStateL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestACLBVSetFindEmptyListStateL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknColumnListBox* listBox = new( ELeave ) CAknColumnListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CAknColumnListBoxView* view =
        static_cast<CAknColumnListBoxView*> ( listBox->View() );
    STIF_ASSERT_NOT_NULL( view );

    view->SetFindEmptyListState( EFalse );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestACLBVDrawEmptyListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestACLBVDrawEmptyListL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestACLBVDrawEmptyListL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknColumnListBox* listBox = new( ELeave ) CAknColumnListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CAknColumnListBoxView* view =
        static_cast<CAknColumnListBoxView*> ( listBox->View() );
    STIF_ASSERT_NOT_NULL( view );

    view->DrawEmptyList( iContainer->Rect() );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestACLBVCalcBottomItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestACLBVCalcBottomItemIndexL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestACLBVCalcBottomItemIndexL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknColumnListBox* listBox = new( ELeave ) CAknColumnListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CAknColumnListBoxView* view =
        static_cast<CAknColumnListBoxView*> ( listBox->View() );
    STIF_ASSERT_NOT_NULL( view );

    view->CalcBottomItemIndex();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//======================= class CAknSetStyleListBoxView ========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSSLBVDrawEmptyListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSSLBVDrawEmptyListL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSSLBVDrawEmptyListL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSetStyleListBox* listBox = new( ELeave ) CAknSetStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    CAknSetStyleListBoxView* view =
        static_cast<CAknSetStyleListBoxView*> ( listBox->View() );
    STIF_ASSERT_NOT_NULL( view );

    view->DrawEmptyList( iContainer->Rect() );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//======================= class CSingleHeadingStyleView ========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSHSVDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSHSVDrawL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSHSLBVDrawL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleHeadingStyleListBox* listBox = new( ELeave ) CAknSingleHeadingStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_HEADING_STYLE );
    listBox->ConstructFromResourceL( reader );

    CSingleHeadingStyleView* view = static_cast<CSingleHeadingStyleView*>( listBox->View() );
    STIF_ASSERT_NOT_NULL( view );
    
    TRect rect = iContainer->Rect();
    view->Draw( &rect );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSHSVDrawEmptyListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSHSVDrawEmptyListL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSHSVDrawEmptyListL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleHeadingStyleListBox* listBox = new( ELeave ) CAknSingleHeadingStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_HEADING_STYLE );
    listBox->ConstructFromResourceL( reader );

    CSingleHeadingStyleView* view = static_cast<CSingleHeadingStyleView*>( listBox->View() );
    STIF_ASSERT_NOT_NULL( view );
    
    view->DrawEmptyList( iContainer->Rect() );
    
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//==================== class CSingleHeadingStyleItemDrawer =====================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSHSIDConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSHSIDConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSHSIDConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    iTLBModel = new( ELeave ) CTextListBoxModel();
    iTLBModel->ConstructL( textArray );

    const CFont* font = iEikonEnvPointer->NormalFont();

    CColumnListBoxData* data = CColumnListBoxData::NewL();
    CleanupStack::PushL( data );
    data->ConstructL( font );

    CSingleHeadingStyleItemDrawer* drawer =
        new( ELeave ) CSingleHeadingStyleItemDrawer( iTLBModel, font, data );
    CleanupStack::PushL( drawer );
    STIF_ASSERT_NOT_NULL( drawer );

    CleanupStack::PopAndDestroy( drawer );
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSHSIDDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSHSIDDestructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSHSIDDestructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    iTLBModel = new( ELeave ) CTextListBoxModel();
    iTLBModel->ConstructL( textArray );

    const CFont* font = iEikonEnvPointer->NormalFont();

    CColumnListBoxData* data = CColumnListBoxData::NewL();
    CleanupStack::PushL( data );
    data->ConstructL( font );

    CSingleHeadingStyleItemDrawer* drawer =
        new( ELeave ) CSingleHeadingStyleItemDrawer( iTLBModel, font, data );
    CleanupStack::PushL( drawer );
    STIF_ASSERT_NOT_NULL( drawer );

    CleanupStack::Pop( 3 );
    delete drawer;
    drawer = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSHSIDDrawItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSHSIDDrawItemL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSHSIDDrawItemL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleHeadingStyleListBox* listBox = new( ELeave ) CAknSingleHeadingStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_HEADING_STYLE );
    listBox->ConstructFromResourceL( reader );

    CSingleHeadingStyleItemDrawer* drawer =
        static_cast<CSingleHeadingStyleItemDrawer*> ( listBox->ItemDrawer() );
    STIF_ASSERT_NOT_NULL( drawer );
    
    drawer->DrawItem( 0, TPoint( 0, 0 ), EFalse, ETrue, ETrue, ETrue );
    
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSHSIDSetTopItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSHSIDSetTopItemIndexL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestSHSIDSetTopItemIndexL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknSingleHeadingStyleListBox* listBox = new( ELeave ) CAknSingleHeadingStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_HEADING_STYLE );
    listBox->ConstructFromResourceL( reader );

    CSingleHeadingStyleItemDrawer* drawer =
        static_cast<CSingleHeadingStyleItemDrawer*> ( listBox->ItemDrawer() );
    STIF_ASSERT_NOT_NULL( drawer );
    
    drawer->SetTopItemIndex( 0 );
    
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//===================== class CDoubleLargeStyleItemDrawer ======================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestDLSIDConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestDLSIDConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestDLSIDConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    iListBox = new( ELeave ) CEikListBox();

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    iTLBModel = new( ELeave ) CTextListBoxModel();
    iTLBModel->ConstructL( textArray );

    const CFont* font = iEikonEnvPointer->NormalFont();

    CFormattedCellListBoxData* data = CFormattedCellListBoxData::NewL();
    CleanupStack::PushL( data );
    data->ConstructL( font );

    CDoubleLargeStyleItemDrawer* drawer =
        new( ELeave ) CDoubleLargeStyleItemDrawer( iTLBModel, font, data, iListBox );
    CleanupStack::PushL( drawer );
    STIF_ASSERT_NOT_NULL( drawer );

    CleanupStack::PopAndDestroy( drawer );
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestDLSIDDrawItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestDLSIDDrawItemL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestDLSIDDrawItemL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleLargeStyleListBox* listBox = new ( ELeave ) CAknDoubleLargeStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_LARGE_STYLE );
    listBox->ConstructFromResourceL( reader );

    CDoubleLargeStyleItemDrawer* drawer =
        static_cast<CDoubleLargeStyleItemDrawer*> ( listBox->ItemDrawer() );
    STIF_ASSERT_NOT_NULL( drawer );
    
    drawer->DrawItem( 0, TPoint( 0, 0 ), EFalse, ETrue, ETrue, ETrue );

    CleanupStack::PopAndDestroy( 2 );


    return KErrNone;
    }

//================= class CWordWrappedFormattedCellItemDrawer ==================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestWWFCIDConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestWWFCIDConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestWWFCIDConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    iListBox = new( ELeave ) CEikListBox();

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    iTLBModel = new( ELeave ) CTextListBoxModel();
    iTLBModel->ConstructL( textArray );

    const CFont* font = iEikonEnvPointer->NormalFont();

    CFormattedCellListBoxData* data = CFormattedCellListBoxData::NewL();
    CleanupStack::PushL( data );
    data->ConstructL( font );

    CWordWrappedFormattedCellItemDrawer* drawer =
        new( ELeave ) CWordWrappedFormattedCellItemDrawer( 
                iTLBModel, font, data, iListBox, 1, 9 );
    CleanupStack::PushL( drawer );
    STIF_ASSERT_NOT_NULL( drawer );

    CleanupStack::PopAndDestroy( drawer );
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestWWFCIDDrawItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestWWFCIDDrawItemL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestWWFCIDDrawItemL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleStyle2ListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_STYLE2 );
    listBox->ConstructFromResourceL( reader );

    CWordWrappedFormattedCellItemDrawer* drawer =
        static_cast<CWordWrappedFormattedCellItemDrawer*> ( listBox->ItemDrawer() );

    drawer->DrawItem( 0, TPoint( 0, 0 ), EFalse, ETrue, ETrue, ETrue );

    CleanupStack::PopAndDestroy( 2 );


    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestWWFCIDDrawItemTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestWWFCIDDrawItemTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestWWFCIDDrawItemTextL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknDoubleStyle2ListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_DOUBLE_STYLE2 );
    listBox->ConstructFromResourceL( reader );

    CWordWrappedFormattedCellItemDrawer* drawer =
        static_cast<CWordWrappedFormattedCellItemDrawer*> ( listBox->ItemDrawer() );

    drawer->DrawItemText( 0, iContainer->Rect(), ETrue, ETrue, ETrue );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

//========================== class AknListBoxLayouts ===========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLSetupStandardListBoxL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLSetupStandardListBoxL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBLSetupStandardListBoxL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    iListBox = new( ELeave ) CEikListBox();

    AknListBoxLayouts::SetupStandardListBox( *iListBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLSetupGridPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLSetupGridPosL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBLSetupGridPosL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknGrid* grid = new( ELeave ) CAknGrid();
    CleanupStack::PushL( grid );
    grid->ConstructL( iContainer, 0 );
    AknListBoxLayouts::SetupGridPos( *grid, 1, 1, 1, 1, 1, 1 );
    CleanupStack::PopAndDestroy( grid );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLSetupListboxPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLSetupListboxPosL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBLSetupListboxPosL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CEikColumnListBox* listBox = new ( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    AknListBoxLayouts::SetupListboxPos( *listBox, 1, 1, 1, 1, 1, 1 );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLSetupStandardColumnListboxL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLSetupStandardColumnListboxL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBLSetupStandardColumnListboxL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CColumnListBoxItemDrawer* drawer = new( ELeave ) CColumnListBoxItemDrawer();
    CleanupStack::PushL( drawer );

    AknListBoxLayouts::SetupStandardColumnListbox( drawer );
    CleanupStack::PopAndDestroy( drawer );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLSetupStandardFormListboxL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLSetupStandardFormListboxL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBLSetupStandardFormListboxL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CFormattedCellListBoxItemDrawer* drawer =
        new( ELeave ) CFormattedCellListBoxItemDrawer( NULL,
                CCoeEnv::Static()->NormalFont(), NULL );
    CleanupStack::PushL( drawer );

    AknListBoxLayouts::SetupStandardFormListbox( drawer );
    CleanupStack::PopAndDestroy( drawer );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLSetupStandardGridL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLSetupStandardGridL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBLSetupStandardGridL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknGrid* grid = new( ELeave ) CAknGrid();
    CleanupStack::PushL( grid );
    grid->ConstructL( iContainer, 0 );
    AknListBoxLayouts::SetupStandardGrid( *grid );
    CleanupStack::PopAndDestroy( grid );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLSetupColumnGfxCellL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLSetupColumnGfxCellL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBLSetupColumnGfxCellL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CEikColumnListBox* listBox = new ( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    AknListBoxLayouts::SetupColumnGfxCell(
            *listBox,
            listBox->ItemDrawer(),
            1, 1, 1, 1, 1, 1, 1, 1, 8
            );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLSetupColumnTextCellL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLSetupColumnTextCellL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBLSetupColumnTextCellL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    const CFont* font = CCoeEnv::Static()->NormalFont();

    AknListBoxLayouts::SetupColumnTextCell(
            *listBox, listBox->ItemDrawer(),
            1, font, 1, 1, 1, 1, 1,
            CGraphicsContext::ECenter, 1, 8
            );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLSetupColumnTextCellTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLSetupColumnTextCellTwoL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBLSetupColumnTextCellTwoL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    TAknTextLineLayout layout;
    AknListBoxLayouts::SetupColumnTextCell(
            *listBox,
            listBox->ItemDrawer(),
            1, layout, 1, 8
            );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLSetupFormGfxCellL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLSetupFormGfxCellL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBLSetupFormGfxCellL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );

    CFormattedCellListBoxItemDrawer* itemDrawer = listBox->ItemDrawer();

    AknListBoxLayouts::SetupFormGfxCell(
            *listBox, itemDrawer,
            1, 1, 1, 1, 1, 1, 1, 
            TPoint( 0, 0 ), TPoint( 0, 0 )
            );

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLSetupGridFormGfxCellL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLSetupGridFormGfxCellL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBLSetupGridFormGfxCellL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknGrid* grid = new ( ELeave ) CAknGrid();
    CleanupStack::PushL( grid );
    grid->ConstructL( iContainer, 0 );

    AknListBoxLayouts::SetupGridFormGfxCell(
            *grid, grid->ItemDrawer(),
            1, 1, 1, 1, 1, 1, 1, 
            TPoint( 0, 0 ), TPoint( 0, 0 )
            );

    CleanupStack::PopAndDestroy( grid );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLSetupGridFormGfxCellTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLSetupGridFormGfxCellTwoL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBLSetupGridFormGfxCellTwoL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CAknGrid* grid = new( ELeave ) CAknGrid();
    CleanupStack::PushL( grid );
    grid->ConstructL( iContainer, 0 );

    TPoint point( 0, 0 );
    TAknWindowLineLayout layout;
    AknListBoxLayouts::SetupGridFormGfxCell(
            *grid, grid->ItemDrawer(),
            1, layout, point, point
            );

    CleanupStack::PopAndDestroy( grid );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLSetupFormTextCellL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLSetupFormTextCellL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBLSetupFormTextCellL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );

    CFormattedCellListBoxItemDrawer* itemDrawer = listBox->ItemDrawer();
    const CFont* font = iEikonEnvPointer->NormalFont();
    AknListBoxLayouts::SetupFormTextCell(
            *listBox, itemDrawer, 1, font, 1, 1, 1, 1, 1, 
            CGraphicsContext::ECenter, TPoint( 0, 0 ), TPoint( 0, 0 )
            );

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLSetupFormAntiFlickerTextCellL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLSetupFormAntiFlickerTextCellL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBLSetupFormAntiFlickerTextCellL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );

    CFormattedCellListBoxItemDrawer* itemDrawer = listBox->ItemDrawer();
    const CFont* font = iEikonEnvPointer->NormalFont();
    AknListBoxLayouts::SetupFormAntiFlickerTextCell(
            *listBox, itemDrawer, 1,
            font, 1, 1, 1, 1, 1, CGraphicsContext::ECenter, 
            TPoint( 0, 0 ), TPoint( 0, 0 )
            );

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLSetupFormTextCellTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLSetupFormTextCellTwoL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBLSetupFormTextCellTwoL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );

    CFormattedCellListBoxItemDrawer* itemDrawer = listBox->ItemDrawer();
    TAknTextLineLayout layout;
    TPoint point( 0, 0 );
    AknListBoxLayouts::SetupFormTextCell(
            *listBox, itemDrawer, 
            1, layout, point, point
            );

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLSetupFormAntiFlickerTextCellTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLSetupFormAntiFlickerTextCellTwoL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBLSetupFormAntiFlickerTextCellTwoL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );

    CFormattedCellListBoxItemDrawer* itemDrawer = listBox->ItemDrawer();
    TAknTextLineLayout layout;
    TPoint point( 0, 0 );
    AknListBoxLayouts::SetupFormAntiFlickerTextCell(
            *listBox, itemDrawer, 1,
            layout, point, point
            );

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLSetupColumnGfxCellTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLSetupColumnGfxCellTwoL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBLSetupColumnGfxCellTwoL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    TAknWindowLineLayout layout;
    AknListBoxLayouts::SetupColumnGfxCell( *listBox, listBox->ItemDrawer(), 1, layout, 1, 8 );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLSetupFormGfxCellTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLSetupFormGfxCellTwoL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBLSetupFormGfxCellTwoL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );

    CFormattedCellListBoxItemDrawer* itemDrawer = listBox->ItemDrawer();
    TAknWindowLineLayout layout;
    TPoint point( 0, 0 );
    AknListBoxLayouts::SetupFormGfxCell( *listBox, itemDrawer, 1, layout, point, point );

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBLSetupListboxPosTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBLSetupListboxPosTwoL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBLSetupListboxPosTwoL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );

    TAknWindowLineLayout layout;
    layout.iC = 1;
    layout.il = 1;
    layout.it = 1;
    layout.ir = 1;
    layout.ib = 1;
    layout.iW = 1;
    layout.iH = 1;
    AknListBoxLayouts::SetupListboxPos( *listBox, layout );

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

//=========================== class AknListBoxUtils ============================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBUHandleItemRemovalAndPositionHighlightL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBUHandleItemRemovalAndPositionHighlightL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBUHandleItemRemovalAndPositionHighlightL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );
    AknListBoxUtils::HandleItemRemovalAndPositionHighlightL(
            listBox, 1, ETrue );
    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBUHandleItemRemovalAndPositionHighlightTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBUHandleItemRemovalAndPositionHighlightTwoL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBUHandleItemRemovalAndPositionHighlightTwoL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );
    CArrayFix<TInt>* array = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( array );
    array->AppendL( 1 );
    array->AppendL( 2 );
    
    AknListBoxUtils::HandleItemRemovalAndPositionHighlightL(
            listBox, 1, *array );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy( 2 );
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBUListBoxLinesShownL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBUListBoxLinesShownL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AKNLISTSTestModule" );
    _LIT( KTestAknlists, "In TestLBUListBoxLinesShownL" );
    TestModuleIf().Printf( 0, KTestModule, KTestAknlists );
    // Print to log file
    iLog->Log( KTestAknlists );

    AknListBoxUtils::ListBoxLinesShown( NULL, NULL );

    return KErrNone;
    }
