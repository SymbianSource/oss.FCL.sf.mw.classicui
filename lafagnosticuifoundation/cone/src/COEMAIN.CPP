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

#include <f32file.h>
#include <s32stor.h>
#include <s32file.h>
#include <coemain.h>
#include "coepriv.h"
#include "COETLS.H"
#include "COEFEP.H"		// class FepName
#include "coepanic.h"
#include "COEVER.H"
#include <coecntrl.h>
#include <coeerror.h>
#include "coeenvextra.h"
#include <barsread.h>
#include <bautils.h>
#include <viewcli.h>
#include <coeaui.h>
#include <hal.h>
#include "CoeDataStorage.h"
#include <coefontprovider.h>
#include <centralrepository.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <viewclipartner.h>
#endif
#include "coescheduler.h"
#include "coeerrorconsts.h"
#include "coedefkeys.h"


//#define CONE_SHOW_TRACE			

#ifdef CONE_SHOW_TRACE
void ShowTrace(TRefByValue<const TDesC> aFmt,...)
	{
	RDebug::Print(aFmt);
	}
#else
void ShowTrace(TRefByValue<const TDesC> /*aFmt*/,...)
	{
	}
#endif

/**
ROM-patchable constant for turning the automatic setting of the CCoeControl's
parent-pointer on or off. Only available in Symbian OS 9.3 and 9.4.
@publishedPartner
*/
//#if !defined(SYMBIAN_WSERV_AND_CONE_MULTIPLE_SCREENS)
EXPORT_C extern const TInt KCoeSetControlParentByDefault = ETrue;	// Used in CCoeControlStaticSettings::ParentByDefault()
//#endif

_LIT(KSystemFont,"Arial");

const TInt KDefaultScreenNumber = 0 ; // If no startup screen is defined at construction use this.

GLDEF_C void Panic(TCoePanic aPanic)
	{
	_LIT(KPanicCone,"CONE");
	User::Panic(KPanicCone,aPanic);
	}


LOCAL_C TBool IsHandleValid(TUint aHandle)
	{
	return (aHandle&3)==0;
	}

//
// Synchronously notifies focus observers of a focus change so
// they can be reset after they receive a focus change event 
// 
// @since	6.1
//
EXPORT_C void CCoeEnv::SyncNotifyFocusObserversOfChangeInFocus()
	{
	iExtra->iHighPriorityActive->NotifyFocusObserversOfChangeInFocus();
	iExtra->iHighPriorityActive->Cancel();
	}


//
// Class CCoeScheduler
//

EXPORT_C CCoeScheduler::CCoeScheduler(CCoeEnv* aCoeEnv)
/** Constructor taking a pointer to the control environment.

@param aCoeEnv The control environment. */
	{
	iCoeEnv=aCoeEnv;
	iFlush=ETrue; // Set the default flushing behaviour to flush automatically
	}

EXPORT_C void CCoeScheduler::WaitForAnyRequest()
/** Waits for an asynchronous request to complete. */
	{
	iCoeEnv->DoFlush();
	CBaActiveScheduler::WaitForAnyRequest();
	}

EXPORT_C void CCoeScheduler::DisplayError(TInt aError) const
/** Displays an application-defined error message.

@param aError An error code. */
	{
	iCoeEnv->HandleError(aError);
	}

TBool CCoeScheduler::Flush() const
	{
	return iFlush;
	}

void CCoeScheduler::SetFlush(TBool aFlush)
	{
	iFlush=aFlush;
	}

EXPORT_C void CCoeScheduler::Reserved_1()
	{
	}

EXPORT_C void CCoeScheduler::Reserved_2()
	{
	}

//
// Class CCoeEnv
//
EXPORT_C TBool CCoeEnv::DisableShutdownChecks() const
	{
	return iEnvFlags&ENoShutdownChecks;
	}
	
inline TUint CCoeEnv::InitialHandleCount() const
	{return (iEnvFlags&0xffff0000)>>16;}

TInt CCoeEnv::SupportedPointers() const
	{
	return iExtra->iSupportedPointers;
	}

const TInt KErrorContextTextLength=80;
const TInt KErrorTextLength=80;

EXPORT_C CCoeEnv::CCoeEnv() : CActive(EActivePriorityWsEvents)
/** Default constructor.

Note - Construction of the CCoeEnv is not complete 
until ConstructL() has been called.

This function raises a CONE 2 panic if the application already owns a CCoeEnv. */
	{
	TInt error=KErrNone;
#ifdef _DEBUG
	HAL::SEntry* pE=NULL;
	TInt entries=0;
	if (error==KErrNone)
		error=HAL::GetAll(entries, pE);
	
	User::Free(pE);
	SetInitialHandleCount();
#endif
	__ASSERT_ALWAYS(!TheCoe(),Panic(ECoePanicEnvironmentAlreadyExists));
	if (error==KErrNone)
		error=SetTheCoe(this);
	__UHEAP_MARK;
	
	iCleanup=CTrapCleanup::New();
	if ((iCleanup==NULL) && (error==KErrNone))
		error=KErrNoMemory;
		
	if (error!=KErrNone)
		{
		iExtra=REINTERPRET_CAST(CCoeEnvExtra*, error);
		iEnvFlags|=EExtraPointerIsErrorCode;
		}
	}

EXPORT_C void CCoeEnv::ExecuteD()
/** Launches the application and destroys the control environment. */ 
	{
	Execute();
	DestroyEnvironment();
	}

EXPORT_C void CCoeEnv::Execute()
/** Launches the application without destroying the control environment. 

This function starts the active scheduler owned by the CCoeEnv, enabling the 
application to start receiving events from the window server. It forms the 
outer loop of all Control Environment applications. */
	{
	iEnvFlags|=ESchedulerIsRunning;
	TRAPD(exitCondition,CActiveScheduler::Start());
	__ASSERT_ALWAYS((exitCondition==KLeaveExit) || (exitCondition==KErrNone), Panic(ECoePanicLeaveWithoutTrap));
	PrepareToExit();
	}

EXPORT_C void CCoeEnv::PrepareToExit()
/** Prepares for exiting the application. 

The function is called from ExecuteD() after the active scheduler's wait loop 
terminates, but before the environment is destroyed. */
	{
	if (iAppUi)
		iAppUi->PrepareToExit();
	}

EXPORT_C void CCoeEnv::RunL()
	{
	switch (iStatus.Int())
		{
	case KErrNone:
		break;
	case KErrCancel:
	case KErrServerTerminated:
		return;
	default:
		Panic(ECoePanicWservBlindCommandFailed);
		}
	TWsEvent event;
	iWsSession.GetEvent(event);
	RequestEventNotification();		//Request now so that WSERV has time to respond (on SMP systems) before the return to the Active Scheduler
	const TUint handle=event.Handle();
	if (handle)
		{
		CCoeControl* const window=IsHandleValid(handle)? reinterpret_cast<CCoeControl*>(handle) : NULL;
		iLastEvent=event;
		iAppUi->MonitorWsEvent(event);
		//coverity[var_deref_model]
		//Passing a NULL value of window to this function is allowed because the window is not always dereferenced by this function. 
		//The window will not be NULL if it is to be dereferenced by this function. 
		iAppUi->HandleWsEventL(event,window);
		}
	}

EXPORT_C void CCoeEnv::SimulateKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
/** Simulates a key event.

This function calls CCoeAppUi::HandleWsEventL() to process the event 
as if it had arrived from the window server.

@param aKeyEvent The key event.
@param aType The event type. */
	{
	TWsEvent event;
	*event.Key()=aKeyEvent;
	event.SetType(aType);
	event.SetTimeNow();
	iLastEvent=event;
	iAppUi->HandleWsEventL(event,NULL);
	}

EXPORT_C void CCoeEnv::DoCancel()
	{
	iWsSession.EventReadyCancel();
	}

EXPORT_C void CCoeEnv::SuppressNextFlush()
/** Suppresses the next flush of the active scheduler queue. 

It prevents the active scheduler automatically flushing its window server 
session the next time that a non-CCoeEnv object runs. After the active object 
has run, the active scheduler reverts back to its normal behaviour, flushing 
after each non-CCoeEnv RunL(). */
	{
	static_cast<CCoeScheduler*>(CActiveScheduler::Current())->SetFlush(EFalse);
	}

void CCoeEnv::DoFlush()
/** Flush WSERV's command buffer */
	{
	CCoeScheduler* coeScheduler=static_cast<CCoeScheduler*>(CActiveScheduler::Current());
	if (coeScheduler->Flush())
		iWsSession.Flush();
	else
		coeScheduler->SetFlush(ETrue);
	}

void CCoeEnv::RequestEventNotification()
/** Asks WSERV to give notification when an event is waiting */
	{
	iWsSession.EventReady(&iStatus);
	SetActive();
	}

CVwsSessionWrapper* CCoeEnv::InitViewServerSessionL(MVwsSessionWrapperObserver& aObserver)
	{
	if (!(iExtra->iVwsSession))
		{
		iExtra->iVwsSession=CVwsSessionWrapper::NewL(aObserver);
		}
	return iExtra->iVwsSession;
	}

EXPORT_C void CCoeEnv::HandleError(TInt /*aErrorValue*/)
/** Handles an application-defined error message.

This function allows application-defined error messages to be called from 
functions within the control framework's active scheduler. It has an empty 
default implementation.

It is called when a leave occurs in CCoeEnv::RunL(), and also when ReadResource() 
fails.

@param aErrorValue KErrNone or another error code. */
	{
	}

EXPORT_C void CCoeEnv::BringOwnerToFront()
/** Brings the application's owning window group to the front of the screen and 
gives it keyboard focus. 

This is done by giving the owning window group an ordinal position of zero. */
	{
	if (iRootWin.WsHandle()) // else initialization hasn't got that far yet
		iRootWin.SetOrdinalPosition(KOrdinalPositionSwitchToOwningWindow);
	}

EXPORT_C void CCoeEnv::DestroyEnvironment()
/** Deletes several resources owned by the CCoeEnv object.

This includes; the app UI, the system graphics context, and the active object 
which receives redraw events. It also closes the window group, the connection 
to the window server, and the connection to the file server.

The function is called from ExecuteD() when the active scheduler's wait loop 
terminates. */
	{
	iExtra->iControlState = EFalse;
	DestroyEnvironmentStatic();
	DestroyEnvironmentEnd();
	delete this;
	}
	
/** @internalTechnology */
EXPORT_C void CCoeEnv::DestroyEnvironmentStatic()
	{
	BringOwnerToFront();
	const TBool extraIsNonNull=(!(iEnvFlags&EExtraPointerIsErrorCode) && (iExtra!=NULL));
	if (extraIsNonNull)
		{
		CCoeEnvExtra::DestroyFep(iExtra->iFep);

		// Delete all CCoeStatics with positive destruction priority
		TDblQueIter<CCoeStatic> iter(iExtra->iCoeStaticList);
		iter.SetToFirst();
		CCoeStatic* coeStatic = NULL;
		while (((coeStatic=iter++)!=NULL) && (coeStatic->DestructionPriority()>=0))
			{
			delete coeStatic;
			}
		}
	}	
	
/** @internalTechnology */
EXPORT_C void CCoeEnv::DestroyEnvironmentEnd()
	{
	const TBool extraIsNonNull=(!(iEnvFlags&EExtraPointerIsErrorCode) && (iExtra!=NULL));	
	delete(iAppUi); // must be destroyed before the iExtra observers
	iAppUi=NULL;
	if (extraIsNonNull)
		{
		delete iExtra->iFepTracker; // this must be deleted *before* the CCoeDataStorage object - the latter is deleted by one of the CCoeStatic objects (with negative destruction priority) below

		// Delete all CCoeStatics with negative destruction priority
		TDblQueIter<CCoeStatic> iter(iExtra->iCoeStaticList);
		iter.SetToFirst();
		CCoeStatic* coeStatic = NULL;
		while ((coeStatic=iter++)!=NULL)
			{
			delete coeStatic;
			}
		DeleteArrayOfScreensItems();
		delete iExtra->iRedrawer;
		delete iExtra->iFepLoader;
		delete iExtra->iVwsSession;
		delete iExtra->iDefaultFontProvider; 
		delete iExtra->iDefaultTextDrawer;
		}
	delete(iSystemGc);
	ReleaseScreenFont(CONST_CAST(CFont*,iNormalFont));
	DestroyScreen(); // this is a virtual function so it must be called here rather than in CCoeEnv's destructor
	iRootWin.Close();
	Cancel();
	}

#if defined(_DEBUG)

template <class T, class R>
TInt FindAllThreadHandles(T& aFindHandle)
	{
	_LIT(KFormatString,"%S::*");
	RThread t;
	TFullName name;
	const TFullName threadName=t.FullName();
	name.Format(KFormatString,&threadName);
	aFindHandle.Find(name);
	TInt count=0;
	FOREVER
		{
		const TInt r=aFindHandle.Next(name);
		if (r!=KErrNone)
			break;
		count++;
		ShowTrace(_L("%S"), &name);
		}
	return count;
	}

void IdentifyOpenHandles1()
	{
	TFindSemaphore sem;
	ShowTrace(_L("Finding open semaphores..."));
	FindAllThreadHandles<TFindSemaphore, RSemaphore>(sem);
	}

void IdentifyOpenHandles2()
	{
	TFindMutex mux;
	ShowTrace(_L("Finding open mutexes..."));
	FindAllThreadHandles<TFindMutex, RMutex>(mux);
	}

void IdentifyOpenHandles3()
	{
	TFindChunk fchunk;
	ShowTrace(_L("Finding open chunks..."));
	FindAllThreadHandles<TFindChunk, RChunk>(fchunk);
	}

void IdentifyOpenHandles4()
	{
	TFindLogicalDevice fldev;
	ShowTrace(_L("Finding open logical devices..."));
	FindAllThreadHandles<TFindLogicalDevice, RDevice>(fldev);
	}

LOCAL_C void IdentifyOpenHandles()
	{
	ShowTrace(_L("Open handles found during thread %Lu shutdown"), RThread().Id().Id()); // %Lu is used for a TUint64
	IdentifyOpenHandles1();
	IdentifyOpenHandles2();
	IdentifyOpenHandles3();
	IdentifyOpenHandles4();
	ShowTrace(_L("Finished attempts to identify handles"));
	Panic(ECoePanicHandleNotClosed);
	}

#endif

EXPORT_C CCoeEnv::~CCoeEnv()
/** Destructor. 

This function deletes any resources owned by the CCoeEnv that were not deleted 
by DestroyEnvironment(). */
	{
	if (!(iEnvFlags&EExtraPointerIsErrorCode) && (iExtra!=NULL))
		{
		delete iExtra->iHighPriorityActive;
#if defined(_DEBUG)
		if (iResourceFileArray!=NULL)
			{
			for (TInt i=iResourceFileArray->Count()-1; i>=0; --i)
				{
				ShowTrace(_L("Resource file with offset 0x%08x has been leaked (search for the 4 most significant hexadecimal digits of this number in epoc32\\include\\*.RSG to find out which resource file)"), (*iResourceFileArray)[i].Offset());
				}
			__ASSERT_DEBUG(iResourceFileArray->Count()==0,Panic(ECoePanicResourceFileNotDeleted));
			}
#endif
		__ASSERT_DEBUG(iExtra->iResFileAccessCount.Count()==0,Panic(ECoePanicResourceFileNotDeleted));
		iExtra->iResFileAccessCount.Close();
		delete iExtra; // can only be done when iAppUi has been destroyed as destroying iAppUi may destroy some controls owned by the control stack, and these controls may call SetFocus when they are destroyed, SetFocus internally referencing iExtra->iNumberOfNestedSetFocusCalls
		}
	DestroyAllResourceFiles();
	delete iScreen;
	delete CActiveScheduler::Current();
	delete iErrorText;
	delete iErrorContextText;
	delete iCleanup;
	__ASSERT_DEBUG(DisableShutdownChecks() || (iWsSession.Handle()==KNullHandle) || (iWsSession.ResourceCount()==0),Panic(ECoePanicWservResourceNotFreed));
	iWsSession.Close();
	// Checks that less than 1 file is open. 1 file may be open because the RFbs keeps one file cached.
	// A defect has been raised to change this.
	__ASSERT_DEBUG(DisableShutdownChecks() || (iFsSession.Handle()==KNullHandle) || (iFsSession.ResourceCount()<=1),Panic(ECoePanicF32ResourceNotFreed));
	iFsSession.Close();
	REComSession::FinalClose();
#if defined(_DEBUG)
	if (!DisableShutdownChecks())
		{
		__UHEAP_MARKEND;
		TInt processHandleCount=0;
		TInt threadHandleCount=0;
		RThread().HandleCount(processHandleCount,threadHandleCount);
		const TInt initialHandleCount=InitialHandleCount();
		if (threadHandleCount>initialHandleCount && initialHandleCount<KMaxTInt16)
			{
			IdentifyOpenHandles();
			}
		}
#endif
	FreeTheCoe();
	}

EXPORT_C void CCoeEnv::DestroyScreen()
/** Destroys the screen device.

By default this function simply deletes the screen device owned by this CCoeEnv. 
However, this function may be overridden by subclasses.

This function is called by DestroyEnvironment(). */
	{ // subclassers can do more
	}

EXPORT_C CCoeAppUi* CCoeEnv::SetAppUi(CCoeAppUi* aAppUi)
/** Sets the application's user interface object.

Standard GUI applications do not need to call this function, as the framework 
sets the app UI, during start up, to be the CEikAppUi-derived object created 
by the application.

@param aAppUi The app UI for this application.
@return The app UI previously owned by this application, or NULL if this is 
the first time its app UI has been set. */
	{
	CCoeAppUi* previous=iAppUi;
	iAppUi=aAppUi;
	if (previous==NULL) // i.e. we've only just set the app ui for the first time
		{
		UpdateStatic(aAppUi);
		}
	return(previous);
	}

EXPORT_C void CCoeEnv::ConstructL()
/** Completes construction of the CCoeEnv object.

It calls the other ConstructL() overload specifying ETrue as the initial 
focus state. */
	{
	ConstructL(ETrue);
	}

EXPORT_C void CCoeEnv::ConstructL(TBool aInitialFocusState)
/** Completes construction of the CCoeEnv. 

It is called by the other overload, with aInitialFocusState set to ETrue.


@param aInitialFocusState Window group initial focus state. If ETrue, keyboard 
focus is enabled, otherwise keyboard focus is disabled. */
	{
	ConstructL( aInitialFocusState, KDefaultScreenNumber ) ;
	}

/** Completes construction of the CCoeEnv. 
It can be called by the previous overload.  It calls the next overload, setting
the default window group ID to 0 which is not a valid ID

@param aInitialFocusState Window group initial focus state. If ETrue, keyboard 
focus is enabled, otherwise keyboard focus is disabled. 
@param aDefaultScreenNumber The default screen number should be zero.*/
EXPORT_C void CCoeEnv::ConstructL( TBool aInitialFocusState, TInt aDefaultScreenNumber ) // Added May 04 support for Multiple Screens

	{
	ConstructL(aInitialFocusState, aDefaultScreenNumber, 0); // 0 is not a valid window group ID
	}

/** Completes construction of the CCoeEnv. 

All of the previous ConstructL() overloads end up at this method.

This function creates an active scheduler, and adds active objects to it for 
standard and redraw events. The active scheduler is not started, however, 
and no events are received, until ExecuteD() is called. It also does the following:

- creates a connection to the window server.

- creates a connection to the file server so that the control environment can 
access resource files

- creates a screen device, the application's window group, a standard font, 
and a graphics context (the system GC).

The window group is constructed with the initial focus state aInitialFocusState, 
which automatically takes keyboard focus when it is created. 

@param aInitialFocusState Window group initial focus state. If ETrue, keyboard 
focus is enabled, otherwise keyboard focus is disabled. 
@param aDefaultScreenNumber The default screen number 
@param aWindowGroupID The window group ID which will be set as the parent
*/
EXPORT_C void CCoeEnv::ConstructL(TBool aInitialFocusState, TInt aDefaultScreenNumber, TInt aWindowGroupID )
	{
	if (iEnvFlags&EExtraPointerIsErrorCode)
		{
		User::LeaveIfError(REINTERPRET_CAST(TInt, iExtra));
		}
	iExtra=new(ELeave) CCoeEnvExtra;
	iExtra->ConstructL();
	iErrorText=new(ELeave) TBuf<KErrorTextLength>;
	iErrorContextText=new(ELeave) TBuf<KErrorContextTextLength>;
	CreateActiveSchedulerL();
	CActiveScheduler::Add(this);
	ConnectToFileServerL();
	ConnectToWindowServerL();
	InitScreenL( aDefaultScreenNumber); // Modified May 04 support for Multiple Screens.
	InitRootWindowL(aInitialFocusState, aWindowGroupID);
	InitSystemFontsL();
	InitSystemGcL();
	PopulateArrayOfScreenItemsL();
	iExtra->iRedrawer=new(ELeave) CCoeRedrawer(iWsSession);
	iExtra->iFepTracker=CCoeFepTracker::NewL(*this);
	iExtra->iFepLoader=CCoeFepLoader::NewL(*this, iExtra->iFepLoader);
	iExtra->iHighPriorityActive=CCoeEnvExtra::CHighPriorityActive::NewL(*iExtra);

	iExtra->iDefaultFontProvider = CCoeFontProvider::NewL();
	User::LeaveIfNull( iExtra->iDefaultTextDrawer = CCoePlainTextDrawer::New(KRgbBlack) );
	iExtra->iDefaultTextDrawer->SetReusable( ETrue );
	// iExtra->iAppStartupInstrumentationEventIdBase is set in SetAppStartupInstrumentationEventIdBaseL
	RequestEventNotification();
	}

void CCoeEnv::CreateActiveSchedulerL()
	{
	CActiveScheduler::Install(new(ELeave) CCoeScheduler(this));
	}

void CCoeEnv::ConnectToFileServerL()
	{
	User::LeaveIfError(iFsSession.Connect());
	}

void CCoeEnv::ConnectToWindowServerL()
	{
	User::LeaveIfError(iWsSession.Connect(iFsSession));
	}

void CCoeEnv::InitScreenL( TInt aDefaultScreenNumber )
	{
	iScreen=new(ELeave) CWsScreenDevice(iWsSession);
	User::LeaveIfError(iScreen->Construct( aDefaultScreenNumber ));
	}

void CCoeEnv::InitRootWindowL(TBool aInitialFocusState, TInt aWindowGroupID)
	{
	iRootWin=RWindowGroup(iWsSession);
	if (aWindowGroupID)
		{
		User::LeaveIfError(iRootWin.ConstructChildApp(aWindowGroupID, (TUint32)this, aInitialFocusState));
		}
	else
		{
		User::LeaveIfError(iRootWin.Construct((TUint32)this, aInitialFocusState));
		}
	}

EXPORT_C void CCoeEnv::InitSystemFontsL()
// Hard-coded font is only used for test code
/** Initialises the system fonts.

This function is called by ConstructL() during the construction of a CCoeEnv. 
The default implementation creates only the normal control environment font, 
but this function may be overridden to create other fonts. */
	{ 
	TFontSpec spec(KSystemFont,200); // 10 points
	iNormalFont=CreateScreenFontL(spec);
	}

void CCoeEnv::InitSystemGcL()
	{
	iSystemGc=CreateGcL();
	}

EXPORT_C CWindowGc* CCoeEnv::CreateGcL()
/** Fully constructs a new graphics context.

CCoeEnv calls this function during construction to create the system graphics 
context, which can be accessed using SystemGc(). Hence the system graphics 
context is always available.

@return A new graphics context.
@see SystemGc() */
	{
	CGraphicsContext* temp;
	User::LeaveIfError(iScreen->CreateContext(temp));
	return((CWindowGc*)temp);
	}

EXPORT_C CFbsFont* CCoeEnv::CreateDeviceFontL(CGraphicsDevice* aDevice,const TFontSpec& aFontSpec)
/** Creates a font for the specified graphics device. 

If you wish to use the default screen device as the graphics device, use 
CreateScreenFontL()  instead of this function.

This function calls GetNearestFontToMaxHeightInTwips() on the graphics device 
given by aDevice, passing it the font defined by aFontSpec.

All fonts created by this function should be released using 
MGraphicsDeviceMap::ReleaseFont(), when they are no longer required.

Note that the font will not be scaled automatically when the control's zoom factor 
is changed using CCoeControl::SetZoomFactor(). This is also the case for NormalFont(), 
CEikonEnv::LegendFont(), CEikonEnv::TitleFont(), CEikonEnv::AnnotationFont(), 
CEikonEnv::DenseFont().

To avoid this problem, and also make resource management much easier, it is highly 
recommended to use CCoeControl::ScreenFont() instead.

@see CCoeEnv::CreateScreenFontL()
@see CCoeControl::ScreenFont()
@see CCoeFontProvider

@param aDevice The graphics device for which to create the font.
@param aFontSpec The font specification.
@return The new font. */
	{
	CFont* ret;
	User::LeaveIfError(aDevice->GetNearestFontToMaxHeightInTwips(ret,aFontSpec,aFontSpec.iHeight));
	return((CFbsFont*)ret);
	}

EXPORT_C CFbsFont* CCoeEnv::CreateScreenFontL(const TFontSpec& aFontSpec)
/** Creates a font for the default graphics device, based on the specified TFontSpec. 

All fonts created using this function should be released using ReleaseScreenFont() 
when they are no longer required.
 
Note that the font will not be scaled automatically when the zoom factor is changed 
using CCoeControl::SetZoomFactor(). This is also the case for NormalFont(), 
CEikonEnv::LegendFont(), CEikonEnv::TitleFont(), CEikonEnv::AnnotationFont(), 
CEikonEnv::DenseFont().

To avoid this problem, and also make resource management much easier, it is highly 
recommended to use CCoeControl::ScreenFont() instead.

@see CCoeControl::ScreenFont()
@see CCoeFontProvider

@param aFontSpec The font specification.
@return The new font. */
	{
	return(CreateDeviceFontL(iScreen,aFontSpec));
	}

EXPORT_C void CCoeEnv::ReleaseScreenFont(CFont* aFont) const
/** Frees all resources used by the font. 

This function should be used to release a font when the font is no longer 
required. Fonts are created using CreateScreenFontL().

@param aFont The font to be released. */
	{
	if (aFont)
		iScreen->ReleaseFont(aFont);
	}

EXPORT_C void CCoeEnv::Flush(TTimeIntervalMicroSeconds32 aDelay)
/** Flushes the client-side window server buffer. 

The function does this by first calling RWsSession::Flush(), and then User::After(aDelay), 
which puts the current process in a sleep state for the time interval 
given by aDelay.

@param aDelay Delay for which to sleep the current process after flushing 
the window server buffer. By default the delay is zero. */
	{
	iWsSession.Flush();
	User::After(aDelay);
	}

EXPORT_C TBool CCoeEnv::IsWservEventPending() const
/** Tests if there is a standard event waiting to be processed. 

Note: standard events are all window server events except redraw and priority 
key events.

@return ETrue if a standard event is pending. EFalse if no standard event 
is pending. */
	{
	return(iStatus.Int()!=KRequestPending);
	}

EXPORT_C TBool CCoeEnv::IsRedrawEventPending() const
/** Tests if there is a redraw event waiting to be processed.

@return ETrue if a redraw event is pending. EFalse if no redraw event is pending. */
	{
	return(iExtra->iRedrawer->iStatus.Int()!=KRequestPending);
	}

EXPORT_C void CCoeEnv::ReadResourceAsDes8(TDes8& aDes,TInt aResourceId) const
/** Reads a resource into an 8 bit descriptor. 

The descriptor must be long enough to contain the entire resource. No memory 
is allocated by this function.

If the read fails the function sets an error condition and performs any cleanup 
required. The error condition causes the GUI to launch an alert window.
Deprecated: use CCoeEnv::ReadResourceAsDes8L() instead.

@deprecated
@param aDes On return, contains the read resource.
@param aResourceId The numeric ID of the resource to be read.
@see RResourceFile::ReadL()
@see KErrCoeFailedToReadFromProgDisk */
	{
	aDes.Zero();
	RResourceFile& rf=ResourceFileForId(aResourceId);
	TRAPD(err,rf.ReadL(aDes,aResourceId));
	if (err==KErrNoMemory)
		{
		CBaActiveScheduler::DisplayExtendedError(KUidConeDll,KErrNoMemory);
		}
 	else if (err!=KErrNone)
		{
		CBaActiveScheduler::DisplayExtendedError(KUidConeDll,KErrCoeFailedToReadFromProgDisk);
		}
	}

EXPORT_C void CCoeEnv::ReadResourceAsDes8L(TDes8& aDes,TInt aResourceId) const
/** Reads a resource into an 8 bit descriptor.

The descriptor must be long enough to contain the entire resource. 
The method leaves if an error occurs when reading from the resource file.

@param aDes On return, contains the read resource.
@param aResourceId The numeric ID of the resource to be read. */
	{
	RResourceFile& rf=ResourceFileForId(aResourceId);
	rf.ReadL(aDes,aResourceId);
	}

EXPORT_C void CCoeEnv::ReadResourceAsDes16(TDes16& aDes,TInt aResourceId) const
/** Reads a resource into a 16 bit descriptor. 

The descriptor must be long enough to contain the entire resource. No memory 
is allocated by this function.

If the read fails the function sets an error condition and performs any cleanup 
required. The error condition causes the GUI to launch an alert window.
Deprecated: use CCoeEnv::ReadResourceAsDes16L() instead.

@deprecated
@param aDes On return, contains the read resource.
@param aResourceId The numeric ID of the resource to be read.
@see RResourceFile::ReadL()
@see KErrCoeFailedToReadFromProgDisk */
	{
	aDes.Zero();
 // Reading Unicode string
	RResourceFile& rf=ResourceFileForId(aResourceId);
	TPtr8 readBuffer((TText8* ) aDes.Ptr(),aDes.MaxSize());
	TRAPD(err,rf.ReadL(readBuffer,aResourceId));
	__ASSERT_DEBUG((readBuffer.Length()%2)==0||(err==KErrNone),Panic(ECoePanicWrongResourceFormat));
	aDes.SetLength((readBuffer.Length()+1)>>1);

	if (err==KErrNoMemory)
		{
		CBaActiveScheduler::DisplayExtendedError(KUidConeDll,KErrNoMemory);
		}
	else if (err!=KErrNone)
		{
		CBaActiveScheduler::DisplayExtendedError(KUidConeDll,KErrCoeFailedToReadFromProgDisk);
		}
	}

EXPORT_C void CCoeEnv::ReadResourceAsDes16L(TDes16& aDes,TInt aResourceId) const
/** Reads a resource into a 16 bit descriptor.

The descriptor must be long enough to contain the entire resource. 
The method leaves if an error occurs when reading from the resource file.

@param aDes On return, contains the read resource.
@param aResourceId The numeric ID of the resource to be read. */
	{
	RResourceFile& rf=ResourceFileForId(aResourceId);
	TPtr8 readBuffer((TText8* ) aDes.Ptr(),aDes.MaxSize());
	rf.ReadL(readBuffer,aResourceId);
 	__ASSERT_DEBUG((readBuffer.Length()%2)==0,Panic(ECoePanicWrongResourceFormat));
	aDes.SetLength((readBuffer.Length()+1)>>1);
	}

EXPORT_C HBufC8* CCoeEnv::AllocReadResourceAsDes8L(TInt aResourceId) const
/** Reads a resource into an 8 bit heap buffer, allocating the buffer. 

The calling program must destroy the heap descriptor when it is no longer 
needed.

@param aResourceId The numeric ID of the resource to be read.
@return Pointer to a heap descriptor containing the resource data.
@see RResourceFile::AllocReadL() */
	{
	RResourceFile& rf=ResourceFileForId(aResourceId);
	return(rf.AllocReadL(aResourceId));
	}

EXPORT_C HBufC16* CCoeEnv::AllocReadResourceAsDes16L(TInt aResourceId) const
/** Reads a resource into a 16 bit heap buffer, allocating the buffer. 

The calling program must destroy the heap descriptor when it is no longer 
needed.

@param aResourceId The numeric ID of the resource to be read.
@return Pointer to a heap descriptor containing the resource data. */
	{
	RResourceFile& rf=ResourceFileForId(aResourceId);
	HBufC8* readBuffer=rf.AllocReadLC(aResourceId);
 	__ASSERT_DEBUG((readBuffer->Length()%2)==0,Panic(ECoePanicWrongResourceFormat));
	const TPtrC16 ptrReadBuffer((TText16*) readBuffer->Ptr(),(readBuffer->Length()+1)>>1);
	HBufC16* textBuffer=HBufC16::NewL(ptrReadBuffer.Length());
	*textBuffer=ptrReadBuffer;
	CleanupStack::PopAndDestroy();
	return textBuffer;
	}

EXPORT_C HBufC8* CCoeEnv::AllocReadResourceAsDes8LC(TInt aResourceId) const
/** Reads a resource into an 8 bit heap buffer, allocating the buffer and pushing 
it onto the cleanup stack. 

The calling program must destroy the heap descriptor when it is no longer 
needed.

@param aResourceId The numeric ID of the resource to be read.
@return Pointer to a heap descriptor containing the resource data.
@see RResourceFile::AllocReadL() */
	{
	RResourceFile& rf=ResourceFileForId(aResourceId);
	return(rf.AllocReadLC(aResourceId));
	}

EXPORT_C HBufC16* CCoeEnv::AllocReadResourceAsDes16LC(TInt aResourceId) const
/** Reads a resource into a 16 bit heap buffer, allocating the buffer and pushing 
it onto the cleanup stack. 

The calling program must destroy the heap descriptor when it is no longer 
needed.

@param aResourceId The numeric ID of the resource to be read.
@return Pointer to a heap descriptor containing the resource data.
@see RResourceFile::AllocReadL() */
	{
 // Reading Unicode string
	HBufC16* textBuffer=AllocReadResourceAsDes16L(aResourceId);
	CleanupStack::PushL(textBuffer);
	return textBuffer;
	}

EXPORT_C void CCoeEnv::CreateResourceReaderLC(TResourceReader& aReader,TInt aResourceId) const
/** Reads a resource from a resource file and sets its resource reader. 

The resource reader can subsequently be used to read resource data from the 
resource. The resource reader is also placed on the cleanup stack.

Note: the GUI framework passes a resource reader as an argument to 
CCoeControl::ConstructFromResourceL(), with the resource reader's buffer already 
set to contain the relevant resource for that control.

@param aReader The resource reader.
@param aResourceId The numeric ID of the resource to be read. */
	{
	RResourceFile& rf=ResourceFileForId(aResourceId);
	HBufC8* resource=rf.AllocReadLC(aResourceId);
	aReader.SetBuffer(resource);
	}

EXPORT_C TInt CCoeEnv::AddResourceFileL(const TDesC& aFileName)
/** Adds the specified resource file to the list maintained by CCoeEnv. 

Resource files are access counted so AddResourceFileL() can be called several 
times for the same resource file. However, care should be taken to call DeleteResourceFile() 
for each resource file added to the list.

@param aFileName The resource file name.
@return The offset value defined for this resource file.
@panic CONE 15 The resource file has no NAME statement (i.e. has no offset).
@see RResourceFile::Offset()
@see ResourceFileVersionNumber() */
	{
	if (!iResourceFileArray)
		iResourceFileArray=new(ELeave) CArrayFixFlat<RResourceFile>(2); // granularity of 2
	RResourceFile resourceFile;
	resourceFile.OpenL(iFsSession,aFileName);
	CleanupClosePushL(resourceFile);
	resourceFile.ConfirmSignatureL(ResourceFileVersionNumber());
	TInt offset=resourceFile.Offset();
	if (!offset)
		Panic(ECoePanicResourceFileHasNullName);
	TInt count=iResourceFileArray->Count();
	while (count--)
		{
		TInt previousOffset=(*iResourceFileArray)[count].Offset();
		if (offset==previousOffset)
			break;
		}
	if (count>=0)
		{
		++iExtra->iResFileAccessCount[count];
		resourceFile.Close();
		}
	else
		{
		iResourceFileArray->AppendL(resourceFile);
		const TInt error=iExtra->iResFileAccessCount.Append(1);
		if (error!=KErrNone)
			{
			iResourceFileArray->Delete(iResourceFileArray->Count()-1);
			User::Leave(error);
			}
		}
	CleanupStack::Pop(); // resourceFile
	return(offset);
	}

EXPORT_C void CCoeEnv::DeleteResourceFile(TInt aOffset)
/** Deletes the specified resource file from the list maintained by CCoeEnv.

@param aOffset The offset value defined for the resource file to delete.
@panic CONE 13 The specified resource file does not exist in the list. */
	{
	if (!aOffset)
		return;
	TInt count=iResourceFileArray->Count();
	while (count--)
		{
		RResourceFile& data=(*iResourceFileArray)[count];
		if (data.Offset()==aOffset)
			{
			if (--iExtra->iResFileAccessCount[count]==0)
				{
				data.Close();
				iResourceFileArray->Delete(count);
				iExtra->iResFileAccessCount.Remove(count);
				}
			return;
			}
		}
	Panic(ECoePanicUnknownResourceFile);
	}

RResourceFile& CCoeEnv::ResourceFileForId(TInt aResourceId) const
	{
	RResourceFile* resourceptr=NULL;
	TRAPD(err, resourceptr=DoResourceFileForIdL(aResourceId));
	if(err!=KErrNone)
	    {
	    Panic(ECoePanicNoResourceFileForId);
	    }
	return *resourceptr;
	}

RResourceFile* CCoeEnv::DoResourceFileForIdL(TInt aResourceId) const
    {
    TInt count=iResourceFileArray->Count();
    FOREVER
        {
        if (!count--)
            Panic(ECoePanicNoResourceFileForId);
        RResourceFile& resourceFile=(*iResourceFileArray)[count];
        if (resourceFile.OwnsResourceIdL(aResourceId))
            return &resourceFile;
        }
    }


void CCoeEnv::DestroyAllResourceFiles()
	{
	if (!iResourceFileArray)
		return;
	TInt count=iResourceFileArray->Count();
	while (count--)
		{
		RResourceFile& resourceFile=(*iResourceFileArray)[count];
		resourceFile.Close();
		}
	delete(iResourceFileArray);
	}

EXPORT_C CDesC8ArrayFlat* CCoeEnv::ReadDesC8ArrayResourceL(TInt aResourceId)
/** Reads a resource into an 8 bit descriptor array.

@param aResourceId The numeric ID of the resource to be read.
@return A pointer to the descriptor array containing the resource data.
@see TResourceReader::ReadDesC8ArrayL() */
	{
	TResourceReader reader;
	CreateResourceReaderLC(reader,aResourceId);
	CDesC8ArrayFlat* array=reader.ReadDesC8ArrayL();
	CleanupStack::PopAndDestroy();
	return(array);
	}

EXPORT_C CDesC16ArrayFlat* CCoeEnv::ReadDesC16ArrayResourceL(TInt aResourceId)
/** Reads a resource into a 16 bit descriptor array. 

Ownership of the array is transferred to the caller.

@param aResourceId The numeric ID of the resource to be read.
@return A pointer to the descriptor array containing the resource data.
@see TResourceReader::ReadDesC16ArrayL() */
	{
	// Reading array of Unicode descriptors
	TResourceReader reader;
	CreateResourceReaderLC(reader,aResourceId);
	CDesC16ArrayFlat* array=reader.ReadDesC16ArrayL();
	CleanupStack::PopAndDestroy();
	return(array);
	}

EXPORT_C void CCoeEnv::Format128(TDes& aDes,TInt aResourceId,...)
/** Reads a 128 byte resource into a formatted string.

The format of the string is given by the variable argument list. 
The unformatted resource data must not be longer than 128 bytes.
If it is, you should use Format256() instead.

@param aDes On return, contains the formatted resource data.
@param aResourceId The numeric ID of the resource to be read.
@param ... Formatting information. */
	{
	TBuf<128> formatString;
	ReadResource(formatString,aResourceId);
	VA_LIST list;
	VA_START(list,aResourceId);
	aDes.FormatList(formatString,list);
	}

EXPORT_C void CCoeEnv::Format256(TDes& aDes,TInt aResourceId,...)
/** Reads a 256 byte resource into a formatted string.

The format of the string is given by the variable argument
list. The unformatted resource data must not be longer than 256 bytes.

@param aDes On return, contains the formatted resource data.
@param aResourceId The numeric ID of the resource to be read.
@param ... Formatting information. */
	{
	TBuf<256> formatString;
	ReadResource(formatString,aResourceId);
	VA_LIST list;
	VA_START(list,aResourceId);
	aDes.FormatList(formatString,list);
	}

EXPORT_C TInt CCoeEnv::ResourceFileVersionNumber() const
/** Gets the resource file version number.

The function is intended to be replaced in a derived class. It should return 
a defined constant which should correspond to the version number of resource 
files used by the application. It is implemented by the standard GUI framework.

AddResourceFileL() uses this function to verify that the application is not 
using an out of date resource file. An out of date resource file causes AddResourceFileL() 
to leave with error code KErrBaflWrongResourceFileSignature.

@return The resource file version number. */
	{
	return(0);
	}

EXPORT_C void CCoeEnv::LeaveWithErrorText(const TDesC& aMsg,const TDesC* aContextText)
/** Triggers a dialog which will display the error message

@param aMsg The error message.
@param aContextText The error context text. */
	{
	BaflUtils::CopyWithTruncation(ErrorText(),aMsg);
	TDes& errContextText=ErrorContextText();
	errContextText.Zero();
	if (aContextText)
		BaflUtils::CopyWithTruncation(errContextText,*aContextText);
	User::Leave(KErrExtendedWithText);	// Leave with a code of KErrExtendedWithText
	}

EXPORT_C TVersion CCoeEnv::Version()
/** Gets the version number of the UI Control Framework API.

@deprecated
@return The version number, comprising major, minor and build numbers. */
	{ // static
	return(TVersion(KCoeMajorVersionNumber,KCoeMinorVersionNumber,KCoeBuildVersionNumber));
	}

EXPORT_C CCoeEnv* CCoeEnv::Static()
/** Gets a pointer to a CCoeEnv which can be used to access CCoeEnv's functions.

It allows application code to access CCoeEnv's functions even where there 
is no direct access to a CCoeEnv object. 

For example:

@code
CCoeEnv::Static()->CreateResourceReaderLC(aReader, aResourceId);
@endcode
@return The pointer for accessing CCoeEnv's functions. */
	{ // static
	return(TheCoe());
	}

EXPORT_C void CCoeEnv::AddObserverOfLoadedFepL(MCoeObserverOfLoadedFep& aObserverOfLoadedFep)
/** Adds the specified MCoeObserverOfLoadedFep to the loaded FEP list. 

This enables objects to be notified when a front-end processor is loaded.

@param aObserverOfLoadedFep The loaded FEP observer to be added to the list. */
	{
	iExtra->AddObserverOfLoadedFepL(aObserverOfLoadedFep);
	}

EXPORT_C void CCoeEnv::RemoveObserverOfLoadedFep(MCoeObserverOfLoadedFep& aObserverOfLoadedFep)
/** Removes the specified loaded FEP observer.

@param aObserverOfLoadedFep The FEP observer to be removed. */
	{
	iExtra->RemoveObserverOfLoadedFep(aObserverOfLoadedFep);
	}

EXPORT_C void CCoeEnv::AddFocusObserverL(MCoeFocusObserver& aFocusObserver)
/** Adds the specified MCoeFocusObserver to the focus observer list. 

@param aFocusObserver The focus observer to be added to the list.
@panic CONE 18 aFocusObserver is NULL.
@panic CONE 21 aFocusObserver has already been added to the list. */
	{
	iExtra->AddFocusObserverL(aFocusObserver);
	}

EXPORT_C void CCoeEnv::RemoveFocusObserver(MCoeFocusObserver& aFocusObserver)
/** Removes the specified focus observer.

@param aFocusObserver The focus observer to be removed.
@see AddFocusObserverL() */
	{
	iExtra->RemoveFocusObserver(aFocusObserver);
	}

void CCoeEnv::NotifyFocusObserversOfDestructionOfFocusedItem()
	{
	iExtra->NotifyFocusObserversOfDestructionOfFocusedItem(); // this enables focus observers to *immediately* NULL any pointers to the object being destroyed
	QueueNotificationToFocusObserversOfChangeInFocus(); // this enables focus observers to pick up the newly focused control, once the things being destoyed has completely been destroyed
	}

EXPORT_C void CCoeEnv::AddForegroundObserverL(MCoeForegroundObserver& aForegroundObserver)
/** Adds the specified MCoeForegroundObserver to the foreground observer list.

@param aForegroundObserver The foreground observer to be added to the list.
@panic CONE 18 aForegroundObserver is NULL.
@panic CONE 21 aForegroundObserver has already been added to the list. */
	{
	iExtra->AddForegroundObserverL(aForegroundObserver);
	}

EXPORT_C void CCoeEnv::RemoveForegroundObserver(MCoeForegroundObserver& aForegroundObserver)
/** Removes the specified foreground observer.

@param aForegroundObserver The foreground observer to be removed.
@see AddForegroundObserverL() */
	{
	iExtra->RemoveForegroundObserver(aForegroundObserver);
	}

void CCoeEnv::NotifyForegroundObserversOfGainingForeground()
	{
	iExtra->NotifyForegroundObserversOfGainingForeground();
	}

void CCoeEnv::NotifyForegroundObserversOfLosingForeground()
	{
	iExtra->NotifyForegroundObserversOfLosingForeground();
	}

EXPORT_C void CCoeEnv::AddResourceChangeObserverL(MCoeResourceChangeObserver& aResourceChangeObserver)
/** Adds the specified MCoeResourceChangeObserver to the resource 
change observer list.

@param aResourceChangeObserver The resource change observer to be added to the list. */
	{
	iExtra->AddResourceChangeObserverL(aResourceChangeObserver);
	}

EXPORT_C void CCoeEnv::RemoveResourceChangeObserver(MCoeResourceChangeObserver& aResourceChangeObserver)
/** Removes the specified resource change observer.

@param aResourceChangeObserver The resource change observer to be removed. */
	{
	iExtra->RemoveResourceChangeObserver(aResourceChangeObserver);
	}

void CCoeEnv::NotifyResourceObserversOfChangeInResource()
	{
	iExtra->NotifyResourceObserversOfChangeInResource();
	}

EXPORT_C void CCoeEnv::AddMessageObserverL(MCoeMessageObserver& aMessageObserver)
/** Adds the specified MCoeMessageObserver to the message observer list.

@param aMessageObserver The message observer to be added to the list.
@see RemoveMessageObserver() */
	{
	iExtra->AddMessageObserverL(aMessageObserver);
	}

EXPORT_C void CCoeEnv::RemoveMessageObserver(MCoeMessageObserver& aMessageObserver)
/** Removes the specified MCoeMessageObserver from the message observer list.

@param aMessageObserver The message observer to be removed from the list.
@see AddMessageObserverL() */
	{
	iExtra->RemoveMessageObserver(aMessageObserver);
	}
	
EXPORT_C void CCoeEnv::AddMessageMonitorObserverL(MCoeMessageMonitorObserver& aMessageMonitorObserver)
/** Adds the specified MCoeMessageMonitorObserver to the message observer list
@param aMessageMonitorObserver The visibility change observer to be added to the list. */
	{
	iExtra->AddMessageMonitorObserverL(aMessageMonitorObserver);
	}

EXPORT_C void CCoeEnv::RemoveMessageMonitorObserver(MCoeMessageMonitorObserver& aMessageMonitorObserver)
/** Removes the specified MCoeMessageMonitorObserver.
@param aMessageMonitorObserver The visibility change observer to be removed. */
	{
	iExtra->RemoveMessageMonitorObserver(aMessageMonitorObserver);
	}

void CCoeEnv::NotifyMessageMonitorObserversOfEvent(const TWsEvent& aEvent)
	{
/**Passes control of this function to the CCoeExtra class*/
	iExtra->NotifyMessageMonitorObserversOfEvent(aEvent);
	}

EXPORT_C void CCoeEnv::AddFepObserverL(MCoeFepObserver& aFepObserver)
/** Adds the specified MCoeFepObserver to the FEP observer list. 

@param aFepObserver The FEP observer to be added to the list.
@panic CONE 18 aFepObserver is NULL.
@panic CONE 21 aFepObserver has already been added to the list. */
	{
	iExtra->AddFepObserverL(aFepObserver);
	}

EXPORT_C void CCoeEnv::RemoveFepObserver(MCoeFepObserver& aFepObserver)
/** Removes the specified FEP observer.

@param aFepObserver The FEP observer to be removed.
@see AddFepObserverL() */
	{
	iExtra->RemoveFepObserver(aFepObserver);
	}

EXPORT_C void CCoeEnv::ForEachFepObserverCall(TCoeFepObserverFunction aFepObserverFunction)
/** Calls the specified function for each FEP observer.

This function is called for each MCoeFepObserver object that has been registered. 
FEP observers are registered by calling CCoeEnv::AddFepObserverL().

@param aFepObserverFunction The function to be called. */
	{
	iExtra->ForEachFepObserverCall(aFepObserverFunction);
	}

TInt CCoeEnv::AppStartupInstrumentationEventIdBase()
/** @internalComponent */
	{
	return iExtra->iAppStartupInstrumentationEventIdBase;
	}

EXPORT_C void CCoeEnv::SetAppStartupInstrumentationEventIdBaseL(TInt aAppStartupInstrumentationEventIdBase)
/** @internalTechnology */
	{
	iExtra->iAppStartupInstrumentationEventIdBase=aAppStartupInstrumentationEventIdBase;
	}

void CCoeEnv::EnsureCorrectFepIsLoadedL()
	{
	// Called to load the initial FEP when CCoeEnv is constructed.
	CRepository& repository=CCoeDataStorage::GetL(*this).FepFrameworkRepositoryL();
	TBool loadDefaultFep=ETrue;
	TBuf<16> fepId;
	TInt error=repository.Get(ERepositoryKey_DynamicFepId, fepId);
	if ((error!=KErrNotFound) && (fepId.Length()>0))
		{
		User::LeaveIfError(error);
		// Use the currently installed FEP.
		TRAP(error, EnsureSpecifiedFepIsLoadedL(FepName::UidFromNameL(fepId)));
		if (error==KErrNone)
			{
			loadDefaultFep=EFalse;
			}
		if (error==KErrNoMemory) // if it's any other error, we'll ignore it and just try to load the default FEP instead (below)
			{
			User::Leave(error);
			}
		}
	if (loadDefaultFep)
		{
		User::LeaveIfError(repository.Get(ERepositoryKey_DefaultFepId, fepId));
		EnsureSpecifiedFepIsLoadedL(FepName::UidFromNameL(fepId)); // call this even if fep.Length()==0
		}
	}

EXPORT_C CCoeFep* CCoeEnv::Fep() const
/** Gets a pointer to the currently loaded FEP.

@return The currently loaded FEP, or NULL if none is currently loaded. */
	{
	return iExtra->iFep.iFep;
	}

EXPORT_C TUid CCoeEnv::FepUid() const
/** Gets the UID of the currently loaded FEP.

@return The UID of the currently loaded FEP. Zero if none is currently loaded. */
	{
	return iExtra->iFep.iFepUid;
	}

void CCoeEnv::QueueNotificationToFocusObserversOfChangeInFocus()
	{
	iExtra->iHighPriorityActive->QueueNotificationToFocusObserversOfChangeInFocus();
	}

TInt CCoeEnv::FocusObserverNotificationIdentifier() const
	{
	return iExtra->iHighPriorityActive->FocusObserverNotificationIdentifier();
	}

TBool CCoeEnv::FocusObserverNotificationIsStillPending(TInt aFocusObserverNotificationIdentifier) const
	{
	return iExtra->iHighPriorityActive->FocusObserverNotificationIsStillPending(aFocusObserverNotificationIdentifier);
	}
	
/** @internalTechnology*/
void CCoeEnv::RefetchPixelMappingL()
	{
	CCoeFontProvider* fontProvider = iExtra->iDefaultFontProvider;
	if(fontProvider) 
		{
		fontProvider->RefetchPixelMappingL();
		}
	}
	
/**
This function returns the default text drawer.
@return The default text drawer.
*/
EXPORT_C CCoeTextDrawerBase& CCoeEnv::DefaultTextDrawer() const
	{
	return *iExtra->iDefaultTextDrawer;
	}

EXPORT_C TTypeUid::Ptr CCoeEnv::MopSupplyObject(TTypeUid /*aId*/)
/** Retrieves an object of the same type as that encapsulated in aId.

This function is used to allow to ask owners for access to 
other objects that they own.

Other than in the case where NULL is returned, the object returned must be 
of the same object type - that is, the ETypeId member of the object pointed 
to by the pointer returned by this function must be equal to the iUid member 
of aId.

@param aId An encapsulated object type ID.
@return Encapsulates the pointer to the object provided. Note that the encapsulated 
pointer may be NULL. */
	{
	return TTypeUid::Null();
	}

/**
Sets the zoom factor of all controls currently on the control stack.

@see CCoeControl::SetZoomFactor()
@publishedPartner
@released
*/
EXPORT_C void CCoeEnv::SetZoomFactor(const TZoomFactor& aZoomFactor)
	{
	iExtra->iZoomFactor=aZoomFactor;
	iAppUi->HandleStackedControlsResourceChange(KUidValueCoeZoomChangeEvent);
	}

/**
Returns the zoom factor last set by calling CCoeEnv::SetZoomFactor().

@publishedPartner
@released
*/
EXPORT_C TZoomFactor CCoeEnv::ZoomFactor() const
	{
	return iExtra->iZoomFactor;
	}
	
EXPORT_C CWindowGc* CCoeEnv::SwapSystemGc(CWindowGc* aGc)
/** Sets the new system graphics context. 

The function returns a pointer to the old system graphics context.

@param aGc The new graphics context.
@return A pointer to the old graphics context.
@panic CONE 27 aGc is NULL. */
	{
	__ASSERT_ALWAYS(aGc,Panic(ECoePanicNullGc));
	CWindowGc* gc=iSystemGc;
	iSystemGc=aGc;
	return gc;
	}

EXPORT_C CCoeStatic* CCoeEnv::Static(TUid aUid)
/** Gets a pointer to the specified CCoeStatic derived class. 

If no match is found it will return NULL.

This function might be used to allow a CCoeStatic derived class to get a handle 
on itself.

Note: ownership of the object remains with CCoeEnv in all cases.

@param aUid The UID of the CCoeStatic derived class.
@return A pointer to the CCoeStatic derived object. NULL if no match is 
found. */
	{ // static
	CCoeEnv* env=CCoeEnv::Static();
	return env->FindStatic (aUid);
	}

//
// Gets a pointer to the specified <code>CCoeStatic</code> derived class.
//
// If no match is found it will simply return a NULL.This function might
// be used to allow a <code>CCoeStatic</code> derived class to get a
// handle on itself.Note:Ownership of the object remains with
// <code>CCoeEnv</code> in all cases.
//
// @since     7.0s
// @param     "TUid aUid"
//            The UID of the <code>CCoeStatic</code> derived class.
// @return   "CCoeStatic*"
//            A pointer to the <code>CCoeStatic</code> derived
//            objects. NULL - If no match is found.
//
EXPORT_C CCoeStatic* CCoeEnv::FindStatic(TUid aUid)
	{
	TDblQueIter<CCoeStatic> iter(iExtra->iCoeStaticList);
	CCoeStatic* obj=NULL;
	iter.SetToFirst();
	while ((obj=iter++)!=NULL)
		{
		if (obj->iCsUid==aUid)
			{
			if ((obj->CsScope()!=CCoeStatic::EApp) || (obj->CsAppUi()==AppUi()))
				{
				return obj;
				}
			}
		}
	return obj;
	}

//
// Add aStatic to CCoeEnv, transferring ownership at the end of the function.
// Should only be called once for an object of each uid.
//
void CCoeEnv::AddStatic(CCoeStatic* aStatic)
	{
	iExtra->iCoeStaticList.Add(*aStatic);
	}

void CCoeEnv::UpdateStatic(CCoeAppUi* aNewAppUi)
	{
	TDblQueIter<CCoeStatic> iter(iExtra->iCoeStaticList);
	CCoeStatic* obj=NULL;
	iter.SetToFirst();
	while ((obj=iter++)!=NULL)
		{
		if (obj->CsScope()==CCoeStatic::EApp)
			{
			obj->SetCsAppUi(aNewAppUi);
			}
		}
	}

EXPORT_C void CCoeEnv::DisableExitChecks(TBool aDisable)
/** Disables exit checks on kernel resources. Affects debug builds only.

CCoeEnv checks for kernel resources on exit (e.g. open file handles). 
These checks may be too strict for some applications, such as a web browser, 
so this function is provided to disable them.

CCoeEnv also checks on heap allocation and window server resources on exit.

@param aDisable True to disable resource checking, false to enable it.*/
	{
	if (aDisable)
		iEnvFlags|=ENoShutdownChecks;
	else
		iEnvFlags&=~ENoShutdownChecks;
	}

EXPORT_C void CCoeEnv::InputCapabilitiesChanged()
/** Notifies all focus observers (FEPs) that a change has been made to the input 
capabilities of the focused control. */
	{
	QueueNotificationToFocusObserversOfChangeInFocus();
	}

/** 
@internalTechnology
*/
EXPORT_C void CCoeEnv::GetMessageNotifyingObserversLC(TUint32 aClientHandleOfTargetWindowGroup, TUid& aMessageUid, TPtr8& aMessageParameters, const TWsEvent& aMessageEvent)
	{
	User::LeaveIfError(iWsSession.FetchMessage(aMessageUid, aMessageParameters, aMessageEvent));
	CleanupStack::PushL((TAny*)aMessageParameters.Ptr());
	iExtra->NotifyMessageObserversOfMessageL(aClientHandleOfTargetWindowGroup, aMessageUid, aMessageParameters);
	}

void CCoeEnv::SetInitialHandleCount()
	{
	TInt processHandleCount=0;
	TInt threadHandleCount=0;
	RThread().HandleCount(processHandleCount,threadHandleCount);
	if (threadHandleCount>KMaxTInt16)
		threadHandleCount=KMaxTInt16;
	iEnvFlags|=(threadHandleCount<<16);
	}

EXPORT_C void CCoeEnv::Reserved_1()
	{
	}

EXPORT_C void CCoeEnv::Reserved_2()
	{
	}

EXPORT_C TInt CCoeEnv::RunError(TInt aError)
	{
	return CActive::RunError(aError);
	}

/** 
Checks if the given resource is owned by one of the resource files in 
the list maintained by CCoeEnv.
@publishedAll
@released 
@since 9.0
@param aResourceId The ID of the resource.
@return ETrue if resource is available, EFalse otherwise.
*/
EXPORT_C TBool CCoeEnv::IsResourceAvailableL(TInt aResourceId) const
	{
	TInt count = iResourceFileArray->Count();
	for (TInt ii=0; ii<count; ii++)
		{
		RResourceFile& resFile = iResourceFileArray->At(ii);
		if (resFile.OwnsResourceIdL(aResourceId))
			{
			return ETrue;   
			}
		}
	return EFalse;
	}
	
/**
This function returns the default font provider.
@return The default font provider.
*/
EXPORT_C const CCoeFontProvider& CCoeEnv::DefaultFontProvider() const 
    { 
    return *iExtra->iDefaultFontProvider; 
    } 

/**
This function returns the screen device with this particular screen number.
@param aScreenNumber 
@return the screen device with this particular screen number.
*/
EXPORT_C CWsScreenDevice* CCoeEnv::ScreenDevice(TInt aScreenNumber) const
	{
	__ASSERT_DEBUG(((aScreenNumber>=0) && (aScreenNumber < iExtra->iArrayOfScreenItems.Count())),Panic(ECoePanicInvalidScreenNumber));
	return iExtra->iArrayOfScreenItems[aScreenNumber]->ScreenDevice();			
	}

/**
This function returns the window group associated with the screen device that bears this particular screen number.
@param aScreenNumber
@return the window group associated with the screen device that bears this particular screen number. 
	
*/
EXPORT_C RWindowGroup* CCoeEnv::RootWin(TInt aScreenNumber) const
 	{
 	__ASSERT_DEBUG(((aScreenNumber>=0) && (aScreenNumber < iExtra->iArrayOfScreenItems.Count())),Panic(ECoePanicInvalidScreenNumber));
	return iExtra->iArrayOfScreenItems[aScreenNumber]->WindowGroup();	
 	}	

/**
This function initializes an array of TScreenItems. Each SScreenItem object contains a pointer to a screen device and a window group
The first entry in this array points to the default screen device and window group.
The default screen device is the primary screen device in the system.
*/
void CCoeEnv::PopulateArrayOfScreenItemsL()
	{
	TInt numScreens(0);
	numScreens = iWsSession.NumberOfScreens();	
	//Initialise the first entry with the default screen device and default window group	
	//The default screen number is always 0
	CCoeEnvExtra::CScreenItem* defaultScreenItem = new(ELeave) CCoeEnvExtra::CScreenItem(iScreen,&iRootWin);
	CleanupStack::PushL(defaultScreenItem);
	iExtra->iArrayOfScreenItems.AppendL(defaultScreenItem);
	CleanupStack::Pop(defaultScreenItem);

	for(TInt i=1;i<numScreens;i++)
		{
		CWsScreenDevice* screenDevice =new(ELeave) CWsScreenDevice(iWsSession);
		CleanupStack::PushL(screenDevice);	
		User::LeaveIfError(screenDevice->Construct(i));
		RWindowGroup* windowGroup = new(ELeave) RWindowGroup(iWsSession);
		CleanupStack::PushL(windowGroup);
		User::LeaveIfError(windowGroup->Construct((TUint32)screenDevice, EFalse,screenDevice));
		CCoeEnvExtra::CScreenItem* screenItem = new(ELeave) CCoeEnvExtra::CScreenItem(screenDevice,windowGroup);
		CleanupStack::Pop(2,screenDevice);  // ownership of screenDevice and windowGroup goes to screenItem
		CleanupStack::PushL(screenItem);
		iExtra->iArrayOfScreenItems.AppendL(screenItem);
		CleanupStack::Pop(screenItem); 
		}
	}

/**
This function deletes the array of TScreenItems
*/
void CCoeEnv::DeleteArrayOfScreensItems()
	{
	if(iExtra && iExtra->iArrayOfScreenItems.Count() > 0)
		{
		iExtra->iArrayOfScreenItems[0]->SetScreenDevice(0);
		iExtra->iArrayOfScreenItems[0]->SetWindowGroup(0);
		iExtra->iArrayOfScreenItems.ResetAndDestroy();
		}
	}


/**
Return an error code if something failed during early c'tor construction.
@internalTechnology
*/
EXPORT_C TInt CCoeEnv::CoeEnvConstructorError() const
	{
	return (iEnvFlags&EExtraPointerIsErrorCode ? reinterpret_cast<TInt>(iExtra) : KErrNone);
	}	

/**
Return the status of the report control state change.
@internalTechnology
*/
TBool CCoeEnv::ControlStateChange()
	{	return iExtra->iControlState;	}


// MCoeObserverOfLoadedFep
EXPORT_C MCoeObserverOfLoadedFep::MCoeObserverOfLoadedFep()
	{
	}
EXPORT_C void MCoeObserverOfLoadedFep::MCoeObserverOfLoadedFep_Reserved_1()
	{
	}

EXPORT_C void MCoeObserverOfLoadedFep::MCoeObserverOfLoadedFep_Reserved_2()
	{
	}

// MCoeFocusObserver
EXPORT_C MCoeFocusObserver::MCoeFocusObserver()
	{
	}
EXPORT_C void MCoeFocusObserver::MCoeFocusObserver_Reserved_1()
	{
	}

EXPORT_C void MCoeFocusObserver::MCoeFocusObserver_Reserved_2()
	{
	}

// MCoeResourceObserver
EXPORT_C MCoeResourceChangeObserver::MCoeResourceChangeObserver()
	{
	}
EXPORT_C void MCoeResourceChangeObserver::MCoeResourceChangeObserver_Reserved_1()
	{
	}

EXPORT_C void MCoeResourceChangeObserver::MCoeResourceChangeObserver_Reserved_2()
	{
	}
// MCoeForegroundObserver
EXPORT_C MCoeForegroundObserver::MCoeForegroundObserver()
	{
	}
EXPORT_C void MCoeForegroundObserver::MCoeForegroundObserver_Reserved_1()
	{
	}

EXPORT_C void MCoeForegroundObserver::MCoeForegroundObserver_Reserved_2()
	{
	}

// MCoeMessageObserver
EXPORT_C MCoeMessageObserver::MCoeMessageObserver()
	{
	}
EXPORT_C void MCoeMessageObserver::MCoeMessageObserver_Reserved_1()
	{
	}

EXPORT_C void MCoeMessageObserver::MCoeMessageObserver_Reserved_2()
	{
	}


// MCoeMessageMonitorObserver

EXPORT_C void MCoeMessageMonitorObserver::MCoeMessageMonitorObserver_Reserved_1()
	{
	}

EXPORT_C void MCoeMessageMonitorObserver::MCoeMessageMonitorObserver_Reserved_2()
	{
	}


// CCoeStatic
EXPORT_C CCoeStatic::CCoeStatic()
	{
	}

EXPORT_C CCoeStatic::~CCoeStatic()
/** Destructor. */
	{
	iCsLink.Deque();
	}

EXPORT_C CCoeStatic::CCoeStatic(TUid aUid,TScope aScope)
/** Constructor specifying a unique UID and the scope of the object.

@param aUid The unique UID.
@param The scope of access to the object. By default, the object can be accessed 
from anywhere in the thread (EThread). */
	{
	DoConstruction(aUid,EDefaultDestructionPriority,aScope);
	}

EXPORT_C CCoeStatic::CCoeStatic(TUid aUid,TInt aDestructionPriority,TScope aScope)
/** Constructor specifying a unique UID and the destruction priority and scope of the object.

@param aUid The unique UID.
@param aDestructionPriority Priority determining the order of destruction relative to other
CCoeStatic-derived objects. The higher the destruction-priority of the object, the earlier that
object is deleted. Objects with a positive destruction-priority are destroyed before the CCoeAppUi
object is destroyed. Objects with a negative destruction-priority are destroyed after the CCoeAppUi
object is destroyed.
@param aScope The scope of access to the object. By default, the object can be accessed
from anywhere in the thread (EThread). */
	{
	DoConstruction(aUid,aDestructionPriority,aScope);
	}

void CCoeStatic::DoConstruction(const TUid& aUid,TInt aDestructionPriority,TScope aScope)
	{
	__ASSERT_ALWAYS(aUid!=KNullUid,Panic(ECoePanicNullObjectUid));
	__ASSERT_ALWAYS(CCoeEnv::Static(aUid)==NULL,Panic(ECoePanicDuplicateObjectUid));
	iCsLink.iPriority=aDestructionPriority;
	iCsUid=aUid;
	CCoeEnv* env = CCoeEnv::Static();
	iCsAppUiAndScope=0;
	if (aScope==EApp)
		{
		iCsAppUiAndScope=(REINTERPRET_CAST(TUint,env->AppUi())|0x1u);
		}
	env->AddStatic(this);
	}

void CCoeStatic::SetCsAppUi(CCoeAppUi* aAppUi)
	{
	const TUint scopeFlag=(iCsAppUiAndScope&0x1u);
	iCsAppUiAndScope=(REINTERPRET_CAST(TUint,aAppUi)|scopeFlag);
	}

CCoeAppUi* CCoeStatic::CsAppUi() const
	{
	return REINTERPRET_CAST(CCoeAppUi*, iCsAppUiAndScope&~0x1u);
	}

CCoeStatic::TScope CCoeStatic::CsScope() const
	{
	return (iCsAppUiAndScope&0x1u)? EApp: EThread;
	}

IMPORT_C void PanicStub1();
EXPORT_C void PanicStub1()
	{
	Panic(ECoePanicExportNotSupported);
	}
EXPORT_C void CCoeStatic::CCoeStatic_Reserved1()
	{
	}

EXPORT_C void CCoeStatic::CCoeStatic_Reserved2()
	{
	}
