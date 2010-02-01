// LAFVCURS.H
// Copyright (c) 2000-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __LAFVCURS_H__
#define __LAFVCURS_H__

#include <e32std.h>
#include <w32std.h>


class LafVirtualCursor
/** Virtual cursor LAF support.

@publishedPartner 
@released */
	{
public:
	/** Gets the mode that should be used when the virtual cursor is switched on. 
	
	The return value has no effect for devices not using a virtual cursor. 
	
	@return Cursor mode */
	IMPORT_C static TPointerCursorMode PointerCursorOnMode();
	};

#endif
