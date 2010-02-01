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
* Description:  test aknshortcuts.h
*
*/


#include <aknshortcuts.h>
#include <eiktxlbx.h> 
#include <barsread.h>
#include <coemain.h>
#include <eiklbm.h>
#include <eiktxlbm.h>

#include <testdomlists.rsg>
#include "testdomlists.h"
#include "testdomlistscontainer.h"
#include "testdomlistsext.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMLists::TestTempConstructL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestTempConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestTempConstructL, "In TempConstructL" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestTempConstructL );
    // Print to log file
    iLog->Log( KTestTempConstructL );

    AknListBoxShortCutTemplate<CEikTextListBox>* shortCut = new ( ELeave )
            AknListBoxShortCutTemplate<CEikTextListBox>;
    CleanupStack::PushL( shortCut );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );

    shortCut->ConstructL( container, EAknListBoxIncrementalMatching );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( shortCut );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestTempConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestTempConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestTempConstructFromResourceL, "In TempConstructFromResourceL" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestTempConstructFromResourceL );
    // Print to log file
    iLog->Log( KTestTempConstructFromResourceL );

    AknListBoxShortCutTemplate<CEikTextListBox>* shortCut = new ( ELeave )
            AknListBoxShortCutTemplate<CEikTextListBox>;
    CleanupStack::PushL( shortCut );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    shortCut->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LISTBOX );
    shortCut->ConstructFromResourceL( reader );

    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( shortCut );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestTempOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestTempOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestTempOfferKeyEventL, "In TempOfferKeyEventL" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestTempOfferKeyEventL );
    // Print to log file
    iLog->Log( KTestTempOfferKeyEventL );

    AknListBoxShortCutTemplate<CEikTextListBox>* shortCut = new ( ELeave )
            AknListBoxShortCutTemplate<CEikTextListBox>;
    CleanupStack::PushL( shortCut );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    shortCut->ConstructL( container, EAknListBoxIncrementalMatching );

    TKeyEvent keyEvent;
    keyEvent.iScanCode = EStdKeyEnter;
    TKeyResponse keyResponse = shortCut->OfferKeyEventL( keyEvent, EEventKey );
    STIF_ASSERT_TRUE( keyResponse == EKeyWasNotConsumed );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( shortCut );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestTempShortcutValueForNextListL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestTempShortcutValueForNextListL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestTempShortcutValueForNextList, "In TempShortcutValueForNextList" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestTempShortcutValueForNextList );
    // Print to log file
    iLog->Log( KTestTempShortcutValueForNextList );

    AknListBoxShortCutTemplate<CEikTextListBox>* shortCut = new ( ELeave )
            AknListBoxShortCutTemplate<CEikTextListBox>;
    CleanupStack::PushL( shortCut );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    shortCut->ConstructL( container, EAknListBoxIncrementalMatching );

    TInt value = shortCut->ShortcutValueForNextList();
    STIF_ASSERT_EQUALS( 0, value );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( shortCut );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestTempSetShortcutValueFromPrevListL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestTempSetShortcutValueFromPrevListL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestTempSetShortcutValueFromPrevList, "In TempSetShortcutValueFromPrevList" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestTempSetShortcutValueFromPrevList );
    // Print to log file
    iLog->Log( KTestTempSetShortcutValueFromPrevList );

    AknListBoxShortCutTemplate<CEikTextListBox>* shortCut = new ( ELeave )
            AknListBoxShortCutTemplate<CEikTextListBox>;
    CleanupStack::PushL( shortCut );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    shortCut->ConstructL( container, EAknListBoxIncrementalMatching );

    shortCut->SetShortcutValueFromPrevList( 0 );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( shortCut );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestTempSetShortcutEnabledL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestTempSetShortcutEnabledL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestTempSetShortcutEnabledL, "In TempSetShortcutEnabledL" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestTempSetShortcutEnabledL );
    // Print to log file
    iLog->Log( KTestTempSetShortcutEnabledL );

    AknListBoxShortCutTemplate<CEikTextListBox>* shortCut = new ( ELeave )
            AknListBoxShortCutTemplate<CEikTextListBox>;
    CleanupStack::PushL( shortCut );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    shortCut->ConstructL( container, EAknListBoxIncrementalMatching );

    shortCut->SetShortcutEnabledL( 0 );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( shortCut );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestCutsDefConL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestCutsDefConL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestCutsDefCon, "In CutsDefCon" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestCutsDefCon );
    // Print to log file
    iLog->Log( KTestCutsDefCon );

    AknListBoxShortCutsExt* shortCutExt = new ( ELeave ) AknListBoxShortCutsExt;
    CleanupStack::PushL( shortCutExt );
    STIF_ASSERT_NOT_NULL( shortCutExt );

    CleanupStack::PopAndDestroy( shortCutExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestCutsConstructL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestCutsConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestCutsConstructL, "In CutsConstructL" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestCutsConstructL );
    // Print to log file
    iLog->Log( KTestCutsConstructL );

    AknListBoxShortCutsExt* shortCutExt = new ( ELeave ) AknListBoxShortCutsExt;
    CleanupStack::PushL( shortCutExt );

    shortCutExt->ConstructL();

    CleanupStack::PopAndDestroy( shortCutExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestCutsOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestCutsOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestCutsOfferKeyEventL, "In CutsOfferKeyEventL" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestCutsOfferKeyEventL );
    // Print to log file
    iLog->Log( KTestCutsOfferKeyEventL );

    AknListBoxShortCutsExt* shortCutExt = new ( ELeave ) AknListBoxShortCutsExt;
    CleanupStack::PushL( shortCutExt );
    shortCutExt->ConstructL();

    TKeyEvent keyEvent;
    keyEvent.iScanCode = EStdKeyEnter;
    TKeyResponse keyResponse = shortCutExt->OfferKeyEventL( keyEvent, EEventKey );
    STIF_ASSERT_TRUE( keyResponse == EKeyWasNotConsumed );

    CleanupStack::PopAndDestroy( shortCutExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestCutsRecursionLockL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestCutsRecursionLockL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestCutsRecursionLock, "In CutsRecursionLock" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestCutsRecursionLock );
    // Print to log file
    iLog->Log( KTestCutsRecursionLock );

    AknListBoxShortCutsExt* shortCutExt = new ( ELeave ) AknListBoxShortCutsExt;
    CleanupStack::PushL( shortCutExt );
    shortCutExt->ConstructL();

    TBool lock = shortCutExt->RecursionLock();
    STIF_ASSERT_TRUE( lock );

    CleanupStack::PopAndDestroy( shortCutExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestCutsRecursionUnlockL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestCutsRecursionUnlockL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestCutsRecursionUnlock, "In CutsRecursionUnlock" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestCutsRecursionUnlock );
    // Print to log file
    iLog->Log( KTestCutsRecursionUnlock );

    AknListBoxShortCutsExt* shortCutExt = new ( ELeave ) AknListBoxShortCutsExt;
    CleanupStack::PushL( shortCutExt );
    shortCutExt->ConstructL();

    shortCutExt->RecursionUnlock();

    CleanupStack::PopAndDestroy( shortCutExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestCutsRunL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestCutsRunL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestCutsRunL, "In CutsRunL" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestCutsRunL );
    // Print to log file
    iLog->Log( KTestCutsRunL );

    AknListBoxShortCutsExt* shortCutExt = new ( ELeave ) AknListBoxShortCutsExt;
    CleanupStack::PushL( shortCutExt );
    shortCutExt->ConstructL();

    shortCutExt->RunL();

    CleanupStack::PopAndDestroy( shortCutExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestCutsChangeStateL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestCutsChangeStateL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestCutsChangeStateL, "In CutsChangeStateL" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestCutsChangeStateL );
    // Print to log file
    iLog->Log( KTestCutsChangeStateL );

    AknListBoxShortCutsExt* shortCutExt = new ( ELeave ) AknListBoxShortCutsExt;
    CleanupStack::PushL( shortCutExt );
    shortCutExt->ConstructL();

    shortCutExt->DoChangeStateL();

    CleanupStack::PopAndDestroy( shortCutExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestCutsDoProcedureL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestCutsDoProcedureL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestCutsDoProcedureL, "In CutsDoProcedureL" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestCutsDoProcedureL );
    // Print to log file
    iLog->Log( KTestCutsDoProcedureL );

    AknListBoxShortCutsExt* shortCutExt = new ( ELeave ) AknListBoxShortCutsExt;
    CleanupStack::PushL( shortCutExt );
    shortCutExt->ConstructL();

    shortCutExt->DoProcedureL();

    CleanupStack::PopAndDestroy( shortCutExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestCutsStartTimerL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestCutsStartTimerL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestCutsStartTimerL, "In CutsStartTimerL" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestCutsStartTimerL );
    // Print to log file
    iLog->Log( KTestCutsStartTimerL );

    AknListBoxShortCutsExt* shortCutExt = new ( ELeave ) AknListBoxShortCutsExt;
    CleanupStack::PushL( shortCutExt );
    shortCutExt->ConstructL();

    shortCutExt->DoStartTimerL();

    CleanupStack::PopAndDestroy( shortCutExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestCutsEndTimerL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestCutsEndTimerL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestCutsEndTimer, "In CutsEndTimer" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestCutsEndTimer );
    // Print to log file
    iLog->Log( KTestCutsEndTimer );

    AknListBoxShortCutsExt* shortCutExt = new ( ELeave ) AknListBoxShortCutsExt;
    CleanupStack::PushL( shortCutExt );
    shortCutExt->ConstructL();

    shortCutExt->EndTimer();

    CleanupStack::PopAndDestroy( shortCutExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestImpleDefConL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestImpleDefConL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestImpleDefCon, "In ImpleDefCon" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestImpleDefCon );
    // Print to log file
    iLog->Log( KTestImpleDefCon );

    CEikTextListBox* listBox = new ( ELeave ) CEikTextListBox;
    CleanupStack::PushL( listBox );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    listBox->ConstructL( container, EAknListBoxIncrementalMatching );
    CTextListBoxModel* model = listBox->Model();
    model->SetOwnershipType( ELbmDoesNotOwnItemArray );

    AknListBoxShortCutsImplementation* implement = new ( ELeave )
            AknListBoxShortCutsImplementation( listBox );
    CleanupStack::PushL( implement );
    STIF_ASSERT_NOT_NULL( implement );

    CleanupStack::PopAndDestroy( implement );
    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( listBox );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestImpleConstructL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestImpleConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestImpleConstructL, "In ImpleConstructL" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestImpleConstructL );
    // Print to log file
    iLog->Log( KTestImpleConstructL );

    CEikTextListBox* listBox = new ( ELeave ) CEikTextListBox;
    CleanupStack::PushL( listBox );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    listBox->ConstructL( container, EAknListBoxIncrementalMatching );
    CTextListBoxModel* model = listBox->Model();
    model->SetOwnershipType( ELbmDoesNotOwnItemArray );

    AknListBoxShortCutsImplementation* implement = new ( ELeave )
            AknListBoxShortCutsImplementation( listBox );
    CleanupStack::PushL( implement );

    implement->ConstructL();

    CleanupStack::PopAndDestroy( implement );
    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( listBox );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestImpleDoTestL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestImpleDoTestL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestImpleDoTest, "In ImpleDoTest" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestImpleDoTest );
    // Print to log file
    iLog->Log( KTestImpleDoTest );

    CEikTextListBox* listBox = new ( ELeave ) CEikTextListBox;
    CleanupStack::PushL( listBox );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    listBox->ConstructL( container, EAknListBoxIncrementalMatching );
    CTextListBoxModel* model = listBox->Model();
    model->SetOwnershipType( ELbmDoesNotOwnItemArray );

    AknListBoxShortCutsImplementationExt* implementExt = new ( ELeave )
            AknListBoxShortCutsImplementationExt( listBox );
    CleanupStack::PushL( implementExt );
    implementExt->ConstructL();

    TBool test = implementExt->TestDoTest();
    STIF_ASSERT_TRUE( test );

    CleanupStack::PopAndDestroy( implementExt );
    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( listBox );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestImpleDoActionL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestImpleDoActionL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestImpleDoActionL, "In ImpleDoActionL" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestImpleDoActionL );
    // Print to log file
    iLog->Log( KTestImpleDoActionL );

    CEikTextListBox* listBox = new ( ELeave ) CEikTextListBox;
    CleanupStack::PushL( listBox );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    listBox->ConstructL( container, EAknListBoxIncrementalMatching );
    CTextListBoxModel* model = listBox->Model();
    model->SetOwnershipType( ELbmDoesNotOwnItemArray );

    AknListBoxShortCutsImplementationExt* implementExt = new ( ELeave )
            AknListBoxShortCutsImplementationExt( listBox );
    CleanupStack::PushL( implementExt );
    implementExt->ConstructL();

    implementExt->TestDoActionL();

    CleanupStack::PopAndDestroy( implementExt );
    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( listBox );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestImpleOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestImpleOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestImpleOfferKeyEventL, "In ImpleOfferKeyEventL" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestImpleOfferKeyEventL );
    // Print to log file
    iLog->Log( KTestImpleOfferKeyEventL );

    CEikTextListBox* listBox = new ( ELeave ) CEikTextListBox;
    CleanupStack::PushL( listBox );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    listBox->ConstructL( container, EAknListBoxIncrementalMatching );
    CTextListBoxModel* model = listBox->Model();
    model->SetOwnershipType( ELbmDoesNotOwnItemArray );

    AknListBoxShortCutsImplementation* implement = new ( ELeave )
            AknListBoxShortCutsImplementation( listBox );
    CleanupStack::PushL( implement );
    implement->ConstructL();

    TKeyEvent keyEvent;
    keyEvent.iScanCode = EStdKeyEnter;
    TKeyResponse keyResponse = implement->OfferKeyEventL( keyEvent, EEventKey );
    STIF_ASSERT_TRUE( keyResponse == EKeyWasNotConsumed );

    CleanupStack::PopAndDestroy( implement );
    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( listBox );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestImpleShortcutValueForNextListL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestImpleShortcutValueForNextListL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestImpleShortcutValueForNextList, "In ImpleShortcutValueForNextList" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestImpleShortcutValueForNextList );
    // Print to log file
    iLog->Log( KTestImpleShortcutValueForNextList );

    CEikTextListBox* listBox = new ( ELeave ) CEikTextListBox;
    CleanupStack::PushL( listBox );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    listBox->ConstructL( container, EAknListBoxIncrementalMatching );
    CTextListBoxModel* model = listBox->Model();
    model->SetOwnershipType( ELbmDoesNotOwnItemArray );

    AknListBoxShortCutsImplementation* implement = new ( ELeave )
            AknListBoxShortCutsImplementation( listBox );
    CleanupStack::PushL( implement );
    implement->ConstructL();

    TInt value = implement->ShortcutValueForNextList();
    STIF_ASSERT_EQUALS( 0, value );

    CleanupStack::PopAndDestroy( implement );
    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( listBox );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestImpleSetShortcutValueFromPrevListL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestImpleSetShortcutValueFromPrevListL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestImpleSetShortcutValueFromPrevList, "In ImpleSetShortcutValueFromPrevList" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestImpleSetShortcutValueFromPrevList );
    // Print to log file
    iLog->Log( KTestImpleSetShortcutValueFromPrevList );

    CEikTextListBox* listBox = new ( ELeave ) CEikTextListBox;
    CleanupStack::PushL( listBox );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    listBox->ConstructL( container, EAknListBoxIncrementalMatching );
    CTextListBoxModel* model = listBox->Model();
    model->SetOwnershipType( ELbmDoesNotOwnItemArray );

    AknListBoxShortCutsImplementation* implement = new ( ELeave )
            AknListBoxShortCutsImplementation( listBox );
    CleanupStack::PushL( implement );
    implement->ConstructL();

    implement->SetShortcutValueFromPrevList( 0 );

    CleanupStack::PopAndDestroy( implement );
    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( listBox );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestImpleProcessCommandL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestImpleProcessCommandL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestImpleProcessCommandL, "In ImpleProcessCommandL" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestImpleProcessCommandL );
    // Print to log file
    iLog->Log( KTestImpleProcessCommandL );

    CEikTextListBox* listBox = new ( ELeave ) CEikTextListBox;
    CleanupStack::PushL( listBox );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    listBox->ConstructL( container, EAknListBoxIncrementalMatching );
    CTextListBoxModel* model = listBox->Model();
    model->SetOwnershipType( ELbmDoesNotOwnItemArray );

    AknListBoxShortCutsImplementation* implement = new ( ELeave )
            AknListBoxShortCutsImplementation( listBox );
    CleanupStack::PushL( implement );
    implement->ConstructL();

    implement->ProcessCommandL( 0 );

    CleanupStack::PopAndDestroy( implement );
    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( listBox );
    return KErrNone;

    }


