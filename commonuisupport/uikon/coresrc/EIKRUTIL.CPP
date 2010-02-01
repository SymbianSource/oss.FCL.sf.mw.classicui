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

#include <eikenv.h> 
#include <eikrutil.h>
#include <barsread.h>
#include <gulcolor.h>
#include <gulfont.hrh>
#include <uikon.hrh>
#include <gulutil.h>

enum TEikPanicResourceUtil
	{
	EEikPanicResourceNonEnvironment,
	EEikPanicResourceNullPointer,
	EEikPanicResourceInvalidNumberType,
	};

LOCAL_C void Panic(TEikPanicResourceUtil aPanic)
	{
	_LIT(KPanicCat,"EIKON-RUTIL");
	User::Panic(KPanicCat, aPanic);
	}

EXPORT_C CFbsFont* EikResourceUtils::CreateScreenFontL(TInt aResourceId,CEikonEnv* aEnv)
/** Creates a screen font.

Creates a font for the specified environment by reading a font UID and font 
flags from the given resource. Returns a pointer to the font and transfers 
ownership.

@param aResourceId ID of the resource from which to read the font. 
@param aEnv The UI environment for which the screen font will be created. 
@return Pointer to the created screen font. */
	{
	if (aEnv==NULL)
		aEnv=CEikonEnv::Static();
	__ASSERT_DEBUG(aEnv!=NULL,Panic(EEikPanicResourceNonEnvironment));
	TResourceReader reader;
	aEnv->CreateResourceReaderLC(reader,aResourceId);
	CWsScreenDevice* screenDevice=aEnv->ScreenDevice();
	__ASSERT_DEBUG(screenDevice!=NULL,Panic(EEikPanicResourceNullPointer));
	CFbsFont* font=CreateScreenFontL(reader,*screenDevice);
	CleanupStack::PopAndDestroy(); // resource reader
	return(font);
	}


/**
Static private utility used by exported inline functions to read from resource file.
@param aResourceId 
@param aEnv May be Null
@param aSize Specifies integer size: EResourceInt8, EResourceInt16, EResourceInt32
@return Integer value read from resource.  May be 8, 16 or 32 bit value.
*/
EXPORT_C TInt32 EikResourceUtils::ReadResourceIntL(TInt aResourceId,CEikonEnv* aEnv,TResourceTypeInt aSize)
//
//	Read a resource specifying a number
//
	{
	if (aEnv==NULL)
		aEnv=CEikonEnv::Static();
	__ASSERT_DEBUG(aEnv!=NULL,Panic(EEikPanicResourceNonEnvironment));
	TResourceReader reader;
	aEnv->CreateResourceReaderLC(reader,aResourceId);
	TInt32 value=0;
	switch(aSize)
		{
	case EResourceInt8:
		value=reader.ReadInt8();
		break;
	case EResourceInt16:
		value=reader.ReadInt16();
		break;
	case EResourceInt32:
		value=reader.ReadInt32();
		break;
	default:
		Panic(EEikPanicResourceInvalidNumberType);
		}
	CleanupStack::PopAndDestroy(); // resource reader
	return(value);
	}

EXPORT_C CColorArray* EikResourceUtils::CreateColorArrayL(TInt aResourceId,CEikonEnv* aEnv)
/** Creates an array of colours from a resource definition.

@param aResourceId ID of the resource from which to read the colours. 
@param aEnv The UI environment in which the control colours are to be created. 
This is optional. 
@return Array of control colours. */
	{ // static
	CColorArray* colors=EikResourceUtils::CreateColorArrayLC(aResourceId,aEnv);
	CleanupStack::Pop(); // colors
	return colors;
	}

EXPORT_C CColorArray* EikResourceUtils::CreateColorArrayLC(TInt aResourceId,CEikonEnv* aEnv)
/** Creates an array of control colours from a resource definition and returns it 
on the cleanup stack.

@param aResourceId ID of the resource from which to create the array of control 
colours. 
@param aEnv The UI environment in which the control colours are to be created. 
@return Array of control colours. */
	{ // static
	if (aEnv==NULL)
		aEnv=CEikonEnv::Static();
	__ASSERT_DEBUG(aEnv!=NULL,Panic(EEikPanicResourceNonEnvironment));
	CColorArray* colors=CColorArray::NewLC();
	TResourceReader reader;
	aEnv->CreateResourceReaderLC(reader,aResourceId);
    TInt listId=reader.ReadInt32();
	CleanupStack::PopAndDestroy(); // reader
	aEnv->CreateResourceReaderLC(reader,listId);
	ResourceUtils::PopulateColorArrayL(*colors,reader);
	CleanupStack::PopAndDestroy(); // reader
	return colors;
	}
