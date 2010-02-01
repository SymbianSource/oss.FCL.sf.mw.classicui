// Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __TMULTIPTRTESTCONTROL_H__
#define __TMULTIPTRTESTCONTROL_H__


class CConeMultiPtrTestAppUi;
class CConeMultiPtrCompoundTestAppUi;
class CMultiPtrTestControlBase : public CCoeControl
    {
    
public:
	enum { EEventBufferSize = 256 };
	
    enum
	    {
	    EMultiPtrTestFailed,
	    EmultiPtrNext
	    };
    
public:
    void ConstructL();
    ~CMultiPtrTestControlBase();
    TInt EventsLeft();
    void AddExpectedEvent( TAdvancedPointerEvent& aPointerEvent );
    void CheckEventL( const TAdvancedPointerEvent& aExpectedEvent, const TAdvancedPointerEvent& aActualEvent );
    TBool Captures();
    void SetDrags();
    void SetGrabs();
    void SetPassive( TBool aPassive = ETrue );
    
    virtual void NotifyControlL( TInt aNotify ) = 0;
    // From CCoeControl
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);

protected:					
	// Specialised controls can derive from this class and gain access to these variables
	CCirBuf<TAdvancedPointerEvent> iEventBuffer;
	
private:
	TBool iPassive;
    };


class CMultiPtrTestControl : public CMultiPtrTestControlBase
	{
public:
	static CMultiPtrTestControl* NewL( TPoint aOrigin, TSize aSize );
	
	~CMultiPtrTestControl();
	// From CMultiPtrTestControlBase
	void NotifyControlL( TInt aNotify );
	
protected:
	CMultiPtrTestControl();
	void ConstructL( TPoint aOrigin, TSize aSize );
private:
	void Draw(const TRect& aRect) const;
	
private:
	CConeMultiPtrTestAppUi* iAppUi;
	};


/**
 Differs from CMultiPtrTestControl in the AppUi member.
*/
class CMultiPtrTestCompoundAppUiControl : public CMultiPtrTestControlBase
	{
public:
	static CMultiPtrTestCompoundAppUiControl* NewL( TPoint aOrigin, TSize aSize );
	
	~CMultiPtrTestCompoundAppUiControl();
	// From CMultiPtrTestControlBase
	void NotifyControlL( TInt aNotify );
	
protected:
	CMultiPtrTestCompoundAppUiControl();
	void ConstructL( TPoint aOrigin, TSize aSize );
private:
	void Draw(const TRect& aRect) const;
	
private:
	CConeMultiPtrCompoundTestAppUi* iAppUi;
	};
#endif // __TMULTIPTRTESTCONTROL_H__
