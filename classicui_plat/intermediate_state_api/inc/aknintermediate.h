/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:
*
*/

#ifndef __AKNINTERMEDIATE__
#define __AKNINTERMEDIATE__

/** Intermediate state
 *
 * To implement intermediate states:
 * 1) add iAvkonEnv->RegisterIntermediateState(this) to dialog's ActivateL()
 * 2) add iAvkonEnv->UnRegisterIntermediateState(this) to destructor
 * 3) derive your control from MAknIntermediateState.
 * 4) implement CloseState() method. It should call TryExitL() or something.
 * (NOTE, the method is NOT L-method, so use T_RAPD(err, TryExitL(buttonid));
 *
 * This will cause your intermediate states to close automatically when
 * you swap to another application.
 */

class MAknIntermediateState
    {
public:
    virtual void CloseState() = 0;
    };

#endif
