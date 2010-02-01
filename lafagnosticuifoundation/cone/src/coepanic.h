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

#ifndef __COEPANIC_H__
#define __COEPANIC_H__

enum TCoePanic
	{
	ECoePanicStartupHeapTooSmall					=1, // no longer used
	ECoePanicEnvironmentAlreadyExists				=2,
	ECoePanicRootControlAlreadyExists				=3,
	ECoePanicNoSuchControlInStack					=4,
	ECoePanicLeaveWithoutTrap						=5,
	ECoePanicLeaveWithoutTrapDuringRedraw			=6,
	ECoePanicF32ResourceNotFreed					=7,
	ECoePanicWservResourceNotFreed					=8,
	ECoePanicWservBlindCommandFailed				=9,
	ECoePanicWindowAlreadyCreated					=10,
	ECoePanicNoWindow								=11,
	ECoePanicControlIsNotContainer					=12,
	ECoePanicUnknownResourceFile					=13,
	ECoePanicNoResourceFileForId					=14,
	ECoePanicResourceFileHasNullName				=15,
	ECoePanicWrongResourceFormat					=16,
	ECoePanicExtensionAlreadyExists					=17,
	ECoePanicIllegalNullParameter3					=18,
	ECoePanicIllegalNullParameter4					=19,
	ECoePanicFocusObserverHasAlreadyBeenAdded		=21,
	ECoePanicForegroundObserverHasAlreadyBeenAdded	=22,
	ECoePanicFepObserverHasAlreadyBeenAdded			=23,
	ECoePanicIllegalNullParameter13					=25,
	ECoePanicIllegalNullParameter14					=26,
	ECoePanicNullGc									=27,
	ECoePanicResourceFileNotDeleted					=28,
	ECoePanicNoViewServerConnection					=29,
	ECoePanicViewNotFound							=30,
	ECoePanicNullObjectUid							=31,
	ECoePanicDuplicateObjectUid						=32,
	ECoePanicNullEnvironment						=33,
	ECoePanicSystemSoundNotReleased					=34,
	ECoePanicNoWindowGroup							=35,
	ECoePanicHandleNotClosed						=36,
	ECoePanicViewEventNotHandled					=37,
	ECoePanicViewObserverNotFound					=38, //no longer used
	ECoePanicViewNotificationObserverAlreadyExists	=39,
	ECoePanicInnerAppUiNotNull1						=40,
	ECoePanicInnerAppUiNotNull2						=41,
	ECoePanicInnerAppUiNotNull3						=42,
	ECoePanicInnerAppUiNotNull4						=43,
	ECoePanicControlNotRemovedFromStack				=44,
	ECoePanicFocusObserverNotificationIsNotPending	=45,
	ECoePanicInvalidHandle							=46,
	ECoePanicViewInvalid							=47,
	ECoePanicExportNotSupported						=48,
	ECoePanicCyclicParentChildRelationship          =49,
	ECoePanicIncorrectControlParent					=50,
	ECoePanicDuplicateControlId						=51,
	ECoePanicNonExistentArray						=52,
	ECoePanicInvalidControlId						=53,
	ECoePanicNoControlParent 						=54,
	ECoePanicNoControlForId							=55,
	ECoePanicNoBaseCallInOverriddenInterfaceMethod	=56,
	ECoePanicUnexpectedError						=57,
	ECoePanicLogicalColorNotFound					=58,
	ECoePanicInvalidColorRange						=59,
	ECoePanicInvalidScreenNumber					=60,
	ECoePanicHasBackedUpWindow						=61,
	ECoePanicControlNotWindowOwning					=62,
	ECoePanicControlWindowIsBackedUp				=63,
	ECoePanicNoSuchNumberedPointer					=64

	};

GLREF_C void Panic(TCoePanic aPanic);

#endif	// __COEPANIC_H__
