/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  derived from eikscrlb.h
*
*/


#ifndef C_TESTSDKSCROLLEREIKSCRLB_H
#define C_TESTSDKSCROLLEREIKSCRLB_H

// [INCLUDE FILES]
#include <coecntrl.h>

// forward declarations
class CEikScrollBar;
class CAknDoubleSpanScrollBar;


class CEikScrollBarExt : public CEikScrollBar
    {
public:
    /** 
     * From @c CCoeControl
     *
     * Gets the specified scrollbar component. Each component control is 
     * identified by an index, where the index depends on the order the 
     * controls were added: the first is given an index of 0, the next an index
     * of 1.
     * 
     * @param aIndex The index of the control to get.
     *
     * @return The component control with an index of aIndex.
     */
    CCoeControl* DoComponentControl( TInt aIndex ) const;

    /** 
     * From @cCCoeControl.
     *
     * Gets the number of controls contained in this scrollbar.
     * 
     * @return The number of component controls contained by this scrollbar.
     */
    TInt DoCountComponentControls() const;

    // imimplement SetButtonPosition method of base class
    void DoSetButtonPositionL( CAknScrollButton* aButton );

    // change of size
    virtual void SizeChanged();
    };

class CAknDouSpanScBarExt : public CAknDoubleSpanScrollBar
    {
public: // constructor and destructor

    CAknDouSpanScBarExt( CCoeControl* aParentWindow );

    ~CAknDouSpanScBarExt();

public: // from base class

    /** 
     * Not implemented 
     * 
     * @param Not used. 
     */
    virtual void CreateButtonL( CAknScrollButton*& aButton,
            CAknScrollButton::TType aType );

    /** 
     * Not implemented 
     * 
     * @param aButton Not used. 
     */
    virtual void SetButtonPositionL( CAknScrollButton* aButton );

public:
    /** 
     * From @c CCoeControl
     *
     * Gets the specified scrollbar component. Each component control is 
     * identified by an index, where the index depends on the order the 
     * controls were added: the first is given an index of 0, the next an index
     * of 1.
     * 
     * @param aIndex The index of the control to get.
     *
     * @return The component control with an index of aIndex.
     */
    CCoeControl* DoComponentControl( TInt aIndex ) const;

    /** 
     * From @cCCoeControl.
     *
     * Gets the number of controls contained in this scrollbar.
     * 
     * @return The number of component controls contained by this scrollbar.
     */
    TInt DoCountComponentControls() const;


    };


#endif // C_TESTSDKSCROLLEREIKSCRLB_H
