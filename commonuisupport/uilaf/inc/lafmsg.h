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

#ifndef __LAFMSG_H__
#define __LAFMSG_H__

#include <e32std.h>
#include <clock.h>
#include <gulalign.h>
#include <coemain.h>
#include <lafmain.h>


class LafMsgWin
/** Provides LAF settings for the system environment's message windows (CEikMsgWin).

@publishedPartner
@released */
	{
public:
	class TDisplayParameters;
public:
	/** Sets the shadow on the blank window which the message is contained in. 
	
	@param aBlankWindow Message window */
	IMPORT_C static void SetUpBlankWindow(RBlankWindow& aBlankWindow);
	/** Completes the intitialisation of the message window.
	
	This function should select a font and call RMessageWindow::ConstructL() for 
	aMessageWin.
	
	@param aMessageWin Message window
	@param aEnv LAF environment functions */
	IMPORT_C static void CompleteMessageWinConstructionL(RMessageWindow& aMessageWin,const MLafEnv& aEnv);
	/** Handles a change to the system resources that may affect how the window is 
	displayed.
	
	The function should update aMessageWin appropriately.
	
	@param aMessageWin Message window
	@param aEnv LAF environment functions */
	IMPORT_C static void HandleResourceChange(RMessageWindow& aMessageWin,const MLafEnv& aEnv);
	/** Formats message text display.
	
	The function should truncate the text in aParams.iTextToDisplay to fit 
	the device display, and set aParms.iMsgWinSize and aParams.iMsgWinPosition 
	appropriately, depending on the corner aParams.iDisplayCorner, and the 
	font for the device.
	
	aParams.iClientRect is provided for devices that wish to set the position 
	relative to the client rect of the application rather than the screen rect.
	
	@param aParams Display parameters
	@param aEnv LAF environment functions */
	IMPORT_C static void ConfigureText(TDisplayParameters& aParams,const MLafEnv& aEnv);
	};


class LafMsgWin::TDisplayParameters
/** Holds message window text display parameters.

@publishedPartner
@released */
	{
public:
	/** Constructor. 

	@param aTextToDispay Message window text. */
	IMPORT_C TDisplayParameters(TDes& aTextToDispay);
public:
	/** Message window position. */
	TPoint iMsgWinPosition;
	/** Message window size. */
	TSize  iMsgWinSize;
	/** Message window text. */
	TDes&  iTextToDisplay;
	/** Message window margins. */
	TMargins iMsgWinBorders;
	/** Message window alignment. */
	TGulAlignment iDisplayCorner;
	/** Associated control environment. */
	CCoeEnv* iEnv;
	/** Message window client screen area. */
	TRect iClientRect;
	};


class LafInfoMsgWin
/** Provides LAF settings for the system environment's information message 
window (CEikonEnv::InfoMsg() etc.).

@publishedPartner
@released */
	{
public:
	/** Gets the default number of microseconds for which a message is displayed. 
	
	@return Default duration */
	IMPORT_C static TTimeIntervalMicroSeconds32 DefaultDuration();
	};


class LafBusyMsgWin
/** Provides LAF settings for the system environment's busy message window 
(CEikonEnv::BusyMsgL()).

@publishedPartner
@released */
	{
public:
	/** Gets the default number of microseconds for which a message is displayed. 
	
	@return Default delay */
	IMPORT_C static TTimeIntervalMicroSeconds32 DefaultInitialDelay();
	};

#endif //__LAFMSG_H__
