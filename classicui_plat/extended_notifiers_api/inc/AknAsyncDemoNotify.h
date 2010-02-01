/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __AKNASYNCDEMONOTIFY_H__
#define __AKNASYNCDEMONOTIFY_H__

#include <AknNotify.h>

class CAknAsyncDemoNotify : public CActive
    {
public:
    IMPORT_C static CAknAsyncDemoNotify* NewL(const TCallBack& aCallBack);
    IMPORT_C ~CAknAsyncDemoNotify();
    IMPORT_C const TDesC8& Message();

private:
    CAknAsyncDemoNotify(const TCallBack& aCallBack);
    void ConstructL();
    void QueueL();

    void DoCancel();
    void RunL();

private:
    TBuf8<32> iBuf;
    RNotifier iNotify;
    TCallBack iCallBack;
    };

#endif // __AKNASYNCDEMONOTIFY_H__
