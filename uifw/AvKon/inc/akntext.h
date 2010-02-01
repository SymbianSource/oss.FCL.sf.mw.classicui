/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: 
*
*     Store and handle text labels for note dialogs. Each note dialog
*     can have two different labels, one singular and one plural.
*     For example:-
*        "You have 1 new message" is the singular label and
*        "You have 2 new messages" is the plural label.
*     This class supports the ability to change number inside the label, 
*     e.g. "You have 100 new messages" is supported.
*     Text is read from resource but can also be set dynamically via the
*     public API.
* 
*
*/


#ifndef __AKNNOTETEXT__
#define __AKNNOTETEXT__ 

#include <e32base.h>
#include <e32std.h>
#include <barsread.h>

/**
 * An avkon dynamic text class. 
 *
 * Manage static or dynamic text. Static text never changes,
 * e.g. "Delete?". Dynamic text changes depending on a number,
 * e.g. "Delete 1 message?" or "Delete 3 messages?"
 *
 * Client can specify plurality and/or number to determine which
 * text is returned. 
 *
 * Formatted text is stored in a buffer, there are then 2 additional
 * buffers storing the unformatted texts, e.g. "Delete %d message"
 * and "Delete %d messages".
 *
 * One current limitation is that only one number can be supported 
 * per text. A better approach would be to offer a printf alike interface.
 * In fact the whole idea of the control having to manage these texts
 * is a bit of a nonsese - the client should simply call a method
 * passing a text a number of args, like when calling printf. For future
 * implementations.
 *
 */
NONSHARABLE_CLASS(CAknText) : public CBase
	{
	public:
		enum TPlurality 
			{
			ENotSpecified,
			ESingular,
			EPlural
			};
		enum TType
			{
			EFormatted,
			ENotFormatted
			};
	public:
		CAknText();
		CAknText(const TType& aType);
		~CAknText();
	
	public:
		void ConstructFromResourceL(TResourceReader& aRes);
	    CAknText& operator=(CAknText& aNoteText);

		void SetPluralityL(TBool aIsPlural);
		void SetNumberL(TInt aNumber);
		void SetL(const TDesC& aText);
		TPtr Get() const;
	
	private:
		void FormatL();
		void DoFormatTextL(HBufC* aUnformattedText);
		TPtr TranslateDintoN(HBufC* aUnformattedText);

		void  DoSetTextL(HBufC*& aBuffer, const TDesC& aText);
		TBool TextIsNotFormatted(const TDesC& aText);

	private:
		CAknText(const CAknText&);

	private:
		TPlurality iPlurality;
		TType      iType;
		TInt       iNumber;
		TBool      iNumberHasBeenSet;
		HBufC*     iUnformattedSingularText;
		HBufC*     iUnformattedPluralText;
		HBufC*     iText;
		HBufC*     iTextCopy;
		TInt iSpare;
	};

#endif
