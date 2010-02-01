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
#include "CAknCommonDialogsQueryDialog.h"

#include <apparc.h>
#include <aknnotewrappers.h>
#include <bautils.h>
#include <StringLoader.h>
#include <commondialogs.rsg>
#include <aknQueryControl.h>

#include <AknTasHook.h> // for testability hooks
#include "MAknFileSelectionObserver.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknCommonDialogsQueryDialog
//
//
// -----------------------------------------------------------------------------
//
CAknCommonDialogsQueryDialog::CAknCommonDialogsQueryDialog(
	MAknFileSelectionObserver* aObserver,
	const TDesC& aPath,
	TDes& aDataText,
	const TDesC& aExtension,
	CCoeEnv* aCoeEnv )
	:	CAknTextQueryDialog( aDataText ),
		iPath( aPath ),
		iExtension( aExtension ),
		iObserver( aObserver ),
		iCoeEnv( aCoeEnv )
	{
	AKNTASHOOK_ADD( this, "CAknCommonDialogsQueryDialog" );
	}

// Destructor
CAknCommonDialogsQueryDialog::~CAknCommonDialogsQueryDialog()
	{
	AKNTASHOOK_REMOVE();
	}


// -----------------------------------------------------------------------------
// CAknCommonDialogsQueryDialog::OkToExitL
//
//
// -----------------------------------------------------------------------------
//
TBool CAknCommonDialogsQueryDialog::OkToExitL( TInt aButtonId )
	{
	// Call OkToExitL of the base class
	TBool returnValue( CAknTextQueryDialog::OkToExitL( aButtonId ) );

	if( returnValue )
		{
		// User wants to go with the typed filename

        TBool userCancelled( EFalse );
		if( !FileNameAllowedL( iPath, iDataText, iExtension, userCancelled ) )
			{
            // If user cancelled the "rename" query, this dialog must exit,
            // so return ETrue, but clear the given name first:
            if( userCancelled )
                {
                iDataText.Zero();
                return ETrue;
                }
			// Otherwise if the name is not allowed, it is not Ok to exit.
            // CAknQueryControl::SetTextL() is used here to get the
            // user-written text selected:
            CAknQueryControl* queryCtrl = QueryControl();
            queryCtrl->SetTextL( iDataText );
			return EFalse;
			}

		// Filename is valid, ask observer's opinion too.

		if( iObserver )
			{
			TEntry entry;
			entry.iName = iDataText;
			if( !iObserver->OkToExitL( iPath, entry ) )
				{
				// Observer doesn't think the file is Ok, don't exit. But first,
                // make the user-written text selected:
                CAknQueryControl* queryCtrl = QueryControl();
                queryCtrl->SetTextL( iDataText );
				return EFalse;
				}
			}
		}
	return returnValue;
	}

// -----------------------------------------------------------------------------
// CAknCommonDialogsQueryDialog::FileNameAllowedL
//
//
// -----------------------------------------------------------------------------
//
TBool CAknCommonDialogsQueryDialog::FileNameAllowedL(
	const TDesC& aPath, const TDesC& aFileName, const TDesC& aExtension,
    TBool& aUserCancelled )
	{
	// Create a TFileName descriptor and set full path and filename to it
	TFileName fileName( aPath );
	fileName += aFileName;
	fileName += aExtension;
	// Create a TParsePtrC with the full path and filename, parsed filename points
	// its data to the created TFileName
	TParsePtrC parsedFile( fileName );
	// Temporary descriptor pointer
	TPtrC temp( parsedFile.Name() );

	RFs fs( iCoeEnv->FsSession() );
	TBool badFileName( EFalse );
	TBool illegalCharacters( EFalse );
	_LIT( KSingleDotCharacter, "."  );
	_LIT( KDualDotCharacter,   ".." );
	_LIT( KCarriageReturn, "\x2029" );
	
	if( ( temp.Compare( KSingleDotCharacter ) == 0 ) ||
		( temp.Compare( KDualDotCharacter   ) == 0 ) ||
		( aFileName.Find( KCarriageReturn ) != KErrNotFound ) ||
        ( ( aFileName.Compare( KSingleDotCharacter ) == 0 ) && 
          ( aExtension.Compare( KNullDesC ) == 0 ) ) )
		{
		// If filename consists only of "." or ".." it is BAD file name
		badFileName= ETrue;
		}
	else
		{
		// Also RFs::IsValidName tells efficiently if the filename is ok.
		// Get the name and extension for next check
		temp.Set( parsedFile.FullName() );
		illegalCharacters = !fs.IsValidName( temp );
        
        // RFs::IsValidName does not check if filename includes '\' and mirror '?'       
        TChar backslash( '\\' );
        _LIT( KMirrorQuestion, "\x061F" );
        if (( aFileName.Locate( backslash ) != KErrNotFound ) || 
            ( aFileName.Find( KMirrorQuestion ) != KErrNotFound ) )
            {
            illegalCharacters = ETrue;
            }
		}

	if( badFileName || illegalCharacters )
		{
		// Depending on the error, read loc string
		HBufC* text = iCoeEnv->AllocReadResourceLC( badFileName ?
			R_CFD_QTN_FLDR_BAD_FILE_NAME : R_CFD_QTN_FLDR_ILLEGAL_CHARACTERS );
		CAknErrorNote* note = new( ELeave ) CAknErrorNote( EFalse ); 
		note->ExecuteLD( *text );
		CleanupStack::PopAndDestroy(); // text
		return EFalse;
		}

	// the filename is valid

	// Get the full filename and path for FileExists check
	temp.Set( parsedFile.FullName() );
	if( !BaflUtils::FileExists( fs, temp ) )
		{
		// If the file does not exist, accept it
		return ETrue;
		}

    // The file already exists
    // Check if it's a folder (it cannot be overwritten).
    TBool overwriteNotAllowed( EFalse );
    User::LeaveIfError( BaflUtils:: IsFolder( fs, temp, overwriteNotAllowed ) );
	temp.Set( parsedFile.Name() );

	CAknQueryDialog* dialog = new( ELeave ) CAknQueryDialog();
	dialog->PrepareLC( R_CFD_CONFIRMATION_QUERY );
	HBufC* confirmationText = NULL;
    if( overwriteNotAllowed )
        {
        confirmationText = StringLoader::LoadLC(     // "Name %U already in use.
                R_CFD_QTN_FLDR_RENAME_QUERY, temp ); // Rename?"
        }
    else
        {
        confirmationText = StringLoader::LoadLC(        // "%U already exists!
                R_CFD_QTN_FLDR_OVERWRITE_QUERY, temp ); // Overwrite?"
        }
	dialog->SetPromptL( *confirmationText );
	CleanupStack::PopAndDestroy(); // confirmationText
	TInt result( dialog->RunLD() );

	if( ( result == EAknSoftkeyYes ) || ( result == EAknSoftkeyOk ) )
		{
		// User accepted overwrite or OK'ed the rename query:
		return !overwriteNotAllowed;
		}

	// User answered "No", if it was rename query, this dialog must be exited:
    if ( overwriteNotAllowed )
        {
        aUserCancelled = ETrue;
        return EFalse;
        }

    // User didnt' accept overwrite, ask a new name from user.

	HBufC* renamePrompt = iCoeEnv->AllocReadResourceLC( R_CFD_QTN_FLDR_ITEM_NAME_PRMPT ); // "New name:"
	SetPromptL( *renamePrompt );
	CleanupStack::PopAndDestroy(); // renamePrompt

	return EFalse;
	}

// End of File
