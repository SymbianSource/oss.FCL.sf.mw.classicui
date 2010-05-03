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
* Description:  adapter of layout
 *
*/

 
#include <w32std.h>

#include "bctestdomadapter.h"

const TInt KWindowTxtStart( 2 );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAdapter* CBCTestDomAdapter::NewL()
    {
    CBCTestDomAdapter* self = new( ELeave ) CBCTestDomAdapter( );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAdapter::CBCTestDomAdapter()
    : iAdpDataLookup( NULL )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomAdapter::~CBCTestDomAdapter()
    {  
    if ( iAdpDataLookup )
        {
        delete []iAdpDataLookup;
        iAdpDataLookup = NULL;
        }
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomAdapter::ConstructL()
    {   
    iAdpDataLookup = new (ELeave) TUint[12];
    iAdpDataLookup[0] = 0x18;
    iAdpDataLookup[1] = 2;
    iAdpDataLookup[2 ] = ( TUint )CBCTestDomAdapter::WindowLine0f;
    iAdpDataLookup[3] = ( TUint )CBCTestDomAdapter::WindowLine1f;
    iAdpDataLookup[4] = 0x0001;
    iAdpDataLookup[5] = KWindowTxtStart;
    iAdpDataLookup[6] = 2;
    iAdpDataLookup[7] = ( TUint )CBCTestDomAdapter::TextLine0f;
    iAdpDataLookup[8] = ( TUint )CBCTestDomAdapter::TextLine1f;
    iAdpDataLookup[9] = 0x0001;
    iAdpDataLookup[10] = KWindowTxtStart;
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAdapter::GetAdpDataLookup
// ---------------------------------------------------------------------------
//
TUint* CBCTestDomAdapter::GetAdpDataLookup()
    { 
    return iAdpDataLookup;
    }

// ---------------------------------------------------------------------------
// CBCTestDomAdapter::WindowLine0f
// ---------------------------------------------------------------------------
//    
TAknWindowLineLayout CBCTestDomAdapter::WindowLine0f()
    {
    return TAknWindowLineLayout(); 
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAdapter::WindowLine1f
// ---------------------------------------------------------------------------
//
TAknWindowLineLayout CBCTestDomAdapter::WindowLine1f( TInt /* aIndex */)   
    {
    return TAknWindowLineLayout();
    }
    
    
// ---------------------------------------------------------------------------
// CBCTestDomAdapter::TextLine0f
// ---------------------------------------------------------------------------
//
TAknTextLineLayout CBCTestDomAdapter::TextLine0f()
    {
    return TAknTextLineLayout();
    }

// ---------------------------------------------------------------------------
// CBCTestDomAdapter::TextLine1f
// ---------------------------------------------------------------------------
//
TAknTextLineLayout CBCTestDomAdapter::TextLine1f( TInt /* aIndex */ )
    {
    return TAknTextLineLayout();
    }
