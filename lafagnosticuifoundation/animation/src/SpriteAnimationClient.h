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

#ifndef SPRITEANIMATIONCLIENT_H
#define SPRITEANIMATIONCLIENT_H

#include <w32std.h>

class TAnimationConfig;

/** @internalComponent */
NONSHARABLE_CLASS(RSpriteAnimationClient) : public RAnim
	{
public:
	RSpriteAnimationClient(RAnimDll& aAnimDll);
	~RSpriteAnimationClient();
	void ConstructL(const RWsSprite& aDevice, const TDesC8& aDataType);
	void ConstructL(const RWsSprite& aDevice, const TDesC8& aDataType, TInt aHostHandle);
	void Start(const TAnimationConfig& aConfig);
	void Stop();
	void Pause();
	void Resume();
	void Hold();
	void Unhold();
	void Freeze();
	void Unfreeze();
	void SendEventL(TInt aEvent, const TAny* aData, TInt aDataLength);
	TSize Size();
protected:
	void SetMinBufferSizeL(TInt aSize);
private:
	TPtr8 iBuf;
	};
	
#endif // SPRITEANIMATIONCLIENT_H
