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

#include <coemain.h>
#include "coeenvextra.h"
#include "coepanic.h"
#include <fepplugin.h>
#include "COEFEP.H"
#include "CoeDataStorage.h"


#include <ecom/ecom.h>


CCoeFepParameters* CCoeFepParameters::NewLC()
/**
@internalTechnology
*/
	{
	CCoeFepParameters* const fepParameters=new(ELeave) CCoeFepParameters;
	CleanupStack::PushL(fepParameters);
	return fepParameters;
	}

void CCoeEnv::EnsureSpecifiedFepIsLoadedL(TUid aFepUid)
	{
	if (iExtra->iFep.iFepUid != aFepUid)
		{
		if (aFepUid == KNullUid)
			{
			CCoeEnvExtra::DestroyFep(iExtra->iFep);
			iExtra->HandleChangeInLoadedFep();
			}
		else
			{
			CCoeEnvExtra::TFep newFep;
			CleanupStack::PushL(TCleanupItem(CCoeEnvExtra::DestroyFep, &newFep));
			newFep.iFepPlugIn = CCoeFepPlugIn::NewL(aFepUid);
			CCoeFepParameters* const dummyFepParameters = CCoeFepParameters::NewLC();
			newFep.iFep = newFep.iFepPlugIn->NewFepL(*this, *dummyFepParameters);
			CleanupStack::PopAndDestroy(dummyFepParameters);
			newFep.iFepUid=aFepUid;
			CleanupStack::Pop(&newFep);
			CCoeEnvExtra::DestroyFep(iExtra->iFep);
			iExtra->iFep = newFep;
			iExtra->HandleChangeInLoadedFep();
			}
		}
	}

static void CleanupResetEComImpArray(TAny* aArray)
	{
	RImplInfoPtrArray* implementationArray = reinterpret_cast<RImplInfoPtrArray*>(aArray);
	implementationArray->ResetAndDestroy();
	}
	
EXPORT_C void CCoeEnv::AvailableFepsL(RArray<TUid>& aUids, CDesCArray* aDisplayNames)
/**
Gets the UIDs, and optionally display names, of all the secure FEPs that are available.

@param	aUids The array of FEP UIDs to be filled.
@param	aDisplayNames The array of FEP display names to be filled. May be passed as NULL if display names are not required.
*/
	{
    CleanupClosePushL(aUids);
	aUids.Reset();
	if(aDisplayNames)
		{
		aDisplayNames->Reset();
		}
	RImplInfoPtrArray implementationArray;
	CleanupStack::PushL(TCleanupItem(CleanupResetEComImpArray, &implementationArray));
	REComSession::ListImplementationsL(KUidFepPluginInterface, implementationArray);
	const TInt count = implementationArray.Count();
	for(TInt index=0; index<count; ++index)
		{
		CImplementationInformation& impl = *(implementationArray[index]);
		User::LeaveIfError(aUids.Append( impl.ImplementationUid() ));
		if(aDisplayNames)
			{
			aDisplayNames->AppendL(impl.DisplayName());
			}
		}
	CleanupStack::PopAndDestroy(&implementationArray);
	CleanupStack::Pop(&aUids);
	}

EXPORT_C void CCoeEnv::InstallFepL(TUid aFepUid)
/**
Loads the specified secure FEP into all running applications. 

The currently loaded FEP, if any, is unloaded.

@param aFepUid The UID of the secure FEP to be loaded.
@capability WriteDeviceData		To protect against installation of insecure FEP.
*/
	{
	InstallFepL(aFepUid, EFalse);
	}

EXPORT_C void CCoeEnv::InstallFepL(TUid aFepUid, const TBool aLeave)
/**
Loads the specified secure FEP into all running applications.

The currently loaded FEP, if any, is unloaded.

@param aFepUid The UID of the secure FEP to be loaded.
@param aLeave No longer used.
@capability WriteDeviceData		To protect against installation of insecure FEP.
*/
	{
	(void)aLeave;
	TBuf<16> fepId;
	FepName::NameFromUid(fepId, aFepUid);
	CCoeDataStorage::GetL(*this).SetInstalledFepIdL(fepId);
	}

EXPORT_C void CCoeEnv::ExecuteFepSettingsDialogL(TUid aFepUid)
/**
Executes the settings dialog for the specified secure FEP.

The specified FEP does not need to be loaded.

@param aFepUid The UID of the secure FEP for which the settings dialog 
is to be executed.
*/
	{
	CCoeFepPlugIn* fepPlugIn = CCoeFepPlugIn::NewL(aFepUid);
	CleanupStack::PushL(fepPlugIn);
	fepPlugIn->SynchronouslyExecuteSettingsDialogL(*this);
	CleanupStack::PopAndDestroy(fepPlugIn);
	}


//


