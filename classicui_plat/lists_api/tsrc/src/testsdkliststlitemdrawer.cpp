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
* Description:  
*
*/


#include "testsdkliststlitemdrawer.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKListsTLItemDrawer::DoDrawItemText
// -----------------------------------------------------------------------------
//
CTestSDKListsTLItemDrawer::CTestSDKListsTLItemDrawer(MTextListBoxModel* aTextListBoxModel, 
                                                     const CFont* aFont)
                          : CTextListItemDrawer( aTextListBoxModel, aFont )
    {
    
    }
// -----------------------------------------------------------------------------
// CTestSDKListsTLItemDrawer::DoDrawItemText
// -----------------------------------------------------------------------------
//

void CTestSDKListsTLItemDrawer::DoDrawItemText(const TDesC& aDes, 
                                               const TRect& aItemTextRect, 
                                               TBool aItemIsCurrent, 
                                               TBool aViewIsEmphasized, 
                                               TBool aItemIsSelected, 
                                               TInt aItemIndex) const
    {
    CTextListItemDrawer::DoDrawItemText( aDes, aItemTextRect, aItemIsCurrent,
                                         aViewIsEmphasized, aItemIsSelected, aItemIndex );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsTLItemDrawer::DrawItemText
// -----------------------------------------------------------------------------
//

void CTestSDKListsTLItemDrawer::DrawItemText(TInt aItemIndex, 
                                             const TRect& aItemTextRect, 
                                             TBool aItemIsCurrent, 
                                             TBool aViewIsEmphasized, 
                                             TBool aItemIsSelected) const
    {
    CTextListItemDrawer::DrawItemText(aItemIndex, 
                                      aItemTextRect, 
                                      aItemIsCurrent, 
                                      aViewIsEmphasized, 
                                      aItemIsSelected);
    }

// -----------------------------------------------------------------------------
// CTestSDKListsTLItemDrawer::ResetGc
// -----------------------------------------------------------------------------
//

void CTestSDKListsTLItemDrawer::ResetGc() const
    {
    CTextListItemDrawer::ResetGc();
    }
