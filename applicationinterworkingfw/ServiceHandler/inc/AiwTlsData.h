/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:     TLS data object.
*
*/





#ifndef _AIW_TLS_DATA_H
#define _AIW_TLS_DATA_H

#include <e32base.h>

class MAiwMenuLaunchObserver
    {
    public:
        virtual void MenuLaunched() = 0;
    };

NONSHARABLE_CLASS( CAiwTlsData ) : public CBase
	{
	public:
		static CAiwTlsData* OpenL();
		static void Close();
		
		inline static CAiwTlsData* Instance()
		    {
		    return static_cast<CAiwTlsData*>( Dll::Tls() );
		    }

        void AddMenuLaunchObserverL( MAiwMenuLaunchObserver* aObserver );
        void RemoveMenuLaunchObserver( MAiwMenuLaunchObserver* aObserver );
	
	    // CEikMenuPane uses this to inform AIW when a menu is launched.
	    void ReportMenuLaunch();
	
	private:
	    CAiwTlsData();
	    virtual ~CAiwTlsData();
	    
	    static CAiwTlsData* NewL();
	    void ConstructL();
	
	private:
	    TInt iRefCount;
		RPointerArray<MAiwMenuLaunchObserver> iMenuLaunchObservers;
	};

#endif // _AIW_TLS_DATA_H

// End of file
