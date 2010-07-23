/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef C_TESTSDKCPCONTEXTPANE_H
#define C_TESTSDKCPCONTEXTPANE_H

#include <akncontext.h>

class CTestSDKCPContextPane : public CAknContextPane
    {
public:
    //constructor and destructor
    CTestSDKCPContextPane();
    ~CTestSDKCPContextPane();
    
    //protected
    /**
     * From CCoeControl. Handle the size change events.
    */
    virtual void SizeChanged();

    /**
     * Handles a change to the control's resources of type aType
     * which are shared across the environment, e.g. color scheme change.
     * @param aType Event type.
    */
    virtual void HandleResourceChange(TInt aType);

    /**
     * From CCoeControl. Returns number of controls inside the context pane control.
     * @return Number of component controls.
     */
    virtual TInt CountComponentControls() const;

    /**
     * From CCoeControl. Returns a control determined by control id.
     * @param anIndex Index of a control to be returned.
     * @return Pointer to control
    */
    virtual CCoeControl* ComponentControl(TInt aIndex) const;
    
    TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
    };
#endif /*C_TESTSDKCPCONTEXTPANE_H*/
