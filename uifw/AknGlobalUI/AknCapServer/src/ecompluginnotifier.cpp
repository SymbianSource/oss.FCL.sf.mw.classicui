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
/*
* ============================================================================
* TODO: Appropriate header needs to go here
* ============================================================================
*/

#include <ecompluginnotifier.h>
#include <coemain.h>


EXPORT_C TEComPluginInfo::TEComPluginInfo(const TUid& aUid, const TInt aVersion, const TDriveUnit& aDrive)
: iUid(aUid), iVersion(aVersion), iDrive(aDrive)
	{
	}



CEComPluginNotifier::CEComPluginNotifier(const TUid& aInterfaceId, TCallBack& aCallBack)
:CActive(EActivePriorityDefault), iInterfaceId(aInterfaceId), iCallBack(aCallBack)
	{
	// TODO: What happens if this fails?
	CActiveScheduler::Add(this);
	}


void CEComPluginNotifier::ConstructL()
	{
	iEComSession = &REComSession::OpenL();
	}


CEComPluginNotifier::~CEComPluginNotifier()
	{
	Cancel();
	if (iEComSession)
		{
		iEComSession->Close();
		iEComSession = NULL;
		}
	iPreviousPlugins.Reset();
	}


EXPORT_C CEComPluginNotifier* CEComPluginNotifier::NewL(const TUid& iInterfaceId, TCallBack& aCallBack)
	{
	CEComPluginNotifier* self = CEComPluginNotifier::NewLC(iInterfaceId, aCallBack);
	CleanupStack::Pop(self);
	return self;
	}


EXPORT_C CEComPluginNotifier* CEComPluginNotifier::NewLC(const TUid& iInterfaceId, TCallBack& aCallBack)
	{
	CEComPluginNotifier* self = new (ELeave) CEComPluginNotifier(iInterfaceId, aCallBack);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}


EXPORT_C void CEComPluginNotifier::Start()
	{
	// Load initial list of plugins for the UID
	if(iInterfaceId.iUid != 0)
		EComPluginUtils::GetInfoArrayL(iInterfaceId, iPreviousPlugins);
	
	if (!IsActive())
		{
		iEComSession->NotifyOnChange(iStatus);
		SetActive();
		}
	}

	
void CEComPluginNotifier::RunL()
	{
	// TODO: Should the client be notified if there was an error?
	if (iStatus.Int() == KErrNone )
		{
		if(iInterfaceId.iUid == 0)
			{
			RunCallBack();
			}
		else
			{
			TRAP_IGNORE(CheckForEComPluginChangeL())
			}
		// TODO: Should this be outside the if? What if there was a connection error?
		Start();
		}
	}

	
void CEComPluginNotifier::DoCancel()
	{
	iEComSession->CancelNotifyOnChange(iStatus);
	}
	
	
void CEComPluginNotifier::CheckForEComPluginChangeL()
	{
	// TODO: Deal with errors here
	REComPluginInfoArray newPlugins;
	EComPluginUtils::GetInfoArrayL(iInterfaceId, newPlugins);
	
	TBool pluginsChanged = EFalse;
	
	TInt prevCount = iPreviousPlugins.Count();
	TInt newCount = newPlugins.Count();
	
	if(newCount != prevCount)
		{
		pluginsChanged = ETrue;
		}
	else
		{
		while(prevCount>0)
			{
			prevCount--;
			
			TUid prevUid = (iPreviousPlugins[prevCount]).iUid;
			TInt prevVer = (iPreviousPlugins[prevCount]).iVersion;
			TBool found = EFalse;
			
			newCount = newPlugins.Count();
			while(newCount>0)
				{
				newCount--;
				TUid newUid = (newPlugins[newCount]).iUid;
				TInt newVer = (newPlugins[newCount]).iVersion;
				if(prevUid == newUid && prevVer == newVer)
					{
					found = ETrue;
					}
				}
			
			if(!found)
				{
				pluginsChanged = ETrue;
				break;
				}
			}
		}
	
	if(pluginsChanged)
		{
		RunCallBack();
		}
	
	iPreviousPlugins.Reset();
	iPreviousPlugins = newPlugins;
	}


void CEComPluginNotifier::RunCallBack()
	{
	(iCallBack.iFunction)(iCallBack.iPtr);
	}



// a kind of cleanup item for ecom info array
NONSHARABLE_CLASS(CCleanupEComArray) : public CBase
    {
public:
    ~CCleanupEComArray()
        {
        iArray.ResetAndDestroy();
        iArray.Close();
        }
    RImplInfoPtrArray iArray;
    };

/**
 * Reusable utility functions from here, exported as static functions
 * of CEComPluginUtils
 **/ 
EXPORT_C TInt EComPluginUtils::GetInfoArrayL(const TUid aInterfaceId, REComPluginInfoArray& aReturnArray)
	{
	CCleanupEComArray* plugins = new (ELeave) CCleanupEComArray;
	CleanupStack::PushL(plugins);
	REComSession::ListImplementationsL(aInterfaceId, plugins->iArray);
	CreateInfoArray(plugins->iArray, aReturnArray);
	CleanupStack::PopAndDestroy(plugins);
	return KErrNone;
	}


EXPORT_C TInt EComPluginUtils::CreateInfoArray(const RImplInfoPtrArray aEComArray, REComPluginInfoArray& aReturnArray)
	{
	for(TInt i=0; i<aEComArray.Count(); i++)
		{
		TUid uid = (aEComArray[i])->ImplementationUid();
		TInt ver = (aEComArray[i])->Version();
		TDriveUnit drive = (aEComArray[i])->Drive();
		TEComPluginInfo info(uid, ver, drive);
		aReturnArray.Append(info);
		}
	return KErrNone;
	}
