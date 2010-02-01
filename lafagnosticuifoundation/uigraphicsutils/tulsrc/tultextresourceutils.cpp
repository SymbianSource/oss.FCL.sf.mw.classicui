// Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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



#include <tultextresourceutils.h>
#include <tulpanics.h>
#include "languagespecificnumberconverter.h"
#include <coeutils.h>
#include <bautils.h>
#include <coemain.h>

// CP1252 ellipsis character value.
#define KEllipsis		0x2026  // cp1252=133

// KIntSize and KKeySize define maximum number of characters
// in input TInts and in keystring. KNumOfParams is maximum number of
// parameters in the resource string.
const TInt KIntSize(11); //Max 11 digits.
const TInt KNumOfParams(20); //Max 20 parameters
const TInt KKeySize (4); //Max 2 digits in index. For example %20U

// Key strings for number and unicode data.
_LIT(KNumKeyBuf, "%N"); //Number data
_LIT(KStringKeyBuf, "%U"); //Unicode data

// Key characters to format key strings.
const TText KKeyPrefix('%');
const TText KNumKey('N');
const TText KStringKey('U');
const TText KSubStringSeparator(0x0001);	// pipe ('|') character
const TText KDirNotFound( 0x0002 );

const TInt KNoIndex(-1); //No index- code in Format-method.

//Panic category
_LIT(KPanicCategory, "TulTextResourceUtils");

const TInt KExtraSpaceForMainStringDirMarker = 1;
const TInt KExtraSpaceForSubStringDirMarkers = 2;
const TText KLRMarker = 0x200E;
const TText KRLMarker = 0x200F;

// KUnknownCount is used as default value for param count in FormatStringL
const TInt KUnknownCount(-99);

//
// class TulTextResourceUtils
//

/**
Reads a resource string without memory allocation. The loaded string is stored in the 
destination TDes&. Because this method doesn't allocate memory the destination 
descriptor must be long enough.

@param aResourceId The numeric ID of the resource string to be read.
@param aDest Reference to the descriptor where the resource string is loaded.
@param aLoaderEnv Pointer to the control environment. If user doesn't
                   give this, CCoeEnv::Static is called to get it.

@panic ECCoeEnvNotInitialized Parameter aLoaderEnv is NULL and CCoeEnv::Static returned NULL.
*/
EXPORT_C void TulTextResourceUtils::Load(TDes& aDest, TInt aResourceId, CCoeEnv* aLoaderEnv)
    {
    if (!aLoaderEnv)
        {
        aLoaderEnv=CCoeEnv::Static();
        if (!aLoaderEnv)
            User::Panic(KPanicCategory, ECCoeEnvNotInitialized);
        }

    //If aDes is too small, this function causes CCoeEnv::HandleError() to be called.
    TInt ignore(KErrNone); // To avoid compiler warning.
    // Trapped because ReadResource() is deprecated and method cannot leave.
    TRAP(ignore, aLoaderEnv->ReadResourceL(aDest, aResourceId));
	}

/**
Reads a resource string with memory allocation. 

@param aResourceId The numeric ID of the resource string to be read.
@param aLoaderEnv Pointer to the control environment. If user doesn't
                   give this, CCoeEnv::Static is called to get it.
@return Pointer to a heap descriptor containing the resource
         string. The calling program must destroy the heap descriptor
         when it is no longer needed.

@leave KErrNotSupported Parameter aLoaderEnv is NULL and CCoeEnv::Static returned NULL.
*/
EXPORT_C HBufC* TulTextResourceUtils::LoadL(TInt aResourceId, CCoeEnv* aLoaderEnv)
    {
    if (!aLoaderEnv)
        {
        aLoaderEnv=CCoeEnv::Static();
        if (!aLoaderEnv)
            User::Leave(KErrNotSupported);
        }
    return aLoaderEnv->AllocReadResourceL(aResourceId);
	}

/**
Reads a resource string with memory allocation and replaces the first \%N-string in it 
with replacement TInt. In debug builds the Symbian OS panic mechanism is used to 
notify programming errors.
 
@param aResourceId The numeric ID of the resource string to be read.
@param aInt The replacing TInt.
@param aLoaderEnv Pointer to the control environment. If user doesn't
        			give this, CCoeEnv::Static is called to get it.
@return Pointer to a heap descriptor containing the formatted
        resource string. The calling program must destroy the heap 
        descriptor when it is no longer needed.

@panic EKeyStringNotFound In debug build if the key string 'N' wasn't
                           found in formatting.
@leave KErrNotSupported Parameter aLoaderEnv is NULL and CCoeEnv::Static returned NULL.
*/
EXPORT_C HBufC* TulTextResourceUtils::LoadL(TInt aResourceId, TInt aInt, CCoeEnv* aLoaderEnv)
    {
    HBufC* resbuf = LoadLC(aResourceId, aLoaderEnv);
    TPtr retptr = resbuf->Des();
    //
    //Converting input TInt to a descriptor. This way the size
    //of the return string can be controlled.
    //
    TBuf<KIntSize> intbuf;
    intbuf.Num(aInt);

    if (LanguageSpecificNumberConverter::IsConversionNeeded())
        LanguageSpecificNumberConverter::Convert(intbuf);
    //
    // Get number of sub strings
    TInt count = GetSubStringCount(retptr); 
    TBool marker(EFalse); 
    
    if (count >= 1)
        {
        HBufC* buffer = ResolveSubStringDirsL(retptr, count, &marker);
        CleanupStack::PushL(buffer);
        
        TBool found(EFalse);
        TBidiText::TDirectionality mainDir = DirectionalityL(*buffer , &found);
        
        //Adding int    
        HBufC* retbuf = FormatStringL(*buffer, KNumKeyBuf, intbuf, mainDir);
        
        CleanupStack::PopAndDestroy(buffer);
        CleanupStack::PopAndDestroy(resbuf);
                        
        if (marker && retbuf->Length())
            {
            TPtr ptr = retbuf->Des();
            RemoveNoDirMarkers(ptr);
            } 
        __ASSERT_DEBUG(retbuf->Length(), 
                    User::Panic(KPanicCategory, EKeyStringNotFound));
        return retbuf;
        }
     else
        {
        CleanupStack::PopAndDestroy(resbuf);
        HBufC* retbuf = HBufC::NewL(0); // return empty buffer
        __ASSERT_DEBUG(retbuf->Length(), 
                    User::Panic(KPanicCategory, EKeyStringNotFound));
        return retbuf;
        }
   	}

/**
Reads a resource string with memory allocation and replaces the first \%U-string in it 
with replacement string. In debug builds the Symbian OS panic mechanism is used to 
notify programming errors.

@param aResourceId The numeric ID of the resource string to be read.
@param aString Reference to the replacing string.
@param aLoaderEnv Pointer to the control environment. If user doesn't
                   give this, CCoeEnv::Static is called to get it.
@return Pointer to a heap descriptor containing the formatted
         resource string. The calling program must destroy the heap 
         descriptor when it is no longer needed.

@panic EKeyStringNotFound In debug build if the key string 'U' wasn't
                           found in formatting.
@leave KErrNotSupported Parameter aLoaderEnv is NULL and 
                         CCoeEnv::Static returned NULL.
*/
EXPORT_C HBufC* TulTextResourceUtils::LoadL(TInt aResourceId, const TDesC& aString, CCoeEnv* aLoaderEnv)
    {
    HBufC* resbuf = LoadLC(aResourceId, aLoaderEnv);
    TPtr retptr(resbuf->Des());
        
    // Get number of sub strings
    TInt count = GetSubStringCount(retptr); 
    TBool marker(EFalse); 
    
    if (count >= 1)
        {
        HBufC* buffer = ResolveSubStringDirsL(retptr, count, &marker);
        CleanupStack::PushL(buffer);
        
        TBool found(EFalse);
        TBidiText::TDirectionality mainDir = DirectionalityL(*buffer , &found);
        
        //Formating the return string with FormatStringL.
        HBufC* retbuf = FormatStringL(*buffer, KStringKeyBuf, aString, mainDir);
        
        CleanupStack::PopAndDestroy(buffer);
        CleanupStack::PopAndDestroy(resbuf);
                        
        if (marker && retbuf->Length())
            {
            TPtr ptr = retbuf->Des();
            RemoveNoDirMarkers(ptr);
            } 
            
        __ASSERT_DEBUG(retbuf->Length(), 
                    User::Panic(KPanicCategory, EKeyStringNotFound));    
        return retbuf;
        }
     else
        {
        CleanupStack::PopAndDestroy(resbuf);
        HBufC* retbuf = HBufC::NewL(0); // return empty buffer
        __ASSERT_DEBUG(retbuf->Length(), 
                    User::Panic(KPanicCategory, EKeyStringNotFound));
        return retbuf;
        }
   	}

/**
Reads a resource string with memory allocation, replaces the first \%N-string in it with
replacement TInt and the first \%U-string in it with replacement string. 
In debug builds the Symbian OS panic mechanism is used to 
notify programming errors.

@param aResourceId The numeric ID of the resource string to be read.
@param aString Reference to the replacing string.
@param aInt The replacing TInt.
@param aLoaderEnv Pointer to the control environment. If user doesn't
                   give this, CCoeEnv::Static is called to get it.
@return Pointer to a heap descriptor containing the formatted
         resource string. The calling program must destroy the heap
         descriptor when it is no longer needed.

@panic EKeyStringNotFound In debug build if the key string 'N' or 'U'
                           wasn't found in formatting.
@leave KErrNotSupported Parameter aLoaderEnv is NULL and 
                         CCoeEnv::Static returned NULL.
*/
EXPORT_C HBufC* TulTextResourceUtils::LoadL(TInt aResourceId, const TDesC& aString, TInt aInt, CCoeEnv* aLoaderEnv)
    {
    HBufC* resbuf = LoadLC(aResourceId, aLoaderEnv);
    TPtr retptr = resbuf->Des();
            
    //Converting input TInt to a descriptor. This way the size
    //of the return string can be controlled.
    TBuf<KIntSize> intbuf;
    intbuf.Num(aInt);
    
    if (LanguageSpecificNumberConverter::IsConversionNeeded())
        LanguageSpecificNumberConverter::Convert(intbuf);
 
    // Get number of sub strings
    TInt count = GetSubStringCount(retptr); 
    TBool marker(EFalse); 
    
    if (count >= 1)
        {
        HBufC* buffer = ResolveSubStringDirsL(retptr, count, &marker);
        CleanupStack::PushL(buffer);
        
        TBool found(EFalse);
        TBidiText::TDirectionality mainDir = DirectionalityL(*buffer , &found);
        
        //Adding int    
        HBufC* cacbuf = FormatStringL(*buffer, KNumKeyBuf, intbuf, mainDir);
        CleanupStack::PushL(cacbuf);
        
        // Resolve directionality of the modified text and 
        // forward information to Formater().
        mainDir = DirectionalityL(*cacbuf, &found);
      
        //Adding string.
        HBufC* retbuf = FormatStringL(*cacbuf, KStringKeyBuf, aString, mainDir);
        __ASSERT_DEBUG(retbuf->Length(), 
                        User::Panic(KPanicCategory, EKeyStringNotFound));
        
        CleanupStack::PopAndDestroy(cacbuf);
        CleanupStack::PopAndDestroy(buffer);
        CleanupStack::PopAndDestroy(resbuf);
        
        if (marker && retbuf->Length())
            {
            TPtr ptr = retbuf->Des();
            RemoveNoDirMarkers(ptr);
            }   

        __ASSERT_DEBUG(retbuf->Length(), 
                        User::Panic(KPanicCategory, EKeyStringNotFound));
        return retbuf;
        }
    else
        {
        CleanupStack::PopAndDestroy(resbuf);
        HBufC* retbuf = HBufC::NewL(0); // return empty buffer
        __ASSERT_DEBUG(retbuf->Length(), 
                        User::Panic(KPanicCategory, EKeyStringNotFound));
        return retbuf;
        }
   	}

/**
Reads a resource string with memory allocation and replaces the \%(index)N-strings 
in it with replacement TInts from an array. In debug builds the Symbian OS 
panic mechanism is used to notify programming errors.

@param aResourceId The numeric ID of the resource string to be read.
@param aInts Reference to the array including the replacing TInts.
@param aLoaderEnv Pointer to the control environment. If user doesn't
                   give this, CCoeEnv::Static is called to get it.
@return Pointer to a heap descriptor containing the formatted
         resource string. The calling program must destroy the heap
         descriptor when it is no longer needed.

@panic ETooManyArguments In debug build if too many replacing 
                         elements in aInts array.
@leave KErrNotSupported Parameter aLoaderEnv is NULL and 
                        CCoeEnv::Static returned NULL.
*/
EXPORT_C HBufC* TulTextResourceUtils::LoadL(TInt aResourceId, const CArrayFix<TInt>& aInts, CCoeEnv* aLoaderEnv)
    {
    HBufC* resbuf = LoadLC(aResourceId, aLoaderEnv);
    TPtr retptr(resbuf->Des());
    TInt max = aInts.Count(); //Number of keystrings in resource string
    __ASSERT_DEBUG(max <= KNumOfParams, 
                    User::Panic(KPanicCategory, ETooManyArguments));
    
    TInt count = GetSubStringCount(retptr); 
    TBool marker(EFalse); 
    
    if (count >= 1)
        {
        HBufC* buffer = ResolveSubStringDirsL(retptr, count, &marker);
        CleanupStack::PushL(buffer);
        
        TBool found(EFalse);
        TBidiText::TDirectionality mainDir = DirectionalityL(*buffer , &found);
        
        //Formating the return string with FormatStringL. 
        HBufC* retbuf = FormatStringL(*buffer, aInts, max, mainDir);
        
        CleanupStack::PopAndDestroy(buffer);
        CleanupStack::PopAndDestroy(resbuf);
                        
        if (marker && retbuf->Length())
            {
            TPtr ptr = retbuf->Des();
            RemoveNoDirMarkers(ptr);
            } 
            
        __ASSERT_DEBUG(retbuf->Length(), 
                    User::Panic(KPanicCategory, EKeyStringNotFound));    
        return retbuf;
        }
     else
        {
        CleanupStack::PopAndDestroy(resbuf);
        HBufC* retbuf = HBufC::NewL(0); // return empty buffer
        __ASSERT_DEBUG(retbuf->Length(), 
                    User::Panic(KPanicCategory, EKeyStringNotFound));
        return retbuf;
        }
    }

/**
Reads a resource string with memory allocation and replaces the \%(index)U-strings 
in it with replacement strings from an array. In debug builds the Symbian OS 
panic mechanism is used to notify programming errors.

@param aResourceId The numeric ID of the resource string to be read.
@param aStrings Reference to the array  including pointers to the
                replacing strings.
@param aLoaderEnv Pointer to the control environment. If user doesn't
                  give this, CCoeEnv::Static is called to get it.
@return Pointer to a heap descriptor containing the formatted
         resource string. The calling program must destroy the heap
         descriptor when it is no longer needed.        
        
@panic ETooManyArguments In debug build if too many replacing 
                          elements in aStrings 
                          array.
@leave KErrNotSupported Parameter aLoaderEnv is NULL and 
                         CCoeEnv::Static returned NULL.
*/
EXPORT_C HBufC* TulTextResourceUtils::LoadL(TInt aResourceId, const MDesCArray& aStrings, CCoeEnv* aLoaderEnv)
    {
    HBufC* resbuf = LoadLC(aResourceId, aLoaderEnv);
    TPtr retptr(resbuf->Des());
    
    TInt max = aStrings.MdcaCount(); //Number of keystrings in resource string
    __ASSERT_DEBUG(max <= KNumOfParams, 
                    User::Panic(KPanicCategory, ETooManyArguments));
                    
    TInt count = GetSubStringCount(retptr); 
    TBool marker(EFalse); 
    
    if (count >= 1)
        {
        HBufC* buffer = ResolveSubStringDirsL(retptr, count, &marker);
        CleanupStack::PushL(buffer);
        
        TBool found(EFalse);
        TBidiText::TDirectionality mainDir = DirectionalityL(*buffer , &found);
        
        //Formating the return string with FormatStringL. 
        HBufC* retbuf = FormatStringL(*buffer, aStrings, max, mainDir);
    
        CleanupStack::PopAndDestroy(buffer);
        CleanupStack::PopAndDestroy(resbuf);
                        
        if (marker && retbuf->Length())
            {
            TPtr ptr = retbuf->Des();
            RemoveNoDirMarkers(ptr);
            } 
            
        __ASSERT_DEBUG(retbuf->Length(), 
                    User::Panic(KPanicCategory, EKeyStringNotFound));    
        return retbuf;
        }
     else
        {
        CleanupStack::PopAndDestroy(resbuf);
        HBufC* retbuf = HBufC::NewL(0); // return empty buffer
        __ASSERT_DEBUG(retbuf->Length(), 
                    User::Panic(KPanicCategory, EKeyStringNotFound));
        return retbuf;
        }
    }

/**
Reads a resource string with memory allocation and replaces the
\%(index)U-strings in it with replacement strings from an array and
the \%(index)N-strings in it with replacement TInts from another
array. In debug builds the Symbian OS panic mechanism is used to 
notify programming errors.

@param aResourceId The numeric ID of the resource string to be read.
@param aStrings Reference to the array including pointers to the
                 replacing strings.
@param aInts Reference to the array including the replacing TInts.
@param aLoaderEnv Pointer to the control environment. If user doesn't
                   give this, CCoeEnv::Static is called to get it.
@return Pointer to a heap descriptor containing the formatted
         resource string. The calling program must destroy the heap
         descriptor when it is no longer needed.        
        
@panic ETooManyArguments In debug build if too many replacing 
                          elements in aStrings and/or aInts arrays.
@leave KErrNotSupported Parameter aLoaderEnv is NULL and 
                         CCoeEnv::Static returned NULL.
*/
EXPORT_C HBufC* TulTextResourceUtils::LoadL(TInt aResourceId, const MDesCArray& aStrings, const CArrayFix<TInt>& aInts, CCoeEnv* aLoaderEnv)
    {
    HBufC* resbuf = LoadLC(aResourceId, aLoaderEnv);
    TPtr retptr(resbuf->Des());
    
    //Number of keystrings in resource string.
    TInt max = (aInts.Count() + aStrings.MdcaCount()); 
    __ASSERT_DEBUG(max <= KNumOfParams, User::Panic(KPanicCategory,
                    ETooManyArguments));
    
    // Get number of sub strings
    TInt count = GetSubStringCount(retptr); 
    TBool marker(EFalse); 
    
    if (count >= 1)
        {
        HBufC* buffer = ResolveSubStringDirsL(retptr, count, &marker);
        CleanupStack::PushL(buffer);
        
        TBool found(EFalse);
        TBidiText::TDirectionality mainDir = DirectionalityL(*buffer , &found);
        
        //Adding int    
        HBufC* cacbuf = FormatStringL(*buffer, aInts, max, mainDir); //Adding ints
        CleanupStack::PushL(cacbuf);
        
        // Resolve directionality of the modified text and 
        // forward information to Formater().
        mainDir = DirectionalityL(*cacbuf, &found);
      
        //Adding string.
        HBufC* retbuf = FormatStringL(*cacbuf, aStrings, max, mainDir); //Adding strings
        __ASSERT_DEBUG(retbuf->Length(), 
                        User::Panic(KPanicCategory, EKeyStringNotFound));
        
        CleanupStack::PopAndDestroy(cacbuf);
        CleanupStack::PopAndDestroy(buffer);
        CleanupStack::PopAndDestroy(resbuf);
        
        if (marker && retbuf->Length())
            {
            TPtr ptr = retbuf->Des();
            RemoveNoDirMarkers(ptr);
            }   

        __ASSERT_DEBUG(retbuf->Length(), 
                        User::Panic(KPanicCategory, EKeyStringNotFound));
        return retbuf;
        }
    else
        {
        CleanupStack::PopAndDestroy(resbuf);
        HBufC* retbuf = HBufC::NewL(0); // return empty buffer
        __ASSERT_DEBUG(retbuf->Length(), 
                        User::Panic(KPanicCategory, EKeyStringNotFound));
        return retbuf;
        }
    }

/**
Reads a resource string with memory allocation and pushes the string 
onto the cleanup stack.

@param aResourceId The numeric ID of the resource string to be read.
@param aLoaderEnv Pointer to the control environment. If user doesn't
                   give this, CCoeEnv::Static is called to get it.
@return Pointer to a heap descriptor containing the resource
         string. This pointer is in the cleanup stack. The calling 
         program should pop and destroy the heap descriptor when it is
         no longer needed.
        
@leave KErrNotSupported Parameter aLoaderEnv is NULL and 
                         CCoeEnv::Static returned NULL.
*/
EXPORT_C HBufC* TulTextResourceUtils::LoadLC(TInt aResourceId, CCoeEnv* aLoaderEnv)
    {
    if (!aLoaderEnv)
        {
        aLoaderEnv=CCoeEnv::Static();
        if (!aLoaderEnv)
            User::Leave(KErrNotSupported);
        }

    return aLoaderEnv->AllocReadResourceLC(aResourceId);
	}

/**
Reads a resource string with memory allocation, replaces the first \%N-string 
in it with replacement TInt and pushes the string onto the cleanup stack. In debug builds
the Symbian OS panic mechanism is used to notify programming errors.

@param aResourceId The numeric ID of the resource string to be read.
@param aInt the replacing TInt.
@param aLoaderEnv Pointer to the control environment. If user doesn't
                   give this, CCoeEnv::Static is called to get it.
@return pointer to a heap descriptor containing the formatted
         resource string. This pointer is in the cleanup stack. 
         The calling program should pop and destroy the heap 
         descriptor when it is no longer needed.

@panic EKeyStringNotFound In debug build if the key string 'N' wasn't
                           found in formatting.
@leave KErrNotSupported Parameter aLoaderEnv is NULL and 
                         CCoeEnv::Static returned NULL.
*/
EXPORT_C HBufC* TulTextResourceUtils::LoadLC(TInt aResourceId, TInt aInt, CCoeEnv* aLoaderEnv)
    {
    HBufC* retbuf = LoadL(aResourceId, aInt, aLoaderEnv);
    CleanupStack::PushL(retbuf);
    return retbuf;
   	}

/**
Reads a resource string with memory allocation, replaces the first \%U-string 
in it with replacement string and pushes the string onto the cleanup stack. 
In debug builds the Symbian OS panic mechanism is used to notify programming errors.

@param aResourceId The numeric ID of the resource string to be read.
@param aString Reference to the replacing string.
@param aLoaderEnv Pointer to the control environment. If user doesn't
                   give this, CCoeEnv::Static is called to get it.
@return Pointer to a heap descriptor containing the formatted
         resource string. This pointer is in the cleanup stack.
         The calling program should pop and destroy the heap 
         descriptor when it is no longer needed.

@panic EKeyStringNotFound In debug build if the key string 'U' wasn't
                           found in formatting.
@leave KErrNotSupported Parameter aLoaderEnv is NULL and 
                         CCoeEnv::Static returned NULL.
*/
EXPORT_C HBufC* TulTextResourceUtils::LoadLC(TInt aResourceId, const TDesC& aString, CCoeEnv* aLoaderEnv)
    {
    HBufC* retbuf = LoadL(aResourceId, aString, aLoaderEnv);
    CleanupStack::PushL(retbuf);
    return retbuf;
   	}

/**
Reads a resource string with memory allocation, replaces the first \%N-string 
in it with replacement TInt and the first \%U-string in it with replacement
string and pushes the string onto the cleanup stack. In debug builds
the Symbian OS panic mechanism is used to notify programming errors.

@param aResourceId The numeric ID of the resource string to be
                    read.
@param aString Reference to the replacing string.
@param aInt The replacing TInt.
@param aLoaderEnv Pointer to the control environment. If user doesn't
                   give this, CCoeEnv::Static is called to get it.
@return Pointer to a heap descriptor containing the formatted
         resource string. This pointer is in the cleanup stack.
         The calling program should pop and destroy the heap 
         descriptor when it is no longer needed.

@panic EKeyStringNotFound In debug build if the key string 'N' or 'U'
                           wasn't found in formatting.
@leave KErrNotSupported Parameter aLoaderEnv is NULL and 
                         CCoeEnv::Static returned NULL.
*/
EXPORT_C HBufC* TulTextResourceUtils::LoadLC(TInt aResourceId, const TDesC& aString, TInt aInt, CCoeEnv* aLoaderEnv)
    {
    HBufC* retbuf = LoadL(aResourceId, aString, aInt, aLoaderEnv);
    CleanupStack::PushL(retbuf);
    return retbuf;
   	}

/**
Reads a resource string with memory allocation, replaces the \%(index)N-strings in it with
replacement TInts from an array and pushes the string onto the
cleanup stack. In debug builds the Symbian OS panic mechanism is 
used to notify programming errors.

@param aResourceId The numeric ID of the resource string to be
                   read.
@param aInts Reference to the array including the replacing TInts.
@param aLoaderEnv Pointer to the control environment. If user doesn't
                   give this, CCoeEnv::Static is called to get it.
@return Pointer to a heap descriptor containing the formatted
         resource string. This pointer is in the cleanup stack.
         The calling program should pop and destroy the heap 
         descriptor when it is no longer needed.

@panic ETooManyArguments In debug build if too many replacing 
                          elements in aInts array.
@leave KErrNotSupported Parameter aLoaderEnv is NULL and 
*                         CCoeEnv::Static returned NULL.
*/
EXPORT_C HBufC* TulTextResourceUtils::LoadLC(TInt aResourceId, const CArrayFix<TInt>& aInts, CCoeEnv* aLoaderEnv)
    {
    HBufC* retbuf = LoadL(aResourceId, aInts, aLoaderEnv);
    CleanupStack::PushL(retbuf);
    return retbuf;
    }


/**
Reads a resource string with memory allocation, replaces the \%(index)U-strings 
in it with replacement strings from an array and pushes the string onto the
cleanup stack. In debug builds the Symbian OS panic mechanism is 
used to notify programming errors.

@param aResourceId The numeric ID of the resource string to be read.
@param aStrings Reference to the array  including pointers to the
                 replacing strings.
@param aLoaderEnv Pointer to the control environment. If user doesn't
                   give this, CCoeEnv::Static is called to get it.
@return Pointer to a heap descriptor containing the formatted
         resource string. This pointer is in the cleanup stack.
         The calling program should pop and destroy the heap 
         descriptor when it is no longer needed.

@panic ETooManyArguments In debug build if too many replacing 
                          elements in aStrings array.
@leave KErrNotSupported Parameter aLoaderEnv is NULL and 
                         CCoeEnv::Static returned NULL.
*/
EXPORT_C HBufC* TulTextResourceUtils::LoadLC(TInt aResourceId, const MDesCArray& aStrings, CCoeEnv* aLoaderEnv)
    {
    HBufC* retbuf = LoadL(aResourceId, aStrings, aLoaderEnv);
    CleanupStack::PushL(retbuf);
    return retbuf;
    }

/**
Reads a resource string with memory allocation, replaces the \%(index)U-strings 
in it with replacement strings from an array. Replaces
the \%(index)N-strings with replacement TInts from another
array. Pushes the string onto the cleanup stack. In debug builds
the Symbian OS panic mechanism is used to notify programming errors.

@param aResourceId The numeric ID of the resource string to be read.
@param aStrings Reference to the array including pointers to the
                 replacing strings.
@param aInts Reference to the array including the replacing TInts.
@param aLoaderEnv Pointer to the control environment. If user doesn't
                   give this, CCoeEnv::Static is called to get it.
@return Pointer to a heap descriptor containing the formatted
         resource string. This pointer is in the cleanup stack.
         The calling program should pop and destroy the heap 
         descriptor when it is no longer needed.
        
@panic ETooManyArguments In debug build if too many replacing 
                          elements in aStrings and/or aInts arrays.
@leave KErrNotSupported Parameter aLoaderEnv is NULL and 
                         CCoeEnv::Static returned NULL.
*/
EXPORT_C HBufC* TulTextResourceUtils::LoadLC(TInt aResourceId, const MDesCArray& aStrings, const CArrayFix<TInt>& aInts, CCoeEnv* aLoaderEnv)
    {
    HBufC* retbuf = LoadL(aResourceId, aStrings, aInts, aLoaderEnv); 
    CleanupStack::PushL(retbuf);
    return retbuf;
    }

/**
Formats a resource string without memory allocation. The formatted string 
is stored in the destination TDes&. Since this method doesn't allocate memory the 
destination descriptor must be long enough. In aPosition -1 means 
that there is no index in the key string and all \%U-strings in the
original string are replaced with aSubs. In debug builds the 
Symbian OS panic mechanism is used to notify programming errors.

@param aDest Reference to the descriptor where the resource string
              is formatted.
@param aSource Reference to the original string.
@param aPosition The index of the key string.
@param aSubs Reference to the replacing string.
       
@panic EInvalidIndex In debug build if the index of the key string 
                      is invalid.
@panic EDescriptorTooSmall In debug build if the length of the 
                            destination descriptor is too small.
@panic EKeyStringNotFound In debug build if the key string 'U' wasn't
                           found, aDest is empty.

One small sample describing the usage of the method.
@code
 // Load example string "%0U %1U" defined in rss- and loc-files.
 // %0U stands for weekday string and %1U for date string.
 HBufC* timeFormat = TulTextResourceUtils::LoadLC(R_TIME_FORMAT, iEikonEnv);

 // The replacing string.
 _LIT(dateString, "02/10/2006");

 TulTextResourceUtils::Format(destBuf, timeFormat, 
                       1, // %1U stands for date string
                       dateString);

 // After returning destBuf contains string "%0U 02/10/2006".
 @endcode
*/
EXPORT_C void TulTextResourceUtils::Format(TDes& aDest, const TDesC& aSource, TInt aPosition, const TDesC& aSubs)
    {
    //Checking the index.
    __ASSERT_DEBUG((aPosition >= KNoIndex && aPosition <=KNumOfParams), 
                    User::Panic(KPanicCategory, EInvalidIndex));
    //
    //Formating the keystring.
    //
    TBuf<KKeySize> keybuf;
    KeyStringFormater(keybuf, KStringKey, aPosition, KStringKeyBuf);

#ifdef _RD_COMMONENGINE_DETAILED_TRACE
    TInt paramCount = GetParamCount(aSource, aPosition);
    #ifdef _DEBUG
    TInt checklength(0);
    #endif
    TInt subslength(aSubs.Length() * paramCount);
    TInt keylength(keybuf.Length() * paramCount);
    if (subslength > keylength)
        {
        #ifdef _DEBUG
        checklength = 
        #endif
        aSource.Length()+subslength-keylength;
        }
    else
        {
        #ifdef _DEBUG
        checklength = 
        #endif
        aSource.Length();
        }

    //Checking the length of the destination descriptor.
    __ASSERT_DEBUG(checklength <= aDest.MaxLength(), User::Panic(
                   KPanicCategory, EDescriptorTooSmall));
#endif // _RD_COMMONENGINE_DETAILED_TRACE

    TRAPD( err, FormatL( aDest, aSource, keybuf, aSubs ) );
    
    if ( err != KErrNone )
        {
        aDest.Zero();
        aDest.Copy(aSource);
        TBool found(EFalse);
        TBidiText::TDirectionality dir = ResolveDirectionality(aDest, &found);
        aDest.Zero();

        //Formating the resource string.
	    Formater(aDest, aSource, keybuf, aSubs, dir);
        }
    
    //If the key string wasn't found, aDest is empty.
    __ASSERT_DEBUG( aDest.Length(), User::Panic( KPanicCategory,
                    EKeyStringNotFound ) );
    }

/**
Formats a resource string without memory allocation. The formatted string is stored 
in the destination TDes&. Since this method doesn't allocate memory the destination 
descriptor must be long enough. In aPosition -1 means that there is
no index in the key string and all \%N-strings in the original string 
are replaced with aSubs. In debug builds the Symbian OS panic 
mechanism is used to notify programming errors.

@param aDest Reference to the descriptor where the resource string
              is formatted.
@param aSource Reference to the original string.
@param aPosition The index of the key string.
@param aSubs The replacing TInt.

@panic EInvalidIndex In debug build if the index of the key string 
                      is invalid.
@panic EDescriptorTooSmall In debug build if the length of the 
                            destination descriptor is too small.
@panic EKeyStringNotFound In debug build if the key string 'N' wasn't
                           found, aDest is empty.

One small sample describing the usage of the method.
 @code
 // Load example string "%0N %1N" defined in rss- and loc-files.
 // %0N stands for area code and %1N for phone number.
 HBufC* telFormat = TulTextResourceUtils::LoadLC(R_TEL_FORMAT, iEikonEnv);

 // The replacing number.
 TInt areaCode(123);

 TulTextResourceUtils::Format(destBuf, telFormat, 
                       0, // %0N stands for area code
                       areaCode);

 // After returning destBuf contains string "123 %1N".
*/
EXPORT_C void TulTextResourceUtils::Format(TDes& aDest, const TDesC& aSource, TInt aPosition, TInt aSubs)
    {
    //Checking the index.
    __ASSERT_DEBUG((aPosition >= KNoIndex && aPosition <=KNumOfParams), 
                    User::Panic(KPanicCategory, EInvalidIndex));
    //
    //Formating the keystring.
    //
    TBuf<KKeySize> keybuf;
    KeyStringFormater(keybuf, KNumKey, aPosition, KNumKeyBuf);
    TBuf<KIntSize> intbuf;
    intbuf.Num(aSubs);
    
    if (LanguageSpecificNumberConverter::IsConversionNeeded())
        LanguageSpecificNumberConverter::Convert(intbuf);

#ifdef _RD_COMMONENGINE_DETAILED_TRACE
    TInt paramCount = GetParamCount(aSource, aPosition);
    #ifdef _DEBUG
    TInt checklength(0);
    #endif
    TInt subslength(intbuf.Length() * paramCount);
    TInt keylength(keybuf.Length() * paramCount);
    
    if (subslength > keylength)
        {
        #ifdef _DEBUG
        checklength = 
        #endif
        aSource.Length()+subslength-keylength;
        }
    else
        {
        #ifdef _DEBUG
        checklength = 
        #endif
        aSource.Length();
        }

    //Checking the length of the destination descriptor.
    __ASSERT_DEBUG(checklength <= aDest.MaxLength(), User::Panic(
                   KPanicCategory, EDescriptorTooSmall));
#endif // _RD_COMMONENGINE_DETAILED_TRACE
     TRAPD(err, FormatL(aDest, aSource, keybuf, intbuf));
     
     if(err != KErrNone)
        {
        aDest.Zero();
        aDest.Copy(aSource);
        TBool found(EFalse);
        TBidiText::TDirectionality dir = ResolveDirectionality(aDest, &found);
        aDest.Zero();

	    //Formating the resource string.
	    Formater(aDest, aSource, keybuf, intbuf, dir);
        }
    //
    //If the key string wasn't found, aDest is empty.
    //
    __ASSERT_DEBUG(aDest.Length(), User::Panic(KPanicCategory,
                   EKeyStringNotFound));
    }

/**
Finds the keystring from the source string and replaces it with the
replacement string.
*/
HBufC* TulTextResourceUtils::FormatStringL(const TDesC& aSource, const TDesC& aKey, const TDesC& aSubs,TBidiText::TDirectionality aDir)
    {
    TInt paramCount(KUnknownCount); // variable needed as it may be updated
    return FormatStringL(aSource, aKey, aSubs, aDir, paramCount, KUnknownCount);
    }

/**
Finds the keystring from the source string and replaces it with the
replacement string.
*/
HBufC* TulTextResourceUtils::FormatStringL(const TDesC& aSource, const TDesC& aKey, const TDesC& aSubs, TBidiText::TDirectionality aDirectionality,
    TInt& aParamCount, TInt aSubCount)
    {
    if (aParamCount == KUnknownCount)
        aParamCount = GetParamCount(aSource);

    if (aSubCount == KUnknownCount)
        aSubCount = GetSubStringCount(aSource);

    // determine lenght of needed buffer 
    TInt sourcelength(aSource.Length()); 
    TInt keylength(aKey.Length());
    TInt subslength(aSubs.Length());
    TInt destlength = 0;
    if (subslength >= keylength)
        {
        destlength = sourcelength + ((subslength - keylength) * aParamCount);
        }
    else
        {
        destlength = sourcelength;
        }

    destlength += KExtraSpaceForMainStringDirMarker * aSubCount;
    destlength += KExtraSpaceForSubStringDirMarkers * aParamCount;
    //
    // Allocating heap buffer for return string.
    //

    HBufC* retbuf = HBufC::NewL(destlength);
    TPtr retptr(retbuf->Des());

    // Formating the resource string. Don't bother with format, 
    // if parameter count is not above zero
    if (aParamCount > 0)
        {
        aParamCount -= Formater(retptr, aSource, aKey, aSubs, aDirectionality);
        __ASSERT_DEBUG(aParamCount >= 0, User::Invariant());
        }

    //
    // If the key string wasn't found, retbuf is empty.
    //
    return retbuf; 
    }

/**
Finds the \%(index)N-keystrings from the source string and replaces it with the
replacement TInts.
*/
HBufC* TulTextResourceUtils::FormatStringL(TDesC& aSource, const CArrayFix<TInt>& aInts, TInt aMax, TBidiText::TDirectionality aDir)
    {
    TInt numbers = aInts.Count(); //Number of input TInts.
    //
    //Allocating heap buffer for return string.
    //
    TInt paramCount = GetParamCount(aSource);
    TInt subCount = GetSubStringCount(aSource);
    HBufC* retbuf = HBufC::NewLC(
        aSource.Length() + 
        paramCount * KIntSize +
        paramCount * KExtraSpaceForSubStringDirMarkers +
        subCount * KExtraSpaceForMainStringDirMarker);
    TPtr retptr(retbuf->Des());

    TBidiText::TDirectionality mainDir = aDir;
        

    //The input TInt is converted to a descriptor. This way the size
    //of the return string can be controlled.
    TBuf<KIntSize> intbuf;

    //The key string must be formated again in the for-loop every round.
    TBuf<KKeySize> keybuf;

    //intcount keeps track of used TInts from aInts.
    TInt intcount(0);

    //loopcount counts the loops in the while loop.
    TInt loopcount(0);

    //The resource string is read from retptr and formatted in retbuf 
    //in every round.
    retptr.Append(aSource);

    while (loopcount <= aMax && paramCount > 0)
        {
        //Formating key string.
        keybuf.Zero();
        keybuf.Append(KKeyPrefix);
        keybuf.AppendNum(loopcount);
        keybuf.Append(KNumKey);

        //If all the TInts from aInts are used, the resource string is checked
        //for unsolved parameters.
        if (intcount == numbers)
            {
#ifdef _RD_COMMONENGINE_DETAILED_TRACE	// debug build
            HBufC* checkbuf = FormatStringL(retptr, keybuf, keybuf, mainDir, 
                                             paramCount, subCount);
            __ASSERT_DEBUG(!checkbuf->Length(), User::Panic(
                           KPanicCategory, ETooFewArguments));
            delete checkbuf;
#endif // _RD_COMMONENGINE_DETAILED_TRACE
            }
        else if (loopcount == aMax)
            {
#ifdef _RD_COMMONENGINE_DETAILED_TRACE	// debug build
            HBufC* checkbuf = FormatStringL(retptr, keybuf, keybuf, mainDir, 
                                             paramCount, subCount);
            __ASSERT_DEBUG(!checkbuf->Length(), User::Panic(
                           KPanicCategory, EInvalidIndex));
            delete checkbuf;
#endif // _RD_COMMONENGINE_DETAILED_TRACE
            }
        else
            {
            //Converting TInt.
            intbuf.Zero();
            intbuf.Num(aInts[intcount]);
            
            if (LanguageSpecificNumberConverter::IsConversionNeeded())
                LanguageSpecificNumberConverter::Convert(intbuf);

            //Formating the return string.
            HBufC* cacbuf = FormatStringL(retptr, keybuf, intbuf, mainDir, paramCount, subCount);
            TPtr cacptr(cacbuf->Des());

            //If the cacbuf is empty, the key string with this round's
            //index was a string variable. If there are no string 
            //variables in this resource string, it's an error.
            //
            if (cacptr.Length())
                {
                retptr = cacptr;
                intcount++;
                }
            else
                __ASSERT_DEBUG(numbers != aMax, User::Panic(KPanicCategory,
                                                             EInvalidIndex));
            delete cacbuf;
            }

        loopcount++;
        }
    __ASSERT_DEBUG(intcount == numbers, User::Panic(KPanicCategory,
                   ETooManyArguments));

    //Reallocating the return buffer to right size.
    retbuf = retbuf->ReAllocL(retptr.Length());
    CleanupStack::Pop(); //retbuf
    return retbuf;
    }

/**
Finds the \%(index)U-keystrings from the source string and replaces it with the
replacement strings.
*/
HBufC* TulTextResourceUtils::FormatStringL(TDesC& aSource, const MDesCArray& aStrings, TInt aMax, TBidiText::TDirectionality aDir)
    {
    TInt strings(aStrings.MdcaCount()); //Number of input strings.

    //Counting the overall length of input strings.
    TInt maxSubsLength(0);
    for (TInt i(0); i < strings; i++)
        {
        if (maxSubsLength < aStrings.MdcaPoint(i).Length())
            maxSubsLength = aStrings.MdcaPoint(i).Length();
        }

    //Allocating heap buffer for return string.
    TInt paramCount = GetParamCount(aSource);
    TInt subCount = GetSubStringCount(aSource);
    HBufC* retbuf = HBufC::NewLC(
        aSource.Length() + 
        paramCount * maxSubsLength +   // worst case scenario; more accurate alloc 
                                       // would require complex analysis
        paramCount * KExtraSpaceForSubStringDirMarkers +
        subCount * KExtraSpaceForMainStringDirMarker);
    TPtr retptr(retbuf->Des());

    TBidiText::TDirectionality mainDir = aDir;
    
    //The key string must be formated again in the for-loop every round.
    TBuf<KKeySize> keybuf;

    //descount keeps track of used HBufC*'s from aStrings.
    TInt descount(0);

    //loopcount counts the loops in the while loop.
    TInt loopcount(0);

    //The resource strings is read from retptr and formatted in retbuf every round.
    retptr.Append(aSource);

    while (loopcount <= aMax && paramCount > 0)
        {
        //Formating key string.
        keybuf.Zero();
        keybuf.Append(KKeyPrefix);
        keybuf.AppendNum(loopcount);
        keybuf.Append(KStringKey);

        //If all the strings from aStrings are used, the resource string is 
        //checked for unsolved parameters.
        if (descount == strings)
            {
#ifdef _RD_COMMONENGINE_DETAILED_TRACE	// debug build
            HBufC* checkbuf = FormatStringL(retptr, keybuf, keybuf, mainDir, 
                                             paramCount, subCount);
            __ASSERT_DEBUG(!checkbuf->Length(), User::Panic(
                           KPanicCategory, ETooFewArguments));
            delete checkbuf;
#endif // _RD_COMMONENGINE_DETAILED_TRACE
            }
        else if (loopcount == aMax)
            {
#ifdef _RD_COMMONENGINE_DETAILED_TRACE	// debug build
            HBufC* checkbuf = FormatStringL(retptr, keybuf, keybuf, 
                                             mainDir, paramCount, subCount);
            __ASSERT_DEBUG(!checkbuf->Length(), User::Panic(
                            KPanicCategory, EInvalidIndex));
            delete checkbuf;
#endif // _RD_COMMONENGINE_DETAILED_TRACE
            }
        else
            {
            //Formating the return string.
            HBufC* cacbuf = FormatStringL(retptr, keybuf, aStrings.MdcaPoint(descount), mainDir, paramCount, subCount);
            TPtr cacptr(cacbuf->Des());

            //If the cacbuf is empty, the key string with this
            //round's index was a number variable. If there are no
            //number variables in this resource string, it's an error.
            if (cacptr.Length())
                {
                retptr = cacptr;
                descount++;
                }
            else
                __ASSERT_DEBUG(strings != aMax, User::Panic(KPanicCategory, EInvalidIndex));

            delete cacbuf;
            }
        loopcount++;
        }
        
    __ASSERT_DEBUG(descount == strings, User::Panic(KPanicCategory, ETooManyArguments));

    //Reallocating the return buffer to right size.
    retbuf = retbuf->ReAllocL(retptr.Length());
    CleanupStack::Pop(); //retbuf
    return retbuf;
    }

/**
Finds the keystring from the source string and replaces it with the
replacement string. The formated string is stored in the destination
descriptor.
*/
TInt TulTextResourceUtils::Formater(TDes& aDest, const TDesC& aSource, const TDesC& aKey, const TDesC& aSubs, TBidiText::TDirectionality aDirectionality)    
    {
    // substitute string must not contain KSubStringSeparator, 
    // or results will be unpredictable 
    __ASSERT_DEBUG(aSubs.Locate(KSubStringSeparator) == KErrNotFound, 
        User::Panic(KPanicCategory, EInvalidSubstitute));

    TInt keylength(aKey.Length());

    //aDest must be empty.
    aDest.Zero();

    // offset indicates end of last handled key in source
    TInt offset(0);

    // offset in destination string
    TInt desOffset(0);

    // Substring directionalities are adjusted after all changes are done.
    TBool checkSubstringDirectionalities(EFalse);

    // count is the position in the source from which the substring starts
    TInt count(0);

    // Replaced parameters count
    TInt replaceCount(0);

    while (count != KErrNotFound)
        {
        // desCount is the position of the substring starts in destination.
        TInt desCount(0);

        TPtrC remainder = aSource.Right(aSource.Length() - offset);
        count = remainder.Find(aKey);

        TInt maxSubLength = -1;
        if (count != KErrNotFound)
            {
            replaceCount++;
            desOffset += count;
            offset += count;
            count = offset;
            desCount = desOffset;

            // copy source to destination if first time
            if (aDest.Length() == 0)
                aDest.Append(aSource);

            // delete found key from destination
            aDest.Delete(desCount, keylength);

            offset += keylength; // increase offset by key length

            if (count + keylength < (aSource.Length()-1)) // aKey is not at the end of string
                {
                if (aSource[count+keylength] == '[') // Key includes max datalength
                    {
                    maxSubLength = 10*(aSource[count+keylength+1]-'0') 
                                   + (aSource[count+keylength+2]-'0');
                    aDest.Delete(desCount,4); // Length information stored->delete from descriptor
                    offset += 4; // increase offset by max sub length indicator
                    }
                }
         
            aDest.Insert(desCount, aSubs);
        
            desOffset = desCount + aSubs.Length();

            if (maxSubLength > 0 && aSubs.Length() > maxSubLength)
                {
                aDest.Delete(desCount+maxSubLength-1, aSubs.Length()+1-maxSubLength);     
                TText ellipsis(KEllipsis);
                aDest.Insert(desCount+maxSubLength-1, TPtrC(&ellipsis,1));
                desOffset = desCount + maxSubLength;
                }

            TBidiText::TDirectionality subsDir =
                TBidiText::TextDirectionality(aDest.Mid(desCount, desOffset - desCount));

            // If inserted string has different directionality,
            // insert directionality markers so that bidi algorithm works in a desired way.
            if (aDirectionality != subsDir)
                {
                checkSubstringDirectionalities = ETrue;

                TInt freeSpace = aDest.MaxLength() - aDest.Length();

                // Protect the directionality of the inserted string.
                if (freeSpace >= KExtraSpaceForSubStringDirMarkers)
                    {
                    TBuf<1> subsMarker;
                    subsMarker.Append(subsDir == TBidiText::ELeftToRight ?
                        KLRMarker : KRLMarker);

                    aDest.Insert(desOffset, subsMarker);
                    aDest.Insert(desCount, subsMarker);
                    desOffset += KExtraSpaceForSubStringDirMarkers;
                    }
                }
            }
        }

    // Adjust substring directionality markers if necessary
    // and if there is enough room in destination string
    if (checkSubstringDirectionalities)
        {
        TText mainMarker = (aDirectionality == TBidiText::ELeftToRight ? 
            KLRMarker : KRLMarker);

        TInt freeSpace = aDest.MaxLength() - aDest.Length();

        // If not already done, protect the directionality of the original string
        // and all of the KSubStringSeparator separated substrings.
        if (freeSpace > 0 
            && aDest.Length()
            && aDest[0] != mainMarker 
            && aDest[0] != KSubStringSeparator
            && aDest[0] != KDirNotFound)  
            {
            aDest.Insert(0, TPtrC(&mainMarker, 1));
            freeSpace--;
            }

        // Find and protect KSubStringSeparator separated substrings.
        // Go through string backwards so that any changes will not affect indexes 
        // that are not yet checked.
        TInt j(aDest.Length()-1);
        while (freeSpace > 0 && j >= 0) 
            {
            if (aDest[j] == KSubStringSeparator && j < (aDest.Length() - 1) 
                && aDest[j+1] != mainMarker && aDest[j+1] != KDirNotFound)
                {
                aDest.Insert(j+1, TPtrC(&mainMarker, 1));
                freeSpace--;
                }
            j--;
            }
        }

    return replaceCount;
    }

/**
Formats the keystring from given parameters.
*/
void TulTextResourceUtils::KeyStringFormater(TDes& aDest, const TText& aKey, TInt aPosition, const TDesC& aKeyString)
    {
    if (aPosition > KNoIndex)
        {
        aDest.Append(KKeyPrefix);
        aDest.AppendNum(aPosition);
        aDest.Append(aKey);
        }
    else
        {
        aDest.Append(aKeyString);
        }
    }

/**
Resolves directionality of the given source text.
Place-holder strings are removed so that they don't affect the result.
*/
TBidiText::TDirectionality TulTextResourceUtils::ResolveDirectionality(TDes& aText, TBool* aFound)
    {
    TInt i = 0;

    // Remove place-holders from string so they don't affect directionality
    // length parameters e.g. "[29]" do not contain strongly directional
    // characters so can ignore them.
    while (i < aText.Length())
        {
        TPtrC remainder = aText.Right(aText.Length() - i);
        TInt nextKey = remainder.Locate(KKeyPrefix);
        i += nextKey;

        if (nextKey != KErrNotFound && i < aText.Length() - 1)
            {
            TInt lastCharInKey = i + 1;

            // skip possible key index
            TText t = aText[lastCharInKey];
            if (t >= '0' && t <= '9')
                {
                lastCharInKey++;

                if (lastCharInKey < aText.Length())
                    {
                    t = aText[lastCharInKey];
                    if (t >= '0' && t <= '9')
                        {
                        lastCharInKey++;
                        }
                    }
                }

            // lastCharInKey is now the index of 'N' or 'U' in the key

            if (lastCharInKey < aText.Length())
                {
                TText t = aText[lastCharInKey];
                if (t == 'U' || t == 'N')
                    {
                    // found key, delete it and continue loop to
                    // search for the next key
                    aText.Delete(i, lastCharInKey - i + 1);
                    }
                // This was not a proper key - check the remaining string
                else
                    {
                    i = lastCharInKey + 1;
                    }
                }
            // end of string encountered - stop
            else
                {
                break;
                }
            }
        // no key found - stop
        else
            {
            break;
            }
        }

    return TBidiText::TextDirectionality(aText, aFound);
    }

/**
Counts the number of parameters in the text. 
Needed for correct memory allocations.
*/
TInt TulTextResourceUtils::GetParamCount(const TDesC& aText, TInt aIndex)
	{
    TInt paramCount(0);
    TInt i(0);
    TBool singleIndex((aIndex < 0) || (aIndex > KNumOfParams) ? EFalse : ETrue);

    while (i < aText.Length())
        {
        TPtrC remainder = aText.Right(aText.Length() - i);
        TInt nextKey = remainder.Locate(KKeyPrefix);
        i += nextKey;

        if (nextKey != KErrNotFound && i < aText.Length() - 1)
            {
            TInt lastCharInKey = i + 1;

            // skip possible key index
            TText t = aText[lastCharInKey];
            TInt foundIndex(-1);
            
            if (t >= '0' && t <= '9')
                {
                lastCharInKey++;
                foundIndex = t - '0';

                if (lastCharInKey < aText.Length())
                    {
                    t = aText[lastCharInKey];
                    if (t >= '0' && t <= '9')
                        {
                        foundIndex *= 10;
                        foundIndex += t - '0';
                        lastCharInKey++;
                        }
                    }
                }

            // lastCharInKey is now the index of 'N' or 'U' in the key

            if (lastCharInKey < aText.Length())
                {
                // Only count parameter, if index matches
                if (!singleIndex || (foundIndex == aIndex))
                    {
                    TText t = aText[lastCharInKey];
                    if (t == 'U' || t == 'N')
                        {
                        // found legit key, count it
                        paramCount++;
                        // continue search after index
                        i = lastCharInKey + 1;
                        }
                    else if (t == '%')
                        i = lastCharInKey;
                    else	// continue search after index
                        i = lastCharInKey + 1;
                    }
                else	// continue search after index
                    i = lastCharInKey + 1;
                }
            else	// end of string encountered - stop
                break;
            }
        else	 // no key found - stop
            break;
        }

    return paramCount;
	}

/**
Counts the number of substrings (separated by KSubStringSeparators) in the text. 
Needed for correct memory allocations.
*/
TInt TulTextResourceUtils::GetSubStringCount(const TDesC& aText)
	{
    TInt subCount = 0;
    TInt i = 0;

    while (i < aText.Length())
        {
        TPtrC remainder = aText.Right(aText.Length() - i);
        TInt nextKey = remainder.Locate(KSubStringSeparator);
        i += nextKey;

        // Always increase subcount, as a string without any separators counts as one substring.
        // However, if string length is zero, then there are no substrings.
        subCount++;

        if (nextKey != KErrNotFound && i < aText.Length() - 1)
            {
            i++; // skip separator
            }
        else
            break;
        }

    return subCount;
	}

/**
Resolves sub strings. Uses ResolveSubStringL()
*/
HBufC* TulTextResourceUtils::ResolveSubStringDirsL(TDes& aText, TInt aCount, TBool* aMarker)
    {   
    // Allocating heap buffer for return string.
    TInt destlength(aText.Length());
    destlength = destlength + (KExtraSpaceForMainStringDirMarker) * aCount;
    HBufC* retbuf = HBufC::NewLC(destlength);
    TPtr retptr(retbuf->Des());
    TInt freeSpace(destlength); 
    TInt i(0);
    TInt j(0);
    TBuf<1> subsMarker;
    subsMarker.Append(KSubStringSeparator);
    TInt count(aCount - 1);

    while (i  < aCount)
        {
        // Resolve sub string
        HBufC* buffer = ResolveSubStringL(aText, aMarker);
        TPtr ptr = buffer->Des();
        CleanupStack::PushL(buffer); 
        
        // Restore sub string separators
        if (freeSpace >= ptr.Length()) 
            {
            retptr.Insert(j, ptr);
            freeSpace -= ptr.Length();
            j += ptr.Length();
            if (freeSpace > KExtraSpaceForMainStringDirMarker && i < count)
                {
                retptr.Append(subsMarker);
                j ++;
                }
            }    
        CleanupStack::PopAndDestroy(buffer);  
        i++;                       
        } 
    
    retbuf = retbuf->ReAllocL(retptr.Length());
    CleanupStack::Pop(); //retbuf  
    return retbuf;
    }

/**
Resolves sub string and directionality of the sub string.
Adds no dir marker if directionality of the string not found.
*/
HBufC* TulTextResourceUtils::ResolveSubStringL(TDes& aText, TBool* aMarker)
    {
    // Allocating heap buffer for return string.
    TInt destlength(aText.Length());
    HBufC* retbuf = HBufC::NewLC(destlength + 1); // no dir marker
    TPtr retptr(retbuf->Des());
    
    TBuf<1> marker;
    marker.Append(KDirNotFound);
        
    TPtrC remainder = aText.Right(aText.Length());
    TInt nextKey = remainder.Locate(KSubStringSeparator);
    
    if (nextKey == 0)
        {
        remainder.Set(remainder.Mid(1));
        nextKey = remainder.Locate(KSubStringSeparator);
        if (nextKey != KErrNotFound)
            {
            retptr.Insert(0, aText.Mid(1, nextKey));           
            // Remove string from aText
            aText.Delete(0, nextKey + 1);
            }
        else
            {
            TInt length = aText.Length();
            retptr.Insert(0, aText.Mid(1, length - 1));
            // Remove string from aText
            aText.Delete(0, length);
            }
        }
    else if (nextKey == KErrNotFound)
        {
        retptr.Insert(0, aText); 
        // Remove string from aText
        aText.Delete(0, aText.Length());
        }
    else
        {
        retptr.Insert(0, aText.Mid(0, nextKey));
        // Remove string from aText
        aText.Delete(0, nextKey);
        }
     
    // Resolve directionality of sub string
    HBufC* dirbuf = retbuf->AllocL();
    TPtr dirptr = dirbuf->Des();
    TBool found(EFalse);
    TBidiText::TDirectionality mainDir = ResolveDirectionality(dirptr, &found);
    delete dirbuf;
    
    if (!found)
        {
        retptr.Insert(0, marker);
        *aMarker = ETrue;
        }
    else
        {
        *aMarker = EFalse;
        }
        
    retbuf = retbuf->ReAllocL(retptr.Length());
    CleanupStack::Pop(); //retbuf
    // If the key string wasn't found, retbuf is empty.
    return retbuf;     
    }
    
TBidiText::TDirectionality TulTextResourceUtils::DirectionalityL(const TDesC& aText, TBool* aFound)
    {
    // Resolve directionality of sub string
    HBufC* dirbuf = aText.AllocL();
    TPtr dirptr = dirbuf->Des();
    TBidiText::TDirectionality dir = ResolveDirectionality(dirptr, aFound);
    delete dirbuf;
    return dir;
    }
    
/**
Removes no dir markers from source text.
*/
void TulTextResourceUtils::RemoveNoDirMarkers(TDes& aText)
    {
    TInt nextkey(0);
    while (nextkey < aText.Length())
        {
        nextkey = aText.Locate(KDirNotFound);
        if (nextkey != KErrNotFound)
            {
            aText.Delete(nextkey, 1);
            nextkey++;    
            }
        else
            {
            break;
            }     
        }
    }
    
/**
Used by exported Format methods.
*/
void TulTextResourceUtils::FormatL(TDes& aDest, const TDesC& aSource, const TDesC& aKeybuf, const TDesC& aSubs)
{
    // Get number of sub strings 
    TInt count = GetSubStringCount(aSource); 
    
    if (count >= 1)
        {
        HBufC* retbuf = retbuf = aSource.AllocLC();
        
        TPtr retptr(retbuf->Des());
        TBool marker(EFalse); 
        HBufC* buffer = buffer = ResolveSubStringDirsL(retptr, count, &marker);
        
        CleanupStack::PushL(buffer);
        
        TBool found(EFalse);
        TBidiText::TDirectionality dir = DirectionalityL(*buffer, &found);
        
        if (!marker)
            {
            //Formating the resource string.
            Formater(aDest, aSource, aKeybuf, aSubs, dir);
            //If the key string wasn't found, aDest is empty.
            __ASSERT_DEBUG(aDest.Length(), User::Panic(KPanicCategory,
                            EKeyStringNotFound));
            }
        else            
            {
            // length of input string.
            TInt maxSubsLength = aSubs.Length();
            TInt subCount = GetSubStringCount(aSource);
            HBufC* destbuf = HBufC::NewLC(
                       aSource.Length() + 
                       count * maxSubsLength +   // worst case scenario; more accurate alloc 
                                                      // would require complex analysis
                       count * KExtraSpaceForSubStringDirMarkers +
                       subCount * KExtraSpaceForMainStringDirMarker + 
                       subCount * KExtraSpaceForMainStringDirMarker); // no dir markers             
            TPtr destptr(destbuf->Des());
            //Formating the resource string.
            Formater(destptr, *buffer, aKeybuf, aSubs, dir);
            
            if (destptr.Length())
                {
                RemoveNoDirMarkers(destptr);
                }
                
            aDest.Zero();
            aDest.Append(destptr);
            //If the key string wasn't found, aDest is empty.
            __ASSERT_DEBUG(aDest.Length(), User::Panic(KPanicCategory,EKeyStringNotFound));               
            CleanupStack::PopAndDestroy(destbuf);  
            }
        CleanupStack::PopAndDestroy(buffer);
        CleanupStack::PopAndDestroy(retbuf);
        }
    
    __ASSERT_DEBUG(aDest.Length(), User::Panic(KPanicCategory, EKeyStringNotFound));
	}
