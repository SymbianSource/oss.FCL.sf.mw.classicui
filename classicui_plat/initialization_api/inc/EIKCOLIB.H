/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:
*
*/


#if !defined(__EIKCOLIB_H__)
#define __EIKCOLIB_H__

#include <eikaufty.h>
#include <f32file.h>
#include <e32base.h>
#include <eiklibry.h>
#include <eikbtgpc.h>
#include <eikspane.h>
#include <eikbgfty.h>
#include <lafmain.h>



class CEikAppUiFactory;
class CEikAppUi;

/**
 * @internal
 * Do not use
 */
class CEikCoCtlLibrary : public CBase
	{
public:
	/**
	 * ResourceFile eikcoctl.rsc file name
	 */
	IMPORT_C static TFileName				ResourceFile();
	/**
	 * ControlFactory provides ability to create controls by id number.
	 */
	IMPORT_C static TCreateByTypeFunction	ControlFactory();
	/**
     * Factory to create buttongroups
     */
	IMPORT_C static TCreateButtonGroupByTypeFunction ButtonGroupFactory();
public:
	static SEikControlInfo CreateByTypeL(TInt aControlType);
	static MEikButtonGroup* CreateButtonGroupByTypeL(TInt aButtonGroupType,EikButtonGroupFactory::TCreationData& aCreationData,TBool& aAddToButtonGroupStack);
private:
	CEikCoCtlLibrary();
	};

class CEikToolBar;
class CEikMenuBar;
class CEikMenuPane;
class CEikCommandButton;
class CAknTouchPane;
class CEikAppUiFactoryExtension;
class CAknToolbar;
/**
 * @internal
 * Do not use
 */
class CEikAppUiFactory : public CBase, public MEikAppUiFactory, public MLafClientRectResolver
	{
public:
	IMPORT_C CEikAppUiFactory();
	~CEikAppUiFactory();
public: // from MEikAppUiFactory
	void CreateResourceIndependentFurnitureL(CEikAppUi* aAppUi);
	TRect ClientRect();
	void ReadAppInfoResourceL(TInt aResourceFileOffset, CEikAppUi* aAppUi);
	void LaunchPopupMenuL(
							TInt aResourceId,
							const TPoint& aTargetPos,
							TPopupTargetPosType aTargetType,
							const CEikHotKeyTable* aHotKeyTable,
							CEikAppUi* aAppUi);
	void DoLaunchPopupL(
							TInt aResourceId,
							const TPoint& aTargetPos, 
							const CEikHotKeyTable* aHotKeyTable, 
							TPopupTargetPosType aTargetType,
							CEikAppUi* aAppUi);
	void ClosePopup(CEikAppUi* aAppUi);
	void StopDisplayingMenuBar();
	void HandleSideBarMenuL(
							TInt aResourceId,
							const TPoint& aPos,
							const CEikHotKeyTable* aHotKeyTable,
							CEikAppUi* aAppUi);

	void CreateHotKeyControlL(TInt aResourceId, CEikAppUi* aAppUi);
	CEikMenuBar* MenuBar() const;
	CEikMenuBar* SwapMenuBar(CEikMenuBar* aMenu);
	CEikMenuPane* Popup() const;
	CEikButtonGroupContainer* SwapButtonGroup(CEikButtonGroupContainer* aNewGroup);
	CEikButtonGroupContainer* ToolBar() const;
	CEikToolBar* ToolBand() const;
	CEikToolBar* TitleBand() const;
	CEikToolBar* SwapToolBar(CEikToolBar* aToolBar,TToolBarType aType);
	CEikStatusPane* StatusPane() const;
	CEikButtonGroupContainer* Cba() const;

	CEikCommandButton* CreateStandardTabButtonL() const;
	void CreateEmbeddedL(CEikonEnv& aEikonEnv);
	void DestroyEmbedded(CEikonEnv& aEikonEnv);
	void HandleResourceChangeL(TInt aType);
public: // New functions
    IMPORT_C CAknTouchPane* TouchPane() const;
    	
    /**
     * Returns the pointer to the application avkon toolbar object if
     * there is one or NULL.
     * 
     * @return Pointer to the AVKON toolbar object
     * @since Series 60 3.1
     */
    IMPORT_C CAknToolbar* PopupToolbar() const;
    
    /** 
     * Returns the pointer to the current view avkon toolbar object if
     * there is one, if no it will return the pointer to the application 
     * avkon toolbar or NULL.
     *
     * @return Pointer to the AVKON toolbar object
     * @since Series 60 3.1
     */
    IMPORT_C CAknToolbar* CurrentPopupToolbar() const;
    
    /**
     * Sets the avkon toolbar for the current view. Called by CAknView when view is
     * activated.
     *
     * @param aViewPopupToolbar Pointer to the view specific toolbar.
     * @since Series 60 3.1
     */
    IMPORT_C void SetViewPopupToolbar(CAknToolbar* aViewPopupToolbar); 

    /** 
     * Returns the pointer to the current view avkon fixed toolbar object if
     * there is one, if no it will return the pointer to the application 
     * avkon fixed toolbar or NULL.
     *
     * @return Pointer to the AVKON toolbar object
     * @since S60 5.0
     */
    IMPORT_C CAknToolbar* CurrentFixedToolbar() const;


    /**
     * Sets the avkon fixed toolbar for the current view. Called by CAknView 
     * when view is activated.
     *
     * @param aViewFixedToolbar Pointer to the view specific fixed toolbar.
     * @since S60 5.0
     */
    IMPORT_C void SetViewFixedToolbar( CAknToolbar* aViewFixedToolbar ); 



private: // from MLafClientRectResolver
	void ReduceRect(TScreenFurniture aScreenFurniture,TRect& aRect) const;
private:
	void AddTitleBandL(CEikAppUi* aAppUi);
private: // from MObjectProvider
	TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
private:
	struct SEikAppInfo
		{
		TInt iHotKeysId;
		TInt iMenuBarId;
		TInt iToolBarId;
		TInt iToolBandId;
		TInt iCbaId;
		TInt iStatusPaneId;
        TInt iExtensionId; // link to extension resource struct.
		};
	struct SRssSignature
		{
		TInt iSignature;
		TInt iSelf;
		};
private:
	CEikButtonGroupContainer* iToolBar;
	CEikToolBar* iToolBand;
	CEikToolBar* iTitleBand;
	CEikMenuBar* iMenuBar;
	CEikMenuPane* iPopup;
	TInt iSidebarPopupId;
	CEikStatusPane* iStatusPane;
	// To avoid BC break, iCba is replaced with an extension containing iCba
	// and some additional items.
	//CEikButtonGroupContainer* iCba;
	CEikAppUiFactoryExtension* iExtension;
	};

#endif
