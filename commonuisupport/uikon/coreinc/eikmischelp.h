// Copyright (c) 2000-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef EIKMISCHELP_H
#define EIKMISCHELP_H


const TUid KEikBubbleHelpUid={0x10008E48};

class CCoeControl;

/**
The MEikTriggeredHelp class defines an interface for UI classes 
to implement triggered, transient help message display.
@publishedPartner
@deprecated
*/
class MEikTriggeredHelp	
	{
public:
	virtual void TriggerHelp(const TDesC& aDes,const TRect& aRect,TInt aHandle)=0;
	virtual void CancelHelp()=0;
	virtual void CancelHelpTrigger()=0;
	virtual TBool IsDisplayingHelp(TInt aHandle)=0;
	virtual void Release()=0;
protected:
	IMPORT_C virtual void MEikTriggeredHelp_Reserved_1();
	IMPORT_C virtual void MEikTriggeredHelp_Reserved_2();
	};

/**
The CEikBubbleHelp class implements global static storage and access to the object providing bubble help
for the application. 
@publishedPartner
@deprecated
*/
class CEikBubbleHelp : public CCoeStatic 
	{
	~CEikBubbleHelp();
public: 
	IMPORT_C static void SetTriggeredHelpL(MEikTriggeredHelp* aTriggeredHelp);
public:
	static void Trigger(const TDesC& aDes,const TRect& aRect,TInt aHandle=-1);
	static void Cancel();
	static void CancelTrigger();
	static TBool IsDisplaying(TInt aHandle);
private:
	inline CEikBubbleHelp();
	inline static CEikBubbleHelp* Self();
private:
	MEikTriggeredHelp* iHelp;
	};

inline CEikBubbleHelp::CEikBubbleHelp()
	: CCoeStatic(KEikBubbleHelpUid)
	{}

inline CEikBubbleHelp* CEikBubbleHelp::Self()
	{return STATIC_CAST(CEikBubbleHelp*,CCoeEnv::Static(KEikBubbleHelpUid));}

#endif	// EIKMISCHELP_H
