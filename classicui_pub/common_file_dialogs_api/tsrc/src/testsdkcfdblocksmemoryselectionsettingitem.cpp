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
* Description:  Test CAknMemorySelectionSettingItem.h
 *
*/


// [INCLUDE FILES]
#include <aknsettingitemlist.h> 
#include <testsdkcfd.rsg>

#include "testsdkcfd.h"
#include "testsdkcfdsettingitem.h"

// CONSTS
const TInt KBufSize = 64;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingItemConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingItemConstructorL(CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KExample, "In TestSettingItemConstructorL" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KExample );
    iLog->Log(KExample);

    iSettingItemList = new (ELeave) CTestSettingItemList;
    iSettingItemList->ConstructL();
    STIF_ASSERT_NOT_NULL( iSettingItemList );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingItemDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingItemDeconstructorL(CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KExample, "In TestSettingItemDeconstructorL" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KExample );
    iLog->Log(KExample);
    
    CTestSettingItemList* temp = new (ELeave) CTestSettingItemList;
    CleanupStack::PushL( temp );
    temp->ConstructL();
    CleanupStack::PopAndDestroy( temp );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingItemCompleteConstructionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingItemCompleteConstructionL(CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KExample, "In TestSettingItemCompleteConstructionL" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KExample );
    iLog->Log(KExample);
    
    if ( !iSettingItemList )
        {
        iSettingItemList = new (ELeave) CTestSettingItemList;
        iSettingItemList->ConstructL();
        }
//    iSettingItemList->iItem->CompleteConstructionL();
    CAknMemorySelectionSettingPage* temp= NULL;
    temp = iSettingItemList->iItem->GetSettingPagePointer();
    STIF_ASSERT_NOT_NULL( temp );
    temp = NULL;
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingItemEditItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingItemEditItemL(CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KExample, "In TestSettingItemEditItemL" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KExample );
    iLog->Log(KExample);
    if ( !iSettingItemList )
        {
        iSettingItemList = new (ELeave) CTestSettingItemList;
        iSettingItemList->ConstructL();
        }
    iSettingItemList->EditItemL(0, ETrue);
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingItemLoadL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingItemLoadL(CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KExample, "In TestSettingItemLoadL" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KExample );
    iLog->Log(KExample);

    if ( !iSettingItemList )
        {
        iSettingItemList = new (ELeave) CTestSettingItemList;
        iSettingItemList->ConstructL();
        }
    
    CAknMemorySelectionDialog::TMemory backtpye = iSettingItemList->iItem->GetInternalData();
    STIF_ASSERT_EQUALS( CAknMemorySelectionDialog::EPhoneMemory, backtpye );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingItemStoreL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingItemStoreL(CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KExample, "In TestSettingItemStoreL" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KExample );
    iLog->Log(KExample);

    if ( !iSettingItemList )
            {
            iSettingItemList = new (ELeave) CTestSettingItemList;
            iSettingItemList->ConstructL();
            }
    iSettingItemList->StoreSettingsL();
    CAknMemorySelectionDialog::TMemory backtpye = iSettingItemList->iItem->GetExternalData();
    STIF_ASSERT_EQUALS( CAknMemorySelectionDialog::EPhoneMemory, backtpye );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingItemSettingTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingItemSettingTextL(CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KExample, "In TestSettingItemSettingTextL" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KExample );
    iLog->Log(KExample);

    if ( !iSettingItemList )
            {
            iSettingItemList = new (ELeave) CTestSettingItemList;
            iSettingItemList->ConstructL();
            }
    
    iSettingItemList->iItem->GetSettingText();
    TBuf<KBufSize> buf;
    iSettingItemList->iItem->GetText( buf );
// sth need to do
    return KErrNone;
    }

// End of File
