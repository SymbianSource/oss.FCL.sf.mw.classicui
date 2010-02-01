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

#include <coemain.h>
#include <coecntrl.h>
#include <eikmobs.h>
#include <barsread.h>
#include <eikenv.h>
#include <eikappui.h>
#include <uiklafgt/eikcore.rsg>
#include <clock.h>

//
// class MEikMenuObserver
//

/** Constructor for MEikMenuObserver */
EXPORT_C MEikMenuObserver::MEikMenuObserver()
	{
	}

EXPORT_C void MEikMenuObserver::HandleAttemptDimmedSelectionL(TInt /*aCommandId*/)
/** Responds to a user's attempt to select a dimmed item by displaying a message 
(CEikonEnv::InfoMsg()) to indicate the item is unavailable.

@param aCommandId Command ID for the menu item. */
    {
	CEikonEnv *env = CEikonEnv::Static();
	TBuf<RMessageWindow::EMaxTextLength> res;
	env->ReadResource( res, R_EIK_TBUF_NOT_AVAILABLE );
	if( res.Length() ) 
		env->InfoMsg(res);
    }

EXPORT_C void MEikMenuObserver::HandleSideBarMenuL(TInt /*aResourceId*/,const TPoint& /*aPos*/,TInt /*aModifiers*/,const CEikHotKeyTable* /*aTable*/)
/** This function is invoked by CEikMenuBar's input handling functions. 

It may be overridden to handle displaying menus launched from the side bar.

@param aResourceId Resource ID identifying the menu to launch.
@param aPos Position of the menu's reference point. For sidebar menus, this 
is the top-right corner.
@param aModifiers Key modifiers held when the menu was invoked.
@param aTable The menu bar's hotkey items. */
	{
	}

EXPORT_C TBool MEikMenuObserver::CheckHotKeyNotDimmedL(TInt /*CommandId*/)
/** Determines whether a command should be passed to the application.

Applications can choose whether to respond to a hotkey event that corresponds to a 
dimmed item. This function is called when a recognised key press is offered to a 
menu bar or a menu pane to determine whether to send the corresponding command.

@param aCommandId The command corresponding to the selected hotkey.
@return ETrue if the command should be passed to the application. This is the 
default. EFalse if the command should not be passed to the application. */
    {
	return ETrue;
    }

EXPORT_C void MEikMenuObserver::RestoreMenuL(CCoeControl* aMenuWindow,TInt aMenuId,TMenuType aMenuType)
/** Restores the menu window aMenuWindow.

@param aMenuWindow The menu window to be restored.
@param aMenuId The menu's ID.
@param aMenuType The type of menu being restored. */
    {
    TResourceReader reader;
    aMenuWindow->ControlEnv()->CreateResourceReaderLC(reader,aMenuId);
    aMenuWindow->ConstructFromResourceL(reader);
	CleanupStack::PopAndDestroy();
    if (aMenuType==EMenuPane)
        DynInitMenuPaneL(aMenuId,(CEikMenuPane*)aMenuWindow);
    else
        DynInitMenuBarL(aMenuId,(CEikMenuBar*)aMenuWindow);
    }

EXPORT_C void MEikMenuObserver::DynInitMenuPaneL(TInt /*aMenuId*/,CEikMenuPane* /*aMenuPane*/)
/** Dynamically initialises a menu pane. 

The Uikon framework calls this function, if it is implemented in a menu's 
observer, immediately before the menu pane is activated. 

Typically this function should inquire the value of application data, and 
initialise menu items accordingly. This includes dimming menu items, changing 
their text, setting the state of checked items and radio buttons and dynamically 
adding items to a menu. 

@param aMenuId Resource ID identifying the menu pane to initialise.
@param aMenuPane The in-memory representation of the menu pane. */
    {
    }

EXPORT_C void MEikMenuObserver::DynInitMenuBarL(TInt /*aMenuId*/,CEikMenuBar* /*aMenuBar*/)
/** As DynInitMenuPaneL(), but for menu bars.

@param aMenuId Resource ID identifying the menu bar to initialise.
@param aMenuBar The in-memory representation of the menu bar. */
    {
    }

EXPORT_C void MEikMenuObserver::OfferKeyToAppL(const TKeyEvent& /*aKeyEvent*/,TEventCode /*aType*/)
/** Called if a key which is not used by the menu is pressed while the observer's 
menu is displaying.

@param aKeyEvent The key event the menu is offering to the app.
@param aType Event code type. */
	{
	}

EXPORT_C void MEikMenuObserver::Reserved_1_MenuObserver()
	{}

EXPORT_C void MEikMenuObserver::Reserved_2_MenuObserver()
	{}

EXPORT_C void MEikMenuObserver::MEikCommandObserver_Reserved1()
	{
	}

EXPORT_C void MEikMenuObserver::MEikCommandObserver_Reserved2()
	{
	}

/**
This functions simpy wraps MEikCommandObserver::CreateCustomCommandControlL(TInt aControlType)
@param aControlType A custom control ID. 
@return @see MEikCommandObserver::CreateCustomCommandControlL(TInt aControlType)
*/	
EXPORT_C CCoeControl* MEikMenuObserver::CreateCustomCommandControlL(TInt aControlType)
	{
	return MEikCommandObserver::CreateCustomCommandControlL(aControlType);
	}


//
// class MEikCommandObserver
//

EXPORT_C CCoeControl* MEikCommandObserver::CreateCustomCommandControlL(TInt /*aControlType*/)
/** Glue for creating custom controls.

This function can be called to create custom controls on request from 
their control ID. Custom controls are user-supplied control 
classes. Given the ID of a custom control, this function should return 
a pointer to a newly-instantiated and fully constructed control. If 
the ID is unrecognised, NULL should be returned. The control returned 
will be owned by the caller.

@param aControlType A custom control ID.
@return By default, NULL. */
	{
	return(NULL);
	}


//
// class MEikAutoMenuObserver
//

EXPORT_C void MEikAutoMenuObserver::SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis)
/** Sets the specified control's emphasis.

@param aMenuControl The control for which emphasis is set. 
@param aEmphasis If ETrue the menu is emphasised. If EFalse the menu is not 
emphasised. */
	{
	CEikAppUi* appUi=CEikonEnv::Static()->EikAppUi();
	appUi->UpdateStackedControlFlags(aMenuControl,aEmphasis? 0: ECoeStackFlagRefusesFocus,ECoeStackFlagRefusesFocus);
	appUi->HandleStackChanged();
	}

EXPORT_C void MEikAutoMenuObserver::Reserved_1_MenuObserver()
	{}
	
EXPORT_C void MEikAutoMenuObserver::Reserved_2_MenuObserver()
	{
	}

EXPORT_C void MEikAutoMenuObserver::MEikCommandObserver_Reserved1()
	{
	}
	
EXPORT_C void MEikAutoMenuObserver::MEikCommandObserver_Reserved2()
	{
	}
	
EXPORT_C MEikAutoMenuObserver::MEikAutoMenuObserver()
	{
	}

// from MEikCommandObserver
EXPORT_C void MEikAutoMenuObserver::HandleAttemptDimmedSelectionL(TInt aCommandId)
	{
	MEikMenuObserver::HandleAttemptDimmedSelectionL(aCommandId);	
	}

EXPORT_C TBool MEikAutoMenuObserver::CheckHotKeyNotDimmedL(TInt aCommandId)
	{
	return MEikMenuObserver::CheckHotKeyNotDimmedL(aCommandId);
	}
	
EXPORT_C void MEikAutoMenuObserver::RestoreMenuL(CCoeControl* aMenuControl,TInt aResourceId,TMenuType aType)
	{
	MEikMenuObserver::RestoreMenuL(aMenuControl, aResourceId, aType);
	}
	
EXPORT_C void MEikAutoMenuObserver::DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane)
	{
	MEikMenuObserver::DynInitMenuPaneL(aResourceId, aMenuPane);
	}
	
EXPORT_C void MEikAutoMenuObserver::DynInitMenuBarL(TInt aResourceId,CEikMenuBar* aMenuBar)
	{
	MEikMenuObserver::DynInitMenuBarL(aResourceId, aMenuBar);
	}

EXPORT_C void MEikAutoMenuObserver::HandleSideBarMenuL(TInt aResourceId,const TPoint& aPos,TInt aModifiers,const CEikHotKeyTable* aTable)
	{
	MEikMenuObserver::HandleSideBarMenuL(aResourceId, aPos, aModifiers, aTable);
	}
	
EXPORT_C void MEikAutoMenuObserver::OfferKeyToAppL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	MEikMenuObserver::OfferKeyToAppL(aKeyEvent, aType);
	}
	
EXPORT_C CCoeControl* MEikAutoMenuObserver::CreateCustomCommandControlL(TInt aControlType)
	{
	return MEikMenuObserver::CreateCustomCommandControlL(aControlType);
	}

//
// MEikCommandObserver
//

/** Constructor for MEikCommandObserver */
EXPORT_C MEikCommandObserver::MEikCommandObserver()
	{
	}

/** Reserved for Future use */
EXPORT_C void MEikCommandObserver::MEikCommandObserver_Reserved1()
	{
	}
	
/** Reserved for Future use */
EXPORT_C void MEikCommandObserver::MEikCommandObserver_Reserved2()
	{
	}
