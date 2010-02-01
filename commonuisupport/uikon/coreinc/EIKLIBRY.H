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

#ifndef __EIKLIBRY_H__
#define __EIKLIBRY_H__

#include <f32file.h>
#include <e32base.h>
#include <eikfctry.h>


/**
Abstract base class specifying the interface for a dynamically-loaded DLL
which goes on to configure other Uikon statically-loaded DLLs.

@publishedPartner
@deprecated
*/
class CEikLibrary : public CBase
	{
public:
	// When EikEnv dynamically loads a DLL, it calls its InitializeL function
	// which will set up any variables which EikEnv requires. 
	virtual void InitializeL() = 0;
	// These functions give the EikEnv access to the libraries
	// resources and Control Factories. 
	virtual CArrayFix<TFileName>*				ResourceFileArrayL() const = 0;
	virtual CArrayFix<TCreateByTypeFunction>*	ControlFactoryArrayL() const = 0;
	IMPORT_C virtual void PostAppUiInitializeL();
	};


/**
Abstract base class specifying the interface for a ECom plugin DLL
which goes on to configure other Uikon statically-loaded DLLs.

@publishedPartner
@released
*/
class CEikLibrary2 : public CEikLibrary
	{
public:
	// Destructor.
	IMPORT_C virtual ~CEikLibrary2();
	IMPORT_C static CEikLibrary2* LoadLibraryL(TUid aImplementationUid); 
private:
	// UID of the implementation instantiated.
	TUid iDtrkey;
	};

#endif // __EIKLIBRY_H__
