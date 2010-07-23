/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <eikenv.h>
#include <barsread.h>
#include <aknuniteditor.h>

#include <bctestuniteditor.rsg>

#include "bctestuniteditorcase.h"
#include "bctestuniteditorcontainer.h"
#include "bctestuniteditor.hrh"

// ======== ASSERTION COMMENTS ========

_LIT ( KNewL, "NewL" );
_LIT ( KNewLC, "NewLC" );
_LIT ( KConstructL, "ConstructL" );
_LIT ( KConstructFromResourceL, "ConstructFromResourceL" );
_LIT ( KSetValue, "SetValue" );
_LIT ( KValue, "Value" );
_LIT ( KSupportsUnit, "SupportsUnit" );
_LIT ( KSetUnitLconstTDesC, "SetUnitL( const TDesC& )" );
_LIT ( KSetUnitLTInt, "SetUnitL( TInt )" );
_LIT ( KGetUnit, "GetUnit" );
_LIT ( KUnit, "Unit" );
_LIT ( KSetMaxFractionalDigits, "SetMaxFractionalDigits" );
_LIT ( KMaxFractionalDigits, "MaxFractionalDigits" );
_LIT ( KSetMinimumAndMaximum, "SetMinimumAndMaximum" );
_LIT ( KGetMinimumAndMaximum, "GetMinimumAndMaximum" );
_LIT ( KSetFlags, "SetFlags" );
_LIT ( KFlags, "Flags" );
_LIT ( KPrepareForFocusLossL, "PrepareForFocusLossL" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestUnitEditorCase* CBCTestUnitEditorCase::NewL( 
    CBCTestUnitEditorContainer* aContainer )
    {
    CBCTestUnitEditorCase* self = new( ELeave ) CBCTestUnitEditorCase( 
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestUnitEditorCase::CBCTestUnitEditorCase( 
    CBCTestUnitEditorContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestUnitEditorCase::~CBCTestUnitEditorCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestUnitEditorCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestUnitEditorCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestUnitEditorCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(1), LeftCBA, KeyOK, TEND );
    }
    
// ---------------------------------------------------------------------------
// CBCTestUnitEditorCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestUnitEditorCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline1 )
        {
        return;
        }
        
    // Call release before prepare to let container has time to draw the 
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    
    switch ( aCmd )  
        {
        case EBCTestCmdOutline1:
            TestUnitEditorL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestUnitEditorCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestUnitEditorCase::PrepareCaseL( TInt aCmd )
    {        
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            iControl = new ( ELeave ) CCoeControl;            
            iControl->SetContainerWindowL( *iContainer );
            iControl->MakeVisible( ETrue );
            break;
        default:
            break;
        }
    // Pass the owner of iControl to iContainer.
    iContainer->SetControl( iControl );
    }

// ---------------------------------------------------------------------------
// CBCTestUnitEditorCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestUnitEditorCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestUnitEditorCase::TestUnitEditorL
// ---------------------------------------------------------------------------
//    
void CBCTestUnitEditorCase::TestUnitEditorL()
    {
    TReal tmpValue = 2.5;
    TReal tmpMax = 5.0;
    TReal tmpMin = -5.0;
    TInt tmpUnit = EAknUnitEditorMeter;
    TInt tmpMaxFractionalDigits = 4;
    TInt tmpFlags = 0;
    _LIT ( KTmpUnit, "C/kg" );
    TBuf<16> tmpUnitBuf;
    
    CAknUnitEditor* unitEditor = NULL;
    
    unitEditor = CAknUnitEditor::NewL();
    CleanupStack::PushL( unitEditor );
    AssertNotNullL( unitEditor, KNewL );
    
    unitEditor->ConstructL( 
        tmpMin, tmpMax, tmpValue, tmpMaxFractionalDigits, tmpUnit, tmpFlags );
    AssertTrueL( ETrue, KConstructL );
    CleanupStack::PopAndDestroy(); // unitEditor
    unitEditor = NULL;
    
    unitEditor = CAknUnitEditor::NewLC();
    AssertNotNullL( unitEditor, KNewLC );
    
    TResourceReader resourceReader;
    CEikonEnv::Static()->CreateResourceReaderLC( 
        resourceReader, R_BCTESTUNITEDITOR );
    unitEditor->ConstructFromResourceL( resourceReader );
    AssertTrueL( ETrue, KConstructFromResourceL );
    
    CleanupStack::PopAndDestroy(); // resourceReader
    
    unitEditor->SetContainerWindowL( *iContainer );
        
    unitEditor->SetValue( tmpValue );
    AssertTrueL( ETrue, KSetValue );
    
    unitEditor->Value();
    AssertTrueL( ETrue, KValue );
    
    unitEditor->SupportsUnit( tmpUnit );
    AssertTrueL( ETrue, KSupportsUnit );
    
    unitEditor->SetUnitL( KTmpUnit );
    AssertTrueL( ETrue, KSetUnitLconstTDesC );
    
    unitEditor->SetUnitL( tmpUnit );
    AssertTrueL( ETrue, KSetUnitLTInt );
    
    unitEditor->GetUnit( tmpUnitBuf );
    AssertTrueL( ETrue, KGetUnit );
    
    unitEditor->Unit();
    AssertTrueL( ETrue, KUnit );
    
    unitEditor->SetMaxFractionalDigits( tmpMaxFractionalDigits );
    AssertTrueL( ETrue, KSetMaxFractionalDigits );
    
    unitEditor->MaxFractionalDigits();
    AssertTrueL( ETrue, KMaxFractionalDigits );
    
    unitEditor->SetMinimumAndMaximum( tmpMin, tmpMax );
    AssertTrueL( ETrue, KSetMinimumAndMaximum );
    
    unitEditor->GetMinimumAndMaximum( tmpMin, tmpMax );
    AssertTrueL( ETrue, KGetMinimumAndMaximum );
    
    unitEditor->SetFlags( tmpFlags );
    AssertTrueL( ETrue, KSetFlags );
    
    unitEditor->Flags();
    AssertTrueL( ETrue, KFlags );
    
    // PrepareForFocusLossL might leave due to a state in
    // the editor. This is not relevant for BC testing, hence trap.
    TRAPD ( ignore, unitEditor->PrepareForFocusLossL(); )
    AssertTrueL( ETrue, KPrepareForFocusLossL );

    CleanupStack::PopAndDestroy(); // unitEditor
    unitEditor = NULL;
    }
    
