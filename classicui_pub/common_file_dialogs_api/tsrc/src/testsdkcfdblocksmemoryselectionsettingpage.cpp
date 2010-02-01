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
* Description:  Test CAknMemorySelectionSettingPage.h
*
*/


#include <testsdkcfd.rsg>

#include "testsdkcfd.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingPageNewLNoParaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingPageNewLNoParaL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KExample, "In TestSettingPageNewLNoPara" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KExample );
    iLog->Log( KExample );
    
    CAknMemorySelectionSettingPage* pagepointer = CAknMemorySelectionSettingPage::NewL();
    CleanupStack::PushL( pagepointer );
    STIF_ASSERT_NOT_NULL( pagepointer );
    CleanupStack::PopAndDestroy( pagepointer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingPageNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingPageNewL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KNewL, "In TestSettingPageNewL" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KNewL );
    iLog->Log(KNewL);
    
    iSettingPage = CAknMemorySelectionSettingPage::NewL( R_TEST_MEMORY_SELECTION_DIALOG );
    STIF_ASSERT_NOT_NULL( iSettingPage );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingPageExecuteLOnlyMemoryTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingPageExecuteLOnlyMemoryTypeL( CStifItemParser& aItem )
    {
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KExample, "In TestSettingPageExecuteLOnlyMemoryType" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    CAknMemorySelectionDialog::TMemory memorytype = CAknMemorySelectionDialog::EPhoneMemory;
    CAknCommonDialogsBase::TReturnKey returnkey;
    if( !iSettingPage )
        {
        iSettingPage = CAknMemorySelectionSettingPage::NewL();
        }

    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if( err != KErrNone)
        return err;
    switch ( num )
        {
        case ECaseOne:
            {
            returnkey = iSettingPage->ExecuteL(memorytype);
            STIF_ASSERT_EQUALS( CAknCommonDialogsBase::ELeftSoftkey, returnkey );
            STIF_ASSERT_EQUALS( CAknMemorySelectionDialog::EPhoneMemory, memorytype );
            break;
            }
        case ECaseTwo:
            {
            returnkey = iSettingPage->ExecuteL(memorytype);
            STIF_ASSERT_EQUALS( CAknCommonDialogsBase::ERightSoftkey, returnkey );
            STIF_ASSERT_EQUALS( CAknMemorySelectionDialog::EPhoneMemory, memorytype );
            break;
            }
        case ECaseThree:
            {
            returnkey = iSettingPage->ExecuteL(memorytype);
            //ESelectionKey in TReturnKey can't be getten in here, ELeftSoftkey will be return
            STIF_ASSERT_EQUALS( CAknCommonDialogsBase::ELeftSoftkey, returnkey );
            STIF_ASSERT_EQUALS( CAknMemorySelectionDialog::EPhoneMemory, memorytype );
            break;
            }
        default:
            return KErrNotSupported;
        }
    
    _LIT( KFinished, "TestSettingPageExecuteLOnlyMemoryTypeL finished" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KFinished );
    iLog->Log( KFinished );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingPageDeconstructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingPageDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknMemorySelectionSettingPage* pagepointer = CAknMemorySelectionSettingPage::NewL();
    CleanupStack::PushL( pagepointer );
    STIF_ASSERT_NOT_NULL( pagepointer );
    CleanupStack::PopAndDestroy( pagepointer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingPageRunDlgLDTwoParaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingPageRunDlgLDTwoParaL( CStifItemParser& aItem )
    {
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KExample, "In TestSettingPageRunDlgLDTwoParaL" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KExample );
    iLog->Log( KExample );
    
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    CCoeEnv::Static()->AppUi()->AddToStackL( control );
    TInt err = control->TestSettingPageRunLDL( aItem );
    CCoeEnv::Static()->AppUi()->RemoveFromStack( control );
    CleanupStack::PopAndDestroy( control );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingPageRunDlgLDThreeParaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingPageRunDlgLDThreeParaL( CStifItemParser& aItem )
    {
    //can't get the title because the object will be destoried after display 
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KExample, "In TestSettingPageRunDlgLDTwoParaL" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KExample );
    iLog->Log(KExample);

    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    CCoeEnv::Static()->AppUi()->AddToStackL( control );
    TInt err = control->TestSettingPageRunLDL( aItem );
    CCoeEnv::Static()->AppUi()->RemoveFromStack( control );
    CleanupStack::PopAndDestroy( control );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingPageRunDlgLDFiveParaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingPageRunDlgLDFiveParaL( CStifItemParser& aItem )
    {
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KExample, "In TestSettingPageRunDlgLDTwoParaL" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KExample );
    iLog->Log(KExample);

    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    CCoeEnv::Static()->AppUi()->AddToStackL( control );
    TInt err = control->TestSettingPageRunLDL( aItem );
    CCoeEnv::Static()->AppUi()->RemoveFromStack( control );
    CleanupStack::PopAndDestroy( control );

    return err;
    }

// End of File
