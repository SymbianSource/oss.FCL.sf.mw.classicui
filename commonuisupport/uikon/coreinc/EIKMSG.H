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

#ifndef __EIKMSG_H__
#define __EIKMSG_H__

#include <clock.h>
#include <gulalign.h>

#include <eikinfomsgwin.h>
#include <eikbusymsgwin.h>


class CCoeControl;
class CEikonEnv;
class RWindowGroup;
class CEikResourceChange;


/** Base class providing functions to construct and display an information message. 

@publishedAll
@released */
class CEikMsgWin : public CBase
	{
protected:
	IMPORT_C CEikMsgWin(CEikonEnv& aEikonEnv);
public:
	IMPORT_C void ConstructL(RWindowGroup& aWindowGroup);
	IMPORT_C virtual ~CEikMsgWin();
	IMPORT_C void StartDisplay(const TDesC& aText, TGulAlignment aCorner);
	IMPORT_C void CancelDisplay();
private:
	IMPORT_C virtual void CEikMsgWin_Reserved1();
	IMPORT_C virtual void CEikMsgWin_Reserved2();
protected:
	TDes& PrepareDisplay(TDes& aText, TGulAlignment aCorner);
private:
	virtual void DoStartDisplay(const TDesC& aText)=0;
protected:
	/** A CEikonEnv*, which all applications have. This is required for construction 
	of a CEikMsgWin as it provides access to services which the message window 
	needs, the window server session for example. */
	CEikonEnv& iEikonEnv_; // the underscore is to prevent a name clash with the iEikonEnv #define
	/** An empty control required for construction of a blank window. This defines 
	a handle back to the client side object, which is only required if you need 
	to later initiate client side drawing. */
	CCoeControl* iDummy;
	/** The window in which the message will be drawn. */
	RBlankWindow* iBlankWindow;
	/** An RAnim derived class, which is responsible for interacting with server side 
	classes to provide the message window's animation on the screen. It is constructed 
	by passing in the RWindowBase which it will use to draw its contents to, and 
	also a handle to an animation DLL, which provides the animation functionality. */
	RMessageWindow* iMessageWindow;
private:
	CEikResourceChange* iResourceChange;
	TInt iCEikMsgWin_Spare1;
	};

/**
@publishedAll
@released
*/
const TInt KEikInfoMsgMaxLen=RMessageWindow::EMaxTextLength;

/** Specifies the maximum length of the message buffer. 

@publishedAll
@released */
typedef TBuf<KEikInfoMsgMaxLen> TEikInfoMsgBuf;

class CEikInfoMsgWin : public CEikMsgWin, public MEikInfoMsgWin
/** Enables construction of an information message window. 

@publishedAll 
@released */
	{
public:
	IMPORT_C void ConstructL(RWindowGroup& aWindowGroup, TInt aParam = 0);
	IMPORT_C CEikInfoMsgWin(CEikonEnv& aEikonEnv);
public:  //from MEikInfoMsgWin
	IMPORT_C void StartDisplaySpecifyingDuration(const TDesC& aText, TGulAlignment aCorner, TTimeIntervalMicroSeconds32 aDuration);	
	IMPORT_C void StartDisplay(const TDesC& aText, TGulAlignment aCorner);
	IMPORT_C void CancelDisplay();
	IMPORT_C void Release();
private:
	virtual void DoStartDisplay(const TDesC& aText);
	IMPORT_C virtual void CEikInfoMsgWin_Reserved1();
	IMPORT_C virtual void CEikInfoMsgWin_Reserved2();
private: // From CEikMsgWin. do not override!
	IMPORT_C void CEikMsgWin_Reserved1();
	IMPORT_C void CEikMsgWin_Reserved2();
private:
	TInt iCEikInfoMsgWin_Spare1;
	};


/**
@publishedAll
@released
*/
const TInt KEikBusyMsgMaxLen=RMessageWindow::EMaxTextLength;

/**
@publishedAll
@released
*/
typedef TBuf<KEikBusyMsgMaxLen> TEikBusyMsgBuf;

/** 
@publishedAll 
@released
*/
class CEikBusyMsgWin : public CEikMsgWin, public MEikBusyMsgWin
	{
public:
	IMPORT_C void ConstructL(RWindowGroup& aWindowGroup);
	IMPORT_C CEikBusyMsgWin(CEikonEnv& aEikonEnv);
public:   //from MEikBusyMsgWin
	IMPORT_C void StartDisplaySpecifyingInitialDelay(const TDesC& aText, TGulAlignment aCorner, TTimeIntervalMicroSeconds32 aInitialDelay);
	IMPORT_C void StartDisplay(const TDesC& aText, TGulAlignment aCorner);
	IMPORT_C void Release();
private:
	IMPORT_C virtual void CEikBusyMsgWin_Reserved1();
	IMPORT_C virtual void CEikBusyMsgWin_Reserved2();
private: // From CEikMsgWin. do not override!
	IMPORT_C void CEikMsgWin_Reserved1();
	IMPORT_C void CEikMsgWin_Reserved2();
private:
	virtual void DoStartDisplay(const TDesC& aText);
private:
	TTimeIntervalMicroSeconds32 iInitialDelay;
	TInt iCEikBusyMsgWin_Spare1;
	};

#endif	// __EIKMSG_H__

