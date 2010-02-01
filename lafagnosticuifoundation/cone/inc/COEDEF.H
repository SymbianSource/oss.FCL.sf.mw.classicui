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

#ifndef __COEDEF_H__
#define __COEDEF_H__

#include <e32std.h> 
#include <guldef.h> // only requried for limited source compatability with releases prior to 250






#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <graphics/cone/coedefkeys.h>
#endif //SYMBIAN_ENABLE_SPLIT_HEADERS

/**

@publishedAll
@released */
const TInt KCoeCustomColorsArrayValue=0x100057C2;
/**

@publishedAll
@released */
const TInt KCoeColorGray4=0x19bd6002;

/**

@publishedAll
@released */
const TInt KCoeColorColor16=0x19bd6003;

/**

@publishedAll
@released */
const TInt ECoeResourceSignatureValue=4;


/** Event handling flags. 

These should be returned by CCoeControl::OfferKeyEventL() to indicate whether 
or not a key event was processed by the control. 

@publishedAll
@released */
enum TKeyResponse
	{
	/** The key event was not handled. */
	EKeyWasNotConsumed,
	/** The key event was handled. */
	EKeyWasConsumed
	};

/** Control redraw flags. 

Passed to CCoeControl::SetFocus() to indicate the requirements for control 
redrawing. 

@publishedAll
@released */
enum TDrawNow
	{
	/** Redraw of the control is not required immediately. */
	ENoDrawNow,
	/** Redraw control immediately. */
	EDrawNow
	};

/** Window priority values. 

These are passed in the aOrdinalPriority argument to RWindowTreeNode::SetOrdinalPosition(). 

@publishedAll
@released */
enum TCoeWinPriority
	{
	/** -1000 */
	ECoeWinPriorityNeverAtFront		=-1000,
	/** -750 */
	ECoeWinPriorityLow				=-750,
	/** 0 */
	ECoeWinPriorityNormal			=0,
	/** 500 */
	ECoeWinPriorityMedium			=500,
	/** 750 */
	ECoeWinPriorityHigh				=750,
	/** 900 */
	ECoeWinPriorityFep				=900,
	/** 1000 */
	ECoeWinPriorityAlwaysAtFront	=1000
	};

/** The message UID sent when a colour scheme change event occurs.
WARNING: Constants for internal use ONLY.  Compatibility is not guaranteed in future releases.
 */
const TInt KUidValueCoeColorSchemeChangeEvent	=0x100056C4;
const TInt KUidValueCoeZoomChangeEvent          =0x100057C3;
const TInt KUidValueCoeFontChangeEvent          =0x100057C4;

/** Control key modifier.

Key codes get changed when the Ctrl key modifier is pressed at the same time as the key . 
The CTRL macro is used to shift the key character appropriately.

Note: this is not an inline function since that can't be used as the case of a switch 
statement.
 
@publishedAll
@released */
#define CTRL(x) ((x)-'a'+1)

/** Constant that represents all standard keyboard modifier keys.

@publishedAll
@released */
#define EAllStdModifiers (EModifierFunc|EModifierCtrl|EModifierShift)

#endif	// __COEDEF_H__
