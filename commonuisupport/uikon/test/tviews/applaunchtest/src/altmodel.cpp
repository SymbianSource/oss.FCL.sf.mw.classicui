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
// Created for Quartz 6.0
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code 
*/


#include <apgaplst.h>
#include <eikenv.h>

#include "altmodel.h"
#include <apfrec.h>
#include <barsread.h>
#include <apsscan.h>
#include <apgicnfl.h>

const TInt KUnlistedApplication = -1;
const TInt KUnInitialized = -1;

//const TInt KAppLauncherCheckerRateInMicroSeconds=2000000;


class TSorter : public TSwap, public TKey
	{
public:
	TSorter( CArrayFixFlat<TInt>& aArray, TBool aSortingAllCategory, 
			 CAppLauncherModel::TSortApps aSortOrder, const CAppLauncherModel& aModel) 
			 : iArray(aArray), iSortingAllCategory(aSortingAllCategory), iModel(aModel), iSortOrder(aSortOrder) {};
	
	// Method called by User::QuickSort()
	void Swap(TInt aLeft, TInt aRight) const;
	TInt Compare(TInt aLeft, TInt aRight) const;
private:
	CArrayFixFlat<TInt>& iArray;
	TBool iSortingAllCategory;
	const CAppLauncherModel& iModel;
	CAppLauncherModel::TSortApps iSortOrder;
	};


/**
   Class CApplication Implementation
 */

/**
   Creates an instance of an Application item.
  
   @param aAppData	a pointer the application's data
   @return				   a pointer to this object
 */
TAppLauncherApplication::TAppLauncherApplication(const TApaAppInfo& aAppData)
	{
	iUid = aAppData.iUid;
	iAllOrder = KUnInitialized; 
	iUpdated = ETrue;	// avoid the application be deleted as soon as it's added
	}

/**
   Creates an instance of an AppLauncher model.
  
   @param aDocument	 a pointer to the AppLauncher document
   @return			  a pointer to this object
 */
CAppLauncherModel* CAppLauncherModel::NewL()
	{
	CAppLauncherModel* self=new (ELeave) CAppLauncherModel();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

/**
   Destructor.
 */
CAppLauncherModel::~CAppLauncherModel()
	{
	if (iApplications)
		{
		iApplications->ResetAndDestroy();
		}
	delete iApplications;
	iFs.Close();
	iLsSession.Close();
	delete iTempIcon;
	delete iListNotifier;
	}

CAppLauncherModel::CAppLauncherModel()
	{
	}

/**
   Handles the actual initialization of this object.
  
  @param aDocument	 a pointer to the AppLauncher document 
 */
void CAppLauncherModel::ConstructL()
	{
	User::LeaveIfError(iFs.Connect());
	User::LeaveIfError(iLsSession.Connect());
	// prepare the application list
	iApplications = new (ELeave) CArrayPtrFlat<TAppLauncherApplication>(5);	
	iScreenMode=0;
	UpdateApplicationListL();
	iListNotifier = CApaAppListNotifier::NewL(this,CActive::EPriorityUserInput);
	}

void CAppLauncherModel::HandleAppListEvent(TInt /*aEvent*/)
	{
   	TRAP_IGNORE(UpdateApplicationListL());	// Ignore errors
	}

// change the scren mode and update the application list
void CAppLauncherModel::SetScreenModeL(TInt aScreenMode)
	{
	iScreenMode=aScreenMode;
	UpdateApplicationListL();
	}

/**
  	Update the application list
 */
void CAppLauncherModel::UpdateApplicationListL()
	{
	iLsSession.GetAllApps(iScreenMode);
	TInt appCount = 0;
	iLsSession.AppCount(appCount);
	TApaAppInfo appInfo;
	TInt index;
//	TBool appAdded = EFalse;
//	TBool appRemoved = EFalse;
	TApaAppCapabilityBuf capability;
	CArrayFixFlat<TSize>* iconSizes = new CArrayFixFlat<TSize>(5);
	CleanupStack::PushL(iconSizes);
	
	while(iLsSession.GetNextApp(appInfo,iScreenMode) == KErrNone)
		{
		iLsSession.GetAppCapability(capability,appInfo.iUid);

		// if application is hidden, only add it if hidden files are allowed
//		if(iDocument.ShowHiddenFiles() || !(capability().iAppIsHidden))
//			{
			TUid appUid = appInfo.iUid;
			if(iLsSession.GetAppIconSizes(appUid,*iconSizes)==KErrNone && iconSizes->Count()>0)
				{
				index=ApplicationIndex(appUid);
				if (index==KUnlistedApplication)
					{
					TAppLauncherApplication* app=new(ELeave)TAppLauncherApplication(appInfo);
					CleanupStack::PushL(app);
					iApplications->AppendL(app);
					CleanupStack::Pop(app);
					}
				else 
					{
					iApplications->At(index)->iUpdated = ETrue;
					}
				}
//			}
		iconSizes->Reset();
		}
	CleanupStack::PopAndDestroy(iconSizes);
	for (index = 0; index < iApplications->Count(); index++)
		{	// clean the updated flag
		TAppLauncherApplication* app = iApplications->At(index);
		if (!app->iUpdated)
			{	// remove the application from the list
			delete iApplications->At(index);
			iApplications->Delete(index--);
			}
		else
			{ // clear the flag for the next turn
			app->iUpdated=EFalse;
			}
		}
	// memorize we made the update
//	if (appAdded)
//		{
//		CheckUnInitializedApplication();
//		}
	if (iAppListObserver)
		{
		iAppListObserver->AppListChangedL();
		}
	}	

/**
   Tell the model it's observer
  
   @param aAppListObserver object called when teh list change
 */
void CAppLauncherModel::SetAppListObserver(MAppListObserver* aAppListObserver)
	{
	iAppListObserver=aAppListObserver;
	}

TTime CAppLauncherModel::TimeOfLastStartedApplication() const
	{
	return iLastStartedAppTime;
	}

void CAppLauncherModel::SetTimeOfLastStartedApplication(const TTime& aTime)
	{
	iLastStartedAppTime=aTime;
	}

/**
   Returns the name of an application with a certain index.
  
   @param aIndex			the index of the application
   @param aApplicationName	filled up with the name of the application
 */
void CAppLauncherModel::ApplicationCaption(TInt aIndex, TApaAppCaption& aApplicationName) const //aIndex ranges from 0 to number of applications - 1
	{
	TApaAppInfo info;
	if( iLsSession.GetAppInfo(info,iApplications->At(aIndex)->iUid)==KErrNone)
		{
		aApplicationName.Copy(info.iCaption);
		}
	}

/**
   Returns the number of applications in application array.
  
   @return  the number of applications
 */
TInt CAppLauncherModel::NumberOfApplications() const
	{
	return iApplications->Count();
	}

/**
   Returns the unique id of the application with a certain index.
  
   @param aIndex  the index of the application
   @return		the unique id
 */
TUid CAppLauncherModel::ApplicationUid(TInt aIndex) const
	{
	return (iApplications->At(aIndex))->iUid;
	}

/**
   Returns the applications filename of the application with a certain index.
  
   @param aIndex				the index of the application
   @param aApplicationFileName	filled up with the file name
 */
void CAppLauncherModel::ApplicationFileName(TInt aIndex, TDes& aApplicationFileName) const
	{
	TApaAppInfo info;
	if(iLsSession.GetAppInfo(info,iApplications->At(aIndex)->iUid)==KErrNone)
		{
		aApplicationFileName.Copy(info.iFullName);
		}
	}

/**
   Returns information on one application.
  
   @param aIndex  the application index
   @return		the application data
 */
const TAppLauncherApplication& CAppLauncherModel::ApplicationData(TInt aIndex) const
	{
	return *(iApplications->At(aIndex));
	}

/**
   Saves the model data to persistent storage.
  
   @param aStream  the data stream used to save the data
 */

/** Not used - commented out for WINS UREL warning
void CAppLauncherModel::ExternalizeL(RWriteStream& aStream) const
	{
	TInt count = iApplications->Count();		
	aStream.WriteInt32L(count);
	for(TInt index=0;index<count;index++)
		{
		aStream.WriteInt32L((ApplicationUid(index)).iUid);
		aStream.WriteInt32L(ApplicationAllOrder(index)); 
		}

	}
*/

/**
   Loads the model data from persistent storage.
  
   @param aStream  the data stream used to load the data
 */

/** Not used - commented out for WINS UREL warning
void CAppLauncherModel::InternalizeL(RReadStream& aStream)
	{
	TInt count=aStream.ReadInt32L();
	TInt id;
	TUid uid;
	for(TInt index=0;index<count;index++)
		{
		id=aStream.ReadInt32L();
		uid.iUid=id;
		if(ApplicationIndex(uid)==KUnlistedApplication)
			{
			continue; // the application is no longer listed and is ignored
			}
		const TInt numOfApps=iApplications->Count();
		for(TInt appIndex=0;appIndex<numOfApps;appIndex++)
			{
			if(uid==ApplicationUid(appIndex))
				{
				SetApplicationAllOrder(appIndex,aStream.ReadInt32L());
				break; //found!
				}
			
			}		
		}
//	CheckUnInitializedApplication();
	}
*/

/**
   Reads a chunk of the resource file if no ALAUNCH.ini-file can be found.
  
   @param resourceReader  a resource reader by wich we get information from resource file
 */

void CAppLauncherModel::ReadResource(TResourceReader resourceReader)
	{
	TInt32 applicationOrders = resourceReader.ReadInt32();	//The size of the resource array
	TInt err;
	TRAP(err, ReadApplicationsOrdersL(applicationOrders));
//	CheckUnInitializedApplication();
	}

void CAppLauncherModel::ReadApplicationsOrdersL(TInt32 aResourceId)
	{
	TResourceReader resourceReader;
	CEikonEnv::Static()->CreateResourceReaderLC(resourceReader, aResourceId);
	const TInt size = resourceReader.ReadUint16();	//The size of the resource array
	for(TInt ii=0;ii<size;ii++)
		{
		const TInt appCount=resourceReader.ReadUint16(); // the size of the array
		for(TInt app=0;app<appCount;app++)
			{
			TUid uid;
			uid.iUid=resourceReader.ReadUint32();
			for (TInt index2=0;index2<NumberOfApplications();index2++)
				{	
				if (uid==ApplicationUid(index2))
					{
					SetApplicationAllOrder(index2,app);
					break;
					}
				}
			}
		}
	CleanupStack::PopAndDestroy(); // resourceReader
	}

/**
   Returns the index number of an application with a certain Uid.
  
   @param aUid  the Uid of the application
   @return	  the index number of the application
 */
TInt CAppLauncherModel::ApplicationIndex(const TUid& aUid) const
	{
	const TInt numOfApps=iApplications->Count();
	for(TInt index=0;index<numOfApps;index++)
		{
		if(ApplicationUid(index).iUid==aUid.iUid)
			{
			return index;
			}
		}
	return KUnlistedApplication;
	}

/**
   Returns the index number of an application with a certain Name.
  
   @param aFileName		the Full file name of the application
   @return				the index number of the application
 */
TInt CAppLauncherModel::ApplicationIndex(const TFileName& aFileName) const
	{
	const TInt numOfApps=iApplications->Count();
	for(TInt index=0;index<numOfApps;index++)
		{
		TApaAppInfo info;
		if(iLsSession.GetAppInfo(info,iApplications->At(index)->iUid)==KErrNone)
			{
			if (info.iFullName.Compare(aFileName)==0)
				{
				return index;
				}
			}
		}
	return KUnlistedApplication;
	}

/**
   Sets the all order at certain index
  
   @param aIndex		the index of the application
   @param aOrder		the order the application should be shown
 */
void CAppLauncherModel::SetApplicationAllOrder(TInt aIndex, TInt aOrder)
	{
	iApplications->At(aIndex)->iAllOrder = aOrder;
	}

/**
   Returns the all order at certain index
  
   @param aIndex		the index of the application
   @return				allOrder
 */
TInt CAppLauncherModel::ApplicationAllOrder(TInt aIndex) const
	{
	return (iApplications->At(aIndex)->iAllOrder);
	}

void TSorter::Swap(TInt aLeft, TInt aRight) const
	{
	TInt left=iArray[aLeft];
	TInt right=iArray[aRight];
	iArray.Delete(aLeft);
	iArray.InsertL(aLeft,right);	// This InsertL() cannot leave
	iArray.Delete(aRight);
	iArray.InsertL(aRight,left);	// This InsertL() cannot leave
	}

TInt TSorter::Compare(TInt aLeft, TInt aRight) const
	{
	const TInt left=iArray[aLeft];
	const TInt right=iArray[aRight];
	TInt compare=0;
	if(compare == 0)
		{
		TApaAppCaption leftCaption;
		TApaAppCaption rightCaption;
		iModel.ApplicationCaption(left, leftCaption);
		iModel.ApplicationCaption(right, rightCaption);
		compare = leftCaption.CompareC(rightCaption);
		}
	return compare;
	}

RApaLsSession CAppLauncherModel::LsSession()
	{
	return iLsSession;
	}
