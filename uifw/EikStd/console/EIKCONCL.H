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


#if !defined(__EIKCONCL_H__)
#define __EIKCONCL_H__

#if !defined(__E32CONS_H__)
#include <e32cons.h>
#endif

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

class CEikConsoleScreen;

typedef const TAny* CATP;

class CEikConsoleClient : public CConsoleBase
	{
public:
	~CEikConsoleClient();
public: // from CConsoleBase
	void Read(TRequestStatus& aStatus);
	void ReadCancel();
	void Write(const TDesC& aDes);
	TPoint CursorPos() const;
	void SetCursorPosAbs(const TPoint& aPoint);
	void SetCursorPosRel(const TPoint& aPoint);
	void SetCursorHeight(TInt aPercentage);
	void SetTitle(const TDesC& aTitle);
	void ClearScreen();
	void ClearToEndOfLine();
	TSize ScreenSize() const;
	TKeyCode KeyCode() const;
	TUint KeyModifiers() const;
private:
	friend TAny* NewConsole();
	CEikConsoleClient();
private: // from CConsoleBase
	TInt Create(const TDesC& aTitle,TSize aSize);
private: // internal use only
	void SendReceive(TInt aMessage,const TAny* aParam);
	inline void SendReceive(TInt aMessage,TInt aParam) { SendReceive(aMessage,(const TAny*)aParam); }
private:
	friend class CEikConsMessager;
	RThread iThread;
	TRequestStatus iLogonStatus;
	TRequestStatus* iThreadStatus;
	TInt* iMessage;
	CATP* iParam;
	TRequestStatus** iReplyStatus;
	TKeyEvent iKeyEvent;
	CEikConsoleScreen* iScreen;
	};

#endif
