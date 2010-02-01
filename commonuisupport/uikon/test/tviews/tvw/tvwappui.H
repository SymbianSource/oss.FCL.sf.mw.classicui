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

#ifndef __TVWAPPUI_H__
#define __TVWAPPUI_H__

#include <eikappui.h>

#include "tvwview.H"


//
// CTestVwAppUi.
//

class CTestVwAppUi : public CEikAppUi
	{
public:
	 CTestVwAppUi();
	 ~CTestVwAppUi();
	 void ConstructL();
public:
	 void ActivateViewL(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC16& aCustomMessage);
	 void AddViewL(CTestVwAppView* aView);
	 void DeleteView(const TVwsViewId& aViewId);
	 CTestVwAppView* View(const TVwsViewId& aViewId) const;
	 CTestVwAppView* ActiveView() const;
private: // From CEikAppUi.
	 void HandleModelChangeL();
private:
	TInt AppViewIndex(const TVwsViewId& aViewId) const;
	TInt AppViewIndex(CTestVwAppView* aView) const;
private:
	CArrayPtrFlat<CTestVwAppView> iAppViewArray;
	};

#endif
