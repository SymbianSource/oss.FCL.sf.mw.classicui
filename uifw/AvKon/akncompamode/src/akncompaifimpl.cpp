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
* Description:  Compa-mode ecom interface implementation
*
*/


#include <e32base.h>
#include <../ecom/implementationproxy.h>

#include "akncompaifimpl.h"
#include "akncompaif.hrh"
#include "akncompautils.h"
#include "akncompakb.h"
#include "akncompaclearer.h"

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CAknCompaIfImpl* CAknCompaIfImpl::NewL()
    {
    return new (ELeave) CAknCompaIfImpl;
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CAknCompaIfImpl::~CAknCompaIfImpl()
    {
    delete iCompaKb;
    delete iClearer;
    }

// --------------------------------------------------------------------------
// Check if application requires compa-mode. Set screen mode to compa-mode
// if compa-mode is enabled and application requires it. Returns KErrNotFound
// if compa-mode is not needed.
// --------------------------------------------------------------------------
TInt CAknCompaIfImpl::SetCompaAppScreenModeL(TBool& aScrModeChanged,
    TBool& aIsConsoleApp, TInt aAppUiFlags, CAknAppUiBase& aAppUi,
    const CCoeEnv& aCoeEnv, CRepository& aRepository)
    {
    return AknCompaUtils::SetCompaAppScreenModeL(aScrModeChanged,
        aIsConsoleApp, iClearer, aAppUiFlags, aAppUi, aCoeEnv, aRepository);
    }

// --------------------------------------------------------------------------
// Create instance of compa keyboard
// --------------------------------------------------------------------------
void CAknCompaIfImpl::CreateKbL(TInt aCompaScreenMode, TBool aMakeVisible)
    {
    iCompaKb = CAknCompaKb::NewL(aCompaScreenMode, aMakeVisible);
    delete iClearer; iClearer = NULL;
    }

// --------------------------------------------------------------------------
// Check if compa-mode application is on foreground
// --------------------------------------------------------------------------
TBool CAknCompaIfImpl::IsForeground()
    {
    return iCompaKb->IsForeground();
    }

// --------------------------------------------------------------------------
// Find compatibility screen mode
// --------------------------------------------------------------------------
TInt CAknCompaIfImpl::FindCompaScreenMode()
    {
    return AknCompaUtils::FindCompaScreenMode();
    }

// --------------------------------------------------------------------------
// Disable transition effects
// --------------------------------------------------------------------------
void CAknCompaIfImpl::DisableTransEffects(TBool aDisable)
    {
    iCompaKb->DisaTransEffects(aDisable);
    }

// --------------------------------------------------------------------------
// Return factory functions for ECOM interface implementations
// --------------------------------------------------------------------------
EXPORT_C const TImplementationProxy* ImplementationGroupProxy(
    TInt& aTableCount)
    {
    static const TImplementationProxy ImplementationTable[] = 
        {
        IMPLEMENTATION_PROXY_ENTRY(
            AKNCOMPAIF_ECOM_IMPL_UID, CAknCompaIfImpl::NewL)
        };
    aTableCount =
        sizeof(ImplementationTable) / sizeof(ImplementationTable[0]);

    return ImplementationTable;
    }
