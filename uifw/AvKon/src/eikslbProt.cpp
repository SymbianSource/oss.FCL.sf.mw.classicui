/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Protected setting listbox item drawer implementation.
*
*/


#include "eikslbProt.h"

// ======== MEMBER FUNCTIONS ========

// -----------------------------------------------------------------------------
// CSettingsProtListBoxItemDrawer::CSettingsProtListBoxItemDrawer
// -----------------------------------------------------------------------------
//
CSettingsProtListBoxItemDrawer::CSettingsProtListBoxItemDrawer( 
    MTextListBoxModel* aTextListBoxModel,
    const CFont* aFont,
    CSettingsListBoxData* aSettingsData,
    CEikListBox* aListBox)
    : CSettingsListBoxItemDrawer( aTextListBoxModel, aFont, aSettingsData )
    {
    iListBox = aListBox;
    }

// -----------------------------------------------------------------------------
// CSettingsProtListBoxItemDrawer::DrawItemText
// -----------------------------------------------------------------------------
//
void CSettingsProtListBoxItemDrawer::DrawItemText( TInt aItemIndex,
                                                   const TRect& aItemTextRect,
                                                   TBool aItemIsCurrent,
                                                   TBool aViewIsEmphasized,
                                                   TBool aItemIsSelected ) const
    {
    CSettingsListBoxItemDrawer::DrawItemText( aItemIndex,
                                              aItemTextRect,
                                              aItemIsCurrent,
                                              aViewIsEmphasized,
                                              aItemIsSelected );
    }
