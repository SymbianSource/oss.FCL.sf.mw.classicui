/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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


// AKNANIMDLLSTD.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

// Avkon AnimDll Definitions


#if !defined(__AKNANIMDLLSTD_H__)
#define __AKNANIMDLLSTD_H__

// CONSTANTS

/**
* Enumerates instance types.
*/
enum TAknAnimType
    {
    EAnimKeySound,
	EAnimPhoneBlock
    };

/**
* Enumerates event types supported by the plugin.
*/
enum TAknKeySoundOpcode
    {
    EEnableKeyBlock = 50,
    EDisableKeyBlock = 51
    };

enum TAknPhoneBlockOpcode
    {
    ECancelBlackList
    };

#endif // __AKNANIMDLLSTD_H__

// End of File
