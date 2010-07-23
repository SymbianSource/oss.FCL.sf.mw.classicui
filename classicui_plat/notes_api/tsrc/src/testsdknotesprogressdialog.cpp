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
* Description:  Test AknProgressDialog.h 
*
*/


//  INCLUDES
#include "testsdknotesprogressdialog.h"

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::DialogDismissedL
// -----------------------------------------------------------------------------
void  CTestSDKNotesProgressDialog::DialogDismissedL (TInt /*aButtonId*/ )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::CTestSDKNotesProgressDialog
// -----------------------------------------------------------------------------
CTestSDKNotesProgressDialog::CTestSDKNotesProgressDialog( TInt aFinalValue,TInt anIncrement,TInt anInterval, CEikDialog** aSelfPtr ):CAknProgressDialog( aFinalValue, anIncrement, anInterval, aSelfPtr )
    {
    CAknProgressDialog::SetCallback(this);
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::PreLayoutDynInitL
// -----------------------------------------------------------------------------
void CTestSDKNotesProgressDialog::PreLayoutDynInitL()
    {
    CAknProgressDialog::PreLayoutDynInitL();
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::~CTestSDKNotesProgressDialog
// -----------------------------------------------------------------------------
CTestSDKNotesProgressDialog::~CTestSDKNotesProgressDialog()
    {
    delete iDialog;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::OkToExitL
// -----------------------------------------------------------------------------
TBool CTestSDKNotesProgressDialog::OkToExitL( TInt aButtonId )
    {
    return CAknProgressDialog::OkToExitL( aButtonId );
    }
