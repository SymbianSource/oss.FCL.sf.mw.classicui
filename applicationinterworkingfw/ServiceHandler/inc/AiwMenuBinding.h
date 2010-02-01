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
* Description:     Declares AIW Menu utilities for providers to access consumer menu.
*
*/




#ifndef _AIW_MENUBINDING_H
#define _AIW_MENUBINDING_H

#include "AiwServiceIfMenu.h"
#include "AiwBinding.h"

/**
* This utility class is used for binding a set of providers to a menu placeholder.
*/
NONSHARABLE_CLASS(CAiwMenuBinding) : public CAiwBinding
    {
    public:
        static CAiwMenuBinding* NewL();
        static CAiwMenuBinding* NewL(TInt aMenuItemIndex, TInt aMenuId);
        static CAiwMenuBinding* NewLC();
        static CAiwMenuBinding* NewLC(TInt aMenuItemIndex, TInt aMenuId);

        virtual ~CAiwMenuBinding();

        inline void SetMenuItemIndex(TInt aMenuItemIndex);
        inline TInt MenuItemIndex() const;
        inline CAiwServiceIfMenu* MenuProvider(TInt aIndex);
        inline TInt MenuCmd() const;
        inline void SetMenuCmd(TInt aMenuCmd);
        inline TInt MenuId();
        inline void SetMenuId(TInt aId);
        inline void SetMenuPane(CAiwMenuPane* aPane);
        inline CAiwMenuPane* MenuPane();
        
    private:
        CAiwMenuBinding();
        CAiwMenuBinding(TInt aMenuItemIndex, TInt aParentId);
        void ConstructL();

    private:
        TInt iMenuItemIndex;
        TInt iMenuCmd;      
        TInt iMenuId;
        CAiwMenuPane* iMenuPane;
    };

#include "AiwMenuBinding.inl"

#endif // _AIW_MENUBINDING_H

// End of file
