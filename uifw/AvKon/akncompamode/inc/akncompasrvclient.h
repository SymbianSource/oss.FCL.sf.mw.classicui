/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Client interface to CompaKeyServ
*
*/


#ifndef __AKNCOMPAKEYCLIENT_H__
#define __AKNCOMPAKEYCLIENT_H__

#include <e32base.h>
#include <w32std.h>

/**
 * Client session to AknCompaSrv
 *
 * The component is used by compa-keyboard to simulate key events
 *
 * @since S60 v5.0
 */
NONSHARABLE_CLASS(RAknCompaSrvSession) : public RSessionBase
    {
public:

    TInt Connect();
    TVersion Version() const;

    // Services
    void SimulateKeyEventL(TInt aScanCode, TBool aKeyDown);
    TInt DisaTransEffects();
    TInt RestoreTransEffects();
    };

#endif // __AKNCOMPAKEYCLIENT_H__
