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

#ifndef __EIKNOTAPI_H__
#define __EIKNOTAPI_H__

#include <e32std.h>
#include <e32base.h>
#include <f32file.h>

#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikscchange.h>
#endif

/** Defines the second Uid value for plug in notifier DLLs. 

@publishedAll
@released */
const TUid KUidNotifierPlugIn = {0x10005522}; 
const TUid KUidNotifierPlugInV2 = {0x101fdfae};

/**
@publishedAll
@released
*/
enum TEikNotExtStatus
	{
	EEikNotExtRequestCompleted = 0,
	EEikNotExtRequestQueued = 1
	};

/** A set of flags that define the capabilities of the notifier.

Capabilities are returned by calling MEikSrvNotifierBase2::NotifierCapabilites(). 

@publishedAll
@released */
enum TNotifierCapabilities
	{
	/** The notifier has no special capabilities. */
	ENoSpecialCapabilities			= 0x00000000,
	/** The notifier can handle a change to the screen device. */
	EScreenDeviceChangeSupported	= 0x00000001,
	};
	
/** 
Interface to allow notifiers to manage their own startup/shutdown.  This class is likely to be of most
interest to notifiers that observe engines using publically available APIs rather than those that are run
via RNotifier.

@publishedAll
@released 
*/
class MEikSrvNotifierManager
	{
public:
	virtual void StartNotifierL(TUid aNotifierUid, const TDesC8& aBuffer, TDes8& aResponse) = 0;
	virtual void CancelNotifier(TUid aNotifierUid) = 0;
	virtual void UpdateNotifierL(TUid aNotifierUid, const TDesC8& aBuffer, TDes8& aResponse) = 0;
protected:
	IMPORT_C MEikSrvNotifierManager();
private:
	IMPORT_C virtual void MEikSrvNotifierManager_Reserved1();
	IMPORT_C virtual void MEikSrvNotifierManager_Reserved2();
private:
	TInt iMEikSrvNotifierManager_Spare1;
	};


/** Interface to a plug-in server side notifier.

Any number of MEikSrvNotifierBase2 objects can be included in a single DLL. 
All notifiers are loaded during device startup and are not destroyed until 
the Uikon server closes down.

All notifiers run in the uikon server thread so are able to directly access 
server side status panes but cannot call any functions on REikAppUiSession. 

@publishedAll
@released */
class MEikSrvNotifierBase2
	{
public:
	/** Defines a set of notifier priorities. The use and application of these values 
	is implementation-dependent. */
	enum TNotifierPriority
		{
		/** The highest priority value. */
		ENotifierPriorityAbsolute = 500,
		/** The second highest priority value. */
		ENotifierPriorityVHigh = 400,	
		/** The third highest priority value. */
		ENotifierPriorityHigh = 300,	
		/** The fourth highest priority value. */
		ENotifierPriorityLow = 200,	
		/** The fifth highest priority value. */
		ENotifierPriorityVLow = 100,	
		/** The lowest priority value. */
		ENotifierPriorityLowest = 0	
		};
public:
	/** Contains the notifier parameters.

	@see TNotifierPriority */
	class TNotifierInfo
		{
	public:
		/** The Uid that identifies the notifier. */
		TUid iUid;
		/** The Uid that identifies the channel to be used by the notifier (e.g. the screen, 
		an LED etc) */
		TUid iChannel;
		/** The notifier priority, typically chosen from the standard set.
	
		@see TNotifierPriority */
		TInt iPriority;
		};

public:
	IMPORT_C MEikSrvNotifierBase2();
	IMPORT_C virtual ~MEikSrvNotifierBase2();
public:
	/** Frees all resources owned by this notifier.
	
	This function is called by the notifier framework when all resources allocated 
	by notifiers should be freed. As a minimum, this function should delete this 
	object (i.e. delete this;).
	
	Note that it is important to implement this function correctly to avoid memory 
	leaks. */
	virtual void Release() = 0;
	/** Performs any initialisation that this notifier may require.
	
	The function is called when the notifier is loaded (when the plug-in DLL is 
	loaded). It is called only once.
	
	As a minimum, the function should return a TNotifierInfo instance describing 
	the notifier parameters. A good implementation would be to set this into a 
	data member, and then to return it. This is because the same information is 
	returned by Info().
	
	The function is safe to leave from, so it is possible, although rarely necessary, 
	to allocate objects as you would normally do in a ConstructL() function as 
	part of two-phase construction.
	
	@return Describes the parameters of the notifier. */
	virtual TNotifierInfo RegisterL() = 0;
	/** Gets the notifier parameters.
	
	This is usually the same information as returned by RegisterL() but can be 
	varied at run time.
	
	@return Describes the parameters of the notifier. */
	virtual TNotifierInfo Info() const = 0;
	/** Starts the notifier.
	
	This is called as a result of a client-side call to RNotifier::StartNotifier(), 
	which the client uses to start a notifier from which it does not expect a 
	response.
	
	The function is synchronous, but it should be implemented so that it completes 
	as soon as possible, allowing the notifier framework to enforce its priority 
	mechanism.
	
	It is not possible to to wait for a notifier to complete before returning 
	from this function unless the notifier is likely to finish implementing its 
	functionality immediately.
	
	@param aBuffer Data that can be passed from the client-side. The format and 
	meaning of any data is implementation dependent.
	@return A pointer descriptor representing data that may be returned. The format 
	and meaning of any data is implementation dependent. */
	virtual TPtrC8 StartL(const TDesC8& aBuffer) = 0;
	/** Starts the notifier.
	
	This is called as a result of a client-side call to the asynchronous function 
	RNotifier::StartNotifierAndGetResponse(). This means that the client is waiting, 
	asynchronously, for the notifier to tell the client that it has finished its 
	work.
	
	It is important to return from this function as soon as possible, and derived 
	classes may find it useful to take a copy of the reply-slot number and 
	the RMessage object.
	
	The implementation of a derived class must make sure that Complete() is called 
	on the RMessage object when the notifier is deactivated.
	
	This function may be called multiple times if more than one client starts 
	the notifier.
	
	@param aBuffer Data that can be passed from the client-side. The format and 
	meaning of any data is implementation dependent.
	@param aReplySlot Identifies which message argument to use for the reply.
    This message argument will refer to a modifiable descriptor, a TDes8 type, 
	into which data can be returned. The format and meaning of any returned data 
	is implementation dependent.
	@param aMessage Encapsulates a client request. */
	virtual void StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage) = 0;
	
	/** Cancels an active notifier.
	
	This is called as a result of a client-side call to RNotifier::CancelNotifier().
	
	An implementation should free any relevant resources and complete any outstanding 
	messages, if relevant. */
	virtual void Cancel() = 0;
	/** Updates a currently active notifier with new data.
	
	This is called as a result of a client-side call to RNotifier::UpdateNotifier().
	
	@param aBuffer Data that can be passed from the client-side. The format and 
	meaning of any data is implementation dependent.
	@return A pointer descriptor representing data that may be returned. The format 
	and meaning of any data is implementation dependent. */
	virtual TPtrC8 UpdateL(const TDesC8& aBuffer) = 0;
	/** Updates a currently active notifier with new data.
	
	This is called as a result of a client-side call to the asynchronous function 
	RNotifier::UpdateNotifierAndGetResponse(). This means that the client is waiting, 
	asynchronously, for the notifier to tell the client that it has finished its 
	work.
	
	It is important to return from this function as soon as possible, and derived 
	classes may find it useful to take a copy of the reply-slot number and 
	the RMessage object.
	
	The implementation of a derived class must make sure that Complete() is called 
	on the RMessage object when the notifier is deactivated.
	
	This function may be called multiple times if more than one client updates 
	the notifier.
	
	@param aBuffer Data that can be passed from the client-side. The format and 
	meaning of any data is implementation dependent.
	@param aReplySlot Identifies which message argument to use for the reply.
    This message argument will refer to a modifiable descriptor, a TDes8 type, 
	into which data can be returned. The format and meaning of any returned data 
	is implementation dependent.
	@param aMessage Encapsulates a client request. */
	IMPORT_C virtual void UpdateL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
public:
	void SetManager(MEikSrvNotifierManager* aManager);
protected:
	MEikSrvNotifierManager* iManager;
private:
	IMPORT_C virtual void MEikSrvNotifierBase2_Reserved_2();
public:	// internal
	IMPORT_C virtual void HandleSystemEventL(TUid aEvent);
	IMPORT_C virtual TInt NotifierCapabilites();
private:
	TInt iNotBSpare;
	TInt iMEikSrvNotifierBase2_Spare;
	};


#endif	// __EIKNOTAPI_H__
