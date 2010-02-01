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

// AKNINIT.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNINIT_H__)
#define __AKNINIT_H__

#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__EIKLIBRY_H__)
#include <eiklibry.h>
#endif

class CAknControlFactory;
class CEikCDlgDialogFactory;
class CEikAppUiFactory;

NONSHARABLE_CLASS(CAknDllInitializer) : public CEikLibrary2
	{
public:
	~CAknDllInitializer();
	CAknDllInitializer();
private: // from CEikLibrary
	void								InitializeL();
	CArrayFix<TFileName>*				ResourceFileArrayL() const;
	CArrayFix<TCreateByTypeFunction>*	ControlFactoryArrayL() const;
	void PostAppUiInitializeL();
private:
	void AppendAvkonResourceFileL(CArrayFix<TFileName>& aResFileArray) const;
	void AppendAvkonPrivateResourceFileL(CArrayFix<TFileName>& aResFileArray) const;
	void AppendCtlResourcFileL(CArrayFix<TFileName>& aResFileArray) const;
	void AppendCDlgResourcFileL(CArrayFix<TFileName>& aResFileArray) const;
	void AppendFileResourcFileL(CArrayFix<TFileName>& aResFileArray) const;
	void AppendPrintResourcFileL(CArrayFix<TFileName>& aResFileArray) const;
	void AppendIrResourcFileL(CArrayFix<TFileName>& aResFileArray) const;
	void AppendMiscResourcFileL(CArrayFix<TFileName>& aResFileArray) const;
	void AppendCoCtlResourcFileL(CArrayFix<TFileName>& aResFileArray) const;
private:
	CEikAppUiFactory* iAppUiFactory;
	CEikCDlgDialogFactory* iCDlgDialogFactory;
	};

#endif
