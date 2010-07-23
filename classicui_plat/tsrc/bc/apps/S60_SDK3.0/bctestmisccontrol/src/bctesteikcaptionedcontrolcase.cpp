/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Implements test bc for eik captioned control.
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <bctestmisccontrol.rsg>
#include <bctestmisccontrol.mbg>
#include <aknscontrolcontext.h>     // MAknsControlContext  
#include <barsread.h>               // TResourceReader
#include <s32mem.h>                 // RBufWriteStream 
#include <eikcapc.h>                // CEikCaptionedControl
#include <eikcapca.h>               // CEikCapCArray
#include <fbs.h>                    // CFbsBitmap
#include <akniconutils.h>           // AknIconUtils
#include <akndef.h>                 // KEikDynamicLayoutVariantSwitch

#include "bctesteikcaptionedcontrolcase.h"
#include "bctestsubeikcaptionedcontrol.h"
#include "bctestsubaknform.h"
#include "bctestmisccontrolcontainer.h"
#include "bctestmisccontrol.hrh"
#include "autotestcommands.h"

//Constant for CEikCaptionedControl
_LIT( KForm, "Form created" );
_LIT( KRCapControl, "Eik captioned control created" );
_LIT( KSetDimmed, "Invoke CEikCaptionedControl's SetDimmed()" );
_LIT( KSetDividerAfter, 
    "Invoke CEikCaptionedControl's SetDividerAfter()" );
_LIT( KSetLatent, "Invoke CEikCaptionedControl's SetLatent()" );
_LIT( KSetDrawNoWhiteBackground, 
    "Invoke CEikCaptionedControl's SetDrawNoWhiteBackground()" );
_LIT( KSetOfferHotKeys, 
    "Invoke CEikCaptionedControl's SetOfferHotKeys()" );
_LIT( KSetLatentGroupLineFollows, 
    "Invoke CEikCaptionedControl's SetLatentGroupLineFollows()" );
_LIT( KSetSpaceSharingFlags, 
    "Invoke CEikCaptionedControl's SetSpaceSharingFlags()" );
_LIT( KSetTakesEnterKey, 
    "Invoke CEikCaptionedControl's SetTakesEnterKey()" );
_LIT( KSetUsesEars, 
    "Invoke CEikCaptionedControl's SetUsesEars()" );
_LIT( KOfferKeyEventL, 
    "Invoke CEikCaptionedControl's OfferKeyEventL()" );
_LIT( KOfferHotKeys, 
    "Invoke CEikCaptionedControl's OfferHotKeys()" );
_LIT( KHandlePointerEventL, 
    "Invoke CEikCaptionedControl's HandlePointerEventL()" );
_LIT( KCheckDimmedDisplayState, 
    "Invoke CEikCaptionedControl's CheckDimmedDisplayState()" );
_LIT( KDividerAfter, 
    "Invoke CEikCaptionedControl's DividerAfter()" );
_LIT( KSetIconL, "Invoke CEikCaptionedControl's SetIconL()" );
_LIT( KHandleControlEventL, 
    "Invoke CEikCaptionedControl's HandleControlEventL()" );
_LIT( KSetBitmapFromFileL, 
    "Invoke CEikCaptionedControl's SetBitmapFromFileL()" );
_LIT( KGetColorUseListL, 
        "Invoke CEikCaptionedControl's GetColorUseListL()" );
_LIT( KWriteInternalStateL, 
        "Invoke CEikCaptionedControl's WriteInternalStateL()" );
_LIT( KDraw, "Invoke CEikCaptionedControl's Draw()" );
_LIT( KGetFullCaptionText, 
    "Invoke CEikCaptionedControl's GetFullCaptionText()" );
_LIT( KHandleResourceChange, 
    "Invoke CEikCaptionedControl's HandleResourceChange()" );        
_LIT( KInputCapabilities, 
    "Invoke CEikCaptionedControl's InputCapabilities()" );
_LIT( KIsLatent, "Invoke CEikCaptionedControl's IsLatent()" );
_LIT( KLatentGroupLineFollows, 
    "Invoke CEikCaptionedControl's LatentGroupLineFollows()" );
_LIT( KMinimumSize, 
    "Invoke CEikCaptionedControl's MinimumSize()" );
_LIT( KSetCurrent, 
    "Invoke CEikCaptionedControl's SetCurrent()" );
_LIT( KSetExtraAscent, 
    "Invoke CEikCaptionedControl's SetExtraAscent()" );
_LIT( KTakesEnterKey, 
    "Invoke CEikCaptionedControl's TakesEnterKey()" );
_LIT( KToolTipText, 
    "Invoke CEikCaptionedControl's ToolTipText()" );
    
//Constant for CEikCapCArray
_LIT( KCEikCapCArray, "Create CEikCapCArray object" );
_LIT( KSetRect, "Invoke CEikCapCArray's SetRect()" );
_LIT( KAdjustAllIds, "Invoke CEikCapCArray's AdjustAllIds()" );
_LIT( KFindLineIndex, "Invoke CEikCapCArray's FindLineIndex()" );

//MBMFileName constant                       
_LIT( KMBMFileName, "\\resource\\apps\\bctestmisccontrol.mbm" );

const TInt KGranularity = 4;
const TInt KZero = 0;
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KFour = 4;
const TInt KTwoHundred = 200;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestEikCaptionedControlCase* CBCTestEikCaptionedControlCase::NewL(
    CBCTestMiscControlContainer* aContainer )
    {
    CBCTestEikCaptionedControlCase* self = 
        new( ELeave ) CBCTestEikCaptionedControlCase( aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestEikCaptionedControlCase::CBCTestEikCaptionedControlCase(
    CBCTestMiscControlContainer* aContainer ) : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestEikCaptionedControlCase::~CBCTestEikCaptionedControlCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestEikCaptionedControlCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestEikCaptionedControlCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestEikCaptionedControlCase::BuildScriptL()
    {
    const TInt scripts[] =
        {
        //outline1
        DELAY( KOne ),  // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        KeyOK,
        KeyOK,

        //outline2
        LeftCBA,
        KeyOK,
        Down,
        KeyOK,
        
        //outline3
        LeftCBA,
        KeyOK,
        REP( Down, KTwo ),
        KeyOK        
        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );    
    }

// ---------------------------------------------------------------------------
// CBCTestEikCaptionedControlCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestEikCaptionedControlCase::RunL( TInt aCmd )
    {
    if ( ( aCmd < EBCTestMiscControlCmdOutline01 ) 
        || ( aCmd > EBCTestMiscControlCmdOutline03 ) )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestMiscControlCmdOutline01:
            TestPublicFunctionsL();
            break;
        case EBCTestMiscControlCmdOutline02:
            TestProtectedFunctionsL();
            break;
        case EBCTestMiscControlCmdOutline03:
            TestFunctionsOfEikCapCArrayL();
            break;            
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestEikCaptionedControlCase::TestPublicFunctionsL
// ---------------------------------------------------------------------------
//
void CBCTestEikCaptionedControlCase::TestPublicFunctionsL()
    {
    // Construct CBCTestSubAknForm
    iForm = new( ELeave ) CBCTestSubAknForm();
    AssertNotNullL( iForm, KForm );       
    iForm->PrepareLC( R_BCTESTMISCCONTROL_TEXT_SLIDER_FIELD_DIALOG );
    CleanupStack::Pop();
    
    // Construct CEikCaptionedControl
    iCapControl = iForm->GetFirstLineOnFirstPageOrNull();
    AssertNotNullL( iCapControl, KRCapControl );
    
    // Invoke CEikCaptionedControl's CEikCaptionedControl()    
    iCapControl->SetDimmed( EFalse );
    AssertTrueL( ETrue, KSetDimmed ); 
    
    // Invoke CEikCaptionedControl's SetDividerAfter()    
    iCapControl->SetDividerAfter( ETrue );
    iCapControl->SetDividerAfter( EFalse );
    AssertTrueL( ETrue, KSetDividerAfter );
    
    // Invoke CEikCaptionedControl's SetLatent()    
    iCapControl->SetLatent( EFalse );
    iCapControl->SetLatent( ETrue );
    AssertTrueL( ETrue, KSetLatent );     
    
    // Invoke CEikCaptionedControl's SetDrawNoWhiteBackground()    
    iCapControl->SetDrawNoWhiteBackground( EFalse );
    iCapControl->SetDrawNoWhiteBackground( ETrue );
    AssertTrueL( ETrue, KSetDrawNoWhiteBackground ); 
    
    // Invoke CEikCaptionedControl's SetOfferHotKeys()    
    iCapControl->SetOfferHotKeys( ETrue );
    iCapControl->SetOfferHotKeys( EFalse );
    AssertTrueL( ETrue, KSetOfferHotKeys ); 
    
    // Invoke CEikCaptionedControl's SetLatentGroupLineFollows()    
    iCapControl->SetLatentGroupLineFollows( ETrue );
    iCapControl->SetLatentGroupLineFollows( EFalse );
    AssertTrueL( ETrue, KSetLatentGroupLineFollows ); 

    // Invoke CEikCaptionedControl's SetSpaceSharingFlags()    
    iCapControl->SetSpaceSharingFlags( 
        CEikCaptionedControl::EIfTooSmallCtlGetsWidthFirst );
    AssertTrueL( ETrue, KSetSpaceSharingFlags );
    
    // Invoke CEikCaptionedControl's SetTakesEnterKey()    
    iCapControl->SetTakesEnterKey( ETrue );
    iCapControl->SetTakesEnterKey( EFalse );
    AssertTrueL( ETrue, KSetTakesEnterKey ); 
    
    // Invoke CEikCaptionedControl's SetUsesEars()    
    iCapControl->SetUsesEars();
    AssertTrueL( ETrue, KSetUsesEars ); 

    // Invoke CEikCaptionedControl's OfferKeyEventL()    
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyCBA1;
    iCapControl->OfferKeyEventL( keyEvent, EEventKey );
    AssertTrueL( ETrue, KOfferKeyEventL ); 

    // Invoke CEikCaptionedControl's OfferHotKeys()    
    iCapControl->OfferHotKeys();
    AssertTrueL( ETrue, KOfferHotKeys ); 
    
    // Invoke CEikCaptionedControl's HandlePointerEventL()  
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;
    iCapControl->HandlePointerEventL( pointEvent );
    pointEvent.iType = TPointerEvent::EButton1Up;  
    iCapControl->HandlePointerEventL( pointEvent );    
    AssertTrueL( ETrue, KHandlePointerEventL );

    // Invoke CEikCaptionedControl's CheckDimmedDisplayState()    
    iCapControl->CheckDimmedDisplayState();
    AssertTrueL( ETrue, KCheckDimmedDisplayState );

    // Invoke CEikCaptionedControl's DividerAfter()    
    iCapControl->DividerAfter();
    AssertTrueL( ETrue, KDividerAfter );

    // Invoke CEikCaptionedControl's SetBitmapFromFileL()    
    iCapControl->SetBitmapFromFileL( KMBMFileName, 
        EMbmBctestmisccontrol30x40, EMbmBctestmisccontrol30x40m );
    AssertTrueL( ETrue, KSetBitmapFromFileL );
    
    // Invoke CEikCaptionedControl's SetIconL()    
    CFbsBitmap* bitmap = AknIconUtils::CreateIconL( 
        KMBMFileName, EMbmBctestmisccontrol30x40 ); //not own
    CleanupStack::PushL( bitmap );
    CFbsBitmap* bitmapMask = AknIconUtils::CreateIconL( 
        KMBMFileName, EMbmBctestmisccontrol30x40m );  //not own
    CleanupStack::PushL( bitmapMask );       
    iCapControl->SetIconL( bitmap, bitmapMask );
    AssertTrueL( ETrue, KSetIconL );
    CleanupStack::Pop( bitmapMask );   
    CleanupStack::Pop( bitmap );

    // Invoke CEikCaptionedControl's HandleControlEventL()    
    iCapControl->HandleControlEventL( iForm, 
        MCoeControlObserver::EEventRequestExit );
    AssertTrueL( ETrue, KHandleControlEventL );

    // Invoke CEikCaptionedControl's GetColorUseListL()
    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
        CArrayFixFlat<TCoeColorUse>( KGranularity );
    CleanupStack::PushL( colorUseList );
    iCapControl->GetColorUseListL( *colorUseList );
    AssertTrueL( ( colorUseList->Count() > KZero ), KGetColorUseListL );
    colorUseList->Reset();
    CleanupStack::PopAndDestroy( colorUseList );

    // Invoke CEikCaptionedControl's GetFullCaptionText()    
    iCapControl->GetFullCaptionText();
    AssertTrueL( ETrue, KGetFullCaptionText );
    
    // Invoke CEikCaptionedControl's HandleResourceChange()    
    iCapControl->HandleResourceChange( KAknsMessageSkinChange );
    iCapControl->HandleResourceChange( KEikDynamicLayoutVariantSwitch );    
    AssertTrueL( ETrue, KHandleResourceChange );

    // Invoke CEikCaptionedControl's InputCapabilities()    
    iCapControl->InputCapabilities();
    AssertTrueL( ETrue, KInputCapabilities );

    // Invoke CEikCaptionedControl's IsLatent()    
    iCapControl->IsLatent();
    AssertTrueL( ETrue, KIsLatent );  
    
    // Invoke CEikCaptionedControl's LatentGroupLineFollows()    
    iCapControl->LatentGroupLineFollows();
    AssertTrueL( ETrue, KLatentGroupLineFollows );  
    
    // Invoke CEikCaptionedControl's MinimumSize()    
    iCapControl->MinimumSize();
    AssertTrueL( ETrue, KMinimumSize );
    
    // Invoke CEikCaptionedControl's SetCurrent()    
    iCapControl->SetCurrent( ETrue );
    iCapControl->SetCurrent( EFalse );
    AssertTrueL( ETrue, KSetCurrent );
    
    // Invoke CEikCaptionedControl's SetExtraAscent()    
    iCapControl->SetExtraAscent();
    AssertTrueL( ETrue, KSetExtraAscent );
    
    // Invoke CEikCaptionedControl's TakesEnterKey()    
    iCapControl->TakesEnterKey();
    AssertTrueL( ETrue, KTakesEnterKey );
    
    // Invoke CEikCaptionedControl's ToolTipText()    
    iCapControl->ToolTipText();
    AssertTrueL( ETrue, KToolTipText ); 
            
    delete iForm;
    iForm = NULL;   
    }
    
// ---------------------------------------------------------------------------
// CBCTestEikCaptionedControlCase::TestProtectedFunctionsL
// ---------------------------------------------------------------------------
//
void CBCTestEikCaptionedControlCase::TestProtectedFunctionsL()
    {
    // Construct CBCTestSubAknForm
    iForm = new( ELeave ) CBCTestSubAknForm();
    iForm->PrepareLC( R_BCTESTMISCCONTROL_TEXT_SLIDER_FIELD_DIALOG );
    CleanupStack::Pop();
    
    // Construct CSubEikCaptionedControl
    iSubCapControl = static_cast<CBCTestSubEikCaptionedControl*> 
                         ( iForm->GetFirstLineOnFirstPageOrNull() );
    
    // Invoke CEikCaptionedControl's MopSupplyObject()    
    TTypeUid typeId( MAknsControlContext::ETypeId );
    iSubCapControl->MopSupplyObject( typeId );
    _LIT( KMopSupplyObject, 
        "Invoke CEikCaptionedControl's MopSupplyObject()" );
    AssertTrueL( ETrue, KMopSupplyObject );
    
    iSubCapControl->DrawNow();
    AssertTrueL( ETrue, KDraw ); 
    
    // Invoke CEikCaptionedControl's WriteInternalStateL()
    CBufFlat* buf = CBufFlat::NewL( KTwoHundred );
    RBufWriteStream stream;
    stream.Open( *buf );
    iSubCapControl->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KWriteInternalStateL ); 
    stream.Close();
    delete buf;
    
    delete iForm;
    iForm = NULL; 
    }
    
// ---------------------------------------------------------------------------
// CBCTestEikCaptionedControlCase::TestFunctionsOfEikCapCArrayL
// ---------------------------------------------------------------------------
//
void CBCTestEikCaptionedControlCase::TestFunctionsOfEikCapCArrayL()
    {
    CEikCapCArray* eikCapCArray = new( ELeave ) CEikCapCArray( KGranularity );
    CleanupStack::PushL( eikCapCArray );
    AssertNotNullL( eikCapCArray, KCEikCapCArray );
    
    // Invoke CEikCapCArray's SetRect()
    TRect rect;
    eikCapCArray->SetRect( rect );
    AssertTrueL( ETrue, KSetRect );  
    
    // Invoke CEikCapCArray's AdjustAllIds()
    eikCapCArray->AdjustAllIds( KFour );
    AssertTrueL( ETrue, KAdjustAllIds ); 
    
    // Invoke CEikCapCArray's MinimumSize()
    eikCapCArray->MinimumSize();
    _LIT( KECCMinimumSize, 
        "Invoke CEikCapCArray's MinimumSize()" );    
    AssertTrueL( ETrue, KECCMinimumSize ); 
    
    // Invoke CEikCapCArray's ResetMinimumSizes()
    eikCapCArray->ResetMinimumSizes();
    _LIT( KECCResetMinimumSizes, 
        "Invoke CEikCapCArray's ResetMinimumSizes()" );    
    AssertTrueL( ETrue, KECCResetMinimumSizes );     
    
    // Invoke CEikCapCArray's FindLineIndex()
    CCoeControl* coeControl = new( ELeave ) CCoeControl();
    CleanupStack::PushL( coeControl );
    eikCapCArray->FindLineIndex( coeControl );
    AssertTrueL( ETrue, KFindLineIndex ); 
    CleanupStack::PopAndDestroy( coeControl );   
    
    CleanupStack::PopAndDestroy( eikCapCArray );    
        
    }

    





    
   

    
