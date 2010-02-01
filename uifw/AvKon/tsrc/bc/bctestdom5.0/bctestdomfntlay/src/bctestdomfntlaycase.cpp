/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test case
 *
*/


#include <w32std.h>
#include <coecntrl.h>
#include <eikenv.h>

#include <aknfontid.h>
#include <aknfontprovider.h>
#include <aknfontprovidersuppliedmetrics.h>

#include "bctestdomfntlaycase.h"
#include "bctestdomfntlaycontainer.h"
#include "bctestdomfntlay.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomFntlayCase* CBCTestDomFntlayCase::NewL( 
    CBCTestDomFntlayContainer* aContainer )
    {
    CBCTestDomFntlayCase* self = new( ELeave ) CBCTestDomFntlayCase( 
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
CBCTestDomFntlayCase::CBCTestDomFntlayCase( 
    CBCTestDomFntlayContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomFntlayCase::~CBCTestDomFntlayCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomFntlayCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomFntlayCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomFntlayCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(1),
              LeftCBA, LeftCBA, LeftCBA,
              LeftCBA, LeftCBA, REP(Down,1), LeftCBA,
              LeftCBA, LeftCBA, REP(Down,2), LeftCBA,
              TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomFntlayCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomFntlayCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestDomCmdOutline01 || aCmd > EBCTestDomCmdOutline03 )
        {
        return;
        }
    // Call release before prepare to let container has time to draw the 
    // control created in PrepareCaseL.
     //TestFontL(aCmd);
    switch( aCmd )
        {
        case EBCTestDomCmdOutline01:
            TestFontIdL(); 
            break;
        case EBCTestDomCmdOutline02:
            TestFontProviderL();
            break;
        case EBCTestDomCmdOutline03:
            TestProviderSuppliedMetricsL();
            break;
        default:
            break;    
        }
    }

// ---------------------------------------------------------------------------
// CBCTestDomFntlayCase::TestFontIdL
// ---------------------------------------------------------------------------
// 
void CBCTestDomFntlayCase::TestFontIdL() //AknFontId.h 2
    {
    TBool isEncode = TAknFontId::IsEncodedFont( 1 );  
    _LIT( KTxtIsEncodedFont, "TAknFontId::IsEncodedFont" );
    AssertTrueL( ETrue, KTxtIsEncodedFont );
    
    TInt fontId = TAknFontId::TAknFontId::FontIdForStartupNormalFont();
    _LIT( KTxtStartup, "TAknFontId::TAknFontId::FontIdForStartupNormalFont" );
    AssertTrueL( ETrue, KTxtStartup );
      
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomFntlayCase::TestFontProviderL
// ---------------------------------------------------------------------------
// 
void CBCTestDomFntlayCase::TestFontProviderL() //AknFontProvider.h 7
    {
    CEikonEnv* eikEnv = ( CEikonEnv* )iContainer->GetEnv();
    AknFontProvider::InitializeSystemL( *eikEnv );
    _LIT( KTxtInitSystem, "AknFontProvider::InitializeSystemL" );
    AssertTrueL( ETrue, KTxtInitSystem );   
                    
    CWsScreenDevice* screenDevice = CCoeEnv::Static()->ScreenDevice();
        
    TInt fontId = 1;
    TAknFontSpecification metrics( fontId );
    TAknFontProviderSuppliedMetrics additionalMetrics;
    TInt providerIndex;
    CFbsFont* fbsFont = AknFontProvider::CreateFontFromMetrics(
        *screenDevice, fontId, metrics,
        additionalMetrics, providerIndex );
    CleanupStack::PushL( fbsFont );
    _LIT( KTxtCreateFont, "AknFontProvider::CreateFontFromMetrics" );
    AssertTrueL( ETrue, KTxtCreateFont );
    CleanupStack::Pop( fbsFont );
    screenDevice->ReleaseFont( fbsFont );
                
    TTypeface typeFace;
    CFbsFont* fbsFont2 = 
        AknFontProvider::CreateFontFromTypefaceAndMetrics(
        *screenDevice, typeFace,metrics, 
        additionalMetrics, providerIndex );
    CleanupStack::PushL( fbsFont2 );
    _LIT( KTxtCreateFontFromTyapeFace, 
           "AknFontProvider::CreateFontFromTypefaceAndMetrics" );
    AssertTrueL( ETrue, KTxtCreateFontFromTyapeFace );
    CleanupStack::Pop( fbsFont2 );
    screenDevice->ReleaseFont( fbsFont2 );
                
    TBool hasBase = AknFontProvider::HasBaselineCorrection( 1 );
    _LIT( KTxtHaseBase, "AknFontProvider::HasBaselineCorrection" );
    AssertTrueL( ETrue, KTxtHaseBase );
            
    TInt baseLine;
    TInt demon;
    TInt ret = AknFontProvider::BaselineDeltaForCharacter( 1,
        'a', baseLine, demon );
    _LIT( KTxtBaseLine,
          "AknFontProvider::BaselineDeltaForCharacter" );
    AssertTrueL( ETrue, KTxtBaseLine );
            
    TInt minBaseLine;
    TInt minDemon;
    _LIT( KTxtSame, "abc" );
    TInt numInit( 0 );
    ret = AknFontProvider::MinimumBaselineDeltaForDescriptor(
        1, KTxtSame, minBaseLine, minDemon, ETrue, numInit );
    _LIT( KTxtMiniBaseLine,
          "AknFontProvider::MinimumBaselineDeltaForDescriptor" );
    AssertTrueL( ETrue, KTxtMiniBaseLine );
            
    TFontSpec fontSpec;
    ret = AknFontProvider::FontProviderIndexFromFontSpec( fontSpec );           
    _LIT( KTxtFontSpec,
          "AknFontProvider::FontProviderIndexFromFontSpec" );
    AssertTrueL( ETrue, KTxtFontSpec );   
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomFntlayCase::TestProviderSuppliedMetricsL
// ---------------------------------------------------------------------------
// 
void CBCTestDomFntlayCase::TestProviderSuppliedMetricsL() 
    {
    //AknFontProviderSuppliedMetrics.h 6
    TAknFontProviderSuppliedMetrics fontMetiec;
    fontMetiec.SetExcessAscent( 1 );
    _LIT( KTxtSetExcessAscent,
        "TAknFontProviderSuppliedMetrics::SetExcessAscent" );
    AssertTrueL( ETrue, KTxtSetExcessAscent );

    TInt ascent = fontMetiec.ExcessAscent();
    _LIT( KTxtExcessAscent,
        "TAknFontProviderSuppliedMetrics::ExcessAscent" );
    AssertTrueL (ETrue, KTxtExcessAscent );
            
    fontMetiec.SetExcessDescent( 1 ); 
    _LIT( KTxtSetExcessDescent,
        "TAknFontProviderSuppliedMetrics::SetExcessDescent" );
    AssertTrueL( ETrue, KTxtSetExcessDescent );

    TInt descent = fontMetiec.ExcessDescent();
    _LIT( KTxtExcessDescent,
        "TAknFontProviderSuppliedMetrics::ExcessDescent" );
    AssertTrueL( ETrue, KTxtExcessDescent );

    fontMetiec.SetMaxDescentToTextPaneBottom( 1 );
    _LIT( KTxtSetMaxDescentToTextPaneBottom,
        "TAknFontProviderSuppliedMetrics::\
        SetMaxDescentToTextPaneBottom" );
    AssertTrueL( ETrue, KTxtSetMaxDescentToTextPaneBottom );

    TInt maxDescent = fontMetiec.MaxDescentToTextPaneBottom();
    _LIT( KTxtMaxDescentToTextPaneBottom,
        "TAknFontProviderSuppliedMetrics::\
        MaxDescentToTextPaneBottom" );
    AssertTrueL( ETrue ,KTxtMaxDescentToTextPaneBottom );    
    }
