/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies).
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

#if !defined(__AKNMEDIATOROBSERVER_H_)
#define __AKNMEDIATOROBSERVER_H_

#include <e32std.h>

enum TAknDialogMediatorObserverCommand
    {
    EAcceptDialog = 1,
    ECancelDialog,
    EHandleAsNormal,
    EDoNothingWithThisCommand
    };


class MAknDialogMediatorObserver
    {
public:
        /**
        * A Mediator Service command.
        *
        * @since Series 60 3.1     
        * @param aDomain    The identifier of the domain         
        * @param aCategory  The identifier of the category.
        * @param aCommandId The identifier of the command.
        * @param aVersion   The version information of the command.
        * @param aData      The parameters of the command.
        * @return TAknDialogMediatorObserverCommand  How dialog should handle this event
        */
        virtual TAknDialogMediatorObserverCommand MediatorCommandL( TUid aDomain,
                                       TUid aCategory, 
                                       TInt aCommandId,
                                       const TDesC8& aData ) = 0;
    
    
        /**
        * Called when Avkon encapsulation is being destroyed
        *
        */
        virtual void NotifyMediatorExit() = 0;
    };

#endif
