/*
* Copyright (c) 2002 - 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Avkon Trace
*
*/

#include "akntrace.h"
#include <e32base.h>
#include <e32debug.h>

NONSHARABLE_CLASS(TOverflowTruncate8) : public TDes8Overflow
    {
public:
    void Overflow(TDes8& /*aDes*/) {}
    };

NONSHARABLE_CLASS(TOverflowTruncate16) : public TDes16Overflow
    {
public:
    void Overflow(TDes16& /*aDes*/) {}
    };


EXPORT_C void AknTracePrint(TRefByValue<const TDesC16> aFmt, ...)
    {
    TOverflowTruncate16 overflow;
    VA_LIST list;
    VA_START(list, aFmt);
    TBuf<KAknTraceMaxLength> tmpBuf;
    tmpBuf.AppendFormatList(aFmt, list, &overflow);
    
    RDebug::Print(_L("%S"), &tmpBuf);
    }


EXPORT_C void AknTracePrint(const char* aFmt, ...)
    {
    TOverflowTruncate8 overflow;
    TBuf8<KAknTraceMaxLength> tmpBuf;
    TPtrC8 fmt((unsigned char*)aFmt);
    
    VA_LIST list;
    VA_START(list, aFmt);
    tmpBuf.AppendFormatList(fmt, list, &overflow);
    
    RDebug::RawPrint(tmpBuf);
    }
