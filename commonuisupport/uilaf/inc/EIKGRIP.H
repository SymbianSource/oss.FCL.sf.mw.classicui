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

#if !defined(__EIKGRIP_H__)
#define __EIKGRIP_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

class CGraphicsContext;

class TEikGrip
	{
public:
	enum TOrientation {EHorizontal=0x00,EVertical=0x01};
public:
	inline TEikGrip(TOrientation aOrientation=EHorizontal);
	void Draw(CGraphicsContext& aGc, const TRect& aRect) const;
	inline void SetOrientation(TOrientation aOrientation);
	inline TOrientation Orientation() const;
private:
	TInt iData;
	};

#include <eikgrip.inl>
#endif
