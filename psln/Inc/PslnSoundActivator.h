/*
* Copyright (c) 2004-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Handles activation of sound files linked to skins.
*
*/


#ifndef PSLNSOUNDACTIVATOR_H
#define PSLNSOUNDACTIVATOR_H

#include <e32base.h>
#include <e32std.h>
#include <AknsItemID.h>

class CPslnProfileSettingsLoader;

// TYPE DEFINITIONS

// Struct containing sound activation data.
struct TPslnSoundActivatorEntry
    {
    // Filename for the audio file.
    TFileName iFullName;
    // Skin instance id.
    TAknsItemID iID;
    };

/**
* Class that handles the activation of sound files linked to skins.
*
* @since 2.5
*/
class CPslnSoundActivator : public CBase
    {
    public:
        
        /**
        * Two-phased constructor.
        * @return new instance of CPslnSoundActivator.
        */
        static CPslnSoundActivator* NewLC();
        
        /**
        * Destructor.
        */
        virtual ~CPslnSoundActivator();

        /**
        * Collects sound files of the current. Call to this method
        * must precede any other calls (except construction).
        * @param aSkinPath path to collect from.
        * @param number of sound files found.
        */
        void CollectSoundsL( const TDesC& aSkinPath, TInt& aCount );

        /**
        * Activates sound files into profiles.
        */
        void ActivateToProfilesL();

    private:

        /**
        * Symbian 2nd phase constructor can leave.
        */
        void ConstructL();

        /**
        * Find the complete filename of the given sound file.
        */
        void FindSoundFile( 
            TDes& aFullName, 
            const TDesC& aSoundFile, 
            const TDesC& aSkinPath );

        /**
        * Moves the sound files possibly in the skin directory.
        */
        void MoveSoundFilesL();

        /**
        * C++ default constructor.
        */
        CPslnSoundActivator();

    private: // Data

        /*
        * Array of sound activation entries.
        */
        RArray<TPslnSoundActivatorEntry> iSoundArray;

        /*
        * Has the Profiles Tone Settings DLL already been loaded.
        */
        TBool iProfilesDllLoaded;

        /*
        * A handle to a dynamically loadable DLL.
        */
        RLibrary iProfilesDll;

        /*
        * Loads Profiles Tone Settings DLL dynamically to memory.
        * Allows use of the DLL through this pointer, but only for
        * methods implemented within.
        * Own.
        */
        CPslnProfileSettingsLoader* iProfilesSetter;
    };

#endif // PSLNSOUNDACTIVATOR_H
            
// End of File
