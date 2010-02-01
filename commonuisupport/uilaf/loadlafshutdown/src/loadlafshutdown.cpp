// Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "loadlafshutdown.h"
EXPORT_C MSsmLoadLafShut * CLoadLafShutdown::NewL()
    {
    CLoadLafShutdown* loadLafShutdown = new (ELeave) CLoadLafShutdown();
    return loadLafShutdown ;
    }

CLoadLafShutdown::CLoadLafShutdown()
    {
    }

CLoadLafShutdown::~CLoadLafShutdown()
    {
    delete iLafShutdown;
    }

void CLoadLafShutdown::CreateShutdownManager(MShutdownEventObserver& aObserver)
    {
    ASSERT(!iLafShutdown);
    iLafShutdown = LafShutdown::CreateShutdownManager(aObserver);
    }

void CLoadLafShutdown::DeleteShutdownManager()
    {
    delete this;
    }
