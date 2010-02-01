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

#if !defined(__GRDMAP_H__)
#define __GRDMAP_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

class RWriteStream;
class RReadStream;

class TSizeElement
	{
public:
    void ExternalizeL(RWriteStream &aStream) const;
	void InternalizeL(RReadStream &aStream);
public:
	TInt iId;
	TInt iValueInTwips;
	TInt iValueInPixels;
	};

class CSparseMap : public CBase
	{
public:
	static CSparseMap* NewL();
	static CSparseMap* NewL(const CSparseMap* aSparseMap);
	~CSparseMap();

	TInt Count() const;
	void SetL(TInt aId,TInt aValueInTwips,TInt aValueInPixels);
	TInt DefaultValueInTwips() const;
	TInt DefaultValueInPixels() const;
	void SetDefaultValueInTwips(TInt aValueInTwips);
	void SetDefaultValueInPixels(TInt aValueInPixels);
	void ResetArray();
	TInt ValueInTwips(TInt aId) const;
	TInt ValueInPixels(TInt aId) const;
	void OpenCloseGap(TInt aStartId,TInt aShiftOffset,TInt aMaxId);
	void IdToDisplacement(TInt aId1,TInt aId2,TInt& aReturnDisp) const;
	TBool DisplacementToId(TInt aId,TInt aDisp,TInt& aReturnId) const;
	const TSizeElement& operator[](TInt aIndex) const;
	TSizeElement& operator[](TInt aIndex);

	void ExternalizeL(RWriteStream &aStream) const;
	void InternalizeL(RReadStream &aStream);
private:
	CSparseMap();
	void ConstructL();
	void ConstructL(const CSparseMap* aSparseMap);
	TInt FindId(TInt aId,TInt& aFindPos) const;
private:
	TInt iDefaultValueInTwips;
	TInt iDefaultValueInPixels;
	CArrayFixFlat<TSizeElement> *iArray;
	};


#endif
