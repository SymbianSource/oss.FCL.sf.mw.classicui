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

#ifndef __COEFEP_H__
#define __COEFEP_H__

#include <e32base.h>	// class CActive

class CCoeEnv;
class CRepository;

/**
The CCoeFepLoader class implements a FEP loader for internal use by Cone. It loads the
front-end processor in a high-priority active object which is run as soon as the active-scheduler
starts. This enables the front-end processor to be set up before it is loaded.

@internalTechnology
*/
class CCoeFepLoader : public CActive
	{
public:
	static CCoeFepLoader* NewL(CCoeEnv& aCoeEnv, CCoeFepLoader*& aOwner);
	virtual ~CCoeFepLoader();
private:
	CCoeFepLoader(CCoeEnv& aCoeEnv, CCoeFepLoader*& aOwner);
	// from CActive
	virtual void DoCancel();
	virtual void RunL();
	virtual TInt RunError(TInt aError);
private:
	CCoeEnv& iCoeEnv;
	CCoeFepLoader*& iOwner;
	TBool iFirstRunL;
	};


/**
The CCoeFepTracker class implements a FEP tracker for internal use by Cone. It enables
the front-end processors in the system to be re-loaded when a new one is installed.

@internalTechnology
*/
NONSHARABLE_CLASS(CCoeFepTracker) : public CActive
	{
public:
	static CCoeFepTracker* NewL(CCoeEnv& aCoeEnv);
	virtual ~CCoeFepTracker();
private:
	CCoeFepTracker(CCoeEnv& aCoeEnv, CRepository& aRepository);
	void ConstructL();
	void Queue();
	virtual void DoCancel();
	virtual void RunL();
private:
	CCoeEnv& iCoeEnv;
	CRepository& iRepository;
	};

/**
The old FEP architecture identifies FEP implementations by the file name of the
polymorphic DLL that implements them. The new secure FEP architecture uses ECom
and identifies FEP implementations by their ECom implementation UID.

This class provides a common representation for uniquely identifying a FEP and
determining its type. This enables both types of FEP to be used in the system
at the same time.
This representation is used when storing the current FEP in the ini file, and
when sending the window group message notifying all apps of a change in FEP.

@internalTechnology
*/
class FepName
	{
public:
	static TUid UidFromNameL(const TDesC& aName);
	static void NameFromUid(TDes& aName, const TUid& aUid);
	};

#endif // __COEFEP_H__