/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Subscriber control for touch gesture framework.
*
*/

#ifndef C_AKNTOUCHGESTUREFWTESTSUBSCRIBERCONTROL_H
#define C_AKNTOUCHGESTUREFWTESTSUBSCRIBERCONTROL_H

#include <coecntrl.h>

/**
 *  Test observer.
 */
NONSHARABLE_CLASS( CAknTouchGestureFwTestSubscriberControl )
    : public CCoeControl
    {

public:

    /**
     * Two-phased constructor.
     */
    static CAknTouchGestureFwTestSubscriberControl* NewL();

    /**
     * Two-phased constructor.
     */
    static CAknTouchGestureFwTestSubscriberControl* NewLC();

    /**
     * Destructor.
     */
    virtual ~CAknTouchGestureFwTestSubscriberControl();

private:

    /**
     * Default C++ constructor.
     */
    CAknTouchGestureFwTestSubscriberControl();

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();
    };

#endif // C_AKNTOUCHGESTUREFWTESTSUBSCRIBERCONTROL_H
