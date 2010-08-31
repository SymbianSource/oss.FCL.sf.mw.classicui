/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Observer for avkon toolbar
*
*/



#ifndef __AKNTOOLBAROBSERVER_H__
#define __AKNTOOLBAROBSERVER_H__

// INCLUDES
#include <e32def.h>

// FORWARD DECLARATIONS
class CAknToolbar;

// CLASS DECLARATION

/**
*  The observer interface to handle toolbar events
*
*  @lib eikcoctl.lib
*  @since Series 60 3.1
*/
class MAknToolbarObserver
    {
    public:
        /**
         * Should be used to set the properties of some toolbar components 
         * before it is drawn.
         * @param aResourceId The resource ID for particular toolbar
         * @param aToolbar The toolbar object pointer
         */
        IMPORT_C virtual void DynInitToolbarL( TInt aResourceId, 
                                               CAknToolbar* aToolbar );
        
        /**
         * Handles toolbar events for a certain toolbar item.
         * @param aCommand The command ID of some toolbar item.
         */
        virtual void OfferToolbarEventL( TInt aCommand ) = 0;
    
    protected:
        IMPORT_C virtual TInt MAknToolbarObserver_Reserved_1();
        IMPORT_C virtual TInt MAknToolbarObserver_Reserved_2();
    };
    
#endif // __AKNTOOLBAROBSERVER_H__

// end of file