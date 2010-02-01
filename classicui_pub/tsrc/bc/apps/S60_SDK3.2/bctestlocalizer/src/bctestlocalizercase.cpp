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
#include <cdirectorylocalizer.h>
#include <bctestlocalizer.rsg>

#include "bctestlocalizercase.h"
#include "bctestlocalizercontainer.h"
#include "bctestlocalizer.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestLocalizerCase* CBCTestLocalizerCase::NewL(
    CBCTestLocalizerContainer* aContainer )
    {
    CBCTestLocalizerCase* self = new( ELeave ) CBCTestLocalizerCase(
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
CBCTestLocalizerCase::CBCTestLocalizerCase(
    CBCTestLocalizerContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestLocalizerCase::~CBCTestLocalizerCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestLocalizerCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestLocalizerCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestLocalizerCase::BuildScriptL()
    {
    // Add script as your need.
    const TInt scripts[] =
        {
        DELAY( 5 ), // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        LeftCBA
        };
    AddTestScriptL( scripts, sizeof( scripts )/sizeof( TInt ) );
    }

// ---------------------------------------------------------------------------
// CBCTestLocalizerCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestLocalizerCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline1 )
        {
        return;
        }

    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            TestFunctionL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestLocalizerCase::TestFunctionL
// ---------------------------------------------------------------------------
//
void CBCTestLocalizerCase::TestFunctionL()
    {
    // Test some API here
	_LIT( KDLTestExistsDir, "c:\\data\\Games\\" );

    CDirectoryLocalizer* localizer = CDirectoryLocalizer::NewL();
    CleanupStack::PushL( localizer );
  	_LIT( KNewL, "CDirectoryLocalizer::NewL() called" );
  	AssertNotNullL( localizer, KNewL );
  	
  	localizer->AddFromResourceL( R_DLTEST_CUSTOM_ENTRIES );
  	_LIT( KAddFromResourceL, 
  	    "CDirectoryLocalizer::AddFromResourceL( aResourceId ) called" );
  	AssertTrueL( ETrue, KAddFromResourceL );
    
    localizer->SetFullPath( KDLTestExistsDir );
  	_LIT( KSetFullPath, "CDirectoryLocalizer::SetFullPath() called" );
  	AssertTrueL( ETrue, KSetFullPath );
    
    _LIT( KIsLocalized, "CDirectoryLocalizer::IsLocalized() called" );
    AssertTrueL( localizer->IsLocalized(), KIsLocalized );
    
    _LIT( KLocalizedName, 
        "CDirectoryLocalizer::LocalizedName() called" );  
    localizer->LocalizedName();
    AssertTrueL( ETrue, KLocalizedName );

    _LIT( KExtraData, "CDirectoryLocalizer::ExtraData() called" );  
    localizer->ExtraData();  
    AssertTrueL( ETrue, KExtraData );

    _LIT( KIcon, "CDirectoryLocalizer::Icon() called" );  
    localizer->Icon();  
    AssertTrueL( ETrue, KIcon );
    
    CleanupStack::PopAndDestroy( localizer );

    CDirectoryLocalizer* localizer2 = 
        CDirectoryLocalizer::NewL( R_DLTEST_CUSTOM_ENTRIES );
    CleanupStack::PushL( localizer2 );
  	_LIT( KNewL2, "CDirectoryLocalizer::NewL( aResourceId ) called" );
  	AssertNotNullL( localizer2, KNewL2 );
    CleanupStack::PopAndDestroy( localizer2 );
    
    }

