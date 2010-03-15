/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Setting item to support multiple drives.
*
*/


#include <driveinfo.h>

#include "CAknMemorySelectionSettingItemMultiDrive.h"
#include "CAknMemorySelectionDialogMultiDrive.h"
#include "maknmemoryselectionmodel.h"
#include "AknCFDUtility.h"
#include "CAknCFDFileSystemEvent.h"
#include "MAknCFDFileSystemObserver.h"


NONSHARABLE_CLASS(CAknMemorySelectionSettingItemExtension)
    : public CBase,
      public MAknCFDFileSystemObserver
    {

public:
    CAknMemorySelectionSettingItemExtension(
        CAknMemorySelectionSettingItemMultiDrive* aSettingItem );
    ~CAknMemorySelectionSettingItemExtension();

    /**
     * second phase construct
     *
     * @param aIncludedMedias bit flag definition of which medias are
     *        included in the dialog. See AknCommonDialogsDynMem::TMemoryTypes.
     */
    void ConstructL( TInt aIncludedMedias );
    
    /**
     * Static constructor.
     *
     * @since S60 5.0
     * @param aSettingItem defines a pointer to the setting item. 
     * @param aIncludedMedias bit flag definition of which medias are
     *        included in the dialog. See AknCommonDialogsDynMem::TMemoryTypes.
     *        if not set, use dialog default value.
     * @return Returns a pointer to an instance of itself.
     */
    static CAknMemorySelectionSettingItemExtension* NewL(
        CAknMemorySelectionSettingItemMultiDrive* aSettingItem,
        TInt aIncludedMedias = -1 );
    
    /**
     * Construct memory selection dialog
     *
     * @param aIncludedMedias bit flag definition of which medias are
     *        included in the dialog. See AknCommonDialogsDynMem::TMemoryTypes.
     */
    void ConstructDialogL( TInt aIncludedMedias );
    
    // Functions from base interface MAknCFDFileSystemObserver
    /**
     * From MAknCFDFileSystemObserver
     */
    void NotifyFileSystemChangedL();
    
    // Own: memory selection dialog
    CAknMemorySelectionDialogMultiDrive* iDialog;
    
    // Ref: The external data
    CAknMemorySelectionSettingItemMultiDrive* iSettingItem;
    
    // Own: The extension of setting item
    CAknCFDFileSystemEvent* iFSEvent;
    
    // Own: Indicate which media types of drives could be visible.
    TInt iIncludedMedias;
    };

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItem::CAknMemorySelectionSettingItem
// ---------------------------------------------------------------------------
//
EXPORT_C CAknMemorySelectionSettingItemMultiDrive
    ::CAknMemorySelectionSettingItemMultiDrive(
        TInt aIdentifier,
        TDriveNumber& aSelectedDrive )
        :   CAknSettingItem( aIdentifier ),
            iExternalData( aSelectedDrive )
    {
    
    }

// Destructor
EXPORT_C CAknMemorySelectionSettingItemMultiDrive::
    ~CAknMemorySelectionSettingItemMultiDrive()
    {
    delete iSettingText;
    delete iExtension, iExtension = NULL;
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItemMultiDrive::CompleteConstructionL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemorySelectionSettingItemMultiDrive::CompleteConstructionL()
    {
    if ( !iExtension )
        {
        iExtension = CAknMemorySelectionSettingItemExtension::NewL( this );
        }
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItemMultiDrive::EditItemL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemorySelectionSettingItemMultiDrive::EditItemL(
    TBool aCalledFromMenu )
    {
    if( !iExtension )
        {
        // This in case application hasn't called CompleteConstructionL()
        CompleteConstructionL();
        }

    if( aCalledFromMenu )
        {
        // Changed with Options/Change
        iExtension->iDialog->ExecuteL( iInternalData, NULL, NULL );
        }
    else
        {
        // Changed with selection key
        if( ( iExtension->iDialog->NumberOfItems() == 2 ) )
            {
            // Two items in list, function as binary pop-up setting page
            TInt selectedIndex =
                iExtension->iDialog->FindIndexByDrive( iInternalData );
	          if ( selectedIndex == KErrNotFound )
	              {
	              selectedIndex = 0;
	              }
	          else
	              {
                  TDriveNumber driveNum =
                      iExtension->iDialog->FindDriveByIndex( 1 - selectedIndex );
                  if ( AknCFDUtility::DriveStatusL( driveNum ) == EDriveOK )
                      {
                      selectedIndex = 1 - selectedIndex; // switch to another one.
                      }
	              }
            iInternalData =
                iExtension->iDialog->FindDriveByIndex( selectedIndex );
            }
        else
            {
            iExtension->iDialog->ExecuteL( iInternalData, NULL, NULL );
            }
        }

    UpdateListBoxTextL();

    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItemMultiDrive::LoadL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemorySelectionSettingItemMultiDrive::LoadL()
    {
    iInternalData = iExternalData;
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItemMultiDrive::StoreL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemorySelectionSettingItemMultiDrive::StoreL()
    {
    iExternalData = iInternalData;
    
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItemMultiDrive::SettingTextL
// ---------------------------------------------------------------------------
//
EXPORT_C const TDesC& CAknMemorySelectionSettingItemMultiDrive::SettingTextL()
    {
    if( !iExtension )
        {
        // This in case application hasn't called CompleteConstructionL()
        CompleteConstructionL();
        }

    TInt memoryIndex = iExtension->iDialog->FindIndexByDrive( iInternalData );
    if ( AknCFDUtility::DriveStatusL( iInternalData ) != EDriveOK )
        {
        // Find the first proper drive in the dialog list.
        memoryIndex = 0;
        while ( memoryIndex < iExtension->iDialog->NumberOfItems() )
            {
            iInternalData = iExtension->iDialog->FindDriveByIndex( memoryIndex );
            if ( AknCFDUtility::DriveStatusL( iInternalData ) == EDriveOK )
                {
                break;
                }
            memoryIndex++;
            }
        // Not find the proper drive.
        if ( memoryIndex == iExtension->iDialog->NumberOfItems() )
            {
            iInternalData = EDriveC;
            memoryIndex = KErrNotFound;
            }
        }

    if ( memoryIndex == KErrNotFound )
        {
        return KNullDesC;
        }

    if( !iSettingText )
        iSettingText = HBufC::NewL( KMaxName );
    TPtr ptrSettingText( iSettingText->Des() );
    iExtension->iDialog->GetItem( memoryIndex, ptrSettingText );

    return *iSettingText;
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItemMultiDrive::UpdateSettingItemContentL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionSettingItemMultiDrive::UpdateSettingItemContentL()
    {
    if ( iExtension->iDialog != NULL )
        {
        // Update model.
        iExtension->iDialog->UpdateModelL();

        // Update setting item value.
        TInt selectedIndex = iExtension->iDialog->
            FindIndexByDrive( iInternalData );

        if ( selectedIndex == KErrNotFound )
            {
            // If the selected index is not found, set it to the first one
            selectedIndex = 0;
            }
        iInternalData = iExtension->iDialog->FindDriveByIndex( selectedIndex );

        UpdateListBoxTextL();
        }
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItemMultiDrive::SetIncludedMediasL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemorySelectionSettingItemMultiDrive::SetIncludedMediasL(
    TInt aIncludedMedias )
    {
    if ( !iExtension )
        {
        iExtension = CAknMemorySelectionSettingItemExtension::NewL(
            this, aIncludedMedias );
        }
    else if ( iExtension->iIncludedMedias != aIncludedMedias )
        {
        iExtension->ConstructDialogL( aIncludedMedias );
        }
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItemExtension
// Constructor
// ---------------------------------------------------------------------------
//
CAknMemorySelectionSettingItemExtension::
    CAknMemorySelectionSettingItemExtension(
        CAknMemorySelectionSettingItemMultiDrive* aSettingItem )
        : iSettingItem( aSettingItem )
    {
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItemExtension
// Constructor
// ---------------------------------------------------------------------------
//
CAknMemorySelectionSettingItemExtension::
    ~CAknMemorySelectionSettingItemExtension()
    {
    delete iDialog;
    iDialog = NULL;
    
    if ( iFSEvent )
        {
        iFSEvent->Cancel();
        delete iFSEvent;
        iFSEvent = NULL;
        }
        
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItemExtension
// NotifyFileSystemChangedL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionSettingItemExtension::NotifyFileSystemChangedL()
    {
    iSettingItem->UpdateSettingItemContentL();
    
    if (iFSEvent != NULL)
        {
        iFSEvent->Setup();
        }
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItemExtension
// ConstructDialogL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionSettingItemExtension::ConstructDialogL(
    TInt aIncludedMedias )
    {
    if ( iDialog )
        {
        delete iDialog;
        iDialog = NULL;
        }
    
    iIncludedMedias = aIncludedMedias;
    
    if ( aIncludedMedias == -1 )
        {
        iDialog = CAknMemorySelectionDialogMultiDrive::NewL(
            ECFDDialogTypeNormal, ETrue );
        }
    else
        {
        iDialog = CAknMemorySelectionDialogMultiDrive::NewL( 
            ECFDDialogTypeNormal, 0, ETrue, aIncludedMedias );
        }
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItemExtension
// ConstructL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionSettingItemExtension::ConstructL( TInt aIncludedMedias )
    {
    ConstructDialogL( aIncludedMedias );
    
    iFSEvent = CAknCFDFileSystemEvent::NewL(
        CCoeEnv::Static()->FsSession(), *this, ENotifyDisk );
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionSettingItemExtension
// NewL
// ---------------------------------------------------------------------------
//
CAknMemorySelectionSettingItemExtension*
    CAknMemorySelectionSettingItemExtension::NewL(
        CAknMemorySelectionSettingItemMultiDrive* aSettingItem,
        TInt aIncludedMedias )
    {
    CAknMemorySelectionSettingItemExtension* self =
        new( ELeave ) CAknMemorySelectionSettingItemExtension( aSettingItem );

    CleanupStack::PushL( self );
    self->ConstructL( aIncludedMedias );
    CleanupStack::Pop( self );

    return self;
    }
