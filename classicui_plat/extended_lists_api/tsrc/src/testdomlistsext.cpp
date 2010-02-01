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
* Description:  test aknjavalists.h, aknshortcuts.h and eikslbd.h
*
*/



#include <aknshortcuts.h>

#include "testdomlistsext.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// AknListBoxShortCutsExt::DoTest
// -----------------------------------------------------------------------------
//
TBool AknListBoxShortCutsExt::DoTest( TConcreteQuery /*q*/ )
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// AknListBoxShortCutsExt::DoActionL
// -----------------------------------------------------------------------------
//
void AknListBoxShortCutsExt::DoActionL( TConcreteShortcutActions /*a*/ )
    {
    }

// -----------------------------------------------------------------------------
// AknListBoxShortCutsExt::ShortcutValueForNextList
// -----------------------------------------------------------------------------
//
TInt AknListBoxShortCutsExt::ShortcutValueForNextList()
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// AknListBoxShortCutsExt::SetShortcutValueFromPrevList
// -----------------------------------------------------------------------------
//
void AknListBoxShortCutsExt::SetShortcutValueFromPrevList( TInt /*aValue*/ )
    {
    }

// -----------------------------------------------------------------------------
// AknListBoxShortCutsExt::ChangeStateL
// -----------------------------------------------------------------------------
//
void AknListBoxShortCutsExt::DoChangeStateL()
    {
    ChangeStateL( AknListBoxShortCuts::ENone );
    }

// -----------------------------------------------------------------------------
// AknListBoxShortCutsExt::ChangeStateL
// -----------------------------------------------------------------------------
//
void AknListBoxShortCutsExt::DoStartTimerL()
    {
    StartTimerL( AknListBoxShortCuts::ENoTimeout );
    }

// -----------------------------------------------------------------------------
// default constructor
// -----------------------------------------------------------------------------
//
AknListBoxShortCutsImplementationExt::AknListBoxShortCutsImplementationExt( CEikListBox* aListBox) :
        AknListBoxShortCutsImplementation( aListBox )
    {
    }

// -----------------------------------------------------------------------------
// AknListBoxShortCutsImplementationExt::TestDoTest
// -----------------------------------------------------------------------------
//
TBool AknListBoxShortCutsImplementationExt::TestDoTest()
    {
    return DoTest( AknListBoxShortCuts::ENewItemFocused );
    }

// -----------------------------------------------------------------------------
// AknListBoxShortCutsImplementationExt::TestDoActionL
// -----------------------------------------------------------------------------
//
void AknListBoxShortCutsImplementationExt::TestDoActionL()
    {
    DoActionL( AknListBoxShortCuts::EShowShortcutNumber );
    }

