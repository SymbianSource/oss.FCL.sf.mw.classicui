/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Model used in listbox of memory selection dialog.
*
*/


// INCLUDES
#include "CAknMemorySelectionModel.h"
#include "CAknCommonDialogsBase.h"
#include "AknCFDUtility.h"

#include <coemain.h>
#include <StringLoader.h>
#include <commondialogs.rsg>

#include <pathinfo.h> //PathInfo
#include <driveinfo.h> //DriveInfo

// CONSTANTS
const TInt KListBoxEntryMaxLength( KMaxFileName + 32 );

_LIT( KImageHeader, "%d" );
_LIT( KTabChar, "\t" );


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknMemorySelectionModel::CAknMemorySelectionModel
//
//
// -----------------------------------------------------------------------------
//
CAknMemorySelectionModel::CAknMemorySelectionModel(
	CCoeEnv* aCoeEnv,
	MDesCArray* aDriveArray,
	TBool aShowUnavailable,
	TListBoxLayout aLayout )
	:	iCoeEnv( aCoeEnv ),
		iDriveArray( aDriveArray ),
		iShowUnavailable( aShowUnavailable ),
		iLayout( aLayout )
	{
	}

// -----------------------------------------------------------------------------
// CAknMemorySelectionModel::ConstructL
//
// -----------------------------------------------------------------------------
//
void CAknMemorySelectionModel::ConstructL()
	{
	ReadResourcesL();
	UpdateItemsL();
	}

// -----------------------------------------------------------------------------
// CAknMemorySelectionModel::NewL
//
// -----------------------------------------------------------------------------
//
CAknMemorySelectionModel* CAknMemorySelectionModel::NewL(
	CCoeEnv* aCoeEnv,
	MDesCArray* aDriveArray,
	TBool aShowUnavailable,
	TListBoxLayout aLayout )
	{
	CAknMemorySelectionModel* self = new( ELeave ) CAknMemorySelectionModel(
		aCoeEnv, aDriveArray, aShowUnavailable, aLayout );
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}

// Destructor
CAknMemorySelectionModel::~CAknMemorySelectionModel()
	{
	iListBoxArray.ResetAndDestroy();
	iListBoxArray.Close();
	iLocStringArray.ResetAndDestroy();
	iLocStringArray.Close();
	}


// -----------------------------------------------------------------------------
// CAknMemorySelectionModel::GetItem
//
//
// -----------------------------------------------------------------------------
//
void CAknMemorySelectionModel::GetItem( TInt aIndex, TDes& aItem )
	{
    TInt err = 0;
	TRAP( err, UpdateItemsL() );
	aItem = iListBoxArray[ aIndex ]->Des();
	if( iLayout == ELayoutPopupMenu || iLayout == ELayoutDoublePopup )
		{
		// On layout with graphic, delete image index.
		_LIT( KTab, "\t" );
		TInt tabIndex( aItem.Find( KTab ) );
		if( tabIndex >= 0 )
			{
			aItem.Delete( 0, tabIndex + 1 );
			}
		if( iLayout == ELayoutDoublePopup )
			{
			tabIndex = aItem.Find( KTab );
			if( tabIndex >= 0 )
				{
				aItem = aItem.Left( tabIndex );
				}
			}
		}
	}

// -----------------------------------------------------------------------------
// CAknMemorySelectionModel::UpdateItemsL
//
//
// -----------------------------------------------------------------------------
//
void CAknMemorySelectionModel::UpdateItemsL()
	{
	TInt drive;
	TCFDDriveInfo driveInfo;

	// If array has items - reset it before updating
	iListBoxArray.ResetAndDestroy();
	_LOG( "[CAknMemorySelectionModel] iDriveArray: " );

	// Go through all drives
    for (TInt index( 0); index < iDriveArray->MdcaCount(); index++)
        {
        TPtrC text = iDriveArray->MdcaPoint( index );
        _LOG1( "%S", &text );

        drive = AknCFDUtility::DriveNumber( iDriveArray->MdcaPoint( index ) );
        User::LeaveIfError( drive ); // Leaves if < 0
        AknCFDUtility::DriveInfoL( TDriveNumber( drive ), driveInfo );

        _LOG7( "\n[CAknMemorySelectionModel] TCFDDriveInfo \n DriveNum:%d \n Path:%S \n Media:%d \n Status:%d \n Label:%S \n Space:%d \n ConnectionState:%d",
                driveInfo.iDriveNumber,
                &text,
                driveInfo.iMediaType,
                driveInfo.iDriveStatus,
                &(driveInfo.iVolumeLabel),
                driveInfo.iDiskSpace,
                driveInfo.iConnectionState );

        AddItemToLbxL(driveInfo);
        } // for
	}


// -----------------------------------------------------------------------------
// CAknMemorySelectionModel::MdcaCount
//
//
// -----------------------------------------------------------------------------
//
TInt CAknMemorySelectionModel::MdcaCount() const
	{
	return iListBoxArray.Count();
	}

// -----------------------------------------------------------------------------
// CAknMemorySelectionModel::MdcaPoint
//
//
// -----------------------------------------------------------------------------
//
TPtrC CAknMemorySelectionModel::MdcaPoint( TInt aIndex ) const
	{
	return *iListBoxArray[ aIndex ];
	}

// -----------------------------------------------------------------------------
// CAknMemorySelectionModel::ReadResourcesL
//
//
// -----------------------------------------------------------------------------
//
void CAknMemorySelectionModel::ReadResourcesL()
	{
	HBufC* buffer;
	TInt resource;
	for( TInt locStrIndex( 0 ); locStrIndex < ETextCount; locStrIndex++ )
		{
		resource = 0;
        // Resource depends on the layout type (TListBoxLayout):
		switch( iLayout )
			{
		    case ELayoutPopupMenu:
		        {
		        resource = ResourceIDForLayoutPopupMenuItem( locStrIndex );
		        break;
		        }
			case ELayoutSettingPage:
			    {
			    resource = ResourceIDForLayoutSettingPageItem( locStrIndex );
			    break;
			    }
			case ELayoutDoublePopup:
			    {
			    resource = ResourceIDForLayoutDoublePopupItem( locStrIndex );
			    break;
			    }
		    default:
				{
				User::Panic( KCFDPanicText, ECFDPanicOutOfBounds );
				}
			}//iLayout

        if( resource )
		    {
		    buffer = NULL;
    	    buffer = iCoeEnv->AllocReadResourceLC( resource );
    	    User::LeaveIfError( iLocStringArray.Append( buffer ) );
	        CleanupStack::Pop();// Buffer???
		    }

		}//For loop

#ifdef _DEBUG
        _LOG( "[CAknMemorySelectionModel] iLocStringArray: " );
        for( TInt lsa = 0; lsa < iLocStringArray.Count(); lsa++ )
    	    {
    	    _LOG1( "%S",iLocStringArray[ lsa ] );
    	    }
#endif // _DEBUG
	}


// -----------------------------------------------------------------------------
// CAknMemorySelectionModel::ResourceIDForLayoutPopupMenuItem
//
//
// -----------------------------------------------------------------------------
//
TInt CAknMemorySelectionModel::ResourceIDForLayoutPopupMenuItem(
    TInt aLocStrIndex )
    {
    TInt resource = 0;
    switch( aLocStrIndex )
        {
    	case ETextPhoneMemory:
			{
			resource = R_CFD_QTN_MEMC_PHONE;
			break;
			}
		case ETextMMC:
			{
			resource = R_CFD_QTN_MEMC_MMC;
			break;
			}
		case ETextMMCLocked:
			{
			resource = R_CFD_QTN_MEMC_MMC_LOCKED;
			break;
			}
		case ETextMMCUnavailable:
			{
			resource = R_CFD_QTN_MEMC_MMC_UNAVAILABLE;
			break;
			}
		case ETextRemoteDrive:
			{
			resource = R_CFD_QTN_MEMC_REMOTE_DRIVE;
			break;
			}
        }
    return resource;
    }


// -----------------------------------------------------------------------------
// CAknMemorySelectionModel::ResourceIDForLayoutSettingPageItem
//
//
// -----------------------------------------------------------------------------
//
TInt CAknMemorySelectionModel::ResourceIDForLayoutSettingPageItem(
    TInt aLocStrIndex )
    {
    TInt resource = 0;
    switch( aLocStrIndex )
        {
		case ETextPhoneMemory:
			{
			resource = R_CFD_QTN_DATABASE_PHONE;
			break;
			}
		case ETextMMC:
			{
			resource = R_CFD_QTN_MEMC_MCE_DEFAULT;
			break;
			}
		case ETextMMCLocked:
			{
			resource = R_CFD_QTN_DATABASE_LOCKED;
			break;
			}
		case ETextMMCUnavailable:
			{
			resource = R_CFD_QTN_DATABASE_UNAVAILABLE;
			break;
			}
	    case ETextRemoteDrive:
			{
			resource = R_CFD_QTN_MEMC_REMOTE_DRIVE;
			break;
			}
        }
    return resource;
    }


// -----------------------------------------------------------------------------
// CAknMemorySelectionModel::ResourceIDForLayoutDoublePopupItem
//
//
// -----------------------------------------------------------------------------
//
TInt CAknMemorySelectionModel::ResourceIDForLayoutDoublePopupItem(
    TInt aLocStrIndex )
    {
    TInt resource = 0;
     switch( aLocStrIndex )
        {
		case ETextPhoneMemory:
			{
			resource = R_CFD_QTN_MEMC_PHONE_DOUBLE_LIST;
			break;
			}
		case ETextMMC:
			{
			resource = R_CFD_QTN_MEMC_MMC_DOUBLE_LIST;
			break;
			}
		case ETextMMCLocked:
			{
			resource = R_CFD_QTN_MEMC_MMC_LOCKED_DOUBLE;
			break;
			}
		case ETextMMCUnavailable:
			{
			resource = R_CFD_QTN_MEMC_MMC_UNAVAILABLE_DOUBLE;
			break;
			}
		case ETextRemoteDrive:
			{
			resource = R_CFD_QTN_MEMC_REMOTE_DRIVE_DOUBLE_LIST;
			break;
			}
        }
    return resource;

    }


// -----------------------------------------------------------------------------
// CAknMemorySelectionModel::AddItemToLbxL
//
//
// -----------------------------------------------------------------------------
//
void CAknMemorySelectionModel::AddItemToLbxL( const TCFDDriveInfo& aDriveInfo )
    {
	// Drives C and E are special cases and these point to phone memory and MMC
	// memory regardless the media type. Listbox items are differend depending
	// on the media type.
    TDriveNumber phoneDrive, mmcDrive;
    phoneDrive = ( TDriveNumber )AknCFDUtility::DriveNumber(
                        PathInfo::PhoneMemoryRootPath() );
    User::LeaveIfError(
        DriveInfo::GetDefaultDrive( DriveInfo::EDefaultRemovableMassStorage,
                                    ( TInt& )mmcDrive ) );
	if( aDriveInfo.iDriveNumber == phoneDrive /*Phone memory*/ )
	    {
	    AddPhoneItemToLbxL( aDriveInfo );
	    }
    else if( aDriveInfo.iDriveNumber == mmcDrive  /*MMC memory*/ )
	    {
	    AddMMCItemToLbxL( aDriveInfo );
	    }
	else
	    {
        switch( aDriveInfo.iMediaType )
			{
			// Different media type cases can be added here in the future
			case EMediaRemote:
				{
				AddRemoteItemToLbxL( aDriveInfo );
                break;
				}
			default:
				{
				// No actual use case for this yet (only remote drives should
				// exist).
				AddDefaultItemToLbxL( aDriveInfo );
                break;
				}
			}
	    }
    }


// -----------------------------------------------------------------------------
// CAknMemorySelectionModel::AddPhoneItemToLbxL
//
//
// -----------------------------------------------------------------------------
//
void CAknMemorySelectionModel::AddPhoneItemToLbxL( const TCFDDriveInfo& aDriveInfo )
    {
    HBufC* lbxItemBuf = HBufC::NewLC( KListBoxEntryMaxLength );
	TPtr itemString( lbxItemBuf->Des() );

	// Item text is affected by layout
	switch( iLayout )
	    {
	        case ELayoutPopupMenu:
	            {
                // A-column icon:
            	itemString.Format( KImageHeader, EIconPhoneMemory );
            	itemString.Append( KTabChar );

        		// 1st row text:
            	if( aDriveInfo.iVolumeLabel.Length() > 0 )
            	    {
            	    // Append drive name if it has one
            	    itemString.Append( aDriveInfo.iVolumeLabel );
            	    }
            	else
            	    {
            	    // Use default drive description
            	    itemString.Append( *iLocStringArray[ ETextPhoneMemory ] );
            	    }
   	            break;
	            }
	        case ELayoutSettingPage:
	            {
	            // 1st row text:
            	if( aDriveInfo.iVolumeLabel.Length() > 0 )
            	    {
            	    // Append drive name if it has one
            	    itemString.Append( aDriveInfo.iVolumeLabel );
            	    }
            	else
            	    {
            	    // Use default drive description
            	    itemString.Append( *iLocStringArray[ ETextPhoneMemory ] );
            	    }
	            break;
	            }
	        case ELayoutDoublePopup:
	            {
	            // A-column icon:
            	itemString.Format( KImageHeader, EIconPhoneMemory );
            	itemString.Append( KTabChar );

            	// 1st row text:
            	if( aDriveInfo.iVolumeLabel.Length() > 0 )
            	    {
            	    // Append drive name if it has one
            	    itemString.Append( aDriveInfo.iVolumeLabel );
            	    itemString.Append( KTabChar );
            	    }
            	else
            	    {
            	    // Use default drive description
            	    itemString.Append( *iLocStringArray[ ETextPhoneMemory ] );
            	    itemString.Append( KTabChar );
            	    }

            	// 2nd row text:
            	HBufC* buffer;
            	TInt64 freeSpace = aDriveInfo.iDiskSpace;
                if ( freeSpace >= 0 )
                    {
                    buffer = HBufC::NewLC( KListBoxEntryMaxLength );  
                    TPtr unitStr( buffer->Des() );
                    AknCFDUtility::SetSecondRowTextL( freeSpace, unitStr );	
                    }
                else
        	        {
        			// Disk space is unavailable
        			buffer = StringLoader::LoadLC(
        			            R_CFD_QTN_MEMC_SPACE_NOT_AVAILABLE,
        			            iCoeEnv);
        			}
            	itemString.Append( *buffer );//Free mem text
            	CleanupStack::PopAndDestroy( buffer );
	            break;
	            }
	        }

	// Finally!: append the formatted string to listbox
    User::LeaveIfError( iListBoxArray.Append( lbxItemBuf ) );
	CleanupStack::Pop( lbxItemBuf );
    _LOG1( "[CAknMemorySelectionModel] Item string added to lbx array: %S", &itemString );
    _LOG1( "itemString length=%d", itemString.Length() );
    }


// -----------------------------------------------------------------------------
// CAknMemorySelectionModel::AddMMCItemToLbxL
//
//
// -----------------------------------------------------------------------------
//
void CAknMemorySelectionModel::AddMMCItemToLbxL( const TCFDDriveInfo& aDriveInfo )
    {
    HBufC* lbxItemBuf = HBufC::NewLC( KListBoxEntryMaxLength );
	TPtr itemString( lbxItemBuf->Des() );

    // Item text is affected by layout
    switch( iLayout )
        {
        case ELayoutPopupMenu:
            {
            // A-column icon:
        	itemString.Format( KImageHeader, EIconMMC );
        	itemString.Append( KTabChar );

        	// 1st row text:
        	if( aDriveInfo.iVolumeLabel.Length() > 0 )
        	    {
        	    // Append drive name if it has one
        	    itemString.Append( aDriveInfo.iVolumeLabel );
        	    }
        	else
        	    {
        	        if( aDriveInfo.iDriveStatus == EDriveNotReady )
                    {
                    itemString.Append( *iLocStringArray[ ETextMMCUnavailable ] );
                    }
                    else if( aDriveInfo.iDriveStatus == EDriveLocked )
                    {
        	        itemString.Append( *iLocStringArray[ ETextMMCLocked ] );
                    }
                    else
                    {
        	        // Use default drive description
        	        itemString.Append( *iLocStringArray[ ETextMMC ] );
                    }
        	    }
            break;
            }
        case ELayoutSettingPage:
            {
            // 1st row text:
        	if( aDriveInfo.iVolumeLabel.Length() > 0 )
        	    {
        	    // Append drive name if it has one
        	    itemString.Append( aDriveInfo.iVolumeLabel );
        	    }
        	else
        	    {
        	        if( aDriveInfo.iDriveStatus == EDriveNotReady )
                    {
                    itemString.Append( *iLocStringArray[ ETextMMCUnavailable ] );
                    }
                    else if( aDriveInfo.iDriveStatus == EDriveLocked )
                    {
        	        itemString.Append( *iLocStringArray[ ETextMMCLocked ] );
                    }
                    else
                    {
        	        // Use default drive description
        	        itemString.Append( *iLocStringArray[ ETextMMC ] );
                    }
        	    }
            break;
            }
        case ELayoutDoublePopup:
            {
            // A-column icon:
        	itemString.Format( KImageHeader, EIconMMC );
        	itemString.Append( KTabChar );

        	// 1st row text:
        	if( aDriveInfo.iVolumeLabel.Length() > 0 )
        	    {
        	    // Append drive name if it has one
        	    itemString.Append( aDriveInfo.iVolumeLabel );
        	    itemString.Append( KTabChar );
        	    }
        	else
        	    {
        	    // Use default drive description
        	    itemString.Append( *iLocStringArray[ ETextMMC ] );
        	    itemString.Append( KTabChar );
        	    }

        	// 2nd row text:
            switch( aDriveInfo.iDriveStatus )
                {
                case EDriveOK:
                    {
                    HBufC* buffer;
                    TInt64 freeSpace = aDriveInfo.iDiskSpace;
                    if ( freeSpace >= 0 )
                        {
                        buffer = HBufC::NewLC( KListBoxEntryMaxLength );  
                        TPtr unitStr( buffer->Des() );
                        AknCFDUtility::SetSecondRowTextL( freeSpace, unitStr );	 
                        }
                    else
        			    {
        			    // Disk space is unavailable
        			    buffer = StringLoader::LoadLC(
        			                R_CFD_QTN_MEMC_SPACE_NOT_AVAILABLE,
        			                iCoeEnv);
        			    }
        			itemString.Append( *buffer );//Free mem text
        			CleanupStack::PopAndDestroy( buffer );
                    break;
                    }
                case EDriveNotReady:
                    {
                    itemString.Append( *iLocStringArray[ ETextMMCUnavailable ] );
                    break;
                    }
                case EDriveLocked:
                    {
                    itemString.Append( *iLocStringArray[ ETextMMCLocked ] );
                    break;
                    }
                default:
                    {
                    // This is not defined in specification.
                    itemString.Append( *iLocStringArray[ ETextMMCUnavailable ] );
                    break;
                    }
                }
            break;
            }
        }

	// Finally!: append the formatted string to listbox
    User::LeaveIfError( iListBoxArray.Append( lbxItemBuf ) );
	CleanupStack::Pop( lbxItemBuf );
    _LOG1( "[CAknMemorySelectionModel] Item string added to lbx array: %S", &itemString );
    _LOG1( "itemString length=%d", itemString.Length() );
    }


// -----------------------------------------------------------------------------
// CAknMemorySelectionModel::AddRemoteItemToLbxL
//
//
// -----------------------------------------------------------------------------
//
void CAknMemorySelectionModel::AddRemoteItemToLbxL( const TCFDDriveInfo& aDriveInfo )
    {
    HBufC* lbxItemBuf = HBufC::NewLC( KListBoxEntryMaxLength );
	TPtr itemString( lbxItemBuf->Des() );

    // Item text is affected by layout
    switch( iLayout )
        {
        case ELayoutPopupMenu:
            {
            // A-column icon:
        	itemString.Format( KImageHeader, EIconRemoteDrive );
        	itemString.Append( KTabChar );

        	// 1st row text:
        	if( aDriveInfo.iVolumeLabel.Length() > 0 )
        	    {
        	    // Append drive name if it has one
        	    itemString.Append( aDriveInfo.iVolumeLabel );
        	    }
        	else
        	    {
        	    // Use default drive description
        	    itemString.Append( *iLocStringArray[ ETextRemoteDrive ] );
        	    }
            break;
            }
        case ELayoutSettingPage:
            {
          	// 1st row text:
        	if( aDriveInfo.iVolumeLabel.Length() > 0 )
        	    {
        	    // Append drive name if it has one
        	    itemString.Append( aDriveInfo.iVolumeLabel );
        	    }
        	else
        	    {
        	    // Use default drive description
        	    itemString.Append( *iLocStringArray[ ETextRemoteDrive ] );
        	    }
            break;
            }
        case ELayoutDoublePopup:
            {
            // A-column icon:
        	itemString.Format( KImageHeader, EIconRemoteDrive );
        	itemString.Append( KTabChar );

        	// 1st row text:
        	if( aDriveInfo.iVolumeLabel.Length() > 0 )
        	    {
        	    // Append drive name if it has one
        	    itemString.Append( aDriveInfo.iVolumeLabel );
        	    itemString.Append( KTabChar );
        	    }
        	else
        	    {
        	    // Use default drive description
        	    itemString.Append( *iLocStringArray[ ETextRemoteDrive ] );
        	    itemString.Append( KTabChar );
        	    }

            if( aDriveInfo.iDriveStatus == EDriveOK )
                {
                // 2nd row text:
                // Currently Remote drive does not support query for available
                // disk space, so just return " "
                _LIT( KEmptySpace, " ");
                itemString.Append( KEmptySpace ); 

                //  if( aDriveInfo.iConnectionState == KMountStronglyConnected )
                //    {
                // D-column icon: Show active icon if drive has no error
                //    itemString.Append( KTabChar );
                //    itemString.AppendFormat( KImageHeader, EIconRemoteDriveActive );
                //    }
                // else // KMountNotConnected
                //    {
                // D-column icon: Show active icon if drive has no error
                itemString.Append( KTabChar );
                //    }
                }
            else
                {
                // 2nd row text:
                itemString.Append( *iLocStringArray[ ETextMMCUnavailable ] );
                // D-column is empty if error.
                }
            break;
            }
        }

	// Finally!: append the formatted string to listbox
    User::LeaveIfError( iListBoxArray.Append( lbxItemBuf ) );
	CleanupStack::Pop( lbxItemBuf );
    _LOG1( "[CAknMemorySelectionModel] Item string added to lbx array: %S", &itemString );
    _LOG1( "itemString length=%d", itemString.Length() );
    }


// -----------------------------------------------------------------------------
// CAknMemorySelectionModel::AddDefaultItemToLbxL
//
// If drive has volume label, use it. Otherwise use drive letter for drive name.
// -----------------------------------------------------------------------------
//
void CAknMemorySelectionModel::AddDefaultItemToLbxL( const TCFDDriveInfo& aDriveInfo )
    {
    HBufC* lbxItemBuf = HBufC::NewLC( KListBoxEntryMaxLength );
    TPtr itemString( lbxItemBuf->Des() );
    TChar driveLetter;
    _LIT( KFormat, ":" );

	// Item text is affected by layout
	switch( iLayout )
        {
        case ELayoutSettingPage:
            {
            if( aDriveInfo.iVolumeLabel.Length() > 0 )
                {
                itemString.Append( aDriveInfo.iVolumeLabel/*aDriveLetter*/ );
                }
            else
                {
                User::LeaveIfError( RFs::DriveToChar( aDriveInfo.iDriveNumber, driveLetter ) );
                itemString.Append( driveLetter );
                itemString.Append( KFormat );
                }
            break;
            }
        case ELayoutPopupMenu:
        case ELayoutDoublePopup:
            {
        	itemString.Format( KImageHeader, EIconPhoneMemory );
        	itemString.Append( KTabChar );

            if( aDriveInfo.iVolumeLabel.Length() > 0 )
                {
                itemString.Append( aDriveInfo.iVolumeLabel );
                }
            else
                {
                User::LeaveIfError( RFs::DriveToChar( aDriveInfo.iDriveNumber, driveLetter ) );
                itemString.Append( driveLetter );
                itemString.Append( KFormat );
                }
            break;
            }
        }

	// Finally!: append the formatted string to listbox
    User::LeaveIfError( iListBoxArray.Append( lbxItemBuf ) );
	CleanupStack::Pop( lbxItemBuf );
    _LOG1( "[CAknMemorySelectionModel] Item string added to lbx array: %S", &itemString );
    _LOG1( "itemString length=%d", itemString.Length() );
    }


// -----------------------------------------------------------------------------
// CAknMemorySelectionModel::GetDrive
//
//
// -----------------------------------------------------------------------------
//
void CAknMemorySelectionModel::GetDrive( TInt aLbxItemIndex, TDes& aDrivePath )
    {
    if( aLbxItemIndex < iDriveArray->MdcaCount() )
        {
        aDrivePath = iDriveArray->MdcaPoint( aLbxItemIndex );
        }
    }

// End of File
