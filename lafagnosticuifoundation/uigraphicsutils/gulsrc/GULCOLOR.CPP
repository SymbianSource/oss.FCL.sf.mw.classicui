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

#include <s32std.h>
#include <s32stor.h>
#include <s32strm.h>
#include <gulcolor.h>
#include <gulpanic.h>
#include "GULSTD.H"

const TUint KEikCustomColorsArrayValue=0x100057c2; // this constant is properly defined in Eikenv.h

//
// class CColorList
//

inline CColorList::TAppColorList::TAppColorList(TUid aApp, CColorArray* aColorArray)
	:iApp(aApp), iColorArray(aColorArray)
	{}

const TInt KGulColorGranularity=1;
const TInt KGulColListVer=1;

EXPORT_C CColorList* CColorList::NewLC()
/** Allocates and constructs a new colour list and puts the pointer 
to the new colour list object onto the cleanup stack.

@return The colour list. */
	{ // static
	CArrayFix<TRgb>* colors=new(ELeave) CArrayFixFlat<TRgb>(4);
	CleanupStack::PushL(colors);
	CColorList* self=new(ELeave) CColorList(colors);
	CleanupStack::Pop(); // colors;
	CleanupStack::PushL(self);
	return self;
	}

EXPORT_C CColorList* CColorList::NewL(CArrayFix<TRgb>* aColors)
/** Allocates and constructs a new colour list.

@param aColors The array of physical colours to store in the list. 
The colour list takes ownership.
@return The colour list. */
	{ // static
	__ASSERT_ALWAYS(aColors,Panic(EEgulPanicNullPointer));
	CColorList* self=new(ELeave) CColorList(aColors);
	return self;
	}

CColorList::CColorList(CArrayFix<TRgb>* aColors)
	: iEikColors(aColors)
	{}

EXPORT_C CColorList::~CColorList()
/** Destructor. */
	{
	delete iEikColors;
	if (iAppColors)
		{
		const TInt count=iAppColors->Count();
		for (TInt ii=0;ii<count;ii++)
			delete (*iAppColors)[ii].iColorArray;
		delete iAppColors;
		}
	}

EXPORT_C TRgb CColorList::Color(TLogicalColor aColor) const
/** Gets the physical colour (TRgb) equivalent of a logical colour.

@param aColor Logical colour value.
@return The physical colour equivalent of aColor.
@panic EGUL 3 The logical color specified is not found in the colour list. */
	{
	if ((TInt)aColor<0 || (TInt)aColor>=iEikColors->Count())
		{
		Panic(EEgulPanicLogicalColorNotFound);
		}
	return (*iEikColors)[aColor];
	}

/** Gets the number of colors in the list.

@return The number of colors in the list
*/
EXPORT_C TInt CColorList::Count() const
	{
	return iEikColors->Count();
	}

EXPORT_C TRgb CColorList::Color(TUid aApp, TInt aColor) const
/** Gets the physical colour (TRgb) equivalent of a logical colour from 
the specified application's colour array.

@param aApp The UID of the application.
@param aColor A logical colour supported by the application.
@return The physical colour equivalent of the logical colour.
@panic EGUL 6 The specified application does not have an entry in the colour list. */
	{
	const TInt pos=Find(aApp);
	if (pos==KErrNotFound)
		{
		Panic(EEgulPanicAppColorArrayNotFound);
		}
	return (*iAppColors)[pos].iColorArray->Color(aColor);
	}

EXPORT_C CColorArray* CColorList::ColorArray(TUid aApp) const
/** Gets an application's colour array.

@param aApp The UID of the application.
@return The specified application's colour array. The caller does not take ownership.
@panic EGUL 6 The specified application does not have an entry in the colour list. */
	{
	TInt pos=Find(aApp);
	__ASSERT_ALWAYS(pos!=KErrNotFound,Panic(EEgulPanicAppColorArrayNotFound));
	return (*iAppColors)[pos].iColorArray;
	}

EXPORT_C TBool CColorList::ContainsColorArray(TUid aApp) const
/** Tests whether the specified application has an entry in the colour list.

@param aApp The UID of the application.
@return True if a colour array is found for the application, false if not. */
	{
	return (Find(aApp)!=KErrNotFound);
	}

EXPORT_C void CColorList::SetColor(TLogicalColor aLogicalColor, TRgb aColor)
/** Sets the TRgb colour value that a logical colour maps to.

@param aLogicalColor The logical colour that needs to be set.
@param aColor The TRgb colour value. */
	{
	(*iEikColors)[aLogicalColor]=aColor;
	}

EXPORT_C void CColorList::AddColorArrayL(TUid aApp, CColorArray* aArray)
/** Creates a new entry in the colour list with the specified  application UID 
and its colour array.

@param aApp The UID of the application.
@param aArray The application's colour array. The colour list takes ownership. */
	{
	__ASSERT_DEBUG(aArray,User::Invariant());
	if (!iAppColors)
		iAppColors=new(ELeave) CArrayFixFlat<TAppColorList>(KGulColorGranularity);
	iAppColors->AppendL(TAppColorList(aApp,aArray));
	}

EXPORT_C void CColorList::DeleteColorArray(TUid aApp)
/** Deletes the entry in the colour list for the specified application, and 
deletes the application's colour array.

@param aApp The UID of the application whose entry is deleted from the colour list.
@panic EGUL 6 The specified application does not have an entry in the colour list. */
	{
	TInt pos=Find(aApp);
	__ASSERT_ALWAYS(pos!=KErrNotFound,Panic(EEgulPanicAppColorArrayNotFound));
	delete (*iAppColors)[pos].iColorArray;
	iAppColors->Delete(pos);
	}

EXPORT_C void CColorList::InternalizeL(RReadStream& aStream)
/** Internalises the colour list from a read stream.

@param aStream Stream from which the object should be internalised.*/
	{
	TCardinality version;
	aStream>>version; // ignore version number for now
	// read in eik colors
	if (iEikColors)
		iEikColors->Reset();
	else
		iEikColors=new(ELeave) CArrayFixFlat<TRgb>(4);
	TCardinality card;
	aStream>>card;
	const TInt count(card);
	TRgb rgb;
	for (TInt ii=0;ii<count;ii++)
		{
		aStream>>rgb;
		iEikColors->AppendL(rgb);
		}
	// then the other arrays, one at a time
	if (!iAppColors)
		iAppColors=new(ELeave) CArrayFixFlat<TAppColorList>(KGulColorGranularity);
	else
		{
		const TInt colCount=iAppColors->Count();
		for (TInt jj=0;jj<colCount;jj++)
			delete (*iAppColors)[jj].iColorArray;
		iAppColors->Reset();
		}
	aStream>>card;
	const TInt arrayCount(card);
	for (TInt jj=0;jj<arrayCount;jj++)
		{
		TUid uid=TUid::Uid(aStream.ReadInt32L());
		CColorArray* array=CColorArray::NewLC();
		aStream>>*array;
		iAppColors->AppendL(TAppColorList(uid,array));
		CleanupStack::Pop(); //array
		}
	}

EXPORT_C void CColorList::ExternalizeL(RWriteStream& aStream) const
/** Externalises the colour list to a write stream.

@param aStream Stream to which the object should be externalised.*/
	{
	TCardinality version(KGulColListVer);
	aStream<<version;

	const TInt colCount=iEikColors->Count();
	aStream<<TCardinality(colCount);
	for (TInt ii=0;ii<colCount;ii++)
		{
		aStream<<(*iEikColors)[ii];
		}

	const TInt arrayCount=(iAppColors? iAppColors->Count() : 0);
//	aStream<<TCardinality(arrayCount);
	TBool wroteDeviceSpecificStream=EFalse;
	for (TInt jj=0;jj<arrayCount;jj++)
		{
		const TAppColorList& colList=(*iAppColors)[jj];
		if (colList.iApp.iUid==KEikCustomColorsArrayValue)
			{
			aStream<<TCardinality(1);
			aStream.WriteInt32L(colList.iApp.iUid);
			aStream<<*(colList.iColorArray);
			wroteDeviceSpecificStream=ETrue;
			break;
			}
		}
	if (wroteDeviceSpecificStream==EFalse)
		{
		aStream<<TCardinality(0);
		}
	}

EXPORT_C void CColorList::MergeL(const CColorList& aList)
/** Merges the specified CColorList with target object. 

@param aList A reference to the colour list object, set by calling CColorList::AddColorArray() 
*/
	{
	//AddColorArray() should have been called
	if (!aList.iAppColors)
		{
		return;
		}

	const TInt count=aList.iAppColors->Count();
	for (TInt ii=0;ii<count;ii++)
		{
		CArrayFix<TAppColorList>* array=aList.iAppColors;
		TAppColorList& appColorList=(*array)[ii];
		TUid uid=appColorList.iApp;
//		const TInt match=aList.Find(uid);
		const TInt match=Find(uid);
//		if (match!=KErrNotFound)
		if (match==KErrNotFound)
			{
			CColorArray* copy=CColorArray::NewLC(*(appColorList.iColorArray));
			AddColorArrayL(uid,copy);
			CleanupStack::Pop(copy);
			}
		}
	}

TInt CColorList::Find(TUid aApp) const
	{
	if (!iAppColors)
		return KErrNotFound;
	TInt pos;
	TKeyArrayFix key(_FOFF(TAppColorList,iApp.iUid),ECmpTInt);
	TAppColorList appColor(aApp,NULL);
	if (iAppColors->Find(appColor,key,pos)==KErrNone)
		return pos;
	return KErrNotFound;
	}

//
// class CColorArray
//

inline CColorArray::TColor::TColor()
	: iColor(KRgbWhite), iLogicalColor(0)
	{}
inline CColorArray::TColor::TColor(TRgb aColor,TInt aLogicalColor)
	: iColor(aColor), iLogicalColor(aLogicalColor)
	{}

void CColorArray::TColor::InternalizeL(RReadStream& aStream)
	{
	aStream>>iColor;
	iLogicalColor=aStream.ReadInt32L();
	}

void CColorArray::TColor::ExternalizeL(RWriteStream& aStream) const
	{
	aStream<<iColor;
	aStream.WriteInt32L(iLogicalColor);
	}

EXPORT_C CColorArray* CColorArray::NewL()
/** Creates a colour array.

@return Pointer to the colour array.*/
	{ // static
	CColorArray* self=new(ELeave) CColorArray;
	return self;
	}

EXPORT_C CColorArray* CColorArray::NewLC()
/** Creates a colour array and leaves it on the cleanup stack.

@return Pointer to the colour array. */
	{ // static
	CColorArray* self=CColorArray::NewL();
	CleanupStack::PushL(self);
	return self;
	}

EXPORT_C CColorArray::~CColorArray()
/** Destructor. */
	{
	iColors.Reset();
	}

EXPORT_C TRgb CColorArray::Color(TInt aLogicalColor) const
/** Gets the physical colour (TRgb) which corresponds to a logical colour.

@param aLogicalColor The logical colour.
@return The TRgb value.
@panic EGUL 3 The logical colour specified is not found in the colour array. */
	{
	TInt index=Find(aLogicalColor);
	__ASSERT_ALWAYS(index!=KErrNotFound,Panic(EEgulPanicLogicalColorNotFound));
	return iColors[index].iColor;
	}

EXPORT_C void CColorArray::SetColor(TInt aLogicalColor,TRgb aColor)
/** Changes a logical to physical mapping in the colour array. The specified 
logical colour must already exist in the colour array.

@param aLogicalColor The logical colour.
@param aColor The TRgb value.
@panic EGUL 3 The logical colour specified is not found in the colour array. */
	{
	TInt index=Find(aLogicalColor);
	__ASSERT_ALWAYS(index!=KErrNotFound,Panic(EEgulPanicLogicalColorNotFound));
	iColors[index].iColor=aColor;
	}

EXPORT_C TBool CColorArray::Contains(TInt aLogicalColor) const
/** Tests whether the colour array contains the specified logical colour.

@param aLogicalColor The logical colour.
@return True if the logical colour is found in the colour array, false if not. */
	{
	return Find(aLogicalColor)!=KErrNotFound;
	}

EXPORT_C TInt CColorArray::Count() const
/** Gets the number of logical to physical colour mappings in the array.

@return The number of logical to physical colour mappings in the array. */
	{
	return iColors.Count();
	}

EXPORT_C void CColorArray::Reset()
/** Resets the colour array. */
	{
	iColors.Reset();
	}

EXPORT_C void CColorArray::AddL(TInt aLogicalColor,TRgb aColor)
/** Adds a logical to physical colour mapping to the colour array. 
The specified logical colour must not already exist in the colour array.

@param aLogicalColor The logical colour.
@param aColor The TRgb colour.
@panic EGUL 4 The logical colour specified already exists in the array. Debug builds only.*/
	{
	__ASSERT_DEBUG(Find(aLogicalColor)==KErrNotFound,Panic(EEgulPanicLogicalColorAlreadyExists));
	iColors.AppendL(CColorArray::TColor(aColor,aLogicalColor));
	}

EXPORT_C void CColorArray::Remove(TInt aLogicalColor)
/** Removes a logical to physical colour mapping from the array.

@param aLogicalColor The logical colour to remove. 
@panic EGUL 3 The logical colour specified is not found in the array. */
	{
	const TInt index=Find(aLogicalColor);
	__ASSERT_ALWAYS(index!=KErrNotFound,Panic(EEgulPanicLogicalColorNotFound));
	iColors.Delete(index);
	}

void CColorArray::InternalizeL(RReadStream& aStream)
	{
	iColors.Reset();
	TCardinality card;
	aStream>>card;
	const TInt count(card);
	for (TInt ii=0;ii<count;ii++)
		{
		TColor color;
		aStream>>color;
		iColors.AppendL(color);
		}
	}

void CColorArray::ExternalizeL(RWriteStream& aStream) const
	{
	const TInt count=Count();
	aStream<<TCardinality(count);
	for (TInt ii=0;ii<count;ii++)
		{
		aStream<<iColors[ii];
		}
	}

CColorArray::CColorArray()
	: iColors(4)
	{}

TInt CColorArray::Find(TInt aLogicalColor) const
	{
	TInt pos;
	TKeyArrayFix key(sizeof(TRgb),ECmpTInt);
	TRgb junk; // never used
	CColorArray::TColor color(junk,aLogicalColor);
	if (iColors.Find(color,key,pos)==KErrNone)
		return pos;
	return KErrNotFound;
	}

CColorArray* CColorArray::NewLC(const CColorArray& aArray)
	{ // static
	CColorArray* self=CColorArray::NewLC();
	const TInt count=aArray.iColors.Count();
	for (TInt ii=0;ii<count;ii++)
		{
		self->iColors.AppendL(aArray.iColors[ii]);
		}
	return self;
	}
