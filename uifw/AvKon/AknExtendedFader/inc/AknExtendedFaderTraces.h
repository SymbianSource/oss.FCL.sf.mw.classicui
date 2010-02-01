/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
#ifndef AKNEXTENDEDFADERTRACES_H_
#define AKNEXTENDEDFADERTRACES_H_

#if defined(_DEBUG) || defined(AKNEXTENDEDFADER_UREL_TRACES)

// Traces in debug mode or if somebody forced them in UREL as well
#define TRACE(x)                    RDebug::RawPrint(_L8(x));
#define TRACE1(x, a)                RDebug::Printf(x, a);
#define TRACE2(x, a, b)             RDebug::Printf(x, a, b);
#define TRACE3(x, a, b, c)          RDebug::Printf(x, a, b, c);
#define TRACE4(x, a, b, c, d)       RDebug::Printf(x, a, b, c, d);
#define TRACE5(x, a, b, c, d, e)    RDebug::Printf(x, a, b, c, d, e);
#define TRACE6(x, a, b, c, d, e, f) RDebug::Printf(x, a, b, c, d, e, f);

#else

#define TRACE(x)
#define TRACE1(x, a)
#define TRACE2(x, a, b)
#define TRACE3(x, a, b, c)
#define TRACE4(x, a, b, c, d)
#define TRACE5(x, a, b, c, d, e)
#define TRACE6(x, a, b, c, d, e, f)

#endif

#endif
