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
#include <bctestlocation.rsg>
#include <barsread.h>
#include "bctestlocationcase.h"
#include "bctestlocationcontainer.h"
#include "bctestlocationview.h"
#include "bctestlocation.hrh"
#include <lbsposition.h>
#include <aknquerydialog.h>
#include <AknQueryControl.h>

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestLocationCase* CBCTestLocationCase::NewL( 
    CBCTestLocationContainer* aContainer )
    {
    CBCTestLocationCase* self = new( ELeave ) CBCTestLocationCase( 
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
CBCTestLocationCase::CBCTestLocationCase( 
    CBCTestLocationContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestLocationCase::~CBCTestLocationCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestLocationCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestLocationCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestLocationCase::BuildScriptL()
    {      
    AddTestL( DELAY(1), LeftCBA, KeyOK, TEND );  
    }
    
// ---------------------------------------------------------------------------
// CBCTestLocationCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestLocationCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdMaxOutline )
        {
        return;
        }    
    switch ( aCmd )  
        {
        case EBCTestCmdOutline1:
            TestFunctionOne();
            break;
        default:
            break;
        }
    }

void CBCTestLocationCase::TestFunctionOne()
    {
    _LIT(strCAknQueryNewL, "test NewL() in AknQueryDialog.h");
    _LIT(strGetLocation, "test GetLocation() in AknQueryControl.h");
    _LIT(strSetLocation, "test SetLocation() in AknQueryControl.h");
    
    TCoordinate coord(01.00, 01.0);
	TLocality loc(coord, 0.1);
	TPosition bp(loc, TTime());
    CAknMultiLineDataQueryDialog* mulDlg = 
        CAknMultiLineDataQueryDialog::NewL( bp );  
    AssertTrueL( ETrue, strCAknQueryNewL );
    delete mulDlg;
        
    CAknQueryControl* qd = new (ELeave) CAknQueryControl();
    CleanupStack::PushL( qd );
    qd->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, 
        R_BCTESTLOCATION_QUERY );
    qd->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // reader
    
    qd->SetLocation(bp);
    AssertTrueL( ETrue, strSetLocation );
    
    qd->GetLocation(bp);
    AssertTrueL( ETrue, strGetLocation );
    
    CleanupStack::PopAndDestroy( qd );    
    }    
