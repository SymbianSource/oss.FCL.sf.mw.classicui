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

#include "bctesteffectqueuecase.h"
#include "bctestskinscontainer.h"
#include "bctestskins.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestEffectQueueCase* CBCTestEffectQueueCase::NewL(
    CBCTestSkinsContainer* aContainer )
    {
    CBCTestEffectQueueCase* self = new( ELeave ) CBCTestEffectQueueCase(
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
CBCTestEffectQueueCase::CBCTestEffectQueueCase(
    CBCTestSkinsContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestEffectQueueCase::~CBCTestEffectQueueCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestEffectQueueCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestEffectQueueCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestEffectQueueCase::BuildScriptL()
    {
   const TInt scripts[] =
        {
        DELAY(1),        // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        REP(Down, 1),
        LeftCBA
        };
    AddTestScriptL(scripts, sizeof(scripts)/sizeof(TInt));
    }

// ---------------------------------------------------------------------------
// CBCTestEffectQueueCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestEffectQueueCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline2 || aCmd > EBCTestCmdOutline2 )
        {
        return;
        }

    switch ( aCmd )
        {
        case EBCTestCmdOutline2:
            TestFunctionL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestEffectQueueCase::TestFunctionL
// ---------------------------------------------------------------------------
//
void CBCTestEffectQueueCase::TestFunctionL()
    {
    // Test CAknsEffectQueueItemData APIs
    CAknsEffectQueueItemData* queueData = CAknsEffectQueueItemData::NewL();
    CleanupStack::PushL( queueData );
    _LIT( KQueue, "CAknsEffectQueueItemData::NewL" );
    AssertNotNullL( queueData, KQueue );

    queueData->SetInputLayer(2);
    TInt input = queueData->InputLayer();
    _LIT( KInputLayer, "CAknsEffectQueueItemData::InputLayer" );
    AssertIntL( 2, input, KInputLayer );
	
    queueData->SetInputLayerMode(3);
    TInt mode = queueData->InputLayerMode();
    _LIT( KInputMode, "CAknsEffectQueueItemData::InputLayerMode" );
    AssertIntL( 3, mode, KInputMode );	
	
    queueData->SetOutputLayer(4);
    TInt output = queueData->OutputLayer();
    _LIT( KOutputLayer, "CAknsEffectQueueItemData::OutputLayer" );
    AssertIntL( 4, output, KOutputLayer );
	
    queueData->SetOutputLayerMode(5);
    TInt outMode = queueData->OutputLayerMode();
    _LIT( KOutputMode, "CAknsEffectQueueItemData::OutputLayerMode" );
    AssertIntL( 5, outMode, KOutputMode );	
	
    CAknsEffectCommand* eftCmd = CAknsEffectCommand::NewL();
   	CleanupStack::PushL( eftCmd );
    queueData->AppendCommandL(eftCmd);
	CleanupStack::Pop( eftCmd );
	
	// The class returned is not defined in public SDK, panic.
	/*TAny* cmdItr = queueData->CreateCommandIteratorL(); 
	CleanupStack::PushL( cmdItr );
    _LIT( KCmdIterator, "CAknsEffectQueueItemData::CreateCommandIteratorL" );
    AssertNotNullL( cmdItr, KCmdIterator );
	CleanupStack::Pop( cmdItr );
	delete cmdItr;*/
		 
	CleanupStack::PopAndDestroy( queueData );    
    }

