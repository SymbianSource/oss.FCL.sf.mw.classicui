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

#ifndef __LAFSHUT_H__
#define __LAFSHUT_H__

#include <e32base.h>
#include <savenotf.h>
#include <shutdownsrv.h>


class CLafShutdownManagerBase : public CBase
/** Base class for a LAF shutdown manager.

A LAF implements a derived class to implement a policy on when to shutdown 
the device. The policy can involve listening for events, timers, etc.

@see LafShutdown 
@publishedPartner 
@released */
	{
protected:
	inline CLafShutdownManagerBase(MShutdownEventObserver& aObserver);
protected:
	/** Kernel's shutdown observer, initialised by the constructor. */
	MShutdownEventObserver& iObserver;
	};


class LafShutdown
/** Device shutdown LAF support.

@publishedPartner 
@released */
	{
public:
	/** Creates a shutdown manager.
	
	@param aObserver Provides a means for the LAF to notify the kernel of shutdown-related 
	events.
	@return Shutdown manager */
	IMPORT_C static CLafShutdownManagerBase* CreateShutdownManager(MShutdownEventObserver& aObserver);
	/** Tests if the current application should be asked to save when a view change 
	occurs.
	
	This is called when a view change occurs.
	
	@return Type of save (including none) that the application should perform
	@see CCoeAppUi::ActivateViewL()
	@see CEikDocument::SaveL() */
	IMPORT_C static MSaveObserver::TSaveType SaveFromViewSwitch();
	/** Tests if the current application should be asked to save when an application 
	switch occurs.
	
	This is called when an application switch occurs.
	
	@return Type of save (including none) that the application should perform */
	IMPORT_C static MSaveObserver::TSaveType SaveFromAppSwitch();
	};


inline CLafShutdownManagerBase::CLafShutdownManagerBase(MShutdownEventObserver& aObserver)
	: iObserver(aObserver)
/** Constructor.

@param aObserver Kernel's shutdown observer. The LAF can call this interface 
to notify the kernel of device shutdown, so that the kernel can take appropriate 
power management steps. */
	{}


#endif
