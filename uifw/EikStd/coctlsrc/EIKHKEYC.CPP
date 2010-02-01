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


#include <eikhkeyc.h>
#include <eikhkeyt.h>
#include <eikcmobs.h>

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @internal
 * @since App-Framework_6.1
 */
#ifndef _DEBUG
EXPORT_C void CEikHotKeyControl::WriteInternalStateL(RWriteStream&) const
	{}
#else
EXPORT_C void CEikHotKeyControl::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	_LIT(KEikLitBtpanCtlSt,"<CEikHotKeyControl>");
	_LIT(KEikLitBtpanCtlEnd,"<\\CEikHotKeyControl>");
	_LIT(KEikLitBtpanCtlHkeyObs, "<iObserver>");
	_LIT(KEikLitBtpanCtlHkeyObsEnd, "<\\iObserver>");
	_LIT(KEikLitBtpanCtlHkeyTab, "<iTable>");
	_LIT(KEikLitBtpanCtlHkeyTabEnd, "<\\iTable>");

	aWriteStream << KEikLitBtpanCtlSt;
	aWriteStream << KEikLitBtpanCtlHkeyTab;

	const TInt count=iTable->Count();
	for(TInt i=0;i<count;i++)
		{
		const SEikHotKey& hkey=(*iTable)[i];
		aWriteStream.WriteInt32L(hkey.iCommandId);
		aWriteStream.WriteInt32L(hkey.iKeycode);
		}
	aWriteStream << KEikLitBtpanCtlHkeyTabEnd;
	aWriteStream << KEikLitBtpanCtlHkeyObs;
	aWriteStream.WriteInt32L((TInt)iObserver);
	aWriteStream << KEikLitBtpanCtlHkeyObsEnd;
	CCoeControl::WriteInternalStateL(aWriteStream);
	aWriteStream << KEikLitBtpanCtlEnd;
	}
#endif

TKeyResponse CEikHotKeyControl::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if (aType!=EEventKey)
        return(EKeyWasNotConsumed);
    TInt command=iTable->CommandIdFromHotKey(aKeyEvent.iCode,aKeyEvent.iModifiers&(EModifierCtrl|EModifierShift|EModifierPureKeycode));
    if (!command)
        return(EKeyWasNotConsumed);
    iObserver->ProcessCommandL(command);
    return(EKeyWasConsumed);
    }

CEikHotKeyControl::CEikHotKeyControl(CEikHotKeyTable* aTable,MEikCommandObserver* aObserver)
	: iTable(aTable),
    iObserver(aObserver)
    {
	MakeVisible(EFalse);
	}

CEikHotKeyControl::~CEikHotKeyControl()
    {
    delete(iTable);
    }
