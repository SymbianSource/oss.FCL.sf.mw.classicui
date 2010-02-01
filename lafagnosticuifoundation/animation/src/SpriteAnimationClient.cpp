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

#include <e32std.h>

#include "SpriteAnimationClient.h"
#include "AnimationConfig.h"
#include "AnimationCmd.h"

/** 
Constructor.
@param aAnimDll A reference to the DLL that runs the animation 
*/
RSpriteAnimationClient::RSpriteAnimationClient(RAnimDll& aAnimDll) : RAnim(aAnimDll),iBuf(NULL,0,0)
	{
	}

RSpriteAnimationClient::~RSpriteAnimationClient()
	{
	User::Free((TAny *)iBuf.Ptr());
	}

/** 
Completes construction of an animation object.
 
This must be done after calling RSpriteAnimationClient(), and before an
application attempts any other communication with the server.

@param aWindow A reference to the container control window that will hold the
animation.
*/
void RSpriteAnimationClient::ConstructL(const RWsSprite& aDevice, const TDesC8& aDataType)
	{
	User::LeaveIfError(RAnim::Construct(aDevice, 0, aDataType));
	}
	
/** 
Completes construction of an animation object.
 
This must be done after calling RSpriteAnimationClient(), and before an
application attempts any other communication with the server.

@param aWindow A reference to the container control window that will hold the
animation.
*/
void RSpriteAnimationClient::ConstructL(const RWsSprite& aDevice, const TDesC8& aDataType, TInt aHostHandle)
	{
	User::LeaveIfError(RAnim::Construct(aDevice, 0, aDataType));
	TPckgBuf<TInt> pckg;
	pckg() = aHostHandle;
	Command(EAnimationCmdHostHandle, pckg);
	}


/** Starts the animation.*/
void RSpriteAnimationClient::Start(const TAnimationConfig& aConfig)
	{
	TPckgBuf<TAnimationConfig> Pckg;
	Pckg() = aConfig;
	Command(EAnimationCmdStart, Pckg);
	}

/** Stops the animation.*/
void RSpriteAnimationClient::Stop()
	{
	Command(EAnimationCmdStop);
	}

/** Pause the animation.*/
void RSpriteAnimationClient::Pause()
	{
	Command(EAnimationCmdPause);
	}
	
/** Resume a paused animation.*/
void RSpriteAnimationClient::Resume()
	{
	Command(EAnimationCmdResume);
	}

/** Hold an animation.*/
void RSpriteAnimationClient::Hold()
	{
	Command(EAnimationCmdHold);
	}

/** Resume a held animation.*/
void RSpriteAnimationClient::Unhold()
	{
	Command(EAnimationCmdUnhold);
	}

/** Freeze the server side ticker.*/
void RSpriteAnimationClient::Freeze()
	{
	Command(EAnimationCmdFreeze);
	}

/** Unfreeze the server side ticker.*/
void RSpriteAnimationClient::Unfreeze()
	{
	Command(EAnimationCmdUnfreeze);
	}

TSize RSpriteAnimationClient::Size()
	{
	const TInt reply = CommandReply(EAnimationCmdSize);
	TSize size(0,0);

	if (reply > 0)
		{
		size.iWidth = reply >> 16;
		size.iHeight = reply & ((1 << 16)-1);
		}

	return size;
	}

/** Send animation data to the animation.*/
void RSpriteAnimationClient::SendEventL(TInt aEvent, const TAny* aData, TInt aDataLength)
	{
	SetMinBufferSizeL(sizeof(TInt) * 2 + aDataLength);
	iBuf.SetLength(0);
	iBuf.Append((TUint8*)&aEvent,sizeof(TInt));
	iBuf.Append((TUint8*)&aDataLength,sizeof(TInt));
	iBuf.Append((TUint8*)aData, aDataLength);
	User::LeaveIfError(CommandReply(EAnimationCmdDataEvent, iBuf));
	}

void RSpriteAnimationClient::SetMinBufferSizeL(TInt aSize)
	{
	if (aSize > iBuf.MaxSize())
		{
		const TUint8* ptr = iBuf.Ptr();
		iBuf.Set((TUint8 *)User::AllocL(aSize),0,aSize);
		User::Free((TAny*)ptr);	
		}
	}

