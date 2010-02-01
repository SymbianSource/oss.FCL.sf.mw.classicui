/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#include <eiklbm.h>
#include <eiktxlbm.h>
#include <badesca.h>

// class CTextListBoxModel

EXPORT_C CTextListBoxModel::CTextListBoxModel()
    {
    }

EXPORT_C CTextListBoxModel::~CTextListBoxModel()
	{
	if (iItemArrayOwnershipType == ELbmOwnsItemArray)
		delete(iItemTextArray);
	}

EXPORT_C TInt CTextListBoxModel::NumberOfItems() const
	{
	return iItemTextArray->MdcaCount();
	}

EXPORT_C const MDesCArray* CTextListBoxModel::MatchableTextArray() const
	{
	return iItemTextArray;
	}

EXPORT_C TPtrC CTextListBoxModel::ItemText(TInt aItemIndex) const
	{
	return iItemTextArray->MdcaPoint(aItemIndex);
	}

EXPORT_C void CTextListBoxModel::ConstructL(MDesCArray* aItemTextArray, TListBoxModelItemArrayOwnership aOwnershipType)
	{
	if (! aItemTextArray)
		{
		iItemTextArray = new(ELeave) CDesCArrayFlat(5);
		iItemArrayOwnershipType = ELbmOwnsItemArray;
		}
	else
		{ 	
		iItemTextArray = aItemTextArray;
		iItemArrayOwnershipType = aOwnershipType;
		}
	}

EXPORT_C void CTextListBoxModel::SetItemTextArray(MDesCArray* aItemTextArray)
	{
	// __ASSERT_ALWAYS((aItemTextArray), User::Panic(_L("aItemTextArray is NULL"), 0));
	if (iItemArrayOwnershipType == ELbmOwnsItemArray)
		delete iItemTextArray;
	iItemTextArray = aItemTextArray;
	}

EXPORT_C MDesCArray* CTextListBoxModel::ItemTextArray() const
	{
	return iItemTextArray;
	}

EXPORT_C void CTextListBoxModel::SetOwnershipType(TListBoxModelItemArrayOwnership aOwnershipType)
	{
	iItemArrayOwnershipType = aOwnershipType;
	}

EXPORT_C TListBoxModelItemArrayOwnership CTextListBoxModel::ItemArrayOwnershipType() const
	{
	return iItemArrayOwnershipType;
	}

EXPORT_C TAny* CTextListBoxModel::MListBoxModel_Reserved()
	{
	return NULL;
	}
