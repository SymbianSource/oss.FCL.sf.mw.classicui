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

#ifndef HGVGTIMER_H_
#define HGVGTIMER_H_

// INCLUDES
#include <e32base.h>
#include <e32std.h> 

/**
 * Timer class. Needed for better timer resolution in HgVgMediaWall.
 */
NONSHARABLE_CLASS(CHgVgTimer) : public CTimer
    {
public:

    /**
     * Creates new CHgVgTimer
     */
    static CHgVgTimer* NewL (); 
        
    // Destructor.
    virtual ~CHgVgTimer();

protected:
    CHgVgTimer();
    
public: // CTimer
    
    void RunL();
    
public:        
    void Start( TTimeIntervalMicroSeconds32 aDelay,
                    TTimeIntervalMicroSeconds32 anInterval,
                    TCallBack aCallBack );
            
private:    
    TTimeIntervalMicroSeconds32 iInterval;
    TCallBack iCallBack;
    };

#endif /* HGVGTIMER */
