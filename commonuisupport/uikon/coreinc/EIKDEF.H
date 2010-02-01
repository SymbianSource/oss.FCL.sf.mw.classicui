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

#ifndef __EIKDEF_H__
#define __EIKDEF_H__

#include <e32std.h>
#include <coedef.h>

#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikdefconst.h>
#include <uikon/eikdefmacros.h>
#include <uikon/eikdefconstinternal.h>
#endif

/** This is used in combination with a specified position to place a popout on 
the display. 

The TPopupTargetPosType enum identifies which corner of the popout 
will be placed in the given target position. The default is the top left corner. 

@publishedAll
@released */
enum TPopupTargetPosType
	{
	/** Places the popout with the top left corner in the specified position. */
	EPopupTargetTopLeft,
	/** Places the popout with the top right corner in the specified position. */
	EPopupTargetTopRight,
	/** Places the popout with the bottom left corner in the specified position. */
	EPopupTargetBottomLeft,
	/** Places the popout with the bottom right corner in the specified position. */
	EPopupTargetBottomRight
	};


/** Defines the printer port settings. This is used by GUI print dialogs.*/
enum TEikPortFlag
	{
	/** Printing is via a serial port.*/
	ESerialPort = 0x01,
	/** Printing is via a parallel port.*/
	EParallelPort = 0x02,
	/** Printing is via infra red.*/
	EIrdaPort = 0x04,
	/** Printing is to a file. */
	EFilePort = 0x08,
	/** Printing is via a PC.*/
	EViaPCPort = 0x10
	};

/** Macro to allow easy access to the CEikonEnv instance.

@publishedAll
@released
*/
#define iEikonEnv (STATIC_CAST(CEikonEnv*,iCoeEnv))

/** Indicates that all windows should appear faded.

@publishedAll
@released
*/
const TInt KEikMessageFadeAllWindows			=0x100056C2;

/** Indicates that all windows should appear unfaded.

@publishedAll
@released
*/
const TInt KEikMessageUnfadeWindows				=0x100056C3;

/** Indicates that the colour scheme has changed.

@publishedAll
@released
*/
const TInt KEikMessageColorSchemeChange			=KUidValueCoeColorSchemeChangeEvent;

/** Indicates that the color scheme has changed.

@publishedAll
@released
*/
#define KEikColorResourceChange KEikMessageColorSchemeChange // for source compatibility

/** Indicates that the zoom level has changed.

@publishedAll
@released
*/
const TInt KEikMessageZoomChange				=KUidValueCoeZoomChangeEvent;

/** Indicates that a font has changed. Controls should ensure they are using 
the right font after receiving this message.

@publishedAll
@released
*/
const TInt KEikMessageFontChange     = KUidValueCoeFontChangeEvent;  

/** Indicates that the state of the virtual cursor has changed.

@publishedAll
@released
*/
const TInt KEikMessageVirtualCursorStateChange	=0x10005D0A;

/** Indicates that caps lock key has been pressed.

@publishedAll
@released
*/
const TInt KEikMessageCapsLock					=0x100048F9;

/** Indicates that the application should be ready to save any data that needs saving.

@publishedAll
@released
*/
const TInt KEikMessagePrepareForSave			=0x100069FD;

/** Indicates that the level of embedding of the application has changed.

@publishedAll
@released
*/
const TInt KEikMessageEmbedLevelChange			=0x1000A4AA;

/** Passed immediately after completion of the call to CCoeEnv::SetAppUi() 
when aNewAppUi has become current AppUi. This happens during the destruction of the embedded
AppUi.

@publishedAll 
@released
*/
const TInt KEikHasBecomeCurrentAppUiWhileEmbeddedAppUiDeletes = 0x10207F75;

/** Passed immediately before CEikAppUiFactory::CreateEmbeddedL()

@publishedAll 
@released
*/
const TInt KEikNotifyPreCreateEmbeddedL = 0x10207F67;

/** Passed immediately after CEikAppUiFactory::CreateEmbeddedL()

@publishedAll 
@released
*/
const TInt KEikNotifyPostCreateEmbeddedL = 0x10207F65;

/** Passed immediately after CCoeAppUi::ConstructL()

@publishedAll 
@released
*/
const TInt KEikPostCoeAppUiConstructL = 0x10207F66;

/**
@publishedAll
@released
*/
_LIT8(KDebugStart, "-DebugMemFail:");

/**
WARNING: constant for internal use ONLY.  Compatibility is not guaranteed in future releases.
*/
const TInt KEikCustomColorsArrayValue			=0x100057C2;


#endif	// __EIKDEF_H__
