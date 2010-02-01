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

/**
 @file
 @internalComponent - Internal Symbian test code 
*/

#if !defined(__CONTENTMGR_H__)
#define __CONTENTMGR_H__

#include <e32def.h>
#include <e32std.h>
#include <gdi.h>
#include <eikenv.h>

class RFs;
class CTestContentTls;
class TDataType;

class CEikTestContentManager : public CBase, public MEikPictureFactory, public MPictureFactory
	{
public:
	IMPORT_C static CEikTestContentManager* NewL(RFs& aFs);
	IMPORT_C ~CEikTestContentManager();
	IMPORT_C void GetPictureTypeFromDataL(TUid& aPictureType,CBase*& aData,const TDesC& aFileName,const TDesC8& aSrcData) const;
public: // from MEikPictureFactory
	TBool SupportsPictureType(TUid aPictureType) const;
	const MPictureFactory* PictureFactory(TUid aPictureType) const;
	TPictureHeader InsertL(TUid aPictureType,CBase* aData);
	void EditL(const TPictureHeader& aPictureHeader,TBool aReadOnly);
public: // from MPictureFactory
	void NewPictureL(TPictureHeader& aHeader,const CStreamStore& aDeferredPictureStore) const;
private:
	CEikTestContentManager(RFs& aFs);
private:
	RFs& iFs;
	};

#endif // __CONTENTMGR_H__
