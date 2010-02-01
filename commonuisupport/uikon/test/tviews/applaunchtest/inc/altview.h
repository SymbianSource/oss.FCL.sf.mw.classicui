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

 
#ifndef altview_H 
#define altview_H 
 
#include <coecntrl.h>
#include <coeview.h>
#include <techview/eikclb.h>
#include <techview/eikchkbx.h>
#include <techview/eiklabel.h>
#include <eikspane.h>
#include "altmodel.h"

const TInt KMaxAppBufSize=256;

class CAltView : public CCoeControl, public MCoeView, public MAppListObserver, public MCoeControlObserver
	{
public:
	static CAltView* NewL(TRect& aRect, CAppLauncherModel* aModel);
	~CAltView();
	TVwsViewId ViewId() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	TInt CountComponentControls() const;
	void Draw( const TRect& aRect ) const;
public: //from maltmodelobserver
	void AppListChangedL();
public: //from mcoeview
	void ViewActivatedL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage);
	void ViewDeactivated();
public: //from mcoecontrolobserver
	virtual void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
private:
	CAltView();
	void ConstructL(TRect& aRect, CAppLauncherModel* aModel);
	void BuildVisibleStringL(TBuf<KMaxAppBufSize>& appString, TUid& aUid );
	void BuildAppListL();
private:
	CAppLauncherModel* iModel;
	CEikColumnListBox* iAppList;
	CEikCheckBox* iFilterChoice;
	CEikLabel* iFilterLabel;
	CEikStatusPane* iStatusPane;
	};

#endif 
