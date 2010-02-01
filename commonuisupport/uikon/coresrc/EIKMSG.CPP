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

#include <w32std.h>
#include <coecntrl.h>
#include <gulcolor.h>
#include <uikon.hrh>
#include <eikenv.h>
#include <eikmsg.h>
#include "EIKMSG.PAN"
#include <uiklaf/private/lafmsg.h>
#include <eikappui.h>
#include <e32std.h>
#include <eikpanic.h>

// global functions

GLDEF_C void Panic(TEikMsgWinPanic aPanic)
	{
	_LIT(KPanicCat,"EIKON-MSG-WIN");
	User::Panic(KPanicCat, aPanic);
	}

NONSHARABLE_CLASS(CEikResourceChange) : public CBase, public MCoeResourceChangeObserver
	{
public:
	static CEikResourceChange* NewL(RMessageWindow& aMessageWindow, CEikonEnv& aEnv);
private://from MCoeResourceObserver
	void HandleResourceChange();
private: 
	CEikResourceChange(RMessageWindow& aMessageWindow, CEikonEnv& aEnv);
private:
	RMessageWindow& iMessageWindow;
	CEikonEnv& iEnv;
	};


/**
@internalComponent
*/
CEikResourceChange::CEikResourceChange(RMessageWindow& aMessageWindow, CEikonEnv& aEnv)
	:iMessageWindow(aMessageWindow), iEnv(aEnv)
	{
	}
	
/**
@internalComponent
*/	
CEikResourceChange* CEikResourceChange::NewL(RMessageWindow& aMessageWindow, CEikonEnv& aEnv)
	{
	CEikResourceChange* self = new(ELeave) CEikResourceChange(aMessageWindow, aEnv);
	return self;
	}
	
/**
@internalComponent
*/
void CEikResourceChange::HandleResourceChange()
	{
	LafMsgWin::HandleResourceChange(iMessageWindow, iEnv.LafEnv());
	}

//
// CEikMsgWin
//

EXPORT_C CEikMsgWin::CEikMsgWin(CEikonEnv& aEikonEnv)
	:iEikonEnv_(aEikonEnv)
/** Protected constructor.

@param aEikonEnv The Uikon environment for which the information message is 
constructed. */
	{
	}

EXPORT_C void CEikMsgWin::ConstructL(RWindowGroup& aWindowGroup)
/** Completes construction.

@param aWindowGroup The window group for which the information message is 
constructed. */
	{
	iDummy = new(ELeave) CCoeControl;
	iDummy->SetNonFocusing();
	iBlankWindow = new(ELeave) RBlankWindow(iEikonEnv_.WsSession());
	User::LeaveIfError(iBlankWindow->Construct(aWindowGroup, (TUint32)iDummy));
	iBlankWindow->SetOrdinalPosition(0, ECoeWinPriorityAlwaysAtFront);
	LafMsgWin::SetUpBlankWindow(*iBlankWindow);
	RAnimDll& clockDll = iEikonEnv_.ClockDllL(); // ClockDllL cannot be called directly as a parameter to RMessageWindow below since ClockDllL may leave, in which case the unconstructed RMessageWindow object (which would have already been allocated on the stack, although not yet constructed) would be orphaned
	iMessageWindow = new(ELeave) RMessageWindow(clockDll, *iBlankWindow);
	LafMsgWin::CompleteMessageWinConstructionL(*iMessageWindow,iEikonEnv_.LafEnv());
	iBlankWindow->Activate();
	iResourceChange = CEikResourceChange::NewL(*iMessageWindow, iEikonEnv_);
	iEikonEnv_.AddResourceChangeObserverL(*iResourceChange);
	}

EXPORT_C CEikMsgWin::~CEikMsgWin()
/** Destructor. */
	{
	if (iResourceChange)
		{
		iEikonEnv_.RemoveResourceChangeObserver(*iResourceChange);
		delete iResourceChange;
		}
		
	if (iMessageWindow)
		iMessageWindow->Destroy();
	
	if (iBlankWindow)
		iBlankWindow->Destroy();
	
	delete iDummy;
	}


/**
Configures the message window, blank window and display text for specified alignment and display area.
@param aText The text to be displayed
@param aCorner Description of message window position.
@return Configured text
@internalTechnology
*/
TDes& CEikMsgWin::PrepareDisplay(TDes& aText, TGulAlignment aCorner)
	{
	LafMsgWin::TDisplayParameters params(aText);
	__ASSERT_DEBUG(iEikonEnv_.AppUi(),Panic(EEikPanicAppUiNotConstructed));
	params.iClientRect = static_cast<CEikAppUi*>(iEikonEnv_.AppUi())->ClientRect();
	iMessageWindow->GetBorders(params.iMsgWinBorders);
	params.iEnv = &iEikonEnv_;
	params.iDisplayCorner = aCorner;
	LafMsgWin::ConfigureText(params,iEikonEnv_.LafEnv());
	iBlankWindow->SetExtent(params.iMsgWinPosition, params.iMsgWinSize);
	iBlankWindow->SetOrdinalPosition(0);
	return params.iTextToDisplay;
	}

EXPORT_C void CEikMsgWin::StartDisplay(const TDesC& aText, TGulAlignment aCorner)
/** Displays the message window with the specified text and alignment.

@param aText The text to display in the message. 
@param aCorner The position in which the message window will appear. There 
are 9 options for this, each square of a 3 by 3 matrix on the screen. */
	{
	TBuf<RMessageWindow::EMaxTextLength> bufToModify=aText.Left(Min(aText.Length(), (TInt)RMessageWindow::EMaxTextLength));
	DoStartDisplay(PrepareDisplay(bufToModify,aCorner));
	}

EXPORT_C void CEikMsgWin::CancelDisplay()
/** Stops displaying the message window. */
	{
	iMessageWindow->CancelDisplay();
	}

EXPORT_C void CEikMsgWin::CEikMsgWin_Reserved1()
	{
	}
	
EXPORT_C void CEikMsgWin::CEikMsgWin_Reserved2()
	{
	}



//
// CEikInfoMsgWin
//

EXPORT_C CEikInfoMsgWin::CEikInfoMsgWin(CEikonEnv& aEikonEnv)
	:CEikMsgWin(aEikonEnv)
/** Constructs an information message for the specified Uikon environment.

@param aEikonEnv The Uikon environment for which the information message is 
constructed. */
	{
	}

EXPORT_C void CEikInfoMsgWin::ConstructL(RWindowGroup& aWindowGroup, TInt /*aParam*/)
/** Completes construction.

@param aWindowGroup The window group for which the information message is 
constructed. 
@param aParam An extra parameter */
	{
	CEikMsgWin::ConstructL(aWindowGroup);
	}

/**
Displays an information message window for a specified duration.

@param aText The text for the information message.
@param aCorner The alignment for the information message.
@param aDuration The time period for the information message.

@publishedPartner
@released
*/
EXPORT_C void CEikInfoMsgWin::StartDisplaySpecifyingDuration(const TDesC& aText, TGulAlignment aCorner, TTimeIntervalMicroSeconds32 aDuration)
	{
	TBuf<RMessageWindow::EMaxTextLength> bufToModify = aText.Left(Min(aText.Length(), (TInt)RMessageWindow::EMaxTextLength));
	iMessageWindow->StartDisplay(EFalse, 0, aDuration, PrepareDisplay(bufToModify,aCorner));
	}

/**
@param aText The text to be displayed 
@internalComponent
*/
void CEikInfoMsgWin::DoStartDisplay(const TDesC& aText)
	{
	iMessageWindow->StartDisplay(EFalse, 0, LafInfoMsgWin::DefaultDuration(), aText);
	}

/**
@publishedPartner
@released
*/
EXPORT_C void CEikInfoMsgWin::StartDisplay(const TDesC& aText, TGulAlignment aCorner)
	{
	CEikMsgWin::StartDisplay(aText, aCorner);	
	}

/**
@publishedPartner
@released
*/	
EXPORT_C void CEikInfoMsgWin::Release()
	{
	delete this;
	}

/**
@publishedPartner
@released
*/
EXPORT_C void CEikInfoMsgWin::CancelDisplay()
	{
	CEikMsgWin::CancelDisplay();	
	}

EXPORT_C void CEikInfoMsgWin::CEikInfoMsgWin_Reserved1()
	{
	}
	
EXPORT_C void CEikInfoMsgWin::CEikInfoMsgWin_Reserved2()
	{
	}

// From CEikMsgWin
EXPORT_C void CEikInfoMsgWin::CEikMsgWin_Reserved1()
	{
	}
	
EXPORT_C void CEikInfoMsgWin::CEikMsgWin_Reserved2()
	{
	}
	

// CEikBusyMsgWin
//

/**
Constructor.  Sets delay to laf default.
@param aEikonEnv 
*/
EXPORT_C CEikBusyMsgWin::CEikBusyMsgWin(CEikonEnv& aEikonEnv)
	:CEikMsgWin(aEikonEnv),
	 iInitialDelay(LafBusyMsgWin::DefaultInitialDelay())
	{
	}

EXPORT_C void CEikBusyMsgWin::ConstructL(RWindowGroup& aWindowGroup)
/** Completes construction.

@param aWindowGroup The window group for which the information message is 
constructed. */
	{
	CEikMsgWin::ConstructL(aWindowGroup);
	}

/**
@publishedPartner
@released
*/
EXPORT_C void CEikBusyMsgWin::StartDisplaySpecifyingInitialDelay(const TDesC& aText, TGulAlignment aCorner, TTimeIntervalMicroSeconds32 aInitialDelay)
	{
	__ASSERT_DEBUG(iInitialDelay==LafBusyMsgWin::DefaultInitialDelay(), Panic(EEikPanicMsgWinBadInitialDelay));
	iInitialDelay = aInitialDelay;
	CEikMsgWin::StartDisplay(aText, aCorner);
	iInitialDelay = LafBusyMsgWin::DefaultInitialDelay();
	}

/**
@internalComponent
@param aText The text to be displayed.
*/
void CEikBusyMsgWin::DoStartDisplay(const TDesC& aText)
	{
	iMessageWindow->StartDisplay(ETrue, iInitialDelay, aText);
	}
	
/**
@publishedPartner
@released
*/
EXPORT_C void CEikBusyMsgWin::StartDisplay(const TDesC& aText, TGulAlignment aCorner)
	{
	CEikMsgWin::StartDisplay(aText, aCorner);
	}
	
/**
@publishedPartner
@released
*/
EXPORT_C void CEikBusyMsgWin::Release()
	{
	delete this;
	}

EXPORT_C void CEikBusyMsgWin::CEikBusyMsgWin_Reserved1()
	{
	}
	
EXPORT_C void CEikBusyMsgWin::CEikBusyMsgWin_Reserved2()
	{
	}

// From CEikMsgWin
EXPORT_C void CEikBusyMsgWin::CEikMsgWin_Reserved1()
	{
	}
	
EXPORT_C void CEikBusyMsgWin::CEikMsgWin_Reserved2()
	{
	}

