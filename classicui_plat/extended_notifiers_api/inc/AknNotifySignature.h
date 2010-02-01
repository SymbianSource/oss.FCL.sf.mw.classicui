/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Signature definitions to validate notifier messages. 
*                If signature is not valid, whole message will be ignored in 
*                notifier plugin.
*
*/

#ifndef __AKNNOTIFYSIGNATURE_H__
#define __AKNNOTIFYSIGNATURE_H__

#include <e32std.h>
#include <AknNotifyStd.h>

const TInt KAKNNOTIFIERSIGNATURE('a'*'k'*'n');

// Used only when preallocating a global note id.
const TInt KAKNNOTIFIERSIGNATURE_GETNOTEID('a'*'k'*'n'*'2');

struct SAknNotifierSignature
    {
    SAknNotifierSignature():iSignature(KAKNNOTIFIERSIGNATURE){};
    const TInt iSignature; 
    };

template <class T>
struct SAknNotifierPackage: public SAknNotifierSignature
    { 
    T iParamData;
    };

#endif // __AKNNOTIFYSIGNATURE_H__
