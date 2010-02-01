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

#ifndef __EIKSFONT_H__
#define __EIKSFONT_H__

/** Defines character codes for characters in the Eikon Symbol font.

@publishedPartner
@released */
enum TSymbolFontChars
	{
	/** Tick. */
	ESymFontTick					= 0x2713,
	/** Tab character. */
	ESymFontTabout					= 0xF6E3,
	/** 16-colour gray block, left-point */
	ESymFontGraySel16LeftPoint		= 0xF6E4,
	/** 16-colour gray block, right-point. */
	ESymFontGraySel16RightPoint		= 0xF6E5,
	/** 4-colour gray block, left-point. */
	ESymFontGraySel4				= 0xF6E6,
	/** Down left ear. */
	ESymFontDownLeftEar				= 0xF6E7,
	/** Down right ear. */
	ESymFontDownRightEar			= 0xF6E8,
	/** Up left ear. */
	ESymFontUpLeftEar				= 0xF6E9,
	/** Up right ear. */
	ESymFontUpRightEar				= 0xF6EA,
	/** Menu ellipsis. */
	ESymFontMenuEllipsis			= 0xF6EB,
	/** Menu cascade symbol. */
	ESymFontMenuCascade				= 0xF6EC,
	/** Scroll to bottom symbol. */
	ESymFontScrollToBottom			= 0xF6ED,
	/** Scroll to top symbol. */
	ESymFontScrollToTop				= 0xF6EE,
	/** Scroll to left-edge symbol. */
	ESymFontScrollToLeftEnd			= 0xF6EF,
	/** Scroll to right-edge symbol. */
	ESymFontScrollToRightEnd		= 0xF6F0,
	/** Scroll page down symbol. */
	ESymFontScrollPageDown			= 0xF6F1,
	/** Scroll page up symbol. */
	ESymFontScrollPageUp			= 0xF6F2,
	/** Scroll page left symbol. */
	ESymFontScrollPageLeft			= 0xF6F3,
	/** Scroll page right symbol. */
	ESymFontScrollPageRight			= 0xF6F4,
	/** Scroll down symbol. */
	ESymFontScrollDown				= 0xF6F5,
	/** Scroll up symbol. */
	ESymFontScrollUp				= 0xF6F6,
	/** Scroll left symbol. */
	ESymFontScrollLeft				= 0xF6F7,
	/** Scroll right symbol. */
	ESymFontScrollRight				= 0xF6F8,
	/** File browse A-Z symbol. */
	ESymFontFileBrowseOrderAToZ		= 0xF6F9,
	/** File browse by extension symbol. */
	ESymFontFileBrowseOrderByExt	= 0xF6FA,
	/** File browse by size symbol. */
	ESymFontFileBrowseOrderBySize	= 0xF6FB,
	/** File browse by date symbol. */
	ESymFontFileBrowseOrderByDate	= 0xF6FC
	};


#endif
