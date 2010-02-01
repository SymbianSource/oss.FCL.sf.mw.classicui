/*
* Copyright (c) 2005-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Get count of VoIP profiles and
*               Handles Preferred Telephony setting events.
*
*/

#include "FindItemVoIPExtension.h"
#include <featmgr.h>
#ifndef RD_VOIP_REL_2_2
#include <CRCSEProfileRegistry.h>
#include <centralrepository.h>
#include <SettingsInternalCRKeys.h>

// CONSTANTS
// Preferred Telephony value is PS call
static const TInt KRCSEInternetCallPreferred = 1;
// Dynamic VoIP off
static const TInt KVoIPOFF = 0;

#else
#include <spsettings.h>
#include <spsettingsvoiputils.h>
#endif // RD_VOIP_REL_2_2
// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
#ifndef RD_VOIP_REL_2_2
CFindItemVoIPExtension::CFindItemVoIPExtension():
    iVoIPSupported( EFalse ),
    iPreferredTelephonyVoIP(EFalse)
    {
    }
#else
CFindItemVoIPExtension::CFindItemVoIPExtension()
    {
    }
#endif // RD_VOIP_REL_2_2

// Two-phased constructor.
//
CFindItemVoIPExtension* CFindItemVoIPExtension::NewL()
    {
    CFindItemVoIPExtension *self =
        new ( ELeave ) CFindItemVoIPExtension();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// ConstructL
//
void CFindItemVoIPExtension::ConstructL()
    {
    if ( FeatureManager::FeatureSupported( KFeatureIdCommonVoip ) )
        {
#ifndef RD_VOIP_REL_2_2
        TInt VoIPSupported( KVoIPOFF );
        TInt value( 0 );
        iVoIPVariation = CRepository::NewL( KCRUidTelephonySettings );
        iVoIPVariation->Get( KDynamicVoIP, VoIPSupported );
        iVoIPVariationNotifier = CCenRepNotifyHandler::NewL( *this, *iVoIPVariation,
            CCenRepNotifyHandler::EIntKey, KDynamicVoIP );
        iVoIPVariationNotifier->StartListeningL();

        iVoIPSupported = KVoIPOFF != VoIPSupported;

        // Create the session
        iCenRepSession = CRepository::NewL( KCRUidRichCallSettings );
        iCenRepSession->Get( KRCSEPreferredTelephony, value );
        if ( iCenRepSession )
            {
            iPreferredTelephonyVoIP = KRCSEInternetCallPreferred == value;

            // Create the notifer
            iNotifier = CCenRepNotifyHandler::NewL( *this, *iCenRepSession,
                CCenRepNotifyHandler::EIntKey, KRCSEPreferredTelephony );

            // Start listening
            iNotifier->StartListeningL();
            }
#else
        // for handling services related data
        iSPSettings = CSPSettings::NewL();
        iSPSettingsVoipUtils = CSPSettingsVoIPUtils::NewL();

#endif // RD_VOIP_REL_2_2
        }
    }

// Destructor
//
CFindItemVoIPExtension::~CFindItemVoIPExtension()
    {
#ifndef RD_VOIP_REL_2_2
    if ( FeatureManager::FeatureSupported( KFeatureIdCommonVoip ) )
        {
        if( NULL != iVoIPVariationNotifier )
        	{
        	iVoIPVariationNotifier->StopListening();
        	}
        delete iVoIPVariationNotifier;
        delete iVoIPVariation;

        delete iNotifier;
        delete iCenRepSession;
        }
#else
    delete iSPSettings;
    delete iSPSettingsVoipUtils;
#endif // RD_VOIP_REL_2_2
    }

#ifndef RD_VOIP_REL_2_2
// ----------------------------------------------------
//  CFindItemVoIPExtension::HandleNotifyInt
//
// ----------------------------------------------------
//
void CFindItemVoIPExtension::HandleNotifyInt(
    const TUint32 aID,
    const TInt    aNewValue )
    {
    if ( KRCSEPreferredTelephony == aID )
        {
        iPreferredTelephonyVoIP =
            KRCSEInternetCallPreferred == aNewValue;
        }
    if ( KDynamicVoIP == aID )
        {
        iVoIPSupported = KVoIPOFF != aNewValue;
        }
    }

// ----------------------------------------------------
//  CFindItemVoIPExtension::HandleNotifyError
// ----------------------------------------------------
//
void CFindItemVoIPExtension::HandleNotifyError(
    const TUint32 /*aID*/,
    const TInt    /*aError*/,
  CCenRepNotifyHandler* /*aHandler*/ )
    {
    //NO OPERATION
    }
#endif // !RD_VOIP_REL_2_2

// ----------------------------------------------------
// CFindItemVoIPExtension::VoIPProfilesExistL
//
// ----------------------------------------------------
TBool CFindItemVoIPExtension::VoIPProfilesExistL() const
    {
#ifndef RD_VOIP_REL_2_2
  TBool isProfiles = EFalse;

    if ( iVoIPSupported )
        {
        RArray<TUint32> profileArray;

        CRCSEProfileRegistry* rcseProfileRegistry = CRCSEProfileRegistry::NewLC();
        rcseProfileRegistry->GetAllIdsL( profileArray );

        if ( profileArray.Count() > 0 )
            {
            isProfiles = ETrue;
            }

        profileArray.Close();

        CleanupStack::PopAndDestroy(); // rcseProfile
        }

    return isProfiles;
#else // RD_VOIP_REL_2_2
    TBool ret( EFalse );

    if ( FeatureManager::FeatureSupported( KFeatureIdCommonVoip ) )
        {
        ret = iSPSettings->IsFeatureSupported( ESupportVoIPFeature );
        }

    return ret;
#endif // !RD_VOIP_REL_2_2
    }

// ----------------------------------------------------
// CFindItemVoIPExtension::IsPreferredTelephonyVoIP
//
// ----------------------------------------------------
TBool CFindItemVoIPExtension::IsPreferredTelephonyVoIP()
    {
#ifndef RD_VOIP_REL_2_2
    return iPreferredTelephonyVoIP && iVoIPSupported;
#else // RD_VOIP_REL_2_2
    if ( FeatureManager::FeatureSupported( KFeatureIdCommonVoip ) )
        {
        return iSPSettingsVoipUtils->IsPreferredTelephonyVoIP();
        }
    else
        {
        return EFalse;
        }
#endif // !RD_VOIP_REL_2_2
    }

// ----------------------------------------------------
// CFindItemVoIPExtension::IsVoIPSupported
//
// ----------------------------------------------------
TBool CFindItemVoIPExtension::IsVoIPSupported()
    {
#ifndef RD_VOIP_REL_2_2
    return iVoIPSupported;
#else // RD_VOIP_REL_2_2
    if ( FeatureManager::FeatureSupported( KFeatureIdCommonVoip ) )
        {
        return iSPSettings->IsFeatureSupported( ESupportVoIPFeature );
        }
    else
        {
        return EFalse;
        }
#endif // !RD_VOIP_REL_2_2
    }
//  End of File

