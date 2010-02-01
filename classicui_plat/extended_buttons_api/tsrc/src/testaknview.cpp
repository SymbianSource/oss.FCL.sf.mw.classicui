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
* Description:  function implement of CTestAknView
*
*/


// INCLUDE FILES
#include "testaknview.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestAknView::CTestAknView
// -----------------------------------------------------------------------------
//
CTestAknView::CTestAknView(): CAknView()
    {
    }

// -----------------------------------------------------------------------------
// CTestAknView::Id
// -----------------------------------------------------------------------------
//
TUid CTestAknView::Id() const
    {
    return TUid::Null();
    }

// -----------------------------------------------------------------------------
// CTestAknView::DoActivateL
// -----------------------------------------------------------------------------
//
void CTestAknView::DoActivateL( const TVwsViewId& /*aPrevViewId*/,
        TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestAknView::DoDeactivate
// -----------------------------------------------------------------------------
//
void CTestAknView::DoDeactivate()
    {
    }


// End of File
