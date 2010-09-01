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
* Description:  Test grids_api
*
*/

#ifndef C_TESTSDKGRIDSEXT_H
#define C_TESTSDKGRIDSEXT_H

/*
 *  INCLUDES
 */
#include <e32base.h>
#include <akngrid.h>
#include <gulicon.h>
#include <e32cmn.h>
#include <eikclb.h>

/**
 *  Test Class CMPslnFWMSKObserverExt
 */       
class CAknGridExt : public CAknGrid
    {
public:
    /*
     * Constructor
     */
    CAknGridExt();
    /*
     * Destructor
     */
    virtual ~CAknGridExt();
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    TInt HorizontalNudgeValue() const;
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    TInt HorizScrollGranularityInPixels() const;
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    void AdjustTopItemIndex() const;
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    void HandleDragEventL(TPoint aPointerPos);
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    void RestoreClientRectFromViewRect(TRect& aClientRect) const;
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    TInt AdjustRectHeightToWholeNumberOfItems(TRect& aRect) const;
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    void UpdateScrollBarThumbs() const;
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    TInt CountComponentControls() const;
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    void MoveToNextOrPreviousItemL(TPoint aPoint);
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    void CalcGridSizeL();
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    void CreateItemDrawerL();
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    void HandleScrollEventL(CEikScrollBar* aScrollBar, TEikScrollEvent aEventType);
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
    };

#endif /*TESTSDKGRIDSEXT_H_*/

/*
 * End files
 */
