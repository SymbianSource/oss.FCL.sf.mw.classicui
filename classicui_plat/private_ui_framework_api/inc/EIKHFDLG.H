/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined(__EIKHGDLG_H__)
#define __EIKHGDLG_H__

#if !defined(__EIKDIALG_H__)
#include <eikdialg.h>
#endif

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#if !defined(__EIKENV_H__)
#include <eikenv.h>
#endif


class CCoeRedrawer;
class CSchedulerShaker;

class TEikHeapFailModel
	{
public:
	TInt iHeapFailRate;
	TInt iHeapFailType;
	TInt iWservFailRate;
	TInt iWservFailType;
	TInt iFileFailRate;
	TInt iFileFailType;
	};


//
//	class CEikDebugKeys
//

class CEikDebugKeys : public CCoeControl, public MEikDebugKeys
	{
public: 
    // From CCoeControl
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	
private: // from MEikDebugKeys
	void ConstructL();
	void Release();
private: // framework
	virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	void InfoNote(const TDesC& aDes);
private:
	friend class CEikonEnv;
//	friend class CDebugKeysDlg;
//	friend class CDebugKeysAppUi;
	TEikHeapFailModel iModel;
	TBool iVerbose;
	CCoeRedrawer* iPhantomBorderDrawer;
	CSchedulerShaker* iSchedulerShaker;
	};


//
//	class CEikDebugWin
//

class CEikDebugWin : public CCoeControl
    {
public:
    void ConstructL();
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	
private:
	void Draw(const TRect& aRect) const;
    };


#endif
