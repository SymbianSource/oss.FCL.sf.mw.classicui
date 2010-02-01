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

#ifndef __COEFEPFF_H__
#define __COEFEPFF_H__

#include <e32std.h>

class CCoeFepParameters;
class CCoeFep;

/** FEP factory function which must be exported by every FEP.

The function is called by the UI Control Framework when it loads the
FEP. It returns a fully constructed object of a CCoeFep-derived class, 
and passes ownership of that object to the caller.

The function can leave with any of the system-wide error codes,
for instance KErrNoMemory.

@publishedAll
@released
@param aConeEnvironment A reference to the application's control environment. 
@param aFullFileNameOfDll The full file name of the FEP's top-level DLL, i.e. 
something like "z:\system\fep\TFEP1.FEP". A FEP could use this parameter to 
work out the location of its resource file.
@param aFepParameters FEP parameters. These should simply be passed to 
CCoeFep::BaseConstructL().
@return A pointer to the newly created object belonging to a 
CCoeFep-derived class. */
IMPORT_C CCoeFep* NewFepL(CCoeEnv& aConeEnvironment, const TDesC& aFullFileNameOfDll, const CCoeFepParameters& aFepParameters);

/** Runs the FEP settings dialog.

The function is called by the FEPs control panel plug-in in order 
to run the settings dialog for the FEP. It must be exported by 
every FEP.

The function can leave with any of the system-wide error codes,
for instance KErrNoMemory.

Note: the FEP may or may not be loaded when this function is called.

@publishedAll
@released
@param aConeEnvironment A reference to the application's control environment.
@param aFullFileNameOfDll The full file name of the FEP's top-level DLL, i.e.
something like "z:\system\fep\TFEP1.FEP". */
IMPORT_C void SynchronouslyExecuteSettingsDialogL(CCoeEnv& aConeEnvironment, const TDesC& aFullFileNameOfDll);
IMPORT_C void Reserved_1();
IMPORT_C void Reserved_2();
IMPORT_C void Reserved_3();
IMPORT_C void Reserved_4();
IMPORT_C void Reserved_5();
IMPORT_C void Reserved_6();
IMPORT_C void Reserved_7();
IMPORT_C void Reserved_8();

#endif	// __COEFEPFF_H__

