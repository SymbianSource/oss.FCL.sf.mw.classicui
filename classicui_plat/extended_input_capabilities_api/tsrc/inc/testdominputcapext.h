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
* Description:  test aknextendedinputcapabilities.h
*
*/



#ifndef C_TESTDOMINPUTCAPEXT_H
#define C_TESTDOMINPUTCAPEXT_H


#include <aknextendedinputcapabilities.h>


// class declaration
class CAknExtInputCapObserver : public CBase,
                        public CAknExtendedInputCapabilities::MAknEventObserver
    {
public:

    /**
     * Handle an event. Note that the possible parameters are valid only
     * while this functions is called. If client needs to use them
     * later, it needs to copy them. Due to the internal nature of
     * this interface the aParams is trusted not to get changed in
     * the observers.
     *
     * @since S60 v3.2
     * @param aEvent An event, see TInputCapabilitiesEvent
     * @param aParams Event dependent parameters
     */
    virtual void HandleInputCapabilitiesEventL( TInt aEvent, TAny* aParams );

    };


#endif // C_TESTDOMINPUTCAPEXT_H
