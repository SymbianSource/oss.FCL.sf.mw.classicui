/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test utility, the interface of test framework.
*
*/


#include <sysutil.h>
#include "bctestendcase.h"

#include <e32property.h>
const TUid KPSUidAvkonDomainForBC = { 0x10207218 }; // Same as KPSUidAvkonDomain
const TUint32 KAknMenuOptionNoTaskSwapper = 0x10000002;
enum TAknMenuOptionNoTaskSwapper
    {
    ETaskSwapper,
    ENoTaskSwapper
    };
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestEndCase::CBCTestEndCase()
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestEndCase::~CBCTestEndCase()
    {    
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd constructor
// ---------------------------------------------------------------------------
//
CBCTestEndCase* CBCTestEndCase::NewL()
    {
    CBCTestEndCase* self = new( ELeave ) CBCTestEndCase();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd constructor
// ---------------------------------------------------------------------------
//
void CBCTestEndCase::ConstructL()
    {
    BuildScriptL();
    }

static TInt SDKVersion()
	{	
	TInt swver = 30;
    TInt taskSwapper( ENoTaskSwapper ) ;// taskSwapper
    TInt result = RProperty::Get( KPSUidAvkonDomainForBC, 
            KAknMenuOptionNoTaskSwapper, taskSwapper );
    TInt ret = RProperty::Define( KPSUidAvkonDomainForBC,
            KAknMenuOptionNoTaskSwapper, RProperty::EInt );
    
    if (ret == KErrAlreadyExists)
        {
        if ( result == KErrNotFound )
            {
            swver = 30;
            }
        else
            {
            if ( taskSwapper == 0 )
                {
                swver = 50;
                }
            else
                {
                swver = 30;
                }
            }
        }
    else
        {
        RProperty::Set( KPSUidAvkonDomainForBC,
                KAknMenuOptionNoTaskSwapper, ENoTaskSwapper );
        }
    return swver;	//default version	
    }

// ---------------------------------------------------------------------------
// CBCTestEndCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestEndCase::BuildScriptL()
    {
    TInt sdkver = SDKVersion();
    if ( sdkver == 32 || sdkver == 50 )
        {
        AddTestL( LeftCBA, Up, Up, LeftCBA, TEND );
        }
    else
        {
        AddTestL( LeftCBA, Up, LeftCBA, TEND );
        }
    }
