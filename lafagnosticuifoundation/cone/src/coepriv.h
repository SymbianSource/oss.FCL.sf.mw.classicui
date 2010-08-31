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

#ifndef __COEPRIV_H__
#define __COEPRIV_H__

#include <e32base.h>
#include <w32std.h>
#include <coemain.h>
#include <coedef.h>
#include <coeaui.h>


class RWsSession;

/**
 * The CCoeRedrawer class implements an active monitor of redraw events from the
 * window server for internal use by Cone.
 *
 */ 
class CCoeRedrawer : public CActive
	{
public:
	CCoeRedrawer(RWsSession& aWsSession);
	~CCoeRedrawer();
private:
	void Queue();
	// from CActive
	virtual void RunL();
	virtual void DoCancel();
private:
	RWsSession& iWsSession;
	TBool iFirstRunL;
	};

class CCoeEnv;


/**
 * The CCoeView class encapsulates a view with its own control stack for use in internal view management.
 *
 */
class CCoeView : public CBase
	{
public:
	static CCoeView* NewLC(MCoeView& aView);
private:
	CCoeView(MCoeView& aView);
public:
	MCoeView& iView;
	TBool iConstructed;
	};


const TUid KUidTopViewId = {270559570};// as special command, i.e., hacking
#endif	// __COEPRIV_H__
