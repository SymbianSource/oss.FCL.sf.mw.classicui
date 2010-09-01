/*
* Copyright (c) 2004-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Background task for activating sounds in skin package.
*
*/


#ifndef C_PSLNTASKACTIVATESOUNDS_H
#define C_PSLNTASKACTIVATESOUNDS_H

#include <e32base.h>
#include <e32std.h>
#include <AknWaitNoteWrapper.h>

class CPslnSoundActivator;

/**
 *  Background task activator for activating sounds in skin package.
 *
 *  @since S60 v2.6
 */
class CPslnTaskActivateSounds : public CBase, public MAknBackgroundProcess
    {
public:

    /**
    * C++ constructor.
    * @param aActivator reference to sound activator.
    */
    CPslnTaskActivateSounds( CPslnSoundActivator& aActivator );

    /**
    * From MAknBackgroundProcess.
    * Return ETrue when the process is done.
    * @return ETrue if process is ready.
    */
    TBool IsProcessDone() const;

    /**
    * From MAknBackgroundProcess. 
    * Completes one cycle of the process.
    */
    void StepL();

private: // data

    /**
    * Has the task been done.
    */
    TBool iDone;

    /**
    * Reference to sound activator.
    */
    CPslnSoundActivator& iActivator;

public: // public data

    /**
    * Has an error occured.
    */
    TInt iActivationErr;
    };

#endif // C_PSLNTASKACTIVATESOUNDS_H
