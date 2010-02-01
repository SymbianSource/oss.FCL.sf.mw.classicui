/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined(__EIKDLGTB_H__)
#define __EIKDLGTB_H__

#if !defined(__EIKCTGRP_H__)
#include <eikctgrp.h>
#endif

#if !defined(__COECOBS_H__)
#include <coecobs.h>
#endif

class CCoeBrushAndPenContext;

class CEikDialogToolBar : public CEikControlGroup, private MCoeControlObserver
	{
public:
	IMPORT_C ~CEikDialogToolBar();
	IMPORT_C CEikDialogToolBar();
	IMPORT_C void BaseConstructL();
	IMPORT_C CCoeControl* StateChangeControl() const;
	IMPORT_C TInt StateChangeControlId() const;
public: // from CCoeControl
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
public: // from CEikControlGroup
	IMPORT_C void AddControlL(TEikGroupControl& aGroupControl);
private: // from MCoeControlObserver
	void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
private:
	CCoeControl* iStateChangeControl;
	CCoeBrushAndPenContext* iBrushAndPenContext;
	};



#endif
