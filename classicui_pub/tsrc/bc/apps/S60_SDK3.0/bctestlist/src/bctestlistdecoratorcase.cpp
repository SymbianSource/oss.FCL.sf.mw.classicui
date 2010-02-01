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
* Description:         test case for aknlistboxlayoutdecorator
*
*/









#include <w32std.h>
#include <eikenv.h>
#include <aknlistboxlayoutdecorator.h>

#include "bctestlistdecoratorcase.h"
#include "bctestlistcontainer.h"
#include "bctestlist.hrh"
#include <bctestlist.rsg>

_LIT( KDecoratorTest1, "CAknListBoxLayoutDecorator::NewL()" );
_LIT( KDecoratorTest2, "CAknListBoxLayoutDecorator::SetArray and Array" );
_LIT( KDecoratorTest3, "CAknListBoxLayoutDecorator::SetLeadingDecorationTextL" );
_LIT( KDecoratorTest4, "CAknListBoxLayoutDecorator::SetTrailingDecorationTextL" );
_LIT( KDecoratorTest5, "CAknListBoxLayoutDecorator::SetActive" );
_LIT( KDecoratorTest6, "CAknListBoxLayoutDecorator::MdcaCount" );
_LIT( KDecoratorTest7, "CAknListBoxLayoutDecorator::MdcaPoint" );
_LIT( KTextLeading, "Leading text" );
_LIT( KTextTrailing, "Trailing text" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestListDecoratorCase* CBCTestListDecoratorCase::NewL( 
    CBCTestListContainer* aContainer, CEikonEnv* aEikEnv )
    {
    CBCTestListDecoratorCase* self = new( ELeave ) CBCTestListDecoratorCase( 
        aContainer, aEikEnv );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestListDecoratorCase::CBCTestListDecoratorCase( CBCTestListContainer* aContainer,
    CEikonEnv* aEikEnv )
    : CBCTestListBaseCase( aContainer, aEikEnv )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestListDecoratorCase::~CBCTestListDecoratorCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestListDecoratorCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListDecoratorCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestListDecoratorCase::BuildScriptL()
    {    
    for ( TInt i=0; i <= EBCTestCmdOutline44 - EBCTestCmdOutline43; i++ )
        {
        AddTestL( LeftCBA, REP( Down, 5 ), KeyOK, TEND );
        AddTestL( REP( Down, i ), KeyOK, TEND );
        }      
    }
    
// ---------------------------------------------------------------------------
// CBCTestListDecoratorCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestListDecoratorCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline43 || aCmd > EBCTestCmdOutline44 )
        {
        return;
        }
    ReleaseCase();
    switch ( aCmd )  
        {
        case EBCTestCmdOutline43:
            TestLayoutDecoratorL();
            break;        
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestListDecoratorCase::ReleaseCase
// ---------------------------------------------------------------------------
//   
void CBCTestListDecoratorCase::ReleaseCase()
    {
    iContainer->ResetControl();    
    }

// ---------------------------------------------------------------------------
// CBCTestListDecoratorCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestListDecoratorCase::TestLayoutDecoratorL()
    {
    CDesCArray* textArray = iEikEnv->ReadDesCArrayResourceL( 
        R_BCTESTLIST_ITEM_SINGLE1 );
    CleanupStack::PushL( textArray );

    CAknListBoxLayoutDecorator* decorator = NULL;    
    decorator = CAknListBoxLayoutDecorator::NewL();
    CleanupStack::PushL( decorator );
    AssertNotNullL( decorator, KDecoratorTest1 );    
    
    decorator->SetArray( textArray );
    const MDesCArray* array = decorator->Array();
    AssertTrueL( ( array == textArray ), KDecoratorTest2 );    
    
    decorator->SetLeadingDecorationTextL( KTextLeading );
    AssertTrueL( ETrue, KDecoratorTest3 );
    
    decorator->SetTrailingDecorationTextL( KTextTrailing );
    AssertTrueL( ETrue, KDecoratorTest4 );
        
    decorator->SetActive( ETrue );
    decorator->SetActive( EFalse );
    AssertTrueL( ETrue, KDecoratorTest5 );    
    
    TInt mdcaCount = decorator->MdcaCount();
    AssertIntL( textArray->Count(), mdcaCount, KDecoratorTest6 );    
    for ( TInt i=0; i< mdcaCount; i++ )
        {
        TPtrC ptr = decorator->MdcaPoint( i );        
        }
    AssertTrueL( ETrue, KDecoratorTest7 );
    
    CleanupStack::PopAndDestroy( decorator );    
    CleanupStack::PopAndDestroy( textArray );
    }
    
