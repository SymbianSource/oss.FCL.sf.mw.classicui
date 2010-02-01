/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  observer
*
*/


// INCLUDE FILES
#include "testsdkcfdmaknmemoryselectionobserver.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKCFDMAknMemorySelectionOberver::CTestSDKCFDMAknMemorySelectionOberver
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSDKCFDMAknMemorySelectionOberver::CTestSDKCFDMAknMemorySelectionOberver()
    {
    }

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
CTestSDKCFDMAknMemorySelectionOberver::~CTestSDKCFDMAknMemorySelectionOberver()
    {
    }

// -----------------------------------------------------------------------------
// Get's called when user selects a memory.
// -----------------------------------------------------------------------------
//
TBool CTestSDKCFDMAknMemorySelectionOberver::OkToExitL(
    CAknMemorySelectionDialog::TMemory /*aMemory*/ )
    { 
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFDMAknMemorySelectionOberver::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestSDKCFDMAknMemorySelectionOberver* CTestSDKCFDMAknMemorySelectionOberver::NewL()
    {
    CTestSDKCFDMAknMemorySelectionOberver* self = new( ELeave ) CTestSDKCFDMAknMemorySelectionOberver;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFDMAknMemorySelectionOberver::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestSDKCFDMAknMemorySelectionOberver::ConstructL()
    {
    }

