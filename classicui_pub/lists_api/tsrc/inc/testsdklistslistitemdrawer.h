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
* Description:  test protected for CListItemDrawer
*
*/

#ifndef C_TESTSDKLISTSLISTITEMDRAWER_H
#define C_TESTSDKLISTSLISTITEMDRAWER_H

#include <eiklbi.h>

class CTestSDKListsListItemDrawer : public CListItemDrawer
{
public:

    /**
     * C++ default constructor.
     */
    CTestSDKListsListItemDrawer();

    /**
     * Destructor.
     */
    virtual ~CTestSDKListsListItemDrawer();

    /**
     * Resets the pen style, brush style, brush colour etc. to suitable 
     * starting values for this class. 
     * 
     * This function is called after every drawing operation.
     */
    virtual void ResetGc() const;

    /**
     * Gets the colour used to draw tick marks. 
     *
     * A tick mark usually indicates that an item is selected.
     *
     * @return The tick mark colour.
     */
    inline TRgb MarkColor() const;

    /**
     * Gets the vertical gap between items in pixels.
     *
     * @return The vertical gap between items in pixels.
     */
    TInt VerticalInterItemGap() const;
    
    /**
     * Sets up the graphics context for the specified item.
     *
     * @param aItemIndex The item for which the graphics context 
     *        will be set up.
     */
    void SetupGc(TInt aItemIndex) const;

    /**
     * Draws item text.
     * 
     * This function is called by @c CListItemDrawer::DrawItem() with 
     * appropriate arguments. Its purpose is to draw the actual item 
     * - everything other than the item mark - into the graphics context.
     *
     * @param aItemIndex Which item to draw. 
     * @param aActualItemRect Where the item should be drawn. 
     * @param aItemIsCurrent Whether the item is current. 
     * @param aViewIsEmphasized Whether the list box view is emphasised. 
     * @param aViewIsDimmed Whether the list box view is dimmed. 
     * @param aItemIsSelected Whether the list box item is selected.
     */
    virtual void DrawActualItem(TInt aItemIndex, 
                                const TRect& aActualItemRect, 
                                TBool aItemIsCurrent, 
                                TBool aViewIsEmphasized, 
                                TBool aViewIsDimmed, 
                                TBool aItemIsSelected) const;
};

inline TRgb CTestSDKListsListItemDrawer::MarkColor() const
    {
    return CListItemDrawer::MarkColor();
    }

#endif /*C_TESTSDKLISTSLISTITEMDRAWER_H*/
