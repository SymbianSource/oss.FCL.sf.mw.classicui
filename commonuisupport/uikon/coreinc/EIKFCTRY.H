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
//

#ifndef __EIKFCTRY_H__
#define __EIKFCTRY_H__

#include <e32def.h>

#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikctrlstatus.h>
#endif

class CCoeControl;

/** Structure to hold the control specific information. It is used by 
EikControlFactory.

@see EikControlFactory
@publishedAll
@released
*/
struct SEikControlInfo
    {
    CCoeControl* iControl;
	TInt iTrailerTextId;
    TInt iFlags;
    };


/** Abstract factory that creates controls by type. 

This class provides a unified way to create controls according to the 
specified control integer ID. 

@publishedAll 
@released */
class EikControlFactory
	{
public:
    IMPORT_C static SEikControlInfo CreateByTypeL(TInt aControlType);
	};

/**
WARNING: typedef for internal use ONLY.  Compatibility is not guaranteed in future releases.
@publishedPartner
@released
*/
typedef SEikControlInfo (*TCreateByTypeFunction)(TInt);

#endif	// __EIKFCTRY_H__
