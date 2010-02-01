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

#ifndef __EIKCMOBS_H__
#define __EIKCMOBS_H__

#include <e32def.h>

class CCoeControl;

/** Command observers respond to user commands, and have the secondary function 
of creating custom controls on request for classes such as CEikToolbar, or 
user-defined classes.

An implementation of the pure virtual function ProcessCommandL() must be provided 
for each concrete class derived from MEikCommandObserver. CreateCustomCommandControlL() 
may also be re-implemented. 

@publishedAll 
@released */
class MEikCommandObserver
	{
public:
	/** Processes user commands.
	
	Derived classes must provide an implementation of this function which responds 
	to user commands appropriately based on a user-defined ID for the command.
	
	@param aCommandId ID of the command to respond to. */
	virtual void ProcessCommandL(TInt aCommandId)=0;
	/** Glue for creating custom controls.
	
	This function can be called to create custom controls on request from their 
	control ID. Custom controls are user-supplied control classes.
	
	Given the ID of a custom control, this function should return a pointer to 
	a newly-instantiated and fully constructed control. If the ID is unrecognised, 
	NULL should be returned. The control returned will be owned by the caller.
	
	@param aControlType A custom control ID. 
	@return By default, NULL. */
	IMPORT_C virtual CCoeControl* CreateCustomCommandControlL(TInt aControlType);
protected:
	IMPORT_C MEikCommandObserver();
private:
	IMPORT_C virtual void MEikCommandObserver_Reserved1();
	IMPORT_C virtual void MEikCommandObserver_Reserved2();
private:
	TInt iMEikCommandObserver_Reserved1;
	};

#endif	// __EIKCMOBS_H__
