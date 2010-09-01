/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Debug macros for Psln.
*
*/


#ifndef PSLNDEBUG_H
#define PSLNDEBUG_H

// MACROS

// If PSLN_TRACING_ENABLED is defined, tracing will be enabled (all levels)
//
// Alternatively, the following macros can be used to enable traces:
//  PSLN_TRACING_ENABLED_INFO   Informative traces
//  PSLN_TRACING_ENABLED_NORMAL Normal traces
//  PSLN_TRACING_ENABLED_ERROR  Error traces
// Default for debug builds is NORMAL and ERROR

#if defined(_DEBUG)
    #define PSLN_TRACING_ENABLED_NORMAL
    #define PSLN_TRACING_ENABLED_ERROR
#endif // _DEBUG

#if defined(PSLN_TRACING_ENABLED)
    #undef PSLN_TRACING_ENABLED_INFO
    #define PSLN_TRACING_ENABLED_INFO
    #undef PSLN_TRACING_ENABLED_NORMAL
    #define PSLN_TRACING_ENABLED_NORMAL
    #undef PSLN_TRACING_ENABLED_ERROR
    #define PSLN_TRACING_ENABLED_ERROR
#endif // PSLN_TRACING_ENABLED

#if defined(PSLN_TRACING_ENABLED_INFO) || defined(PSLN_TRACING_ENABLED_NORMAL) || defined(PSLN_TRACING_ENABLED_ERROR)
    #if !defined(__E32SVR_H__)
        #include <e32svr.h>
    #endif // __E32SVR_H__

    #define PSLN_TRACECMDPFX RDebug::Print
    #define PSLN_TRACECMDSFX
    #define PSLN_TRACE_ADDPREFIX(aText) (TPtrC((const TText *)L"PSLN: \"" L##aText L"\""))
#endif // PSLN_TRACING_ENABLED_INFO || PSLN_TRACING_ENABLED_NORMAL || PSLN_TRACING_ENABLED_ERROR

#if defined(PSLN_TRACING_ENABLED_INFO)
#pragma message("PslnDebug: Info-mode tracing is enabled, performance will be degraded!")
    #define PSLN_TRACE_ADDPREFIX_INFO(aText) (TPtrC((const TText *)L"PSLN: (Info) \"" L##aText L"\""))
    #define PSLN_TRACE_INFO(aMsg) PSLN_TRACECMDPFX ( PSLN_TRACE_ADDPREFIX_INFO(aMsg) ) PSLN_TRACECMDSFX
    #define PSLN_TRACE_INFO1(aFormat,aP1) PSLN_TRACECMDPFX ( PSLN_TRACE_ADDPREFIX_INFO(aFormat),(aP1) ) PSLN_TRACECMDSFX
    #define PSLN_TRACE_INFO2(aFormat,aP1,aP2) PSLN_TRACECMDPFX ( PSLN_TRACE_ADDPREFIX_INFO(aFormat),(aP1),(aP2) ) PSLN_TRACECMDSFX
    #define PSLN_TRACE_INFO3(aFormat,aP1,aP2,aP3) PSLN_TRACECMDPFX ( PSLN_TRACE_ADDPREFIX_INFO(aFormat),(aP1),(aP2),(aP3) ) PSLN_TRACECMDSFX
#else
    #define PSLN_TRACE_INFO(aMsg)
    #define PSLN_TRACE_INFO1(aFormat,aP1)
    #define PSLN_TRACE_INFO2(aFormat,aP1,aP2)
    #define PSLN_TRACE_INFO3(aFormat,aP1,aP2,aP3)
#endif // PSLN_TRACING_ENABLED_INFO

#if defined(PSLN_TRACING_ENABLED_NORMAL)
    #define PSLN_TRACE_DEBUG(aMsg) PSLN_TRACECMDPFX ( PSLN_TRACE_ADDPREFIX(aMsg) ) PSLN_TRACECMDSFX
    #define PSLN_TRACE_DEBUG1(aFormat,aP1) PSLN_TRACECMDPFX ( PSLN_TRACE_ADDPREFIX(aFormat),(aP1) ) PSLN_TRACECMDSFX
    #define PSLN_TRACE_DEBUG2(aFormat,aP1,aP2) PSLN_TRACECMDPFX ( PSLN_TRACE_ADDPREFIX(aFormat),(aP1),(aP2) ) PSLN_TRACECMDSFX
    #define PSLN_TRACE_DEBUG3(aFormat,aP1,aP2,aP3) PSLN_TRACECMDPFX ( PSLN_TRACE_ADDPREFIX(aFormat),(aP1),(aP2),(aP3) ) PSLN_TRACECMDSFX
#else
    #define PSLN_TRACE_DEBUG(aMsg)
    #define PSLN_TRACE_DEBUG1(aFormat,aP1)
    #define PSLN_TRACE_DEBUG2(aFormat,aP1,aP2)
    #define PSLN_TRACE_DEBUG3(aFormat,aP1,aP2,aP3)
#endif // PSLN_TRACING_ENABLED_NORMAL

#if defined(PSLN_TRACING_ENABLED_ERROR)
    #define PSLN_TRACE_ADDPREFIX_ERROR(aText) (TPtrC((const TText *)L"PSLN: (Error) \"" L##aText L"\""))
    #define PSLN_TRACE_ERROR(aMsg) PSLN_TRACECMDPFX ( PSLN_TRACE_ADDPREFIX_ERROR(aMsg) ) PSLN_TRACECMDSFX
    #define PSLN_TRACE_ERROR1(aFormat,aP1) PSLN_TRACECMDPFX ( PSLN_TRACE_ADDPREFIX_ERROR(aFormat),(aP1) ) PSLN_TRACECMDSFX
    #define PSLN_TRACE_ERROR2(aFormat,aP1,aP2) PSLN_TRACECMDPFX ( PSLN_TRACE_ADDPREFIX_ERROR(aFormat),(aP1),(aP2) ) PSLN_TRACECMDSFX
    #define PSLN_TRACE_ERROR3(aFormat,aP1,aP2,aP3) PSLN_TRACECMDPFX ( PSLN_TRACE_ADDPREFIX_ERROR(aFormat),(aP1),(aP2),(aP3) ) PSLN_TRACECMDSFX
    #define PSLN_TRACE_OBSOLETE(aFunc) PSLN_TRACECMDPFX ( _L("PSLN: (Error) Obsolete function %s used"), _S(aFunc) ) PSLN_TRACECMDSFX
#else
    #define PSLN_TRACE_ERROR(aMsg)
    #define PSLN_TRACE_ERROR1(aFormat,aP1)
    #define PSLN_TRACE_ERROR2(aFormat,aP1,aP2)
    #define PSLN_TRACE_ERROR3(aFormat,aP1,aP2,aP3)
    #define PSLN_TRACE_OBSOLETE(aFunc)
#endif // PSLN_TRACING_ENABLED_ERROR

//lint -e960 Disable null statement note
//lint -esym(755,PSLN_TRACE*) Used in debug only

#endif // PSLNDEBUG_H
            
// End of File
