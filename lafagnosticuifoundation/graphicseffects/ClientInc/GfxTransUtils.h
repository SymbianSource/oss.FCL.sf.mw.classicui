// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
//

#ifndef __GFXTRANS_UTILS_H__
#define __GFXTRANS_UTILS_H__

#include <e32base.h>
//#include "debugprint.h"
/** 
panic with the GFXTRANS identifier
@internalComponent
*/
void Panic(const TInt aCode);


/** 
Tests whether the value is a 'legal' array index.  This is not a bounds check!
It does allow functions to return error values (such as KErrNotFound) rather than
array indices, and the easy clean testing of these.
@internalComponent
*/
inline bool IsValidIndex(const TInt aIndex)
	{
	return (0 <= aIndex);
	}

#endif // __GFXTRANS_UTILS_H__
