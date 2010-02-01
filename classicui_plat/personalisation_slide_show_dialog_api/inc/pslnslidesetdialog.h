/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Base slideset settings dialog.
*
*/


#ifndef C_PSLNSLIDESETDIALOG_H
#define C_PSLNSLIDESETDIALOG_H

#include <pslnslidesetdialoginterface.h>
#include <aknsettingpage.h>
#include <ConeResLoader.h>
#include <eikclb.h>

class CPslnSlideSetDialogContainer;
class CEikTextListBox;
class CPslnSlideSetModel;

/**
 *  Provides the base dialog functionality for defining Slide Set Settings
 *  for wallpapers and screensavers.
 *
 *  To use this from code, instantiate the ECOM plugin, then call ExecuteLD.
 *  See details from pslnslidesetwallpaperdialog.h and 
 *  pslnslidesetscreensaverdialog.h.
 *
 *  @lib pslnslidesetdialog.dll
 *  @since S60 3.2
 */
class CPslnSlidesetDialog:
    public CPslnSlidesetDialogInterface,
    public MEikListBoxObserver, 
    public MAknSettingPageObserver
    {
public:

    /**
    * Constructs all common parts of the dialog.
    * @param aType type of slide set (wallpaper or screen saver).
    *
    * See CPslnSlidesetDialogInterface::TPslnSlideSetDialogType for valid values.
    */
    void BaseConstructL( const TInt aType );

    /**
    * Symbian two-phase constructor.
    */
    virtual void ConstructL() = 0;

    /**
    * Creates listbox items.
    */
    virtual void CreateListBoxItemsL() = 0;

    /**
    * Destructor
    */
    virtual ~CPslnSlidesetDialog();

    /**
    * Returns listbox's current item index.
    * @return current item index.
    */
    TInt CurrentItemIndex() const;

    /**
    * Sets current item index for listbox and re-draws screen.
    * @param aNewIndex new index.
    */
    void SetCurrentItemIndexAndDraw( TInt aNewIndex );

    /**
    * Checks if feature is supported.
    * @param aFeatureID feature ID.
    * @return ETrue if feature is supported, EFalse otherwise.
    */
    TBool IsFeatureSupported( TInt aFeatureID );

protected:

    /**
    * C++ default constructor.
    */
    CPslnSlidesetDialog();

    /**
    * Sets title pane text.
    * @param aResourceId resource ID of title text to use.
    */
    void SetTitlePaneL( const TInt aResourceId );

    /**
    * Makes one specific folder name item.
    * @param aIndex item index to create.
    */
    void MakeItemL( const TInt aIndex );

    /**
    * Sets middle softkey label.
    * @param aResourceId resource ID of label text to use.
    * @param aCommandId command to place to middle softkey.
    */
    void SetMiddleSoftKeyLabelL( 
        const TInt aResourceId, 
        const TInt aCommandId );

    /**
    * From CEikDialog. Prelayouts the dialog.
    */
    void PreLayoutDynInitL();

    /**
    * From CAknDialog.
    * Called by framework to process commands invoked by the user.
    */
    void ProcessCommandL( TInt aCommandId );

    /**
    * From CEikDialog. Checks if it is okay to exit the dialog.
    */
    TBool OkToExitL( TInt aButtonId );

private:

    /**
    * From CAknDialog.
    * Called by framework to dynamically manipulate the menu
    * for the dialog.
    */
    void  DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );

    /**
    * From CAknDialog.
    * Called by framework to notify resize of dialog.
    */
    void SizeChanged();

    /**
    * From CCoeControl.
    * Key Handling Method for control.
    */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                 TEventCode aType );

    /**
    * From MAknSettingPageObserver.
    */
    void HandleSettingPageEventL(
        CAknSettingPage* aSettingPage,
        TAknSettingPageEvent aEventType );

    /**
    * From CCoeControl.
    * Handles resource changes.
    */
    void HandleResourceChange( TInt aType );

    /**
    * From CCoeControl 
    * Handles list focus changes.
    */
    void FocusChanged( TDrawNow aDrawNow );

    /**
    * From CCoeControl. 
    */
    TInt CountComponentControls() const;

    /**
    * From CCoeControl. 
    */
    CCoeControl* ComponentControl( TInt aIndex ) const;

    /* 
    * From MEikListBoxObserver. Handle listbox events.
    */
    void HandleListBoxEventL(
        CEikListBox* aListBox, 
        TListBoxEvent aEventType );

    /* 
    * Creates listbox items. 
    */
    void CreateSettingsListL();

    /* 
    * Handles list box selection based on active index 
    */
    void HandleListBoxSelectionL();

    /**
    * Show slide set type setting page. 
    */
    virtual void ShowSlideSetTypeSelectionL();

    /** 
    * Show backlight period setting page. Empty implementation. 
    */
    virtual void ShowBacklightSliderL();

    /** 
    * Show slide set duration setting page. Empty implementation. 
    */
    virtual void ShowDurationSliderL();

    /**
    * Show slide set image interval peridod setting page. Empty implementation. 
    */
    virtual void ShowIntervalListL();

    /**
    * Show slide set image list. 
    */
    TBool ShowSlideSetImageListL();

    /**
    * Removes caller's navi pane and replaces it with default navi pane.
    * When dialog is closed, previous navi pane is reapplied. 
    */
    void ToggleDefaultNaviPaneL( const TBool aNaviPaneVisible );

    /**
    * Updates dialog with new value.
    */
    void UpdateDialogL( const TInt aSettingId );

    /**
    * Sets current value of setting page to listbox.
    */
    void SetSettingPageValueToListL( 
        const CDesCArrayFlat& aArray,
        const TInt aCurrentIndex, 
        const TInt aCurrentValue, 
        const TBool aNumericConversionNeeded );

    /**
    * Sets current value of slider page to listbox.
    */
    void SetSliderValueToListL( 
        const TInt aCurrentIndex,
        const TInt aCurrentValue, 
        const TInt aResourceID );

    /**
    * Selects correct resource string to use with setting item.
    */
    TInt SelectResourceStringForImages( TInt aCurrentValue );

    /**
    * Starts MGFetch.
    */
    void HandleLaunchMGFetchL();

protected: // data

    /**
    * List of setting items. 
    * Own.
    */
    CDesCArrayFlat* iItems;

    /**
    * Listbox.
    * Own.
    */
    CEikTextListBox* iListBox;

    /**
    * Setting items for slide set interval setting page.
    * Own.
    */
    CDesCArrayFlat* iIntervalItems;

    /**
    * Slide set model.
    * Own.
    */
    CPslnSlideSetModel* iModel;

    /**
    * Is the dialog launched for activation and configuration, 
    * or configuration only?
    */
    TInt iLaunchMode;

    /**
    * Setting items for slide set type setting page.
    * Own.
    */
    CDesCArrayFlat* iSlideSetTypeItems;


private:

    /**
    * List of items in listbox.
    * Not own (owned by listbox).
    */
    CDesCArray* iItemArray;

    /**
    * Type of dialog.
    * Values according to TPslnSlideSetDialogType.
    */
    TInt iType;

    /**
    * Offset of resource file.
    */
    TInt iResourceOffset;

    /**
    * Defines which features are supported.
    */
    TBitFlags iFeaturesSupport;

    /**
    *
    * Own.
    */
    const HBufC* iPreviousTitleTxt;

    /**
    * ETrue, when MGFetch has been started.
    */
    TBool iMGFetchRunning;
    };


#endif // C_PSLNSLIDESETDIALOG_H
