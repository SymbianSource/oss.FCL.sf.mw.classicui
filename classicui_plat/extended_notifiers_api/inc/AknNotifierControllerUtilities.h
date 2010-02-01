/*
* Copyright (c) 2004-2007 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __AKNNOTIFIERCONTROLLERUTILITIES__
#define __AKNNOTIFIERCONTROLLERUTILITIES__

#include <e32base.h>

const TInt KDoNotifierControllerCommand(0xFFFF); // to avoid lapping with opcodes below

class CAknNotifierControllerUtility: public CBase
    {
public: 
    enum TNotifierControllerCommand
        {
        EDoAllow,
        EDoStop,
        DoCancelAll 
        };

    CAknNotifierControllerUtility(TInt aOrdinalPosition):
        iMyOrdinalPosition(aOrdinalPosition){}
public: 
    IMPORT_C void DoAllowNotifications();
    IMPORT_C void DoStopNotifications();
    IMPORT_C void DoCancelAllNotificatonsL();
    
public: // for internal use
    void DoNotifierContollerCommandL(TNotifierControllerCommand aCommand);
            
private:
    TInt iSpare1;
    TInt iMyOrdinalPosition;
    };
    
#endif // __AKNNOTIFIERCONTROLLERUTILITIES__

// End of file
