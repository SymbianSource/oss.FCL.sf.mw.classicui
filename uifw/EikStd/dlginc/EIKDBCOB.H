/*
* Copyright (c) 1999 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __EIKDBCOB_H__
#define __EIKDBCOB_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#ifndef __EIKCMOBS_H__
#include <eikcmobs.h>
#endif

class CEikDialog;

/**
 * The CEikDialogButtonCommandObserver class handles commands issued from a dialog's buttons
 * for a dialog. This allows a dialog to directly observe commands issued by controls on its pages or
 * from menus which it launches.
 *
 * @since ER5U
 * @internal
 */
NONSHARABLE_CLASS(CEikDialogButtonCommandObserver) : public CBase, public MEikCommandObserver
	{
public:
	static CEikDialogButtonCommandObserver* NewLC(CEikDialog& aDialog);
	static CEikDialogButtonCommandObserver* NewL(CEikDialog& aDialog);
	~CEikDialogButtonCommandObserver();
public:	// from MEikCommandObserver:
	virtual void ProcessCommandL(TInt aCommandId);
private:
	CEikDialogButtonCommandObserver(CEikDialog& aDialog);
private:
	CEikDialog& iDialog;
	};

#endif
