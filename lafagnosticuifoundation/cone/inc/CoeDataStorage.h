// Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __COEDATASTORAGE_H__
#define __COEDATASTORAGE_H__

#include <coemain.h>

class CBufBase;
class CBufFlat;
class CRepository;
class CColorList;

/** @internalTechnology */
class CCoeDataStorage : public CBase
	{
public:
	IMPORT_C static CCoeDataStorage& GetL(CCoeEnv& aCoeEnv);
	IMPORT_C static CCoeDataStorage* NewL();
	IMPORT_C virtual ~CCoeDataStorage();
	IMPORT_C void GetInstalledFepIdL(TDes& aFepId);
	IMPORT_C void SetInstalledFepIdL(const TDesC& aFepId);
	IMPORT_C void GetFepAttributeL(TUid aAttributeUid, TDes8& aAttributeData);
	IMPORT_C void SetFepAttributeL(TUid aAttributeUid, const TDesC8& aAttributeData);
	IMPORT_C CColorList* GetSystemColorListL();
	IMPORT_C CBufBase* GetSystemColorListBufferL();
	IMPORT_C void SetSystemColorListL(const CColorList& aColors);
	IMPORT_C void SetSystemColorListFromBufferL(const TDesC8& aBuffer);
	IMPORT_C CColorList* PopulateColorArrayL();
	
public: // but not exported
	CRepository& FepFrameworkRepositoryL();
private:
	NONSHARABLE_CLASS(COwner) : public CCoeStatic
		{
	public:
		enum {ECoeStaticUid=0x10202b3d};
	public:
		COwner(CCoeDataStorage* aDataStorage);
		virtual ~COwner();
		inline CCoeDataStorage* DataStorage() {return iDataStorage;}
	private:
		CCoeDataStorage* const iDataStorage;
		};
private:
	inline CCoeDataStorage() {}
	CRepository& FepSpecificSettingsRepositoryL();
	CRepository& SystemColorListRepositoryL();
	CBufFlat* GetSystemColorListBufferLC(TBool& aExists);
private:
	CRepository* iFepFrameworkRepository;
	CRepository* iFepSpecificSettingsRepository;
	CRepository* iSystemColorListRepository;
	};

#endif	// __COEDATASTORAGE_H__
