/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Compa Mode Settings model implementation.
*
*/


#include <centralrepository.h>
#include <AvkonInternalCRKeys.h>

#include "akncompagsmodel.h"
#include "akncompaflags.h"

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CAknCompaGSModel* CAknCompaGSModel::NewL()
    {
    CAknCompaGSModel* self = new( ELeave ) CAknCompaGSModel;
    CleanupStack::PushL( self );
    self->ConstructL();

    CleanupStack::Pop( self );
    return self;
    }


// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
CAknCompaGSModel::CAknCompaGSModel()
    {
    }


// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
void CAknCompaGSModel::ConstructL()
    {
    iRepository = CRepository::NewL(KCRUidAvkon);
    iRepository->Get(KAknCompaModeFeatures, iFeatures);
    iRepository->Get(KAknCompaModeSettings, iSettings);
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CAknCompaGSModel::~CAknCompaGSModel()
    {
    delete iRepository;
    }

// --------------------------------------------------------------------------
// Check if compatibility mode feature is enabled in the image
// --------------------------------------------------------------------------
TBool CAknCompaGSModel::FeatureEnabled()
    {
    return iFeatures & KAknCompaFeatureEnaCompaMode;
    }


// --------------------------------------------------------------------------
// Get compatibility mode enable/disable setting
// --------------------------------------------------------------------------
TBool CAknCompaGSModel::CompaAppState()
    {
    return iSettings & KAknCompaSettingEnaApps;
    }


// --------------------------------------------------------------------------
// Set compatibility mode enable/disable setting
// --------------------------------------------------------------------------
void CAknCompaGSModel::SetCompaAppState(TBool aState)
    {
    if (FeatureEnabled() && CompaAppState() != aState)
        {
        if (aState)
            {
            iSettings |= KAknCompaSettingEnaApps;
            }
        else
            {
            iSettings &= ~KAknCompaSettingEnaApps;
            }
        iRepository->Set(KAknCompaModeSettings, iSettings);
        }
    }
