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
* Description:     Inline methods for CAiwMenuBinding class.    
*
*/




inline void CAiwMenuBinding::SetMenuItemIndex(TInt aMenuItemIndex)
    {
    iMenuItemIndex = aMenuItemIndex;
    }


inline TInt CAiwMenuBinding::MenuItemIndex() const
    {
    return iMenuItemIndex;
    }


inline TInt CAiwMenuBinding::MenuCmd() const
    {
    return iMenuCmd;
    }


inline void CAiwMenuBinding::SetMenuCmd(TInt aMenuCmd)
    {
    iMenuCmd = aMenuCmd;
    }


inline TInt CAiwMenuBinding::MenuId()
    {
    return iMenuId;
    }


inline void CAiwMenuBinding::SetMenuId(TInt aId)
    {
    iMenuId = aId;
    }


inline CAiwServiceIfMenu* CAiwMenuBinding::MenuProvider(TInt aIndex)
    {
    if (aIndex >= 0 && aIndex < iProviders.Count())
        {
        return reinterpret_cast<CAiwServiceIfMenu*>(iProviders[aIndex]);
        }
    return NULL;
    }


inline void CAiwMenuBinding::SetMenuPane(CAiwMenuPane* aPane)
    {
    iMenuPane = aPane;
    }


inline CAiwMenuPane* CAiwMenuBinding::MenuPane()
    {
    return iMenuPane;
    }   


// End of file

