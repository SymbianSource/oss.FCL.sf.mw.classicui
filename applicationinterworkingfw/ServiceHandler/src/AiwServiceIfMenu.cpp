/*
* Copyright (c) 2003-2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:     Implements service API for providers offering menu services 
*                for consumers.
*
*/




#include <ecom/ecom.h>
#include "AiwServiceIfMenu.h"
#include "AiwMenu.h"


void CAiwServiceIfMenu::InitializeMenuPaneHookL(
    CAiwMenuPane* aMenuPane,
    TInt aIndex,
    TInt aCascadeId,
    const CAiwGenericParamList& aInParamList)
    {
    iMenuPane = aMenuPane;  

    // Trapping prevents a leaving provider from breaking the whole consumer menu.  
    TRAPD(err, InitializeMenuPaneL(*aMenuPane, aIndex, aCascadeId, aInParamList));
    if(err)
        {
#ifdef _DEBUG
        RDebug::Print(_L("AIW PROVIDER ERROR: CAiwServiceIfMenu::InitializeMenuPaneL() failed, leave code:%d"), err);
#endif        
        }
    }



void CAiwServiceIfMenu::HandleMenuCmdHookL(
    CAiwMenuPane* aMenuPane,
    TInt aMenuCmdId,
    const CAiwGenericParamList& aInParamList,
    CAiwGenericParamList& aOutParamList,
    TUint aCmdOptions,
    const MAiwNotifyCallback* aCallback)
    {
    if (!iMenuPane)
        {
        return;
        }

    HandleMenuCmdL(aMenuPane->MenuCmdId(aMenuCmdId), aInParamList, aOutParamList,
        aCmdOptions, aCallback);
    }       


EXPORT_C const CAiwMenuPane* CAiwServiceIfMenu::MenuPane() const
    {
    return iMenuPane;
    }


EXPORT_C CAiwServiceIfMenu::~CAiwServiceIfMenu()
    {
    }
    
    
EXPORT_C void* CAiwServiceIfMenu::ExtensionInterface(TUid /*aInterface*/)
    {
    return NULL;
    }    

// End of file
