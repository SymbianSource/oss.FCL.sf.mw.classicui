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


#include "eikenvextra.h"
#include <gdi.h>		// class MPictureFactory
#include <apgdoor.h>	// class TApaPictureFactory
#include <eikenv.h>		// class CEikonEnv
#include <eikproc.h>	// class CEikProces

//
// class TLocalizedFilenameCacheEntry
//

NONSHARABLE_CLASS(TLocalizedFilenameCacheEntry)
	{
public:
	TLocalizedFilenameCacheEntry(TDesC* aGenericFilename, TDesC* aLocalizedFilename);
	static TLocalizedFilenameCacheEntry MakeEntryL(const TDesC& aGenericFilename, const TDesC& aLocalizedFilename);
	static void CleanupStackableFree(TAny* aPointer);
	void Free();
	inline const TDesC& LocalizedFilename() const {return *iLocalizedFilename;}
	static TInt Compare(const TLocalizedFilenameCacheEntry& aLeft, const TLocalizedFilenameCacheEntry& aRight);
private:
	TDesC* iGenericFilename;
	TDesC* iLocalizedFilename;
	};

NONSHARABLE_CLASS(CLocalizedFilenameCache)
	{
public:
	CLocalizedFilenameCache(TUint cacheSize=8) : iCacheSize(cacheSize), iFilenameCache(cacheSize) {};
	~CLocalizedFilenameCache();
	TBool FindLocalizedVersion(TDesC& aFilename, TDes& aLocalizedFileName);
	void InsertIfRoomInCacheL(const TDesC& aGeneralFilename,const TDesC& aLocalizedFilename);
private:
	const TInt iCacheSize;
	RArray<TLocalizedFilenameCacheEntry> iFilenameCache;
	};

//
// class CEikPictureFactoryResolver
//

// This class is a clutch used to locate a MEikPictureFactory implementation 
// supporting the picture type TPictureHeader::iPictureType. This allows clients
// using the original CEikonEnv::PictureFactory() API to locate picture factories 
// added using the newer CEikonEnv::AddPictureFactoryL(), usually accessed
// via CEikonEnv::ExtendedPictureFactory().
//
// Note that this class does not derive from MEikPictureFactory
NONSHARABLE_CLASS(CEikPictureFactoryResolver) : public CBase, public MPictureFactory	
	{
public:
	CEikPictureFactoryResolver(const CEikonEnv& aEnv);
public: // from MPictureFactory
	void NewPictureL(TPictureHeader& aHeader, const CStreamStore& aDeferredPictureStore) const;
private:
	const CEikonEnv& iEnv;
	TApaPictureFactory iApaFactory;
	};


//
// class CEikEnvExtra
//

CEikEnvExtra::CEikEnvExtra() : iAppLanguage(ELangNone)
	{}

CEikEnvExtra::~CEikEnvExtra()
	{
	delete iLocalizedFilenameCache;
	delete iPictureFactoryResolver;
	delete iPictureFactoryArray;
	}

CEikEnvExtra* CEikEnvExtra::NewL(const CEikonEnv& aEikEnv)
	{
	CEikEnvExtra* self = new (ELeave) CEikEnvExtra;
	CleanupStack::PushL(self);
	
	self->iLocalizedFilenameCache = new (ELeave) CLocalizedFilenameCache;
	self->iPictureFactoryResolver = new (ELeave) CEikPictureFactoryResolver(aEikEnv);
	self->iPictureFactoryArray = new (ELeave) CArrayPtrFlat<MEikPictureFactory>(1);
	
	CleanupStack::Pop(self);
	return self;
	}

TBool CEikEnvExtra::FindLocalizedBitmapFilenameInCache(TDesC& aFilename, TDes& aLocalizedFileName)
	{
	return iLocalizedFilenameCache->FindLocalizedVersion(aFilename, aLocalizedFileName);
	}
	
void CEikEnvExtra::CacheLocalizedBitmapFilenameL(const TDesC& aGeneralFilename, const TDesC& aLocalizedFilename)
	{
	iLocalizedFilenameCache->InsertIfRoomInCacheL(aGeneralFilename, aLocalizedFilename);
	}
 
const MPictureFactory& CEikEnvExtra::PictureFactory() const
	{
	return *iPictureFactoryResolver;
	}

const MEikPictureFactory& CEikEnvExtra::PictureFactory(TInt aIndex) const
	{
	return *iPictureFactoryArray->At(aIndex);
	}

const TArray<MEikPictureFactory*> CEikEnvExtra::PictureFactories() const
	{
	return iPictureFactoryArray->Array();
	}
	
void CEikEnvExtra::AppendPictureFactoryL(MEikPictureFactory* aPictureFactory)
	{
	iPictureFactoryArray->AppendL(aPictureFactory);
	}	
	
void CEikEnvExtra::DeletePictureFactory(TInt aIndex)
	{
	iPictureFactoryArray->Delete(aIndex);
	}
	
	

//
// class TLocalizedFilenameCacheEntry
//

TLocalizedFilenameCacheEntry::TLocalizedFilenameCacheEntry(TDesC* aGenericFilename, TDesC* aLocalizedFilename)
 :iGenericFilename(aGenericFilename),
  iLocalizedFilename(aLocalizedFilename)
	{
	}

TLocalizedFilenameCacheEntry TLocalizedFilenameCacheEntry::MakeEntryL(const TDesC& aGenericFilename, const TDesC& aLocalizedFilename)
	{
	TLocalizedFilenameCacheEntry entry(NULL, NULL);
	CleanupStack::PushL(TCleanupItem(CleanupStackableFree, &entry));
	entry.iGenericFilename=aGenericFilename.AllocL();
	entry.iLocalizedFilename=aLocalizedFilename.AllocL();
	CleanupStack::Pop();
	return entry;
	}

void TLocalizedFilenameCacheEntry::CleanupStackableFree(TAny* aPointer)
	{
	STATIC_CAST(TLocalizedFilenameCacheEntry*, aPointer)->Free();
	}

void TLocalizedFilenameCacheEntry::Free()
	{
	delete iGenericFilename;
	delete iLocalizedFilename;
	}

TInt TLocalizedFilenameCacheEntry::Compare(const TLocalizedFilenameCacheEntry& aLeft, const TLocalizedFilenameCacheEntry& aRight)
	{
	return aLeft.iGenericFilename->Compare(*(aRight.iGenericFilename));
	}

//
// class CLocalizedFilenameCache
//

CLocalizedFilenameCache::~CLocalizedFilenameCache()
	{
	for(TInt i=iFilenameCache.Count()-1; i>=0; --i)
		{
		iFilenameCache[i].Free();
		}
	iFilenameCache.Close();
	}

TBool CLocalizedFilenameCache::FindLocalizedVersion(TDesC& aFilename, TDes& aLocalizedFileName)
	{
	TLocalizedFilenameCacheEntry searchEntry(&aFilename, NULL); // must not call Free on the searchEntry object as it doesn't own what it thinks it owns
	const TInt pos=iFilenameCache.FindInOrder(searchEntry,TLinearOrder<TLocalizedFilenameCacheEntry>(TLocalizedFilenameCacheEntry::Compare));
	if (pos!=KErrNotFound)
		{
		aLocalizedFileName=iFilenameCache[pos].LocalizedFilename();
		return ETrue;
		}
	return EFalse;
	}


void CLocalizedFilenameCache::InsertIfRoomInCacheL(const TDesC& aGeneralFilename,const TDesC& aLocalizedFilename)
	{
	if (iFilenameCache.Count()<iCacheSize)
		{
		TLocalizedFilenameCacheEntry entry(TLocalizedFilenameCacheEntry::MakeEntryL(aGeneralFilename,aLocalizedFilename));
		CleanupStack::PushL(TCleanupItem(TLocalizedFilenameCacheEntry::CleanupStackableFree, &entry));
		User::LeaveIfError(iFilenameCache.InsertInOrder(entry, TLinearOrder<TLocalizedFilenameCacheEntry>(TLocalizedFilenameCacheEntry::Compare)));
		CleanupStack::Pop();
		}
	}


//
// class CEikPictureFactoryResolver
//

CEikPictureFactoryResolver::CEikPictureFactoryResolver(const CEikonEnv& aEnv)
	: iEnv(aEnv), iApaFactory(iEnv.Process())
	{}

void CEikPictureFactoryResolver::NewPictureL(TPictureHeader& aHeader, const CStreamStore& aDeferredPictureStore) const
	{
	const TUid picType = aHeader.iPictureType;
	MEikPictureFactory* ext = iEnv.ExtendedPictureFactory(picType);
	if (ext)
		ext->PictureFactory(picType)->NewPictureL(aHeader, aDeferredPictureStore);
	else
		iApaFactory.NewPictureL(aHeader, aDeferredPictureStore);
	}

