/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  avkon trace
*
*/

#ifndef __AKNTRACE_H_
#define __AKNTRACE_H_

#include <e32cmn.h>


/*
 * Global switch :
 * In default, trace functions are only enabled for armv5 debug.
 * If they should be enabled on emulator, just enable the macro _AKN_TRACE_WINSCW
 */
#if defined(__ARMCC__) && defined(_DEBUG)
#define _AKN_TRACE_ARMCC
#endif

#if defined(__WINS__) && defined(_DEBUG)
//#define _AKN_TRACE_WINSCW
#endif


#if defined(_AKN_TRACE_ARMCC) || defined(_AKN_TRACE_WINSCW)
#define _AKNDEBUG(x)    do{x;}while(0)
#else
#define _AKNDEBUG(x)    do{}while(0)
#endif


// The macro used for tracing the normal logs in common.
#define _AKNTRACE(args...)  _AKNDEBUG(AknTracePrint(args))  


// AKNTRACE_FUNC_ENTER and AKNTRACE_FUNC_EXIT can be used for tracing a function entered/exited.
#if defined(_AKN_TRACE_ARMCC)
#define _AKNTRACE_FUNC_ENTER    _AKNTRACE("[%s][%s][%d] Enter", __MODULE__, __FUNCTION__, __LINE__)
#define _AKNTRACE_FUNC_EXIT     _AKNTRACE("[%s][%s][%d] Exit", __MODULE__, __FUNCTION__, __LINE__)
#elif defined(_AKN_TRACE_WINSCW)
#define _AKNTRACE_FUNC_ENTER    _AKNTRACE("[%s][%s][%d] Enter", __FILE__, __FUNCTION__, __LINE__)
#define _AKNTRACE_FUNC_EXIT     _AKNTRACE("[%s][%s][%d] Exit", __FILE__, __FUNCTION__, __LINE__)
#else
#define _AKNTRACE_FUNC_ENTER     do{}while(0)
#define _AKNTRACE_FUNC_EXIT      do{}while(0)
#endif

// The max length of trace string.
const TInt KAknTraceMaxLength = 0x100;

/*
 * A wrapper for RDebug::Print().
 * For saving stack memory, please trace log with ANSI string as much as possible.
 */
IMPORT_C void AknTracePrint(TRefByValue<const TDesC16> aFmt, ...);
IMPORT_C void AknTracePrint(const char* aFmt, ...);


#endif /* __AKNTRACE_H_ */
