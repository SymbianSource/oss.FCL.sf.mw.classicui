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
* Description:  test protected for CFormattedCellListBoxData
*
*/

#ifndef C_TESTSDKLISTSFCLBDATA_H
#define C_TESTSDKLISTSFCLBDATA_H

#include <eikfrlbd.h>

class CTestSDKListsFCLBData : public CFormattedCellListBoxData
{
public:
    /**
     * C++ default constructor.
     */
    CTestSDKListsFCLBData();

    /**
     * Second phase constructor. Highlight animation will be 
     * created by default (if it is provided by the skin).
     */
    void ConstructLD();

    /**
     * Second phase constructor for subclasses that want to override highlight
     * animation creation.
     *
     * @param aAnimationIID Skin ItemID of the constructed animation. Passing
     *        @c KAknsIIDNone will disable highlight animation.
     */
    void ConstructLD(const TAknsItemID& aAnimationIID);

    /**
     * Main drawing algorithm used for drawing S60 list item. 
     * @c Draw() method should call this method after clearing the list item
     * area and drawing the highlight.
     *
     * @param aProperties Properties attached to the list item.
     * @param aGc Graphics Context used for drawing the list item.
     * @param aText A text string describing the list item cells.
     * @param aRect The area of the screen for the whole list item.
     * @param aHighlight Whether the list item is selected.
     * @param aColors The colors used for drawing the item.
     * @panic EAknPanicFormattedCellListInvalidBitmapIndex The defined bitmap
     *        index is invalid.
     * @panic EAknPanicOutOfRange The defined index is out of the range. 
     */
    void DrawFormatted(TListItemProperties aProperties,
                                CWindowGc& aGc,
                                const TDesC* aText,
                                const TRect& aRect,
                                TBool aHighlight,
                                const TColors& aColors) const;
};

#endif /*C_TESTSDKLISTSFCLBDATA_H*/
