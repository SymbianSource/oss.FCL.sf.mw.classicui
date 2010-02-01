/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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


#include <uiklaf/private/lafvcurs.h>
#include <w32std.h>


/**
 * This function returns an enum of the type TPointerCursorMode,
 * which describes the mode that should be used when the virtual
 * cursor is switched on. The return value has no effect for devices
 * not using a virtual cursor.
 *
 */
EXPORT_C TPointerCursorMode LafVirtualCursor::PointerCursorOnMode()
	{//static
	return EPointerCursorNormal;
	}


