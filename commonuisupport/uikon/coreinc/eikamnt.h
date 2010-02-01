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

#ifndef __EIKAMNT_H__
#define __EIKAMNT_H__

#include <e32base.h>

#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikautomenutitlearray.h>
#endif

class CGulIcon;
class MEikAutoMenuObserver;

/** A menu title that will be added to a standard resource-constructed menu bar. 

If added to the CEikAutoMenuTitleArray stored by CEikonEnv during standard 
application start up, the menu pane specified will appear in all applications. 
The menu observer passed in is notified of any events on such menu panes in 
preference to the usual observer (C<MyApp>AppUi). 

@publishedAll 
@released */
NONSHARABLE_CLASS(CEikAutoMenuTitle) : public CBase
	{
public:
	/** Specifies the position of a menu title in a menu. 

	If an array of menu titles holds more than one menu title that is specified 
	for the start or end of a menu, the menu titles are placed in the same order 
	as that in which they appear in the array. This means the first menu title 
	specified with EStart in an array will be the first on a menu bar and the last 
	EEnd will be the last on a menu bar. */
	enum TTitlePos
		{
		/** The menu title is placed first in a menu. */
		EStart,
		/** The menu title is placed last in a menu. */
		EEnd
		};
	enum { ENominalTextLength=40 };
public:
	IMPORT_C static CEikAutoMenuTitle* NewLC(TTitlePos aPos, const TDesC& aText, MEikAutoMenuObserver& aMenuObserver,
										TInt aMenuPaneResourceId = 0, CGulIcon* aIcon = NULL);
	IMPORT_C ~CEikAutoMenuTitle();
private:
	CEikAutoMenuTitle(TTitlePos aPos, const TDesC& aText, MEikAutoMenuObserver& aMenuObserver,
						TInt aMenuPaneResourceId, CGulIcon* aIcon);
public:
	TTitlePos iPos;
	TBuf<ENominalTextLength> iText;
	MEikAutoMenuObserver& iMenuObserver;
	TInt iMenuPaneResourceId;
	CGulIcon* iIcon;
	};

#endif	// __EIKAMNT_H__
