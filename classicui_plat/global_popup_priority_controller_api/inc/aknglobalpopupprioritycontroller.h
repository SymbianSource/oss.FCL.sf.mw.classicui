/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  System for managing global popup window priorities
*
*/


#ifndef AKNGLOBALPOPUPPRIORITYCONTROLLER_H
#define AKNGLOBALPOPUPPRIORITYCONTROLLER_H

#include <e32std.h>
#include <coeaui.h>

class MAknFadedComponent;
class TAknPopupFader;

/**
 * AknGlobalPopupPriorityController is the public interface
 * of the Popup Priority Controller system. This system is
 * used in place of other window position, window group position,
 * control stack and fade stack
 * APIs to give correct behavior when prioritised
 * notifiers and other global popups are displayed.
 * The system works by allowing popups to be associated with
 * a priority. When the system is enabled and a popup is shown,
 * the app's window group will be brought forward to a priority
 * of ECoeWinPriorityAlwaysAtFront + (highest shown popup priority).
 * The app's window group is pushed to the background when no
 * popups are displayed.
 * Therefore this system should only be enabled for applications
 * who only display popup windows, ie the notifier host apps.
 * @since 3.2
 * @capability SwEvent is required to display popups at global priorities.
 */
class AknGlobalPopupPriorityController
	{
public:
	/**
	* Enables the Popup Priority Controller in this app.
	* Before this function is called, all other functions in
	* this API have no effect.
	* It is safe to use the other APIs in all apps. They will only
	* have effect where the system is enabled.
 	*/
	IMPORT_C static void EnablePriorityControlL();
	/**
	* Set whether global popups are to be shown or not.
	* If global popups are not allowed, the app's window group
	* will be pushed to the background.
	* Callers will need SwEvent
	* @param aAllow, ETrue if global popups can be shown, EFalse if not.
	*/
	IMPORT_C static void AllowGlobalPopups(TBool aAllow);
	/**
	 * Return whether global popups are to be shown or not.
	 */
	IMPORT_C static TBool GlobalPopupsAllowed();
	/**
	* Sets the priority for a popup control.
	* The priority affects two things, how the popup is displayed
	* in relation to other popups and how the app is displayed in
	* relation to other apps.
	* Popups with higher priority will have their windows placed
	* before popups with lower priority.
	* The app's window group priority will be affected by the
	* highest priority popup shown.
	* If a popup does not have a priority set, it is automatically
	* given the default value of 0. Low priority popups should be
	* given negative priority values. High priority popups should
	* be given positive priority values.
	* @param aPopup, the popup control whose priority is to be set.
	* @param aPriority, the priority of the popup.
	*/
	IMPORT_C static void SetPopupPriorityL(CCoeControl& aPopup, TInt aPriority);
	/**
	* Removes a popup from the set of shown popups and forgets
	* the popup parameters. When a popup is set with any of the
	* other APIs in this class,
	* this function must be called when the popup is deleted.
	* The common popup classes CEikDialog, CAknChoiceList,
	* and CAknPopupList all call this from their destructors, in case
	* their clients set a priority for them.
	*/
	IMPORT_C static void RemovePopupPriority(CCoeControl& aPopup);
	/**
	* Sets whether a popup is shown or not, which can affect the 
	* popup's window priority, the app's window group priority,
	* the control stack and the fade stack.
	* When a popup is shown, it is added to a list of shown popups
	* and its window priority is set according to the position in this
	* list. If the highest priority popup changes, the window
	* group priority for the app is changed according to the new
	* highest priority popup.
	* The highest priority popup will also be activated on the control stack
	* and placed at the top of the fade stack.
	* @param aPopup, the popup which is having its shown status set.
	* @param aShow, ETrue if the popup is being shown, EFalse otherwise.
	*/
	IMPORT_C static void ShowPopup(CCoeControl& aPopup, TBool aShow);
	/**
	* Sets the ordinal position for the Eikon environment's root window group,
	* that will be used when a popup is shown.
	* @param aOrdinalPosition the ordinal position which the window group will
	* use when showing popups. Note, ordinal position only affects windows groups
	* with the same ordinal priority. Since popup priority affects window group
	* ordinal priority, setting the ordinal position will have only a minor effect.
	*/
	IMPORT_C static void SetRootWinOrdinalPosition(TInt aOrdinalPosition);
	/**
	* Adds a sub-popup to a parent popup. For instance a softkey control could
	* be added to a global note popup window.
	* The sub-popup's window and control stack positions will be changed as
	* its parent's positions are changed.
	* A popup may have at most one sub-popup and one parent popup.
	* @param aPopup the parent popup which will be have the sub popup added to it.
	* @param aSubPopup the sub popup which is to follow the control stack and
	* window position behavior of its parent.
	*/
	IMPORT_C static void AddSubPopupL(CCoeControl& aPopup, CCoeControl& aSubPopup);
	/**
	* Puts a popup on the control stack with the specified priority and flags.
	* If the popup (or its ultimate parent if it's a sub-popup) are not the
	* highest priority popup, the control stack flags ECoeStackFlagRefusesAllKeys
	* and ECoeStackFlagRefusesFocus will be added in. This makes the popup behave
	* like a sleeping dialog while in the background. For correct behavior, 
	* the priority and flag parameters should be set as if the popup were in the foreground.
	* This function analogous to CCoeAppUi::AddToStackL, and should be used in place
	* of that for controls which may be used as global popups. When global popups
	* are not enabled, this function forwards the call to CCoeAppUi::AddToStackL.
	* It is still the responsibility of the calling code to remove popups from the
	* control stack using CCoeAppUi::RemoveFromStack.
	* @param aPopup the popup or sub-popup which should be added to the control stack.
	* @param aPriority the control stack priority for this popup
	* @param aStackingFlags the control stack flags for this popup
	*/
	IMPORT_C static void AddPopupToControlStackL(CCoeControl& aPopup,TInt aPriority=ECoeStackPriorityDefault,TInt aStackingFlags=ECoeStackFlagStandard);
	/**
	* Modifies the control stack flags as appropriate for a sleeping popup.
	* This function is analogous to CEikonEnv::RouseSleepingDialog. When global popups
	* are not enabled, this function forwards the call to CEikonEnv::RouseSleepingDialog.
	* @param aPopup the popup which should be roused.
	* @param aRoused whether the popup should be roused or sent back to sleep.
	*/
	IMPORT_C static void RouseSleepingPopup(CCoeControl& aPopup, TBool aRoused);
	/**
	* This allows the global priority controller to control fade such that the
	* top global popup is unfaded, and all other windows are faded.
	* This function is analogous to TAknPopupFader::FadeBehindPopup. When global popups
	* are not enabled, this function forwards the call to TAknPopupFader::FadeBehindPopup.
	* @param aPopup the popup to which the fade parameters apply
	* @param aFader the TAknPopupFader normally used by the popup (nb this is not
	* stored, so can be temporary).
	* @param aFadedComponent the faded component interface, allowing access to the
	* components of the popup.
	* @param aFade whether the screen behind the popup should be faded or not.
	*/
	IMPORT_C static void FadeBehindPopup(CCoeControl& aPopup, TAknPopupFader& aFader, MAknFadedComponent& aFadedComponent, TBool aFade);
	};


#endif
