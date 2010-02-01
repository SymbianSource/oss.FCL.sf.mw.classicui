// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#ifndef __COEINPUT_H__
#define __COEINPUT_H__

#include <e32std.h>

// classes defined in FEPBASE, declared here
class MCoeFepAwareTextEditor;
class MCoeCaptionRetrieverForFep;

class MObjectProvider;

class TCoeInputCapabilities
/** Describes which forms of text input are consumed by a control or view.

@publishedAll 
@released */
	{
public:
	/** Text input capability flags. These are used to define the text input 
	capabilities of a control or view. */
	enum
		{
		/** No text input capabilities supported. */
		ENone							=0,
		/** Supports positive western integers. */
		EWesternNumericIntegerPositive	=0x00000001,
		/** Supports negative western integers. */
		EWesternNumericIntegerNegative	=0x00000002,
		/** Supports real numbers. */
		EWesternNumericReal				=0x00000004,
		/** Supports the western alphabets. */
		EWesternAlphabetic				=0x00000008,
		/** Supports Hiragana. */
		EJapaneseHiragana				=0x00000010,
		/** Supports half width Katakana. */
		EJapaneseKatakanaHalfWidth		=0x00000020,
		/** Supports full width Katakana. */
		EJapaneseKatakanaFullWidth		=0x00000040,
		/** Supports dialable characters */
		EDialableCharacters				=0x00000080,
		/** Supports secret text. This is text in which characters appear 
		as asterisks. */
		ESecretText						=0x00000100,
		/** Supports auto sentence case.
		This is text in which first word in a sentence begins with an uppercase letter, 
		with all other letters and words in lowercase. */
		EAutoSentenceCase				=0x00000200,
		/** Supports non-predictive input. */
		ENonPredictive					=0x00000400,
		/** Supports all types of text. */
		EAllText						=0x01000000,
		/** Supports navigation keys. These include arrow keys, page-up,
		page-down, home, end, tab, etc. */
		ENavigation						=0x02000000
		};
	class MCoeFepSpecificExtensions; // to be defined by concrete FEPs, declared here
public:
	// all these functions are exported (rather than inline) so that binary compatibility becomes easier to maintain
	IMPORT_C TCoeInputCapabilities();
	IMPORT_C TCoeInputCapabilities(TUint aCapabilities);
	IMPORT_C TCoeInputCapabilities(TUint aCapabilities, MCoeFepAwareTextEditor* aFepAwareTextEditor, MCoeCaptionRetrieverForFep* aCaptionRetrieverForFep);
	IMPORT_C TCoeInputCapabilities(TUint aCapabilities, MCoeFepAwareTextEditor* aFepAwareTextEditor, MCoeCaptionRetrieverForFep* aCaptionRetrieverForFep, TUid aFepUid, MCoeFepSpecificExtensions* aFepSpecificExtensions);
	IMPORT_C TCoeInputCapabilities(const TCoeInputCapabilities& aAnother); // defined so that iSpareForFutureUse is not copied
	IMPORT_C TCoeInputCapabilities& operator=(const TCoeInputCapabilities& aAnother); // defined so that iSpareForFutureUse is not copied
	IMPORT_C TBool operator==(const TCoeInputCapabilities& aAnother) const; // defined so that iSpareForFutureUse is not tested
	IMPORT_C TBool operator!=(const TCoeInputCapabilities& aAnother) const; // defined so that iSpareForFutureUse is not tested
	IMPORT_C void MergeWith(const TCoeInputCapabilities& aAnother);
	IMPORT_C void SetCapabilities(TUint aCapabilities);
	IMPORT_C TUint Capabilities() const;
	IMPORT_C TBool IsNone() const;
	IMPORT_C TBool SupportsWesternNumericIntegerPositive() const;
	IMPORT_C TBool SupportsWesternNumericIntegerNegative() const;
	IMPORT_C TBool SupportsWesternNumericReal() const;
	IMPORT_C TBool SupportsWesternAlphabetic() const;
	IMPORT_C TBool SupportsJapaneseHiragana() const;
	IMPORT_C TBool SupportsJapaneseKatakanaHalfWidth() const;
	IMPORT_C TBool SupportsJapaneseKatakanaFullWidth() const;
	IMPORT_C TBool SupportsDialableCharacters() const;
	IMPORT_C TBool SupportsSecretText() const;
	IMPORT_C TBool SupportsAutoSentenceCase() const;
	IMPORT_C TBool SupportsNonPredictive() const;
	IMPORT_C TBool SupportsAllText() const;
	IMPORT_C TBool SupportsNavigation() const;
	IMPORT_C MCoeFepAwareTextEditor* FepAwareTextEditor() const;
	IMPORT_C MCoeCaptionRetrieverForFep* CaptionRetrieverForFep() const;
	IMPORT_C MCoeFepSpecificExtensions* FepSpecificExtensions(TUid aFepUid) const;
    IMPORT_C MObjectProvider* ObjectProvider() const;
    IMPORT_C void SetObjectProvider(MObjectProvider* aObjectProvider);

private:
	TUint iCapabilities;
	MCoeFepAwareTextEditor* iFepAwareTextEditor;
	MCoeCaptionRetrieverForFep* iCaptionRetrieverForFep;
	TUint iFepUid;
	MCoeFepSpecificExtensions* iFepSpecificExtensions;
    MObjectProvider* iObjectProvider;
    TAny* iSpareForFutureUse[5];
	};

#endif	// __COEINPUT_H__
