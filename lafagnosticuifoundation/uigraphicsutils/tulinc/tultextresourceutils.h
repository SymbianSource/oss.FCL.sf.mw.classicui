/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
*/



#ifndef __TULTEXTRESOURCEUTILS_H__
#define __TULTEXTRESOURCEUTILS_H__

#include <e32std.h>
#include <e32base.h>	// class CArrayFix
#include <bamdesca.h>	// class MDesCArray
#include <biditext.h>	// class TBidiText
class CCoeEnv;


/**
Utility that provides methods to load and format resource strings.
String Loader API provides an interface to load and format resource strings
that may contain parameter(s) (\%U for (unicode) text or or \%N for numerical).
Resource strings are usually defined in an RSS file.

The API consists of the TulTextResourceUtils class. All methods are static, so there is
no need to explicitly allocate memory for the interface class.
The implementation needs a CCoeEnv instance to access for example the
resource files.


Usage:

Applications load and format resource strings from normal resources with
static methods of the TulTextResourceUtils class. The loading is done with the LoadL
and LoadLC methods and with the Load method in situations where memory
allocation from the heap is not possible. Formatting is done automatically
after loading in the LoadL and LoadLC methods, but it can also be done
separately with the Format method in situations where memory allocation from
the heap is not possible. For reading the resource strings with the Load,
LoadL and LoadLC methods, the user should provide a pointer to CCoeEnv for
efficiency reasons. If the pointer is not provided, the implementation uses
the CCoeEnv::Static method internally to get it.

Different size displays can handle different length strings. To take full
advantage of this fact, TulTextResourceUtils supports resource strings with multiple
options for strings, separated by the character 0x0001. Each such string can
contain the same or different sub string keys (\%U and \%N). TulTextResourceUtils returns
all strings, it is the responsibility of the caller to parse the result and
choose the proper string to display.

Setting the maximum sub string length may be done in the text resources. Sub
string maximum lengths can be localized separately for every language.
The maximum sub string length is of the format: \%U[NN]
where NN is a number [01..99]. Please note that NN must always consist of two
characters, i.e. if the sub string maximum length is eight characters, the
value to be used is 08, not plain 8. If the number of characters exceeds the
maximum length, the sub string is cut to fit and the last character is
replaced with an ellipsis character.

The following examples describe the usage of the String Loader API.

Usage when one TInt is added:

@code
 // In .loc -file
 // #define text_example "You have %N undone tasks."

 // In .rss -file
 // RESOURCE TBUF r_text_example { buf = text_example; }

 // (In the .cpp -file)
 #include <coeutils.h>

 // Get CCoeEnv instance
 CEikonEnv* iEikonEnv = CEikonEnv::Static();

 TInt number(324);

 // Method reads a resource string with memory allocation
 // and replaces the first %N-string in it with replacement TInt.
 // The heap descriptor must be destroyed when it is no longer needed.
 // iEikonEnv is needed for loading the resource string.
 HBufC* stringholder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE, number, iEikonEnv);

 // The 'number' is added to the resource string. The result is
 // that stringholder points to a heap descriptor containing string:
 // "You have 324 undone tasks."

 // Delete the heap descriptor
 delete stringholder;
@endcode


Usage when several strings are added:

An index can be included to parameters. Several parameters can have same index
if the same replacement is needed multiple times.

@code
 // In .loc -file
 // #define text_example "I'm %2U%1U %3U%0U fine."

 // In .rss -file
 // RESOURCE TBUF r_text_example { buf = text_example; }

 // In the .cpp -file
 #include <coeutils.h>

 // Get CCoeEnv instance
 CEikonEnv* iEikonEnv = CEikonEnv::Static();

 CDesCArrayFlat* strings = new CDesCArrayFlat(4);
 CleanupStack::PushL(strings);

 strings->AppendL(_L("orking")); //First string

 strings->AppendL(_L("ll")); //Second string

 strings->AppendL(_L("sti")); //Third string

 strings->AppendL(_L("w")); //Fourth string

 // Method reads a resource string with memory allocation and replaces
 // the %(index)U strings in it with replacement strings from an array.
 // The heap descriptor must be destroyed when it is no longer needed.
 // iEikonEnv is needed for loading the resource string.
 HBufC* stringholder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE, *strings, iEikonEnv);

 // Four strings are added to the resource string. The result is
 // that stringholder points to a heap descriptor containing string:
 // "I'm still working fine."

 // Pop and delete strings array
 CleanupStack::PopAndDestroy();

 // Delete the heap descriptor
 delete stringholder;
@endcode


Usage with scalable UI support:

@code
 // In .loc -file
 // #define TEXT_EXAMPLE "You have missed %N messages from %U."<0x0001>"Missed %N msgs from %U."<0x0001>"Missed %N msgs."

 // In .rss -file
 // RESOURCE TBUF R_TEXT_EXAMPLE { buf = TEXT_EXAMPLE; }

 // In the .cpp -file
 #include <coeutils.h>

 // Get CCoeEnv instance
 CEikonEnv* iEikonEnv = CEikonEnv::Static();

 TInt number(12);
 _LIT(name, "John Doe");

 // Method reads a resource string with memory allocation,
 // replaces all %N strings in it with a replacement TInt and
 // all %U strings in it with a replacement string.
 // The heap descriptor must be destroyed  when it is no longer needed.
 // iEikonEnv is needed for loading the resource string.
 HBufC stringholder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE, name, number, iEikonEnv);

 // The number and name are added to the resource string. The result is
 // that stringholder points to a heap descriptor containing string:
 // "You have missed 12 messages from John Doe.\001Missed 12 msgs from John
 // Doe.\001Missed 12 msgs."

 // Delete the heap descriptor
 delete stringholder;
@endcode


Error handling:

The leave mechanism of the Symbian OS environment is used to handle memory
exhaustion. The panic mechanism is used to handle programming errors while
debugging. TulTextResourceUtils panics for seven different reasons. The panic 
category is named TulTextResourceUtils. The panic codes are:

- ETooFewArguments        = 0 (Unsolved parameters in resource string.)
- ETooManyArguments       = 1 (Already solved all parameters in  resource string.)
- EKeyStringNotFound      = 2 (The key string wasn't found in formatting.)
- EInvalidIndex           = 3 (Invalid index in Format-method)
- EDescriptorTooSmall     = 4 (Too small destination descriptor.)
- ECCoeEnvNotInitialized  = 5 (CCoeEnv is not initialized)
- EInvalidSubstitute      = 6 (Substituted string contains KSubStringSeparator)

@publishedAll
@released
*/
NONSHARABLE_CLASS(TulTextResourceUtils)
    {
public:
    IMPORT_C static void Load(TDes& aDest, TInt aResourceId, CCoeEnv* aLoaderEnv = NULL);
    IMPORT_C static void Format(TDes& aDest, const TDesC& aSource, TInt aPosition, TInt aSubs);
    IMPORT_C static void Format(TDes& aDest, const TDesC& aSource, TInt aPosition, const TDesC& aSubs);
    IMPORT_C static HBufC* LoadL(TInt aResourceId, CCoeEnv* aLoaderEnv = NULL);
    IMPORT_C static HBufC* LoadL(TInt aResourceId, TInt aInt, CCoeEnv* aLoaderEnv = NULL);
    IMPORT_C static HBufC* LoadL(TInt aResourceId, const TDesC& aString, CCoeEnv* aLoaderEnv = NULL);
    IMPORT_C static HBufC* LoadL(TInt aResourceId, const TDesC& aString, TInt aInt, CCoeEnv* aLoaderEnv = NULL);
    IMPORT_C static HBufC* LoadL(TInt aResourceId, const CArrayFix<TInt>& aInts, CCoeEnv* aLoaderEnv = NULL);
    IMPORT_C static HBufC* LoadL(TInt aResourceId, const MDesCArray& aStrings, CCoeEnv* aLoaderEnv = NULL);
    IMPORT_C static HBufC* LoadL(TInt aResourceId, const MDesCArray& aStrings, const CArrayFix<TInt>& aInts, CCoeEnv* aLoaderEnv = NULL);
    IMPORT_C static HBufC* LoadLC(TInt aResourceId, CCoeEnv* aLoaderEnv = NULL);
    IMPORT_C static HBufC* LoadLC(TInt aResourceId, TInt aInt, CCoeEnv* aLoaderEnv = NULL);
    IMPORT_C static HBufC* LoadLC(TInt aResourceId, const TDesC& aString, CCoeEnv* aLoaderEnv = NULL);
    IMPORT_C static HBufC* LoadLC(TInt aResourceId, const TDesC& aString, TInt aInt, CCoeEnv* aLoaderEnv = NULL);
    IMPORT_C static HBufC* LoadLC(TInt aResourceId, const CArrayFix<TInt>& aInts, CCoeEnv* aLoaderEnv = NULL);
    IMPORT_C static HBufC* LoadLC(TInt aResourceId, const MDesCArray& aStrings, CCoeEnv* aLoaderEnv = NULL);
    IMPORT_C static HBufC* LoadLC(TInt aResourceId, const MDesCArray& aStrings, const CArrayFix<TInt>& aInts, CCoeEnv* aLoaderEnv = NULL);
private:
    TulTextResourceUtils();
    TulTextResourceUtils(const TulTextResourceUtils&);	// Prohibit copy constructor
    TulTextResourceUtils& operator= (const TulTextResourceUtils&);	// Prohibit assigment operator
    static HBufC* FormatStringL(const TDesC& aSource, const TDesC& aKey, const TDesC& aSubs, TBidiText::TDirectionality aDir);
    static HBufC* FormatStringL(const TDesC& aSource, const TDesC& aKey, const TDesC& aSubs,
        						 TBidiText::TDirectionality aDirectionality, TInt& aParamCount, TInt aSubCount);
    static HBufC* FormatStringL(TDesC& aSource, const CArrayFix<TInt>& aInts, TInt aMax, TBidiText::TDirectionality aDir);
    static HBufC* FormatStringL(TDesC& aSource, const MDesCArray& aStrings, TInt aMax, TBidiText::TDirectionality aDir);
    static TInt Formater(TDes& aDest, const TDesC& aSource, const TDesC& aKey,
        					const TDesC& aSubs, TBidiText::TDirectionality aDirectionality);

    static void KeyStringFormater(TDes& aDest, const TText& aKey, TInt aPosition, const TDesC& aKeyString);
    static TBidiText::TDirectionality ResolveDirectionality(TDes& aText, TBool* aFound);
    static TInt GetParamCount(const TDesC& aText, TInt aIndex = -1);
    static TInt GetSubStringCount(const TDesC& aText);
        
    static TBidiText::TDirectionality DirectionalityL(const TDesC& aText, TBool* aFound);
    static HBufC* ResolveSubStringDirsL(TDes& aText, TInt aCount, TBool* aMarker);
    static HBufC* ResolveSubStringL(TDes& aText, TBool* aMarker);
    static void RemoveNoDirMarkers(TDes& aText);
    static void FormatL(TDes& aDest, const TDesC& aSource, const TDesC& aKeybuf, const TDesC& aSubs);
    };


#endif	// __TULTEXTRESOURCEUTILS_H__
