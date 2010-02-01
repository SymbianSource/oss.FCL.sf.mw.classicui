/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies).
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

#include "finditemcontroller.h"

// ---------------------------------------------------------
// Position and count methods
// ---------------------------------------------------------

// ---------------------------------------------------------
// CFindItemController::ItemCount() const
//  Returns the number of found items
// ---------------------------------------------------------
//
inline const TInt CFindItemController::ItemCount() const
    {
    return iEngine->ItemCount();    
    }

// ---------------------------------------------------------
// CFindItemController::Position() const
//  Returns current position
// ---------------------------------------------------------
//
inline const TInt CFindItemController::Position() const
    {
    return iEngine->Position();    
    }

// ---------------------------------------------------------
// CFindItemController::FirstItem() const
//  Returns ETrue if at first item
// ---------------------------------------------------------
//
inline const TBool CFindItemController::FirstItem() const
    {
    return iEngine->Position() == 0;
    }

// ---------------------------------------------------------
// CCFindItemController::LastItem() const
//  Returns ETrue if at last item
// ---------------------------------------------------------
//
inline const TBool CFindItemController::LastItem() const
    {
    return iEngine->Position() + 1 >= iEngine->ItemCount();
    }

// ---------------------------------------------------------
// Control Engine methods
// ---------------------------------------------------------

// ---------------------------------------------------------
// CFindItemController::Item( CFindItemEngine::SFoundItem& aItem ) const
//  Gives the currently 'selected' item
// ---------------------------------------------------------
//
inline TBool CFindItemController::Item( CFindItemEngine::SFoundItem& aItem ) const
    {
    return iEngine->Item( aItem );
    }

// End of File
