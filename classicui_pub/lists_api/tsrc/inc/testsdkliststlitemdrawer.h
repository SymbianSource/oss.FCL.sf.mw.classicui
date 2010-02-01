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
* Description:  
*
*/


#ifndef C_TESTSDKLISTSTLITEMDRAWER_H
#define C_TESTSDKLISTSTLITEMDRAWER_H

#include <eiklbi.h>

class CTestSDKListsTLItemDrawer : public CTextListItemDrawer
{
public:
    /**
     * C++ default constructor.
     *
     * Constructs a new text item drawer which draws the data of the specified 
     * model using the supplied font.
     *
     * @param aTextListBoxModel The model whose items will be drawn. 
     * @param aFont The font in which the items will be drawn.
     */
    CTestSDKListsTLItemDrawer(MTextListBoxModel* aTextListBoxModel, 
                                 const CFont* aFont);
    /**
     * Draws text.
     *
     * This function is invoked by @c DrawItemText() to draw a string into a 
     * rectangular area of @c iGc.
     *
     * @param aDes The string to draw. 
     * @param aItemTextRect Area to draw into. 
     * @param aItemIsCurrent @c ETrue if the item is current. 
     * @param aViewIsEmphasized @c ETrue if the view is emphasised. 
     * @param aItemIsSelected @c ETrue if the item is selected. 
     * @param aItemIndex The item�s index.
     */
    virtual void DoDrawItemText(const TDesC& aDes, 
                                         const TRect& aItemTextRect, 
                                         TBool aItemIsCurrent, 
                                         TBool aViewIsEmphasized, 
                                         TBool aItemIsSelected, 
                                         TInt aItemIndex) const;

    /**
     * Draw item text.
     * 
     * This function is invoked by @c DrawActualItem() to draw the item text.
     *
     * @param aItemIndex Index of the item to draw. 
     * @param aItemTextRect Area to draw into. 
     * @param aItemIsCurrent @c ETrue if the item is current. 
     * @param aViewIsEmphasized @c ETrue if the view is emphasised.
     * @param aItemIsSelected @c ETrue if the item is selected. 
     */
    virtual void DrawItemText(TInt aItemIndex, 
                                       const TRect& aItemTextRect, 
                                       TBool aItemIsCurrent, 
                                       TBool aViewIsEmphasized, 
                                       TBool aItemIsSelected) const;

    /**
     * Resets the graphics context.
     * This function invokes @c CListItemDrawer::ResetGc() and resets the pen 
     * colour to @c iTextColor.
     */
    virtual void ResetGc() const;

};

#endif /*C_TESTSDKLISTSTLITEMDRAWER_H*/
