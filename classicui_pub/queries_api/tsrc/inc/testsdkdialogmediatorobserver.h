/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test queries_api
*
*/

#ifndef C_TestSDKDIALOGMEDIATOROBSERVER_H
#define C_TestSDKDIALOGMEDIATOROBSERVER_H

//INCLUDE
#include <aknmediatorobserver.h>
#include <e32base.h>

//Class declare

/*
 * The implement of the pure class MAknDialogMediatorObserver
 */
class CTestDialogMediatorObserver:public CBase, public MAknDialogMediatorObserver
    {
public:
    /*
     * Constructor
     */
    CTestDialogMediatorObserver();
    
    /*
     * Destructor
     */
    ~CTestDialogMediatorObserver();
    
    /*
     * The implement of the pure function
     */
    TAknDialogMediatorObserverCommand MediatorCommandL( TUid aDomain,
        TUid aCategory, 
        TInt aCommandId,
        const TDesC8& aData );
    
    /*
     * The implement of the pure function
     */
    void NotifyMediatorExit();
    };


#endif /*C_TestSDKDIALOGMEDIATOROBSERVER_H*/

//End file
