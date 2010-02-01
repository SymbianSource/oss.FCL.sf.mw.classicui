/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef AKNSYNCDRAW_H
#define AKNSYNCDRAW_H

#include <babitflags.h>
#include <coecntrl.h>
#include <eikdef.h>

class CCoeControlAccess;


class MAknSyncDrawer
	{
public:
	virtual void MasrPrepareForDraw() = 0;
	virtual void MasrDraw() = 0;
	virtual void MasrDeactivateGc() const = 0;
	virtual void MasrActivateGc() const = 0;
private:
	IMPORT_C virtual void MAknSyncDrawer_Reserved_1();
	IMPORT_C virtual void MAknSyncDrawer_Reserved_2();
	};


class TAknSyncControlDrawer : public MAknSyncDrawer
	{
public:
	IMPORT_C TAknSyncControlDrawer();
	IMPORT_C void SetControl(CCoeControl* aControl);
	IMPORT_C void MasrPrepareForDraw();
	IMPORT_C void MasrDraw();
	IMPORT_C void MasrDeactivateGc() const;
	IMPORT_C void MasrActivateGc() const;
private:
	TRect iDrawRect;
	CCoeControlAccess* iControl;
	};


NONSHARABLE_CLASS(CAknDrawSynchronizer) : public CBase
	{
public:
	IMPORT_C static CAknDrawSynchronizer* NewL();
	IMPORT_C ~CAknDrawSynchronizer();

	IMPORT_C void AddL(MAknSyncDrawer* aRedrawer);
	IMPORT_C void Remove(MAknSyncDrawer* aRedrawer);
	IMPORT_C void Signal(const MAknSyncDrawer* aRedrawer);

private:
	CAknDrawSynchronizer();
	void ConstructL();

private:
	typedef CArrayFixFlat<MAknSyncDrawer*> CSyncDrawers;
	CSyncDrawers* iSyncDrawers;
	TBitFlags iFlags;
	};


#endif

// End of File
