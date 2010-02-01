/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Observer class derived from MMdaAudioToneObserver.
*
*/

#ifndef __AKNEIKAUDIOTONEOBSERVER_H__
#define __AKNEIKAUDIOTONEOBSERVER_H__

// INCLUDES
#include <mdaaudiotoneplayer.h>  // base class

// FORWARD DECLARATIONS
class CEikSoundInfo;

// CLASS DECLARATION
/**
* Simple observer class for CAknToneSoundInfo and CAknSequenceSoundInfo.
*
* @lib eiksrvui.lib
* @since Series 60 3.0
*/
NONSHARABLE_CLASS(CAknEikAudioToneObserver) : public CBase, public MMdaAudioToneObserver
    {
public: // Constructors and destructors
    /**
    * Two-phased constructor.
    * @param aId The id of the observer.        
    * @param aKeySoundServer Reference to the key sound server instance.
    */
    static CAknEikAudioToneObserver* NewL(CEikSoundInfo& aSoundInfo);

    /**
     * Destructor.
     */
     virtual ~CAknEikAudioToneObserver();

private:        
    /**
    * C++ default constructor.
    * @param aId The id of the observer.            
    */
    CAknEikAudioToneObserver(CEikSoundInfo& aSoundInfo);

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
    * From MMdaAudioToneObserver
    */
    virtual void MatoPrepareComplete(TInt aError);

    /**
    * From MMdaAudioToneObserver
    */           
    virtual void MatoPlayComplete(TInt aError);

private: // Data
    CEikSoundInfo& iSoundInfo;
    };

#endif // __AKNEIKAUDIOTONEOBSERVER_H__

// End of File
