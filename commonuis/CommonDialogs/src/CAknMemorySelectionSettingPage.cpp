/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Setting page used to selection target memory.
*
*/



#include <commondialogs.rsg>
#include <pathinfo.h>
#include <driveinfo.h> //DriveInfo

#include "CAknMemorySelectionSettingPage.h"
#include "CAknMemorySelectionModel.h"       // KMemorySelectionGranularity
#include "CAknCommonDialogsRadioButtonSettingPage.h"
#include "CAknMemorySelectionEventHandler.h"
#include "MAknCommonDialogsEventObserver.h"
#include "AknCFDUtility.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingPage::CAknMemorySelectionSettingPage
// ---------------------------------------------------------------------------
//
CAknMemorySelectionSettingPage::CAknMemorySelectionSettingPage()
    :   CAknMemorySelectionDialog( ECFDDialogTypeDefaultSetting )
    {
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingPage::NewL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknMemorySelectionSettingPage* CAknMemorySelectionSettingPage::NewL()
    {
    return NewL( 0 );
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingPage::NewL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknMemorySelectionSettingPage* CAknMemorySelectionSettingPage::NewL(
    TInt aResourceId )
    {
    CAknMemorySelectionSettingPage* self = new( ELeave ) CAknMemorySelectionSettingPage();
    CleanupStack::PushL( self );
    self->ConstructFromResourceL( aResourceId, ETrue );
    CleanupStack::Pop(); // self
    return self;
    }

// Destructor
EXPORT_C CAknMemorySelectionSettingPage::~CAknMemorySelectionSettingPage()
    {
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingPage::ExecuteL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknCommonDialogsBase::TReturnKey CAknMemorySelectionSettingPage::ExecuteL(
    TMemory& aSelectedMemory )
    {
    return ExecuteL( aSelectedMemory, NULL, NULL );
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingPage::ExecuteL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknCommonDialogsBase::TReturnKey
    CAknMemorySelectionSettingPage::ExecuteL(
        TMemory& aSelectedMemory, TDes* aRootPath, TDes* aDefaultFolder )
    {
    __ASSERT_DEBUG( iTitle && iLeftSoftkey && iRightSoftkey,
        User::Panic( KCFDPanicText, ECFDPanicTitleOrSoftkeyNotSet ) );

    TInt selectedItem( aSelectedMemory );

    CAknCommonDialogsRadioButtonSettingPage* dlg =
        new( ELeave ) CAknCommonDialogsRadioButtonSettingPage(
        R_CFD_RADIOBUTTON_SETTING_PAGE, selectedItem, iModel, *iEventHandler, iModel );
    CleanupStack::PushL( dlg );
    dlg->ConstructL();
    dlg->SetSettingTextL( *iTitle );
    CEikButtonGroupContainer* cba = dlg->Cba();
    MEikButtonGroup* buttonGroup = cba->ButtonGroup();
    cba->SetCommandL( buttonGroup->CommandId( 0 ), *iLeftSoftkey );
    cba->SetCommandL( buttonGroup->CommandId( 2 ), *iRightSoftkey );

    TDriveNumber memoryCardDrive;
    User::LeaveIfError(
        DriveInfo::GetDefaultDrive( DriveInfo::EDefaultRemovableMassStorage,
                                    ( TInt& )memoryCardDrive ) );
    TCFDDriveStatus driveStatus = AknCFDUtility::DriveStatusL( memoryCardDrive );

    // If the selected memory is MMC but it is not ready, make LSK invisible:
    if( ( aSelectedMemory == EMemoryCard ) &&
        ( driveStatus == EDriveNotReady ) )
        {
        cba->MakeCommandVisible( buttonGroup->CommandId( 0 ),
                                 TBool( EFalse ) );
        }

    // Start listen to NotifyDisk only if MMC is unavailable
    TBool ifNotifyDisk = EFalse;
    if ( driveStatus ==  EDriveNotReady )
        {
        iEventHandler->StartNotifyDisk(dlg);
        ifNotifyDisk = ETrue;
        }

    // CAknSettingPage::ExecuteLD pushes itself to cleanup stack.
    CleanupStack::Pop(); // dlg
    TBool returnValue( dlg->ExecuteLD() );

    // Stop notifyDisk if started
    if (ifNotifyDisk)
        {
        iEventHandler->StopNotifyDisk();
        }

    if( returnValue ) // If user accepted selection
        {
        // Change value to user selected EEikListBoxMultipleSelection
        aSelectedMemory = TMemory( selectedItem );
        GetMemories( aSelectedMemory, aRootPath, aDefaultFolder );
        }
    // There is no need to know if the selection is done with left or right
    // softkey and there is no support for it in the
    // CAknCommonDialogsRadioButtonSettingPage
    return TReturnKey( returnValue );
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingPage::RunDlgLD
// A wrapper for RunL.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknMemorySelectionSettingPage::RunDlgLD(
    TMemory& aSelectedMemory,
    MAknMemorySelectionObserver* aObserver )
    {
    return RunL( 0, aSelectedMemory, KNullDesC, NULL, NULL, aObserver );
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingPage::RunDlgLD
// A wrapper for RunL.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknMemorySelectionSettingPage::RunDlgLD(
    TMemory& aSelectedMemory,
    const TDesC& aTitle,
    MAknMemorySelectionObserver* aObserver )
    {
    return RunL( 0, aSelectedMemory, aTitle, NULL, NULL, aObserver );
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingPage::RunDlgLD
// A wrapper for RunL.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknMemorySelectionSettingPage::RunDlgLD(
    TMemory& aSelectedMemory,
    TInt aResourceId,
    TDes* aRootPath, TDes* aDefaultFolder,
    MAknMemorySelectionObserver* aObserver )
    {
    return RunL( aResourceId, aSelectedMemory, KNullDesC, aRootPath, aDefaultFolder, aObserver );
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingPage::RunL
// ---------------------------------------------------------------------------
//
TBool CAknMemorySelectionSettingPage::RunL(
    TInt aResourceId,
    TMemory& aSelectedMemory,
    const TDesC& aTitle,
    TDes* aRootPath,
    TDes* aDefaultFolder,
    MAknMemorySelectionObserver* aObserver )
    {
    CAknMemorySelectionSettingPage* self =
        CAknMemorySelectionSettingPage::NewL( aResourceId );
    CleanupStack::PushL( self );
    self->iObserver = aObserver;
    self->SetTitleL( aTitle );

    TBool returnValue(
        self->ExecuteL( aSelectedMemory, aRootPath, aDefaultFolder )
        );

    CleanupStack::PopAndDestroy();
    return returnValue;
    }
