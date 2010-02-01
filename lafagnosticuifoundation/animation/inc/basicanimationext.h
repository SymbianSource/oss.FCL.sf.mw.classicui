// Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __BASICANIMATIONEXT_H__
#define __BASICANIMATIONEXT_H__

#include <e32base.h>


class CCoeControl;
/**
Extension class to allow CBasicAnimation to grow without breaking BC.
New data members may be added to CBasicAnimationExt.

@internalComponent
*/
NONSHARABLE_CLASS( CBasicAnimationExt ) : public CBase
	{
public:
	static CBasicAnimationExt* NewL( const CCoeControl* aHost );
	~CBasicAnimationExt();

private:
	CBasicAnimationExt( const CCoeControl* aHost );

public:
	const CCoeControl* iHost;
	};



#endif // __BASICANIMATIONEXT_H__
