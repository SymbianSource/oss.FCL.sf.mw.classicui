/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __LAFPANIC_H__
#define __LAFPANIC_H__

/** Panic codes used throughout the code in Avkon library.
  * These panics have a category of EIKON or EikCoCtlLaf.
  */
enum TLafPanic
	{
	/** 00: Invalid pointer cursor index used. */
	ELafPanicPointerCursorIndexOutOfRange,
	/** 01: Invalid font index used in menu. */
	ELafPanicFontIndexOutOfRange,
	/** 02: Invalid constant used. */
	ELafPanicConstantNotKnown,
	/** 03: Invalid horizontal alignment constant used. */
	ELafPanicMsgWinBadHorizontalAlignment,
	/** 04: Invalid vertical alignment constant used. */
	ELafPanicMsgWinBadVerticalAlignment,
	/** 05: Bitmap index out of range. */
	ELafPanicBitmapIndexOutOfRange,
	/** 06: @deprecated */
	ELafPanicNotificationWithoutRequest,
	/** 07: Invalid logical font category used. */
    ELafPanicFontUidUnknownOrMissing,
	/** 08: APAC font requested in western variant. */
    ELafPanicUsingFontFromWrongVariant,
	/** 09: Font creation failure. */
    ELafPanicFontCreationFailure
	};

#endif //__LAFPANIC_H__

// End of file.
