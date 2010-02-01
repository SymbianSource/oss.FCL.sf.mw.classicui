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


// INCLUDE FILES
#include <akntoolbarobserver.h> 


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// MAknToolbarObserver::DynInitToolbarL
// Should be used to set the properties of some toolbar components 
// before it is drawn
// -----------------------------------------------------------------------------
//
EXPORT_C void MAknToolbarObserver::DynInitToolbarL( TInt /*aResourceId*/, 
                                                    CAknToolbar* /*aToolbar*/ )
    {
    }
    

// -----------------------------------------------------------------------------
// MAknToolbarObserver::MAknToolbarObserver_Reserved_1
// -----------------------------------------------------------------------------
//
EXPORT_C TInt MAknToolbarObserver::MAknToolbarObserver_Reserved_1()
    {
    return 1;
    }

// -----------------------------------------------------------------------------
// MAknToolbarObserver::MAknToolbarObserver_Reserved_2
// -----------------------------------------------------------------------------
//
EXPORT_C TInt MAknToolbarObserver::MAknToolbarObserver_Reserved_2()
    {
    return 1;
    }
    
// end of file 

