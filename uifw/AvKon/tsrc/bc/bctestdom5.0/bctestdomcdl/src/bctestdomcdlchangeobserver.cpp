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
* Description:  aid class implemention.
*
*/


#include "bctestdomcdlchangeobserver.h"


// ---------------------------------------------------------------------------
// CBCTestMCdlChangeObserver::CBCTestMCdlChangeObserver
// ---------------------------------------------------------------------------
//
CBCTestMCdlChangeObserver::CBCTestMCdlChangeObserver()
    {
    
    }

// ---------------------------------------------------------------------------
// CBCTestMCdlChangeObserver::~CBCTestMCdlChangeObserver
// ---------------------------------------------------------------------------
//
CBCTestMCdlChangeObserver::~CBCTestMCdlChangeObserver()
    {
    
    }

// ---------------------------------------------------------------------------
// CBCTestDomCdlInst::CBCTestDomCdlInst
// ---------------------------------------------------------------------------
//
CBCTestDomCdlInst::CBCTestDomCdlInst()
    { 
    
    }
    
// ---------------------------------------------------------------------------
// BCTestCdlInst::~CBCTestDomCdlInst
// ---------------------------------------------------------------------------
//
CBCTestDomCdlInst::~CBCTestDomCdlInst()
    {
    
    }

// ---------------------------------------------------------------------------
// CBCTestDomCdlInst::CreateInstanceLC
// ---------------------------------------------------------------------------
//
CCdlInstance* CBCTestDomCdlInst::CreateInstanceLC( const TCdlRef& /*aRef*/, 
                                                const CCdlInstance* /*aSubLayer*/)
    {
    return NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestDomCdlInst::CallCompare
// ---------------------------------------------------------------------------
//
TCdlInstanceComparison CBCTestDomCdlInst::CallCompare( const CCdlInstance& /*aFirst*/,
                                                    const CCdlInstance& /*aSecond*/ )const
    {
    //return,only for avoid warning
    TCdlInstanceComparison temValue = ECdlInstancesNotComparable;
    return temValue;
    }

// ---------------------------------------------------------------------------
// CBCTestDomCdlInst::CallIsValid
// ---------------------------------------------------------------------------
//
TBool CBCTestDomCdlInst::CallIsValid(const CCdlInstance& /*aInstance*/)const
    {
    //return,only for avoid warning
    return ETrue;
    }

// ---------------------------------------------------------------------------
// CBCTestDomCdlInst::FindLC
// ---------------------------------------------------------------------------
//
void CBCTestDomCdlInst::FindLC()
    {
    //return,only for avoid warning
    TUid aUid =  { 0x174657FC };
    CCdlInstanceExplorerBase::FindLC(aUid);
    }
    
