/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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




#include <ecom/ecom.h>
#include "AiwMenuBinding.h"

CAiwMenuBinding* CAiwMenuBinding::NewL()
    {
    CAiwMenuBinding* bind = new (ELeave) CAiwMenuBinding();
    CleanupStack::PushL(bind);
    bind->ConstructL();
    CleanupStack::Pop(); // bind
    return bind;
    }


CAiwMenuBinding* CAiwMenuBinding::NewL(TInt aMenuItemIndex, TInt aParentId)
    {
    CAiwMenuBinding* bind = new (ELeave) CAiwMenuBinding(aMenuItemIndex, aParentId);
    CleanupStack::PushL(bind);
    bind->ConstructL();
    CleanupStack::Pop(); // bind
    return bind;
    }


CAiwMenuBinding* CAiwMenuBinding::NewLC()
    {
    CAiwMenuBinding* bind = new (ELeave) CAiwMenuBinding();
    CleanupStack::PushL(bind);
    bind->ConstructL();
    return bind;
    }


CAiwMenuBinding* CAiwMenuBinding::NewLC(TInt aMenuItemIndex, TInt aMenuId)
    {
    CAiwMenuBinding* bind = new (ELeave) CAiwMenuBinding(aMenuItemIndex, aMenuId);
    CleanupStack::PushL(bind);
    bind->ConstructL();
    return bind;
    }



CAiwMenuBinding::CAiwMenuBinding()
    {
    }


void CAiwMenuBinding::ConstructL()
    {
    }


CAiwMenuBinding::CAiwMenuBinding(TInt aMenuItemIndex, TInt aParentId) 
:iMenuItemIndex(aMenuItemIndex), iMenuId(aParentId)
    {
    // Nothing to do here.
    }



CAiwMenuBinding::~CAiwMenuBinding()
    {
    }


// End of file

