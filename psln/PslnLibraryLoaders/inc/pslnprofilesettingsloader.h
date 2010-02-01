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
* Description:  Loads ProfileSettingsView.dll dynamically.
*
*/


#ifndef C_PSLNPROFILESETTINGSLOADER
#define C_PSLNPROFILESETTINGSLOADER

#include <e32base.h>

class MProfileEngineExtended;
class MProfileExtended;
class CDRMHelper;
/**
*  Interface class for profile settings view.
*  
*  @lib PslnProfileSettingsLoader.lib
*  @since Series 60 3.1
*/
class MPslnProfileSettingsLoader
    {
    public:

        /**
        * Pure virtual method for setting ringing tone for all profiles.
        * @param aType type of tone (actual ringing tone, or message alert tone).
        * @param aFullName full filename (inc. path) of tone.
        */
        virtual void SetToneForProfilesL( TInt aType, TDes& aFullName ) = 0;

        /**
        * Pure virtual method for indicating to the media gallery that 
        * there is new sound file available in the gallery.
        * @param aFullPath path and file of the new sound file..
        */
        virtual void IndicateFileUpdationL( const TDesC& aFullPath ) = 0;
    };

/**
*  This class is for dynamically loading ProfilesSettingsView.dll that 
*  enables setting of ringing tone for all profiles.
*
*  @lib PslnProfileSettingsLoader.lib
*  @since Series 60 3.1
*/
class CPslnProfileSettingsLoader : public CBase, 
                                   public MPslnProfileSettingsLoader
    {
public:
    /**
    * Two-phased constructor.
    * @return new instance of CPslnProfileSettingsLoader.
    */
    static CPslnProfileSettingsLoader* NewL();

    /**
    * Destructor.
    */
    virtual ~CPslnProfileSettingsLoader();

    /**
    * Sets tone for all profiles.
    * @param aType type of tone (actual ringing tone, or message alert tone).
    * @param aFullName full filename (inc. path) of tone.
    */
    void SetToneForProfilesL( TInt aType, TDes& aFullName );

    /**
    * Indicates to the media gallery that there is new sound file 
    * available in the gallery.
    * @param aFullPath path and file of the new sound file.
    */
    void IndicateFileUpdationL( const TDesC& aFullPath );

private:

    /**
    * C++ default constructor.
    */
    CPslnProfileSettingsLoader();
    
    /**
    * Stores the settings to Profiles Engine and adds the file to automated
    * content list and removes the old file from automated content list.
    * @param aProfileEngine The MProfileEngineExtended.
    * @param aProfileId The ID of the profile (NOT an index).
    * @param aType Identifies the tone which is updated.
    * @param aFileName Full path and filename of the tone to be used
    *                  as the new ringing or alert tone.
    */    
    void DoSetProfileToneL( MProfileEngineExtended* aProfileEngine, TInt aProfileId, 
    		TInt aType, const TDesC& aFileName );
    
    /**
    * Sets the tone to an MProfileExtended instance.
    * @param aProfile The MProfileExtended instance.
    * @param aType Identifies the tone which is updated.
    * @param aFileName The tone file name.
    */
    void SetToneL( MProfileExtended& aProfile,
    		TInt aType, const TDesC& aFileName );
    
    /**
    * Reads a tone setting from an MProfileExtended instance.
    * @param aProfile The MProfileExtended instance.
    * @param aType Identifies the tone which is read.
    * @return Returns the tone file name.
    */
    const TDesC& ToneL( MProfileExtended& aProfile,TInt aType );
    
    /**
    * Set Automated content
    * @param aDrmHelper Pointer to Drm helper.
    * @param aType Identifies the type the content.
    * @param aFileName Filename for the content.
    * @return Returns success/fail.
    */
    TInt SetAutomated( CDRMHelper* aDrmHelper,TInt aType,
    		const TDesC& aFileName );
    /**
    * Remove Automated content
    * @param aDrmHelper Pointer to Drm helper.
    * @param aFileName Filename for the content.
    */
    void RemoveAutomated( CDRMHelper* aDrmHelper,const TDesC& aFileName );

    
private:

#ifdef RD_CONTENTNOTIFICATION
    /**
    * Array of notification events.
    * Own.
    */
    CArrayFixFlat<CContentNotificationEvent*>* iEventArray;
#endif // RD_CONTENTNOTIFICATION
    };

// Environment gate function
IMPORT_C TAny* GateFunction();

#endif // C_PSLNPROFILESETTINGSLOADER

// End of File
