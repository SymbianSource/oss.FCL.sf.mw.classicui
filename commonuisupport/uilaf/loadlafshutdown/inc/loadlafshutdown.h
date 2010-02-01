// Copyright (c)2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors: 
//
// Description: Used by lafshutdowneventobserveradaptor for creating shutdown manager.
//

#ifndef __LOADLAFSHUTDOWN_H__
#define __LOADLAFSHUTDOWN_H__

#include <uiklaf/private/lafshut.h> 
#include <ssm/ssmloadlafshut.h>

/**
Used by lafshutdowneventobserveradaptor for creating shutdown manager.

@internalAll
@released
*/  
NONSHARABLE_CLASS(CLoadLafShutdown) :  public CBase,public MSsmLoadLafShut
    {
public:
    IMPORT_C static MSsmLoadLafShut* NewL();
    
    //from MSsmLoadLafShut class
    void CreateShutdownManager(MShutdownEventObserver& aObserver);
    void DeleteShutdownManager();
private:
    CLoadLafShutdown();
    ~CLoadLafShutdown();
private:
    CLafShutdownManagerBase* iLafShutdown;
    };

#endif  //__LOADLAFSHUTDOWN_H__


