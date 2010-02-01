/*
* Copyright (c) 2003-2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:     Declares ECom monitoring class for AIW framework.
*
*/




#ifndef _AIWECOMMONITOR_H
#define _AIWECOMMONITOR_H

#include <ecom/ecom.h>

// FORWARD DECLARATIONS
class CAiwCriteriaItem;
class CAiwServiceIfBase;

class CAiwEcomMonitor : public CActive
    {
    public:
        static CAiwEcomMonitor* NewL(TCallBack& aSynchronizeCallBack);
        virtual ~CAiwEcomMonitor();

    protected:  // Functions from base classes
        /**
        * From CActive
        */
        void RunL();

        /**
        * From CActive
        */
        void DoCancel();

    public:
        inline REComSession& EComSession();
        void ListImplemetationsL(RImplInfoPtrArray& aResult, CAiwCriteriaItem* aItem) const;
        CAiwServiceIfBase* CreateImplementationL(TUid aImplUid);

    protected:
        /**
        * C++ default constructor.
        */
        CAiwEcomMonitor(TCallBack& aSynchronizeCallBack);
        void ConstructL();
        void StartMonitoring();

    private:
        TCallBack    iSynchronizeCallBack;
        REComSession iEcomSession;
    };


inline REComSession& CAiwEcomMonitor::EComSession()
    {
    return iEcomSession;
    }

#endif // _AIWECOMMONITOR_H

// End of file
