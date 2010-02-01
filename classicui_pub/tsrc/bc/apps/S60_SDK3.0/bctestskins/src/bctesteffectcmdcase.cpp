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
#include <eikenv.h>
#include <aknsitemdata.h> 

#include "bctesteffectcmdcase.h"
#include "bctestskinscontainer.h"
#include "bctestskins.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestEffectCmdCase* CBCTestEffectCmdCase::NewL( 
    CBCTestSkinsContainer* aContainer )
    {
    CBCTestEffectCmdCase* self = new( ELeave ) CBCTestEffectCmdCase( 
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
CBCTestEffectCmdCase::CBCTestEffectCmdCase( 
    CBCTestSkinsContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestEffectCmdCase::~CBCTestEffectCmdCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestEffectCmdCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestEffectCmdCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestEffectCmdCase::BuildScriptL()
    { 
   const TInt scripts[] =
        {
        DELAY(1),        // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        REP(Down, 4),
        LeftCBA
        };
    AddTestScriptL(scripts, sizeof(scripts)/sizeof(TInt));
    }
    
// ---------------------------------------------------------------------------
// CBCTestEffectCmdCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestEffectCmdCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline5 || aCmd > EBCTestCmdOutline5 )
        {
        return;
        }

    switch ( aCmd )  
        {
        case EBCTestCmdOutline5:
            TestFunctionL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestEffectCmdCase::TestFunctionL
// ---------------------------------------------------------------------------
//   
void CBCTestEffectCmdCase::TestFunctionL()
    {
    // Test CAknsEffectCommand APIs
    CAknsEffectCommand* eftCmd = CAknsEffectCommand::NewL();
    CleanupStack::PushL( eftCmd );
    _LIT( KNew, "CAknsEffectCommand::NewL" );
    AssertNotNullL( eftCmd, KNew );
	
	eftCmd->SetEffectUid( TUid::Uid(0x101F84AF) );
    _LIT( KSetEffectUid, "CAknsEffectCommand::SetEffectUid" );
    AssertNotNullL( eftCmd, KSetEffectUid );
	
	TUid eftUid = eftCmd->EffectUid(); 
    _LIT( KEffectUid, "CAknsEffectCommand::EffectUid" );
    AssertTrueL( (eftUid==TUid::Uid(0x101F84AF)), KEffectUid );
    
  	TAknsRlRenderOpParam para;
  	para.iInputLayerAStatus = KAknsRlLayerNone;
  	para.iInputLayerAIndex = KAknsRlLayerRGBA;
  	para.iInputLayerBStatus = KAknsRlLayerNone;
  	para.iInputLayerBIndex = KAknsRlLayerAlphaOnly;
  	para.iOutputLayerStatus = KAknsRlLayerNone;
  	para.iOutputLayerIndex = KAknsRlLayerRGBA;
	eftCmd->SetLayerConf( para ); 
    _LIT( KParam, "CAknsEffectCommand::SetLayerConf" );
    AssertNotNullL( eftCmd, KParam );
	
	para = eftCmd->LayerConf();
    _LIT( KLayerConf, "CAknsEffectCommand::LayerConf" );
    AssertNotNullL( &para, KLayerConf );	 

	MAknsRlParameterIterator* iterator = eftCmd->CreateParameterIteratorL();
    _LIT( KParaIterator, "CAknsEffectCommand::CreateParameterIteratorL" );
    AssertNotNullL( iterator, KParaIterator );	 
	delete iterator;
	iterator = NULL;
	
	TAknsRlParameterData paraData;
	_LIT( KName, "EffectName" );
	TDesC16 paraName ( KName );
	paraData.iName = &paraName;
	eftCmd->AppendParameterL( paraData );
    _LIT( KParaData, "CAknsEffectCommand::AppendParameterL" );
    AssertNotNullL( eftCmd, KParaData);	 
	
    CleanupStack::PopAndDestroy( eftCmd );
   	}
    
