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

#include <s32strm.h>
#include "GRDPANIC.H"
#include "GRDMAP.H"


RWriteStream& operator<<(RWriteStream& aStream,const TSizeElement &aElement)
	{
	aElement.ExternalizeL(aStream);
	return aStream;
	}

RReadStream& operator>>(RReadStream &aStream,TSizeElement &aElement)
	{
	aElement.InternalizeL(aStream);
	return aStream;
	}

void TSizeElement::ExternalizeL(RWriteStream& aStream) const
	{
	aStream.WriteInt32L(iId);
	aStream.WriteInt32L(iValueInTwips);
	}

void TSizeElement::InternalizeL(RReadStream& aStream)
	{
	iId = aStream.ReadInt32L();
	iValueInTwips = aStream.ReadInt32L();
	}
		
//

CSparseMap* CSparseMap::NewL()
	{
	CSparseMap* self = new(ELeave) CSparseMap();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

CSparseMap* CSparseMap::NewL(const CSparseMap* aSparseMap)
	{
	CSparseMap* self = new(ELeave) CSparseMap();
	CleanupStack::PushL(self);
	self->ConstructL(aSparseMap);
	CleanupStack::Pop();
	return self;
	}

void CSparseMap::ConstructL()
//
	{
	iArray = new(ELeave) CArrayFixFlat<TSizeElement>(1);
	}

void CSparseMap::ConstructL(const CSparseMap* aSparseMap)
	{
	iArray = new(ELeave) CArrayFixFlat<TSizeElement>(1);
	iDefaultValueInTwips=aSparseMap->iDefaultValueInTwips;
	iDefaultValueInPixels=aSparseMap->iDefaultValueInPixels;
	TInt end=aSparseMap->iArray->Count();
	for (TInt ii=0;ii<end;ii++)
		iArray->AppendL((*aSparseMap)[ii]);
	}

CSparseMap::CSparseMap()
	: iDefaultValueInTwips(0),
	iDefaultValueInPixels(0)
	{
	}

CSparseMap::~CSparseMap()
//
	{
	delete iArray;
	}

TInt CSparseMap::Count() const
	{
	return iArray->Count();
	}

void CSparseMap::SetL(TInt aId,TInt aValueInTwips,TInt aValueInPixels)
//
	{
	TKeyArrayFix key(0,ECmpTInt);
	TInt pos;
	TSizeElement element;
	element.iId = aId;
	element.iValueInTwips = aValueInTwips;
	element.iValueInPixels = aValueInPixels;
	if (iDefaultValueInTwips==aValueInTwips && iDefaultValueInPixels==aValueInPixels)
		{// remove it from the array if it is already there
		if (iArray->FindIsq(element,key,pos)==0)
			{// found
			iArray->Delete(pos);
			}
		}
	else
		{
		if (iArray->FindIsq(element,key,pos)==0)
			{// found
			(*iArray)[pos] = element;
			}
		else
			{
			iArray->InsertIsqL(element,key);
			}
		}
	}

TInt CSparseMap::DefaultValueInTwips() const
	{
	return iDefaultValueInTwips;
	}

TInt CSparseMap::DefaultValueInPixels() const
	{
	return iDefaultValueInPixels;
	}

void CSparseMap::SetDefaultValueInTwips(TInt aValueInTwips)
//
	{
	iDefaultValueInTwips = aValueInTwips;
/*	TInt end=iArray->Count();
	for (TInt ii=0;ii<end;ii++)
		{
		if (*iArray)[ii]==iDefaultValue)
			{
			iArray->Delete(ii--);
			end--;
			}
		} //!! Is this a valid optimization? */
	}

void CSparseMap::SetDefaultValueInPixels(TInt aValueInPixels)
	{
	__ASSERT_DEBUG(aValueInPixels,Panic(EGridMapDefaultValueIsZero));
	iDefaultValueInPixels = aValueInPixels;
	}

TInt CSparseMap::ValueInTwips(TInt aId) const
//
	{
	TInt pos;
	if (FindId(aId,pos)==0)
		{// found
		return (*iArray)[pos].iValueInTwips;
		}
	return (iDefaultValueInTwips);
	}

TInt CSparseMap::ValueInPixels(TInt aId) const
//
	{
	TInt pos;
	if (FindId(aId,pos)==0)
		{// found
		return (*iArray)[pos].iValueInPixels;
		}
	return (iDefaultValueInPixels);
	}

void CSparseMap::ResetArray()
	{
	iArray->Reset();
	}

void CSparseMap::OpenCloseGap(TInt aStartId,TInt aShiftOffset,TInt aMaxId)
//
// +ve offsets opens a gap causing shifted ids that are greater than aMaxId to be deleted
// -ve offsets close a gap causing shifted ids that are less than aStartId to be deleted
	{
	TInt pos;
	FindId(aStartId,pos);
	TInt count=iArray->Count();
	for (;pos<count;pos++)
		{
		TInt& currentId=(*iArray)[pos].iId;
		currentId+=aShiftOffset;
		if (currentId<aStartId)
			{
			iArray->Delete(pos--);
			count--;
			}
		else if (currentId>aMaxId)
			{
			iArray->Delete(pos,count-pos);	// All the rest
			break;
			}
		}
	}

void CSparseMap::IdToDisplacement(TInt aId1,TInt aId2,TInt& aReturnDisp) const
//
// Returns the displacement in pixels between two id's. Skips over sections with default
// value to minimize array accesses
//
	{
	TInt direction=1;
	if (aId2<aId1)
		{
		Mem::Swap(&aId1,&aId2,sizeof(TInt));
		direction=-1;
		}
	TInt pos=0;
	FindId(aId1,pos);
	TInt maxPos=iArray->Count()-1;
	TInt currentId;
	if (pos>maxPos || (currentId=(*iArray)[pos].iId)>=aId2)
		{
		aReturnDisp=((aId2-aId1)*iDefaultValueInPixels*direction);
		return;
		}
	aReturnDisp=((currentId-aId1)*iDefaultValueInPixels);
	TInt newId;
	FOREVER
		{
		aReturnDisp+=((*iArray)[pos].iValueInPixels);
		pos++;
		if (pos>maxPos || (newId=(*iArray)[pos].iId)>=aId2)
			break;
		aReturnDisp+=((newId-currentId-1)*iDefaultValueInPixels);
		currentId=newId;
		}
	aReturnDisp+=((aId2-currentId-1)*iDefaultValueInPixels);
	aReturnDisp*=direction;
	}

TBool CSparseMap::DisplacementToId(TInt aId,TInt aDisp,TInt& aReturnId) const
//
// Changes the returnId nearest to the given displacement in pixels from aId. Nearest in this sense
// means rounded down to the lowest id. Returns ETrue if the displacement lands on an exact id.
//
	{
	if (aDisp==0)
		{
		aReturnId=aId;
		return ETrue;
		}
	__ASSERT_DEBUG(iDefaultValueInPixels,Panic(EGridMapDefaultValueIsZero));
	TInt pos=0;
	FindId(aId,pos);
	TInt maxPos=iArray->Count()-1;
	aReturnId=0;
	TInt tempDisp=0;
	if (aDisp>0)
		{
		if (pos<=maxPos)
			{
			aReturnId=(*iArray)[pos].iId;
			tempDisp=(aReturnId-aId)*iDefaultValueInPixels;
			}
		if (pos>maxPos || tempDisp>aDisp)
			{
			aReturnId=aDisp/iDefaultValueInPixels+aId;
			tempDisp=(aReturnId-aId)*iDefaultValueInPixels;
			}
		else
			{
			tempDisp+=(*iArray)[pos].iValueInPixels;
			TInt newDisp=0;
			TInt newId=0;
			while (tempDisp<=aDisp)
				{
				aReturnId++;
				pos++;
				if (pos<=maxPos)
					{
					newId=(*iArray)[pos].iId;
					newDisp=tempDisp+(newId-aReturnId)*iDefaultValueInPixels;
					}
				if (pos>maxPos || newDisp>aDisp)
					{
					TInt add = (aDisp-tempDisp)/iDefaultValueInPixels;
					tempDisp+=add*iDefaultValueInPixels;
					aReturnId+=add;
					break;
					}
				aReturnId=newId;
				tempDisp=newDisp+(*iArray)[pos].iValueInPixels;
				}
			}
		}
	else
		{
		pos--;
		if (pos>=0)
			{
			aReturnId=(*iArray)[pos].iId;
			tempDisp=(aReturnId-aId+1)*iDefaultValueInPixels;
			}
		if (pos<0 || tempDisp<aDisp)
			{
			aReturnId=aDisp/iDefaultValueInPixels+aId-1;
			tempDisp=(aReturnId-aId+1)*iDefaultValueInPixels;
			}
		else
			{
			tempDisp-=(*iArray)[pos].iValueInPixels;
			TInt newDisp=0;
			TInt newId=0;
			while (tempDisp>=aDisp)
				{
				pos--;
				if (pos>=0)
					{
					newId=(*iArray)[pos].iId;
					newDisp=tempDisp+(newId-aReturnId+1)*iDefaultValueInPixels;
					}
				if (pos<0 || newDisp<aDisp)
					{
					TInt add = (aDisp-tempDisp)/iDefaultValueInPixels-1;
					tempDisp+=(add+1)*iDefaultValueInPixels;
					aReturnId+=add;
					break;
					}
				aReturnId=newId;
				tempDisp=newDisp;
				tempDisp-=(*iArray)[pos].iValueInPixels;
				}
			}
		}
	return (aDisp==tempDisp);
	}

TInt CSparseMap::FindId(TInt aId,TInt& aFindPos) const
	{
	TKeyArrayFix key(0,ECmpTInt);
	TSizeElement element;
	element.iId = aId;
	return iArray->FindIsq(element,key,aFindPos);
	} 

const TSizeElement& CSparseMap::operator[](TInt aIndex) const
	{
	return (*iArray)[aIndex];
	}

TSizeElement& CSparseMap::operator[](TInt aIndex)
	{
	return (*iArray)[aIndex];
	}

void CSparseMap::ExternalizeL(RWriteStream& aStream) const
	{
	aStream.WriteInt32L(iDefaultValueInTwips);
	aStream << *iArray;
	}

void CSparseMap::InternalizeL(RReadStream& aStream)
	{
	iDefaultValueInTwips = aStream.ReadInt32L();
	aStream >> *iArray;
	}

