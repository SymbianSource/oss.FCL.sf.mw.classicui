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

#include "AknSyncDraw.h"


class CCoeControlAccess : public CCoeControl
	{
public:
	using CCoeControl::ActivateGc;
	using CCoeControl::DeactivateGc;
	using CCoeControl::Window;
	using CCoeControl::HandleRedrawEvent;
	};


enum TSyncDrawFlags
	{
	EInDrawLoop
	};


const TInt KSyncDrawArrayGranularity = 4;


EXPORT_C void MAknSyncDrawer::MAknSyncDrawer_Reserved_1() {}
EXPORT_C void MAknSyncDrawer::MAknSyncDrawer_Reserved_2() {}


EXPORT_C TAknSyncControlDrawer::TAknSyncControlDrawer()
	{
	}

EXPORT_C void TAknSyncControlDrawer::SetControl(CCoeControl* aControl)
	{
	iControl = static_cast<CCoeControlAccess*>(aControl);
	}

EXPORT_C void TAknSyncControlDrawer::MasrPrepareForDraw()
	{
	iDrawRect = TRect();
	RWindow& window = iControl->Window();
	RRegion region;
	window.GetInvalidRegion(region);
	if (!region.CheckError())
		{
		iDrawRect = region.BoundingRect();
		}
	region.Close();
	}

EXPORT_C void TAknSyncControlDrawer::MasrDraw()
	{
	if (!iDrawRect.IsEmpty())
		iControl->HandleRedrawEvent(iDrawRect);
	}

EXPORT_C void TAknSyncControlDrawer::MasrDeactivateGc() const
	{
	iControl->DeactivateGc();
	}

EXPORT_C void TAknSyncControlDrawer::MasrActivateGc() const
	{
	iControl->ActivateGc();
	}


EXPORT_C CAknDrawSynchronizer* CAknDrawSynchronizer::NewL()
	{
	CAknDrawSynchronizer* self = new(ELeave) CAknDrawSynchronizer();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

EXPORT_C CAknDrawSynchronizer::~CAknDrawSynchronizer()
	{
	delete iSyncDrawers;
	}

CAknDrawSynchronizer::CAknDrawSynchronizer()
	{
	}

void CAknDrawSynchronizer::ConstructL()
	{
	iSyncDrawers = new(ELeave) CSyncDrawers(KSyncDrawArrayGranularity);
	}

EXPORT_C void CAknDrawSynchronizer::AddL(MAknSyncDrawer* aDrawer)
	{
	Remove(aDrawer);
	iSyncDrawers->AppendL(aDrawer);
	}

EXPORT_C void CAknDrawSynchronizer::Remove(MAknSyncDrawer* aDrawer)
	{
	TInt count = iSyncDrawers->Count();
	for (TInt ii = count-1; ii >= 0; ii--)
		{
		if (iSyncDrawers->At(ii) == aDrawer)
			iSyncDrawers->Delete(ii);
		}
	}

EXPORT_C void CAknDrawSynchronizer::Signal(const MAknSyncDrawer* aDrawer)
	{
	if (iFlags[EInDrawLoop])
		return;
	iFlags.Set(EInDrawLoop);

	if (aDrawer)
		aDrawer->MasrDeactivateGc();

	const TInt count = iSyncDrawers->Count();
	TInt ii;

	// prepare to draw
	for (ii = 0; ii<count; ++ii)
		{
		MAknSyncDrawer* redrawer = iSyncDrawers->At(ii);
		if (redrawer != aDrawer)
			redrawer->MasrPrepareForDraw();
		}

	// draw
	for (ii = 0; ii<count; ++ii)
		{
		MAknSyncDrawer* redrawer = iSyncDrawers->At(ii);
		if (redrawer != aDrawer)
			redrawer->MasrDraw();
		}

	if (aDrawer)
		aDrawer->MasrActivateGc();

	iFlags.Clear(EInDrawLoop);
	}


// End of File
