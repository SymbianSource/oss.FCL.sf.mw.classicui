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

#ifndef __LAFAPPUI_H__
#define __LAFAPPUI_H__

#include <e32std.h>
#include <lafmain.h>

class CCoeEnv;
struct TPointerEvent;


class LafAppUi
/** Application UI level LAF support. 

@publishedPartner 
@released */
	{
public:
	/** Tests whether to attempt to fade all windows of an application when that application's 
	window group moves into the background.
	
	@return True to fade, otherwise false */
	IMPORT_C static TBool FadeWhenInBackground();
	/** Adjusts a screen rectangle to allow room for any other applications that should 
	always be visible.
	
	@param aRect Pass in the rectangle to adjust; on return, the adjusted rectangle */
	IMPORT_C static void ReduceRect(TRect& aRect);
	/** Tests if bubble help should be cancelled due to a specified pointer event.
	
	This is called when processing a window server event in the AppUi.
	
	@param aEvent Pointer event
	@return True if bubble help should be cancelled */
	IMPORT_C static TBool CancelBubbleHelpOnEvent(const TPointerEvent& aEvent);
	/** Gets the screen area available to a specified client application.
	
	The screen area should exclude screen furniture such as menu bars and status 
	panes.
	
	@param aEnv Application's control environment
	@param aClientRectResolver Object that works out how screen furniture reduces 
	the available screen area 
	@return Available screen area */
	IMPORT_C static TRect ClientRect(const CCoeEnv& aEnv,const MLafClientRectResolver& aClientRectResolver);
	};

#endif //__LAFAPPUI_H__
