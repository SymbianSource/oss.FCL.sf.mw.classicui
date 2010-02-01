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
* Description:  Wrapper for media gallery and profiles libraries.
*
*/

#include <MProfile.h> 
#include <MProfileTones.h>               
#include <MProfilesNamesArray.h>
#include <MProfileEngineExtended.h>
#include <MProfileSetExtraTones.h>
#include <MProfileSetTones.h>
#include <MProfileExtended.h>
#include <MProfileName.h>

#include <DRMHelper.h>

#ifdef RD_CONTENTNOTIFICATION
#include <contentnotification.hrh>
#include <contentcreatedevent.h>
#include <contentnotification.h>
#endif //RD_CONTENTNOTIFICATION
#include <coemain.h>

#include "pslnprofilesettingsloader.h"
#include "PslnConst.h"

#ifdef RD_CONTENTNOTIFICATION
const TInt KPslnEventArraySize = 2;
#endif // RD_CONTENTNOTIFICATION

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// ---------------------------------------------------------------------------
//
CPslnProfileSettingsLoader::CPslnProfileSettingsLoader()
    {
    }

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CPslnProfileSettingsLoader* CPslnProfileSettingsLoader::NewL()
    {
    CPslnProfileSettingsLoader* self = 
        new( ELeave ) CPslnProfileSettingsLoader();

    return self;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CPslnProfileSettingsLoader::~CPslnProfileSettingsLoader()
    {
#ifdef RD_CONTENTNOTIFICATION
    if ( iEventArray )
        {
        iEventArray->Delete( 0 );
        iEventArray->Reset();        
        }
    delete iEventArray;
#endif // RD_CONTENTNOTIFICATION
    }

// ---------------------------------------------------------------------------
// Sets tone for all profiles.
// ---------------------------------------------------------------------------
//
void CPslnProfileSettingsLoader::SetToneForProfilesL( 
    TInt aType, TDes& aFullName )
    {
    MProfileEngineExtended* profileEngine = CreateProfileEngineExtendedL();
    CleanupReleasePushL( *profileEngine );
    MProfilesNamesArray* profileArray = profileEngine->ProfilesNamesArrayLC();

    TInt arrayCount( profileArray->MdcaCount() );
    TInt arrayIndex( 0 );
    TInt profileId( 0 );
    TInt activeId( profileEngine->ActiveProfileId() );

    while( arrayIndex < arrayCount )
    	{
    	profileId = profileArray->ProfileName( arrayIndex )->Id();
    	// Updating of the active profile will be done last to make sure that
    	// UI gets the new value of the ringing tone if settings view is active
    	// and it is containing settings of another than active profile
    	if( profileId != activeId )
    		{
    	    TRAPD(r, DoSetProfileToneL( profileEngine, profileId, aType, aFullName ));
    	    // Filter situation when profile is not allowed to be changed
    	    // e.g. Drive-profile
    	    if( ( r != KErrNone ) && ( r != KErrAccessDenied ) )
    	    	{
    	    	User::Leave( r );
    	    	}
    	    }
    	arrayIndex ++;
    	}	    

    // Update the active profile:
    TRAPD(r, DoSetProfileToneL( profileEngine, activeId, aType, aFullName ));
    if( ( r != KErrNone ) && ( r != KErrAccessDenied ) )
    	{
        User::Leave( r );
        }
	CleanupStack::PopAndDestroy( 2 ); //profileEngine,profileArray
    }

// ---------------------------------------------------------------------------
// Do Sets tone for all profiles.
// ---------------------------------------------------------------------------
//
void CPslnProfileSettingsLoader::DoSetProfileToneL( MProfileEngineExtended* aProfileEngine,
		TInt aProfileId, TInt aType,const TDesC& aFileName )
	{
	MProfileExtended* profile = aProfileEngine->ProfileLC( aProfileId );
	CDRMHelper* drmHelper = CDRMHelper::NewLC();
	
	// Get the old tone in order to remove it from the automated content list
	TFileName oldTone( ToneL( *profile, aType ) );

	// Replace the old tone with the new tone
	SetToneL( *profile, aType, aFileName );
	
	// Commit changes. Write the new settings to the Profiles Engine
	aProfileEngine->CommitChangeL( *profile );

	// Register file as automated content
	TInt err( SetAutomated( drmHelper, aType, aFileName ) );
	if( err == KErrNone )
		{
	    // Remove old tone from the automated content list
	    RemoveAutomated( drmHelper,oldTone );
	    }
	else
		{
	    // Put the old tone back into Profiles:
	    TRAP_IGNORE(
	    		SetToneL( *profile, aType, oldTone );
	    		aProfileEngine->CommitChangeL( *profile );
	            );
	    }

	CleanupStack::PopAndDestroy( 2 ); // profile,drmHelper
	}

// ---------------------------------------------------------------------------
// SetTones.
// ---------------------------------------------------------------------------
//
void CPslnProfileSettingsLoader::SetToneL( MProfileExtended& aProfile,
   		TInt aType, const TDesC& aFileName )
	{
	MProfileSetTones& setTones = aProfile.ProfileSetTones();
	switch ( aType )
		{
		case EAknsMinorSoundRingingTone:
			setTones.SetRingingTone1L( aFileName );
			break;
		case EAknsMinorSoundMessageAlert:
			setTones.SetMessageAlertToneL( aFileName );
			break;
		default:
			User::Leave( KErrArgument );
			break;
		}
	}

// ---------------------------------------------------------------------------
// Read Tones.
// ---------------------------------------------------------------------------
//
const TDesC& CPslnProfileSettingsLoader::ToneL( MProfileExtended& aProfile,
   		TInt aType )
	{
	const MProfileTones& tones = aProfile.ProfileTones();	
	switch ( aType )
		{
		case EAknsMinorSoundRingingTone:
			{
			return tones.RingingTone1();
			}
		case EAknsMinorSoundMessageAlert:
			{
			return tones.MessageAlertTone();
			}
		default:
			User::Leave( KErrArgument );
			break;
		}
	return KNullDesC;
	}

// -----------------------------------------------------------------------------
// SetAutomated
// -----------------------------------------------------------------------------
//
TInt CPslnProfileSettingsLoader::SetAutomated( CDRMHelper* aDrmHelper,TInt aType,
                                        const TDesC& aFileName )
    {
    switch ( aType )
    	{
		case EAknsMinorSoundRingingTone:
			aDrmHelper->SetAutomatedType( CDRMHelper::EAutomatedTypeRingingTone );
			break;
    	case EAknsMinorSoundMessageAlert:
    		aDrmHelper->SetAutomatedType( CDRMHelper::EAutomatedTypeMessageAlert );
    		break;
    	default:
    		aDrmHelper->SetAutomatedType( CDRMHelper::EAutomatedTypeOther );
    	}
    return aDrmHelper->SetAutomatedSilent( aFileName, EFalse );
    }

// -----------------------------------------------------------------------------
// RemoveAutomated
// -----------------------------------------------------------------------------
//
void CPslnProfileSettingsLoader::RemoveAutomated( CDRMHelper* aDrmHelper,const TDesC& aFileName )
    {
    aDrmHelper->RemoveAutomatedPassive( aFileName ); // ignore return value
    }

// ---------------------------------------------------------------------------
// Indicates to the Media Gallery that new file has been copied.
// ---------------------------------------------------------------------------
//
void CPslnProfileSettingsLoader::IndicateFileUpdationL( const TDesC& aFullPath )
    {
	// Notice: this code is used to avoid the building warning!
    aFullPath.Length();
#ifdef RD_CONTENTNOTIFICATION
	CContentNotification* notifier = CContentNotification::NewL();
    CleanupStack::PushL( notifier );

    if ( iEventArray )
        {
        iEventArray->Delete( 0 );
        iEventArray->Reset();
        delete iEventArray;
        iEventArray = NULL;
        }

    iEventArray =
        new CArrayFixFlat<CContentNotificationEvent*>(KPslnEventArraySize);

	// Nofication about new content
	CContentNotificationEvent* event = 
        CContentCreatedEvent::NewL( aFullPath );
    CleanupStack::PushL( event );
    iEventArray->AppendL( event );
    CleanupStack::Pop( event ); // array owns the event

	// Send all notification event with one call
    User::LeaveIfError( notifier->SendNotification( iEventArray->Array() ) );
    delete event;
    event = NULL;
    CleanupStack::PopAndDestroy( notifier );
#endif //RD_CONTENTNOTIFICATION
    }

//----------------------------------------------------------------------------
// Launcher gate function
//----------------------------------------------------------------------------
EXPORT_C TAny* GateFunction()
    {
    CPslnProfileSettingsLoader* launcher = NULL;
    TRAPD( err, launcher = CPslnProfileSettingsLoader::NewL() );
    if( err != KErrNone )
        {
        return NULL;
        }
    return launcher;
    }

//  End of File  
