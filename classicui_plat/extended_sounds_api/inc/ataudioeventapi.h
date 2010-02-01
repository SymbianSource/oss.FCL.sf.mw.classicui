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
* Description:  Client side application interface.
*
*/


#ifndef __ATAUDIOEVENTAPI_H__
#define __ATAUDIOEVENTAPI_H__

//  INCLUDES
#include <e32base.h>
#include <avkon.hrh>
#include "ataudioeventconstants.hrh" // TAudioThemeEvent, TATError

class RATSoundServerSession;
class MATEventCompleteObserver;
class CATMessageHelper;

/**
*  Implements client side API for Audio Theme sound server.
*
*  @lib ATSoundServerClient.lib
*  @since Series 60 release 3.0
*/
class CATAudioEventAPI : public CBase
	{
public:

	/**
    * Two-phased constructor.
    * @since 3.0
    * @param aClient reference to client object
    * @return A pointer to the created object
    */
	IMPORT_C static CATAudioEventAPI* NewL(MATEventCompleteObserver& aClient);

	/**
    * Two-phased constructor. Leaves pointer to object to cleanup stack.
    * @since 3.0
    * @param aClient reference to client object
    * @return A pointer to the created object
    */
	IMPORT_C static CATAudioEventAPI* NewLC(MATEventCompleteObserver& aClient);

	/**
	* Destructor
	*/
	~CATAudioEventAPI();

	/**
    * Send event to the server. UI Settings uses demoplay as true, so
    * that server will play "profile" events as well.
    * @since 3.0
    * @param aEvent event number
    *        aDemoPlay ETrue if called from UI settings application, EFalse from observer
    *                  and keysoundserver
    */
    virtual void SendAudioEventL(TAudioThemeEvent aEvent, TBool aDemoPlay);

	/**
    * Stop playing of earlier sent playing request.
    * @since 3.0
    * @param aEvent event number
    */
	virtual void StopAudio(TAudioThemeEvent aEvent);

	/**
    * This methods is called by message helper when sent messages completes.
    * Client will be called for completion in this method as well.
    * @since 3.0
    * @param aError error code
    * @param aHelper messagehelper that received completion from the server.
    */
	void MessageComplete(TInt aError, CATMessageHelper* aHelper);

private:

	/**
    * C++ default constructor.
    * @since 3.0
    * @param aClient reference to client object
	*/
	CATAudioEventAPI(MATEventCompleteObserver& aClient);

	/**
    * Symbian 2nd phase constructor.
    */
	void ConstructL();

private: // Data

	// Session to AT sound server
  	RATSoundServerSession* iSession; // Owned

	// Reference to client
  	MATEventCompleteObserver& iClient;

  	// Array for message helpers
  	RPointerArray<CATMessageHelper> iMessageHelperArray;

	};


#endif // __ATAUDIOEVENTAPI_H__

// End of File
