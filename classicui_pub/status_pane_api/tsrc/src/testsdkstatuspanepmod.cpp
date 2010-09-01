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
* Description:  test eikspmod.h
*
*/


#include "testsdkstatuspanepmod.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKStatusPanePmod::CTestSDKStatusPanePmod
// -----------------------------------------------------------------------------
CTestSDKStatusPanePmod::CTestSDKStatusPanePmod( CEikonEnv& aEikEnv ):CEikStatusPaneModelBase( aEikEnv )
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPanePmod::PaneInits
// -----------------------------------------------------------------------------
CEikStatusPaneSetInit* CTestSDKStatusPanePmod::PaneInits() const
    {
    return CEikStatusPaneModelBase::PaneInits();
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPanePmod::PaneInits
// -----------------------------------------------------------------------------
void CTestSDKStatusPanePmod::SetLayoutL( TInt aLayoutResId )
    {
    CEikStatusPaneModelBase::SetLayoutL( aLayoutResId );
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPanePmod::PaneInits
// -----------------------------------------------------------------------------
CEikStatusPaneLayout* CTestSDKStatusPanePmod::CurrentLayout() const
    {
    return CEikStatusPaneModelBase::CurrentLayout();
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPanePmod::PaneInits
// -----------------------------------------------------------------------------
TInt CTestSDKStatusPanePmod::CurrentLayoutResId() const
    {
    return CEikStatusPaneModelBase::CurrentLayoutResId();
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPanePmod::PaneInits
// -----------------------------------------------------------------------------
void CTestSDKStatusPanePmod::BaseConstructL( TInt aCoreResId )
    {
    CEikStatusPaneModelBase::BaseConstructL( aCoreResId );
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPanePmod::PaneInits
// -----------------------------------------------------------------------------
CEikStatusPaneLayout* CTestSDKStatusPanePmod::LoadLayoutL( TInt aLayoutResId )
    {
    return CEikStatusPaneModelBase::LoadLayoutL( aLayoutResId );
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPanePmod::PaneInits
// -----------------------------------------------------------------------------
CArrayFixFlat<TInt>* CTestSDKStatusPanePmod::LegalIds() const
    {
    return CEikStatusPaneModelBase::LegalIds();
    }
// End of file

