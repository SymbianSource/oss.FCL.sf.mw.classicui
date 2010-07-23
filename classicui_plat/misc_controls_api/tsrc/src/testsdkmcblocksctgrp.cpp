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
#include <eikctgrp.h>
#include <s32mem.h>
#include <testsdkmisccontrols.rsg>
#include "testsdkmisccontrols.h"
#include "testsdkgroupprotectedclass.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestGCConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestGCConstructorL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestGCConstructorL, "In TestGCConstructorL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestGCConstructorL );
    // Print to log file
    iLog->Log( KTestGCConstructorL );

    iGroupControl = new (ELeave) TEikGroupControl();
    STIF_ASSERT_NOT_NULL( iGroupControl );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestGCConstructorWithControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestGCConstructorWithControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestGCConstructorWithControlL, "In TestGCConstructorWithControlL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestGCConstructorWithControlL );
    // Print to log file
    iLog->Log( KTestGCConstructorWithControlL );

    CCoeControl* control = new (ELeave) CCoeControl();
    TInt cId = 0;
    TInt length = 0;
    TInt flags = 0;
    iGroupControl = new (ELeave) TEikGroupControl( control, cId, length, flags );
    STIF_ASSERT_NOT_NULL( iGroupControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestGCIsLengthSet
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestGCIsLengthSet( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestGCIsLengthSet, "In TestGCIsLengthSet" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestGCIsLengthSet );
    // Print to log file
    iLog->Log( KTestGCIsLengthSet );

    TBool lengthSet = iGroupControl->IsLengthSet();
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestGCLength
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestGCLength( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestGCLength, "In TestGCLength" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestGCLength );
    // Print to log file
    iLog->Log( KTestGCLength );

    TInt length = iGroupControl->Length();
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestGCIsStretchable
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestGCIsStretchable( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestGCIsStretchable, "In TestGCIsStretchable" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestGCIsStretchable );
    // Print to log file
    iLog->Log( KTestGCIsStretchable );

    TBool stretchable = iGroupControl->IsStretchable();
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestGCSetLength
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestGCSetLength( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestGCSetLength, "In TestGCSetLength" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestGCSetLength );
    // Print to log file
    iLog->Log( KTestGCSetLength );
    TInt length = iGroupControl->Length();
    iGroupControl->SetLength( length );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestGCSetStretchable
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestGCSetStretchable( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestGCSetStretchable, "In TestGCSetStretchable" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestGCSetStretchable );
    // Print to log file
    iLog->Log( KTestGCSetStretchable );

    iGroupControl->SetStretchable();
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGConstructorL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGConstructorL, "In TestCGConstructorL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGConstructorL );
    // Print to log file
    iLog->Log( KTestCGConstructorL );
    iControlGroup = new (ELeave) CEikControlGroup();
    STIF_ASSERT_NOT_NULL( iControlGroup );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGDestructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGDestructor( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGDestructor, "In TestCGDestructor" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGDestructor );
    // Print to log file
    iLog->Log( KTestCGDestructor );
    delete iControlGroup;
    iControlGroup = NULL;
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGConstructL, "In TestCGConstructL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGConstructL );
    // Print to log file
    iLog->Log( KTestCGConstructL );
    TBool err = KErrNone;
    TRAP( err, iControlGroup->ConstructL( CEikControlGroup::EFromTopLeft, 
                               CEikControlGroup::ELayHorizontally ) );
    
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGAddControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGAddControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGAddControlL, "In TestCGAddControlL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGAddControlL );
    // Print to log file
    iLog->Log( KTestCGAddControlL );
    TBool err = KErrNone;
    CCoeControl* coeControl = new( ELeave ) CCoeControl();
    CleanupStack::PushL( coeControl );
    TInt cId = 1;
        
    TRAP( err, iControlGroup->AddControlL( coeControl, cId ) );
    CleanupStack::Pop( coeControl );
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGAddControlWithGroupControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGAddControlWithGroupControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGAddControlWithGroupControlL, "In TestCGAddControlWithGroupControlL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGAddControlWithGroupControlL );
    // Print to log file
    iLog->Log( KTestCGAddControlWithGroupControlL );
    TBool err = KErrNone;
    CCoeControl* control = new( ELeave ) CCoeControl();
    CleanupStack::PushL( control );
    TEikGroupControl ctrl;
    ctrl.iControl = control;
    ctrl.iId = 2;
    TRAP( err, iControlGroup->AddControlL( ctrl ) );
    CleanupStack::Pop();

    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGInsertControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGInsertControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGInsertControlL, "In TestCGInsertControlL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGInsertControlL );
    // Print to log file
    iLog->Log( KTestCGInsertControlL );
    TBool err = KErrNone;
    CCoeControl* control = new( ELeave ) CCoeControl();
    CleanupStack::PushL( control );
    TEikGroupControl ctrl;
    ctrl.iControl = control;
    ctrl.iId = 1;
    TInt cIndex = 0;
    TRAP( err, iControlGroup->InsertControlL( ctrl, cIndex ) );
    CleanupStack::Pop();

    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGDeleteControl
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGDeleteControl( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGDeleteControl, "In TestCGDeleteControl" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGDeleteControl );
    // Print to log file
    iLog->Log( KTestCGDeleteControl );

    TInt cIndex = 0;
    TInt count =1;
    iControlGroup->DeleteControl( cIndex, count );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGSetLengthInPixels
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGSetLengthInPixels( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGSetLengthInPixels, "In TestCGSetLengthInPixels" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGSetLengthInPixels );
    // Print to log file
    iLog->Log( KTestCGSetLengthInPixels );
    TInt length = 1;
    iControlGroup->SetLengthInPixels( length );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGSetBreadthInPixels
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGSetBreadthInPixels( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGSetBreadthInPixels, "In TestCGSetBreadthInPixels" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGSetBreadthInPixels );
    // Print to log file
    iLog->Log( KTestCGSetBreadthInPixels );
    TInt breadth = 1;
    iControlGroup->SetBreadthInPixels( breadth );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGSetControlSpacing
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGSetControlSpacing( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGSetControlSpacing, "In TestCGSetControlSpacing" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGSetControlSpacing );
    // Print to log file
    iLog->Log( KTestCGSetControlSpacing );
    TInt hSpacing = 3;
    TInt vSpacing = 3;
    iControlGroup->SetControlSpacing( hSpacing, vSpacing );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGSetControlLayout
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGSetControlLayout( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGSetControlLayout, "In TestCGSetControlLayout" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGSetControlLayout );
    // Print to log file
    iLog->Log( KTestCGSetControlLayout );

    iControlGroup->SetControlLayout( CEikControlGroup::EFromTopLeft, 
            CEikControlGroup::ELayHorizontally );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGSetNumberOfLines
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGSetNumberOfLines( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGSetNumberOfLines, "In TestCGSetNumberOfLines" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGSetNumberOfLines );
    // Print to log file
    iLog->Log( KTestCGSetNumberOfLines );
    TInt numLines = 1;
    TBool distributeEvenly = ETrue;
    iControlGroup->SetNumberOfLines( numLines, distributeEvenly );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGSetControlsAllSameSize
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGSetControlsAllSameSize( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGSetControlsAllSameSize, "In TestCGSetControlsAllSameSize" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGSetControlsAllSameSize );
    // Print to log file
    iLog->Log( KTestCGSetControlsAllSameSize );

    iControlGroup->SetControlsAllSameSize();
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGLayoutControls
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGLayoutControls( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGLayoutControls, "In TestCGLayoutControls" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGLayoutControls );
    // Print to log file
    iLog->Log( KTestCGLayoutControls );

    iControlGroup->LayoutControls();
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGControlByIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGControlByIdL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGControlByIdL, "In TestCGControlByIdL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGControlByIdL );
    // Print to log file
    iLog->Log( KTestCGControlByIdL );
    TInt cId = 0;
    CCoeControl* control = iControlGroup->ControlById( cId );
    STIF_ASSERT_NULL( control );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGIndexById
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGIndexById( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGIndexById, "In TestCGIndexById" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGIndexById );
    // Print to log file
    iLog->Log( KTestCGIndexById );
    TInt cId = 0;
    TInt cIndex = iControlGroup->IndexById( cId );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGReset
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGReset( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGReset, "In TestCGReset" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGReset );
    // Print to log file
    iLog->Log( KTestCGReset );

    iControlGroup->Reset();
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGControlId
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGControlId( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGControlId, "In TestCGControlId" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGControlId );
    // Print to log file
    iLog->Log( KTestCGControlId );
    CCoeControl* control = iControlGroup->ControlById( 0 );
    TInt ctl = iControlGroup->ControlId( control );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGControl, "In TestCGControl" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGControl );
    // Print to log file
    iLog->Log( KTestCGControl );
    TInt cId = 1;
    TInt cIndex = iControlGroup->IndexById( cId );

    CCoeControl* ctl  = iControlGroup->Control( cIndex );
    STIF_ASSERT_NOT_NULL( ctl );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGControlArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGControlArrayL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGControlArrayL, "In TestCGControlArrayL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGControlArrayL );
    // Print to log file
    iLog->Log( KTestCGControlArrayL );
    TInt cId = 1;
    TInt cIndex = iControlGroup->IndexById( cId );

    CArrayFix<TEikGroupControl>* ctl  = iControlGroup->ControlArray();
    STIF_ASSERT_NOT_NULL( ctl );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGOrientation
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGOrientation( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGOrientation, "In TestCGOrientation" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGOrientation );
    // Print to log file
    iLog->Log( KTestCGOrientation );
    CEikControlGroup::TOrientation orientation = iControlGroup->Orientation();

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGControlSpacing
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGControlSpacing( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGControlSpacing, "In TestCGControlSpacing" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGControlSpacing );
    // Print to log file
    iLog->Log( KTestCGControlSpacing );
    TInt vSpacing;
    TInt hSpacing;
    iControlGroup->ControlSpacing( vSpacing, hSpacing );
    
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGMinimumSize
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGMinimumSize( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGMinimumSize, "In TestCGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGMinimumSize );
    // Print to log file
    iLog->Log( KTestCGMinimumSize );

    TSize size = iControlGroup->MinimumSize();

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGCountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGCountComponentControls( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGCountComponentControls, "In TestCGCountComponentControls" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGCountComponentControls );
    // Print to log file
    iLog->Log( KTestCGCountComponentControls );

    TInt count = iControlGroup->CountComponentControls();

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGGetColorUseListL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGGetColorUseListL, "In TestCGGetColorUseListL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGGetColorUseListL );
    // Print to log file
    iLog->Log( KTestCGGetColorUseListL );
    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
            CArrayFixFlat<TCoeColorUse>( 4 );
    CleanupStack::PushL( colorUseList );
    TBool err = KErrNone;
    TRAP( err, iControlGroup->GetColorUseListL( *colorUseList ) );
    colorUseList->Reset();
    CleanupStack::PopAndDestroy( colorUseList );

    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGHandleResourceChange
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGHandleResourceChange( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGHandleResourceChange, "In TestCGHandleResourceChange" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGHandleResourceChange );
    // Print to log file
    iLog->Log( KTestCGHandleResourceChange );
    TInt type = 0;
    iControlGroup->HandleResourceChange( type );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGHandlePointerEventL, "In TestCGHandlePointerEventL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestCGHandlePointerEventL );
    TPointerEvent pointEvent;
    TBool err = KErrNone;
    pointEvent.iType = TPointerEvent::EButton1Down; 
    TRAP( err, iControlGroup->HandlePointerEventL( pointEvent ) );

    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGComponentControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGComponentControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGComponentControlL, "In TestCGComponentControlL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGComponentControlL );
    // Print to log file
    iLog->Log( KTestCGComponentControlL );
    CTestControlGroup* controlGroup = new (ELeave) CTestControlGroup();
    CleanupStack::PushL( controlGroup );
    controlGroup->ConstructL( CEikControlGroup::EFromTopLeft, 
                                       CEikControlGroup::ELayHorizontally );
    CCoeControl* coeControl = new( ELeave ) CCoeControl();
    CleanupStack::PushL( coeControl );
    TInt cId = 1;
    controlGroup->AddControlL( coeControl, cId );
    TInt count = controlGroup->CountComponentControls();
    CCoeControl* control = controlGroup->ComponentControl( count-1 );
    STIF_ASSERT_NOT_NULL( control );
    CleanupStack::Pop( coeControl );
    CleanupStack::PopAndDestroy();

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestCGWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestCGWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestCGWriteInternalStateL, "In TestCGWriteInternalStateL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestCGWriteInternalStateL );
    // Print to log file
    iLog->Log( KTestCGWriteInternalStateL );
    CTestControlGroup* controlGroup = new (ELeave) CTestControlGroup();
    CleanupStack::PushL( controlGroup );
    controlGroup->ConstructL( CEikControlGroup::EFromTopLeft, 
                                       CEikControlGroup::ELayHorizontally );
    CBufFlat* buf = CBufFlat::NewL( 200 );
    CleanupStack::PushL( buf );
    RBufWriteStream stream;
    stream.Open( *buf );
    TBool err = KErrNone;
    TRAP( err, controlGroup->WriteInternalStateL( stream ) );
    stream.Close();
    CleanupStack::PopAndDestroy( buf );
    CleanupStack::PopAndDestroy();
    return err;
    }
