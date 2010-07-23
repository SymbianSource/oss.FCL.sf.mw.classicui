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

//INCLUDE
#include "testsdkdialogmediatorobserver.h"

// -----------------------------------------------------------------------------
// CTestDialogMediatorObserver::CTestDialogMediatorObserver
// -----------------------------------------------------------------------------
//
CTestDialogMediatorObserver::CTestDialogMediatorObserver()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestDialogMediatorObserver::~CTestDialogMediatorObserver
// -----------------------------------------------------------------------------
//
CTestDialogMediatorObserver::~CTestDialogMediatorObserver()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestDialogMediatorObserver::MediatorCommandL
// -----------------------------------------------------------------------------
//
TAknDialogMediatorObserverCommand CTestDialogMediatorObserver::MediatorCommandL( TUid /*aDomain*/,
    TUid /*aCategory*/, 
    TInt /*aCommandId*/,
    const TDesC8& /*aData*/ )
    {
    return EAcceptDialog;
    }

// -----------------------------------------------------------------------------
// CTestDialogMediatorObserver::NotifyMediatorExit
// -----------------------------------------------------------------------------
//
void CTestDialogMediatorObserver::NotifyMediatorExit()
    {
    
    }

//End file



