/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Interface to product layout configuration data,
*               which is independent of the source of the configuration data.
*
*/


#ifndef AKNLAYOUTCONFIG_H
#define AKNLAYOUTCONFIG_H

#include <w32std.h>
#include <AknPriv.hrh>
#include <AknScreenMode.h>

class CResourceFile;
struct SHardwareStateInfo;

/**
*  Layout configuration data
*
*  @since Series 60 3.0
*/
NONSHARABLE_CLASS(CAknLayoutConfig) : public CBase
	{
public:
	// Forward declared structures and T-class wrappers gives
	// a handle body pattern that should allow maximum extensibility
	// of the layout configuration data.
	// Note: never add member data directly to these T-classes.
	// if new member data is required, add it to the coresponding
	// structs.
	
	/**
	* Information about a screen mode
	*/
	class TScreenMode : public TAknScreenMode
		{
	public:
		/**
		* Gets the Pixels, Twips and Rotation for this screen mode.
		* @return The Pixels, Twips and Rotation.
		*/
		IMPORT_C const TPixelsTwipsAndRotation& PixelsTwipsAndRotation() const;
		/**
		* The location of the softkeys relative to the screen
		* in this screen mode.
		* @return the softkey location
		*/
		IMPORT_C TAknPrivSoftkeyLocation SoftkeyLocation() const;
		/**
		* A number identifying the screen style for this screen mode.
		* @return a hash of the screen style string
		*/
		IMPORT_C TInt ScreenStyleHash() const;
	public:
		/**
		* Constructor.
		*/
		TScreenMode(const SAknScreenModeInfo& aInfo);
		};
	
	/**
	* An array of all available screen modes.
	*/
	class TScreenModeArray : public TAknScreenModes
		{
	public:
		/**
		* Get a screen mode by index
		* @param aIndex the array index number
		* @return The screen mode.
		*/
		IMPORT_C TScreenMode At(TInt aIndex) const;
		/**
		* Get a screen mode by mode number
		* @param aModeNumber the mode number of the screen mode to find
		* @return The screen mode with that mode number, 
		*         or the first screen mode if none is found.
		*/
		IMPORT_C TScreenMode Find(TInt aModeNumber) const;
	public:
		/**
		* Constructor.
		*/
		TScreenModeArray(const SAknLayoutConfig& aInfo);
		};
	
	/**
	* Information about a hardware state.
	*/
	class THardwareState
		{
	public:
		/**
		* The state number of the hardware state.
		* @return The state number.
		*/
		IMPORT_C TInt StateNumber() const;
		/**
		* The keycode which identifies activation of this hardware state.
		* @return the keycode value.
		*/
		IMPORT_C TInt KeyCode() const;
		/**
		* The screen mode number that should be used in this hardware state.
		* @return The screen mode number.
		*/
		IMPORT_C TInt ScreenMode() const;
		/**
		* The screen mode number to use for applications that need the
		* other orientation than provided by @c ScreenMode().
		* @return The alternate screen mode number.
		*/
		IMPORT_C TInt AlternateScreenMode() const;
	public:
		/**
		* Constructor.
		*/
		THardwareState(const SHardwareStateInfo& aInfo);
	private:
		const SHardwareStateInfo& iInfo;
		};
	
	/**
	* An array of available hardware states.
	*/
	class THardwareStateArray
		{
	public:
		/**
		* @return The number of hardware states in the array.
		*/
		IMPORT_C TInt Count() const;
		/**
		* Get a hardware state by index
		* @param aIndex the array index number
		* @return The hardware state.
		*/
		IMPORT_C THardwareState At(TInt aIndex) const;
		/**
		* Get a hardware state by state number
		* @param aStateNumber the state number of the hardware state to find
		* @return The hardware state with that state number, 
		*         or the first hardware state if none is found.
		*/
		IMPORT_C THardwareState Find(TInt aStateNumber) const;
	public:
		/**
		* Constructor.
		*/
		THardwareStateArray(const SAknLayoutConfig& aInfo);
	private:
		const SAknLayoutConfig& iInfo;
		};
		
public:
	/**
	* Factory Function
	*
	* This factory function should only be used in non-UI processes.
	* In a process, such as an app, where the Avkon environment exists, an instance of
	* CAknLayoutConfig can be obtained from CAknSgcClient::LayoutConfig().
	*
	* @return a new instance of CAknLayoutConfig.
	*/
	IMPORT_C static CAknLayoutConfig* NewL();
	
public:
	/**
	* @return An array of the available hardware states.
	*/
	IMPORT_C THardwareStateArray HardwareStates() const;
	/**
	* @return An array of the available screen modes.
	*/
	IMPORT_C TScreenModeArray ScreenModes() const;

public:
	// Non-exported framework only API
	/**
	* Constructor.
	*/
	CAknLayoutConfig();
	/**
	* Destructor.
	*/
	~CAknLayoutConfig();
	/**
	* Second stage constructor.
	* @param aBuf a descriptor of containing packed layout configuration data.
	*		 Ownership of aBuf is transferred immediately when called, so caller
	*        should release ownership of aBuf before calling.
	*/
	void ConstructL(HBufC8* aBuf);	// takes ownership of aBuf immediately
	/**
	* Create a descriptor containing packed layout configuration data.
	* @return a descriptor containing packed layout configuration data.
	*/
	HBufC8* CreatePackedBufL();
	
private:
	void GetConfigL(SAknLayoutConfig& aConfig, 
					RArray<SAknScreenModeInfo>& aScreenInfoArray, 
					RArray<SHardwareStateInfo>& aHardwareStateArray);
	void GetScreenMapFromAknPrivL(CResourceFile* aResFile,
								  RArray<SAknScreenModeInfo>& aScreenInfoArray, 
								  RArray<SHardwareStateInfo>& aHardwareStateArray);
	void GetKeyMapFromAknPrivL(CResourceFile* aResFile,
							   RArray<SHardwareStateInfo>& aHardwareStateArray);
	TAknPrivSoftkeyLocation GetLandscapeSoftkeyLocationFromAknPrivL(CResourceFile* aResFile);
	void GetScreenModesFromWservL(SAknLayoutConfig& aConfig,
								  RArray<SAknScreenModeInfo>& aScreenInfoArray, 
								  TAknPrivSoftkeyLocation aLandscapeSoftkeyLocation);
private:
	HBufC8* iBuf;				// owned
	SAknLayoutConfig* iData;	// not owned
	};

#endif
