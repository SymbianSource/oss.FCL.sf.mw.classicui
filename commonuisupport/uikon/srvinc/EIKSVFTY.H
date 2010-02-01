// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
// Standard factory definitions
// 
//

#ifndef __EIKSVFTY_H__
#define __EIKSVFTY_H__

// System includes
#include <e32base.h>

#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eiknotifyalert.h>
#endif

class MEikSrvNotifierBase2;

/** Creates an interface object to a plug-in server side notifier.

@publishedAll
@released
*/
typedef CArrayPtr<MEikSrvNotifierBase2>* (*CreateEikSrvNotifierBase)();

#endif	// __EIKSVFTY_H__
