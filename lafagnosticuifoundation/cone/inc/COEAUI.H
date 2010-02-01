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

#ifndef __COEAUI_H__
#define __COEAUI_H__

#include <e32std.h>
#include <e32base.h>
#include <w32std.h>
#include <coedef.h>
#include <coehelp.h>
#include <coeview.h>
#include <coeinput.h>

#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <vwsdef.h>
#endif //SYMBIAN_ENABLE_SPLIT_HEADERS


class CCoeEnv;
class CCoeControl;

/**
Creates a FEP interface object.

@publishedAll
@released
*/
typedef CCoeFep* (*TCoeFepFactoryFunctionL)(CCoeEnv& aConeEnvironment, const TDesC& aFullFileNameOfDll, const CCoeFepParameters& aFepParameters);

/**
Calls the second ordinal function of the FEP for which the settings dialog is to be executed.

@publishedAll
@released
*/
typedef void (*TCoeSynchronouslyExecuteFepSettingsDialogFunctionL)(CCoeEnv& aConeEnvironment, const TDesC& aFullFileNameOfDll);

/** Stack priority flags.
  
Controls with higher priorities get offered key events before controls	
with lower priorities.	  
		
@publishedAll 
@released */
enum
	{
	/** 0 */
	ECoeStackPriorityDefault=0,
	/** 10 */
	ECoeStackPriorityMenu=10,
	/** 50 */
	ECoeStackPriorityDialog=50,
	/** 60 */
	ECoeStackPriorityCba=60,
	/** 200 */
	ECoeStackPriorityAlert=200,
	/** 240 */
	ECoeStackPrioritySoftkey=240,
	/** 250 */
	ECoeStackPriorityFep=250,
	/** 300 */
	ECoeStackPriorityEnvironmentFilter=300
	};


/** Control stack flags.

Each control on the stack has a set of these flags which can be used 
to refuse to accept key events and to refuse requests for focus.

@publishedAll 
@released */
enum
	{
	/** The default value */
	ECoeStackFlagStandard			= 0,	
	/** The control does not accept key events. */
	ECoeStackFlagRefusesAllKeys		= 0x01,
	/** The control does not accept keyboard focus. */
	ECoeStackFlagRefusesFocus		= 0x02,
	/** The control is owned and deleted by the stack. */
	ECoeStackFlagOwnershipTransfered= 0x04,	
	/** The control is also added to the stack of any embedded app UI. For 
	example, an alert dialog added through CEikonEnv will be 
	shared on the stack of all embedded app UIs that may appear in the 
	application. */
	ECoeStackFlagSharable			= 0x08
	};

class CCoeControlStack;
class CCoeViewManager;

/** Application user interface (app UI) base class. 

The app UI's responsibilities include owning the application's control stack and views, 
handling user commands, (see the derived class CEikAppUi), and handling events sent by 
the OS to the application, for instance being brought to the foreground.

The UI framework class CEikAppUi is derived from this class. UIs may derive 
further to add their own UI-specific features to the app UI; each application must 
derive its own concrete app UI class from this.

@publishedAll 
@released */
class CCoeAppUi : public CBase
	{
public:
	// Construction and destruction
	IMPORT_C CCoeAppUi();
	IMPORT_C ~CCoeAppUi();
	IMPORT_C void ConstructL(CCoeAppUi* aPrevious=NULL);
	// Control stack
	IMPORT_C void AddToStackL(const MCoeView& aView,CCoeControl* aControl,TInt aPriority=ECoeStackPriorityDefault,TInt aStackingFlags=ECoeStackFlagStandard);
	IMPORT_C void AddToStackL(CCoeControl* aControl,TInt aPriority=ECoeStackPriorityDefault,TInt aStackingFlags=ECoeStackFlagStandard);
	IMPORT_C void RemoveFromStack(CCoeControl* aControl);
	IMPORT_C void HandleStackChanged();
	IMPORT_C void HandleStackedControlsResourceChange(TInt aType);
	IMPORT_C void UpdateStackedControlFlags(CCoeControl* aControl,TInt aFlags,TInt aMask);
	// Help context
	IMPORT_C CArrayFix<TCoeHelpContext>* AppHelpContextL() const;
	// Text input
	IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;
	// Control focus
	IMPORT_C CCoeControl* TopFocusedControl() const;
	// Utility
	IMPORT_C TBool IsDisplayingMenuOrDialog() const; 
	IMPORT_C TBool IsDisplayingDialog() const; 
	IMPORT_C TBool IsDisplayingControlBetweenPriorities(TInt aLowerPriority, TInt aHigherPriority) const;
	// View registration
	IMPORT_C void RegisterViewL(MCoeView& aView);
	IMPORT_C void DeregisterView(const MCoeView& aView);
	IMPORT_C void SetDefaultViewL(const MCoeView& aView);
	IMPORT_C TInt GetDefaultViewId(TVwsViewId& aViewId) const;
	// Pseudo-view registration
	IMPORT_C void CheckInitializeViewsL(TUid aAppUid);
	IMPORT_C void RegisterApplicationViewL(TUid aAppUid);
	IMPORT_C void DeregisterApplicationView();
	// View construction
	IMPORT_C TBool IsViewConstructed(const TVwsViewId& aViewId) const;
	// View activation
	IMPORT_C void ActivateViewL(const TVwsViewId& aViewId);
	IMPORT_C void ActivateViewL(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage);
	IMPORT_C void ActivateTopViewL();
	IMPORT_C void CreateActivateViewEventL(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage);
	IMPORT_C void DeactivateActiveViewIfOwnerMatchL();
	IMPORT_C void DeactivateActiveViewL();
	IMPORT_C TInt GetActiveViewId(TVwsViewId& aViewId) const;	
	// View registration 
	IMPORT_C void AddViewObserverL(MCoeViewObserver* aViewObserver);
	IMPORT_C void RemoveViewObserver(MCoeViewObserver* aViewObserver);
	// View activation observer
	IMPORT_C void AddViewActivationObserverL(MCoeViewActivationObserver* aViewActivationObserver);
	IMPORT_C void RemoveViewActivationObserver(MCoeViewActivationObserver* aViewActivationObserver);
	IMPORT_C void NotifyNextActivation(const TVwsViewId& aViewId, MCoeViewActivationObserver& aViewActivationObserver);
	IMPORT_C void NotifyNextActivation(MCoeViewActivationObserver& aViewActivationObserver);
	IMPORT_C TBool CheckSourceOfViewSwitchL(const TSecurityPolicy& aSecurityPolicy,const char* aDiagnostic=NULL) const;
	// View decativation observer
	IMPORT_C void AddViewDeactivationObserverL(MCoeViewDeactivationObserver* aViewDeactivationObserver);
	IMPORT_C void RemoveViewDeactivationObserver(MCoeViewDeactivationObserver* aViewDeactivationObserver);
	IMPORT_C void NotifyNextDeactivation(const TVwsViewId& aViewId, MCoeViewDeactivationObserver& aViewDeactivationObserver);
	IMPORT_C void NotifyNextDeactivation(MCoeViewDeactivationObserver& aViewDeactivationObserver);
	// View session configuration
	IMPORT_C TInt EnableExternalViewSwitches(TBool aEnable);
	IMPORT_C void UpdateViewServerBackgroundColor(const TRgb& aBgColor);

	// New APIs
	IMPORT_C void SetCustomControl(TInt aCustomControl);
	IMPORT_C TInt GetTopViewId(TVwsViewId& aViewId) const;
	IMPORT_C void SetWindowGroupOrdinal(TInt aWindowGroupOrdinal);

public: // Internal
	IMPORT_C void SetApplicationViewAsDefaultL(); // internalTechnology
 	IMPORT_C void SetSystemDefaultViewL(const TVwsViewId& aViewId,TInt aMode); // internalTechnology
 	IMPORT_C void SetSystemDefaultViewL(const TVwsViewId& aViewId); // internalTechnology
 	IMPORT_C void GetSystemDefaultViewL(TVwsViewId& aViewId); // internalTechnology
	IMPORT_C virtual void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination);
	IMPORT_C virtual void PrepareToExit();
protected: // Internal
	IMPORT_C virtual void HandleScreenDeviceChangedL();
private: // Internal
	IMPORT_C virtual TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C virtual void HandleForegroundEventL(TBool aForeground);
	IMPORT_C virtual void HandleSwitchOnEventL(CCoeControl* aDestination);
	IMPORT_C virtual void HandleSystemEventL(const TWsEvent& aEvent);
	IMPORT_C virtual void HandleApplicationSpecificEventL(TInt aType,const TWsEvent& aEvent);
	IMPORT_C virtual void SetAndDrawFocus(TBool aFocus);
	IMPORT_C virtual CArrayFix<TCoeHelpContext>* HelpContextL() const;
public: // Internal
	IMPORT_C virtual TBool FrameworkCallsRendezvous() const;
public: // Internal 
	IMPORT_C void WriteInternalStateOfStackedControlsL(RWriteStream& aWriteStream) const; // internalTechnology
public: // Deprecated. Do not use!
	IMPORT_C void RegisterViewAndAddStackL(MCoeView& aView);	// deprecated
	IMPORT_C void DeregisterViewAndRemoveStack(const MCoeView& aView);	// deprecated
	IMPORT_C void RemoveFromViewStack(const MCoeView& aView,CCoeControl* aControl);	// deprecated
	IMPORT_C void UpdateViewStackedControlFlags(const MCoeView& aView,CCoeControl* aControl,TInt aFlags,TInt aMask);	// deprecated
	IMPORT_C void AddToViewStackL(const MCoeView& aView,CCoeControl* aControl,TInt aPriority=ECoeStackPriorityDefault,TInt aStackingFlags=ECoeStackFlagStandard);	// deprecated
public: // not exported
	TBool IsControlOnStack(CCoeControl* aControl) const;
	void SetCurrentControlStackGroupId(TInt aGroupId);
	void NotifyFontChange(const CCoeFontProvider& aFontProvider); 
	void RefetchPixelMappingL();
private:
	enum TRemoveCondition
		{
		ERemoveUnconditionally,
		ERemoveOnlyIfSharable
		};
private:// Internal
	IMPORT_C virtual void CCoeAppUi_Reserved_2();
private:
	CCoeControl* TopFocusableControl() const;
	TInt FindPos(CCoeControlStack* aStack,CCoeControl* aControl) const;
	void SetFocusToControl(CCoeControl* aControl,TBool aFocus);
	void DoAddToStackL(CCoeControlStack* aStack,CCoeControl* aControl,TInt aPriority,TInt aStackingFlags);
	void DoAddToStackL(CCoeControlStack* aStack,CCoeControl* aControl,TInt aPriority,TInt aStackingFlags, TInt aGroupId);
	void DoRemoveFromStack(CCoeControlStack* aStack,CCoeControl* aControl,TRemoveCondition aRemoveCondition=ERemoveUnconditionally);
	void DoUpdateStackedControlFlags(CCoeControlStack* aStack,CCoeControl* aControl,TInt aFlags,TInt aMask);
public:
/**Monitor function for passing all windows events to registered monitor observers for optional inspection*/
	void MonitorWsEvent(const TWsEvent& aEvent);
private:
	class CExtra;
	friend class CExtra;
	friend class CTestDriver;
protected:
	CCoeEnv* iCoeEnv;
private:
	CCoeViewManager* iViewManager;
	CCoeControlStack* iStack;
	CExtra* iExtra;
	TInt iCCoeAppUi_Reserved1;
	};


#endif // __COEAUI_H__
