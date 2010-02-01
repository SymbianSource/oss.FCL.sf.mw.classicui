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

#ifndef EIKDEFCONSTINTERNAL_H
#define EIKDEFCONSTINTERNAL_H

/**
@file
@internalComponent
@released
*/


#if defined(_DEBUG)
#define __UHEAP_CHECK_INTEGRITY User::Heap().Check()
#else
#define __UHEAP_CHECK_INTEGRITY
#endif


#define PROFILE_POINT_EIKON_FIRST		32

#define PROFILE_POINT_EIKON_LAST		39

#define PROFILE_POINT_EIKON_SIMPLE		32

#define PROFILE_POINT_EIKON_DIALOG_LOAD	33

#define PROFILE_POINT_EIKON_APP_LAUNCH	34

#define PROFILE_POINT_EIKON_CLOCK		35

#define PROFILE_POINT_EIKON_CALENDER	35

#define PROFILE_POINT_EIKON_LIBS_LOAD	36

#define PROFILE_POINT_EIKON_ADD_RES		37

#define KEikEikonBitmapStore		KNullDesC

const TUid KSystemIniFileUid = {0x1000010C};
	
const TInt KLastSystemWideErrCode = KErrCommsBreak;

#endif	// EIKDEFCONSTINTERNAL_H
