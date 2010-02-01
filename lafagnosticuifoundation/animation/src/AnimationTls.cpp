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

#include "AnimationTls.h"

#include <e32std.h>

#include "AnimationTicker.h"

/**
Two-stage constructor.

There is only ever one of these objects in existence.  The object is reference
counted, and is destroyed only when every call to NewL has been matched by a
call to Close.

@return The new object
*/
EXPORT_C CAnimationTls* CAnimationTls::NewL()
	{
	CAnimationTls* self = static_cast<CAnimationTls*>(Dll::Tls());
	if (!self)
		{
		self = new (ELeave) CAnimationTls();
		CleanupStack::PushL(self);
		self->iTimer = CAnimationTicker::NewL();
		CleanupStack::Pop(self);
		Dll::SetTls(self);
		}
	++(self->iRefCount);
	return self;
	}

/**
Decrements the reference counter for this object, and destroys it if the
reference count reaches 0.  This should be called once for every call to NewL.
*/
EXPORT_C void CAnimationTls::Close()
	{
	--iRefCount;
	if (iRefCount < 1)
		{
		Dll::FreeTls();
		delete this;
		}
	}

/**
Returns the CAnimationTicker object for this thread.
@return A pointer to the shared ticker object
*/
EXPORT_C CAnimationTicker* CAnimationTls::Ticker()
	{
	return iTimer;
	}

CAnimationTls::CAnimationTls()
	{
	}

CAnimationTls::~CAnimationTls()
	{
	delete iTimer;
	}

/** Reserved for future use */
EXPORT_C void CAnimationTls::CAnimationTls_Reserved1() {}

/** Reserved for future use */
EXPORT_C void CAnimationTls::CAnimationTls_Reserved2() {}
