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

#include <apgcli.h>
#include <apgaplst.h>
#include <eikembal.h>
#include <eikdoc.h>
#include <eikenv.h>
#include <eikfutil.h>
#include <barsread.h>
#include <uiklafgt/eikcore.rsg>

const TInt KMaxRetries=5;

//
// class CEikEmbeddableAppList
//

EXPORT_C CEikEmbeddableAppList::CEikEmbeddableAppList()
	: CArrayFixFlat<TApaAppInfo>(4)
/** Default constructor. */
	{
	}

EXPORT_C CEikEmbeddableAppList::~CEikEmbeddableAppList()
/** Destructor. */
	{
	}

EXPORT_C void CEikEmbeddableAppList::ConstructL()
/** Completes construction; populates and sorts the list.

@leave KErrGeneral The apparc server's initial population 
of the list has not completed. */
	{
	TApaEmbeddabilityFilter filter;
	filter.AddEmbeddability(TApaAppCapability::EEmbeddable);
	filter.AddEmbeddability(TApaAppCapability::EEmbeddableOnly);
	ConstructL(filter);
	}

EXPORT_C void CEikEmbeddableAppList::ConstructL(const TApaEmbeddabilityFilter& aFilter)
/** 
Completes construction; populates and sorts the list.

@param aFilter Defines the filter to be applied to the list.
@leave KErrGeneral The apparc server's initial population of the list has not completed.
*/
	{
	TInt ret=GetAppListL(aFilter);
	TInt count=0;
	while (ret==RApaLsSession::EAppListInvalid && count++<KMaxRetries)
		{
		ret=GetAppListL(aFilter);
		}
	if (ret==RApaLsSession::EAppListInvalid)
		{
		User::Leave(KErrGeneral);
		}
	User::LeaveIfError(ret);
	SortAppListL();
	}


/**
@internalComponent
*/
TInt CEikEmbeddableAppList::GetAppListL(const TApaEmbeddabilityFilter& aFilter)
	{
	// open a list server session
	RApaLsSession ls;
	User::LeaveIfError(ls.Connect());
	//
	// get the app list piece by piece
	TInt ret=0;
	TRAPD(err,ret=DoGetAppListL(ls, aFilter));
	ls.Close(); 
	return (err!=KErrNone)? err : ret;
	}

/**
@internalComponent
*/
TInt CEikEmbeddableAppList::DoGetAppListL(RApaLsSession& aLs, const TApaEmbeddabilityFilter& aFilter)
	{
	// get the app list piece by piece
	User::LeaveIfError(aLs.GetFilteredApps(aFilter));
	TApaAppInfo info;
	TInt ret=aLs.GetNextApp(info);
	TApaAppCapabilityBuf buf;
	while (ret==KErrNone)
		{
		aLs.GetAppCapability(buf,info.iUid);
		TApaAppCapability capability=buf();
		if(!capability.iAppIsHidden)
			{
			AppendL(info);
			}
		ret = aLs.GetNextApp(info);
		}
	if (ret!=RApaLsSession::ENoMoreAppsInList && ret!=RApaLsSession::EAppListInvalid)
		{
		User::Leave(ret);
		}
	return ret;	
	}

const TInt KEikAppSortUidBase=-1024;
const TInt KEikAppSortUidLimit=0;

/**
@internalComponent
*/
void CEikEmbeddableAppList::SortAppListL()
	{
	TResourceReader reader;
	CEikonEnv::Static()->CreateResourceReaderLC(reader,R_EIK_ARRAY_FILE_SORT_TABLE);
	CBaflFileSortTable* sortTable=new(ELeave) CBaflFileSortTable;
	CleanupStack::PushL(sortTable);
	sortTable->ConstructFromResourceL(reader);

	const TInt count=Count();
	for (TInt i=0;i<count;i++)
		{
		TApaAppInfo* pEntry=&(*this)[i];
		TInt index;
		TKeyArrayFix key(0,ECmpTInt);
		if (sortTable->Find(pEntry->iUid,key,index)==KErrNone)
			{
			pEntry->iUid=TUid::Uid(index+KEikAppSortUidBase);
			}
		}

	TKeyArrayFix key(_FOFF(TApaAppInfo,iUid),ECmpTInt);
	Sort(key); // Ignore return codes from Sort()

	for (TInt j=0;j<count;j++)
		{
		TApaAppInfo* pEntry=&(*this)[j];
		TInt index=pEntry->iUid.iUid;
		if (index>=KEikAppSortUidBase && index<KEikAppSortUidLimit)
			{
			pEntry->iUid=(*sortTable)[index-KEikAppSortUidBase];
			}
		}

	CleanupStack::PopAndDestroy(2); // reader, sortTable
	}

/**
@see MDesCArray::MdcaCount()
*/
EXPORT_C TInt CEikEmbeddableAppList::MdcaCount() const
	{
	return Count();
	}

/**
@see MDesCArray::MdcaPoint(TInt aIndex)
@return The caption for the embeddable application at aIndex
*/
EXPORT_C TPtrC CEikEmbeddableAppList::MdcaPoint(TInt aIndex) const
	{
	return (*this)[aIndex].iCaption;
	}

EXPORT_C CEikDocument* CEikEmbeddableAppList::CreateEmbeddedDocumentL(TInt aIndex,CApaProcess* aProcess)
/** Creates and returns a document of the correct type for the 
indexed embeddable application. Ultimately calls the application's 
CreateDocumentL() function.

@param aIndex Index of the application in the list of embeddable 
applications, for which a document should be created.
@param aProcess A pointer to the process object that manages the list 
of documents. An application can use iEikonEnv->Process() to provide this.
@return The new embeddable document.
@see CApaProcess::AddNewDocumentL() */
	{
	TApaAppInfo info = (*this)[aIndex];
	CApaDocument* newDoc=aProcess->AddNewDocumentL(info.iUid);
	return ((CEikDocument*)newDoc);
	}

EXPORT_C void CEikEmbeddableAppList::CEikEmbeddableAppList_Reserved1()
	{
	}
	
EXPORT_C void CEikEmbeddableAppList::CEikEmbeddableAppList_Reserved2()
	{
	}
