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
* Description: 
*
*
*/


#ifndef AKNTASKLIST_H
#define AKNTASKLIST_H

// INCLUDES

#include <w32std.h>
#include <apgtask.h>

// CLASS DECLARATION

/**
*  Class for finding out about running applications.
*  This class specialises in locating and identifying root applications,
*  those applications who do not have any parent window group.
*  It can be used along-side TApaTaskList.
*
*  @since Series 60 3.0
*/
class CAknTaskList : public CBase
	{
public:
    /**
    * Factory function
    * @param aWsSession an open session to the window server, often from CEikonEnv::WsSession()
    * @return a new fully constructed instance of CAknTaskList
    */
	IMPORT_C static CAknTaskList* NewL(RWsSession& aWsSession);
    /**
    * Factory function
    * @param aWsSession an open session to the window server, often from CEikonEnv::WsSession()
    * @return a new fully constructed instance of CAknTaskList, which is on the cleanup stack
    */
	IMPORT_C static CAknTaskList* NewLC(RWsSession& aWsSession);
    /**
    * Destructor.
    */
	IMPORT_C ~CAknTaskList();
	
	/**
	* Refresh the window group array
	*/
	IMPORT_C void UpdateListL();
	/**
	* Accessor for the window group array
	* @return an array containing the window groups of running applications.
	*/
	IMPORT_C const RArray<RWsSession::TWindowGroupChainInfo>& WgArray() const;

	/**
	* Find an application with the requested UID 3, which is running as a root application
	* @param aAppUid the UID 3 of the target application.
	* @return a TApaTask which refers to the running instance of the application.
	* if the application is not running, the TApaTask's Exists() function will return EFalse.
	*/	
	IMPORT_C TApaTask FindRootApp(TUid aAppUid) const;
	/**
	* Query whether an application's window group is running as a root application.
	* @param aWgId the window group identifier of the target application.
	* @return ETrue if this window group is running as a root window group.
	*/
	IMPORT_C TBool IsRootWindowGroup(TInt aWgId) const;
	
	/**
	* Find the parent window group. If there is no parent, 0 is returned.
	* @param aWgId the window group id that you want to find the parent of.
	* @return The window group id of the parent, or 0 if there is no parent.
	*/
	IMPORT_C TInt FindParentWgId(TInt aWgId) const;
	/**
	* Find the child window group. If there is no child, 0 is returned.
	* @param aWgId the window group id that you want to find the child of.
	* @return The window group id of the child, or 0 if there is no child.
	*/
	IMPORT_C TInt FindChildWgId(TInt aWgId) const;
	
private:
	CAknTaskList(RWsSession& aWsSession);
	void ConstructL();

private:
	RWsSession& iWs;
	RArray<RWsSession::TWindowGroupChainInfo> iWgs;
	};

#endif
