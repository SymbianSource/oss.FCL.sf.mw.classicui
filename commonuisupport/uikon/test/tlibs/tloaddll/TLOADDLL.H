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
//

/**
 @file
 @internalComponent - Internal Symbian test code 
*/

#if !defined(__TLOADDLL_H__)
#define __TLOADDLL_H__

#include <f32file.h>
#include <e32base.h>
#include <eiklibry.h>
#include <techview/eiklabel.h>

class CEikTestContentManager;

//
//
//	CTestEikDllLoadedLabel
//
//
class CTestEikDllLoadedLabel : public CEikLabel
	{
public:
	enum
		{
		ECtTestEikDllLoadedLabel = 666,
		ECtTestEikEComDllLoadedLabel
		};
private: 
	// framework
    void Draw(const TRect& aRect) const;
	};


//
//
//	CTestEikonDllLoading
//
//
class CTestEikonDllLoading : public CEikLibrary
	{
public:
	~CTestEikonDllLoading();
	IMPORT_C static const CTestEikonDllLoading*	NewL();
	static SEikControlInfo CreateByTypeL(TInt aControlType);
private: // from CEikLibrary
	void								InitializeL();
	CArrayFix<TFileName>*				ResourceFileArrayL() const;
	CArrayFix<TCreateByTypeFunction>*	ControlFactoryArrayL() const;
private:
	CTestEikonDllLoading();
	TFileName ResourceFile() const;
private:
	CEikTestContentManager* iContentManager;
	};

//! TAutoLib 
/** 
  ECom plugin dll - derived from CEikLibrary2 supporting ECom
  CTestAutoContainer loads this to test that the CEikonEnv::LoadLibrariesL()
  loads both old style dll and ecom plugin dll.
*/

class CTestEikonEComDllLoading : public CEikLibrary2
	{
public:
	~CTestEikonEComDllLoading();
	IMPORT_C static const CTestEikonEComDllLoading*	NewL();
	static SEikControlInfo CreateByTypeL(TInt aControlType);
private: // from CEikLibrary2
	void								InitializeL();
	CArrayFix<TFileName>*				ResourceFileArrayL() const;
	CArrayFix<TCreateByTypeFunction>*	ControlFactoryArrayL() const;
private:
	CTestEikonEComDllLoading();
	TFileName ResourceFile() const;
private:
	CEikTestContentManager* iContentManager;
	};

#endif
