/*
* Copyright (c) 2004-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Utility class that defines supported features for Psln.
*
*/


// INCLUDE FILES

// Feature manager.
#include <featmgr.h>

// Central repository
#include <centralrepository.h>
#include "PslnVariationPrivateCRKeys.h"

// Psln specific.
#include "PslnVariant.hrh"
#include "PslnFeatures.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// PslnFeatures::IsHelpSupported
// -----------------------------------------------------------------------------
//
EXPORT_C TBool PslnFeatures::IsHelpSupported()
    {
    return FeatureManager::FeatureSupported( KFeatureIdHelp ); //lint !e40 Declared
    }

// -----------------------------------------------------------------------------
// PslnFeatures::IsEnhancedEmbeddedLinksSupported
// -----------------------------------------------------------------------------
//
EXPORT_C TBool PslnFeatures::IsEnhancedEmbeddedLinksSupported()
    {
    TBool linkSupport = EFalse;
    if ( IsSupported( KPslnEnhancedEmbeddedLinks ) &&
         IsSeamlessLinksSupported() )
        {
        linkSupport = ETrue;
        }
    return linkSupport;
    }

// -----------------------------------------------------------------------------
// PslnFeatures::IsSoundsInSkinsSupported
// -----------------------------------------------------------------------------
//
EXPORT_C TBool PslnFeatures::IsSoundsInSkinsSupported()
    {
    return IsSupported( KPslnSoundsInSkins );
    }

// -----------------------------------------------------------------------------
// PslnFeatures::IsMMCSupported
// -----------------------------------------------------------------------------
//
TBool PslnFeatures::IsMMCSupported()
    {
    return FeatureManager::FeatureSupported( KFeatureIdMmc );
    }

// -----------------------------------------------------------------------------
// PslnFeatures::IsAPACSupported
// -----------------------------------------------------------------------------
//
TBool PslnFeatures::IsAPACSupported()
    {
    return FeatureManager::FeatureSupported( KFeatureIdAvkonApac );
    }

// -----------------------------------------------------------------------------
// Checks if the given feature is currently supported.
// -----------------------------------------------------------------------------
//
EXPORT_C TBool PslnFeatures::IsSupported( TInt aLocalVariationID )
    {
    TBool retVal = EFalse;
    TRAP_IGNORE( retVal = IsSupportedL( aLocalVariationID ) );
    return retVal;
    }

// -----------------------------------------------------------------------------
// PslnFeatures::IsSeamlessLinksSupported
// -----------------------------------------------------------------------------
//
TBool PslnFeatures::IsSeamlessLinksSupported()
    {
    // Note that this method must return ETrue for EEL as well
    return FeatureManager::FeatureSupported( KFeatureIdSeamlessLinks ); //lint !e40 Declared
    }

// -----------------------------------------------------------------------------
// Checks if the given feature is currently supported.
// -----------------------------------------------------------------------------
//
TBool PslnFeatures::IsSupportedL( TInt aLocalVariationID )
    {
    TInt value = KErrNone;
    CRepository* variationRepository =
        CRepository::NewL( KCRUidThemesVariation );
    variationRepository->Get( KThemesLocalVariation, value );
    delete variationRepository;
    variationRepository = NULL;
    return ( value & aLocalVariationID );
    }

//  End of File
