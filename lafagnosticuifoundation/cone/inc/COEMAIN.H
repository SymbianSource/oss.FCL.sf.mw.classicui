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

#ifndef __COEMAIN_H__
#define __COEMAIN_H__

#include <e32base.h>
#include <w32std.h>
#include <barsc.h>
#include <badesca.h>
#include <basched.h>
#include <coemop.h>
#include <coetextdrawer.h>


#if defined(USE_IH_RAISE_EVENT)
#include <systemmonitor/raiseevent.h>
#include <test/testinstrumentation.h>
#endif

class CVwsSessionWrapper;
class MVwsSessionWrapperObserver;
class TCoeInputCapabilities; // forward declaration of class defined in COEINPUT.H
class CCoeAppUi;
class CCoeEnv;
class TResourceReader;
class RGenericPointerArray;
class CCoeFep; // must derive from CBase
class CCoeFontProvider;
class CCoeEnvExtra;
class CCoeStatic;

#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <graphics/cone/coescheduler.h>
#endif //SYMBIAN_ENABLE_SPLIT_HEADERS

/** UI Control framework active object priorities. 
These are in addition to the values contained in the TPriority enum in class CActive.

@publishedAll
@released */
enum TActivePriority
	{
	/** 300 */
	EActivePriorityClockTimer=300,
	/** 200 */
	EActivePriorityIpcEventsHigh=200,
	/** 150 */
	EActivePriorityFepLoader=150,
	/** 100 */
	EActivePriorityWsEvents=100,
	/** 50 */
	EActivePriorityRedrawEvents=50,
	/** 0 */
	EActivePriorityDefault=0,
	/** 10 */
	EActivePriorityLogonA=-10
	};


/** Interface providing notification when there is a change in the currently 
loaded FEP. 

This happens either on application start-up, or as a result of a different 
front end processor having been installed.

Anyone requiring this notification should derive from this class and implement 
its pure virtual function. Derived classes also need to call CCoeEnv::AddObserverOfLoadedFepL() 
during construction, and CCoeEnv::RemoveObserverOfLoadedFep() in their destructor. 

@publishedAll
@released */
class MCoeObserverOfLoadedFep
	{
public:
	/** Handles a change in the loaded FEP. 
	
	The function is called if a new FEP is loaded, or if the current one is unloaded. */
	virtual void HandleChangeInLoadedFep()=0;
protected:
	IMPORT_C MCoeObserverOfLoadedFep();
	
private:
	IMPORT_C virtual void MCoeObserverOfLoadedFep_Reserved_1();
	IMPORT_C virtual void MCoeObserverOfLoadedFep_Reserved_2();
private:
 	TInt iMCoeObserverOfLoadedFep_Reserved1;
	};


/** Interface providing notification if any control gains or loses focus or is 
destroyed. 

The FEP framework uses this class to observe when a target control changes 
for reasons unrelated to the FEP.

Anything that needs such notification should derive from this class and implement 
its two pure virtual functions. 

In addition, derived classes need to call CCoeEnv::AddFocusObserverL() during 
construction, and CCoeEnv::RemoveFocusObserver() in their destructors. 

@publishedAll
@released 
@see CCoeFep */
class MCoeFocusObserver
	{
public:
	/** Handles changes in focus. The function is called if any control gains or loses 
	focus. */
	virtual void HandleChangeInFocus()=0;
	/** Handles the destruction of any control. It is called by the framework if any 
	control is destroyed. */
	virtual void HandleDestructionOfFocusedItem()=0;
protected:
	IMPORT_C MCoeFocusObserver();
private:
	IMPORT_C virtual void MCoeFocusObserver_Reserved_1();
	IMPORT_C virtual void MCoeFocusObserver_Reserved_2();
private:
	TInt iMCoeFocusObserver_Reserved1;
	};

/** An interface which enables message windows to observe resource changes.

Resource change observers should be added to the control environment using 
CCoeEnv::AddResourceChangeObserverL(). 

@publishedAll 
@released */
class MCoeResourceChangeObserver
	{
public:
	/** Handles a change to the application's resources. */
	virtual void HandleResourceChange()=0;
protected:
	IMPORT_C MCoeResourceChangeObserver();
private:
	IMPORT_C virtual void MCoeResourceChangeObserver_Reserved_1();
	IMPORT_C virtual void MCoeResourceChangeObserver_Reserved_2();
private:
	TInt iMCoeResourceChangeObserver_Reserved1;
	};

/** Interface providing notification of foreground/background changes. 

The FEP framework class, CCoeFep, derives from MCoeForegroundObserver, which 
enables FEPs to receive notification when the target application (which receives 
the FEP's output) goes into the foreground or background.

Anything that needs this notification should derive from this class and override 
its two pure virtual functions.

In addition, derived classes also need to call CCoeEnv::AddForegroundObserverL() 
during construction, and CCoeEnv::RemoveForegroundObserver() in their destructors. 

@publishedAll
@released 
@see CCoeFep */
class MCoeForegroundObserver
	{
public:
	/** Handles the application coming to the foreground. */
	virtual void HandleGainingForeground()=0;
	/** Handles the application going into the background. */
	virtual void HandleLosingForeground()=0;
protected:
	IMPORT_C MCoeForegroundObserver();
private:
	IMPORT_C virtual void MCoeForegroundObserver_Reserved_1();
	IMPORT_C virtual void MCoeForegroundObserver_Reserved_2();
private:
	TInt iMCoeForegroundObserver_Reserved1;
	};


/** Interface for handling incoming window server messages.

This interface is used to enable FEPs to keep their settings synchronised 
across all running instances.

Anything that needs to be notified of messages that get sent by the window server's 
message-sending service should derive from this class and override its pure 
virtual function. 

In addition, derived classes also need to call CCoeEnv::AddMessageObserverL() 
during construction and CCoeEnv::RemoveMessageObserver() in their destructors. 

@publishedAll 
@released */
class MCoeMessageObserver
	{
public:
	/** Message response flags. */
	enum TMessageResponse
		{
		/** Message not handled. */
		EMessageNotHandled,
		/** Message handled. */
		EMessageHandled
		};
public:
	/** Handles window server messages. 
	
	Implementations should return EMessageHandled if they are able to handle the 
	message, or EMessageNotHandled if the message is not appropriate to this observer.
	
	@param aClientHandleOfTargetWindowGroup The window group that the message 
	was sent to. Many implementations will not need this information.
	@param aMessageUid The message UID.
	@param aMessageParameters The message parameters.
	@return Indicates whether the message was handled or not handled 
	by the function. */
	virtual TMessageResponse HandleMessageL(TUint32 aClientHandleOfTargetWindowGroup, TUid aMessageUid, const TDesC8& aMessageParameters)=0;
protected:
	IMPORT_C MCoeMessageObserver();
private:
	IMPORT_C virtual void MCoeMessageObserver_Reserved_1();
	IMPORT_C virtual void MCoeMessageObserver_Reserved_2();
	};

/** Mix-in interface for handling window visibility messages. 	

@publishedAll
@released */
class MCoeMessageMonitorObserver
	{
public:
	/** Received windows messages for monitoring. 
	@param aEvent The windows server event data.*/
	virtual void MonitorWsMessage(const TWsEvent& aEvent)=0;
private:
	IMPORT_C virtual void MCoeMessageMonitorObserver_Reserved_1();
	IMPORT_C virtual void MCoeMessageMonitorObserver_Reserved_2();
	};

// classes defined in FEPBASE, declared here
class MCoeFepObserver;

/** 
@publishedAll
@released
*/
typedef void (*TCoeFepObserverFunction)(MCoeFepObserver& aFepObserver);

/**
@publishedAll 
@released 
*/
class CCoeFepParameters : public CBase
	{
public:
	static CCoeFepParameters* NewLC();
private:
	inline CCoeFepParameters() {}
	};


/** Control environment.

CCoeEnv provides an active environment for creating controls. It implements 
active objects and an active scheduler, which provide access to the window 
server, simplifying the API for application programs. It also provides utility 
functions that are useful to many applications.

When a standard event occurs, the active scheduler calls CCoeEnv::RunL(). 
When a redraw event occurs, it calls CCoeRedrawer::RunL(). Priority key events 
must be accessed using the Window Server API directly.

Note: standard events are all events except redraw events and priority key events. 

@publishedAll
@released */
class CCoeEnv : public CActive, public MObjectProvider
	{
public:
	// Properties
	IMPORT_C static TVersion Version();
	IMPORT_C static CCoeEnv* Static();
	// Construction and destruction
	IMPORT_C CCoeEnv();
	IMPORT_C ~CCoeEnv();
	IMPORT_C void ConstructL();
	IMPORT_C void ConstructL(TBool aInitialFocusState);
	IMPORT_C void ConstructL(TBool aInitialFocusState, TInt aDefaultScreenNumber);
	IMPORT_C void ConstructL(TBool aInitialFocusState, TInt aDefaultScreenNumber, TInt aWindowGroupID);
	IMPORT_C CCoeAppUi* SetAppUi(CCoeAppUi* aAppUi);
	IMPORT_C void ExecuteD();
	IMPORT_C void Execute();
	IMPORT_C void RunL();
	IMPORT_C void DoCancel();
	IMPORT_C void PrepareToExit();
	IMPORT_C virtual void DestroyEnvironment();
	IMPORT_C void DisableExitChecks(TBool aDisable);
	IMPORT_C virtual void HandleError(TInt aError);
	// System resources
	inline CCoeAppUi* AppUi() const;
	inline RFs& FsSession() const;
	inline RWsSession& WsSession() const;
	inline RWindowGroup& RootWin() const;
	inline CWsScreenDevice* ScreenDevice() const;
	inline CWindowGc& SystemGc() const;
	inline const CFont* NormalFont() const;
	inline const TWsEvent& LastEvent() const;
	inline TBool IsSchedulerRunning() const;
	// Graphics
	IMPORT_C CWindowGc* CreateGcL();
	IMPORT_C CWindowGc* SwapSystemGc(CWindowGc* aGc);
	IMPORT_C void Flush(TTimeIntervalMicroSeconds32 aDelay=0);
	IMPORT_C void SuppressNextFlush();
	IMPORT_C TBool IsWservEventPending() const;
	IMPORT_C TBool IsRedrawEventPending() const;
	// Fonts
	IMPORT_C CFbsFont* CreateDeviceFontL(CGraphicsDevice* aDevice,const TFontSpec& aFontSpec);
	IMPORT_C CFbsFont* CreateScreenFontL(const TFontSpec& aFontSpec);
	IMPORT_C void ReleaseScreenFont(CFont* aFont) const;
	// Font provider
	IMPORT_C const CCoeFontProvider& DefaultFontProvider() const; 
	// Text drawer
	IMPORT_C CCoeTextDrawerBase& DefaultTextDrawer() const;
	// Zooming
	IMPORT_C TZoomFactor ZoomFactor() const;
	IMPORT_C void SetZoomFactor(const TZoomFactor& aZoomFactor);
	// Resource reading	
	IMPORT_C TInt AddResourceFileL(const TDesC& aFileName);
	IMPORT_C void DeleteResourceFile(TInt aOffset);
	IMPORT_C TBool IsResourceAvailableL(TInt aResourceId) const;
	IMPORT_C void CreateResourceReaderLC(TResourceReader& aReader,TInt aResourceId) const;
	inline void ReadResource(TDes& aDes,TInt aResourceId) const; 
	inline void ReadResourceL(TDes& aDes,TInt aResourceId) const; 
	inline HBufC* AllocReadResourceL(TInt aResourceId) const;
	inline HBufC* AllocReadResourceLC(TInt aResourceId) const;
	inline CDesCArrayFlat* ReadDesCArrayResourceL(TInt aResourceId);
	IMPORT_C void ReadResourceAsDes8(TDes8& aDes,TInt aResourceId) const; /** @deprecated 7.0*/
	IMPORT_C void ReadResourceAsDes8L(TDes8& aDes,TInt aResourceId) const;
	IMPORT_C HBufC8* AllocReadResourceAsDes8L(TInt aResourceId) const;
	IMPORT_C HBufC8* AllocReadResourceAsDes8LC(TInt aResourceId) const;
	IMPORT_C CDesC8ArrayFlat* ReadDesC8ArrayResourceL(TInt aResourceId);
	IMPORT_C void ReadResourceAsDes16(TDes16& aDes,TInt aResourceId) const; /** @deprecated 7.0*/
	IMPORT_C void ReadResourceAsDes16L(TDes16& aDes,TInt aResourceId) const; 
	IMPORT_C HBufC16* AllocReadResourceAsDes16L(TInt aResourceId) const;
	IMPORT_C HBufC16* AllocReadResourceAsDes16LC(TInt aResourceId) const;
	IMPORT_C CDesC16ArrayFlat* ReadDesC16ArrayResourceL(TInt aResourceId);
	IMPORT_C void Format128(TDes& aDes,TInt aResourceId,...);
	IMPORT_C void Format256(TDes& aDes,TInt aResourceId,...);
	// Error handling
	IMPORT_C void LeaveWithErrorText(const TDesC& aMsg,const TDesC* aContextText=NULL);
	// Key handling
	IMPORT_C void SimulateKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	// FEP handling
	IMPORT_C void AddObserverOfLoadedFepL(MCoeObserverOfLoadedFep& aObserverOfLoadedFep);
	IMPORT_C void RemoveObserverOfLoadedFep(MCoeObserverOfLoadedFep& aObserverOfLoadedFep);
	IMPORT_C void AddFepObserverL(MCoeFepObserver& aFepObserver);
	IMPORT_C void RemoveFepObserver(MCoeFepObserver& aFepObserver);
	IMPORT_C void ForEachFepObserverCall(TCoeFepObserverFunction aFepObserverFunction);
	void EnsureCorrectFepIsLoadedL();
	void EnsureSpecifiedFepIsLoadedL(TUid aFepUid);
	IMPORT_C void InstallFepL(TUid aFepUid);
	IMPORT_C void InstallFepL(TUid aFepUid, const TBool aLeave);
	IMPORT_C void AvailableFepsL(RArray<TUid>& aUids, CDesCArray* aDisplayNames);
	IMPORT_C void ExecuteFepSettingsDialogL(TUid aFepUid);
	IMPORT_C CCoeFep* Fep() const;
	IMPORT_C TUid FepUid() const;
	IMPORT_C void InputCapabilitiesChanged();
	// Control focus handling
	IMPORT_C void AddFocusObserverL(MCoeFocusObserver& aFocusObserver);
	IMPORT_C void RemoveFocusObserver(MCoeFocusObserver& aFocusObserver);
	IMPORT_C void SyncNotifyFocusObserversOfChangeInFocus();
	void NotifyFocusObserversOfDestructionOfFocusedItem();
	// Application focus (foreground) handling
	IMPORT_C void BringOwnerToFront();
	IMPORT_C void AddForegroundObserverL(MCoeForegroundObserver& aForegroundObserver);
	IMPORT_C void RemoveForegroundObserver(MCoeForegroundObserver& aForegroundObserver);
	void NotifyForegroundObserversOfGainingForeground();
	void NotifyForegroundObserversOfLosingForeground();
	// Resource change handling
	IMPORT_C void AddResourceChangeObserverL(MCoeResourceChangeObserver& aResourceChangeObserver); 
	IMPORT_C void RemoveResourceChangeObserver(MCoeResourceChangeObserver& aResourceChangeObserver); 
	void NotifyResourceObserversOfChangeInResource(); 
	// Window server message handling
	IMPORT_C void AddMessageObserverL(MCoeMessageObserver& aMessageObserver);
	IMPORT_C void RemoveMessageObserver(MCoeMessageObserver& aMessageObserver);
	IMPORT_C void AddMessageMonitorObserverL(MCoeMessageMonitorObserver& aMessageMonitorObserver); 
	IMPORT_C void RemoveMessageMonitorObserver(MCoeMessageMonitorObserver& aMessageMonitorObserver); 
	void NotifyMessageMonitorObserversOfEvent(const TWsEvent& aEvent); 	
	// Singleton access
	IMPORT_C static CCoeStatic* Static(TUid aUid);
	IMPORT_C CCoeStatic* FindStatic(TUid aUid);
	//multiple screens
 	IMPORT_C CWsScreenDevice* ScreenDevice(TInt aScreenNumber) const;
 	IMPORT_C RWindowGroup* RootWin(TInt aScreenNumber) const;
public: // *** Do not use! API liable to change ***
	TInt AppStartupInstrumentationEventIdBase();
public: // Internal to Symbian
	IMPORT_C void GetMessageNotifyingObserversLC(TUint32 aClientHandleOfTargetWindowGroup, TUid& aMessageUid, TPtr8& aMessageParameters, const TWsEvent& aMessageEvent);
	IMPORT_C TBool DisableShutdownChecks() const;
protected: // Internal to Symbian
	IMPORT_C void SetAppStartupInstrumentationEventIdBaseL(TInt aAppStartupInstrumentationEventIdBase);
	IMPORT_C void DestroyEnvironmentStatic();
	IMPORT_C void DestroyEnvironmentEnd();
	IMPORT_C TInt CoeEnvConstructorError() const;
private: // reserved virtual function space
	IMPORT_C virtual void Reserved_1();
	IMPORT_C virtual void Reserved_2();
private: // from CActive
	IMPORT_C TInt RunError(TInt aError);
protected:	// from MObjectProvider
	IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId); 
protected:
	IMPORT_C virtual void DestroyScreen();
	inline TDes& ErrorText();
	inline TDes& ErrorContextText();
public: // but not exported
	void DoFlush();
	CVwsSessionWrapper* InitViewServerSessionL(MVwsSessionWrapperObserver& aObserver);
	void AddStatic(CCoeStatic* aStatic);
	void QueueNotificationToFocusObserversOfChangeInFocus();
	TInt FocusObserverNotificationIdentifier() const;
	TBool FocusObserverNotificationIsStillPending(TInt aFocusObserverNotificationIdentifier) const;
	void RefetchPixelMappingL();
	TBool ControlStateChange();
	TInt SupportedPointers() const;
private:
	void RequestEventNotification();
	void CreateActiveSchedulerL();
	void ConnectToFileServerL();
	void ConnectToWindowServerL();
	void InitScreenL( TInt aDefaultScreenNumber );
	void InitRootWindowL(TBool aInitialFocusState, TInt aWindowGroupID=0);
	void InitSystemGcL();
	IMPORT_C virtual void InitSystemFontsL();
	IMPORT_C virtual TInt ResourceFileVersionNumber() const;
	RResourceFile& ResourceFileForId(TInt aResourceId) const;
	void DestroyAllResourceFiles();
	void AddObserverL(TAny* aObserver, RGenericPointerArray& aArray);
	void RemoveObserver(TAny* aObserver, RGenericPointerArray& aArray);
	void UpdateStatic(CCoeAppUi* aNewAppUi);
	void SetInitialHandleCount();
	TUint InitialHandleCount() const;
	RResourceFile* DoResourceFileForIdL(TInt aResourceId) const;
	void PopulateArrayOfScreenItemsL();
	void DeleteArrayOfScreensItems();
protected:
	CCoeAppUi* iAppUi;
	RFs iFsSession;
	RWsSession iWsSession;
	RWindowGroup iRootWin;
	CWindowGc* iSystemGc;
	const CFont* iNormalFont;
	CWsScreenDevice* iScreen;
	TWsEvent iLastEvent;
	CArrayFix<RResourceFile>* iResourceFileArray;
private:
	enum TFlags // used in the bottom 16 bits only of iEnvFlags
		{
		ENoShutdownChecks			=0x0001,
		EExtraPointerIsErrorCode	=0x0002,
		ESchedulerIsRunning			=0x0004
		};
private:
	TDes* iErrorText;
	TDes* iErrorContextText;
	CCoeEnvExtra* iExtra;
	CTrapCleanup* iCleanup;
	TUint iEnvFlags;
	};

/** Base class for creating singleton objects that will be stored by CCoeEnv.

Each object must have a unique TUid.

Symbian OS does not provide writeable global static data. Singleton objects 
provide its equivalent in thread local storage, which is supported.

This behaviour is useful for objects in which only one copy is ever needed 
in the thread or application, e.g. in alert windows. 

@publishedAll 
@released */
class CCoeStatic : public CBase
	{
public:
	/** Scope of access to the singleton object. */
	enum TScope
		{
		/** Access from the entire thread. */
		EThread,
		/** Access from an appUi in that thread. */
		EApp,
		};
	/** The default destruction priority if none is specified in the constructor */
	enum {EDefaultDestructionPriority=100};
public:
	IMPORT_C ~CCoeStatic();
protected:
	IMPORT_C CCoeStatic();
	IMPORT_C CCoeStatic(TUid aUid,TScope=EThread);
	IMPORT_C CCoeStatic(TUid aUid,TInt aDestructionPriority,TScope aScope=EThread);
private:
	IMPORT_C virtual void CCoeStatic_Reserved1();
	IMPORT_C virtual void CCoeStatic_Reserved2();
private:
	void DoConstruction(const TUid& aUid,TInt aDestructionPriority,TScope aScope);
	void SetCsAppUi(CCoeAppUi* aAppUi);
	CCoeAppUi* CsAppUi() const;
	TScope CsScope() const;
	inline TInt DestructionPriority() const {return iCsLink.iPriority;}
private:
	TPriQueLink iCsLink;
	TUid iCsUid;
	TUint iCsAppUiAndScope;
	TInt iCCoeStatic_Reserved1;
private:
	friend class CCoeEnv;
	friend class CCoeEnvExtra;
	};

#include <coemain.inl>

#endif	// __COEMAIN_H__
