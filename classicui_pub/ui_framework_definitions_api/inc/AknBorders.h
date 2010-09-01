/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __AKNBORDERS_H__
#define __AKNBORDERS_H__

#include <e32std.h>

/** 
 * Border ids for Avkon extended TGulBorder.
 * Contains hard coded border definitions for different
 * dialogs.
 */
class AknBorderId
	{
public:
	enum TAknBorderId
		{
		/** Border id for notes and queries. */
		EAknBorderNotePopup = 0x800110,
		/** Border id for options menu. */
		EAknBorderMenuPopup,
		/** Border id for sub-menu of options menu. */
		EAknBorderMenuSubmenuPopup,
		/** Border id for notification popup. */
		EAknBorderNotificationPopup,
		/** Border id for grouped notification popup. */
		EAknBorderGroupedNotificationsPopup,
		/** Border id for character selection popup. */
		EAknBorderCharacterSelectionPopup,
		/** Border id for list query dialog. */		
		EAknBorderPopups,
		/** Border id for list query dialog with heading. */		
		EAknBorderPopupsWithHeading,
		/** End marker for Avkon borders. Not a real border type. */		
		EAknBorderMax
		};
	};


#endif //__AKNBORDERS_H__
