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

#include "COEFEP.H"
#include <coedef.h>		// enum ERepositoryKeyMask_FepId etc
#include <e32std.h>
#include <e32base.h>
#include <coemain.h>
#include "CoeDataStorage.h"
#include "coepanic.h"
#include <centralrepository.h>
#include "coedefkeys.h"

//
// class CCoeFepLoader
//

CCoeFepLoader* CCoeFepLoader::NewL(CCoeEnv& aCoeEnv, CCoeFepLoader*& aOwner)
	{
	return new(ELeave) CCoeFepLoader(aCoeEnv, aOwner);
	}

CCoeFepLoader::~CCoeFepLoader()
	{
	Cancel();
	iOwner=NULL;
	}

CCoeFepLoader::CCoeFepLoader(CCoeEnv& aCoeEnv, CCoeFepLoader*& aOwner)
	:CActive(EActivePriorityFepLoader),
	 iCoeEnv(aCoeEnv),
	 iOwner(aOwner),
	 iFirstRunL(ETrue)
	{
	CActiveScheduler::Add(this);
	TRequestStatus* status=&iStatus;
	User::RequestComplete(status, KErrNone);
	SetActive();
	}

void CCoeFepLoader::DoCancel()
	{
	}

void CCoeFepLoader::RunL()
	{
	iCoeEnv.EnsureCorrectFepIsLoadedL();

	if (iFirstRunL)
		{
		iFirstRunL=EFalse;
#if defined(USE_IH_RAISE_EVENT)
        const TInt appStartupInstrumentationEventIdBase=iCoeEnv.AppStartupInstrumentationEventIdBase();
        if (appStartupInstrumentationEventIdBase!=0)
            {
            IH_DECLARE( lInstrumentationHandler );
            IH_CREATE( lInstrumentationHandler );
            IH_RAISE_EVENT( lInstrumentationHandler, appStartupInstrumentationEventIdBase+MTestInstrumentation::TIDOffsetEndApplicationReadyForInput );
            IH_DELETE( lInstrumentationHandler );
            }
#endif
		}
    delete this;
	}

TInt CCoeFepLoader::RunError(TInt aError)
	{
	delete this;
	return aError;
	}


//
// class CCoeFepTracker
//

CCoeFepTracker* CCoeFepTracker::NewL(CCoeEnv& aCoeEnv)
	{ // static
	CRepository& repository(CCoeDataStorage::GetL(aCoeEnv).FepFrameworkRepositoryL());
	CCoeFepTracker* fepTracker = new(ELeave) CCoeFepTracker(aCoeEnv,repository);
	CleanupStack::PushL(fepTracker);
	fepTracker->ConstructL();
	CleanupStack::Pop(fepTracker);
	return fepTracker;
	}

CCoeFepTracker::~CCoeFepTracker()
	{
	Cancel();
	}

CCoeFepTracker::CCoeFepTracker(CCoeEnv& aCoeEnv, CRepository& aRepository)
: CActive(EActivePriorityWsEvents), iCoeEnv(aCoeEnv), iRepository(aRepository)
	{
	CActiveScheduler::Add(this);
	}

void CCoeFepTracker::ConstructL()
	{
	Queue();
	}

void CCoeFepTracker::Queue()
	{
#if defined(_DEBUG)
	const TInt error=
#endif
	iRepository.NotifyRequest(ERepositoryKeyMask_FepId, ERepositoryKeyMask_FepId, iStatus);
	__ASSERT_DEBUG(error==KErrNone, Panic(ECoePanicUnexpectedError));
	SetActive();
	}

void CCoeFepTracker::DoCancel()
	{
	iRepository.NotifyCancel(ERepositoryKeyMask_FepId, ERepositoryKeyMask_FepId);
	}

void CCoeFepTracker::RunL()
	{
	const TInt error = iStatus.Int();
	Queue();
	User::LeaveIfError(error);
	iCoeEnv.EnsureCorrectFepIsLoadedL();
	}

//
// class FepName
//

TUid FepName::UidFromNameL(const TDesC& aName)
	{
	_LIT(KLitSecureFepNameMatch,"::*");
	const TInt pos = aName.Match(KLitSecureFepNameMatch);
	if(pos != 0)
		{
		return TUid::Null();
		}
	// The specified FEP uses ECom, and aName is actually the UID in hex prefixed with "::".
	TPtrC uidVal(aName.Mid(KLitSecureFepNameMatch().Length() - 1));
	if((uidVal.Length() > 2) && (uidVal[1] == 'x'))
		{
		// Has "0x" prefix.
		uidVal.Set(uidVal.Mid(2));
		}
	TUint32 uid = 0;
	TLex lexer(uidVal);
	User::LeaveIfError(lexer.Val(uid, EHex));
	return TUid::Uid(TInt(uid));
	}
	
void FepName::NameFromUid(TDes& aName, const TUid& aUid)
/**
Generates a common FEP name representation for a secure FEP.

@param		aName		On return, the common name representation.
@param		aUid		The UID of the secure FEP implementation.
*/
	{
	_LIT(KLitSecureFepNameFormat,"::%08X");
	aName.Format(KLitSecureFepNameFormat, aUid.iUid);
	}
	

