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
#include <gdi.h>
#include <eikenv.h>
#include <avkon.hrh>

// test header of Api
#include <akninputlanguageinfo.h>
#include <akninfrm.h>
#include <aknnotewrappers.h>
#include <stringloader.h>
#include <akniconutils.h>
#include <avkon.mbg>
#include <bctestfontinput_aif.mbg>
#include <barsread.h>
#include <bctestfontinput.rsg>

#include "bctestframeinfocase.h"
#include "bctestfontinputcontainer.h"
#include "bctestfontinput.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestFrameInfoCase* CBCTestFrameInfoCase::NewL(
    CBCTestFontInputContainer* aContainer )
    {

    CBCTestFrameInfoCase* self = new( ELeave ) CBCTestFrameInfoCase(
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------

CBCTestFrameInfoCase::CBCTestFrameInfoCase(
    CBCTestFontInputContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestFrameInfoCase::~CBCTestFrameInfoCase()
    {

    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestFrameInfoCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestFrameInfoCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestFrameInfoCase::BuildScriptL()
    {    
    AddTestL( DELAY( 2 ),LeftCBA,Down,Down,KeyOK,LeftCBA,Down,Down,Down,KeyOK,TEND );
    }

// ---------------------------------------------------------------------------
// CBCTestFrameInfoCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestFrameInfoCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestInputFrame || aCmd > EBCTestInputInfo )
        {
        return;
        }    
    switch ( aCmd )
        {
        case EBCTestInputInfo:
             TestInputInfoL();
            break;
        case EBCTestInputFrame:
            TestInputFrameL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestFrameInfoCase::TestInputInfoL
// ---------------------------------------------------------------------------
//
void CBCTestFrameInfoCase::TestInputInfoL()
    {
      
    CAknInputLanguageInfo* inFact =
        AknInputLanguageInfoFactory::CreateInputLanguageInfoL();
    CleanupStack::PushL( inFact );
    
    CAknInputLanguageList* inputList = new ( ELeave )
                                        CAknInputLanguageList( TInt( 1 ) );
    CleanupStack::PushL( inputList );
    _LIT( langList," Test CAknInputLanguageList() " );
    AssertTrueL( ETrue,langList);
    
    CArrayFixFlat<TInt>* codeList = new( ELeave ) CArrayFixFlat<TInt>( 1 );
    CleanupStack::PushL( codeList );    
    codeList->AppendL( ELangEnglish );
    
    TAknInputLanguageCapabilities capFilter;
    capFilter.AssignCapability( 
        TAknInputLanguageCapabilities::EMultitap, ETrue );
    
    inFact->AppendLanguagesL( inputList, codeList, capFilter );
     
    TInt count = inputList->MdcaCount();
    _LIT( mdCount," Test MdcaCount() " );
    AssertTrueL( ETrue, mdCount );
    
    if (count > 0)
    		{
    		TPtrC ptr = inputList->MdcaPoint( 0 );
    		_LIT( KMdcaPoint, "CAknInputLanguageList::MdcaPoint" );
    		AssertTrueL( ETrue, KMdcaPoint );
    
    		CAknInputLanguageItem* item = (*inputList)[0];
    		
    		TLanguage code = item->LanguageCode();
    		_LIT( KLanItem1, "CAknInputLanguageItem::LanguageCode" );
    		AssertIntL( ELangEnglish, code, KLanItem1 );
    
    		TPtrC name = item->LanguageName();
    		_LIT( KLanItem2, "CAknInputLanguageItem::LanguageName" );
    		AssertTrueL( ETrue, KLanItem2 );

   		  TAknInputLanguageCapabilities cap = item->Capabilities();
   		  _LIT( KLanItem3, "CAknInputLanguageItem::Capabilities" );
   		  AssertTrueL( ETrue, KLanItem3 );
			  }
    CleanupStack::PopAndDestroy( codeList );
    CleanupStack::PopAndDestroy( inputList );
    CleanupStack::PopAndDestroy( inFact );

    TAknInputLanguageCapabilities inputCap;
    TAknInputLanguageCapabilities desCap;
    _LIT( langCap, " Test TAknInputLanguageCapabilities() " );
    AssertTrueL( ETrue, langCap );
     
    inputCap.AssignCapability( TInt ( 1 ),EFalse );
    _LIT( assCap, " Test AssignCapability() " );
    AssertTrueL( ETrue, assCap );

    inputCap.FilteredCapabilities( desCap );
    _LIT( filterCap, " Test FilteredCapabilities()" );
    AssertTrueL( ETrue, filterCap );

    inputCap.HasAnySupport();
    _LIT( hasSup, " Test HasAnySupport() " );
    AssertTrueL( ETrue, hasSup );

    inputCap.HasCapability( TInt ( 1 ) );
    _LIT( hasCap, " Test HasCapability() " );
    AssertTrueL( ETrue, hasCap );

    inputCap.SetAllCapabilities();
    _LIT( stCap, " Test SetAllCapabilities() " );
    AssertTrueL( ETrue, stCap );

    }

// ---------------------------------------------------------------------------
// CBCTestFrameInfoCase::TestInputFrameL
// ---------------------------------------------------------------------------
//
void CBCTestFrameInfoCase::TestInputFrameL()
    {
    CEikEdwin* edwin = new( ELeave ) CEikEdwin();
    CleanupStack::PushL( edwin );
    edwin->ConstructL( 0, 30, 100, 1 );
    
    CFbsBitmap* bmp = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bmp );
    bmp->Load( AknIconUtils::AvkonIconFileName(), 
        EMbmAvkonQgn_stat_chi_pinyin );
    
    CGulIcon* icon = CGulIcon::NewL( bmp );
    CleanupStack::PushL( icon );

    CAknInputFrame* inputFrame = CAknInputFrame::NewL( edwin,
        EFalse, icon );
    CleanupStack::PushL( inputFrame );  
    CleanupStack::PopAndDestroy( inputFrame );
    CleanupStack::Pop( icon );
    CleanupStack::Pop( bmp );
    
    inputFrame = CAknInputFrame::NewL( edwin, EFalse, 
        AknIconUtils::AvkonIconFileName(), 
        EMbmAvkonQgn_stat_chi_pinyin, EMbmAvkonQgn_stat_chi_pinyin_mask );
    CleanupStack::PushL( inputFrame );
    _LIT( KInputFrame2, "CAknInputFrame::NewL with 4 parameters" );
    AssertNotNullL( inputFrame, KInputFrame2 );
    
    inputFrame->Field();
    _LIT( fld," Test Field() " );
    AssertTrueL( ETrue,fld );

    inputFrame->HandleControlEventL( edwin, 
        MCoeControlObserver::EEventStateChanged);
    _LIT( hdCtrl," Test HandleControlEventL() " );
    AssertTrueL( ETrue,hdCtrl);

    inputFrame->MinimumSize();
    _LIT( minSize," Test MinimumSize() " );
    AssertTrueL( ETrue,minSize );

    TKeyEvent kEvent;
    kEvent.iCode = '0';
    inputFrame->OfferKeyEventL( kEvent,EEventKeyUp );
    _LIT( ofKeyEvnt," Test OfferKeyEventL() ");
    AssertTrueL( ETrue,ofKeyEvnt );

    inputFrame->SetLineState( ETrue );
    _LIT( stLnState," Test SetLineState() " );
    AssertTrueL( ETrue,stLnState );

    inputFrame->SetInputContext( NULL );
    _LIT( stInputCn," Test SetInputContext() " );
    AssertTrueL( ETrue,stInputCn );
    
    _LIT( KInfoText, "Test CAknInputFrame" );
    inputFrame->SetInfoTextL( KInfoText );
    _LIT( stInfoTxt," Test SetInfoTextL() " );
    AssertTrueL( ETrue, stInfoTxt );
    
    CleanupStack::PopAndDestroy( inputFrame );
    CleanupStack::PopAndDestroy( edwin );
    }
