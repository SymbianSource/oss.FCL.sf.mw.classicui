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
* Description:         Invoke eik progress info's protected APIs.
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <s32file.h>
#include <f32file.h>

#include "bctestsubeikprogressinfo.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestSubEikProgressInfo* CBCTestSubEikProgressInfo::NewL()
    {
    CBCTestSubEikProgressInfo* self = new( ELeave ) 
        CBCTestSubEikProgressInfo();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestSubEikProgressInfo::CBCTestSubEikProgressInfo()
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestSubEikProgressInfo::~CBCTestSubEikProgressInfo()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestSubEikProgressInfo::ConstructL()
    {
    }
    
    





    
   

    
