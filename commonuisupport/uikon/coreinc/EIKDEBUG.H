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

/**
 @file
 @publishedAll
 @deprecated
*/

#ifndef __EIKDEBUG_H__
#define __EIKDEBUG_H__

//#define UIKON_OOM_TESTING		// enabling the testing requires also adding the FBSRV.LIB to eiksrvs and console mmp file.

#if defined(UIKON_OOM_TESTING)
#define __SHOW_FAIL_RATE(aFormatString, aFailRate) RDebug::Print(aFormatString,aFailRate)
#else
#define __SHOW_FAIL_RATE(aFormatString, aFailRate)
#endif

//#define _LOGGING // enabling RDebug::Print
#ifdef _LOGGING
#include <e32debug.h>

#define DEBUGPRINT1(_p1) RDebug::Print(_p1)
#define DEBUGPRINT2(_p1,_p2) RDebug::Print(_p1,_p2)
#define DEBUGPRINT3(_p1,_p2,_p3) RDebug::Print(_p1,_p2,_p3)
#define DEBUGPRINT4(_p1,_p2,_p3,_p4) RDebug::Print(_p1,_p2,_p3,_p4)
#else
#define DEBUGPRINT1(_p1)
#define DEBUGPRINT2(_p1,_p2)
#define DEBUGPRINT3(_p1,_p2,_p3)
#define DEBUGPRINT4(_p1,_p2,_p3,_p4)
#endif

#endif	// __EIKDEBUG_H__

