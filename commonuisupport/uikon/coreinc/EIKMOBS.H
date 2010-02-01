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

#ifndef __EIKMOBS_H__
#define __EIKMOBS_H__

#include <eikcmobs.h>
#include <w32std.h>
#include <coedef.h>

class CCoeControl;
class CEikMenuPane;
class CEikMenuBar;
class CEikHotKeyTable;
class TPoint;

/** Menu observer interface.

Menu observers cooperate with menu bars and menu panes, initialising them 
before display and responding to menu events appropriately. CEikAppUi implements 
MEikMenuObserver, so these functions may be implemented on an application's 
App UI.

@publishedAll
@released */
class MEikMenuObserver : public MEikCommandObserver
	{
public:
	/** Menu types */
	enum TMenuType
		{
		/** Menu pane. */
		EMenuPane,
		/** Menu bar. */
		EMenuBar
		};
public:
	IMPORT_C virtual void HandleAttemptDimmedSelectionL(TInt aCommandId);
	IMPORT_C virtual TBool CheckHotKeyNotDimmedL(TInt aCommandId);
	IMPORT_C virtual void RestoreMenuL(CCoeControl* aMenuControl,TInt aResourceId,TMenuType aType);
	IMPORT_C virtual void DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane);
	IMPORT_C virtual void DynInitMenuBarL(TInt aResourceId,CEikMenuBar* aMenuBar);
	IMPORT_C virtual void HandleSideBarMenuL(TInt aResourceId,const TPoint& aPos,TInt aModifiers,const CEikHotKeyTable* aTable);
	IMPORT_C virtual void OfferKeyToAppL(const TKeyEvent& aKeyEvent,TEventCode aType);
	/** Called by the Uikon framework to handle the emphasising or de-emphasising of 
	a menu window. 
	
	CEikMenuBar objects call this on their observer to emphasise 
	themselves when they are displayed, and de-emphasise themselves when they 
	stop displaying.
	
	@param aMenuControl The menu control.
	@param aEmphasis ETrue to emphasize the menu, EFalse otherwise. */
	virtual void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis)=0;
public:
	IMPORT_C virtual CCoeControl* CreateCustomCommandControlL(TInt aControlType);
protected:
	IMPORT_C MEikMenuObserver();
private:
	IMPORT_C virtual void Reserved_1_MenuObserver();
	IMPORT_C virtual void Reserved_2_MenuObserver();
private: // from MEikCommandObserver. do not override!
	IMPORT_C void MEikCommandObserver_Reserved1();
	IMPORT_C void MEikCommandObserver_Reserved2();
private:
	TInt iMEikMenuObserver_Spare1;
	};


/** Provides additional functionality to an auto menu title, in the form of an 
OfferHotKeyL() method, which is not required in the normal MEikMenuObserver.
 
Auto menu titles are used to ensure that some menu panes appear in every menu 
constructed for an application. 

@publishedAll 
@released */
class MEikAutoMenuObserver : public MEikMenuObserver
	{
public:
	/** Offers the specified hot key to the auto menu title.
	
	Implement this function if you expect to handle any events from an auto menu. 
	
	@param aKeyEvent The key event.
	@param aType The type of key event.
	@return The auto menu title's response. */
	virtual TKeyResponse OfferHotKeyL(const TKeyEvent& aKeyEvent,TEventCode aType)=0;
public: // from MEikMenuObserver
	IMPORT_C void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);
public: 
	IMPORT_C virtual void HandleAttemptDimmedSelectionL(TInt aCommandId);
	IMPORT_C virtual TBool CheckHotKeyNotDimmedL(TInt aCommandId);
	IMPORT_C virtual void RestoreMenuL(CCoeControl* aMenuControl,TInt aResourceId,TMenuType aType);
	IMPORT_C virtual void DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane);
	IMPORT_C virtual void DynInitMenuBarL(TInt aResourceId,CEikMenuBar* aMenuBar);
	IMPORT_C virtual void HandleSideBarMenuL(TInt aResourceId,const TPoint& aPos,TInt aModifiers,const CEikHotKeyTable* aTable);
	IMPORT_C virtual void OfferKeyToAppL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C virtual CCoeControl* CreateCustomCommandControlL(TInt aControlType);
protected:
	IMPORT_C MEikAutoMenuObserver();
private:
	IMPORT_C virtual void Reserved_1_MenuObserver();
	IMPORT_C virtual void Reserved_2_MenuObserver();
private: // from MEikCommandObserver. do not override!
	IMPORT_C void MEikCommandObserver_Reserved1();
	IMPORT_C void MEikCommandObserver_Reserved2();
private:
	TInt iMEikAutoMenuObserver_Spare1;
	};


#endif	// __EIKMOBS_H__
