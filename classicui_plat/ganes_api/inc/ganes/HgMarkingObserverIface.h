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
* Description:     
*
*/


#ifndef HGMARKINGOBSERVERIFACE_H_
#define HGMARKINGOBSERVERIFACE_H_

#include <e32base.h>

/**
 * Marking observer interface.
 */
class MHgMarkingObserver
    {
public:

    /**
     * Handle marking.
     * 
     * @param aIndex Selected item index.
     * @param aMarked ETrue if item marked, EFalse if item is unmarked.
     */
    virtual void HandleMarkingL( TInt aIndex, TBool aMarked ) = 0;

    };

#endif // HGMARKINGOBSERVERIFACE_H_
