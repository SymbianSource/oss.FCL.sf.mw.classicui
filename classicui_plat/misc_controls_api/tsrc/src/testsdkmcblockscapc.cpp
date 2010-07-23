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
#include <barsread.h>
#include <testsdkmisccontrols.rsg>
#include <s32mem.h>
#include <aknappui.h>
#include <aknscontrolcontext.h> 
#include <avkon.mbg>
#include <akniconutils.h> 

#include "testsdkmisccontrols.h"
#include "testsdkmisccontrolcontainer.h"
#include "testsdkcapcprotectedclass.h"
#include "testsdkcapcsubprotectedclass.h"


// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestMCConstructorL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCConstructorL, "In TestMCConstructorL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCConstructorL );
    // Print to log file
    iLog->Log( KTestMCConstructorL );

    
    iCaptionedControl = new (ELeave) CEikCaptionedControl();
    STIF_ASSERT_NOT_NULL( iCaptionedControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCDestructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestMCDestructor( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCDestructor, "In TestMCDestructor" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCDestructor );
    // Print to log file
    iLog->Log( KTestMCDestructor );
    if ( iCaptionedControl )
        {
        delete iCaptionedControl;
        iCaptionedControl = NULL;
        }
    
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetUsesEars
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestMCSetUsesEars( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetUsesEars, "In TestMCSetUsesEars" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetUsesEars );
    // Print to log file
    iLog->Log( KTestMCSetUsesEars );

    iCaptionedControl->SetUsesEars();
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetSpaceSharingFlags
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestMCSetSpaceSharingFlags( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetSpaceSharingFlags, "In TestMCSetSpaceSharingFlags" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetSpaceSharingFlags );
    // Print to log file
    iLog->Log( KTestMCSetSpaceSharingFlags );
    TInt flags = 0x20;
    iCaptionedControl->SetSpaceSharingFlags( flags );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetExtraAscent
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestMCSetExtraAscent( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetExtraAscent, "In TestMCSetExtraAscent" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetExtraAscent );
    // Print to log file
    iLog->Log( KTestMCSetExtraAscent );

    iCaptionedControl->SetExtraAscent();
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetCaptionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestMCSetCaptionL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetCaptionL, "In TestMCSetCaptionL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetCaptionL );
    // Print to log file
    iLog->Log( KTestMCSetCaptionL );
    _LIT( Kbuf, "buf");
    TBool err = KErrNone;
    TRAP( err, iCaptionedControl->SetCaptionL( Kbuf ) );
    
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetTrailerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestMCSetTrailerL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetTrailerL, "In TestMCSetTrailerL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetTrailerL );
    // Print to log file
    iLog->Log( KTestMCSetTrailerL );
    _LIT( Kbuf, "buf");
    TBool err = KErrNone;
    TRAP( err, iCaptionedControl->SetTrailerL( Kbuf ) );
    
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetCurrentL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCSetCurrentL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetCurrentL, "In TestMCSetCurrentL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetCurrentL );
    // Print to log file
    iLog->Log( KTestMCSetCurrentL );
    TInt controlId = 1;
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );

    iCaptionedControl = dia->Line( controlId );
    iCaptionedControl->SetCurrent( EFalse );

    CleanupStack::PopAndDestroy( dia );
    iCaptionedControl = NULL;
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCCheckDimmedDisplayStateL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCCheckDimmedDisplayStateL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCCheckDimmedDisplayStateL, "In TestMCCheckDimmedDisplayStateL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCCheckDimmedDisplayStateL );
    // Print to log file
    iLog->Log( KTestMCCheckDimmedDisplayStateL );
    TInt controlId = 1;
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    iCaptionedControl = dia->Line( controlId );
    iCaptionedControl->CheckDimmedDisplayState();
    CleanupStack::PopAndDestroy( dia );
    iCaptionedControl = NULL;
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCResetMinimumSizes
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCResetMinimumSizes( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCResetMinimumSizes, "In TestMCResetMinimumSizes" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCResetMinimumSizes );
    // Print to log file
    iLog->Log( KTestMCResetMinimumSizes );

    iCaptionedControl->ResetMinimumSizes();

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCIsLatent
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCIsLatent( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCIsLatent, "In TestMCIsLatent" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCIsLatent );
    // Print to log file
    iLog->Log( KTestMCIsLatent );

    TBool latent = iCaptionedControl->IsLatent();

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetLatentL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCSetLatentL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetLatentL, "In TestMCSetLatentL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetLatentL );
    // Print to log file
    iLog->Log( KTestMCSetLatentL );
    TInt controlId = 1;
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    iCaptionedControl = dia->Line( controlId );
    TBool latent = iCaptionedControl->IsLatent();
    iCaptionedControl->SetLatent( latent );
    CleanupStack::PopAndDestroy( dia );
    iCaptionedControl = NULL;
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCLatentGroupLineFollows
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCLatentGroupLineFollows( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCLatentGroupLineFollows, "In TestMCLatentGroupLineFollows" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCLatentGroupLineFollows );
    // Print to log file
    iLog->Log( KTestMCLatentGroupLineFollows );

    TBool control = iCaptionedControl->LatentGroupLineFollows();

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetLatentGroupLineFollows
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCSetLatentGroupLineFollows( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetLatentGroupLineFollows, "In TestMCSetLatentGroupLineFollows" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetLatentGroupLineFollows );
    // Print to log file
    iLog->Log( KTestMCSetLatentGroupLineFollows );
    TBool control = iCaptionedControl->LatentGroupLineFollows();
    iCaptionedControl->SetLatentGroupLineFollows( control );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCDividerAfter
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCDividerAfter( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCDividerAfter, "In TestMCDividerAfter" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCDividerAfter );
    // Print to log file
    iLog->Log( KTestMCDividerAfter );

    TBool dividerAfter = iCaptionedControl->DividerAfter();

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetDividerAfter
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCSetDividerAfter( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetDividerAfter, "In TestMCSetDividerAfter" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetDividerAfter );
    // Print to log file
    iLog->Log( KTestMCSetDividerAfter );

    TBool dividerAfter = iCaptionedControl->DividerAfter();
    iCaptionedControl->SetDividerAfter( dividerAfter );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCTakesEnterKey
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCTakesEnterKey( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCTakesEnterKey, "In TestMCTakesEnterKey" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCTakesEnterKey );
    // Print to log file
    iLog->Log( KTestMCTakesEnterKey );

    TBool enterKey = iCaptionedControl->TakesEnterKey();
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetTakesEnterKey
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCSetTakesEnterKey( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetTakesEnterKey, "In TestMCSetTakesEnterKey" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetTakesEnterKey );
    // Print to log file
    iLog->Log( KTestMCSetTakesEnterKey );

    TBool enterKey = iCaptionedControl->TakesEnterKey();
    iCaptionedControl->SetTakesEnterKey( enterKey );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCOfferHotKeys
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCOfferHotKeys( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCOfferHotKeys, "In TestMCOfferHotKeys" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCOfferHotKeys );
    // Print to log file
    iLog->Log( KTestMCOfferHotKeys );

    TBool hotKeys = iCaptionedControl->OfferHotKeys();

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetOfferHotKeys
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCSetOfferHotKeys( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetOfferHotKeys, "In TestMCSetOfferHotKeys" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetOfferHotKeys );
    // Print to log file
    iLog->Log( KTestMCSetOfferHotKeys );

    TBool hotKeys = iCaptionedControl->OfferHotKeys();
    iCaptionedControl->SetOfferHotKeys( hotKeys );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCHandleControlEventL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCHandleControlEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCHandleControlEventL, "In TestMCHandleControlEventL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCHandleControlEventL );
    // Print to log file
    iLog->Log( KTestMCHandleControlEventL );

    TBool err = KErrNone;
    CCoeControl* control = new ( ELeave ) CCoeControl();
    TRAP( err, iCaptionedControl->HandleControlEventL( control, MCoeControlObserver::EEventRequestExit ) );

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCMinimumSizeL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCMinimumSizeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCMinimumSizeL, "In TestMCMinimumSizeL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCMinimumSizeL );
    // Print to log file
    iLog->Log( KTestMCMinimumSizeL );
    TInt controlId = 1;
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    iCaptionedControl = dia->Line( controlId );

    TSize size = iCaptionedControl->MinimumSize();
    STIF_ASSERT_NOT_NULL( &size );
    CleanupStack::PopAndDestroy( dia );
    iCaptionedControl = NULL;
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCConstructFromResourceL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCConstructFromResourceL, "In TestMCConstructFromResourceL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCConstructFromResourceL );
    // Print to log file
    iLog->Log( KTestMCConstructFromResourceL );

    CEikDialog* dialog = new ( ELeave ) CEikDialog();
    dialog->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    CleanupStack::PopAndDestroy( dialog );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCOfferKeyEventL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCOfferKeyEventL, "In TestMCOfferKeyEventL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCOfferKeyEventL );
    // Print to log file
    iLog->Log( KTestMCOfferKeyEventL );
    TInt controlId = 1;
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    iCaptionedControl = dia->Line( controlId );

    TBool err = KErrNone;
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyCBA1;

    TRAP( err, TKeyResponse key = iCaptionedControl->OfferKeyEventL( keyEvent, EEventKey ) );
    CleanupStack::PopAndDestroy( dia );
    iCaptionedControl = NULL;
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCGetColorUseListL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCGetColorUseListL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCGetColorUseListL, "In TestMCGetColorUseListL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCGetColorUseListL );
    // Print to log file
    iLog->Log( KTestMCGetColorUseListL );
    TInt controlId = 1;
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    iCaptionedControl = dia->Line( controlId );
    TBool err = KErrNone;
    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
            CArrayFixFlat<TCoeColorUse>( 4 );
    CleanupStack::PushL( colorUseList );

    TRAP( err, iCaptionedControl->GetColorUseListL( *colorUseList ) );
    colorUseList->Reset();
    CleanupStack::PopAndDestroy( colorUseList );
    CleanupStack::PopAndDestroy( dia );
    iCaptionedControl = NULL;

    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCHandleResourceChangeL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCHandleResourceChangeL, "In TestMCHandleResourceChangeL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCHandleResourceChangeL );
    // Print to log file
    iLog->Log( KTestMCHandleResourceChangeL );
    TInt controlId = 1;
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    iCaptionedControl = dia->Line( controlId );
    TInt type = 0;
    iCaptionedControl->HandleResourceChange( type );
    CleanupStack::PopAndDestroy( dia );
    iCaptionedControl = NULL;
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCInputCapabilities
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCInputCapabilities( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCInputCapabilities, "In TestMCInputCapabilities" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCInputCapabilities );
    // Print to log file
    iLog->Log( KTestMCInputCapabilities );

    TCoeInputCapabilities capabilities = iCaptionedControl->InputCapabilities();
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetDimmed
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCSetDimmed( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetDimmed, "In TestMCSetDimmed" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetDimmed );
    // Print to log file
    iLog->Log( KTestMCSetDimmed );

    iCaptionedControl->SetDimmed( ETrue );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCHandlePointerEventL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCHandlePointerEventL, "In TestMCHandlePointerEventL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestMCHandlePointerEventL );
    TBool err = KErrNone;
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;
    TInt controlId = 1;
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    iCaptionedControl = dia->Line( controlId );
    TRAP( err, iCaptionedControl->HandlePointerEventL( pointEvent ) );
    CleanupStack::PopAndDestroy( dia );
    iCaptionedControl = NULL;
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCDrawL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCDrawL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCDrawL, "In TestMCDrawL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCDrawL );
    // Print to log file
    iLog->Log( KTestMCDrawL );
    TRect rect( 10, 10, 10, 10 );
    TInt controlId = 1;
    CTestSubCaptionedControl* captionedControl = new ( ELeave ) CTestSubCaptionedControl();
    CleanupStack::PushL( captionedControl );
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    captionedControl = static_cast<CTestSubCaptionedControl*>( dia->Line( controlId ) );

    iConsoleContainer = new ( ELeave ) CMiscControlsContainer();
    iConsoleContainer->ConstructL( rect );
    captionedControl->SetContainerWindowL( *iConsoleContainer );
    iConsoleContainer->ActivateGc();

    captionedControl->Draw( rect );
    iConsoleContainer->DeactivateGc();
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCWriteInternalStateL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCWriteInternalStateL, "In TestMCWriteInternalStateL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCWriteInternalStateL );
    // Print to log file
    iLog->Log( KTestMCWriteInternalStateL );
    TBool err = KErrNone;
    CTestSubCaptionedControl* captionedControl = new ( ELeave ) CTestSubCaptionedControl();
    CleanupStack::PushL( captionedControl );
    TInt controlId = 1;
    CBufFlat* buf = CBufFlat::NewL( 200 );
    CleanupStack::PushL( buf );
    RBufWriteStream stream;
    stream.Open( *buf );
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    captionedControl = static_cast<CTestSubCaptionedControl*>( dia->Line( controlId ) );
    TRAP( err, captionedControl->WriteInternalStateL( stream ) );
    stream.Close();
    CleanupStack::PopAndDestroy( 3 );


    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCMopSupplyObjectL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCMopSupplyObjectL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCMopSupplyObjectL, "In TestMCMopSupplyObjectL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCMopSupplyObjectL );
    // Print to log file
    iLog->Log( KTestMCMopSupplyObjectL );

    CTestSubCaptionedControl* captionedControl = new ( ELeave ) CTestSubCaptionedControl();
    CleanupStack::PushL( captionedControl );
    TInt controlId = 1;
    TTypeUid typeId( MAknsControlContext::ETypeId );
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    captionedControl = static_cast<CTestSubCaptionedControl*>( dia->Line( controlId ) );
    captionedControl->MopSupplyObject( typeId );
    CleanupStack::PopAndDestroy( 2 );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetToolTipTextL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCSetToolTipTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetToolTipTextL, "In TestMCSetToolTipTextL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetToolTipTextL );
    // Print to log file
    iLog->Log( KTestMCSetToolTipTextL );
    TBool err = KErrNone;

    TInt controlId = 1;
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    iCaptionedControl = dia->Line( controlId );
    _LIT( Kbuf, "buf");
    TRAP( err, iCaptionedControl->SetToolTipTextL( Kbuf ) );
    CleanupStack::PopAndDestroy( dia );
    iCaptionedControl = NULL;
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCToolTipTextL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCToolTipTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCToolTipTextL, "In TestMCToolTipTextL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCToolTipTextL );
    // Print to log file
    iLog->Log( KTestMCToolTipTextL );

    TInt controlId = 1;
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    iCaptionedControl = dia->Line( controlId );
    
    iCaptionedControl->ToolTipText();

    CleanupStack::PopAndDestroy( dia );
    iCaptionedControl = NULL;
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetBitmapFromFileL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCSetBitmapFromFileL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetBitmapFromFileL, "In TestMCSetBitmapFromFileL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetBitmapFromFileL );
    // Print to log file
    iLog->Log( KTestMCSetBitmapFromFileL );
    TBool err = KErrNone;
    TInt controlId = 1;
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    iCaptionedControl = dia->Line( controlId );

    TRAP( err, iCaptionedControl->SetBitmapFromFileL( AknIconUtils::AvkonIconFileName(),
                    EMbmAvkonQgn_graf_tab_21) );
    CleanupStack::PopAndDestroy( dia );
    iCaptionedControl = NULL;
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetEditableL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCSetEditableL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetEditableL, "In TestMCSetEditableL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetEditableL );
    // Print to log file
    iLog->Log( KTestMCSetEditableL );
    TBool err = KErrNone;
    TInt controlId = 1;
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    iCaptionedControl = dia->Line( controlId );

    TRAP( err, iCaptionedControl->SetEditableL( ETrue ) );
    CleanupStack::PopAndDestroy( dia );
    iCaptionedControl = NULL;
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetFormFlagsL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCSetFormFlagsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetFormFlagsL, "In TestMCSetFormFlagsL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetFormFlagsL );
    // Print to log file
    iLog->Log( KTestMCSetFormFlagsL );

    TInt controlId = 1;
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    iCaptionedControl = dia->Line( controlId );
    TInt flags = 0; 
    iCaptionedControl->SetFormFlags( flags );
    CleanupStack::PopAndDestroy( dia );
    iCaptionedControl = NULL;
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCGetFullCaptionTextL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCGetFullCaptionTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCGetFullCaptionTextL, "In TestMCGetFullCaptionTextL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCGetFullCaptionTextL );
    // Print to log file
    iLog->Log( KTestMCGetFullCaptionTextL );

    TInt controlId = 1;
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    iCaptionedControl = dia->Line( controlId );

    iCaptionedControl->GetFullCaptionText();
    CleanupStack::PopAndDestroy( dia );
    iCaptionedControl = NULL;
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetDrawNoWhiteBackgroundLl
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCSetDrawNoWhiteBackgroundL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetDrawNoWhiteBackgroundL, "In TestMCSetDrawNoWhiteBackgroundL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetDrawNoWhiteBackgroundL );
    // Print to log file
    iLog->Log( KTestMCSetDrawNoWhiteBackgroundL );

    TInt controlId = 1;
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    iCaptionedControl = dia->Line( controlId );

    iCaptionedControl->SetDrawNoWhiteBackground( ETrue );
    CleanupStack::PopAndDestroy( dia );
    iCaptionedControl = NULL;
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetIconL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCSetIconL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetIconL, "In TestMCSetIconL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetIconL );
    // Print to log file
    iLog->Log( KTestMCSetIconL );
    TBool err = KErrNone;
    TInt controlId = 1;
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    iCaptionedControl = dia->Line( controlId );
    
    CFbsBitmap* bitmap = AknIconUtils::CreateIconL( AknIconUtils::AvkonIconFileName(),
                                                    EMbmAvkonQgn_graf_tab_21 ); 
    CleanupStack::PushL( bitmap );
    CFbsBitmap* bitmapMask = AknIconUtils::CreateIconL( AknIconUtils::AvkonIconFileName(),
                                                        EMbmAvkonQgn_graf_tab_21_mask );
    CleanupStack::PushL( bitmapMask );       
    TRAP( err, iCaptionedControl->SetIconL( bitmap, bitmapMask ) );
    CleanupStack::Pop( bitmapMask );  
    CleanupStack::Pop( bitmap );
    CleanupStack::PopAndDestroy( dia );
    iCaptionedControl = NULL;
     
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetIndicatorIconL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCSetIndicatorIconL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetIndicatorIconL, "In TestMCSetIndicatorIconL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetIndicatorIconL );
    // Print to log file
    iLog->Log( KTestMCSetIndicatorIconL );
    TBool err = KErrNone;
    TInt controlId = 1;
    TInt cIcon = 0;
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    iCaptionedControl = dia->Line( controlId );
    
    CFbsBitmap* bitmap = AknIconUtils::CreateIconL( AknIconUtils::AvkonIconFileName(),
                                                    EMbmAvkonQgn_graf_tab_21 ); 
    CleanupStack::PushL( bitmap );
    CFbsBitmap* bitmapMask = AknIconUtils::CreateIconL( AknIconUtils::AvkonIconFileName(),
                                                        EMbmAvkonQgn_graf_tab_21_mask );
    CleanupStack::PushL( bitmapMask );       
    TRAP( err, iCaptionedControl->SetIndicatorIconL( cIcon, bitmap, bitmapMask ) );
    CleanupStack::Pop( bitmapMask );  
    CleanupStack::Pop( bitmap );
    CleanupStack::PopAndDestroy( dia );
    iCaptionedControl = NULL;
     
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestMCSetPointerEventObserverL
// -----------------------------------------------------------------------------

TInt CTestSDKMiscControls::TestMCSetPointerEventObserverL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestMCSetPointerEventObserverL, "In TestMCSetPointerEventObserverL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestMCSetPointerEventObserverL );
    // Print to log file
    iLog->Log( KTestMCSetPointerEventObserverL );
 
    TInt controlId = 1;
    CTestSubCaptionedControl *observer = new ( ELeave ) CTestSubCaptionedControl();
    CleanupStack::PushL( observer );
    CTestCaptionedControl* dia = new ( ELeave ) CTestCaptionedControl();
    dia->PrepareLC( R_TESTMISCCONTROL_EIKLINE );
    iCaptionedControl = dia->Line( controlId );
    
    iCaptionedControl->SetPointerEventObserver( observer );
    
    CleanupStack::PopAndDestroy( dia );
    CleanupStack::PopAndDestroy( observer );
    iCaptionedControl = NULL;
     
    return KErrNone;

    }
