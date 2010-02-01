/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Property subscriber.
*
*/



#ifndef C_PSLNPROPERTYSUBSCRIBER_H
#define C_PSLNPROPERTYSUBSCRIBER_H

#include    <e32base.h>
#include    <e32property.h>

/**
*  Property subscriber wrapper class.
*  Implements callback when property's value changes.
*
*  @since S60 v3.1
*/
class CPslnPropertySubscriber : public CActive
    {
    public:

        /**
        * C++ constructor.
        *
        * NOTE that callback method is NOT allowed to leave. If it leaves,
        * subscription is not activated after the leave.
        *
        * @param aCallBack callback method to handle notification of a change
        *        to client.
        * @param aProperty property to subscribe.
        */
        CPslnPropertySubscriber( TCallBack aCallBack, RProperty& aProperty );
        
        /**
        * Destructor.
        */
        virtual ~CPslnPropertySubscriber();   
        
        /**
        * Subscribe property. 
        * To stop subscription, just call Cancel.
        */
        void Subscribe();

        /**
        * From CActive. 
        * Called when Active Object is ready.
        */
        void RunL();
        
        /**
        * From CActive. 
        * Called when Active Object has been cancelled.
        */
        void DoCancel();

    private:    // Data
        /**
        * Callback harness.
        */
        TCallBack   iCallBack;

        /**
        * Publish & Subsribe property.
        */
        RProperty&  iProperty;

    };

#endif      // C_PSLNPROPERTYSUBSCRIBER_H
            
// End of File
