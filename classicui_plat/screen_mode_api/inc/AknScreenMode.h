/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Interface to product screen mode data.
*
*
*/


#ifndef AKNSCREENMODE_H
#define AKNSCREENMODE_H

#include <w32std.h>

class CAknAppUiBase;
class SAknLayoutConfig;
class SAknScreenModeInfo;


/**
*  Information about a screen mode
*
*  @since 3.1
*/
class TAknScreenMode
    {
public:
    /**
    * Gets the size of the screen for this screen mode in pixels..
    * @return The screen size.
    */
    IMPORT_C TSize SizeInPixels() const;
    /**
    * Gets the display mode (color depth) for this screen mode.
    * @return The display mode.
    */
    IMPORT_C TDisplayMode DisplayMode() const;
	/**
	* Gets the screen mode number. This is the screen mode number
	* as used by @c CWsScreenDevice APIs, which start from zero.
	* It is one less than the number of the coresponding entry 
	* in wsini.ini, which start from one.
	* @return The screen mode number.
	*/
	IMPORT_C TInt ModeNumber() const;

public:
    TAknScreenMode(const SAknScreenModeInfo& aInfo);
    
protected:
    const SAknScreenModeInfo& iInfo;
    };


/**
*  TAknScreenModes is a collection of available screen 
*  modes on this device, with API for setting an application's
*  screen mode.
*
*  @since 3.1
*/
class TAknScreenModes
    {
public:
    /**
    * Factory function.
    * @return A constructed TAknScreenModes object.
    */
    IMPORT_C static TAknScreenModes GetModes();
    /**
    * Get the number of screen modes.
    * @return The number of screen modes.
    */
    IMPORT_C TInt Count() const;
    /**
    * Get screen mode information by index.
    * @param aIndex, the screen mode index, must be in the
    * range [0, Count()).
    * @return Information about a screen mode.
    */
    IMPORT_C TAknScreenMode operator[](TInt aIndex) const;
    /**
    * Set the screen mode for an application UI.
    * The application will be displayed in the selected
    * screen mode. The application will no longer respond to
    * hardware or software events which would normally affect
    * screen mode. It will be permanently fixed to the selected
    * screen mode.
    * By using this API, the application effectively declares
    * itself to be non-scalable.
    * Notifier dialogs and other non-full-screen UI will appear
    * in the selected screen mode when displayed over this app.
    * Other full-screen applications will not be affected by
    * this call, except in that switching between this app and
    * other apps using different screen modes will be slow.
    * The screen mode selected must be one returned through
    * the API of this class. There are no fixed screen modes
    * which will appear on every device. The emulator may
    * support many screen modes, but any particular device
    * will probably only support one or two modes.
    * Setting a screen mode may result in the application looking
    * low resolution, badly positioned, the wrong shape,
    * incorrect for certain hardware configurations (eg softkeys
    * in the wrong place), only taking up part of the screen,
    * other applications being visible behind it and generally
    * bad in many other ways.
    * It is strongly recommended that application authors write
    * their applications to be scalable, rather than use this API.
    * If an application wants a fixed orientation, it should use
    * @c CAknAppUiBase::SetOrientationL().
    * Note: this API has no effect on non-full-screen app UIs.
    * @param aAppUi The app UI.
    * @param aMode A screen mode accessed through this API.
    */
    IMPORT_C static void SetAppUiScreenModeL(CAknAppUiBase* aAppUi, const TAknScreenMode& aMode);

public:
    TAknScreenModes(const SAknLayoutConfig& aInfo);

protected:
    const SAknLayoutConfig& iInfo;
    };


#endif