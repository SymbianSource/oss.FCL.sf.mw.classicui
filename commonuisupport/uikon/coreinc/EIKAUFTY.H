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
// Defines mix-in interace to break dependencey of Eikon Application UI 
// on controls
// 
//

#ifndef __EIKAUFTY_H__
#define __EIKAUFTY_H__

#include <f32file.h>
#include <e32base.h>
#include <eikdef.h>

#include <coemop.h>

class CEikHotKeyTable;
class CEikMenuBar;
class CEikMenuPane;
class CEikCommandButton;
class CEikToolBar;
class CEikButtonGroupContainer;
class CEikAppUi;
class CEikonEnv;
class CEikStatusPane;


/** This class defines a mixin interface to break the dependency of the Uikon Application 
User Interface on controls. 

@publishedAll 
@released */
class MEikAppUiFactory : public MObjectProvider
	{
public:
	virtual void CreateResourceIndependentFurnitureL(CEikAppUi* aAppUi) =0;
	virtual TRect ClientRect() = 0;
	virtual void ReadAppInfoResourceL(TInt aResourceFileOffset,CEikAppUi* aAppUi) = 0;
	virtual void LaunchPopupMenuL(	TInt aResourceId,
									const TPoint& aTargetPos,
									TPopupTargetPosType aTargetType,
									const CEikHotKeyTable* aHotKeyTable,
									CEikAppUi* aAppUi) = 0;

	virtual void DoLaunchPopupL(TInt aResourceId,const TPoint& aTargetPos, const CEikHotKeyTable* aHotKeyTable, 
								TPopupTargetPosType aTargetType,CEikAppUi* aAppUi) = 0;

   	virtual void ClosePopup(CEikAppUi* aAppUi) = 0;
	virtual void StopDisplayingMenuBar() = 0;
	virtual void HandleSideBarMenuL(TInt aResourceId,const TPoint& aPos,
									const CEikHotKeyTable* aHotKeyTable,CEikAppUi* aAppUi) = 0;
	virtual void CreateHotKeyControlL(TInt aResourceId, CEikAppUi* aAppUi) = 0;
	/** Gets a pointer to the menu bar.
	
	@return Pointer to the menu bar. */
	virtual CEikMenuBar* MenuBar() const = 0;
	/** Replaces or clears a menu bar, returning a pointer to the replaced menu bar.
	
	@param aMenu The new menu bar. This can be NULL to clear an existing menu bar. 
	@return Pointer to the replaced menu bar. */
	virtual CEikMenuBar* SwapMenuBar(CEikMenuBar* aMenu) = 0;
	virtual CEikMenuPane* Popup() const = 0;
	/** Gets a pointer to the tool bar.
	
	@return Pointer to the tool bar. */
	virtual CEikButtonGroupContainer* ToolBar() const = 0;
	/** Replaces or clears a button group, returning a pointer to the replaced button 
	group.
	
	@param aNewGroup The new button group. This can be NULL to clear an existing 
	button group. 
	@return Pointer to the replaced button group. */
	virtual CEikButtonGroupContainer* SwapButtonGroup(CEikButtonGroupContainer* aNewGroup) = 0;
	/** Gets a pointer to the tool band.
	
	@return Pointer to the tool band. */
	virtual CEikToolBar* ToolBand() const = 0;
	/** Gets a pointer to the title band.
	
	@return Pointer to the title band. */
	virtual CEikToolBar* TitleBand() const = 0;
	/** Gets a pointer to the status pane.
	
	@return Pointer to the status pane */
	virtual CEikStatusPane* StatusPane() const = 0;
	/** Gets a pointer to the CBA. 
	
	@return Pointer to the CBA */
	virtual CEikButtonGroupContainer* Cba() const = 0;
	inline CEikToolBar* SwapToolBand(CEikToolBar* aToolBand);
	inline CEikToolBar* SwapTitleBand(CEikToolBar* aTitleBand);
	/** Creates a standard tab button.
	
	@return Pointer to the created tab button. */
	virtual CEikCommandButton*  CreateStandardTabButtonL() const = 0;
	virtual void CreateEmbeddedL(CEikonEnv& aEikonEnv) = 0;
	virtual void DestroyEmbedded(CEikonEnv& aEikonEnv) = 0;
	virtual void HandleResourceChangeL(TInt aType) = 0;
protected:
	/** Defines the type of tool bar. */
	enum TToolBarType
		{
		/** Defines a band tool bar. */
		EBand,
		/** Defines a title tool bar. */
		ETitle
		};
private:
	virtual CEikToolBar* SwapToolBar(CEikToolBar* aToolBar,TToolBarType aType) = 0;
	};



/** Replaces or clears a tool band, returning a pointer to the replaced tool band.

@param aToolBand The new tool band. This can be NULL to clear an existing 
tool band. 
@return Pointer to the replaced tool band. */
inline CEikToolBar* MEikAppUiFactory::SwapToolBand(CEikToolBar* aToolBand)
	{return SwapToolBar(aToolBand,EBand);}


/** Replaces or clears a title band, returning a pointer to the replaced title 
band.

@param aTitleBand The new title band. This can be NULL to clear an existing 
title band. 
@return Pointer to the replaced title band. */
inline CEikToolBar* MEikAppUiFactory::SwapTitleBand(CEikToolBar* aTitleBand)
	{return SwapToolBar(aTitleBand,ETitle);}

#endif	// __EIKAUFTY_H__
