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

#ifndef __ANIMATIONDATAPROVIDER_H__
#define __ANIMATIONDATAPROVIDER_H__

#include <e32std.h>
#include <animationframe.h>

class MAnimationDataProviderObserver;

_LIT8(KUndefinedAnimationDataType, "undefined");

/**
Pure virtual base class for data providers.

A data provider takes an animation specification (such as a file), converts
it (if needed) into a format recognised by an animator (such as CAnimationFrame
objects), and passes it to the animator, via the medium of an animation.

Most animation types take a data provider as an argument during contruction.
For more detailed usage instructions, refer to the documentation of the derived
classes.

@see CAnimation
@see MAnimationDataProviderObserver
@publishedAll
@released
*/
class CAnimationDataProvider : public CBase
	{
public:
    IMPORT_C void SetObserver(MAnimationDataProviderObserver* aObserver);
    /** Called from the animation when it is ready to begin receiving data. */
    virtual void StartL() = 0;
    /** Called from the animation to obtain the type of data to expect.
    @return An 8 bit identifier string*/
    virtual TPtrC8 DataType() = 0;
protected:
	IMPORT_C CAnimationDataProvider();
	IMPORT_C virtual void CAnimationDataProvider_Reserved1();
	IMPORT_C virtual void CAnimationDataProvider_Reserved2();

    IMPORT_C void SendEventL(TInt aEvent);
    IMPORT_C void SendEventL(TInt aEvent, TInt aData);
    IMPORT_C void SendEventL(TInt aEvent, TAny* aData, TInt aDataSize);
protected: 
	/** Reserved for future use */
	TInt iCAnimationDataProvider_Reserved;
	/** The destination to send data to. Usually an animation class. */
	MAnimationDataProviderObserver* iObserver;
	};

#endif // __ANIMATIONDATAPROVIDER_H__
