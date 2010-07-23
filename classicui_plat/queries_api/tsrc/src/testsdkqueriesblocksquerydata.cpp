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
* Description:  Test aknquerydata.h
*
*/

//INCLUDE
#include <aknquerydata.h>
#include <testsdkqueries.rsg>
#include <aknquerydialog.h>

#include "testsdkqueries.h"
#include "testsdkaknquerydialogprotected.h"

const TInt KZero = 0;
const TInt KFive = 5;
const TInt KTen = 10;
const TInt KBufSize = 32;
const TInt KHundred = 100;
_LIT( KTestString, "It is a test!" );

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdGetMaxTextLengthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdataGetMaxTextLengthL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    CAknNumberQueryDialog* numberDlg = new (ELeave) CAknNumberQueryDialog ( number );
    numberDlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    CTestCAknNumberQueryDialog* testNumberDlg = static_cast<CTestCAknNumberQueryDialog*>( numberDlg );
    CAknQueryControl* dlgControl = testNumberDlg->QueryControl();
    
    dlgControl->SetTextEntryLength( KFive );
    
    TBuf< KBufSize > buffer( KTestString );
    
    TInt length = GetMaxTextLength( dlgControl, buffer, KTen );
    STIF_ASSERT_EQUALS( KTen, length );
    
    length = GetMaxTextLength( dlgControl, buffer, KHundred );
    STIF_ASSERT_EQUALS( KFive, length );
    
    dlgControl->SetTextEntryLength( KZero );
    
    length = GetMaxTextLength( dlgControl, buffer, KHundred );
    STIF_ASSERT_EQUALS( KBufSize, length );
    
    CleanupStack::PopAndDestroy( numberDlg );
    return KErrNone;
    }

//End file


