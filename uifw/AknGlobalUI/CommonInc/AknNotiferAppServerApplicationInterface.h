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
* Description:  
*
*/

#ifndef __AKNNOTIFIERSERVERAPPLICATIONINTERFACE__
#define __AKNNOTIFIERSERVERAPPLICATIONINTERFACE__

#include <e32std.h>

class MAknCapServerInterface
    {
public:
    virtual void SuppressAppSwitchingL(TInt aAddCount, TInt aClientId) = 0;
    };

#endif // __AKNNOTIFIERSERVERAPPLICATIONINTERFACE__
 