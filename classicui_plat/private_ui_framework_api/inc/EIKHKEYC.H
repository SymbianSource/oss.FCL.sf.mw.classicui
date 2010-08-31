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


#if !defined(__EIKHKEYC_H__)
#define __EIKHKEYC_H__

#include <AknControl.h>

class CEikHotKeyTable;
class MEikCommandObserver;

NONSHARABLE_CLASS(CEikHotKeyControl) : public CAknControl
	{
public:
	CEikHotKeyControl(CEikHotKeyTable* aTable,MEikCommandObserver* aObserver);
	~CEikHotKeyControl();
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // framework
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private:
	CEikHotKeyTable* iTable;
	MEikCommandObserver* iObserver;
	};

#endif
