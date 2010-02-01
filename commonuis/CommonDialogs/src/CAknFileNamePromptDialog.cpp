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
* Description:  ?Description
*
*/


// INCLUDES
#include "CAknFileNamePromptDialog.h"

#include <AknQueryDialog.h>     // CAknTextQueryDialog
#include <barsread.h>           // TResourceReader
#include <bautils.h>
#include <commondialogs.rsg>

#include "CAknCommonDialogsQueryDialog.h"
#include "AknCFDUtility.h"

// CONSTANTS
// If number is 10 or more 2 digits are needed to display it
const TInt KTwoDigitNeeded = 10;
_LIT( KFormatStringTwoDigit, "%02d" );
_LIT( KFormatString, "%d" );
const TInt KFormatBufLen = 16;
const TInt KMaxAutoNum = 99;
// =========================== MEMBER FUNCTIONS ==============================

// ---------------------------------------------------------------------------
// CAknFileNamePromptDialog::CAknFileNamePromptDialog
//
//
// -----------------------------------------------------------------------------
//
CAknFileNamePromptDialog::CAknFileNamePromptDialog()
    {
    }

// -----------------------------------------------------------------------------
// CAknFileNamePromptDialog::ConstructFromResourceL
//
// -----------------------------------------------------------------------------
//
void CAknFileNamePromptDialog::ConstructFromResourceL( TInt aResourceId )
    {
    BaseConstructL();
    if( aResourceId )
        {
        // If a resource id is given, read settings from it.
        ReadFromResourceL( aResourceId );
        }
    // After user resource is read, "patch" the missing values with defaults
    // by reading all missing settings from default resource.
    SetResourceId( aResourceId );
    ReadFromResourceL( aResourceId );
    }

// -----------------------------------------------------------------------------
// CAknFileNamePromptDialog::NewL
//
// -----------------------------------------------------------------------------
//
EXPORT_C CAknFileNamePromptDialog* CAknFileNamePromptDialog::NewL()
    {
    return NewL( 0 );
    }

// -----------------------------------------------------------------------------
// CAknFileNamePromptDialog::NewL
//
// -----------------------------------------------------------------------------
//
EXPORT_C CAknFileNamePromptDialog* CAknFileNamePromptDialog::NewL( TInt aResourceId )
    {
    CAknFileNamePromptDialog* self = new( ELeave ) CAknFileNamePromptDialog();
    CleanupStack::PushL( self );
    self->ConstructFromResourceL( aResourceId );
    CleanupStack::Pop(); // self
    return self;
    }

// Destructor
EXPORT_C CAknFileNamePromptDialog::~CAknFileNamePromptDialog()
    {
    delete iTitle;
    delete iRightSoftkey;
    delete iLeftSoftkey;
    delete iPath;
    delete iDefaultFileName;
    }


// -----------------------------------------------------------------------------
// CAknFileNamePromptDialog::SetPathL
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknFileNamePromptDialog::SetPathL( const TDesC& aPath )
    {
    AknCFDUtility::AllocateIfValidL( iPath, aPath );
    }

// -----------------------------------------------------------------------------
// CAknFileNamePromptDialog::SetObserver
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknFileNamePromptDialog::SetObserver( MAknFileSelectionObserver* aObserver )
    {
    iObserver = aObserver;
    }

// -----------------------------------------------------------------------------
// CAknFileNamePromptDialog::SetTitleL
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknFileNamePromptDialog::SetTitleL( const TDesC& aText )
    {
    AknCFDUtility::AllocateIfValidL( iTitle, aText );
    }

// -----------------------------------------------------------------------------
// CAknFileNamePromptDialog::SetLeftSoftkeyL
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknFileNamePromptDialog::SetLeftSoftkeyL( const TDesC& aText )
    {
    AknCFDUtility::AllocateIfValidL( iLeftSoftkey, aText );
    }

// -----------------------------------------------------------------------------
// CAknFileNamePromptDialog::SetRightSoftkeyL
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknFileNamePromptDialog::SetRightSoftkeyL( const TDesC& aText )
    {
    AknCFDUtility::AllocateIfValidL( iRightSoftkey, aText );
    }

// -----------------------------------------------------------------------------
// CAknFileNamePromptDialog::ShowDialogL
//
//
// -----------------------------------------------------------------------------
//
TBool CAknFileNamePromptDialog::ShowDialogL( TDes& aFilename, TBool aIfRename )
    {
    __ASSERT_DEBUG( iPath,
        User::Panic( KCFDPanicText, ECFDPanicNoPathForFileNamePromptDialog ) );
    __ASSERT_DEBUG( iTitle && iLeftSoftkey && iRightSoftkey,
        User::Panic( KCFDPanicText, ECFDPanicTitleOrSoftkeyNotSet ) );

    TParsePtr parse(aFilename);
    if( ( iDefaultFileName ) && ( aFilename.Length() == 0 ) )
        {
        // If default filename is only set in resource, use it.
        TPtr defaultFileName = iDefaultFileName->Des();
        parse = TParsePtr( defaultFileName );
        }

    HBufC * originDataText = parse.Name().AllocL();
    originDataText = originDataText->ReAllocL( KMaxFileName );
    CleanupStack::PushL( originDataText );

    TPtr dataText = originDataText->Des();
    TInt pathLength( 0 );
    if( iPath )
        {
        pathLength = iPath->Length();
        }
    TInt maxLength( aFilename.MaxLength() - parse.Ext().Length() - pathLength );
	if ( aIfRename == EFalse )
		{
		//Give a default file name
		TInt i = 0;
		TFileName fileName;
		TBuf< KFormatBufLen > numBuf; // For autonumbering
		
		while ( ETrue )
			{
			// Create a TFileName descriptor and set full path + filename to it
			fileName = *iPath; 
			TInt tempNumber = dataText.Length();
			if ( ( i > 1 ) && ( tempNumber >= 2 ) )
			    {
			    // Delete previous automatic number
				dataText.Delete( tempNumber - 2, 2 ); 
			    }
			dataText += numBuf; 
			tempNumber = dataText.Length();
			if( tempNumber > maxLength )
				{
				if( i )
				    {
				    dataText.Delete(( maxLength - 2 ), ( tempNumber - maxLength ));
				    }
				else
				    {
				    dataText.Delete( maxLength, ( tempNumber - maxLength ));	
			        }
				}
			fileName += dataText;
			fileName += parse.Ext();
			
			if( !BaflUtils::FileExists( iCoeEnv->FsSession(), fileName ) )
				{
				// If the file does not exist, accept it
				break;
				}
			else
				{	
				i++;
				if( i > KMaxAutoNum )
				    {
					break;
				    }
				numBuf.Zero();
			    if( i < KTwoDigitNeeded ) 
				    {
				    numBuf.Format( KFormatStringTwoDigit, i );
				    }   
			    else
				    {
				    numBuf.Format( KFormatString, i );
				    }
				
                AknTextUtils::DisplayTextLanguageSpecificNumberConversion(
                    numBuf ); // Localize digits
				}
			}
		} 

    CAknCommonDialogsQueryDialog* dialog = new( ELeave ) CAknCommonDialogsQueryDialog(
        iObserver, *iPath, dataText, parse.Ext(), iCoeEnv );

    dialog->PrepareLC( R_CFD_FILENAME_PROMPT_DIALOG );

    if( ( maxLength >= 0 ) && ( maxLength < KMaxFileName ) )
        {
        dialog->SetMaxLength( maxLength );
        }

    dialog->SetPromptL( *iTitle );
    CEikButtonGroupContainer* cba = &dialog->ButtonGroupContainer();
    MEikButtonGroup* buttonGroup = cba->ButtonGroup();
    cba->SetCommandL( buttonGroup->CommandId( 0 ), *iLeftSoftkey );
    cba->SetCommandL( buttonGroup->CommandId( 2 ), *iRightSoftkey );

    // Run dialog
    TBool returnValue( dialog->RunLD() == EAknSoftkeyOk );

    if( dataText.Length() == 0 )
        {
        // User has cancelled a query launched by dialog:
        CleanupStack::PopAndDestroy(); // originDataText
        return EFalse;
        }

    if( returnValue )
        {
        dataText += parse.Ext();
        aFilename = dataText;
        }

    CleanupStack::PopAndDestroy(); // originDataText
    return returnValue;
    }

// -----------------------------------------------------------------------------
// CAknFileNamePromptDialog::ExecuteL
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknFileNamePromptDialog::ExecuteL( TDes& aFileName )
    {
	return ShowDialogL( aFileName, EFalse );
    }

// -----------------------------------------------------------------------------
// CAknFileNamePromptDialog::RenameL
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknFileNamePromptDialog::RenameL( TDes& aFileName )
	{
    return ShowDialogL( aFileName, ETrue );
	}

// -----------------------------------------------------------------------------
// CAknFileNamePromptDialog::RunDlgLD
// A wrapper for RunL.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknFileNamePromptDialog::RunDlgLD( TDes& aFileName,
    const TDesC& aPath,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( 0, aFileName, aPath, KNullDesC, aObserver );
    }

// -----------------------------------------------------------------------------
// CAknFileNamePromptDialog::RunDlgLD
// A wrapper for RunL.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknFileNamePromptDialog::RunDlgLD( TDes& aFileName,
    const TDesC& aPath,
    const TDesC& aTitle,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( 0, aFileName, aPath, aTitle, aObserver );
    }

// -----------------------------------------------------------------------------
// CAknFileNamePromptDialog::RunDlgLD
// A wrapper for RunL.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknFileNamePromptDialog::RunDlgLD( TDes& aFileName,
    const TDesC& aPath,
    TInt aResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( aResourceId, aFileName, aPath, KNullDesC, aObserver );
    }

// -----------------------------------------------------------------------------
// CAknFileNamePromptDialog::RunL
//
//
// -----------------------------------------------------------------------------
//
TBool CAknFileNamePromptDialog::RunL(
    TInt aResourceId,
    TDes& aFileName,
    const TDesC& aPath,
    const TDesC& aTitle,
    MAknFileSelectionObserver* aObserver )
    {
    CAknFileNamePromptDialog* self = CAknFileNamePromptDialog::NewL( aResourceId );
    CleanupStack::PushL( self );
    self->SetPathL( aPath );
    self->SetTitleL( aTitle );
    self->iObserver = aObserver;

    TBool returnValue( self->ExecuteL( aFileName ) );

    CleanupStack::PopAndDestroy(); // self
    return returnValue;
    }

// -----------------------------------------------------------------------------
// CAknFileNamePromptDialog::?member_function
//
//
// -----------------------------------------------------------------------------
//
void CAknFileNamePromptDialog::SetResourceId( TInt& aResourceId ) const
    {
    aResourceId = R_CFD_DEFAULT_SAVE_FILENAME_PROMPT;
    }

// -----------------------------------------------------------------------------
// CAknFileNamePromptDialog::?member_function
//
//
// -----------------------------------------------------------------------------
//
void CAknFileNamePromptDialog::ReadFromResourceL( TInt aResourceId )
    {
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC( reader, aResourceId );
    AknCFDUtility::AllocateIfNullL( iTitle, reader.ReadTPtrC() );
    AknCFDUtility::AllocateIfNullL( iDefaultFileName, reader.ReadTPtrC() );
    AknCFDUtility::AllocateIfNullL( iPath, reader.ReadTPtrC() );
    AknCFDUtility::AllocateIfNullL( iLeftSoftkey, reader.ReadTPtrC() );
    AknCFDUtility::AllocateIfNullL( iRightSoftkey, reader.ReadTPtrC() );
    CleanupStack::PopAndDestroy(); // reader
    }

//  End of File
