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
#include <eikbctrl.h>
#include <eikenv.h>

// the extra header make for test 
#include <aknnotewrappers.h>

// below header from framework
#include "bctesteikbctrlcase.h"
#include "bctesteikbctrlcontainer.h"
#include "bctesteikbctrl.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTesteikbctrlCase* CBCTesteikbctrlCase::NewL( 
    CBCTesteikbctrlContainer* aContainer )
    {
    CBCTesteikbctrlCase* self = new( ELeave ) CBCTesteikbctrlCase( 
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
CBCTesteikbctrlCase::CBCTesteikbctrlCase( 
    CBCTesteikbctrlContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//

CBCTesteikbctrlCase::~CBCTesteikbctrlCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTesteikbctrlCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTesteikbctrlCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTesteikbctrlCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY( 1 ), LeftCBA, KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTesteikbctrlCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTesteikbctrlCase::RunL( TInt aCmd )
    { 
    if ( aCmd < EBCTestCtrlCreat || aCmd > EBCTestCtrlCreat )
       {
       	return;
       }    
    
    switch ( aCmd )  
        {
        case EBCTestCtrlCreat:
            TestFunctionL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTesteikbctrlCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTesteikbctrlCase::TestFunctionL()
    {
     //tst text declare here
     _LIT( creatBorder,"new a CEikBorderedControl object " );
     _LIT( setBorderTInt, " SetBorder( TInt) test for EikBctrl! " ) ;
     _LIT( setBorderType, " SetBorder( TGulBorder::BorderType ) test for EikBctrl! " ) ;
     _LIT( getBorder," Border( ) test for EikBctrl! " ) ;
     _LIT( setAdjacent," invoke SetAdjacent" );
     _LIT( resourceChange, " call handleResourceChange " );
     _LIT( pointEvent, " call handlePointEvent" );
     _LIT( retHasBorder," HasBorder( ) test for EikBctrl! " ) ;
     
     //create no parameter border control
     CEikBorderedControl * boder = new ( ELeave ) CEikBorderedControl();
     AssertNotNullL( boder,creatBorder );
     
     //invoke SetBorder function
     boder->SetBorder(TGulBorder::EDeepSunken);
     AssertTrueL( ETrue,setBorderType );
     
     boder->SetBorder(TInt(2));
     AssertTrueL( ETrue, setBorderTInt);
     
     //invoke border function
     TGulBorder gulBorder = boder->Border();
     AssertTrueL( ETrue,getBorder );
     
	 boder->SetAdjacent(EGulAdjBottom);
	 AssertTrueL( ETrue,setAdjacent);
	 
	 //invoke handleresourcechange
	 boder->HandleResourceChange(TInt(1));
	 AssertTrueL( ETrue,resourceChange);
	
	 //invoke handlePointEventL function
	 TPointerEvent pEvnt;
	 pEvnt.iType = TPointerEvent::EButton1Down;
	 boder->HandlePointerEventL( pEvnt );
	 AssertTrueL( ETrue, pointEvent);
	 
	 boder->HasBorder();
	 AssertTrueL( ETrue, retHasBorder);
	 
 	 CArrayFix<TCoeColorUse>* clrList =
		new (ELeave) CArrayFixFlat<TCoeColorUse>(256);
     CleanupStack::PushL(clrList);
     boder->GetColorUseListL( *clrList ); 
     _LIT(gtClrUsrList," Test GetColorUseListL()" );
     AssertTrueL( ETrue, gtClrUsrList);
     CleanupStack::Pop(clrList);
     delete clrList;
	 
     delete boder;
    }
    
