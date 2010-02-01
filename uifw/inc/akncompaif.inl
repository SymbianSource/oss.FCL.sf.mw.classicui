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
* Description:  Compa-mode interface (client) implementation
*
*/


#include <e32base.h>
#include <../ecom/ecom.h>
#include <aknappui.h>
#include <centralrepository.h>
#include <AvkonInternalCRKeys.h>

#include "akncompaif.h"

// akncompaflags.h is not included. These are from there.
const TInt KAknCompaFeatureEnaCompaMode = 1; // Enable compa-mode in device
const TInt KAknCompaSettingEnaApps = 1;

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
inline CAknCompaIf::~CAknCompaIf()
    {
    REComSession::DestroyedImplementation(iEcomDtorId);
    }

// --------------------------------------------------------------------------
// Create instance of compa-mode interface
// --------------------------------------------------------------------------
inline CAknCompaIf* CAknCompaIf::NewL()
    {
    const TUid KImplUid = {0x20010126}; // AKNCOMPAIF_ECOM_IMPL_UID
    return reinterpret_cast<CAknCompaIf*>(
        REComSession::CreateImplementationL(KImplUid,
            _FOFF(CAknCompaIf, iEcomDtorId)));
    }

// --------------------------------------------------------------------------
// Check if compa-mode may be needed. If this function returns false,
// compa-mode is definetely not needed. Either application is touch
// compatible or compa mode feature is not enabled. If it returns true,
// compa-mode plugin should be instantiated to perform further checks.
// --------------------------------------------------------------------------
inline TBool CAknCompaIf::IsNeeded(TInt aAppUiFlags,
    CRepository* aRepository)
    {
    TBool isNeeded = EFalse;
    if ((aAppUiFlags & CAknAppUiBase::EAknTouchCompatible) == 0 &&
        aRepository)
        {
        // Compa-mode maybe needed if compa-mode feature is enabled in device
        TInt compaFeatures = 0;
        aRepository->Get(KAknCompaModeFeatures, compaFeatures);
        if (compaFeatures & KAknCompaFeatureEnaCompaMode)
            {
            TInt compaSettings = 0;
            aRepository->Get(KAknCompaModeSettings, compaSettings);
            // Compa-mode may be needed if compa-mode is enabled from settings
            // or the application is a global UI server.
            isNeeded = compaSettings & KAknCompaSettingEnaApps ||
                aAppUiFlags & CEikAppUi::ENoScreenFurniture;
            }
        }
    return isNeeded;
    }
