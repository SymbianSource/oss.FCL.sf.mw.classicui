// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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

/**
 @file
 @internalComponent - Internal Symbian test code 
*/

#if !defined(__TMENUASI_H__)
#define __TMENUASI_H__

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

enum TMenuAsiEventSend
	{
	ESendCountWindows=EEventUser+1,
	ESendAddWindow,
	ESendRemoveWindow
	};

enum TMenuAsiEventReply
	{
	EReplyWindowAdded=EEventUser+1,
	EReplyFailedToAddWindow,
	EReplyWindowRemoved,
	EReplyNoWindowToRemove,
	EReplyWindowsCounted
	};

enum TMessageControlFontStyle
    {
    EStyleElementBold,
    EStyleElementItalic,
    EStyleElementUnderline,
    EStyleElementStrikethrough
    };

#define TMenu1GroupName _L("TMenu1GroupName")

#endif
