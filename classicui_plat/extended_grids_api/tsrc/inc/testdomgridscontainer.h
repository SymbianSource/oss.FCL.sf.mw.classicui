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
* Description:  test aknappgrid.h
*
*/



#ifndef C_TESTDOMGRIDSCONTAINER_H
#define C_TESTDOMGRIDSCONTAINER_H

#include <coecntrl.h>

/**
* container class
*/
class CTestDOMGridsContainer: public CCoeControl
    {
public: // constructor and destructor

    /**
     * Symbian 2nd constructor
     */
    static CTestDOMGridsContainer* NewL();

    /**
     * Destructor
     */
    virtual ~CTestDOMGridsContainer();

private:

    /**
     * C++ default constructor
     */
    CTestDOMGridsContainer();

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

private: // from CCoeControl

    /**
     * Return count of component controls
     */
    TInt CountComponentControls() const;

    /**
     * Return pointer to component control specified by index
     * @param aIndex, a index to specify a component control
     */
    CCoeControl* ComponentControl( TInt aIndex ) const;

    /**
    * From CCoeControl, Draw.
    * Fills the window's rectangle.
    * @param aRect Region of the control to be (re)drawn.
    */
    void Draw( const TRect& aRect ) const;  

    /**
     * Resize screen.
     */
    void SizeChanged();

public:

    /**
     * ActivateGc
     */
    void DoActivateGc();

    /**
     * DeactivateGc
     */
    void DoDeactivateGc();

    };


#endif // C_TESTDOMGRIDSCONTAINER_H
