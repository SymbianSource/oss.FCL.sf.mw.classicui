/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Interface for controlling keysounds from Avkon.
*
*/

#ifndef __AKNSOUNDSYSTEM_H__
#define __AKNSOUNDSYSTEM_H__

// INCLUDES
#include <e32base.h>
#include <w32std.h>
#include <aknSoundinfo.h>

// FORWARD DECLARATIONS
class CAknSoundPlayer;
class CAknKeySoundStack;

// CLASS DECLARATION
/**
*  Interface for controlling keysounds from Avkon.
*  Provides support for handling key sounds.
*  @since S60 0.9
*/
NONSHARABLE_CLASS(CAknKeySoundSystem) : public CBase
    {
public:
    /**
    * Base class default constructor. If a client application is derived from @c CAknAppUi, 
    * its @c KeySounds() method should be used instead to obtain a key sound system instance.
    * If this method is used, the client needs explicitly call @c BringToForeground().
    *
    * @param aUid Application UID.
    * @return A pointer to a new @c CAknKeySoundSystem object.
    */
    IMPORT_C static CAknKeySoundSystem* NewL(TInt aUid);

    /**
    * Destructor.
    */
    IMPORT_C ~CAknKeySoundSystem();

    /**
    * Reads key sound context from resource file and pushes it to the sound stack.
    * All key presses for the application produce sounds as specified in this key sound context.
    * The resource specified must be of the @c AVKON_SKEY_LIST type. There are also some default
    * Avkon contexts available, e.g. @c R_AVKON_DEFAULT_SKEY_LIST and @c R_AVKON_SILENT_SKEY_LIST.
    *
    * @param aResourceId Key sound context resource ID.
    */
    IMPORT_C void PushContextL(TInt aResourceId);

    /**
    * Pops the top context from the key sound stack.
    */
    IMPORT_C void PopContext();

    /**
    * Plays a sound corresponding to the given key event. This is called directly by Avkon,
    * though it can be used in other circumstances in order to play the correct sound
    * associated with certain key presses.
    *
    * @param aKeyEvent The scan code of the key that caused the event.
    */
    IMPORT_C void PlaySound(const TKeyEvent& aKeyEvent);

    /**
    * Plays a sound corresponding to the given sound ID. The ID can be an application specific ID
    * or a system specific ID. System specific IDs are specified in Avkon enum @c TAvkonSystemSID.
    *
    * @param aSid Sound ID to be played.
    */
    IMPORT_C void PlaySound(TInt aSid);

    /**
    * Installs an application specific set of sound IDs. The specified resource ID must be
    * of the type @c AVKON_SOUND_INFO_LIST. The sound IDs contained in the resource are made
    * available for use in sound contexts within this application only. The method can only be
    * used to install a single application sound information list. Calling the method a
    * second time causes the previous sound information list to be replaced. Note also that
    * application specific SIDs should be less than 1000.
    *
    * @param aResourceId Avkon resource ID.
    */
    IMPORT_C void AddAppSoundInfoListL(TInt aResourceId);

    /**
    * This function brings the sounds back to foreground. This function should
    * be called from @c HandleForegroundEventL(). @c HandleForegroundEventL() is
    * implemented in @c CAknAppUi and it is reimplemented in @c CAknViewAppUi.
    * No need to call this function if using the @c KeySounds() method from @c CAknAppUi instead
    * of @c CAknKeySoundSystem::NewL(). In such case @c CAknAppUi calls this method automatically.
    */
    IMPORT_C void BringToForeground();

    /**
    * Stops playing the sound with given ID. Does nothing if a sound matching the ID is
    * not playing.
    *
    * @param aSid Sound ID to stop.
    */
    IMPORT_C void StopSound(TInt aSid);

    /**
    * Locks sound context, which prevents other instances from bringing their sound contexts
    * topmost. Only the first call is effective, i.e. if some other instance has already
    * locked its own context, the function does nothing. This is used in system components,
    * e.g. in key lock where key tones must be disabled while lock is active.
    */
    IMPORT_C void LockContext();

    /**
    * Releases the context lock. After calling this method, all instances can freely modify
    * their sound contexts again. The caller of the method can be some other instance than
    * the instance that locked the context.
    */
    IMPORT_C void ReleaseContext();

    /**
    * Reads sound information from given Avkon sound ID. This method is intended for applications
    * that need Avkon sound definitions for playing sounds with their own audio instances of
    * Multimedia Framework (such applications should not read Avkon resources as the resource
    * format can change without any notice but instead use this method).
    *
    * @since S60 2.0
    * @param aAvkonSid ID for Avkon sound whose information is requested.
    * @param aInfo Sound information will be put in this structure.
    * @return @c KErrNone if succesful, @c KErrNotFound if requested sound ID is not found.
    */
    IMPORT_C TInt RequestSoundInfoL(TInt aAvkonSid, CAknSoundInfo& aInfo);

    /**
    * Returns top context id from the session.
    *
    * @since S60 3.1
    * @return The resource id of the context that is at the top of the sound stack.
    */
    IMPORT_C TInt TopContext();

    /**
    * Disables next matching key sound until next pointer up event.
    *
    * @since S60 5.0
    * @param aScanCode ScanCode of key which sound is disabled.
    */
    void DisableNextKeySound(TInt aScanCode);

private:
    CAknKeySoundSystem();
    void ConstructL(TInt aUid);

private:
    CAknSoundPlayer* iSoundPlayer;
    TInt iSpare;
    };

#endif // __AKNSOUNDSYSTEM_H__

// End of file
