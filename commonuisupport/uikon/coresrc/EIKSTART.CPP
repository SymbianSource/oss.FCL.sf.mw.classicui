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

#include <eikstart.h>
#include <f32file.h>
#include <bautils.h>
#include <basched.h>
#include <eikenv.h>
#include <eikdebug.h>
#include <eikpanic.h>
#include <uiklafgt/eikcore.rsg>

#if defined(_DEBUG) // for the HAL::Get call to pre-allocate its heap-cell before any OOM testing is started
#include <hal.h>
#include <hal_data.h>
#endif


/** Called to run the application specified in aApplicationFactory using the command line of the current process.
This overload of the function should be called from the E32Main() function. This overload should not be called
from the WinsMain() function in an exedll in EKA1 - the version that takes the command line as a parameter should.
 
@param aApplicationFactory Should be created implicitly by passing a pointer to
a factory function, an ECOM plugin UID, or a CImplementationInformation reference.
@see TApaApplicationFactory */
EXPORT_C TInt EikStart::RunApplication(TApaApplicationFactory aApplicationFactory)
	{ // static
	// Get the command line object with data as attached to the process by AppArc.
	CApaCommandLine* commandLine = NULL;
	TBool disableShutdownChecks = EFalse;
	TInt error = CApaCommandLine::GetCommandLineFromProcessEnvironment(commandLine);
	if(error)
		goto done;
		
#ifdef ALLOC_COUNTING
	TInt allocData[2];
	allocData[0]=0;
	allocData[1]=0;
	User::__DbgSetAllocFail(RHeap::EUser, STATIC_CAST(RHeap::TAllocFail, REINTERPRET_CAST(TUint, &allocData[0])), 0); // this line requires \base\e32\euser\US_HEAP.CPP to be temporarily modified to write to the allocData array passed in here
#endif // ALLOC_COUNTING

#ifdef _DEBUG
	TInt notUsed;
	HAL::Get(HALData::EDisplayColors, notUsed); // this is to pre-allocate the heap-cell that certain HAL functions leave lying around (without actually orphaning it) - if we don't do this then the User::__DbgMarkEnd near the end of the loop below will panic because of this heap-cell
#endif // _DEBUG

	// Mark the heap to detect memory leaks in debug builds.
	// The corresponding __DbgMarkEnd method is called conditionally below, dependent upon whether the app has disabled shutdown checks.
	// Here, the app has not yet run and so cannot yet have disabled shutdown checks. This call is therefore not conditional.
	User::__DbgMarkStart(RHeap::EUser);
	
	// Rename the thread. Do it in a {} block so that executableFileName does not stay 
	// on the stack while the application is running.
	{
	TFileName executableFileName = RProcess().FileName();
	error = User::RenameThread(TParsePtrC(executableFileName).Name());
	if(error)
		goto done;
	}

	// Continue in a {} block, to avoid gccxml compiler complaining about gotos jumping over CEikEnv initialization
	{
	// Create the CEikonEnv, and construct the app from the command line if no problems
	CEikonEnv* env = new CEikonEnv;
	if(!env)
		error = KErrNoMemory;
	else if(env->ConstructorError()!=KErrNone)
	    error = env->ConstructorError();
	else
		TRAP(error, env->ConstructAppFromCommandLineL(aApplicationFactory, *commandLine));
		
#ifdef ALLOC_COUNTING
	RDebug::Print(_L("Allocated %d and deallocated %d heap-cells %S start-up"), allocData[0], allocData[1], executable);
#endif // ALLOC_COUNTING
		
	delete commandLine;	// Must be deleted or CCoeEnv's heap checks will fail
	commandLine = NULL;
	
	if (!error)	// Start the app if no errors
		{		
		// Run the application
		env->Execute();
		}
	else if(env)	// ... or handle errors (error != KErrNone)
		{
		if (error==KLeaveWithoutAlert || error==KLeaveExit)
			error = KErrNone;
		else
			TRAP_IGNORE(env->HandleError(error));	
		} 
	if (env!=NULL)
		{
		disableShutdownChecks = env->DisableShutdownChecks();
   		env->DestroyEnvironment();
   		}
   				
	if (!error)
		{
		env = NULL;
		}
	}

done:
	delete commandLine;
	if (!disableShutdownChecks)
		{
		User::__DbgMarkEnd(RHeap::EUser, 0); // Affects debug builds.
		}
	
#ifdef ALLOC_COUNTING
	User::__DbgSetAllocFail(RHeap::EUser, RHeap::ENone, 0);
#endif // ALLOC_COUNTING
	
	return error;
	}


