/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#include <uiklaf/private/lafappui.h>
#include <coemain.h>
#include <w32std.h>
#include <AknLayout.lag>

/**
 * Determines whether to attempt to fade all app windows when an app's
 * window group moves into the background
 */
EXPORT_C TBool LafAppUi::FadeWhenInBackground()
	{ // static
	return EFalse;
	}

/**
 * Adjust aRect to allow room for any other apps that should always be visible
 */
EXPORT_C void LafAppUi::ReduceRect(TRect& /*aRect*/)
	{ // static
	}

/**
 * Returns ETrue if bubble help should be cancelled due to the pointer event aPointerEvent. Called when
 * processing a WServ event in the appUi.
 *
 * @since App-Framework_6.1
 */ 
EXPORT_C TBool LafAppUi::CancelBubbleHelpOnEvent(const TPointerEvent& /*aEvent*/)
	{ // static
	return EFalse;
	}

/**
 * Returns the client rect for this app thread.
 *
 * @since App-Framework_6.1
 */ 
EXPORT_C TRect LafAppUi::ClientRect(const CCoeEnv& /*aEnv*/,const MLafClientRectResolver& aClientRectResolver)
	{ // static
	TRect clientRect=TSize(AKN_LAYOUT_WINDOW_screen.iW,AKN_LAYOUT_WINDOW_screen.iH); //Ok so far. 'screen' layout is used.
	LafAppUi::ReduceRect(clientRect);
	aClientRectResolver.ReduceRect(MLafClientRectResolver::EStatusPane,clientRect);
	aClientRectResolver.ReduceRect(MLafClientRectResolver::ECba,clientRect);
	aClientRectResolver.ReduceRect(MLafClientRectResolver::EButtonGroup,clientRect);
	aClientRectResolver.ReduceRect(MLafClientRectResolver::EMenuBar,clientRect);
	aClientRectResolver.ReduceRect(MLafClientRectResolver::ETitleBand,clientRect);
	aClientRectResolver.ReduceRect(MLafClientRectResolver::EToolBand,clientRect);
	return clientRect;
	}
