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
* Description:  Test aknnavide.h
 *
*/

#include <aknnavilabel.h>

#include "testsdknavipane.h"
#include "testsdknavipanenavilblext.h"


// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviLblCAknNaviLabelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviLblCAknNaviLabelL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviLblCAknNaviLabel, "In TestNaviLblCAknNaviLabel" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviLblCAknNaviLabel );
    // Print to log file
    iLog->Log( KTestNaviLblCAknNaviLabel );
    
    TInt err = KErrNone;

    iNaviLbl = new (ELeave) CAknNaviLabel();
    
    STIF_ASSERT_NOT_NULL( iNaviLbl );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviLblDelete
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviLblDelete( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviLblDelete, "In TestNaviLblDelete" );
    TestModuleIf().Printf( 0, testsdknavipane,
    		KTestNaviLblDelete );
    // Print to log file
    iLog->Log( KTestNaviLblDelete );
    
    delete iNaviLbl;
    iNaviLbl = NULL;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviLblSetNaviLabelType
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviLblSetNaviLabelType( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviLblSetNaviLabelType, "In TestNaviLblSetNaviLabelType" );
    TestModuleIf().Printf( 0, testsdknavipane,
    		KTestNaviLblSetNaviLabelType );
    // Print to log file
    iLog->Log( KTestNaviLblSetNaviLabelType );
    
    TInt err = KErrNone;

    CAknNaviLabel::TNaviLabelType labelType = CAknNaviLabel::ENavigationLabel;
    
    TRAP( err, iNaviLbl->SetNaviLabelType( labelType ) );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviLblNaviLabelType
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviLblNaviLabelType( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviLblNaviLabelType, "In TestNaviLblNaviLabelType" );
    TestModuleIf().Printf( 0, testsdknavipane,
    		KTestNaviLblNaviLabelType );
    // Print to log file
    iLog->Log( KTestNaviLblNaviLabelType );
    
    TInt err = KErrNone;

    CAknNaviLabel::TNaviLabelType labelType = CAknNaviLabel::ENavigationLabel;
    
    iNaviLbl->SetNaviLabelType( labelType );
    
    CAknNaviLabel::TNaviLabelType type = iNaviLbl->NaviLabelType();
    
    STIF_ASSERT_EQUALS( type, CAknNaviLabel::ENavigationLabel );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviLblSetTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviLblSetTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviLblSetTextL, "In TestNaviLblSetTextL" );
    TestModuleIf().Printf( 0, testsdknavipane,
    		KTestNaviLblSetTextL );
    // Print to log file
    iLog->Log( KTestNaviLblSetTextL );
    
    TInt err = KErrNone;

    TBuf<10> text = _L("Test Text");
    
    TRAP( err, iNaviLbl->SetTextL( text ) );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviLblHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviLblHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviLblHandlePointerEventL, "In TestNaviLblHandlePointerEventL" );
    TestModuleIf().Printf( 0, testsdknavipane,
    		KTestNaviLblHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestNaviLblHandlePointerEventL );
    
    TInt err = KErrNone;
       
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
     
    TRAP( err, iNaviLbl->HandlePointerEventL( event ) );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviLblSizeChanged
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviLblSizeChangedL( CStifItemParser& /*aItem*/ )
	{
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviLblSizeChanged, "In TestNaviLblSizeChanged" );
    TestModuleIf().Printf( 0, testsdknavipane,
    		KTestNaviLblSizeChanged );
    // Print to log file
    iLog->Log( KTestNaviLblSizeChanged );
    
    TInt err = KErrNone;

    iNaviLblExt = new (ELeave) CTestSDKNavipaneNaviLblExt();
    
    TRAP( err, iNaviLblExt->SizeChanged() );
    
    delete iNaviLblExt;
    iNaviLblExt = NULL;
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviLblDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviLblDrawL( CStifItemParser& /*aItem*/ )
{
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviLblDraw, "In TestNaviLblDraw" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviLblDraw );
    // Print to log file
    iLog->Log( KTestNaviLblDraw );
    
    TInt err = KErrNone;

    iNaviLblExt = new (ELeave) CTestSDKNavipaneNaviLblExt();
    
    TRect rect( TPoint( 0, 0 ), TPoint( 30, 30 ) );
    TRAP( err, iNaviLblExt->Draw( rect ) );
    
    delete iNaviLblExt;
    iNaviLblExt = NULL;
    
    return err;
    }

// End of File
