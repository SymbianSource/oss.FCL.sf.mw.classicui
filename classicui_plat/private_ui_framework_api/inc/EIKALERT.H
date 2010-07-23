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


#if !defined(__EIKALERT_H__)
#define __EIKALERT_H__

#if !defined(__EIKDIALG_H__)
#include <eikdialg.h>
#endif

#if !defined(__EIKENV_H__)
#include <eikenv.h>
#endif

#include <aknstaticnotedialog.h>

class CEikAlert : public CAknNoteDialog, public MEikAlertWin
	{
public: 
    // From CCoeControl
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	
private:
	// Defined by the Mix-in class:
	void ConstructL();
	void RunAlert(const TDesC& aMsg1,const TDesC& aMsg2);
	void Release();
	CEikDialog* AsEikDialog();
private:
	void PreLayoutDynInitL();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private: 
	virtual void CEikDialog_Reserved_1();
	virtual void CEikDialog_Reserved_2();	
private: 
	virtual void CAknNoteDialog_Reserved();

protected:
	const TDesC* iMsg1;
	const TDesC* iMsg2;
	friend class CEikAlertNotifier;
	};

NONSHARABLE_CLASS(CEikAlertNotifier): public CBase, public MEikAlertWin
    {
    public: 
        ~CEikAlertNotifier();
    private: // from MEikAlert    
        void ConstructL();
        void RunAlert(const TDesC& aTitle, const TDesC& aMsg) ;
        void Release();
        CEikDialog* AsEikDialog();
    private:
        void CreateLocalDialogIfRequired();     
        CEikAlert* iLocalDialog;
        CBufFlat* iNotifierBuffer;
    };

#endif
