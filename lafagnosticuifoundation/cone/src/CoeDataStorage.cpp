// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include <e32base.h>
#include <s32mem.h>
#include <centralrepository.h>
#include <coemain.h>
#include "CoeDataStorage.h"
#include <coedef.h>
#include <gulcolor.h>
#include <barsread.h>
#include "coepanic.h"
#include <bautils.h>
#include "coedefkeys.h"

const TUint KUidSystemColorRepository=0x10272619;
const TUint KSystemColorRepositoryKey=0;
const TInt KColorListBufferGranularity=1024;
const TUint KUidFepSpecificSettingsRepository=0x10009793; // also defined in fepbase\source\Fepbase.cpp

// CCoeDataStorage

EXPORT_C CCoeDataStorage& CCoeDataStorage::GetL(CCoeEnv& aCoeEnv)
	{ // static
	COwner* owner=STATIC_CAST(COwner*, aCoeEnv.FindStatic(TUid::Uid(COwner::ECoeStaticUid)));
	if (owner==NULL)
		{
		CCoeDataStorage* const dataStorage=NewL();
		CleanupStack::PushL(dataStorage);
		owner=new(ELeave) COwner(dataStorage);
		CleanupStack::Pop(dataStorage);
		}
	return *owner->DataStorage();
	}

EXPORT_C CCoeDataStorage* CCoeDataStorage::NewL()
	{ // static
	return new(ELeave) CCoeDataStorage;
	}

EXPORT_C CCoeDataStorage::~CCoeDataStorage()
	{
	delete iFepFrameworkRepository;
	delete iFepSpecificSettingsRepository;
	delete iSystemColorListRepository;
	}

EXPORT_C void CCoeDataStorage::GetInstalledFepIdL(TDes& aFepId)
	{
	CRepository& repository=FepFrameworkRepositoryL();
	if (repository.Get(ERepositoryKey_DynamicFepId, aFepId)!=KErrNone)
		{
		User::LeaveIfError(repository.Get(ERepositoryKey_DefaultFepId, aFepId));
		}
	}

EXPORT_C void CCoeDataStorage::SetInstalledFepIdL(const TDesC& aFepId)
	{
	User::LeaveIfError(FepFrameworkRepositoryL().Set(ERepositoryKey_DynamicFepId, aFepId));
	}

EXPORT_C void CCoeDataStorage::GetFepAttributeL(TUid aAttributeUid, TDes8& aAttributeData)
	{
	CRepository& repository=FepSpecificSettingsRepositoryL();
	User::LeaveIfError(repository.Get(aAttributeUid.iUid, aAttributeData));
	}

EXPORT_C void CCoeDataStorage::SetFepAttributeL(TUid aAttributeUid, const TDesC8& aAttributeData)
	{
	User::LeaveIfError(FepSpecificSettingsRepositoryL().Set(aAttributeUid.iUid, aAttributeData));
	}

/** This method will return a new CColorList object poplulated with the color information
read from a configuration ini-file. If the ini-file cannot be found, this method will return NULL, 
in which case the color list should be read from resource file. This is the action taken by PopulateColorArrayL(). */
EXPORT_C CColorList* CCoeDataStorage::GetSystemColorListL()
	{
	TBool doesExist = EFalse;
	CBufFlat* const buffer = GetSystemColorListBufferLC(doesExist);
	CColorList* colorList = NULL;
	if (doesExist)
		{
		colorList=CColorList::NewLC();
		RBufReadStream readStream(*buffer);
		TRAPD(err,colorList->InternalizeL(readStream));
		CleanupStack::Pop(colorList);
		if (err != KErrNone)
			{
			delete colorList;
			colorList=NULL;
			}
		}
	CleanupStack::PopAndDestroy(buffer);
	return colorList;
	}

EXPORT_C CBufBase* CCoeDataStorage::GetSystemColorListBufferL()
	{
	TBool exists=EFalse;
	CBufFlat* const buffer=GetSystemColorListBufferLC(exists);
	if (!exists)
		{
		buffer->Reset();
		}
	CleanupStack::Pop(buffer);
	return buffer;
	}

EXPORT_C void CCoeDataStorage::SetSystemColorListL(const CColorList& aColorList)
	{
	CBufFlat* const buffer=CBufFlat::NewL(KColorListBufferGranularity);
	CleanupStack::PushL(buffer);
	RBufWriteStream writeStream(*buffer);
	aColorList.ExternalizeL(writeStream);
	writeStream.CommitL();
	const TPtrC8 data(buffer->Ptr(0));
	SetSystemColorListFromBufferL(data);
	CleanupStack::PopAndDestroy(buffer);
	}

EXPORT_C void CCoeDataStorage::SetSystemColorListFromBufferL(const TDesC8& aBuffer)
	{
	User::LeaveIfError(SystemColorListRepositoryL().Set(KSystemColorRepositoryKey, aBuffer));
	}

/**
Returns a new color list object. The list will be populated from a configuration ini-file.
If the ini-file cannot be found, the list will be populated with the default colors from eikpriv.rsc.
*/
EXPORT_C CColorList* CCoeDataStorage::PopulateColorArrayL()
	{
	CColorList* colorList =GetSystemColorListL();
	if (colorList==NULL)
		{
		TInt numGrays=0;
		TInt numColors=0;
		RFs fs;
		CleanupClosePushL(fs);
		User::LeaveIfError(fs.Connect());
		RWsSession ws;
		CleanupClosePushL(ws);
		User::LeaveIfError(ws.Connect(fs));
		TDisplayMode defaultMode=ws.GetDefModeMaxNumColors(numColors,numGrays);
		const TInt resourceId=(defaultMode>=EColor16? KCoeColorColor16:KCoeColorGray4);
		_LIT(KResourceFileName,"z:\\Resource\\Uiklaf\\eikpriv.rsc");
		TFileName resourceFileName(KResourceFileName);
		BaflUtils::NearestLanguageFile(fs,resourceFileName);
		if (!(BaflUtils::FileExists(fs, resourceFileName)))
			{
			_LIT(KAppResourceFileName,"z:\\Resource\\Apps\\eikpriv.rsc");
			resourceFileName = KAppResourceFileName;
			BaflUtils::NearestLanguageFile(fs,resourceFileName);
			}
		RResourceFile resourceFile;
		resourceFile.OpenL(fs, resourceFileName);
		CleanupClosePushL(resourceFile);
		resourceFile.ConfirmSignatureL(ECoeResourceSignatureValue);
		resourceFile.Offset();
		
		HBufC8* resource= resourceFile.AllocReadLC(resourceId);
		TResourceReader reader;
		reader.SetBuffer(resource);
		const TInt listId=reader.ReadInt32();
		const TInt extrasId=reader.ReadInt32();
		HBufC8* resourceList =resourceFile.AllocReadLC(listId);
		reader.SetBuffer(resourceList);			
		CColorArray* colorArray=CColorArray::NewLC();
		ResourceUtils::PopulateColorArrayL(*colorArray,reader);
		__ASSERT_ALWAYS(colorArray->Count()==EColorLabelHighlightFullEmphasis+1,Panic(ECoePanicInvalidColorRange));
		CArrayFix<TRgb>* colors=new(ELeave) CArrayFixFlat<TRgb>(8);
		CleanupStack::PushL(colors);
		for (TInt ii=EColorWindowBackground;ii<=EColorLabelHighlightFullEmphasis;ii++)
			{
			__ASSERT_ALWAYS(colorArray->Contains(ii),Panic(ECoePanicLogicalColorNotFound));
			colors->InsertL(STATIC_CAST(TLogicalColor,ii),colorArray->Color(ii));
			}
		colorList=CColorList::NewL(colors);
		CleanupStack::Pop(colors); // colors
		CleanupStack::PushL(colorList);
		CColorArray* extrasArray=CColorArray::NewLC();
		HBufC8* resourceExtras=resourceFile.AllocReadLC(extrasId);
		reader.SetBuffer(resourceExtras);		
		ResourceUtils::PopulateColorArrayL(*extrasArray,reader);
		colorList->AddColorArrayL(TUid::Uid(KCoeCustomColorsArrayValue),extrasArray);
		CleanupStack::PopAndDestroy(resourceExtras);
		CleanupStack::Pop(extrasArray); // extrasArray
		TRAP_IGNORE(SetSystemColorListL(*colorList) );
		CleanupStack::Pop(colorList);
		CleanupStack::PopAndDestroy(colorArray); // colorArray
		CleanupStack::PopAndDestroy(resourceList);
		CleanupStack::PopAndDestroy(resource);
		CleanupStack::PopAndDestroy(3); // resourceFile,ws, fs
		}
	return colorList;
	}


CRepository& CCoeDataStorage::FepFrameworkRepositoryL()
	{
	if (iFepFrameworkRepository==NULL)
		{
		iFepFrameworkRepository=CRepository::NewL(TUid::Uid(KUidFepFrameworkRepository));
		}
	return *iFepFrameworkRepository;
	}

CRepository& CCoeDataStorage::FepSpecificSettingsRepositoryL()
	{
	if (iFepSpecificSettingsRepository==NULL)
		{
		iFepSpecificSettingsRepository=CRepository::NewL(TUid::Uid(KUidFepSpecificSettingsRepository));
		}
	return *iFepSpecificSettingsRepository;
	}

CRepository& CCoeDataStorage::SystemColorListRepositoryL()
	{
	if (iSystemColorListRepository==NULL)
		{
		iSystemColorListRepository=CRepository::NewL(TUid::Uid(KUidSystemColorRepository));
		}
	return *iSystemColorListRepository;
	}

CBufFlat* CCoeDataStorage::GetSystemColorListBufferLC(TBool& aExists)
	{
	aExists=ETrue;
	CRepository& repository=SystemColorListRepositoryL();
	CBufFlat* const buffer=CBufFlat::NewL(2048);
	CleanupStack::PushL(buffer);
	FOREVER
		{
		TInt sizeOfBufferToAllocate=0;
		TPtr8 bufferAsDescriptor(buffer->Ptr(0));
		const TInt error=repository.Get(KSystemColorRepositoryKey, bufferAsDescriptor, sizeOfBufferToAllocate);
		if (error==KErrOverflow)
			{
			buffer->ResizeL(sizeOfBufferToAllocate);
			}
		else
			{
			if (error==KErrNotFound)
				{
				aExists=EFalse;
				}
			else
				{
				User::LeaveIfError(error);
				}
			break;
			}
		}
	return buffer;
	}

// CCoeDataStorage::COwner

CCoeDataStorage::COwner::COwner(CCoeDataStorage* aDataStorage)
	:CCoeStatic(TUid::Uid(ECoeStaticUid), KMinTInt), // the second parameter (aDestructionPriority) must be less than zero so that this CCoeStatic object still exists when the CCoeEnv's iExtra->iFepTracker is destroyed, as CCoeFepTracker's destructor uses this CCoeStatic object (via CCoeFepTracker's iRepository reference)
	 iDataStorage(aDataStorage)
	{
	}

CCoeDataStorage::COwner::~COwner()
	{
	delete iDataStorage;
	}

