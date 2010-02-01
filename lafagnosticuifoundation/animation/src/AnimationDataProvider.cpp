// Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "AnimationDataProvider.h"
#include "AnimationMixins.h"


/**
Constructor
*/
EXPORT_C CAnimationDataProvider::CAnimationDataProvider()  
	{	
 	}

/**
Sets the destination for data from this data provider.

You do not need to call this function unless you are writing a new animation
type.

@param aObserver The destination to send data to. Usually an animation class.
*/
EXPORT_C void CAnimationDataProvider::SetObserver(MAnimationDataProviderObserver* aObserver)
	{
	iObserver = aObserver;
	}

/**
Sends an event with no associated data to the observer.

See SendEventL(TInt,TAny*,TInt) for further details.
@param aEvent The event to pass.  This may be a member of TAnimationEvent, or a
user defined value.  User defined events must be greater than EAnimationReservedEvents
*/
EXPORT_C void CAnimationDataProvider::SendEventL(TInt aEvent)
	{
	iObserver->DataProviderEventL(aEvent, 0, 0);
	}

/**
Sends an event with a single integer data item to the observer.

See SendEventL(TInt,TAny*,TInt) for further details.
@param aEvent The event to pass.  This may be a member of TAnimationEvent, or a
user defined value.  User defined events must be greater than EAnimationReservedEvents
@param aData A pointer to the data to send
*/
EXPORT_C void CAnimationDataProvider::SendEventL(TInt aEvent, TInt aData)
	{
	iObserver->DataProviderEventL(aEvent, &aData, sizeof(TInt));
	}

/**
Sends an event with an arbitrary size data item to the observer.
 
@see TAnimationEvent
@param aEvent The event to pass.  This may be a member of TAnimationEvent, or a
user defined value.  User defined events must be greater than EAnimationReservedEvents
@param aData A pointer to the data to send
@param aDataSize The size of the data item passed in aData
*/
EXPORT_C void CAnimationDataProvider::SendEventL(TInt aEvent, TAny* aData, TInt aDataSize)
	{
	iObserver->DataProviderEventL(aEvent, aData, aDataSize);
	}

/** Reserved for future use */
EXPORT_C void CAnimationDataProvider::CAnimationDataProvider_Reserved1() { }

/** Reserved for future use */
EXPORT_C void CAnimationDataProvider::CAnimationDataProvider_Reserved2() { }

/** Reserved for future use */
EXPORT_C void MAnimationDataProviderObserver::MAnimationDataProviderObserver_Reserved1()
	{
	}

/** Reserved for future use */
EXPORT_C void MAnimationDataProviderObserver::MAnimationDataProviderObserver_Reserved2()
	{
	}

/** Reserved for future use */
EXPORT_C void MAnimationDrawer::MAnimationDrawer_Reserved1()
	{
	}

/** Reserved for future use */
EXPORT_C void MAnimationDrawer::MAnimationDrawer_Reserved2()
	{
	}

/** Reserved for future use */
EXPORT_C void MAnimationObserver::MAnimationObserver_Reserved1()
	{
	}

/** Reserved for future use */
EXPORT_C void MAnimationObserver::MAnimationObserver_Reserved2()
	{
	}

/** Reserved for future use */
EXPORT_C void MAnimationTickee::MAnimationTickee_Reserved1()
	{
	}

/** Reserved for future use */
EXPORT_C void MAnimationTickee::MAnimationTickee_Reserved2()
	{
	}
