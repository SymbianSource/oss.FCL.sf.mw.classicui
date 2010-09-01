/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test aknnavide.h
 *
*/


#include "testsdknavipanenaviext.h"

// ---------------------------------------------------------------------------
// Implementation of CAknNavigationControlContainerExt
// ---------------------------------------------------------------------------
//

void CAknNavigationControlContainerExt::ConstructL()
    {
    CAknNavigationControlContainer::ConstructL();
    }
// ---------------------------------------------------------------------------
// CAknNavigationControlContainerExt::SizeChanged
// ---------------------------------------------------------------------------
//
void CAknNavigationControlContainerExt::SizeChanged()
    {
    CAknNavigationControlContainer::SizeChanged();
    }

//
// ---------------------------------------------------------------------------
// CAknNavigationControlContainerExt::HandleResourceChange
// ---------------------------------------------------------------------------
//
void CAknNavigationControlContainerExt::HandleResourceChange(TInt aType)
    {
    CAknNavigationControlContainer::HandleResourceChange(aType);
    }


//
// ---------------------------------------------------------------------------
// CAknNavigationControlContainerExt::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CAknNavigationControlContainerExt::CountComponentControls() const
    {
    return CAknNavigationControlContainer::CountComponentControls();
    }


//
// ---------------------------------------------------------------------------
// CAknNavigationControlContainerExt::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl*  CAknNavigationControlContainerExt::ComponentControl(TInt aIndex) const
    {
    return CAknNavigationControlContainer::ComponentControl(aIndex);
    }


//
// ---------------------------------------------------------------------------
// CAknNavigationControlContainerExt::HandleControlEventL
// ---------------------------------------------------------------------------
//
void CAknNavigationControlContainerExt::HandleControlEventL( CCoeControl* aControl,
    TCoeEvent aEventType )
    {
    CAknNavigationControlContainer::HandleControlEventL( aControl, aEventType );
    }



//
// ---------------------------------------------------------------------------
// CAknNavigationControlContainerExt::MopSupplyObject
// ---------------------------------------------------------------------------
//
TTypeUid::Ptr CAknNavigationControlContainerExt::MopSupplyObject( TTypeUid aId )
    {
    if ( aId.iUid == CAknNavigationControlContainer::ETypeId )
        {
        return aId.MakePtr( this );
        }

    return CCoeControl::MopSupplyObject( aId );
    }

