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
// EIKSRV.CPP
// 
//

#include <bautils.h>
#include <eiksrvs.h>
#include <eiksrv.h>
#include <eiksvdef.h>
#include <eikdebug.h>
#include <e32hal.h>
#include <eikdll.h>
#include "EIKNFYSV.H"
#include "EIKBAKSV.H"
#include "EIKALSRV.H"
#include "EIKUNDER.H"
#include <c32comm.h>
#include <s32file.h>
#include <apasvst.h>
#include <basched.h>
#include <apgcli.h>
#include <eikenv.h>

#if defined(_DEBUG) // for the HAL::Get call in EikDll::RunAppInsideThread to pre-allocate its heap-cell before any OOM testing is started
#include <hal.h>
#include <hal_data.h>
#endif


/**
Local static function run directly from entry point.  Starts up server.
@internalComponent
*/
static TInt RunServer()
	{
	TBool oomTestingOnEiksrvStartUp=EFalse;
#if defined(UIKON_OOM_TESTING)
	User::__DbgMarkStart(RHeap::EUser);
	CEikDebugPreferences* debugPreferences=CEikDebugPreferences::New();
	if (debugPreferences!=NULL)
		{
		RFs fileServerSession;
		if (fileServerSession.Connect()==KErrNone)
			{
			if (debugPreferences->Restore(fileServerSession)==KErrNone)
				{
				oomTestingOnEiksrvStartUp=(debugPreferences->Flags()&CEikDebugPreferences::EFlagOOMTestingOnEiksrvStartUp);
				}
			}
		fileServerSession.Close();
		delete debugPreferences;
		}
	User::__DbgMarkEnd(RHeap::EUser, 0);
#endif

#if defined(_DEBUG)
	{
	TInt notUsed;
	HAL::Get(HALData::EDisplayColors, notUsed); // this is to pre-allocate the heap-cell that certain HAL functions leave lying around (without actually orphaning it) - if we don't do this then the User::__DbgMarkEnd near the end of the loop below will panic because of this heap-cell
	}
#endif


	TInt error=User::RenameThread(EIKAPPUI_SERVER_THREAD_NAME);
	if (error!=KErrNone)
		{
		return error;
		}
	for (TInt failRate=1; ; ++failRate)
		{
		TBool tryAgain=EFalse;
		User::__DbgMarkStart(RHeap::EUser);
		if (oomTestingOnEiksrvStartUp)
			{
			__SHOW_FAIL_RATE(_L("OOM testing on Eiksrv start up (fail rate %d)"), failRate);
			User::__DbgSetAllocFail(RHeap::EUser, RHeap::EFailNext, failRate);
			}
		TInt error=KErrNoMemory;
		CEikonEnv* coe=new CEikServEnv;
		if ((coe!=NULL) && (User::TrapHandler()!=NULL))
			{
			TRAP(error,
				coe->ConstructL();
				CEikServAppUiServer::NewL()); // the object created by CEikServAppUiServer::NewL is owned by CEikServEnv's iServer
			}
		if (oomTestingOnEiksrvStartUp)
			{
			TAny* const pointer=User::Alloc(1);
			User::Free(pointer);
			if (pointer!=NULL)
				{
				tryAgain=ETrue;
				}
			}
		if ((error==KErrNone) && !tryAgain)
			{
			RProcess::Rendezvous(KErrNone);
			coe->ExecuteD();
			}
		else
			{
			if (coe!=NULL)
				{
				coe->DestroyEnvironment();
				}
			if (!tryAgain)
				{
				User::__DbgMarkEnd(RHeap::EUser, 0);
				return error;
				}
			}
		User::__DbgMarkEnd(RHeap::EUser, 0);
		if (!tryAgain)
			{
			break;
			}
		}
	return KErrNone;
	}


TInt E32Main()
	{
	return RunServer();
	}

