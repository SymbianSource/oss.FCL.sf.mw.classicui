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
* Description:  test aknsgcc.h, aknstatuspaneutils.h and aknsyncdraw.h
*
*/



#ifndef C_TESTDOMSTATUSPANECONTROL_H
#define C_TESTDOMSTATUSPANECONTROL_H

#include <coecntrl.h>
#include <aknsgcc.h>


// class declaration
class CTestStatusPaneControl : public CCoeControl,
                               public MAknSgcStatusPaneRedrawCoordinator
    {
public:    //constructor and destructor

    /**
     * Constructor.
     */
    CTestStatusPaneControl();

    /**
     * Two-phased constructor.
     */
    static CTestStatusPaneControl* NewL();

    /**
     * Destructor.
     */
    ~CTestStatusPaneControl();

private:    // constructor

    /**
     * By default Symbian 2nd phase constructor is private.
     */
    void ConstructL();

private:    // from CCoeControl class

    /**
     * Receive key events.
     */
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

    /**
     * Draw control.
     */
    void Draw(const TRect& aRect) const;

    /**
     * Return number of controls in its window.
     */
    TInt CountComponentControls() const;

    /**
     * Controls in its window.
     */
    CCoeControl* ComponentControl(TInt aIndex) const;

    /**
     * Resize screen.
     */
    void SizeChanged();

public:

    /**
     * derived from MAknSgcStatusPaneRedrawCoordinator
     */
    virtual void BlockServerStatusPaneRedrawsL();

    /**
     * derived from MAknSgcStatusPaneRedrawCoordinator
     */
    virtual void RedrawServerStatusPane();

    };

class CAknSgcImplExt : public CAknSgcImpl
    {

public:
    /**
     * derived from CAknSgcImpl
     */
    virtual void MoveApp( TInt aAppWindowGroupId, TSgcMoveAppToWhere aWhere );

    };

#endif // C_TESTDOMSTATUSPANECONTROL_H
