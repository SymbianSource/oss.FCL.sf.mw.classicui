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
* Description:  Observer for avkon AdaptiveSearchGrid
*
*/



#ifndef __AKNADAPTIVESEARCHGRIDOBSERVER_H__
#define __AKNADAPTIVESEARCHGRIDOBSERVER_H__

// INCLUDES
#include <e32def.h>

// FORWARD DECLARATIONS
class CAknAdaptiveSearchGrid;

// CLASS DECLARATION

/**
*  The observer interface to handle adaptive search grid events
*
*  @lib avkon.lib
*  @since Series 60 5.0
*/
class MAknAdaptiveSearchGridObserver
    {
    public:      

        /**
         * Handles adaptive search grid events for a certain adaptive search grid item.
         * @param aCommand The command ID of some adaptive search grid item.
         */
        virtual void ProcessCommandL( TInt aCommand ) = 0;    
 
    };
    
#endif // __AKNADAPTIVESEARCHGRIDOBSERVER_H__

// end of file