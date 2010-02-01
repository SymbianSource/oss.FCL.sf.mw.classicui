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
* Description:         test case
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <aknslider.h>
#include <barsread.h>
#include <bctestsliderandicons.rsg>
#include <eikenv.h>
#include <gulicon.h>
#include <akniconutils.h>


#include "bctestforslider.h"
#include "bctestsliderandiconscontainer.h"
#include "bctestsliderandicons.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestForSlider* CBCTestForSlider::NewL( 
    CBCTestSliderAndIconsContainer* aContainer )
    {
    CBCTestForSlider* self = new( ELeave ) CBCTestForSlider( 
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
CBCTestForSlider::CBCTestForSlider( 
    CBCTestSliderAndIconsContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestForSlider::~CBCTestForSlider()
    {      
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestForSlider::ConstructL()
    {    
    BuildScriptL();
    iEnv = CEikonEnv::Static();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestForSlider::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestForSlider::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( LeftCBA, KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestForSlider::RunL
// ---------------------------------------------------------------------------
//
void CBCTestForSlider::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdEmptyOutline || aCmd > EBCTestCmdMaxOutline )
        {
        return;
        }    
    switch ( aCmd )  
        {
        case EBCTestSlider:
            TestSliderL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestForSlider::TestSlider
// ---------------------------------------------------------------------------
//    
void CBCTestForSlider::TestSliderL()
    {
    CAknSlider* slider1 = new( ELeave ) CAknSlider();
    CleanupStack::PushL( slider1 );
    _LIT( KCAknSlider, "CAknSlider test" );
    AssertTrueL( ETrue, KCAknSlider );
    
    TResourceReader reader1;
    iEnv->CreateResourceReaderLC( reader1, R_BCTESTSLIDERANDICONS_SLIDER );
    slider1->ConstructFromResourceL( reader1 ); 
    _LIT( KConstructFromResourceL, "ConstructFromResourceL test" );
    AssertTrueL( ETrue, KConstructFromResourceL );
    CleanupStack::PopAndDestroy(); //reader
    
    TInt value = slider1->Value();
    _LIT( KValue, "Value test" );
    AssertTrueL( ETrue, KValue );
    
    slider1->SetValueL( value );
    _LIT( KSetValueL, "SetValueL test" );
    AssertTrueL( ETrue, KSetValueL );
    
    CleanupStack::PopAndDestroy( slider1 );
    slider1 = NULL;
    
    CAknSlider* slider = new( ELeave ) CAknSlider();
    CleanupStack::PushL( slider );
    
    TResourceReader reader2;
    iEnv->CreateResourceReaderLC( reader2, R_BCTESTSLIDERANDICONS_SLIDER );
    slider->ConstructFromResourceL( iContainer, value, reader2 );
    _LIT( KConstructFromResourceL2, 
        "ConstructFromResourceL For Control test" );
    AssertTrueL( ETrue, KConstructFromResourceL2 );
    CleanupStack::PopAndDestroy(); //reader
     
    TInt minimumValue = 0;
    TInt maximumValue =100;
    slider->SetRange( minimumValue, maximumValue );
    _LIT( KSetRange, "SetRange test" );
    AssertTrueL( ETrue, KSetRange );
    
    TInt stepSize = 2;
    slider->SetStepSize( stepSize );
    _LIT( KSetStepSize, "SetStepSizetest" );
    AssertTrueL( ETrue, KSetStepSize );
    
    _LIT( KText, "xxxxxxxxx" );
    slider->SetMinimumTextL( KText );
    _LIT( KSetMinimumTextL, "SetMinimumTextL test" );
    AssertTrueL( ETrue, KSetMinimumTextL );
    
    slider->SetMaximumTextL( KText );
    _LIT( KSetMaximumTextL, "SetMaximumTextL test" );
    AssertTrueL( ETrue, KSetMaximumTextL );
    
    TInt decimalPlaces = 0;
    slider->SetDecimalPlaces( decimalPlaces );
    _LIT( KSetDecimalPlaces, "SetDecimalPlaces test" );
    AssertTrueL( ETrue, KSetDecimalPlaces );
    
    decimalPlaces = slider->DecimalPlaces();
    _LIT( KDecimalPlaces, "DecimalPlaces test" );
    AssertTrueL( ETrue, KDecimalPlaces );
    
    CFbsBitmap* bitmap = slider->CreateBitmapL( 
        value, R_BCTESTSLIDERANDICONS_SLIDER );
    _LIT( KCreateBitmapL, "CreateBitmapL test" );
    AssertTrueL( ETrue, KCreateBitmapL );
    delete bitmap;
    
    CFbsBitmap* bitmap2 = slider->CreateBitmapL( 
        value, minimumValue, maximumValue );
    _LIT( KCreateBitmapL2, "CreateBitmapL with Min and Max test" );
    AssertTrueL( ETrue, KCreateBitmapL2 );
    delete bitmap2;
    
    CGulIcon* gulIcon = slider->CreateSetStyleListBoxIconL( 
        value, R_BCTESTSLIDERANDICONS_SLIDER );
    _LIT( KCreateSetStyleListBoxIconL, "CreateSetStyleListBoxIconL test" );
    AssertTrueL( ETrue, KCreateSetStyleListBoxIconL );
    delete gulIcon;
    
    CGulIcon* gulIcon2 = slider->CreateSetStyleListBoxIconL( 
        value, minimumValue, maximumValue );
    _LIT( KCreateSetStyleListBoxIconL2, 
        "CreateSetStyleListBoxIconL with maxmumValue test" );
    AssertTrueL( ETrue, KCreateSetStyleListBoxIconL2 );
    delete gulIcon2;
    
    slider->HandleResourceChange( R_BCTESTSLIDERANDICONS_SLIDER ); 
    _LIT( KHandleResourceChange, "HandleResourceChange test" );
    AssertTrueL( ETrue, KHandleResourceChange );
    
    TInt numberOfLines = slider->NumberOfLines();
    _LIT( KNumberOfLines, "NumberOfLines test" );
    AssertTrueL( ETrue, KNumberOfLines );
    
    HBufC* bufC = slider->CreateValueTextInHBufCL( 
        value, R_BCTESTSLIDERANDICONS_SLIDER );
     _LIT( KCreateValueTextInHBufCL, "CreateValueTextInHBufCL test" );
    AssertTrueL( ETrue, KCreateValueTextInHBufCL );
    delete bufC;
   
    TPointerEvent pointerEvent = { TPointerEvent::EButton1Up,
         EModifierAutorepeatable, TPoint( 20,20 ), TPoint( 0,0 ) };
    slider->HandlePointerEventL( pointerEvent );
    _LIT( KHandlePointerEventL, "HandlePointerEventL test" );
    AssertTrueL( ETrue, KHandlePointerEventL );
   
#ifdef	__S60_32__


		TUint slTickInterval = slider->TickInterval();
    _LIT( KTickInterval, "TickInterval test" );
    AssertTrueL( ETrue, KTickInterval );

		slider->SetTickInterval(slTickInterval+1);
		slider->SetTickInterval(slTickInterval);
    _LIT( KSetTickInterval, "SetTickInterval test" );
    AssertTrueL( ETrue, KSetTickInterval );


		TBool slTicksEnabled = slider->TicksEnabled();
    _LIT( KTicksEnabled, "TicksEnabled test" );
    AssertTrueL( ETrue, KTicksEnabled );

		slider->SetTicksEnabled(!slTicksEnabled);
		slider->SetTicksEnabled(slTickInterval);
    _LIT( KSetTicksEnabled, "SetTicksEnabled test" );
    AssertTrueL( ETrue, KSetTicksEnabled );


		TUint32 slPositionIndicators = slider->PositionIndicators();
    _LIT( KPositionIndicators, "PositionIndicators test" );
    AssertTrueL( ETrue, KPositionIndicators );

		slider->SetPositionIndicators(slPositionIndicators+1);
		slider->SetPositionIndicators(slPositionIndicators);
    _LIT( KSetPositionIndicators, "SetPositionIndicators test" );
    AssertTrueL( ETrue, KSetPositionIndicators );



		TBool slUsesDefaultGraphics = slider->UsesDefaultGraphics(0);
    _LIT( KUsesDefaultGraphics, "UsesDefaultGraphics test" );
    AssertTrueL( ETrue, KUsesDefaultGraphics );
    
    
		slider->UseDefaultGraphics(0);
    _LIT( KUseDefaultGraphics, "UseDefaultGraphics test" );
    AssertTrueL( ETrue, KUseDefaultGraphics );

#endif /* __S60_32__ */



  

    CleanupStack::PopAndDestroy( slider );
    _LIT( KDesCAknSlider, "~CAknSlider test" );
    AssertTrueL( ETrue, KDesCAknSlider );
    slider = NULL;
    }
    
