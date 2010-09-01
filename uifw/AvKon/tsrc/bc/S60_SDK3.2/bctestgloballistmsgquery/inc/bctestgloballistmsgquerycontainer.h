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
* Description:  Container declaration for BCTestGlobalListMsgQuery.
*
*/

#ifndef BCTEST_GLOBALLISTMSGQUERYCONTAINER_H
#define BCTEST_GLOBALLISTMSGQUERYCONTAINER_H

#include <coecntrl.h>

/**
* Container class.
*/
class CBCTestGlobalListMsgQueryContainer : public CCoeControl
    {
public: // constructor and destructor
    /**
     * C++ default constructor.
     */
    CBCTestGlobalListMsgQueryContainer();

    /**
     * Destructor
     */
    virtual ~CBCTestGlobalListMsgQueryContainer();

    /**
     * Symbian 2nd phase constructor.
     */
    void ConstructL( const TRect& aRect );

public: // new functions
    /**
    * Set component control, and container will own the control.
    *
    * @param aControl pointer to a control.
    */
    void SetControl( CCoeControl* aControl );

    /**
     * Delete control.
     */
    void ResetControl();

public: // from CCoeControl
    /**
     * Return count of component controls.
     */
    TInt CountComponentControls() const;

    /**
     * Return pointer to component control specified by index.
     *
     * @param aIndex An index to specify a component control.
     */
    CCoeControl* ComponentControl( TInt aIndex ) const;

private: // from CCoeControl
    /**
    * From CCoeControl.
    * Fills the window's rectangle.
    *
    * @param aRect Region of the control to be (re)drawn.
    */
    void Draw( const TRect& aRect ) const;

private: // data
    /**
     * Pointer to component control.
     * own
     */
    CCoeControl* iControl;
    };

#endif

// End of file
