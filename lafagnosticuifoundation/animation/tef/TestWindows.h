// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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

/**
 @file
 @internalComponent - Internal Symbian test code 
*/

#ifndef __TESTWINDOWS_H__
#define __TESTWINDOWS_H__

#include <e32base.h>

class TWsEvent;
class TWsRedrawEvent;
class RWindowTreeNode;
class RWindow;
class RWindowGroup;
class RWsSession;
class CWindowGc;

class CTestWindowTreeNode : public CBase
	{
public:
	virtual void EventL(TWsEvent & aEvent) = 0;
	virtual void RedrawL(TWsRedrawEvent & aEvent) = 0;
	virtual RWindowTreeNode* WindowTreeNode() 	{ return iWin; }
protected:
	RWindowTreeNode* iWin;
	};

class CTestWindowGroup : public CTestWindowTreeNode
	{
public:
	CTestWindowGroup(RWsSession & aWs);
	~CTestWindowGroup();
	void EventL(TWsEvent & aEvent);
	void RedrawL(TWsRedrawEvent & aEvent);
	RWindowGroup* WindowGroup() { return reinterpret_cast<RWindowGroup*>(iWin); }
	};

class CTestWindow : public CTestWindowTreeNode
	{
public:
	CTestWindow(RWsSession& aWs, CTestWindowGroup& aGroup, CWindowGc& aGc);
	~CTestWindow();
	void EventL(TWsEvent & aEvent);
	void RedrawL(TWsRedrawEvent & aEvent);
	RWindow* Window() { return reinterpret_cast<RWindow*>(iWin); }
	virtual void DrawL();
protected:
	CWindowGc& iGc;
	};

#endif //__TESTWINDOWS_H__
