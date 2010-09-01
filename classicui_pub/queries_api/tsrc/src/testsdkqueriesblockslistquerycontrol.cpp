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
* Description:  Test aknlistquerycontrol.h
*
*/

//INCLUDE
#include <aknlistquerycontrol.h>
#include <testsdkqueries.rsg>
#include <barsread.h>
#include <aknpopuplayout.h>

#include "testsdkqueries.h"
#include "testsdkqueriescontainer.h"
#include "testsdkqueriesview.h"

const TInt KZero = 0;
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KThree = 3;
const TInt KFifty = 50;
const TInt KThirty = 30;


// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqcConstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknListQueryControl* controlDlg = new( ELeave ) CAknListQueryControl;
    CleanupStack::PushL( controlDlg );
    STIF_ASSERT_NOT_NULL( controlDlg );
    CleanupStack::PopAndDestroy( controlDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqcConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CAknListQueryControl* controlDlg = new( ELeave ) CAknListQueryControl;
    CleanupStack::PushL( controlDlg );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LIST_QUERY_CONTROL );
    controlDlg->SetContainerWindowL( *iContainer );
    controlDlg->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy( KTwo );
    
    CAknListQueryControl* listDlg = new( ELeave ) CAknListQueryControl;
    CleanupStack::PushL( listDlg );
    TResourceReader readertwo;
    CCoeEnv::Static()->CreateResourceReaderLC( readertwo, R_LIST_QUERY_MSG_CONTROL );
    listDlg->SetContainerWindowL( *iContainer );
    listDlg->ConstructFromResourceL( readertwo );
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqcDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknListQueryControl* controlDlg = new( ELeave ) CAknListQueryControl;
    CleanupStack::PushL( controlDlg );
    CleanupStack::PopAndDestroy( controlDlg );
    return KErrNone;
    }
//Some problem
// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqcMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    CAknListQueryControl* controlDlg = new( ELeave ) CAknListQueryControl;
    CleanupStack::PushL( controlDlg );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LIST_QUERY_CONTROL );
    controlDlg->SetContainerWindowL( *iContainer );
    controlDlg->ConstructFromResourceL( reader );
    
    TAknPopupWindowLayoutDef* layoutDef = new( ELeave ) TAknPopupWindowLayoutDef;
    CleanupStack::PushL( layoutDef );
    controlDlg->SetLayout( layoutDef );
    
    TSize size( KFifty, KFifty );
    TSize returnSize = controlDlg->MinimumSize();
    STIF_ASSERT_EQUALS( size, returnSize );
    
    CleanupStack::Pop( layoutDef );
    CleanupStack::PopAndDestroy( KTwo );
    
    CAknListQueryControl* Dlg = new( ELeave ) CAknListQueryControl;
    CleanupStack::PushL( Dlg );
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LIST_QUERY_NOHEADING_CONTROL );
    Dlg->SetContainerWindowL( *iContainer );
    Dlg->ConstructFromResourceL( reader );
    
    TAknPopupWindowLayoutDef* layout = new( ELeave ) TAknPopupWindowLayoutDef;
    CleanupStack::PushL( layout );
    Dlg->SetLayout( layout );
    
    TSize sizeTwo( KThirty, KThirty );
    TSize returnSizeTwo = Dlg->MinimumSize();
    STIF_ASSERT_EQUALS( sizeTwo, returnSizeTwo );
    
    CleanupStack::Pop( layout );
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqcCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {
    CAknListQueryControl* controlDlg = new( ELeave ) CAknListQueryControl;
    CleanupStack::PushL( controlDlg );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LIST_QUERY_CONTROL );
    controlDlg->SetContainerWindowL( *iContainer );
    controlDlg->ConstructFromResourceL( reader );
    
    TInt controlNumber = controlDlg->CountComponentControls();
    STIF_ASSERT_NOT_EQUALS( KOne, controlNumber );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcComponentControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqcComponentControlL( CStifItemParser& /*aItem*/ )
    {
    CAknListQueryControl* controlDlg = new( ELeave ) CAknListQueryControl;
    CleanupStack::PushL( controlDlg );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LIST_QUERY_MSG_CONTROL );
    controlDlg->SetContainerWindowL( *iContainer );
    controlDlg->ConstructFromResourceL( reader );
    
    CCoeControl* control = controlDlg->ComponentControl( KZero );
    STIF_ASSERT_NOT_NULL( control );
    
    control = controlDlg->ComponentControl( KOne );
    STIF_ASSERT_NOT_NULL( control );
    
    control = controlDlg->ComponentControl( KTwo );
    STIF_ASSERT_NOT_NULL( control );
    
    control = controlDlg->ComponentControl( KThree );
    STIF_ASSERT_NULL( control );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqcOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CAknListQueryControl* controlDlg = new( ELeave ) CAknListQueryControl;
    CleanupStack::PushL( controlDlg );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LIST_QUERY_MSG_CONTROL );
    controlDlg->SetContainerWindowL( *iContainer );
    controlDlg->ConstructFromResourceL( reader );
    
    TKeyEvent event;
    event.iCode = EKeyDownArrow;
    controlDlg->OfferKeyEventL( event, EEventKey );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqcDrawL( CStifItemParser& /*aItem*/ )
    {
    CAknListQueryControl* controlDlg = new( ELeave ) CAknListQueryControl;
    CleanupStack::PushL( controlDlg );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LIST_QUERY_MSG_CONTROL );
    
    TAknPopupWindowLayoutDef* layout = new( ELeave ) TAknPopupWindowLayoutDef;
    CleanupStack::PushL( layout );
    controlDlg->SetLayout( layout );
        
    iContainer->ActivateGc();
    controlDlg->SetContainerWindowL( *iContainer );
    controlDlg->ConstructFromResourceL( reader );
    TRect rect( TPoint( KFifty, KFifty ), TPoint( KFifty, KFifty ));
    controlDlg->Draw( rect );
    iContainer->DeactivateGc();
    
    CleanupStack::Pop( layout );
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcSetLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqcSetLayoutL( CStifItemParser& aItem )
    {
    TInt err = TestLqcDrawL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcFocusChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqcFocusChangedL( CStifItemParser& /*aItem*/ )
    {
    CAknListQueryControl* controlDlg = new( ELeave ) CAknListQueryControl;
    CleanupStack::PushL( controlDlg );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LIST_QUERY_MSG_CONTROL );
    controlDlg->SetContainerWindowL( *iContainer );
    controlDlg->ConstructFromResourceL( reader );
    
    TAknPopupWindowLayoutDef* layout = new( ELeave ) TAknPopupWindowLayoutDef;
    CleanupStack::PushL( layout );
    controlDlg->SetLayout( layout );
    
    controlDlg->FocusChanged( EDrawNow );
    
    CleanupStack::Pop( layout );
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcListboxL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqcListboxL( CStifItemParser& /*aItem*/ )
    {
    CAknListQueryControl* controlDlg = new( ELeave ) CAknListQueryControl;
    CleanupStack::PushL( controlDlg );
    
    CEikFormattedCellListBox* listBox = controlDlg->Listbox();
    STIF_ASSERT_NULL( listBox );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LIST_QUERY_MSG_CONTROL );
    controlDlg->SetContainerWindowL( *iContainer );
    controlDlg->ConstructFromResourceL( reader );
    
    listBox = controlDlg->Listbox();
    STIF_ASSERT_NOT_NULL( listBox );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcHeadingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqcHeadingL( CStifItemParser& /*aItem*/ )
    {
    CAknListQueryControl* controlDlg = new( ELeave ) CAknListQueryControl;
    CleanupStack::PushL( controlDlg );
    
    CAknPopupHeadingPane* heading = controlDlg->Heading();
    STIF_ASSERT_NULL( heading );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LIST_QUERY_MSG_CONTROL );
    controlDlg->SetContainerWindowL( *iContainer );
    controlDlg->ConstructFromResourceL( reader );
    
    heading = controlDlg->Heading();
    STIF_ASSERT_NOT_NULL( heading );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcListtypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqcListtypeL( CStifItemParser& /*aItem*/ )
    {
    CAknListQueryControl* controlDlg = new( ELeave ) CAknListQueryControl;
    CleanupStack::PushL( controlDlg );
    
    TInt type = controlDlg->Listtype();
    STIF_ASSERT_EQUALS( KZero, type );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LIST_QUERY_MSG_CONTROL );
    controlDlg->SetContainerWindowL( *iContainer );
    controlDlg->ConstructFromResourceL( reader );
    
    type = controlDlg->Listtype();
    STIF_ASSERT_NOT_EQUALS( KZero, type );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqcHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CAknListQueryControl* controlDlg = new( ELeave ) CAknListQueryControl;
    CleanupStack::PushL( controlDlg );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LIST_QUERY_MSG_CONTROL );
    controlDlg->SetContainerWindowL( *iContainer );
    controlDlg->ConstructFromResourceL( reader );
    
    TAknPopupWindowLayoutDef* layout = new( ELeave ) TAknPopupWindowLayoutDef;
    CleanupStack::PushL( layout );
    controlDlg->SetLayout( layout );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TInt err = KErrNone;
    TRAP( err, controlDlg->HandlePointerEventL( event ) );
    
    CleanupStack::Pop( layout );
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqclistboxL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqclistboxL( CStifItemParser& /*aItem*/ )
    {
    CAknListQueryControl* controlDlg = new( ELeave ) CAknListQueryControl;
    CleanupStack::PushL( controlDlg );
    
    CEikFormattedCellListBox* listBox = controlDlg->listbox();
    STIF_ASSERT_NULL( listBox );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LIST_QUERY_MSG_CONTROL );
    controlDlg->SetContainerWindowL( *iContainer );
    controlDlg->ConstructFromResourceL( reader );
    
    listBox = controlDlg->listbox();
    STIF_ASSERT_NOT_NULL( listBox );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

//End file



