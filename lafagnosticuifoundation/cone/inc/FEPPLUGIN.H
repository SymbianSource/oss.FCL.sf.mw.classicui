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

#ifndef __FEPPLUGIN_H__
#define __FEPPLUGIN_H__

#include <e32base.h>

class CCoeEnv;
class CCoeFep;
class CCoeFepParameters;

const TUid KUidFepPluginInterface = { 0x1020233F };

/**
CCoeFepPlugIn
Abstract base class for FEP plug ins
@publishedAll
@released
*/
class CCoeFepPlugIn : public CBase
	{
public:
	inline static CCoeFepPlugIn* NewL(TUid aFepUid);
	virtual ~CCoeFepPlugIn();
public:
	/** Creates a fully constructed object of CCoeFEP.

	@param aConeEnvironment	A reference to the application's control environment.
	@param aFepParameters FEP parameters.
	@return A pointer to the newly created object.
	*/
	virtual CCoeFep* NewFepL(CCoeEnv& aConeEnvironment, const CCoeFepParameters& aFepParameters) = 0;

	/** Runs the FEP settings dialog. 
	
	@param aConeEnvironment A reference to the application's control environment.
	*/
	virtual void SynchronouslyExecuteSettingsDialogL(CCoeEnv& aConeEnvironment) = 0;

private:
	TUid iDtorTag;
	};

#include <fepplugin.inl>

#endif	// __FEPPLUGIN_H__
