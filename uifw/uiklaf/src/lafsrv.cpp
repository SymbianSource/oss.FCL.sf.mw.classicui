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


#include <lafpanic.h>
#include "LAFSTD.H"
#include <coemain.h>
#include <uiklaf/private/lafsrv.h>

const TInt KLafSrvNumPointerCursors=0;
//_LIT(KLafSrvAppUIBaseMbmFile,"Z:\\system\\data\\lafcurs.mbm");

// local functions

//LOCAL_C void PointerCleanup(TAny* aPtr)
//	{REINTERPRET_CAST(RWsPointerCursor*,aPtr)->Close();}

//LOCAL_C RWsPointerCursor* AddCursorL(CFbsBitmap* /*aBitmap*/, CFbsBitmap* /*aMaskBitmap*/, const TPoint &/*aHotSpot*/, TSpriteMember& /*aSpriteMember*/, TInt /*aCursorNumber*/, CCoeEnv& /*aEnv*/)
/*	{
	RWsSession& session = aEnv.WsSession();
	RWsPointerCursor* pointerCursor = new(ELeave) RWsPointerCursor(session);
	CleanupStack::PushL(pointerCursor);
	User::LeaveIfError(pointerCursor->Construct(0));
	CleanupStack::PushL(TCleanupItem(PointerCleanup,pointerCursor));
	aSpriteMember.iBitmap = aBitmap;
	aSpriteMember.iMaskBitmap = aMaskBitmap;
	aSpriteMember.iInvertMask = EFalse;
	aSpriteMember.iOffset = aHotSpot;
	aSpriteMember.iInterval = TTimeIntervalMicroSeconds32 (0);
	aSpriteMember.iDrawMode = CGraphicsContext::EDrawModePEN;
	User::LeaveIfError(pointerCursor->AppendMember(aSpriteMember));
	User::LeaveIfError(pointerCursor->Activate());
	session.SetSystemPointerCursor(*pointerCursor, aCursorNumber);
	CleanupStack::Pop(2); // pointerCursor - handle & ptr
	return pointerCursor;
	}
*/
//LOCAL_C RWsPointerCursor* LoadCursorL(TInt32 /*aBitmapId*/,TInt32 /*aBitmapMaskId*/, const TPoint &/*aHotSpot*/, TSpriteMember& /*aSpriteMember*/, TInt /*aCursorNumber*/, CCoeEnv& /*aEnv*/)
//	{
    /*
	__ASSERT_DEBUG(aCursorNumber<KLafSrvNumPointerCursors,Panic(ELafPanicPointerCursorIndexOutOfRange));
	TBool shareIfLoaded(ETrue);
	CFbsBitmap* bitmap = new (ELeave) CFbsBitmap();
	CleanupStack::PushL(bitmap);
	User::LeaveIfError(bitmap->Load(KLafSrvAppUIBaseMbmFile, aBitmapId,shareIfLoaded));
	CFbsBitmap* bitmapMask = new (ELeave) CFbsBitmap();
	CleanupStack::PushL(bitmapMask);
	User::LeaveIfError(bitmapMask->Load(KLafSrvAppUIBaseMbmFile, aBitmapMaskId,shareIfLoaded));
	RWsPointerCursor* cursor=AddCursorL(bitmap,bitmapMask,aHotSpot,aSpriteMember,aCursorNumber,aEnv);
	CleanupStack::PopAndDestroy(2); // bitmap, bitmapMask
	return cursor;
    */
//	}

//
// class LafServAppUiBase
//

/**
 * This method returns the number of pointer cursors supplied by the laf.
 * It may be zero for some devices.
 *
 */
EXPORT_C TInt LafServAppUiBase::NumberOfCursorsInSystemCursorList()
	{//static
	return KLafSrvNumPointerCursors;
	}

/**
 * Called by EikServAppUiBase. Claims the pointer cursor list if this
 * device has a global pointer cursor list, does nothing otherwise.
 *
 */
EXPORT_C TInt LafServAppUiBase::ClaimPointerCursorListIfNeeded(CCoeEnv& aEnv)
	{//static
	RWsSession& session=aEnv.WsSession();
	TBool ret=session.ClaimSystemPointerCursorList();
	if(ret==KErrNone)
		session.SetDefaultSystemPointerCursor(1); //pointer cursor
	return ret;
	}

/**
 * Called by EikServAppUiBase. Frees the pointer cursor list if this
 * device has a global pointer cursor list, does nothing otherwise.
 *
 */
EXPORT_C void LafServAppUiBase::FreePointerCursorListIfNeeded(CCoeEnv& aEnv)
	{//static
	aEnv.WsSession().FreeSystemPointerCursorList();
	}

/**
 * Constructs the TSpriteMember a member corresponding to the pointer cursor with index
 * aCursorNumber. Does nothing for devices with no system pointer cursors.
 * The numeric values used in the LoadCursorL() function call are for the position of
 * the cursors hotspot.
 *
 */
EXPORT_C RWsPointerCursor* LafServAppUiBase::ConstructPointerCursorL(TInt aCursorNumber, TSpriteMember& /*aSpriteMember*/, CCoeEnv& /*aEnv*/)
	{//static

	__ASSERT_DEBUG(aCursorNumber<KLafSrvNumPointerCursors,Panic(ELafPanicPointerCursorIndexOutOfRange));
	RWsPointerCursor* cursor=NULL;
	return cursor;
	}
