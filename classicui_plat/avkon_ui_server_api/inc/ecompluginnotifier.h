/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
#ifndef __ECOMPLUGINNOTIFIER_H__
#define __ECOMPLUGINNOTIFIER_H__

#include <e32std.h>
#include <ecom/ecom.h>

/**
 * Simple type to keep track of essential ECom plugin information.
 * Can be used for comparisons before/after a change.
 **/ 
struct TEComPluginInfo
	{
public:
	IMPORT_C TEComPluginInfo(const TUid& aUid, const TInt aVersion, const TDriveUnit& aDrive);
public:
	TUid		iUid;
	TInt		iVersion;
	TDriveUnit	iDrive;
	};


typedef RArray<TEComPluginInfo> REComPluginInfoArray;


/**
 * ECom notifier helper
 **/ 
class CEComPluginNotifier : public CActive
    {
public:
	IMPORT_C static CEComPluginNotifier* NewL(const TUid& iInterfaceId, TCallBack& aCallBack);
	IMPORT_C static CEComPluginNotifier* NewLC(const TUid& iInterfaceId, TCallBack& aCallBack);
	~CEComPluginNotifier();
	IMPORT_C void Start();
	
private:
	CEComPluginNotifier(const TUid& iInterfaceId, TCallBack& aCallBack);
	void CheckForEComPluginChangeL();
	void ConstructL();
	void RunL();
	void DoCancel();
	void RunCallBack();
	
private:
	TUid					iInterfaceId;
	TCallBack				iCallBack;
	REComSession*			iEComSession;	// Owned
	REComPluginInfoArray 	iPreviousPlugins;
    };


/**
 * General reusable utilities related to ECom plugin monitoring.
 **/ 
class EComPluginUtils
	{
public:
	IMPORT_C static TInt GetInfoArrayL(const TUid aInterfaceId, REComPluginInfoArray& aReturnArray);
	IMPORT_C static TInt CreateInfoArray(const RImplInfoPtrArray aEComArray, REComPluginInfoArray& aReturnArray);
	};


#endif // __ECOMPLUGINNOTIFIER_H__
