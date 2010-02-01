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
* Description:  Active scheduler used in the thread that hosts OOM & OOD watchers.
*
*/

#ifndef __EIKLAFSHUTSCHEDULER_H__
#define __EIKLAFSHUTSCHEDULER_H__

#include <e32base.h>

class CEikLafShutScheduler : public CActiveScheduler
    {
    public:
        CEikLafShutScheduler();
        ~CEikLafShutScheduler();

    private:
        void Error( TInt aLeaveCode ) const;
    };

#endif // __EIKLAFSHUTSCHEDULER_H__

// End of File
