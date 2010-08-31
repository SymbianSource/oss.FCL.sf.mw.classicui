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
* Description:  Test EIKINFO.H
*
*/

#include <eikinfo.h>

#include "testsdknotes.h"

const TInt KLength = 10;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNCEikInfoDialogL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNCEikInfoDialogL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KTitle, "Title" );
    _LIT( KMsg, "Msg" );
    TBuf<KLength> title( KTitle );
    TBuf<KLength> msg( KMsg );
    
    CEikInfoDialog* dialog = new (ELeave) CEikInfoDialog( title, msg );
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::PopAndDestroy( dialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNCEikInfoDialogL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNRunDlgLD( CStifItemParser& /*aItem*/ )
    {
    _LIT( KTitle, "Title" );
    _LIT( KMsg, "Msg" );
    TBuf<KLength> title( KTitle );
    TBuf<KLength> msg( KMsg );
    
    CEikInfoDialog* dialog = new (ELeave) CEikInfoDialog(  title, msg, CEikInfoDialog::EAllowEnter );
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    TBool flag = dialog->RunDlgLD( title, msg );
    
    delete dialog;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNHandlePointerEventL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KTitle, "Title" );
    _LIT( KMsg, "Msg" );
    TBuf<KLength> title( KTitle );
    TBuf<KLength> msg( KMsg );
    
    CEikInfoDialog* dialog = new (ELeave) CEikInfoDialog( title, msg );
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton2Up;
    dialog->HandlePointerEventL( event );
    CleanupStack::Pop( dialog );
    
    TBool flag = dialog->RunDlgLD( title, msg );
    delete dialog;
    
    return KErrNone;
    
    }
