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
* Description:  Dialog used to diplay filename prompt dialog.
*
*/


#ifndef CAKNCOMMONDIALOGSQUERYDIALOG_H
#define CAKNCOMMONDIALOGSQUERYDIALOG_H

// INCLUDES
#include <AknQueryDialog.h>

// FORWARD DECLARATIONS
class MAknFileSelectionObserver;
class CCoeEnv;

//  CLASS DEFINITION
/**
*  A class derived from CAknTextQueryDialog in order to catch and report events.
*
*  @lib CommonDialogs.lib
*  @since 1.2
*/
NONSHARABLE_CLASS(CAknCommonDialogsQueryDialog) : public CAknTextQueryDialog
	{
	public:		// Constructors and destructors

		/**
		* Default constructor.
		* @param aObserver An observer which is asked, if set, to verify the filename that user types.
		* @param aPath Path where the filename is saved. If aPath is empty on
        *        return of RunLD(), it means that user cancelled a query
        *        launched by this dialog.
		* @param aDataText Default text for dialog. User's input is stored to this.
		* @param aExtension File extension of the filename. This is not shown to user.
		* @param aCoeEnv Pointer to control environment.
		*/
		CAknCommonDialogsQueryDialog(
			MAknFileSelectionObserver* aObserver,
			const TDesC& aPath,
			TDes& aDataText,
			const TDesC& aExtension,
			CCoeEnv* aCoeEnv );

		~CAknCommonDialogsQueryDialog();

	public:		// New functions

		/**
		* Checks if a filename is valid and that it does not exist.
		* If the file already exists, user is asked if the old one is replaced.
		* @param aPath Target path for the filename.
		* @param aFileName Name of the file without extension.
		* @param aExtension Extension for the file.
		* @param aUserCancelled if user cancelled the query launched inside this
        *        function, this is ETrue on return.
		* @return Returns ETrue if filename is be allowed or it is renamed
		*         to such that it can be allowed.
		*/
		TBool FileNameAllowedL(
			const TDesC& aPath,
			const TDesC& aFileName,
			const TDesC& aExtension,
			TBool& aUserCancelled );
		
	private:	// Functions from base classes

		/**
		* From CEikDialog
		* Derived in order to check whether the selected item can be accepted or not.
		* Reports an event to the observer.
		*/
		TBool OkToExitL( TInt aButtonId );

	private:	// Data

		// Ref: Path
		const TDesC& iPath;

		// Ref: Extension
		const TDesC& iExtension;

		// Ref: Pointer to observer
		MAknFileSelectionObserver* iObserver;

		// Ref: Pointer to control environment
		CCoeEnv* iCoeEnv;
	};

#endif // CAKNCOMMONDIALOGSQUERYDIALOG_H

// End of File
