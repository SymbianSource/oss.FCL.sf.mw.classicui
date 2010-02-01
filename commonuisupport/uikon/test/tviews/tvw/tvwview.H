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


#ifndef __TVWVIEW_H__
#define __TVWVIEW_H__

#include <vwsdef.h>
#include <coeview.h>
#include <coeaui.h>
#include <eikmobs.h>


//
// Forward declarations.
//

struct TKeyEvent;
enum TEventCode;
class TResourceReader;
class CEikonEnv;
class CTestVwAppUi;

class CTestVwAppView : public CBase, public MCoeView, public MEikMenuObserver
	{
public:
	 ~CTestVwAppView();
public:
	 void ActivateViewL(const TVwsViewId& aViewId);
	 void ActivateViewL(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC16& aCustomMessage);

	 CTestVwAppView* ActiveView() const;
	 TRect ClientRect() const;
	 void HandleResourceChangeL(TInt aType);
	 CTestVwAppUi& AppUi() const;
	 void AddToStackL(CCoeControl* aControl,TInt aPriority=ECoeStackPriorityDefault,TInt aStackingFlags=ECoeStackFlagStandard);
	 void RemoveFromStack(CCoeControl* aControl);
	 void UpdateStackedControlFlags(CCoeControl* aControl,TInt aFlags,TInt aMask);

	 virtual void HandleCommandL(TInt aCommand);
	 virtual void HandleModelChangeL();
public: // From MCoeView.
	 virtual TVwsViewId ViewId() const;
protected:
	 CTestVwAppView(const TVwsViewId& aViewId,CTestVwAppUi& aAppUi);
private: // New.
	friend class CTestVwAppUi;
	 virtual void DoActivateL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC16& aCustomMessage);
	 virtual void DoDeactivate();
	 virtual void DoActivateNarrowL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage);
private: // From MCoeView.
	 void ViewActivatedL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage);
	 void ViewDeactivated();
	 void ViewConstructL();
private: // From MEikCommandObserver.
	 void ProcessCommandL(TInt aCommand);
private: // From MEikMenuObserver.
	 void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);
private:
	CTestVwAppUi& iAppUi;
	TVwsViewId iViewId;
	};

#endif
// end of file
