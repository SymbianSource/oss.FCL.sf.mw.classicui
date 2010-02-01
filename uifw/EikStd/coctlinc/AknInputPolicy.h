/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
#ifndef AKNINPUTPOLICY_H
#define AKNINPUTPOLICY_H

#include <e32base.h>

// forward declarations
class CEikEdwin;

class CAknInputPolicyManager : public CBase
	{
public:
	enum TEventType
		{
		ECMEventNull,
		ECMEventInitialise,
		ECMEventInlineEditUpdate,
		ECMEventInsertion,
		ECMEventDeletion,
		ECMEventNavigation
		};
public:
	/** 
	* 2 phase constructor
	*
	*/
	static CAknInputPolicyManager* NewL(CEikEdwin* aEdwin);

	/** 
	* Destructor
	*
	*/
	virtual ~CAknInputPolicyManager();

	/** 
	* Forwards externally generated events to the appropriate cursor
	* manager handler method
	*/
	void HandleInputPolicyManagerEventL(TEventType aEvent, TInt aData1 = 0, TAny* aData2 = NULL);

private:
	CAknInputPolicyManager(CEikEdwin* aEdwin);
	void ConstructL();

	void NormaliseCursorPositionFollowingDeleteL();
	void NormaliseCursorPositionFollowingNavigationL();
	void SetCursorUsingLanguageL();

private:
	// not owned
	CEikEdwin* iEdwin;
	};


#endif
