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

#ifndef __COEENVEXTRA_H__
#define __COEENVEXTRA_H__

#include <e32base.h>
#include <coemain.h>
#include "coepriv.h"

class CRepository;
class CCoeFepLoader;
class CCoeFepPlugIn;
class CCoeFepTracker;
class CCoeRedrawer;
class CCoeFep;
class CCoeTextDrawerBase;

/** @internalTechnology */
class CCoeEnvExtra : public CBase
	{
public:
	class TFep
		{
	public:
		inline TFep() : iFep(NULL), iFepUid(KNullUid), iFepPlugIn(NULL) {}
	public:
		CCoeFep* iFep;
		TUid iFepUid;
		CCoeFepPlugIn* iFepPlugIn;
		};
		
	class CHighPriorityActive : public CActive
		{
	public:
		static CHighPriorityActive* NewL(CCoeEnvExtra& aCoeEnvExtra);
		~CHighPriorityActive();
		void QueueNotificationToFocusObserversOfChangeInFocus();
		TInt FocusObserverNotificationIdentifier() const;
		TBool FocusObserverNotificationIsStillPending(TInt aFocusObserverNotificationIdentifier) const;
		void NotifyFocusObserversOfChangeInFocus();
	private:
		CHighPriorityActive(CCoeEnvExtra& aCoeEnvExtra);
	private: // from CActive	
		void DoCancel();
		void RunL();
	private:
		CCoeEnvExtra& iCoeEnvExtra;
		TInt iFocusObserverNotificationIdentifier;
		};
	NONSHARABLE_CLASS(CScreenItem) : public CBase 
		{
	public:
		CScreenItem(CWsScreenDevice* aScreenDevice,RWindowGroup* aWindowGroup);
		~CScreenItem();
		CWsScreenDevice* ScreenDevice();
		RWindowGroup* WindowGroup();
		void SetScreenDevice(CWsScreenDevice* aScreenDevice);
		void SetWindowGroup(RWindowGroup* aWindowGroup);
	private:
		CWsScreenDevice* iScreenDevice;
		RWindowGroup* iWindowGroup;
		};
public:
	CCoeEnvExtra();
	void ConstructL();
	virtual ~CCoeEnvExtra();
	// ObserverOfLoadedFep
	void AddObserverOfLoadedFepL(MCoeObserverOfLoadedFep& aObserverOfLoadedFep) {AddObserverL(iArrayOfObserversOfLoadedFep, &aObserverOfLoadedFep);}
	void RemoveObserverOfLoadedFep(const MCoeObserverOfLoadedFep& aObserverOfLoadedFep) {RemoveObserver(iArrayOfObserversOfLoadedFep, &aObserverOfLoadedFep);}
	void HandleChangeInLoadedFep();
	// FocusObserver
	void AddFocusObserverL(MCoeFocusObserver& aFocusObserver) {AddObserverL(iArrayOfFocusObservers, &aFocusObserver);}
	void RemoveFocusObserver(const MCoeFocusObserver& aFocusObserver) {RemoveObserver(iArrayOfFocusObservers, &aFocusObserver);}
	void NotifyFocusObserversOfChangeInFocus();
	void NotifyFocusObserversOfDestructionOfFocusedItem();
	// ForegroundObserver
	void AddForegroundObserverL(MCoeForegroundObserver& aForegroundObserver) {AddObserverL(iArrayOfForegroundObservers, &aForegroundObserver);}
	void RemoveForegroundObserver(const MCoeForegroundObserver& aForegroundObserver) {RemoveObserver(iArrayOfForegroundObservers, &aForegroundObserver);}
	void NotifyForegroundObserversOfGainingForeground();
	void NotifyForegroundObserversOfLosingForeground();
	// MessageObserver
	void AddMessageObserverL(MCoeMessageObserver& aMessageObserver) {AddObserverL(iArrayOfMessageObservers, &aMessageObserver);}
	void RemoveMessageObserver(const MCoeMessageObserver& aMessageObserver) {RemoveObserver(iArrayOfMessageObservers, &aMessageObserver);}
	void NotifyMessageObserversOfMessageL(TUint32 aClientHandleOfTargetWindowGroup, const TUid& aMessageUid, const TDesC8& aMessageParameters);
	// FepObserver
	void AddFepObserverL(MCoeFepObserver& aFepObserver) {AddObserverL(iArrayOfFepObservers, &aFepObserver);}
	void RemoveFepObserver(const MCoeFepObserver& aFepObserver) {RemoveObserver(iArrayOfFepObservers, &aFepObserver);}
	void ForEachFepObserverCall(TCoeFepObserverFunction aFepObserverFunction);
	static void DestroyFep(TAny* aFep);
	static void DestroyFep(TFep& aFep);
	// ResourceChangeObserver
	void AddResourceChangeObserverL(MCoeResourceChangeObserver& aResourceChangeObserver) {AddObserverL(iArrayOfResourceChangeObservers, &aResourceChangeObserver);}
	void RemoveResourceChangeObserver(const MCoeResourceChangeObserver& aResourceChangeObserver) {RemoveObserver(iArrayOfResourceChangeObservers, &aResourceChangeObserver);}
	void NotifyResourceObserversOfChangeInResource();
	// AddMessageMonitorObserver
	void AddMessageMonitorObserverL(MCoeMessageMonitorObserver& aMessageMonitorObserver) {AddObserverL(iArrayOfMessageMonitorObservers, &aMessageMonitorObserver);}
	void RemoveMessageMonitorObserver(const MCoeMessageMonitorObserver& aMessageMonitorObserver) {RemoveObserver(iArrayOfMessageMonitorObservers, &aMessageMonitorObserver);}
	void NotifyMessageMonitorObserversOfEvent(const TWsEvent &aEvent);
private:
	static void AddObserverL(RArray<TAny*>& aArrayOfObservers, TAny* aObserver);
	static void RemoveObserver(RArray<TAny*>& aArrayOfObservers, const TAny* aObserver);
public:
	CCoeRedrawer* iRedrawer;
	CCoeFepTracker* iFepTracker;
	CCoeFepLoader* iFepLoader;
	TFep iFep;
	CHighPriorityActive* iHighPriorityActive;
	RArray<TInt> iResFileAccessCount;
	TPriQue<CCoeStatic> iCoeStaticList;
	CVwsSessionWrapper* iVwsSession;
	CCoeFontProvider* iDefaultFontProvider; 
	TZoomFactor iZoomFactor;
	CCoeTextDrawerBase* iDefaultTextDrawer;
	TInt iAppStartupInstrumentationEventIdBase;
	TBool iControlState;
	TInt iSupportedPointers;
	RPointerArray<CScreenItem> iArrayOfScreenItems;
private:
	RArray<TAny*> iArrayOfObserversOfLoadedFep;
	RArray<TAny*> iArrayOfFocusObservers;
	RArray<TAny*> iArrayOfForegroundObservers;
	RArray<TAny*> iArrayOfMessageObservers;
	RArray<TAny*> iArrayOfFepObservers;
	RArray<TAny*> iArrayOfResourceChangeObservers;
	RArray<TAny*> iArrayOfMessageMonitorObservers;
	RMutex iMutex;
	};

#endif

