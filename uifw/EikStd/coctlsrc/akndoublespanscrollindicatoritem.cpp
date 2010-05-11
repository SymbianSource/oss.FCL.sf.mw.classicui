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
* Description:  Indicator item for double span scroll bar.
*
*
*/


#include "AknDoubleSpanScrollIndicatorItem.h"
#include <aknconsts.h>
#include <AknUtils.h>
#include <AknsDrawUtils.h>
#include <aknappui.h>
#include <aknlayoutscalable_avkon.cdl.h>

CAknDoubleSpanScrollIndicatorItem* CAknDoubleSpanScrollIndicatorItem::NewL(TBool aRotated,
       TAknsItemID aTopItem,
        TInt        aTopItemBitmapId,
        TInt        aTopItemMaskId,
        TAknsItemID aMiddleItem,
        TInt        aMiddleItemBitmapId,
        TInt        aMiddleItemMaskId,
        TAknsItemID aBottomItem,
        TInt        aBottomItemBitmapId,
        TInt        aBottomItemMaskId)
    {
    CAknDoubleSpanScrollIndicatorItem* self = new (ELeave) CAknDoubleSpanScrollIndicatorItem();
    CleanupStack::PushL(self);
    self->ConstructL(aRotated,
        aTopItem,
        aTopItemBitmapId,
        aTopItemMaskId,
        aMiddleItem,
        aMiddleItemBitmapId,
        aMiddleItemMaskId,
        aBottomItem,
        aBottomItemBitmapId,
        aBottomItemMaskId);
    CleanupStack::Pop();
    return self;
    }

CAknDoubleSpanScrollIndicatorItem* CAknDoubleSpanScrollIndicatorItem::NewL()
    {
    CAknDoubleSpanScrollIndicatorItem* self
        = new ( ELeave ) CAknDoubleSpanScrollIndicatorItem;

    return self;
    }

CAknDoubleSpanScrollIndicatorItem::CAknDoubleSpanScrollIndicatorItem()
    {
    }

CAknDoubleSpanScrollIndicatorItem::~CAknDoubleSpanScrollIndicatorItem()
    {
    }

void CAknDoubleSpanScrollIndicatorItem::ConstructL(TBool /*aRotated*/,
        TAknsItemID aTopItem,
        TInt        /*aTopItemBitmapId*/,
        TInt        /*aTopItemMaskId*/,
        TAknsItemID aMiddleItem,
        TInt        /*aMiddleItemBitmapId*/,
        TInt        /*aMiddleItemMaskId*/,
        TAknsItemID aBottomItem,
        TInt        /*aBottomItemBitmapId*/,
        TInt        /*aBottomItemMaskId*/)
    {
    iTopId = aTopItem;
    iMidId = aMiddleItem;
    iBottomId = aBottomItem;
    }

