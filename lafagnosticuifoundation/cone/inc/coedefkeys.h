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

#ifndef COEDEFKEYS_H_
#define COEDEFKEYS_H_
#include <e32std.h> 
/**
 HAL supplies the number of supported pointers.
 This value places a hard, local limit on that number.
 
 @prototype
 @internalTechnology
 */
const TInt KConeMaxSupportedPointers = 8;

/** @internalTechnology */
const TUint KUidFepFrameworkRepository=0x10272618;

/** @internalTechnology */
enum // key-masks and keys for the "KUidFepFrameworkRepository" repository
	{
	ERepositoryKeyMask_DefaultSetting	=0x00001000,
	ERepositoryKeyMask_DynamicSetting	=0x00002000,

	ERepositoryKeyMask_FepId			=0x00000001,
	ERepositoryKeyMask_OnState			=0x00000002,
	ERepositoryKeyMask_OnKeyData		=0x00000004,
	ERepositoryKeyMask_OffKeyData		=0x00000008,

	ERepositoryKey_DefaultFepId			=ERepositoryKeyMask_DefaultSetting|ERepositoryKeyMask_FepId,
	ERepositoryKey_DefaultOnState		=ERepositoryKeyMask_DefaultSetting|ERepositoryKeyMask_OnState,
	ERepositoryKey_DefaultOnKeyData		=ERepositoryKeyMask_DefaultSetting|ERepositoryKeyMask_OnKeyData,
	ERepositoryKey_DefaultOffKeyData	=ERepositoryKeyMask_DefaultSetting|ERepositoryKeyMask_OffKeyData,

	ERepositoryKey_DynamicFepId			=ERepositoryKeyMask_DynamicSetting|ERepositoryKeyMask_FepId,
	ERepositoryKey_DynamicOnState		=ERepositoryKeyMask_DynamicSetting|ERepositoryKeyMask_OnState,
	ERepositoryKey_DynamicOnKeyData		=ERepositoryKeyMask_DynamicSetting|ERepositoryKeyMask_OnKeyData,
	ERepositoryKey_DynamicOffKeyData	=ERepositoryKeyMask_DynamicSetting|ERepositoryKeyMask_OffKeyData
	};

/** @internalTechnology */
#if defined(_DEBUG)
#define __DEBUG_CHECK_HEAP_INTEGRITY User::Heap().Check()
#else
#define __DEBUG_CHECK_HEAP_INTEGRITY
#endif

#endif /* COEDEFKEYS_H_ */
