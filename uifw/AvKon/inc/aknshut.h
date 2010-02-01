/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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

// EIKSHUT.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNSHUT_H__)
#define __AKNSHUT_H__

#include <e32base.h>
#include <w32std.h>

class CEikonEnv;
class CAknView;
class CAknAppUi;

NONSHARABLE_CLASS(CAknShutter) : public CActive
	{
public:
	void DeleteSelfWhenReady();
protected:
	CAknShutter(CEikonEnv& aEikEnv, CAknAppUi* aBaseAppUi);
	~CAknShutter();
	void Queue();
	static TInt StartLevel();
private: // virtual from CActive
	void DoCancel();
	void RunL();
	TInt RunError(TInt aError);
private:
	virtual TBool IsDisplayingMenuOrDialog() const = 0;
	virtual void SimulateKeyEventL(const TKeyEvent& aKeyEvent) = 0;
	virtual void StopDisplayingMenuBar() = 0;
	virtual void ExitL() = 0;
	virtual void Stop() = 0;
	void DeleteSelfIfSelfOwned();
private:
	enum TFlags
		{ETriedDismissMenu=0x01};
protected:
	CEikonEnv& iEikEnv;
	CAknAppUi* iBaseAppUi;
	TInt iStartLevel;
	TInt iCount;
	TBool iSelfOwned;
	};


NONSHARABLE_CLASS(CAknAppShutter) : public CAknShutter
	{
public:
	static CAknAppShutter* NewL(CEikonEnv& aEikEnv, CAknAppUi* aBaseAppUi, CAknAppShutter** aSelfPtr);		// aSelfPtr must be the address of a CAknAppShutter* in the heap
	void Start();
private:
	CAknAppShutter(CEikonEnv& aEikEnv, CAknAppUi* aBaseAppUi, CAknAppShutter** aSelfPtr);
	TBool IsDisplayingMenuOrDialog() const;
	void SimulateKeyEventL(const TKeyEvent& aKeyEvent);
	void StopDisplayingMenuBar();
	void ExitL();
	void Stop();
	void StopDisplayingToolbar();
private:
	CAknAppShutter** iSelfPtr;
	};


NONSHARABLE_CLASS(CAknViewShutter) : public CAknShutter
	{
public:
	~CAknViewShutter();
	static CAknViewShutter* NewL(CEikonEnv& aEikEnv, CAknAppUi* aBaseAppUi);
	void Start( const RPointerArray<CAknView>& aViews );
private:
	CAknViewShutter(CEikonEnv& aEikEnv, CAknAppUi* aBaseAppUi);
	TBool IsDisplayingMenuOrDialog() const;
	void SimulateKeyEventL(const TKeyEvent& aKeyEvent);
	void StopDisplayingMenuBar();
	void ExitL();
	void Stop();
private:
    RPointerArray<CAknView> iViews;
	};

#endif

