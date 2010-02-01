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

#ifndef __ALNCMODL_H
#define __ALNCMODL_H

#ifndef __E32BASE_H__
#include <e32base.h>	// class CBase
#endif

#include <apgaplst.h>
#include <apgnotif.h>
#include <barsread.h>

#include <f32file.h>

class CApaMaskedBitmap;
class CApaAppData;
class CApaAppList;
class CApaFileRecognizer;
class RWriteStream;
class CAppLauncherDocument;
class CApaFsMonitor;

/**
   This class holds the properties of one application (to be launched by the AppLauncher).
 */
class TAppLauncherApplication : public CBase
	{
public:
	TAppLauncherApplication(const TApaAppInfo& aAppData);		// Creates an instance of an CAppLauncherApplication item.
protected:
	// the four following informations are get from CApaAppData
	TUid iUid;	// Uid for the application
	TInt iAllOrder;  // the order when all is shown
	TBool iUpdated;  // if the application have been visited during an AppList update
private:
	friend class CAppLauncherModel;
	};

/**
   This class allow an object to be notified when the application list have changed
 */
class MAppListObserver
	{
public:
	virtual void AppListChangedL() = 0;
	};


/**
   This class contains modifiable persistent application data.
 */
class CAppLauncherModel : public CBase, public MApaAppListServObserver
{
public:
	typedef enum
		{ESortByAppName} TSortApps;
public:
	static CAppLauncherModel* NewL();
	~CAppLauncherModel();
	TInt ApplicationAllOrder(TInt aIndex) const;
	void SetApplicationAllOrder(TInt index, TInt aOrder);
	void ApplicationCaption(TInt aIndex, TApaAppCaption& aApplicationName) const;
	TInt NumberOfApplications() const;
	TUid ApplicationUid(TInt aIndex) const;
	TInt ApplicationIndex(const TUid& aUid) const;
	TInt ApplicationIndex(const TFileName& aFileName) const;
//	void ExternalizeL(RWriteStream& aStream) const;
//	void InternalizeL(RReadStream& aStream);
	void ApplicationFileName(TInt aIndex, TDes& aApplicationFileName) const;
	const TAppLauncherApplication& ApplicationData(TInt aIndex) const;
	void ReadResource(TResourceReader resourceReader);
	CArrayFixFlat<TInt>* CreateAndAllocateApplicationOrderArrayLC(TInt aCategoryIndex, TSortApps aSort = ESortByAppName) const;
	TTime TimeOfLastStartedApplication() const;
	void SetTimeOfLastStartedApplication(const TTime& aTime);
	RApaLsSession LsSession();
	void SetScreenModeL(TInt aScreenMode);
public:
	/** Callback for completion of applist from AppArc */
	virtual void HandleAppListEvent(TInt aEvent);
public:		// applications list  monitoring
	void NotifyUpdate(TInt aReason);	// from MApaAppListObserver
	void SetAppListObserver(MAppListObserver* aAppListObserver);
private:
	CAppLauncherModel();
	void ConstructL();
	void ReadApplicationsOrdersL(TInt32 aResourceId);
private:	// applications list  monitoring
	void UpdateApplicationListL(); 
private:
	CArrayPtrFlat<TAppLauncherApplication>* iApplications;  //Contains all applications
	TInt iCurrentCategory;					// the currently selected category
	mutable CApaMaskedBitmap* iTempIcon;	// currently allocated icon
	RFs iFs;								// file system session
	RApaLsSession iLsSession;
	TInt iAppListUpdateCounter;				// counter of the last time we check to see if the application list has changed
	MAppListObserver* iAppListObserver;		// observer of this class, notified when the application list has changed
	TTime iLastStartedAppTime;				// Remember when last application was started
	/** Notifier for callbacks when applist changes */
	CApaAppListNotifier*            iListNotifier;
	TInt iScreenMode; //Current screen mode
	};

#endif
