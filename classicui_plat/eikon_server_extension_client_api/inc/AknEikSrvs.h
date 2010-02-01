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
* Description:  Additional op codes for Avkon extensions to Eiksrv.
*
*/

#ifndef __AKNEIKSRVS_H__
#define __AKNEIKSRVS_H__

const TUint KAknEikSrvDefaultHeapSize = 0x10000; 
const TUint KAknEikSrvDefaultMaxHeapSize = 0x100000;

enum TAknEikUiOpCode
    {
    EAknEikAppUiShutdownApps = 50, // To avoid other op codes
    EAknEikAppUiNotifer,
    EAknEikAppUiAddToStack,
    EAknEikAppUiRemoveFromStack,
    EAknEikAppUiExecuteD,
    EEikAppUiNotifyAlarmServerOfTaskChange,
    };
    
enum TAknEikUiOpCodesWWriteDeviceDataProt
    {
    EAknNotifierControllerCmd = 100,
    EAknCapServerStartupComplete,
    EAknSignalAknCapServerReady,
    EAknCommonNotifierServerRunning
    };
    
struct SStartThreadArg
    {
    //empty
    };

class TLaunchServer
    {
public:
    virtual void LaunchL(RLibrary* aLibrary) = 0;
    };
      
#endif // __AKNEIKSRVS_H__
