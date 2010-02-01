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

#ifndef __SPRITEANIMATIONEXT_H__
#define __SPRITEANIMATIONEXT_H__

#include <e32base.h>


/**
Extension class to allow CSpriteAnimation to grow without breaking BC.
New data members may be added to CSpriteAnimationExt.

@internalComponent
*/
NONSHARABLE_CLASS( CSpriteAnimationExt ) : public CBase
	{
public:
	static CSpriteAnimationExt* NewL( const TPoint& aPoint, const TDesC8& aDataType );
	~CSpriteAnimationExt();
	
private:
	CSpriteAnimationExt( const TPoint& aPoint, const TDesC8& aDataType );
	
public:
	TPoint iPoint;
	const TDesC8& iDataType;
	};
#endif // __SPRITEANIMATIONEXT_H__
