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

#include <eikamnt.h>
#include <gulicon.h>
#include "eikautomenutitlearray.h"

/** Allocates and constructs a new CEikAutoMenuTitle object. 

This function takes ownership of aIcon and pushes it to the cleanup stack.

@param aPos The position of the title within the menu bar.
@param aText The menu title's text.
@param aMenuObserver The menu observer.
@param aMenuPaneResourceId The menu pane's resource ID.
@param aIcon The icon to include in the menu title.
@return A newly-constructed menu title object. */
EXPORT_C CEikAutoMenuTitle* CEikAutoMenuTitle::NewLC(TTitlePos aPos, const TDesC& aText, MEikAutoMenuObserver& aMenuObserver,
														TInt aMenuPaneResourceId, CGulIcon* aIcon)
	{ // static
	CleanupStack::PushL(aIcon);
	CEikAutoMenuTitle* self = new(ELeave) CEikAutoMenuTitle(aPos, aText, aMenuObserver, aMenuPaneResourceId,aIcon);
	CleanupStack::Pop(aIcon);
	CleanupStack::PushL(self);
	return self;
	}

CEikAutoMenuTitle::CEikAutoMenuTitle(TTitlePos aPos, const TDesC& aText, MEikAutoMenuObserver& aMenuObserver,
										TInt aMenuPaneResourceId, CGulIcon* aIcon)
	: iPos(aPos), iText(aText), iMenuObserver(aMenuObserver), iMenuPaneResourceId(aMenuPaneResourceId), iIcon(aIcon)
	{}

/** Destructor */
EXPORT_C CEikAutoMenuTitle::~CEikAutoMenuTitle()
	{
	delete iIcon;
	}


//
// class CEikAutoMenuTitleArray
//

/** Constructs an array of menu titles. */
CEikAutoMenuTitleArray::CEikAutoMenuTitleArray()
	: CArrayPtrFlat<CEikAutoMenuTitle>(1)
	{}

/** Destructor. This also calls ResetAndDestroy() on the menu title array. */
CEikAutoMenuTitleArray::~CEikAutoMenuTitleArray()
	{
	ResetAndDestroy();
	}
