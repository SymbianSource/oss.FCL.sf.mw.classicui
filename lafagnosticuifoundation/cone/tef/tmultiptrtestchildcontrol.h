// Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __TMULTIPTRTESTCHILDCONTROL_H__
#define __TMULTIPTRTESTCHILDCONTROL_H__

#include "tmultiptrtestcontrol.h"
#include "tconemultiptrcompoundstep.h"


class CMultiPtrTestChildControl : public CMultiPtrTestControlBase
	{
public:
	CMultiPtrTestChildControl();
	~CMultiPtrTestChildControl();
	void ConstructL( const TDesC& aName );
	
	const TDesC& WhoAmI() const;
	// From CCoeControl
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);

	// From CMultiPtrTestControlBase
	void NotifyControlL( TInt aNotify );
	
	void SetAppUiCallback( TBool aCallback = ETrue );
	
protected:
	void WriteName( CWindowGc& aGc, const TDesC& aText ) const;
	void ConstructL();
	
private:
	void Draw(const TRect& aRect) const;

protected:
	HBufC* iName;
	TBool iDoAppUiCallback;
	
private:
    CFont* iFont;
    CConeMultiPtrCompoundTestAppUi* iAppUi;
	};   

#endif // __TMULTIPTRTESTCHILDCONTROL_H__
