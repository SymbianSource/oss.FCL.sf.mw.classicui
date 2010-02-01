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
* Description:  Interface class for CEikAlarmControl.                                             
*
*/

#ifndef ALARMOBSERVER_H
#define ALARMOBSERVER_H

// INCLUDES
#include <uikon/eiksvfty.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eiknotifyalert.h>
#endif
// FORWARD DECLARATIONS
class CEikAlmControlSupervisor;
class CEikServAppUiBase;

// CLASS DECLARATION

/**
*  Interface class for CEikAlarmControl.
*/
class MAlarmObserver : public MEikServAlarm
    {
public: // New functions
    /**
    * Two-phased constructor.
    * @param aSupervisor CEikAlmControlSupervisor class.
    * @param aAppUi CEikServAppUiBase class.
    */
    virtual void ConstructL(
        CEikAlmControlSupervisor* aSupervisor,
        CEikServAppUiBase* aAppUi) = 0;
    };

#endif // ALARMOBSERVER_H

// End of File
