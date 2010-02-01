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


#ifndef HGSELECTIONOBSERVERIFACE_H_
#define HGSELECTIONOBSERVERIFACE_H_

#include <e32base.h>

// FORWARD DECLARATIONS
class CCoeControl;

/**
 * Selection observer interface.
 */
class MHgSelectionObserver
    {
public:

    /**
     * Handle selection.
     * 
     * @param aIndex Selected item index.
     */
    virtual void HandleSelectL( TInt aIndex ) = 0;

    /**
     * Handle opening.
     * 
     * @param aIndex Opened item index.
     */
    virtual void HandleOpenL( TInt aIndex ) = 0;

    
    /**
     * Handle selection from certain CCoeControl
     * 
     * @param aIndex Selected item index.
     * @param aControl CCoeontrol calling this method. 
     */
    virtual void HandleSelectL( TInt aIndex, CCoeControl* /*aControl*/ ) { HandleSelectL(aIndex); }    

    /**
     * Handle open from certain CCoeControl
     * 
     * @param aIndex Opened item index.
     * @param aControl CCoeontrol calling this method.
     */
    virtual void HandleOpenL( TInt aIndex, CCoeControl* /*aControl*/ ) { HandleOpenL(aIndex); }        
    };

#endif // HGSELECTIONOBSERVERIFACE_H_
